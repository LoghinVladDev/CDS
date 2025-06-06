//
// Created by loghin on 6/3/25.
//

#if defined(CDS_COLLECTION_HASH_MAP_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP) \
&& !defined(CDS_FORMAT_HASH_MAP_FORMAT_HPP)
#define CDS_FORMAT_HASH_MAP_FORMAT_HPP

namespace cds {
template <typename C, typename K, typename V, typename H, typename E, typename A>
struct Formatter<HashMap<K, V, H, E, A>, C> : impl::fmt::RangeFormatter<impl::MapEntry<K, V>, C>{};
} // namespace cds

#endif
