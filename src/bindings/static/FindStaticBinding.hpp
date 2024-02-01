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

template <typename R, typename Tr, typename, typename = void> class FindByValueStaticBinding {};

template <typename R, typename Tr, typename _> class FindByValueStaticBinding<R, Tr, _> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<V>(value), P(), Tr())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<V>(value), P(), Tr())) {
    return impl::find(*static_cast<R*>(this), cds::forward<V>(value), P(), Tr());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<V>(value), P(), Tr())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<V>(value), P(), Tr())) {
    return impl::find(cds::move(*static_cast<R*>(this)), cds::forward<V>(value), P(), Tr());
  }
};

template <typename R, typename Tr, typename _> class FindByValueStaticBinding<R const, Tr, _> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<V>(value), P(), Tr())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<V>(value), P(), Tr())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<V>(value), P(), Tr());
  }

  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<V>(value), P(), Tr())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<V>(value), P(), Tr())) {
    return impl::find(cds::move(*static_cast<R const*>(this)), cds::forward<V>(value), P(), Tr());
  }
};

template <typename R, typename, typename Tr, typename = void> class FindFirstByValueStaticBinding {};

template <typename R, typename _, typename Tr> class FindFirstByValueStaticBinding<R, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<V>(value), P(), Tr())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<V>(value), P(), Tr())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<V>(value), P(), Tr());
  }
};

template <typename R, typename _, typename Tr> class FindFirstByValueStaticBinding<R const, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value) const CDS_ATTR(noexcept(
      noexcept(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), P(), Tr()))
  )) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), P(), Tr())) {
    return impl::findFirst(*static_cast<R const*>(this), cds::forward<V>(value), P(), Tr());
  }
};

template <typename R, typename, typename Tr, typename = void> class FindLastByValueStaticBinding {};

template <typename R, typename _, typename Tr> class FindLastByValueStaticBinding<R, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<V>(value), P(), Tr())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<V>(value), P(), Tr())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<V>(value), P(), Tr());
  }
};

template <typename R, typename _, typename Tr> class FindLastByValueStaticBinding<R const, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value) const CDS_ATTR(noexcept(
      noexcept(impl::findLast(rvalue<R const>(), cds::forward<V>(value), P(), Tr()))
  )) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<V>(value), P(), Tr())) {
    return impl::findLast(*static_cast<R const*>(this), cds::forward<V>(value), P(), Tr());
  }
};

template <typename R, typename Tr, typename, typename = void> class FindBySelectorStaticBinding {};

template <typename R, typename Tr, typename _> class FindBySelectorStaticBinding<R, Tr, _> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::find(*static_cast<R*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr());
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::find(cds::move(*static_cast<R*>(this)), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr());
  }
};

template <typename R, typename Tr, typename _> class FindBySelectorStaticBinding<R const, Tr, _> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr());
  }

  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto find(V&& value, S&& selector) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::find(
        cds::move(*static_cast<R const*>(this)), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr()
    );
  }
};

template <typename R, typename, typename Tr, typename = void> class FindFirstBySelectorStaticBinding {};

template <typename R, typename _, typename Tr> class FindFirstBySelectorStaticBinding<R, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr());
  }
};

template <typename R, typename _, typename Tr> class FindFirstBySelectorStaticBinding<R const, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(V&& value, S&& selector) const CDS_ATTR(noexcept(
      noexcept(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr()))
  )) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::findFirst(*static_cast<R const*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr());
  }
};

template <typename R, typename, typename Tr, typename = void> class FindLastBySelectorStaticBinding {};

template <typename R, typename _, typename Tr> class FindLastBySelectorStaticBinding<R, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr());
  }
};

template <typename R, typename _, typename Tr> class FindLastBySelectorStaticBinding<R const, _, Tr> {
protected:
  using P = Equal<>;

public:
  template <typename V, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(V&& value, S&& selector) const CDS_ATTR(noexcept(
      noexcept(impl::findLast(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr()))
  )) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr())) {
    return impl::findLast(*static_cast<R const*>(this), cds::forward<V>(value), cds::forward<S>(selector), P(), Tr());
  }
};

namespace findDeriv {
using sel::Forward;
using sel::Backward;
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
> struct ForwardMethodSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Value, Selector>::value,
      "Must select Value, Selector or both"
  );
};

template <typename P> struct ForwardMethodSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindByValueStaticBinding<A...>,
      public FindFirstByValueStaticBinding<A...> {};
};

template <typename P> struct ForwardMethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindBySelectorStaticBinding<A...>,
      public FindFirstBySelectorStaticBinding<A...> {};
};

template <typename P> struct ForwardMethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindByValueStaticBinding<A...>,
      public FindBySelectorStaticBinding<A...>,
      public FindFirstByValueStaticBinding<A...>,
      public FindFirstBySelectorStaticBinding<A...> {
  public:
    using FindByValueStaticBinding<A...>::find;
    using FindBySelectorStaticBinding<A...>::find;

    using FindFirstByValueStaticBinding<A...>::findFirst;
    using FindFirstBySelectorStaticBinding<A...>::findFirst;
  };
};

template <
    typename P,
    typename = typename ContainsSelector<P, Mutable>::Type,
    typename = typename ContainsSelector<P, Immutable>::Type
> struct ForwardMutationSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Mutable, Immutable>::value,
      "Must select Mutable, Immutable or both"
  );
};

template <typename P> struct ForwardMutationSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public ForwardMethodSelector<P>::template Type<A...> {};
};

template <typename P> struct ForwardMutationSelector<P, False, True> {
  template <typename R, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public ForwardMethodSelector<P>::template Type<R const, A...> {};
};

template <typename P> struct ForwardMutationSelector<P, True, True> {
  template <typename R, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public ForwardMethodSelector<P>::template Type<R, A...>,
      public ForwardMethodSelector<P>::template Type<R const, A...> {
  public:
    using ForwardMethodSelector<P>::template Type<R, A...>::find;
    using ForwardMethodSelector<P>::template Type<R const, A...>::find;

    using ForwardMethodSelector<P>::template Type<R, A...>::findFirst;
    using ForwardMethodSelector<P>::template Type<R const, A...>::findFirst;
  };
};

template <
    typename P,
    typename = typename ContainsSelector<P, Value>::Type,
    typename = typename ContainsSelector<P, Selector>::Type
> struct BackwardMethodSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Value, Selector>::value,
      "Must select Value, Selector or both"
  );
};

template <typename P> struct BackwardMethodSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindLastByValueStaticBinding<A...> {};
};

template <typename P> struct BackwardMethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindLastBySelectorStaticBinding<A...> {};
};

template <typename P> struct BackwardMethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindLastByValueStaticBinding<A...>,
      public FindLastBySelectorStaticBinding<A...> {
  public:
    using FindLastByValueStaticBinding<A...>::findLast;
    using FindLastBySelectorStaticBinding<A...>::findLast;
  };
};

template <
    typename P,
    typename = typename ContainsSelector<P, Mutable>::Type,
    typename = typename ContainsSelector<P, Immutable>::Type
> struct BackwardMutationSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Mutable, Immutable>::value,
      "Must select Mutable, Immutable or both"
  );
};

template <typename P> struct BackwardMutationSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public BackwardMethodSelector<P>::template Type<A...> {};
};

template <typename P> struct BackwardMutationSelector<P, False, True> {
  template <typename R, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public BackwardMethodSelector<P>::template Type<R const, A...> {};
};

template <typename P> struct BackwardMutationSelector<P, True, True> {
  template <typename R, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public BackwardMethodSelector<P>::template Type<R, A...>,
      public BackwardMethodSelector<P>::template Type<R const, A...> {
  public:
    using BackwardMethodSelector<P>::template Type<R, A...>::findLast;
    using BackwardMethodSelector<P>::template Type<R const, A...>::findLast;
  };
};

template <
    typename P,
    typename = typename ContainsSelector<P, Forward>::Type,
    typename = typename ContainsSelector<P, Backward>::Type
> struct DirectionalSelector {
  using Type = Int<0>;
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Forward, Backward>::value,
      "Must select Forward, Backward or both"
  );
};

template <typename P> struct DirectionalSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public ForwardMutationSelector<P>::template Type<A...> {};
};

template <typename P> struct DirectionalSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public BackwardMutationSelector<P>::template Type<A...> {};
};

template <typename P> struct DirectionalSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public ForwardMutationSelector<P>::template Type<A...>,
      public BackwardMutationSelector<P>::template Type<A...> {};
};
} // namespace findDeriv

template <
    typename R, typename P,
    typename Tr = impl::FindResultTransformer<>,
    typename TrFirstLast = impl::FindPreserveTransformer<>
> struct FindStaticBinding :
    public findDeriv::DirectionalSelector<P>::template Type<R, Tr, TrFirstLast> {};
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDINGS_STATIC_FIND_BINDING_STATIC_HPP
