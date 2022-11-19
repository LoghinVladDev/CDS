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
        protected: using DelegateForwardIterableClient              = __hidden :: __impl :: __TreeMapDelegateForwardIterableClient < __KeyType, __ValueType >;
        protected: using DelegateBackwardIterableClient             = __hidden :: __impl :: __TreeMapDelegateBackwardIterableClient < __KeyType, __ValueType >;
        protected: using DelegateForwardConstIterableClient         = __hidden :: __impl :: __TreeMapDelegateForwardConstIterableClient < __KeyType, __ValueType >;
        protected: using DelegateBackwardConstIterableClient        = __hidden :: __impl :: __TreeMapDelegateBackwardConstIterableClient < __KeyType, __ValueType >;
        protected: using IteratorRemoveClient                       = __hidden :: __impl :: __TreeMapIteratorRemoveClient < __KeyType, __ValueType >;
        protected: using ConstIteratorRemoveClient                  = __hidden :: __impl :: __TreeMapConstIteratorRemoveClient < __KeyType, __ValueType >;
        protected: using FindUniqueClient                           = __hidden :: __impl :: __TreeMapFindUniqueClient < __KeyType, __ValueType >;
        protected: using FindUniqueConstClient                      = __hidden :: __impl :: __TreeMapFindUniqueConstClient < __KeyType, __ValueType >;
        protected: using RandomInsertionClient                      = __hidden :: __impl :: __TreeMapRandomInsertionClient < __KeyType, __ValueType >;
        protected: using ContainsOfCollectionClient                 = __hidden :: __impl :: __TreeMapContainsOfCollectionClient < __KeyType, __ValueType >;
        protected: using ContainsOfInitializerListClient            = __hidden :: __impl :: __TreeMapContainsOfInitializerListClient < __KeyType, __ValueType >;
        protected: using FindByClient                               = __hidden :: __impl :: __TreeMapFindByClient < __KeyType, __ValueType >;
        protected: using FindByConstClient                          = __hidden :: __impl :: __TreeMapFindByConstClient < __KeyType, __ValueType >;
        protected: using FindOfCollectionClient                     = __hidden :: __impl :: __TreeMapFindOfCollectionClient < __KeyType, __ValueType >;
        protected: using FindOfInitializerListClient                = __hidden :: __impl :: __TreeMapFindOfInitializerListClient < __KeyType, __ValueType >;
        protected: using FindOfConstCollectionClient                = __hidden :: __impl :: __TreeMapFindOfConstCollectionClient < __KeyType, __ValueType >;
        protected: using FindOfConstInitializerListClient           = __hidden :: __impl :: __TreeMapFindOfConstInitializerListClient < __KeyType, __ValueType >;
        protected: using GenericStatementsClient                    = __hidden :: __impl :: __TreeMapGenericStatementsClient < __KeyType, __ValueType >;
        protected: using ConstGenericStatementsClient               = __hidden :: __impl :: __TreeMapConstGenericStatementsClient < __KeyType, __ValueType >;
        protected: using RemoveByClient                             = __hidden :: __impl :: __TreeMapRemoveByClient < __KeyType, __ValueType >;
        protected: using RemoveOfCollectionClient                   = __hidden :: __impl :: __TreeMapRemoveOfCollectionClient < __KeyType, __ValueType >;
        protected: using RemoveOfInitializerListClient              = __hidden :: __impl :: __TreeMapRemoveOfInitializerListClient < __KeyType, __ValueType >;

        private: friend Server;

        private: friend DelegateForwardIterableClient;
        private: friend DelegateBackwardIterableClient;
        private: friend DelegateForwardConstIterableClient;
        private: friend DelegateBackwardConstIterableClient;

        public: using __ElementType =  typename MapBase :: ElementType;   /* NOLINT(bugprone-reserved-identifier) */

        private: using typename MapBase :: __GenericHandler;              /* NOLINT(bugprone-reserved-identifier) */
        private: using typename MapBase :: __GenericConstHandler;         /* NOLINT(bugprone-reserved-identifier) */

        protected: using typename MapBase :: AbstractKeySetProxy;
        protected: using typename MapBase :: AbstractValueMutableCollectionProxy;
        protected: using typename MapBase :: AbstractEntryMutableCollectionProxy;

        public: class ValueMutableCollectionProxy;
        private: class EntryMutableCollectionProxy;
        private: class KeySetProxy;

        private:
            ValueMutableCollectionProxy _valueMutableCollectionProxy;



        public:     using DelegateForwardIterableClient :: begin;
        public:     using DelegateForwardIterableClient :: end;

        public:     using DelegateBackwardIterableClient :: rbegin;
        public:     using DelegateBackwardIterableClient :: rend;

        public:     using DelegateForwardConstIterableClient :: begin;
        public:     using DelegateForwardConstIterableClient :: end;
        public:     using DelegateForwardConstIterableClient :: cbegin;
        public:     using DelegateForwardConstIterableClient :: cend;

        public:     using DelegateBackwardConstIterableClient :: rbegin;
        public:     using DelegateBackwardConstIterableClient :: rend;
        public:     using DelegateBackwardConstIterableClient :: crbegin;
        public:     using DelegateBackwardConstIterableClient :: crend;

        public:     using IteratorRemoveClient :: remove;
        public:     using IteratorRemoveClient :: removeAll;

        public:     using ConstIteratorRemoveClient :: remove;
        public:     using ConstIteratorRemoveClient :: removeAll;

        public:     using RandomInsertionClient :: insert;
        public:     using RandomInsertionClient :: add;
        public:     using RandomInsertionClient :: emplace;
        public:     using RandomInsertionClient :: insertAll;
        public:     using RandomInsertionClient :: insertAllOf;
        public:     using RandomInsertionClient :: addAllOf;

        public:     using FindUniqueClient :: find;

        public:     using FindUniqueConstClient :: find;

        public:     using ContainsOfCollectionClient :: containsAnyOf;
        public:     using ContainsOfCollectionClient :: containsAnyNotOf;
        public:     using ContainsOfCollectionClient :: containsAllOf;
        public:     using ContainsOfCollectionClient :: containsNoneOf;

        public:     using ContainsOfInitializerListClient :: containsAnyOf;
        public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
        public:     using ContainsOfInitializerListClient :: containsAllOf;
        public:     using ContainsOfInitializerListClient :: containsNoneOf;

        public:     using FindOfCollectionClient :: findOf;
        public:     using FindOfCollectionClient :: findFirstOf;
        public:     using FindOfCollectionClient :: findLastOf;
        public:     using FindOfCollectionClient :: findAllOf;
        public:     using FindOfCollectionClient :: findNotOf;
        public:     using FindOfCollectionClient :: findFirstNotOf;
        public:     using FindOfCollectionClient :: findLastNotOf;
        public:     using FindOfCollectionClient :: findAllNotOf;

        public:     using FindOfInitializerListClient :: findOf;
        public:     using FindOfInitializerListClient :: findFirstOf;
        public:     using FindOfInitializerListClient :: findLastOf;
        public:     using FindOfInitializerListClient :: findAllOf;
        public:     using FindOfInitializerListClient :: findNotOf;
        public:     using FindOfInitializerListClient :: findFirstNotOf;
        public:     using FindOfInitializerListClient :: findLastNotOf;
        public:     using FindOfInitializerListClient :: findAllNotOf;

        public:     using FindOfConstCollectionClient :: findOf;
        public:     using FindOfConstCollectionClient :: findFirstOf;
        public:     using FindOfConstCollectionClient :: findLastOf;
        public:     using FindOfConstCollectionClient :: findAllOf;
        public:     using FindOfConstCollectionClient :: findNotOf;
        public:     using FindOfConstCollectionClient :: findFirstNotOf;
        public:     using FindOfConstCollectionClient :: findLastNotOf;
        public:     using FindOfConstCollectionClient :: findAllNotOf;

        public:     using FindOfConstInitializerListClient :: findOf;
        public:     using FindOfConstInitializerListClient :: findFirstOf;
        public:     using FindOfConstInitializerListClient :: findLastOf;
        public:     using FindOfConstInitializerListClient :: findAllOf;
        public:     using FindOfConstInitializerListClient :: findNotOf;
        public:     using FindOfConstInitializerListClient :: findFirstNotOf;
        public:     using FindOfConstInitializerListClient :: findLastNotOf;
        public:     using FindOfConstInitializerListClient :: findAllNotOf;

        public:     using FindByClient :: findThat;
        public:     using FindByClient :: findFirstThat;
        public:     using FindByClient :: findLastThat;
        public:     using FindByClient :: findAllThat;

        public:     using FindByConstClient :: findThat;
        public:     using FindByConstClient :: findFirstThat;
        public:     using FindByConstClient :: findLastThat;
        public:     using FindByConstClient :: findAllThat;

        public:     using RemoveOfCollectionClient :: removeOf;
        public:     using RemoveOfCollectionClient :: removeFirstOf;
        public:     using RemoveOfCollectionClient :: removeLastOf;
        public:     using RemoveOfCollectionClient :: removeAllOf;
        public:     using RemoveOfCollectionClient :: removeNotOf;
        public:     using RemoveOfCollectionClient :: removeFirstNotOf;
        public:     using RemoveOfCollectionClient :: removeLastNotOf;
        public:     using RemoveOfCollectionClient :: removeAllNotOf;

        public:     using RemoveOfInitializerListClient :: removeOf;
        public:     using RemoveOfInitializerListClient :: removeFirstOf;
        public:     using RemoveOfInitializerListClient :: removeLastOf;
        public:     using RemoveOfInitializerListClient :: removeAllOf;
        public:     using RemoveOfInitializerListClient :: removeNotOf;
        public:     using RemoveOfInitializerListClient :: removeFirstNotOf;
        public:     using RemoveOfInitializerListClient :: removeLastNotOf;
        public:     using RemoveOfInitializerListClient :: removeAllNotOf;

        public:     using RemoveByClient :: removeThat;
        public:     using RemoveByClient :: removeFirstThat;
        public:     using RemoveByClient :: removeLastThat;
        public:     using RemoveByClient :: removeAllThat;

        public:     using GenericStatementsClient :: forEach;
        public:     using GenericStatementsClient :: some;
        public:     using GenericStatementsClient :: atLeast;
        public:     using GenericStatementsClient :: atMost;
        public:     using GenericStatementsClient :: moreThan;
        public:     using GenericStatementsClient :: fewerThan;
        public:     using GenericStatementsClient :: count;
        public:     using GenericStatementsClient :: any;
        public:     using GenericStatementsClient :: all;
        public:     using GenericStatementsClient :: none;

        public:     using ConstGenericStatementsClient :: forEach;
        public:     using ConstGenericStatementsClient :: some;
        public:     using ConstGenericStatementsClient :: atLeast;
        public:     using ConstGenericStatementsClient :: atMost;
        public:     using ConstGenericStatementsClient :: moreThan;
        public:     using ConstGenericStatementsClient :: fewerThan;
        public:     using ConstGenericStatementsClient :: count;
        public:     using ConstGenericStatementsClient :: any;
        public:     using ConstGenericStatementsClient :: all;
        public:     using ConstGenericStatementsClient :: none;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (        /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () const noexcept -> ValueMutableCollectionProxy const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () noexcept -> ValueMutableCollectionProxy & override;

        public:
            constexpr TreeMap() noexcept;

        public:
            TreeMap (
                    TreeMap const & map
            ) noexcept;

        public:
            constexpr TreeMap (
                    TreeMap && map
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > TreeMap (
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count = 0ULL
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    >
            > TreeMap (
                    std :: initializer_list < __TElementType > const & initializer_list
            ) noexcept;

        public:
            template < typename __IterableType >        /* NOLINT(bugprone-reserved-identifier) */
            __CDS_Explicit TreeMap ( __IterableType const & iterable ) noexcept;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size;

        public:
            auto clear () noexcept -> void;
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