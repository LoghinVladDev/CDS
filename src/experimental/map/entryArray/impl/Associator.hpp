//
// Created by loghin on 6/17/22.
//

#ifndef __CDS_EX_MAP_ENTRY_ARRAY_ENTRY_ASSOCIATOR_IMPL_HPP__
#define __CDS_EX_MAP_ENTRY_ARRAY_ENTRY_ASSOCIATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                template < typename __KeyType > // NOLINT(bugprone-reserved-identifier)
                constexpr __EntryArray < __ValueType > :: __EntryAssociator < __KeyType > :: __EntryAssociator (
                        __EntryArray < __ValueType > & array
                ) noexcept :
                        _array ( array ) {

                }

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_ARRAY_ENTRY_ASSOCIATOR_IMPL_HPP__
