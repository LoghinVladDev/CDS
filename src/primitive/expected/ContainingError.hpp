//
// Created by loghin on 7/28/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_CONTAINING_ERROR_HPP
#define CDS_PRIMITIVE_EXPECTED_CONTAINING_ERROR_HPP
#pragma once

#include <cds/meta/ObjectTraits>

#include "../../meta/CRTPBase.hpp"

namespace cds {
namespace impl {
using meta::And;
using meta::IsDestructible;
using meta::IsUnboundedArray;
using meta::Not;
using meta::impl::CRTPBase;

template <typename B, typename E> class ContainingError : private CRTPBase<B> {
  static_assert(And<
      IsDestructible<E>,
      Not<IsUnboundedArray<E>>
  >::value, "Invalid Unexpected error type");

  using CRTPBase<B>::refl;

public:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto error() const& noexcept -> E const& {
    return refl()->_error;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto error() const&& noexcept -> E const&& {
    return mv(refl()->_error);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto error()& noexcept -> E& {
    return refl()->_error;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto error()&& noexcept -> E&& {
    return mv(refl()->_error);
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_CONTAINING_ERROR_HPP
