//
// Created by loghin on 27.10.2021.
//

#ifndef CDS_GENERATOR_HPP
#define CDS_GENERATOR_HPP

#include <CDS/Semaphore>
#include <CDS/Thread>
#include <CDS/Boolean>

template < typename T, typename ... Args >
class Generator : public Object {
private:
    UniquePointer < T > pYieldedValue {nullptr};
    UniquePointer < T > pToReturnValue {nullptr};
    UniquePointer < Thread > pTaskThread {nullptr};

    Semaphore promiseObjectReady;
    Semaphore promiseObjectUsed;
    Boolean::Atomic firstCall {true};
    Boolean::Atomic lastCall {false};
    Boolean::Atomic running {false};

//    UniquePointer < std :: tuple < Args ... > > pArguments {nullptr};

protected:
    virtual auto task ( Args ... ) noexcept -> T = 0;

    template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
    auto yield ( T const & value, bool isFinal = false ) noexcept ( noexcept ( T ( value ) ) ) -> void {
        if ( ! this->firstCall )
            this->promiseObjectUsed.wait();
        else
            this->firstCall = false;

        this->pYieldedValue = new T (value);

        if ( isFinal )
            this->lastCall = true;

        this->promiseObjectReady.notify();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
    auto yield ( T && value, bool isFinal = false ) noexcept ( noexcept ( T ( std :: forward < T > ( value ) ) ) ) -> void {
        if ( ! this->firstCall )
            this->promiseObjectUsed.wait();
        else
            this->firstCall = false;

        this->pYieldedValue = new T ( std :: forward < T > (value) );

        if ( isFinal )
            this->lastCall = true;

        this->promiseObjectReady.notify();
    }

    template < typename V = T, typename std :: enable_if < ! Type < V > :: copyConstructible && Type < V > :: defaultConstructible && Type < V > :: copyAssignable, int > :: type = 0 >
    auto yield ( T const & value, bool isFinal = false ) noexcept ( noexcept ( T ( value ) ) ) -> void {
        if ( ! this->firstCall )
            this->promiseObjectUsed.wait();
        else
            this->firstCall = false;

        this->pYieldedValue = new T;
        * this->pYieldedValue = value;

        if ( isFinal )
            this->lastCall = true;

        this->promiseObjectReady.notify();
    }

    template < typename V = T, typename std :: enable_if < ! Type < V > :: moveConstructible && Type < V > :: defaultConstructible && Type < V > :: moveAssignable, int > :: type = 0 >
    auto yield ( T && value, bool isFinal = false ) noexcept ( noexcept ( T ( std :: forward < T > ( value ) ) ) ) -> void {
        if ( ! this->firstCall )
            this->promiseObjectUsed.wait();
        else
            this->firstCall = false;

        this->pYieldedValue = new T;
        * this->pYieldedValue = std :: forward < T > ( value );

        if ( isFinal )
            this->lastCall = true;

        this->promiseObjectReady.notify();
    }

private:
    auto singleCallReturnValue () noexcept (false) -> T * {
        this->promiseObjectReady.wait();
        this->pToReturnValue = this->pYieldedValue;

        if ( ! this->lastCall )
            this->promiseObjectUsed.notify();
        else
            this->running = false;

        return this->pToReturnValue.get();
    }

    auto restart ( Args && ... args ) noexcept -> void {
        this->firstCall = true;
        this->lastCall = false;
        this->promiseObjectUsed.reset();
        this->promiseObjectReady.reset();

        this->pTaskThread = new Runnable (
                [&] {
                    this->yield ( this->task ( std :: forward < Args > ( args ) ... ), true );
                }
        );

        this->pTaskThread->start();
        this->running = true;
    }

public:
    class IterableGenerator : public Object {
    public:
        class Iterator {
        private:
            ForeignPointer < T > mutable pData { nullptr };
            ForeignPointer < Generator > pGen { nullptr };

        public:
            explicit Iterator ( Generator * gen, bool ignore = false ) noexcept :
                    pGen(gen),
                    pData(nullptr) {

                if ( ! ignore )
                    this->pData = this->pGen->singleCallReturnValue();
            }

            operator T & () const noexcept {
                return this->value();
            }

            auto value () const noexcept -> T & { return * this->pData; }
            auto next () const noexcept -> Iterator & {
                if ( ! this->pGen->finished )
                    this->pData = this->pGen->singleCallReturnValue();
                else
                    this->pData == nullptr;

                return * this;
            }

            auto equals ( Iterator const & it ) const noexcept -> bool { return this->pData == it.pData; }
        };

    private:
        ForeignPointer < Generator > pGen { nullptr };

    public:

        operator T & () const noexcept {
            return * this->pGen->singleCallReturnValue();
        }

        using ConstIterator = Iterator;

        inline explicit IterableGenerator( Generator * pGen ) noexcept :
                pGen ( pGen ) {

        }

        auto begin () noexcept -> Iterator { return Iterator ( this->pGen ); }
        auto end () noexcept -> Iterator { return Iterator ( this->pGen, true ); }

        auto cbegin () const noexcept -> ConstIterator { return ConstIterator ( this->pGen ); }
        auto cend () const noexcept -> ConstIterator { return ConstIterator ( this->pGen, true ); }
    };

    auto operator () ( Args && ... args ) noexcept -> IterableGenerator {
        if ( ! this->running ) {
            if ( ! this->pTaskThread.isNull() ) {
                this->pTaskThread->join();
                this->pTaskThread.reset();
            }

            this->restart ( std::forward<Args>(args) ...);
        }

        return IterableGenerator ( this );
    }

    ~Generator () noexcept override {
        this->pTaskThread->kill();
    }
};

#endif //CDS_GENERATOR_HPP
