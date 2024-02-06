//
// Created by loghin on 12/8/23.
//

#ifndef CDS_META_STRING_TRAITS_HPP
#define CDS_META_STRING_TRAITS_HPP
#pragma once

#include <cds/meta/Base>
#include <ostream>

namespace cds {
namespace meta {
template <typename> struct StringTraits {
  using IsChar = False;
  using IsSeparator = False;
};

template <> struct StringTraits<char> {
  using IsChar = True;
  using IsSeparator = True;
  using OStream = std::ostream;
  static constexpr char const* emptyString = "";
  static constexpr char nullChar = '\0';
  constexpr static char const* digits = "0123456789";
  constexpr static char const* lowercaseAlphabet = "abcdefghijklmnopqrstuvwxyz";
  constexpr static char const* uppercaseAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  constexpr static char const* vowels = "AEIOUaeiou";
  constexpr static char const* consonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
  constexpr static char const* whitespace = " \t\n\r\f";

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isUpper(char c) noexcept -> bool {
    return c >= 'A' && c <= 'Z';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isLower(char c) noexcept -> bool {
    return c >= 'a' && c <= 'z';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isDigit(char c) noexcept -> bool {
    return c >= '0' && c <= '9';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isLetter(char c) noexcept -> bool {
    return isLower(c) || isUpper(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isAlpha(char c) noexcept -> bool {
    return isLower(c) || isDigit(c) || isUpper(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isVowel(char c) noexcept -> bool {
    return ((c & 0x60u) == 0x60u) // 0x60 = 96. 'a' is 97
        ? (
            c == 'a'
            || c == 'e'
            || c == 'i'
            || c == 'o'
            || c == 'u'
        )
        : (
             c == 'A'
             || c == 'E'
             || c == 'I'
             || c == 'O'
             || c == 'U'
        );
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isConsonant(char c) noexcept -> bool {
    return isLetter(c) && !isVowel(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static lower(char c) noexcept -> char {
    return !isUpper(c)
        ? c
        : c - 'A' + 'a';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static upper(char c) noexcept -> char {
    return !isLower(c)
        ? c
        : c - 'a' + 'A';
  }
};

template <> struct StringTraits<wchar_t> {
  using IsChar = True;
  using IsSeparator = True;
  using OStream = std::wostream;
  static constexpr wchar_t const* emptyString = L"";
  static constexpr wchar_t nullChar = L'\0';
  constexpr static wchar_t const* digits = L"0123456789";
  constexpr static wchar_t const* lowercaseAlphabet = L"abcdefghijklmnopqrstuvxyzw";
  constexpr static wchar_t const* uppercaseAlphabet = L"ABCDEFGHIJKLMNOPQRSTUVXYZW";
  constexpr static wchar_t const* vowels = L"AEIOUaeiou";
  constexpr static wchar_t const* consonants = L"BCDFGHJKLMNPQRSTVXYZWbcdfghjklmnpqrstvxyzw";
  constexpr static wchar_t const* whitespace = L" \t\n\r\f";
};
} // namespace meta
} // namespace cds

#endif // CDS_META_STRING_TRAITS_HPP
