/*
 * Created by stefan on 16.08.2022.
 */

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/RedBlackTreeIterator.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType >                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
        using AbstractRedBlackTreeIterator      __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: AbstractRedBlackTreeIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        using AbstractRedBlackTreeConstIterator __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: AbstractRedBlackTreeConstIterator < __ElementType >;    /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
        using RedBlackTreeForwardIterator       __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: RedBlackTreeForwardIterator < __ElementType >;  /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        using RedBlackTreeForwardConstIterator  __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: RedBlackTreeForwardConstIterator < __ElementType >;     /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
        using RedBlackTreeBackwardIterator      __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: RedBlackTreeBackwardIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        using RedBlackTreeBackwardConstIterator __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: RedBlackTreeBackwardConstIterator < __ElementType >;    /* NOLINT(bugprone-reserved-identifier) */

    }
}

#endif /* __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__ */
