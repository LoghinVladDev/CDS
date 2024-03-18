//
// Created by loghin on 3/16/24.
//

#ifndef CDS_ALGORITHM_GENERIC_CONTAINS_HPP
#define CDS_ALGORITHM_GENERIC_CONTAINS_HPP
#pragma once

#include <cds/iterator/AddressIterator>
#include <cds/functional/Comparator>

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

template <
    typename T, typename V, typename E,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<Not<Or<C, I, RI>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, E const& equal) noexcept -> bool {
  (void) where;
  (void) what;
  (void) equal;
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
  (void) where;
  (void) what;
  (void) projector;
  (void) equal;
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
  (void) equal;
  return cds::forward<T>(where).contains(cds::forward<V>(what));
}

template <
    typename T, typename V, typename E,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    EnableIf<And<I, Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, E const& equal)
    CDS_ATTR(noexcept(noexcept(equal(cds::forward<V>(what), *cds::begin(cds::forward<T>(where)))))) -> bool {
  for (auto it = cds::begin(cds::forward<T>(where)), end = cds::end(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), *it)) {
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
    CDS_ATTR(noexcept(noexcept(equal(cds::forward<V>(what), *cds::rbegin(cds::forward<T>(where)))))) -> bool {
  for (auto it = cds::rbegin(cds::forward<T>(where)), end = cds::rend(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), *it)) {
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
  (void) equal;
  return cds::forward<T>(where).contains(cds::forward<V>(what), cds::forward<P>(projector));
}

template <
    typename T, typename V, typename P, typename E,
    typename C = HasProjectorContains<T, V, P>,
    typename I = IsIterable<T>,
    EnableIf<And<I, Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P&& projector, E const& equal)
    CDS_ATTR(noexcept(noexcept(
        equal(cds::forward<V>(what), cds::forward<P>(projector)(*cds::begin(cds::forward<T>(where))))
    ))) -> bool {
  for (auto it = cds::begin(cds::forward<T>(where)), end = cds::end(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), cds::forward<P>(projector)(*it))) {
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
    CDS_ATTR(noexcept(noexcept(
        equal(cds::forward<V>(what), cds::forward<P>(projector)(*cds::rbegin(cds::forward<T>(where))))
    ))) -> bool {
  for (auto it = cds::rbegin(cds::forward<T>(where)), end = cds::rend(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), cds::forward<P>(projector)(*it))) {
      return true;
    }
  }

  return false;
}

template <typename E> class CDS_ATTR(inheritsEBOs) Contains : private E {
public:
  CDS_ATTR(2(explicit, constexpr(11))) Contains() noexcept : E() {}
  CDS_ATTR(2(explicit, constexpr(11))) Contains(E const& equal) noexcept : E(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(contains(cds::forward<L>(lhs), cds::forward<R>(rhs), static_cast<E const&>(*this)))))
      -> bool {
    return contains(cds::forward<L>(lhs), cds::forward<R>(rhs), static_cast<E const&>(*this));
  }

  template <typename L, typename R, typename P>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, P&& projector)
      const CDS_ATTR(noexcept(noexcept(contains(
          cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), static_cast<E const&>(*this)
      )))) -> bool {
    return
        contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), static_cast<E const&>(*this));
  }
};

template <typename E> class CDS_ATTR(inheritsEBOs) NotContains : private E {
public:
  CDS_ATTR(2(explicit, constexpr(11))) NotContains() noexcept : E() {}
  CDS_ATTR(2(explicit, constexpr(11))) NotContains(E const& equal) noexcept : E(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(!contains(cds::forward<L>(lhs), cds::forward<R>(rhs), static_cast<E const&>(*this)))))
      -> bool {
    return !contains(cds::forward<L>(lhs), cds::forward<R>(rhs), static_cast<E const&>(*this));
  }

  template <typename L, typename R, typename P>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, P&& projector)
      const CDS_ATTR(noexcept(noexcept(!contains(
          cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), static_cast<E const&>(*this)))
      )) -> bool {
    return
        !contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), static_cast<E const&>(*this));
  }
};
} // namespace impl
} // namespace cds

#endif // CDS_ALGORITHM_GENERIC_CONTAINS_HPP
