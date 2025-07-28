//
// Created by rosa on 7/28/25.
//

#ifndef CDS_META_CRTP_BASE_HPP
#define CDS_META_CRTP_BASE_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace meta {
namespace impl {
template <typename B> class CRTPBase {
protected:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto refl() const noexcept -> B const* {
    return static_cast<B const*>(this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto refl() noexcept -> B* {
    return static_cast<B*>(this);
  }
};
} // namespace impl
} // namespace meta
} // namespace cds

#endif // #ifndef CDS_META_CRTP_BASE_HPP
