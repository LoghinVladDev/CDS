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
template <typename K, typename V> struct MapEntryKeyProjector {
  [[nodiscard]] constexpr auto operator()(MapEntry<K, V> const& entry) const noexcept -> K const& {
    return entry.key();
  }
};

template <typename K, typename V, typename H, typename E, typename A> class BaseHashMap :
    private HashTableBase<
        MapEntry<K, V>, K, H, TableRehashPolicy<PrimeRehashTable<>>,
        MapEntryKeyProjector<K, V>, E, A
    > {
  using Base = HashTableBase<
      MapEntry<K, V>, K, H, TableRehashPolicy<PrimeRehashTable<>>,
      MapEntryKeyProjector<K, V>, E, A
  >;

  using Base::tryEmplace;

public:
  using Base::Base;
  using Base::operator=;
  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::clear;
  using Base::empty;
  using Base::end;
  using Base::size;

  // template <typename... Args> CDS_ATTR(constexpr(20)) auto emplace(Args&&... args)
  //     CDS_ATTR(noexcept(noexcept(tryEmplace(fwd<Args>(args)...))))
  //     -> Tuple<>
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_COLLECTION_HASH_MAP_BASE_HPP
