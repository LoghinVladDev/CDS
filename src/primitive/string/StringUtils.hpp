//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_UTILS_HPP
#define CDS_PRIMITIVE_STRING_UTILS_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/meta/Base>
#include <cds/Utility>

#include "StringAbstract.hpp"
#include <cstdio>

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::IsBoundedArray;
using meta::RemoveCVRef;
using meta::IsSigned;
using meta::IsUnsigned;
using meta::UnsignedEquivalent;

template <typename> struct StringUtilsConstants {};

template <typename = void> struct StringUtilsCharConstants {
  static char constexpr minusChar = '-';
  static char constexpr zeroChar = '0';
  static char constexpr writeIntPrepNumsB2[65]
    = "00000001001000110100010101100111"
      "10001001101010111100110111101111";
  static_assert(sizeof(writeIntPrepNumsB2) ==
      sizeof("00000001001000110100010101100111"
             "10001001101010111100110111101111"), "Unexpected writeIntPrepNumsB2 size");
  static char constexpr writeIntPrepNumsB8[129]
    = "00010203040506071011121314151617"
      "20212223242526273031323334353637"
      "40414243444546475051525354555657"
      "60616263646566677071727374757677";
  static_assert(sizeof(writeIntPrepNumsB8) ==
      sizeof("00010203040506071011121314151617"
             "20212223242526273031323334353637"
             "40414243444546475051525354555657"
             "60616263646566677071727374757677"), "Unexpected writeIntPrepNumsB8 size");
  static char constexpr writeIntPrepNumsB10[201]
    = "0001020304050607080910111213141516171819"
      "2021222324252627282930313233343536373839"
      "4041424344454647484950515253545556575859"
      "6061626364656667686970717273747576777879"
      "8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNumsB10) ==
    sizeof("0001020304050607080910111213141516171819"
           "2021222324252627282930313233343536373839"
           "4041424344454647484950515253545556575859"
           "6061626364656667686970717273747576777879"
           "8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNumsB10 size");
  static char constexpr writeIntPrepNumsB16l[513]
    = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
      "202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
      "404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
      "606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
      "808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
      "a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
      "c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
      "e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  static_assert(sizeof(writeIntPrepNumsB16l) ==
      sizeof("000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
             "202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
             "404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
             "606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
             "808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
             "a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
             "c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
             "e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"),
             "Unexpected writeIntPrepNumsB16l size");
  static char constexpr writeIntPrepNumsB16L[513]
    = "000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
      "202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
      "404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
      "606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
      "808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
      "A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
      "C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
      "E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
  static_assert(sizeof(writeIntPrepNumsB16L) ==
      sizeof("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
             "202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
             "404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
             "606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
             "808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
             "A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
             "C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
             "E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF"),
             "unexpected writeIntPrepNumsB16l size");
};

template <> struct StringUtilsConstants<char> : StringUtilsCharConstants<> {};

template <typename T> char const StringUtilsCharConstants<T>::minusChar;
template <typename T> char const StringUtilsCharConstants<T>::zeroChar;
template <typename T> char const StringUtilsCharConstants<T>::writeIntPrepNumsB2[65];
template <typename T> char const StringUtilsCharConstants<T>::writeIntPrepNumsB8[129];
template <typename T> char const StringUtilsCharConstants<T>::writeIntPrepNumsB10[201];
template <typename T> char const StringUtilsCharConstants<T>::writeIntPrepNumsB16l[513];
template <typename T> char const StringUtilsCharConstants<T>::writeIntPrepNumsB16L[513];

template <typename = void> struct StringUtilsWCharConstants {
  static wchar_t constexpr minusChar = L'-';
  static wchar_t constexpr zeroChar = L'0';
  static wchar_t constexpr writeIntPrepNumsB2[65]
      = L"00000001001000110100010101100111"
        L"10001001101010111100110111101111";
  static_assert(sizeof(writeIntPrepNumsB2) ==
      sizeof(L"00000001001000110100010101100111"
             L"10001001101010111100110111101111"), "Unexpected writeIntPrepNumsB2 size");
  static wchar_t constexpr writeIntPrepNumsB8[129]
      = L"00010203040506071011121314151617"
        L"20212223242526273031323334353637"
        L"40414243444546475051525354555657"
        L"60616263646566677071727374757677";
  static_assert(sizeof(writeIntPrepNumsB8) ==
      sizeof(L"00010203040506071011121314151617"
             L"20212223242526273031323334353637"
             L"40414243444546475051525354555657"
             L"60616263646566677071727374757677"), "Unexpected writeIntPrepNumsB8 size");
  static wchar_t constexpr writeIntPrepNumsB10[201]
      = L"0001020304050607080910111213141516171819"
        L"2021222324252627282930313233343536373839"
        L"4041424344454647484950515253545556575859"
        L"6061626364656667686970717273747576777879"
        L"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNumsB10) ==
    sizeof(L"0001020304050607080910111213141516171819"
           L"2021222324252627282930313233343536373839"
           L"4041424344454647484950515253545556575859"
           L"6061626364656667686970717273747576777879"
           L"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNumsB10 size");
  static wchar_t constexpr writeIntPrepNumsB16l[513]
      = L"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
        L"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
        L"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
        L"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
        L"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
        L"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
        L"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
        L"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  static_assert(sizeof(writeIntPrepNumsB16l) ==
      sizeof(L"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
             L"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
             L"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
             L"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
             L"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
             L"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
             L"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
             L"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"),
             "Unexpected writeIntPrepNumsB16l size");
  static wchar_t constexpr writeIntPrepNumsB16L[513]
      = L"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
        L"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
        L"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
        L"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
        L"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
        L"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
        L"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
        L"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
  static_assert(sizeof(writeIntPrepNumsB16L) ==
      sizeof(L"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
             L"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
             L"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
             L"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
             L"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
             L"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
             L"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
             L"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF"),
             "unexpected writeIntPrepNumsB16l size");
};

template <> struct StringUtilsConstants<wchar_t> : StringUtilsWCharConstants<> {};

template <typename T> wchar_t const StringUtilsWCharConstants<T>::minusChar;
template <typename T> wchar_t const StringUtilsWCharConstants<T>::zeroChar;
template <typename T> wchar_t const StringUtilsWCharConstants<T>::writeIntPrepNumsB2[65];
template <typename T> wchar_t const StringUtilsWCharConstants<T>::writeIntPrepNumsB8[129];
template <typename T> wchar_t const StringUtilsWCharConstants<T>::writeIntPrepNumsB10[201];
template <typename T> wchar_t const StringUtilsWCharConstants<T>::writeIntPrepNumsB16l[513];
template <typename T> wchar_t const StringUtilsWCharConstants<T>::writeIntPrepNumsB16L[513];

template <typename = void> struct StringUtilsChar16Constants {
  static char16_t constexpr minusChar = u'-';
  static char16_t constexpr zeroChar = u'0';
  static char16_t constexpr writeIntPrepNumsB2[65]
      = u"00000001001000110100010101100111"
        u"10001001101010111100110111101111";
  static_assert(sizeof(writeIntPrepNumsB2) ==
      sizeof(u"00000001001000110100010101100111"
             u"10001001101010111100110111101111"), "Unexpected writeIntPrepNumsB2 size");
  static char16_t constexpr writeIntPrepNumsB8[129]
      = u"00010203040506071011121314151617"
        u"20212223242526273031323334353637"
        u"40414243444546475051525354555657"
        u"60616263646566677071727374757677";
  static_assert(sizeof(writeIntPrepNumsB8) ==
      sizeof(u"00010203040506071011121314151617"
             u"20212223242526273031323334353637"
             u"40414243444546475051525354555657"
             u"60616263646566677071727374757677"), "Unexpected writeIntPrepNumsB8 size");
  static char16_t constexpr writeIntPrepNumsB10[201]
      = u"0001020304050607080910111213141516171819"
        u"2021222324252627282930313233343536373839"
        u"4041424344454647484950515253545556575859"
        u"6061626364656667686970717273747576777879"
        u"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNumsB10) ==
    sizeof(u"0001020304050607080910111213141516171819"
           u"2021222324252627282930313233343536373839"
           u"4041424344454647484950515253545556575859"
           u"6061626364656667686970717273747576777879"
           u"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNumsB10 size");
  static char16_t constexpr writeIntPrepNumsB16l[513]
      = u"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
        u"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
        u"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
        u"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
        u"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
        u"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
        u"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
        u"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  static_assert(sizeof(writeIntPrepNumsB16l) ==
      sizeof(u"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
             u"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
             u"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
             u"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
             u"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
             u"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
             u"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
             u"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"),
             "Unexpected writeIntPrepNumsB16l size");
  static char16_t constexpr writeIntPrepNumsB16L[513]
      = u"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
        u"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
        u"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
        u"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
        u"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
        u"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
        u"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
        u"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
  static_assert(sizeof(writeIntPrepNumsB16L) ==
      sizeof(u"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
             u"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
             u"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
             u"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
             u"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
             u"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
             u"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
             u"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF"),
             "unexpected writeIntPrepNumsB16l size");
};

template <> struct StringUtilsConstants<char16_t> : StringUtilsChar16Constants<> {};

template <typename T> char16_t const StringUtilsChar16Constants<T>::minusChar;
template <typename T> char16_t const StringUtilsChar16Constants<T>::zeroChar;
template <typename T> char16_t const StringUtilsChar16Constants<T>::writeIntPrepNumsB2[65];
template <typename T> char16_t const StringUtilsChar16Constants<T>::writeIntPrepNumsB8[129];
template <typename T> char16_t const StringUtilsChar16Constants<T>::writeIntPrepNumsB10[201];
template <typename T> char16_t const StringUtilsChar16Constants<T>::writeIntPrepNumsB16l[513];
template <typename T> char16_t const StringUtilsChar16Constants<T>::writeIntPrepNumsB16L[513];

template <typename = void> struct StringUtilsChar32Constants {
  static char32_t constexpr minusChar = U'-';
  static char32_t constexpr zeroChar = U'0';
  static char32_t constexpr writeIntPrepNumsB2[65]
      = U"00000001001000110100010101100111"
        U"10001001101010111100110111101111";
  static_assert(sizeof(writeIntPrepNumsB2) ==
      sizeof(U"00000001001000110100010101100111"
             U"10001001101010111100110111101111"), "Unexpected writeIntPrepNumsB2 size");
  static char32_t constexpr writeIntPrepNumsB8[129]
      = U"00010203040506071011121314151617"
        U"20212223242526273031323334353637"
        U"40414243444546475051525354555657"
        U"60616263646566677071727374757677";
  static_assert(sizeof(writeIntPrepNumsB8) ==
      sizeof(U"00010203040506071011121314151617"
             U"20212223242526273031323334353637"
             U"40414243444546475051525354555657"
             U"60616263646566677071727374757677"), "Unexpected writeIntPrepNumsB8 size");
  static char32_t constexpr writeIntPrepNumsB10[201]
      = U"0001020304050607080910111213141516171819"
        U"2021222324252627282930313233343536373839"
        U"4041424344454647484950515253545556575859"
        U"6061626364656667686970717273747576777879"
        U"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNumsB10) ==
    sizeof(U"0001020304050607080910111213141516171819"
           U"2021222324252627282930313233343536373839"
           U"4041424344454647484950515253545556575859"
           U"6061626364656667686970717273747576777879"
           U"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNumsB10 size");
  static char32_t constexpr writeIntPrepNumsB16l[513]
      = U"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
        U"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
        U"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
        U"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
        U"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
        U"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
        U"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
        U"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  static_assert(sizeof(writeIntPrepNumsB16l) ==
      sizeof(U"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
             U"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
             U"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
             U"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
             U"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
             U"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
             U"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
             U"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"),
             "Unexpected writeIntPrepNumsB16l size");
  static char32_t constexpr writeIntPrepNumsB16L[513]
      = U"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
        U"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
        U"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
        U"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
        U"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
        U"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
        U"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
        U"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
  static_assert(sizeof(writeIntPrepNumsB16L) ==
      sizeof(U"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
             U"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
             U"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
             U"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
             U"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
             U"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
             U"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
             U"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF"),
             "unexpected writeIntPrepNumsB16l size");
};

template <> struct StringUtilsConstants<char32_t> : StringUtilsChar32Constants<> {};

template <typename T> char32_t const StringUtilsChar32Constants<T>::minusChar;
template <typename T> char32_t const StringUtilsChar32Constants<T>::zeroChar;
template <typename T> char32_t const StringUtilsChar32Constants<T>::writeIntPrepNumsB2[65];
template <typename T> char32_t const StringUtilsChar32Constants<T>::writeIntPrepNumsB8[129];
template <typename T> char32_t const StringUtilsChar32Constants<T>::writeIntPrepNumsB10[201];
template <typename T> char32_t const StringUtilsChar32Constants<T>::writeIntPrepNumsB16l[513];
template <typename T> char32_t const StringUtilsChar32Constants<T>::writeIntPrepNumsB16L[513];

#if CDS_ATTR(cpp20)
template <typename = void> struct StringUtilsChar8Constants {
  static char8_t constexpr minusChar = u8'-';
  static char8_t constexpr zeroChar = u8'0';
  static char8_t constexpr writeIntPrepNumsB2[65]
      = u8"00000001001000110100010101100111"
        u8"10001001101010111100110111101111";
  static_assert(sizeof(writeIntPrepNumsB2) ==
      sizeof(u8"00000001001000110100010101100111"
             u8"10001001101010111100110111101111"), "Unexpected writeIntPrepNumsB2 size");
  static char8_t constexpr writeIntPrepNumsB8[129]
      = u8"00010203040506071011121314151617"
        u8"20212223242526273031323334353637"
        u8"40414243444546475051525354555657"
        u8"60616263646566677071727374757677";
  static_assert(sizeof(writeIntPrepNumsB8) ==
      sizeof(u8"00010203040506071011121314151617"
             u8"20212223242526273031323334353637"
             u8"40414243444546475051525354555657"
             u8"60616263646566677071727374757677"), "Unexpected writeIntPrepNumsB8 size");
  static char8_t constexpr writeIntPrepNumsB10[201]
      = u8"0001020304050607080910111213141516171819"
        u8"2021222324252627282930313233343536373839"
        u8"4041424344454647484950515253545556575859"
        u8"6061626364656667686970717273747576777879"
        u8"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNumsB10) ==
    sizeof(u8"0001020304050607080910111213141516171819"
           u8"2021222324252627282930313233343536373839"
           u8"4041424344454647484950515253545556575859"
           u8"6061626364656667686970717273747576777879"
           u8"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNumsB10 size");
  static char8_t constexpr writeIntPrepNumsB16l[513]
      = u8"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
        u8"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
        u8"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
        u8"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
        u8"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
        u8"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
        u8"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
        u8"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  static_assert(sizeof(writeIntPrepNumsB16l) ==
      sizeof(u8"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
             u8"202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
             u8"404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f"
             u8"606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"
             u8"808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9f"
             u8"a0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
             u8"c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
             u8"e0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"),
             "Unexpected writeIntPrepNumsB16l size");
  static char8_t constexpr writeIntPrepNumsB16L[513]
      = u8"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
        u8"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
        u8"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
        u8"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
        u8"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
        u8"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
        u8"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
        u8"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
  static_assert(sizeof(writeIntPrepNumsB16L) ==
      sizeof(u8"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
             u8"202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
             u8"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
             u8"606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
             u8"808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
             u8"A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
             u8"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
             u8"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF"),
             "unexpected writeIntPrepNumsB16l size");
};

template <typename T> char8_t const StringUtilsChar8Constants<T>::minusChar;
template <typename T> char8_t const StringUtilsChar8Constants<T>::zeroChar;
template <typename T> char8_t const StringUtilsChar8Constants<T>::writeIntPrepNumsB2[65];
template <typename T> char8_t const StringUtilsChar8Constants<T>::writeIntPrepNumsB8[129];
template <typename T> char8_t const StringUtilsChar8Constants<T>::writeIntPrepNumsB10[201];
template <typename T> char8_t const StringUtilsChar8Constants<T>::writeIntPrepNumsB16l[513];
template <typename T> char8_t const StringUtilsChar8Constants<T>::writeIntPrepNumsB16L[513];

template <> struct StringUtilsConstants<char8_t> : StringUtilsChar8Constants<> {};
#endif // #if CDS_ATTR(cpp20)

template <typename C> struct StringUtilsFloatingOps {
  static auto floatingLength(float const value) noexcept -> U8 {
    return static_cast<U8>(snprintf(nullptr, 0, "%f", value));
  }

  static auto floatingLength(double const value) noexcept -> U8 {
    return static_cast<U8>(snprintf(nullptr, 0, "%lf", value));
  }

  static auto floatingLength(long double const value) noexcept -> U8 {
    return static_cast<U8>(snprintf(nullptr, 0, "%Lf", value));
  }

  template <typename I> static auto writeFloating(float const value, U8 const length, I const dst) noexcept -> I {
    char buf[64];
    assert(length < 64 && "Too small local buffer size for floating write");
    snprintf(buf, 63, "%f", value);
    return impl::copy(buf, buf + length, dst);
  }

  template <typename I> static auto writeFloating(double const value, U8 const length, I const dst) noexcept -> I {
    char buf[64];
    assert(length < 64 && "Too small local buffer size for floating write");
    snprintf(buf, 63, "%lf", value);
    return impl::copy(buf, buf + length, dst);
  }

  template <typename I> static auto writeFloating(long double const value, U8 const length, I const dst) noexcept -> I {
    char buf[64];
    assert(length < 64 && "Too small local buffer size for floating write");
    snprintf(buf, 63, "%Lf", value);
    return impl::copy(buf, buf + length, dst);
  }
};

template <> struct StringUtilsFloatingOps<char> {
  static auto floatingLength(float const value) noexcept -> U8 {
    return static_cast<U8>(snprintf(nullptr, 0, "%f", value));
  }

  static auto floatingLength(double const value) noexcept -> U8 {
    return static_cast<U8>(snprintf(nullptr, 0, "%lf", value));
  }

  static auto floatingLength(long double const value) noexcept -> U8 {
    return static_cast<U8>(snprintf(nullptr, 0, "%Lf", value));
  }

  template <typename I> static auto writeFloating(float const value, U8 const length, I const dst) noexcept -> I {
    ignore = snprintf(dst, length + 1u, "%f", value);
    return dst + length;
  }

  template <typename I> static auto writeFloating(double const value, U8 const length, I const dst) noexcept -> I {
    ignore = snprintf(dst, length + 1u, "%lf", value);
    return dst + length;
  }

  template <typename I> static auto writeFloating(long double const value, U8 const length, I const dst) noexcept -> I {
    ignore = snprintf(dst, length + 1u, "%Lf", value);
    return dst + length;
  }
};

template <typename C, typename T> struct StringUtils : private StringUtilsConstants<C>, StringUtilsFloatingOps<C> {
  using Constants = StringUtilsConstants<C>;
  using Traits = T;

  CDS_ATTR(2(nodiscard, constexpr(11)))
  static auto startsWith(C const* str, Size const len, C const needle) noexcept -> bool {
    return len != 0u && str[0] == needle;
  }

  CDS_ATTR(2(nodiscard, constexpr(11)))
  static auto endsWith(C const* str, Size const len, C const needle) noexcept -> bool {
    return len != 0u && str[len - 1u] == needle;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto startsWith(C const* str, Size len, N&& needle) noexcept -> bool {
    using Abs = StringAbstract<N>;
    auto nbeg = Abs::data(cds::forward<N>(needle));
    auto const nend = nbeg + Abs::length(cds::forward<N>(needle));
    for (auto const end = str + len; str != end && nbeg != nend; ++str, ++nbeg) {
      if (*str != *nbeg) {
        return false;
      }
    }
    return nbeg == nend;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto endsWith(C const* str, Size len, N&& needle) noexcept -> bool {
    using Abs = StringAbstract<N>;
    auto const nlen = Abs::length(cds::forward<N>(needle));
    auto nbeg = Abs::data(cds::forward<N>(needle)) + nlen;
    auto beg = str + len;
    auto const nend = nbeg - nlen;
    for (auto const end = beg - len; beg != end && nbeg != nend; --beg, --nbeg) {
      if (*(beg - 1) != *(nbeg - 1)) {
        return false;
      }
    }

    return nbeg == nend;
  }

  template <typename N, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto intLength(N value, U8 base) noexcept -> U8 {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    return static_cast<U8>(neg)
        + intLength(neg ? static_cast<U>(~value) + 1 : static_cast<U>(value), base);
  }

  template <typename N, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto intLength(N value, U8 base) noexcept -> U8 {
    U8 cnt = 1;
    U32 const b2 = base * base;
    U32 const b3 = b2 * base;
    U32 const b4 = b3 * base;

    for (;;) {
      if (value < base) {
        return cnt;
      }
      if (value < b2) {
        return cnt + 1;
      }
      if (value < b3) {
        return cnt + 2;
      }
      if (value < b4) {
        return cnt + 3;
      }

      value /= b4;
      cnt += 4;
    }

    unreachable();
  }

  template <typename N, typename I> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeInt(N value, U8 len, I dst, U8 base = 10, bool upper = false) noexcept -> I {
    if (base == 10u) {
      return writeIntB10(value, len, dst);
    }
    if (base == 16u) {
      return writeIntB16(value, len, dst, upper);
    }
    if (base == 2u) {
      return writeIntB2(value, len, dst);
    }
    if (base == 8u) {
      return writeIntB8(value, len, dst);
    }
    return writeIntGeneric(value, len, dst, base, upper);
  }

  template <typename N, typename I, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntGeneric(N value, U8 len, I dst, U8 base, bool upper) noexcept -> I {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    auto const uns = neg
        ? static_cast<U>(~value) + 1u
        : static_cast<U>(value);
    if (neg) {
      *(dst++) = Constants::minusChar;
      --len;
    }
    return writeIntGeneric(uns, len, dst, base, upper);
  }

  template <typename N, typename I, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB10(N value, U8 len, I dst) noexcept -> I {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    auto const uns = neg
        ? static_cast<U>(~value) + 1u
        : static_cast<U>(value);
    if (neg) {
      *(dst++) = Constants::minusChar;
      --len;
    }
    return writeIntB10(uns, len, dst);
  }

  template <typename N, typename I, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB16(N value, U8 len, I dst, bool upper = false) noexcept -> I {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    auto const uns = neg
        ? static_cast<U>(~value) + 1u
        : static_cast<U>(value);
    if (neg) {
      *(dst++) = Constants::minusChar;
      --len;
    }
    return writeIntB16(uns, len, dst, upper);
  }

  template <typename N, typename I, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB2(N value, U8 len, I dst) noexcept -> I {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    auto const uns = neg
        ? static_cast<U>(~value) + 1u
        : static_cast<U>(value);
    if (neg) {
      *(dst++) = Constants::minusChar;
      --len;
    }
    return writeIntB2(uns, len, dst);
  }

  template <typename N, typename I, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB8(N value, U8 len, I dst) noexcept -> I {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    auto const uns = neg
        ? static_cast<U>(~value) + 1u
        : static_cast<U>(value);
    if (neg) {
      *(dst++) = Constants::minusChar;
      --len;
    }
    return writeIntB8(uns, len, dst);
  }

  template <typename N, typename I, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB10(N value, U8 const len, I dst) noexcept -> I {
    auto const end = dst + len;
    auto beg = end - 1;
    while (value >= 100) {
      auto const idx = value % 100 * 2;
      value /= 100;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB10[idx + 1]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB10[idx]);
    }

    if (value >= 10) {
      auto const idx = value * 2;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB10[idx + 1]);
      *beg = static_cast<C>(Constants::writeIntPrepNumsB10[idx]);
    } else {
      *beg = static_cast<C>(Constants::zeroChar + value);
    }

    return end;
  }

  template <typename N, typename I, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB16(N value, U8 const len, I dst, bool upper = false) noexcept -> I {
    if (upper) {
      return writeIntB16L(value, len, dst);
    }
    return writeIntB16l(value, len, dst);
  }

  template <typename N, typename I> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB16l(N value, U8 const len, I dst) noexcept -> I {
    static_assert(IsUnsigned<N>::value, "Do not use this call directly with signed values, use writeInt instead");
    auto const end = dst + len;
    auto beg = end - 1;
    while (value >= 256) {
      auto const idx = value % 256 * 2;
      value /= 256;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB16l[idx + 1]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB16l[idx]);
    }

    if (value >= 16) {
      auto const idx = value * 2;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB16l[idx + 1]);
      *beg = static_cast<C>(Constants::writeIntPrepNumsB16l[idx]);
    } else if (value >= 10) {
      *beg = static_cast<C>(static_cast<unsigned>('a') + value - 10);
    } else {
      *beg = static_cast<C>(Constants::zeroChar + value);
    }

    return end;
  }

  template <typename N, typename I> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB16L(N value, U8 const len, I dst) noexcept -> I {
    static_assert(IsUnsigned<N>::value,
                  "Do not use this call directly with signed values, use writeInt or writeIntB16 instead");
    auto const end = dst + len;
    auto beg = end - 1;
    while (value >= 256) {
      auto const idx = value % 256 * 2;
      value /= 256;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB16L[idx + 1]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB16L[idx]);
    }

    if (value >= 16) {
      auto const idx = value * 2;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB16L[idx + 1]);
      *beg = static_cast<C>(Constants::writeIntPrepNumsB16L[idx]);
    } else if (value >= 10) {
      *beg = static_cast<C>(static_cast<unsigned>('A') + value - 10);
    } else {
      *beg = static_cast<C>(Constants::zeroChar + value);
    }

    return end;
  }

  template <typename N, typename I, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB8(N value, U8 const len, I dst) noexcept -> I {
    auto const end = dst + len;
    auto beg = end - 1;
    while (value >= 64) {
      auto const idx = value % 64 * 2;
      value /= 64;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB8[idx + 1]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB8[idx]);
    }

    if (value >= 8) {
      auto const idx = value * 2;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB8[idx + 1]);
      *beg = static_cast<C>(Constants::writeIntPrepNumsB8[idx]);
    } else {
      *beg = static_cast<C>(Constants::zeroChar + value);
    }

    return end;
  }

  template <typename N, typename I, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntB2(N value, U8 const len, I dst) noexcept -> I {
    auto const end = dst + len;
    auto beg = end - 1;
    while (value >= 16) {
      auto const idx = value % 16 * 4;
      value /= 16;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 3]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 2]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 1]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx]);
    }

    if (value >= 8) {
      auto const idx = value * 4;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 3]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 2]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 1]);
      *beg = static_cast<C>(Constants::writeIntPrepNumsB2[idx]);
    } else if (value >= 4) {
      auto const idx = value * 4;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 3]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 2]);
      *beg = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 1]);
    } else if (value >= 2) {
      auto const idx = value * 4;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 3]);
      *beg = static_cast<C>(Constants::writeIntPrepNumsB2[idx + 2]);
    } else {
      *beg = static_cast<C>(Constants::zeroChar + value);
    }

    return end;
  }

  template <typename N, typename I, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntGeneric(N value, U8 const len, I dst, U8 base, bool upper) noexcept -> I {
    return base < 10
        ? writeIntGenericUnderB10(value, len, dst, base)
        : writeIntGenericAboveB10(value, len, dst, base, upper);
  }

  template <typename N, typename I> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntGenericUnderB10(N value, U8 const len, I dst, U8 base) noexcept -> I {
    static_assert(IsUnsigned<N>::value, "Do not use this call directly, use 'writeInt' or 'writeIntGeneric' instead");
    auto const end = dst + len;
    auto beg = end - 1;
    if (value == 0) {
      *beg = Constants::zeroChar;
      return end;
    }

    while (value > 0) {
      auto dig = value % base;
      *(beg--) = static_cast<C>(StringUtilsCharConstants<C>::zeroChar + dig);
      value /= base;
    }

    return end;
  }

  template <typename N, typename I> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeIntGenericAboveB10(N value, U8 const len, I dst, U8 base, bool upper) noexcept -> I {
    static_assert(IsUnsigned<N>::value, "Do not use this call directly, use 'writeInt' or 'writeIntGeneric' instead");
    if (base >= 36) {
      assert(false && "Undefined behavior");
    }

    auto const end = dst + len;
    auto beg = end - 1;
    if (value == 0) {
      *beg = Constants::zeroChar;
      return end;
    }

    while (value > 0) {
      auto dig = value % base;
      *(beg--) = dig < 10
          ? static_cast<C>(StringUtilsCharConstants<C>::zeroChar + dig)
          : upper
              ? static_cast<C>(static_cast<unsigned>('A') + dig - 10)
              : static_cast<C>(static_cast<unsigned>('a') + dig - 10);
      value /= base;
    }

    return end;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto readIntBase(
      C const*& ptr,
      Size& len,
      U8& base
  ) noexcept -> bool {
    base = 10;
    if (len == 1u) {
      return static_cast<C>('0') <= *ptr && *ptr <= static_cast<C>('9');
    }

    if (*ptr != static_cast<C>('0')) {
      return false;
    }

    --len;
    ++ptr;

    if (*ptr == static_cast<C>('x') || *ptr == static_cast<C>('X')) {
      ++ptr;
      --len;
      base = 16;
      return true;
    }

    if (*ptr == static_cast<C>('b') || *ptr == static_cast<C>('B')) {
      ++ptr;
      --len;
      base = 2;
      return true;
    }

    base = 8;
    return static_cast<C>('0') <= *ptr && *ptr <= static_cast<C>('7');
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) static auto readInt(
      C const* ptr,
      Size len,
      C const** out,
      N* num,
      U8 base = 0u
  ) noexcept -> bool {
    if (!ptr) {
      return false;
    }

    if (out) {
      *out = ptr;
    }

    while (len > 0 && (*ptr == static_cast<C>(' ') || *ptr == static_cast<C>('\t')
                       || *ptr == static_cast<C>('\r') || *ptr == static_cast<C>('\f'))) {
      ++ptr;
      --len;
    }

    if (len == 0u) {
      return false;
    }

    N sign = 1u;
    if (*ptr == static_cast<C>('-')) {
      if (IsUnsigned<N>::value) {
        return false;
      }
      ++ptr;
      --len;
    }

    if (len == 0u) {
      return false;
    }

    if (!readIntBestFit(ptr, len, num, base)) {
      return false;
    }
    *num *= sign;
    if (out) {
      *out = ptr;
    }
    return true;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) static auto readIntBestFit(
      C const*& ptr,
      Size len,
      N* num,
      U8 base
  ) noexcept -> bool {
    if (base == 0u && !readIntBase(ptr, len, base)) {
      return false;
    }
    if (base == 10u) {
      return readIntB10(ptr, len, num);
    }
    if (base == 16u) {
      return readIntB16(ptr, len, num);
    }
    if (base == 8u) {
      return readIntB8(ptr, len, num);
    }
    if (base == 2u) {
      return readIntB2(ptr, len, num);
    }
    return readIntBAny(ptr, len, num, base);
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) static auto readIntB10(
      C const*& ptr,
      Size len,
      N* num
  ) noexcept -> bool {
    N value = 0u;
    auto anyFound = false;
    while (len > 0 && static_cast<C>('0') <= *ptr && *ptr <= static_cast<C>('9')) {
      anyFound = true;
      value = value * 10u + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('0')));
      ++ptr;
      --len;
    }

    if (!anyFound) {
      return false;
    }

    *num = value;
    return true;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) static auto readIntB16(
      C const*& ptr,
      Size len,
      N* num
  ) noexcept -> bool {
    N value = 0u;
    auto anyFound = false;
    while (len > 0) {
      if (static_cast<C>('0') <= *ptr && *ptr <= static_cast<C>('9')) {
        value = (value << 4u) + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('0')));
      } else if (static_cast<C>('a') <= *ptr && *ptr <= static_cast<C>('f')) {
        value = (value << 4u) + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('a')) + 10u);
      } else if (static_cast<C>('A') <= *ptr && *ptr <= static_cast<C>('F')) {
        value = (value << 4u) + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('A')) + 10u);
      } else {
        break;
      }

      anyFound = true;
      ++ptr;
      --len;
    }

    if (!anyFound) {
      return false;
    }

    *num = value;
    return true;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) static auto readIntB8(
      C const*& ptr,
      Size len,
      N* num
  ) noexcept -> bool {
    N value = 0u;
    auto anyFound = false;
    while (len > 0 && static_cast<C>('0') <= *ptr && *ptr <= static_cast<C>('7')) {
      value = (value << 3u) + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('0')));
      anyFound = true;
      ++ptr;
      --len;
    }

    if (!anyFound) {
      return false;
    }

    *num = value;
    return true;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) static auto readIntB2(
      C const*& ptr,
      Size len,
      N* num
  ) noexcept -> bool {
    N value = 0u;
    auto anyFound = false;
    while (len > 0 && static_cast<C>('0') == *ptr && *ptr == static_cast<C>('1')) {
      value = (value << 1u) + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('0')));
      anyFound = true;
      ++ptr;
      --len;
    }

    if (!anyFound) {
      return false;
    }

    *num = value;
    return true;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) static auto readIntBAny(
      C const*& ptr,
      Size len,
      N* num,
      U8 base
  ) noexcept -> bool {
    N value = 0u;
    auto anyFound = false;
    while (len > 0) {
      if (static_cast<C>('0') <= *ptr && *ptr <= static_cast<C>('9')) {
        value = value * base + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('0')));
      } else if (static_cast<C>('a') <= *ptr && *ptr <= static_cast<C>('z')) {
        value = value * base + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('a')) + 10u);
      } else if (static_cast<C>('A') <= *ptr && *ptr <= static_cast<C>('Z')) {
        value = value * base + (static_cast<unsigned>(*ptr) - static_cast<unsigned>(static_cast<C>('Z')) + 10u);
      } else {
        break;
      }

      anyFound = true;
      ++ptr;
      --len;
    }

    if (!anyFound) {
      return false;
    }

    *num = value;
    return true;
  }
};
} // namespace impl
} // namespace cds

#include "../../common/StringHash.hpp"

#endif // CDS_PRIMITIVE_STRING_UTILS_HPP
