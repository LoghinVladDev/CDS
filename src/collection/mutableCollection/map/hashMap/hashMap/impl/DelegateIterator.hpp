//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_HASH_MAP_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_HASH_MAP_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: HashMapDelegateIterator (
            HashTableIterator const & iterator
    ) noexcept :
            _iterator ( iterator ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: HashMapDelegateIterator (
            HashMapDelegateIterator const & iterator
    ) noexcept :
            _iterator ( iterator._iterator ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: HashMapDelegateIterator (
            HashMapDelegateIterator && iterator
    ) noexcept :
            _iterator ( std :: move ( iterator._iterator ) ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: ~HashMapDelegateIterator () noexcept = default;


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: valid () const noexcept -> bool {

        return static_cast < bool > ( this->_iterator );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: iterator () const noexcept -> HashTableIterator const & {

        return this->_iterator;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: next () noexcept -> HashMapDelegateIterator & {

        ++ this->_iterator;
        return * this;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: previous () noexcept -> HashMapDelegateIterator & {

        return this->next();
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: value () const noexcept -> HashMap < __KeyType, __ValueType, __Hasher > :: ElementType & {

        return * this->_iterator;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: equals (
            AbstractDelegateIterator const & iterator
    ) const noexcept -> bool {

        return reinterpret_cast < decltype ( this ) > ( & iterator )->_iterator == this->_iterator;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator :: copy () const noexcept -> HashMapDelegateIterator * {

        return cds :: copy ( * this );
    }
    
}

#endif // __CDS_HASH_MAP_DELEGATE_ITERATOR_IMPL_HPP__
