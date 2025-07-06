//
// Created by loghin on 6/16/25.
//

#ifndef CDS_COLLECTION_LINKED_HASH_MAP_HPP
#define CDS_COLLECTION_LINKED_HASH_MAP_HPP
#pragma once

#include "../ds/hashTable/HashTableBase.hpp"
#include "../ds/map/MapBase.hpp"
#include "../ds/map/MapEntry.hpp"

#include "linkedHashMap/LinkedHashMapBase.hpp"
#include "linkedHashMap/LinkedHashMapDecl.hpp"

#include "../format/LinkedHashMapFormatter.hpp"

namespace cds {
namespace impl {
template <typename K, typename V, typename H, typename E, typename TA, typename LA>
class LinkedHashMap : public BaseMap<K, V, BaseLinkedHashMap<K, V, H, E, TA, LA>> {
  using Base = BaseMap<K, V, BaseLinkedHashMap<K, V, H, E, TA, LA>>;

public:
  using Base::Base;
  using Base::operator=;
};
} // namespace impl
} // namespace cds


#endif // #ifndef CDS_COLLECTION_LINKED_HASH_MAP_HPP
