//
// Created by loghin on 1/9/25.
//

#ifndef CDS_DS_MAP_BASE_HPP
#define CDS_DS_MAP_BASE_HPP
#pragma once

#include <cds/functional/Transformer>
#include <cds/iterator/ProjectionIterator>
#include <cds/meta/IterableTraits>
#include <cds/meta/ObjectTraits>

#include "../../algorithm/RangeEqual.hpp"
#include "../../ds/map/MapEntry.hpp"
#include "../../ds/set/SetProjection.hpp"
#include "../../meta/Ignore.hpp"

#include <initializer_list>

namespace cds {
namespace impl {
using functional::impl::Identity;

using iterator::ProjectionIterator;

using meta::IsIterable;
using meta::IsForwardIterator;
using meta::impl::IsBaseOfIntrusiveICVR;

template <typename K, typename V, typename B> class BaseMap;

template <typename K, typename V, typename B> struct SetProjectionTraits<BaseMap<K, V, B>, MapEntryKeyProjection> {
  using Value = K;
  using Projector = MapEntryKeyProjection;
  using Iterator = ProjectionIterator<typename B::Iterator, Projector>;
  using ConstIterator = ProjectionIterator<typename B::ConstIterator, Projector>;
  using CanInsert = False;
  using CanRemove = True;
};

template <typename K, typename V, typename B>
struct SetProjectionTraits<BaseMap<K, V, B> const, MapEntryKeyProjection> {
  using Value = K const;
  using Projector = MapEntryKeyProjection;
  using Iterator = ProjectionIterator<typename B::ConstIterator, Projector>;
  using ConstIterator = ProjectionIterator<typename B::ConstIterator, Projector>;
  using CanInsert = False;
  using CanRemove = False;
};

template <typename K, typename V, typename B> struct SetProjectionTraits<BaseMap<K, V, B>, MapEntryValueProjection> {
  using Value = V;
  using Projector = MapEntryValueProjection;
  using Iterator = ProjectionIterator<typename B::Iterator, Projector>;
  using ConstIterator = ProjectionIterator<typename B::ConstIterator, Projector>;
  using CanInsert = False;
  using CanRemove = False;
};

template <typename K, typename V, typename B>
struct SetProjectionTraits<BaseMap<K, V, B> const, MapEntryValueProjection> {
  using Value = V const;
  using Projector = MapEntryValueProjection;
  using Iterator = ProjectionIterator<typename B::ConstIterator, Projector>;
  using ConstIterator = ProjectionIterator<typename B::ConstIterator, Projector>;
  using CanInsert = False;
  using CanRemove = False;
};

template <typename K, typename V, typename B> struct SetProjectionTraits<BaseMap<K, V, B>, Identity<>> {
  using Value = MapEntry<K, V>;
  using Projector = Identity<>;
  using Iterator = typename B::Iterator;
  using ConstIterator = typename B::ConstIterator;
  using CanInsert = True;
  using CanRemove = True;
};

template <typename K, typename V, typename B> struct SetProjectionTraits<BaseMap<K, V, B> const, Identity<>> {
  using Value = MapEntry<K, V> const;
  using Projector = Identity<>;
  using Iterator = typename B::ConstIterator;
  using ConstIterator = typename B::ConstIterator;
  using CanInsert = False;
  using CanRemove = False;
};

template <typename K, typename V, typename B> class BaseMap : private B {
public:
  using typename B::Iterator;
  using typename B::ConstIterator;

  using B::B;
  using B::operator=;
  using B::begin;
  using B::cbegin;
  using B::cend;
  using B::clear;
  using B::emplace;
  using B::empty;
  using B::end;
  using B::find;
  using B::remove;
  using B::size;
  using B::operator[];

  BaseMap() = default;

  template <typename It, typename S, EnableIf<IsForwardIterator<It, S>> = 0> CDS_ATTR(constexpr(20))
  BaseMap(It first, S last) CDS_ATTR(noexcept(noexcept(emplace(get<0>(*first), get<1>(*first))))) {
    for (; first != last; ++first) {
      emplace(get<0>(*first), get<1>(*first));
    }
  }

  template <typename R, EnableIf<And<
      IsIterable<R>,
      Not<IsBaseOfIntrusiveICVR<BaseMap, R>>
  >> = 0> CDS_ATTR(2(explicit, constexpr(20))) BaseMap(R&& range)
      CDS_ATTR(noexcept(noexcept(BaseMap{cds::begin(fwd<R>(range)), cds::end(fwd<R>(range))}))) :
  BaseMap{cds::begin(fwd<R>(range)), cds::end(fwd<R>(range))} {}

  CDS_ATTR(constexpr(20)) BaseMap(std::initializer_list<MapEntry<K, V>> const& list)
      CDS_ATTR(noexcept(noexcept(BaseMap{list.begin(), list.end()}))) : BaseMap{list.begin(), list.end()} {}

  template <typename R, EnableIf<And<
      IsIterable<R>,
      Not<IsBaseOfIntrusiveICVR<BaseMap, R>>
  >> = 0> CDS_ATTR(constexpr(20)) auto operator=(R&& range) CDS_ATTR(noexcept(
      noexcept(emplace(get<0>(*cds::begin(fwd<R>(range))), get<1>(*cds::begin(fwd<R>(range)))))
  )) -> BaseMap& {
    clear();
    auto&& first = cds::begin(fwd<R>(range));
    auto&& last = cds::end(fwd<R>(range));
    for (; first != last; ++first) {
      ignore = emplace(get<0>(*first), get<1>(*first));
    }
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(std::initializer_list<MapEntry<K, V>> const& list)
      CDS_ATTR(noexcept(noexcept(emplace(get<0>(*list.begin()), get<1>(*list.begin()))))) -> BaseMap& {
    clear();
    for (auto const& entry : list) {
      ignore = emplace(get<0>(entry), get<1>(entry));
    }
    return *this;
  }

  CDS_ATTR(2(explicit, constexpr(20))) operator bool() const noexcept {
    return !empty();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(K const& key)
      const CDS_ATTR(noexcept(noexcept(find(key)))) -> bool {
    return find(key) != end();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto keys() noexcept -> SetProjection<BaseMap, MapEntryKeyProjection> {
    return SetProjection<BaseMap, MapEntryKeyProjection>{*this};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto keys() const noexcept
      -> SetProjection<BaseMap const, MapEntryKeyProjection> {
    return SetProjection<BaseMap const, MapEntryKeyProjection>{*this};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto values() noexcept -> SetProjection<BaseMap, MapEntryValueProjection> {
    return SetProjection<BaseMap, MapEntryValueProjection>{*this};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto values() const noexcept
      -> SetProjection<BaseMap const, MapEntryValueProjection> {
    return SetProjection<BaseMap const, MapEntryValueProjection>{*this};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto entries() noexcept -> SetProjection<BaseMap, Identity<>> {
    return SetProjection<BaseMap, Identity<>>{*this};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto entries() const noexcept
      -> SetProjection<BaseMap const, Identity<>> {
    return SetProjection<BaseMap const, Identity<>>{*this};
  }
};

template <typename K, typename V, typename B> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator==(BaseMap<K, V, B> const& lhs, BaseMap<K, V, B> const& rhs) noexcept -> bool {
  if (&lhs == &rhs) {
    return true;
  }

  if (lhs.size() != rhs.size()) {
    return false;
  }

  return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename K, typename V, typename B> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator!=(BaseMap<K, V, B> const& lhs, BaseMap<K, V, B> const& rhs) noexcept -> bool {
  if (&lhs == &rhs) {
    return false;
  }

  if (lhs.size() != rhs.size()) {
    return true;
  }

  return !equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_MAP_BASE_HPP
