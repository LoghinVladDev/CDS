//
// Created by loghin on 3/16/24.
//

#ifndef CDS_ITERATOR_ITERATOR_HPP
#define CDS_ITERATOR_ITERATOR_HPP
#pragma once

#include <cds/meta/IteratorTraits>
#include <cds/meta/Semantics>

namespace cds {
namespace impl {
using meta::And;
using meta::EnableIf;
using meta::IsRandomAccessIterator;
using meta::IsForwardIterator;
using meta::Not;
using meta::RemoveRef;
using meta::RemoveCVRef;

using meta::impl::HasConstIterableMemberFns;
using meta::impl::HasConstReverseIterableMemberFns;
using meta::impl::HasIterableMemberFns;
using meta::impl::HasReverseIterableMemberFns;
using meta::impl::HasSizeMemberFn;

template <typename T, typename D = RemoveRef<T>, typename E = HasIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto begin(T&& range) noexcept -> typename E::Iterator {
  return cds::forward<T>(range).begin();
}

template <typename T, typename D = RemoveRef<T>, typename E = HasIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename E::Sentinel {
  return cds::forward<T>(range).end();
}

template <
    typename T, typename D = RemoveRef<T>,
    typename E = HasIterableMemberFns<D>, typename CE = HasConstIterableMemberFns<D>,
    EnableIf<And<Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto begin(T&& range) noexcept -> typename CE::ConstIterator {
  return cds::forward<T>(range).cbegin();
}

template <
    typename T, typename D = RemoveRef<T>,
    typename E = HasIterableMemberFns<D>, typename CE = HasConstIterableMemberFns<D>,
    EnableIf<And<Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto end(T&& range) noexcept -> typename CE::Sentinel {
  return cds::forward<T>(range).cend();
}

template <typename T, typename D = RemoveRef<T>, typename E = HasConstIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin(T&& range) noexcept -> typename E::ConstIterator {
  return cds::forward<T>(range).cbegin();
}

template <typename T, typename D = RemoveRef<T>, typename E = HasConstIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto cend(T&& range) noexcept -> typename E::Sentinel {
  return cds::forward<T>(range).cend();
}

template <typename T, typename D = RemoveRef<T>, typename E = HasReverseIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin(T&& range) noexcept -> typename E::ReverseIterator {
  return cds::forward<T>(range).rbegin();
}

template <typename T, typename D = RemoveRef<T>, typename E = HasReverseIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename E::Sentinel {
  return cds::forward<T>(range).rend();
}

template <
    typename T, typename D = RemoveRef<T>,
    typename E = HasReverseIterableMemberFns<D>, typename CE = HasConstReverseIterableMemberFns<D>,
    EnableIf<And<Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin(T&& range) noexcept -> typename CE::ConstReverseIterator {
  return cds::forward<T>(range).crbegin();
}

template <
    typename T, typename D = RemoveRef<T>,
    typename E = HasReverseIterableMemberFns<D>, typename CE = HasConstReverseIterableMemberFns<D>,
    EnableIf<And<Not<E>, CE>> = 0
> CDS_ATTR(2(nodiscard, constexpr(11))) auto rend(T&& range) noexcept -> typename CE::Sentinel {
  return cds::forward<T>(range).crend();
}

template <typename T, typename D = RemoveRef<T>, typename E = HasConstReverseIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin(T&& range) noexcept -> typename E::ConstReverseIterator {
  return cds::forward<T>(range).crbegin();
}

template <typename T, typename D = RemoveRef<T>, typename E = HasConstReverseIterableMemberFns<D>, EnableIf<E> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto crend(T&& range) noexcept -> typename E::Sentinel {
  return cds::forward<T>(range).crend();
}

template <typename I, typename S, EnableIf<IsRandomAccessIterator<I, S>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto dist(I const& begin, S const& end) noexcept -> Size {
  return end - begin;
}

template <typename I, typename S, EnableIf<And<Not<IsRandomAccessIterator<I, S>>, IsForwardIterator<I, S>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto dist(I begin, S const& end) noexcept -> Size {
  Size dist = 0u;
  while (begin != end) {
    ++begin;
    ++dist;
  }
  return dist;
}

template <typename R, EnableIf<HasSizeMemberFn<R>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto size(R const& object) noexcept -> Size {
  return object.size();
}

template <typename R, EnableIf<HasSizeMemberFn<R>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto len(R const& object) noexcept -> Size {
  return object.size();
}
} // namespace impl

using impl::begin;
using impl::end;
using impl::cbegin;
using impl::cend;
using impl::rbegin;
using impl::rend;
using impl::crbegin;
using impl::crend;

using impl::dist;
using impl::size;

namespace meta {
namespace impl {
using meta::True;
using meta::False;
using meta::Void;
using meta::rvalue;
using cds::impl::len;

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

template <typename, typename = void> struct IsSizeInvocable : False {};
template <typename T> struct IsSizeInvocable<T, Void<decltype(len(rvalue<T>()))>> : True {};
} // namespace impl

template <typename T> struct IsIterable : impl::IsIterable<T>::Type {};
template <typename T> struct IsReverseIterable : impl::IsReverseIterable<T>::Type {};
} // namespace meta
} // namespace cds

#endif // CDS_ITERATOR_ITERATOR_HPP
