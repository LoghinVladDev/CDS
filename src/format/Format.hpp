//
// Created by loghin on 31.03.2024.
//

#ifndef CDS_FORMAT_FORMAT_HPP
#define CDS_FORMAT_FORMAT_HPP
#pragma once

#include <cds/String>

#include "CallableFormatString.hpp"
#include "FormatContext.hpp"
#include "FormatParseContext.hpp"
#include "FormatParseInvoker.hpp"
#include "FormatString.hpp"
#include "FormatStringToken.hpp"
#include "FormatStringIterator.hpp"
#include "FormatStringTokenRange.hpp"
#include "Formatter.hpp"
#include "FormatterVisitor.hpp"
#include "FormatterVisitorTable.hpp"
#include "RangeFormatter.hpp"
#include "StandardFormattingSpecification.hpp"
#include "StandardFormattingSpecificationComponents.hpp"
#include "StandardFormatters.hpp"
#include "TupleLikeFormatter.hpp"

#include "HashMapFormatter.hpp"
#include "LinkedHashMapFormatter.hpp"
#include "JsonNodeFormatter.hpp"
#include "JsonArrayFormatter.hpp"
#include "JsonObjectFormatter.hpp"
#include "MapEntryFormatter.hpp"
#include "OptionalFormatter.hpp"
#include "SetProjectionFormat.hpp"
#include "TupleFormatter.hpp"
#include "VectorFormat.hpp"
#include "VectorViewFormat.hpp"

namespace cds {
namespace impl {
namespace fmt {
using meta::TypeId;

template <typename... Args> CDS_ATTR(2(nodiscard, constexpr(20))) auto format(
    FormatString<char, StringUtils<char, StringTraits<char>>, TypeId<Args>...> fmt, Args&&... args
) CDS_ATTR(noexcept(false)) -> String {
  String out;
  visitFormattersForFormat(out, fmt, forwardAsTuple(fwd<Args>(args)...));
  return out;
}

template <typename... Args> CDS_ATTR(2(nodiscard, constexpr(20))) auto vformat(
    DynamicFormatString<char, StringUtils<char, StringTraits<char>>, TypeId<Args>...> fmt, Args&&... args
) CDS_ATTR(noexcept(false)) -> String {
  String out;
  visitFormattersForFormat(out, fmt, forwardAsTuple(fwd<Args>(args)...));
  return out;
}

template <typename... Args> CDS_ATTR(2(nodiscard, constexpr(20))) auto formatTo(
    String& out, FormatString<char, StringUtils<char, StringTraits<char>>, TypeId<Args>...> fmt, Args&&... args
) CDS_ATTR(noexcept(false)) -> String& {
  visitFormattersForFormat(out, fmt, forwardAsTuple(fwd<Args>(args)...));
  return out;
}

template <typename... Args> CDS_ATTR(2(nodiscard, constexpr(20))) auto vformatTo(
    String& out, DynamicFormatString<char, StringUtils<char, StringTraits<char>>, TypeId<Args>...> fmt, Args&&... args
) CDS_ATTR(noexcept(false)) -> String& {
  visitFormattersForFormat(out, fmt, forwardAsTuple(fwd<Args>(args)...));
  return out;
}
} // namespace fmt
} // namespace impl

using impl::fmt::format;
using impl::fmt::formatTo;
using impl::fmt::vformat;
using impl::fmt::vformatTo;

inline namespace literals {
CDS_ATTR(2(nodiscard, consteval(20, constexpr(14))))
auto operator ""_f(char const *fmt, std::size_t const len) noexcept
    -> impl::fmt::CallableFormatString<char, impl::StringUtils<char, impl::StringTraits<char>>> {
  return {impl::BaseStringView<char>{fmt, len}};
}
} // inline namespace literals
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_HPP
