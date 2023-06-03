// NOLINT(llvm-header-guard)
// Created by loghin on 6/24/22.
// 

#ifndef __CDS_LINKED_HASH_SET_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_SET_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Set>                  // NOLINT(llvm-include-order)
#include <CDS/FunctionalInterface>

#include "../../../shared/Node.hpp"
#include "../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../shared/iterator/HashTableIterator.hpp"
#include "../../../shared/iterator/NodeIterator.hpp"                    // NOLINT(llvm-include-order)
#include "../../../shared/iterator/IteratorGenericDecorator.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../shared/hashTable/HashTable.hpp"
#include "../../../shared/linkedList/SingleLinkedList.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServer.hpp"

#include "linkedHashSet/LinkedHashSetConstructs.hpp"

namespace cds {
template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs LinkedHashSet :
    public Set <__ElementType>,
    protected __hidden::__impl::__LinkedHashSetServer <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetHashTableImplementation <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetLinkedListImplementation <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetRandomInsertionClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetIteratorRemoveClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetFindOfIterableClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetFindOfInitializerListClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetFindByClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetRemoveOfIterableClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetRemoveOfInitializerListClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetRemoveByClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetGenericStatementsClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetFindUniqueClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetContainsOfIterableClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetContainsOfInitializerListClient <__ElementType, __Hasher>,
    public __hidden::__impl::__LinkedHashSetDelegateForwardConstIterableClient <__ElementType, __Hasher> {
protected:
  using SetBase                               = Set <__ElementType>;
  using Server                                = __hidden::__impl::__LinkedHashSetServer <__ElementType, __Hasher>;
  using HashTableImplementation               = __hidden::__impl::__LinkedHashSetHashTableImplementation <__ElementType, __Hasher>;
  using LinkedListImplementation              = __hidden::__impl::__LinkedHashSetLinkedListImplementation <__ElementType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__LinkedHashSetRandomInsertionClient <__ElementType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__LinkedHashSetIteratorRemoveClient <__ElementType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__LinkedHashSetFindOfIterableClient <__ElementType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__LinkedHashSetFindOfInitializerListClient <__ElementType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__LinkedHashSetFindByClient <__ElementType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__LinkedHashSetRemoveOfIterableClient <__ElementType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__LinkedHashSetRemoveOfInitializerListClient <__ElementType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__LinkedHashSetRemoveByClient <__ElementType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__LinkedHashSetGenericStatementsClient <__ElementType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__LinkedHashSetContainsOfIterableClient <__ElementType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__LinkedHashSetContainsOfInitializerListClient <__ElementType, __Hasher>;
  using FindUniqueClient                      = __hidden::__impl::__LinkedHashSetFindUniqueClient <__ElementType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__LinkedHashSetDelegateForwardConstIterableClient <__ElementType, __Hasher>;

public:
  using ConstIterator = __hidden::__impl::__LinkedHashSetIterator <__ElementType, __Hasher>;
  using ElementType   = __ElementType;
  
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

  constexpr LinkedHashSet () noexcept;
  LinkedHashSet (LinkedHashSet const& set) noexcept(false);
  constexpr LinkedHashSet (LinkedHashSet&& set) noexcept;
  __CDS_Explicit constexpr LinkedHashSet (__Hasher const& hasher) noexcept;

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashSet (
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashSet (
      __Hasher const&       hasher,
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashSet (std::initializer_list <__ElementType> const& initializerList) noexcept(false);

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashSet (
      __Hasher const&                               hasher,
      std::initializer_list <__ElementType> const&  initializerList
  ) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit LinkedHashSet (
      __IterableType const& iterable
  ) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  LinkedHashSet (
      __Hasher const&       hasher,
      __IterableType const& iterable
  ) noexcept(false);

  ~LinkedHashSet () noexcept override;

  auto operator = (LinkedHashSet const& set) noexcept(false) -> LinkedHashSet&;
  auto operator = (LinkedHashSet&& set) noexcept -> LinkedHashSet&;
  auto operator = (std::initializer_list <__ElementType> const& initializerList) noexcept(false) -> LinkedHashSet&;

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (__IterableType const& iterable) noexcept(false) -> LinkedHashSet&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      LinkedHashSet const& set
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      LinkedHashSet const& set
  ) const noexcept -> bool;

  auto clear () noexcept -> void override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;
  auto remove (__ElementType const& element) noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
      __ElementType const& element
  ) const noexcept -> bool override;

  __CDS_NoDiscard auto sequence () & noexcept -> Sequence <LinkedHashSet <__ElementType, __Hasher>>;
  __CDS_NoDiscard auto sequence () && noexcept -> Sequence <LinkedHashSet <__ElementType, __Hasher>>;
  __CDS_NoDiscard auto sequence () const& noexcept -> Sequence <LinkedHashSet <__ElementType, __Hasher> const>;
  __CDS_NoDiscard auto sequence () const&& noexcept -> Sequence <LinkedHashSet <__ElementType, __Hasher> const>;

private:
  friend Server;

  using typename SetBase::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename SetBase::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  friend __hidden::__impl::__SetServer <LinkedHashSet, __ElementType>;
  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient <LinkedHashSet, __ElementType, __ElementType const>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient <LinkedHashSet, __ElementType, typename LinkedListImplementation::__sll_ConstIterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <LinkedHashSet, typename LinkedListImplementation::__sll_ConstIterator>;

  using IteratorRemoveClient::removeAll;

  using Server::__ss_handlers;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ss_constHandlers;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using HashTableImplementation::__ht_clear;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_size;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_removeGetPtr; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_getConst;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_equals;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using LinkedListImplementation::__sll_clear;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_remove;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard static auto __cbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ElementType const>*;

  __CDS_NoDiscard static auto __cend (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ElementType const>*;

  __CDS_NoDiscard constexpr static auto __cbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet const* pObject
  ) noexcept -> ConstIterator;

  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet*        pObject,
      __ElementType const*  pReferenceElement,
      bool*                 pNewElementCreated
  ) noexcept -> __ElementType*;

  static auto __removeConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet*        pObject,
      ConstIterator const*  pIterator
  ) noexcept -> bool;

  static auto __removeConstArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet*              pObject,
      ConstIterator const* const* ppIterators,
      Size                        iteratorArraySize
  ) noexcept -> Size;

  static auto __findConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet const* pObject,
      __ElementType const& element
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ElementType const>*;

  __CDS_cpplang_NonConstConstexprMemberFunction auto __findConstLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashSet const* pObject,
      __ElementType const& element
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;
};

} // namespace cds

#include "../../../shared/hashTable/impl/HashTableImpl.hpp"
#include "../../../shared/linkedList/impl/SingleLinkedListImpl.hpp"

#include "../../../shared/iterator/impl/HashTableIterator.hpp"
#include "../../../shared/iterator/impl/NodeIterator.hpp"                                                   // NOLINT(llvm-include-order)
#include "../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../shared/iterableInternalCommunication/server/impl/SetServer.hpp"
#include "../../../shared/iterableInternalCommunication/server/impl/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../shared/linkedHashSet/impl/Sequence.hpp"

#include "linkedHashSet/impl/LinkedHashSetImpl.hpp"                                                             // NOLINT(llvm-include-order)
#include "linkedHashSet/impl/LinkedHashSetCTAD.hpp"

#include "../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_LINKED_HASH_SET_HPP__
