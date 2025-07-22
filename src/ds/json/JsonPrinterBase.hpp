//
// Created by loghin on 7/17/25.
//

#ifndef CDS_DS_JSON_PRINTER_BASE_HPP
#define CDS_DS_JSON_PRINTER_BASE_HPP
#pragma once

#include "JsonPrinterDecl.hpp"

namespace cds {
namespace json {
namespace impl {
template <typename Derived> class JsonPrinterBase {
public:
  JsonPrinterBase() = default;
  CDS_ATTR(2(explicit, constexpr(11))) JsonPrinterBase(JsonPrinterOptions const& opt) noexcept : _opt{opt} {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto options() noexcept -> JsonPrinterOptions& {
    return _opt;
  }

  template <typename B> CDS_ATTR(constexpr(20)) auto write(JsonArrayBase<B> const& array) noexcept -> Derived& {
    JsonPrinterContext ctx{options()};
    auto printer = refl()->printer(ctx);
    printJsonArray(printer, array, ctx);
    return *refl();
  }

  template <typename B> CDS_ATTR(constexpr(20)) auto write(JsonObjectBase<B> const& object) noexcept -> Derived& {
    JsonPrinterContext ctx{options()};
    auto printer = refl()->printer(ctx);
    printJsonObject(printer, object, ctx);
    return *refl();
  }

private:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto refl() const noexcept -> Derived const* {
    return static_cast<Derived const*>(this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto refl() noexcept -> Derived* {
    return static_cast<Derived*>(this);
  }

  JsonPrinterOptions _opt{};
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PRINTER_BASE_HPP
