//
// Created by loghin on 7/2/25.
//

#ifndef CDS_DS_JSON_NODE_IMPL_HPP
#define CDS_DS_JSON_NODE_IMPL_HPP
#pragma once

#include "JsonNodeDef.hpp"
#include "JsonArrayDef.hpp"
#include "JsonObjectDef.hpp"

namespace cds {
namespace json {
namespace impl {
template <typename B, typename A> CDS_ATTR(constexpr(11))
auto JsonNodeBase<B, A>::isArray() const noexcept -> bool {
  return Base::template is<JsonArray*>();
}

template <typename B, typename A> CDS_ATTR(constexpr(11))
auto JsonNodeBase<B, A>::isObject() const noexcept -> bool {
  return Base::template is<JsonObject*>();
}

template <typename B, typename A> CDS_ATTR(constexpr(20))
JsonNodeBase<B, A>::JsonNodeBase(JsonNodeBase const& node) noexcept : Base{} {
  if (node.isPrimitive()) {
    Base::operator=(static_cast<Base const&>(node));
    return;
  }

  if (node.isString()) {
    Base::operator=(construct(Alloc::template get<JsonString>().allocate(1), node.getString()));
  } else if (node.isArray()) {
    Base::operator=(construct(Alloc::template get<JsonArray>().allocate(1), node.getArray()));
  } else {
    assert(node.isObject() && "undefined behavior");
    Base::operator=(construct(Alloc::template get<JsonObject>().allocate(1), node.getObject()));
  }
}

template <typename B, typename A>
template <typename T, EnableIf<AdaptsAsAllocated<T>>> CDS_ATTR(constexpr(20))
JsonNodeBase<B, A>::JsonNodeBase(T&& value) noexcept :
    Base{construct(Alloc::template get<typename JsonNodeAdapt<T>::AdaptedAs>().allocate(1), fwd<T>(value))} {}

template <typename B, typename A> CDS_ATTR(constexpr(20))
JsonNodeBase<B, A>::JsonNodeBase(std::initializer_list<JsonNodeBase> const& list) noexcept : Base{} {
  auto const isThisAnObject = cds::impl::all(list.begin(), list.end(), [](JsonNodeBase const& node) {
    return node.isArray() && node.getArray().size() == 2 && node.getArray()[0].isString();
  });

  if (!isThisAnObject) {
    Base::operator=(construct(Alloc::template get<JsonArray>().allocate(1), list));
    return;
  }

  Base::operator=(construct(Alloc::template get<JsonObject>().allocate(1)));
  auto& object = getObject();
  for (auto const& entry : list) {
    auto const& key = entry.getArray()[0].getString();
    auto const& value = entry.getArray()[1];
    object.emplace(key, value);
  }
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
auto JsonNodeBase<B, A>::getArray() const CDS_ATTR(noexcept(false)) -> JsonArray const& {
  return *Base::template get<JsonArray*>();
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14)))
auto JsonNodeBase<B, A>::getArray() CDS_ATTR(noexcept(false)) -> JsonArray& {
  return *Base::template get<JsonArray*>();
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
auto JsonNodeBase<B, A>::getObject() const CDS_ATTR(noexcept(false)) -> JsonObject const& {
  return *Base::template get<JsonObject*>();
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14)))
auto JsonNodeBase<B, A>::getObject() CDS_ATTR(noexcept(false)) -> JsonObject& {
  return *Base::template get<JsonObject*>();
}

template <typename B, typename A>
template <typename T, EnableIf<AdaptsAsAllocated<T>>> CDS_ATTR(constexpr(20))
auto JsonNodeBase<B, A>::operator=(T&& value) noexcept -> JsonNodeBase& {
  if (!isPrimitive()) {
    clear();
  }

  Base::operator=(construct(Alloc::template get<typename JsonNodeAdapt<T>::AdaptedAs>().allocate(1), fwd<T>(value)));
  return *this;
}

template <typename B, typename A> CDS_ATTR(constexpr(20))
auto JsonNodeBase<B, A>::operator=(JsonNodeBase const& node) noexcept -> JsonNodeBase& {
  if (this == &node) {
    return *this;
  }

  if (isPrimitive() && node.isPrimitive()) {
    Base::operator=(static_cast<Base const&>(node));
    return *this;
  }

  if (Base::index() == node.index()) {
    if (node.isString()) {
      getString() = node.getString();
    } else if (node.isArray()) {
      getArray() = node.getArray();
    } else {
      assert(node.isObject() && "undefined behavior");
      getObject() = node.getObject();
    }
    return *this;
  }

  if (!isPrimitive()) {
    clear();
  }

  if (node.isPrimitive()) {
    Base::operator=(node);
    return *this;
  }

  if (node.isString()) {
    Base::operator=(construct(Alloc::template get<JsonString>().allocate(1), node.getString()));
  } else if (node.isArray()) {
    Base::operator=(construct(Alloc::template get<JsonArray>().allocate(1), node.getArray()));
  } else {
    assert(node.isObject() && "undefined behavior");
    Base::operator=(construct(Alloc::template get<JsonObject>().allocate(1), node.getObject()));
  }
  return *this;
}

template <typename B, typename A> CDS_ATTR(constexpr(20)) auto JsonNodeBase<B, A>::clear() noexcept -> void {
  if (isString()) {
    auto const pObj = Base::template get<JsonString*>();
    destruct(pObj);
    Alloc::template get<JsonString>().deallocate(pObj, 1);
  } else if (isArray()) {
    auto const pObj = Base::template get<JsonArray*>();
    destruct(pObj);
    Alloc::template get<JsonArray>().deallocate(pObj, 1);
  } else {
    assert(isObject() && "undefined behavior");
    auto const pObj = Base::template get<JsonObject*>();
    destruct(pObj);
    Alloc::template get<JsonObject>().deallocate(pObj, 1);
  }
  Base::template emplace<JsonNull>(nullptr);
}

template <typename B0, typename A0, typename B1, typename A1> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonNodeBase<B0, A0> const& lhs,
    JsonNodeBase<B1, A1> const& rhs
    ) noexcept -> bool {
  if (&lhs == &rhs) {
    return true;
  }

  JsonNodeBasePeeker const peeker{};
  if (peeker.index(lhs) != peeker.index(rhs)) {
    return false;
  }

  if (peeker.isPrimitive(lhs)) {
    return peeker.base(lhs) == peeker.base(rhs);
  }

  if (lhs.isString()) {
    return lhs.getString() == rhs.getString();
  }

  if (lhs.isArray()) {
    return lhs.getArray() == rhs.getArray();
  }

  assert(lhs.isObject() && "undefined behavior");
  return lhs.getObject() == rhs.getObject();
}

template <typename B0, typename A0, typename B1, typename A1> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonNodeBase<B0, A0> const& lhs,
    JsonNodeBase<B1, A1> const& rhs
    ) noexcept -> bool {
  return !(lhs == rhs);
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonNodeBase<B, A> const& lhs,
    T const& value
    ) noexcept -> bool {
  return lhs.isArray() && lhs.getArray() == value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonNodeBase<B, A> const& lhs,
    T const& value
    ) noexcept -> bool {
  return !lhs.isArray() || lhs.getArray() != value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    T const& value,
    JsonNodeBase<B, A> const& rhs
    ) noexcept -> bool {
  return rhs.isArray() && rhs.getArray() == value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    T const& value,
    JsonNodeBase<B, A> const& rhs
    ) noexcept -> bool {
  return !rhs.isArray() || rhs.getArray() != value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonNodeBase<B, A> const& lhs,
    T const& value
    ) noexcept -> bool {
  return lhs.isObject() && lhs.getObject() == value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonNodeBase<B, A> const& lhs,
    T const& value
    ) noexcept -> bool {
  return !lhs.isObject() || lhs.getObject() != value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    T const& value,
    JsonNodeBase<B, A> const& rhs
    ) noexcept -> bool {
  return rhs.isObject() && rhs.getObject() == value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    T const& value,
    JsonNodeBase<B, A> const& rhs
    ) noexcept -> bool {
  return !rhs.isObject() || rhs.getObject() != value;
}

template <typename C, typename B, typename A> CDS_ATTR(inline)
auto operator<<(std::basic_ostream<C>& out, JsonNodeBase<B, A> const& value) noexcept -> std::basic_ostream<C>& {
  if (value.isNull()) {
    return out << "null";
  }

  if (value.isBool()) {
    return out << (value.getBool() ? "true" : "false");
  }

  if (value.isIntegral()) {
    return out << value.getInt();
  }

  if (value.isFloating()) {
    return out << value.getDouble();
  }

  if (value.isString()) {
    return out << value.getString();
  }

  if (value.isArray()) {
    return out << value.getArray();
  }

  assert(value.isObject() && "undefined behavior");
  return out << value.getObject();
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_NODE_IMPL_HPP
