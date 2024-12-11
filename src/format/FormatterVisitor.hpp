//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMATTER_VISITOR_HPP
#define CDS_FORMAT_FORMATTER_VISITOR_HPP
#pragma once

#include <cds/String>
#include <cds/StringView>
#include <cds/Tuple>

#include "Formatter.hpp"
#include "FormatContext.hpp"
#include "FormatParseContext.hpp"
#include "FormatParseInvoker.hpp"

namespace cds {
namespace impl {
namespace fmt {
using meta::RemoveCVRef;
using meta::value;

template <Size idx> struct FormatterVisitor {
  template <typename C, typename U, typename FormatString, typename... Args> static auto doFormat(
      BaseString<C, U>& out, BaseStringView<C, U> const& in, Tuple<Args&&...> const& args, FormatString& fmtStr
  ) CDS_ATTR(noexcept(false)) -> void {
    using ParseCtx = FormatParseContext<C, U>;
    using ArgT = RemoveCVRef<decltype(get<idx>(args))>;
    auto& formatter = get<idx>(fmtStr.formatters());

    ParseCtx parseContext{in};
    if (!fmtStr.constantlyEvaluated() || fmtStr.usesExplicitArgumentIndexing()) {
      auto parseIt = FormatParseInvoker<Formatter<ArgT, C>, ParseCtx>::parse(formatter, parseContext);
      if (parseIt != in.end()) {
        throw FormatException("Format specification was not completely parsed");
      }
    }

    FormatContext<C, U> context{out};
    ignore = formatter.format(get<idx>(args), context);
  }

  template <typename C, typename U, typename FormatString, typename... Args> CDS_ATTR(constexpr(14))
  static auto doParse(BaseStringView<C, U> const& in, FormatString& fmtStr) CDS_ATTR(noexcept(false)) -> void {
    using ParseCtx = FormatParseContext<C, U>;
    using ArgT = RemoveCVRef<decltype(get<idx>(value<Tuple<Args&&...>>()))>;
    auto& formatter = get<idx>(fmtStr.formatters());

    ParseCtx parseContext{in};
    auto parseIt = FormatParseInvoker<Formatter<ArgT, C>, ParseCtx>::parse(formatter, parseContext);
    if (parseIt != in.end()) {
      throw FormatException("Format specification was not completely parsed");
    }
  }
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMATTER_VISITOR_HPP
