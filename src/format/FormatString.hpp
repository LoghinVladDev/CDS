//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_STRING_HPP
#define CDS_FORMAT_FORMAT_STRING_HPP
#pragma once

#include <cds/StringView>
#include <cds/Tuple>

#include "Formatter.hpp"
#include "FormatterVisitorTable.hpp"

namespace cds {
namespace impl {
namespace fmt {
using meta::inConstexpr;

template <typename C, typename U, typename... Args> class FormatString {
public:
  using View = BaseStringView<C, U>;
  using FormatterTuple = Tuple<Formatter<RemoveCVRef<Args>>...>;

  template <typename Str> CDS_ATTR(2(implicit, consteval(20, constexpr(14)))) FormatString(Str const& fmtStr)
      CDS_ATTR(noexcept(false)) : _fmtStr{fmtStr} {
    if (inConstexpr()) {
      _explicitArgumentsUsed = visitFormattersForParse<Tuple<Args&&...>>(_fmtStr, *this);
      _compileTimeValidated = true;
    }
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const noexcept -> View const& {
    return _fmtStr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto constantlyEvaluated() const noexcept -> bool {
    return _compileTimeValidated;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto usesExplicitArgumentIndexing() const noexcept -> bool {
    return _explicitArgumentsUsed;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto formatters() const noexcept -> FormatterTuple const& {
    return _formatters;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto formatters() noexcept -> FormatterTuple& {
    return _formatters;
  }

private:
  View _fmtStr;
  FormatterTuple _formatters;
  bool _compileTimeValidated{false};
  bool _explicitArgumentsUsed{false};
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_STRING_HPP
