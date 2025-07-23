//
// Created by loghin on 7/17/25.
//

#ifndef CDS_DS_JSON_STREAM_PRINTER_HPP
#define CDS_DS_JSON_STREAM_PRINTER_HPP
#pragma once

#include "JsonPrinterBase.hpp"
#include "../../stdlib/ostream.hpp"

namespace cds {
namespace json {
namespace impl {
using meta::EnableIf;
using meta::IsBaseOf;

template <typename StreamType> class JsonPrinter<StreamType, EnableIf<IsBaseOf<std::ostream, StreamType>, void>> :
    public JsonPrinterBase<JsonPrinter<std::ostream, void>> {
public:
  JsonPrinter() = delete;
  CDS_ATTR(constexpr(20)) JsonPrinter(std::ostream& out, JsonPrinterOptions const& options = {}) noexcept :
      JsonPrinterBase<JsonPrinter<std::ostream, void>>{options}, _output{out} {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto printer(JsonPrinterContext& ctx) noexcept
      -> JsonPrinterOutput<StreamType> {
    return {ctx, _output};
  }

private:
  std::ostream& _output;
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_STREAM_PRINTER_HPP
