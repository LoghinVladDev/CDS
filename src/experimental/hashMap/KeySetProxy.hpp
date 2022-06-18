//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__
#define __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMapKeySetProxy : public AbstractKeySetProxy {

        public:
            using typename AbstractKeySetProxy :: KeyType;

        public:
            using typename AbstractKeySetProxy :: ElementType;

        public:
            using typename AbstractKeySetProxy :: ConstIterator;

        public:
            using typename AbstractKeySetProxy :: ConstReverseIterator;

        protected:
            using typename AbstractKeySetProxy :: InitializerList;

        protected:
            using typename AbstractKeySetProxy :: DelegateConstIterator;

        protected:
            using typename AbstractKeySetProxy :: AbstractIterator;

        protected:
            using typename AbstractKeySetProxy :: AbstractDelegateIterator;

        protected:
            using typename AbstractKeySetProxy :: DelegateIteratorRequestType;

        private:
            class HashMapKeySetProxyDelegateConstIterator;

        private:
            class HashMapKeySetProxyDelegateConstReverseIterator;

        public:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        public:
            constexpr HashMapKeySetProxy (
                    HashMap < __KeyType, __ValueType, __HashCalculator > * pMap
            ) noexcept;

        public:
            constexpr HashMapKeySetProxy (
                    HashMapKeySetProxy const & set
            ) noexcept;

        public:
            constexpr HashMapKeySetProxy (
                    HashMapKeySetProxy && set
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapKeySetProxy() noexcept override;

        public:
            auto operator == (
                    HashMapKeySetProxy const & set
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashMapKeySetProxy const & set
            ) const noexcept -> bool;

        public:
            auto sequence () & noexcept -> Sequence < HashMapEntrySetProxy >;

        public:
            auto sequence () && noexcept -> Sequence < HashMapEntrySetProxy >;

        public:
            auto sequence () const & noexcept -> Sequence < HashMapEntrySetProxy const >;

        public:
            auto sequence () const && noexcept -> Sequence < HashMapEntrySetProxy const >;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__
