//
// Created by loghin on 3/17/24.
//

#ifndef CDS_STRING_OPERATOR_HPP
#define CDS_STRING_OPERATOR_HPP
#pragma once

#include <cds/meta/Base>

#include "StringAbstract.hpp"

namespace cds {
namespace impl {
namespace strop {
using meta::False;
using meta::True;
using meta::RemoveCVRef;
using meta::Count;
using meta::Le;
using meta::Int;

#if CDS_ATTR(spaceship)
using std::strong_ordering;
#endif

template <typename> struct UsesStringStropD : False {};
template <typename C, typename U> struct UsesStringStropD<BaseStringView<C, U>> : True {};
template <typename C, typename U, typename A> struct UsesStringStropD<BaseString<C, U, A>> : True {};
template <typename T> struct UsesStringStrop : UsesStringStropD<RemoveCVRef<T>> {};

template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(L&& lhs, R&& rhs) noexcept -> bool {
  using LA = StringAbstract<L>;
  using RA = StringAbstract<R>;
  auto const b1 = LA::data(fwd<L>(lhs));
  auto const l1 = LA::length(fwd<L>(lhs));
  auto const b2 = RA::data(fwd<R>(rhs));
  auto const l2 = RA::length(fwd<R>(rhs));
  if (l1 != l2) {
    return false;
  }

  return Ordering::Equal == compare(b1, b1 + l1, b2, b2 + l2);
}

template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(L&& lhs, R&& rhs) noexcept -> bool {
  using LA = StringAbstract<L>;
  using RA = StringAbstract<R>;
  auto const b1 = LA::data(fwd<L>(lhs));
  auto const l1 = LA::length(fwd<L>(lhs));
  auto const b2 = RA::data(fwd<R>(rhs));
  auto const l2 = RA::length(fwd<R>(rhs));
  if (l1 != l2) {
    return true;
  }

  return Ordering::Equal != compare(b1, b1 + l1, b2, b2 + l2);
}

template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator<(L&& lhs, R&& rhs) noexcept -> bool {
  using LA = StringAbstract<L>;
  using RA = StringAbstract<R>;
  auto const b1 = LA::data(fwd<L>(lhs));
  auto const l1 = LA::length(fwd<L>(lhs));
  auto const b2 = RA::data(fwd<R>(rhs));
  auto const l2 = RA::length(fwd<R>(rhs));
  return Ordering::Less == compare(b1, b1 + l1, b2, b2 + l2);
}

template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator>(L&& lhs, R&& rhs) noexcept -> bool {
  using LA = StringAbstract<L>;
  using RA = StringAbstract<R>;
  auto const b1 = LA::data(fwd<L>(lhs));
  auto const l1 = LA::length(fwd<L>(lhs));
  auto const b2 = RA::data(fwd<R>(rhs));
  auto const l2 = RA::length(fwd<R>(rhs));
  return Ordering::Greater == compare(b1, b1 + l1, b2, b2 + l2);
}

template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator<=(L&& lhs, R&& rhs) noexcept -> bool {
  using LA = StringAbstract<L>;
  using RA = StringAbstract<R>;
  auto const b1 = LA::data(fwd<L>(lhs));
  auto const l1 = LA::length(fwd<L>(lhs));
  auto const b2 = RA::data(fwd<R>(rhs));
  auto const l2 = RA::length(fwd<R>(rhs));
  return Ordering::Greater != compare(b1, b1 + l1, b2, b2 + l2);
}

template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator>=(L&& lhs, R&& rhs) noexcept -> bool {
  using LA = StringAbstract<L>;
  using RA = StringAbstract<R>;
  auto const b1 = LA::data(fwd<L>(lhs));
  auto const l1 = LA::length(fwd<L>(lhs));
  auto const b2 = RA::data(fwd<R>(rhs));
  auto const l2 = RA::length(fwd<R>(rhs));
  return Ordering::Less != compare(b1, b1 + l1, b2, b2 + l2);
}

#if CDS_ATTR(spaceship)
template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator<=>(L&& lhs, R&& rhs) noexcept -> strong_ordering {
  using LA = StringAbstract<L>;
  using RA = StringAbstract<R>;
  auto const b1 = LA::data(fwd<L>(lhs));
  auto const l1 = LA::length(fwd<L>(lhs));
  auto const b2 = RA::data(fwd<R>(rhs));
  auto const l2 = RA::length(fwd<R>(rhs));
  auto const r = compare(b1, b1 + l1, b2, b2 + l2);
  if (r == Ordering::Greater) { return strong_ordering::greater; }
  if (r == Ordering::Less) { return strong_ordering::less; }
  return strong_ordering::equal;
}
#endif

class StringOperatorUser {
private:
  template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>>>
  CDS_ATTR(constexpr(14)) friend auto operator==(L&& lhs, R&& rhs) noexcept -> bool;

  template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>>>
  CDS_ATTR(constexpr(14)) friend auto operator!=(L&& lhs, R&& rhs) noexcept -> bool;

  template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>>>
  CDS_ATTR(constexpr(14)) friend auto operator<(L&& lhs, R&& rhs) noexcept -> bool;

  template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>>>
  CDS_ATTR(constexpr(14)) friend auto operator>(L&& lhs, R&& rhs) noexcept -> bool;

  template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>>>
  CDS_ATTR(constexpr(14)) friend auto operator<=(L&& lhs, R&& rhs) noexcept -> bool;

  template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>>>
  CDS_ATTR(constexpr(14)) friend auto operator>=(L&& lhs, R&& rhs) noexcept -> bool;

#if CDS_ATTR(spaceship)
  template <typename L, typename R, EnableIf<Le<Int<1>, Count<UsesStringStrop, L, R>>>>
  CDS_ATTR(constexpr(14)) friend auto operator<=>(L&& lhs, R&& rhs) noexcept -> strong_ordering;
#endif
};
} // namespace strop
} // namespace impl
} // namespace cds

#endif // CDS_STRING_OPERATOR_HPP
