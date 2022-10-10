/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_ITERATOR_MODEL_HPP__
#define __CDS_EX_ITERATOR_MODEL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/IteratorModel.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */

        namespace meta {

            using Iterator              __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: meta :: Iterator;
            using ForwardIterator       __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: meta :: ForwardIterator;
            using BidirectionalIterator __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: meta :: BidirectionalIterator;
            using RandomAccessIterator  __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: meta :: RandomAccessIterator;

        }

    }
}

#endif /* __CDS_EX_ITERATOR_MODEL_HPP__ */
