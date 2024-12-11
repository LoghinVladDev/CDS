//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_PARSE_CONTEXT_HPP
#define CDS_FORMAT_FORMAT_PARSE_CONTEXT_HPP
#pragma once

#include <cds/StringView>

namespace cds {
namespace impl {
namespace fmt {
template <typename C, typename U> class FormatParseContext {
  using SV = BaseStringView<C, U>;
public:
  using Iterator = typename SV::Iterator;

  CDS_ATTR(2(explicit, constexpr(11))) FormatParseContext(SV const& fmtStr) noexcept : _fmtStr{fmtStr} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> Iterator {
    return _fmtStr.begin();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Iterator {
    return _fmtStr.end();
  }

private:
  SV const& _fmtStr;
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_PARSE_CONTEXT_HPP
