//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP_
#define __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP_     /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __iicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
            cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__mcs_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __iicch_obtainGenericConstHandler (         /* NOLINT(bugprone-reserved-identifier) */
            cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
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
    > :: ValueMutableCollectionProxy :: __begin (
            ValueMutableCollectionProxy * pObject
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > * {

        return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType, Iterator > >(
                Iterator ( TreeMapBase :: __beginLocal( pObject->template map < TreeMapBase > () ) )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __end (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > * {

        return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType, Iterator > >(
                Iterator ( TreeMapBase :: __endLocal( pObject->template map < TreeMapBase > () ) )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __beginLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> Iterator {

        return Iterator ( TreeMapBase :: __beginLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __endLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> Iterator {

        return Iterator ( TreeMapBase :: __endLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __cbegin (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > * {

        return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType const, ConstIterator > >(
                ConstIterator ( TreeMapBase :: __cbeginLocal( pObject->template map < TreeMapBase > () ) )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __cend (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > * {

        return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __ValueType const, ConstIterator > >(
                ConstIterator ( TreeMapBase :: __cendLocal( pObject->template map < TreeMapBase > () ) )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __cbeginLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator {

        return Iterator ( TreeMapBase :: __cbeginLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __cendLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator {

        return Iterator ( TreeMapBase :: __cendLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __rbeginLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> ReverseIterator {

        return Iterator ( TreeMapBase :: __rbeginLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __rendLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> ReverseIterator {

        return Iterator ( TreeMapBase :: __rendLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __crbeginLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstReverseIterator {

        return Iterator ( TreeMapBase :: __crbeginLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __crendLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstReverseIterator {

        return Iterator ( TreeMapBase :: __crendLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __remove (
            ValueMutableCollectionProxy * pObject,
            AbstractIterator const * iterator
    ) noexcept -> bool {

        return TreeMapBase :: __remove (
                pObject->template map < TreeMapBase > (),
                & iterator->iterator()
            );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __removeConst (
            ValueMutableCollectionProxy * pObject,
            AbstractConstIterator const * iterator
    ) noexcept -> bool {

        return TreeMapBase :: __removeConst (
                pObject->template map < TreeMapBase > (),
                & iterator->iterator()
            );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: ValueMutableCollectionProxy :: __removeArray (
            ValueMutableCollectionProxy * pObject,
            AbstractIterator const * const * ppIterators,
            Size                             iteratorCount
    ) noexcept -> Size {

        auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                typename cds :: __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractIterator const *
            > ( iteratorCount );

        for ( auto iteratorIndex = 0U; iteratorIndex < iteratorCount; ++ iteratorIndex ) {

            if ( ppIterators [ iteratorIndex ] != nullptr ) {
                ppWrappedIteratorArray [ iteratorIndex ] = & ppIterators [ iteratorIndex ]->iterator();
            } else {
                ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
            }
        }

        auto const removedIteratorCount = TreeMapBase :: __removeArray (
                pObject->template map < TreeMapBase > (),
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
            ValueMutableCollectionProxy * pObject,
            AbstractConstIterator const * const * ppIterators,
            Size                                  iteratorCount
    ) noexcept -> Size {

        auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                typename cds :: __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractConstIterator const *
            > ( iteratorCount );

        for ( auto iteratorIndex = 0U; iteratorIndex < iteratorCount; ++ iteratorIndex ) {

            if ( ppIterators [ iteratorIndex ] != nullptr ) {
                ppWrappedIteratorArray [ iteratorIndex ] = & ppIterators [ iteratorIndex ]->iterator();
            } else {
                ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
            }
        }

        auto const removedIteratorCount = TreeMapBase :: __removeConstArray (
                pObject->template map < TreeMapBase > (),
                ppWrappedIteratorArray,
                iteratorCount
        );

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppWrappedIteratorArray );
        return removedIteratorCount;
    }
}

#endif //__CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP_
