//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_CONVERTIBLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_CONVERTIBLE_BASE_HPP
#pragma once

#include <cds/meta/ObjectTraits>

#include "ExpectedMonadicBase.hpp"
#include "Unexpected.hpp"

namespace cds {
namespace impl {
using meta::And;
using meta::EnableIf;
using meta::IsConstructible;
using meta::IsConvertible;
using meta::IsNoexceptConstructible;
using meta::Or;

template <typename T, typename E> class ExpectedConvertibleBase :
    public ExpectedMonadicBase<T, E> {
  using Base = ExpectedMonadicBase<T, E>;

protected:
  using Base::constructFrom;

public:
  using Base::Base;

  ExpectedConvertibleBase() = default;
  ExpectedConvertibleBase(ExpectedConvertibleBase const&) = default;
  ExpectedConvertibleBase(ExpectedConvertibleBase&&) = default;
  auto operator=(ExpectedConvertibleBase const&) -> ExpectedConvertibleBase& = default;
  auto operator=(ExpectedConvertibleBase&&) -> ExpectedConvertibleBase& = default;
  ~ExpectedConvertibleBase() = default;

  template <typename U, typename G, EnableIf<And<
      IsConstructible<T, U const&>,
      IsConstructible<E, G const&>,
      IsConvertible<U const&, T>,
      IsConvertible<G const&, E>
  >> = 0> CDS_ATTR(2(implicit, constexpr(14))) ExpectedConvertibleBase(Expected<U, G> const& other)
      CDS_ATTR(noexcept_v(And<IsNoexceptConstructible<T, U const&>, IsNoexceptConstructible<E, G const&>>)) {
    constructFrom(other);
  }

  template <typename U, typename G, EnableIf<And<
      IsConstructible<T, U const&>,
      IsConstructible<E, G const&>, Or<
          Not<IsConvertible<U const&, T>>,
          Not<IsConvertible<G const&, E>>
      >
  >> = 0> CDS_ATTR(2(explicit, constexpr(14))) ExpectedConvertibleBase(Expected<U, G> const& other)
      CDS_ATTR(noexcept_v(And<IsNoexceptConstructible<T, U const&>, IsNoexceptConstructible<E, G const&>>)) {
    constructFrom(other);
  }

  template <typename U, typename G, EnableIf<And<
      IsConstructible<T, U&&>,
      IsConstructible<E, G&&>,
      IsConvertible<U, T&&>,
      IsConvertible<G, E&&>
  >> = 0> CDS_ATTR(2(implicit, constexpr(14))) ExpectedConvertibleBase(Expected<U, G>&& other)
      CDS_ATTR(noexcept_v(And<IsNoexceptConstructible<T, U&&>, IsNoexceptConstructible<E, G&&>>)) {
    constructFrom(mv(other));
  }

  template <typename U, typename G, EnableIf<And<
      IsConstructible<T, U&&>,
      IsConstructible<E, G&&>, Or<
          Not<IsConvertible<U&&, T>>,
          Not<IsConvertible<G&&, E>>
      >
  >> = 0> CDS_ATTR(2(explicit, constexpr(14))) ExpectedConvertibleBase(Expected<U, G>&& other)
      CDS_ATTR(noexcept_v(And<IsNoexceptConstructible<T, U&&>, IsNoexceptConstructible<E, G&&>>)) {
    constructFrom(mv(other));
  }

  template <typename G, EnableIf<And<
      IsConstructible<E, G const&>,
      IsConvertible<G const&, E>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G> const& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G const&>)) :
      Base{Unexpect{}, unexpected.error()} {}

  template <typename G, EnableIf<And<
      IsConstructible<E, G const&>,
      Not<IsConvertible<G const&, E>>
  >> = 0> CDS_ATTR(2(explicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G> const& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G const&>)) :
      Base{Unexpect{}, unexpected.error()} {}

  template <typename G, EnableIf<And<
      IsConstructible<E, G&&>,
      IsConvertible<G&&, E>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G>&& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G&&>)) :
      Base{Unexpect{}, mv(unexpected).error()} {}

  template <typename G, EnableIf<And<
      IsConstructible<E, G&&>,
      Not<IsConvertible<G&&, E>>
  >> = 0> CDS_ATTR(2(explicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G>&& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G&&>)) :
      Base{Unexpect{}, mv(unexpected).error()} {}
};

template <typename E> class ExpectedConvertibleBase<void, E> :
    public ExpectedMonadicBase<void, E> {
  using Base = ExpectedMonadicBase<void, E>;

protected:
  using Base::constructFrom;

public:
  using Base::Base;

  ExpectedConvertibleBase() = default;
  ExpectedConvertibleBase(ExpectedConvertibleBase const&) = default;
  ExpectedConvertibleBase(ExpectedConvertibleBase&&) = default;
  auto operator=(ExpectedConvertibleBase const&) -> ExpectedConvertibleBase& = default;
  auto operator=(ExpectedConvertibleBase&&) -> ExpectedConvertibleBase& = default;
  ~ExpectedConvertibleBase() = default;

  template <typename G, EnableIf<And<
      IsConstructible<E, G const&>,
      IsConvertible<G const&, E>
  >> = 0> CDS_ATTR(2(implicit, constexpr(14))) ExpectedConvertibleBase(Expected<void, G> const& other)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G const&>)) {
    constructFrom(other);
  }

  template <typename G, EnableIf<And<
      IsConstructible<E, G const&>,
      Not<IsConvertible<G const&, E>>
  >> = 0> CDS_ATTR(2(explicit, constexpr(14))) ExpectedConvertibleBase(Expected<void, G> const& other)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G const&>)) {
    constructFrom(other);
  }

  template <typename G, EnableIf<And<
      IsConstructible<E, G&&>,
      IsConvertible<G, E&&>
  >> = 0> CDS_ATTR(2(implicit, constexpr(14))) ExpectedConvertibleBase(Expected<void, G>&& other)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G&&>)) {
    constructFrom(mv(other));
  }

  template <typename G, EnableIf<And<
      IsConstructible<E, G&&>,
      Not<IsConvertible<G&&, E>>
  >> = 0> CDS_ATTR(2(explicit, constexpr(14))) ExpectedConvertibleBase(Expected<void, G>&& other)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G&&>)) {
    constructFrom(mv(other));
  }

  template <typename G, EnableIf<And<
      IsConstructible<E, G const&>,
      IsConvertible<G const&, E>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G> const& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G const&>)) :
      Base{Unexpect{}, unexpected.error()} {}

  template <typename G, EnableIf<And<
      IsConstructible<E, G const&>,
      Not<IsConvertible<G const&, E>>
  >> = 0> CDS_ATTR(2(explicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G> const& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G const&>)) :
      Base{Unexpect{}, unexpected.error()} {}

  template <typename G, EnableIf<And<
      IsConstructible<E, G&&>,
      IsConvertible<G&&, E>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G>&& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G&&>)) :
      Base{Unexpect{}, mv(unexpected).error()} {}

  template <typename G, EnableIf<And<
      IsConstructible<E, G&&>,
      Not<IsConvertible<G&&, E>>
  >> = 0> CDS_ATTR(2(explicit, constexpr(11))) ExpectedConvertibleBase(Unexpected<G>&& unexpected)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, G&&>)) :
      Base{Unexpect{}, mv(unexpected).error()} {}
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_CONVERTIBLE_BASE_HPP
