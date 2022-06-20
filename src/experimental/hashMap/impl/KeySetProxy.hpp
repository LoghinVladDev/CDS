//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            /// TODO : return here after HashMap iterators done
            return nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxy (
                HashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractKeySetProxy ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxy (
                HashMapKeySetProxy const & keySetProxy
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractKeySetProxy ( keySetProxy ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxy (
                HashMapKeySetProxy && keySetProxy
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractKeySetProxy ( std :: move ( keySetProxy ) ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: ~HashMapKeySetProxy() noexcept = default;

    }
}

#endif // __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
