//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_TYPE_HPP__
#define __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_TYPE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                /**
                 * @enum The types of delegate iterator requests the Collection Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
                 * @test tested in nester class test
                 */
                enum class __CollectionInternalRequestType {    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a Beginning Iterator, Advancing Forward
                    __cirt_begin            = 0x00U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for an End Iterator, Advancing Forward
                    __cirt_end              = 0x01U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a Beginning Iterator, Advancing Backwards ( reverse iteration )
                    __cirt_rbegin           = 0x02U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a End Iterator, Advancing Backwards ( reverse iteration )
                    __cirt_rend             = 0x03U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a removal of an element pointed to at by an iterator
                    __cirt_remove           = 0x04U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a removal of an element pointed to at by a const iterator
                    __cirt_removeConst      = 0x05U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a new element address
                    __cirt_newAddress       = 0x06U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a new element address at the front of the collection
                    __cirt_newFrontAddress  = 0x07U,    // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a new element address at the back of the collection
                    __cirt_newBackAddress   = 0x08U,    // NOLINT(bugprone-reserved-identifier)
                };

            }
        }
    }
}

#endif // __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_TYPE_HPP__
