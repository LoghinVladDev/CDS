//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_EX_HASH_MAP_KEY_SET_PROXY_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_EX_HASH_MAP_KEY_SET_PROXY_DELEGATE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator : public DelegateConstIterator {

        private:
            using HashTableConstIterator = typename HashMap < __KeyType, __ValueType, __Hasher > :: HashTableConstIterator;

        private:
            HashTableConstIterator _iterator;

        public:
            __CDS_Explicit constexpr HashMapKeySetProxyDelegateConstIterator (
                    HashTableConstIterator const & iterator
            ) noexcept;

        public:
            constexpr HashMapKeySetProxyDelegateConstIterator (
                    HashMapKeySetProxyDelegateConstIterator const & iterator
            ) noexcept;

        public:
            constexpr HashMapKeySetProxyDelegateConstIterator (
                    HashMapKeySetProxyDelegateConstIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapKeySetProxyDelegateConstIterator () noexcept override;

        public:
            __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

        public:
            __CDS_NoDiscard constexpr auto iterator () const noexcept -> HashTableConstIterator const &;

        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> HashMapKeySetProxyDelegateConstIterator & override;

        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> HashMapKeySetProxyDelegateConstIterator & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __KeyType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                    AbstractDelegateIterator const & iterator
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard auto copy () const noexcept -> HashMapKeySetProxyDelegateConstIterator * override;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_KEY_SET_PROXY_DELEGATE_CONST_ITERATOR_HPP__
