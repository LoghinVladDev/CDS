//
// Created by loghin on 6/3/25.
//

#ifndef CDS_COLLECTION_LINKED_HASH_MAP_ALLOCATOR_HPP
#define CDS_COLLECTION_LINKED_HASH_MAP_ALLOCATOR_HPP
#pragma once

#include "../../ds/map/MapEntry.hpp"
#include "../../ds/node/FwdNode.hpp"
#include <cds/memory/Allocator>

namespace cds {
namespace impl {
template <typename K, typename V> using LinkedHashMapNode = FwdNode<FwdNode<MapEntry<K, V>>*>;
template <typename K, typename V> using LinkedHashMapNodeAllocator = Allocator<LinkedHashMapNode<K, V>>;
template <typename K, typename V> using LinkedHashMapBucketAllocator = Allocator<LinkedHashMapNode<K, V>*>;
template <typename K, typename V> using LinkedHashMapAllocator =
    AllocatorSet<LinkedHashMapNodeAllocator<K, V>, LinkedHashMapBucketAllocator<K, V>>;
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_COLLECTION_LINKED_HASH_MAP_ALLOCATOR_HPP
