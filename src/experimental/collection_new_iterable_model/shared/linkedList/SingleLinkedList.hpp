/*
 * Created by loghin on 17/07/22.
 */

#ifndef __CDS_EX_SHARED_SINGLE_LINKED_LIST_HPP__
#define __CDS_EX_SHARED_SINGLE_LINKED_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/linkedList/SingleLinkedList.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals                        /* NOLINT(bugprone-reserved-identifier) */
                > using __SingleLinkedList __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __SingleLinkedList < __ElementType, __equals >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_SINGLE_LINKED_LIST_HPP__ */
