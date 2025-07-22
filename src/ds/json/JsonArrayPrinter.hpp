//
// Created by loghin on 7/8/25.
//

#ifndef CDS_DS_JSON_ARRAY_PRINTER_HPP
#define CDS_DS_JSON_ARRAY_PRINTER_HPP
#pragma once

#include "JsonPrinterDecl.hpp"

namespace cds {
namespace json {
namespace impl {
template <typename O, typename B> auto printJsonArray(
    JsonPrinterOutput<O>& output,
    JsonArrayBase<B> const& array,
    JsonPrinterContext& ctx
) noexcept -> void {
  using Node = typename JsonArrayBase<B>::Value;

  auto const& opt = ctx.options;
  auto const averageElementSize = 8u;
  auto const estArrayImpact = array.size() * averageElementSize;
  auto const shouldPreventivelyBreakDown =
      !output.fits(estArrayImpact)
      || array.any([](Node const& n) { return n.isArray() || n.isObject(); })
      || opt.beforeSeparator == SpacingKind::Newline
      || opt.afterSeparator == SpacingKind::Newline;
  auto const breaksDown = !array.empty() && (shouldPreventivelyBreakDown
      && opt.arrayBreakdown == RearrangeKind::BreakDownIfLong
      || opt.arrayBreakdown == RearrangeKind::BreakDown);

  auto indenter = output.indenter();
  if (opt.beforeLeftSquareBracket == SpacingKind::Newline
      || opt.beforeLeftSquareBracket == SpacingKind::Space && !output.fits(opt.spacing)) {
    indenter.newLineContinuation();
  } else if (opt.beforeLeftSquareBracket == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }

  auto outerIndenter = indenter.store();
  if (!output.write(opt.arrayStartIndicator)) {
    indenter.newLineContinuation();
    output.forceWrite(opt.arrayStartIndicator);
  }

  bool breakDownIndent = false;
  if (opt.arrayBreakdown != RearrangeKind::KeepInline
      && (breaksDown
          || opt.afterLeftSquareBracket == SpacingKind::Newline && !array.empty()
          || opt.afterLeftSquareBracket == SpacingKind::Space && !output.fits(opt.spacing))) {
    indenter.newLineIndent();
    breakDownIndent = true;
  } else if (opt.afterLeftSquareBracket == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }

  Size index = 0u;
  if (opt.arrayBreakdown == RearrangeKind::ChopDownIfLong
      && opt.beforeSeparator != SpacingKind::Newline
      && opt.afterSeparator != SpacingKind::Newline) {

    bool chopped = false;
    for (auto const& node : array) {
      String string;
      JsonPrinterOutput<String> stringPrinter{ctx, string};
      Size offset = 0u;

      if (index > 0u) {
        if (opt.beforeSeparator == SpacingKind::Space) {
          stringPrinter.forceWrite(opt.spacing);
          ++offset;
        }
        stringPrinter.forceWrite(opt.elementSeparator);
        offset += opt.elementSeparator.length();
        if (opt.afterSeparator == SpacingKind::Space) {
          stringPrinter.forceWrite(opt.spacing);
          ++offset;
        }
      }

      auto presenter = ctx.imbuePresenterFor(index);
      presenter(stringPrinter, node, ctx);

      if (!output.write(string)) {
        if (opt.beforeSeparator == SpacingKind::Space) {
          output.forceWrite(opt.spacing);
        }
        output.forceWrite(opt.elementSeparator);

        if (!chopped) {
          indenter.newLineContinuation();
          chopped = true;
        } else {
          indenter.newLinePreserveIndent();
        }

        output.forceWrite(string.sub(offset));
      }
      ++index;
    }
  } else {
    for (auto const& node : array) {
      if (index > 0) {
        if (opt.beforeSeparator == SpacingKind::Newline) {
          if (breakDownIndent) {
            indenter.newLinePreserveIndent();
          } else {
            indenter.newLineIndent();
            breakDownIndent = true;
          }
        } else if (opt.beforeSeparator == SpacingKind::Space) {
          output.forceWrite(opt.spacing);
        }

        output.forceWrite(opt.elementSeparator);

        if (breaksDown || opt.afterSeparator == SpacingKind::Newline
            || opt.afterSeparator == SpacingKind::Space && !output.fits(opt.spacing)) {
          if (breakDownIndent) {
            indenter.newLinePreserveIndent();
          } else {
            indenter.newLineIndent();
            breakDownIndent = true;
          }
        } else if (opt.afterSeparator == SpacingKind::Space) {
          output.forceWrite(opt.spacing);
        }
      }

      auto presenter = ctx.imbuePresenterFor(index);
      presenter(output, node, ctx);
      ++index;
    }
  }


  indenter.restore(outerIndenter);
  if (opt.arrayBreakdown != RearrangeKind::KeepInline
      && (breaksDown
          || opt.beforeRightSquareBracket == SpacingKind::Newline
          || opt.beforeRightSquareBracket == SpacingKind::Space && !output.fits(opt.spacing))) {
    indenter.newLinePreserveIndent();
  } else if (opt.beforeRightSquareBracket == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }

  if (!output.write(opt.arrayEndIndicator)) {
    indenter.newLinePreserveIndent();
    output.forceWrite(opt.arrayEndIndicator);
  }

  if (opt.afterRightSquareBracket == SpacingKind::Newline) {
    indenter.newLinePreserveIndent();
  } else if (opt.afterRightSquareBracket == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_ARRAY_PRINTER_HPP
