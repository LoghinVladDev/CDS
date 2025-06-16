//
// Created by loghin on 6/16/25.
//

#ifndef CDS_COLLECTION_LINKED_HASH_MAP_HPP
#define CDS_COLLECTION_LINKED_HASH_MAP_HPP
#pragma once

#include <cds/functional/Comparator>
#include <cds/functional/Hash>
#include <cds/memory/Allocator>

#include "../ds/hashTable/HashTableBase.hpp"
#include "../ds/map/MapBase.hpp"
#include "../ds/map/MapEntry.hpp"
#include "linkedHashMap/LinkedHashMapAllocator.hpp"
#include "linkedHashMap/LinkedHashMapBase.hpp"

namespace cds {
namespace impl {
using functional::Hash;
using functional::Equal;

template <
    typename K, typename V, typename H = Hash<>, typename E = Equal<>,
    typename TA = LinkedHashMapAllocator<K, V>, typename LA = Allocator<FwdNode<MapEntry<K, V>>>
> class LinkedHashMap : public BaseMap<K, V, BaseLinkedHashMap<K, V, H, E, TA, LA>> {
  using Base = BaseMap<K, V, BaseLinkedHashMap<K, V, H, E, TA, LA>>;

public:
  using Base::Base;
  using Base::operator=;
};
} // namespace impl

using impl::LinkedHashMap;
} // namespace cds

#endif // #ifndef CDS_COLLECTION_LINKED_HASH_MAP_HPP
