//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
#define __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)

        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                /**
                 * @enum The types of delegate iterator requests the Collection Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
                 * @test tested in nester class test
                 */
                enum class DelegateIteratorRequestType {

                    /// Represents a Request for a Beginning Iterator, Advancing Forward
                    ForwardBegin,

                    /// Represents a Request for an End Iterator, Advancing Forward
                    ForwardEnd,

                    /// Represents a Request for a Beginning Iterator, Advancing Backwards ( reverse iteration )
                    BackwardBegin,

                    /// Represents a Request for a End Iterator, Advancing Backwards ( reverse iteration )
                    BackwardEnd,
                };

            }
        }

    }
}

#endif // __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
