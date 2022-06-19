//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMapValueMutableCollectionProxy : public AbstractValueMutableCollectionProxy {

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
            class HashMapValueMutableCollectionProxyDelegateReverseIterator;

        private:
            class HashMapValueMutableCollectionProxyDelegateConstReverseIterator;

        public:
            auto delegateIterator (
                    DelegateIteratorRequestType requestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override;

        public:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        public:
            constexpr HashMapValueMutableCollectionProxy (
                    HashMap < __KeyType, __ValueType, __HashCalculator > * pMap
            ) noexcept;

        public:
            constexpr HashMapValueMutableCollectionProxy (
                    HashMapValueMutableCollectionProxy const & set
            ) noexcept;

        public:
            constexpr HashMapValueMutableCollectionProxy (
                    HashMapValueMutableCollectionProxy && set
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapValueMutableCollectionProxy() noexcept override;

        public:
            auto operator == (
                    HashMapValueMutableCollectionProxy const & set
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashMapValueMutableCollectionProxy const & set
            ) const noexcept -> bool;

        public:
            auto sequence () & noexcept -> Sequence < HashMapValueMutableCollectionProxy >;

        public:
            auto sequence () && noexcept -> Sequence < HashMapValueMutableCollectionProxy >;

        public:
            auto sequence () const & noexcept -> Sequence < HashMapValueMutableCollectionProxy const >;

        public:
            auto sequence () const && noexcept -> Sequence < HashMapValueMutableCollectionProxy const >;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
