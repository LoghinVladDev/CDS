//
// Created by stefan on 28.08.2022.
//

#ifndef __CDS_TREE_SET_HPP__
#define __CDS_TREE_SET_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Set>

#include "../../../shared/Node.hpp"
#include "../../../shared/impl/generalPredicates.hpp"

#include "../../../shared/iterator/RedBlackTreeIterator.hpp"

#include "../../../shared/iterableInternalCommunication/server/TreeSetServerDispatcher.hpp"

#include "../../../shared/redBlackTree/RedBlackTree.hpp"

#include "../../../shared/iterableInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServer.hpp"

#include "treeSet/TreeSetConstructs.hpp"

namespace cds {

template <typename __ElementType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs TreeSet :
    public Set <__ElementType>,
    protected __hidden::__impl::__TreeSetServer <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetImplementation <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetDispatcher <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetDelegateForwardConstIterableClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetDelegateBackwardConstIterableClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetConstIteratorRemoveClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetRandomInsertionClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetFindUniqueClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetContainsOfCollectionClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetContainsOfInitializerListClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetFindOfCollectionClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetFindOfInitializerListClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetFindByClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetRemoveOfCollectionClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetRemoveOfInitializerListClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetRemoveByClient <__ElementType, __Comparator>,
    public __hidden::__impl::__TreeSetGenericStatementsClient <__ElementType, __Comparator> {
protected:
  using SetBase                                = Set <__ElementType>;
  using Server                                 = __hidden::__impl::__TreeSetServer <__ElementType, __Comparator>;
  using Implementation                         = __hidden::__impl::__TreeSetImplementation <__ElementType, __Comparator>;
  using Dispatcher                             = __hidden::__impl::__TreeSetDispatcher <__ElementType, __Comparator>;
  using DelegateForwardConstIterableClient     = __hidden::__impl::__TreeSetDelegateForwardConstIterableClient <__ElementType, __Comparator>;
  using DelegateBackwardConstIterableClient    = __hidden::__impl::__TreeSetDelegateBackwardConstIterableClient <__ElementType, __Comparator>;
  using ConstIteratorRemoveClient              = __hidden::__impl::__TreeSetConstIteratorRemoveClient <__ElementType, __Comparator>;
  using RandomInsertionClient                  = __hidden::__impl::__TreeSetRandomInsertionClient <__ElementType, __Comparator>;
  using FindUniqueClient                       = __hidden::__impl::__TreeSetFindUniqueClient <__ElementType, __Comparator>;
  using ContainsOfCollectionClient             = __hidden::__impl::__TreeSetContainsOfCollectionClient <__ElementType, __Comparator>;
  using ContainsOfInitializerListClient        = __hidden::__impl::__TreeSetContainsOfInitializerListClient <__ElementType, __Comparator>;
  using FindOfCollectionClient                 = __hidden::__impl::__TreeSetFindOfCollectionClient <__ElementType, __Comparator>;
  using FindOfInitializerListClient            = __hidden::__impl::__TreeSetFindOfInitializerListClient <__ElementType, __Comparator>;
  using FindByClient                           = __hidden::__impl::__TreeSetFindByClient<__ElementType, __Comparator>;
  using RemoveOfCollectionClient               = __hidden::__impl::__TreeSetRemoveOfCollectionClient<__ElementType, __Comparator>;
  using RemoveOfInitializerListClient          = __hidden::__impl::__TreeSetRemoveOfInitializerListClient<__ElementType, __Comparator>;
  using RemoveByClient                         = __hidden::__impl::__TreeSetRemoveByClient<__ElementType, __Comparator>;
  using GenericStatementsClient                = __hidden::__impl::__TreeSetGenericStatementsClient<__ElementType, __Comparator>;

public:
  using typename ConstIteratorRemoveClient::ConstIterator;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using DelegateBackwardConstIterableClient::rbegin;
  using DelegateBackwardConstIterableClient::rend;
  using DelegateBackwardConstIterableClient::crbegin;
  using DelegateBackwardConstIterableClient::crend;

  using ConstIteratorRemoveClient::remove;

  using RandomInsertionClient::insert;
  using RandomInsertionClient::add;
  using RandomInsertionClient::emplace;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::addAllOf;

  using FindUniqueClient::find;

  using ContainsOfCollectionClient::containsAnyOf;
  using ContainsOfCollectionClient::containsAnyNotOf;
  using ContainsOfCollectionClient::containsAllOf;
  using ContainsOfCollectionClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  using FindOfCollectionClient::findOf;
  using FindOfCollectionClient::findFirstOf;
  using FindOfCollectionClient::findLastOf;
  using FindOfCollectionClient::findAllOf;
  using FindOfCollectionClient::findNotOf;
  using FindOfCollectionClient::findFirstNotOf;
  using FindOfCollectionClient::findLastNotOf;
  using FindOfCollectionClient::findAllNotOf;

  using FindOfInitializerListClient::findOf;
  using FindOfInitializerListClient::findFirstOf;
  using FindOfInitializerListClient::findLastOf;
  using FindOfInitializerListClient::findAllOf;
  using FindOfInitializerListClient::findNotOf;
  using FindOfInitializerListClient::findFirstNotOf;
  using FindOfInitializerListClient::findLastNotOf;
  using FindOfInitializerListClient::findAllNotOf;

  using FindByClient::findThat;
  using FindByClient::findFirstThat;
  using FindByClient::findLastThat;
  using FindByClient::findAllThat;

  using RemoveOfCollectionClient::removeOf;
  using RemoveOfCollectionClient::removeFirstOf;
  using RemoveOfCollectionClient::removeLastOf;
  using RemoveOfCollectionClient::removeAllOf;
  using RemoveOfCollectionClient::removeNotOf;
  using RemoveOfCollectionClient::removeFirstNotOf;
  using RemoveOfCollectionClient::removeLastNotOf;
  using RemoveOfCollectionClient::removeAllNotOf;

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

  constexpr TreeSet () noexcept;
  TreeSet (TreeSet const& set) noexcept(false);
  constexpr TreeSet (TreeSet&& set) noexcept;

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > TreeSet (
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __TElementType = __ElementType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > TreeSet (std::initializer_list <__ElementType> const& initializerList) noexcept(false);

  template <typename __IterableType>                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit TreeSet (__IterableType const& iterable) noexcept(false);

  __CDS_cpplang_ConstexprDestructor ~TreeSet () noexcept override;

  auto operator = (TreeSet const& set) noexcept(false) -> TreeSet&;
  auto operator = (TreeSet&& set) noexcept -> TreeSet&;
  auto operator = (std::initializer_list <__ElementType> const& initializerList) noexcept(false) -> TreeSet&;

  template <typename __IterableType>
  auto operator = (__IterableType const& iterable) noexcept(false) -> TreeSet&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      TreeSet const & set
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      TreeSet const & set
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
      __ElementType const& element
  ) const noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;
  auto clear () noexcept -> void override;
  auto remove (__ElementType const& element) noexcept -> bool override;
  
private:
  friend __hidden::__impl::__SetServer <TreeSet, __ElementType>;
  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient <TreeSet, __ElementType, __ElementType const>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient <TreeSet, __ElementType, typename Implementation::__rbt_AbstractConstIterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <TreeSet, typename Implementation::__rbt_ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <TreeSet, typename Implementation::__rbt_ReverseConstIterator>;

  using typename SetBase::__GenericHandler;              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename SetBase::__GenericConstHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Server::__ss_handlers;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ss_constHandlers; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Implementation::__rbt_copyCleared;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_copy;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_move;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_clear;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_get;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_size;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_remove;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_equals;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;
};
}

#include "../../../shared/redBlackTree/impl/RedBlackTreeImpl.hpp"

#include "../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../shared/iterator/impl/RedBlackTreeIterator.hpp"

#include "../../../shared/iterableInternalCommunication/server/impl/SetServer.hpp"
#include "../../../shared/iterableInternalCommunication/server/impl/TreeSetServerDispatcher.hpp"

#include "../../../shared/iterableInternalCommunication/client/primitive/impl/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "treeSet/impl/TreeSetImpl.hpp"
#include "treeSet/impl/TreeSetCTAD.hpp"


#endif // __CDS_TREE_SET_HPP__
