//
// Created by loghin on 7/16/25.
//

#ifndef CDS_DS_JSON_PRINTER_OUTPUT_HPP
#define CDS_DS_JSON_PRINTER_OUTPUT_HPP
#pragma once

#include <cds/StringView>

namespace cds {
namespace json {
namespace impl {
template <typename, typename = void> struct JsonPrinterOutput {
  /*
  auto setColumnLimit(U32) -> void;
  auto write(V&&) -> bool;
  auto forceWrite(V&&) -> void;
  auto forceWriteEscaped(StringView) -> void;
  auto indenter() -> Indenter;

  auto finishLine(V&&) -> JsonPrinterOutput&;
  */
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PRINTER_OUTPUT_HPP
