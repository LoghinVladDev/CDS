//
// Created by loghin on 30.10.2021.
//

#ifndef CDS_ASYNC_HPP
#define CDS_ASYNC_HPP

#include <CDS/Pointer>
#include <CDS/Semaphore>

template < typename ReturnType, typename ... ArgumentTypes >
class Async;

template < typename ReturnType, typename ... ArgumentTypes >
class Async < ReturnType ( ArgumentTypes ... ) >;

template < typename T >
class AsyncResult : public Object {
private:
    UniquePointer < T > result;
    SharedPointer < Semaphore > asyncSemaphore { nullptr };

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
    auto get () noexcept -> T & {
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

    inline auto operator () ( ArgumentTypes ... arguments ) const noexcept -> AsyncResult < ReturnType > {
        AsyncResult < ReturnType > result;

        this->pThread = new Runnable ([& result] {

        });

        this->pThread->start();
    }
};

#endif //CDS_ASYNC_HPP
