//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_STRING_TOKEN_RANGE_HPP
#define CDS_FORMAT_FORMAT_STRING_TOKEN_RANGE_HPP
#pragma once

#include <cds/StringView>

#include "FormatStringIterator.hpp"

namespace cds {
namespace impl {
namespace fmt {
template <typename C, typename U> class FormatStringTokenRange {
  using SV = BaseStringView<C, U>;
  using I = FormatStringIterator<C, U>;
public:
  CDS_ATTR(2(explicit, constexpr(11))) FormatStringTokenRange(SV fmtStr) noexcept : _fmtStr{fmtStr} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const CDS_ATTR(noexcept(false)) -> I {
    return I{_fmtStr.begin(), _fmtStr.end()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    /* ignore = this; */
    return Sentinel{};
  }

private:
  SV _fmtStr;
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_STRING_TOKEN_RANGE_HPP
