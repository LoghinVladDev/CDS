//
// Created by loghin on 1/9/25.
//

#ifndef CDS_COLLECTION_HASH_MAP_HPP
#define CDS_COLLECTION_HASH_MAP_HPP
#pragma once

#include <cds/functional/Comparator>
#include <cds/functional/Hash>
#include <cds/memory/Allocator>

#include "../ds/hashTable/HashTableBase.hpp"
#include "../ds/map/MapBase.hpp"
#include "../ds/map/MapEntry.hpp"
#include "hashMap/HashMapBase.hpp"

namespace cds {
namespace impl {
using functional::Equal;
using functional::Hash;

template <typename K, typename V> using HashMapNode = FwdNode<MapEntry<K, V>>;
template <typename K, typename V> using HashMapNodeAllocator = Allocator<HashMapNode<K, V>>;
template <typename K, typename V> using HashMapBucketAllocator = Allocator<HashMapNode<K, V>*>;
template <typename K, typename V> using HashMapAllocator =
    AllocatorSet<HashMapNodeAllocator<K, V>, HashMapBucketAllocator<K, V>>;

template <typename K, typename V, typename H = Hash<>, typename E = Equal<>, typename A = HashMapAllocator<K, V>>
class HashMap : public BaseMap<K, V, BaseHashMap<K, V, H, E, A>> {
  using Base = BaseMap<K, V, BaseHashMap<K, V, H, E, A>>;
public:
  using Base::Base;
  using Base::operator=;
};
} // namespace impl

using impl::HashMap;
} // namespace cds

#endif // CDS_COLLECTION_HASH_MAP_HPP
