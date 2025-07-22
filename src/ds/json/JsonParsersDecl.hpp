//
// Created by loghin on 7/6/25.
//

#ifndef CDS_DS_JSON_PARSERS_DECL_HPP
#define CDS_DS_JSON_PARSERS_DECL_HPP
#pragma once

#include <cds/Optional>
#include <cds/StringView>
#include <cds/Tuple>

#include "JsonTokens.hpp"

#include "JsonNodeDecl.hpp"
#include "JsonArrayDecl.hpp"
#include "JsonObjectDecl.hpp"

namespace cds {
namespace json {
namespace impl {
using cds::impl::BaseString;
using cds::impl::BaseStringView;

enum class JsonParseError {
  None,
  ErrorNumberNoIntegralBeforeFraction,
  ErrorNumberInvalid,
  ErrorNumberNoDigitsAfterFraction,
  ErrorStringWithoutStartingQuote,
  ErrorStringWithoutEndingQuote,
  ErrorStringInvalidEscapeSequence,
  ErrorUTFCodePointTooShort,
  ErrorUTFCodePointInvalid,
  ErrorValueInvalid,
  ErrorArrayWithoutStartingBracket,
  ErrorArrayWithoutEndingBracket,
  ErrorArrayWithoutElementSeparator,
  ErrorObjectWithoutStartingBrace,
  ErrorObjectWithoutEndingBrace,
  ErrorObjectWithoutMemberSeparator,
  ErrorObjectMemberWithoutKeyValueSeparator,
};

struct JsonParseOptions {
  bool readPlusSign {false};
  bool readNonBase10Integrals {false};
  bool readFloatingStartingWithFraction {false};
};

template <typename /* CharType */ = char> struct CodePointParser;

template <> struct CodePointParser<char> {
  CDS_ATTR(constexpr(20)) auto operator()(BaseString<char>& dst, U16 codePoint)
      const noexcept -> void {
    if (codePoint == (codePoint & static_cast<U16>(0x007fu))) {
      dst += static_cast<char>(codePoint & static_cast<U16>(0x007fu));
    } else if (codePoint == (codePoint & static_cast<U16>(0x07ffu))) {
      dst += static_cast<char>(0xc0u | (static_cast<U16>(codePoint >> 6u) & static_cast<U16>(0x001fu)));
      dst += static_cast<char>(0x80u | (codePoint & static_cast<U16>(0x03fu)));
    } else {
      dst += static_cast<char>(0xe0u | (static_cast<U16>(codePoint >> 12u) & static_cast<U16>(0x000fu)));
      dst += static_cast<char>(0x80u | (static_cast<U16>(codePoint >> 6u) & static_cast<U16>(0x003fu)));
      dst += static_cast<char>(0x80u | (codePoint & static_cast<U16>(0x003fu)));
    }
  }
};

template <typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseErrorAsString(JsonParseError err, BaseStringView<C> loc) noexcept -> String {
  auto const compose = [loc](StringView expectation) noexcept -> String {
    return String{expectation} + ", received '" + loc + "'";
  };

  switch (err) {
    case JsonParseError::None:
      return "";
    case JsonParseError::ErrorNumberNoIntegralBeforeFraction:
      return compose("Expected integral before '.'");
    case JsonParseError::ErrorNumberInvalid:
      return compose("Expected number");
    case JsonParseError::ErrorNumberNoDigitsAfterFraction:
      return compose("Expected fraction digits after '.'");
    case JsonParseError::ErrorStringWithoutStartingQuote:
      return compose("Expected '\"'");
    case JsonParseError::ErrorStringWithoutEndingQuote:
      return compose("Unterminated string, expected '\"'");
    case JsonParseError::ErrorUTFCodePointTooShort:
    case JsonParseError::ErrorUTFCodePointInvalid:
      return compose("Expected '\\u<digit><digit><digit><digit>'");
    case JsonParseError::ErrorValueInvalid:
      return compose("Expected '<value>'");
    case JsonParseError::ErrorArrayWithoutStartingBracket:
      return compose("Expected array starting bracket '['");
    case JsonParseError::ErrorArrayWithoutEndingBracket:
      return compose("Unterminated array, expected ']'");
    case JsonParseError::ErrorArrayWithoutElementSeparator:
      return compose("Expected array element separator ','");
    case JsonParseError::ErrorObjectWithoutStartingBrace:
      return compose("Expected object starting brace '{'");
    case JsonParseError::ErrorObjectWithoutEndingBrace:
      return compose("Unterminated object, expected '}'");
    case JsonParseError::ErrorObjectWithoutMemberSeparator:
      return compose("Expected object member separator ','");
    case JsonParseError::ErrorObjectMemberWithoutKeyValueSeparator:
      return compose("Expected object member key-value separator ':'");
    case JsonParseError::ErrorStringInvalidEscapeSequence:
      return compose("Invalid escape sequence after '\\'");
    default:
      assert(false && "Unhandled error case");
      cds::impl::unreachable();
  }
}

class JsonParseException : public RuntimeException {
public:
  template <typename C> JsonParseException(JsonParseError err, BaseStringView<C> loc) noexcept :
      RuntimeException(parseErrorAsString(err, loc)) {}
};

template <typename C> CDS_ATTR(constexpr(20))
auto throwIfErroneous(Tuple<BaseStringView<C>, JsonParseError> const& locAndErr) CDS_ATTR(noexcept(false)) -> void {
  auto const err = cds::get<1>(locAndErr);
  if (err == JsonParseError::None) {
    return;
  }

  auto const loc = cds::get<0>(locAndErr);
  auto const maxTextLength = 16;
  auto const truncated = loc.length() > maxTextLength;
  auto errLoc = truncated ? (String{loc.sub(0, maxTextLength)} + "...") : String{loc};
  throw JsonParseException(err, BaseStringView<C>{errLoc});
}

template <typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonString(JsonString& dst, BaseStringView<C> src, JsonParseOptions const& options = {}) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError> {
  using U = typename BaseStringView<C>::Utils;
  using Tok = JsonTokens<C>;

  ignore = options;
  auto it = src.begin();
  auto end = src.end();
  if (it == end || *it != Tok::stringQuote) {
    return {src, JsonParseError::ErrorStringWithoutStartingQuote};
  }

  JsonString value;
  ++it;
  for (auto escaped = false; it != end && (escaped || *it != Tok::stringQuote); ++it) {
    if (!escaped && *it == Tok::reverseSolidus) {
      escaped = true;
      continue;
    }

    if (escaped) {
      switch (*it) {
        case Tok::stringQuote:
        case Tok::reverseSolidus:
        case Tok::solidus:
          value += *it;
          break;
        case Tok::escapedBackspace:
          value += Tok::backspace;
          break;
        case Tok::escapedFormFeed:
          value += Tok::formFeed;
          break;
        case Tok::escapedLineFeed:
          value += Tok::lineFeed;
          break;
        case Tok::escapedCarriageReturn:
          value += Tok::carriageReturn;
          break;
        case Tok::escapedHorizontalTab:
          value += Tok::horizontalTab;
          break;
        case Tok::escapedUTF: {
          ++it;
          if (it + 4 > end) {
            return {src, JsonParseError::ErrorUTFCodePointTooShort};
          }
          // going with default char here, since JsonString is encoded in default char, therefore utf-8
          C const* after;
          U16 codePoint;
          auto successful = U::readInt(&*it, 4, &after, &codePoint, 16);
          if (!successful || after != &*it + 4) {
            return {src, JsonParseError::ErrorUTFCodePointInvalid};
          }

          CodePointParser<>{}(value, codePoint);
          it = it + 3;
          break;
        }
        default:
          return {src, JsonParseError::ErrorStringInvalidEscapeSequence};
      }

      escaped = false;
      continue;
    }

    value += *it;
  }

  dst = mv(value);
  if (it == end || *it != Tok::stringQuote) {
    return {src, JsonParseError::ErrorStringWithoutEndingQuote};
  }

  ++it;
  return {BaseStringView<C>{&*it, end - it}.ltrim(), JsonParseError::None};
};

template <typename B, typename A, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonNode(JsonNodeBase<B, A>& dst, BaseStringView<C> src, JsonParseOptions const& options = {}) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError>;

template <typename B, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonArray(JsonArrayBase<B>& dst, BaseStringView<C> src, JsonParseOptions const& options = {}) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError>;

template <typename B, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonObject(JsonObjectBase<B>& dst, BaseStringView<C> src, JsonParseOptions const& options = {}) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError>;
} // namespace impl

using impl::JsonParseError;
using impl::JsonParseException;
using impl::JsonParseOptions;

template <typename B> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonArray(impl::JsonArrayBase<B>& dst, impl::BaseStringView<char> src, JsonParseOptions options = {}) noexcept
    -> Tuple<impl::BaseStringView<char>, JsonParseError> {
  return impl::parseJsonArray(dst, src, options);
};

CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonArray(impl::BaseStringView<char> src, JsonParseOptions options = {}) noexcept
    -> Tuple<JsonArray, impl::BaseStringView<char>, JsonParseError> {
  JsonArray arr;
  auto result = impl::parseJsonArray(arr, src, options);
  return {mv(arr), cds::get<0>(result), cds::get<1>(result)};
};

template <typename B> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonObject(impl::JsonObjectBase<B>& dst, impl::BaseStringView<char> src, JsonParseOptions options = {}) noexcept
    -> Tuple<impl::BaseStringView<char>, JsonParseError> {
  return impl::parseJsonObject(dst, src, options);
};

CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonObject(impl::BaseStringView<char> src, JsonParseOptions options = {}) noexcept
    -> Tuple<JsonObject, impl::BaseStringView<char>, JsonParseError> {
  JsonObject obj;
  auto result = impl::parseJsonObject(obj, src, options);
  return {mv(obj), cds::get<0>(result), cds::get<1>(result)};
};

inline namespace literals {
CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator ""_json(char const* string, std::size_t length) CDS_ATTR(noexcept(false))
    -> JsonObject {
  return JsonObject(StringView{string, length});
}

CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator ""_json_array(char const* string, std::size_t length) CDS_ATTR(noexcept(false))
    -> JsonArray {
  return JsonArray(StringView{string, length});
}
} // inline namespace literals
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PARSERS_DECL_HPP
