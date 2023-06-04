//
// Created by stefan on 26.09.2022.
//

#ifndef __CDS_TREE_MAP_HPP__     // NOLINT(llvm-header-guard)
#define __CDS_TREE_MAP_HPP__     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Map>

#include "../../../../shared/Node.hpp"
#include "../../../../shared/impl/generalPredicates.hpp"

#include "../../../../shared/iterableInternalCommunication/server/TreeMapServerDispatcher.hpp"

#include "../../../../shared/iterator/RedBlackTreeIterator.hpp"

#include "../../../../shared/iterableInternalCommunication/client/primitive/DelegateBackwardIterablePrimitiveClient.hpp"
#include "../../../../shared/iterableInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "../../../../shared/iterator/IteratorGenericDecorator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/redBlackTree/RedBlackTree.hpp"

#include "../../../../shared/iterableInternalCommunication/server/MapServer.hpp"
#include "../../../../shared/iterableInternalCommunication/server/SetServer.hpp"

#include "treeMap/TreeMapConstructs.hpp"

namespace cds {

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs TreeMap :
    public cds::Map <__KeyType, __ValueType>,
    protected __hidden::__impl::__TreeMapServer <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapImplementation <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapDispatcher <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapDelegateForwardIterableClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapDelegateBackwardIterableClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapDelegateForwardConstIterableClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapDelegateBackwardConstIterableClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapIteratorRemoveClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapConstIteratorRemoveClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindUniqueClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindUniqueConstClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapRandomInsertionClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapContainsOfCollectionClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapContainsOfInitializerListClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindByClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindByConstClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindOfCollectionClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindOfInitializerListClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindOfConstCollectionClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapFindOfConstInitializerListClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapGenericStatementsClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapConstGenericStatementsClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapRemoveByClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapRemoveOfCollectionClient <__KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapRemoveOfInitializerListClient <__KeyType, __ValueType, __Comparator> {
protected:
  using MapBase                             = Map <__KeyType, __ValueType>;
  using Server                              = __hidden::__impl::__TreeMapServer <__KeyType, __ValueType, __Comparator>;
  using Implementation                      = __hidden::__impl::__TreeMapImplementation <__KeyType, __ValueType, __Comparator>;
  using Dispatcher                          = __hidden::__impl::__TreeMapDispatcher <__KeyType, __ValueType, __Comparator>;
  using DelegateForwardIterableClient       = __hidden::__impl::__TreeMapDelegateForwardIterableClient <__KeyType, __ValueType, __Comparator>;
  using DelegateBackwardIterableClient      = __hidden::__impl::__TreeMapDelegateBackwardIterableClient <__KeyType, __ValueType, __Comparator>;
  using DelegateForwardConstIterableClient  = __hidden::__impl::__TreeMapDelegateForwardConstIterableClient <__KeyType, __ValueType, __Comparator>;
  using DelegateBackwardConstIterableClient = __hidden::__impl::__TreeMapDelegateBackwardConstIterableClient <__KeyType, __ValueType, __Comparator>;
  using IteratorRemoveClient                = __hidden::__impl::__TreeMapIteratorRemoveClient <__KeyType, __ValueType, __Comparator>;
  using ConstIteratorRemoveClient           = __hidden::__impl::__TreeMapConstIteratorRemoveClient <__KeyType, __ValueType, __Comparator>;
  using FindUniqueClient                    = __hidden::__impl::__TreeMapFindUniqueClient <__KeyType, __ValueType, __Comparator>;
  using FindUniqueConstClient               = __hidden::__impl::__TreeMapFindUniqueConstClient <__KeyType, __ValueType, __Comparator>;
  using RandomInsertionClient               = __hidden::__impl::__TreeMapRandomInsertionClient <__KeyType, __ValueType, __Comparator>;
  using ContainsOfCollectionClient          = __hidden::__impl::__TreeMapContainsOfCollectionClient <__KeyType, __ValueType, __Comparator>;
  using ContainsOfInitializerListClient     = __hidden::__impl::__TreeMapContainsOfInitializerListClient <__KeyType, __ValueType, __Comparator>;
  using FindByClient                        = __hidden::__impl::__TreeMapFindByClient <__KeyType, __ValueType, __Comparator>;
  using FindByConstClient                   = __hidden::__impl::__TreeMapFindByConstClient <__KeyType, __ValueType, __Comparator>;
  using FindOfCollectionClient              = __hidden::__impl::__TreeMapFindOfCollectionClient <__KeyType, __ValueType, __Comparator>;
  using FindOfInitializerListClient         = __hidden::__impl::__TreeMapFindOfInitializerListClient <__KeyType, __ValueType, __Comparator>;
  using FindOfConstCollectionClient         = __hidden::__impl::__TreeMapFindOfConstCollectionClient <__KeyType, __ValueType, __Comparator>;
  using FindOfConstInitializerListClient    = __hidden::__impl::__TreeMapFindOfConstInitializerListClient <__KeyType, __ValueType, __Comparator>;
  using GenericStatementsClient             = __hidden::__impl::__TreeMapGenericStatementsClient <__KeyType, __ValueType, __Comparator>;
  using ConstGenericStatementsClient        = __hidden::__impl::__TreeMapConstGenericStatementsClient <__KeyType, __ValueType, __Comparator>;
  using RemoveByClient                      = __hidden::__impl::__TreeMapRemoveByClient <__KeyType, __ValueType, __Comparator>;
  using RemoveOfCollectionClient            = __hidden::__impl::__TreeMapRemoveOfCollectionClient <__KeyType, __ValueType, __Comparator>;
  using RemoveOfInitializerListClient       = __hidden::__impl::__TreeMapRemoveOfInitializerListClient <__KeyType, __ValueType, __Comparator>;

  using typename MapBase::AbstractMapProxy;
  using typename MapBase::AbstractKeySetProxy;
  using typename MapBase::AbstractValueMutableCollectionProxy;
  using typename MapBase::AbstractEntryMutableCollectionProxy;

  class KeySetProxy;
  class ValueMutableCollectionProxy;
  class EntryMutableCollectionProxy;

public:
  using __ElementType = typename MapBase::ElementType;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using EntryType     = typename MapBase::EntryType;

  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;
  using typename DelegateBackwardIterableClient::ReverseIterator;
  using typename DelegateBackwardConstIterableClient::ConstReverseIterator;

  using DelegateForwardIterableClient::begin;
  using DelegateForwardIterableClient::end;

  using DelegateBackwardIterableClient::rbegin;
  using DelegateBackwardIterableClient::rend;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using DelegateBackwardConstIterableClient::rbegin;
  using DelegateBackwardConstIterableClient::rend;
  using DelegateBackwardConstIterableClient::crbegin;
  using DelegateBackwardConstIterableClient::crend;

  using IteratorRemoveClient::remove;
  using IteratorRemoveClient::removeAll;

  using ConstIteratorRemoveClient::remove;
  using ConstIteratorRemoveClient::removeAll;

  using RandomInsertionClient::insert;
  using RandomInsertionClient::add;
  using RandomInsertionClient::emplace;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::addAllOf;

  using FindUniqueClient::find;

  using FindUniqueConstClient::find;

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

  using FindOfConstCollectionClient::findOf;
  using FindOfConstCollectionClient::findFirstOf;
  using FindOfConstCollectionClient::findLastOf;
  using FindOfConstCollectionClient::findAllOf;
  using FindOfConstCollectionClient::findNotOf;
  using FindOfConstCollectionClient::findFirstNotOf;
  using FindOfConstCollectionClient::findLastNotOf;
  using FindOfConstCollectionClient::findAllNotOf;

  using FindOfConstInitializerListClient::findOf;
  using FindOfConstInitializerListClient::findFirstOf;
  using FindOfConstInitializerListClient::findLastOf;
  using FindOfConstInitializerListClient::findAllOf;
  using FindOfConstInitializerListClient::findNotOf;
  using FindOfConstInitializerListClient::findFirstNotOf;
  using FindOfConstInitializerListClient::findLastNotOf;
  using FindOfConstInitializerListClient::findAllNotOf;

  using FindByClient::findThat;
  using FindByClient::findFirstThat;
  using FindByClient::findLastThat;
  using FindByClient::findAllThat;

  using FindByConstClient::findThat;
  using FindByConstClient::findFirstThat;
  using FindByConstClient::findLastThat;
  using FindByConstClient::findAllThat;

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

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () noexcept -> KeySetProxy& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () const noexcept -> KeySetProxy const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () const noexcept -> ValueMutableCollectionProxy const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () noexcept -> ValueMutableCollectionProxy& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () const noexcept -> EntryMutableCollectionProxy const& override;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () noexcept -> EntryMutableCollectionProxy& override;

  constexpr TreeMap() noexcept;
  TreeMap (TreeMap const& map) noexcept(false);
  constexpr TreeMap (TreeMap&& map) noexcept;

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > TreeMap (
      __IteratorType const& begin,
      __IteratorType const& end,
      Size                  count = 0u
  ) noexcept(false);

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > TreeMap (std::initializer_list <__ElementType> const& initializer_list) noexcept(false);

  template <typename __IterableType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit TreeMap (__IterableType const& iterable) noexcept(false);
  __CDS_cpplang_ConstexprDestructor ~TreeMap () noexcept override;

  auto operator = (TreeMap const& map) noexcept(false) -> TreeMap&;
  auto operator = (TreeMap&& map) noexcept -> TreeMap&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      TreeMap const& map
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      TreeMap const& map
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

  auto clear () noexcept -> void override;
  auto remove (__KeyType const& key) noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto containsKey (
      __KeyType const& key
  ) const noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto containsValue (
      __ValueType const& value
  ) const noexcept -> bool override;

private:
  friend __hidden::__impl::__MapServer <TreeMap, EntryType>;

  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <TreeMap, Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <TreeMap, ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardIterablePrimitiveClient <TreeMap, ReverseIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <TreeMap, ConstReverseIterator>;

  friend __hidden::__impl::__LocalRandomInsertionPrimitiveClient <TreeMap, EntryType, EntryType>;
  friend __hidden::__impl::__LocalIteratorRemovePrimitiveClient <TreeMap, EntryType, typename IteratorRemoveClient::Iterator>;
  friend __hidden::__impl::__LocalConstIteratorRemovePrimitiveClient <TreeMap, EntryType, typename ConstIteratorRemoveClient::ConstIterator>;

  friend __hidden::__impl::__LocalFindUniqueMutablePrimitiveClient <TreeMap, __KeyType, Iterator>;
  friend __hidden::__impl::__LocalFindUniqueImmutablePrimitiveClient <TreeMap, __KeyType, ConstIterator>;

  using typename MapBase::__GenericHandler;              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename MapBase::__GenericConstHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Server::__ms_handlers;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ms_constHandlers; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Implementation::__rbt_clear;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_copy;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_copyCleared;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_move;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_size;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_remove;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_get;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_cbegin;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_cend;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__rbt_equals;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  KeySetProxy                 _keySetProxy;
  ValueMutableCollectionProxy _valueMutableCollectionProxy;
  EntryMutableCollectionProxy _entryMutableCollectionProxy;

  auto entryAt (
      __KeyType const&  key,
      bool*             pNewElementCreated
  ) noexcept -> EntryType* override;

  auto entryAt (
      __KeyType const& key
  ) const noexcept -> EntryType const* override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;
};
} // namespace cds

#include "treeMap/TreeMapKeySetProxy.hpp"
#include "treeMap/TreeMapValueMutableCollectionProxy.hpp"
#include "treeMap/TreeMapEntryMutableCollectionProxy.hpp"


#include "../../../../shared/redBlackTree/impl/RedBlackTreeImpl.hpp"

#include "../../../../shared/iterableInternalCommunication/server/impl/MapServer.hpp"
#include "../../../../shared/iterableInternalCommunication/server/impl/SetServer.hpp"

#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"
#include "../../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../../shared/iterableInternalCommunication/client/primitive/impl/DelegateBackwardIterablePrimitiveClient.hpp"
#include "../../../../shared/iterableInternalCommunication/client/primitive/impl/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "../../../../shared/iterator/impl/RedBlackTreeIterator.hpp"

#include "../../../../shared/iterableInternalCommunication/server/impl/TreeMapServerDispatcher.hpp"

#include "treeMap/impl/TreeMapImpl.hpp"
#include "treeMap/impl/TreeMapCTAD.hpp"

#include "treeMap/impl/TreeMapKeySetProxyImpl.hpp"
#include "treeMap/impl/TreeMapValueMutableCollectionProxyImpl.hpp"
#include "treeMap/impl/TreeMapEntryMutableCollectionProxyImpl.hpp"

#endif // __CDS_TREE_MAP_HPP__
