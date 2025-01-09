//
// Created by loghin on 1/9/25.
//

#ifndef CDS_DS_MAP_BASE_HPP
#define CDS_DS_MAP_BASE_HPP
#pragma once

#include <cds/meta/ObjectTraits>

#include "../../ds/map/MapEntry.hpp"

namespace cds {
namespace impl {
using meta::impl::IsBaseOfIntrusiveICVR;

template <typename K, typename V, typename B> class BaseMap : private B {
public:
  using B::B;
  using B::operator=;
  using B::begin;
  using B::cbegin;
  using B::cend;
  using B::clear;
  using B::emplace;
  using B::empty;
  using B::end;
  using B::size;

  template <typename It, typename S, EnableIf<IsForwardIterator<It, S>> = 0> CDS_ATTR(constexpr(20))
  BaseMap(It first, S last) CDS_ATTR(noexcept(noexcept(emplace(get<0>(*first), get<1>(*first))))) {
    for (; first != last; ++first) {
      emplace(get<0>(*first), get<1>(first));
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
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_MAP_BASE_HPP
