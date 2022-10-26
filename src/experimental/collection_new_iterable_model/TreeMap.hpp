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

#include "../../shared/iterator/IteratorGenericDecorator.hpp"
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

        protected: using MapBase                                    = Map < __KeyType, __ValueType >;
        protected: using Server                                     = __hidden :: __impl :: __TreeMapServer < __KeyType, __ValueType >;
        protected: using Implementation                             = __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType >;
        protected: using Dispatcher                                 = __hidden :: __impl :: __TreeMapDispatcher < __KeyType, __ValueType >;
        protected: using DelegateForwardIterableClient              = __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType >;
        protected: using DelegateBackwardIterableClient             = __hidden :: __impl :: __TreeMapDispatcher < __KeyType, __ValueType >;
        protected: using DelegateForwardConstIterableClient         = __hidden :: __impl :: __TreeMapDelegateForwardIterableClient < __KeyType, __ValueType >;
        protected: using DelegateBackwardConstIterableClient        = __hidden :: __impl :: __TreeMapDelegateBackwardIterableClient < __KeyType, __ValueType >;
        protected: using IteratorRemoveClient                       = __hidden :: __impl :: __TreeMapDelegateForwardConstIterableClient < __KeyType, __ValueType >;
        protected: using ConstIteratorRemoveClient                  = __hidden :: __impl :: __TreeMapDelegateBackwardConstIterableClient < __KeyType, __ValueType >;
        protected: using FindUniqueClient                           = __hidden :: __impl :: __TreeMapIteratorRemoveClient < __KeyType, __ValueType >;
        protected: using FindUniqueConstClient                      = __hidden :: __impl :: __TreeMapConstIteratorRemoveClient < __KeyType, __ValueType >;
        protected: using RandomInsertionClient                      = __hidden :: __impl :: __TreeMapFindUniqueClient < __KeyType, __ValueType >;
        protected: using ContainsOfCollectionClient                 = __hidden :: __impl :: __TreeMapFindUniqueConstClient < __KeyType, __ValueType >;
        protected: using ContainsOfInitializerListClient            = __hidden :: __impl :: __TreeMapRandomInsertionClient < __KeyType, __ValueType >;
        protected: using FindByClient                               = __hidden :: __impl :: __TreeMapContainsOfCollectionClient < __KeyType, __ValueType >;
        protected: using FindByConstClient                          = __hidden :: __impl :: __TreeMapContainsOfInitializerListClient < __KeyType, __ValueType >;
        protected: using FindOfCollectionClient                     = __hidden :: __impl :: __TreeMapFindByClient < __KeyType, __ValueType >;
        protected: using FindOfInitializerListClient                = __hidden :: __impl :: __TreeMapFindByConstClient < __KeyType, __ValueType >;
        protected: using FindOfConstCollectionClient                = __hidden :: __impl :: __TreeMapFindOfCollectionClient < __KeyType, __ValueType >;
        protected: using FindOfConstInitializerListClient           = __hidden :: __impl :: __TreeMapFindOfInitializerListClient < __KeyType, __ValueType >;
        protected: using GenericStatementsClient                    = __hidden :: __impl :: __TreeMapFindOfConstCollectionClient < __KeyType, __ValueType >;
        protected: using ConstGenericStatementsClient               = __hidden :: __impl :: __TreeMapFindOfConstInitializerListClient < __KeyType, __ValueType >;
        protected: using RemoveByClient                             = __hidden :: __impl :: __TreeMapGenericStatementsClient < __KeyType, __ValueType >;
        protected: using RemoveOfCollectionClient                   = __hidden :: __impl :: __TreeMapConstGenericStatementsClient < __KeyType, __ValueType >;
        protected: using RemoveOfInitializerListClient              = __hidden :: __impl :: __TreeMapRemoveByClient < __KeyType, __ValueType >;

        private: friend Server;

        private: friend DelegateForwardIterableClient;
        private: friend DelegateBackwardIterableClient;
        private: friend DelegateForwardConstIterableClient;
        private: friend DelegateBackwardConstIterableClient;

        private: using typename MapBase :: __GenericHandler;              /* NOLINT(bugprone-reserved-identifier) */
        private: using typename MapBase :: __GenericConstHandler;         /* NOLINT(bugprone-reserved-identifier) */

        protected: using typename MapBase :: AbstractKeySetProxy;
        protected: using typename MapBase :: AbstractValueMutableCollectionProxy;
        protected: using typename MapBase :: AbstractEntryMutableCollectionProxy;

        private: class ValueMutableCollectionProxy;
        private: class EntryMutableCollectionProxy;
        private: class KeySetProxy;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (        /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        };
                
    }
}
#include "treeMap/KeySetProxy.hpp"
#include "treeMap/ValueMutableCollectionProxy.hpp"
#include "treeMap/EntryMutableCollectionProxy.hpp"


#include "shared/redBlackTree/impl/RedBlackTree.hpp"

#include "shared/collectionInternalCommunication/server/impl/MapServer.hpp"

#include "../../shared/delegateIterator/impl/DelegateIterator.hpp"
#include "../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardIterablePrimitiveClient.hpp"
#include "../../shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "shared/iterator/impl/RedBlackTreeIterator.hpp"

#include "shared/collectionInternalCommunication/server/impl/TreeMapServerDispatcher.hpp"

#include "treeMap/impl/TreeMap.hpp"

#include "treeMap/impl/KeySetProxy.hpp"
#include "treeMap/impl/ValueMutableCollectionProxy.hpp"
#include "treeMap/impl/EntryMutableCollectionProxy.hpp"

#endif //__CDS_EX_TREE_MAP_HPP__
