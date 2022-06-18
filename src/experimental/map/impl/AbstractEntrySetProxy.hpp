//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_ENTRY_SET_PROXY_IMPL_HPP__
#define __CDS_EX_MAP_ABSTRACT_ENTRY_SET_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractEntrySetProxy :: AbstractEntrySetProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept :
                _pMap ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: AbstractEntrySetProxy :: ~AbstractEntrySetProxy() noexcept = default;

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_ENTRY_SET_PROXY_IMPL_HPP__
