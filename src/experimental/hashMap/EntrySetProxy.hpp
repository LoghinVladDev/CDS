//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_SET_PROXY_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_SET_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMapEntrySetProxy : public AbstractEntrySetProxy {

        public:
            using typename AbstractEntrySetProxy :: EntryType;

        public:
            using typename AbstractEntrySetProxy :: ElementType;

        public:
            using typename AbstractEntrySetProxy :: ConstIterator;

        public:
            using typename AbstractEntrySetProxy :: ConstReverseIterator;

        protected:
            using typename AbstractEntrySetProxy :: InitializerList;

        protected:
            using typename AbstractEntrySetProxy :: DelegateConstIterator;

        protected:
            using typename AbstractEntrySetProxy :: AbstractIterator;

        protected:
            using typename AbstractEntrySetProxy :: AbstractDelegateIterator;

        protected:
            using typename AbstractEntrySetProxy :: DelegateIteratorRequestType;

        private:
            class HashMapEntrySetProxyDelegateConstIterator;

        private:
            class HashMapEntrySetProxyDelegateConstReverseIterator;

        public:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        public:
            constexpr HashMapEntrySetProxy (
                    HashMap < __KeyType, __ValueType, __HashCalculator > * pMap
            ) noexcept;

        public:
            constexpr HashMapEntrySetProxy (
                    HashMapEntrySetProxy const & set
            ) noexcept;

        public:
            constexpr HashMapEntrySetProxy (
                    HashMapEntrySetProxy && set
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapEntrySetProxy() noexcept override;

        public:
            auto operator == (
                    HashMapEntrySetProxy const & set
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashMapEntrySetProxy const & set
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

#endif // __CDS_EX_HASH_MAP_ENTRY_SET_PROXY_HPP__
