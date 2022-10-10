/*
 * Created by loghin on 6/29/22.
 */

#ifndef __CDS_EX_SHARED_ITERATOR_DISTANCE_HPP__
#define __CDS_EX_SHARED_ITERATOR_DISTANCE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/IteratorDistance.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __IteratorType, typename >                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                using __IteratorDistance __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: __hidden :: __impl :: __IteratorDistance < __IteratorType >;   /* NOLINT(bugprone-reserved-identifier) */

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_ITERATOR_DISTANCE_HPP__ */
