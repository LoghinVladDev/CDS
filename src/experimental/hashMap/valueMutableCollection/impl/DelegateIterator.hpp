//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: HashMapValueMutableCollectionProxyDelegateIterator (
                HashTableIterator const & iterator
        ) noexcept :
                _iterator ( iterator ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: HashMapValueMutableCollectionProxyDelegateIterator (
                HashMapValueMutableCollectionProxyDelegateIterator const & iterator
        ) noexcept :
                _iterator ( iterator._iterator ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: HashMapValueMutableCollectionProxyDelegateIterator (
                HashMapValueMutableCollectionProxyDelegateIterator && iterator
        ) noexcept :
                _iterator ( std :: move ( iterator._iterator ) ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: ~HashMapValueMutableCollectionProxyDelegateIterator () noexcept = default;


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: valid () const noexcept -> bool {

            return static_cast < bool > ( this->_iterator );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: iterator () const noexcept -> HashTableIterator const & {

            return this->_iterator;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: next () noexcept -> HashMapValueMutableCollectionProxyDelegateIterator & {

            ++ this->_iterator;
            return * this;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: previous () noexcept -> HashMapValueMutableCollectionProxyDelegateIterator & {

            return this->next();
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: value () const noexcept -> __ValueType & {

            return ( * this->_iterator ).value();
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool {

            return reinterpret_cast < decltype ( this ) > ( & iterator )->_iterator == this->_iterator;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxyDelegateIterator :: copy () const noexcept -> HashMapValueMutableCollectionProxyDelegateIterator * {

            return cds :: copy ( * this );
        }

    }
}

#endif // __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_DELEGATE_ITERATOR_IMPL_HPP__
