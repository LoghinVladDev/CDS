//
// Created by loghin on 7/28/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_UNEXPECTED_HPP
#define CDS_PRIMITIVE_EXPECTED_UNEXPECTED_HPP
#pragma once

#include "ContainingError.hpp"

#include <initializer_list>
#include <cds/meta/ObjectTraits>
#include <cds/meta/Semantics>
#include <cds/meta/Tags>

namespace cds {
namespace impl {
using cds::meta::Default;
using cds::meta::DoesNotHide;
using cds::meta::EnableIf;
using cds::meta::False;
using cds::meta::IsDefaultConstructible;
using cds::meta::IsNoexceptConstructible;
using cds::meta::IsNoexceptDefaultConstructible;
using cds::meta::RemoveCVRef;
using cds::meta::True;

struct Unexpect{};

template <typename E> class Unexpected;

template <typename> struct IsUnexpected : False {};
template <typename E> struct IsUnexpected<Unexpected<E>> : True {};

template <typename E> class Unexpected : public ContainingError<Unexpected<E>, E> {
  friend class ContainingError<Unexpected<E>, E>;

public:
  using Error = E;

  Unexpected() = delete;
  Unexpected(Unexpected const&) = default;
  Unexpected(Unexpected&&) = default;
  auto operator=(Unexpected const&) -> Unexpected& = default;
  auto operator=(Unexpected&&) -> Unexpected& = default;
  ~Unexpected() = default;

  template <typename E0 = E, EnableIf<IsDefaultConstructible<E0>> = 0> CDS_ATTR(2(explicit, constexpr(11)))
  Unexpected(Default) CDS_ATTR(noexcept_v(IsNoexceptDefaultConstructible<E0>)) : _error{} {}

  template <typename... Args, EnableIf<DoesNotHide<Unexpected, Args...>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) Unexpected(Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) : _error{fwd<Args>(args)...} {}

  template <typename T, typename... Args> CDS_ATTR(2(implicit, constexpr(11)))
  Unexpected(std::initializer_list<T> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<T> const&, Args&&...>)) :
      _error{list, fwd<Args>(args)...} {}

private:
  E _error;
};

#if CDS_ATTR(ctad)
template <typename E> Unexpected(E) -> Unexpected<E>;
#endif // #if CDS_ATTR(ctad)

template <typename E> CDS_ATTR(2(nodiscard, constexpr(11))) auto unexpectedOf(E&& error)
    CDS_ATTR(noexcept_v(IsNoexceptConstructible<Unexpected<RemoveCVRef<E>>, E&&>)) -> Unexpected<RemoveCVRef<E>> {
  return Unexpected<RemoveCVRef<E>>{fwd<E>(error)};
}

template <typename E, typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto unexpectedOf(Args&&... args)
    CDS_ATTR(noexcept_v(IsNoexceptConstructible<Unexpected<E>, Args&&...>)) -> Unexpected<E> {
  return Unexpected<E>{fwd<Args>(args)...};
}

template <typename E1, typename E2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    Unexpected<E1> const& lhs, Unexpected<E2> const& rhs
) noexcept -> bool {
  return lhs.error() == rhs.error();
}

template <typename E1, typename E2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    Unexpected<E1> const& lhs, Unexpected<E2> const& rhs
) noexcept -> bool {
  return lhs.error() != rhs.error();
}
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_UNEXPECTED_HPP
