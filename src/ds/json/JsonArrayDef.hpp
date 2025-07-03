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
using JsonArrayBaseImpl = Vector<JsonNodeBase<>>;

template <typename Base> struct JsonArrayBaseSelector : Base {
  using Base::Base;
  using Base::operator=;
};

template <> struct JsonArrayBaseSelector<Default> : JsonArrayBaseSelector<JsonArrayBaseImpl> {
  using JsonArrayBaseSelector<JsonArrayBaseImpl>::JsonArrayBaseSelector;
  using JsonArrayBaseSelector<JsonArrayBaseImpl>::operator=;
};

template <typename TBase> class JsonArrayBase : public JsonArrayBaseSelector<TBase> {
  using Base = JsonArrayBaseSelector<TBase>;

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
