//
// Created by stefan on 26.09.2022.
//

#ifndef __CDS_EX_TREE_MAP_HPP__     /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_EX_TREE_MAP_HPP__     /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/experimental/Map>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>
#include <CDS/Function>

#include "../../shared/Node.hpp"
#include "../../shared/impl/generalPredicates.hpp"

#include "shared/collectionInternalCommunication/server/TreeMapServerDispatcher.hpp"

#include "shared/iterator/RedBlackTreeIterator.hpp"

#include "../../shared/collectionInternalCommunication/client/primitive/DelegateBackwardIterablePrimitiveClient.hpp"
#include "../../shared/collectionInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "../../shared/delegateIterator/DelegateIterator.hpp"

#include "shared/redBlackTree/RedBlackTree.hpp"

#include "shared/collectionInternalCommunication/server/MapServer.hpp"

#include "treeMap/Constructs.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > class TreeMap :
                public cds :: Map < __KeyType, __ValueType >,
                protected  __hidden :: __impl :: __TreeMapServer < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapDispatcher < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapDelegateForwardIterableClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapDelegateBackwardIterableClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapDelegateForwardConstIterableClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapDelegateBackwardConstIterableClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapIteratorRemoveClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapConstIteratorRemoveClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindUniqueClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindUniqueConstClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapRandomInsertionClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapContainsOfCollectionClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapContainsOfInitializerListClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindByClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindByConstClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindOfCollectionClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindOfInitializerListClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindOfConstCollectionClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapFindOfConstInitializerListClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapGenericStatementsClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapConstGenericStatementsClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapRemoveByClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapRemoveOfCollectionClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapRemoveOfInitializerListClient < __KeyType, __ValueType > {

        };
                
    }
}

#include "shared/redBlackTree/impl/RedBlackTree.hpp"

#include "shared/collectionInternalCommunication/server/impl/MapServer.hpp"

#include "../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardIterablePrimitiveClient.hpp"
#include "../../shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "shared/iterator/impl/RedBlackTreeIterator.hpp"

#include "shared/collectionInternalCommunication/server/impl/TreeMapServerDispatcher.hpp"

#endif //__CDS_EX_TREE_MAP_HPP__
