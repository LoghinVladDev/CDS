//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_MOVE_CONSTRUCTIBLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_MOVE_CONSTRUCTIBLE_BASE_HPP
#pragma once

#include <cds/meta/ObjectTraits>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedCopyConstructibleBase.hpp"

namespace cds {
namespace impl {
using meta::IsNoexceptMoveConstructible;
using meta::SpecialMemberFunctionInfoType;

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedMoveConstructionDetail<T, E>::value>
class ExpectedMoveConstructibleBase;

template <typename T, typename E> class ExpectedMoveConstructibleBase<T, E, SpecialMemberFunctionInfoType::Trivial> :
    public ExpectedCopyConstructibleBase<T, E> {
  using Base = ExpectedCopyConstructibleBase<T, E>;

public:
  using Base::Base;
  ExpectedMoveConstructibleBase() = default;
  ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase const&) = default;
  ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase&&) = default;
  auto operator=(ExpectedMoveConstructibleBase const&) -> ExpectedMoveConstructibleBase& = default;
  auto operator=(ExpectedMoveConstructibleBase&&) -> ExpectedMoveConstructibleBase& = default;
  ~ExpectedMoveConstructibleBase() = default;
};

template <typename T, typename E> class ExpectedMoveConstructibleBase<T, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedCopyConstructibleBase<T, E> {
  using Base = ExpectedCopyConstructibleBase<T, E>;

protected:
  using Base::constructFrom;

public:
  using Base::Base;
  ExpectedMoveConstructibleBase() = default;
  ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase const&) = default;
  auto operator=(ExpectedMoveConstructibleBase const&) -> ExpectedMoveConstructibleBase& = default;
  auto operator=(ExpectedMoveConstructibleBase&&) -> ExpectedMoveConstructibleBase& = default;
  ~ExpectedMoveConstructibleBase() = default;

  CDS_ATTR(constexpr(14)) ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase&& base)
      CDS_ATTR(noexcept_v(All<IsNoexceptMoveConstructible, T, E>)) {
    constructFrom(mv(base));
  }
};

template <typename T, typename E> class ExpectedMoveConstructibleBase<T, E, SpecialMemberFunctionInfoType::Deleted> :
    public ExpectedCopyConstructibleBase<T, E> {
  using Base = ExpectedCopyConstructibleBase<T, E>;

public:
  using Base::Base;
  ExpectedMoveConstructibleBase() = default;
  ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase const&) = default;
  ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase&&) = delete;
  auto operator=(ExpectedMoveConstructibleBase const&) -> ExpectedMoveConstructibleBase& = default;
  auto operator=(ExpectedMoveConstructibleBase&&) -> ExpectedMoveConstructibleBase& = default;
  ~ExpectedMoveConstructibleBase() = default;
};

template <typename E> class ExpectedMoveConstructibleBase<void, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedCopyConstructibleBase<void, E> {
  using Base = ExpectedCopyConstructibleBase<void, E>;

protected:
  using Base::constructFrom;

public:
  using Base::Base;
  ExpectedMoveConstructibleBase() = default;
  ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase const&) = default;
  auto operator=(ExpectedMoveConstructibleBase const&) -> ExpectedMoveConstructibleBase& = default;
  auto operator=(ExpectedMoveConstructibleBase&&) -> ExpectedMoveConstructibleBase& = default;
  ~ExpectedMoveConstructibleBase() = default;

  CDS_ATTR(constexpr(14)) ExpectedMoveConstructibleBase(ExpectedMoveConstructibleBase&& base)
  CDS_ATTR(noexcept_v(IsNoexceptMoveConstructible<E>)) {
    constructFrom(mv(base));
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_MOVE_CONSTRUCTIBLE_BASE_HPP
