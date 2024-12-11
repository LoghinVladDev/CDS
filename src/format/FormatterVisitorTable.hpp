//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMATTER_VISITOR_TABLE_HPP
#define CDS_FORMAT_FORMATTER_VISITOR_TABLE_HPP
#pragma once

#include <cds/Tuple>
#include <cds/exception/FormatException>

#include "FormatterVisitor.hpp"
#include "FormatStringTokenRange.hpp"

namespace cds {
namespace impl {
namespace fmt {
using meta::Common;
using meta::Decay;
using meta::IndexSequence;
using meta::MakeIndexSequence;
using meta::visitors;

template <typename, typename, typename, typename...> struct FormatterVisitorTableImpl;

template <typename C, typename U, typename FormatString, typename... Args, unsigned... indices>
struct FormatterVisitorTableImpl<IndexSequence<indices...>, C, U, FormatString, Args...> {
  static constexpr Size size = sizeof...(indices);
  static constexpr Common<Decay<decltype(&FormatterVisitor<indices>
      ::template doParse<C, U, FormatString, Args&&...>)>...>
      parsers[size] = {&FormatterVisitor<indices>::template doParse<C, U, FormatString, Args&&...>...};
  static constexpr Common<Decay<decltype(&FormatterVisitor<indices>
      ::template doFormat<C, U, FormatString, Args&&...>)>...>
      formatters[size] = {&FormatterVisitor<indices>::template doFormat<C, U, FormatString, Args&&...>...};
};

// ODR before C++17
template <typename C, typename U, typename Fmt, typename... Args, unsigned... indices>
Size const FormatterVisitorTableImpl<IndexSequence<indices...>, C, U, Fmt, Args...>::size;

template <typename C, typename U, typename Fmt, typename... Args, unsigned... indices>
Common<Decay<decltype(&FormatterVisitor<indices>::template doParse<C, U, Fmt, Args&&...>)>...> const
    FormatterVisitorTableImpl<IndexSequence<indices...>, C, U, Fmt, Args...>
    ::parsers[FormatterVisitorTableImpl<IndexSequence<indices...>, C, U, Fmt, Args...>::size];

template <typename C, typename U, typename Fmt, typename... Args, unsigned... indices>
Common<Decay<decltype(&FormatterVisitor<indices>::template doFormat<C, U, Fmt, Args&&...>)>...> const
    FormatterVisitorTableImpl<IndexSequence<indices...>, C, U, Fmt, Args...>
    ::formatters[FormatterVisitorTableImpl<IndexSequence<indices...>, C, U, Fmt, Args...>::size];

template <typename, typename, typename, typename> struct FormatterVisitorTable;
template <typename C, typename U, typename Fmt, typename... Args>
struct FormatterVisitorTable<C, U, Fmt, Tuple<Args...>> :
    FormatterVisitorTableImpl<MakeIndexSequence<sizeof...(Args)>, C, U, Fmt, Args...> {
  using FormatterVisitorTableImpl<MakeIndexSequence<sizeof...(Args)>, C, U, Fmt, Args...>::size;
  using FormatterVisitorTableImpl<MakeIndexSequence<sizeof...(Args)>, C, U, Fmt, Args...>::parsers;
  using FormatterVisitorTableImpl<MakeIndexSequence<sizeof...(Args)>, C, U, Fmt, Args...>::formatters;
};

template <typename A, typename C, typename U, typename Fmt> CDS_ATTR(2(nodiscard, constexpr(14)))
auto visitFormattersForParse(BaseStringView<C, U> const& formatString, Fmt& formatStringObject)
    CDS_ATTR(noexcept(false)) -> bool {
  auto const range = FormatStringTokenRange<C, U>{formatString};
  auto it = range.begin();
  bool explicitUsed = false;
  for (auto end = range.end(); it != end; ++it) {
    it->visit(visitors(
        [](BaseStringView<C, U> const& plainText) {
          ignore = plainText;
        },
        [&formatStringObject](FormatStringToken<C, U> const& token) {
          using Table = FormatterVisitorTable<C, U, Fmt, A>;
          if (Table::size <= token.index()) {
            throw FormatException("Format index specification is out of range for the received arguments");
          }
          Table::parsers[token.index()](token.token(), formatStringObject);
        }
    ));
    if (it.usesExplicitArgumentIndexing()) {
      explicitUsed = true;
    }
  }
  return explicitUsed;
}

template <typename A, typename C, typename U, typename Fmt> CDS_ATTR(constexpr(14))
auto visitFormattersForFormat(BaseString<C, U>& out, Fmt& formatStringObject, A&& args)
    CDS_ATTR(noexcept(false)) -> void {
  for (auto const& token : FormatStringTokenRange<C, U>{formatStringObject.get()}) {
    token.visit(visitors(
        [&out](BaseStringView<C, U> const& plainText) {
          out += plainText;
        },
        [&out, &args, &formatStringObject](FormatStringToken<C, U> const& token) {
          FormatterVisitorTable<C, U, Fmt, RemoveCVRef<A>>
              ::formatters[token.index()](out, token.token(), fwd<A>(args), formatStringObject);
        }
    ));
  }
}
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMATTER_VISITOR_TABLE_HPP
