//
// Created by loghin on 3/16/24.
//

#ifndef CDS_ALGORITHM_GENERIC_CONTAINS_HPP
#define CDS_ALGORITHM_GENERIC_CONTAINS_HPP
#pragma once

#include <cds/iterator/AddressIterator>
#include <cds/functional/Comparator>
#include <cds/functional/Invoke>

#include "../meta/Ignore.hpp"

namespace cds {
namespace meta {
namespace impl {
using meta::True;
using meta::False;
using meta::Void;
using meta::rvalue;

template <typename, typename, typename = void> struct HasContains : False {
  static constexpr bool exceptSpec = true;
};

template <typename T, typename V>
struct HasContains<T, V, Void<decltype(rvalue<T>().contains(rvalue<V>()))>> : True {
  static constexpr bool exceptSpec = CDS_ATTR(noexcept(rvalue<T>().contains(rvalue<V>())));
};
template <typename, typename, typename, typename = void> struct HasProjectorContains : False {
  static constexpr bool exceptSpec = true;
};

template <typename T, typename V, typename P>
struct HasProjectorContains<T, V, P, Void<decltype(rvalue<T>().contains(rvalue<V>(), rvalue<P>()))>> : True {
  static constexpr bool exceptSpec = CDS_ATTR(noexcept(rvalue<T>().contains(rvalue<V>(), rvalue<P>())));
};
} // namespace impl
} // namespace meta

namespace impl {
using meta::IsIterable;
using meta::IsReverseIterable;
using meta::EnableIf;
using meta::Not;
using meta::Or;
using meta::And;
using meta::impl::HasContains;
using meta::impl::HasProjectorContains;

namespace fn = cds::functional;

template <
    typename T, typename V, typename E,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<Not<Or<C, I, RI>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, E const& equal) noexcept -> bool {
  ignore = where;
  ignore = what;
  ignore = equal;
  static_assert(
      C::value || I::value || RI::value,
      "Given type does not provide a 'contains' function for target parameter"
  );
  return false;
}

template <
    typename T, typename V, typename P, typename E,
    typename C = HasProjectorContains<T, V, P>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<Not<Or<C, I, RI>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P&& projector, E const& equal)
    noexcept -> bool {
  ignore = where;
  ignore = what;
  ignore = projector;
  ignore = equal;
  static_assert(
      C::value || I::value || RI::value,
      "Given type does not provide a 'contains' function with projector for target parameter"
  );
  return false;
}

template <
    typename T, typename V, typename E,
    typename C = HasContains<T, V>,
    EnableIf<C> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, E const& equal)
    CDS_ATTR(noexcept(C::exceptSpec)) -> bool {
  ignore = equal;
  return fwd<T>(where).contains(fwd<V>(what));
}

template <
    typename T, typename V, typename E,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    EnableIf<And<I, Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, E const& equal)
    CDS_ATTR(noexcept(noexcept(fn::invoke(equal, fwd<V>(what), *cds::begin(fwd<T>(where)))))) -> bool {
  for (auto it = cds::begin(fwd<T>(where)), end = cds::end(fwd<T>(where)); it != end; ++it) {
    if (fn::invoke(equal, fwd<V>(what), *it)) {
      return true;
    }
  }
  return false;
}

template <
    typename T, typename V, typename E,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<And<RI, Not<C>, Not<I>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, E const& equal)
    CDS_ATTR(noexcept(noexcept(fn::invoke(equal, fwd<V>(what), *cds::rbegin(fwd<T>(where)))))) -> bool {
  for (auto it = cds::rbegin(fwd<T>(where)), end = cds::rend(fwd<T>(where)); it != end; ++it) {
    if (fn::invoke(equal, fwd<V>(what), *it)) {
      return true;
    }
  }
  return false;
}

template <
    typename T, typename V, typename P, typename E,
    typename C = HasProjectorContains<T, V, P>,
    EnableIf<C> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P&& projector, E const& equal)
    CDS_ATTR(noexcept(C::exceptSpec)) -> bool {
  ignore = equal;
  return fwd<T>(where).contains(fwd<V>(what), fwd<P>(projector));
}

template <
    typename T, typename V, typename P, typename E,
    typename C = HasProjectorContains<T, V, P>,
    typename I = IsIterable<T>,
    EnableIf<And<I, Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P&& projector, E const& equal)
    CDS_ATTR(noexcept(noexcept(fn::invoke(equal, fwd<V>(what), fwd<P>(projector)(*cds::begin(fwd<T>(where)))))))
    -> bool {
  for (auto it = cds::begin(fwd<T>(where)), end = cds::end(fwd<T>(where)); it != end; ++it) {
    if (fn::invoke(equal, fwd<V>(what), fwd<P>(projector)(*it))) {
      return true;
    }
  }

  return false;
}

template <
    typename T, typename V, typename P, typename E,
    typename C = HasProjectorContains<T, V, P>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<And<RI, Not<C>, Not<I>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P&& projector, E const& equal)
    CDS_ATTR(noexcept(noexcept(fn::invoke(equal, fwd<V>(what), fwd<P>(projector)(*cds::rbegin(fwd<T>(where)))))))
    -> bool {
  for (auto it = cds::rbegin(fwd<T>(where)), end = cds::rend(fwd<T>(where)); it != end; ++it) {
    if (fn::invoke(equal, fwd<V>(what), fwd<P>(projector)(*it))) {
      return true;
    }
  }

  return false;
}

template <typename E> class CDS_ATTR(ebo) Contains : private E {
public:
  CDS_ATTR(2(explicit, constexpr(11))) Contains() noexcept : E() {}
  CDS_ATTR(2(explicit, constexpr(11))) Contains(E const& equal) noexcept : E(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(contains(fwd<L>(lhs), fwd<R>(rhs), static_cast<E const&>(*this)))))
      -> bool {
    return contains(fwd<L>(lhs), fwd<R>(rhs), static_cast<E const&>(*this));
  }

  template <typename L, typename R, typename P>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, P&& projector)
      const CDS_ATTR(noexcept(noexcept(contains(
          fwd<L>(lhs), fwd<R>(rhs), fwd<P>(projector), static_cast<E const&>(*this)
      )))) -> bool {
    return
        contains(fwd<L>(lhs), fwd<R>(rhs), fwd<P>(projector), static_cast<E const&>(*this));
  }
};

template <typename E> class CDS_ATTR(ebo) NotContains : private E {
public:
  CDS_ATTR(2(explicit, constexpr(11))) NotContains() noexcept : E() {}
  CDS_ATTR(2(explicit, constexpr(11))) NotContains(E const& equal) noexcept : E(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(!contains(fwd<L>(lhs), fwd<R>(rhs), static_cast<E const&>(*this)))))
      -> bool {
    return !contains(fwd<L>(lhs), fwd<R>(rhs), static_cast<E const&>(*this));
  }

  template <typename L, typename R, typename P>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, P&& projector)
      const CDS_ATTR(noexcept(noexcept(!contains(
          fwd<L>(lhs), fwd<R>(rhs), fwd<P>(projector), static_cast<E const&>(*this)))
      )) -> bool {
    return
        !contains(fwd<L>(lhs), fwd<R>(rhs), fwd<P>(projector), static_cast<E const&>(*this));
  }
};
} // namespace impl
} // namespace cds

#endif // CDS_ALGORITHM_GENERIC_CONTAINS_HPP
