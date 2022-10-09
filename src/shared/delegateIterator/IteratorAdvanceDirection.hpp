/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__
#define __CDS_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @enum The types of delegate iterator requests the Collection Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             */
            enum class __IteratorAdvanceDirection {     /* NOLINT(bugprone-reserved-identifier) */

                /** Represents a Request for a Beginning Iterator, Advancing Forward */
                __iad_forward,                          /* NOLINT(bugprone-reserved-identifier) */

                /** Represents a Request for an End Iterator, Advancing Forward */
                __iad_backward,                         /* NOLINT(bugprone-reserved-identifier) */
            };

        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__ */
