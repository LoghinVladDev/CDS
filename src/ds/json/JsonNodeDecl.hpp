//
// Created by loghin on 6/16/25.
//

#ifndef CDS_DS_JSON_NODE_DECL_HPP
#define CDS_DS_JSON_NODE_DECL_HPP
#pragma once

#include <cds/meta/Tags>
#include <cds/String>
#include "../../stdlib/ostream.hpp"

namespace cds {
namespace json {
namespace impl {
using meta::Default;
using meta::Null;

using JsonString = String;
using JsonBool = bool;
using JsonNull = Null;
using JsonNumberIntegral = S64;
using JsonNumberFloating = double;

template <typename TBase = Default, typename TAlloc = Default> class JsonNodeBase;

template <typename C> auto escapeJsonString(std::basic_ostream<C>& out, JsonString const& string) noexcept
    -> std::basic_ostream<C>& {
  out << static_cast<C>('"');
  for (auto c : string) {
    auto escaped = true;
    if (c == '\t') {
      c = 't';
    } else if (c == '\n') {
      c = 'n';
    } else if (c == '\r') {
      c = 'r';
    } else if (c == '\f') {
      c = 'f';
    } else if (c == '"' || c == '\\') {
      // nothing
    } else {
      escaped = false;
    }

    if (escaped) {
      out << '\\';
    }
    out << c;
  }
  return out << '"';
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_NODE_DECL_HPP
