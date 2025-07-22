//
// Created by loghin on 7/16/25.
//

#ifndef CDS_DS_JSON_ELEMENT_PRESENTER_HPP
#define CDS_DS_JSON_ELEMENT_PRESENTER_HPP
#pragma once

#include "JsonPrinterOptions.hpp"
#include "JsonPrinterOutput.hpp"

#include <cds/exception/RuntimeException>

namespace cds {
namespace json {
namespace impl {
struct JsonPrinterContext;

class JsonPresentationFormulaException : public RuntimeException {
public:
  CDS_ATTR(explicit) JsonPresentationFormulaException(StringView formula) noexcept :
      RuntimeException{String{"Invalid formula: '"} + formula + "'"} {}
};

enum class JsonElementPresenterAction {
  Constant, Key, Index, Value,
};

CDS_ATTR(constexpr(14)) auto actionFor(StringView formula) CDS_ATTR(noexcept(false)) -> JsonElementPresenterAction {
  if (formula == "key") {
    return JsonElementPresenterAction::Key;
  }

  if (formula == "value") {
    return JsonElementPresenterAction::Value;
  }

  if (formula == "index") {
    return JsonElementPresenterAction::Index;
  }

  throw JsonPresentationFormulaException(formula);
}

struct JsonElementPresentationData {
  Vector<JsonElementPresenterAction> actions;
  Vector<StringView> constants;

  JsonElementPresentationData() = delete;

  CDS_ATTR(2(explicit, constexpr(20))) JsonElementPresentationData(StringView formula) CDS_ATTR(noexcept(false)) {
    actions.reserve(4);
    constants.reserve(2);

    auto inFormula = false;
    Size constantStart = 0u;
    for (Size idx = 0u, formulaStart = 0u; idx < formula.size(); ++idx) {
      if (!inFormula && formula[idx] == '$' && idx + 1 < formula.size() && formula[idx + 1] == '{') {
        if (constantStart < idx) {
          actions.emplaceBack(JsonElementPresenterAction::Constant);
          constants.pushBack(formula.sub(constantStart, idx));
        }
        formulaStart = idx + 2;
        inFormula = true;
      } else if (inFormula && formula[idx] == '}') {
        constantStart = idx + 1;
        inFormula = false;

        auto const extract = formula.sub(formulaStart, idx);
        actions.emplaceBack(actionFor(extract));
      }
    }

    if (!inFormula && constantStart < formula.size()) {
      actions.emplaceBack(JsonElementPresenterAction::Constant);
      constants.pushBack(formula.sub(constantStart));
    }
  }
};

struct JsonElementPresenter {
  JsonElementPresentationData arrayPresentation;
  JsonElementPresentationData objectPresentation;

  Vector<String> indexStore{};
  Vector<StringView> keyStore{};

  JsonElementPresenter() = delete;

  CDS_ATTR(2(implicit, constexpr(20))) JsonElementPresenter(JsonPrinterOptions const& options)
      CDS_ATTR(noexcept(false)) :
      arrayPresentation{options.arrayElementPresentation},
      objectPresentation{options.objectEntryPresentation} {}

  CDS_ATTR(constexpr(14)) auto imbue(Size const i) noexcept -> JsonElementPresenter& {
    indexStore.emplaceBack(i);
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto imbue(StringView k) noexcept -> JsonElementPresenter& {
    keyStore.pushBack(k);
    return *this;
  }

  template <typename O, typename B, typename A> CDS_ATTR(constexpr(20)) auto operator()(
      JsonElementPresentationData const& data,
      JsonPrinterOutput<O>& output,
      JsonNodeBase<B, A> const& node,
      JsonPrinterContext& ctx
  ) noexcept -> void;

  CDS_ATTR(constexpr(20)) auto popIndex() noexcept -> void {
    assert(!indexStore.empty() && "undefined behavior");
    indexStore.popBack();
  }

  CDS_ATTR(constexpr(20)) auto popKey() noexcept -> void {
    assert(!keyStore.empty() && "undefined behavior");
    keyStore.popBack();
  }
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_ELEMENT_PRESENTER_HPP
