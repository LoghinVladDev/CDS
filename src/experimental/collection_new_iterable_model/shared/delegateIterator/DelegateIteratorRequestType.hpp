//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
#define __CDS_SHARED_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                /**
                 * @enum The types of delegate iterator requests the Collection Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
                 * @test tested in nester class test
                 */
                enum class __DelegateIteratorRequestType {      // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a Beginning Iterator, Advancing Forward
                    __dirt_begin,                               // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for an End Iterator, Advancing Forward
                    __dirt_end,                                 // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a Beginning Iterator, Advancing Backwards ( reverse iteration )
                    __dirt_rbegin,                              // NOLINT(bugprone-reserved-identifier)

                    /// Represents a Request for a End Iterator, Advancing Backwards ( reverse iteration )
                    __dirt_rend,                                // NOLINT(bugprone-reserved-identifier)
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
