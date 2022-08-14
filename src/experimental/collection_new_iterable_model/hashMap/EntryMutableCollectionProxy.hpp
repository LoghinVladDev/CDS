//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > class HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :
                public AbstractEntryMutableCollectionProxy,
                protected __hidden :: __impl :: __MutableCollectionServer <
                        EntryMutableCollectionProxy,
                        EntryType
                > {

        protected:  using typename AbstractEntryMutableCollectionProxy :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename AbstractEntryMutableCollectionProxy :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        public:
            __CDS_Explicit constexpr EntryMutableCollectionProxy (
                    HashMap < __KeyType, __ValueType, __Hasher > * pMap
            ) noexcept;
            
        public:
            auto __newAddress (
                    EntryType const * pReferenceElement,
                    bool            * pIsNew
            ) noexcept -> EntryType *;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
