//
// Created by loghin on 12/17/23.
//

#ifndef CDS_SHARED_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
#define CDS_SHARED_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
#pragma once

#include "../BindingSelectors.hpp"
#include <initializer_list>
#include <cds/functional/FunctionalInterface>
#include <cds/Utility>

namespace cds {
namespace impl {
using std::initializer_list;

using meta::rvalue;
using meta::IterableTraits;

using impl::Contains;
using impl::NotContains;

using functional::Equal;

template <typename, typename, typename, typename = void> class FindOfByValueStaticBinding {};

template <typename R, typename TrAll, typename TrOne> class FindOfByValueStaticBinding<R, TrAll, TrOne> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using P = Contains<Equal<>>;
  using NP = NotContains<Equal<>>;

public:
  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<F>(from), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<F>(from), P(), TrAll())) {
    return impl::find(*static_cast<R*>(this), cds::forward<F>(from), P(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<F>(from), NP(), TrAll())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<F>(from), NP(), TrAll())) {
    return impl::find(*static_cast<R*>(this), cds::forward<F>(from), NP(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<F>(from), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<F>(from), P(), TrAll())) {
    return impl::find(cds::move(*static_cast<R*>(this)), cds::forward<F>(from), P(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<F>(from), NP(), TrAll())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<F>(from), NP(), TrAll())) {
    return impl::find(cds::move(*static_cast<R*>(this)), cds::forward<F>(from), NP(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<F>(from), P(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<F>(from), P(), TrOne())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<F>(from), P(), TrOne());
  }

  template <typename F = initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(
      F&& from
  ) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<F>(from), NP(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<F>(from), NP(), TrOne())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<F>(from), NP(), TrOne());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<F>(from), P(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<F>(from), P(), TrOne())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<F>(from), P(), TrOne());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<F>(from), NP(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<F>(from), NP(), TrOne())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<F>(from), NP(), TrOne());
  }
};

template <typename R, typename TrAll, typename TrOne> class FindOfByValueStaticBinding<R const, TrAll, TrOne> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using P = Contains<Equal<>>;
  using NP = NotContains<Equal<>>;

public:
  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<F>(from), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<F>(from), P(), TrAll())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<F>(from), P(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<F>(from), NP(), TrAll())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<F>(from), NP(), TrAll())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<F>(from), NP(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<F>(from), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<F>(from), P(), TrAll())) {
    return impl::find(cds::move(*static_cast<R const*>(this)), cds::forward<F>(from), P(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<F>(from), NP(), TrAll())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<F>(from), NP(), TrAll())) {
    return impl::find(cds::move(*static_cast<R const*>(this)), cds::forward<F>(from), NP(), TrAll());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), cds::forward<F>(from), P(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<F>(from), P(), TrOne())) {
    return impl::findFirst(*static_cast<R const*>(this), cds::forward<F>(from), P(), TrOne());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), cds::forward<F>(from), NP(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<F>(from), NP(), TrOne())) {
    return impl::findFirst(*static_cast<R const*>(this), cds::forward<F>(from), NP(), TrOne());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), cds::forward<F>(from), P(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<F>(from), P(), TrOne())) {
    return impl::findLast(*static_cast<R const*>(this), cds::forward<F>(from), P(), TrOne());
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), cds::forward<F>(from), NP(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<F>(from), NP(), TrOne())) {
    return impl::findLast(*static_cast<R const*>(this), cds::forward<F>(from), NP(), TrOne());
  }
};

template <typename, typename, typename, typename = void> class FindOfBySelectorStaticBinding {};

template <typename R, typename TrAll, typename TrOne> class FindOfBySelectorStaticBinding<R, TrAll, TrOne> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using P = Contains<Equal<>>;
  using NP = NotContains<Equal<>>;

public:
  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, S&& selector)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector) , P(), TrAll())) {
    return impl::find(*static_cast<R*>(this), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, S&& selector)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())
  ))) -> decltype(impl::find(lvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())) {
    return impl::find(*static_cast<R*>(this), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, S&& selector)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector) , P(), TrAll())) {
    return impl::find(cds::move(*static_cast<R*>(this)), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, S&& selector)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())
  ))) -> decltype(impl::find(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())) {
    return impl::find(cds::move(*static_cast<R*>(this)), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())) {
    return impl::findFirst(*static_cast<R*>(this), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())) {
    return impl::findLast(*static_cast<R*>(this), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne());
  }
};

template <typename R, typename TrAll, typename TrOne> class FindOfBySelectorStaticBinding<R const, TrAll, TrOne> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using P = Contains<Equal<>>;
  using NP = NotContains<Equal<>>;

public:
  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, S&& selector) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector) , P(), TrAll())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, S&& selector) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())
  ))) -> decltype(impl::find(lvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())) {
    return impl::find(*static_cast<R const*>(this), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, S&& selector) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector) , P(), TrAll())) {
    return impl::find(
        cds::move(*static_cast<R const*>(this)), cds::forward<F>(from), cds::forward<S>(selector), P(), TrAll()
    );
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, S&& selector) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())
  ))) -> decltype(impl::find(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll())) {
    return impl::find(
        cds::move(*static_cast<R const*>(this)), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrAll()
    );
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findFirst(*static_cast<R const*>(this), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())
  ))) -> decltype(impl::findFirst(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())) {
    return impl::findFirst(*static_cast<R const*>(this), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne())) {
    return impl::findLast(*static_cast<R const*>(this), cds::forward<F>(from), cds::forward<S>(selector), P(), TrOne());
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())
  ))) -> decltype(impl::findLast(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne())) {
    return impl::findLast(*static_cast<R const*>(this), cds::forward<F>(from), cds::forward<S>(selector), NP(), TrOne());
  }
};

namespace findOfDeriv {
using meta::True;
using meta::False;
using meta::Any;
using meta::Bind;
using meta::Ph;

using sel::Value;
using sel::Selector;
using sel::Mutable;
using sel::Immutable;
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
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
    public FindOfByValueStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
    public FindOfBySelectorStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindOfByValueStaticBinding<A...>,
      public FindOfBySelectorStaticBinding<A...> {
  public:
    using FindOfByValueStaticBinding<A...>::findOf;
    using FindOfByValueStaticBinding<A...>::findNotOf;
    using FindOfByValueStaticBinding<A...>::findFirstOf;
    using FindOfByValueStaticBinding<A...>::findFirstNotOf;
    using FindOfByValueStaticBinding<A...>::findLastOf;
    using FindOfByValueStaticBinding<A...>::findLastNotOf;

    using FindOfBySelectorStaticBinding<A...>::findOf;
    using FindOfBySelectorStaticBinding<A...>::findNotOf;
    using FindOfBySelectorStaticBinding<A...>::findFirstOf;
    using FindOfBySelectorStaticBinding<A...>::findFirstNotOf;
    using FindOfBySelectorStaticBinding<A...>::findLastOf;
    using FindOfBySelectorStaticBinding<A...>::findLastNotOf;
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
    using MethodSelector<P>::template Type<R, A...>::findOf;
    using MethodSelector<P>::template Type<R, A...>::findNotOf;
    using MethodSelector<P>::template Type<R const, A...>::findOf;
    using MethodSelector<P>::template Type<R const, A...>::findNotOf;

    using MethodSelector<P>::template Type<R, A...>::findFirstOf;
    using MethodSelector<P>::template Type<R, A...>::findFirstNotOf;
    using MethodSelector<P>::template Type<R const, A...>::findFirstOf;
    using MethodSelector<P>::template Type<R const, A...>::findFirstNotOf;

    using MethodSelector<P>::template Type<R, A...>::findLastOf;
    using MethodSelector<P>::template Type<R, A...>::findLastNotOf;
    using MethodSelector<P>::template Type<R const, A...>::findLastOf;
    using MethodSelector<P>::template Type<R const, A...>::findLastNotOf;
  };
};
} // namespace findOfDeriv

template <
    typename R, typename P,
    typename TrAll = FindResultTransformer<>,
    typename TrOne = FindPreserveTransformer<>
> class CDS_ATTR(inheritsEBOs) FindOfStaticBinding :
    public findOfDeriv::MutationSelector<P>::template Type<R, TrAll, TrOne> {};
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
