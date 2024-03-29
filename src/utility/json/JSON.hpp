// 
// Created by loghin on 28.02.2021.
//

#ifndef __CDS_JSON_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_JSON_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

#include <CDS/meta/TypeTraits>              // NOLINT(llvm-include-order)
#include <CDS/LinkedHashMap>
#include <CDS/Array>
#include <CDS/exception/FormatException>
#include <CDS/exception/TypeException>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

namespace filesystem {
class Path;
} // namespace filesystem

namespace json {

class JsonElement;
class JsonObject;
class JsonArray;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __JsonBaseMap             = cds::Map <String, JsonElement>;           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __JsonBaseArray           = cds::Array <JsonElement>;                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

using __JsonMapImplementation   = cds::LinkedHashMap <String, JsonElement>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __JsonArrayImplementation = cds::Array <JsonElement>;                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

enum class __JsonElementType {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Object,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Array,                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_String,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Bool,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Long,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Int       = __jet_Long,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Double,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Float     = __jet_Double,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __jet_Invalid                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

__CDS_cpplang_ConstexprMultipleReturn auto __jet_toString( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __JsonElementType type
) noexcept -> StringLiteral;

template <typename __BaseType>                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __JsonElementAdapterPropertiesHelper { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool const __adaptable = false;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::uint8> {                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::uint16> {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::uint32> {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::uint64> {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::sint8> {                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::sint16> {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::sint32> {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <cds::sint64> {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Long; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = long long;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <float> {                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Double; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = double;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <double> {                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Double; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = double;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <bool> {                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Bool; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = bool;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <StringLiteral> {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_String; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = String;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <StringView> {                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_String; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = String;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <String> {                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_String; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = String;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <std::string> {                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_String; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = String;                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <JsonArray> {                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Array;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = JsonArray;                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <> struct __JsonElementAdapterPropertiesHelper <JsonObject> {                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static bool               const __adaptable   = true;                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static __JsonElementType  const __type        = __JsonElementType::__jet_Object; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using                                     __AdaptedType = JsonObject;                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <typename __ToDecay> struct __JsonElementAdapterProperties : __JsonElementAdapterPropertiesHelper <cds::meta::Decay <__ToDecay>> {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __Element, typename __Decayed = cds::meta::Decay <__Element>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __JsonElementPrimitiveAdaptable :                                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::And <
        cds::meta::BoolConstant <__JsonElementAdapterProperties <__Decayed>::__adaptable>,
        cds::meta::IsFundamental <__Decayed>,
        cds::meta::Or <
            cds::meta::Not <cds::meta::IsSame <__Decayed, StringLiteral>>,
            cds::meta::IsBasicPointer <__Decayed>
        >
    > {};

template <typename __Element, typename __Decayed = cds::meta::Decay <__Element>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __JsonElementAdaptable :                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::And <
        cds::meta::BoolConstant <__JsonElementAdapterProperties <__Decayed>::__adaptable>,
        cds::meta::Not <cds::meta::IsFundamental <__Decayed>>,
        cds::meta::Not <
            cds::meta::And <
                cds::meta::Not <cds::meta::IsSame <__Decayed, StringLiteral>>,
                cds::meta::IsBasicPointer <__Decayed>
             >
        >
    > {};
} // namespace __impl
} // namespace __hidden

class JsonElement : public Object {
public:
  JsonElement() noexcept = delete;
  JsonElement(JsonElement const& element) noexcept(false);
  JsonElement(JsonElement&& element) noexcept;

  template <
      typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <__hidden::__impl::__JsonElementPrimitiveAdaptable <__Element>::value> = 0
  > __CDS_Implicit JsonElement(__Element value) noexcept(false); // NOLINT(*-explicit-*) 

  template <
      typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <__hidden::__impl::__JsonElementAdaptable <__Element>::value> = 0
  > __CDS_Implicit JsonElement(__Element&& value) noexcept(false); // NOLINT(*-explicit-*, bugprone-forwarding-reference-overload)

  ~JsonElement() noexcept override;

  auto operator =(JsonElement const& element) noexcept(false) -> JsonElement&;
  auto operator =(JsonElement&& element) noexcept -> JsonElement&;
  
  template <
      typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <__hidden::__impl::__JsonElementPrimitiveAdaptable <__Element>::value> = 0
  > auto operator =(__Element value) noexcept(false) -> JsonElement&;

  template <
      typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <__hidden::__impl::__JsonElementAdaptable <__Element>::value> = 0
  > auto operator =(__Element&& value) noexcept(false) -> JsonElement&;

  __CDS_NoDiscard auto toString() const noexcept -> String override;
  __CDS_NoDiscard auto hash() const noexcept -> Size override;
  __CDS_NoDiscard auto equals(Object const& object) const noexcept -> bool override;

  __CDS_NoDiscard auto getInt() const noexcept(false) -> int;
  __CDS_NoDiscard auto getLong() const noexcept(false) -> long long int;
  __CDS_NoDiscard auto getFloat() const noexcept(false) -> float;
  __CDS_NoDiscard auto getDouble() const noexcept(false) -> double;
  __CDS_NoDiscard auto getBoolean() const noexcept(false) -> bool;
  __CDS_NoDiscard auto getString() const noexcept(false) -> String const&;
  __CDS_NoDiscard auto getJson() const noexcept(false) -> JsonObject const&;
  __CDS_NoDiscard auto getArray() const noexcept(false) -> JsonArray const&;
  __CDS_NoDiscard auto getString() noexcept(false) -> String&;
  __CDS_NoDiscard auto getJson() noexcept(false) -> JsonObject&;
  __CDS_NoDiscard auto getArray() noexcept(false) -> JsonArray&;

  __CDS_NoDiscard constexpr auto isInt() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_Int>(); 
  }

  __CDS_NoDiscard constexpr auto isLong() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_Long>(); 
  }

  __CDS_NoDiscard constexpr auto isFloat() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_Float>(); 
  }

  __CDS_NoDiscard constexpr auto isDouble() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_Double>(); 
  }

  __CDS_NoDiscard constexpr auto isBoolean() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_Bool>(); 
  }

  __CDS_NoDiscard constexpr auto isString() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_String>(); 
  }

  __CDS_NoDiscard constexpr auto isJson() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_Object>(); 
  }

  __CDS_NoDiscard constexpr auto isArray() const noexcept -> bool { 
    return this->is <__hidden::__impl::__JsonElementType::__jet_Array>(); 
  }

  [[nodiscard]] constexpr auto operator==(JsonElement const& obj) const noexcept -> bool;

private:
  friend class JsonArray;
  friend class JsonObject;
 
  union __GenericData {   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool          bValue;
    long long int iValue;
    double        dValue;
    cds::Object*  pObject;
  };
   
  __hidden::__impl::__JsonElementType                                 _type {__hidden::__impl::__JsonElementType::__jet_Invalid};
  cds::__hidden::__impl::__allocation::__RawContainer <__GenericData> _data;

  auto copyData(__GenericData const& genericData) noexcept(false) -> void;
  auto moveData(__GenericData& genericData) noexcept -> void;
  auto clearData() noexcept -> void;
  
  template <__hidden::__impl::__JsonElementType __type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto is() const noexcept -> bool { 
    return this->_type == __type; 
  }
};


class JsonObject : public __hidden::__impl::__JsonMapImplementation {
private:
  using __Base = __hidden::__impl::__JsonMapImplementation;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

public:
  constexpr JsonObject() noexcept;
  JsonObject(JsonObject const& object) noexcept(false);
  constexpr JsonObject(JsonObject&& object) noexcept;
  __CDS_Implicit JsonObject(Map <String, JsonElement> const& map) noexcept(false); // NOLINT(*-explicit-*) 
  __CDS_Explicit JsonObject(StringView asString) noexcept(false);
  ~JsonObject() noexcept override;

  auto operator =(JsonObject const& object) noexcept(false) -> JsonObject&;
  auto operator =(JsonObject&& object) noexcept -> JsonObject&;
  auto operator =(Map <String, JsonElement> const& map) noexcept(false) -> JsonObject&;
  
  template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto put(StringView label, __Element&& value) noexcept -> JsonObject&;

  auto get(StringView label) noexcept(false) -> JsonElement&;
  auto get(StringView label) const noexcept(false) -> JsonElement const&;
  auto operator [](StringView label) noexcept(false) -> JsonElement&;
  auto operator [](StringView label) const noexcept(false) -> JsonElement const&;
  __CDS_NoDiscard auto getBoolean(StringView label) const noexcept(false) -> bool;
  __CDS_NoDiscard auto getInt(StringView label) const noexcept(false) -> int;
  __CDS_NoDiscard auto getLong(StringView label) const noexcept(false) -> long long int;
  __CDS_NoDiscard auto getFloat(StringView label) const noexcept(false) -> float;
  __CDS_NoDiscard auto getDouble(StringView label) const noexcept(false) -> double;
  __CDS_NoDiscard auto getString(StringView label) const noexcept(false) -> String const&;
  __CDS_NoDiscard auto getArray(StringView label) const noexcept(false) -> JsonArray const&;
  __CDS_NoDiscard auto getJson(StringView label) const noexcept(false) -> JsonObject const&;
  __CDS_NoDiscard auto getString(StringView label) noexcept(false) -> String&;
  __CDS_NoDiscard auto getArray(StringView label) noexcept(false) -> JsonArray&;
  __CDS_NoDiscard auto getJson(StringView label) noexcept(false) -> JsonObject&;
  
  __CDS_NoDiscard auto toString() const noexcept -> String override;

  [[nodiscard]] constexpr auto operator==(JsonObject const& obj) const noexcept -> bool {
    return *static_cast<__Base const*>(this) == *static_cast<__Base const*>(&obj);
  }
};


class JsonArray : public __hidden::__impl::__JsonArrayImplementation {
private:
  using __Base = __hidden::__impl::__JsonArrayImplementation; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

public:
  constexpr JsonArray() noexcept;
  JsonArray(JsonArray const &array) noexcept(false);
  constexpr JsonArray(JsonArray&& array) noexcept;
  __CDS_Implicit JsonArray(List <JsonElement> const& list) noexcept(false); // NOLINT(*-explicit-*) 
  __CDS_Explicit JsonArray(StringView asString) noexcept(false);
  ~JsonArray() noexcept override;

  auto operator =(JsonArray const& array) noexcept(false) -> JsonArray&;
  auto operator =(JsonArray&& array) noexcept -> JsonArray&;
  auto operator =(List <JsonElement> const& list) noexcept(false) -> JsonArray&;
 
  template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pushBack(__Element&& value) noexcept(false) -> JsonArray&;

  template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pushFront(__Element&& value) noexcept(false) -> JsonArray&;
  
  __CDS_NoDiscard auto getBoolean(Index index) const noexcept(false) -> bool;
  __CDS_NoDiscard auto getInt(Index index) const noexcept(false) -> int;
  __CDS_NoDiscard auto getLong(Index index) const noexcept(false) -> long long int;
  __CDS_NoDiscard auto getFloat(Index index) const noexcept(false) -> float;
  __CDS_NoDiscard auto getDouble(Index index) const noexcept(false) -> double;
  __CDS_NoDiscard auto getString(Index index) const noexcept(false) -> String const&;
  __CDS_NoDiscard auto getArray(Index index) const noexcept(false) -> JsonArray const&;
  __CDS_NoDiscard auto getJson(Index index) const noexcept(false) -> JsonObject const&;
  __CDS_NoDiscard auto getString(Index index) noexcept(false) -> String&;
  __CDS_NoDiscard auto getArray(Index index) noexcept(false) -> JsonArray&;
  __CDS_NoDiscard auto getJson(Index index) noexcept(false) -> JsonObject&;

  [[nodiscard]] constexpr auto operator==(JsonArray const& obj) const noexcept -> bool {
    return *static_cast<__Base const*>(this) == *static_cast<__Base const*>(&obj);
  }
};

__CDS_NoDiscard auto parseJson(StringView asString) noexcept(false) -> JsonObject;
__CDS_NoDiscard auto parseJsonArray(StringView asString) noexcept(false) -> JsonArray;
__CDS_NoDiscard auto dump(JsonObject const& object, Size indent = 4U) noexcept -> String;
__CDS_NoDiscard auto dump(JsonArray const& object, Size indent = 4U) noexcept -> String;

__CDS_NoDiscard auto loadJson(filesystem::Path const& path) noexcept(false) -> JsonObject;
__CDS_NoDiscard auto loadJsonArray(filesystem::Path const& path) noexcept(false) -> JsonArray;

class JsonFormatException : public FormatException { // NOLINT(*-special-member-functions)
public:
  JsonFormatException() noexcept : FormatException( "JSON Input Format Exception" ) {}
  explicit JsonFormatException(StringView message) noexcept : FormatException(message) {}
  ~JsonFormatException() noexcept override = default;

  explicit JsonFormatException(
      char expected,
      char after,
      char received
  ) noexcept : FormatException(
      String::f(
          "JSON Input Format Exception : Expected '%c' after '%c', got '%c'",
          expected, after, received
      )
  ) {

  }


  explicit JsonFormatException(
      char        expected,
      StringView  after,
      char        received
  ) noexcept : FormatException(
      String::f(
          "JSON Input Format Exception : Expected '%c' after '%s', got '%c'",
          expected, after.cStr(), received
      )
  ) {

  }

  explicit JsonFormatException(
      StringView  expected,
      StringView  after,
      StringView  reason
  ) noexcept : FormatException(
      String::f(
          "JSON Input Format Exception : Expected '%s' after '%s', problem - '%s'",
          expected.cStr(), after.cStr(), reason.cStr()
      )
  ) {

  }
};
} // namespace json 
} // namespace cds 

#include "json/impl/JSON.hpp"               // NOLINT(llvm-include-order) 
#include "../../shared/util/JsonLoad.hpp"

#endif // __CDS_JSON_HPP__ 
