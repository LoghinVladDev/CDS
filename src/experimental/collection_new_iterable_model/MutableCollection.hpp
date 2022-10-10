/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_MUTABLE_COLLECTION_HPP__
#define __CDS_EX_MUTABLE_COLLECTION_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/MutableCollection>

#include <CDS/experimental/Collection>

#include "shared/collectionInternalCommunication/client/primitive/DelegateForwardIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IteratorRemovePrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/GenericMutableStatementsCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindOfMutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindByMutableCompositeClient.hpp"

#include "mutableCollection/MutableCollectionConstructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        using MutableCollection __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: MutableCollection < __ElementType >;

    }
}

#endif /* __CDS_EX_MUTABLE_COLLECTION_HPP__ */
