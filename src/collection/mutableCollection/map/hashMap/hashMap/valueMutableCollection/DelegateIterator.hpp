//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_ITERATOR_HPP__
#define __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_ITERATOR_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    class HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator : public DelegateIterator {

    private:
        using HashTableIterator = typename HashMap < __KeyType, __ValueType, __Hasher > :: HashTableIterator;

    private:
        HashTableIterator _iterator;

    public:
        __CDS_Explicit constexpr HashMapValueMutableCollectionProxyDelegateIterator (
                HashTableIterator const & iterator
        ) noexcept;

    public:
        constexpr HashMapValueMutableCollectionProxyDelegateIterator (
                HashMapValueMutableCollectionProxyDelegateIterator const & iterator
        ) noexcept;

    public:
        constexpr HashMapValueMutableCollectionProxyDelegateIterator (
                HashMapValueMutableCollectionProxyDelegateIterator && iterator
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~HashMapValueMutableCollectionProxyDelegateIterator () noexcept override;

    public:
        __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

    public:
        __CDS_NoDiscard constexpr auto iterator () const noexcept -> HashTableIterator const &;

    public:
        __CDS_cpplang_ConstexprOverride auto next () noexcept -> HashMapValueMutableCollectionProxyDelegateIterator & override;

    public:
        __CDS_cpplang_ConstexprOverride auto previous () noexcept -> HashMapValueMutableCollectionProxyDelegateIterator & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ValueType & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto copy () const noexcept -> HashMapValueMutableCollectionProxyDelegateIterator * override;
    };

}

#endif // __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_ITERATOR_HPP__
