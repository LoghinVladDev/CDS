//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_HASH_MAP_ASSOCIATOR_HPP__
#define __CDS_EX_HASH_MAP_ASSOCIATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __KeyType, typename __ValueType, typename __HashCalculator >
                class __HashEntryArrayAssociator : public __EntryArray < __ValueType > :: template __EntryAssociator < __KeyType > {

                };

            }
        }
    }
}

#endif // __CDS_EX_HASH_MAP_ASSOCIATOR_HPP__
