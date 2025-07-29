//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_DEFAULT_CONSTRUCTIBLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_DEFAULT_CONSTRUCTIBLE_BASE_HPP
#pragma once

#include <cds/meta/Tags>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedConstructionBase.hpp"

namespace cds {
namespace impl {
using meta::InPlace;
using meta::SpecialMemberFunctionInfoType;

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedDefaultConstructionDetail<T, E>::value>
class ExpectedDefaultConstructibleBase : public ExpectedConstructionBase<T, E> {
  using Base = ExpectedConstructionBase<T, E>;

public:
  using Base::Base;
  ExpectedDefaultConstructibleBase(ExpectedDefaultConstructibleBase const&) = default;
  ExpectedDefaultConstructibleBase(ExpectedDefaultConstructibleBase&&) = default;
  auto operator=(ExpectedDefaultConstructibleBase const&) -> ExpectedDefaultConstructibleBase& = default;
  auto operator=(ExpectedDefaultConstructibleBase&&) -> ExpectedDefaultConstructibleBase& = default;
  ~ExpectedDefaultConstructibleBase() = default;

  CDS_ATTR(constexpr(11)) ExpectedDefaultConstructibleBase()
      CDS_ATTR(noexcept_v(IsNoexceptDefaultConstructible<T>)) = default;
};

template <typename T, typename E> class ExpectedDefaultConstructibleBase<T, E, SpecialMemberFunctionInfoType::Deleted> :
    public ExpectedConstructionBase<T, E> {
  using Base = ExpectedConstructionBase<T, E>;

public:
  using Base::Base;
  ExpectedDefaultConstructibleBase(ExpectedDefaultConstructibleBase const&) = default;
  ExpectedDefaultConstructibleBase(ExpectedDefaultConstructibleBase&&) = default;
  auto operator=(ExpectedDefaultConstructibleBase const&) -> ExpectedDefaultConstructibleBase& = default;
  auto operator=(ExpectedDefaultConstructibleBase&&) -> ExpectedDefaultConstructibleBase& = default;
  ~ExpectedDefaultConstructibleBase() = default;

  ExpectedDefaultConstructibleBase() = delete;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_DEFAULT_CONSTRUCTIBLE_BASE_HPP
