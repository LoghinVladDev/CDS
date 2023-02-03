//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_TREE_MAP_KEY_SET_PROXY_IMPL_HPP__     /* NOLINT(bugprone-reserved-identifier) */


namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __cicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
            cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __cicch_obtainGenericConstHandler (         /* NOLINT(bugprone-reserved-identifier) */
            cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: KeySetProxy (
            TreeMap < __KeyType, __ValueType > * pMap
    ) noexcept :
            AbstractKeySetProxy ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: contains (
            __KeyType const & key
    ) const noexcept -> bool {

        return this->map()->containsKey ( key );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __cbegin (
            KeySetProxy const * pObject
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

        return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > >(
                ConstIterator ( TreeMapBase :: __cbeginLocal( pObject->template map < TreeMapBase > () ) )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __cend (
            KeySetProxy const * pObject
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

        return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > >(
                ConstIterator ( TreeMapBase :: __cendLocal( pObject->template map < TreeMapBase > () ) )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __cbeginLocal (
            KeySetProxy const * pObject
    ) noexcept -> ConstIterator {

        return ConstIterator ( TreeMapBase :: __cbeginLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __cendLocal (
            KeySetProxy const * pObject
    ) noexcept -> ConstIterator {

        return ConstIterator ( TreeMapBase :: __cendLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __crbeginLocal (
            KeySetProxy const * pObject
    ) noexcept -> ConstReverseIterator {

        return Iterator ( TreeMapBase :: __crbeginLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __crendLocal (
            KeySetProxy const * pObject
    ) noexcept -> ConstReverseIterator {

        return Iterator ( TreeMapBase :: __crendLocal( pObject->template map < TreeMapBase > () ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __removeConst (
            KeySetProxy * pObject,
            AbstractConstIterator const * iterator
    ) noexcept -> bool {

        return TreeMapBase :: __removeConst (
                pObject->template map < TreeMapBase > (),
                & iterator->iterator()
        ) ;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __removeConstArray (
            KeySetProxy * pObject,
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

        auto const removedIteratorCount = TreeMapBase ::  __removeConstArray (
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
    > :: KeySetProxy :: __findConst (
            KeySetProxy const * pObject,
            __KeyType const &  key
    ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

        return Memory :: instance().create < cds :: __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > > (
                ConstIterator (
                        TreeMapBase :: __findConstLocal (
                                pObject->template map < TreeMapBase > (),
                                key
                        )
                )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeMap <
            __KeyType,
            __ValueType
    > :: KeySetProxy :: __findConstLocal (
            KeySetProxy const * pObject,
            __KeyType const &  key
    ) noexcept -> ConstIterator {

        return ConstIterator (
                TreeMapBase :: __findConstLocal (
                        pObject->template map < TreeMapBase > (),
                        key
                )
        );
    }
}

#endif //__CDS_TREE_MAP_KEY_SET_PROXY_IMPL_HPP__
