/*
 * Created by loghin on 4/26/22.
 */

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_TYPE_HPP__
#define __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_TYPE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @enum The types of delegate iterator requests the Collection Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 */
                enum class __CollectionInternalRequestType {    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a Beginning Iterator, Advancing Forward */
                    __cirt_begin                        = 0x00U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for an End Iterator, Advancing Forward */
                    __cirt_end                          = 0x01U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a Beginning Iterator, Advancing Backwards ( reverse iteration ) */
                    __cirt_rbegin                       = 0x02U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a End Iterator, Advancing Backwards ( reverse iteration ) */
                    __cirt_rend                         = 0x03U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a removal of an element pointed to at by an iterator */
                    __cirt_remove                       = 0x04U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a removal of an element pointed to at by a const iterator */
                    __cirt_removeConst                  = 0x05U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a removal of multiple iterators via a pointer array */
                    __cirt_removeArray                  = 0x06U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a removal of multiple const iterators via a pointer array */
                    __cirt_removeConstArray             = 0x07U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a new element address */
                    __cirt_newAddress                   = 0x08U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a new element address at the front of the collection */
                    __cirt_newFrontAddress              = 0x09U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a new element address at the back of the collection */
                    __cirt_newBackAddress               = 0x0AU,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for multiple elements addresses at the front of the collection */
                    __cirt_newFrontAddressArray         = 0x0BU,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for multiple elements addresses at the back of the collection */
                    __cirt_newBackAddressArray          = 0x0CU,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a new element address before a given abstract iterator */
                    __cirt_newBeforeAddress             = 0x0DU,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a new element address before a given abstract const iterator */
                    __cirt_newBeforeAddressConst        = 0x0EU,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a new element address after a given abstract iterator */
                    __cirt_newAfterAddress              = 0x0FU,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for a new element address after a given abstract const iterator */
                    __cirt_newAfterAddressConst         = 0x10U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for multiple element addresses before a given abstract iterator */
                    __cirt_newBeforeAddressArray        = 0x11U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for multiple element addresses before a given abstract const iterator */
                    __cirt_newBeforeAddressArrayConst   = 0x12U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for multiple element addresses after a given abstract iterator */
                    __cirt_newAfterAddressArray         = 0x13U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for multiple element addresses after a given abstract const iterator */
                    __cirt_newAfterAddressArrayConst    = 0x14U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for finding an iterator to an element by key/value */
                    __cirt_find                         = 0x15U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents a Request for finding a const iterator to an element by key/value */
                    __cirt_findConst                    = 0x16U,    /* NOLINT(bugprone-reserved-identifier) */

                    /** Represents the number of possible requests, not to be used in requests */
                    __cirt_requestCountDoNotUse         = 0x17U     /* NOLINT(bugprone-reserved-identifier) */
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_TYPE_HPP__ */
