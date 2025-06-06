//
// Created by loghin on 3/16/24.
//

#ifndef CDS_ALGORITHM_GENERIC_LOOP_HPP
#define CDS_ALGORITHM_GENERIC_LOOP_HPP
#pragma once

#include <cds/iterator/Iterator>
#include <cds/iterator/AddressIterator>

#include <cds/functional/Invoke>

#include "../meta/Ignore.hpp"

namespace cds {
namespace impl {
using meta::IsInvocable;
using meta::ReturnIf;
using meta::rvalue;

namespace fn = functional;

template <typename I, typename S, typename C, typename = EnableIf<IsInvocable<C, decltype(*rvalue<I>())>>>
CDS_ATTR(constexpr(14)) auto forEach(I&& begin, S&& end, C&& consumer) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<C>(consumer), *fwd<I>(begin)))
)) -> void {
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    (void) fn::invoke(fwd<C>(consumer), *it);
  }
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto some(I&& begin, S&& end, Size const count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  Size valid = 0u;
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    if (fn::invoke(fwd<P>(predicate), *it)) {
      ++valid;
    }

    if (valid > count) {
      return false;
    }
  }
  return valid == count;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto atLeast(I&& begin, S&& end, Size const count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  Size valid = 0u;
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    if (fn::invoke(fwd<P>(predicate), *it)) {
      ++valid;
    }

    if (valid >= count) {
      return true;
    }
  }
  return false;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto atMost(I&& begin, S&& end, Size const count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  Size valid = 0u;
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    if (fn::invoke(fwd<P>(predicate), *it)) {
      ++valid;
    }

    if (valid > count) {
      return false;
    }
  }
  return true;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto moreThan(I&& begin, S&& end, Size const count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  return atLeast(fwd<I>(begin), fwd<S>(end), count + 1u, fwd<P>(predicate));
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto lessThan(I&& begin, S&& end, Size const count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  if (count == 0u) {
    return false;
  }
  return atMost(fwd<I>(begin), fwd<S>(end), count - 1u, fwd<P>(predicate));
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto count(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<Size, IsInvocable<P, decltype(*rvalue<I>())>> {
  Size valid = 0u;
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    if (fn::invoke(fwd<P>(predicate), *it)) {
      ++valid;
    }
  }
  return valid;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto any(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    if (fn::invoke(fwd<P>(predicate), *it)) {
      return true;
    }
  }
  return false;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto all(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    if (!fn::invoke(fwd<P>(predicate), *it)) {
      return false;
    }
  }
  return true;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto none(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(fn::invoke(fwd<P>(predicate), *fwd<I>(begin)))
)) -> ReturnIf<bool, IsInvocable<P, decltype(*rvalue<I>())>> {
  for (auto it = fwd<I>(begin); it != fwd<S>(end); ++it) {
    if (fn::invoke(fwd<P>(predicate), *it)) {
      return false;
    }
  }
  return true;
}
} // namespace impl
} // namespace cds

#endif // CDS_ALGORITHM_GENERIC_LOOP_HPP
