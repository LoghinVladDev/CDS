/*
 * Created by loghin on 17/07/22.
 */

#ifndef __CDS_EX_SHARED_NODE_ITERATOR_HPP__
#define __CDS_EX_SHARED_NODE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "IteratorModel.hpp"
#include "../../../../shared/iterator/NodeIterator.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType >                                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        using UnidirectionalNodeIterator                __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: UnidirectionalNodeIterator < __ElementType >;   /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
        using UnidirectionalNodeConstIterator           __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: UnidirectionalNodeConstIterator < __ElementType >;  /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
        using AbstractBidirectionalNodeIterator         __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: AbstractBidirectionalNodeIterator < __ElementType >;    /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        using AbstractBidirectionalNodeConstIterator    __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: AbstractBidirectionalNodeConstIterator < __ElementType >;   /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
        using ForwardBidirectionalNodeIterator          __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: ForwardBidirectionalNodeIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        using ForwardBidirectionalNodeConstIterator     __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: ForwardBidirectionalNodeConstIterator < __ElementType >;    /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
        using BackwardBidirectionalNodeIterator         __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: BackwardBidirectionalNodeIterator < __ElementType >;    /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        using BackwardBidirectionalNodeConstIterator    __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: BackwardBidirectionalNodeConstIterator < __ElementType >;   /* NOLINT(bugprone-reserved-identifier) */

    }
}

#endif /* __CDS_EX_SHARED_NODE_ITERATOR_HPP__ */
