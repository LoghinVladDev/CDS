//
// Created by loghin on 1/9/25.
//

#ifndef CDS_DS_MAP_ENTRY_HPP
#define CDS_DS_MAP_ENTRY_HPP
#pragma once

#include <cds/meta/TypeTraits>
#include <cds/Tuple>

namespace cds {
namespace impl {
using cds::meta::And;
using cds::meta::IsNoexceptConstructible;

template <typename K, typename V> class MapEntry : public Tuple<K, V> {
public:
  using Tuple<K, V>::Tuple;

  template <typename RK, typename... RV> CDS_ATTR(2(implicit, constexpr(11))) MapEntry(RK&& key, RV&&... valueArgs)
      CDS_ATTR(noexcept(And<IsNoexceptConstructible<K, RK>, IsNoexceptConstructible<V, RV...>>::value)) :
      Tuple<K, V>{fwd<RK>(key), V{fwd<RV>(valueArgs)...}} {}

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

namespace std {
template <typename K, typename V> struct tuple_size<cds::MapEntry<K, V>> : cds::meta::Integral<std::size_t, 2> {};

template <typename K, typename V> struct tuple_element<0, cds::MapEntry<K, V>> {
  using type = K;
};

template <typename K, typename V> struct tuple_element<1, cds::MapEntry<K, V>> {
  using type = V;
};
}

#endif // #ifndef CDS_DS_MAP_ENTRY_HPP
