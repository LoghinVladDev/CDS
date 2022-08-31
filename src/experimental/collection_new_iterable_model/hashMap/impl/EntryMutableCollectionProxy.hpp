//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__mcs_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__mcs_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: EntryMutableCollectionProxy (
                HashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept :
                AbstractEntryMutableCollectionProxy ( pMap ) {

        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprDestructor HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: ~EntryMutableCollectionProxy () noexcept = default;


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __newAddress (
                EntryType const * pReferenceElement,
                bool            * pIsNew
        ) noexcept -> EntryType * {

            return this->template map < HashMapBase > ()->__ht_new (
                    pReferenceElement,
                    pIsNew
            );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __begin () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

            return this->template map < HashMapBase > ()->__begin();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __end () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

            return this->template map < HashMapBase > ()->__end();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __cbegin () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

            return this->template map < HashMapBase > ()->__cbegin();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __cend () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

            return this->template map < HashMapBase > ()->__cend();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __beginLocal () noexcept -> Iterator {

            return this->template map < HashMapBase > ()->__beginLocal();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __endLocal () noexcept -> Iterator {

            return this->template map < HashMapBase > ()->__endLocal();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __cbeginLocal () const noexcept -> ConstIterator {

            return this->template map < HashMapBase > ()->__cbeginLocal();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __cendLocal () const noexcept -> ConstIterator {

            return this->template map < HashMapBase > ()->__cendLocal();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __remove (
                Iterator const * iterator
        ) noexcept -> bool {

            return this->template map < HashMapBase > ()->__remove ( iterator );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __removeConst (
                ConstIterator const * iterator
        ) noexcept -> bool {

            return this->template map < HashMapBase > ()->__removeConst ( iterator );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __removeArray (
                Iterator    const * const * ppIterators,
                Size                        iteratorArrayCount
        ) noexcept -> Size {

            return this->template map < HashMapBase > ()->__removeArray (
                    ppIterators,
                    iteratorArrayCount
            );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __removeConstArray (
                ConstIterator   const * const * ppIterators,
                Size                            iteratorArrayCount
        ) noexcept -> Size {

            return this->template map < HashMapBase > ()->__removeConstArray (
                    ppIterators,
                    iteratorArrayCount
            );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __equals (
                EntryMutableCollectionProxy const & set
        ) const noexcept -> bool {

            return this->template map < HashMapBase > ()->__ht_equals ( * set.template map < HashMapBase > () );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: operator == (
                EntryMutableCollectionProxy const & set
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
        > :: EntryMutableCollectionProxy :: operator != (
                EntryMutableCollectionProxy const & set
        ) const noexcept -> bool {

            return ! this->__equals ( set );
        }

    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
