//
// Created by loghin on 3/16/24.
//

#ifndef CDS_ITERATOR_ITERATOR_HPP
#define CDS_ITERATOR_ITERATOR_HPP
#pragma once

#include <cds/meta/IteratorTraits>
#include <cds/meta/Semantics>

namespace cds {
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
> CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename E::Sentinel {
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
> CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename CE::Sentinel {
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
> CDS_ATTR(2(nodiscard, constexpr(11))) auto cend(T&& range) noexcept -> typename E::Sentinel {
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
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename E::Sentinel {
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
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename CE::Sentinel {
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
> CDS_ATTR(2(nodiscard, constexpr(11))) auto crend(T&& range) noexcept -> typename E::Sentinel {
  return cds::forward<T>(range).crend();
}

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
} // namespace cds

#endif // CDS_ITERATOR_ITERATOR_HPP
