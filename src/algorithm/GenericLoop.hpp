//
// Created by loghin on 3/16/24.
//

#ifndef CDS_ALGORITHM_GENERIC_LOOP_HPP
#define CDS_ALGORITHM_GENERIC_LOOP_HPP
#pragma once

#include <cds/iterator/Iterator>
#include <cds/iterator/AddressIterator>
#include <cds/functional/Invoke>

namespace cds {
namespace impl {
using functional::invoke;

template <typename I, typename S, typename C> CDS_ATTR(constexpr(14))
auto forEach(I&& begin, S&& end, C&& consumer) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<C>(consumer), *cds::forward<I>(begin)))
)) -> void {
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    (void) invoke(cds::forward<C>(consumer), *it);
  }
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto some(I&& begin, S&& end, Size count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  Size valid = 0u;
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    if (invoke(cds::forward<P>(predicate), *it)) {
      ++valid;
    }

    if (valid > count) {
      return false;
    }
  }
  return valid == count;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto atLeast(I&& begin, S&& end, Size count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  Size valid = 0u;
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    if (invoke(cds::forward<P>(predicate), *it)) {
      ++valid;
    }

    if (valid >= count) {
      return true;
    }
  }
  return false;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto atMost(I&& begin, S&& end, Size count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  Size valid = 0u;
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    if (invoke(cds::forward<P>(predicate), *it)) {
      ++valid;
    }

    if (valid > count) {
      return false;
    }
  }
  return true;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto moreThan(I&& begin, S&& end, Size count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  return atLeast(cds::forward<I>(begin), cds::forward<S>(end), count + 1u, cds::forward<P>(predicate));
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto lessThan(I&& begin, S&& end, Size count, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  if (count == 0u) {
    return false;
  }
  return atMost(cds::forward<I>(begin), cds::forward<S>(end), count - 1u, cds::forward<P>(predicate));
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto count(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> Size {
  Size valid = 0u;
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    if (invoke(cds::forward<P>(predicate), *it)) {
      ++valid;
    }
  }
  return valid;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto any(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    if (invoke(cds::forward<P>(predicate), *it)) {
      return true;
    }
  }
  return false;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto all(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    if (!invoke(cds::forward<P>(predicate), *it)) {
      return false;
    }
  }
  return true;
}

template <typename I, typename S, typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
auto none(I&& begin, S&& end, P&& predicate) CDS_ATTR(noexcept(
    noexcept(invoke(cds::forward<P>(predicate), *cds::forward<I>(begin)))
)) -> bool {
  for (auto it = cds::forward<I>(begin); it != cds::forward<S>(end); ++it) {
    if (invoke(cds::forward<P>(predicate), *it)) {
      return false;
    }
  }
  return true;
}
} // namespace impl
} // namespace cds

#endif // CDS_ALGORITHM_GENERIC_LOOP_HPP
