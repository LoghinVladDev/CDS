//
// Created by loghin on 12/8/23.
//

#ifndef CDS_META_STRING_TRAITS_HPP
#define CDS_META_STRING_TRAITS_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/meta/Base>
#include <iosfwd>

namespace cds {
namespace meta {
namespace impl {
template <typename> struct StringTraitsConstants {};
template <typename> struct StringTraitsPrivateConstants {};

template <typename = void> struct StringTraitsCharConstants {
  static char constexpr emptyString[1] = "";
  static char constexpr nullChar = '\0';
  static char constexpr digits[11] = "0123456789";
  static char constexpr lowercaseAlphabet[27] = "abcdefghijklmnopqrstuvwxyz";
  static char constexpr uppercaseAlphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static char constexpr vowels[11] = "AEIOUaeiou";
  static char constexpr consonants[43] = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
  static char constexpr whitespace[6] = " \t\n\r\f";

  static_assert(sizeof(emptyString) == sizeof(""), "Unexpected emptyString size");
  static_assert(sizeof(digits) == sizeof("0123456789"), "Unexpected emptyString size");
  static_assert(sizeof(lowercaseAlphabet) == sizeof("abcdefghijklmnopqrstuvwxyz"), "Unexpected emptyString size");
  static_assert(sizeof(uppercaseAlphabet) == sizeof("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Unexpected emptyString size");
  static_assert(sizeof(vowels) == sizeof("AEIOUaeiou"), "Unexpected emptyString size");
  static_assert(sizeof(consonants) == sizeof("BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz"),
      "Unexpected emptyString size");
  static_assert(sizeof(whitespace) == sizeof(" \t\n\r\f"), "Unexpected emptyString size");
};

template <typename = void> struct StringTraitsPrivateCharConstants {
  static char constexpr encoded[15] = "09AEIOUZaeiouz";
  static char constexpr _true[5] = "true";
  static char constexpr _false[6] = "false";
  static char constexpr _null[5] = "null";

  static_assert(sizeof(encoded) == sizeof("09AEIOUZaeiouz"), "Unexpected encoded size");
  static_assert(sizeof(_true) == sizeof("true"), "Unexpected _true size");
  static_assert(sizeof(_false) == sizeof("false"), "Unexpected _false size");
  static_assert(sizeof(_null) == sizeof("null"), "Unexpected _null size");
};

template <> struct StringTraitsConstants<char> : StringTraitsCharConstants<> {};
template <> struct StringTraitsPrivateConstants<char> : StringTraitsPrivateCharConstants<> {};

// ODR before cpp17
template <typename T> char const StringTraitsCharConstants<T>::emptyString[1];
template <typename T> char const StringTraitsCharConstants<T>::nullChar;
template <typename T> char const StringTraitsCharConstants<T>::digits[11];
template <typename T> char const StringTraitsCharConstants<T>::lowercaseAlphabet[27];
template <typename T> char const StringTraitsCharConstants<T>::uppercaseAlphabet[27];
template <typename T> char const StringTraitsCharConstants<T>::vowels[11];
template <typename T> char const StringTraitsCharConstants<T>::consonants[43];
template <typename T> char const StringTraitsCharConstants<T>::whitespace[6];

template <typename T> char constexpr StringTraitsPrivateCharConstants<T>::encoded[15];
template <typename T> char constexpr StringTraitsPrivateCharConstants<T>::_true[5];
template <typename T> char constexpr StringTraitsPrivateCharConstants<T>::_false[6];
template <typename T> char constexpr StringTraitsPrivateCharConstants<T>::_null[5];

template <typename = void> struct StringTraitsWCharConstants {
  static wchar_t constexpr emptyString[1] = L"";
  static wchar_t constexpr nullChar = L'\0';
  static wchar_t constexpr digits[11] = L"0123456789";
  static wchar_t constexpr lowercaseAlphabet[27] = L"abcdefghijklmnopqrstuvwxyz";
  static wchar_t constexpr uppercaseAlphabet[27] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static wchar_t constexpr vowels[11] = L"AEIOUaeiou";
  static wchar_t constexpr consonants[43] = L"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
  static wchar_t constexpr whitespace[6] = L" \t\n\r\f";

  static_assert(sizeof(emptyString) == sizeof(L""), "Unexpected emptyString size");
  static_assert(sizeof(digits) == sizeof(L"0123456789"), "Unexpected emptyString size");
  static_assert(sizeof(lowercaseAlphabet) == sizeof(L"abcdefghijklmnopqrstuvwxyz"), "Unexpected emptyString size");
  static_assert(sizeof(uppercaseAlphabet) == sizeof(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Unexpected emptyString size");
  static_assert(sizeof(vowels) == sizeof(L"AEIOUaeiou"), "Unexpected emptyString size");
  static_assert(sizeof(consonants) == sizeof(L"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz"),
      "Unexpected emptyString size");
  static_assert(sizeof(whitespace) == sizeof(L" \t\n\r\f"), "Unexpected emptyString size");
};

template <typename = void> struct StringTraitsPrivateWCharConstants {
  static wchar_t constexpr encoded[15] = L"09AEIOUZaeiouz";
  static wchar_t constexpr _true[5] = L"true";
  static wchar_t constexpr _false[6] = L"false";
  static wchar_t constexpr _null[5] = L"null";

  static_assert(sizeof(encoded) == sizeof(L"09AEIOUZaeiouz"), "Unexpected encoded size");
  static_assert(sizeof(_true) == sizeof(L"true"), "Unexpected _true size");
  static_assert(sizeof(_false) == sizeof(L"false"), "Unexpected _false size");
  static_assert(sizeof(_null) == sizeof(L"null"), "Unexpected _null size");
};

template <> struct StringTraitsConstants<wchar_t> : StringTraitsWCharConstants<> {};
template <> struct StringTraitsPrivateConstants<wchar_t> : StringTraitsPrivateWCharConstants<> {};

// ODR before cpp17
template <typename T> wchar_t const StringTraitsWCharConstants<T>::emptyString[1];
template <typename T> wchar_t const StringTraitsWCharConstants<T>::nullChar;
template <typename T> wchar_t const StringTraitsWCharConstants<T>::digits[11];
template <typename T> wchar_t const StringTraitsWCharConstants<T>::lowercaseAlphabet[27];
template <typename T> wchar_t const StringTraitsWCharConstants<T>::uppercaseAlphabet[27];
template <typename T> wchar_t const StringTraitsWCharConstants<T>::vowels[11];
template <typename T> wchar_t const StringTraitsWCharConstants<T>::consonants[43];
template <typename T> wchar_t const StringTraitsWCharConstants<T>::whitespace[6];

template <typename T> wchar_t constexpr StringTraitsPrivateWCharConstants<T>::encoded[15];
template <typename T> wchar_t constexpr StringTraitsPrivateWCharConstants<T>::_true[5];
template <typename T> wchar_t constexpr StringTraitsPrivateWCharConstants<T>::_false[6];
template <typename T> wchar_t constexpr StringTraitsPrivateWCharConstants<T>::_null[5];

template <typename = void> struct StringTraitsChar16Constants {
  static char16_t constexpr emptyString[1] = u"";
  static char16_t constexpr nullChar = u'\0';
  static char16_t constexpr digits[11] = u"0123456789";
  static char16_t constexpr lowercaseAlphabet[27] = u"abcdefghijklmnopqrstuvwxyz";
  static char16_t constexpr uppercaseAlphabet[27] = u"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static char16_t constexpr vowels[11] = u"AEIOUaeiou";
  static char16_t constexpr consonants[43] = u"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
  static char16_t constexpr whitespace[6] = u" \t\n\r\f";

  static_assert(sizeof(emptyString) == sizeof(u""), "Unexpected emptyString size");
  static_assert(sizeof(digits) == sizeof(u"0123456789"), "Unexpected emptyString size");
  static_assert(sizeof(lowercaseAlphabet) == sizeof(u"abcdefghijklmnopqrstuvwxyz"), "Unexpected emptyString size");
  static_assert(sizeof(uppercaseAlphabet) == sizeof(u"ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Unexpected emptyString size");
  static_assert(sizeof(vowels) == sizeof(u"AEIOUaeiou"), "Unexpected emptyString size");
  static_assert(sizeof(consonants) == sizeof(u"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz"),
      "Unexpected emptyString size");
  static_assert(sizeof(whitespace) == sizeof(u" \t\n\r\f"), "Unexpected emptyString size");
};

template <typename = void> struct StringTraitsPrivateChar16Constants {
  static char16_t constexpr encoded[15] = u"09AEIOUZaeiouz";
  static char16_t constexpr _true[5] = u"true";
  static char16_t constexpr _false[6] = u"false";
  static char16_t constexpr _null[5] = u"null";

  static_assert(sizeof(encoded) == sizeof(u"09AEIOUZaeiouz"), "Unexpected encoded size");
  static_assert(sizeof(_true) == sizeof(u"true"), "Unexpected _true size");
  static_assert(sizeof(_false) == sizeof(u"false"), "Unexpected _false size");
  static_assert(sizeof(_null) == sizeof(u"null"), "Unexpected _null size");
};

template <> struct StringTraitsConstants<char16_t> : StringTraitsChar16Constants<> {};
template <> struct StringTraitsPrivateConstants<char16_t> : StringTraitsPrivateChar16Constants<> {};

// ODR before cpp17
template <typename T> char16_t const StringTraitsChar16Constants<T>::emptyString[1];
template <typename T> char16_t const StringTraitsChar16Constants<T>::nullChar;
template <typename T> char16_t const StringTraitsChar16Constants<T>::digits[11];
template <typename T> char16_t const StringTraitsChar16Constants<T>::lowercaseAlphabet[27];
template <typename T> char16_t const StringTraitsChar16Constants<T>::uppercaseAlphabet[27];
template <typename T> char16_t const StringTraitsChar16Constants<T>::vowels[11];
template <typename T> char16_t const StringTraitsChar16Constants<T>::consonants[43];
template <typename T> char16_t const StringTraitsChar16Constants<T>::whitespace[6];

template <typename T> char16_t constexpr StringTraitsPrivateChar16Constants<T>::encoded[15];
template <typename T> char16_t constexpr StringTraitsPrivateChar16Constants<T>::_true[5];
template <typename T> char16_t constexpr StringTraitsPrivateChar16Constants<T>::_false[6];
template <typename T> char16_t constexpr StringTraitsPrivateChar16Constants<T>::_null[5];

template <typename = void> struct StringTraitsChar32Constants {
  static char32_t constexpr emptyString[1] = U"";
  static char32_t constexpr nullChar = U'\0';
  static char32_t constexpr digits[11] = U"0123456789";
  static char32_t constexpr lowercaseAlphabet[27] = U"abcdefghijklmnopqrstuvwxyz";
  static char32_t constexpr uppercaseAlphabet[27] = U"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static char32_t constexpr vowels[11] = U"AEIOUaeiou";
  static char32_t constexpr consonants[43] = U"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
  static char32_t constexpr whitespace[6] = U" \t\n\r\f";

  static_assert(sizeof(emptyString) == sizeof(U""), "Unexpected emptyString size");
  static_assert(sizeof(digits) == sizeof(U"0123456789"), "Unexpected emptyString size");
  static_assert(sizeof(lowercaseAlphabet) == sizeof(U"abcdefghijklmnopqrstuvwxyz"), "Unexpected emptyString size");
  static_assert(sizeof(uppercaseAlphabet) == sizeof(U"ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Unexpected emptyString size");
  static_assert(sizeof(vowels) == sizeof(U"AEIOUaeiou"), "Unexpected emptyString size");
  static_assert(sizeof(consonants) == sizeof(U"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz"),
      "Unexpected emptyString size");
  static_assert(sizeof(whitespace) == sizeof(U" \t\n\r\f"), "Unexpected emptyString size");
};

template <typename = void> struct StringTraitsPrivateChar32Constants {
  static char32_t constexpr encoded[15] = U"09AEIOUZaeiouz";
  static char32_t constexpr _true[5] = U"true";
  static char32_t constexpr _false[6] = U"false";
  static char32_t constexpr _null[5] = U"null";

  static_assert(sizeof(encoded) == sizeof(U"09AEIOUZaeiouz"), "Unexpected encoded size");
  static_assert(sizeof(_true) == sizeof(U"true"), "Unexpected _true size");
  static_assert(sizeof(_false) == sizeof(U"false"), "Unexpected _false size");
  static_assert(sizeof(_null) == sizeof(U"null"), "Unexpected _null size");
};

template <> struct StringTraitsConstants<char32_t> : StringTraitsChar32Constants<> {};
template <> struct StringTraitsPrivateConstants<char32_t> : StringTraitsPrivateChar32Constants<> {};

// ODR before cpp17
template <typename T> char32_t const StringTraitsChar32Constants<T>::emptyString[1];
template <typename T> char32_t const StringTraitsChar32Constants<T>::nullChar;
template <typename T> char32_t const StringTraitsChar32Constants<T>::digits[11];
template <typename T> char32_t const StringTraitsChar32Constants<T>::lowercaseAlphabet[27];
template <typename T> char32_t const StringTraitsChar32Constants<T>::uppercaseAlphabet[27];
template <typename T> char32_t const StringTraitsChar32Constants<T>::vowels[11];
template <typename T> char32_t const StringTraitsChar32Constants<T>::consonants[43];
template <typename T> char32_t const StringTraitsChar32Constants<T>::whitespace[6];

template <typename T> char32_t constexpr StringTraitsPrivateChar32Constants<T>::encoded[15];
template <typename T> char32_t constexpr StringTraitsPrivateChar32Constants<T>::_true[5];
template <typename T> char32_t constexpr StringTraitsPrivateChar32Constants<T>::_false[6];
template <typename T> char32_t constexpr StringTraitsPrivateChar32Constants<T>::_null[5];

#if CDS_ATTR(cpp20)
template <typename = void> struct StringTraitsChar8Constants {
  static char8_t constexpr emptyString[1] = u8"";
  static char8_t constexpr nullChar = u8'\0';
  static char8_t constexpr digits[11] = u8"0123456789";
  static char8_t constexpr lowercaseAlphabet[27] = u8"abcdefghijklmnopqrstuvwxyz";
  static char8_t constexpr uppercaseAlphabet[27] = u8"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static char8_t constexpr vowels[11] = u8"AEIOUaeiou";
  static char8_t constexpr consonants[43] = u8"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
  static char8_t constexpr whitespace[6] = u8" \t\n\r\f";

  static_assert(sizeof(emptyString) == sizeof(u8""), "Unexpected emptyString size");
  static_assert(sizeof(digits) == sizeof(u8"0123456789"), "Unexpected emptyString size");
  static_assert(sizeof(lowercaseAlphabet) == sizeof(u8"abcdefghijklmnopqrstuvwxyz"), "Unexpected emptyString size");
  static_assert(sizeof(uppercaseAlphabet) == sizeof(u8"ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Unexpected emptyString size");
  static_assert(sizeof(vowels) == sizeof(u8"AEIOUaeiou"), "Unexpected emptyString size");
  static_assert(sizeof(consonants) == sizeof(u8"BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz"),
      "Unexpected emptyString size");
  static_assert(sizeof(whitespace) == sizeof(u8" \t\n\r\f"), "Unexpected emptyString size");
};

template <typename = void> struct StringTraitsPrivateChar8Constants {
  static char8_t constexpr encoded[15] = u8"09AEIOUZaeiouz";
  static char8_t constexpr _true[5] = u8"true";
  static char8_t constexpr _false[6] = u8"false";
  static char8_t constexpr _null[5] = u8"null";

  static_assert(sizeof(encoded) == sizeof(u8"09AEIOUZaeiouz"), "Unexpected encoded size");
  static_assert(sizeof(_true) == sizeof(u8"true"), "Unexpected _true size");
  static_assert(sizeof(_false) == sizeof(u8"false"), "Unexpected _false size");
  static_assert(sizeof(_null) == sizeof(u8"null"), "Unexpected _null size");
};

template <> struct StringTraitsConstants<char8_t> : StringTraitsChar8Constants<> {};
template <> struct StringTraitsPrivateConstants<char8_t> : StringTraitsPrivateChar8Constants<> {};

// ODR before cpp17
template <typename T> char8_t const StringTraitsChar8Constants<T>::emptyString[1];
template <typename T> char8_t const StringTraitsChar8Constants<T>::nullChar;
template <typename T> char8_t const StringTraitsChar8Constants<T>::digits[11];
template <typename T> char8_t const StringTraitsChar8Constants<T>::lowercaseAlphabet[27];
template <typename T> char8_t const StringTraitsChar8Constants<T>::uppercaseAlphabet[27];
template <typename T> char8_t const StringTraitsChar8Constants<T>::vowels[11];
template <typename T> char8_t const StringTraitsChar8Constants<T>::consonants[43];
template <typename T> char8_t const StringTraitsChar8Constants<T>::whitespace[6];

template <typename T> char8_t constexpr StringTraitsPrivateChar8Constants<T>::encoded[15];
template <typename T> char8_t constexpr StringTraitsPrivateChar8Constants<T>::_true[5];
template <typename T> char8_t constexpr StringTraitsPrivateChar8Constants<T>::_false[6];
template <typename T> char8_t constexpr StringTraitsPrivateChar8Constants<T>::_null[5];
#endif

template <typename C> CDS_ATTR(consteval(20, constexpr(14)))
bool charRangeEvaluation(C h1, C const t1, char h2, char const t2) {
  for (; h1 != t1 && h2 != t2; ++h1, ++h2) {
    if (static_cast<int>(h1) != static_cast<int>(h2)) {
      return false;
    }
  }
  return h1 == t1 && h2 == t2 && static_cast<int>(h1) == static_cast<int>(h2);
}
} // namespace impl

template <typename C> struct CommonStringTraits : impl::StringTraitsConstants<C> {
  using IsChar = True;
  using IsSeparator = True;
  using OStream = std::basic_ostream<C>;
  using Constants = impl::StringTraitsPrivateConstants<C>;

#if CDS_ATTR(cpp14)
  static_assert(
    impl::charRangeEvaluation(Constants::encoded[0], Constants::encoded[1], '0', '9')
    && impl::charRangeEvaluation(Constants::encoded[2], Constants::encoded[7], 'A', 'Z')
    && impl::charRangeEvaluation(Constants::encoded[8], Constants::encoded[13], 'a', 'z'),
    "Unexpected char range values for standard encoding"
  );
#endif

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isUpper(C const c) noexcept -> bool {
    return c >= Constants::encoded[2] && c <= Constants::encoded[7];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isLower(C const c) noexcept -> bool {
    return c >= Constants::encoded[8] && c <= Constants::encoded[13];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isDigit(C const c) noexcept -> bool {
    return c >= Constants::encoded[0] && c <= Constants::encoded[1];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isLetter(C const c) noexcept -> bool {
    return isLower(c) || isUpper(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isAlpha(C const c) noexcept -> bool {
    return isLower(c) || isDigit(c) || isUpper(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isVowel(C const c) noexcept -> bool {
    return ((c & 0x60u) == 0x60u) // 0x60 = 96. 'a' is 97
        ? (c == Constants::encoded[8] || c == Constants::encoded[9] || c == Constants::encoded[10]
          || c == Constants::encoded[11] || c == Constants::encoded[12])
        : (c == Constants::encoded[2] || c == Constants::encoded[3] || c == Constants::encoded[4]
          || c == Constants::encoded[5] || c == Constants::encoded[6]);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isConsonant(C const c) noexcept -> bool {
    return isLetter(c) && !isVowel(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static lower(C const c) noexcept -> C {
    return !isUpper(c)
        ? c
        : c - Constants::encoded[2] + Constants::encoded[8];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static upper(C const c) noexcept -> C {
    return !isLower(c)
        ? c
        : c - Constants::encoded[8] + Constants::encoded[2];
  }
};

template <typename> struct StringTraits {
  using IsChar = False;
  using IsSeparator = False;
};

template <> struct StringTraits<char> : CommonStringTraits<char> {};
template <> struct StringTraits<wchar_t> : CommonStringTraits<wchar_t> {};
template <> struct StringTraits<char16_t> : CommonStringTraits<char16_t> {};
template <> struct StringTraits<char32_t> : CommonStringTraits<char32_t> {};
#if CDS_ATTR(cpp20)
template <> struct StringTraits<char8_t> : CommonStringTraits<char8_t> {};
#endif
} // namespace meta
} // namespace cds

#endif // CDS_META_STRING_TRAITS_HPP
