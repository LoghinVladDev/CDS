//
// Created by loghin on 12/13/23.
//

#ifndef CDS_META_UTILITY_HPP
#define CDS_META_UTILITY_HPP
#pragma once

#include <cds/meta/IteratorTraits>
#include <cds/meta/FunctionTraits>
#include <cds/meta/Semantics>
#include <cds/meta/StdLib>
#include <cds/functional/Comparator>
#include <cds/iterator/AddressIterator>

#if CDS_ATTR(sentinel)
#include <cds/iterator/Sentinel>
#endif // #if CDS_ATTR(sentinel)

#include <initializer_list>

namespace cds {
template <typename T, typename U = T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto minOf(T&& lhs, U&& rhs) noexcept -> meta::Common<T, U> {
  return cds::forward<T>(lhs) < cds::forward<U>(rhs) ? lhs : rhs;
}

template <typename T, typename U = T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto maxOf(T&& lhs, U&& rhs) noexcept -> meta::Common<T, U> {
  return cds::forward<T>(lhs) > cds::forward<U>(rhs) ? lhs : rhs;
}

template <typename T1, typename T2, typename T3, typename... R> CDS_ATTR(2(nodiscard, constexpr(11))) auto minOf(
    T1&& v1, T2&& v2, T3&& v3, R&&... r
) noexcept -> meta::Common<T1, T2, T3, R...> {
  return minOf(cds::forward<T1>(v1), minOf(cds::forward<T2>(v2), cds::forward<T3>(v3), cds::forward<R>(r)...));
}

template <typename T1, typename T2, typename T3, typename... R> CDS_ATTR(2(nodiscard, constexpr(11))) auto maxOf(
    T1&& v1, T2&& v2, T3&& v3, R&&... r
) noexcept -> meta::Common<T1, T2, T3, R...> {
  return maxOf(cds::forward<T1>(v1), maxOf(cds::forward<T2>(v2), cds::forward<T3>(v3), cds::forward<R>(r)...));
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto asConst(T& obj) noexcept -> meta::AddConst<T>& {
  return obj;
}

template <typename T> auto asConst(T&& obj) noexcept -> void = delete;

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasIterableMemberFns<D>,
    meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto begin(T&& range) noexcept -> typename E::Iterator {
  return cds::forward<T>(range).begin();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasIterableMemberFns<D>,
    meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename E::Iterator {
  return cds::forward<T>(range).end();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasIterableMemberFns<D>,
    typename CE = meta::impl::HasConstIterableMemberFns<D>,
    meta::EnableIf<meta::And<meta::Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto begin(T&& range) noexcept -> typename CE::ConstIterator {
  return cds::forward<T>(range).cbegin();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasIterableMemberFns<D>,
    typename CE = meta::impl::HasConstIterableMemberFns<D>,
    meta::EnableIf<meta::And<meta::Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename CE::ConstIterator {
  return cds::forward<T>(range).cend();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasConstIterableMemberFns<D>, meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin(T&& range) noexcept -> typename E::ConstIterator {
  return cds::forward<T>(range).cbegin();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasConstIterableMemberFns<D>, meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto cend(T&& range) noexcept -> typename E::ConstIterator {
  return cds::forward<T>(range).cend();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasReverseIterableMemberFns<D>,
    meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin(T&& range) noexcept -> typename E::ReverseIterator {
  return cds::forward<T>(range).rbegin();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasReverseIterableMemberFns<D>,
    meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename E::ReverseIterator {
  return cds::forward<T>(range).rend();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasReverseIterableMemberFns<D>,
    typename CE = meta::impl::HasConstReverseIterableMemberFns<D>,
    meta::EnableIf<meta::And<meta::Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin(T&& range) noexcept -> typename CE::ConstReverseIterator {
  return cds::forward<T>(range).crbegin();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasReverseIterableMemberFns<D>,
    typename CE = meta::impl::HasConstReverseIterableMemberFns<D>,
    meta::EnableIf<meta::And<meta::Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename CE::ConstReverseIterator {
  return cds::forward<T>(range).crend();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasConstReverseIterableMemberFns<D>, meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin(T&& range) noexcept -> typename E::ConstReverseIterator {
  return cds::forward<T>(range).crbegin();
}

template <
    typename T, typename D = meta::RemoveRef<T>,
    typename E = meta::impl::HasConstReverseIterableMemberFns<D>, meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto crend(T&& range) noexcept -> typename E::ConstReverseIterator {
  return cds::forward<T>(range).crend();
}

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

namespace meta {
namespace impl {
using meta::True;
using meta::False;
using meta::Void;
using meta::rvalue;

template <typename, typename = void> struct IsIterable : False {};
template <typename, typename = void> struct IsReverseIterable : False {};

template <typename T, Size s> struct IsIterable<T[s]> : True {};
template <typename T, Size s> struct IsIterable<T(&)[s]> : True {};
template <typename T, Size s> struct IsReverseIterable<T[s]> : True {};

template <typename T>
struct IsIterable<T, Void<decltype(cds::begin(rvalue<T>())), decltype(cds::end(rvalue<T>()))>> : True {
  using Iterator = decltype(cds::begin(rvalue<T>()));
};

template <typename T>
struct IsReverseIterable<T, Void<decltype(cds::rbegin(rvalue<T>())), decltype(cds::rend(rvalue<T>()))>> : True {
  using ReverseIterator = decltype(cds::rbegin(rvalue<T>()));
};
} // namespace impl

template <typename T> struct IsIterable : impl::IsIterable<T>::Type {};
template <typename T> struct IsReverseIterable : impl::IsReverseIterable<T>::Type {};
} // namespace meta

namespace impl {
using meta::IsIterable;
using meta::IsReverseIterable;
using meta::EnableIf;
using meta::Not;
using meta::Or;
using meta::And;
using meta::rvalue;
using meta::impl::HasContains;
using meta::impl::HasProjectorContains;
using meta::IsInvocable;
using meta::IsSame;
using meta::True;
using meta::RemoveCVRef;

using functional::Equal;

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
    EnableIf<And<Not<Or<C, I, RI>>>> = 0
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
} // namespace impl

namespace iterator {
namespace impl {
using meta::rvalue;

using functional::Equal;

template <typename = void> struct FindResultTransformer {
  template <typename IB, typename IE, typename I> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(CDS_ATTR(unused) IB&& b, CDS_ATTR(unused) IE&& e, I&& i) const noexcept
      -> decltype(*rvalue<I>()) {
    return *cds::forward<I>(i);
  }
};

template <typename = void> struct FindPreserveTransformer {
  template <typename IB, typename IE, typename I> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(CDS_ATTR(unused) IB&& b, CDS_ATTR(unused) IE&& e, I&& i) const noexcept -> I {
    return cds::forward<I>(i);
  }
};

template <typename I, typename V, typename E, typename T> class FindIterator {
public:
  using Iterator = I;
  using Value = V;
  using Predicate = E;
  using Transformer = T;

  template <typename RI, typename RSI> CDS_ATTR(constexpr(14)) FindIterator(RI&& b, RSI&& e, V const& v)
      CDS_ATTR(noexcept(noexcept(filter()))) :
      _i(cds::forward<RI>(b)),
      _b(cds::forward<RI>(b)),
      _e(cds::forward<RSI>(e)),
      _v(v) {
    filter();
  }

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(filter()))) -> FindIterator& {
    (void) ++_i;
    filter();
    return *this;
  }

#if CDS_ATTR(sentinel)
  template <typename FI, typename FV, typename FE, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator==(FindIterator<FI, FV, FE, FT> const& obj, Sentinel)
      CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FE, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator!=(FindIterator<FI, FV, FE, FT> const& obj, Sentinel)
      CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool;
#endif // #if CDS_ATTR(sentinel)

  template <typename FI, typename FV, typename FE, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator==(FindIterator<FI, FV, FE, FT> const& lhs, FindIterator<FI, FV, FE, FT> const& rhs)
      CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FE, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator!=(FindIterator<FI, FV, FE, FT> const& lhs, FindIterator<FI, FV, FE, FT> const& rhs)
      CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    return T()(_b, _e, _i);
  }

private:
  CDS_ATTR(constexpr(14)) auto filter()
      CDS_ATTR(noexcept(noexcept(++_i) && noexcept(_i != _e) && noexcept(rvalue<E>()(_v, *_i)))) -> void {
    E const equal;
    while (_i != _e && !equal(_v, *_i)) {
      ++_i;
    }
  }

  I _i;
  I const _b;
  I const _e;
  V const& _v;
};

#if CDS_ATTR(sentinel)
template <typename I, typename V, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(FindIterator<I, V, E, T> const& obj, Sentinel)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return obj._i == obj._e;
}

template <typename I, typename V, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(FindIterator<I, V, E, T> const& obj, Sentinel)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<I>() != rvalue<I>()))) -> bool {
  return obj._i != obj._e;
}
#endif // #if CDS_ATTR(sentinel)

template <typename FI, typename FV, typename FE, typename FT> CDS_ATTR(constexpr(11))
auto operator==(FindIterator<FI, FV, FE, FT> const& lhs, FindIterator<FI, FV, FE, FT> const& rhs)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool {
  return lhs._i == rhs._i;
}

template <typename FI, typename FV, typename FE, typename FT> CDS_ATTR(constexpr(11))
auto operator!=(FindIterator<FI, FV, FE, FT> const& lhs, FindIterator<FI, FV, FE, FT> const& rhs)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool {
  return lhs._i != rhs._i;
}

template <typename I, typename V, typename P, typename E, typename T> class FindProjectIterator {
public:
  using Iterator = I;
  using Value = V;
  using Predicate = E;
  using Transformer = T;

  template <typename RI, typename RSI> CDS_ATTR(constexpr(14))
  FindProjectIterator(RI&& b, RSI&& e, V const& v, P const& s)
      CDS_ATTR(noexcept(noexcept(filter()))) :
      _i(cds::forward<RI>(b)),
      _b(cds::forward<RI>(b)),
      _e(cds::forward<RSI>(e)),
      _p(s),
      _v(v) {
    filter();
  }

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(filter()))) -> FindProjectIterator& {
    (void) ++_i;
    filter();
    return *this;
  }

#if CDS_ATTR(sentinel)
  template <typename FI, typename FV, typename FP, typename FE, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator==(FindProjectIterator<FI, FV, FP, FE, FT> const& obj, Sentinel)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FP, typename FE, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator!=(FindProjectIterator<FI, FV, FP, FE, FT> const& obj, Sentinel)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool;
#endif // #if CDS_ATTR(sentinel)

  template <typename FI, typename FV, typename FP, typename FE, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator==(
      FindProjectIterator<FI, FV, FP, FE, FT> const& lhs, FindProjectIterator<FI, FV, FP, FE, FT> const& rhs
  ) CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FP, typename FE, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator!=(
      FindProjectIterator<FI, FV, FP, FE, FT> const& lhs, FindProjectIterator<FI, FV, FP, FE, FT> const& rhs
  ) CDS_ATTR(friend_noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    return T()(_b, _e, _i);
  }

private:
  CDS_ATTR(constexpr(14)) auto filter()
      CDS_ATTR(noexcept(noexcept(++_i) && noexcept(_i != _e) && noexcept(rvalue<E>()(_v, _p(*_i))))) -> void {
    E const equal;
    while (_i != _e && !equal(_v, _p(*_i))) {
      ++_i;
    }
  }

  I _i;
  I const _b;
  I const _e;
  P const& _p;
  V const& _v;
};

#if CDS_ATTR(sentinel)
template <typename I, typename V, typename P, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(FindProjectIterator<I, V, P, E, T> const& obj, Sentinel)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return obj._i == obj._e;
}

template <typename I, typename V, typename P, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(FindProjectIterator<I, V, P, E, T> const& obj, Sentinel)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<I>() != rvalue<I>()))) -> bool {
  return obj._i != obj._e;
}
#endif // #if CDS_ATTR(sentinel)

template <typename I, typename V, typename P, typename E, typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(FindProjectIterator<I, V, P, E, T> const& lhs, FindProjectIterator<I, V, P, E, T> const& rhs)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return lhs._i == rhs._i;
}

template <typename I, typename V, typename P, typename E, typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(FindProjectIterator<I, V, P, E, T> const& lhs, FindProjectIterator<I, V, P, E, T> const& rhs)
    CDS_ATTR(friend_noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return lhs._i != rhs._i;
}
} // namespace impl
} // namespace iterator

namespace impl {
using meta::value;
using meta::lvalue;
using meta::rvalue;
using meta::Decay;
using meta::EnableIf;
using meta::Not;
using meta::Or;
using meta::And;
using meta::IsLValRef;
using meta::IsRValRef;
using meta::RemoveRef;
using meta::IsConst;
using meta::Conditional;

using functional::Equal;

using iterator::impl::FindIterator;
using iterator::impl::FindProjectIterator;
using iterator::impl::FindResultTransformer;
using iterator::impl::FindPreserveTransformer;

#if CDS_ATTR(sentinel)
using iterator::Sentinel;
#endif // #if CDS_ATTR(sentinel)

namespace extension {
using meta::IsSame;
using meta::Conditional;

namespace extendImpl {
using meta::False;
using meta::True;

template <typename> struct IsInitializerList : False {};
template <typename T> struct IsInitializerList<std::initializer_list<T>> : True {};

template <typename T, typename R = RemoveRef<T>> struct Extend {
  static_assert(!IsInitializerList<T>::value, "Cannot extend lifetime of std::initializer_list");
  using Type = Conditional<Or<IsRValRef<T>, IsSame<R, T>>, R, R&>;
};
} // namespace extendImpl

template <typename T> using Extend = typename extendImpl::Extend<T>::Type;
} // namespace extension
using extension::Extend;

template <typename TAttr, typename VAttr, typename E, typename Tr> class FindIterableRange {
public:
  using Iterable = TAttr;
  using Value = VAttr;
  using Predicate = E;
  using Transformer = Tr;
  using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
  using Iterator = FindIterator<UnderlyingIterator, RemoveRef<VAttr>, E, Tr>;
  using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
  using ConstIterator = FindIterator<UnderlyingConstIterator, RemoveRef<VAttr>, E, Tr>;

  template <typename T, typename V> CDS_ATTR(constexpr(11)) FindIterableRange(T&& obj, V&& v)
      CDS_ATTR(noexcept(noexcept(TAttr(cds::forward<T>(obj))) && noexcept(VAttr(cds::forward<V>(v))))) :
      _o(cds::forward<T>(obj)), _v(cds::forward<V>(v)) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_o), cds::end(_o), _v)))) -> Iterator {
    return Iterator(cds::begin(_o), cds::end(_o), _v);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_o), cds::end(_o), _v)))) -> ConstIterator {
    return ConstIterator(cds::begin(_o), cds::end(_o), _v);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_o), cds::end(_o), _v)))) -> Iterator {
    return Iterator(cds::end(_o), cds::end(_o), _v);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_o), cds::end(_o), _v)))) -> ConstIterator {
    return ConstIterator(cds::end(_o), cds::end(_o), _v);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  TAttr _o;
  VAttr const _v;
};

template <typename TAttr, typename VAttr, typename PAttr, typename E, typename Tr> class FindSelectIterableRange {
public:
  using Iterable = TAttr;
  using Value = VAttr;
  using Predicate = E;
  using Transformer = Tr;
  using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
  using Iterator = FindProjectIterator<UnderlyingIterator, RemoveRef<VAttr>, RemoveRef<PAttr>, E, Tr>;
  using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
  using ConstIterator = FindProjectIterator<UnderlyingConstIterator, RemoveRef<VAttr>, RemoveRef<PAttr>, E, Tr>;

  template <typename T, typename V, typename P>
  CDS_ATTR(constexpr(11)) FindSelectIterableRange(T&& obj, V&& v, P&& p) CDS_ATTR(noexcept(
      noexcept(TAttr(cds::forward<T>(obj)))
      && noexcept(VAttr(cds::forward<V>(v)))
      && noexcept(PAttr(cds::forward<P>(p)))
  )) : _o(cds::forward<T>(obj)), _v(cds::forward<V>(v)), _p(cds::forward<P>(p)) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_o), cds::end(_o), _v, _p)))) -> Iterator {
    return Iterator(cds::begin(_o), cds::end(_o), _v, _p);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_o), cds::end(_o), _v, _p)))) -> ConstIterator {
    return ConstIterator(cds::begin(_o), cds::end(_o), _v, _p);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_o), cds::end(_o), _v, _p)))) -> Iterator {
    return Iterator(cds::end(_o), cds::end(_o), _v, _p);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_o), cds::end(_o), _v, _p)))) -> ConstIterator {
    return ConstIterator(cds::end(_o), cds::end(_o), _v, _p);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  TAttr _o;
  VAttr const _v;
  PAttr const _p;
};

template <typename, typename> struct GenericFindEnabledFor : True {};

template <
    typename I, typename V, typename E, typename T,
    typename R = FindIterableRange<Extend<I>, Extend<V>, E, T>,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    I&& iterable, V&& value, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(iterable), cds::forward<V>(value))))) -> R {
  return R(cds::forward<I>(iterable), cds::forward<V>(value));
}

template <
    typename I, typename V, typename P, typename E, typename T,
    typename R = FindSelectIterableRange<Extend<I>, Extend<V>, Extend<P>, E, T>,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    I&& iterable, V&& value, P&& projector, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(iterable), cds::forward<V>(value), cds::forward<P>(projector))))) -> R {
  return R(cds::forward<I>(iterable), cds::forward<V>(value), cds::forward<P>(projector));
}

template <
    typename I, typename V, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(equal(*cds::begin(cds::forward<I>(iterable)), cds::forward<V>(value)))
    && noexcept(transform(
        cds::begin(cds::forward<I>(iterable)),
        cds::end(cds::forward<I>(iterable)),
        cds::begin(cds::forward<I>(iterable))
    ))
)) -> decltype(transform(
    cds::begin(cds::forward<I>(iterable)),
    cds::end(cds::forward<I>(iterable)),
    cds::begin(cds::forward<I>(iterable))
)) {
  auto const b = cds::begin(cds::forward<I>(iterable));
  auto const e = cds::end(cds::forward<I>(iterable));
  for (auto i = b; i != e; ++i) {
    if (equal(cds::forward<V>(value), *i)) {
      return transform(b, e, i);
    }
  }
  return transform(b, e, e);
}

template <
    typename I, typename V, typename P, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(equal(cds::forward<P>(projector)(*cds::begin(cds::forward<I>(iterable))), cds::forward<V>(value)))
    && noexcept(transform(
        cds::begin(cds::forward<I>(iterable)),
        cds::end(cds::forward<I>(iterable)),
        cds::begin(cds::forward<I>(iterable))
    ))
)) -> decltype(transform(
    cds::begin(cds::forward<I>(iterable)),
    cds::end(cds::forward<I>(iterable)),
    cds::begin(cds::forward<I>(iterable))
)) {
  auto const b = cds::begin(cds::forward<I>(iterable));
  auto const e = cds::end(cds::forward<I>(iterable));
  for (auto i = b; i != e; ++i) {
    if (equal(cds::forward<V>(value), cds::forward<P>(projector)(*i))) {
      return transform(b, e, i);
    }
  }
  return transform(b, e, e);
}

template <
    typename I, typename V, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(equal(*cds::begin(cds::forward<I>(iterable)), cds::forward<V>(value)))
    && noexcept(transform(
        cds::begin(cds::forward<I>(iterable)),
        cds::end(cds::forward<I>(iterable)),
        cds::begin(cds::forward<I>(iterable))
    ))
)) -> decltype(transform(
    cds::begin(cds::forward<I>(iterable)),
    cds::end(cds::forward<I>(iterable)),
    cds::begin(cds::forward<I>(iterable))
)) {
  auto const b = cds::begin(cds::forward<I>(iterable));
  auto const e = cds::end(cds::forward<I>(iterable));
  auto l = e;
  for (auto i = b; i != e; ++i) {
    if (equal(cds::forward<V>(value), *i)) {
      l = i;
    }
  }
  return transform(b, e, l);
}

template <
    typename I, typename V, typename P, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(equal(cds::forward<P>(projector)(*cds::begin(cds::forward<I>(iterable))), cds::forward<V>(value)))
    && noexcept(transform(
        cds::begin(cds::forward<I>(iterable)),
        cds::end(cds::forward<I>(iterable)),
        cds::begin(cds::forward<I>(iterable))
    ))
)) -> decltype(transform(
    cds::begin(cds::forward<I>(iterable)),
    cds::end(cds::forward<I>(iterable)),
    cds::begin(cds::forward<I>(iterable))
)) {
  auto const b = cds::begin(cds::forward<I>(iterable));
  auto const e = cds::end(cds::forward<I>(iterable));
  auto l = e;
  for (auto i = b; i != e; ++i) {
    if (equal(cds::forward<V>(value), cds::forward<P>(projector)(*i))) {
      l = i;
    }
  }
  return transform(b, e, l);
}

template <typename E> class Contains {
public:
  CDS_ATTR(2(explicit, constexpr(11))) Contains() noexcept : _equal(E()) {}
  CDS_ATTR(2(explicit, constexpr(11))) Contains(E const& equal) noexcept : _equal(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal)))) -> bool {
    return contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal);
  }

  template <typename L, typename R, typename P>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, P&& projector) const CDS_ATTR(noexcept(
      noexcept(contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), _equal))
  )) -> bool {
    return contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), _equal);
  }

private:
  CDS_ATTR(no_unique_address) E _equal;
};

template <typename E> class NotContains {
public:
  CDS_ATTR(2(explicit, constexpr(11))) NotContains() noexcept : _equal(E()) {}
  CDS_ATTR(2(explicit, constexpr(11))) NotContains(E const& equal) noexcept : _equal(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(!contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal)))) -> bool {
    return !contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal);
  }

  template <typename L, typename R, typename P>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, P&& projector) const CDS_ATTR(noexcept(
      noexcept(!contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), _equal))
  )) -> bool {
    return !contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<P>(projector), _equal);
  }

private:
  CDS_ATTR(no_unique_address) E _equal;
};

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(14)) auto copy(I sFirst, S sLast, O dFirst) CDS_ATTR(noexcept(
    noexcept(*dFirst = *sFirst) &&
    noexcept(sFirst != sLast) &&
    noexcept(++sFirst) &&
    noexcept(++dFirst)
)) -> O {
  for (; sFirst != sLast; ++sFirst, ++dFirst) {
    *dFirst = *sFirst;
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(14)) auto copyN(I sFirst, S count, O dFirst) CDS_ATTR(noexcept(
    noexcept(*dFirst = *sFirst) &&
    noexcept(++sFirst) &&
    noexcept(++dFirst)
)) -> O {
  for (S cnt = 0; cnt != count; ++sFirst, ++dFirst, ++cnt) {
    *dFirst = *sFirst;
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto copyInitialize(I sFirst, S sLast, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, *sFirst)) &&
    noexcept(sFirst != sLast) &&
    noexcept(++sFirst) &&
    noexcept(++dFirst)
)) -> O {
  for (; sFirst != sLast; ++sFirst, ++dFirst) {
    construct(dFirst, *sFirst);
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto copyNInitialize(I sFirst, S count, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, *sFirst)) &&
    noexcept(++sFirst) &&
    noexcept(++dFirst)
)) -> O {
  for (S cnt = 0; cnt != count; ++sFirst, ++dFirst, ++cnt) {
    construct(dFirst, *sFirst);
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto moveInitialize(I sFirst, S sLast, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, cds::move(*sFirst))) &&
    noexcept(sFirst != sLast) &&
    noexcept(++sFirst) &&
    noexcept(++dFirst)
)) -> O {
  for (; sFirst != sLast; ++sFirst, ++dFirst) {
    construct(dFirst, cds::move(*sFirst));
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto moveNInitialize(I sFirst, S count, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, cds::move(*sFirst))) &&
    noexcept(++sFirst) &&
    noexcept(++dFirst)
)) -> O {
  for (S cnt = 0; cnt != count; ++sFirst, ++dFirst, ++cnt) {
    construct(dFirst, cds::move(*sFirst));
  }
  return dFirst;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fill(I first, S last, T const& value) CDS_ATTR(noexcept(
    noexcept(*first = value) &&
    noexcept(first != last) &&
    noexcept(++first)
)) -> I {
  for (; first != last; ++first) {
    *first = value;
  }
  return first;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fillN(I first, S count, T const& value) CDS_ATTR(noexcept(
    noexcept(*first = value) &&
    noexcept(++first)
)) -> I {
  for (S cnt = 0; cnt != count; ++first, ++cnt) {
    *first = value;
  }
  return first;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fillInitialize(I first, S last, T const& value) CDS_ATTR(noexcept(
    noexcept(construct(first, value)) &&
    noexcept(first != last) &&
    noexcept(++first)
)) -> I {
  for (; first != last; ++first) {
    construct(first, value);
  }
  return first;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fillNInitialize(I first, S count, T const& value) CDS_ATTR(noexcept(
    noexcept(construct(first, value)) &&
    noexcept(++first)
)) -> I {
  for (S cnt = 0; cnt != count; ++first, ++cnt) {
    construct(first, value);
  }
  return first;
}

template <typename I, typename S>
CDS_ATTR(constexpr(20)) auto destruct(I first, S last) noexcept -> void {
  for (; first != last; ++first) {
    destruct(first);
  }
}

template <typename I, typename S>
CDS_ATTR(constexpr(20)) auto destructN(I first, S count) noexcept -> void {
  for (S cnt = 0; cnt != count; ++first, ++cnt) {
    destruct(first);
  }
}
} // namespace impl
} // namespace cds

#endif // CDS_META_UTILITY_HPP
