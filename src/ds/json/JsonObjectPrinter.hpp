//
// Created by loghin on 7/8/25.
//

#ifndef CDS_DS_JSON_OBJECT_PRINTER_HPP
#define CDS_DS_JSON_OBJECT_PRINTER_HPP
#pragma once

#include "../map/MapEntry.hpp"
#include "JsonPrinterDecl.hpp"

namespace cds {
namespace json {
namespace impl {
using cds::impl::MapEntry;

template <typename O, typename B> auto printJsonObject(
    JsonPrinterOutput<O>& output,
    JsonObjectBase<B> const& object,
    JsonPrinterContext& ctx
) noexcept -> void {
  using Node = typename JsonObjectBase<B>::Value;

  auto const& opt = ctx.options;
  auto const averageElementSize = 16u;
  auto const estObjectImpact = object.size() * averageElementSize;
  auto const shouldPreventivelyBreakDown =
      !output.fits(estObjectImpact)
      || object.any([](MapEntry<String, Node> const& e) { return e.value().isArray() || e.value().isObject(); })
      || opt.beforeSeparator == SpacingKind::Newline
      || opt.afterSeparator == SpacingKind::Newline;
  auto const breaksDown = !object.empty() && (shouldPreventivelyBreakDown
      && opt.objectBreakdown == RearrangeKind::BreakDownIfLong
      || opt.objectBreakdown == RearrangeKind::BreakDown);

  auto indenter = output.indenter();
  if (opt.beforeLeftBrace == SpacingKind::Newline
      || opt.beforeLeftBrace == SpacingKind::Space && !output.fits(opt.spacing)) {
    indenter.newLineContinuation();
  } else if (opt.beforeLeftBrace == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }

  auto outerIndenter = indenter.store();
  if (!output.write(opt.objectStartIndicator)) {
    indenter.newLineContinuation();
    output.forceWrite(opt.objectStartIndicator);
  }

  bool breakDownIndent = false;
  if (opt.objectBreakdown != RearrangeKind::KeepInline
      && (breaksDown
          || opt.afterLeftBrace == SpacingKind::Newline && !object.empty()
          || opt.afterLeftBrace == SpacingKind::Space && !output.fits(opt.spacing))) {
    indenter.newLineIndent();
    breakDownIndent = true;
  } else if (opt.afterLeftBrace == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }

  Size index = 0u;
  if (opt.objectBreakdown == RearrangeKind::ChopDownIfLong
      && opt.beforeSeparator != SpacingKind::Newline
      && opt.afterSeparator != SpacingKind::Newline) {

    bool chopped = false;
    for (auto const& entry : object) {
      String string;
      JsonPrinterOutput<String> stringPrinter {ctx, string};
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

      auto presenter = ctx.imbuePresenterFor(entry.key());
      presenter(stringPrinter, entry.value(), ctx);

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
    for (auto const& entry : object) {
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

      auto presenter = ctx.imbuePresenterFor(entry.key());
      presenter(output, entry.value(), ctx);
      ++index;
    }
  }

  indenter.restore(outerIndenter);
  if (opt.objectBreakdown != RearrangeKind::KeepInline
      && (breaksDown
          || opt.beforeRightBrace == SpacingKind::Newline
          || opt.beforeRightBrace == SpacingKind::Space && !output.fits(opt.spacing))) {
    indenter.newLinePreserveIndent();
  } else if (opt.beforeRightBrace == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }

  if (!output.write(opt.objectEndIndicator)) {
    indenter.newLinePreserveIndent();
    output.forceWrite(opt.objectEndIndicator);
  }

  if (opt.afterRightBrace == SpacingKind::Newline) {
    indenter.newLinePreserveIndent();
  } else if (opt.afterRightBrace == SpacingKind::Space) {
    output.forceWrite(opt.spacing);
  }
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_OBJECT_PRINTER_HPP
