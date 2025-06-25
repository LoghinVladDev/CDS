//
// Created by loghin on 6/17/25.
//

#ifndef CDS_DS_JSON_ARRAY_HPP
#define CDS_DS_JSON_ARRAY_HPP

#include "JsonArrayDecl.hpp"
#include "JsonNodeDecl.hpp"

#include <cds/collection/Vector>

namespace cds {
namespace json {
namespace impl {
template <typename A> using JsonArrayBaseImpl = Vector<JsonNodeBase<A>>;

template <typename A> class JsonArrayBase : private JsonArrayBaseImpl<A> {
public:
  JsonArrayBase() = default;
  JsonArrayBase(JsonArrayBase const&) = default;
  JsonArrayBase(JsonArrayBase&&) = default;
  auto operator=(JsonArrayBase const&) -> JsonArrayBase& = default;
  auto operator=(JsonArrayBase&&) -> JsonArrayBase& = default;
  ~JsonArrayBase() = default;
};

template <typename A0, typename A1> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator==(JsonArrayBase<A0> const& lhs, JsonArrayBase<A1> const& rhs) noexcept -> bool {
  assert(false && "unimplemented");
  return true;
}

template <typename A0, typename A1> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator!=(JsonArrayBase<A0> const& lhs, JsonArrayBase<A1> const& rhs) noexcept -> bool {
  assert(false && "unimplemented");
  return true;
}
} // namespace impl

using JsonArray = impl::JsonArrayBase<>;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_ARRAY_HPP
