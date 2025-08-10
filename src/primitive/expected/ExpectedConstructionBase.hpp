//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_CONSTRUCTION_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_CONSTRUCTION_BASE_HPP
#pragma once

#include <initializer_list>

#include <cds/meta/ObjectTraits>

#include "ExpectedDestructibleBase.hpp"

namespace cds {
namespace impl {
using meta::IsNoexceptConstructible;
using meta::IsNoexceptAssignable;
using meta::RemoveConstVolatile;

template <typename T, typename E> class ExpectedConstructionBase : public ExpectedDestructibleBase<T, E> {
  using Base = ExpectedDestructibleBase<T, E>;

protected:
  using Base::destroy;
  using Base::data;
  using Base::state;

public:
  using Base::Base;
  ExpectedConstructionBase() = default;
  ExpectedConstructionBase(ExpectedConstructionBase const&) = default;
  ExpectedConstructionBase(ExpectedConstructionBase&&) = default;
  auto operator=(ExpectedConstructionBase const&) -> ExpectedConstructionBase& = default;
  auto operator=(ExpectedConstructionBase&&) -> ExpectedConstructionBase& = default;
  ~ExpectedConstructionBase() = default;

  template <typename... Args> CDS_ATTR(constexpr(20)) auto emplace(Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) -> T& {
    destroy();
    auto& value = *construct(&data().value, fwd<Args>(args)...);
    state() = ExpectedState::Value;
    return value;
  }

  template <typename U, typename... Args> CDS_ATTR(constexpr(20))
  auto emplace(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) -> T& {
    destroy();
    auto& value = *construct(&data().value, list, fwd<Args>(args)...);
    state() = ExpectedState::Value;
    return value;
  }

  template <typename U = RemoveConstVolatile<T>> CDS_ATTR(constexpr(20)) auto operator=(U&& value)
      CDS_ATTR(noexcept_v(And<IsNoexceptConstructible<T, U&&>, IsNoexceptAssignable<T, U&&>>))
      -> ExpectedConstructionBase& {
    if (ExpectedState::Value == state()) {
      data().value = fwd<U>(value);
      return *this;
    }

    destroy();
    construct(&data().value, fwd<U>(value));
    state() = ExpectedState::Value;
    return *this;
  }

protected:
  template <typename B> CDS_ATTR(constexpr(20)) auto constructFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    if (ExpectedState::Value == otherBase.state()) {
      construct(&data().value, fwd<B>(otherBase).data().value);
      state() = ExpectedState::Value;
    } else if (ExpectedState::Error == otherBase.state()) {
      construct(&data().error, fwd<B>(otherBase).data().error);
      state() = ExpectedState::Error;
    }
  }

  template <typename B> CDS_ATTR(constexpr(20)) auto assignFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    if (ExpectedState::Value == otherBase.state() && ExpectedState::Value == state()) {
      data().value = fwd<B>(otherBase).data().value;
    } else if (ExpectedState::Error == otherBase.state() && ExpectedState::Error == state()) {
      data().error = fwd<B>(otherBase).data().error;
    } else {
      destroy();
      constructFrom(fwd<B>(otherBase));
    }
  }
};

template <typename E> class ExpectedConstructionBase<void, E> : public ExpectedDestructibleBase<void, E> {
  using Base = ExpectedDestructibleBase<void, E>;

protected:
  using Base::destroy;
  using Base::data;
  using Base::state;

public:
  using Base::Base;
  ExpectedConstructionBase() = default;
  ExpectedConstructionBase(ExpectedConstructionBase const&) = default;
  ExpectedConstructionBase(ExpectedConstructionBase&&) = default;
  auto operator=(ExpectedConstructionBase const&) -> ExpectedConstructionBase& = default;
  auto operator=(ExpectedConstructionBase&&) -> ExpectedConstructionBase& = default;
  ~ExpectedConstructionBase() = default;

  CDS_ATTR(constexpr(14)) auto emplace() noexcept -> void {
    destroy();
    state() = ExpectedState::Value;
  }

protected:
  template <typename B> CDS_ATTR(constexpr(20)) auto constructFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    if (ExpectedState::Value == otherBase.state()) {
      state() = ExpectedState::Value;
    } else if (ExpectedState::Error == otherBase.state()) {
      construct(&data().error, fwd<B>(otherBase).data().error);
      state() = ExpectedState::Error;
    }
  }

  template <typename B> CDS_ATTR(constexpr(20)) auto assignFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    if (ExpectedState::Value == otherBase.state() && ExpectedState::Value == state()) {
      /* nothing */
    } else if (ExpectedState::Error == otherBase.state() && ExpectedState::Error == state()) {
      data().error = fwd<B>(otherBase).data().error;
    } else {
      destroy();
      constructFrom(fwd<B>(otherBase));
    }
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_CONSTRUCTION_BASE_HPP
