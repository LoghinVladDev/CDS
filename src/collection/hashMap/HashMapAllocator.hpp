//
// Created by loghin on 6/3/25.
//

#ifndef CDS_COLLECTION_HASH_MAP_ALLOCATOR_HPP
#define CDS_COLLECTION_HASH_MAP_ALLOCATOR_HPP
#pragma once

#include "../../ds/map/MapEntry.hpp"
#include "../../ds/node/FwdNode.hpp"
#include <cds/memory/Allocator>

namespace cds {
namespace impl {
template <typename K, typename V> using HashMapNode = FwdNode<MapEntry<K, V>>;
template <typename K, typename V> using HashMapNodeAllocator = Allocator<HashMapNode<K, V>>;
template <typename K, typename V> using HashMapBucketAllocator = Allocator<HashMapNode<K, V>*>;
template <typename K, typename V> using HashMapAllocator =
    AllocatorSet<HashMapNodeAllocator<K, V>, HashMapBucketAllocator<K, V>>;
} // namespace impl
} // namespace cds

#endif // CDS_COLLECTION_HASH_MAP_ALLOCATOR_HPP
