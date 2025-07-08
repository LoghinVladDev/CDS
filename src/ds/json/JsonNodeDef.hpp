//
// Created by loghin on 6/16/25.
//

#ifndef CDS_DS_JSON_NODE_DEF_HPP
#define CDS_DS_JSON_NODE_DEF_HPP
#pragma once

#include "JsonArrayDecl.hpp"
#include "JsonNodeDecl.hpp"
#include "JsonObjectDecl.hpp"

#include <cds/String>
#include <cds/StringView>
#include <cds/Tuple>
#include <cds/Union>

#include "../../stdlib/ostream.hpp"

namespace cds {
namespace json {
namespace impl {
using meta::Bool;
using meta::EnableIf;
using meta::IsIntegral;
using meta::IsFloating;
using meta::IsIterable;
using meta::Not;
using meta::Or;
using meta::False;
using meta::True;
using meta::RemoveCVRef;
using meta::Void;
using meta::rvalue;

using cds::impl::StringAbstract;
using cds::impl::construct;

class JsonNodeAllocator : public AllocatorSet<
    Allocator<JsonString>,
    Allocator<JsonArrayBase<>>,
    Allocator<JsonObjectBase<>>
> {
  using AllocatorSet::AllocatorSet;
};

enum class JsonNodeAdaptType {
  Primitive, String, Array, Object, None,
};

template <typename T, typename = void> struct IsMapPairLike : False {};
template <typename T>
struct IsMapPairLike<T, Void<decltype(cds::impl::get<0>(rvalue<T>()), cds::impl::get<1>(rvalue<T>()))>> : True {};

template <typename T, typename = void> struct IteratedTypeOfIterable {
  using Type = void;
};

template <typename T> struct IteratedTypeOfIterable<T, Void<decltype(*cds::begin(rvalue<T>()))>> {
  using Type = RemoveCVRef<decltype(*cds::begin(rvalue<T>()))>;
};

template <typename T, typename = typename IsIterable<T>::Type> struct IsIterableOfTupleLikes : False {};
template <typename T> struct IsIterableOfTupleLikes<T, True> :
    IsMapPairLike<typename IteratedTypeOfIterable<T>::Type> {};

template <
    typename T,
    typename = typename Or<IsIntegral<T>, IsFloating<T>>::Type,
    typename = typename StringAbstract<T>::Type,
    typename = typename IsIterable<T>::Type,
    typename = typename IsIterableOfTupleLikes<T>::Type
> struct JsonNodeAdapt {
  static constexpr auto value = JsonNodeAdaptType::None;
};

template <typename T> struct JsonNodeAdapt<T, True, False, False, False> {
  static constexpr auto value = JsonNodeAdaptType::Primitive;
};

template <typename T> struct JsonNodeAdapt<T, False, True, True, False> {
  static constexpr auto value = JsonNodeAdaptType::String;
  using AdaptedAs = JsonString;
};

template <typename T> struct JsonNodeAdapt<T, False, False, True, False> {
  static constexpr auto value = JsonNodeAdaptType::Array;
  using AdaptedAs = JsonArrayBase<>;
};

template <typename T> struct JsonNodeAdapt<T, False, False, True, True> {
  static constexpr auto value = JsonNodeAdaptType::Object;
  using AdaptedAs = JsonObjectBase<>;
};

template <typename B> struct JsonNodeAdapt<JsonArrayBase<B>, False, False, True, False> {
  static constexpr auto value = JsonNodeAdaptType::Array;
  using AdaptedAs = JsonArrayBase<B>;
};

template <typename B> struct JsonNodeAdapt<JsonObjectBase<B>, False, False, True, True> {
  static constexpr auto value = JsonNodeAdaptType::Object;
  using AdaptedAs = JsonObjectBase<B>;
};

template <typename T> using AdaptsAsPrimitive =
    Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::Primitive>;

template <typename T> using AdaptsAsString = Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::String>;
template <typename T> using AdaptsAsArray = Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::Array>;
template <typename T> using AdaptsAsObject = Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::Object>;

template <typename T> using AdaptsAsAllocated = Or<AdaptsAsString<T>, AdaptsAsArray<T>, AdaptsAsObject<T>>;

// Keep these in this order, otherwise change bitwise check for first 4.
template <typename TJsonArray = JsonArrayBase<>, typename TJsonObject = JsonObjectBase<>>
struct JsonNodeBaseImpl : Union<
    JsonNull, JsonBool, JsonNumberIntegral, JsonNumberFloating,
    JsonString*, TJsonArray*, TJsonObject*
> {
  using UnionBase = Union<
      JsonNull, JsonBool, JsonNumberIntegral, JsonNumberFloating,
      JsonString*, TJsonArray*, TJsonObject*
  >;

  using JsonArray = TJsonArray;
  using JsonObject = TJsonObject;

  using UnionBase::UnionBase;
  using UnionBase::operator=;
};

struct JsonNodeBasePeeker {
  template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11))) auto index(JsonNodeBase<B, A> const& node)
      const noexcept -> U8 {
    return static_cast<U8>(node.index());
  }

  template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto isPrimitive(JsonNodeBase<B, A> const& node) const noexcept -> bool {
    return node.isPrimitive();
  }

  template <typename TBase, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto base(JsonNodeBase<TBase, A> const& node) const noexcept -> typename JsonNodeBase<TBase, A>::Base const& {
    return node;
  }
};

template <typename TBase> struct JsonNodeBaseSelector : TBase {
  using TBase::TBase;
  using TBase::operator=;
};

template <typename TAlloc> struct JsonNodeAllocSelector : TAlloc {
  using TAlloc::TAlloc;
  using TAlloc::operator=;
};

template <> struct JsonNodeBaseSelector<Default> : JsonNodeBaseSelector<JsonNodeBaseImpl<>> {
  using JsonNodeBaseSelector<JsonNodeBaseImpl<>>::JsonNodeBaseSelector;
  using JsonNodeBaseSelector<JsonNodeBaseImpl<>>::operator=;
};

template <> struct JsonNodeAllocSelector<Default> : JsonNodeAllocSelector<JsonNodeAllocator> {
  using JsonNodeAllocSelector<JsonNodeAllocator>::JsonNodeAllocSelector;
  using JsonNodeAllocSelector<JsonNodeAllocator>::operator=;
};

template <typename TBase, typename TAlloc> class JsonNodeBase :
    private JsonNodeBaseSelector<TBase>, private JsonNodeAllocSelector<TAlloc> {
  friend struct JsonNodeBasePeeker;

  using Base = JsonNodeBaseSelector<TBase>;
  using Alloc = JsonNodeAllocSelector<TAlloc>;

public:
  using typename Base::JsonArray;
  using typename Base::JsonObject;

  CDS_ATTR(constexpr(11)) JsonNodeBase() : Base{InPlaceIndex<0>{}, nullptr} {}

  CDS_ATTR(constexpr(20)) JsonNodeBase(JsonNodeBase const& node) noexcept;

  CDS_ATTR(constexpr(14)) JsonNodeBase(JsonNodeBase&& node) noexcept : Base{mv(node)} {
    static_cast<Base&>(node) = nullptr;
  }

  CDS_ATTR(2(implicit, constexpr(11))) JsonNodeBase(JsonNull) : JsonNodeBase{} {}
  CDS_ATTR(2(implicit, constexpr(11))) JsonNodeBase(JsonBool value) : Base{InPlaceIndex<1>{}, value} {}

  template <typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(implicit, constexpr(11)))
  JsonNodeBase(N value) : Base{InPlaceIndex<2>{}, value} {}

  template <typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(implicit, constexpr(11)))
  JsonNodeBase(N value) : Base{InPlaceIndex<3>{}, value} {}

  template <typename T, EnableIf<AdaptsAsAllocated<T>> = 0>
  CDS_ATTR(2(implicit, constexpr(20))) JsonNodeBase(T&& value) noexcept;

  CDS_ATTR(2(implicit, constexpr(20))) JsonNodeBase(std::initializer_list<JsonNodeBase> const& list) noexcept;

  CDS_ATTR(constexpr(20)) ~JsonNodeBase() noexcept {
    if (!isPrimitive()) {
      clear();
    }
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isNull() const noexcept -> bool {
    return Base::template is<JsonNull>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isBool() const noexcept -> bool {
    return Base::template is<JsonBool>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isIntegral() const noexcept -> bool {
    return Base::template is<JsonNumberIntegral>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isFloating() const noexcept -> bool {
    return Base::template is<JsonNumberFloating>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isNumber() const noexcept -> bool {
    return isIntegral() || isFloating();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isString() const noexcept -> bool {
    return Base::template is<JsonString*>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isArray() const noexcept -> bool;
  CDS_ATTR(2(nodiscard, constexpr(11))) auto isObject() const noexcept -> bool;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto getBool() const CDS_ATTR(noexcept(false)) -> bool {
    return Base::template get<bool>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto getInt() const CDS_ATTR(noexcept(false)) -> S32 {
    return static_cast<S32>(getLong());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto getLong() const CDS_ATTR(noexcept(false)) -> S64 {
    return Base::template get<JsonNumberIntegral>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto getDouble() const CDS_ATTR(noexcept(false)) -> double {
    return Base::template get<JsonNumberFloating>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto getString() const CDS_ATTR(noexcept(false)) -> JsonString const& {
    return *Base::template get<JsonString*>();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto getString() CDS_ATTR(noexcept(false)) -> JsonString& {
    return *Base::template get<JsonString*>();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto getArray() const CDS_ATTR(noexcept(false)) -> JsonArray const&;
  CDS_ATTR(2(nodiscard, constexpr(14))) auto getArray() CDS_ATTR(noexcept(false)) -> JsonArray&;
  CDS_ATTR(2(nodiscard, constexpr(11))) auto getObject() const CDS_ATTR(noexcept(false)) -> JsonObject const&;
  CDS_ATTR(2(nodiscard, constexpr(14))) auto getObject() CDS_ATTR(noexcept(false)) -> JsonObject&;

  CDS_ATTR(constexpr(20)) auto operator=(JsonNull) noexcept -> JsonNodeBase& {
    if (!isPrimitive()) {
      clear();
    }

    Base::template emplace<JsonNull>(nullptr);
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(bool value) noexcept -> JsonNodeBase& {
    if (!isPrimitive()) {
      clear();
    }

    Base::template emplace<JsonBool>(value);
    return *this;
  }

  template <typename T, EnableIf<IsIntegral<T>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(T value) noexcept -> JsonNodeBase& {
    if (!isPrimitive()) {
      clear();
    }

    Base::template emplace<JsonNumberIntegral>(value);
    return *this;
  }

  template <typename T, EnableIf<IsFloating<T>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(T value) noexcept -> JsonNodeBase& {
    if (!isPrimitive()) {
      clear();
    }

    Base::template emplace<JsonNumberFloating>(value);
    return *this;
  }

  template <typename T, EnableIf<AdaptsAsAllocated<T>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(T&& value) noexcept -> JsonNodeBase&;
  CDS_ATTR(constexpr(20)) auto operator=(JsonNodeBase const& node) noexcept -> JsonNodeBase&;

  CDS_ATTR(constexpr(20)) auto operator=(JsonNodeBase&& node) noexcept -> JsonNodeBase& {
    if (this == &node) {
      return *this;
    }

    if (!isPrimitive()) {
      clear();
    }

    Base::operator=(mv(node));
    static_cast<Base&>(node) = nullptr;
    return *this;
  }

private:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto isPrimitive() const noexcept -> bool {
    return 0 == (Base::index() & 0x4u);
  }

  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void;
};

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonNodeBase<B, A> const& lhs,
    JsonNull
) noexcept -> bool {
  return lhs.isNull();
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonNodeBase<B, A> const& lhs,
    JsonNull
) noexcept -> bool {
  return !lhs.isNull();
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonNull,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return rhs.isNull();
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonNull,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return !rhs.isNull();
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonNodeBase<B, A> const& lhs,
    JsonBool value
) noexcept -> bool {
  return lhs.isBool() && lhs.getBool() == value;
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonNodeBase<B, A> const& lhs,
    JsonBool value
) noexcept -> bool {
  return !lhs.isBool() || lhs.getBool() != value;
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonBool value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return rhs.isBool() && rhs.getBool() == value;
}

template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonBool value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return !rhs.isBool() || rhs.getBool() != value;
}

template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator==(
    JsonNodeBase<B, A> const& lhs,
    N value
) noexcept -> bool {
  return lhs.isIntegral() && lhs.getInt() == value;
}

template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator!=(
    JsonNodeBase<B, A> const& lhs,
    N value
) noexcept -> bool {
  return !lhs.isIntegral() || lhs.getInt() != value;
}

template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator==(
    N value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return rhs.isIntegral() && rhs.getInt() == value;
}

template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator!=(
    N value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return !rhs.isIntegral() || rhs.getInt() != value;
}

template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator==(
    JsonNodeBase<B, A> const& lhs,
    N value
) noexcept -> bool {
  return lhs.isFloating() && lhs.getDouble() == value;
}

template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator!=(
    JsonNodeBase<B, A> const& lhs,
    N value
) noexcept -> bool {
  return !lhs.isFloating() || lhs.getDouble() != value;
}

template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
auto operator==(
    N value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return rhs.isFloating() && rhs.getDouble() == value;
}

template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    N value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return !rhs.isFloating() || rhs.getDouble() != value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    JsonNodeBase<B, A> const& lhs,
    T const& value
) noexcept -> bool {
  return lhs.isString() && lhs.getString() == value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    JsonNodeBase<B, A> const& lhs,
    T const& value
) noexcept -> bool {
  return !lhs.isString() || lhs.getString() != value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    T const& value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return rhs.isString() && rhs.getString() == value;
}

template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    T const& value,
    JsonNodeBase<B, A> const& rhs
) noexcept -> bool {
  return !rhs.isString() || rhs.getString() != value;
}
} // namespace impl

using JsonNode = impl::JsonNodeBase<>;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_NODE_DEF_HPP
