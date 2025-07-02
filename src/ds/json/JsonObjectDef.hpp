//
// Created by loghin on 6/17/25.
//

#ifndef CDS_DS_JSON_OBJECT_DEF_HPP
#define CDS_DS_JSON_OBJECT_DEF_HPP

#include "JsonNodeDef.hpp"
#include "JsonObjectDecl.hpp"

#include <cds/String>
#include <cds/collection/LinkedHashMap>

namespace cds {
namespace json {
namespace impl {
using meta::DefaultOr;

using JsonObjectBaseImpl = LinkedHashMap<String, JsonNodeBase<>>;

template <typename TBase> class JsonObjectBase : public DefaultOr<TBase, JsonObjectBaseImpl> {
  using Base = DefaultOr<TBase, JsonObjectBaseImpl>;

public:
  using Base::Base;
  using Base::operator=;
  ~JsonObjectBase() = default;
};
} // namespace impl

using JsonObject = impl::JsonObjectBase<>;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_OBJECT_DEF_HPP
