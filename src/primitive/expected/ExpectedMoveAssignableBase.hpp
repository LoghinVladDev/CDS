//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_MOVE_ASSIGNABLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_MOVE_ASSIGNABLE_BASE_HPP
#pragma once

#include <cds/meta/ObjectTraits>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedCopyAssignableBase.hpp"

namespace cds {
namespace impl {
using meta::IsNoexceptMoveAssignable;
using meta::SpecialMemberFunctionInfoType;

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedMoveAssignDetail<T, E>::value>
class ExpectedMoveAssignableBase;

template <typename T, typename E> class ExpectedMoveAssignableBase<T, E, SpecialMemberFunctionInfoType::Trivial> :
    public ExpectedCopyAssignableBase<T, E> {
  using Base = ExpectedCopyAssignableBase<T, E>;

public:
  using Base::Base;
  ExpectedMoveAssignableBase() = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase const&) = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase&&) = default;
  auto operator=(ExpectedMoveAssignableBase const&) -> ExpectedMoveAssignableBase& = default;
  auto operator=(ExpectedMoveAssignableBase&&) -> ExpectedMoveAssignableBase& = default;
  ~ExpectedMoveAssignableBase() = default;
};

template <typename T, typename E> class ExpectedMoveAssignableBase<T, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedCopyAssignableBase<T, E> {
  using Base = ExpectedCopyAssignableBase<T, E>;

protected:
  using Base::assignFrom;

public:
  using Base::Base;
  ExpectedMoveAssignableBase() = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase const&) = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase&&) = default;
  auto operator=(ExpectedMoveAssignableBase const&) -> ExpectedMoveAssignableBase& = default;
  ~ExpectedMoveAssignableBase() = default;

  CDS_ATTR(constexpr(14)) auto operator=(ExpectedMoveAssignableBase&& base)
      CDS_ATTR(noexcept_v(All<IsNoexceptMoveAssignable, T, E>)) -> ExpectedMoveAssignableBase& {
    if (&base == this) {
      return *this;
    }

    assignFrom(mv(base));
    return *this;
  }
};

template <typename T, typename E> class ExpectedMoveAssignableBase<T, E, SpecialMemberFunctionInfoType::Deleted> :
    public ExpectedCopyAssignableBase<T, E> {
  using Base = ExpectedCopyAssignableBase<T, E>;

public:
  using Base::Base;
  ExpectedMoveAssignableBase() = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase const&) = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase&&) = default;
  auto operator=(ExpectedMoveAssignableBase const&) -> ExpectedMoveAssignableBase& = default;
  auto operator=(ExpectedMoveAssignableBase&&) -> ExpectedMoveAssignableBase& = delete;
  ~ExpectedMoveAssignableBase() = default;
};

template <typename E> class ExpectedMoveAssignableBase<void, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedCopyAssignableBase<void, E> {
  using Base = ExpectedCopyAssignableBase<void, E>;

protected:
  using Base::assignFrom;

public:
  using Base::Base;
  ExpectedMoveAssignableBase() = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase const&) = default;
  ExpectedMoveAssignableBase(ExpectedMoveAssignableBase&&) = default;
  auto operator=(ExpectedMoveAssignableBase const&) -> ExpectedMoveAssignableBase& = default;
  ~ExpectedMoveAssignableBase() = default;

  CDS_ATTR(constexpr(14)) auto operator=(ExpectedMoveAssignableBase&& base)
      CDS_ATTR(noexcept_v(IsNoexceptMoveAssignable<E>)) -> ExpectedMoveAssignableBase& {
    if (&base == this) {
      return *this;
    }

    assignFrom(mv(base));
    return *this;
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_MOVE_ASSIGNABLE_BASE_HPP
