//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_COPY_CONSTRUCTIBLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_COPY_CONSTRUCTIBLE_BASE_HPP
#pragma once

#include <cds/meta/ObjectTraits>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedConstructionBase.hpp"

namespace cds {
namespace impl {
using meta::IsNoexceptCopyConstructible;
using meta::SpecialMemberFunctionInfoType;

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedCopyConstructionDetail<T, E>::value>
class ExpectedCopyConstructibleBase;

template <typename T, typename E> class ExpectedCopyConstructibleBase<T, E, SpecialMemberFunctionInfoType::Trivial> :
    public ExpectedDefaultConstructibleBase<T, E> {
  using Base = ExpectedDefaultConstructibleBase<T, E>;

public:
  using Base::Base;
  ExpectedCopyConstructibleBase() = default;
  ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase const&) = default;
  ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase&&) = default;
  auto operator=(ExpectedCopyConstructibleBase const&) -> ExpectedCopyConstructibleBase& = default;
  auto operator=(ExpectedCopyConstructibleBase&&) -> ExpectedCopyConstructibleBase& = default;
  ~ExpectedCopyConstructibleBase() = default;
};

template <typename T, typename E> class ExpectedCopyConstructibleBase<T, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedDefaultConstructibleBase<T, E> {
  using Base = ExpectedDefaultConstructibleBase<T, E>;

protected:
  using Base::constructFrom;

public:
  using Base::Base;
  ExpectedCopyConstructibleBase() = default;
  ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase&&) = default;
  auto operator=(ExpectedCopyConstructibleBase const&) -> ExpectedCopyConstructibleBase& = default;
  auto operator=(ExpectedCopyConstructibleBase&&) -> ExpectedCopyConstructibleBase& = default;
  ~ExpectedCopyConstructibleBase() = default;

  CDS_ATTR(constexpr(14)) ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase const& base)
      CDS_ATTR(noexcept_v(All<IsNoexceptCopyConstructible, T, E>)) {
    constructFrom(base);
  }
};

template <typename T, typename E> class ExpectedCopyConstructibleBase<T, E, SpecialMemberFunctionInfoType::Deleted> :
    public ExpectedDefaultConstructibleBase<T, E> {
  using Base = ExpectedDefaultConstructibleBase<T, E>;

public:
  using Base::Base;
  ExpectedCopyConstructibleBase() = default;
  ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase const&) = delete;
  ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase&&) = default;
  auto operator=(ExpectedCopyConstructibleBase const&) -> ExpectedCopyConstructibleBase& = default;
  auto operator=(ExpectedCopyConstructibleBase&&) -> ExpectedCopyConstructibleBase& = default;
  ~ExpectedCopyConstructibleBase() = default;
};

template <typename E> class ExpectedCopyConstructibleBase<void, E, SpecialMemberFunctionInfoType::NonTrivial> :
    public ExpectedDefaultConstructibleBase<void, E> {
  using Base = ExpectedDefaultConstructibleBase<void, E>;

protected:
  using Base::constructFrom;

public:
  using Base::Base;
  ExpectedCopyConstructibleBase() = default;
  ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase&&) = default;
  auto operator=(ExpectedCopyConstructibleBase const&) -> ExpectedCopyConstructibleBase& = default;
  auto operator=(ExpectedCopyConstructibleBase&&) -> ExpectedCopyConstructibleBase& = default;
  ~ExpectedCopyConstructibleBase() = default;

  CDS_ATTR(constexpr(14)) ExpectedCopyConstructibleBase(ExpectedCopyConstructibleBase const& base)
  CDS_ATTR(noexcept_v(IsNoexceptCopyConstructible<E>)) {
    constructFrom(base);
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_COPY_CONSTRUCTIBLE_BASE_HPP
