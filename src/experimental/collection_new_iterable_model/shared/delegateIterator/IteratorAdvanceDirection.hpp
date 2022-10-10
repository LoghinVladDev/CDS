/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__
#define __CDS_EX_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/delegateIterator/IteratorAdvanceDirection.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                using __IteratorAdvanceDirection __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __IteratorAdvanceDirection;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__ */
