//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy : public AbstractValueMutableCollectionProxy {

        public:
            using typename AbstractValueMutableCollectionProxy :: ValueType;

        public:
            using typename AbstractValueMutableCollectionProxy :: ElementType;

        public:
            using typename AbstractValueMutableCollectionProxy :: Iterator;

        public:
            using typename AbstractValueMutableCollectionProxy :: ConstIterator;

        public:
            using typename AbstractValueMutableCollectionProxy :: ReverseIterator;

        public:
            using typename AbstractValueMutableCollectionProxy :: ConstReverseIterator;

        protected:
            using typename AbstractValueMutableCollectionProxy :: InitializerList;

        protected:
            using typename AbstractValueMutableCollectionProxy :: DelegateIterator;

        protected:
            using typename AbstractValueMutableCollectionProxy :: DelegateConstIterator;

        protected:
            using typename AbstractValueMutableCollectionProxy :: AbstractIterator;

        protected:
            using typename AbstractValueMutableCollectionProxy :: AbstractDelegateIterator;

        protected:
            using typename AbstractValueMutableCollectionProxy :: DelegateIteratorRequestType;

        private:
            class HashMapValueMutableCollectionProxyDelegateIterator;

        private:
            class HashMapValueMutableCollectionProxyDelegateConstIterator;

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
            __CDS_Explicit constexpr HashMapValueMutableCollectionProxy (
                    HashMap < __KeyType, __ValueType, __Hasher > * pMap
            ) noexcept;

        public:
            constexpr HashMapValueMutableCollectionProxy (
                    HashMapValueMutableCollectionProxy const & collection
            ) noexcept;

        public:
            constexpr HashMapValueMutableCollectionProxy (
                    HashMapValueMutableCollectionProxy && collection
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapValueMutableCollectionProxy() noexcept override;

        public:
            auto remove (
                    Iterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto operator == (
                    HashMapValueMutableCollectionProxy const & collection
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashMapValueMutableCollectionProxy const & collection
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto size () const noexcept -> Size override;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
