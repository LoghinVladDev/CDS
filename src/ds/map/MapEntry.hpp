//
// Created by loghin on 1/9/25.
//

#ifndef CDS_DS_MAP_ENTRY_HPP
#define CDS_DS_MAP_ENTRY_HPP
#pragma once

#include <cds/Tuple>

namespace cds {
namespace impl {
template <typename K, typename V> class MapEntry : public Tuple<K, V> {
public:
  using Tuple<K, V>::Tuple;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto key() const& noexcept -> K const& {
    return get<0>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto key()& noexcept -> K& {
    return get<0>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto key()&& noexcept -> K&& {
    return get<0>(mv(*this));
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto value() const& noexcept -> V const& {
    return get<1>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value()& noexcept -> V& {
    return get<1>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value()&& noexcept -> V&& {
    return get<1>(mv(*this));
  }
};
} // namespace impl

using impl::MapEntry;
} // namespace cds

#endif // #ifndef CDS_DS_MAP_ENTRY_HPP
