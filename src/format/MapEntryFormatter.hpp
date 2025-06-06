//
// Created by loghin on 6/3/25.
//

#if defined(CDS_DS_MAP_ENTRY_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP) \
&& !defined(CDS_FORMAT_MAP_ENTRY_FORMAT_HPP)
#define CDS_FORMAT_MAP_ENTRY_FORMAT_HPP

namespace cds {
template <typename C, typename K, typename V>
struct Formatter<impl::MapEntry<K, V>, C> : impl::fmt::TupleLikeFormatter<C, K, V>{};
} // namespace cds

#endif
