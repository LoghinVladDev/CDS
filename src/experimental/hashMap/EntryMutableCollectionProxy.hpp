//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMapEntryMutableCollectionProxy : public AbstractEntryMutableCollectionProxy {

        public:
            using typename AbstractEntryMutableCollectionProxy :: EntryType;

        public:
            using typename AbstractEntryMutableCollectionProxy :: ElementType;

        public:
            using typename AbstractEntryMutableCollectionProxy :: Iterator;

        public:
            using typename AbstractEntryMutableCollectionProxy :: ConstIterator;

        public:
            using typename AbstractEntryMutableCollectionProxy :: ReverseIterator;

        public:
            using typename AbstractEntryMutableCollectionProxy :: ConstReverseIterator;

        protected:
            using typename AbstractEntryMutableCollectionProxy :: InitializerList;

        protected:
            using typename AbstractEntryMutableCollectionProxy :: DelegateIterator;

        protected:
            using typename AbstractEntryMutableCollectionProxy :: DelegateConstIterator;

        protected:
            using typename AbstractEntryMutableCollectionProxy :: AbstractIterator;

        protected:
            using typename AbstractEntryMutableCollectionProxy :: AbstractDelegateIterator;

        protected:
            using typename AbstractEntryMutableCollectionProxy :: DelegateIteratorRequestType;

        private:
            class HashMapEntryMutableCollectionProxyDelegateIterator;

        private:
            class HashMapEntryMutableCollectionProxyDelegateConstIterator;

        private:
            class HashMapEntryMutableCollectionProxyDelegateReverseIterator;

        private:
            class HashMapEntryMutableCollectionProxyDelegateConstReverseIterator;

        private:
            friend class HashMap;

        public:
            auto delegateIterator (
                    DelegateIteratorRequestType requestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override;

        public:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        public:
            constexpr HashMapEntryMutableCollectionProxy (
                    HashMap < __KeyType, __ValueType, __HashCalculator > * pMap
            ) noexcept;

        public:
            constexpr HashMapEntryMutableCollectionProxy (
                    HashMapEntryMutableCollectionProxy const & collection
            ) noexcept;

        public:
            constexpr HashMapEntryMutableCollectionProxy (
                    HashMapEntryMutableCollectionProxy && collection
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapEntryMutableCollectionProxy() noexcept override;

        public:
            auto operator == (
                    HashMapEntryMutableCollectionProxy const & collection
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashMapEntryMutableCollectionProxy const & collection
            ) const noexcept -> bool;

        public:
            auto operator = (
                    HashMapEntryMutableCollectionProxy const & collection
            ) noexcept -> HashMapEntryMutableCollectionProxy;

        public:
            auto operator = (
                    HashMapEntryMutableCollectionProxy && collection
            ) noexcept -> HashMapEntryMutableCollectionProxy;

        public:
            auto sequence () & noexcept -> Sequence < HashMapEntryMutableCollectionProxy >;

        public:
            auto sequence () && noexcept -> Sequence < HashMapEntryMutableCollectionProxy >;

        public:
            auto sequence () const & noexcept -> Sequence < HashMapEntryMutableCollectionProxy const >;

        public:
            auto sequence () const && noexcept -> Sequence < HashMapEntryMutableCollectionProxy const >;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
