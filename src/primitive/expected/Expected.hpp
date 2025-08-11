//
// Created by loghin on 7/28/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_EXPECTED_HPP
#define CDS_PRIMITIVE_EXPECTED_EXPECTED_HPP
#pragma once

#include "Unexpected.hpp"

#include "ExpectedDecl.hpp"
#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedStorageBase.hpp"
#include "ExpectedDestructibleBase.hpp"
#include "ExpectedConstructionBase.hpp"
#include "ExpectedDefaultConstructibleBase.hpp"
#include "ExpectedCopyConstructibleBase.hpp"
#include "ExpectedMoveConstructibleBase.hpp"
#include "ExpectedCopyAssignableBase.hpp"
#include "ExpectedMoveAssignableBase.hpp"
#include "ExpectedObservableBase.hpp"
#include "ExpectedMonadicBase.hpp"
#include "ExpectedConvertibleBase.hpp"

#include "../../common/SpecialMemberFunctionHelper.hpp"

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;

using meta::All;
using meta::IsCopyAssignable;
using meta::IsCopyConstructible;
using meta::IsMoveAssignable;
using meta::IsMoveConstructible;
using meta::impl::SfinaeAssignBase;
using meta::impl::SfinaeCtorBase;

template <typename T, typename E> class Expected :
    public ExpectedConvertibleBase<T, E>,
    public SfinaeCtorBase<
        All<IsCopyConstructible, T, E>,
        All<IsMoveConstructible, T, E>
    >,
    public SfinaeAssignBase<
        All<IsCopyAssignable, T, E>,
        All<IsMoveAssignable, T, E>
    > {
  using Base = ExpectedConvertibleBase<T, E>;

public:
  using Base::Base;

  Expected() = default;
  Expected(Expected const&) = default;
  Expected(Expected&&) = default;
  auto operator=(Expected const&) -> Expected& = default;
  auto operator=(Expected&&) -> Expected& = default;
  ~Expected() = default;
};

using meta::All;
using meta::IsCopyAssignable;
using meta::IsCopyConstructible;
using meta::IsMoveAssignable;
using meta::IsMoveConstructible;
using meta::impl::SfinaeAssignBase;
using meta::impl::SfinaeCtorBase;

template <typename E> class Expected<void, E> :
    public ExpectedConvertibleBase<void, E>,
    public SfinaeCtorBase<IsCopyConstructible<E>, IsMoveConstructible<E>>,
    public SfinaeAssignBase<IsCopyAssignable<E>, IsMoveAssignable<E>> {
  using Base = ExpectedConvertibleBase<void, E>;

public:
  using Base::Base;

  Expected() = default;
  Expected(Expected const&) = default;
  Expected(Expected&&) = default;
  auto operator=(Expected const&) -> Expected& = default;
  auto operator=(Expected&&) -> Expected& = default;
  ~Expected() = default;
};

template <typename T1, typename E1, typename T2, typename E2> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    Expected<T1, E1> const& lhs, Expected<T2, E2> const& rhs
) noexcept -> bool {
  if (lhs.hasValue() != rhs.hasValue()) {
    return false;
  }

  if (!lhs.hasValue()) {
    return lhs.error() == rhs.error();
  }

  return *lhs == *rhs;
}

template <typename T1, typename E1, typename T2, typename E2> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    Expected<T1, E1> const& lhs, Expected<T2, E2> const& rhs
) noexcept -> bool {
  if (lhs.hasValue() != rhs.hasValue()) {
    return true;
  }

  if (!lhs.hasValue()) {
    return lhs.error() != rhs.error();
  }

  return *lhs != *rhs;
}

template <typename E1, typename E2> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    Expected<void, E1> const& lhs, Expected<void, E2> const& rhs
) noexcept -> bool {
  if (lhs.hasValue() != rhs.hasValue()) {
    return false;
  }

  if (!lhs.hasValue()) {
    return lhs.error() == rhs.error();
  }

  return true;
}

template <typename E1, typename E2> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    Expected<void, E1> const& lhs, Expected<void, E2> const& rhs
) noexcept -> bool {
  if (lhs.hasValue() != rhs.hasValue()) {
    return true;
  }

  if (!lhs.hasValue()) {
    return lhs.error() != rhs.error();
  }

  return false;
}

template <typename T1, typename E1, typename T2, EnableIf<Not<IsExpected<T2>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(Expected<T1, E1> const& lhs, T2 const& rhs) noexcept -> bool {
  return lhs.hasValue() && *lhs == rhs;
}

template <typename T1, typename E1, typename T2, EnableIf<Not<IsExpected<T2>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(Expected<T1, E1> const& lhs, T2 const& rhs) noexcept -> bool {
  return !lhs.hasValue() || *lhs != rhs;
}

template <typename T1, typename E2, typename T2, EnableIf<Not<IsExpected<T1>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(T1 const& lhs, Expected<T2, E2> const& rhs) noexcept -> bool {
  return rhs.hasValue() && lhs == *rhs;
}

template <typename T1, typename E2, typename T2, EnableIf<Not<IsExpected<T1>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(T1 const& lhs, Expected<T2, E2> const& rhs) noexcept -> bool {
  return !rhs.hasValue() || lhs != *rhs;
}

template <typename T1, typename E1, typename E2> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(Expected<T1, E1> const& lhs, Unexpected<E2> const& rhs) noexcept -> bool {
  return !lhs.hasValue() && lhs.error() == rhs.error();
}

template <typename T1, typename E1, typename E2> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(Expected<T1, E1> const& lhs, Unexpected<E2> const& rhs) noexcept -> bool {
  return lhs.hasValue() || lhs.error() != rhs.error();
}

template <typename E1, typename T2, typename E2> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(Unexpected<E1> const& lhs, Expected<T2, E2> const& rhs) noexcept -> bool {
  return !rhs.hasValue() && lhs.error() == rhs.error();
}

template <typename E1, typename T2, typename E2> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(Unexpected<E1> const& lhs, Expected<T2, E2> const& rhs) noexcept -> bool {
  return rhs.hasValue() || lhs.error() != rhs.error();
}
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_EXPECTED_HPP
