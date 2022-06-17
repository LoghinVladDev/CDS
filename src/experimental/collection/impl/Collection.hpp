//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_IMPL_HPP__
#define __CDS_COLLECTION_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {


        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace __impl {

                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                inline static auto __initializerListContains ( // NOLINT(bugprone-reserved-identifier)
                        std :: initializer_list < __ElementType >   const & list,
                        __ElementType                               const & element
                ) noexcept -> bool {

                    for ( auto const & e : list ) {
                        if ( meta :: equals ( e, element ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename __ElementType, typename __LastType > // NOLINT(bugprone-reserved-identifier)
                inline auto __collectionAdd ( // NOLINT(bugprone-reserved-identifier)
                        Collection < __ElementType >    & collection,
                        __LastType                     && element
                ) noexcept -> void {

                    collection.add ( std :: forward < __LastType > ( element ) );
                }


                template < typename __ElementType, typename __FirstType, typename ... __RemainingTypes > // NOLINT(bugprone-reserved-identifier)
                inline auto __collectionAdd ( // NOLINT(bugprone-reserved-identifier)
                        Collection < __ElementType >     &      collection,
                        __FirstType                     &&      firstElement,
                        __RemainingTypes                && ...  remainingElements
                ) noexcept -> void {

                    collection.add ( std :: forward < __FirstType > ( firstElement ) );
                    __collectionAdd ( collection, std :: forward < __RemainingTypes > ( remainingElements ) ... );
                }

            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Collection < __ElementType > :: acquireDelegate (
                AbstractIterator const & iterator
        ) noexcept -> AbstractDelegateIterator const * {

            return iterator._pDelegate.get();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Collection < __ElementType > :: acquireDelegate (
                ConstIterator const & iterator
        ) noexcept -> DelegateConstIterator const * {

            return reinterpret_cast < DelegateConstIterator * > ( iterator._pDelegate.get() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Collection < __ElementType > :: acquireDelegate (
                ConstReverseIterator const & iterator
        ) noexcept -> DelegateConstIterator const * {

            return reinterpret_cast < DelegateConstIterator * > ( iterator._pDelegate.get() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: begin () const noexcept -> ConstIterator {

            return this->cbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: end () const noexcept -> ConstIterator {

            return this->cend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: cbegin () const noexcept -> ConstIterator {

            return ConstIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: cend () const noexcept -> ConstIterator {

            return ConstIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: rbegin () const noexcept -> ConstReverseIterator {

            return this->crbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: rend () const noexcept -> ConstReverseIterator {

            return this->crend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: crbegin () const noexcept -> ConstReverseIterator {

            return ConstReverseIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: crend () const noexcept -> ConstReverseIterator {

            return ConstReverseIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: remove (
                Size                count,
                __Predicate const & predicate
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeFirst (
                __Predicate const & predicate
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeLast (
                __Predicate const & predicate
        ) noexcept -> bool {

            ConstIterator toRemove;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeAll (
                __Predicate const & predicate
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: remove (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeFirst (
                ElementType const & element
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeLast (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeAll (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeFirstOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeLastOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeAllOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeNotOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeFirstNotOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeLastNotOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeAllNotOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeOf (
                Size                    count,
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeFirstOf (
                InitializerList const & list
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeLastOf (
                InitializerList const & list
        ) noexcept -> bool {

            ConstIterator toRemove;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeAllOf (
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeNotOf (
                Size                    count,
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeFirstNotOf (
                InitializerList const & list
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeLastNotOf (
                InitializerList const & list
        ) noexcept -> bool {

            ConstIterator toRemove;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: removeAllNotOf (
                InitializerList const & list
        ) noexcept -> Size {

            ConstIterator * pIteratorBuffer = Memory :: instance().createArray < ConstIterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( reinterpret_cast < ConstIterator const * > ( & pIteratorBuffer[0] ), iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Action > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: forEach (
                __Action const & action
        ) const noexcept ( noexcept ( action ( meta :: referenceOf < ElementType const > () ) ) ) -> void {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                action ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: some (
                Size                count,
                __Predicate const & predicate
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: atLeast (
                Size                count,
                __Predicate const & predicate
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: atMost (
                Size                count,
                __Predicate const & predicate
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: moreThan (
                Size                count,
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            return this->atLeast ( count + 1, predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: fewerThan (
                Size                count,
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            return this->atMost ( count - 1, predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: count (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Size {

            Size trueCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }
            }

            return trueCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: any (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: all (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: none (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: find (
                Size                                        maxCount,
                ElementType                         const & element,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: find (
                Size                                        maxCount,
                ElementType                         const & element
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> find ( maxCount, element, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findFirst (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findLast (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAll (
                ElementType                         const & element,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAll (
                ElementType                         const & element
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> findAll ( element, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findFirstOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findLastOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllOf (
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllOf (
                Collection < ElementType >          const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            Collection < ConstIterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findFirstNotOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findLastNotOf (
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllNotOf (
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllNotOf (
                Collection < ElementType >  const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findFirstOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findLastOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllOf (
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllOf (
                InitializerList                     const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            Collection < ConstIterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findFirstNotOf (
                InitializerList                     const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findLastNotOf (
                InitializerList                     const & elements
        ) const noexcept -> ConstIterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllNotOf (
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAllNotOf (
                InitializerList                     const & elements
        ) const noexcept -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: find (
                Size                                        maxCount,
                __Predicate                         const & predicate,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > & {

            Size matchCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && matchCount < maxCount; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ matchCount;
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: find (
                Size                                        maxCount,
                __Predicate                         const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this->find ( maxCount, predicate, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findFirst (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findLast (
                __Predicate const & predicate
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAll (
                __Predicate                         const & predicate,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: findAll (
                __Predicate                           const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > {

            __CollectionType < ConstIterator > iterators;
            return this->findAll ( predicate, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprPureAbstract Collection < __ElementType > :: operator bool () const noexcept {

            return ! this->empty();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: hash () const noexcept -> Index {

            Index finalHashValue __CDS_MaybeUnused = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                finalHashValue += cds :: hash ( * iterator );
            }

            return finalHashValue;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: equals (
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
                        leftIt  = this->begin(),    leftEnd = this->end(),
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Collection < __ElementType > :: Collection (
                Collection const & collection
        ) noexcept :
                _size ( collection._size ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Collection < __ElementType > :: Collection (
                Collection && collection
        ) noexcept :
                _size ( cds :: exchange ( collection._size, 0ULL ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Collection < __ElementType > :: Collection (
                Size size
        ) noexcept :
                _size ( size ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Collection < __ElementType > :: size () const noexcept -> Size {

            return this->_size;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Collection < __ElementType > :: empty () const noexcept -> bool {

            return this->size() == 0ULL;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: contains (
                ElementType const & element
        ) const noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAnyOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAnyNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAllOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAllNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAnyOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAnyNotOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAllOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( ! this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: containsAllNotOf (
                InitializerList const & elements
        ) const noexcept -> bool {

            for ( auto iterator = elements.begin(), end = elements.end(); iterator != end; ++ iterator ) {
                if ( this->contains ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: add (
                ElementType const & element
        ) noexcept ( noexcept ( ElementType ( element ) ) ) -> void {

            auto & pElementLocation = this->pNewInsert ( element );
            if ( pElementLocation == nullptr ) {
                pElementLocation = Memory :: instance().create < ElementType > ( element );
                this->pNewInsertPost();
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: add (
                ElementType && element
        ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> void {

            auto & pElementLocation = this->pNewInsert ( element );
            if ( pElementLocation == nullptr ) {
                pElementLocation = Memory :: instance().create < ElementType > ( std :: move ( element ) );
                this->pNewInsertPost();
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: addAll (
                __ArgumentTypes && ... arguments
        ) noexcept -> void {

            __hidden :: __impl :: __collectionAdd ( * this, std :: forward < __ArgumentTypes > ( arguments ) ... );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, typename __ArgumentTypes, meta :: EnableIf < meta :: isCopyConstructible < __ArgumentTypes > () || meta :: isConvertible < __OtherElementType, __ArgumentTypes > () > > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: addAllOf (
                Collection < __OtherElementType > const & otherCollection
        ) noexcept -> void {

            for ( auto iterator = otherCollection.begin(), end = otherCollection.end(); iterator != end; ++ iterator ) {
                this->add ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: pNewInsertPost() noexcept -> void {
            /* left empty intentionally, derived classes can override this, but it is not mandatory.
             * Refer to Collection :: add to when this should be overridden */
        }

    }
}

#endif // __CDS_COLLECTION_IMPL_HPP__
