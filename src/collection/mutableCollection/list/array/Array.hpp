// NOLINT(llvm-header-guard)
// Created by loghin on 01.03.2021.
//

#ifndef __CDS_ARRAY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ARRAY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/List>

#include "array/ArrayPredeclaration.hpp"

#include "../../../../shared/iterator/IteratorSort.hpp"                                         // NOLINT(llvm-include-order)
#include "../../../../shared/iterator/AddressIterator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/ListServerDispatcher.hpp"

#include "../../../../shared/array/ArrayBase.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/ListServer.hpp"

#include "array/ArrayConstructs.hpp"

namespace cds {

template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs Array :
    public List <__ElementType>,
    protected __hidden::__impl::__ArrayServer <__ElementType>,
    public __hidden::__impl::__ArrayImplementation <__ElementType>,
    public __hidden::__impl::__ArrayDispatcher <__ElementType>,
    public __hidden::__impl::__ArrayRandomInsertionClient <__ElementType>,
    public __hidden::__impl::__ArrayBoundaryInsertionClient <__ElementType>,
    public __hidden::__impl::__ArrayIteratorRelativeInsertionClient <__ElementType>,
    public __hidden::__impl::__ArrayConstIteratorRelativeInsertionClient <__ElementType>,
    public __hidden::__impl::__ArrayFindOfIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayFindOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__ArrayFindConstOfIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayFindConstOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__ArrayFindByClient <__ElementType>,
    public __hidden::__impl::__ArrayFindConstByClient <__ElementType>,
    public __hidden::__impl::__ArrayIteratorRemoveClient <__ElementType>,
    public __hidden::__impl::__ArrayConstIteratorRemoveClient <__ElementType>,
    public __hidden::__impl::__ArrayRemoveOfIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayRemoveOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__ArrayRemoveByClient <__ElementType>,
    public __hidden::__impl::__ArrayGenericStatementsClient <__ElementType>,
    public __hidden::__impl::__ArrayGenericConstStatementsClient <__ElementType>,
    public __hidden::__impl::__ArrayReplaceClient <__ElementType>,
    public __hidden::__impl::__ArrayReplaceOfIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayReplaceOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__ArrayReplaceByClient <__ElementType>,
    public __hidden::__impl::__ArrayContainsOfIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayContainsOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__ArrayIndexedOperationsClient <__ElementType>,
    public __hidden::__impl::__ArrayIndicesClient <__ElementType>,
    public __hidden::__impl::__ArrayIndicesOfIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayIndicesOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__ArrayIndicesByClient <__ElementType>,
    public __hidden::__impl::__ArrayDelegateForwardIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayDelegateForwardConstIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayDelegateBackwardIterableClient <__ElementType>,
    public __hidden::__impl::__ArrayDelegateBackwardConstIterableClient <__ElementType> {
protected:
  using ListBase                              = List <__ElementType>;
  using Implementation                        = __hidden::__impl::__ArrayImplementation <__ElementType>;
  using Server                                = __hidden::__impl::__ArrayServer <__ElementType>;
  using Dispatcher                            = __hidden::__impl::__ArrayDispatcher <__ElementType>;
  using RandomInsertionClient                 = __hidden::__impl::__ArrayRandomInsertionClient <__ElementType>;
  using BoundaryInsertionClient               = __hidden::__impl::__ArrayBoundaryInsertionClient <__ElementType>;
  using IteratorRelativeInsertionClient       = __hidden::__impl::__ArrayIteratorRelativeInsertionClient <__ElementType>;
  using ConstIteratorRelativeInsertionClient  = __hidden::__impl::__ArrayConstIteratorRelativeInsertionClient <__ElementType>;
  using FindOfIterableClient                  = __hidden::__impl::__ArrayFindOfIterableClient <__ElementType>;
  using FindOfInitializerListClient           = __hidden::__impl::__ArrayFindOfInitializerListClient <__ElementType>;
  using FindConstOfIterableClient             = __hidden::__impl::__ArrayFindConstOfIterableClient <__ElementType>;
  using FindConstOfInitializerListClient      = __hidden::__impl::__ArrayFindConstOfInitializerListClient <__ElementType>;
  using FindByClient                          = __hidden::__impl::__ArrayFindByClient <__ElementType>;
  using FindConstByClient                     = __hidden::__impl::__ArrayFindConstByClient <__ElementType>;
  using IteratorRemoveClient                  = __hidden::__impl::__ArrayIteratorRemoveClient <__ElementType>;
  using ConstIteratorRemoveClient             = __hidden::__impl::__ArrayConstIteratorRemoveClient <__ElementType>;
  using RemoveOfIterableClient                = __hidden::__impl::__ArrayRemoveOfIterableClient <__ElementType>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__ArrayRemoveOfInitializerListClient <__ElementType>;
  using RemoveByClient                        = __hidden::__impl::__ArrayRemoveByClient <__ElementType>;
  using GenericStatementsClient               = __hidden::__impl::__ArrayGenericStatementsClient <__ElementType>;
  using GenericConstStatementsClient          = __hidden::__impl::__ArrayGenericConstStatementsClient <__ElementType>;
  using ReplaceClient                         = __hidden::__impl::__ArrayReplaceClient <__ElementType>;
  using ReplaceOfIterableClient               = __hidden::__impl::__ArrayReplaceOfIterableClient <__ElementType>;
  using ReplaceOfInitializerListClient        = __hidden::__impl::__ArrayReplaceOfInitializerListClient <__ElementType>;
  using ReplaceByClient                       = __hidden::__impl::__ArrayReplaceByClient <__ElementType>;
  using ContainsOfIterableClient              = __hidden::__impl::__ArrayContainsOfIterableClient <__ElementType>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__ArrayContainsOfInitializerListClient <__ElementType>;
  using IndexedOperationsClient               = __hidden::__impl::__ArrayIndexedOperationsClient <__ElementType>;
  using IndicesClient                         = __hidden::__impl::__ArrayIndicesClient <__ElementType>;
  using IndicesOfIterableClient               = __hidden::__impl::__ArrayIndicesOfIterableClient <__ElementType>;
  using IndicesOfInitializerListClient        = __hidden::__impl::__ArrayIndicesOfInitializerListClient <__ElementType>;
  using IndicesByClient                       = __hidden::__impl::__ArrayIndicesByClient <__ElementType>;
  using DelegateForwardIterableClient         = __hidden::__impl::__ArrayDelegateForwardIterableClient <__ElementType>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__ArrayDelegateForwardConstIterableClient <__ElementType>;
  using DelegateBackwardIterableClient        = __hidden::__impl::__ArrayDelegateBackwardIterableClient <__ElementType>;
  using DelegateBackwardConstIterableClient   = __hidden::__impl::__ArrayDelegateBackwardConstIterableClient <__ElementType>;

public:
  using ElementType                   = __ElementType;

  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;
  using typename DelegateBackwardIterableClient::ReverseIterator;
  using typename DelegateBackwardConstIterableClient::ConstReverseIterator;

  using ListBase::empty;

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

  using ContainsOfIterableClient::containsAnyOf;
  using ContainsOfIterableClient::containsAnyNotOf;
  using ContainsOfIterableClient::containsAllOf;
  using ContainsOfIterableClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  using IteratorRemoveClient::remove;

  using ConstIteratorRemoveClient::remove;

  using List <__ElementType>::remove;

  constexpr Array () noexcept = default;
  Array (Array const& array) noexcept(false);
  constexpr Array (Array&& array) noexcept;

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > Array (__IteratorType const& begin, __IteratorType const& end, Size count = 0u) noexcept(false);

  template <
      typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > Array (std::initializer_list <__ElementType> const& initializerList) noexcept(false);

  template <
      typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TElementType>::value> = 0
  > __CDS_Explicit Array (Size size) noexcept(false);

  template <
      typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > Array (Size size, __ElementType const& defaultValue) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit Array (__IterableType const& iterable) noexcept(false);

  ~Array () noexcept override;

  auto operator = (Array const& array) noexcept(false) -> Array&;
  auto operator = (Array&& array) noexcept -> Array&;
  auto operator = (std::initializer_list <__ElementType> const& initializerList) noexcept(false) -> Array&;

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (__IterableType const& iterable) noexcept(false) -> Array&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      Array const& array
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      Array const& array
  ) const noexcept -> bool;

  auto reserve (Size size) noexcept(false) -> void;
  auto shrink (Size size) noexcept -> void;

  template <
      typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TElementType>::value> = 0
  > auto resize (Size size) noexcept(false) -> void;

  template <
      typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto resize (Size size, __ElementType const& defaultValue) noexcept(false) -> void;

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

  __CDS_NoDiscard constexpr auto data () const noexcept -> __ElementType const*;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __ElementType*;

  template <
      typename __Comparator = decltype (&cds::predicates::lessThan <__ElementType>)  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto sort (__Comparator const & comparator = &cds::predicates::lessThan <__ElementType>) noexcept -> void;

  __CDS_NoDiscard auto sequence () & noexcept -> Sequence <Array <__ElementType>>;
  __CDS_NoDiscard auto sequence () && noexcept -> Sequence <Array <__ElementType>>;
  __CDS_NoDiscard auto sequence () const& noexcept -> Sequence <Array <__ElementType> const>;
  __CDS_NoDiscard auto sequence () const&& noexcept -> Sequence <Array <__ElementType> const>;

protected:
  using typename ListBase::__GenericHandler;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename ListBase::__GenericConstHandler;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto sort (
      cds::Function <auto (__ElementType const&, __ElementType const&) -> bool> const& comparator
  ) noexcept -> void override;

private:
  friend __hidden::__impl::__ListServer <Array, __ElementType>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend __hidden::__impl::__LocalBoundaryInsertionPrimitiveClient<Array, __ElementType, __ElementType>;
  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient<Array, __ElementType, __ElementType>;
  friend __hidden::__impl::__LocalIteratorRemovePrimitiveClient<Array, __ElementType, AbstractAddressIterator<__ElementType>>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient<Array, __ElementType, AbstractAddressIterator<__ElementType const>>;
  friend __hidden::__impl::__LocalIteratorRelativeInsertionPrimitiveClient<Array, __ElementType, AbstractAddressIterator<__ElementType>>;
  friend __hidden::__impl::__LocalConstIteratorRelativeInsertionPrimitiveClient<Array, __ElementType, AbstractAddressIterator<__ElementType const>>;
  friend __hidden::__impl::__LocalIndexedOperationsPrimitiveClient<Array, __ElementType>;
  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <Array, typename Implementation::__ab_Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <Array, typename Implementation::__ab_ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardIterablePrimitiveClient <Array, typename Implementation::__ab_ReverseIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <Array, typename Implementation::__ab_ConstReverseIterator>;

  friend IndexedOperationsClient;

  using Server::__ls_handlers;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ls_constHandlers;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Implementation::__ab_resize;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_reserve; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_shrink;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_clear;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_equals;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_size;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_remove;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_get;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_data;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_sort;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_move;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ab_copy;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;
};

} // namespace cds

#include "array/impl/ArrayImpl.hpp"

#include "../../../../shared/array/impl/ArrayBaseImpl.hpp"

#include "../../../../shared/iterator/impl/IteratorSort.hpp"                                            // NOLINT(llvm-include-order)
#include "../../../../shared/iterator/impl/AddressIterator.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/impl/ListServer.hpp"
#include "../../../../shared/iterableInternalCommunication/server/impl/ListServerDispatcher.hpp"

#include "../../../../shared/array/impl/ArraySequence.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#include "array/impl/ArrayCTAD.hpp"

#endif // __CDS_ARRAY_HPP__
