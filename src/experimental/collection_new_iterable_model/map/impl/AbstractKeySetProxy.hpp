//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > constexpr Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: AbstractKeySetProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept :
                ProxyBase ( pMap ) {

        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: clear () noexcept -> void {

            this->map()->clear();
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: remove (
                KeyType const & key
        ) noexcept -> bool {

            return this->map()->remove(key);
        }

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__
