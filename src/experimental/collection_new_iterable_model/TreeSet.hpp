/*
 * Created by stefan on 28.08.2022.
 */

#ifndef __CDS_EX_TREE_SET_HPP__
#define __CDS_EX_TREE_SET_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/Set>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>
#include <CDS/Function>

#include "../../shared/Node.hpp"
#include "../../shared/impl/generalPredicates.hpp"

#include "shared/iterator/RedBlackTreeIterator.hpp"

#include "shared/collectionInternalCommunication/server/TreeSetServerDispatcher.hpp"

#include "shared/redBlackTree/RedBlackTree.hpp"

#include "../../shared/iterableInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../shared/iterableInternalCommunication/server/SetServer.hpp"

#include "treeSet/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        class TreeSet :
                public Set < __ElementType >,
                protected __hidden :: __impl :: __TreeSetServer < __ElementType >,
                public __hidden :: __impl :: __TreeSetImplementation < __ElementType >,
                public __hidden :: __impl :: __TreeSetDispatcher < __ElementType >,
                public __hidden :: __impl :: __TreeSetDelegateForwardConstIterableClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetDelegateBackwardConstIterableClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetConstIteratorRemoveClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetRandomInsertionClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetFindUniqueClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetContainsOfIterableClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetContainsOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetFindOfIterableClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetFindOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetFindByClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetRemoveOfIterableClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetRemoveOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetRemoveByClient < __ElementType >,
                public __hidden :: __impl :: __TreeSetGenericStatementsClient < __ElementType > {

        protected:  using SetBase                               = Set < __ElementType >;
        protected:  using Server                                = __hidden :: __impl :: __TreeSetServer < __ElementType >;
        protected:  using Implementation                        = __hidden :: __impl :: __TreeSetImplementation < __ElementType >;
        protected:  using Dispatcher                            = __hidden :: __impl :: __TreeSetDispatcher < __ElementType >;
        protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __TreeSetDelegateForwardConstIterableClient < __ElementType >;
        protected:  using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __TreeSetDelegateBackwardConstIterableClient < __ElementType >;
        protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __TreeSetConstIteratorRemoveClient < __ElementType >;
        protected:  using RandomInsertionClient                 = __hidden :: __impl :: __TreeSetRandomInsertionClient < __ElementType >;
        protected:  using FindUniqueClient                      = __hidden :: __impl :: __TreeSetFindUniqueClient < __ElementType >;
        protected:  using ContainsOfIterableClient              = __hidden :: __impl :: __TreeSetContainsOfIterableClient < __ElementType >;
        protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __TreeSetContainsOfInitializerListClient < __ElementType >;
        protected:  using FindOfIterableClient                  = __hidden :: __impl :: __TreeSetFindOfIterableClient < __ElementType >;
        protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __TreeSetFindOfInitializerListClient < __ElementType >;
        protected:  using FindByClient                          = __hidden :: __impl :: __TreeSetFindByClient< __ElementType >;
        protected:  using RemoveOfIterableClient                = __hidden :: __impl :: __TreeSetRemoveOfIterableClient< __ElementType >;
        protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __TreeSetRemoveOfInitializerListClient< __ElementType >;
        protected:  using RemoveByClient                        = __hidden :: __impl :: __TreeSetRemoveByClient< __ElementType >;
        protected:  using GenericStatementsClient               = __hidden :: __impl :: __TreeSetGenericStatementsClient< __ElementType >;

        protected:  friend Server;

        private:    friend RandomInsertionClient;
        private:    friend ConstIteratorRemoveClient;
        private:    friend DelegateForwardConstIterableClient;
        private:    friend DelegateBackwardConstIterableClient;

        protected:  using typename SetBase :: __GenericHandler;              /* NOLINT(bugprone-reserved-identifier) */
        protected:  using typename SetBase :: __GenericConstHandler;         /* NOLINT(bugprone-reserved-identifier) */


        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (        /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;



        public:     using DelegateForwardConstIterableClient :: begin;
        public:     using DelegateForwardConstIterableClient :: end;
        public:     using DelegateForwardConstIterableClient :: cbegin;
        public:     using DelegateForwardConstIterableClient :: cend;

        public:     using DelegateBackwardConstIterableClient :: rbegin;
        public:     using DelegateBackwardConstIterableClient :: rend;
        public:     using DelegateBackwardConstIterableClient :: crbegin;
        public:     using DelegateBackwardConstIterableClient :: crend;

        public:     using ConstIteratorRemoveClient :: remove;
        public:     using ConstIteratorRemoveClient :: removeAll;

        public:     using RandomInsertionClient :: insert;
        public:     using RandomInsertionClient :: add;
        public:     using RandomInsertionClient :: emplace;
        public:     using RandomInsertionClient :: insertAll;
        public:     using RandomInsertionClient :: insertAllOf;
        public:     using RandomInsertionClient :: addAllOf;

        public:     using FindUniqueClient :: find;

        public:     using ContainsOfIterableClient :: containsAnyOf;
        public:     using ContainsOfIterableClient :: containsAnyNotOf;
        public:     using ContainsOfIterableClient :: containsAllOf;
        public:     using ContainsOfIterableClient :: containsNoneOf;

        public:     using ContainsOfInitializerListClient :: containsAnyOf;
        public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
        public:     using ContainsOfInitializerListClient :: containsAllOf;
        public:     using ContainsOfInitializerListClient :: containsNoneOf;

        public:     using FindOfIterableClient :: findOf;
        public:     using FindOfIterableClient :: findFirstOf;
        public:     using FindOfIterableClient :: findLastOf;
        public:     using FindOfIterableClient :: findAllOf;
        public:     using FindOfIterableClient :: findNotOf;
        public:     using FindOfIterableClient :: findFirstNotOf;
        public:     using FindOfIterableClient :: findLastNotOf;
        public:     using FindOfIterableClient :: findAllNotOf;

        public:     using FindOfInitializerListClient :: findOf;
        public:     using FindOfInitializerListClient :: findFirstOf;
        public:     using FindOfInitializerListClient :: findLastOf;
        public:     using FindOfInitializerListClient :: findAllOf;
        public:     using FindOfInitializerListClient :: findNotOf;
        public:     using FindOfInitializerListClient :: findFirstNotOf;
        public:     using FindOfInitializerListClient :: findLastNotOf;
        public:     using FindOfInitializerListClient :: findAllNotOf;

        public:     using FindByClient :: findThat;
        public:     using FindByClient :: findFirstThat;
        public:     using FindByClient :: findLastThat;
        public:     using FindByClient :: findAllThat;

        public:     using RemoveOfIterableClient :: removeOf;
        public:     using RemoveOfIterableClient :: removeFirstOf;
        public:     using RemoveOfIterableClient :: removeLastOf;
        public:     using RemoveOfIterableClient :: removeAllOf;
        public:     using RemoveOfIterableClient :: removeNotOf;
        public:     using RemoveOfIterableClient :: removeFirstNotOf;
        public:     using RemoveOfIterableClient :: removeLastNotOf;
        public:     using RemoveOfIterableClient :: removeAllNotOf;

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

        public:
            constexpr TreeSet () noexcept;

        public:
            TreeSet (
                    TreeSet const & set
            ) noexcept;

        public:
            constexpr TreeSet (
                    TreeSet && set
            ) noexcept;

        public:
            template <
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > TreeSet (
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count = 0ULL
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <                    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
            > TreeSet (
                    std :: initializer_list < __ElementType > const & initializerList
            ) noexcept;

        public:
            template < typename __IterableType >                /* NOLINT(bugprone-reserved-identifier) */
            __CDS_Explicit TreeSet (                                           /* NOLINT(bugprone-reserved-identifier) */
                    __IterableType const & iterable
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~TreeSet () noexcept override;

        public:
            auto operator = (
                    TreeSet const & set
            ) noexcept -> TreeSet &;


        public:
            auto operator = (
                    TreeSet && set
            ) noexcept -> TreeSet &;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
                    __ElementType const & element
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

        public:
           auto clear () noexcept -> void override;

        public:
          auto remove (
                    __ElementType const & element
            ) noexcept -> bool override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                    TreeSet const & set
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                    TreeSet const & set
            ) const noexcept -> bool;
        };
    }
}

#include "shared/redBlackTree/impl/RedBlackTree.hpp"

#include "../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "shared/iterator/impl/RedBlackTreeIterator.hpp"

#include "../../shared/iterableInternalCommunication/server/impl/SetServer.hpp"
#include "shared/collectionInternalCommunication/server/impl/TreeSetServerDispatcher.hpp"

#include "treeSet/impl/TreeSet.hpp"

#include "../../shared/iterableInternalCommunication/client/primitive/impl/DelegateBackwardConstIterablePrimitiveClient.hpp"

#endif /* __CDS_EX_TREE_SET_HPP__ */
