/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/List>

#include <CDS/experimental/MutableCollection>

#include "shared/delegateIterator/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/client/primitive/DelegateBackwardIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/ConstIteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/BoundaryInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IndexedOperationsPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/ReplaceCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/ReplaceByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesByCompositeClient.hpp"

#include "list/ListConstructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        using List __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: List < __ElementType >;

    }
}

#endif /* __CDS_EX_LIST_HPP__ */
