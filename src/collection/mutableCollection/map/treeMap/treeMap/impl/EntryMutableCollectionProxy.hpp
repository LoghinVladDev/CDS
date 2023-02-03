//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP_
#define __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP_     /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __cicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
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
    > :: EntryMutableCollectionProxy :: __cicch_obtainGenericConstHandler (         /* NOLINT(bugprone-reserved-identifier) */
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
    > :: EntryMutableCollectionProxy :: EntryMutableCollectionProxy (
            TreeMap < __KeyType, __ValueType > * pMap
    ) noexcept :
            AbstractEntryMutableCollectionProxy ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __newAddress (
            EntryMutableCollectionProxy * pObject,
            EntryType const * pReferenceElement,
            bool            * pIsNew
    ) noexcept -> EntryType * {

        return pObject->template map < TreeMapBase > () -> __rbt_new (
                pReferenceElement,
                pIsNew
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __begin (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

        return TreeMapBase :: __begin ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __end (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

        return TreeMapBase :: __end ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __beginLocal (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> Iterator {

        return TreeMapBase :: __beginLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __endLocal (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> Iterator {

        return TreeMapBase :: __endLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __cbegin (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

        return TreeMapBase :: __cbegin ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __cend (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

        return TreeMapBase :: __cend ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __cbeginLocal (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> ConstIterator {

        return TreeMapBase :: __cbeginLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __cendLocal (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> ConstIterator {

        return TreeMapBase :: __cendLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __rbeginLocal (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> ReverseIterator {

        return TreeMapBase :: __rbeginLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __rendLocal (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> ReverseIterator {

        return TreeMapBase :: __rendLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __crbeginLocal (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> ConstReverseIterator {

        return TreeMapBase :: __crbeginLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __crendLocal (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> ConstReverseIterator {

        return TreeMapBase :: __crendLocal ( pObject->template map < TreeMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __remove (
            EntryMutableCollectionProxy * pObject,
            AbstractIterator const * iterator
    ) noexcept -> bool {

        return TreeMapBase :: __remove ( pObject->template map < TreeMapBase > (), iterator ) ;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __removeConst (
            EntryMutableCollectionProxy * pObject,
            AbstractConstIterator const * iterator
    ) noexcept -> bool {

        return TreeMapBase :: __removeConst ( pObject->template map < TreeMapBase > (), iterator ) ;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: EntryMutableCollectionProxy :: __removeArray (
            EntryMutableCollectionProxy * pObject,
            AbstractIterator const * const * ppIterators,
            Size                             iteratorCount
    ) noexcept -> Size {

        auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                typename cds :: __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractIterator const *
        > ( iteratorCount );

        for ( auto iteratorIndex = 0U; iteratorIndex < iteratorCount; ++ iteratorIndex ) {

            if ( ppIterators [ iteratorIndex ] != nullptr ) {
                ppWrappedIteratorArray [ iteratorIndex ] = ppIterators [ iteratorIndex ];
            } else {
                ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
            }
        }

        auto const removedIteratorCount = TreeMapBase ::  __removeArray (
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
    > :: EntryMutableCollectionProxy :: __removeConstArray (
            EntryMutableCollectionProxy * pObject,
            AbstractConstIterator const * const * ppIterators,
            Size                                  iteratorCount
    ) noexcept -> Size {

        auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                typename cds :: __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractConstIterator const *
        > ( iteratorCount );

        for ( auto iteratorIndex = 0U; iteratorIndex < iteratorCount; ++ iteratorIndex ) {

            if ( ppIterators [ iteratorIndex ] != nullptr ) {
                ppWrappedIteratorArray [ iteratorIndex ] = ppIterators [ iteratorIndex ];
            } else {
                ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
            }
        }

        auto const removedIteratorCount = TreeMapBase ::  __removeConstArray (
                pObject->template map < TreeMapBase > (),
                ppWrappedIteratorArray,
                iteratorCount
        );

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppWrappedIteratorArray );
        return removedIteratorCount;
    }
}

#endif //__CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP_
