//
// Created by loghin on 7/16/25.
//

#ifndef CDS_DS_JSON_PRINTER_INDENTER_HPP
#define CDS_DS_JSON_PRINTER_INDENTER_HPP
#pragma once

namespace cds {
namespace json {
namespace impl {
struct JsonPrinterContext;

inline auto addIndent(JsonPrinterContext& ctx) noexcept -> void {
  auto const& opt = ctx.options;
  auto const oldLen = ctx.currentIndentBuffer.length();
  ctx.currentIndentBuffer.resize(oldLen + opt.indentWidth, '\0');
  cds::impl::fillN(ctx.currentIndentBuffer.data() + oldLen, opt.indentWidth, opt.indent);
}

inline auto addContinuationIndent(JsonPrinterContext& ctx) noexcept -> void {
  auto const& opt = ctx.options;
  auto const oldLen = ctx.currentIndentBuffer.length();
  ctx.currentIndentBuffer.resize(oldLen + opt.continuationIndentWidth, '\0');
  cds::impl::fillN(ctx.currentIndentBuffer.data() + oldLen, opt.continuationIndentWidth, opt.indent);
}

inline auto removeIndent(JsonPrinterContext& ctx) noexcept -> void {
  assert(ctx.currentIndentBuffer.length() >= ctx.options.indentWidth);
  ctx.currentIndentBuffer.resize(ctx.currentIndentBuffer.length() - ctx.options.indentWidth);
}

inline auto removeContinuationIndent(JsonPrinterContext& ctx) noexcept -> void {
  assert(ctx.currentIndentBuffer.length() >= ctx.options.continuationIndentWidth);
  ctx.currentIndentBuffer.resize(ctx.currentIndentBuffer.length() - ctx.options.continuationIndentWidth);
}

struct JsonPrinterIndenterState {
  CDS_ATTR(constexpr(11)) JsonPrinterIndenterState(U32 const indent, U32 const cont) noexcept :
      indentCount{indent}, contIndentCount{cont} {}

  U32 indentCount{0u};
  U32 contIndentCount{0u};
};

template <typename Printer> struct JsonPrinterIndenter {
  CDS_ATTR(2(explicit, constexpr(20))) JsonPrinterIndenter(Printer& printer) noexcept : printer{printer} {}
  ~JsonPrinterIndenter() noexcept {
    while (state.indentCount != 0u) {
      --state.indentCount;
      removeIndent(printer.ctx);
    }
    while (state.contIndentCount != 0u) {
      --state.contIndentCount;
      removeContinuationIndent(printer.ctx);
    }
  }

  CDS_ATTR(constexpr(20)) auto newLine() noexcept -> void {
    printer.finishLine(printer.ctx.options.newLine);
  }

  CDS_ATTR(constexpr(20)) auto indent() noexcept -> void {
    printer.forceWrite(printer.ctx.currentIndentBuffer);
  }

  CDS_ATTR(constexpr(20)) auto newLinePreserveIndent() noexcept -> void {
    newLine();
    indent();
  }

  CDS_ATTR(constexpr(20)) auto newLineIndent() noexcept -> void {
    newLine();
    addIndent(printer.ctx);
    ++state.indentCount;
    indent();
  }

  CDS_ATTR(constexpr(20)) auto newLineContinuation() noexcept -> void {
    newLine();
    addContinuationIndent(printer.ctx);
    ++state.contIndentCount;
    indent();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto store() const noexcept -> JsonPrinterIndenterState {
    return state;
  }

  CDS_ATTR(constexpr(14)) auto restore(JsonPrinterIndenterState from) noexcept -> void {
    while (state.indentCount > from.indentCount) {
      --state.indentCount;
      removeIndent(printer.ctx);
    }
    while (state.contIndentCount > from.contIndentCount) {
      --state.contIndentCount;
      removeContinuationIndent(printer.ctx);
    }
    while (state.indentCount < from.indentCount) {
      ++state.indentCount;
      addIndent(printer.ctx);
    }
    while (state.contIndentCount < from.contIndentCount) {
      ++state.contIndentCount;
      addContinuationIndent(printer.ctx);
    }
  }

  Printer& printer{nullptr};
  JsonPrinterIndenterState state{0u, 0u};
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PRINTER_INDENTER_HPP
