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

#if CDS_ATTR(bit_cast)
#include <bit>
#else // #if CDS_ATTR(bit_cast)
#include <cstring>
#endif // #if CDS_ATTR(bit_cast)

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
template <typename, typename, typename, typename = void> struct HasSelectorContains : False {
  static constexpr bool exceptSpec = true;
};

template <typename T, typename V, typename S>
struct HasSelectorContains<T, V, S, Void<decltype(rvalue<T>().contains(rvalue<V>(), rvalue<S>()))>> : True {
  static constexpr bool exceptSpec = CDS_ATTR(noexcept(rvalue<T>().contains(rvalue<V>(), rvalue<S>())));
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
using meta::impl::HasSelectorContains;
using meta::IsInvocable;
using meta::IsSame;
using meta::True;
using meta::RemoveCVRef;

using functional::Equal;

template <
    typename T, typename V, typename P,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<Not<Or<C, I, RI>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P const& equal) noexcept -> bool {
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
    typename T, typename V, typename S, typename P,
    typename C = HasSelectorContains<T, V, S>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<And<Not<Or<C, I, RI>>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector, P const& equal)
    noexcept -> bool {
  (void) where;
  (void) what;
  (void) selector;
  (void) equal;
  static_assert(
      C::value || I::value || RI::value,
      "Given type does not provide a 'contains' function with selector for target parameter"
  );
  return false;
}

template <
    typename T, typename V, typename P,
    typename C = HasContains<T, V>,
    EnableIf<C> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P const& equal)
    CDS_ATTR(noexcept(C::exceptSpec)) -> bool {
  (void) equal;
  return cds::forward<T>(where).contains(cds::forward<V>(what));
}

template <
    typename T, typename V, typename P,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    EnableIf<And<I, Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P const& equal)
    CDS_ATTR(noexcept(noexcept(equal(cds::forward<V>(what), *cds::begin(cds::forward<T>(where)))))) -> bool {
  for (auto it = cds::begin(cds::forward<T>(where)), end = cds::end(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), *it)) {
      return true;
    }
  }
  return false;
}

template <
    typename T, typename V, typename P,
    typename C = HasContains<T, V>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<And<RI, Not<C>, Not<I>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, P const& equal)
    CDS_ATTR(noexcept(noexcept(equal(cds::forward<V>(what), *cds::rbegin(cds::forward<T>(where)))))) -> bool {
  for (auto it = cds::rbegin(cds::forward<T>(where)), end = cds::rend(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), *it)) {
      return true;
    }
  }
  return false;
}

template <
    typename T, typename V, typename S, typename P,
    typename C = HasSelectorContains<T, V, S>,
    EnableIf<C> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector, P const& equal)
    CDS_ATTR(noexcept(C::exceptSpec)) -> bool {
  (void) equal;
  return cds::forward<T>(where).contains(cds::forward<V>(what), cds::forward<S>(selector));
}

template <
    typename T, typename V, typename S, typename P,
    typename C = HasSelectorContains<T, V, S>,
    typename I = IsIterable<T>,
    EnableIf<And<I, Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector, P const& equal)
    CDS_ATTR(noexcept(noexcept(
        equal(cds::forward<V>(what), cds::forward<S>(selector)(*cds::begin(cds::forward<T>(where))))
    ))) -> bool {
  for (auto it = cds::begin(cds::forward<T>(where)), end = cds::end(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), cds::forward<S>(selector)(*it))) {
      return true;
    }
  }

  return false;
}

template <
    typename T, typename V, typename S, typename P,
    typename C = HasSelectorContains<T, V, S>,
    typename I = IsIterable<T>,
    typename RI = IsReverseIterable<T>,
    EnableIf<And<RI, Not<C>, Not<I>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector, P const& equal)
    CDS_ATTR(noexcept(noexcept(
        equal(cds::forward<V>(what), cds::forward<S>(selector)(*cds::rbegin(cds::forward<T>(where))))
    ))) -> bool {
  for (auto it = cds::rbegin(cds::forward<T>(where)), end = cds::rend(cds::forward<T>(where)); it != end; ++it) {
    if (equal(cds::forward<V>(what), cds::forward<S>(selector)(*it))) {
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

template <typename I, typename V, typename P, typename T> class FindIterator {
public:
  using Iterator = I;
  using Value = V;
  using Predicate = P;
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
  template <typename FI, typename FV, typename FP, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator==(FindIterator<FI, FV, FP, FT> const& obj, Sentinel)
      CDS_ATTR(noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FP, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator!=(FindIterator<FI, FV, FP, FT> const& obj, Sentinel)
      CDS_ATTR(noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool;
#endif // #if CDS_ATTR(sentinel)

  template <typename FI, typename FV, typename FP, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator==(FindIterator<FI, FV, FP, FT> const& lhs, FindIterator<FI, FV, FP, FT> const& rhs)
      CDS_ATTR(noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FP, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator!=(FindIterator<FI, FV, FP, FT> const& lhs, FindIterator<FI, FV, FP, FT> const& rhs)
      CDS_ATTR(noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    T const transform;
    return transform(_b, _e, _i);
  }

private:
  CDS_ATTR(constexpr(14)) auto filter()
      CDS_ATTR(noexcept(noexcept(++_i) && noexcept(_i != _e) && noexcept(rvalue<P>()(_v, *_i)))) -> void {
    P const valid;
    while (_i != _e && !valid(_v, *_i)) {
      ++_i;
    }
  }

  I _i;
  I const _b;
  I const _e;
  V const& _v;
};

#if CDS_ATTR(sentinel)
template <typename I, typename V, typename P, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(FindIterator<I, V, P, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return obj._i == obj._e;
}

template <typename I, typename V, typename P, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(FindIterator<I, V, P, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() != rvalue<I>()))) -> bool {
  return obj._i != obj._e;
}
#endif // #if CDS_ATTR(sentinel)

template <typename FI, typename FV, typename FP, typename FT> CDS_ATTR(constexpr(11))
auto operator==(FindIterator<FI, FV, FP, FT> const& lhs, FindIterator<FI, FV, FP, FT> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool {
  return lhs._i == rhs._i;
}

template <typename FI, typename FV, typename FP, typename FT> CDS_ATTR(constexpr(11))
auto operator!=(FindIterator<FI, FV, FP, FT> const& lhs, FindIterator<FI, FV, FP, FT> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool {
  return lhs._i != rhs._i;
}

template <typename I, typename V, typename S, typename P, typename T> class FindSelectIterator {
public:
  using Iterator = I;
  using Value = V;
  using Predicate = P;
  using Transformer = T;

  template <typename RI, typename RSI> CDS_ATTR(constexpr(14))
  FindSelectIterator(RI&& b, RSI&& e, V const& v, S const& s)
      CDS_ATTR(noexcept(noexcept(filter()))) :
      _i(cds::forward<RI>(b)),
      _b(cds::forward<RI>(b)),
      _e(cds::forward<RSI>(e)),
      _s(s),
      _v(v) {
    filter();
  }

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(filter()))) -> FindSelectIterator& {
    (void) ++_i;
    filter();
    return *this;
  }

#if CDS_ATTR(sentinel)
  template <typename FI, typename FV, typename FS, typename FP, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator==(FindSelectIterator<FI, FV, FS, FP, FT> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FS, typename FP, typename FT>
  CDS_ATTR(constexpr(11)) friend auto operator!=(FindSelectIterator<FI, FV, FS, FP, FT> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool;
#endif // #if CDS_ATTR(sentinel)

  template <typename FI, typename FV, typename FS, typename FP, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator==(
      FindSelectIterator<FI, FV, FS, FP, FT> const& lhs, FindSelectIterator<FI, FV, FS, FP, FT> const& rhs
  ) CDS_ATTR(noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  template <typename FI, typename FV, typename FS, typename FP, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator!=(
      FindSelectIterator<FI, FV, FS, FP, FT> const& lhs, FindSelectIterator<FI, FV, FS, FP, FT> const& rhs
  ) CDS_ATTR(noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    T const transform;
    return transform(_b, _e, _i);
  }

private:
  CDS_ATTR(constexpr(14)) auto filter()
      CDS_ATTR(noexcept(noexcept(++_i) && noexcept(_i != _e) && noexcept(rvalue<P>()(_v, _s(*_i))))) -> void {
    P const valid;
    while (_i != _e && !valid(_v, _s(*_i))) {
      ++_i;
    }
  }

  I _i;
  I const _b;
  I const _e;
  S const& _s;
  V const& _v;
};

#if CDS_ATTR(sentinel)
template <typename I, typename V, typename S, typename P, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(FindSelectIterator<I, V, S, P, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return obj._i == obj._e;
}

template <typename I, typename V, typename S, typename P, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(FindSelectIterator<I, V, S, P, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() != rvalue<I>()))) -> bool {
  return obj._i != obj._e;
}
#endif // #if CDS_ATTR(sentinel)

template <typename I, typename V, typename S, typename P, typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(FindSelectIterator<I, V, S, P, T> const& lhs, FindSelectIterator<I, V, S, P, T> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return lhs._i == rhs._i;
}

template <typename I, typename V, typename S, typename P, typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(FindSelectIterator<I, V, S, P, T> const& lhs, FindSelectIterator<I, V, S, P, T> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
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
using iterator::impl::FindSelectIterator;
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

template <typename TAttr, typename VAttr, typename P, typename Tr> class FindIterableRange {
public:
  using Iterable = TAttr;
  using Value = VAttr;
  using Predicate = P;
  using Transformer = Tr;
  using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
  using Iterator = FindIterator<UnderlyingIterator, RemoveRef<VAttr>, P, Tr>;
  using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
  using ConstIterator = FindIterator<UnderlyingConstIterator, RemoveRef<VAttr>, P, Tr>;

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

template <typename TAttr, typename VAttr, typename SAttr, typename P, typename Tr> class FindSelectIterableRange {
public:
  using Iterable = TAttr;
  using Value = VAttr;
  using Predicate = P;
  using Transformer = Tr;
  using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
  using Iterator = FindSelectIterator<UnderlyingIterator, RemoveRef<VAttr>, RemoveRef<SAttr>, P, Tr>;
  using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
  using ConstIterator = FindSelectIterator<UnderlyingConstIterator, RemoveRef<VAttr>, RemoveRef<SAttr>, P, Tr>;

  template <typename T, typename V, typename S>
  CDS_ATTR(constexpr(11)) FindSelectIterableRange(T&& obj, V&& v, S&& s) CDS_ATTR(noexcept(
      noexcept(TAttr(cds::forward<T>(obj)))
      && noexcept(VAttr(cds::forward<V>(v)))
      && noexcept(SAttr(cds::forward<S>(s)))
  )) : _o(cds::forward<T>(obj)), _v(cds::forward<V>(v)), _s(cds::forward<S>(s)) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_o), cds::end(_o), _v, _s)))) -> Iterator {
    return Iterator(cds::begin(_o), cds::end(_o), _v, _s);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_o), cds::end(_o), _v, _s)))) -> ConstIterator {
    return ConstIterator(cds::begin(_o), cds::end(_o), _v, _s);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_o), cds::end(_o), _v, _s)))) -> Iterator {
    return Iterator(cds::end(_o), cds::end(_o), _v, _s);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_o), cds::end(_o), _v, _s)))) -> ConstIterator {
    return ConstIterator(cds::end(_o), cds::end(_o), _v, _s);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  TAttr _o;
  VAttr const _v;
  SAttr const _s;
};

template <typename, typename> struct GenericFindEnabledFor : True {};

template <
    typename I, typename V, typename P, typename T,
    typename R = FindIterableRange<Extend<I>, Extend<V>, P, T>,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    I&& iterable, V&& value, CDS_ATTR(unused) P const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(iterable), cds::forward<V>(value))))) -> R {
  return R(cds::forward<I>(iterable), cds::forward<V>(value));
}

template <
    typename I, typename V, typename S, typename P, typename T,
    typename R = FindSelectIterableRange<Extend<I>, Extend<V>, Extend<S>, P, T>,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    I&& iterable, V&& value, S&& selector, CDS_ATTR(unused) P const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(iterable), cds::forward<V>(value), cds::forward<S>(selector))))) -> R {
  return R(cds::forward<I>(iterable), cds::forward<V>(value), cds::forward<S>(selector));
}

template <
    typename I, typename V, typename P, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, P const& valid, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(valid(*cds::begin(cds::forward<I>(iterable)), cds::forward<V>(value)))
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
    if (valid(cds::forward<V>(value), *i)) {
      return transform(b, e, i);
    }
  }
  return transform(b, e, e);
}

template <
    typename I, typename V, typename S, typename P, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, S&& selector, P const& valid, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(valid(cds::forward<S>(selector)(*cds::begin(cds::forward<I>(iterable))), cds::forward<V>(value)))
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
    if (valid(cds::forward<V>(value), cds::forward<S>(selector)(*i))) {
      return transform(b, e, i);
    }
  }
  return transform(b, e, e);
}

template <
    typename I, typename V, typename P, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, P const& valid, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(valid(*cds::begin(cds::forward<I>(iterable)), cds::forward<V>(value)))
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
    if (valid(cds::forward<V>(value), *i)) {
      l = i;
    }
  }
  return transform(b, e, l);
}

template <
    typename I, typename V, typename S, typename P, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, S&& selector, P const& valid, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(cds::forward<I>(iterable)) != cds::end(cds::forward<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(cds::forward<I>(iterable)))>())
    && noexcept(valid(cds::forward<S>(selector)(*cds::begin(cds::forward<I>(iterable))), cds::forward<V>(value)))
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
    if (valid(cds::forward<V>(value), cds::forward<S>(selector)(*i))) {
      l = i;
    }
  }
  return transform(b, e, l);
}

template <typename P> class Contains {
public:
  CDS_ATTR(2(explicit, constexpr(11))) Contains() noexcept : _equal(P()) {}
  CDS_ATTR(2(explicit, constexpr(11))) Contains(P const& equal) noexcept : _equal(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal)))) -> bool {
    return contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal);
  }

  template <typename L, typename R, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, S&& selector) const CDS_ATTR(noexcept(
      noexcept(contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<S>(selector), _equal))
  )) -> bool {
    return contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<S>(selector), _equal);
  }

private:
  CDS_ATTR(no_unique_address) P _equal;
};

template <typename P> class NotContains {
public:
  CDS_ATTR(2(explicit, constexpr(11))) NotContains() noexcept : _equal(P()) {}
  CDS_ATTR(2(explicit, constexpr(11))) NotContains(P const& equal) noexcept : _equal(equal) {}

  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs) const
      CDS_ATTR(noexcept(noexcept(!contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal)))) -> bool {
    return !contains(cds::forward<L>(lhs), cds::forward<R>(rhs), _equal);
  }

  template <typename L, typename R, typename S>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(L&& lhs, R&& rhs, S&& selector) const CDS_ATTR(noexcept(
      noexcept(!contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<S>(selector), _equal))
  )) -> bool {
    return !contains(cds::forward<L>(lhs), cds::forward<R>(rhs), cds::forward<S>(selector), _equal);
  }

private:
  CDS_ATTR(no_unique_address) P _equal;
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
