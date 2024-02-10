//
// Created by loghin on 12/22/23.
//

#ifndef CDS_FUNCTIONAL_TRANSFORMER_HPP
#define CDS_FUNCTIONAL_TRANSFORMER_HPP
#pragma once

#include <cds/meta/Semantics>
#include <cds/meta/ObjectTraits>

namespace cds {
namespace functional {
namespace impl {
using meta::EnableIf;
using meta::Ge;
using meta::Lt;
using meta::Int;
using meta::Or;
using meta::Not;
using meta::And;
using meta::IsTriviallyConstructible;

template<typename T = void, typename = void> struct Identity {};

template <typename T>
struct Identity<T, EnableIf<Or<Ge<Int<sizeof(T)>, Int<sizeof(Size)>>, Not<IsTriviallyConstructible<T>>>, void>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T const& obj) const noexcept -> T const& {
    return obj;
  }
};

template <typename T>
struct Identity<T, EnableIf<And<Lt<Int<sizeof(T)>, Int<sizeof(Size)>>, IsTriviallyConstructible<T>>, void>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T obj) const noexcept -> T {
    return obj;
  }
};


template <> struct Identity<void, void> {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T&& v) const noexcept -> T&& {
    return cds::forward<T>(v);
  }
};
} // namespace impl
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_TRANSFORMER_HPP
