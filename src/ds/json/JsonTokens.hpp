//
// Created by loghin on 7/8/25.
//

#ifndef CDS_DS_JSON_TOKENS_HPP
#define CDS_DS_JSON_TOKENS_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace json {
namespace impl {
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
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_TOKENS_HPP
