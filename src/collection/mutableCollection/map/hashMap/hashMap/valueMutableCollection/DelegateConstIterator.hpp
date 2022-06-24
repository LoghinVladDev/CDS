//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_CONST_ITERATOR_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    class HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateConstIterator : public DelegateConstIterator {

    private:
        using HashTableConstIterator = typename HashMap < __KeyType, __ValueType, __Hasher > :: HashTableConstIterator;

    private:
        HashTableConstIterator _iterator;

    public:
        __CDS_Explicit constexpr HashMapValueMutableCollectionProxyDelegateConstIterator (
                HashTableConstIterator const & iterator
        ) noexcept;

    public:
        constexpr HashMapValueMutableCollectionProxyDelegateConstIterator (
                HashMapValueMutableCollectionProxyDelegateConstIterator const & iterator
        ) noexcept;

    public:
        constexpr HashMapValueMutableCollectionProxyDelegateConstIterator (
                HashMapValueMutableCollectionProxyDelegateConstIterator && iterator
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~HashMapValueMutableCollectionProxyDelegateConstIterator () noexcept override;

    public:
        __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

    public:
        __CDS_NoDiscard constexpr auto iterator () const noexcept -> HashTableConstIterator const &;

    public:
        __CDS_cpplang_ConstexprOverride auto next () noexcept -> HashMapValueMutableCollectionProxyDelegateConstIterator & override;

    public:
        __CDS_cpplang_ConstexprOverride auto previous () noexcept -> HashMapValueMutableCollectionProxyDelegateConstIterator & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ValueType const & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto copy () const noexcept -> HashMapValueMutableCollectionProxyDelegateConstIterator * override;
    };

}

#endif // __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_CONST_ITERATOR_HPP__
