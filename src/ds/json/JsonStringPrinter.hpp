//
// Created by loghin on 7/17/25.
//

#ifndef CDS_DS_JSON_STRING_PRINTER_HPP
#define CDS_DS_JSON_STRING_PRINTER_HPP
#pragma once

#include "JsonPrinterBase.hpp"

namespace cds {
namespace json {
namespace impl {
template <> class JsonPrinter<String> : public JsonPrinterBase<JsonPrinter<String>> {
public:
  JsonPrinter() = default;
  CDS_ATTR(constexpr(20)) JsonPrinter(JsonPrinterOptions const& options) noexcept :
      JsonPrinterBase<JsonPrinter<String>>{options} {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto printer(JsonPrinterContext& ctx) noexcept
      -> JsonPrinterOutput<String> {
    return {ctx, _output};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto out() const& noexcept -> String const& {
    return _output;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto out() const&& noexcept -> String const&& {
    return mv(_output);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto out()& noexcept -> String& {
    return _output;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto out()&& noexcept -> String&& {
    return mv(_output);
  }

private:
  String _output{};
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_STRING_PRINTER_HPP
