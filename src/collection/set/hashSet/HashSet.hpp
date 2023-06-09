// NOLINT(llvm-header-guard)
// Created by loghin on 6/13/22.
//

#ifndef __CDS_HASH_SET_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_SET_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Set>                  // NOLINT(llvm-include-order)
#include <CDS/FunctionalInterface>

#include "../../../shared/Node.hpp"
#include "../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../shared/iterator/HashTableIterator.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../shared/hashTable/HashTable.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServer.hpp"

#include "hashSet/HashSetConstructs.hpp"

namespace cds {
template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs HashSet :
    public Set <__ElementType>,
    protected __hidden::__impl::__HashSetServer <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetImplementation <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetDispatcher <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetRandomInsertionClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetIteratorRemoveClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetFindOfIterableClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetFindOfInitializerListClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetFindByClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetRemoveOfIterableClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetRemoveOfInitializerListClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetRemoveByClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetGenericStatementsClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetFindUniqueClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetContainsOfIterableClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetContainsOfInitializerListClient <__ElementType, __Hasher>,
    public __hidden::__impl::__HashSetDelegateForwardConstIterableClient <__ElementType, __Hasher> {
protected:
  using SetBase                               = Set <__ElementType>;
  using Server                                = __hidden::__impl::__HashSetServer <__ElementType, __Hasher>;
  using Implementation                        = __hidden::__impl::__HashSetImplementation <__ElementType, __Hasher>;
  using Dispatcher                            = __hidden::__impl::__HashSetDispatcher <__ElementType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__HashSetRandomInsertionClient <__ElementType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__HashSetIteratorRemoveClient <__ElementType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__HashSetFindOfIterableClient <__ElementType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__HashSetFindOfInitializerListClient <__ElementType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__HashSetFindByClient <__ElementType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__HashSetRemoveOfIterableClient <__ElementType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__HashSetRemoveOfInitializerListClient <__ElementType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__HashSetRemoveByClient <__ElementType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__HashSetGenericStatementsClient <__ElementType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__HashSetContainsOfIterableClient <__ElementType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__HashSetContainsOfInitializerListClient <__ElementType, __Hasher>;
  using FindUniqueClient                      = __hidden::__impl::__HashSetFindUniqueClient <__ElementType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__HashSetDelegateForwardConstIterableClient <__ElementType, __Hasher>;
  
public:
  using ElementType   = __ElementType;
  
  using typename DelegateForwardConstIterableClient::ConstIterator;
  
  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

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

  using FindByClient::findThat;
  using FindByClient::findFirstThat;
  using FindByClient::findLastThat;
  using FindByClient::findAllThat;

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

  using ContainsOfIterableClient::containsAnyOf;
  using ContainsOfIterableClient::containsAnyNotOf;
  using ContainsOfIterableClient::containsAllOf;
  using ContainsOfIterableClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  using RandomInsertionClient::add;
  using RandomInsertionClient::addAll;
  using RandomInsertionClient::addAllOf;
  using RandomInsertionClient::insert;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::emplace;

  using IteratorRemoveClient::remove;
  
  using FindUniqueClient::find;

  constexpr HashSet () noexcept;
  HashSet (HashSet const& set) noexcept(false);
  constexpr HashSet (HashSet&& set) noexcept;
  __CDS_Explicit constexpr HashSet (__Hasher const& hasher) noexcept;

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashSet (
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashSet (
      __Hasher const&       hasher,
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept (false);

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashSet (std::initializer_list <__ElementType> const& initializerList) noexcept(false);

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashSet (
      __Hasher const&                               hasher,
      std::initializer_list <__ElementType> const&  initializerList
  ) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit HashSet (__IterableType const &iterable) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  HashSet (
      __Hasher const&       hasher,
      __IterableType const& iterable
  ) noexcept(false);

  ~HashSet () noexcept override;

  auto operator = (HashSet const& set) noexcept(false) -> HashSet&;
  auto operator = (HashSet&& set) noexcept -> HashSet&;
  auto operator = (std::initializer_list <__ElementType> const& initializerList) noexcept(false) -> HashSet&;

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (__IterableType const& iterable) noexcept(false) -> HashSet&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      HashSet const& set
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      HashSet const& set
  ) const noexcept -> bool;

  auto clear () noexcept -> void override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

  auto remove (__ElementType const& element) noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
      __ElementType const& element
  ) const noexcept -> bool override;

  __CDS_NoDiscard auto sequence ()& noexcept -> Sequence < HashSet <__ElementType, __Hasher> >;

  __CDS_NoDiscard auto sequence ()&& noexcept -> Sequence < HashSet <__ElementType, __Hasher> >;

  __CDS_NoDiscard auto sequence () const& noexcept -> Sequence < HashSet <__ElementType, __Hasher> const >;

  __CDS_NoDiscard auto sequence () const&& noexcept -> Sequence < HashSet <__ElementType, __Hasher> const >;
  
protected:
  using typename SetBase::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename SetBase::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

private:
  friend __hidden::__impl::__SetServer <HashSet, __ElementType>;
  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient <HashSet, __ElementType, __ElementType const>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient <HashSet, __ElementType, typename Implementation::__ht_ConstIterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <HashSet, typename Implementation::__ht_ConstIterator>;

  using IteratorRemoveClient::removeAll;

  using Server::__ss_handlers;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ss_constHandlers; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Implementation::__ht_clear;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_copyCleared; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_copy;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_move;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_size;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_remove;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_getConst;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_equals;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;
};
} // namespace cds

#include "../../../shared/hashTable/impl/HashTableImpl.hpp"

#include "../../../shared/iterator/impl/HashTableIteratorImpl.hpp"

#include "../../../shared/iterableInternalCommunication/server/impl/SetServerImpl.hpp"
#include "../../../shared/iterableInternalCommunication/server/impl/SetServerDispatcherImpl.hpp"

#include "../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "hashSet/impl/HashSetImpl.hpp"                                                                                     // NOLINT(llvm-include-order)
#include "hashSet/impl/HashSetCTAD.hpp"

#include "../../../shared/hashSet/impl/Sequence.hpp"

#include "../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_HASH_SET_HPP__
