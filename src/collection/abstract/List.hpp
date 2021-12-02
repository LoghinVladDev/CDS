//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_LIST_HPP
#define CDS_LIST_HPP

#include <CDS/Collection>
#include <CDS/Concepts>
#include <CDS/Memory>

namespace cds {

    template < typename T >
    class DoubleLinkedList;

    template < typename T >
    class List : public Collection <T> {
    public:
        using ElementType   = typename Collection < T > :: ElementType;

    protected:
        Size _size { 0ull }; // NOLINT(clion-misra-cpp2008-11-0-1)

        List () noexcept = default;
        using ElementRef                = typename Collection < T > :: ElementRef;
        using ElementCRef               = typename Collection < T > :: ElementCRef;
        using ElementMRef               = typename Collection < T > :: ElementMRef;
        using ElementPtr                = typename Collection < T > :: ElementPtr;
        using ElementPtrRef             = typename Collection < T > :: ElementPtrRef;
        using ElementCPtr               = typename Collection < T > :: ElementCPtr;
        using InitializerList           = typename Collection < T > :: InitializerList;

    public:
        using Iterator                  = typename Collection < T > :: Iterator;
        using ConstIterator             = typename Collection < T > :: ConstIterator;

        using ReverseIterator           = typename Collection < T > :: ReverseIterator;
        using ConstReverseIterator      = typename Collection < T > :: ConstReverseIterator;

    protected:
        using DelegateIterator          = typename Collection < T > :: DelegateIterator;
        using DelegateConstIterator     = typename Collection < T > :: DelegateConstIterator;

    protected:
        virtual auto pAt ( Index ) noexcept (false) -> ElementPtr = 0;
        __CDS_NoDiscard __CDS_MaybeUnused virtual auto pAt ( Index ) const noexcept (false) -> ElementCPtr = 0;

    public:

        __CDS_OptimalInline auto get ( Index index ) noexcept (false) -> ElementRef {
            return * this->pAt ( index );
        }

        __CDS_NoDiscard __CDS_OptimalInline auto get ( Index index ) const noexcept -> ElementCRef {
            return * this->pAt ( index );
        };

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_OptimalInline auto set ( ElementCRef e, Index index ) noexcept (false) -> ElementRef {
            * this->pAt(index) = e;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_OptimalInline auto set ( ElementMRef e, Index index ) noexcept (false) -> ElementRef {
            * this->pAt(index) = std :: forward < ElementType > ( e );
        }

        template < typename ListType, typename V = T, EnableIf < Type < V > :: copyAssignable && isDerivedFrom < ListType, List < V > > :: value > = 0 >
        __CDS_MaybeUnused auto sub ( Index, Index = limits::S64_MAX ) const noexcept (false) -> ListType;

        __CDS_OptimalInline auto operator [] ( Index index ) noexcept -> ElementRef {
            return this->get( index );
        }

        __CDS_OptimalInline auto operator [] ( Index index ) const noexcept -> ElementCRef {
            return this->get( index );
        }

        virtual auto remove ( Iterator const & ) noexcept (false) -> ElementType = 0;

        __CDS_MaybeUnused virtual auto popFront ( ) noexcept (false) -> ElementType = 0;
        __CDS_MaybeUnused virtual auto popBack ( ) noexcept (false) -> ElementType = 0;

    protected:

        virtual auto allocFrontGetPtr () noexcept -> ElementPtrRef = 0;
        virtual auto allocBackGetPtr () noexcept -> ElementPtrRef = 0;

        template < typename SortFunc >
        auto static quickSort ( Iterator const &, Iterator const &, SortFunc const & ) noexcept -> void;

        template < typename SortFunc >
        auto static quickSortPartition ( Iterator const &, Iterator const &, SortFunc const & ) noexcept -> Iterator;

    public:
        template < typename SortFunc = Function < bool ( ElementCRef, ElementCRef ) > >
        __CDS_OptimalInline auto sort ( SortFunc const & sortFunction = []( ElementCRef a, ElementCRef b ) noexcept -> bool { return a < b; } ) noexcept -> void {
            if ( this->size() < 2 ) {
                return;
            }

            Iterator previous;
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                previous = it;
            }

            List < T > :: quickSort ( this->begin(), previous, sortFunction );
        }

        __CDS_OptimalInline auto sort ( Comparator < T > const & comparator ) noexcept -> void {
            return this->sort ( [& comparator](T const & a, T const & b) noexcept -> bool {
                return comparator ( a, b );
            });
        }

        template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
        __CDS_OptimalInline auto pushFront ( ElementCRef value ) noexcept -> ElementRef {
            __CDS_Collection_OperationalLock

            auto & p = this->allocFrontGetPtr();
            if ( p == nullptr ) {
                p = Memory::instance().create<ElementType>(value);

                __CDS_Collection_OperationalUnlock
                return * p;
            }

            return * p;
        }

        template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
        __CDS_OptimalInline auto pushBack ( ElementCRef value ) noexcept -> ElementRef {
            __CDS_Collection_OperationalLock

            auto & p = this->allocBackGetPtr();
            if ( p == nullptr ) {
                p = Memory::instance().create<ElementType>(value);

                __CDS_Collection_OperationalUnlock
                return * p;
            }

            return * p;
        }

        template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
        __CDS_OptimalInline auto pushFront ( ElementMRef value ) noexcept -> ElementRef {
            __CDS_Collection_OperationalLock

            auto & p = this->allocFrontGetPtr();
            if ( p == nullptr ) {
                p = Memory::instance().create < ElementType > ( std :: forward < ElementType > ( value ) );

                __CDS_Collection_OperationalUnlock
                return * p;
            }

            return * p;
        }

        template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
        __CDS_OptimalInline auto pushBack ( ElementMRef value ) noexcept -> ElementRef {
            __CDS_Collection_OperationalLock

            auto & p = this->allocBackGetPtr();
            if ( p == nullptr ) {
                p = Memory::instance().create < ElementType > ( std :: forward < ElementType > ( value ) );

                __CDS_Collection_OperationalUnlock
                return * p;
            }

            return * p;
        }

        template < typename V = T, EnableIf< Type < V > :: copyConstructible > = 0 >
        __CDS_OptimalInline auto append ( ElementCRef v ) noexcept -> ElementRef {
            return this->pushBack ( v );
        }

        template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
        __CDS_OptimalInline auto append ( ElementMRef v ) noexcept -> ElementRef {
            return this->pushBack ( std :: forward < ElementType > ( v ) );
        }


        template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
        __CDS_OptimalInline auto prepend ( ElementCRef v ) noexcept -> ElementRef {
            return this->pushFront(v);
        }

        template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
        __CDS_OptimalInline auto prepend ( ElementMRef v ) noexcept -> ElementRef {
            return this->pushFront ( std :: forward < ElementType > ( v ) );
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override {
            return this->_size;
        }

        __CDS_cpplang_ConstexprDestructor ~List () noexcept override = default;

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replace (
                ElementCRef what    __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused,
                Size count          __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replaceCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( replaceCount < count ) {
                    if ( Type < T > :: compare ( e, what ) ) {
                        e = with;
                        ++ replaceCount;
                    }
                } else {
                    return count;
                }
            }

            return replaceCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirst (
                ElementCRef what __CDS_MaybeUnused,
                ElementCRef with __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Type < T > :: compare ( e, what ) ) {
                    e = with;
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirst (
                ElementCRef what __CDS_MaybeUnused,
                ElementMRef with __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Type < T > :: compare ( e, what ) ) {
                    e = std :: forward < ElementType > ( with );
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceAll (
                ElementCRef what __CDS_MaybeUnused,
                ElementCRef with __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Type < T > :: compare ( e, what ) ) {
                    e = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLast (
                ElementCRef what __CDS_MaybeUnused,
                ElementCRef with __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastEncountered;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Type < T > :: compare ( e, what ) ) {
                    lastEncountered = & e;
                }
            }

            if ( lastEncountered != nullptr ) {
                * lastEncountered = with;
            }

            return lastEncountered != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLast (
                ElementCRef what __CDS_MaybeUnused,
                ElementMRef with __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastEncountered;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Type < T > :: compare ( e, what ) ) {
                    lastEncountered = & e;
                }
            }

            if ( lastEncountered != nullptr ) {
                * lastEncountered = std :: forward < ElementType > ( with );
            }

            return lastEncountered != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused,
                Size count                  __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replacedCount __CDS_MaybeUnused = 0u;
            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( replacedCount < count ) {
                    if ( of.contains( e ) ) {
                        e = with;
                        ++ replacedCount;
                    }
                } else {
                    return count;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( of.contains( e ) ) {
                    e = with;
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementMRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( of.contains( e ) ) {
                    e = std :: forward < ElementType > ( with );
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( of.contains( e ) ) {
                    e = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( of.contains( e ) ) {
                    lastOccurred = & e ;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = with;
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementMRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < Iterator > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( of.contains( e ) ) {
                    lastOccurred = & e;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = std :: forward < ElementType > ( with );
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceNotOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused,
                Size count                  __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( replacedCount < count ) {
                    if ( ! of.contains( e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                        e = with;
                        ++ replacedCount;
                    }
                } else {
                    return count;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! of.contains( e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    e = with;
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementMRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! of.contains( e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    e = std :: forward < ElementType > ( with );
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllNotOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! of.contains( e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    e = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementCRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! of.contains( e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    lastOccurred = & e;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = with;
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
                Collection < T > const & of __CDS_MaybeUnused,
                ElementMRef with            __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! of.contains( e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    lastOccurred = & e;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = std :: forward < ElementType > ( with );
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused,
                Size count          __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( replacedCount < count ) {
                    if ( Collection < T > :: iListContains ( of, e ) ) {
                        e = with;
                        ++ replacedCount;
                    }
                } else {
                    return count;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Collection < T > :: iListContains ( of, e ) ) {
                    e = with;
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementMRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Collection < T > :: iListContains ( of, e ) ) {
                    e = std :: forward < ElementType > ( with );
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Collection < T > :: iListContains ( of, e ) ) {
                    e = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Collection < T > ::iListContains( of, e ) ) {
                    lastOccurred = & e;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = with;
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementMRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Collection < T > ::iListContains( of, e ) ) {
                    lastOccurred = & e;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = std :: forward < ElementType > ( with );
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceNotOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused,
                Size count          __CDS_MaybeUnused
        ) noexcept -> Size {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( replacedCount < count ) {
                    if ( ! Collection < T > :: iListContains ( of, e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                        e = with;
                        ++ replacedCount;
                    }
                } else {
                    return count;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! Collection < T > :: iListContains ( of, e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    e = with;
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementMRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! Collection < T > :: iListContains ( of, e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    e = std :: forward < ElementType > ( with );
                    return true;
                }
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllNotOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            Size replacedCount __CDS_MaybeUnused = 0u;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! Collection < T > :: iListContains ( of, e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    e = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementCRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! Collection < T > ::iListContains( of, e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    lastOccurred = & e;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = with;
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
                InitializerList of  __CDS_MaybeUnused,
                ElementMRef with    __CDS_MaybeUnused
        ) noexcept -> bool {

            ForeignPointer < ElementType > lastOccurred;

            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( ! Collection < T > ::iListContains( of, e ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    lastOccurred = & e;
                }
            }

            if ( lastOccurred != nullptr ) {
                * lastOccurred = std :: forward < ElementType > ( with );
            }

            return lastOccurred != nullptr;
        }

        template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptimalInline auto replace (
                Iterator const & iterator,
                ElementCRef value
        ) noexcept -> bool {

            if ( iterator.of ( this ) ) {
                iterator.value() = value;
                return true;
            }

            return false;
        }

        template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
        __CDS_MaybeUnused __CDS_OptimalInline auto replace (
                Iterator const & iterator,
                ElementMRef value
        ) noexcept -> bool {

            if ( iterator.of ( this ) ) {
                iterator.value() = std :: forward < ElementType > ( value );
                return true;
            }

            return false;
        }

        __CDS_cpplang_ConstexprPureAbstract virtual auto back () noexcept (false) -> ElementRef = 0;
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto back () const noexcept (false) -> ElementCRef = 0;

        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto front () const noexcept (false) -> ElementCRef = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto front () noexcept (false) -> ElementRef = 0;

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprOverride auto empty () const noexcept -> bool override {
            return this->_size == 0u;
        }

        __CDS_NoDiscard auto toString () const noexcept -> String final {
            if ( this->empty() ) {
                return {"[ ]"};
            }

            std::stringstream out;
            out << "[ ";

            for ( const auto & e __CDS_MaybeUnused : (*this) ) {
                Type < T > :: streamPrint( out, e ) << ", ";
            }

            auto s = out.str();
            return s.substr(0u, s.length() - 2u).append(" ]");
        }

        __CDS_NoDiscard auto index( ElementCRef value __CDS_MaybeUnused ) const noexcept -> Index {

            __CDS_Collection_OperationalLock

            Index i __CDS_MaybeUnused = 0;
            for ( auto & e __CDS_MaybeUnused : * this ) {
                if ( Type < T > :: compare ( e, value ) ) {

                    __CDS_Collection_OperationalUnlock
                    return i;
                } else {
                    ++ i;
                }
            }

            __CDS_Collection_OperationalUnlock

            return -1;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findFirst ( ElementCRef element ) noexcept -> Iterator {
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( Type < ElementType > :: compare ( * it, element ) ) {
                    return it;
                }
            }

            return {};
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findLast ( ElementCRef element ) noexcept -> Iterator {
            Iterator last;
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( Type < ElementType > :: compare ( * it, element ) ) {
                    last = it;
                }
            }

            return last;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findFirstOf ( Collection < ElementType > const & elements ) noexcept -> Iterator {
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( elements.contains( * it ) ) {
                    return it;
                }
            }

            return {};
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findFirstNotOf ( Collection < ElementType > const & elements ) noexcept -> Iterator {
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( ! elements.contains( * it ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return it;
                }
            }

            return {};
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findLastOf ( Collection < ElementType > const & elements ) noexcept -> Iterator {
            Iterator last;

            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( elements.contains( * it ) ) {
                    last = it;
                }
            }

            return last;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findLastNotOf ( Collection < ElementType > const & elements ) noexcept -> Iterator {
            Iterator last;

            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( ! elements.contains( * it ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    last = it;
                }
            }

            return last;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto find ( ElementCRef, Size = limits::U64_MAX ) noexcept -> DoubleLinkedList < Iterator >;
        __CDS_NoDiscard __CDS_MaybeUnused auto findOf ( Collection < ElementType > const &, Size = limits::U64_MAX ) noexcept -> DoubleLinkedList < Iterator >;
        __CDS_NoDiscard __CDS_MaybeUnused auto findNotOf ( Collection < ElementType > const &, Size = limits::U64_MAX ) noexcept -> DoubleLinkedList < Iterator >;

        __CDS_NoDiscard __CDS_MaybeUnused auto findFirst ( ElementCRef element ) const noexcept -> ConstIterator {
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( Type < ElementType > :: compare ( * it, element ) ) {
                    return it;
                }
            }

            return {};
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findLast ( ElementCRef element ) const noexcept -> ConstIterator {
            ConstIterator last;
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( Type < ElementType > :: compare ( * it, element ) ) {
                    last = it;
                }
            }

            return last;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findFirstOf ( Collection < ElementType > const & elements ) const noexcept -> ConstIterator {
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( elements.contains( * it ) ) {
                    return it;
                }
            }

            return {};
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findFirstNotOf ( Collection < ElementType > const & elements ) const noexcept -> ConstIterator {
            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( ! elements.contains( * it ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return it;
                }
            }

            return {};
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findLastOf ( Collection < ElementType > const & elements ) const noexcept -> ConstIterator {
            ConstIterator last;

            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( elements.contains( * it ) ) {
                    last = it;
                }
            }

            return last;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto findLastNotOf ( Collection < ElementType > const & elements ) const noexcept -> ConstIterator {
            ConstIterator last;

            for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( ! elements.contains( * it ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    last = it;
                }
            }

            return last;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto find ( ElementCRef, Size = limits::U64_MAX ) const noexcept -> DoubleLinkedList < ConstIterator >;
        __CDS_NoDiscard __CDS_MaybeUnused auto findOf ( Collection < ElementType > const &, Size = limits::U64_MAX ) const noexcept -> DoubleLinkedList < ConstIterator >;
        __CDS_NoDiscard __CDS_MaybeUnused auto findNotOf ( Collection < ElementType > const &, Size = limits::U64_MAX ) const noexcept -> DoubleLinkedList < ConstIterator >;
    };


    template < typename T >
    template < typename ListType, typename V, EnableIf < Type < V > :: copyAssignable && isDerivedFrom < ListType, List < V > > :: value > >
    __CDS_MaybeUnused auto List < T > :: sub ( Index from __CDS_MaybeUnused, Index to __CDS_MaybeUnused ) const noexcept(false) -> ListType {
        ListType list;

        if ( from > to ) {
            std :: swap (from, to);
        }

        if ( from < 0 ) {
            from = 0;
        }

        if ( to >= this->size() ) {
            to = this->size();
        }

        Index i __CDS_MaybeUnused = 0;

        for ( auto const & e __CDS_MaybeUnused : * this ) {
            if ( i >= from && i < to ) {
                list.add ( e );
            }

            ++ i;
        }

        return list;
    }

    template < typename T >
    template < typename SortFunc >
    auto List < T > :: quickSort (
            Iterator const & from,
            Iterator const & to,
            SortFunc const & comparisonFunction
    ) noexcept -> void {

        auto next = to;
        if ( next.isValid() ) {
            if ( from == ++ next ) {
                return;
            }
        }

        if ( from != to && from.isValid() && to.isValid() ) {
            auto partitionIterator = List < T > :: quickSortPartition ( from, to, comparisonFunction );

            List < T > :: quickSort ( from, partitionIterator, comparisonFunction );
            if ( ! partitionIterator.isValid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                return;
            }

            if ( partitionIterator == from ) {
                if ( ( ++ partitionIterator ).isValid() ) {
                    List < T > :: quickSort ( partitionIterator, to, comparisonFunction );
                }

                return;
            }

            if ( ! ( ++ partitionIterator ).isValid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                return;
            }

            List < T > :: quickSort ( ++ partitionIterator, to, comparisonFunction );
        }
    }

    template < typename T >
    template < typename SortFunc >
    auto List < T > :: quickSortPartition (
            Iterator const & from,
            Iterator const & to,
            SortFunc const & comparisonFunction
    ) noexcept -> Iterator {
        auto swap = [] ( T & a, T & b ) {
            auto aux = a;
            a = b;
            b = aux;
        };

        auto pivot = * to;
        auto partitionIterator = from;
        Iterator previous;

        for ( auto it = from; it != to; ++ it ) {
            if ( comparisonFunction ( * it, pivot ) ) {
                swap ( * partitionIterator, * it );
                previous = partitionIterator;
                ++ partitionIterator;
            }
        }

        swap ( * partitionIterator, * to );
        if ( ! previous.isValid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
            return partitionIterator;
        }

        return previous;
    }

}

__CDS_RegisterParseTypeTemplateT(List) // NOLINT(clion-misra-cpp2008-8-0-1)

#include <CDS/DoubleLinkedList>

#endif //CDS_LIST_HPP
