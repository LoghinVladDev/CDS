//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_VALUE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_VALUE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMapValueCollectionProxy : public AbstractValueCollectionProxy {

        public:
            using typename AbstractValueCollectionProxy :: ValueType;

        public:
            using typename AbstractValueCollectionProxy :: ElementType;

        public:
            using typename AbstractValueCollectionProxy :: ConstIterator;

        public:
            using typename AbstractValueCollectionProxy :: ConstReverseIterator;

        protected:
            using typename AbstractValueCollectionProxy :: InitializerList;

        protected:
            using typename AbstractValueCollectionProxy :: DelegateConstIterator;

        protected:
            using typename AbstractValueCollectionProxy :: AbstractIterator;

        protected:
            using typename AbstractValueCollectionProxy :: AbstractDelegateIterator;

        protected:
            using typename AbstractValueCollectionProxy :: DelegateIteratorRequestType;

        private:
            class HashMapValueCollectionProxyDelegateConstIterator;

        private:
            class HashMapValueCollectionProxyDelegateConstReverseIterator;

        public:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        public:
            constexpr HashMapValueCollectionProxy (
                    HashMap < __KeyType, __ValueType, __HashCalculator > * pMap
            ) noexcept;

        public:
            constexpr HashMapValueCollectionProxy (
                    HashMapValueCollectionProxy const & set
            ) noexcept;

        public:
            constexpr HashMapValueCollectionProxy (
                    HashMapValueCollectionProxy && set
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapValueCollectionProxy() noexcept override;

        public:
            auto operator == (
                    HashMapValueCollectionProxy const & set
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashMapValueCollectionProxy const & set
            ) const noexcept -> bool;

        public:
            auto toString () const noexcept -> String override;

        public:
            auto sequence () & noexcept -> Sequence < HashMapValueCollectionProxy >;

        public:
            auto sequence () && noexcept -> Sequence < HashMapValueCollectionProxy >;

        public:
            auto sequence () const & noexcept -> Sequence < HashMapValueCollectionProxy const >;

        public:
            auto sequence () const && noexcept -> Sequence < HashMapValueCollectionProxy const >;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_VALUE_COLLECTION_PROXY_HPP__
