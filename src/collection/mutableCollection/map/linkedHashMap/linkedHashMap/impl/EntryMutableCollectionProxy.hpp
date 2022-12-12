/*  NOLINT(llvm-header-guard)
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __cicch_obtainGenericHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__mcs_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __cicch_obtainGenericConstHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__mcs_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: EntryMutableCollectionProxy (
            LinkedHashMap < __KeyType, __ValueType, __Hasher > * pMap
    ) noexcept :
            AbstractEntryMutableCollectionProxy ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprDestructor LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: ~EntryMutableCollectionProxy () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: contains (
            EntryType const & entry
    ) const noexcept -> bool {

        return this->map()->containsKey ( entry.key() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __newAddress (
            EntryMutableCollectionProxy       * pObject,
            EntryType                   const * pReferenceElement,
            bool                              * pIsNew
    ) noexcept -> EntryType * {

        return pObject->template map < LinkedHashMapBase > ()->__ht_new (
                pReferenceElement,
                pIsNew
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
    > :: EntryMutableCollectionProxy :: __begin (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

        return LinkedHashMapBase :: __begin ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __end (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

        return LinkedHashMapBase :: __end ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __cbegin (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

        return LinkedHashMapBase :: __cbegin ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __cend (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

        return LinkedHashMapBase :: __cend ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __beginLocal (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> Iterator {

        return LinkedHashMapBase :: __beginLocal ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __endLocal (
            EntryMutableCollectionProxy * pObject
    ) noexcept -> Iterator {

        return LinkedHashMapBase :: __endLocal ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __cbeginLocal (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> ConstIterator {

        return LinkedHashMapBase :: __cbeginLocal ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __cendLocal (
            EntryMutableCollectionProxy const * pObject
    ) noexcept -> ConstIterator {

        return LinkedHashMapBase :: __cendLocal ( pObject->template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: __remove (
            EntryMutableCollectionProxy       * pObject,
            Iterator                    const * iterator
    ) noexcept -> bool {

        return LinkedHashMapBase :: __remove (
                pObject->template map < LinkedHashMapBase > (),
                iterator
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
    > :: EntryMutableCollectionProxy :: __removeConst (
            EntryMutableCollectionProxy       * pObject,
            ConstIterator               const * iterator
    ) noexcept -> bool {

        return LinkedHashMapBase :: __removeConst (
                pObject->template map < LinkedHashMapBase > (),
                iterator
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
    > :: EntryMutableCollectionProxy :: __removeArray (
            EntryMutableCollectionProxy               * pObject,
            Iterator                    const * const * ppIterators,
            Size                                        iteratorArrayCount
    ) noexcept -> Size {

        return LinkedHashMapBase :: __removeArray (
                pObject->template map < LinkedHashMapBase > (),
                ppIterators,
                iteratorArrayCount
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
    > :: EntryMutableCollectionProxy :: __removeConstArray (
            EntryMutableCollectionProxy               * pObject,
            ConstIterator               const * const * ppIterators,
            Size                                        iteratorArrayCount
    ) noexcept -> Size {

        return LinkedHashMapBase :: __removeConstArray (
                pObject->template map < LinkedHashMapBase > (),
                ppIterators,
                iteratorArrayCount
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
    > :: EntryMutableCollectionProxy :: __equals (
            EntryMutableCollectionProxy const & set
    ) const noexcept -> bool {

        return this->template map < LinkedHashMapBase > ()->__ht_equals ( * set.template map < LinkedHashMapBase > () );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :: operator == (
            EntryMutableCollectionProxy const & set
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
    > :: EntryMutableCollectionProxy :: operator != (
            EntryMutableCollectionProxy const & set
    ) const noexcept -> bool {

        return ! this->__equals ( set ); /* NOLINT(clion-misra-cpp2008-5-3-1) */
    }

} /* namespace cds */

#endif /* __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ */
