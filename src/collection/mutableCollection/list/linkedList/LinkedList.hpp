/* NOLINT(llvm-header-guard)
 * Created by loghin on 15.01.2021.
 */

#ifndef __CDS_LINKED_LIST_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/List>

#include "linkedList/Predeclaration.hpp"

#include "../../../../shared/Node.hpp"

#include "../../../../shared/iterator/NodeIterator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/ListServerDispatcher.hpp"   /* NOLINT(llvm-include-order) */
#include "../../../../shared/iterableInternalCommunication/server/ListServer.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/linkedList/DoubleLinkedList.hpp"

#include "linkedList/Constructs.hpp"


namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class __CDS_InheritsEBOs LinkedList :
            public List < __ElementType >,
            protected __hidden :: __impl :: __LinkedListServer < __ElementType >,
            public __hidden :: __impl :: __LinkedListImplementation < __ElementType >,
            public __hidden :: __impl :: __LinkedListDispatcher < __ElementType >,
            public __hidden :: __impl :: __LinkedListRandomInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListBoundaryInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIteratorRelativeInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListConstIteratorRelativeInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindOfIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindConstOfIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindConstOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindConstByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIteratorRemoveClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListConstIteratorRemoveClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListRemoveOfIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListRemoveOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListRemoveByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListGenericStatementsClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListGenericConstStatementsClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceOfIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListContainsOfIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListContainsOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndexedOperationsClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesOfIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateForwardIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateForwardConstIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateBackwardIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateBackwardConstIterableClient < __ElementType > {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        template < typename, typename >
        friend class __hidden :: __impl :: __ListServer; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Implementation                        = __hidden :: __impl :: __LinkedListImplementation < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __LinkedListServer < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __LinkedListRandomInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient               = __hidden :: __impl :: __LinkedListBoundaryInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient       = __hidden :: __impl :: __LinkedListIteratorRelativeInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __LinkedListConstIteratorRelativeInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient                  = __hidden :: __impl :: __LinkedListFindOfIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedListFindOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient             = __hidden :: __impl :: __LinkedListFindConstOfIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient      = __hidden :: __impl :: __LinkedListFindConstOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __LinkedListFindByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient                     = __hidden :: __impl :: __LinkedListFindConstByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedListIteratorRemoveClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient             = __hidden :: __impl :: __LinkedListConstIteratorRemoveClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient                = __hidden :: __impl :: __LinkedListRemoveOfIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedListRemoveOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __LinkedListRemoveByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __LinkedListGenericStatementsClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient          = __hidden :: __impl :: __LinkedListGenericConstStatementsClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient                         = __hidden :: __impl :: __LinkedListReplaceClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient               = __hidden :: __impl :: __LinkedListReplaceOfIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient        = __hidden :: __impl :: __LinkedListReplaceOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient                       = __hidden :: __impl :: __LinkedListReplaceByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient              = __hidden :: __impl :: __LinkedListContainsOfIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedListContainsOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndexedOperationsClient               = __hidden :: __impl :: __LinkedListIndexedOperationsClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient                         = __hidden :: __impl :: __LinkedListIndicesClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient               = __hidden :: __impl :: __LinkedListIndicesOfIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient        = __hidden :: __impl :: __LinkedListIndicesOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient                       = __hidden :: __impl :: __LinkedListIndicesByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __LinkedListDelegateForwardIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedListDelegateForwardConstIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardIterableClient        = __hidden :: __impl :: __LinkedListDelegateBackwardIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __LinkedListDelegateBackwardConstIterableClient < __ElementType >;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend BoundaryInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend RandomInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend IteratorRemoveClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend ConstIteratorRemoveClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend IteratorRelativeInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend ConstIteratorRelativeInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend IndexedOperationsClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardConstIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateBackwardIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateBackwardConstIterableClient;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ElementType                   = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ListBase                  = List < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename ListBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename ListBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardIterableClient :: Iterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardConstIterableClient :: ConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateBackwardIterableClient :: ReverseIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: begin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: end;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: begin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: end;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cend;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardIterableClient :: rbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardIterableClient :: rend;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: rbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: rend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: crbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: crend;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insert;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: add;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: emplace;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushBack;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushBackAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushBackAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushFront;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushFrontAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushFrontAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: append;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: prepend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: emplaceBack;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: emplaceFront;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllOfBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: emplaceBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllOfAfter
        ;
    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: emplaceAfter;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: emplaceBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: emplaceAfter;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findAllThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findAllThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeAllThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: forEach;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: some;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atLeast;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atMost;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: moreThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: fewerThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: count;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: any;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: all;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: none;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: forEach;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: some;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: atLeast;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: atMost;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: moreThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: fewerThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: count;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: any;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: all;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: none;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAnyOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAnyNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsNoneOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsNoneOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replace;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replaceFirst;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replaceLast;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replaceAll;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceAllThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceThatBy;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceFirstThatBy;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceLastThatBy;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceAllThatBy;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndexedOperationsClient :: sub;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: indicesOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: firstIndexOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: lastIndexOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: allIndicesOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: indicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: firstIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: lastIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: allIndicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: indicesOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: firstIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: lastIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: allIndicesOfNotFrom;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: indicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: firstIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: lastIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: allIndicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: indicesOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: firstIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: lastIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: allIndicesOfNotFrom;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: indicesOfThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: firstIndexOfThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: lastIndexOfThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: allIndicesOfThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient :: remove;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient :: remove;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using List < __ElementType > :: remove;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr LinkedList () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        LinkedList ( /* NOLINT(google-explicit-constructor) */
                LinkedList const & list
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr LinkedList (
                LinkedList && list
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedList (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count = 0ULL
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedList (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Explicit LinkedList (
                __IterableType const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~LinkedList () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                LinkedList const & list
        ) noexcept -> LinkedList &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                LinkedList && list
        ) noexcept -> LinkedList &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> LinkedList &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> LinkedList &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                LinkedList const & list
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                LinkedList const & list
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto popFront () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto popBack () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                Index index
        ) noexcept (false) -> ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                Index index
        ) const noexcept (false) -> ElementType const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto removeAt (
                Index index
        ) noexcept -> bool override;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto sort (
                cds :: Function < auto ( __ElementType const &, __ElementType const & ) -> bool > const & comparator
        ) noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __Comparator = decltype ( & cds :: predicates :: lessThan < __ElementType > )  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > auto sort (
                __Comparator const & comparator = & cds :: predicates :: lessThan < __ElementType >
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < LinkedList < __ElementType > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < LinkedList < __ElementType > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < LinkedList < __ElementType > const >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < LinkedList < __ElementType > const >;
    };

} /* namespace cds */


#include "../../../../shared/iterator/impl/NodeIterator.hpp"

#include "../../../../shared/linkedList/impl/DoubleLinkedListImpl.hpp"

#include "../../../../shared/iterableInternalCommunication/server/impl/ListServer.hpp"
#include "../../../../shared/iterableInternalCommunication/server/impl/ListServerDispatcher.hpp"

#include "../../../../shared/linkedList/impl/Sequence.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "linkedList/impl/LinkedList.hpp" /* NOLINT(llvm-include-order) */
#include "linkedList/impl/CTAD.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif /* __CDS_LINKED_LIST_HPP__ */
