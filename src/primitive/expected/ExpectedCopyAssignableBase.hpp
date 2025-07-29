//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_COPY_ASSIGNABLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_COPY_ASSIGNABLE_BASE_HPP
#pragma once

#include <cds/meta/ObjectTraits>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedMoveConstructibleBase.hpp"

namespace cds {
namespace impl {
using meta::IsNoexceptCopyAssignable;
using meta::SpecialMemberFunctionInfoType;

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedCopyAssignDetail<T, E>::value>
class ExpectedCopyAssignableBase;

template <typename T, typename E> class ExpectedCopyAssignableBase<T, E, SpecialMemberFunctionInfoType::Trivial> :
    public ExpectedMoveConstructibleBase<T, E> {
  using Base = ExpectedMoveConstructibleBase<T, E>;

public:
  using Base::Base;
  ExpectedCopyAssignableBase() = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase const&) = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase&&) = default;
  auto operator=(ExpectedCopyAssignableBase const&) -> ExpectedCopyAssignableBase& = default;
  auto operator=(ExpectedCopyAssignableBase&&) -> ExpectedCopyAssignableBase& = default;
  ~ExpectedCopyAssignableBase() = default;
};

template <typename T, typename E> class ExpectedCopyAssignableBase<T, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedMoveConstructibleBase<T, E> {
  using Base = ExpectedMoveConstructibleBase<T, E>;

protected:
  using Base::assignFrom;

public:
  using Base::Base;
  ExpectedCopyAssignableBase() = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase const&) = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase&&) = default;
  auto operator=(ExpectedCopyAssignableBase&&) -> ExpectedCopyAssignableBase& = default;
  ~ExpectedCopyAssignableBase() = default;

  CDS_ATTR(constexpr(14)) auto operator=(ExpectedCopyAssignableBase const& base)
      CDS_ATTR(noexcept_v(All<IsNoexceptCopyAssignable, T, E>))-> ExpectedCopyAssignableBase& {
    if (&base == this) {
      return *this;
    }

    assignFrom(base);
    return *this;
  }
};

template <typename T, typename E> class ExpectedCopyAssignableBase<T, E, SpecialMemberFunctionInfoType::Deleted> :
    public ExpectedMoveConstructibleBase<T, E> {
  using Base = ExpectedMoveConstructibleBase<T, E>;

public:
  using Base::Base;
  ExpectedCopyAssignableBase() = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase const&) = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase&&) = default;
  auto operator=(ExpectedCopyAssignableBase const&) -> ExpectedCopyAssignableBase& = delete;
  auto operator=(ExpectedCopyAssignableBase&&) -> ExpectedCopyAssignableBase& = default;
  ~ExpectedCopyAssignableBase() = default;
};

template <typename E> class ExpectedCopyAssignableBase<void, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedMoveConstructibleBase<void, E> {
  using Base = ExpectedMoveConstructibleBase<void, E>;

protected:
  using Base::assignFrom;

public:
  using Base::Base;
  ExpectedCopyAssignableBase() = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase const&) = default;
  ExpectedCopyAssignableBase(ExpectedCopyAssignableBase&&) = default;
  auto operator=(ExpectedCopyAssignableBase&&) -> ExpectedCopyAssignableBase& = default;
  ~ExpectedCopyAssignableBase() = default;

  CDS_ATTR(constexpr(14)) auto operator=(ExpectedCopyAssignableBase const& base)
  CDS_ATTR(noexcept_v(IsNoexceptCopyAssignable<E>))-> ExpectedCopyAssignableBase& {
    if (&base == this) {
      return *this;
    }

    assignFrom(base);
    return *this;
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_COPY_ASSIGNABLE_BASE_HPP
