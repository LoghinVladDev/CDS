//
// Created by loghin on 12/13/23.
//

#ifndef CDS_META_UTILITY_HPP
#define CDS_META_UTILITY_HPP

#include <cds/meta/TypeTraits>
#include <cds/meta/IteratorTraits>

namespace cds {
template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto forward(meta::RemoveRef<T>& v) noexcept -> T&& {
  return static_cast<T&&>(v);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto forward(meta::RemoveRef<T>&& v) noexcept -> T&& {
  static_assert(!meta::IsLValRef<T>::value, "Attempted to use forward to convert rvalue to lvalue");
  return static_cast<T&&>(v);
}

template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto move(T&& v) noexcept -> meta::RemoveRef<T>&& {
  return static_cast<meta::RemoveRef<T>&&>(v);
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(14))) auto exchange(T& obj, U&& newVal) -> T {
  T old = move(obj);
  obj = cds::forward<U>(newVal);
  return old;
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(11))) auto minOf(
    T&& lhs, U&& rhs
) noexcept -> meta::Common<T, U> {
  return cds::forward<T>(lhs) < cds::forward<U>(rhs) ? lhs : rhs;
}

template <typename T, typename U = T> CDS_ATTR(2(nodiscard, constexpr(11))) auto maxOf(
    T&& lhs, U&& rhs
) noexcept -> meta::Common<T, U> {
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

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto begin(T&& range) noexcept -> typename E::Iterator {
  return cds::forward<T>(range).begin();
}

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename E::Iterator {
  return cds::forward<T>(range).end();
}

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasConstIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin(T&& range) noexcept -> typename E::ConstIterator {
  return cds::forward<T>(range).cbegin();
}

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasConstIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto cend(T&& range) noexcept -> typename E::ConstIterator {
  return cds::forward<T>(range).cend();
}

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasReverseIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin(T&& range) noexcept -> typename E::ReverseIterator {
  return cds::forward<T>(range).rbegin();
}

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasReverseIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename E::ReverseIterator {
  return cds::forward<T>(range).rend();
}

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasConstReverseIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin(T&& range) noexcept -> typename E::ConstReverseIterator {
  return cds::forward<T>(range).crbegin();
}

template <typename T, typename D = meta::Decay<T>, typename E = meta::impl::HasConstReverseIterableMemberFns<D>, meta::EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto crend(T&& range) noexcept -> typename E::ConstReverseIterator {
  return cds::forward<T>(range).crend();
}

namespace meta {
namespace impl {
template <typename T, typename V, typename = void> struct HasContains : False {
  static constexpr bool exceptSpec = true;
};

template <typename T, typename V> struct HasContains<T, V, Void<decltype(value<T>().contains(value<V>()))>> : True {
  static constexpr bool exceptSpec = noexcept(meta::value<T>().contains(meta::value<V>()));
};
template <typename T, typename V, typename S, typename = void> struct HasSelectorContains : False {
  static constexpr bool exceptSpec = true;
};

template <typename T, typename V, typename S> struct HasSelectorContains<T, V, S, Void<
    decltype(value<T>().contains(value<V>(), value<S>()))
>> : True {
  static constexpr bool exceptSpec = noexcept(
      meta::value<T>().contains(meta::value<V>(), meta::value<S>())
  );
};
} // namespace impl
} // namespace meta

namespace impl {
template <typename T, typename V, typename C = meta::impl::HasContains<T, V>, meta::EnableIf<meta::Not<C>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what) noexcept -> bool {
  (void) where;
  (void) what;
  static_assert(C::value, "Given type does not provide a 'contains' function for target parameter");
  return false;
}

template <typename T, typename V, typename S, typename C = meta::impl::HasSelectorContains<T, V, S>, meta::EnableIf<meta::Not<C>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector) noexcept -> bool {
  (void) where;
  (void) what;
  (void) selector;
  static_assert(C::value, "Given type does not provide a 'contains' function with selector for target parameter");
  return false;
}

template <typename T, typename V, typename C = meta::impl::HasContains<T, V>, meta::EnableIf<C> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what) noexcept(C::exceptSpec) -> bool {
  return forward<T>(where).contains(forward<V>(what));
}

template <typename T, typename V, typename S, typename C = meta::impl::HasSelectorContains<T, V, S>, meta::EnableIf<C> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(T&& where, V&& what, S&& selector) noexcept(C::exceptSpec) -> bool {
  return cds::forward<T>(where).contains(cds::forward<V>(what), cds::forward<S>(selector));
}
} // namespace impl
} // namespace

#endif // CDS_META_UTILITY_HPP
