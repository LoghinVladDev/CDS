//
// Created by loghin on 6/17/25.
//

#ifndef CDS_DS_JSON_OBJECT_HPP
#define CDS_DS_JSON_OBJECT_HPP

namespace cds {
namespace json {
namespace impl {
template <typename A> class JsonObjectBase {};

template <typename A0, typename A1> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator==(JsonObjectBase<A0> const& lhs, JsonObjectBase<A1> const& rhs) noexcept -> bool {
  assert(false && "unimplemented");
  return true;
}

template <typename A0, typename A1> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator!=(JsonObjectBase<A0> const& lhs, JsonObjectBase<A1> const& rhs) noexcept -> bool {
  assert(false && "unimplemented");
  return true;
}
} // namespace impl

using JsonObject = impl::JsonObjectBase<>;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_OBJECT_HPP
