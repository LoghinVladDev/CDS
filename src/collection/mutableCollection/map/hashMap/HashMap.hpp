// NOLINT(llvm-header-guard)
// Created by loghin on 15.01.2021.
//

#ifndef __CDS_HASH_MAP_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_MAP_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Map>                      // NOLINT(llvm-include-order)
#include <CDS/FunctionalInterface>

#include "../../../../shared/Node.hpp"
#include "../../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../../shared/iterator/HashTableIterator.hpp"
#include "../../../../shared/iterator/IteratorGenericDecorator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/MapServerDispatcher.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/hashTable/HashTable.hpp"

#include "../../../../shared/iterableInternalCommunication/server/SetServer.hpp"              // NOLINT(llvm-include-order)
#include "../../../../shared/iterableInternalCommunication/server/MapServer.hpp"

#include "hashMap/HashMapConstructs.hpp"

namespace cds {
template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs HashMap :
    public Map <__KeyType, __ValueType>,
    protected __hidden::__impl::__HashMapServer <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapImplementation <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapDispatcher <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapRandomInsertionClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapIteratorRemoveClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapConstIteratorRemoveClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindOfIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindOfConstIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindOfInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindOfConstInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindByClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindByConstClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindUniqueClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapFindUniqueConstClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapRemoveOfIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapRemoveOfInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapRemoveByClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapGenericStatementsClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapConstGenericStatementsClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapContainsOfIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapContainsOfInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapDelegateForwardIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapDelegateForwardConstIterableClient <__KeyType, __ValueType, __Hasher> {
protected:
  using MapBase                               = Map <__KeyType, __ValueType>;
  using Server                                = __hidden::__impl::__HashMapServer <__KeyType, __ValueType, __Hasher>;
  using Implementation                        = __hidden::__impl::__HashMapImplementation <__KeyType, __ValueType, __Hasher>;
  using Dispatcher                            = __hidden::__impl::__HashMapDispatcher <__KeyType, __ValueType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__HashMapRandomInsertionClient <__KeyType, __ValueType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__HashMapIteratorRemoveClient <__KeyType, __ValueType, __Hasher>;
  using ConstIteratorRemoveClient             = __hidden::__impl::__HashMapConstIteratorRemoveClient <__KeyType, __ValueType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__HashMapFindOfIterableClient <__KeyType, __ValueType, __Hasher>;
  using FindOfConstIterableClient             = __hidden::__impl::__HashMapFindOfConstIterableClient <__KeyType, __ValueType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__HashMapFindOfInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using FindOfConstInitializerListClient      = __hidden::__impl::__HashMapFindOfConstInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__HashMapFindByClient <__KeyType, __ValueType, __Hasher>;
  using FindByConstClient                     = __hidden::__impl::__HashMapFindByConstClient <__KeyType, __ValueType, __Hasher>;
  using FindUniqueClient                      = __hidden::__impl::__HashMapFindUniqueClient <__KeyType, __ValueType, __Hasher>;
  using FindUniqueConstClient                 = __hidden::__impl::__HashMapFindUniqueConstClient <__KeyType, __ValueType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__HashMapRemoveOfIterableClient <__KeyType, __ValueType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__HashMapRemoveOfInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__HashMapRemoveByClient <__KeyType, __ValueType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__HashMapGenericStatementsClient <__KeyType, __ValueType, __Hasher>;
  using ConstGenericStatementsClient          = __hidden::__impl::__HashMapConstGenericStatementsClient <__KeyType, __ValueType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__HashMapContainsOfIterableClient <__KeyType, __ValueType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__HashMapContainsOfInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using DelegateForwardIterableClient         = __hidden::__impl::__HashMapDelegateForwardIterableClient <__KeyType, __ValueType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__HashMapDelegateForwardConstIterableClient <__KeyType, __ValueType, __Hasher>;

  using typename MapBase::AbstractMapProxy;
  using typename MapBase::AbstractKeySetProxy;
  using typename MapBase::AbstractValueMutableCollectionProxy;
  using typename MapBase::AbstractEntryMutableCollectionProxy;

  class KeySetProxy;
  class ValueMutableCollectionProxy;
  class EntryMutableCollectionProxy;

  using MapBase::remove;

public:
  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;

  using ElementType   = typename MapBase::ElementType;
  using EntryType     = typename MapBase::EntryType;
  using KeyType       = typename MapBase::KeyType;
  using ValueType     = typename MapBase::ValueType;

  using DelegateForwardIterableClient::begin;
  using DelegateForwardIterableClient::end;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using IteratorRemoveClient::remove;
  using ConstIteratorRemoveClient::remove;

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

  using ConstGenericStatementsClient::forEach;
  using ConstGenericStatementsClient::some;
  using ConstGenericStatementsClient::atLeast;
  using ConstGenericStatementsClient::atMost;
  using ConstGenericStatementsClient::moreThan;
  using ConstGenericStatementsClient::fewerThan;
  using ConstGenericStatementsClient::count;
  using ConstGenericStatementsClient::any;
  using ConstGenericStatementsClient::all;
  using ConstGenericStatementsClient::none;

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

  using ContainsOfIterableClient::containsAnyOf;
  using ContainsOfIterableClient::containsAnyNotOf;
  using ContainsOfIterableClient::containsAllOf;
  using ContainsOfIterableClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

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

  using FindByConstClient::findThat;
  using FindByConstClient::findFirstThat;
  using FindByConstClient::findLastThat;
  using FindByConstClient::findAllThat;

  using FindOfConstIterableClient::findOf;
  using FindOfConstIterableClient::findFirstOf;
  using FindOfConstIterableClient::findLastOf;
  using FindOfConstIterableClient::findAllOf;
  using FindOfConstIterableClient::findNotOf;
  using FindOfConstIterableClient::findFirstNotOf;
  using FindOfConstIterableClient::findLastNotOf;
  using FindOfConstIterableClient::findAllNotOf;

  using FindOfConstInitializerListClient::findOf;
  using FindOfConstInitializerListClient::findFirstOf;
  using FindOfConstInitializerListClient::findLastOf;
  using FindOfConstInitializerListClient::findAllOf;
  using FindOfConstInitializerListClient::findNotOf;
  using FindOfConstInitializerListClient::findFirstNotOf;
  using FindOfConstInitializerListClient::findLastNotOf;
  using FindOfConstInitializerListClient::findAllNotOf;

  using RandomInsertionClient::add;
  using RandomInsertionClient::addAll;
  using RandomInsertionClient::addAllOf;
  using RandomInsertionClient::insert;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::emplace;

  using FindUniqueClient::find;
  using FindUniqueConstClient::find;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () const noexcept -> KeySetProxy const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () noexcept -> KeySetProxy& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () const noexcept -> ValueMutableCollectionProxy const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () noexcept -> ValueMutableCollectionProxy& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () const noexcept -> EntryMutableCollectionProxy const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () noexcept -> EntryMutableCollectionProxy& override;

  constexpr HashMap () noexcept;
  HashMap (HashMap const& map) noexcept(false);
  constexpr HashMap (HashMap&& map) noexcept;
  __CDS_Explicit constexpr HashMap (__Hasher const& hasher) noexcept;

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashMap (
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false)
  ;
  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashMap (
      __Hasher const&       hasher,
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept (false);

  template <
      typename __TElementType = ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashMap (std::initializer_list <ElementType> const& initializerList) noexcept(false);

  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > HashMap (
      __Hasher const&                             hasher,
      std::initializer_list <ElementType> const&  initializerList
  ) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit HashMap (__IterableType const& iterable) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  HashMap (__Hasher const& hasher, __IterableType const& iterable) noexcept(false);

  ~HashMap () noexcept override;

  auto operator = (HashMap const& map) noexcept(false) -> HashMap&;
  auto operator = (HashMap&& map) noexcept -> HashMap&;
  auto operator = (std::initializer_list <EntryType> const& initializerList) noexcept(false) -> HashMap&;

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (__IterableType const& iterable) noexcept(false) -> HashMap&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      HashMap const& map
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      HashMap const& map
  ) const noexcept -> bool;

  auto clear () noexcept -> void override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;
  auto remove (KeyType const& key) noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto containsKey (
      __KeyType const& key
  ) const noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto containsValue (
      __ValueType const& value
  ) const noexcept -> bool override;

  __CDS_NoDiscard auto sequence () & noexcept -> Sequence <HashMap <__KeyType, __ValueType, __Hasher>>;
  __CDS_NoDiscard auto sequence () && noexcept -> Sequence <HashMap <__KeyType, __ValueType, __Hasher>>;
  __CDS_NoDiscard auto sequence () const & noexcept -> Sequence <HashMap <__KeyType, __ValueType, __Hasher> const>;
  __CDS_NoDiscard auto sequence () const && noexcept -> Sequence <HashMap <__KeyType, __ValueType, __Hasher> const>;

private:
  friend __hidden::__impl::__MapServer <HashMap, EntryType>;

  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <HashMap, Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <HashMap, ConstIterator>;

  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient <HashMap, EntryType, EntryType>;
  friend __hidden::__impl::__LocalIteratorRemovePrimitiveClient <HashMap, EntryType, typename IteratorRemoveClient::Iterator>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient <HashMap, EntryType, typename ConstIteratorRemoveClient::ConstIterator>;

  friend __hidden::__impl::__LocalFindUniqueMutablePrimitiveClient <HashMap, __KeyType, Iterator>;
  friend __hidden::__impl::__LocalFindUniqueImmutablePrimitiveClient <HashMap, __KeyType, ConstIterator>;

  using typename MapBase::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename MapBase::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Server::__ms_handlers;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ms_constHandlers;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Implementation::__ht_clear;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_copy;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_copyCleared; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_move;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_size;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_remove;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_get;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_getConst;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_equals;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_cbegin;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__ht_cend;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  KeySetProxy                 _keySetProxy;
  ValueMutableCollectionProxy _valueMutableCollectionProxy;
  EntryMutableCollectionProxy _entryMutableCollectionProxy;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;

  auto entryAt (
      __KeyType const&  key,
      bool*             pNewElementCreated
  ) noexcept -> EntryType* override;

  __CDS_cpplang_ConstexprOverride auto entryAt (
      __KeyType const& key
  ) const noexcept -> EntryType const* override;
};

} // namespace cds

#include "hashMap/HashMapKeySetProxy.hpp"                                                                  // NOLINT(llvm-include-order)
#include "hashMap/HashMapValueMutableCollectionProxy.hpp"
#include "hashMap/HashMapEntryMutableCollectionProxy.hpp"

#include "../../../../shared/iterator/impl/HashTableIterator.hpp"
#include "../../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../../shared/hashTable/impl/HashTableImpl.hpp"

#include "../../../../shared/iterableInternalCommunication/server/impl/SetServer.hpp"             // NOLINT(llvm-include-order)
#include "../../../../shared/iterableInternalCommunication/server/impl/MapServer.hpp"
#include "../../../../shared/iterableInternalCommunication/server/impl/MapServerDispatcher.hpp"

#include "hashMap/impl/HashMapImpl.hpp"                                                                 // NOLINT(llvm-include-order)
#include "hashMap/impl/HashMapCTAD.hpp"
#include "hashMap/impl/HashMapKeySetProxyImpl.hpp"
#include "hashMap/impl/HashMapValueMutableCollectionProxyImpl.hpp"
#include "hashMap/impl/HashMapEntryMutableCollectionProxyImpl.hpp"

#include "../../../../shared/hashMap/impl/Sequence.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_HASH_MAP_HPP__
