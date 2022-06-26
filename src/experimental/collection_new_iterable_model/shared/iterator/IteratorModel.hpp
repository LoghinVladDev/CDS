//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_ITERATOR_MODEL_HPP__
#define __CDS_ITERATOR_MODEL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        namespace meta {

            struct Iterator {};
            struct ForwardIterator : Iterator {};
            struct BidirectionalIterator : ForwardIterator {};
            struct RandomAccessIterator : BidirectionalIterator {};

        }

    }
}

#endif // __CDS_ITERATOR_MODEL_HPP__
