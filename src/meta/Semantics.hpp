//
// Created by loghin on 11/29/23.
//

#ifndef CDS_META_SEMANTICS_HPP
#define CDS_META_SEMANTICS_HPP
#pragma once

#include <cds/meta/TypeTraits>

namespace cds {
template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto forward(meta::RemoveRef<T>& v) noexcept -> T&& {
  return static_cast<T&&>(v);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto forward(meta::RemoveRef<T>&& v) noexcept -> T&& {
  static_assert(!meta::IsLValRef<T>::value, "Attempted to use forward to convert rvalue to lvalue");
  return static_cast<T&&>(v);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto move(T&& v) noexcept -> meta::RemoveRef<T>&& {
  return static_cast<meta::RemoveRef<T>&&>(v);
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(14))) auto exchange(T& obj, U&& newVal) -> T {
  T old = cds::move(obj);
  obj = cds::forward<U>(newVal);
  return old;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto asConst(T& obj) noexcept -> meta::AddConst<T>& {
  return obj;
}

template <typename T> auto asConst(T&& obj) noexcept -> void = delete;
} // namespace cds

#endif // CDS_META_SEMANTICS_HPP