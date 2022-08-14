//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_MAP_PROXY_IMPL_HPP__
#define __CDS_EX_MAP_ABSTRACT_MAP_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > constexpr Map <
                __KeyType,
                __ValueType
        > :: AbstractMapProxy :: AbstractMapProxy (
                Map < KeyType, ValueType > * pMap
        ) noexcept :
                _pMap ( pMap ) {

        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > constexpr Map <
                __KeyType,
                __ValueType
        > :: AbstractMapProxy :: AbstractMapProxy (
                AbstractMapProxy const & proxy
        ) noexcept :
                _pMap ( proxy._pMap ) {

        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > constexpr Map <
                __KeyType,
                __ValueType
        > :: AbstractMapProxy :: AbstractMapProxy (
                AbstractMapProxy && proxy
        ) noexcept :
                _pMap ( cds :: exchange ( proxy._pMap, nullptr ) ) {

        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > template <
                typename __DerivedType
        > __CDS_OptimalInline auto Map <
                __KeyType,
                __ValueType
        > :: AbstractMapProxy :: map () const noexcept -> __DerivedType * {

            return reinterpret_cast < __DerivedType * > ( this->_pMap );
        }

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_MAP_PROXY_IMPL_HPP__
