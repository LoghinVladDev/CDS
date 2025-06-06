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
using meta::And;
using meta::IsNoexceptConstructible;

struct MapEntryKeyProjection {
  template <typename E> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(E&& entry) const noexcept
      -> decltype(fwd<E>(entry).key()) {
    return fwd<E>(entry).key();
  }
};

struct MapEntryValueProjection {
  template <typename E> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(E&& entry) const noexcept
      -> decltype(fwd<E>(entry).value()) {
    return fwd<E>(entry).value();
  }
};

template <typename K, typename V> class MapEntry : public Tuple<K const, V> {
public:
  using Tuple<K const, V>::Tuple;

  template <typename RK, typename RV0, typename RV1, typename... RVn>
  CDS_ATTR(2(implicit, constexpr(11))) MapEntry(RK&& key, RV0&& v0, RV1&& v1, RVn&&... vn)
      CDS_ATTR(noexcept(And<IsNoexceptConstructible<K, RK>, IsNoexceptConstructible<V, RV0&&, RV1&&, RVn&&...>>::value))
      : Tuple<K const, V>{fwd<RK>(key), V{fwd<RV0>(v0), fwd<RV1>(v1), fwd<RVn>(vn)...}} {}

  CDS_ATTR(2(implicit, constexpr(11))) MapEntry(Tuple<K, V> const& tuple) CDS_ATTR(noexcept(noexcept(
      Tuple<K const, V>{tuple}
  ))) : Tuple<K const, V>{tuple} {}

  CDS_ATTR(2(implicit, constexpr(11))) MapEntry(Tuple<K, V>&& tuple) CDS_ATTR(noexcept(noexcept(
      Tuple<K const, V>{mv(tuple)}
  ))) : Tuple<K const, V>{mv(tuple)} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto key() const& noexcept -> K const& {
    return get<0>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto key()& noexcept -> K const& {
    return get<0>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto key()&& noexcept -> K {
    return get<0>(mv(*this));
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto value() const& noexcept -> V const& {
    return get<1>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value()& noexcept -> V& {
    return get<1>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value()&& noexcept -> V {
    return get<1>(mv(*this));
  }
};

#if CDS_ATTR(ctad)
template <typename K, typename V> MapEntry(K, V) -> MapEntry<K, V>;
#endif
} // namespace impl

using impl::MapEntry;
} // namespace cds

namespace std {
template <typename K, typename V> struct tuple_size<cds::MapEntry<K, V>> : cds::meta::Integral<std::size_t, 2> {};

template <typename K, typename V> struct tuple_element<0, cds::MapEntry<K, V>> {
  using type = K const;
};

template <typename K, typename V> struct tuple_element<1, cds::MapEntry<K, V>> {
  using type = V;
};
} // namespace std

#include "../../format/MapEntryFormatter.hpp"

#endif // #ifndef CDS_DS_MAP_ENTRY_HPP
