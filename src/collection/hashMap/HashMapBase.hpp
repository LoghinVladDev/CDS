//
// Created by loghin on 1/9/25.
//

#ifndef CDS_COLLECTION_HASH_MAP_BASE_HPP
#define CDS_COLLECTION_HASH_MAP_BASE_HPP
#pragma once

#include "../../ds/hashTable/HashTableBase.hpp"
#include "../../ds/map/MapEntry.hpp"
#include "../../policy/RehashPolicy.hpp"

namespace cds {
namespace impl {
using meta::IsDefaultConstructible;

template <typename K, typename V, typename H, typename E, typename A> class CDS_ATTR(ebo) BaseHashMap :
    private HashTableBase<
        MapEntry<K, V>, K, H, TableRehashPolicy<PrimeRehashTable<>>,
        MapEntryKeyProjection, E, A
    > {
  using Base = HashTableBase<
      MapEntry<K, V>, K, H, TableRehashPolicy<PrimeRehashTable<>>,
      MapEntryKeyProjection, E, A
  >;

  using Base::tryEmplace;

public:
  using Base::Base;

  using typename Base::Iterator;
  using typename Base::ConstIterator;

  using Base::operator=;
  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::clear;
  using Base::empty;
  using Base::end;
  using Base::find;
  using Base::remove;
  using Base::size;

  template <typename... Args> CDS_ATTR(constexpr(20)) auto emplace(K const& key, Args&&... args)
      CDS_ATTR(noexcept(noexcept(tryEmplace(key, key, fwd<Args>(args)...))))
      -> Tuple<Iterator, bool> {
    auto const res = tryEmplace(key, key, fwd<Args>(args)...);
    return {res.iter, res.inserted};
  }

  template <typename V0 = V, EnableIf<IsDefaultConstructible<V0>> = 0> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto operator[](K const& key) CDS_ATTR(noexcept(noexcept(tryEmplace(key, key, V{})))) -> V& {
    return tryEmplace(key, key, V{}).iter->value();
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_COLLECTION_HASH_MAP_BASE_HPP
