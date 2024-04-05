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

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::IsBoundedArray;
using meta::RemoveCVRef;
using meta::IsSigned;
using meta::IsUnsigned;
using meta::UnsignedEquivalent;

template <typename C, typename T> struct StringUtils {
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
    auto nbeg = Abs::data(cds::forward<N>(needle)) + nlen - 1;
    auto beg = str + len - 1;
    auto const nend = nbeg - nlen;
    for (auto const end = beg - len; beg != end && nbeg != nend; --beg, --nbeg) {
      if (*beg != *nbeg) {
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
      } else if (value < b2) {
        return cnt + 1;
      } else if (value < b3) {
        return cnt + 2;
      } else if (value < b4) {
        return cnt + 3;
      }

      value /= b4;
      cnt += 4;
    }

    unreachable();
  }

  template <typename N, EnableIf<IsSigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeInt(N value, U8 len, C* dst) noexcept -> C* {
    using U = UnsignedEquivalent<N>;
    auto const neg = value < 0;
    auto const uns = neg
        ? static_cast<U>(~value) + 1u
        : static_cast<U>(value);
    if (neg) {
      *(dst++) = '-';
      --len;
    }
    return writeInt(uns, len, dst);
  }

  template <typename N, EnableIf<IsUnsigned<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto writeInt(N value, U8 const len, C* dst) noexcept -> C* {
    char constexpr prepNums[] =
        "0001020304050607080910111213141516171819"
        "2021222324252627282930313233343536373839"
        "4041424344454647484950515253545556575859"
        "6061626364656667686970717273747576777879"
        "8081828384858687888990919293949596979899";
    auto const end = dst + len;
    auto beg = end - 1;
    while (value >= 100) {
      auto const idx = value % 100 * 2;
      value /= 100;
      *(beg--) = static_cast<C>(prepNums[idx + 1]);
      *(beg--) = static_cast<C>(prepNums[idx]);
    }

    if (value >= 10) {
      auto const idx = value * 2;
      *(beg--) = static_cast<C>(prepNums[idx + 1]);
      *beg = static_cast<C>(prepNums[idx]);
    } else {
      *beg = static_cast<C>('0' + value);
    }

    return end;
  }

  static auto floatingLength(float value) noexcept -> U8 {
    return snprintf(nullptr, 0, "%f", value);
  }

  static auto floatingLength(double value) noexcept -> U8 {
    return snprintf(nullptr, 0, "%lf", value);
  }

  static auto floatingLength(long double value) noexcept -> U8 {
    return snprintf(nullptr, 0, "%Lf", value);
  }

  static auto writeFloating(float value, U8 length, C* dst) noexcept -> C* {
    ignore = snprintf(dst, length + 1u, "%f", value);
    return dst + length;
  }

  static auto writeFloating(double value, U8 length, C* dst) noexcept -> C* {
    ignore = snprintf(dst, length + 1u, "%lf", value);
    return dst + length;
  }

  static auto writeFloating(long double value, U8 length, C* dst) noexcept -> C* {
    ignore = snprintf(dst, length + 1u, "%Lf", value);
    return dst + length;
  }
};
} // namespace impl
} // namespace cds

#include "../../common/StringHash.hpp"

#endif // CDS_PRIMITIVE_STRING_UTILS_HPP
