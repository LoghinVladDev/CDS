//
// Created by loghin on 7/8/25.
//

#ifndef CDS_DS_JSON_NODE_PRINTER_HPP
#define CDS_DS_JSON_NODE_PRINTER_HPP
#pragma once

#include "JsonPrinterDecl.hpp"

namespace cds {
namespace json {
namespace impl {
template <typename O, typename B, typename A> auto printJsonNode(
    JsonPrinterOutput<O>& output,
    JsonNodeBase<B, A> const& node,
    JsonPrinterContext& ctx
) noexcept -> void {
  if (node.isNull()) {
    output.forceWrite("null");
  } else if (node.isBool()) {
    output.forceWrite(node.getBool());
  } else if (node.isIntegral()) {
    output.forceWrite(node.getInt());
  } else if (node.isFloating()) {
    output.forceWrite(node.getDouble());
  } else if (node.isString()) {
    output.forceWriteEscaped(node.getString());
  } else if (node.isArray()) {
    printJsonArray(output, node.getArray(), ctx);
  } else {
    assert(node.isObject() && "undefined behavior");
    printJsonObject(output, node.getObject(), ctx);
  }
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_NODE_PRINTER_HPP
