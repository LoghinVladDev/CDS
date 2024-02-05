//
// Created by loghin on 12/17/23.
//

#ifndef CDS_SHARED_BINDINGS_STATIC_FIND_BINDING_STATIC_HPP
#define CDS_SHARED_BINDINGS_STATIC_FIND_BINDING_STATIC_HPP
#pragma once

#include "../BindingSelectors.hpp"
#include <cds/functional/FunctionalInterface>
#include <cds/Utility>

namespace cds {
namespace impl {
using meta::IterableTraits;

using functional::Equal;

template <typename, typename, typename, typename = void> class FindByValueStaticBinding {};

template <typename R, typename TrAll, typename TrOne> class FindByValueStaticBinding<R, TrAll, TrOne> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<V>(value), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<V>(value), P(), TrAll())) {
    return impl::find(*static_cast<R*>(this), cds::forward<V>(value), P(), TrAll());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<V>(value), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<V>(value), P(), TrAll())) {
    return impl::find(cds::move(*static_cast<R*>(this)), cds::forward<V>(value), P(), TrAll());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<V>(value), P(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<V>(value), P(), TrOne())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<V>(value), P(), TrOne());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<V>(value), P(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<V>(value), P(), TrOne())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<V>(value), P(), TrOne());
  }
};

template <typename R, typename TrAll, typename TrOne> class FindByValueStaticBinding<R const, TrAll, TrOne> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<V>(value), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<V>(value), P(), TrAll())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<V>(value), P(), TrAll());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<V>(value), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<V>(value), P(), TrAll())) {
    return impl::find(cds::move(*static_cast<R const*>(this)), cds::forward<V>(value), P(), TrAll());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value) const CDS_ATTR(noexcept(
      noexcept(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), P(), TrOne()))
  )) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), P(), TrOne())) {
    return impl::findFirst(*static_cast<R const*>(this), cds::forward<V>(value), P(), TrOne());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value) const CDS_ATTR(noexcept(
      noexcept(impl::findLast(rvalue<R const>(), cds::forward<V>(value), P(), TrOne()))
  )) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<V>(value), P(), TrOne())) {
    return impl::findLast(*static_cast<R const*>(this), cds::forward<V>(value), P(), TrOne());
  }
};

template <typename, typename, typename, typename = void> class FindBySelectorStaticBinding {};

template <typename R, typename TrAll, typename TrOne> class FindBySelectorStaticBinding<R, TrAll, TrOne> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())) {
    return impl::find(*static_cast<R*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll());
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())) {
    return impl::find(
        cds::move(*static_cast<R*>(this)), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll()
    );
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne());
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne());
  }
};

template <typename R, typename TrAll, typename TrOne> class FindBySelectorStaticBinding<R const, TrAll, TrOne> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll());
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll())) {
    return impl::find(
        cds::move(*static_cast<R const*>(this)), cds::forward<V>(value), cds::forward<S>(selector), P(), TrAll()
    );
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value, S&& selector) const CDS_ATTR(noexcept(
      noexcept(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne()))
  )) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findFirst(
        *static_cast<R const*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne()
    );
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value, S&& selector) const CDS_ATTR(noexcept(
      noexcept(impl::findLast(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne()))
  )) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findLast(
        *static_cast<R const*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), TrOne()
    );
  }
};

namespace findDeriv {
using sel::Mutable;
using sel::Immutable;
using sel::Value;
using sel::Selector;
using sel::ContainsSelector;

using meta::Int;
using meta::Any;
using meta::Bind;
using meta::Ph;
using meta::True;
using meta::False;

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
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindByValueStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindBySelectorStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindByValueStaticBinding<A...>,
      public FindBySelectorStaticBinding<A...> {
  public:
    using FindByValueStaticBinding<A...>::find;
    using FindByValueStaticBinding<A...>::findFirst;
    using FindByValueStaticBinding<A...>::findLast;

    using FindBySelectorStaticBinding<A...>::find;
    using FindBySelectorStaticBinding<A...>::findFirst;
    using FindBySelectorStaticBinding<A...>::findLast;
  };
};

template <
    typename P,
    typename = typename ContainsSelector<P, Mutable>::Type,
    typename = typename ContainsSelector<P, Immutable>::Type
> struct MutationSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Mutable, Immutable>::value,
      "Must select Mutable, Immutable or both"
  );
};

template <typename P> struct MutationSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public MethodSelector<P>::template Type<A...> {};
};

template <typename P> struct MutationSelector<P, False, True> {
  template <typename R, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public MethodSelector<P>::template Type<R const, A...> {};
};

template <typename P> struct MutationSelector<P, True, True> {
  template <typename R, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public MethodSelector<P>::template Type<R, A...>,
      public MethodSelector<P>::template Type<R const, A...> {
  public:
    using MethodSelector<P>::template Type<R, A...>::find;
    using MethodSelector<P>::template Type<R, A...>::findFirst;
    using MethodSelector<P>::template Type<R, A...>::findLast;

    using MethodSelector<P>::template Type<R const, A...>::find;
    using MethodSelector<P>::template Type<R const, A...>::findFirst;
    using MethodSelector<P>::template Type<R const, A...>::findLast;
  };
};
} // namespace findDeriv

template <
    typename R, typename P,
    typename TrAll = FindResultTransformer<>,
    typename TrOne = FindPreserveTransformer<>
> class CDS_ATTR(inheritsEBOs) FindStaticBinding :
    public findDeriv::MutationSelector<P>::template Type<R, TrAll, TrOne> {};
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDINGS_STATIC_FIND_BINDING_STATIC_HPP
