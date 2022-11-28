//
// Created by loghin on 30.10.2021.
//

#ifndef CDS_ASYNC_HPP
#define CDS_ASYNC_HPP

#include <CDS/memory/UniquePointer>
#include <CDS/memory/SharedPointer>
#include <CDS/Semaphore>
#include <CDS/Memory>
#include <CDS/Function>
#include <CDS/Thread>

namespace cds {

    template < typename ReturnType, typename ... ArgumentTypes >
    class Async;

    template < typename T >
    class AsyncResult : public Object {
    private:
        UniquePointer < T > result;
        SharedPointer < Semaphore > asyncSemaphore { nullptr };

        AsyncResult() noexcept = default;

        explicit AsyncResult ( SharedPointer < Semaphore > && semaphore ) noexcept :
                asyncSemaphore ( std :: forward < SharedPointer < Semaphore > > ( semaphore ) ) {

        }

        AsyncResult ( AsyncResult && resultObject ) noexcept :
                result ( std :: forward < UniquePointer < T > > ( resultObject.result ) ),
                asyncSemaphore ( resultObject.asyncSemaphore ) {

        }

        template < typename ReturnType, typename ... ArgumentTypes >
        friend class Async;

    public:
        auto get () noexcept -> T {
            this->asyncSemaphore->wait();
            return * this->result;
        }
    };

    template < typename ReturnType, typename ... ArgumentTypes >
    class Async < ReturnType ( ArgumentTypes ... ) > : public Object {
    private:
        Function < ReturnType ( ArgumentTypes ... ) > function;
        UniquePointer < Thread > pThread { nullptr };

    public:
        inline explicit Async ( Function < ReturnType ( ArgumentTypes ... ) > const & function ) noexcept:
                function(function) {

        }

        inline auto operator () ( ArgumentTypes ... arguments ) noexcept -> AsyncResult < ReturnType > {
            AsyncResult < ReturnType > result ( Memory :: instance().create < Semaphore > () );

            auto threadTask = [& result, this, params = std :: make_tuple ( std :: forward < ArgumentTypes > ( arguments ) ... )] {
                result.result = Memory :: instance().create < ReturnType > ( std :: apply ( this->function, params ) );
                result.asyncSemaphore->notify();
            };

            this->pThread = Memory :: instance().create < Runnable < decltype ( threadTask ) > > ( threadTask );

            this->pThread->start();

            return result;
        }
    };

}

#endif //CDS_ASYNC_HPP
