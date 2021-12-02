//
// Created by loghin on 27.10.2021.
//

#ifndef CDS_GENERATOR_HPP
#define CDS_GENERATOR_HPP

#include <CDS/Semaphore>
#include <CDS/Thread>
#include <CDS/Boolean>
#include <CDS/Memory>

namespace cds {

    template < typename C >
    class Sequence; // NOLINT(cppcoreguidelines-virtual-class-destructor)

    template < typename T, typename ... Args >
    class Generator : public Object { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    private:
        UniquePointer < T > pYieldedValue {nullptr}; // NOLINT(clion-misra-cpp2008-8-0-1)
        UniquePointer < T > pToReturnValue {nullptr}; // NOLINT(clion-misra-cpp2008-8-0-1)
        UniquePointer < Thread > pTaskThread {nullptr}; // NOLINT(clion-misra-cpp2008-8-0-1)

        Semaphore promiseObjectReady;
        Semaphore promiseObjectUsed;
        Boolean::Atomic firstCall {true}; // NOLINT(clion-misra-cpp2008-8-0-1)
        Boolean::Atomic lastCall {false}; // NOLINT(clion-misra-cpp2008-8-0-1)
        Boolean::Atomic running {false}; // NOLINT(clion-misra-cpp2008-8-0-1)
        Boolean::Atomic trap {false}; // NOLINT(clion-misra-cpp2008-8-0-1)

    protected:
        virtual auto task ( Args ... ) noexcept -> T = 0;

        template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
        __CDS_OptimalInline auto yield ( T const & value ) noexcept ( noexcept ( T ( value ) ) ) -> void {
            return this->yield ( value, false );
        }

        template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
        __CDS_MaybeUnused __CDS_OptimalInline auto yield ( T && value ) noexcept ( noexcept ( T ( std :: forward < T > ( value ) ) ) ) -> void {
            return this->yield ( std :: forward < T > ( value ), false );
        }

        template < typename V = T, typename std :: enable_if < ! Type < V > :: copyConstructible && Type < V > :: defaultConstructible && Type < V > :: copyAssignable, int > :: type = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        __CDS_OptimalInline auto yield ( T const & value ) noexcept ( noexcept ( T ( value ) ) ) -> void {
            return this->yield ( value, false );
        }

        template < typename V = T, typename std :: enable_if < ! Type < V > :: moveConstructible && Type < V > :: defaultConstructible && Type < V > :: moveAssignable, int > :: type = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        __CDS_MaybeUnused __CDS_OptimalInline auto yield ( T && value ) noexcept ( noexcept ( T ( std :: forward < T > ( value ) ) ) ) -> void {
            return this->yield ( std :: forward < T > ( value ), false );
        }

    private:
        template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
        __CDS_MaybeUnused auto yield ( T const & value, bool isFinal ) noexcept ( noexcept ( T ( value ) ) ) -> void {
            while ( this->trap ) {

            }

            if ( ! this->firstCall ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                this->promiseObjectUsed.wait();
            } else {
                this->firstCall = false;
            }

            this->pYieldedValue = Memory :: instance().create < T > (value);

            if ( isFinal ) {
                this->lastCall = true;
            }

            this->promiseObjectReady.notify();
        }

        template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
        __CDS_MaybeUnused auto yield ( T && value, bool isFinal ) noexcept ( noexcept ( T ( std :: forward < T > ( value ) ) ) ) -> void {
            while ( this->trap ) {

            }

            if ( ! this->firstCall ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                this->promiseObjectUsed.wait();
            } else {
                this->firstCall = false;
            }

            this->pYieldedValue = Memory :: instance().create < T > ( std :: forward < T > (value) );

            if ( isFinal ) {
                this->lastCall = true;
            }

            this->promiseObjectReady.notify();
        }

        template < typename V = T, typename std :: enable_if < ! Type < V > :: copyConstructible && Type < V > :: defaultConstructible && Type < V > :: copyAssignable, int > :: type = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        __CDS_MaybeUnused auto yield ( T const & value, bool isFinal ) noexcept ( noexcept ( T ( value ) ) ) -> void {
            while ( this->trap ) {

            }

            if ( ! this->firstCall ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                this->promiseObjectUsed.wait();
            } else {
                this->firstCall = false;
            }

            this->pYieldedValue = Memory :: instance().create < T > ();
            * this->pYieldedValue = value;

            if ( isFinal ) {
                this->lastCall = true;
            }

            this->promiseObjectReady.notify();
        }

        template < typename V = T, typename std :: enable_if < ! Type < V > :: moveConstructible && Type < V > :: defaultConstructible && Type < V > :: moveAssignable, int > :: type = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        __CDS_MaybeUnused auto yield ( T && value, bool isFinal ) noexcept ( noexcept ( T ( std :: forward < T > ( value ) ) ) ) -> void {
            while ( this->trap ) {

            }

            if ( ! this->firstCall ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                this->promiseObjectUsed.wait();
            } else {
                this->firstCall = false;
            }

            this->pYieldedValue = Memory :: instance().create < T > ();
            * this->pYieldedValue = std :: forward < T > ( value );

            if ( isFinal ) {
                this->lastCall = true;
            }

            this->promiseObjectReady.notify();
        }

    private:
        auto singleCallReturnValue () noexcept (false) -> T * {
            this->promiseObjectReady.wait();
            this->pToReturnValue = this->pYieldedValue;

            if ( ! this->lastCall ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                this->promiseObjectUsed.notify();
            } else {
                this->running = false;
            }

            return this->pToReturnValue.get();
        }

        auto restart ( Args && ... args ) noexcept -> void {
            this->firstCall = true;
            this->lastCall = false;
            this->promiseObjectUsed.reset();
            this->promiseObjectReady.reset();

            auto task = [&] { this->yield ( this->task ( std :: forward < Args > ( args ) ... ), true ); };

            this->pTaskThread = Memory :: instance().create < Runnable < decltype (task) > > ( task );

            this->pTaskThread->start();
            this->running = true;
        }

    public:
        class IterableGenerator : public Object { // NOLINT(cppcoreguidelines-virtual-class-destructor)
        public:
            class Iterator {
            private:
                T mutable * pData { nullptr };
                Generator * pGen { nullptr };

            public:
                explicit Iterator ( Generator * gen, bool ignore = false ) noexcept :
                        pGen(gen),
                        pData(nullptr) {

                    if ( ! ignore ) {
                        this->pData = this->pGen->singleCallReturnValue();
                    }
                }

                operator T & () const noexcept { // NOLINT(google-explicit-constructor)
                    return this->value();
                }

                auto value () const noexcept -> T & { return * this->pData; }
                auto next () noexcept -> Iterator & {
                    if ( this->pGen->running ) {
                        this->pData = this->pGen->singleCallReturnValue();
                    } else {
                        this->pData = nullptr;
                    }

                    return * this;
                }

                inline auto operator * () const noexcept -> T & { return * this->pData; }
                inline auto operator ++ () noexcept -> Iterator & { return this->next(); }
                inline auto operator ++ (int) const noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
                inline auto operator == (Iterator const & iterator) const noexcept -> bool { return this->equals(iterator); }
                inline auto operator != (Iterator const & iterator) const noexcept -> bool { return ! this->equals(iterator); } // NOLINT(clion-misra-cpp2008-5-3-1)

                auto equals ( Iterator const & iterator ) const noexcept -> bool { return this->pData == iterator.pData; }
            };

        private:
            Generator * pGen { nullptr }; // NOLINT(clion-misra-cpp2008-8-0-1)

        public:

            operator T & () const noexcept { // NOLINT(google-explicit-constructor)
                return * this->pGen->singleCallReturnValue();
            }

            using ConstIterator = Iterator;

            inline explicit IterableGenerator( Generator * pGen ) noexcept :
                    pGen ( pGen ) {

            }

            auto begin () noexcept -> Iterator { return Iterator ( this->pGen); }
            auto end () noexcept -> Iterator { return Iterator ( this->pGen, true ); }

            __CDS_NoDiscard auto cbegin () const noexcept -> ConstIterator { return ConstIterator ( this->pGen ); }
            __CDS_NoDiscard auto cend () const noexcept -> ConstIterator { return ConstIterator ( this->pGen, true ); }

            __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < IterableGenerator >;// { return Sequence < IterableGenerator > ( *this ); }
            auto sequence () & noexcept -> Sequence < IterableGenerator >;// { return Sequence < IterableGenerator > ( *this ); }
            __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < IterableGenerator >;// { return Sequence < IterableGenerator > ( std::move(*this) ); }
            auto sequence () && noexcept -> Sequence < IterableGenerator >;// { return Sequence < IterableGenerator > ( std::move(*this) ); }
        };

    private:
        friend class IterableGenerator;
        friend class IterableGenerator::Iterator;

    public:

        auto operator () ( Args && ... args ) noexcept -> IterableGenerator {
            if ( ! this->running ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                if ( this->pTaskThread != nullptr ) {
                    this->pTaskThread->join();
                    this->pTaskThread.reset();
                }

                this->restart ( std::forward<Args>(args) ...);
            }

            return IterableGenerator ( this );
        }

        ~Generator () noexcept override {
            if ( this->pTaskThread != nullptr ) {
                this->trap = true;
                this->promiseObjectReady.wait();
                this->promiseObjectUsed.notify();
                this->promiseObjectReady.wait();

                this->pTaskThread->kill();
            }
        }
    };

}

#include <CDS/Pair>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        class __CDS_MaybeUnused FibonacciGenerator : public Generator < int > {
            __CDS_NoReturn auto task () noexcept -> int override {
                Pair < int, int > terms = { 0, 1 };

                while ( true ) {
                    yield ( terms.first() );
                    terms = { terms.second(), terms.first() + terms.second() };
                }
            }
        };

    }
}

#include <CDS/Sequence>

namespace cds {

    template < typename T, typename ... Args >
    auto Generator < T, Args ... > :: IterableGenerator :: sequence () const & noexcept -> Sequence < IterableGenerator > {
        return Sequence < IterableGenerator > ( *this );
    }

    template < typename T, typename ... Args >
    auto Generator < T, Args ... > :: IterableGenerator :: sequence () & noexcept -> Sequence < IterableGenerator > {
        return Sequence < IterableGenerator > ( *this );
    }

    template < typename T, typename ... Args >
    auto Generator < T, Args ... > :: IterableGenerator :: sequence () const && noexcept -> Sequence < IterableGenerator > {
        return Sequence < IterableGenerator > ( std::move(*this) );
    }

    template < typename T, typename ... Args >
    auto Generator < T, Args ... > :: IterableGenerator :: sequence () && noexcept -> Sequence < IterableGenerator > {
        return Sequence < IterableGenerator > ( std::move(*this) );
    }

}

#endif //CDS_GENERATOR_HPP
