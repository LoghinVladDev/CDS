//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
#define __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        /**
         * @enum The types of delegate iterator requests the Collection Base Object can make to its Derivated Objects when acquiring an Iterator Delegate Implementation
         * @tparam T type of elements contained into the Collection class that nests the DelegateIteratorRequestType
         * @test tested in nester class test
         */
        template < typename T >
        enum class Collection < T > :: DelegateIteratorRequestType {

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

#endif // __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
