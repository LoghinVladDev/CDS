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
using JsonObjectBaseImpl = LinkedHashMap<String, JsonNodeBase<>>;

template <typename Base> struct JsonObjectBaseSelector : Base {
  using Base::Base;
  using Base::operator=;
};

template <> struct JsonObjectBaseSelector<Default> : JsonObjectBaseSelector<JsonObjectBaseImpl> {
  using JsonObjectBaseSelector<JsonObjectBaseImpl>::JsonObjectBaseSelector;
  using JsonObjectBaseSelector<JsonObjectBaseImpl>::operator=;
};

template <typename TBase> class JsonObjectBase : public JsonObjectBaseSelector<TBase> {
  using Base = JsonObjectBaseSelector<TBase>;

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
