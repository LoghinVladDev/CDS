/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/Collection>

#include "collection/CollectionConstructs.hpp"
#include "collection/CollectionFunctions.hpp"

#include "shared/delegateIterator/ForwardDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/CollectionInternalRequestType.hpp"

#include "shared/collectionInternalCommunication/channel/CollectionInternalCommunicationChannel.hpp"

#include "shared/collectionInternalCommunication/client/primitive/DelegateForwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/ConstIteratorRemovePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/RandomInsertionPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/ContainsOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindOfImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindByImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/RemoveOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/RemoveByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/GenericImmutableStatementsCompositeClient.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        using Collection __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: Collection < __ElementType >;

    }
}

#endif /* __CDS_EX_COLLECTION_HPP__ */
