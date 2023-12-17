//
// Created by loghin on 12/14/23.
//

#ifndef CDS_SHARED_BINDINGS_STATIC_CONTAINS_OF_BINDING_STATIC_HPP
#define CDS_SHARED_BINDINGS_STATIC_CONTAINS_OF_BINDING_STATIC_HPP
#pragma once

#include <cds/Utility>
#include <cds/meta/Base>
#include <cds/functional/FunctionalInterface>
#include <initializer_list>

namespace cds {
namespace impl {
template <typename R>
class ContainsOfStaticBinding {
protected:
  using Value = typename meta::IterableTraits<R>::Value;

public:
  template <typename F = std::initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyOf(F&& from) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<R>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i)) {
        return true;
      }
    }
    return false;
  }

  template <typename F = std::initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyNotOf(F&& from) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<F>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(*iterable), e = cds::end(*iterable); i != e; ++i) {
      if (!contains(cds::forward<F>(from), *i)) {
        return true;
      }
    }
    return false;
  }

  template <typename F = std::initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAllOf(F&& from) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<R>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (!contains(*iterable, *i)) {
        return false;
      }
    }
    return true;
  }

  template <typename F = std::initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsNoneOf(F&& from) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<R>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i)) {
        return false;
      }
    }
    return true;
  }
};

template <typename R>
class ContainsSelectedOfStaticBinding {
protected:
  using Value = typename meta::IterableTraits<R>::Value;

public:
  template <typename S, typename F = std::initializer_list<meta::ReturnOf<S>>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyOf(F&& from, S&& selector) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<R>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, cds::forward<S>(selector))) {
        return true;
      }
    }
    return false;
  }

  template <typename S, typename F = std::initializer_list<meta::ReturnOf<S>>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyNotOf(F&& from, S&& selector) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<F>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(*iterable), e = cds::end(*iterable); i != e; ++i) {
      if (!contains(cds::forward<F>(from), cds::forward<S>(selector)(*i))) {
        return true;
      }
    }
    return false;
  }

  template <typename S, typename F = std::initializer_list<meta::ReturnOf<S>>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAllOf(F&& from, S&& selector) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<R>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (!contains(*iterable, *i , cds::forward<S>(selector))) {
        return false;
      }
    }
    return true;
  }

  template <typename S, typename F = std::initializer_list<meta::ReturnOf<S>>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsNoneOf(F&& from, S&& selector) const
      CDS_ATTR(noexcept(noexcept(contains(meta::lvalue<R>(), meta::value<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, cds::forward<S>(selector))) {
        return false;
      }
    }
    return true;
  }
};
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDINGS_STATIC_CONTAINS_OF_BINDING_STATIC_HPP
