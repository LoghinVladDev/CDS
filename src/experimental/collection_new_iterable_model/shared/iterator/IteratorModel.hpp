/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_ITERATOR_MODEL_HPP__
#define __CDS_ITERATOR_MODEL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */

        namespace meta {

            /**
             * @interface Model Structure representing a non-standard iterator model
             * @public
             **/
            struct Iterator {};

            /**
             * @interface Model Structure representing a Forward-Iterable Iterator. Can advance begin-to-end
             * @extends Iterator
             * @public
             */
            struct ForwardIterator : Iterator {};

            /**
             * @interface Model Structure representing a Bidirectional-Iterable Iterator. Can advance begin-to-end and end-to-begin
             * @extends ForwardIterator
             * @public
             */
            struct BidirectionalIterator : ForwardIterator {};

            /**
             * @interface Model Structure representing a Random-Access-Iterable Iterator. Can advance begin-to-end, end-to-begin, and jump positions more than one step at a time.
             * @extends BidirectionalIterator
             * @public
             */
            struct RandomAccessIterator : BidirectionalIterator {};

        }

    }
}

#endif /* __CDS_ITERATOR_MODEL_HPP__ */
