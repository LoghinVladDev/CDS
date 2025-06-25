//
// Created by loghin on 6/16/25.
//

#ifndef CDS_DS_JSON_NODE_DECL_HPP
#define CDS_DS_JSON_NODE_DECL_HPP
#pragma once

#include <cds/meta/Tags>

namespace cds {
namespace json {
namespace impl {
using meta::Default;

template <typename TBase = Default, typename TAlloc = Default> class JsonNodeBase;
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_NODE_DECL_HPP
