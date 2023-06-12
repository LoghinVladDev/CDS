// NOLINT(llvm-header-guard)
// Created by loghin on 15.01.2021.
//

#ifndef __CDS_LINKED_LIST_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_LIST_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/List>

#include "linkedList/LinkedListPredeclaration.hpp"

#include "../../../../shared/Node.hpp"

#include "../../../../shared/iterator/NodeIterator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/ListServerDispatcher.hpp"   // NOLINT(llvm-include-order)
#include "../../../../shared/iterableInternalCommunication/server/ListServer.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/linkedList/DoubleLinkedList.hpp"

#include "linkedList/LinkedListConstructs.hpp"


namespace cds {

template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs LinkedList :
    public List <__ElementType>,
    protected __hidden::__impl::__LinkedListServer <__ElementType>,
    public __hidden::__impl::__LinkedListImplementation <__ElementType>,
    public __hidden::__impl::__LinkedListDispatcher <__ElementType>,
    public __hidden::__impl::__LinkedListRandomInsertionClient <__ElementType>,
    public __hidden::__impl::__LinkedListBoundaryInsertionClient <__ElementType>,
    public __hidden::__impl::__LinkedListIteratorRelativeInsertionClient <__ElementType>,
    public __hidden::__impl::__LinkedListConstIteratorRelativeInsertionClient <__ElementType>,
    public __hidden::__impl::__LinkedListFindOfIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListFindOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__LinkedListFindConstOfIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListFindConstOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__LinkedListFindByClient <__ElementType>,
    public __hidden::__impl::__LinkedListFindConstByClient <__ElementType>,
    public __hidden::__impl::__LinkedListIteratorRemoveClient <__ElementType>,
    public __hidden::__impl::__LinkedListConstIteratorRemoveClient <__ElementType>,
    public __hidden::__impl::__LinkedListRemoveOfIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListRemoveOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__LinkedListRemoveByClient <__ElementType>,
    public __hidden::__impl::__LinkedListGenericStatementsClient <__ElementType>,
    public __hidden::__impl::__LinkedListGenericConstStatementsClient <__ElementType>,
    public __hidden::__impl::__LinkedListReplaceClient <__ElementType>,
    public __hidden::__impl::__LinkedListReplaceOfIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListReplaceOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__LinkedListReplaceByClient <__ElementType>,
    public __hidden::__impl::__LinkedListContainsOfIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListContainsOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__LinkedListIndexedOperationsClient <__ElementType>,
    public __hidden::__impl::__LinkedListIndicesClient <__ElementType>,
    public __hidden::__impl::__LinkedListIndicesOfIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListIndicesOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__LinkedListIndicesByClient <__ElementType>,
    public __hidden::__impl::__LinkedListDelegateForwardIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListDelegateForwardConstIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListDelegateBackwardIterableClient <__ElementType>,
    public __hidden::__impl::__LinkedListDelegateBackwardConstIterableClient <__ElementType> {
protected:
  using Implementation                        = __hidden::__impl::__LinkedListImplementation <__ElementType>;
  using Server                                = __hidden::__impl::__LinkedListServer <__ElementType>;
  using RandomInsertionClient                 = __hidden::__impl::__LinkedListRandomInsertionClient <__ElementType>;
  using BoundaryInsertionClient               = __hidden::__impl::__LinkedListBoundaryInsertionClient <__ElementType>;
  using IteratorRelativeInsertionClient       = __hidden::__impl::__LinkedListIteratorRelativeInsertionClient <__ElementType>;
  using ConstIteratorRelativeInsertionClient  = __hidden::__impl::__LinkedListConstIteratorRelativeInsertionClient <__ElementType>;
  using FindOfIterableClient                  = __hidden::__impl::__LinkedListFindOfIterableClient <__ElementType>;
  using FindOfInitializerListClient           = __hidden::__impl::__LinkedListFindOfInitializerListClient <__ElementType>;
  using FindConstOfIterableClient             = __hidden::__impl::__LinkedListFindConstOfIterableClient <__ElementType>;
  using FindConstOfInitializerListClient      = __hidden::__impl::__LinkedListFindConstOfInitializerListClient <__ElementType>;
  using FindByClient                          = __hidden::__impl::__LinkedListFindByClient <__ElementType>;
  using FindConstByClient                     = __hidden::__impl::__LinkedListFindConstByClient <__ElementType>;
  using IteratorRemoveClient                  = __hidden::__impl::__LinkedListIteratorRemoveClient <__ElementType>;
  using ConstIteratorRemoveClient             = __hidden::__impl::__LinkedListConstIteratorRemoveClient <__ElementType>;
  using RemoveOfIterableClient                = __hidden::__impl::__LinkedListRemoveOfIterableClient <__ElementType>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__LinkedListRemoveOfInitializerListClient <__ElementType>;
  using RemoveByClient                        = __hidden::__impl::__LinkedListRemoveByClient <__ElementType>;
  using GenericStatementsClient               = __hidden::__impl::__LinkedListGenericStatementsClient <__ElementType>;
  using GenericConstStatementsClient          = __hidden::__impl::__LinkedListGenericConstStatementsClient <__ElementType>;
  using ReplaceClient                         = __hidden::__impl::__LinkedListReplaceClient <__ElementType>;
  using ReplaceOfIterableClient               = __hidden::__impl::__LinkedListReplaceOfIterableClient <__ElementType>;
  using ReplaceOfInitializerListClient        = __hidden::__impl::__LinkedListReplaceOfInitializerListClient <__ElementType>;
  using ReplaceByClient                       = __hidden::__impl::__LinkedListReplaceByClient <__ElementType>;
  using ContainsOfIterableClient              = __hidden::__impl::__LinkedListContainsOfIterableClient <__ElementType>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__LinkedListContainsOfInitializerListClient <__ElementType>;
  using IndexedOperationsClient               = __hidden::__impl::__LinkedListIndexedOperationsClient <__ElementType>;
  using IndicesClient                         = __hidden::__impl::__LinkedListIndicesClient <__ElementType>;
  using IndicesOfIterableClient               = __hidden::__impl::__LinkedListIndicesOfIterableClient <__ElementType>;
  using IndicesOfInitializerListClient        = __hidden::__impl::__LinkedListIndicesOfInitializerListClient <__ElementType>;
  using IndicesByClient                       = __hidden::__impl::__LinkedListIndicesByClient <__ElementType>;
  using DelegateForwardIterableClient         = __hidden::__impl::__LinkedListDelegateForwardIterableClient <__ElementType>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__LinkedListDelegateForwardConstIterableClient <__ElementType>;
  using DelegateBackwardIterableClient        = __hidden::__impl::__LinkedListDelegateBackwardIterableClient <__ElementType>;
  using DelegateBackwardConstIterableClient   = __hidden::__impl::__LinkedListDelegateBackwardConstIterableClient <__ElementType>;
  using ListBase                              = List <__ElementType>;
  
public:
  using ElementType                   = __ElementType;
  
  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;
  using typename DelegateBackwardIterableClient::ReverseIterator;
  using typename DelegateBackwardConstIterableClient::ConstReverseIterator;

  using DelegateForwardIterableClient::begin;
  using DelegateForwardIterableClient::end;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using DelegateBackwardIterableClient::rbegin;
  using DelegateBackwardIterableClient::rend;

  using DelegateBackwardConstIterableClient::rbegin;
  using DelegateBackwardConstIterableClient::rend;
  using DelegateBackwardConstIterableClient::crbegin;
  using DelegateBackwardConstIterableClient::crend;

  using RandomInsertionClient::insert;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::add;
  using RandomInsertionClient::addAll;
  using RandomInsertionClient::addAllOf;
  using RandomInsertionClient::emplace;

  using BoundaryInsertionClient::pushBack;
  using BoundaryInsertionClient::pushBackAll;
  using BoundaryInsertionClient::pushBackAllOf;
  using BoundaryInsertionClient::pushFront;
  using BoundaryInsertionClient::pushFrontAll;
  using BoundaryInsertionClient::pushFrontAllOf;
  using BoundaryInsertionClient::append;
  using BoundaryInsertionClient::prepend;
  using BoundaryInsertionClient::emplaceBack;
  using BoundaryInsertionClient::emplaceFront;

  using IteratorRelativeInsertionClient::insertBefore;
  using IteratorRelativeInsertionClient::insertAllBefore;
  using IteratorRelativeInsertionClient::insertAllOfBefore;
  using IteratorRelativeInsertionClient::emplaceBefore;
  using IteratorRelativeInsertionClient::insertAfter;
  using IteratorRelativeInsertionClient::insertAllAfter;
  using IteratorRelativeInsertionClient::insertAllOfAfter;
  using IteratorRelativeInsertionClient::emplaceAfter;

  using ConstIteratorRelativeInsertionClient::insertBefore;
  using ConstIteratorRelativeInsertionClient::insertAllBefore;
  using ConstIteratorRelativeInsertionClient::insertAllOfBefore;
  using ConstIteratorRelativeInsertionClient::emplaceBefore;
  using ConstIteratorRelativeInsertionClient::insertAfter;
  using ConstIteratorRelativeInsertionClient::insertAllAfter;
  using ConstIteratorRelativeInsertionClient::insertAllOfAfter;
  using ConstIteratorRelativeInsertionClient::emplaceAfter;

  using FindOfIterableClient::findOf;
  using FindOfIterableClient::findFirstOf;
  using FindOfIterableClient::findLastOf;
  using FindOfIterableClient::findAllOf;
  using FindOfIterableClient::findNotOf;
  using FindOfIterableClient::findFirstNotOf;
  using FindOfIterableClient::findLastNotOf;
  using FindOfIterableClient::findAllNotOf;

  using FindOfInitializerListClient::findOf;
  using FindOfInitializerListClient::findFirstOf;
  using FindOfInitializerListClient::findLastOf;
  using FindOfInitializerListClient::findAllOf;
  using FindOfInitializerListClient::findNotOf;
  using FindOfInitializerListClient::findFirstNotOf;
  using FindOfInitializerListClient::findLastNotOf;
  using FindOfInitializerListClient::findAllNotOf;

  using FindConstOfIterableClient::findOf;
  using FindConstOfIterableClient::findFirstOf;
  using FindConstOfIterableClient::findLastOf;
  using FindConstOfIterableClient::findAllOf;
  using FindConstOfIterableClient::findNotOf;
  using FindConstOfIterableClient::findFirstNotOf;
  using FindConstOfIterableClient::findLastNotOf;
  using FindConstOfIterableClient::findAllNotOf;

  using FindConstOfInitializerListClient::findOf;
  using FindConstOfInitializerListClient::findFirstOf;
  using FindConstOfInitializerListClient::findLastOf;
  using FindConstOfInitializerListClient::findAllOf;
  using FindConstOfInitializerListClient::findNotOf;
  using FindConstOfInitializerListClient::findFirstNotOf;
  using FindConstOfInitializerListClient::findLastNotOf;
  using FindConstOfInitializerListClient::findAllNotOf;

  using FindByClient::findThat;
  using FindByClient::findFirstThat;
  using FindByClient::findLastThat;
  using FindByClient::findAllThat;

  using FindConstByClient::findThat;
  using FindConstByClient::findFirstThat;
  using FindConstByClient::findLastThat;
  using FindConstByClient::findAllThat;

  using RemoveOfIterableClient::removeOf;
  using RemoveOfIterableClient::removeFirstOf;
  using RemoveOfIterableClient::removeLastOf;
  using RemoveOfIterableClient::removeAllOf;
  using RemoveOfIterableClient::removeNotOf;
  using RemoveOfIterableClient::removeFirstNotOf;
  using RemoveOfIterableClient::removeLastNotOf;
  using RemoveOfIterableClient::removeAllNotOf;

  using RemoveOfInitializerListClient::removeOf;
  using RemoveOfInitializerListClient::removeFirstOf;
  using RemoveOfInitializerListClient::removeLastOf;
  using RemoveOfInitializerListClient::removeAllOf;
  using RemoveOfInitializerListClient::removeNotOf;
  using RemoveOfInitializerListClient::removeFirstNotOf;
  using RemoveOfInitializerListClient::removeLastNotOf;
  using RemoveOfInitializerListClient::removeAllNotOf;

  using RemoveByClient::removeThat;
  using RemoveByClient::removeFirstThat;
  using RemoveByClient::removeLastThat;
  using RemoveByClient::removeAllThat;

  using GenericStatementsClient::forEach;
  using GenericStatementsClient::some;
  using GenericStatementsClient::atLeast;
  using GenericStatementsClient::atMost;
  using GenericStatementsClient::moreThan;
  using GenericStatementsClient::fewerThan;
  using GenericStatementsClient::count;
  using GenericStatementsClient::any;
  using GenericStatementsClient::all;
  using GenericStatementsClient::none;

  using GenericConstStatementsClient::forEach;
  using GenericConstStatementsClient::some;
  using GenericConstStatementsClient::atLeast;
  using GenericConstStatementsClient::atMost;
  using GenericConstStatementsClient::moreThan;
  using GenericConstStatementsClient::fewerThan;
  using GenericConstStatementsClient::count;
  using GenericConstStatementsClient::any;
  using GenericConstStatementsClient::all;
  using GenericConstStatementsClient::none;

  using ContainsOfIterableClient::containsAnyOf;
  using ContainsOfIterableClient::containsAnyNotOf;
  using ContainsOfIterableClient::containsAllOf;
  using ContainsOfIterableClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  using ReplaceClient::replace;
  using ReplaceClient::replaceFirst;
  using ReplaceClient::replaceLast;
  using ReplaceClient::replaceAll;

  using ReplaceOfIterableClient::replaceOf;
  using ReplaceOfIterableClient::replaceFirstOf;
  using ReplaceOfIterableClient::replaceLastOf;
  using ReplaceOfIterableClient::replaceAllOf;
  using ReplaceOfIterableClient::replaceNotOf;
  using ReplaceOfIterableClient::replaceFirstNotOf;
  using ReplaceOfIterableClient::replaceLastNotOf;
  using ReplaceOfIterableClient::replaceAllNotOf;

  using ReplaceOfInitializerListClient::replaceOf;
  using ReplaceOfInitializerListClient::replaceFirstOf;
  using ReplaceOfInitializerListClient::replaceLastOf;
  using ReplaceOfInitializerListClient::replaceAllOf;
  using ReplaceOfInitializerListClient::replaceNotOf;
  using ReplaceOfInitializerListClient::replaceFirstNotOf;
  using ReplaceOfInitializerListClient::replaceLastNotOf;
  using ReplaceOfInitializerListClient::replaceAllNotOf;

  using ReplaceByClient::replaceThat;
  using ReplaceByClient::replaceFirstThat;
  using ReplaceByClient::replaceLastThat;
  using ReplaceByClient::replaceAllThat;
  using ReplaceByClient::replaceThatBy;
  using ReplaceByClient::replaceFirstThatBy;
  using ReplaceByClient::replaceLastThatBy;
  using ReplaceByClient::replaceAllThatBy;

  using IndexedOperationsClient::sub;

  using IndicesClient::indicesOf;
  using IndicesClient::firstIndexOf;
  using IndicesClient::lastIndexOf;
  using IndicesClient::allIndicesOf;

  using IndicesOfIterableClient::indicesOfFrom;
  using IndicesOfIterableClient::firstIndexOfFrom;
  using IndicesOfIterableClient::lastIndexOfFrom;
  using IndicesOfIterableClient::allIndicesOfFrom;
  using IndicesOfIterableClient::indicesOfNotFrom;
  using IndicesOfIterableClient::firstIndexOfNotFrom;
  using IndicesOfIterableClient::lastIndexOfNotFrom;
  using IndicesOfIterableClient::allIndicesOfNotFrom;

  using IndicesOfInitializerListClient::indicesOfFrom;
  using IndicesOfInitializerListClient::firstIndexOfFrom;
  using IndicesOfInitializerListClient::lastIndexOfFrom;
  using IndicesOfInitializerListClient::allIndicesOfFrom;
  using IndicesOfInitializerListClient::indicesOfNotFrom;
  using IndicesOfInitializerListClient::firstIndexOfNotFrom;
  using IndicesOfInitializerListClient::lastIndexOfNotFrom;
  using IndicesOfInitializerListClient::allIndicesOfNotFrom;

  using IndicesByClient::indicesOfThat;
  using IndicesByClient::firstIndexOfThat;
  using IndicesByClient::lastIndexOfThat;
  using IndicesByClient::allIndicesOfThat;

  using IteratorRemoveClient::remove;
  using ConstIteratorRemoveClient::remove;
  using List <__ElementType>::remove;

  constexpr LinkedList () noexcept;
  LinkedList (LinkedList const& list) noexcept(false);
  constexpr LinkedList (LinkedList&& list) noexcept;

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedList (
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedList (std::initializer_list <__ElementType> const& initializerList) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit LinkedList (__IterableType const& iterable) noexcept(false);

  ~LinkedList () noexcept override;

  auto operator = (LinkedList const& list) noexcept(false) -> LinkedList&;
  auto operator = (LinkedList&& list) noexcept -> LinkedList&;
  auto operator = (std::initializer_list <__ElementType> const& initializerList) noexcept(false) -> LinkedList&;

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (__IterableType const& iterable) noexcept(false) -> LinkedList&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      LinkedList const& list
  ) const noexcept -> bool;
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      LinkedList const& list
  ) const noexcept -> bool;

  auto clear () noexcept -> void override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;
  auto popFront () noexcept -> void override;
  auto popBack () noexcept -> void override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (Index index) noexcept (false) -> ElementType& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (Index index) const noexcept (false) -> ElementType const& override;

  auto removeAt (Index index) noexcept -> bool override;

  template <
      typename __Comparator = decltype (&cds::predicates::lessThan <__ElementType>)  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto sort (__Comparator const& comparator = &cds::predicates::lessThan <__ElementType>) noexcept -> void;

  __CDS_NoDiscard auto sequence () & noexcept -> Sequence <LinkedList <__ElementType> >;
  __CDS_NoDiscard auto sequence () && noexcept -> Sequence <LinkedList <__ElementType> >;
  __CDS_NoDiscard auto sequence () const& noexcept -> Sequence <LinkedList <__ElementType> const>;
  __CDS_NoDiscard auto sequence () const&& noexcept -> Sequence <LinkedList <__ElementType> const>;

  using ListBase::empty;

protected:
  using typename ListBase::__GenericHandler;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename ListBase::__GenericConstHandler;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto sort (
      cds::Function <auto (__ElementType const&, __ElementType const&) -> bool > const& comparator
  ) noexcept -> void override;

private:
  template < typename, typename >
  friend class __hidden::__impl::__ListServer; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend __hidden::__impl::__LocalBoundaryInsertionPrimitiveClient<LinkedList, __ElementType, __ElementType>;
  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient<LinkedList, __ElementType, __ElementType>;
  friend __hidden::__impl::__LocalIteratorRemovePrimitiveClient<LinkedList, __ElementType, AbstractBidirectionalNodeIterator<__ElementType>>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient<LinkedList, __ElementType, AbstractBidirectionalNodeIterator<__ElementType const>>;
  friend __hidden::__impl::__LocalIteratorRelativeInsertionPrimitiveClient<LinkedList, __ElementType, AbstractBidirectionalNodeIterator<__ElementType>>;
  friend __hidden::__impl::__LocalConstIteratorRelativeInsertionPrimitiveClient<LinkedList, __ElementType, AbstractBidirectionalNodeIterator<__ElementType const>>;
  friend __hidden::__impl::__LocalIndexedOperationsPrimitiveClient<LinkedList, __ElementType>;
  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <LinkedList, typename Implementation::__dll_Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <LinkedList, typename Implementation::__dll_ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardIterablePrimitiveClient <LinkedList, typename Implementation::__dll_ReverseIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <LinkedList, typename Implementation::__dll_ConstReverseIterator>;

  using Server::__ls_handlers;              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ls_constHandlers;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Implementation::__dll_clear;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_copy;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_move;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_size;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_removeFront;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_removeBack;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_front;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_back;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_get;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_removeAt;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_equals;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__dll_sort;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;
};

} // namespace cds


#include "../../../../shared/iterator/impl/NodeIterator.hpp"

#include "../../../../shared/linkedList/impl/DoubleLinkedListImpl.hpp"

#include "../../../../shared/iterableInternalCommunication/server/impl/ListServerImpl.hpp"
#include "../../../../shared/iterableInternalCommunication/server/impl/ListServerDispatcherImpl.hpp"

#include "../../../../shared/linkedList/impl/Sequence.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "linkedList/impl/LinkedListImpl.hpp" // NOLINT(llvm-include-order)
#include "linkedList/impl/LinkedListCTAD.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_LINKED_LIST_HPP__
