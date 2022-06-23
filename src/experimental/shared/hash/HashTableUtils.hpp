//
// Created by loghin on 6/20/22.
//

#ifndef __CDS_EX_HASH_TABLE_UTILS_HPP__
#define __CDS_EX_HASH_TABLE_UTILS_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)

        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __Hasher, typename __RehashPolicy > // NOLINT(bugprone-reserved-identifier)
                struct __HashTableUtils { // NOLINT(bugprone-reserved-identifier)
                    __Hasher        _hasher;
                    __RehashPolicy  _rehashPolicy;

                    constexpr __HashTableUtils () noexcept = default;

                    constexpr __HashTableUtils (
                            __HashTableUtils const & hashUtils
                    ) noexcept :
                            _hasher ( hashUtils._hasher ),
                            _rehashPolicy ( hashUtils._rehashPolicy ) {

                    }

                    __CDS_Explicit constexpr __HashTableUtils (
                            __Hasher const & hasher
                    ) noexcept :
                            _hasher ( hasher ) {

                    }
                };
            }
        }

    }
}

#endif // __CDS_EX_HASH_TABLE_UTILS_HPP__
