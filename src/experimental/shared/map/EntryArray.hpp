//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_ARRAY_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_ARRAY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                class __EntryArray : public cds :: experimental :: Array < __ValueType > { // NOLINT(bugprone-reserved-identifier)

                public:
                    template < typename __KeyType >
                    class __EntryAssociator;
                };

            }
        }
    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_ARRAY_HPP__
