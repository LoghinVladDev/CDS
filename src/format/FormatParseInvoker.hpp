//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_PARSE_INVOKER_HPP
#define CDS_FORMAT_FORMAT_PARSE_INVOKER_HPP
#pragma once

#include <cds/Utility>
#include <cds/exception/FormatException>

namespace cds {
namespace impl {
namespace fmt {
template <typename Fmt, typename Ctx, typename = void> struct FormatParseInvoker {
  CDS_ATTR(2(nodiscard, constexpr(14))) static auto parse(Fmt& formatter, Ctx& ctx) -> typename Ctx::Iterator {
    ignore = formatter;
    auto it = ctx.begin();
    if (it == ctx.end()) {
      return it;
    }

    throw FormatException("Formatter without 'parse' function should take no format specification ('{:...}')");
  }
};

template <typename Fmt, typename Ctx> struct FormatParseInvoker<Fmt, Ctx, Void<decltype(&Fmt::template parse<Ctx>)>> {
  CDS_ATTR(2(nodiscard, constexpr(14))) static auto parse(Fmt& formatter, Ctx& ctx) -> typename Ctx::Iterator {
    return formatter.parse(ctx);
  }
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_PARSE_INVOKER_HPP
