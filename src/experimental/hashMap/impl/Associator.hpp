//
// Created by loghin on 6/17/22.
//

#ifndef __CDS_EX_HASH_MAP_ASSOCIATOR_IMPL_HPP__
#define __CDS_EX_HASH_MAP_ASSOCIATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
                constexpr __HashEntryArrayAssociator <
                        __KeyType,
                        __ValueType,
                        __HashCalculator
                > :: __HashEntryArrayAssociator (
                        __EntryArray < __ValueType > & entryArray
                ) noexcept :
                        __EntryArray < __ValueType > :: template __EntryAssociator < __KeyType > ( entryArray ) {

                }

            }
        }
    }
}

#endif // __CDS_EX_HASH_MAP_ASSOCIATOR_IMPL_HPP__
