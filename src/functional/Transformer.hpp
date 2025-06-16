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
using meta::Gt;
using meta::Le;
using meta::Int;
using meta::Or;
using meta::Not;
using meta::And;
using meta::IsTriviallyConstructible;

template <typename = void, typename = void> struct Identity {};

template <typename T>
struct Identity<T, EnableIf<Or<Gt<Int<sizeof(T)>, Int<sizeof(Size)>>, Not<IsTriviallyConstructible<T>>>, void>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T const& obj) const noexcept -> T const& {
    return obj;
  }
};

template <typename T>
struct Identity<T, EnableIf<And<Le<Int<sizeof(T)>, Int<sizeof(Size)>>, IsTriviallyConstructible<T>>, void>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T obj) const noexcept -> T {
    return obj;
  }
};


template <> struct Identity<void, void> {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T&& v) const noexcept -> T&& {
    return fwd<T>(v);
  }
};

template <typename P = void> struct Indirection : P {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T* obj) const noexcept ->
      decltype(P{}(*obj)) {
    return static_cast<P const&>(*this)(*obj);
  }
};

template <> struct Indirection<void> {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T* obj) const noexcept -> T& {
    return *obj;
  }
};
} // namespace impl

using impl::Identity;
using impl::Indirection;
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_TRANSFORMER_HPP
