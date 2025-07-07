//
// Created by loghin on 6/16/25.
//

#ifndef CDS_DS_JSON_NODE_DECL_HPP
#define CDS_DS_JSON_NODE_DECL_HPP
#pragma once

#include <cds/meta/Tags>
#include <cds/String>

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
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_NODE_DECL_HPP
