// NOLINT(llvm-header-guard)
// Created by loghin on 27/07/22.
//

#ifndef __CDS_LINKED_HASH_MAP_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_MAP_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Map>                  // NOLINT(llvm-include-order)
#include <CDS/FunctionalInterface>

#include "../../../../shared/Node.hpp"
#include "../../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../../shared/iterator/HashTableIterator.hpp"
#include "../../../../shared/iterator/NodeIterator.hpp"                                         // NOLINT(llvm-include-order)
#include "../../../../shared/iterator/IteratorGenericDecorator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/MapServerDispatcher.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/hashTable/HashTable.hpp"
#include "../../../../shared/linkedList/SingleLinkedList.hpp"

#include "../../../../shared/iterableInternalCommunication/server/SetServer.hpp"              // NOLINT(llvm-include-order)
#include "../../../../shared/iterableInternalCommunication/server/MapServer.hpp"

#include "linkedHashMap/LinkedHashMapConstructs.hpp"

namespace cds {

template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs LinkedHashMap :
    public Map <__KeyType, __ValueType>,
    protected __hidden::__impl::__LinkedHashMapServer <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapHashTableImplementation <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapLinkedListImplementation <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapRandomInsertionClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapIteratorRemoveClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapConstIteratorRemoveClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindOfIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindOfConstIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindOfInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindOfConstInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindByClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindByConstClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindUniqueClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapFindUniqueConstClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapRemoveOfIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapRemoveOfInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapRemoveByClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapGenericStatementsClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapConstGenericStatementsClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapContainsOfIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapContainsOfInitializerListClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapDelegateForwardIterableClient <__KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapDelegateForwardConstIterableClient <__KeyType, __ValueType, __Hasher> {
protected:
  using MapBase                               = Map <__KeyType, __ValueType>;
  using Server                                = __hidden::__impl::__LinkedHashMapServer <__KeyType, __ValueType, __Hasher>;
  using HashTableImplementation               = __hidden::__impl::__LinkedHashMapHashTableImplementation <__KeyType, __ValueType, __Hasher>;
  using LinkedListImplementation              = __hidden::__impl::__LinkedHashMapLinkedListImplementation <__KeyType, __ValueType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__LinkedHashMapRandomInsertionClient <__KeyType, __ValueType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__LinkedHashMapIteratorRemoveClient <__KeyType, __ValueType, __Hasher>;
  using ConstIteratorRemoveClient             = __hidden::__impl::__LinkedHashMapConstIteratorRemoveClient <__KeyType, __ValueType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__LinkedHashMapFindOfIterableClient <__KeyType, __ValueType, __Hasher>;
  using FindOfConstIterableClient             = __hidden::__impl::__LinkedHashMapFindOfConstIterableClient <__KeyType, __ValueType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__LinkedHashMapFindOfInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using FindOfConstInitializerListClient      = __hidden::__impl::__LinkedHashMapFindOfConstInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__LinkedHashMapFindByClient <__KeyType, __ValueType, __Hasher>;
  using FindByConstClient                     = __hidden::__impl::__LinkedHashMapFindByConstClient <__KeyType, __ValueType, __Hasher>;
  using FindUniqueClient                      = __hidden::__impl::__LinkedHashMapFindUniqueClient <__KeyType, __ValueType, __Hasher>;
  using FindUniqueConstClient                 = __hidden::__impl::__LinkedHashMapFindUniqueConstClient <__KeyType, __ValueType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__LinkedHashMapRemoveOfIterableClient <__KeyType, __ValueType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__LinkedHashMapRemoveOfInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__LinkedHashMapRemoveByClient <__KeyType, __ValueType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__LinkedHashMapGenericStatementsClient <__KeyType, __ValueType, __Hasher>;
  using ConstGenericStatementsClient          = __hidden::__impl::__LinkedHashMapConstGenericStatementsClient <__KeyType, __ValueType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__LinkedHashMapContainsOfIterableClient <__KeyType, __ValueType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__LinkedHashMapContainsOfInitializerListClient <__KeyType, __ValueType, __Hasher>;
  using DelegateForwardIterableClient         = __hidden::__impl::__LinkedHashMapDelegateForwardIterableClient <__KeyType, __ValueType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__LinkedHashMapDelegateForwardConstIterableClient <__KeyType, __ValueType, __Hasher>;

  using typename MapBase::AbstractMapProxy;
  using typename MapBase::AbstractKeySetProxy;
  using typename MapBase::AbstractValueMutableCollectionProxy;
  using typename MapBase::AbstractEntryMutableCollectionProxy;

  class KeySetProxy;
  class ValueMutableCollectionProxy;
  class EntryMutableCollectionProxy;

  using MapBase::remove;

public:
  using ElementType   = typename MapBase::ElementType;
  using EntryType     = typename MapBase::EntryType;
  using KeyType       = typename MapBase::KeyType;
  using ValueType     = typename MapBase::ValueType;
  using Iterator      = __hidden::__impl::__LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>;
  using ConstIterator = __hidden::__impl::__LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>;

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

  constexpr LinkedHashMap () noexcept;
  LinkedHashMap (LinkedHashMap const& map) noexcept(false);
  constexpr LinkedHashMap (LinkedHashMap&& map) noexcept;
  __CDS_Explicit constexpr LinkedHashMap (__Hasher const& hasher) noexcept;

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashMap (
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashMap (
      __Hasher const&       hasher,
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __TElementType = ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashMap (
      std::initializer_list <ElementType> const& initializerList
  ) noexcept(false);

  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > LinkedHashMap (
      __Hasher const&                             hasher,
      std::initializer_list <ElementType> const&  initializerList
  ) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit LinkedHashMap (
      __IterableType const& iterable
  ) noexcept(false);

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  LinkedHashMap (
      __Hasher const&       hasher,
      __IterableType const& iterable
  ) noexcept(false);

  ~LinkedHashMap () noexcept override;

  auto operator = (LinkedHashMap const& map) noexcept(false) -> LinkedHashMap&;
  auto operator = (LinkedHashMap&& map) noexcept -> LinkedHashMap&;
  auto operator = (std::initializer_list <EntryType> const& initializerList) noexcept(false) -> LinkedHashMap&;

  template <typename __IterableType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (
      __IterableType const& iterable
  ) noexcept(false) -> LinkedHashMap&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      LinkedHashMap const& map
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      LinkedHashMap const& map
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

  __CDS_NoDiscard auto sequence () & noexcept -> Sequence <LinkedHashMap <__KeyType, __ValueType, __Hasher>>;
  __CDS_NoDiscard auto sequence () && noexcept -> Sequence <LinkedHashMap <__KeyType, __ValueType, __Hasher>>;
  __CDS_NoDiscard auto sequence () const& noexcept -> Sequence <LinkedHashMap <__KeyType, __ValueType, __Hasher> const>;
  __CDS_NoDiscard auto sequence () const&& noexcept -> Sequence <LinkedHashMap <__KeyType, __ValueType, __Hasher> const>;

private:
  friend __hidden::__impl::__MapServer <LinkedHashMap, EntryType>;

  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <LinkedHashMap, Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <LinkedHashMap, ConstIterator>;

  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient <LinkedHashMap, EntryType, EntryType>;
  friend __hidden::__impl::__LocalIteratorRemovePrimitiveClient <LinkedHashMap, EntryType, typename IteratorRemoveClient::Iterator>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient <LinkedHashMap, EntryType, typename ConstIteratorRemoveClient::ConstIterator>;

  friend __hidden::__impl::__LocalFindUniqueMutablePrimitiveClient <LinkedHashMap, __KeyType, Iterator>;
  friend __hidden::__impl::__LocalFindUniqueImmutablePrimitiveClient <LinkedHashMap, __KeyType, ConstIterator>;

  using typename MapBase::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename MapBase::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using IteratorRemoveClient::removeAll;

  using Server::__ms_handlers;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ms_constHandlers;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using HashTableImplementation::__ht_clear;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_size;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_remove;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_getConst;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_move;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using HashTableImplementation::__ht_get;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using LinkedListImplementation::__sll_clear;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_remove;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_equals;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_move;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_removeIf;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_cbegin;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_cend;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_newBack;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using LinkedListImplementation::__sll_backNode;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  KeySetProxy                 _keySetProxy;
  ValueMutableCollectionProxy _valueMutableCollectionProxy;
  EntryMutableCollectionProxy _entryMutableCollectionProxy;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;

  __CDS_NoDiscard static auto __begin (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard static auto __end (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard static auto __cbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard static auto __cend (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard constexpr static auto __cbeginLocal (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap const* pObject
  ) noexcept -> ConstIterator;

  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap*    pObject,
      EntryType const*  pReferenceElement,
      bool*             pNewElementCreated
  ) noexcept -> EntryType*;

  static auto __remove ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap*  pObject,
      Iterator const* pIterator
  ) noexcept -> bool;

  static auto __removeConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap*        pObject,
      ConstIterator const*  pIterator
  ) noexcept -> bool;

  static auto __removeArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap*          pObject,
      Iterator const* const*  ppIterators,
      Size                    iteratorArraySize
  ) noexcept -> Size;

  static auto __removeConstArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap*              pObject,
      ConstIterator const* const* ppIterators,
      Size                        iteratorArraySize
  ) noexcept -> Size;

  __CDS_MaybeUnused static auto __find ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap*    pObject,
      __KeyType const&  element
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  static auto __findConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap const*  pObject,
      __KeyType const&      element
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_cpplang_NonConstConstexprMemberFunction static auto __findLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap*    pObject,
      __KeyType const&  element
  ) noexcept -> Iterator;

  __CDS_cpplang_ConstexprConditioned static auto __findConstLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      LinkedHashMap const*  pObject,
      __KeyType const&      element
  ) noexcept -> ConstIterator;

  auto entryAt (
      __KeyType const&  key,
      bool*             pNewElementCreated
  ) noexcept -> EntryType* override;

  __CDS_cpplang_ConstexprOverride auto entryAt (
      __KeyType const& key
  ) const noexcept -> EntryType const* override;
};
} // namespace cds

#include "linkedHashMap/LinkedHashMapKeySetProxy.hpp"                                                            // NOLINT(llvm-include-order)
#include "linkedHashMap/LinkedHashMapValueMutableCollectionProxy.hpp"
#include "linkedHashMap/LinkedHashMapEntryMutableCollectionProxy.hpp"

#include "../../../../shared/hashTable/impl/HashTableImpl.hpp"
#include "../../../../shared/linkedList/impl/SingleLinkedListImpl.hpp"

#include "../../../../shared/iterator/impl/HashTableIteratorImpl.hpp"
#include "../../../../shared/iterator/impl/NodeIterator.hpp"                                        // NOLINT(llvm-include-order)
#include "../../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/impl/MapServerImpl.hpp"
#include "../../../../shared/iterableInternalCommunication/server/impl/SetServerImpl.hpp"             // NOLINT(llvm-include-order)
#include "../../../../shared/iterableInternalCommunication/server/impl/MapServerDispatcherImpl.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../../shared/linkedHashMap/impl/Sequence.hpp"

#include "linkedHashMap/impl/LinkedHashMapImpl.hpp"                                                     // NOLINT(llvm-include-order)
#include "linkedHashMap/impl/LinkedHashMapCTAD.hpp"
#include "linkedHashMap/impl/LinkedHashMapKeySetProxyImpl.hpp"
#include "linkedHashMap/impl/LinkedHashMapValueMutableCollectionProxyImpl.hpp"
#include "linkedHashMap/impl/LinkedHashMapEntryMutableCollectionProxyImpl.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_LINKED_HASH_MAP_HPP__
