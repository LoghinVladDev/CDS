//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_MAP_ENTRY_HPP__
#define __CDS_EX_MAP_ENTRY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                class __MapEntry { // NOLINT(bugprone-reserved-identifier)

                private:
                    __KeyType   _key;

                private:
                    __ValueType _value;


                };

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_HPP__
