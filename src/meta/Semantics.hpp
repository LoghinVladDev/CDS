//
// Created by loghin on 11/29/23.
//

#ifndef CDS_META_SEMANTICS_HPP
#define CDS_META_SEMANTICS_HPP
#pragma once

#include <cds/meta/TypeTraits>

namespace cds {
namespace impl {
using meta::AddConst;
using meta::RemoveRef;
using meta::IsLValRef;

// For ease of use and no clash with std::
template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto asConst(T& obj) noexcept -> AddConst<T>& {
  return obj;
}

template <typename T> auto asConst(T&& obj) noexcept -> void = delete;

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto fwd(RemoveRef<T>& v) noexcept -> T&& {
  return static_cast<T&&>(v);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto fwd(RemoveRef<T>&& v) noexcept -> T&& {
  static_assert(!IsLValRef<T>::value, "Attempted to use forward to convert rvalue to lvalue");
  return static_cast<T&&>(v);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto mv(T&& v) noexcept -> RemoveRef<T>&& {
  return static_cast<RemoveRef<T>&&>(v);
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(14))) auto xch(T& obj, U&& newVal) -> T {
  T old = mv(obj);
  obj = fwd<U>(newVal);
  return old;
}
} // namespace impl

using impl::asConst;
using impl::mv;
using impl::fwd;
using impl::xch;
} // namespace cds

#endif // CDS_META_SEMANTICS_HPP
