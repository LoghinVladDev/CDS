//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMapEntryMutableCollectionProxy :: HashMapEntryMutableCollectionProxy (
                HashMap < __KeyType, __ValueType, __HashCalculator > * pMap
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMapEntryMutableCollectionProxy :: ~HashMapEntryMutableCollectionProxy() noexcept = default;

    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
