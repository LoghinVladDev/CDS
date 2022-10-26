/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @enum The types of delegate iterator requests the Collection Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             */
            enum class __IteratorAdvanceDirection {     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a Beginning Iterator, Advancing Forward */
                __iad_forward,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for an End Iterator, Advancing Forward */
                __iad_backward,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_ADVANCE_DIRECTION_HPP__ */
