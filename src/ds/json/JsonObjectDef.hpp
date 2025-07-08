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

  JsonObjectBase() = default;
  JsonObjectBase(JsonObjectBase const&) = default;
  JsonObjectBase(JsonObjectBase&&) = default;
  auto operator=(JsonObjectBase const&) -> JsonObjectBase& = default;
  auto operator=(JsonObjectBase&&) -> JsonObjectBase& = default;

  CDS_ATTR(2(implicit, constexpr(20))) JsonObjectBase(StringView asString) CDS_ATTR(noexcept(false));

  template <Size n> CDS_ATTR(2(implicit, constexpr(20))) JsonObjectBase(char const(& asString)[n])
      CDS_ATTR(noexcept(false)) : JsonObjectBase(StringView{asString}) {}

  CDS_ATTR(2(implicit, constexpr(20))) JsonObjectBase(char const* asString)
      CDS_ATTR(noexcept(false)) : JsonObjectBase(StringView{asString}) {}

  CDS_ATTR(2(implicit, constexpr(20))) JsonObjectBase(String const& asString)
      CDS_ATTR(noexcept(false)) : JsonObjectBase(StringView{asString}) {}
};

template <typename C, typename B> CDS_ATTR(inline)
auto operator<<(std::basic_ostream<C>& out, JsonObjectBase<B> const& object) noexcept -> std::basic_ostream<C>& {
  out << static_cast<C>('{');
  auto it = object.begin();
  auto end = object.end();
  if (it == end) {
    out << static_cast<C>('}');
    return out;
  }

  escapeJsonString(out, it->key()) << static_cast<C>(':') << static_cast<C>(' ') << it->value();
  for (++it; it != end; ++it) {
    escapeJsonString(out << static_cast<C>(',') << static_cast<C>(' '), it->key())
        << static_cast<C>(':') << static_cast<C>(' ') << it->value();
  }
  out << static_cast<C>('}');
  return out;
}
} // namespace impl

using JsonObject = impl::JsonObjectBase<>;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_OBJECT_DEF_HPP
