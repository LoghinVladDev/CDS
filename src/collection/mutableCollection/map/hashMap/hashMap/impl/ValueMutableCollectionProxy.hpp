/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __cicch_obtainGenericHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__mcs_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __cicch_obtainGenericConstHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__mcs_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: ValueMutableCollectionProxy (
            HashMap < __KeyType, __ValueType, __Hasher > * pMap
    ) noexcept :
            AbstractValueMutableCollectionProxy ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprDestructor HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: ~ValueMutableCollectionProxy () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __begin () noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ValueType > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ValueType, Iterator > > (
                Iterator ( this->template map < HashMapBase > ()->__beginLocal() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __end () noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ValueType > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ValueType, Iterator > > (
                Iterator ( this->template map < HashMapBase > ()->__endLocal() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __cbegin () const noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ValueType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ValueType const, ConstIterator > > (
                ConstIterator ( this->template map < HashMapBase > ()->__cbeginLocal() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __cend () const noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ValueType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ValueType const, ConstIterator > > (
                ConstIterator ( this->template map < HashMapBase > ()->__cendLocal() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __beginLocal () noexcept -> Iterator {

        return Iterator ( this->template map < HashMapBase > ()->__beginLocal() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __endLocal () noexcept -> Iterator {

        return Iterator ( this->template map < HashMapBase > ()->__endLocal() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __cbeginLocal () const noexcept -> ConstIterator {

        return ConstIterator ( this->template map < HashMapBase > ()->__cbeginLocal() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __cendLocal () const noexcept -> ConstIterator {

        return ConstIterator ( this->template map < HashMapBase > ()->__cendLocal() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __remove (
            Iterator const * pIterator
    ) noexcept -> bool {

        return this->template map < HashMapBase > ()->__remove ( & pIterator->iterator() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __removeConst (
            ConstIterator const * pIterator
    ) noexcept -> bool {

        return this->template map < HashMapBase > ()->__removeConst ( & pIterator->iterator() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __removeArray (
            Iterator    const * const * ppIterators,
            Size                        iteratorArrayCount
    ) noexcept -> Size {

        auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                typename cds :: __hidden :: __impl :: __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator const *
        > ( iteratorArrayCount );

        for ( uint32 iteratorIndex = 0U; iteratorIndex < iteratorArrayCount; ++ iteratorIndex ) {

            if ( ppIterators [ iteratorIndex ] != nullptr ) {
                ppWrappedIteratorArray [ iteratorIndex ] = & ppIterators [ iteratorIndex ]->iterator();
            } else {
                ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
            }
        }

        auto const removedIteratorCount = this->template map < HashMapBase > ()->__removeArray (
                ppWrappedIteratorArray,
                iteratorArrayCount
        );

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppWrappedIteratorArray );
        return removedIteratorCount;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __removeConstArray (
            ConstIterator   const * const * ppIterators,
            Size                            iteratorArrayCount
    ) noexcept -> Size {

        auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                typename cds :: __hidden :: __impl :: __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator const *
        > ( iteratorArrayCount );

        for ( uint32 iteratorIndex = 0U; iteratorIndex < iteratorArrayCount; ++ iteratorIndex ) {

            if ( ppIterators [ iteratorIndex ] != nullptr ) {
                ppWrappedIteratorArray [ iteratorIndex ] = & ppIterators [ iteratorIndex ]->iterator();
            } else {
                ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
            }
        }

        auto const removedIteratorCount = this->template map < HashMapBase > ()->__removeConstArray (
                ppWrappedIteratorArray,
                iteratorArrayCount
        );

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppWrappedIteratorArray );
        return removedIteratorCount;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: __equals (
            ValueMutableCollectionProxy const & set
    ) const noexcept -> bool {

        if ( this == & set ) {
            return true;
        }

        if ( this->size() != set.size() ) {
            return false;
        }

        for (
                auto
                        leftIt  = this->begin(),    rightIt     = set.begin(),
                        leftEnd = this->end(),      rightEnd    = set.end();

                leftIt != leftEnd;
                ++ leftIt, ++ rightIt
        ) {
            if ( ! cds :: meta :: equals ( * leftIt, * rightIt ) ) {
                return false;
            }
        }

        return true;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: operator == (
            ValueMutableCollectionProxy const & set
    ) const noexcept -> bool {

        return this->__equals ( set );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :: operator != (
            ValueMutableCollectionProxy const & set
    ) const noexcept -> bool {

        return ! this->__equals ( set );
    }

}

#endif /* __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ */
