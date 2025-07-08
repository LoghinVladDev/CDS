//
// Created by loghin on 6/14/25.
//

#ifndef CDS_COLLECTION_LINKED_HASH_MAP_BASE_HPP
#define CDS_COLLECTION_LINKED_HASH_MAP_BASE_HPP
#pragma once

#include <cds/functional/Transformer>
#include <cds/memory/Allocator>

#include "../../ds/hashTable/HashTableBase.hpp"
#include "../../ds/map/MapEntry.hpp"
#include "../../ds/linkedList/SingleLinkedListBase.hpp"
#include "../../policy/RehashPolicy.hpp"

namespace cds {
namespace impl {
using functional::Equal;
using functional::Indirection;

using meta::And;
using meta::IsAllocatorSet;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptCopyConstructible;
using meta::IsDefaultConstructible;

template <typename K, typename V, typename H, typename E, typename TA, typename LA> class BaseLinkedHashMap :
    private SingleLinkedListBase<MapEntry<K, V>, Equal<>, LA>,
    private HashTableBase<
        FwdNode<MapEntry<K, V>>*, K, H, TableRehashPolicy<PrimeRehashTable<>>,
        Indirection<FwdNodeDataProjection<MapEntryKeyProjection>>, E, TA
    > {
  using ListBase = SingleLinkedListBase<MapEntry<K, V>, Equal<>, LA>;

  using TableBase = HashTableBase<
      FwdNode<MapEntry<K, V>>*, K, H, TableRehashPolicy<PrimeRehashTable<>>,
      Indirection<FwdNodeDataProjection<MapEntryKeyProjection>>, E, TA
  >;

  using ListBase::emplaceBackRetNode;
  using TableBase::tryEmplace;
  using typename TableBase::Hasher;
  using typename TableBase::RehashPolicy;

public:
  using typename ListBase::Iterator;
  using typename ListBase::ConstIterator;

  using ListBase::begin;
  using ListBase::cbegin;
  using ListBase::end;
  using ListBase::cend;

  using TableBase::size;
  using ListBase::empty;

  CDS_ATTR(2(explicit, constexpr(11))) BaseLinkedHashMap() CDS_ATTR(noexcept(
      And<IsNoexceptConstructible<ListBase>, IsNoexceptConstructible<TableBase>>::value
  )) : ListBase{}, TableBase{} {}

  template <typename AllocSet, typename = EnableIf<IsAllocatorSet<AllocSet>>> CDS_ATTR(2(explicit, constexpr(11)))
  BaseLinkedHashMap(AllocSet&& set) CDS_ATTR(noexcept(
      And<IsNoexceptConstructible<ListBase, AllocSet>, IsNoexceptConstructible<TableBase, AllocSet>>::value
  )) : ListBase{fwd<AllocSet>(set)}, TableBase{fwd<AllocSet>(set)} {}

  CDS_ATTR(2(explicit, constexpr(11))) BaseLinkedHashMap(Hasher const& hasher) CDS_ATTR(noexcept(
      And<IsNoexceptConstructible<ListBase>, IsNoexceptConstructible<TableBase, Hasher const&>>::value
  )) : ListBase{}, TableBase{hasher} {}

  template <typename AllocSet, typename = EnableIf<IsAllocatorSet<AllocSet>>> CDS_ATTR(2(explicit, constexpr(11)))
  BaseLinkedHashMap(Hasher const& hasher, AllocSet&& set) CDS_ATTR(noexcept(And<
      IsNoexceptConstructible<ListBase, AllocSet>,
      IsNoexceptConstructible<TableBase, Hasher const&, AllocSet>
  >::value)) : ListBase{fwd<AllocSet>(set)}, TableBase{hasher, fwd<AllocSet>(set)} {}

  CDS_ATTR(2(explicit, constexpr(11))) BaseLinkedHashMap(RehashPolicy const& rehashPolicy, Hasher const& hasher)
      CDS_ATTR(noexcept(And<
          IsNoexceptConstructible<ListBase>,
          IsNoexceptConstructible<TableBase, RehashPolicy const&, Hasher const&>
      >::value))
      : ListBase{}, TableBase{rehashPolicy, hasher} {}

  template <typename AllocSet, typename = EnableIf<IsAllocatorSet<AllocSet>>> CDS_ATTR(2(explicit, constexpr(11)))
  BaseLinkedHashMap(RehashPolicy const& rehashPolicy, Hasher const& hasher, AllocSet&& set) CDS_ATTR(noexcept(And<
      IsNoexceptConstructible<ListBase, AllocSet>,
      IsNoexceptConstructible<TableBase, RehashPolicy const&, Hasher const&, AllocSet>
  >::value)) : ListBase{fwd<AllocSet>(set)}, TableBase{rehashPolicy, hasher, fwd<AllocSet>(set)} {}

  CDS_ATTR(constexpr(20)) BaseLinkedHashMap(BaseLinkedHashMap const& map) CDS_ATTR(noexcept(And<
      IsNoexceptCopyConstructible<ListBase>, IsNoexceptCopyConstructible<TableBase>
  >::value)) {
    for (auto it = map.begin(); it != map.end(); ++it) {
      auto node = emplaceBackRetNode(it->key(), it->value());
      tryEmplace(it->key(), node);
    }
  }

  CDS_ATTR(constexpr(14)) BaseLinkedHashMap(BaseLinkedHashMap&& map) noexcept :
      ListBase{mv(map)}, TableBase{mv(map)} {}

  CDS_ATTR(constexpr(20)) ~BaseLinkedHashMap() noexcept {
    TableBase::clear();
    ListBase::clear();
  }

  CDS_ATTR(constexpr(20)) auto operator=(BaseLinkedHashMap const& map) noexcept -> BaseLinkedHashMap& {
    if (this == &map) {
      return *this;
    }

    clear();
    for (auto it = map.begin(); it != map.end(); ++it) {
      auto node = emplaceBackRetNode(it->key(), it->value());
      tryEmplace(it->key(), node);
    }

    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(BaseLinkedHashMap&& map) noexcept -> BaseLinkedHashMap& {
    if (this == &map) {
      return *this;
    }

    ListBase::move(mv(map));
    TableBase::move(mv(map));
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void {
    TableBase::clear();
    ListBase::clear();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(K const& key) noexcept -> Iterator {
    auto const tableIt = TableBase::find(key);
    return tableIt == TableBase::end() ? end() : Iterator{*tableIt};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(K const& key) const noexcept -> ConstIterator {
    auto const tableIt = TableBase::find(key);
    return tableIt == TableBase::end() ? end() : ConstIterator{*tableIt};
  }

  CDS_ATTR(2(nodiscard, constexpr(20))) auto remove(K const& key) noexcept -> bool {
    auto tableIt = TableBase::find(key);
    if (tableIt == TableBase::end()) {
      return false;
    }

    auto node = *tableIt;
    auto result = TableBase::remove(tableIt);
    assert(result && "undefined behavior");

    ListBase::remove(FwdNodeIterator<MapEntry<K, V>>{node});
    return true;
  }

  template <typename... Args> CDS_ATTR(constexpr(20)) auto emplace(K const& key, Args&&... args)
      CDS_ATTR(noexcept(noexcept(emplaceBackRetNode(fwd<Args>(args)...)))) -> Tuple<Iterator, bool> {
    auto tableIt = TableBase::tryEmplace(key, nullptr);
    if (tableIt.inserted) {
      auto actualNode = ListBase::emplaceBackRetNode(key, fwd<Args>(args)...);
      *tableIt.iter = actualNode;
      return {Iterator{actualNode}, true};
    }
    return {Iterator{*tableIt.iter}, false};
  }

  template <typename V0 = V, EnableIf<IsDefaultConstructible<V0>> = 0> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto operator[](K const& key) CDS_ATTR(noexcept(noexcept(emplace(key, V{})))) -> V& {
    return get<0>(emplace(key, V{}))->value();
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_COLLECTION_LINKED_HASH_MAP_BASE_HPP
