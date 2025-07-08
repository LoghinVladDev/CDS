//
// Created by loghin on 7/6/25.
//

#ifndef CDS_DS_JSON_PARSERS_DECL_HPP
#define CDS_DS_JSON_PARSERS_DECL_HPP
#pragma once

#include <cds/Optional>
#include <cds/StringView>
#include <cds/Tuple>

#include "JsonNodeDecl.hpp"
#include "JsonArrayDecl.hpp"
#include "JsonObjectDecl.hpp"

namespace cds {
namespace json {
namespace impl {
using cds::impl::BaseString;
using cds::impl::BaseStringView;

template <typename /* CharType */> struct JsonTokens;

template <> struct JsonTokens<char> {
  static char constexpr stringQuote = '"';
  static char constexpr reverseSolidus = '\\';
  static char constexpr solidus = '/';
  static char constexpr escapedBackspace = 'b';
  static char constexpr escapedFormFeed = 'f';
  static char constexpr escapedLineFeed = 'n';
  static char constexpr escapedCarriageReturn = 'r';
  static char constexpr escapedHorizontalTab = 't';
  static char constexpr escapedUTF = 'u';
  static char constexpr backspace = '\b';
  static char constexpr formFeed = '\f';
  static char constexpr lineFeed = '\n';
  static char constexpr carriageReturn = '\r';
  static char constexpr horizontalTab = '\t';
  static char constexpr zero = '0';
  static char constexpr binaryLowercase = 'b';
  static char constexpr binaryUppercase = 'B';
  static char constexpr hexLowercase = 'x';
  static char constexpr hexUppercase = 'X';
  static char constexpr dot = '.';
  static char constexpr leftBrace = '{';
  static char constexpr rightBrace = '}';
  static char constexpr leftSquareBracket = '[';
  static char constexpr rightSquareBracket = ']';
  static char constexpr plus = '+';
  static char constexpr minus = '-';
  static char constexpr separator = ',';
  static char constexpr memberSeparator = ':';
  static char constexpr exponent = 'e';
  static char constexpr exponentUppercase = 'E';
};

template <> struct JsonTokens<wchar_t> {
  static wchar_t constexpr stringQuote = L'"';
  static wchar_t constexpr reverseSolidus = L'\\';
  static wchar_t constexpr solidus = L'/';
  static wchar_t constexpr escapedBackspace = L'b';
  static wchar_t constexpr escapedFormFeed = L'f';
  static wchar_t constexpr escapedLineFeed = L'n';
  static wchar_t constexpr escapedCarriageReturn = L'r';
  static wchar_t constexpr escapedHorizontalTab = L't';
  static wchar_t constexpr escapedUTF = L'u';
  static wchar_t constexpr backspace = L'\b';
  static wchar_t constexpr formFeed = L'\f';
  static wchar_t constexpr lineFeed = L'\n';
  static wchar_t constexpr carriageReturn = L'\r';
  static wchar_t constexpr horizontalTab = L'\t';
  static wchar_t constexpr zero = L'0';
  static wchar_t constexpr binaryLowercase = L'b';
  static wchar_t constexpr binaryUppercase = L'B';
  static wchar_t constexpr hexLowercase = L'x';
  static wchar_t constexpr hexUppercase = L'X';
  static wchar_t constexpr dot = L'.';
  static wchar_t constexpr leftBrace = L'{';
  static wchar_t constexpr rightBrace = L'}';
  static wchar_t constexpr leftSquareBracket = L'[';
  static wchar_t constexpr rightSquareBracket = L']';
  static wchar_t constexpr plus = L'+';
  static wchar_t constexpr minus = L'-';
  static wchar_t constexpr separator = L',';
  static wchar_t constexpr memberSeparator = L':';
  static wchar_t constexpr exponent = L'e';
  static wchar_t constexpr exponentUppercase = L'E';
};

template <> struct JsonTokens<char16_t> {
  static char16_t constexpr stringQuote = u'"';
  static char16_t constexpr reverseSolidus = u'\\';
  static char16_t constexpr solidus = u'/';
  static char16_t constexpr escapedBackspace = u'b';
  static char16_t constexpr escapedFormFeed = u'f';
  static char16_t constexpr escapedLineFeed = u'n';
  static char16_t constexpr escapedCarriageReturn = u'r';
  static char16_t constexpr escapedHorizontalTab = u't';
  static char16_t constexpr escapedUTF = u'u';
  static char16_t constexpr backspace = u'\b';
  static char16_t constexpr formFeed = u'\f';
  static char16_t constexpr lineFeed = u'\n';
  static char16_t constexpr carriageReturn = u'\r';
  static char16_t constexpr horizontalTab = u'\t';
  static char16_t constexpr zero = u'0';
  static char16_t constexpr binaryLowercase = u'b';
  static char16_t constexpr binaryUppercase = u'B';
  static char16_t constexpr hexLowercase = u'x';
  static char16_t constexpr hexUppercase = u'X';
  static char16_t constexpr dot = u'.';
  static char16_t constexpr leftBrace = u'{';
  static char16_t constexpr rightBrace = u'}';
  static char16_t constexpr leftSquareBracket = u'[';
  static char16_t constexpr rightSquareBracket = u']';
  static char16_t constexpr plus = u'+';
  static char16_t constexpr minus = u'-';
  static char16_t constexpr separator = u',';
  static char16_t constexpr memberSeparator = u':';
  static char16_t constexpr exponent = u'e';
  static char16_t constexpr exponentUppercase = u'E';
};

template <> struct JsonTokens<char32_t> {
  static char32_t constexpr stringQuote = U'"';
  static char32_t constexpr reverseSolidus = U'\\';
  static char32_t constexpr solidus = U'/';
  static char32_t constexpr escapedBackspace = U'b';
  static char32_t constexpr escapedFormFeed = U'f';
  static char32_t constexpr escapedLineFeed = U'n';
  static char32_t constexpr escapedCarriageReturn = U'r';
  static char32_t constexpr escapedHorizontalTab = U't';
  static char32_t constexpr escapedUTF = U'u';
  static char32_t constexpr backspace = U'\b';
  static char32_t constexpr formFeed = U'\f';
  static char32_t constexpr lineFeed = U'\n';
  static char32_t constexpr carriageReturn = U'\r';
  static char32_t constexpr horizontalTab = U'\t';
  static char32_t constexpr zero = U'0';
  static char32_t constexpr binaryLowercase = U'b';
  static char32_t constexpr binaryUppercase = U'B';
  static char32_t constexpr hexLowercase = U'x';
  static char32_t constexpr hexUppercase = U'X';
  static char32_t constexpr dot = U'.';
  static char32_t constexpr leftBrace = U'{';
  static char32_t constexpr rightBrace = U'}';
  static char32_t constexpr leftSquareBracket = U'[';
  static char32_t constexpr rightSquareBracket = U']';
  static char32_t constexpr plus = U'+';
  static char32_t constexpr minus = U'-';
  static char32_t constexpr separator = U',';
  static char32_t constexpr memberSeparator = U':';
  static char32_t constexpr exponent = U'e';
  static char32_t constexpr exponentUppercase = U'E';
};

#if CDS_ATTR(cpp20)
template <> struct JsonTokens<char8_t> {
  static char8_t constexpr stringQuote = u8'"';
  static char8_t constexpr reverseSolidus = u8'\\';
  static char8_t constexpr solidus = u8'/';
  static char8_t constexpr escapedBackspace = u8'b';
  static char8_t constexpr escapedFormFeed = u8'f';
  static char8_t constexpr escapedLineFeed = u8'n';
  static char8_t constexpr escapedCarriageReturn = u8'r';
  static char8_t constexpr escapedHorizontalTab = u8't';
  static char8_t constexpr escapedUTF = u8'u';
  static char8_t constexpr backspace = u8'\b';
  static char8_t constexpr formFeed = u8'\f';
  static char8_t constexpr lineFeed = u8'\n';
  static char8_t constexpr carriageReturn = u8'\r';
  static char8_t constexpr horizontalTab = u8'\t';
  static char8_t constexpr zero = u8'0';
  static char8_t constexpr binaryLowercase = u8'b';
  static char8_t constexpr binaryUppercase = u8'B';
  static char8_t constexpr hexLowercase = u8'x';
  static char8_t constexpr hexUppercase = u8'X';
  static char8_t constexpr dot = u8'.';
  static char8_t constexpr leftBrace = u8'{';
  static char8_t constexpr rightBrace = u8'}';
  static char8_t constexpr leftSquareBracket = u8'[';
  static char8_t constexpr rightSquareBracket = u8']';
  static char8_t constexpr plus = u8'+';
  static char8_t constexpr minus = u8'-';
  static char8_t constexpr separator = u8',';
  static char8_t constexpr memberSeparator = u8':';
  static char8_t constexpr exponent = u8'e';
  static char8_t constexpr exponentUppercase = u8'E';
};
#endif

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
