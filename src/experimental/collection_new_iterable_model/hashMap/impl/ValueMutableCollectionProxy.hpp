//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: ValueMutableCollectionProxy (
                HashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept :
                AbstractValueMutableCollectionProxy ( pMap ) {
                    
        }

    }
}

#endif // __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
