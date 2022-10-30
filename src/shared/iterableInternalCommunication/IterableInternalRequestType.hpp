/*
 * Created by loghin on 4/26/22.
 */

#ifndef __CDS_SHARED_ITERABLE_INTERNAL_REQUEST_TYPE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERABLE_INTERNAL_REQUEST_TYPE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @enum The types of delegate iterator requests the Iterable Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             */
            enum class __IterableInternalRequestType {          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a Beginning Iterator, Advancing Forward */
                __iirt_begin                        = 0x00U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for an End Iterator, Advancing Forward */
                __iirt_end                          = 0x01U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a Beginning Iterator, Advancing Backwards ( reverse iteration ) */
                __iirt_rbegin                       = 0x02U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a End Iterator, Advancing Backwards ( reverse iteration ) */
                __iirt_rend                         = 0x03U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a removal of an element pointed to at by an iterator */
                __iirt_remove                       = 0x04U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a removal of an element pointed to at by a const iterator */
                __iirt_removeConst                  = 0x05U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a removal of multiple iterators via a pointer array */
                __iirt_removeArray                  = 0x06U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a removal of multiple const iterators via a pointer array */
                __iirt_removeConstArray             = 0x07U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a new element address */
                __iirt_newAddress                   = 0x08U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a new element address at the front of the iterable */
                __iirt_newFrontAddress              = 0x09U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a new element address at the back of the iterable */
                __iirt_newBackAddress               = 0x0AU,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for multiple elements addresses at the front of the iterable */
                __iirt_newFrontAddressArray         = 0x0BU,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for multiple elements addresses at the back of the iterable */
                __iirt_newBackAddressArray          = 0x0CU,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a new element address before a given abstract iterator */
                __iirt_newBeforeAddress             = 0x0DU,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a new element address before a given abstract const iterator */
                __iirt_newBeforeAddressConst        = 0x0EU,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a new element address after a given abstract iterator */
                __iirt_newAfterAddress              = 0x0FU,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for a new element address after a given abstract const iterator */
                __iirt_newAfterAddressConst         = 0x10U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for multiple element addresses before a given abstract iterator */
                __iirt_newBeforeAddressArray        = 0x11U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for multiple element addresses before a given abstract const iterator */
                __iirt_newBeforeAddressArrayConst   = 0x12U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for multiple element addresses after a given abstract iterator */
                __iirt_newAfterAddressArray         = 0x13U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for multiple element addresses after a given abstract const iterator */
                __iirt_newAfterAddressArrayConst    = 0x14U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for finding an iterator to an element by key/value */
                __iirt_find                         = 0x15U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents a Request for finding a const iterator to an element by key/value */
                __iirt_findConst                    = 0x16U,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /** Represents the number of possible requests, not to be used in requests */
                __iirt_requestCountDoNotUse         = 0x17U     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERABLE_INTERNAL_REQUEST_TYPE_HPP__ */
