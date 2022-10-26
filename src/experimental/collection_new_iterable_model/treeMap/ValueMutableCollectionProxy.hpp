//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_
#define __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_  /* NOLINT(bugprone-reserved-identifier) */
namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */


             }
        }

            template <
                    typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
            > class TreeMap <
                    __KeyType,
                    __ValueType
            > :: ValueMutableCollectionProxy :
                    private AbstractValueMutableCollectionProxy
            {

            };
    }
}
#endif //__CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_
