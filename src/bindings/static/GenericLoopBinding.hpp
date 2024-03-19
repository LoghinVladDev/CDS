//
// Created by loghin on 3/18/24.
//

#ifndef CDS_BINDINGS_STATIC_GENERIC_LOOP_BINDING_HPP
#define CDS_BINDINGS_STATIC_GENERIC_LOOP_BINDING_HPP
#pragma once

#include <cds/meta/IteratorTraits>

#include "../../algorithm/GenericLoop.hpp"
#include "../BindingSelectors.hpp"

namespace cds {
namespace impl {
using meta::rvalue;
using meta::IterableTraits;
using meta::SentinelFor;

template <typename, typename = void> class GenericLoopStaticBinding {};

template <typename I> class GenericLoopStaticBinding<I> {
  using Iterator = typename IterableTraits<I>::Iterator;
  using Sentinel = SentinelFor<Iterator>;
public:
  template <typename C> CDS_ATTR(2(nodiscard, constexpr(14))) auto forEach(C&& consumer) CDS_ATTR(noexcept(
      noexcept(impl::forEach(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<C>(consumer)))
  )) -> decltype(impl::forEach(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<C>(consumer))) {
    return impl::forEach(
        cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), cds::forward<C>(consumer)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto some(Size count, P&& predicate) CDS_ATTR(noexcept(
      noexcept(impl::some(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate)))
  )) -> decltype(impl::some(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))) {
    return impl::some(
        cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto atLeast(Size count, P&& predicate) CDS_ATTR(noexcept(
      noexcept(impl::atLeast(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate)))
  )) -> decltype(impl::atLeast(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))) {
    return impl::atLeast(
        cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto atMost(Size count, P&& predicate) CDS_ATTR(noexcept(
      noexcept(impl::atMost(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate)))
  )) -> decltype(impl::atMost(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))) {
    return impl::atMost(
        cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto moreThan(Size count, P&& predicate) CDS_ATTR(
      noexcept(noexcept(impl::moreThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))))
  ) -> decltype(impl::moreThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))) {
    return impl::moreThan(
        cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto lessThan(Size count, P&& predicate) CDS_ATTR(
      noexcept(noexcept(impl::lessThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))))
  ) -> decltype(impl::lessThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))) {
    return impl::lessThan(
        cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto count(P&& predicate) CDS_ATTR(noexcept(
      noexcept(impl::count(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::count(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::count(
        cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto any(P&& predicate) CDS_ATTR(noexcept(
      noexcept(impl::any(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::any(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::any(cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), cds::forward<P>(predicate));
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto all(P&& predicate) CDS_ATTR(noexcept(
      noexcept(impl::all(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::all(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::all(cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), cds::forward<P>(predicate));
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto none(P&& predicate) CDS_ATTR(noexcept(
      noexcept(impl::none(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::none(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::none(cds::begin(*static_cast<I*>(this)), cds::end(*static_cast<I*>(this)), cds::forward<P>(predicate));
  }
};

template <typename I> class GenericLoopStaticBinding<I const> {
    using Iterator = typename IterableTraits<I>::ConstIterator;
    using Sentinel = SentinelFor<Iterator>;
public:
  template <typename C> CDS_ATTR(2(nodiscard, constexpr(14))) auto forEach(C&& consumer) const CDS_ATTR(noexcept(
      noexcept(impl::forEach(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<C>(consumer)))
  )) -> decltype(impl::forEach(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<C>(consumer))) {
    return impl::forEach(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)), cds::forward<C>(consumer)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto some(Size count, P&& predicate) const CDS_ATTR(noexcept(noexcept(
      impl::some(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ))) -> decltype(impl::some(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))) {
    return impl::some(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto atLeast(Size count, P&& predicate) const CDS_ATTR(noexcept(noexcept(
      impl::atLeast(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ))) -> decltype(
      impl::atLeast(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ) {
    return impl::atLeast(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto atMost(Size count, P&& predicate) const CDS_ATTR(noexcept(noexcept(
      impl::atMost(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ))) -> decltype(
      impl::atMost(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ) {
    return impl::atMost(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto moreThan(Size count, P&& predicate) const CDS_ATTR(noexcept(noexcept(
      impl::moreThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ))) -> decltype(
      impl::moreThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ) {
    return impl::moreThan(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto lessThan(Size count, P&& predicate) const CDS_ATTR(noexcept(noexcept(
      impl::lessThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ))) -> decltype(
      impl::lessThan(rvalue<Iterator>(), rvalue<Sentinel>(), count, cds::forward<P>(predicate))
  ) {
    return impl::lessThan(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        count, cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto count(P&& predicate) const CDS_ATTR(noexcept(
      noexcept(impl::count(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::count(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::count(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto any(P&& predicate) const CDS_ATTR(noexcept(
      noexcept(impl::any(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::any(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::any(
        cds::begin(*static_cast<I const*>(this)),
        cds::end(*static_cast<I const*>(this)), cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto all(P&& predicate) const CDS_ATTR(noexcept(
      noexcept(impl::all(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::all(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::all(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        cds::forward<P>(predicate)
    );
  }

  template <typename P> CDS_ATTR(2(nodiscard, constexpr(14))) auto none(P&& predicate) const CDS_ATTR(noexcept(
      noexcept(impl::none(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate)))
  )) -> decltype(impl::none(rvalue<Iterator>(), rvalue<Sentinel>(), cds::forward<P>(predicate))) {
    return impl::none(
        cds::begin(*static_cast<I const*>(this)), cds::end(*static_cast<I const*>(this)),
        cds::forward<P>(predicate)
    );
  }
};

namespace genericLoopDeriv {
using meta::True;
using meta::False;
using meta::Any;
using meta::Bind;
using meta::Ph;

using sel::Mutable;
using sel::Immutable;
using sel::ContainsSelector;
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
  template <typename... A> class CDS_ATTR(inheritsEBOs) Type : public GenericLoopStaticBinding<A...> {};
};

template <typename P> struct MutationSelector<P, False, True> {
  template <typename I, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public GenericLoopStaticBinding<I const, A...> {};
};

template <typename P> struct MutationSelector<P, True, True> {
  template <typename I, typename... A> class CDS_ATTR(inheritsEBOs) Type :
      public GenericLoopStaticBinding<I, A...>,
      public GenericLoopStaticBinding<I const, A...> {
  public:
    using GenericLoopStaticBinding<I, A...>::forEach;
    using GenericLoopStaticBinding<I, A...>::some;
    using GenericLoopStaticBinding<I, A...>::atMost;
    using GenericLoopStaticBinding<I, A...>::atLeast;
    using GenericLoopStaticBinding<I, A...>::moreThan;
    using GenericLoopStaticBinding<I, A...>::lessThan;
    using GenericLoopStaticBinding<I, A...>::count;
    using GenericLoopStaticBinding<I, A...>::any;
    using GenericLoopStaticBinding<I, A...>::all;
    using GenericLoopStaticBinding<I, A...>::none;

    using GenericLoopStaticBinding<I const, A...>::forEach;
    using GenericLoopStaticBinding<I const, A...>::some;
    using GenericLoopStaticBinding<I const, A...>::atMost;
    using GenericLoopStaticBinding<I const, A...>::atLeast;
    using GenericLoopStaticBinding<I const, A...>::moreThan;
    using GenericLoopStaticBinding<I const, A...>::lessThan;
    using GenericLoopStaticBinding<I const, A...>::count;
    using GenericLoopStaticBinding<I const, A...>::any;
    using GenericLoopStaticBinding<I const, A...>::all;
    using GenericLoopStaticBinding<I const, A...>::none;
  };
};
} // namespace genericLoopDeriv

template <typename I, typename P> class CDS_ATTR(inheritsEBOs) GenericLoopBinding :
    public genericLoopDeriv::MutationSelector<P>::template Type<I> {};
} // namespace impl
} // namespace cds

#endif // CDS_BINDINGS_STATIC_GENERIC_LOOP_BINDING_HPP
