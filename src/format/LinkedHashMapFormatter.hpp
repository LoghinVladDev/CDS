//
// Created by loghin on 6/3/25.
//

#if defined(CDS_COLLECTION_LINKED_HASH_MAP_DECL_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP) \
&& !defined(CDS_FORMAT_LINKED_HASH_MAP_FORMAT_HPP)
#define CDS_FORMAT_LINKED_HASH_MAP_FORMAT_HPP

namespace cds {
template <typename C, typename K, typename V, typename H, typename E, typename TA, typename LA>
struct Formatter<LinkedHashMap<K, V, H, E, TA, LA>, C> : impl::fmt::RangeFormatter<impl::MapEntry<K, V>, C>{};
} // namespace cds

#endif
