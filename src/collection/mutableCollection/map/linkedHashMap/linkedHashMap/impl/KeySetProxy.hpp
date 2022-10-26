/*
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __cicch_obtainGenericHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __cicch_obtainGenericConstHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: KeySetProxy (
            LinkedHashMap < __KeyType, __ValueType, __Hasher > * pMap
    ) noexcept :
            AbstractKeySetProxy ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprDestructor LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: ~KeySetProxy () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: contains (
            __KeyType const & key
    ) const noexcept -> bool {

        return this->map()->containsKey ( key );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __cbeginLocal () const noexcept -> ConstIterator {

        return ConstIterator ( this->template map < LinkedHashMapBase > ()->__cbeginLocal() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __cendLocal () const noexcept -> ConstIterator {

        return ConstIterator ( this->template map < LinkedHashMapBase > ()->__cendLocal() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __cbegin () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > > (
                ConstIterator ( this->template map < LinkedHashMapBase > ()->__cbeginLocal() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __cend () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > > (
                ConstIterator ( this->template map < LinkedHashMapBase > ()->__cendLocal() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __removeConst (
            ConstIterator const * pIterator
    ) noexcept -> bool {

        return this->template map < LinkedHashMapBase > ()->__removeConst ( & pIterator->iterator() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __removeConstArray (
            ConstIterator   const * const * ppIterators,
            Size                            iteratorArrayCount
    ) noexcept -> Size {

        auto ppWrappedIteratorArray = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray <
                __hidden :: __impl :: __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher > const *
        > ( iteratorArrayCount );

        for ( uint32 iteratorIndex = 0U; iteratorIndex < iteratorArrayCount; ++ iteratorIndex ) {

            if ( ppIterators [ iteratorIndex ] != nullptr ) {
                ppWrappedIteratorArray [ iteratorIndex ] = & ppIterators [ iteratorIndex ]->iterator();
            } else {
                ppWrappedIteratorArray [ iteratorIndex ] = nullptr;
            }
        }

        auto const removedIteratorCount = this->template map < LinkedHashMapBase > ()->__removeConstArray (
                ppWrappedIteratorArray,
                iteratorArrayCount
        );

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppWrappedIteratorArray );
        return removedIteratorCount;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __findConst (
            __KeyType const & key
    ) const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > > (
                ConstIterator ( this->template map < LinkedHashMapBase > ()->__findConstLocal ( key ) )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __findConstLocal (
            __KeyType const & key
    ) const noexcept -> ConstIterator {

        return ConstIterator ( this->template map < LinkedHashMapBase > ()->__findConstLocal ( key ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: __equals (
            KeySetProxy const & set
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
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: operator == (
            KeySetProxy const & set
    ) const noexcept -> bool {

        return this->__equals ( set );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: KeySetProxy :: operator != (
            KeySetProxy const & set
    ) const noexcept -> bool {

        return ! this->__equals ( set );
    }

} /* namespace cds */

#endif /* __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__ */
