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
  static char constexpr writeIntPrepNums[201]
    = "0001020304050607080910111213141516171819"
      "2021222324252627282930313233343536373839"
      "4041424344454647484950515253545556575859"
      "6061626364656667686970717273747576777879"
      "8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNums) ==
    sizeof("0001020304050607080910111213141516171819"
           "2021222324252627282930313233343536373839"
           "4041424344454647484950515253545556575859"
           "6061626364656667686970717273747576777879"
           "8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNums size");
};

template <> struct StringUtilsConstants<char> : StringUtilsCharConstants<> {};

template <typename T> char const StringUtilsCharConstants<T>::minusChar;
template <typename T> char const StringUtilsCharConstants<T>::zeroChar;
template <typename T> char const StringUtilsCharConstants<T>::writeIntPrepNums[201];

template <typename = void> struct StringUtilsWCharConstants {
  static wchar_t constexpr minusChar = L'-';
  static wchar_t constexpr zeroChar = L'0';
  static wchar_t constexpr writeIntPrepNums[201]
    = L"0001020304050607080910111213141516171819"
      L"2021222324252627282930313233343536373839"
      L"4041424344454647484950515253545556575859"
      L"6061626364656667686970717273747576777879"
      L"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNums) ==
    sizeof(L"0001020304050607080910111213141516171819"
           L"2021222324252627282930313233343536373839"
           L"4041424344454647484950515253545556575859"
           L"6061626364656667686970717273747576777879"
           L"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNums size");
};

template <> struct StringUtilsConstants<wchar_t> : StringUtilsWCharConstants<> {};

template <typename T> wchar_t const StringUtilsWCharConstants<T>::minusChar;
template <typename T> wchar_t const StringUtilsWCharConstants<T>::zeroChar;
template <typename T> wchar_t const StringUtilsWCharConstants<T>::writeIntPrepNums[201];

template <typename = void> struct StringUtilsChar16Constants {
  static char16_t constexpr minusChar = u'-';
  static char16_t constexpr zeroChar = u'0';
  static char16_t constexpr writeIntPrepNums[201]
    = u"0001020304050607080910111213141516171819"
      u"2021222324252627282930313233343536373839"
      u"4041424344454647484950515253545556575859"
      u"6061626364656667686970717273747576777879"
      u"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNums) ==
    sizeof(u"0001020304050607080910111213141516171819"
           u"2021222324252627282930313233343536373839"
           u"4041424344454647484950515253545556575859"
           u"6061626364656667686970717273747576777879"
           u"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNums size");
};

template <> struct StringUtilsConstants<char16_t> : StringUtilsChar16Constants<> {};

template <typename T> char16_t const StringUtilsChar16Constants<T>::minusChar;
template <typename T> char16_t const StringUtilsChar16Constants<T>::zeroChar;
template <typename T> char16_t const StringUtilsChar16Constants<T>::writeIntPrepNums[201];

template <typename = void> struct StringUtilsChar32Constants {
  static char32_t constexpr minusChar = U'-';
  static char32_t constexpr zeroChar = U'0';
  static char32_t constexpr writeIntPrepNums[201]
    = U"0001020304050607080910111213141516171819"
      U"2021222324252627282930313233343536373839"
      U"4041424344454647484950515253545556575859"
      U"6061626364656667686970717273747576777879"
      U"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNums) ==
    sizeof(U"0001020304050607080910111213141516171819"
           U"2021222324252627282930313233343536373839"
           U"4041424344454647484950515253545556575859"
           U"6061626364656667686970717273747576777879"
           U"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNums size");
};

template <> struct StringUtilsConstants<char32_t> : StringUtilsChar32Constants<> {};

template <typename T> char32_t const StringUtilsChar32Constants<T>::minusChar;
template <typename T> char32_t const StringUtilsChar32Constants<T>::zeroChar;
template <typename T> char32_t const StringUtilsChar32Constants<T>::writeIntPrepNums[201];

#if CDS_ATTR(cpp20)
template <typename = void> struct StringUtilsChar8Constants {
  static char8_t constexpr minusChar = u8'-';
  static char8_t constexpr zeroChar = u8'0';
  static char8_t constexpr writeIntPrepNums[201]
    = u8"0001020304050607080910111213141516171819"
      u8"2021222324252627282930313233343536373839"
      u8"4041424344454647484950515253545556575859"
      u8"6061626364656667686970717273747576777879"
      u8"8081828384858687888990919293949596979899";
  static_assert(sizeof(writeIntPrepNums) ==
    sizeof(u8"0001020304050607080910111213141516171819"
           u8"2021222324252627282930313233343536373839"
           u8"4041424344454647484950515253545556575859"
           u8"6061626364656667686970717273747576777879"
           u8"8081828384858687888990919293949596979899"), "Unexpected writeIntPrepNums size");
};

template <typename T> char8_t const StringUtilsChar8Constants<T>::minusChar;
template <typename T> char8_t const StringUtilsChar8Constants<T>::zeroChar;
template <typename T> char8_t const StringUtilsChar8Constants<T>::writeIntPrepNums[201];

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

  template <typename N, typename I, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeInt(N value, U8 len, I dst) noexcept -> I {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    auto const uns = neg
        ? static_cast<U>(~value) + 1u
        : static_cast<U>(value);
    if (neg) {
      *(dst++) = Constants::minusChar;
      --len;
    }
    return writeInt(uns, len, dst);
  }

  template <typename N, typename I, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeInt(N value, U8 const len, I dst) noexcept -> I {
    auto const end = dst + len;
    auto beg = end - 1;
    while (value >= 100) {
      auto const idx = value % 100 * 2;
      value /= 100;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNums[idx + 1]);
      *(beg--) = static_cast<C>(Constants::writeIntPrepNums[idx]);
    }

    if (value >= 10) {
      auto const idx = value * 2;
      *(beg--) = static_cast<C>(Constants::writeIntPrepNums[idx + 1]);
      *beg = static_cast<C>(Constants::writeIntPrepNums[idx]);
    } else {
      *beg = static_cast<C>(Constants::zeroChar + value);
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
