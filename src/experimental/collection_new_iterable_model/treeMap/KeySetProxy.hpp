//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_KEY_SET_PROXY_HPP__
#define __CDS_TREE_MAP_KEY_SET_PROXY_HPP__  /* NOLINT(bugprone-reserved-identifier) */
namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            }
        }

        template <
                typename __KeyType,
                typename __ValueType
        > class TreeMap <
                __KeyType,
                __ValueType
        > :: KeySetProxy :
                public AbstractKeySetProxy {

        };
    }
}
#endif //__CDS_TREE_MAP_KEY_SET_PROXY_HPP__
