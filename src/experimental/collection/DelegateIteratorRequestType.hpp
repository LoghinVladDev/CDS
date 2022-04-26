//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
#define __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        enum class Collection < T > :: DelegateIteratorRequestType {
            ForwardBegin,
            ForwardEnd,
            BackwardBegin,
            BackwardEnd,
        };

    }
}

#endif // __CDS_COLLECTION_DELEGATE_ITERATOR_REQUEST_TYPE_HPP__
