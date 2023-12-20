//
// Created by loghin on 12/13/23.
//

#ifndef CDS_META_UTILITY_HPP
#define CDS_META_UTILITY_HPP

#include <cds/meta/TypeTraits>
#include <cds/meta/IteratorTraits>
#include <cds/iterator/AddressIterator>

namespace cds {
template <typename T, ::cds::meta::EnableIf<::cds::meta::Ge<::cds::meta::Int<sizeof(T)>, meta::Int<sizeof(Size)>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto identity(T const& v) noexcept -> T const& { return v; }

template <
    typename T, ::cds::meta::EnableIf<::cds::meta::Lt<::cds::meta::Int<sizeof(T)>, ::cds::meta::Int<sizeof(Size)>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto identity(T v) noexcept -> T { return v; }

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto forward(::cds::meta::RemoveRef<T>& v) noexcept -> T&& {
  return static_cast<T&&>(v);
}

template <typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto forward(::cds::meta::RemoveRef<T>&& v) noexcept -> T&& {
  static_assert(!::cds::meta::IsLValRef<T>::value, "Attempted to use forward to convert rvalue to lvalue");
  return static_cast<T&&>(v);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto move(T&& v) noexcept -> ::cds::meta::RemoveRef<T>&& {
  return static_cast<::cds::meta::RemoveRef<T>&&>(v);
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(14))) auto exchange(T& obj, U&& newVal) -> T {
  T old = move(obj);
  obj = cds::forward<U>(newVal);
  return old;
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(11))) auto minOf(
    T&& lhs, U&& rhs
) noexcept -> ::cds::meta::Common<T, U> {
  return cds::forward<T>(lhs) < cds::forward<U>(rhs) ? lhs : rhs;
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(11))) auto maxOf(
    T&& lhs, U&& rhs
) noexcept -> ::cds::meta::Common<T, U> {
  return cds::forward<T>(lhs) > cds::forward<U>(rhs) ? lhs : rhs;
}

template <typename T1, typename T2, typename T3, typename... R> CDS_ATTR(2(nodiscard, constexpr(11))) auto minOf(
    T1&& v1, T2&& v2, T3&& v3, R&&... r
) noexcept -> ::cds::meta::Common<T1, T2, T3, R...> {
  return minOf(cds::forward<T1>(v1), minOf(cds::forward<T2>(v2), cds::forward<T3>(v3), cds::forward<R>(r)...));
}

template <typename T1, typename T2, typename T3, typename... R> CDS_ATTR(2(nodiscard, constexpr(11))) auto maxOf(
    T1&& v1, T2&& v2, T3&& v3, R&&... r
) noexcept -> ::cds::meta::Common<T1, T2, T3, R...> {
  return maxOf(cds::forward<T1>(v1), maxOf(cds::forward<T2>(v2), cds::forward<T3>(v3), cds::forward<R>(r)...));
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto begin(T&& range) noexcept -> typename E::Iterator {
  return cds::forward<T>(range).begin();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename E::Iterator {
  return cds::forward<T>(range).end();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E1 = ::cds::meta::impl::HasIterableMemberFns<D>,
    typename E2 = ::cds::meta::impl::HasConstIterableMemberFns<D>,
    ::cds::meta::EnableIf<::cds::meta::And<::cds::meta::Not<E1>, E2>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto begin(T&& range) noexcept -> typename E2::ConstIterator {
  return cds::forward<T>(range).cbegin();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E1 = ::cds::meta::impl::HasIterableMemberFns<D>,
    typename E2 = ::cds::meta::impl::HasConstIterableMemberFns<D>,
    ::cds::meta::EnableIf<::cds::meta::And<::cds::meta::Not<E1>, E2>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename E2::ConstIterator {
  return cds::forward<T>(range).cend();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasConstIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin(T&& range) noexcept -> typename E::ConstIterator {
  return cds::forward<T>(range).cbegin();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasConstIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto cend(T&& range) noexcept -> typename E::ConstIterator {
  return cds::forward<T>(range).cend();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasReverseIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin(T&& range) noexcept -> typename E::ReverseIterator {
  return cds::forward<T>(range).rbegin();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasReverseIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename E::ReverseIterator {
  return cds::forward<T>(range).rend();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E1 = ::cds::meta::impl::HasReverseIterableMemberFns<D>,
    typename E2 = ::cds::meta::impl::HasConstReverseIterableMemberFns<D>,
    ::cds::meta::EnableIf<::cds::meta::And<::cds::meta::Not<E1>, E2>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin(T&& range) noexcept -> typename E2::ConstReverseIterator {
  return cds::forward<T>(range).crbegin();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E1 = ::cds::meta::impl::HasReverseIterableMemberFns<D>,
    typename E2 = ::cds::meta::impl::HasConstReverseIterableMemberFns<D>,
    ::cds::meta::EnableIf<::cds::meta::And<::cds::meta::Not<E1>, E2>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename E2::ConstReverseIterator {
  return cds::forward<T>(range).crend();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasConstReverseIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin(T&& range) noexcept -> typename E::ConstReverseIterator {
  return cds::forward<T>(range).crbegin();
}

template <
    typename T, typename D = ::cds::meta::Decay<T>,
    typename E = ::cds::meta::impl::HasConstReverseIterableMemberFns<D>, ::cds::meta::EnableIf<E> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto crend(T&& range) noexcept -> typename E::ConstReverseIterator {
  return cds::forward<T>(range).crend();
}

namespace meta {
namespace impl {
template <typename T, typename V, typename = void> struct HasContains : False {
  static constexpr bool exceptSpec = true;
};

template <typename T, typename V>
struct HasContains<T, V, Void<decltype(::cds::meta::rvalue<T>().contains(::cds::meta::rvalue<V>()))>> : True {
  static constexpr bool exceptSpec = CDS_ATTR(noexcept(::cds::meta::rvalue<T>().contains(::cds::meta::rvalue<V>())));
};
template <typename T, typename V, typename S, typename = void> struct HasSelectorContains : False {
  static constexpr bool exceptSpec = true;
};

template <typename T, typename V, typename S> struct HasSelectorContains<T, V, S, Void<
    decltype(::cds::meta::rvalue<T>().contains(::cds::meta::rvalue<V>(), ::cds::meta::rvalue<S>()))
>> : True {
  static constexpr bool exceptSpec = CDS_ATTR(noexcept(
      ::cds::meta::rvalue<T>().contains(::cds::meta::rvalue<V>(), ::cds::meta::rvalue<S>())
  ));
};
} // namespace impl
} // namespace meta

namespace meta {
namespace impl {
template <typename T, typename = void> struct IsIterable : False {};
template <typename T, typename = void> struct IsReverseIterable : False {};

template <typename T, Size s> struct IsIterable<T[s]> : True {};
template <typename T, Size s> struct IsIterable<T(&)[s]> : True {};
template <typename T, Size s> struct IsReverseIterable<T[s]> : True {};
template <typename T> struct IsIterable<T, Void<
    decltype(::cds::begin(::cds::meta::rvalue<T>())),
    decltype(::cds::end(::cds::meta::rvalue<T>()))
>> : True {
  using Iterator = decltype(::cds::begin(::cds::meta::rvalue<T>()));
};

template <typename T> struct IsReverseIterable<T, Void<
    decltype(::cds::rbegin(::cds::meta::rvalue<T>())),
    decltype(::cds::rend(::cds::meta::rvalue<T>()))
>> : True {
  using ReverseIterator = decltype(::cds::rbegin(::cds::meta::rvalue<T>()));
};
} // namespace impl

template <typename T> struct IsIterable : ::cds::meta::impl::IsIterable<T>::Type {};
template <typename T> struct IsReverseIterable : ::cds::meta::impl::IsReverseIterable<T>::Type {};
} // namespace meta

namespace impl {
template <
    typename T, typename V,
    typename C = ::cds::meta::impl::HasContains<T, V>,
    typename I = ::cds::meta::impl::IsIterable<T>,
    typename RI = ::cds::meta::impl::IsReverseIterable<T>,
    ::cds::meta::EnableIf<::cds::meta::Not<::cds::meta::Or<C, I, RI>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what) noexcept -> bool {
  (void) where;
  (void) what;
  static_assert(C::value || I::value, "Given type does not provide a 'contains' function for target parameter");
  return false;
}

template <
    typename T, typename V, typename S,
    typename C = ::cds::meta::impl::HasSelectorContains<T, V, S>,
    typename I = ::cds::meta::impl::IsIterable<T>,
    typename RI = ::cds::meta::impl::IsReverseIterable<T>,
    ::cds::meta::EnableIf<::cds::meta::Not<::cds::meta::Or<C, I, RI>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector) noexcept -> bool {
  (void) where;
  (void) what;
  (void) selector;
  static_assert(
      C::value || I::value,
      "Given type does not provide a 'contains' function with selector for target parameter"
  );
  return false;
}

template <typename T, typename V, typename C = ::cds::meta::impl::HasContains<T, V>, ::cds::meta::EnableIf<C> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what) CDS_ATTR(noexcept(C::exceptSpec)) -> bool {
  return cds::forward<T>(where).contains(cds::forward<V>(what));
}

template <
    typename T, typename V,
    typename C = ::cds::meta::impl::HasContains<T, V>,
    typename I = ::cds::meta::impl::IsIterable<T>,
    ::cds::meta::EnableIf<::cds::meta::And<I, ::cds::meta::Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what)
    CDS_ATTR(noexcept(noexcept(*::cds::begin(cds::forward<T>(where)) == ::cds::forward<V>(what)))) -> bool {
  for (auto it = ::cds::begin(::cds::forward<T>(where)), end = ::cds::end(::cds::forward<T>(where)); it != end; ++it) {
    if (*it == ::cds::forward<V>(what)) {
      return true;
    }
  }
  return false;
}

template <
    typename T, typename V,
    typename C = ::cds::meta::impl::HasContains<T, V>,
    typename I = ::cds::meta::impl::IsIterable<T>,
    typename RI = ::cds::meta::impl::IsReverseIterable<T>,
    ::cds::meta::EnableIf<::cds::meta::And<RI, ::cds::meta::Not<C>, ::cds::meta::Not<I>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what)
    CDS_ATTR(noexcept(noexcept(*::cds::rbegin(cds::forward<T>(where)) == ::cds::forward<V>(what)))) -> bool {
  for (auto it = ::cds::rbegin(::cds::forward<T>(where)), end = ::cds::rend(::cds::forward<T>(where)); it != end; ++it) {
    if (*it == ::cds::forward<V>(what)) {
      return true;
    }
  }
  return false;
}

template <
    typename T, typename V, typename S,
    typename C = ::cds::meta::impl::HasSelectorContains<T, V, S>, ::cds::meta::EnableIf<C> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector)
    CDS_ATTR(noexcept(C::exceptSpec)) -> bool {
  return ::cds::forward<T>(where).contains(::cds::forward<V>(what), ::cds::forward<S>(selector));
}

template <
    typename T, typename V, typename S,
    typename C = ::cds::meta::impl::HasSelectorContains<T, V, S>,
    typename I = ::cds::meta::impl::IsIterable<T>,
    ::cds::meta::EnableIf<::cds::meta::And<I, ::cds::meta::Not<C>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector) CDS_ATTR(noexcept(noexcept(
    ::cds::forward<S>(selector)(*::cds::begin(::cds::forward<T>(where))) == ::cds::forward<V>(what)
))) -> bool {
  for (auto it = ::cds::begin(::cds::forward<T>(where)), end = ::cds::end(::cds::forward<T>(where)); it != end; ++it) {
    if (::cds::forward<S>(selector)(*it) == ::cds::forward<V>(what)) {
      return true;
    }
  }

  return false;
}

template <
    typename T, typename V, typename S,
    typename C = ::cds::meta::impl::HasSelectorContains<T, V, S>,
    typename I = ::cds::meta::impl::IsIterable<T>,
    typename RI = ::cds::meta::impl::IsReverseIterable<T>,
    ::cds::meta::EnableIf<::cds::meta::And<RI, ::cds::meta::Not<C>, ::cds::meta::Not<I>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector) CDS_ATTR(noexcept(noexcept(
    ::cds::forward<S>(selector)(*::cds::rbegin(::cds::forward<T>(where))) == ::cds::forward<V>(what)
))) -> bool {
  for (auto it = ::cds::rbegin(::cds::forward<T>(where)), end = ::cds::rend(::cds::forward<T>(where)); it != end; ++it) {
    if (::cds::forward<S>(selector)(*it) == ::cds::forward<V>(what)) {
      return true;
    }
  }

  return false;
}

template <typename T, typename F, typename I = decltype(::cds::begin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(T&& iterable, F&& from) CDS_ATTR(noexcept(noexcept(
    ::cds::impl::contains(::cds::forward<F>(from), *::cds::begin(::cds::forward<T>(iterable)))
))) -> I {
  auto const end = ::cds::end(::cds::forward<T>(iterable));
  for (auto it = ::cds::begin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (::cds::impl::contains(::cds::forward<F>(from), *it)) {
      return it;
    }
  }

  return end;
}

template <typename T, typename F, typename S, typename I = decltype(::cds::begin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(
    T&& iterable,
    F&& from,
    S&& selector
) CDS_ATTR(noexcept(noexcept(::cds::impl::contains(
    ::cds::forward<F>(from),
    ::cds::forward<S>(selector)(*::cds::begin(::cds::forward<T>(iterable)))
)))) -> I {
  auto const end = ::cds::end(cds::forward<T>(iterable));
  for (auto it = ::cds::begin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (::cds::impl::contains(::cds::forward<F>(from), ::cds::forward<S>(selector)(*it))) {
      return it;
    }
  }

  return end;
}

template <typename T, typename F, typename I = decltype(::cds::rbegin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(T&& iterable, F&& from) CDS_ATTR(noexcept(noexcept(
    ::cds::impl::contains(::cds::forward<F>(from), *::cds::rbegin(::cds::forward<T>(iterable)))
))) -> I {
  auto const end = ::cds::rend(::cds::forward<T>(iterable));
  for (auto it = ::cds::rbegin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (::cds::impl::contains(::cds::forward<F>(from), *it)) {
      return it;
    }
  }

  return end;
}

template <typename T, typename F, typename S, typename I = decltype(::cds::rbegin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(
    T&& iterable,
    F&& from,
    S&& selector
) CDS_ATTR(noexcept(noexcept(::cds::impl::contains(
    ::cds::forward<F>(from),
    ::cds::forward<S>(selector)(*::cds::rbegin(::cds::forward<T>(iterable)))
)))) -> I {
  auto const end = ::cds::rend(::cds::forward<T>(iterable));
  for (auto it = ::cds::rbegin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (::cds::impl::contains(::cds::forward<F>(from), ::cds::forward<S>(selector)(*it))) {
      return it;
    }
  }

  return end;
}

template <typename T, typename F, typename I = decltype(::cds::begin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(T&& iterable, F&& from) CDS_ATTR(noexcept(noexcept(
    ::cds::impl::contains(::cds::forward<F>(from), *::cds::begin(::cds::forward<T>(iterable)))
))) -> I {
  auto const end = ::cds::end(::cds::forward<T>(iterable));
  for (auto it = ::cds::begin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (!::cds::impl::contains(::cds::forward<F>(from), *it)) {
      return it;
    }
  }

  return end;
}

template <typename T, typename F, typename S, typename I = decltype(::cds::begin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(
    T&& iterable,
    F&& from,
    S&& selector
) CDS_ATTR(noexcept(noexcept(::cds::impl::contains(
    ::cds::forward<F>(from),
    ::cds::forward<S>(selector)(*::cds::begin(::cds::forward<T>(iterable)))
)))) -> I {
  auto const end = ::cds::end(::cds::forward<T>(iterable));
  for (auto it = ::cds::begin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (!::cds::impl::contains(::cds::forward<F>(from), ::cds::forward<S>(selector)(*it))) {
      return it;
    }
  }

  return end;
}

template <typename T, typename F, typename I = decltype(::cds::rbegin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(T&& iterable, F&& from) CDS_ATTR(noexcept(noexcept(
    ::cds::impl::contains(::cds::forward<F>(from), *::cds::rbegin(::cds::forward<T>(iterable)))
))) -> I {
  auto const end = ::cds::rend(::cds::forward<T>(iterable));
  for (auto it = ::cds::rbegin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (!::cds::impl::contains(::cds::forward<F>(from), *it)) {
      return it;
    }
  }

  return end;
}

template <typename T, typename F, typename S, typename I = decltype(::cds::rbegin(::cds::meta::rvalue<T>()))>
CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(
    T&& iterable,
    F&& from,
    S&& selector
) CDS_ATTR(noexcept(noexcept(::cds::impl::contains(
    ::cds::forward<F>(from),
    ::cds::forward<S>(selector)(*::cds::rbegin(::cds::forward<T>(iterable)))
)))) -> I {
  auto const end = ::cds::rend(::cds::forward<T>(iterable));
  for (auto it = ::cds::rbegin(::cds::forward<T>(iterable)); it != end; ++it) {
    if (!::cds::impl::contains(::cds::forward<F>(from), ::cds::forward<S>(selector)(*it))) {
      return it;
    }
  }

  return end;
}
} // namespace impl
} // namespace cds

#endif // CDS_META_UTILITY_HPP
