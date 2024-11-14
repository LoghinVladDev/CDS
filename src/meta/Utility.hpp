//
// Created by loghin on 12/13/23.
//

#ifndef CDS_META_UTILITY_HPP
#define CDS_META_UTILITY_HPP
#pragma once

#include <cds/meta/StdLib>

#if CDS_ATTR(msvc)
#pragma warning(disable: 4180)
#endif

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

namespace impl {
using meta::lvalue;

enum class Ordering : U8 { Less, Equal, Greater };

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(14)) auto copy(I sFirst, S sLast, O dFirst) CDS_ATTR(noexcept(
    noexcept(*dFirst = *sFirst) && noexcept(sFirst != sLast) && noexcept(++lvalue<I>()) && noexcept(++lvalue<O>())
)) -> O {
  for (; sFirst != sLast; ++sFirst, ++dFirst) {
    *dFirst = *sFirst;
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(14)) auto copyN(I sFirst, S count, O dFirst)
    CDS_ATTR(noexcept(noexcept(*dFirst = *sFirst) && noexcept(++lvalue<I>()) && noexcept(++lvalue<O>()))) -> O {
  for (S cnt = 0; cnt != count; ++sFirst, ++dFirst, ++cnt) {
    *dFirst = *sFirst;
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto copyInitialize(I sFirst, S sLast, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, *sFirst)) && noexcept(sFirst != sLast)
    && noexcept(++lvalue<I>()) && noexcept(++lvalue<O>())
)) -> O {
  for (; sFirst != sLast; ++sFirst, ++dFirst) {
    construct(dFirst, *sFirst);
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto copyNInitialize(I sFirst, S count, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, *sFirst)) && noexcept(++lvalue<I>()) && noexcept(++lvalue<O>())
)) -> O {
  for (S cnt = 0; cnt != count; ++sFirst, ++dFirst, ++cnt) {
    construct(dFirst, *sFirst);
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto moveInitialize(I sFirst, S sLast, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, cds::move(*sFirst))) && noexcept(sFirst != sLast)
    && noexcept(++lvalue<I>()) && noexcept(++lvalue<O>())
)) -> O {
  for (; sFirst != sLast; ++sFirst, ++dFirst) {
    construct(dFirst, cds::move(*sFirst));
  }
  return dFirst;
}

template <typename I, typename S, typename O>
CDS_ATTR(constexpr(20)) auto moveNInitialize(I sFirst, S count, O dFirst) CDS_ATTR(noexcept(
    noexcept(construct(dFirst, cds::move(*sFirst))) && noexcept(++lvalue<I>()) && noexcept(++lvalue<O>())
)) -> O {
  for (S cnt = 0; cnt != count; ++sFirst, ++dFirst, ++cnt) {
    construct(dFirst, cds::move(*sFirst));
  }
  return dFirst;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fill(I first, S last, T const& value)
    CDS_ATTR(noexcept(noexcept(*first = value) && noexcept(first != last) && noexcept(++lvalue<I>()))) -> I {
  for (; first != last; ++first) {
    *first = value;
  }
  return first;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fillN(I first, S count, T const& value)
    CDS_ATTR(noexcept(noexcept(*first = value) && noexcept(++lvalue<I>()))) -> I {
  for (S cnt = 0; cnt != count; ++first, ++cnt) {
    *first = value;
  }
  return first;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fillInitialize(I first, S last, T const& value)
    CDS_ATTR(noexcept(noexcept(construct(first, value)) && noexcept(first != last) && noexcept(++lvalue<I>()))) -> I {
  for (; first != last; ++first) {
    construct(first, value);
  }
  return first;
}

template <typename I, typename S, typename T>
CDS_ATTR(constexpr(14)) auto fillNInitialize(I first, S count, T const& value)
    CDS_ATTR(noexcept(noexcept(construct(first, value)) && noexcept(++lvalue<I>()))) -> I {
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

template <typename I, typename S, typename... Args>
CDS_ATTR(constexpr(20)) auto initialize(I first, S end, Args&&... args)
    CDS_ATTR(noexcept(noexcept(construct(first, cds::forward<Args>(args)...)) && noexcept(++lvalue<I>()))) -> I {
  for (; first != end; ++first) {
    construct(first, cds::forward<Args>(args)...);
  }
  return first;
}

template <typename I, typename S, typename... Args>
CDS_ATTR(constexpr(20)) auto initializeN(I first, S count, Args&&... args)
    CDS_ATTR(noexcept(noexcept(construct(first, cds::forward<Args>(args)...)) && noexcept(++lvalue<I>()))) -> I {
  for (S cnt = 0; cnt != count; ++first, ++cnt) {
    construct(first, cds::forward<Args>(args)...);
  }
  return first;
}

template <typename I1, typename S1, typename I2, typename S2> CDS_ATTR(2(nodiscard, constexpr(14)))
auto compare(I1 b1, S1 e1, I2 b2, S2 e2) noexcept -> Ordering {
  for (; b1 != e1 && b2 != e2; ++b1, ++b2) {
    if (*b1 > *b2) { return Ordering::Greater; }
    if (*b1 < *b2) { return Ordering::Less; }
  }

  if (b1 != e1) { return Ordering::Greater; }
  if (b2 != e2) { return Ordering::Less; }
  return Ordering::Equal;
}

struct Ignore {
  template <typename T> CDS_ATTR(constexpr(14)) auto operator=(T&&) const noexcept -> void {}
};

static Ignore constexpr ignore;
} // namespace impl
using impl::ignore;
} // namespace cds

#if CDS_ATTR(msvc)
#pragma warning(default: 4180)
#endif

#endif // CDS_META_UTILITY_HPP
