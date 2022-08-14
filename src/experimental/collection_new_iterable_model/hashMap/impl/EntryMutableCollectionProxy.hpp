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
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :: __newAddress (
                EntryType const * pReferenceElement,
                bool            * pIsNew
        ) noexcept -> EntryType * {

            return this->template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_new (
                    pReferenceElement,
                    pIsNew
            );
        }

    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
