//
// Created by loghin on 7/16/25.
//

#ifndef CDS_DS_JSON_PRINTER_CONTEXT_HPP
#define CDS_DS_JSON_PRINTER_CONTEXT_HPP
#pragma once

#include "JsonElementPresenter.hpp"

namespace cds {
namespace json {
namespace impl {
struct JsonArrayPresenterRef {
  JsonElementPresenter& presenter;

  template <typename... A> CDS_ATTR(constexpr(20)) auto operator()(A&&... args) noexcept -> void {
    presenter(presenter.arrayPresentation, fwd<A>(args)...);
  }

  ~JsonArrayPresenterRef() noexcept {
    presenter.popIndex();
  }
};

struct JsonObjectPresenterRef {
  JsonElementPresenter& presenter;

  template <typename... A> CDS_ATTR(constexpr(20)) auto operator()(A&&... args) noexcept -> void {
    presenter(presenter.objectPresentation, fwd<A>(args)...);
  }

  ~JsonObjectPresenterRef() noexcept {
    presenter.popKey();
  }
};

struct JsonPrinterContext {
  JsonPrinterContext() = default;
  CDS_ATTR(2(explicit, constexpr(20))) JsonPrinterContext(JsonPrinterOptions const& opt) noexcept : options{opt} {}

  String currentIndentBuffer{};
  JsonPrinterOptions const& options{};
  JsonElementPresenter presenter{options};

  auto imbuePresenterFor(Size index) -> JsonArrayPresenterRef {
    return {presenter.imbue(index)};
  }

  auto imbuePresenterFor(StringView key) -> JsonObjectPresenterRef {
    return {presenter.imbue(key)};
  }
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PRINTER_CONTEXT_HPP
