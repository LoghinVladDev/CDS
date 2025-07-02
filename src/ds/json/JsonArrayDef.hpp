//
// Created by loghin on 6/17/25.
//

#ifndef CDS_DS_JSON_ARRAY_DEF_HPP
#define CDS_DS_JSON_ARRAY_DEF_HPP

#include "JsonArrayDecl.hpp"
#include "JsonNodeDef.hpp"

#include <cds/collection/Vector>

namespace cds {
namespace json {
namespace impl {
using meta::DefaultOr;

using JsonArrayBaseImpl = Vector<JsonNodeBase<>>;

template <typename TBase> class JsonArrayBase : public DefaultOr<TBase, JsonArrayBaseImpl> {
  using Base = DefaultOr<TBase, JsonArrayBaseImpl>;

public:
  using Base::Base;
  using Base::operator=;
  ~JsonArrayBase() = default;
};
} // namespace impl

using JsonArray = impl::JsonArrayBase<>;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_ARRAY_DEF_HPP
