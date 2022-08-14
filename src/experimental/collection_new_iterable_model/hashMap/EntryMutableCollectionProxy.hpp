//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ServerType,                      // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType,                       // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher,                          // NOLINT(bugprone-reserved-identifier)
                        typename __HashMap =                        // NOLINT(bugprone-reserved-identifier)
                                cds :: experimental :: HashMap <    // NOLINT(bugprone-reserved-identifier)
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                > using __HashMapEntryProxyServer =                 // NOLINT(bugprone-reserved-identifier)
                        __MutableCollectionServer <
                                __ServerType,
                                typename __HashMap :: EntryType
                        >;


                template <
                        typename __ServerType,                      // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType,                       // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher,                          // NOLINT(bugprone-reserved-identifier)
                        typename __HashMap =                        // NOLINT(bugprone-reserved-identifier)
                                cds :: experimental :: HashMap <    // NOLINT(bugprone-reserved-identifier)
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                > using __HashMapEntryProxyDelegateIterableServer = // NOLINT(bugprone-reserved-identifier)
                        __DelegateIterableServer <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                true,
                                false,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                                void,
                                void
                        >;

            }
        }

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
                protected __hidden :: __impl :: __HashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyDelegateIterableServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher > {

        protected:  using HashMapBase   = HashMap < __KeyType, __ValueType, __Hasher >;
        protected:  using Server        = __hidden :: __impl :: __HashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

        protected:  using typename AbstractEntryMutableCollectionProxy :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename AbstractEntryMutableCollectionProxy :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        public:     using Iterator      = typename HashMapBase :: Iterator;
        public:     using ConstIterator = typename HashMapBase :: ConstIterator;

        protected:  friend Server;

        protected:  using AbstractEntryMutableCollectionProxy :: begin;
        protected:  using AbstractEntryMutableCollectionProxy :: end;
        protected:  using AbstractEntryMutableCollectionProxy :: cbegin;
        protected:  using AbstractEntryMutableCollectionProxy :: cend;

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
            auto __newAddress ( // NOLINT(bugprone-reserved-identifier)
                    EntryType const * pReferenceElement,
                    bool            * pIsNew
            ) noexcept -> EntryType *;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator;

        public:
            __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;

        public:
            auto __remove ( // NOLINT(bugprone-reserved-identifier)
                    Iterator const * iterator
            ) noexcept -> bool;

        public:
            auto __removeConst (    // NOLINT(bugprone-reserved-identifier)
                    ConstIterator const * iterator
            ) noexcept -> bool;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
