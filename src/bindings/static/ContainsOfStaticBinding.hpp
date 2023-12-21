//
// Created by loghin on 12/14/23.
//

#ifndef CDS_SHARED_BINDINGS_STATIC_CONTAINS_OF_BINDING_STATIC_HPP
#define CDS_SHARED_BINDINGS_STATIC_CONTAINS_OF_BINDING_STATIC_HPP
#pragma once

#include "../BindingSelectors.hpp"
#include <cds/Utility>
#include <cds/meta/Base>
#include <cds/functional/FunctionalInterface>
#include <initializer_list>

namespace cds {
namespace impl {
using std::initializer_list;

using meta::IterableTraits;
using meta::ReturnOf;
using meta::rvalue;

template <typename R> class ContainsByValueOfStaticBinding {
protected:
  using Value = typename IterableTraits<R>::Value;

public:
  template <typename F = initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i)) {
        return true;
      }
    }
    return false;
  }

  template <typename F = initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyNotOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<F>(), rvalue<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(*iterable), e = cds::end(*iterable); i != e; ++i) {
      if (!contains(cds::forward<F>(from), *i)) {
        return true;
      }
    }
    return false;
  }

  template <typename F = initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAllOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (!contains(*iterable, *i)) {
        return false;
      }
    }
    return true;
  }

  template <typename F = initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsNoneOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>())))) -> bool {
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
class ContainsBySelectorOfStaticBinding {
protected:
  using Value = typename IterableTraits<R>::Value;

public:
  template <typename S, typename F = initializer_list<ReturnOf<S>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyOf(F&& from, S&& selector)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), cds::forward<S>(selector))))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, cds::forward<S>(selector))) {
        return true;
      }
    }
    return false;
  }

  template <typename S, typename F = initializer_list<ReturnOf<S>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyNotOf(F&& from, S&& selector)
      const CDS_ATTR(noexcept(noexcept(contains(cds::forward<F>(from), rvalue<Value>())))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(*iterable), e = cds::end(*iterable); i != e; ++i) {
      if (!contains(cds::forward<F>(from), cds::forward<S>(selector)(*i))) {
        return true;
      }
    }
    return false;
  }

  template <typename S, typename F = initializer_list<ReturnOf<S>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAllOf(F&& from, S&& selector)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), cds::forward<S>(selector))))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (!contains(*iterable, *i, cds::forward<S>(selector))) {
        return false;
      }
    }
    return true;
  }

  template <typename S, typename F = initializer_list<ReturnOf<S>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsNoneOf(F&& from, S&& selector)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), cds::forward<S>(selector))))) -> bool {
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, cds::forward<S>(selector))) {
        return false;
      }
    }
    return true;
  }
};

namespace containsOfDeriv {
using meta::True;
using meta::False;
using meta::Any;
using meta::Bind;
using meta::Ph;

using sel::Value;
using sel::Selector;
using sel::ContainsSelector;

template <
    typename P,
    typename = typename ContainsSelector<P, Value>::Type,
    typename = typename ContainsSelector<P, Selector>::Type
> struct MethodSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Value, Selector>::value,
      "Must select Value, Selector or both"
  );
};

template <typename P> struct MethodSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type : public ContainsByValueOfStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type : public ContainsBySelectorOfStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public ContainsByValueOfStaticBinding<A...>,
      public ContainsBySelectorOfStaticBinding<A...> {
  public:
    using ContainsByValueOfStaticBinding<A...>::containsAnyOf;
    using ContainsByValueOfStaticBinding<A...>::containsAnyNotOf;
    using ContainsByValueOfStaticBinding<A...>::containsNoneOf;
    using ContainsByValueOfStaticBinding<A...>::containsAllOf;

    using ContainsBySelectorOfStaticBinding<A...>::containsAnyOf;
    using ContainsBySelectorOfStaticBinding<A...>::containsAnyNotOf;
    using ContainsBySelectorOfStaticBinding<A...>::containsNoneOf;
    using ContainsBySelectorOfStaticBinding<A...>::containsAllOf;
  };
};
} // namespace deriv

template <typename R, typename P> class CDS_ATTR(inheritsEBOs) ContainsOfStaticBinding :
    public containsOfDeriv::MethodSelector<P>::template Type<R>::Type {};
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDINGS_STATIC_CONTAINS_OF_BINDING_STATIC_HPP
