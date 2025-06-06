//
// Created by loghin on 6/18/24.
//

#ifndef CDS_PRIMITIVE_OPTIONAL_HPP
#define CDS_PRIMITIVE_OPTIONAL_HPP
#pragma once

#include "optional/OptionalBase.hpp"

#if CDS_ATTR(spaceship)
#include <compare>
#endif

namespace cds {
template <typename T> class CDS_ATTR(ebo) Optional : private impl::OptionalBase<T> {
  using Base = impl::OptionalBase<T>;
  using StorageBase = impl::OptionalStorageBase<T>;
  using ObservableBase = impl::OptionalObservableBase<T>;
  using MonadicBase = impl::OptionalMonadicBase<T>;

  friend MonadicBase;

public:
  using Base::Base;

  using StorageBase::emplace;
  using StorageBase::reset;

  using ObservableBase::operator*;
  using ObservableBase::operator->;
  using ObservableBase::operator bool;
  using ObservableBase::hasValue;
  using ObservableBase::get;
  using ObservableBase::getOr;

  using MonadicBase::then;
  using MonadicBase::transform;
  using MonadicBase::orElse;

  CDS_ATTR(2(implicit, constexpr(11))) Optional(CDS_ATTR(unused) impl::Nullopt = impl::nullopt) noexcept :
      Base{} {}
};

namespace impl {
using meta::Decay;
using meta::ReturnIf;
using meta::Bool;

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    Optional<T> const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs == *rhs))) -> bool {
  return !lhs
      ? !rhs
      : !rhs
          ? false
          : *lhs == *rhs;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    Optional<T> const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs != *rhs))) -> bool {
  return !lhs
      ? static_cast<bool>(rhs)
      : !rhs
          ? true
          : *lhs != *rhs;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    Optional<T> const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs < *rhs))) -> bool {
  return !rhs
      ? false
      : !lhs
          ? true
          : *lhs < *rhs;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    Optional<T> const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs > *rhs))) -> bool {
  return !lhs
      ? false
      : !rhs
          ? true
          : *lhs > *rhs;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    Optional<T> const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs <= *rhs))) -> bool {
  return !lhs
      ? true
      : !rhs
          ? false
          : *lhs <= *rhs;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    Optional<T> const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs >= *rhs))) -> bool {
  return !rhs
      ? true
      : !lhs
          ? false
          : *lhs >= *rhs;
}

#if CDS_ATTR(spaceship)
template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(20))) auto operator <=>(
    Optional<T> const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs <=> *rhs))) -> decltype(*lhs <=> *rhs) {
  if (lhs && rhs) {
    return *lhs <=> *rhs;
  }

  return static_cast<bool>(lhs) <=> static_cast<bool>(rhs);
}
#endif

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    Optional<T> const& lhs, CDS_ATTR(unused) Nullopt rhs
) noexcept -> bool {
  return !lhs;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    CDS_ATTR(unused) Nullopt lhs, Optional<T> const& rhs
) noexcept -> bool {
  return !rhs;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    Optional<T> const& lhs, CDS_ATTR(unused) Nullopt rhs
) noexcept -> bool {
  return static_cast<bool>(lhs);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    CDS_ATTR(unused) Nullopt lhs, Optional<T> const& rhs
) noexcept -> bool {
  return static_cast<bool>(rhs);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    CDS_ATTR(unused) Optional<T> const& lhs, CDS_ATTR(unused) Nullopt rhs
) noexcept -> bool {
  return false;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    CDS_ATTR(unused) Nullopt lhs, Optional<T> const& rhs
) noexcept -> bool {
  return static_cast<bool>(rhs);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    Optional<T> const& lhs, CDS_ATTR(unused) Nullopt rhs
) noexcept -> bool {
  return static_cast<bool>(lhs);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    CDS_ATTR(unused) Nullopt lhs, CDS_ATTR(unused) Optional<T> const& rhs
) noexcept -> bool {
  return false;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    Optional<T> const& lhs, CDS_ATTR(unused) Nullopt rhs
) noexcept -> bool {
  return !lhs;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    CDS_ATTR(unused) Nullopt lhs, CDS_ATTR(unused) Optional<T> const& rhs
) noexcept -> bool {
  return true;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    CDS_ATTR(unused) Optional<T> const& lhs, CDS_ATTR(unused) Nullopt rhs
) noexcept -> bool {
  return true;
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    CDS_ATTR(unused) Nullopt lhs, Optional<T> const& rhs
) noexcept -> bool {
  return !rhs;
}

#if CDS_ATTR(spaceship)
template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    Optional<T> const& lhs, CDS_ATTR(unused) Nullopt rhs
) noexcept -> std::strong_ordering {
  return static_cast<bool>(lhs) <=> false;
}
#endif

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    Optional<T> const& lhs, U const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs == rhs))) -> bool {
  return lhs ? *lhs == rhs : false;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    T const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(lhs == *rhs))) -> bool {
  return rhs ? lhs == *rhs : false;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    Optional<T> const& lhs, U const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs != rhs))) -> bool {
  return lhs ? *lhs != rhs : true;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    T const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(lhs != *rhs))) -> bool {
  return rhs ? lhs != *rhs : true;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    Optional<T> const& lhs, U const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs < rhs))) -> bool {
  return lhs ? *lhs < rhs : true;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    T const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(lhs < *rhs))) -> bool {
  return rhs ? lhs < *rhs : false;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    Optional<T> const& lhs, U const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs > rhs))) -> bool {
  return lhs ? *lhs > rhs : false;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    T const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(lhs > *rhs))) -> bool {
  return rhs ? lhs > *rhs : true;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    Optional<T> const& lhs, U const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs <= rhs))) -> bool {
  return lhs ? *lhs <= rhs : true;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    T const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(lhs <= *rhs))) -> bool {
  return rhs ? lhs <= *rhs : false;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    Optional<T> const& lhs, U const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs >= rhs))) -> bool {
  return lhs ? *lhs >= rhs : false;
}

template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    T const& lhs, Optional<U> const& rhs
) CDS_ATTR(noexcept(noexcept(lhs >= *rhs))) -> bool {
  return rhs ? lhs >= *rhs : true;
}

#if CDS_ATTR(spaceship)
template <typename T, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    Optional<T> const& lhs, U const& rhs
) CDS_ATTR(noexcept(noexcept(*lhs <=> rhs))) -> decltype(*lhs <=> rhs) {
  return lhs ? *lhs <=> rhs : std::strong_ordering::less;
}
#endif

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(CDS_ATTR(unused) Nullopt, CDS_ATTR(unused) Nullopt) noexcept
    -> bool {
  return true;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(CDS_ATTR(unused) Nullopt, CDS_ATTR(unused) Nullopt) noexcept
    -> bool {
  return false;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(CDS_ATTR(unused) Nullopt, CDS_ATTR(unused) Nullopt) noexcept
    -> bool {
  return false;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(CDS_ATTR(unused) Nullopt, CDS_ATTR(unused) Nullopt) noexcept
    -> bool {
  return false;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(CDS_ATTR(unused) Nullopt, CDS_ATTR(unused) Nullopt) noexcept
    -> bool {
  return true;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(CDS_ATTR(unused) Nullopt, CDS_ATTR(unused) Nullopt) noexcept
    -> bool {
  return true;
}

#if CDS_ATTR(spaceship)
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(CDS_ATTR(unused) Nullopt, CDS_ATTR(unused) Nullopt) noexcept
    -> std::weak_ordering {
  return std::weak_ordering::equivalent;
}
#endif

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto optionalOf(T&& value)
    CDS_ATTR(noexcept(noexcept(Optional<Decay<T>>{fwd<T>(value)}))) -> Optional<Decay<T>> {
  return Optional<Decay<T>>{fwd<T>(value)};
}

template <typename T, typename... Args> CDS_ATTR(2(nodiscard, constexpr(11)))
auto optionalOf(Args&&... args) CDS_ATTR(noexcept(noexcept(Optional<T>{fwd<Args>(args)...})))
    -> ReturnIf<Optional<T>, Bool<(sizeof... (Args) > 0)>> {
  return Optional<T>{fwd<Args>(args)...};
}

auto optionalOf(Nullopt) noexcept -> void = delete;
template <typename T> auto optionalOf(Nullopt) noexcept -> void = delete;

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto optionalOf()
    CDS_ATTR(noexcept(meta::IsDefaultConstructible<T>::value)) -> Optional<T> {
  return Optional<T>{InPlace{}};
}
} // namespace impl

using impl::nullopt;
using impl::optionalOf;

#if CDS_ATTR(ctad)
template <typename T> Optional(T) -> Optional<T>;
#endif // #if CDS_ATTR(ctad)
} // namespace cds

#include "../format/OptionalFormatter.hpp"

#endif // #ifndef CDS_PRIMITIVE_OPTIONAL_HPP
