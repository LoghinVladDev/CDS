//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_ITERATOR_MODEL_HPP__
#define __CDS_ITERATOR_MODEL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */

        namespace meta {

            /**
             * @struct Model Structure representing a non-standard iterator model
             * @public
             **/
            struct Iterator {};

            /**
             * @struct Model Structure representing a Forward-Iterable Iterator. Can advance begin-to-end
             * @public
             */
            struct ForwardIterator : Iterator {};

            /**
             * @struct Model Structure representing a Bidirectional-Iterable Iterator. Can advance begin-to-end and end-to-begin
             * @public
             */
            struct BidirectionalIterator : ForwardIterator {};

            /**
             * @struct Model Structure representing a Random-Access-Iterable Iterator. Can advance begin-to-end, end-to-begin, and jump positions more than one step at a time.
             * @public
             */
            struct RandomAccessIterator : BidirectionalIterator {};

        }

    }
}

#endif /* __CDS_ITERATOR_MODEL_HPP__ */
