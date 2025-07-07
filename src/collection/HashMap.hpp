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
#include "hashMap/HashMapAllocator.hpp"
#include "hashMap/HashMapBase.hpp"

namespace cds {
namespace impl {
using functional::Equal;
using functional::Hash;

template <typename K, typename V, typename H = Hash<>, typename E = Equal<>, typename A = HashMapAllocator<K, V>>
class CDS_ATTR(ebo) HashMap : public BaseMap<K, V, BaseHashMap<K, V, H, E, A>> {
  using Base = BaseMap<K, V, BaseHashMap<K, V, H, E, A>>;
public:
  using Base::Base;
  using Base::operator=;
};
} // namespace impl

using impl::HashMap;
} // namespace cds

#include "../format/HashMapFormatter.hpp"

#endif // CDS_COLLECTION_HASH_MAP_HPP
