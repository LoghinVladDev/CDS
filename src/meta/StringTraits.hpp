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
template <typename> struct StringTraits {
  using IsChar = False;
  using IsSeparator = False;
};

template <> struct StringTraits<char> {
  using IsChar = True;
  using IsSeparator = True;
  using OStream = std::ostream;
  static constexpr auto const* emptyString = "";
  static constexpr char nullChar = '\0';
  constexpr static auto const* digits = "0123456789";
  constexpr static auto const* lowercaseAlphabet = "abcdefghijklmnopqrstuvwxyz";
  constexpr static auto const* uppercaseAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  constexpr static auto const* vowels = "AEIOUaeiou";
  constexpr static auto const* consonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";
  constexpr static auto const* whitespace = " \t\n\r\f";

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isUpper(char const c) noexcept -> bool {
    return c >= 'A' && c <= 'Z';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isLower(char const c) noexcept -> bool {
    return c >= 'a' && c <= 'z';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isDigit(char const c) noexcept -> bool {
    return c >= '0' && c <= '9';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isLetter(char const c) noexcept -> bool {
    return isLower(c) || isUpper(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isAlpha(char const c) noexcept -> bool {
    return isLower(c) || isDigit(c) || isUpper(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isVowel(char const c) noexcept -> bool {
    return ((c & 0x60u) == 0x60u) // 0x60 = 96. 'a' is 97
        ? (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        : (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static isConsonant(char const c) noexcept -> bool {
    return isLetter(c) && !isVowel(c);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static lower(char const c) noexcept -> char {
    return !isUpper(c)
        ? c
        : c - 'A' + 'a';
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto static upper(char const c) noexcept -> char {
    return !isLower(c)
        ? c
        : c - 'a' + 'A';
  }
};

template <> struct StringTraits<wchar_t> {
  using IsChar = True;
  using IsSeparator = True;
  using OStream = std::wostream;
  static constexpr auto const* emptyString = L"";
  static constexpr wchar_t nullChar = L'\0';
  constexpr static auto const* digits = L"0123456789";
  constexpr static auto const* lowercaseAlphabet = L"abcdefghijklmnopqrstuvxyzw";
  constexpr static auto const* uppercaseAlphabet = L"ABCDEFGHIJKLMNOPQRSTUVXYZW";
  constexpr static auto const* vowels = L"AEIOUaeiou";
  constexpr static auto const* consonants = L"BCDFGHJKLMNPQRSTVXYZWbcdfghjklmnpqrstvxyzw";
  constexpr static auto const* whitespace = L" \t\n\r\f";
};
} // namespace meta
} // namespace cds

#endif // CDS_META_STRING_TRAITS_HPP
