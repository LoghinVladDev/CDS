//
// Created by loghin on 7/6/25.
//

#ifndef CDS_COLLECTION_LINKED_HASH_MAP_DECL_HPP
#define CDS_COLLECTION_LINKED_HASH_MAP_DECL_HPP

#include <cds/functional/Comparator>
#include <cds/functional/Hash>
#include <cds/memory/Allocator>

#include "LinkedHashMapAllocator.hpp"

namespace cds {
namespace impl {
using functional::Equal;
using functional::Hash;

template <
    typename K, typename V, typename H = Hash<>, typename E = Equal<>,
    typename TA = LinkedHashMapAllocator<K, V>, typename LA = Allocator<FwdNode<MapEntry<K, V>>>
> class LinkedHashMap;
} // namespace impl

using impl::LinkedHashMap;
} // namespace cds

#endif // #ifndef CDS_COLLECTION_LINKED_HASH_MAP_DECL_HPP
