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

#include "../../algorithm/GenericContains.hpp"
#include "../../iterator/Iterator.hpp"

namespace cds {
namespace impl {
using std::initializer_list;

using meta::IterableTraits;
using meta::ReturnOf;
using meta::rvalue;

using functional::Equal;

template <typename R> class ContainsByValueOfStaticBinding {
protected:
  using Value = typename IterableTraits<R>::Value;
  using E = Equal<>;

public:
  template <typename F = initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, equal)) {
        return true;
      }
    }
    return false;
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyNotOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<F>(), rvalue<Value>(), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(*iterable), e = cds::end(*iterable); i != e; ++i) {
      if (!contains(cds::forward<F>(from), *i, equal)) {
        return true;
      }
    }
    return false;
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAllOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (!contains(*iterable, *i, equal)) {
        return false;
      }
    }
    return true;
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsNoneOf(F&& from)
      const CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, equal)) {
        return false;
      }
    }
    return true;
  }
};

template <typename R> class ContainsByProjectorOfStaticBinding {
protected:
  using Value = typename IterableTraits<R>::Value;
  using E = Equal<>;

public:
  template <typename P, typename F = initializer_list<ReturnOf<P>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyOf(F&& from, P&& projector) const
      CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), cds::forward<P>(projector), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, cds::forward<P>(projector), equal)) {
        return true;
      }
    }
    return false;
  }

  template <typename P, typename F = initializer_list<ReturnOf<P>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAnyNotOf(F&& from, P&& projector)
      const CDS_ATTR(noexcept(noexcept(contains(cds::forward<F>(from), rvalue<Value>(), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(*iterable), e = cds::end(*iterable); i != e; ++i) {
      if (!contains(cds::forward<F>(from), cds::forward<P>(projector)(*i), equal)) {
        return true;
      }
    }
    return false;
  }

  template <typename P, typename F = initializer_list<ReturnOf<P>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsAllOf(F&& from, P&& projector) const
      CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), cds::forward<P>(projector), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (!contains(*iterable, *i, cds::forward<P>(projector), equal)) {
        return false;
      }
    }
    return true;
  }

  template <typename P, typename F = initializer_list<ReturnOf<P>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto containsNoneOf(F&& from, P&& projector) const
      CDS_ATTR(noexcept(noexcept(contains(rvalue<R>(), rvalue<Value>(), cds::forward<P>(projector), E())))) -> bool {
    E const equal;
    auto const* iterable = static_cast<R const*>(this);
    for (auto i = cds::begin(cds::forward<F>(from)), e = cds::end(cds::forward<F>(from)); i != e; ++i) {
      if (contains(*iterable, *i, cds::forward<P>(projector), equal)) {
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
using sel::Projector;
using sel::ContainsSelector;

template <
    typename P,
    typename = typename ContainsSelector<P, Value>::Type,
    typename = typename ContainsSelector<P, Projector>::Type
> struct MethodSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Value, Projector>::value,
      "Must select Value, Projector or both"
  );
};

template <typename P> struct MethodSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type : public ContainsByValueOfStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type : public ContainsByProjectorOfStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public ContainsByValueOfStaticBinding<A...>,
      public ContainsByProjectorOfStaticBinding<A...> {
  public:
    using ContainsByValueOfStaticBinding<A...>::containsAnyOf;
    using ContainsByValueOfStaticBinding<A...>::containsAnyNotOf;
    using ContainsByValueOfStaticBinding<A...>::containsNoneOf;
    using ContainsByValueOfStaticBinding<A...>::containsAllOf;

    using ContainsByProjectorOfStaticBinding<A...>::containsAnyOf;
    using ContainsByProjectorOfStaticBinding<A...>::containsAnyNotOf;
    using ContainsByProjectorOfStaticBinding<A...>::containsNoneOf;
    using ContainsByProjectorOfStaticBinding<A...>::containsAllOf;
  };
};
} // namespace deriv

template <typename R, typename P> class CDS_ATTR(inheritsEBOs) ContainsOfStaticBinding :
    public containsOfDeriv::MethodSelector<P>::template Type<R> {};
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDINGS_STATIC_CONTAINS_OF_BINDING_STATIC_HPP
