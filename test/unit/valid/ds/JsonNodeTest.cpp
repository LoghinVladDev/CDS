//
// Created by loghin on 6/17/25.
//

//#include "UnitTest.hpp"
//
//#include <cds/Union>
//#include <cds/String>
//#include <cds/StringView>
//#include <cds/collection/Vector>
//#include <cds/collection/LinkedHashMap>
//
//#include <cds/meta/Tags>
//
//#include "../../../src/stdlib/ostream.hpp"
//
//namespace {
//using namespace cds;
//using namespace cds::meta;
//using namespace cds::impl;
//
//template <typename TBase = Default, typename TAlloc = Default> class JsonNodeBase;
//template <typename B = Default> class JsonArrayBase;
//template <typename B = Default> class JsonObjectBase;
//
//using JsonString = String;
//using JsonBool = bool;
//using JsonNull = meta::Null;
//using JsonNumberIntegral = S64;
//using JsonNumberFloating = double;
//
//class JsonNodeAllocator : public AllocatorSet<
//                              Allocator<JsonString>,
//                              Allocator<JsonArrayBase<>>,
//                              Allocator<JsonObjectBase<>>
//                              > {
//  using AllocatorSet::AllocatorSet;
//};
//
//
//enum class JsonNodeAdaptType {
//  Primitive, String, Array, Object,
//};
//
//template <typename T, typename = void> struct IsMapPairLike : False {};
//template <typename T> struct IsMapPairLike<T, Void<decltype(get<0>(rvalue<T>()), get<1>(rvalue<T>()))>> : True {};
//
//template <typename T, typename = void> struct IteratedTypeOfIterable {
//  using Type = void;
//};
//
//template <typename T> struct IteratedTypeOfIterable<T, Void<decltype(*cds::begin(rvalue<T>()))>> {
//  using Type = RemoveCVRef<decltype(*cds::begin(rvalue<T>()))>;
//};
//
//template <typename T, typename = typename IsIterable<T>::Type> struct IsIterableOfTupleLikes : False {};
//template <typename T> struct IsIterableOfTupleLikes<T, True> :
//    IsMapPairLike<typename IteratedTypeOfIterable<T>::Type> {};
//
//template <
//    typename T,
//    typename = typename Or<IsIntegral<T>, IsFloating<T>>::Type,
//    typename = typename StringAbstract<T>::Type,
//    typename = typename IsIterable<T>::Type,
//    typename = typename IsIterableOfTupleLikes<T>::Type
//    > struct JsonNodeAdapt;
//
//template <typename T> struct JsonNodeAdapt<T, True, False, False, False> {
//  static constexpr auto value = JsonNodeAdaptType::Primitive;
//};
//
//template <typename T> struct JsonNodeAdapt<T, False, True, True, False> {
//  static constexpr auto value = JsonNodeAdaptType::String;
//  using AdaptedAs = JsonString;
//};
//
//template <typename T> struct JsonNodeAdapt<T, False, False, True, False> {
//  static constexpr auto value = JsonNodeAdaptType::Array;
//  using AdaptedAs = JsonArrayBase<>;
//};
//
//template <typename T> struct JsonNodeAdapt<T, False, False, True, True> {
//  static constexpr auto value = JsonNodeAdaptType::Object;
//  using AdaptedAs = JsonObjectBase<>;
//};
//
//template <typename B> struct JsonNodeAdapt<JsonArrayBase<B>, False, False, True, False> {
//  static constexpr auto value = JsonNodeAdaptType::Array;
//  using AdaptedAs = JsonArrayBase<B>;
//};
//
//template <typename B> struct JsonNodeAdapt<JsonObjectBase<B>, False, False, True, True> {
//  static constexpr auto value = JsonNodeAdaptType::Object;
//  using AdaptedAs = JsonObjectBase<B>;
//};
//
//template <typename T> using AdaptsAsPrimitive =
//    Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::Primitive>;
//
//template <typename T> using AdaptsAsString = Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::String>;
//template <typename T> using AdaptsAsArray = Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::Array>;
//template <typename T> using AdaptsAsObject = Bool<JsonNodeAdapt<RemoveCVRef<T>>::value == JsonNodeAdaptType::Object>;
//
//template <typename T> using AdaptsAsAllocated = Or<AdaptsAsString<T>, AdaptsAsArray<T>, AdaptsAsObject<T>>;
//
//// Keep these in this order, otherwise change bitwise check for first 4.
//template <typename JsonArrayPtr = JsonArrayBase<>*, typename JsonObjectPtr = JsonObjectBase<>*>
//struct JsonNodeBaseImpl : Union<
//                              JsonNull, JsonBool, JsonNumberIntegral, JsonNumberFloating,
//                              JsonString*, JsonArrayPtr, JsonObjectPtr
//                              > {
//  using JsonArray = meta::RemovePointer<JsonArrayPtr>;
//  using JsonObject = meta::RemovePointer<JsonObjectPtr>;
//  using Union<
//      JsonNull, JsonBool, JsonNumberIntegral, JsonNumberFloating,
//      JsonString*, JsonArrayPtr, JsonObjectPtr
//      >::Union;
//};
//
//struct JsonNodeBasePeeker {
//  template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11))) auto index(JsonNodeBase<B, A> const& node)
//      const noexcept -> U8 {
//    return node.index();
//  }
//
//  template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
//  auto isPrimitive(JsonNodeBase<B, A> const& node) const noexcept -> bool {
//    return node.isPrimitive();
//  }
//
//  template <typename TBase, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
//  auto base(JsonNodeBase<TBase, A> const& node) const noexcept -> Conditional<IsSame<TBase, Default>, JsonNodeBaseImpl<>, TBase> const& {
//    return node;
//  }
//};
//
//template <typename TBase, typename TAlloc> class JsonNodeBase :
//    private Conditional<IsSame<TBase, Default>, JsonNodeBaseImpl<>, TBase>, private Conditional<IsSame<TAlloc, Default>, JsonNodeAllocator, TAlloc> {
//  friend struct JsonNodeBasePeeker;
//
//  using Base = DefaultOr<TBase, JsonNodeBaseImpl<>>;
//  using Alloc = DefaultOr<TAlloc, JsonNodeAllocator>;
//
//  using typename Base::JsonArray;
//  using typename Base::JsonObject;
//
//public:
//  CDS_ATTR(constexpr(11)) JsonNodeBase() : Base{InPlaceIndex<0>{}, nullptr} {}
//
//  CDS_ATTR(constexpr(20)) JsonNodeBase(JsonNodeBase const& node) noexcept;
//
//  CDS_ATTR(constexpr(14)) JsonNodeBase(JsonNodeBase&& node) noexcept : Base{mv(node)} {
//    static_cast<Base&>(node) = nullptr;
//  }
//
//  CDS_ATTR(2(implicit, constexpr(11))) JsonNodeBase(JsonNull) : JsonNodeBase{} {}
//  CDS_ATTR(2(implicit, constexpr(11))) JsonNodeBase(JsonBool value) : Base{InPlaceIndex<1>{}, value} {}
//
//  template <typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(implicit, constexpr(11)))
//  JsonNodeBase(N value) : Base{InPlaceIndex<2>{}, value} {}
//
//  template <typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(implicit, constexpr(11)))
//  JsonNodeBase(N value) : Base{InPlaceIndex<3>{}, value} {}
//
//  template <typename T, EnableIf<AdaptsAsAllocated<T>> = 0>
//  CDS_ATTR(2(implicit, constexpr(20))) JsonNodeBase(T&& value) noexcept;
//
//  CDS_ATTR(2(implicit, constexpr(20))) JsonNodeBase(std::initializer_list<JsonNodeBase> const& list) noexcept;
//
//  CDS_ATTR(constexpr(20)) ~JsonNodeBase() noexcept {
//    if (!isPrimitive()) {
//      clear();
//    }
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isNull() const noexcept -> bool {
//    return Base::template is<JsonNull>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isBool() const noexcept -> bool {
//    return Base::template is<JsonBool>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isIntegral() const noexcept -> bool {
//    return Base::template is<JsonNumberIntegral>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isFloating() const noexcept -> bool {
//    return Base::template is<JsonNumberFloating>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isNumber() const noexcept -> bool {
//    return isIntegral() || isFloating();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isString() const noexcept -> bool {
//    return Base::template is<JsonString*>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isArray() const noexcept -> bool;
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isObject() const noexcept -> bool;
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto getBool() const CDS_ATTR(noexcept(false)) -> bool {
//    return Base::template get<bool>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto getInt() const CDS_ATTR(noexcept(false)) -> S32 {
//    return static_cast<S32>(getLong());
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto getLong() const CDS_ATTR(noexcept(false)) -> S64 {
//    return Base::template get<JsonNumberIntegral>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto getDouble() const CDS_ATTR(noexcept(false)) -> double {
//    return Base::template get<JsonNumberFloating>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto getString() const CDS_ATTR(noexcept(false)) -> JsonString const& {
//    return *Base::template get<JsonString*>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(14))) auto getString() CDS_ATTR(noexcept(false)) -> JsonString& {
//    return *Base::template get<JsonString*>();
//  }
//
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto getArray() const CDS_ATTR(noexcept(false)) -> JsonArray const&;
//  CDS_ATTR(2(nodiscard, constexpr(14))) auto getArray() CDS_ATTR(noexcept(false)) -> JsonArray&;
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto getObject() const CDS_ATTR(noexcept(false)) -> JsonObject const&;
//  CDS_ATTR(2(nodiscard, constexpr(14))) auto getObject() CDS_ATTR(noexcept(false)) -> JsonObject&;
//
//  CDS_ATTR(constexpr(20)) auto operator=(JsonNull) noexcept -> JsonNodeBase& {
//    if (!isPrimitive()) {
//      clear();
//    }
//
//    Base::template emplace<JsonNull>(nullptr);
//    return *this;
//  }
//
//  CDS_ATTR(constexpr(20)) auto operator=(bool value) noexcept -> JsonNodeBase& {
//    if (!isPrimitive()) {
//      clear();
//    }
//
//    Base::template emplace<JsonBool>(value);
//    return *this;
//  }
//
//  template <typename T, EnableIf<IsIntegral<T>> = 0>
//  CDS_ATTR(constexpr(20)) auto operator=(T value) noexcept -> JsonNodeBase& {
//    if (!isPrimitive()) {
//      clear();
//    }
//
//    Base::template emplace<JsonNumberIntegral>(value);
//    return *this;
//  }
//
//  template <typename T, EnableIf<IsFloating<T>> = 0>
//  CDS_ATTR(constexpr(20)) auto operator=(T value) noexcept -> JsonNodeBase& {
//    if (!isPrimitive()) {
//      clear();
//    }
//
//    Base::template emplace<JsonNumberFloating>(value);
//    return *this;
//  }
//
//  template <typename T, EnableIf<AdaptsAsAllocated<T>> = 0>
//  CDS_ATTR(constexpr(20)) auto operator=(T&& value) noexcept -> JsonNodeBase&;
//  CDS_ATTR(constexpr(20)) auto operator=(JsonNodeBase const& node) noexcept -> JsonNodeBase&;
//
//  CDS_ATTR(constexpr(20)) auto operator=(JsonNodeBase&& node) noexcept -> JsonNodeBase& {
//    if (this == &node) {
//      return *this;
//    }
//
//    if (!isPrimitive()) {
//      clear();
//    }
//
//    Base::operator=(mv(node));
//    static_cast<Base&>(node) = nullptr;
//    return *this;
//  }
//
//private:
//  CDS_ATTR(2(nodiscard, constexpr(11))) auto isPrimitive() const noexcept -> bool {
//    return 0 == (Base::index() & 0x4u);
//  }
//
//  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void;
//};
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonNodeBase<B, A> const& lhs,
//    JsonNull
//    ) noexcept -> bool {
//  return lhs.isNull();
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonNodeBase<B, A> const& lhs,
//    JsonNull
//    ) noexcept -> bool {
//  return !lhs.isNull();
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonNull,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return rhs.isNull();
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonNull,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return !rhs.isNull();
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonNodeBase<B, A> const& lhs,
//    JsonBool value
//    ) noexcept -> bool {
//  return lhs.isBool() && lhs.getBool() == value;
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonNodeBase<B, A> const& lhs,
//    JsonBool value
//    ) noexcept -> bool {
//  return !lhs.isBool() || lhs.getBool() != value;
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonBool value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return rhs.isBool() && rhs.getBool() == value;
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonBool value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return !rhs.isBool() || rhs.getBool() != value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto operator==(
//    JsonNodeBase<B, A> const& lhs,
//    N value
//    ) noexcept -> bool {
//  return lhs.isIntegral() && lhs.getInt() == value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto operator!=(
//    JsonNodeBase<B, A> const& lhs,
//    N value
//    ) noexcept -> bool {
//  return !lhs.isIntegral() || lhs.getInt() != value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto operator==(
//    N value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return rhs.isIntegral() && rhs.getInt() == value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto operator!=(
//    N value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return !rhs.isIntegral() || rhs.getInt() != value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto operator==(
//    JsonNodeBase<B, A> const& lhs,
//    N value
//    ) noexcept -> bool {
//  return lhs.isFloating() && lhs.getDouble() == value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto operator!=(
//    JsonNodeBase<B, A> const& lhs,
//    N value
//    ) noexcept -> bool {
//  return !lhs.isFloating() || lhs.getDouble() != value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto operator==(
//    N value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return rhs.isFloating() && rhs.getDouble() == value;
//}
//
//template <typename B, typename A, typename N, EnableIf<IsFloating<N>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    N value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return !rhs.isFloating() || rhs.getDouble() != value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonNodeBase<B, A> const& lhs,
//    T const& value
//    ) noexcept -> bool {
//  return lhs.isString() && lhs.getString() == value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonNodeBase<B, A> const& lhs,
//    T const& value
//    ) noexcept -> bool {
//  return !lhs.isString() || lhs.getString() != value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    T const& value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return rhs.isString() && rhs.getString() == value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsString<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    T const& value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return !rhs.isString() || rhs.getString() != value;
//}
//
//using JsonNode = JsonNodeBase<>;
//
//using JsonArrayBaseImpl = Vector<JsonNodeBase<>>;
//
//template <typename TBase> class JsonArrayBase : public Conditional<IsSame<TBase, Default>, JsonArrayBaseImpl, TBase> {
//  using Base = Conditional<IsSame<TBase, Default>, JsonArrayBaseImpl, TBase>;
//
//public:
//  using Base::Base;
//  using Base::operator=;
//  ~JsonArrayBase() = default;
//};
//
//using JsonObjectBaseImpl = LinkedHashMap<String, JsonNodeBase<>>;
//
//template <typename TBase> class JsonObjectBase : public Conditional<IsSame<TBase, Default>, JsonObjectBaseImpl, TBase> {
//  using Base = Conditional<IsSame<TBase, Default>, JsonObjectBaseImpl, TBase>;
//
//public:
//  using Base::Base;
//  using Base::operator=;
//  ~JsonObjectBase() = default;
//};
//
//using JsonArray = JsonArrayBase<>;
//
///// Impl
//
//template <typename B, typename A> CDS_ATTR(constexpr(11))
//auto JsonNodeBase<B, A>::isArray() const noexcept -> bool {
//  return Base::template is<JsonArray*>();
//}
//
//template <typename B, typename A> CDS_ATTR(constexpr(11))
//auto JsonNodeBase<B, A>::isObject() const noexcept -> bool {
//  return Base::template is<JsonObject*>();
//}
//
//template <typename B, typename A> CDS_ATTR(constexpr(20))
//JsonNodeBase<B, A>::JsonNodeBase(JsonNodeBase const& node) noexcept : Base{} {
//  if (node.isPrimitive()) {
//    Base::operator=(static_cast<Base const&>(node));
//    return;
//  }
//
//  if (node.isString()) {
//    Base::operator=(construct(Alloc::template get<JsonString>().allocate(1), node.getString()));
//  } else if (node.isArray()) {
//    Base::operator=(construct(Alloc::template get<JsonArray>().allocate(1), node.getArray()));
//  } else {
//    assert(node.isObject() && "undefined behavior");
//    Base::operator=(construct(Alloc::template get<JsonObject>().allocate(1), node.getObject()));
//  }
//}
//
//template <typename B, typename A>
//template <typename T, EnableIf<AdaptsAsAllocated<T>>> CDS_ATTR(constexpr(20))
//JsonNodeBase<B, A>::JsonNodeBase(T&& value) noexcept :
//    Base{construct(Alloc::template get<typename JsonNodeAdapt<T>::AdaptedAs>().allocate(1), fwd<T>(value))} {}
//
//template <typename B, typename A> CDS_ATTR(constexpr(20))
//JsonNodeBase<B, A>::JsonNodeBase(std::initializer_list<JsonNodeBase> const& list) noexcept : Base{} {
//  auto const isThisAnObject = cds::impl::all(list.begin(), list.end(), [](JsonNodeBase const& node) {
//    return node.isArray() && node.getArray().size() == 2 && node.getArray()[0].isString();
//  });
//
//  if (!isThisAnObject) {
//    Base::operator=(construct(Alloc::template get<JsonArray>().allocate(1), list));
//    return;
//  }
//
//  Base::operator=(construct(Alloc::template get<JsonObject>().allocate(1)));
//  auto& object = getObject();
//  for (auto const& entry : list) {
//    auto const& key = entry.getArray()[0].getString();
//    auto const& value = entry.getArray()[1];
//    object.emplace(key, value);
//  }
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
//auto JsonNodeBase<B, A>::getArray() const CDS_ATTR(noexcept(false)) -> JsonArray const& {
//  return *Base::template get<JsonArray*>();
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto JsonNodeBase<B, A>::getArray() CDS_ATTR(noexcept(false)) -> JsonArray& {
//  return *Base::template get<JsonArray*>();
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(11)))
//auto JsonNodeBase<B, A>::getObject() const CDS_ATTR(noexcept(false)) -> JsonObject const& {
//  return *Base::template get<JsonObject*>();
//}
//
//template <typename B, typename A> CDS_ATTR(2(nodiscard, constexpr(14)))
//auto JsonNodeBase<B, A>::getObject() CDS_ATTR(noexcept(false)) -> JsonObject& {
//  return *Base::template get<JsonObject*>();
//}
//
//template <typename B, typename A>
//template <typename T, EnableIf<AdaptsAsAllocated<T>>> CDS_ATTR(constexpr(20))
//auto JsonNodeBase<B, A>::operator=(T&& value) noexcept -> JsonNodeBase& {
//  if (!isPrimitive()) {
//    clear();
//  }
//
//  Base::operator=(construct(Alloc::template get<typename JsonNodeAdapt<T>::AdaptedAs>().allocate(1), fwd<T>(value)));
//  return *this;
//}
//
//template <typename B, typename A> CDS_ATTR(constexpr(20))
//auto JsonNodeBase<B, A>::operator=(JsonNodeBase const& node) noexcept -> JsonNodeBase& {
//  if (this == &node) {
//    return *this;
//  }
//
//  if (isPrimitive() && node.isPrimitive()) {
//    Base::operator=(static_cast<Base const&>(node));
//    return *this;
//  }
//
//  if (Base::index() == node.index()) {
//    if (node.isString()) {
//      getString() = node.getString();
//    } else if (node.isArray()) {
//      getArray() = node.getArray();
//    } else {
//      assert(node.isObject() && "undefined behavior");
//      getObject() = node.getObject();
//    }
//    return *this;
//  }
//
//  if (!isPrimitive()) {
//    clear();
//  }
//
//  if (node.isPrimitive()) {
//    Base::operator=(node);
//    return *this;
//  }
//
//  if (node.isString()) {
//    Base::operator=(construct(Alloc::template get<JsonString>().allocate(1), node.getString()));
//  } else if (node.isArray()) {
//    Base::operator=(construct(Alloc::template get<JsonArray>().allocate(1), node.getArray()));
//  } else {
//    assert(node.isObject() && "undefined behavior");
//    Base::operator=(construct(Alloc::template get<JsonObject>().allocate(1), node.getObject()));
//  }
//  return *this;
//}
//
//template <typename B, typename A> CDS_ATTR(constexpr(20)) auto JsonNodeBase<B, A>::clear() noexcept -> void {
//  if (isString()) {
//    Alloc::template get<JsonString>().deallocate(Base::template get<JsonString*>(), 1);
//  } else if (isArray()) {
//    Alloc::template get<JsonArray>().deallocate(Base::template get<JsonArray*>(), 1);
//  } else {
//    assert(isObject() && "undefined behavior");
//    Alloc::template get<JsonObject>().deallocate(Base::template get<JsonObject*>(), 1);
//  }
//  Base::template emplace<JsonNull>(nullptr);
//}
//
//template <typename B0, typename A0, typename B1, typename A1> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonNodeBase<B0, A0> const& lhs,
//    JsonNodeBase<B1, A1> const& rhs
//    ) noexcept -> bool {
//  if (&lhs == &rhs) {
//    return true;
//  }
//
//  JsonNodeBasePeeker const peeker{};
//  if (peeker.index(lhs) != peeker.index(rhs)) {
//    return false;
//  }
//
//  if (peeker.isPrimitive(lhs)) {
//    return peeker.base(lhs) == peeker.base(rhs);
//  }
//
//  if (lhs.isString()) {
//    return lhs.getString() == rhs.getString();
//  }
//
//  if (lhs.isArray()) {
//    return lhs.getArray() == rhs.getArray();
//  }
//
//  assert(lhs.isObject() && "undefined behavior");
//  return lhs.getObject() == rhs.getObject();
//}
//
//template <typename B0, typename A0, typename B1, typename A1> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonNodeBase<B0, A0> const& lhs,
//    JsonNodeBase<B1, A1> const& rhs
//    ) noexcept -> bool {
//  return !(lhs == rhs);
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonNodeBase<B, A> const& lhs,
//    T const& value
//    ) noexcept -> bool {
//  return lhs.isArray() && lhs.getArray() == value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonNodeBase<B, A> const& lhs,
//    T const& value
//    ) noexcept -> bool {
//  return !lhs.isArray() || lhs.getArray() != value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    T const& value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return rhs.isArray() && rhs.getArray() == value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsArray<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    T const& value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return !rhs.isArray() || rhs.getArray() != value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    JsonNodeBase<B, A> const& lhs,
//    T const& value
//    ) noexcept -> bool {
//  return lhs.isObject() && lhs.getObject() == value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    JsonNodeBase<B, A> const& lhs,
//    T const& value
//    ) noexcept -> bool {
//  return !lhs.isObject() || lhs.getObject() != value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
//    T const& value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return rhs.isObject() && rhs.getObject() == value;
//}
//
//template <typename B, typename A, typename T, EnableIf<AdaptsAsObject<T>> = 0>
//CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
//    T const& value,
//    JsonNodeBase<B, A> const& rhs
//    ) noexcept -> bool {
//  return !rhs.isObject() || rhs.getObject() != value;
//}
//
//template <typename C, typename B, typename A> CDS_ATTR(inline)
//auto operator<<(std::basic_ostream<C>& out, JsonNodeBase<B, A> const& value) noexcept -> std::basic_ostream<C>& {
//  if (value.isNull()) {
//    return (out << "null");
//  }
//
//  if (value.isBool()) {
//    return (out << std::boolalpha << value.getBool());
//  }
//
//  if (value.isIntegral()) {
//    return (out << value.getInt());
//  }
//
//  if (value.isFloating()) {
//    return (out << value.getDouble());
//  }
//
//  if (value.isString()) {
//    return (out << value.getString());
//  }
//
//  if (value.isArray()) {
//    return (out << value.getArray());
//  }
//
//  assert(value.isObject() && "undefined behavior");
//  return (out << value.getObject());
//}
//} // namespace
//
//TEST(JsonNodeTest, instantiation) {
//  JsonNode n;
//}


#include <cds/json/JSON>

#include <UnitTest.hpp>

#include "../../../src/format/JsonFormatters.hpp"

namespace {
using namespace cds::json;

void copyOverTest(JsonNode& dst) {
  JsonNode asBool;
  asBool = true;
  dst = asBool;
  ASSERT_TRUE(dst.isBool());
  ASSERT_TRUE(dst.getBool());

  JsonNode asInt;
  asInt = 4;
  dst = asInt;
  ASSERT_TRUE(dst.isIntegral());
  ASSERT_EQ(4, dst.getInt());

  JsonNode asFloating;
  asFloating = 4.5;
  dst = asFloating;
  ASSERT_TRUE(dst.isFloating());
  ASSERT_LT(4.0, dst.getDouble());
  ASSERT_GT(5.0, dst.getDouble());

  JsonNode asString;
  asString = "abc";
  dst = asString;
  ASSERT_TRUE(dst.isString());
  ASSERT_EQ("abc", dst.getString());

  JsonNode asNull;
  asNull = nullptr;
  dst = asNull;
  ASSERT_TRUE(dst.isNull());
}
} // namespace

TEST(JsonNodeTest, ctrFromNull) {
  JsonNode node = nullptr;
  ASSERT_TRUE(node.isNull());
}

TEST(JsonNodeTest, ctrFromBool) {
  JsonNode node = true;
  ASSERT_TRUE(node.isBool());
  ASSERT_TRUE(node.getBool());
}

TEST(JsonNodeTest, ctrFromInt) {
  JsonNode node = 4;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(4, node.getInt());
}

TEST(JsonNodeTest, ctrFromFloating) {
  JsonNode node = 4.5;
  ASSERT_TRUE(node.isFloating());
  ASSERT_LT(4.0, node.getDouble());
  ASSERT_GT(5.0, node.getDouble());
}

TEST(JsonNodeTest, ctrFromString) {
  JsonNode node = "abcd";
  ASSERT_TRUE(node.isString());
  ASSERT_EQ("abcd", node.getString());
}

TEST(JsonNodeTest, ctrFromArray) {
  JsonNode node = JsonArray{1, false, "abc"};
  ASSERT_TRUE(node.isArray());
  ASSERT_EQ(node.getArray()[0], 1);
  ASSERT_EQ(node.getArray()[1], false);
  ASSERT_EQ(node.getArray()[2], "abc");
}

TEST(JsonNodeTest, copyCtr) {
  JsonNode nullNode = nullptr;
  JsonNode const nullCopy = nullNode;
  ASSERT_TRUE(nullCopy.isNull());

  JsonNode boolNode = true;
  JsonNode const boolCopy = boolNode;
  ASSERT_TRUE(boolCopy.isBool());
  ASSERT_TRUE(boolCopy.getBool());

  JsonNode intNode = 4;
  JsonNode const intCopy = intNode;
  ASSERT_TRUE(intCopy.isIntegral());
  ASSERT_EQ(4, intCopy.getInt());

  JsonNode floatNode = 4.5;
  JsonNode const floatCopy = floatNode;
  ASSERT_TRUE(floatCopy.isFloating());
  ASSERT_LT(4.0, floatCopy.getDouble());
  ASSERT_GT(5.0, floatCopy.getDouble());

  JsonNode stringNode = "abcd";
  JsonNode const stringCopy = stringNode;
  ASSERT_TRUE(stringCopy.isString());
  ASSERT_EQ("abcd", stringCopy.getString());
}

TEST(JsonNodeTest, moveCtr) {
  JsonNode nullNode = nullptr;
  JsonNode nullCopy = mv(nullNode);
  ASSERT_TRUE(nullCopy.isNull());

  JsonNode boolNode = true;
  JsonNode boolCopy = mv(boolNode);
  ASSERT_TRUE(boolCopy.isBool());
  ASSERT_TRUE(boolCopy.getBool());

  JsonNode intNode = 4;
  JsonNode intCopy = mv(intNode);
  ASSERT_TRUE(intCopy.isIntegral());
  ASSERT_EQ(4, intCopy.getInt());

  JsonNode floatNode = 4.5;
  JsonNode floatCopy = mv(floatNode);
  ASSERT_TRUE(floatCopy.isFloating());
  ASSERT_LT(4.0, floatCopy.getDouble());
  ASSERT_GT(5.0, floatCopy.getDouble());

  JsonNode stringNode = "abcd";
  JsonNode stringCopy = mv(stringNode);
  ASSERT_TRUE(stringCopy.isString());
  ASSERT_EQ("abcd", stringCopy.getString());
}

TEST(JsonNodeTest, nodeFromNull) {
  JsonNode node;

  node = nullptr;
  ASSERT_TRUE(node.isNull());
}

TEST(JsonNodeTest, nodeFromBool) {
  JsonNode node;

  node = true;
  ASSERT_TRUE(node.isBool());
  ASSERT_TRUE(node.getBool());
  node = false;
  ASSERT_TRUE(node.isBool());
  ASSERT_FALSE(node.getBool());
}

TEST(JsonNodeTest, nodeFromIntegral) {
  JsonNode node;

  node = 4;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(4, node.getInt());

  node = 10u;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(10, node.getLong());

  node = -5;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(-5, node.getInt());
}

TEST(JsonNodeTest, nodeFromFloating) {
  JsonNode node;

  node = 3.4;
  ASSERT_TRUE(node.isFloating());
  ASSERT_GT(node.getDouble(), 3.0);
  ASSERT_LT(node.getDouble(), 4.0);
}

TEST(JsonNodeTest, nodeFromString) {
  JsonNode node;

  node = "abc";
  ASSERT_TRUE(node.isString());
  ASSERT_EQ("abc", node.getString());

  node.getString() = "ab";
  ASSERT_EQ("ab", node.getString());
}

TEST(JsonNodeTest, copyOverNull) {
  JsonNode dst;
  dst = nullptr;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverBool) {
  JsonNode dst;
  dst = false;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverInt) {
  JsonNode dst;
  dst = 34;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverFloating) {
  JsonNode dst;
  dst = 3.4;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverString) {
  JsonNode dst;
  dst = 3.4;
  copyOverTest(dst);

  dst = "abc";
  JsonNode directStr;
  directStr = "bcd";
  dst = directStr;
  ASSERT_TRUE(dst.isString());
  ASSERT_EQ("bcd", dst.getString());
}

TEST(JsonNodeTest, isNumber) {
  JsonNode node;
  ASSERT_FALSE(node.isNumber());
  node = 3;
  ASSERT_TRUE(node.isNumber());
  node = 3.4;
  ASSERT_TRUE(node.isNumber());
  node = false;
  ASSERT_FALSE(node.isNumber());
}

TEST(JsonNodeTest, eqNullNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_TRUE(nullNode == nullNode);
  ASSERT_FALSE(nullNode == boolNode0);
  ASSERT_FALSE(nullNode == boolNode1);
  ASSERT_FALSE(nullNode == intNode0);
  ASSERT_FALSE(nullNode == intNode1);
  ASSERT_FALSE(nullNode == floatNode0);
  ASSERT_FALSE(nullNode == floatNode1);
  ASSERT_FALSE(nullNode == stringNode0);
  ASSERT_FALSE(nullNode == stringNode1);

  ASSERT_FALSE(nullNode != nullNode);
  ASSERT_TRUE(nullNode != boolNode0);
  ASSERT_TRUE(nullNode != boolNode1);
  ASSERT_TRUE(nullNode != intNode0);
  ASSERT_TRUE(nullNode != intNode1);
  ASSERT_TRUE(nullNode != floatNode0);
  ASSERT_TRUE(nullNode != floatNode1);
  ASSERT_TRUE(nullNode != stringNode0);
  ASSERT_TRUE(nullNode != stringNode1);
}

TEST(JsonNodeTest, eqBoolNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_FALSE(boolNode0 == nullNode);
  ASSERT_TRUE(boolNode0 == boolNode0);
  ASSERT_FALSE(boolNode0 == boolNode1);
  ASSERT_FALSE(boolNode0 == intNode0);
  ASSERT_FALSE(boolNode0 == intNode1);
  ASSERT_FALSE(boolNode0 == floatNode0);
  ASSERT_FALSE(boolNode0 == floatNode1);
  ASSERT_FALSE(boolNode0 == stringNode0);
  ASSERT_FALSE(boolNode0 == stringNode1);

  ASSERT_TRUE(boolNode0 != nullNode);
  ASSERT_FALSE(boolNode0 != boolNode0);
  ASSERT_TRUE(boolNode0 != boolNode1);
  ASSERT_TRUE(boolNode0 != intNode0);
  ASSERT_TRUE(boolNode0 != intNode1);
  ASSERT_TRUE(boolNode0 != floatNode0);
  ASSERT_TRUE(boolNode0 != floatNode1);
  ASSERT_TRUE(boolNode0 != stringNode0);
  ASSERT_TRUE(boolNode0 != stringNode1);

  ASSERT_FALSE(boolNode1 == nullNode);
  ASSERT_FALSE(boolNode1 == boolNode0);
  ASSERT_TRUE(boolNode1 == boolNode1);
  ASSERT_FALSE(boolNode1 == intNode0);
  ASSERT_FALSE(boolNode1 == intNode1);
  ASSERT_FALSE(boolNode1 == floatNode0);
  ASSERT_FALSE(boolNode1 == floatNode1);
  ASSERT_FALSE(boolNode1 == stringNode0);
  ASSERT_FALSE(boolNode1 == stringNode1);

  ASSERT_TRUE(boolNode1 != nullNode);
  ASSERT_TRUE(boolNode1 != boolNode0);
  ASSERT_FALSE(boolNode1 != boolNode1);
  ASSERT_TRUE(boolNode1 != intNode0);
  ASSERT_TRUE(boolNode1 != intNode1);
  ASSERT_TRUE(boolNode1 != floatNode0);
  ASSERT_TRUE(boolNode1 != floatNode1);
  ASSERT_TRUE(boolNode1 != stringNode0);
  ASSERT_TRUE(boolNode1 != stringNode1);
}

TEST(JsonNodeTest, eqIntNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_FALSE(intNode0 == nullNode);
  ASSERT_FALSE(intNode0 == boolNode0);
  ASSERT_FALSE(intNode0 == boolNode1);
  ASSERT_TRUE(intNode0 == intNode0);
  ASSERT_FALSE(intNode0 == intNode1);
  ASSERT_FALSE(intNode0 == floatNode0);
  ASSERT_FALSE(intNode0 == floatNode1);
  ASSERT_FALSE(intNode0 == stringNode0);
  ASSERT_FALSE(intNode0 == stringNode1);

  ASSERT_TRUE(intNode0 != nullNode);
  ASSERT_TRUE(intNode0 != boolNode0);
  ASSERT_TRUE(intNode0 != boolNode1);
  ASSERT_FALSE(intNode0 != intNode0);
  ASSERT_TRUE(intNode0 != intNode1);
  ASSERT_TRUE(intNode0 != floatNode0);
  ASSERT_TRUE(intNode0 != floatNode1);
  ASSERT_TRUE(intNode0 != stringNode0);
  ASSERT_TRUE(intNode0 != stringNode1);

  ASSERT_FALSE(intNode1 == nullNode);
  ASSERT_FALSE(intNode1 == boolNode0);
  ASSERT_FALSE(intNode1 == boolNode1);
  ASSERT_FALSE(intNode1 == intNode0);
  ASSERT_TRUE(intNode1 == intNode1);
  ASSERT_FALSE(intNode1 == floatNode0);
  ASSERT_FALSE(intNode1 == floatNode1);
  ASSERT_FALSE(intNode1 == stringNode0);
  ASSERT_FALSE(intNode1 == stringNode1);

  ASSERT_TRUE(intNode1 != nullNode);
  ASSERT_TRUE(intNode1 != boolNode0);
  ASSERT_TRUE(intNode1 != boolNode1);
  ASSERT_TRUE(intNode1 != intNode0);
  ASSERT_FALSE(intNode1 != intNode1);
  ASSERT_TRUE(intNode1 != floatNode0);
  ASSERT_TRUE(intNode1 != floatNode1);
  ASSERT_TRUE(intNode1 != stringNode0);
  ASSERT_TRUE(intNode1 != stringNode1);
}

TEST(JsonNodeTest, eqStrNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_FALSE(stringNode0 == nullNode);
  ASSERT_FALSE(stringNode0 == boolNode0);
  ASSERT_FALSE(stringNode0 == boolNode1);
  ASSERT_FALSE(stringNode0 == intNode0);
  ASSERT_FALSE(stringNode0 == intNode1);
  ASSERT_FALSE(stringNode0 == floatNode0);
  ASSERT_FALSE(stringNode0 == floatNode1);
  ASSERT_TRUE(stringNode0 == stringNode0);
  ASSERT_FALSE(stringNode0 == stringNode1);

  ASSERT_TRUE(stringNode0 != nullNode);
  ASSERT_TRUE(stringNode0 != boolNode0);
  ASSERT_TRUE(stringNode0 != boolNode1);
  ASSERT_TRUE(stringNode0 != intNode0);
  ASSERT_TRUE(stringNode0 != intNode1);
  ASSERT_TRUE(stringNode0 != floatNode0);
  ASSERT_TRUE(stringNode0 != floatNode1);
  ASSERT_FALSE(stringNode0 != stringNode0);
  ASSERT_TRUE(stringNode0 != stringNode1);

  ASSERT_FALSE(stringNode1 == nullNode);
  ASSERT_FALSE(stringNode1 == boolNode0);
  ASSERT_FALSE(stringNode1 == boolNode1);
  ASSERT_FALSE(stringNode1 == intNode0);
  ASSERT_FALSE(stringNode1 == intNode1);
  ASSERT_FALSE(stringNode1 == floatNode0);
  ASSERT_FALSE(stringNode1 == floatNode1);
  ASSERT_FALSE(stringNode1 == stringNode0);
  ASSERT_TRUE(stringNode1 == stringNode1);

  ASSERT_TRUE(stringNode1 != nullNode);
  ASSERT_TRUE(stringNode1 != boolNode0);
  ASSERT_TRUE(stringNode1 != boolNode1);
  ASSERT_TRUE(stringNode1 != intNode0);
  ASSERT_TRUE(stringNode1 != intNode1);
  ASSERT_TRUE(stringNode1 != floatNode0);
  ASSERT_TRUE(stringNode1 != floatNode1);
  ASSERT_TRUE(stringNode1 != stringNode0);
  ASSERT_FALSE(stringNode1 != stringNode1);
}

TEST(JsonNodeTest, directNullComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_TRUE(nullNode == nullptr);
  ASSERT_FALSE(boolNode == nullptr);
  ASSERT_FALSE(intNode == nullptr);
  ASSERT_FALSE(floatNode == nullptr);
  ASSERT_FALSE(strNode == nullptr);

  ASSERT_TRUE(nullptr == nullNode);
  ASSERT_FALSE(nullptr == boolNode);
  ASSERT_FALSE(nullptr == intNode);
  ASSERT_FALSE(nullptr == floatNode);
  ASSERT_FALSE(nullptr == strNode);

  ASSERT_FALSE(nullNode != nullptr);
  ASSERT_TRUE(boolNode != nullptr);
  ASSERT_TRUE(intNode != nullptr);
  ASSERT_TRUE(floatNode != nullptr);
  ASSERT_TRUE(strNode != nullptr);

  ASSERT_FALSE(nullptr != nullNode);
  ASSERT_TRUE(nullptr != boolNode);
  ASSERT_TRUE(nullptr != intNode);
  ASSERT_TRUE(nullptr != floatNode);
  ASSERT_TRUE(nullptr != strNode);
}

TEST(JsonNodeTest, directBoolComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == false);
  ASSERT_FALSE(nullNode == true);
  ASSERT_FALSE(boolNode0 == true);
  ASSERT_TRUE(boolNode0 == false);
  ASSERT_FALSE(boolNode1 == false);
  ASSERT_TRUE(boolNode1 == true);
  ASSERT_FALSE(intNode == false);
  ASSERT_FALSE(intNode == true);
  ASSERT_FALSE(floatNode == false);
  ASSERT_FALSE(floatNode == true);
  ASSERT_FALSE(strNode == false);
  ASSERT_FALSE(strNode == true);

  ASSERT_FALSE(false == nullNode);
  ASSERT_FALSE(true == nullNode);
  ASSERT_FALSE(true == boolNode0);
  ASSERT_TRUE(false == boolNode0);
  ASSERT_FALSE(false == boolNode1);
  ASSERT_TRUE(true == boolNode1);
  ASSERT_FALSE(false == intNode);
  ASSERT_FALSE(true == intNode);
  ASSERT_FALSE(false == floatNode);
  ASSERT_FALSE(true == floatNode);
  ASSERT_FALSE(false == strNode);
  ASSERT_FALSE(true == strNode);

  ASSERT_TRUE(nullNode != false);
  ASSERT_TRUE(nullNode != true);
  ASSERT_TRUE(boolNode0 != true);
  ASSERT_FALSE(boolNode0 != false);
  ASSERT_TRUE(boolNode1 != false);
  ASSERT_FALSE(boolNode1 != true);
  ASSERT_TRUE(intNode != false);
  ASSERT_TRUE(intNode != true);
  ASSERT_TRUE(floatNode != false);
  ASSERT_TRUE(floatNode != true);
  ASSERT_TRUE(strNode != false);
  ASSERT_TRUE(strNode != true);

  ASSERT_TRUE(false != nullNode);
  ASSERT_TRUE(true != nullNode);
  ASSERT_TRUE(true != boolNode0);
  ASSERT_FALSE(false != boolNode0);
  ASSERT_TRUE(false != boolNode1);
  ASSERT_FALSE(true != boolNode1);
  ASSERT_TRUE(false != intNode);
  ASSERT_TRUE(true != intNode);
  ASSERT_TRUE(false != floatNode);
  ASSERT_TRUE(true != floatNode);
  ASSERT_TRUE(false != strNode);
  ASSERT_TRUE(true != strNode);
}

TEST(JsonNodeTest, directIntComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == 4);
  ASSERT_FALSE(boolNode == 4);
  ASSERT_FALSE(intNode == 5);
  ASSERT_TRUE(intNode == 4);
  ASSERT_FALSE(floatNode == 4);
  ASSERT_FALSE(strNode == 4);

  ASSERT_FALSE(4 == nullNode);
  ASSERT_FALSE(4 == boolNode);
  ASSERT_FALSE(5 == intNode);
  ASSERT_TRUE(4 == intNode);
  ASSERT_FALSE(4 == floatNode);
  ASSERT_FALSE(4 == strNode);

  ASSERT_TRUE(nullNode != 4);
  ASSERT_TRUE(boolNode != 4);
  ASSERT_TRUE(intNode != 5);
  ASSERT_FALSE(intNode != 4);
  ASSERT_TRUE(floatNode != 4);
  ASSERT_TRUE(strNode != 4);

  ASSERT_TRUE(4 != nullNode);
  ASSERT_TRUE(4 != boolNode);
  ASSERT_TRUE(5 != intNode);
  ASSERT_FALSE(4 != intNode);
  ASSERT_TRUE(4 != floatNode);
  ASSERT_TRUE(4 != strNode);
}

TEST(JsonNodeTest, directFloatComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == 3.4);
  ASSERT_FALSE(boolNode == 3.4);
  ASSERT_FALSE(intNode == 3.4);
  ASSERT_FALSE(floatNode == 4.5);
  ASSERT_TRUE(floatNode == 3.4);
  ASSERT_FALSE(strNode == 3.4);

  ASSERT_FALSE(3.4 == nullNode);
  ASSERT_FALSE(3.4 == boolNode);
  ASSERT_FALSE(3.4 == intNode);
  ASSERT_FALSE(4.5 == floatNode);
  ASSERT_TRUE(3.4 == floatNode);
  ASSERT_FALSE(3.4 == strNode);

  ASSERT_TRUE(nullNode != 3.4);
  ASSERT_TRUE(boolNode != 3.4);
  ASSERT_TRUE(intNode != 3.4);
  ASSERT_TRUE(floatNode != 4.5);
  ASSERT_FALSE(floatNode != 3.4);
  ASSERT_TRUE(strNode != 3.4);

  ASSERT_TRUE(3.4 != nullNode);
  ASSERT_TRUE(3.4 != boolNode);
  ASSERT_TRUE(3.4 != intNode);
  ASSERT_TRUE(4.5 != floatNode);
  ASSERT_FALSE(3.4 != floatNode);
  ASSERT_TRUE(3.4 != strNode);
}

TEST(JsonNodeTest, directStrComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == "abc");
  ASSERT_FALSE(boolNode == "abc");
  ASSERT_FALSE(intNode == "abc");
  ASSERT_FALSE(floatNode == "abc");
  ASSERT_FALSE(strNode == "bcd");
  ASSERT_TRUE(strNode == "abc");

  ASSERT_FALSE("abc" == nullNode);
  ASSERT_FALSE("abc" == boolNode);
  ASSERT_FALSE("abc" == intNode);
  ASSERT_FALSE("abc" == floatNode);
  ASSERT_FALSE("bcd" == strNode);
  ASSERT_TRUE("abc" == strNode);

  ASSERT_TRUE(nullNode != "abc");
  ASSERT_TRUE(boolNode != "abc");
  ASSERT_TRUE(intNode != "abc");
  ASSERT_TRUE(floatNode != "abc");
  ASSERT_TRUE(strNode != "bcd");
  ASSERT_FALSE(strNode != "abc");

  ASSERT_TRUE("abc" != nullNode);
  ASSERT_TRUE("abc" != boolNode);
  ASSERT_TRUE("abc" != intNode);
  ASSERT_TRUE("abc" != floatNode);
  ASSERT_TRUE("bcd" != strNode);
  ASSERT_FALSE("abc" != strNode);
}

TEST(JsonNodeTest, formatNull) {
  ASSERT_EQ("null", cds::format("{}", JsonNode(nullptr)));
  ASSERT_EQ("null", cds::format("{:p}", JsonNode(nullptr)));
  ASSERT_EQ("NULL", cds::format("{:P}", JsonNode(nullptr)));
}

TEST(JsonNodeTest, formatBool) {
  ASSERT_EQ("false", cds::format("{}", JsonNode(false)));
  ASSERT_EQ("true", cds::format("{}", JsonNode(true)));
  ASSERT_EQ("false", cds::format("{:s}", JsonNode(false)));
  ASSERT_EQ("true", cds::format("{:s}", JsonNode(true)));
}

TEST(JsonNodeTest, formatInt) {
  ASSERT_EQ("20", cds::format("{}", JsonNode(20)));
  ASSERT_EQ("20", cds::format("{}", JsonNode(20)));
  ASSERT_EQ("0x14", cds::format("{:#x}", JsonNode(20)));
  ASSERT_EQ("0X14", cds::format("{:#X}", JsonNode(20)));
}

TEST(JsonNodeTest, formatFloating) {
  ASSERT_EQ("3.4", cds::format("{}", JsonNode(3.4)));
  ASSERT_EQ("3.4", cds::format("{}", JsonNode(3.4)));
  ASSERT_EQ("3.400000e+00", cds::format("{:e}", JsonNode(3.4)));
  ASSERT_EQ("3.400000E+00", cds::format("{:E}", JsonNode(3.4)));
}

TEST(JsonNodeTest, formatString) {
  ASSERT_EQ("abc", cds::format("{}", JsonNode("abc")));
  ASSERT_EQ("a\tbc", cds::format("{}", JsonNode("a\tbc")));
  ASSERT_EQ("abc", cds::format("{:?}", JsonNode("abc")));
  ASSERT_EQ("a\\tbc", cds::format("{:?}", JsonNode("a\tbc")));
}
