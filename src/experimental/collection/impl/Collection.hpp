//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_IMPL_HPP__
#define __CDS_COLLECTION_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {


        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename T >
                __CDS_OptimalInline static auto initializerListContains (
                        std :: initializer_list < T >   const & list,
                        T                               const & element
                ) noexcept -> bool {

                    for ( auto const & e : list ) {
                        if ( meta :: equals ( e, element ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename T, typename LastType >
                inline auto collectionAdd (
                        Collection < T >    & collection,
                        LastType           && element
                ) noexcept -> void {

                    collection.add ( std :: forward < LastType > ( element ) );
                }


                template < typename T, typename FirstType, typename ... RemainingTypes >
                inline auto collectionAdd (
                        Collection < T >     &      collection,
                        FirstType           &&      firstElement,
                        RemainingTypes      && ...  remainingElements
                ) noexcept -> void {

                    collection.add ( std :: forward < FirstType > ( firstElement ) );
                    collectionAdd ( collection, std :: forward < RemainingTypes > ( remainingElements ) ... );
                }


                template < typename CollectionType, typename LastArgumentType >
                inline auto collectionOfPush (
                        CollectionType      & collection,
                        LastArgumentType   && lastValue
                ) noexcept -> void {

                    collection.add ( std :: forward < LastArgumentType > ( lastValue ) );
                }


                template < typename CollectionType, typename FirstArgumentType, typename ... RemainingArgumentTypes >
                inline auto collectionOfPush (
                        CollectionType          &       collection,
                        FirstArgumentType      &&       firstValue,
                        RemainingArgumentTypes && ...   remainingValues
                ) noexcept -> void {

                    collection.add ( std :: forward < FirstArgumentType > ( firstValue ) );
                    collectionOfPush ( collection, std :: forward < RemainingArgumentTypes > ( remainingValues ) ... );
                }

            }
        }


        template < typename T >
        constexpr auto Collection < T > :: acquireDelegate (
                AbstractIterator const & iterator
        ) noexcept -> AbstractDelegateIterator const * {

            return iterator._pDelegate.get();
        }


        template < typename T >
        constexpr auto Collection < T > :: acquireDelegate (
                ConstIterator const & iterator
        ) noexcept -> DelegateConstIterator const * {

            return reinterpret_cast < DelegateConstIterator * > ( iterator._pDelegate.get() );
        }


        template < typename T >
        constexpr auto Collection < T > :: acquireDelegate (
                ConstReverseIterator const & iterator
        ) noexcept -> DelegateConstIterator const * {

            return reinterpret_cast < DelegateConstIterator * > ( iterator._pDelegate.get() );
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: begin () const noexcept -> ConstIterator {

            return this->cbegin();
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: end () const noexcept -> ConstIterator {

            return this->cend();
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: cbegin () const noexcept -> ConstIterator {

            return ConstIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: cend () const noexcept -> ConstIterator {

            return ConstIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: rbegin () const noexcept -> ConstReverseIterator {

            return this->crbegin();
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: rend () const noexcept -> ConstReverseIterator {

            return this->crend();
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: crbegin () const noexcept -> ConstReverseIterator {

            return ConstReverseIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: crend () const noexcept -> ConstReverseIterator {

            return ConstReverseIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: remove (
                Size                count,
                Predicate   const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iteratorCount < count && iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: removeFirst (
                Predicate const & predicate
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: removeLast (
                Predicate const & predicate
        ) noexcept -> bool {

            ConstIterator toRemove;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: removeAll (
                Predicate const & predicate
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: remove (
                Size                count,
                ElementType const & element
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iteratorCount < count && iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeFirst (
                ElementType const & element
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: removeLast (
                ElementType const & element
        ) noexcept -> bool {

            ConstIterator toRemove;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename T >
        auto Collection < T > :: removeAll (
                ElementType const & element
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeOf (
                Size                                count,
                Collection < ElementType >  const & collection
        ) noexcept -> Size {

            if ( this == & collection ) {
                if ( this->size() <= count ) {
                    this->clear();
                    return true;
                }

                ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
                Size iteratorCount = 0U;

                for ( auto iterator = this->begin(), end = this->end(); iteratorCount < count && iterator != end; ++ iterator ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
                Memory :: instance().destroyArray ( pIteratorBuffer );

                return removedCount;
            }

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeFirstOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool {

            if ( this == & collection ) {
                return this->remove ( this->begin() );
            }

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: removeLastOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool {

            ConstIterator toRemove;
            if ( this == & collection ) {
                for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                    toRemove = iterator;
                }

                return this->remove ( toRemove );
            }

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename T >
        auto Collection < T > :: removeAllOf (
                Collection < ElementType > const & collection
        ) noexcept -> Size {

            if ( this == & collection ) {
                auto removedCount = this->size();
                this->clear();
                return removedCount;
            }

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeNotOf (
                Size                                count,
                Collection < ElementType >  const & collection
        ) noexcept -> Size {

            if ( this == & collection ) {
                return 0ULL;
            }

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeFirstNotOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool {

            if ( this == & collection ) {
                return false;
            }

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: removeLastNotOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool {

            if ( this == & collection ) {
                return false;
            }

            ConstIterator toRemove;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename T >
        auto Collection < T > :: removeAllNotOf (
                Collection < ElementType > const & collection
        ) noexcept -> Size {

            if ( this == & collection ) {
                return 0ULL;
            }

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeOf (
                Size                    count,
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeFirstOf (
                InitializerList const & list
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: removeLastOf (
                InitializerList const & list
        ) noexcept -> bool {

            ConstIterator toRemove;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename T >
        auto Collection < T > :: removeAllOf (
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeNotOf (
                Size                    count,
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        auto Collection < T > :: removeFirstNotOf (
                InitializerList const & list
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: removeLastNotOf (
                InitializerList const & list
        ) noexcept -> bool {

            ConstIterator toRemove;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename T >
        auto Collection < T > :: removeAllNotOf (
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename T >
        template < typename Action >
        auto Collection < T > :: forEach (
                Action const & action
        ) const noexcept ( noexcept ( action ( meta :: referenceOf < ElementType const > () ) ) ) -> void {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                action ( * iterator );
            }
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: some (
                Size                count,
                Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            Size trueCount = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }

                if ( trueCount > count ) {
                    return false;
                }
            }

            return trueCount == count;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: atLeast (
                Size                count,
                Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            Size trueCount = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }

                if ( trueCount >= count ) {
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: atMost (
                Size                count,
                Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            Size trueCount = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }

                if ( trueCount > count ) {
                    return false;
                }
            }

            return true;
        }


        template < typename T >
        template < typename Predicate >
        __CDS_OptimalInline auto Collection < T > :: moreThan (
                Size                count,
                Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            return this->atLeast ( count + 1, predicate );
        }


        template < typename T >
        template < typename Predicate >
        __CDS_OptimalInline auto Collection < T > :: fewerThan (
                Size                count,
                Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            return this->atMost ( count - 1, predicate );
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: count (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Size {

            Size trueCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }
            }

            return trueCount;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: any (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: all (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: none (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: find (
                Size                                        maxCount,
                ElementType                         const & element,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: find (
                Size                                        maxCount,
                ElementType                         const & element
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> find ( maxCount, element, iterators );
        }


        template < typename T >
        auto Collection < T > :: findFirst (
                ElementType const & element
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        auto Collection < T > :: findLast (
                ElementType const & element
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAll (
                ElementType                         const & element,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAll (
                ElementType                         const & element
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> findAll ( element, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto Collection < T > :: findFirstOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        auto Collection < T > :: findLastOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    lastFound = end;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllOf (
                Collection < ElementType >          const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllOf (
                Collection < ElementType >          const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            Collection < ConstIterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto Collection < T > :: findFirstNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        auto Collection < T > :: findLastNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllNotOf (
                Collection < ElementType >          const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllNotOf (
                Collection < ElementType >  const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto Collection < T > :: findFirstOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        auto Collection < T > :: findLastOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllOf (
                InitializerList                     const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllOf (
                InitializerList                     const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            Collection < ConstIterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto Collection < T > :: findFirstNotOf (
                InitializerList                     const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements,  * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        auto Collection < T > :: findLastNotOf (
                InitializerList                     const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements,  * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllNotOf (
                InitializerList                     const & elements,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept -> CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements,  * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto Collection < T > :: findAllNotOf (
                InitializerList                     const & elements
        ) const noexcept -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto Collection < T > :: find (
                Size                                        maxCount,
                Predicate                           const & predicate,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > & {

            Size matchCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && matchCount < maxCount; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ matchCount;
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto Collection < T > :: find (
                Size                                        maxCount,
                Predicate                           const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this->find ( maxCount, predicate, iterators );
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: findFirst (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: findLast (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto Collection < T > :: findAll (
                Predicate                           const & predicate,
                CollectionType < ConstIterator >          & storeIn
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto Collection < T > :: findAll (
                Predicate                           const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > {

            CollectionType < ConstIterator > iterators;
            return this->findAll ( predicate, iterators );
        }


        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract Collection < T > :: operator bool () const noexcept {

            return ! this->empty();
        }


        template < typename T >
        auto Collection < T > :: hash () const noexcept -> Index {

            Index finalHashValue __CDS_MaybeUnused = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                finalHashValue += cds :: hash ( * iterator );
            }

            return finalHashValue;
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: equals (
                Object const & object
        ) const noexcept -> bool {

            auto pObject = dynamic_cast < decltype ( this ) > ( & object );
            if ( pObject == nullptr ) {
                return false;
            }

            if ( this->size() != pObject->size() ) {
                return false;
            }

            for (
                    auto
                        leftIt  = this->begin(),    leftEnd     = this->end(),
                        rightIt = pObject->begin();
                    leftIt != leftEnd;
                    ++ leftIt, ++ rightIt
            ) {
                if ( ! meta :: equals ( * leftIt, * rightIt ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: empty () const noexcept -> bool {

            return this->size() == 0ULL;
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: contains (
                ElementType const & element
        ) const noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: containsAnyOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }

        template < typename T >
        auto Collection < T > :: containsAnyNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: containsAllOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }

        template < typename T >
        auto Collection < T > :: containsAllNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }

        template < typename T >
        auto Collection < T > :: containsAnyOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: containsAnyNotOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        auto Collection < T > :: containsAllOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename T >
        auto Collection < T > :: containsAllNotOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        auto Collection < T > :: add (
                ElementType const & element
        ) noexcept ( noexcept ( ElementType ( element ) ) ) -> void {

            auto & pElementLocation = this->pNewInsert();
            if ( pElementLocation == nullptr ) {
                pElementLocation = Memory :: instance().create < ElementType > ( element );
                this->pNewInsertPost();
            }
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        auto Collection < T > :: add (
                ElementType && element
        ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> void {

            auto & pElementLocation = this->pNewInsert();
            if ( pElementLocation == nullptr ) {
                pElementLocation = Memory :: instance().create < ElementType > ( std :: move ( element ) );
                this->pNewInsertPost();
            }
        }


        template < typename T >
        template < typename ... ArgumentTypes >
        auto Collection < T > :: addAll (
                ArgumentTypes && ... arguments
        ) noexcept -> void {

            hidden :: impl :: collectionAdd ( * this, std :: forward < ArgumentTypes > ( arguments ) ... );
        }


        template < typename T >
        template < typename R, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () || meta :: isConvertible < R, V > () > >
        auto Collection < T > :: addAllOf (
                Collection < R > const & otherCollection
        ) noexcept -> void {

            for ( auto iterator = otherCollection.begin(), end = otherCollection.end(); iterator != end; ++ iterator ) {
                this->add ( * iterator );
            }
        }


        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: pNewInsertPost() noexcept -> void {
            /* left empty intentionally, derived classes can override this, but it is not mandatory.
             * Refer to Collection :: add to when this should be overridden */
        }


        template < template < typename ... > class CollectionType, typename ... ArgumentTypes, typename Common >
        auto collectionOf (
                ArgumentTypes && ... values
        ) noexcept -> CollectionType < Common > {

            CollectionType < Common > collection;
            hidden :: impl :: collectionOfPush ( collection, std :: forward < ArgumentTypes > ( values ) ... );
            return collection;
        }

    }
}

#endif // __CDS_COLLECTION_IMPL_HPP__
