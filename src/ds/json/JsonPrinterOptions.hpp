//
// Created by loghin on 7/16/25.
//

#ifndef CDS_DS_JSON_PRINTER_OPTIONS_HPP
#define CDS_DS_JSON_PRINTER_OPTIONS_HPP
#pragma once

#include <cds/StringView>

namespace cds {
namespace json {
namespace impl {
enum class SpacingKind {None, Space, Newline};
enum class RearrangeKind {KeepInline, ChopDownIfLong, BreakDownIfLong, BreakDown};

struct JsonPrinterOptions {
  U32 indentWidth{2u};
  U32 continuationIndentWidth{4u};
  U32 columnLimit{120u};
  SpacingKind beforeLeftBrace{SpacingKind::None};
  SpacingKind afterLeftBrace{SpacingKind::Newline};
  SpacingKind beforeRightBrace{SpacingKind::None};
  SpacingKind afterRightBrace{SpacingKind::None};
  SpacingKind beforeLeftSquareBracket{SpacingKind::None};
  SpacingKind afterLeftSquareBracket{SpacingKind::Newline};
  SpacingKind beforeRightSquareBracket{SpacingKind::None};
  SpacingKind afterRightSquareBracket{SpacingKind::None};
  SpacingKind beforeSeparator{SpacingKind::None};
  SpacingKind afterSeparator{SpacingKind::Space};
  RearrangeKind objectBreakdown{RearrangeKind::BreakDown};
  RearrangeKind arrayBreakdown{RearrangeKind::BreakDown};
  char indent{' '};
  char spacing{' '};
  StringView elementSeparator{","};
  StringView newLine{"\n"};
  StringView arrayStartIndicator{"["};
  StringView arrayEndIndicator{"]"};
  StringView objectStartIndicator{"{"};
  StringView objectEndIndicator{"}"};
  /// Formula placeholder values:
  /// ${key} - key of the current entry / value
  ///        - if no key exists for current value (i.e. array, the array's key name will be used)
  ///          - e.g. {"obj": [1, 2, false]}, ${key} for root["obj"][1] is "obj".
  ///          - if no key exists for top level, indexing will be used
  ///          - e.g. [1, 2, false], ${key} for root[1] is "1"
  /// ${value} - current value, 1, 2, false in {"a": 1, "b": 2, "c": false}
  ///                           1, 2, false in [1, 2, false]
  /// ${index} - index of current element, works in objects as well as in arrays.
  StringView arrayElementPresentation{R"(${value})"};
  StringView objectEntryPresentation{R"("${key}": ${value})"};
  bool printNonAsciiAsUTFCodePoints{false};
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PRINTER_OPTIONS_HPP
