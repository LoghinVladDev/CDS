//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_STRING_TOKEN_HPP
#define CDS_FORMAT_FORMAT_STRING_TOKEN_HPP
#pragma once

#include <cds/StringView>

namespace cds {
namespace impl {
namespace fmt {
template <typename C, typename U> class FormatStringToken {
  using SV = BaseStringView<C, U>;

public:
  CDS_ATTR(constexpr(11)) FormatStringToken(SV tok, Size const idx) noexcept : _tok{tok}, _idx{idx} {}
  ~FormatStringToken() noexcept = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto token() const noexcept -> SV const& {
    return _tok;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto index() const noexcept -> Size {
    return _idx;
  }

private:
  BaseStringView<C, U> _tok;
  Size _idx;
};

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    FormatStringToken<C, U> const& lhs, FormatStringToken<C, U> const& rhs
) noexcept -> bool {
  return lhs.index() == rhs.index() && lhs.token() == rhs.token();
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    FormatStringToken<C, U> const& lhs, FormatStringToken<C, U> const& rhs
) noexcept -> bool {
  return lhs.index() != rhs.index() || lhs.token() != rhs.token();
}
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_STRING_TOKEN_HPP
