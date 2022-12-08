//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP_
#define __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP_     /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __cicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__mcs_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __cicch_obtainGenericConstHandler (         /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__mcs_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: ValueMutableCollectionProxy (
                TreeMap < __KeyType, __ValueType > * pMap
        ) noexcept :
                AbstractValueMutableCollectionProxy ( pMap ) {

        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __begin () noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > * {

            return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType, Iterator > >(
                    Iterator ( this->template map < TreeMapBase > ()->__beginLocal() )
            );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __end () noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > * {

            return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType, Iterator > >(
                    Iterator ( this->template map < TreeMapBase > ()->__endLocal() )
            );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __beginLocal () noexcept -> Iterator {

            return Iterator ( this->template map < TreeMapBase > ()->__beginLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __endLocal () noexcept -> Iterator {

            return Iterator ( this->template map < TreeMapBase > ()->__endLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __cbegin () const noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > * {

            return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType const, ConstIterator > >(
                    ConstIterator ( this->template map < TreeMapBase > ()->__cbeginLocal() )
            );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __cend () const noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > * {

            return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType const, ConstIterator > >(
                    ConstIterator ( this->template map < TreeMapBase > ()->__cendLocal() )
            );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __cbeginLocal () const noexcept -> ConstIterator {

            return Iterator ( this->template map < TreeMapBase > ()->__cbeginLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __cendLocal () const noexcept -> ConstIterator {

            return Iterator ( this->template map < TreeMapBase > ()->__cendLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __rbeginLocal () noexcept -> ReverseIterator {

            return Iterator ( this->template map < TreeMapBase > ()->__rbeginLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __rendLocal () noexcept -> ReverseIterator {

            return Iterator ( this->template map < TreeMapBase > ()->__rendLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __crbeginLocal () const noexcept -> ConstReverseIterator {

            return Iterator ( this->template map < TreeMapBase > ()->__crbeginLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __crendLocal () const noexcept -> ConstReverseIterator {

            return Iterator ( this->template map < TreeMapBase > ()->__crendLocal() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __remove (
                AbstractIterator const * iterator
        ) noexcept -> bool {

            return this->template map < TreeMapBase > ()->__remove( & iterator->iterator() ) ;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __removeConst (
                AbstractConstIterator const * iterator
        ) noexcept -> bool {

            return this->template map < TreeMapBase > ()->__removeConst( & iterator->iterator() ) ;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __removeArray (
                AbstractIterator const * const * ppIterators,
                Size                             iteratorCount
        ) noexcept -> Size {

            auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                    typename cds :: experimental :: __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractIterator const *
                > ( iteratorCount );

            for ( auto iteratorIndex = 0U; iteratorIndex < iteratorCount; ++ iteratorIndex ) {

                if ( ppIterators [ iteratorIndex ] != nullptr ) {
                    ppWrappedIteratorArray [ iteratorIndex ] = & ppIterators [ iteratorIndex ]->iterator();
                } else {
                    ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
                }
            }

            auto const removedIteratorCount = this->template map < TreeMapBase > () -> __removeArray (
                    ppWrappedIteratorArray,
                    iteratorCount
            );

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppWrappedIteratorArray );
            return removedIteratorCount;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto TreeMap <
                __KeyType,
                __ValueType
        > :: ValueMutableCollectionProxy :: __removeConstArray (
                AbstractConstIterator const * const * ppIterators,
                Size                                  iteratorCount
        ) noexcept -> Size {

            auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                    typename cds :: experimental :: __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractConstIterator const *
                > ( iteratorCount );

            for ( auto iteratorIndex = 0U; iteratorIndex < iteratorCount; ++ iteratorIndex ) {

                if ( ppIterators [ iteratorIndex ] != nullptr ) {
                    ppWrappedIteratorArray [ iteratorIndex ] = & ppIterators [ iteratorIndex ]->iterator();
                } else {
                    ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
                }
            }

            auto const removedIteratorCount = this->template map < TreeMapBase > () -> __removeConstArray (
                    ppWrappedIteratorArray,
                    iteratorCount
            );

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppWrappedIteratorArray );
            return removedIteratorCount;
        }
    }
}

#endif //__CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP_
