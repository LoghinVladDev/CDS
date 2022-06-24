//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_HASH_MAP_KEY_SET_PROXY_DELEGATE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_HASH_MAP_KEY_SET_PROXY_DELEGATE_CONST_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: HashMapKeySetProxyDelegateConstIterator (
            HashTableConstIterator const & iterator
    ) noexcept :
            _iterator ( iterator ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: HashMapKeySetProxyDelegateConstIterator (
            HashMapKeySetProxyDelegateConstIterator const & iterator
    ) noexcept :
            _iterator ( iterator._iterator ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: HashMapKeySetProxyDelegateConstIterator (
            HashMapKeySetProxyDelegateConstIterator && iterator
    ) noexcept :
            _iterator ( std :: move ( iterator._iterator ) ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: ~HashMapKeySetProxyDelegateConstIterator () noexcept = default;


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: valid () const noexcept -> bool {

        return static_cast < bool > ( this->_iterator );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: iterator () const noexcept -> HashTableConstIterator const & {

        return this->_iterator;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: next () noexcept -> HashMapKeySetProxyDelegateConstIterator & {

        ++ this->_iterator;
        return * this;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: previous () noexcept -> HashMapKeySetProxyDelegateConstIterator & {

        return this->next();
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: value () const noexcept -> __KeyType const & {

        return ( * this->_iterator ).key();
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: equals (
            AbstractDelegateIterator const & iterator
    ) const noexcept -> bool {

        return reinterpret_cast < decltype ( this ) > ( & iterator )->_iterator == this->_iterator;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxyDelegateConstIterator :: copy () const noexcept -> HashMapKeySetProxyDelegateConstIterator * {

        return cds :: copy ( * this );
    }

}

#endif // __CDS_HASH_MAP_KEY_SET_PROXY_DELEGATE_CONST_ITERATOR_IMPL_HPP__
