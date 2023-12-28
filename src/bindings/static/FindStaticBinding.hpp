//
// Created by loghin on 12/17/23.
//

#ifndef CDS_SHARED_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
#define CDS_SHARED_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP

#include "../BindingSelectors.hpp"
#include <initializer_list>
#include <cds/functional/FunctionalInterface>

namespace cds {
namespace impl {
using std::initializer_list;

using meta::rvalue;
using meta::IterableTraits;

template <typename R> struct FindOfResultMappingTraits {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto adapt(R const& iterable, T&& iterator) -> T {
    (void) iterable;
    return cds::forward<T>(iterator);
  }
};

template <typename R, typename Tr = FindOfResultMappingTraits<R>, typename = void>
class FindFirstOfByValueStaticBinding {};

template <typename R, typename Tr> class FindFirstOfByValueStaticBinding<R, Tr> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using Iterator = typename IterableTraits<R>::Iterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), rvalue<Iterator>()));

public:
  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstOf(rvalue<R>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findFirstOf(*iterable, cds::forward<F>(from)));
  }

  template <typename F = initializer_list<Value>> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(
      F&& from
  ) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstNotOf(rvalue<R>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findFirstNotOf(*iterable, cds::forward<F>(from)));
  }
};

template <typename R, typename Tr> class FindFirstOfByValueStaticBinding<R const, Tr> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using Iterator = typename IterableTraits<R>::ConstIterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), rvalue<Iterator>()));

public:
  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstOf(rvalue<R const>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, impl::findFirstOf(*iterable, cds::forward<F>(from)));
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstNotOf(rvalue<R const>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, impl::findFirstNotOf(*iterable, cds::forward<F>(from)));
  }
};

template <typename R, typename Tr = FindOfResultMappingTraits<R>, typename = void>
class FindLastOfByValueStaticBinding {};

template <typename R, typename Tr> class FindLastOfByValueStaticBinding<R, Tr> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using Iterator = typename IterableTraits<R>::ReverseIterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), rvalue<Iterator>()));

public:
  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastOf(rvalue<R>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findLastOf(*iterable, cds::forward<F>(from)));
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastNotOf(rvalue<R>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findLastNotOf(*iterable, cds::forward<F>(from)));
  }
};

template <typename R, typename Tr> class FindLastOfByValueStaticBinding<R const, Tr> {
protected:
  using Value = typename ::cds::meta::IterableTraits<R>::Value;
  using Iterator = typename ::cds::meta::IterableTraits<R>::ConstReverseIterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), ::cds::meta::rvalue<Iterator>()));

public:
  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastOf(rvalue<R const>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, impl::findLastOf(*iterable, cds::forward<F>(from)));
  }

  template <typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastNotOf(rvalue<R const>(), cds::forward<F>(from)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, impl::findLastNotOf(*iterable, cds::forward<F>(from)));
  }
};

template <typename R, typename Tr = FindOfResultMappingTraits<R>, typename = void>
class FindFirstOfBySelectorStaticBinding {};

template <typename R, typename Tr> class FindFirstOfBySelectorStaticBinding<R, Tr> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using Iterator = typename IterableTraits<R>::Iterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), rvalue<Iterator>()));

public:
  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstOf(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findFirstOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstNotOf(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findFirstNotOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
  }
};

template <typename R, typename Tr> class FindFirstOfBySelectorStaticBinding<R const, Tr> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using Iterator = typename IterableTraits<R>::ConstIterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), rvalue<Iterator>()));

public:
  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstOf(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, cds::impl::findFirstOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findFirstNotOf(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, impl::findFirstNotOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
  }
};

template <typename R, typename Tr = FindOfResultMappingTraits<R>, typename = void>
class FindLastOfBySelectorStaticBinding {};

template <typename R, typename Tr> class FindLastOfBySelectorStaticBinding<R, Tr> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using Iterator = typename IterableTraits<R>::ReverseIterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), rvalue<Iterator>()));

public:
  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastOf(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findLastOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, S&& selector) CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastNotOf(rvalue<R>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto* iterable = static_cast<R*>(this);
    return Tr::adapt(*iterable, impl::findLastNotOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
  }
};

template <typename R, typename Tr> class FindLastOfBySelectorStaticBinding<R const, Tr> {
protected:
  using Value = typename IterableTraits<R>::Value;
  using Iterator = typename IterableTraits<R>::ConstReverseIterator;
  using Returned = decltype(Tr::adapt(rvalue<R>(), rvalue<Iterator>()));

public:
  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastOf(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, impl::findLastOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
  }

  template <typename S, typename F = initializer_list<Value>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, S&& selector) const CDS_ATTR(noexcept(noexcept(
      Tr::adapt(rvalue<R>(), impl::findLastNotOf(rvalue<R const>(), cds::forward<F>(from), cds::forward<S>(selector)))
  ))) -> Returned {
    auto const* iterable = static_cast<R const*>(this);
    return Tr::adapt(*iterable, impl::findLastNotOf(*iterable, cds::forward<F>(from), cds::forward<S>(selector)));
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
using sel::Forward;
using sel::Backward;
using sel::Mutable;
using sel::Immutable;
using sel::ContainsSelector;

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
    public FindFirstOfByValueStaticBinding<A...> {};
};

template <typename P> struct ForwardMethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
    public FindFirstOfBySelectorStaticBinding<A...> {};
};

template <typename P> struct ForwardMethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindFirstOfByValueStaticBinding<A...>,
      public FindFirstOfBySelectorStaticBinding<A...> {
  public:
    using FindFirstOfByValueStaticBinding<A...>::findFirstOf;
    using FindFirstOfByValueStaticBinding<A...>::findFirstNotOf;

    using FindFirstOfBySelectorStaticBinding<A...>::findFirstOf;
    using FindFirstOfBySelectorStaticBinding<A...>::findFirstNotOf;
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
    using ForwardMethodSelector<P>::template Type<R, A...>::findFirstOf;
    using ForwardMethodSelector<P>::template Type<R, A...>::findFirstNotOf;
    using ForwardMethodSelector<P>::template Type<R const, A...>::findFirstOf;
    using ForwardMethodSelector<P>::template Type<R const, A...>::findFirstNotOf;
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
    public FindLastOfByValueStaticBinding<A...> {};
};

template <typename P> struct BackwardMethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
    public FindLastOfBySelectorStaticBinding<A...> {};
};

template <typename P> struct BackwardMethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public FindLastOfByValueStaticBinding<A...>,
      public FindLastOfBySelectorStaticBinding<A...> {
  public:
    using FindLastOfByValueStaticBinding<A...>::findLastOf;
    using FindLastOfByValueStaticBinding<A...>::findLastNotOf;

    using FindLastOfBySelectorStaticBinding<A...>::findLastOf;
    using FindLastOfBySelectorStaticBinding<A...>::findLastNotOf;
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
    using BackwardMethodSelector<P>::template Type<R, A...>::findLastOf;
    using BackwardMethodSelector<P>::template Type<R, A...>::findLastNotOf;
    using BackwardMethodSelector<P>::template Type<R const, A...>::findLastOf;
    using BackwardMethodSelector<P>::template Type<R const, A...>::findLastNotOf;
  };
};

template <
    typename P,
    typename = typename ContainsSelector<P, Forward>::Type,
    typename = typename ContainsSelector<P, Backward>::Type
> struct DirectionalSelector {
  using Type = meta::Int<0>;
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
} // namespace findOfDeriv

template <typename R, typename P, typename Tr = FindOfResultMappingTraits<R>> struct FindOfStaticBinding :
    public findOfDeriv::DirectionalSelector<P>::template Type<R, Tr> {};
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
