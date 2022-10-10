/*
 * Created by loghin on 15.01.2021.
 */

#ifndef __CDS_LINKED_LIST_HPP__
#define __CDS_LINKED_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/List>

#include "linkedList/Predeclaration.hpp"

#include "../../../../shared/Node.hpp"

#include "../../../../shared/iterator/NodeIterator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/ListServerDispatcher.hpp"
#include "../../../../shared/collectionInternalCommunication/server/ListServer.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/linkedList/DoubleLinkedList.hpp"

#include "linkedList/Constructs.hpp"


namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    class LinkedList :
            public List < __ElementType >,
            protected __hidden :: __impl :: __LinkedListServer < __ElementType >,
            public __hidden :: __impl :: __LinkedListImplementation < __ElementType >,
            public __hidden :: __impl :: __LinkedListDispatcher < __ElementType >,
            public __hidden :: __impl :: __LinkedListRandomInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListBoundaryInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIteratorRelativeInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListConstIteratorRelativeInsertionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindOfCollectionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindConstOfCollectionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindConstOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListFindConstByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIteratorRemoveClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListConstIteratorRemoveClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListRemoveOfCollectionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListRemoveOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListRemoveByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListGenericStatementsClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListGenericConstStatementsClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceOfCollectionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListReplaceByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListContainsOfCollectionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListContainsOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndexedOperationsClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesOfCollectionClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListIndicesByClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateForwardIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateForwardConstIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateBackwardIterableClient < __ElementType >,
            public __hidden :: __impl :: __LinkedListDelegateBackwardConstIterableClient < __ElementType > {

    private:
        template < typename, typename >
        friend class __hidden :: __impl :: __ListServer; /* NOLINT(bugprone-reserved-identifier) */

    protected:  using Implementation                        = __hidden :: __impl :: __LinkedListImplementation < __ElementType >;
    protected:  using Server                                = __hidden :: __impl :: __LinkedListServer < __ElementType >;
    protected:  using RandomInsertionClient                 = __hidden :: __impl :: __LinkedListRandomInsertionClient < __ElementType >;
    protected:  using BoundaryInsertionClient               = __hidden :: __impl :: __LinkedListBoundaryInsertionClient < __ElementType >;
    protected:  using IteratorRelativeInsertionClient       = __hidden :: __impl :: __LinkedListIteratorRelativeInsertionClient < __ElementType >;
    protected:  using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __LinkedListConstIteratorRelativeInsertionClient < __ElementType >;
    protected:  using FindOfCollectionClient                = __hidden :: __impl :: __LinkedListFindOfCollectionClient < __ElementType >;
    protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedListFindOfInitializerListClient < __ElementType >;
    protected:  using FindConstOfCollectionClient           = __hidden :: __impl :: __LinkedListFindConstOfCollectionClient < __ElementType >;
    protected:  using FindConstOfInitializerListClient      = __hidden :: __impl :: __LinkedListFindConstOfInitializerListClient < __ElementType >;
    protected:  using FindByClient                          = __hidden :: __impl :: __LinkedListFindByClient < __ElementType >;
    protected:  using FindConstByClient                     = __hidden :: __impl :: __LinkedListFindConstByClient < __ElementType >;
    protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedListIteratorRemoveClient < __ElementType >;
    protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __LinkedListConstIteratorRemoveClient < __ElementType >;
    protected:  using RemoveOfCollectionClient              = __hidden :: __impl :: __LinkedListRemoveOfCollectionClient < __ElementType >;
    protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedListRemoveOfInitializerListClient < __ElementType >;
    protected:  using RemoveByClient                        = __hidden :: __impl :: __LinkedListRemoveByClient < __ElementType >;
    protected:  using GenericStatementsClient               = __hidden :: __impl :: __LinkedListGenericStatementsClient < __ElementType >;
    protected:  using GenericConstStatementsClient          = __hidden :: __impl :: __LinkedListGenericConstStatementsClient < __ElementType >;
    protected:  using ReplaceClient                         = __hidden :: __impl :: __LinkedListReplaceClient < __ElementType >;
    protected:  using ReplaceOfCollectionClient             = __hidden :: __impl :: __LinkedListReplaceOfCollectionClient < __ElementType >;
    protected:  using ReplaceOfInitializerListClient        = __hidden :: __impl :: __LinkedListReplaceOfInitializerListClient < __ElementType >;
    protected:  using ReplaceByClient                       = __hidden :: __impl :: __LinkedListReplaceByClient < __ElementType >;
    protected:  using ContainsOfCollectionClient            = __hidden :: __impl :: __LinkedListContainsOfCollectionClient < __ElementType >;
    protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedListContainsOfInitializerListClient < __ElementType >;
    protected:  using IndexedOperationsClient               = __hidden :: __impl :: __LinkedListIndexedOperationsClient < __ElementType >;
    protected:  using IndicesClient                         = __hidden :: __impl :: __LinkedListIndicesClient < __ElementType >;
    protected:  using IndicesOfCollectionClient             = __hidden :: __impl :: __LinkedListIndicesOfCollectionClient < __ElementType >;
    protected:  using IndicesOfInitializerListClient        = __hidden :: __impl :: __LinkedListIndicesOfInitializerListClient < __ElementType >;
    protected:  using IndicesByClient                       = __hidden :: __impl :: __LinkedListIndicesByClient < __ElementType >;
    protected:  using DelegateForwardIterableClient         = __hidden :: __impl :: __LinkedListDelegateForwardIterableClient < __ElementType >;
    protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedListDelegateForwardConstIterableClient < __ElementType >;
    protected:  using DelegateBackwardIterableClient        = __hidden :: __impl :: __LinkedListDelegateBackwardIterableClient < __ElementType >;
    protected:  using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __LinkedListDelegateBackwardConstIterableClient < __ElementType >;

    private:    friend BoundaryInsertionClient;
    private:    friend RandomInsertionClient;
    private:    friend IteratorRemoveClient;
    private:    friend ConstIteratorRemoveClient;
    private:    friend IteratorRelativeInsertionClient;
    private:    friend ConstIteratorRelativeInsertionClient;
    private:    friend IndexedOperationsClient;
    private:    friend DelegateForwardIterableClient;
    private:    friend DelegateForwardConstIterableClient;
    private:    friend DelegateBackwardIterableClient;
    private:    friend DelegateBackwardConstIterableClient;

    public: using ElementType                   = __ElementType;

    protected:  using ListBase                  = List < __ElementType >;

    protected:  using typename ListBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier) */
    protected:  using typename ListBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier) */

    public:     using typename DelegateForwardIterableClient :: Iterator;
    public:     using typename DelegateForwardConstIterableClient :: ConstIterator;
    public:     using typename DelegateBackwardIterableClient :: ReverseIterator;
    public:     using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler ( /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public:     using DelegateForwardIterableClient :: begin;
    public:     using DelegateForwardIterableClient :: end;

    public:     using DelegateForwardConstIterableClient :: begin;
    public:     using DelegateForwardConstIterableClient :: end;
    public:     using DelegateForwardConstIterableClient :: cbegin;
    public:     using DelegateForwardConstIterableClient :: cend;

    public:     using DelegateBackwardIterableClient :: rbegin;
    public:     using DelegateBackwardIterableClient :: rend;

    public:     using DelegateBackwardConstIterableClient :: rbegin;
    public:     using DelegateBackwardConstIterableClient :: rend;
    public:     using DelegateBackwardConstIterableClient :: crbegin;
    public:     using DelegateBackwardConstIterableClient :: crend;

    public:     using RandomInsertionClient :: insert;
    public:     using RandomInsertionClient :: insertAll;
    public:     using RandomInsertionClient :: insertAllOf;
    public:     using RandomInsertionClient :: add;
    public:     using RandomInsertionClient :: addAll;
    public:     using RandomInsertionClient :: addAllOf;
    public:     using RandomInsertionClient :: emplace;

    public:     using BoundaryInsertionClient :: pushBack;
    public:     using BoundaryInsertionClient :: pushBackAll;
    public:     using BoundaryInsertionClient :: pushBackAllOf;
    public:     using BoundaryInsertionClient :: pushFront;
    public:     using BoundaryInsertionClient :: pushFrontAll;
    public:     using BoundaryInsertionClient :: pushFrontAllOf;
    public:     using BoundaryInsertionClient :: append;
    public:     using BoundaryInsertionClient :: prepend;
    public:     using BoundaryInsertionClient :: emplaceBack;
    public:     using BoundaryInsertionClient :: emplaceFront;

    public:     using IteratorRelativeInsertionClient :: insertBefore;
    public:     using IteratorRelativeInsertionClient :: insertAllBefore;
    public:     using IteratorRelativeInsertionClient :: insertAllOfBefore;
    public:     using IteratorRelativeInsertionClient :: emplaceBefore;
    public:     using IteratorRelativeInsertionClient :: insertAfter;
    public:     using IteratorRelativeInsertionClient :: insertAllAfter;
    public:     using IteratorRelativeInsertionClient :: insertAllOfAfter;
    public:     using IteratorRelativeInsertionClient :: emplaceAfter;

    public:     using ConstIteratorRelativeInsertionClient :: insertBefore;
    public:     using ConstIteratorRelativeInsertionClient :: insertAllBefore;
    public:     using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;
    public:     using ConstIteratorRelativeInsertionClient :: emplaceBefore;
    public:     using ConstIteratorRelativeInsertionClient :: insertAfter;
    public:     using ConstIteratorRelativeInsertionClient :: insertAllAfter;
    public:     using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;
    public:     using ConstIteratorRelativeInsertionClient :: emplaceAfter;

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

    public:     using FindConstOfCollectionClient :: findOf;
    public:     using FindConstOfCollectionClient :: findFirstOf;
    public:     using FindConstOfCollectionClient :: findLastOf;
    public:     using FindConstOfCollectionClient :: findAllOf;
    public:     using FindConstOfCollectionClient :: findNotOf;
    public:     using FindConstOfCollectionClient :: findFirstNotOf;
    public:     using FindConstOfCollectionClient :: findLastNotOf;
    public:     using FindConstOfCollectionClient :: findAllNotOf;

    public:     using FindConstOfInitializerListClient :: findOf;
    public:     using FindConstOfInitializerListClient :: findFirstOf;
    public:     using FindConstOfInitializerListClient :: findLastOf;
    public:     using FindConstOfInitializerListClient :: findAllOf;
    public:     using FindConstOfInitializerListClient :: findNotOf;
    public:     using FindConstOfInitializerListClient :: findFirstNotOf;
    public:     using FindConstOfInitializerListClient :: findLastNotOf;
    public:     using FindConstOfInitializerListClient :: findAllNotOf;

    public:     using FindByClient :: findThat;
    public:     using FindByClient :: findFirstThat;
    public:     using FindByClient :: findLastThat;
    public:     using FindByClient :: findAllThat;

    public:     using FindConstByClient :: findThat;
    public:     using FindConstByClient :: findFirstThat;
    public:     using FindConstByClient :: findLastThat;
    public:     using FindConstByClient :: findAllThat;

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

    public:     using GenericConstStatementsClient :: forEach;
    public:     using GenericConstStatementsClient :: some;
    public:     using GenericConstStatementsClient :: atLeast;
    public:     using GenericConstStatementsClient :: atMost;
    public:     using GenericConstStatementsClient :: moreThan;
    public:     using GenericConstStatementsClient :: fewerThan;
    public:     using GenericConstStatementsClient :: count;
    public:     using GenericConstStatementsClient :: any;
    public:     using GenericConstStatementsClient :: all;
    public:     using GenericConstStatementsClient :: none;

    public:     using ContainsOfCollectionClient :: containsAnyOf;
    public:     using ContainsOfCollectionClient :: containsAnyNotOf;
    public:     using ContainsOfCollectionClient :: containsAllOf;
    public:     using ContainsOfCollectionClient :: containsNoneOf;

    public:     using ContainsOfInitializerListClient :: containsAnyOf;
    public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
    public:     using ContainsOfInitializerListClient :: containsAllOf;
    public:     using ContainsOfInitializerListClient :: containsNoneOf;

    public:     using ReplaceClient :: replace;
    public:     using ReplaceClient :: replaceFirst;
    public:     using ReplaceClient :: replaceLast;
    public:     using ReplaceClient :: replaceAll;

    public:     using ReplaceOfCollectionClient :: replaceOf;
    public:     using ReplaceOfCollectionClient :: replaceFirstOf;
    public:     using ReplaceOfCollectionClient :: replaceLastOf;
    public:     using ReplaceOfCollectionClient :: replaceAllOf;
    public:     using ReplaceOfCollectionClient :: replaceNotOf;
    public:     using ReplaceOfCollectionClient :: replaceFirstNotOf;
    public:     using ReplaceOfCollectionClient :: replaceLastNotOf;
    public:     using ReplaceOfCollectionClient :: replaceAllNotOf;

    public:     using ReplaceOfInitializerListClient :: replaceOf;
    public:     using ReplaceOfInitializerListClient :: replaceFirstOf;
    public:     using ReplaceOfInitializerListClient :: replaceLastOf;
    public:     using ReplaceOfInitializerListClient :: replaceAllOf;
    public:     using ReplaceOfInitializerListClient :: replaceNotOf;
    public:     using ReplaceOfInitializerListClient :: replaceFirstNotOf;
    public:     using ReplaceOfInitializerListClient :: replaceLastNotOf;
    public:     using ReplaceOfInitializerListClient :: replaceAllNotOf;

    public:     using ReplaceByClient :: replaceThat;
    public:     using ReplaceByClient :: replaceFirstThat;
    public:     using ReplaceByClient :: replaceLastThat;
    public:     using ReplaceByClient :: replaceAllThat;
    public:     using ReplaceByClient :: replaceThatBy;
    public:     using ReplaceByClient :: replaceFirstThatBy;
    public:     using ReplaceByClient :: replaceLastThatBy;
    public:     using ReplaceByClient :: replaceAllThatBy;

    public:     using IndexedOperationsClient :: sub;

    public:     using IndicesClient :: indicesOf;
    public:     using IndicesClient :: firstIndexOf;
    public:     using IndicesClient :: lastIndexOf;
    public:     using IndicesClient :: allIndicesOf;

    public:     using IndicesOfCollectionClient :: indicesOfFrom;
    public:     using IndicesOfCollectionClient :: firstIndexOfFrom;
    public:     using IndicesOfCollectionClient :: lastIndexOfFrom;
    public:     using IndicesOfCollectionClient :: allIndicesOfFrom;
    public:     using IndicesOfCollectionClient :: indicesOfNotFrom;
    public:     using IndicesOfCollectionClient :: firstIndexOfNotFrom;
    public:     using IndicesOfCollectionClient :: lastIndexOfNotFrom;
    public:     using IndicesOfCollectionClient :: allIndicesOfNotFrom;

    public:     using IndicesOfInitializerListClient :: indicesOfFrom;
    public:     using IndicesOfInitializerListClient :: firstIndexOfFrom;
    public:     using IndicesOfInitializerListClient :: lastIndexOfFrom;
    public:     using IndicesOfInitializerListClient :: allIndicesOfFrom;
    public:     using IndicesOfInitializerListClient :: indicesOfNotFrom;
    public:     using IndicesOfInitializerListClient :: firstIndexOfNotFrom;
    public:     using IndicesOfInitializerListClient :: lastIndexOfNotFrom;
    public:     using IndicesOfInitializerListClient :: allIndicesOfNotFrom;

    public:     using IndicesByClient :: indicesOfThat;
    public:     using IndicesByClient :: firstIndexOfThat;
    public:     using IndicesByClient :: lastIndexOfThat;
    public:     using IndicesByClient :: allIndicesOfThat;

    public:     using IteratorRemoveClient :: remove;
    public:     using ConstIteratorRemoveClient :: remove;
    public:     using List < __ElementType > :: remove;

    public:
        constexpr LinkedList () noexcept;

    public:
        LinkedList ( /* NOLINT(google-explicit-constructor) */
                LinkedList const & list
        ) noexcept;

    public:
        constexpr LinkedList (
                LinkedList && list
        ) noexcept;

    public:
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedList (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count = 0ULL
        ) noexcept;

    public:
        template <
                typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedList (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_Explicit LinkedList (
                __IterableType const & iterable
        ) noexcept;

    public:
        ~LinkedList () noexcept override;

    public:
        auto operator = (
                LinkedList const & list
        ) noexcept -> LinkedList &;

    public:
        auto operator = (
                LinkedList && array
        ) noexcept -> LinkedList &;

    public:
        auto operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> LinkedList &;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> LinkedList &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                LinkedList const & list
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                LinkedList const & list
        ) const noexcept -> bool;

    public:
        auto clear () noexcept -> void override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

    public:
        auto popFront () noexcept -> void override;

    public:
        auto popBack () noexcept -> void override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                Index index
        ) noexcept (false) -> ElementType & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                Index index
        ) const noexcept (false) -> ElementType const & override;

    public:
        auto removeAt (
                Index index
        ) noexcept -> bool override;

    protected:
        auto sort (
                cds :: Function < auto ( __ElementType const &, __ElementType const & ) -> bool > const & comparator
        ) noexcept -> void override;

    public:
        template <
                typename __Comparator = decltype ( & cds :: predicates :: lessThan < __ElementType > )  /* NOLINT(bugprone-reserved-identifier) */
        > auto sort (
                __Comparator const & comparator = & cds :: predicates :: lessThan < __ElementType >
        ) noexcept -> void;

    public:
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < LinkedList < __ElementType > >;

    public:
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < LinkedList < __ElementType > >;

    public:
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < LinkedList < __ElementType > const >;

    public:
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < LinkedList < __ElementType > const >;
    };

}


#include "../../../../shared/iterator/impl/NodeIterator.hpp"

#include "../../../../shared/linkedList/impl/DoubleLinkedList.hpp"

#include "../../../../shared/collectionInternalCommunication/server/impl/ListServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/impl/ListServerDispatcher.hpp"

#include "../../../../shared/linkedList/impl/Sequence.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "linkedList/impl/LinkedList.hpp"
#include "linkedList/impl/CTAD.hpp"

#endif /* __CDS_LINKED_LIST_HPP__ */
