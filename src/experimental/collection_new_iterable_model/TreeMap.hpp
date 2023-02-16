/*
 * Created by stefan on 26.09.2022.
 */

#ifndef __CDS_EX_TREE_MAP_HPP__     /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_EX_TREE_MAP_HPP__     /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/TreeMap>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>
#include <CDS/Function>

#include <CDS/experimental/Map>

#include "../../shared/Node.hpp"
#include "../../shared/impl/generalPredicates.hpp"

#include "shared/collectionInternalCommunication/server/TreeMapServerDispatcher.hpp"

#include "shared/iterator/RedBlackTreeIterator.hpp"

#include "../../shared/collectionInternalCommunication/client/primitive/DelegateBackwardIterablePrimitiveClient.hpp"
#include "../../shared/collectionInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "../../shared/iterator/IteratorGenericDecorator.hpp"
#include "../../shared/delegateIterator/DelegateIterator.hpp"

#include "shared/redBlackTree/RedBlackTree.hpp"

#include "shared/collectionInternalCommunication/server/MapServer.hpp"
#include "shared/collectionInternalCommunication/server/SetServer.hpp"

#include "treeMap/Constructs.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > using TreeMap __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: TreeMap < __KeyType, __ValueType >;

    }
}

#endif /* __CDS_EX_TREE_MAP_HPP__ */
