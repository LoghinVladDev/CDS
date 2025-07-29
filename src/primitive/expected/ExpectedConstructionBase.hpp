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
  using Base::engaged;
  using Base::data;

public:
  using Base::Base;
  ExpectedConstructionBase() = default;
  ExpectedConstructionBase(ExpectedConstructionBase const&) = default;
  ExpectedConstructionBase(ExpectedConstructionBase&&) = default;
  auto operator=(ExpectedConstructionBase const&) -> ExpectedConstructionBase& = default;
  auto operator=(ExpectedConstructionBase&&) -> ExpectedConstructionBase& = default;
  ~ExpectedConstructionBase() = default;

  template <typename... Args> CDS_ATTR(constexpr(14)) auto emplace(Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) -> T& {
    destroy();
    auto& value = *construct(&data().value, fwd<Args>(args)...);
    engaged() = true;
    return value;
  }

  template <typename U, typename... Args> CDS_ATTR(constexpr(14))
  auto emplace(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) -> T& {
    destroy();
    auto& value = *construct(&data().value, list, fwd<Args>(args)...);
    engaged() = true;
    return value;
  }

  template <typename U = RemoveConstVolatile<T>> CDS_ATTR(constexpr(14)) auto operator=(U&& value)
      CDS_ATTR(noexcept_v(And<IsNoexceptConstructible<T, U&&>, IsNoexceptAssignable<T, U&&>>))
      -> ExpectedConstructionBase& {
    if (engaged()) {
      data().value = fwd<U>(value);
      return *this;
    }

    construct(&data().value, fwd<U>(value));
    engaged() = true;
    return *this;
  }

protected:
  template <typename B> CDS_ATTR(constexpr(14)) auto constructFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    if (otherBase.engaged()) {
      construct(&data().value, fwd<B>(otherBase).data().value);
      engaged() = true;
    } else {
      construct(&data().error, fwd<B>(otherBase).data().error);
    }
  }

  template <typename B> CDS_ATTR(constexpr(14)) auto assignFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    destroy();
    constructFrom(fwd<B>(otherBase));
  }
};

template <typename E> class ExpectedConstructionBase<void, E> : public ExpectedDestructibleBase<void, E> {
  using Base = ExpectedDestructibleBase<void, E>;

protected:
  using Base::destroy;
  using Base::engaged;
  using Base::data;

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
    engaged() = true;
  }

protected:
  template <typename B> CDS_ATTR(constexpr(14)) auto constructFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    if (otherBase.engaged()) {
      engaged() = true;
    } else {
      construct(&data().error, fwd<B>(otherBase).data().error);
    }
  }

  template <typename B> CDS_ATTR(constexpr(14)) auto assignFrom(B&& otherBase)
      /* noexcept-context-dependent */ -> void {
    destroy();
    constructFrom(fwd<B>(otherBase));
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_CONSTRUCTION_BASE_HPP
