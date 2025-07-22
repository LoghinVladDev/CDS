//
// Created by loghin on 7/8/25.
//

#ifndef CDS_DS_JSON_PRINTERS_DECL_HPP
#define CDS_DS_JSON_PRINTERS_DECL_HPP
#pragma once

#include "JsonArrayDecl.hpp"
#include "JsonNodeDecl.hpp"
#include "JsonObjectDecl.hpp"
#include "JsonPrinterContext.hpp"
#include "JsonPrinterIndenter.hpp"
#include "JsonPrinterOutput.hpp"
#include "JsonPrinterOutputString.hpp"

#include <cds/String>
#include <cds/StringView>
#include <cds/collection/Vector>
#include <cds/exception/RuntimeException>

namespace cds {
namespace json {
namespace impl {

/*
template <typename> class JsonPrinterOutput {
  auto setColumnLimit(U32) -> void;
  auto write(V&&) -> bool;
  auto forceWrite(V&&) -> void;
  auto forceWriteEscaped(StringView) -> void;
  auto indenter() -> Indenter;

  auto finishLine(V&&) -> JsonPrinterOutput&;
  auto onLine() -> U32;
};

template <typename> struct Indenter {
   ~Indenter();

   auto newLine();
   auto newLineIndent();
   auto newLineContinuation();
};
*/

struct JsonPrinterContext;

template <typename O, typename B, typename A> auto printJsonNode(
    JsonPrinterOutput<O>& output,
    JsonNodeBase<B, A> const& node,
    JsonPrinterContext& ctx
) noexcept -> void;

template <typename O, typename B> auto printJsonArray(
    JsonPrinterOutput<O>& output,
    JsonArrayBase<B> const& array,
    JsonPrinterContext& ctx
) noexcept -> void;

template <typename O, typename B> auto printJsonObject(
    JsonPrinterOutput<O>& output,
    JsonObjectBase<B> const& node,
    JsonPrinterContext& ctx
) noexcept -> void;

template <typename O, typename B, typename A> CDS_ATTR(constexpr(20)) auto JsonElementPresenter::operator()(
    JsonElementPresentationData const& data,
    JsonPrinterOutput<O>& output,
    JsonNodeBase<B, A> const& node,
    JsonPrinterContext& ctx
) noexcept -> void {
  auto actionsIt = data.actions.begin();
  auto actionsEnd = data.actions.end();
  auto constantsIt = data.constants.begin();

  for (; actionsIt != actionsEnd; ++actionsIt) {
    switch (*actionsIt) {
      case JsonElementPresenterAction::Constant: {
        assert(constantsIt != data.constants.end() && "undefined behavior");
        output.forceWrite(*constantsIt);
        ++constantsIt;
        break;
      }

      case JsonElementPresenterAction::Key: {
        assert(!keyStore.empty() && "undefined behavior");
        output.forceWrite(keyStore.back());
        break;
      }

      case JsonElementPresenterAction::Index: {
        assert(!indexStore.empty() && "undefined behavior");
        output.forceWrite(indexStore.back());
        break;
      }

      case JsonElementPresenterAction::Value: {
        printJsonNode(output, node, ctx);
        break;
      }
    }
  }
}

template <typename Output> class JsonPrinter;
} // namespace impl

using impl::JsonPrinter;
using impl::JsonPrinterOptions;
using impl::SpacingKind;
using impl::RearrangeKind;
using JsonStringPrinter = JsonPrinter<String>;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PRINTERS_DECL_HPP
