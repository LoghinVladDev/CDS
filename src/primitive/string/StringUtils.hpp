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

template <typename C, typename T> struct StringUtils {
  using Traits = T;

  enum class Ordering : U8 { Less, Equal, Greater };

  CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto compare(C const* lhs, Size lhsLen, C const* rhs, Size rhsLen) noexcept -> Ordering {
    if (lhsLen == 0u && rhsLen == 0u || !lhs && !rhs) { return Ordering::Equal; }
    if (!lhs) { return Ordering::Less; }
    if (!rhs) { return Ordering::Greater; }

    auto const len = minOf(lhsLen, rhsLen);
    for (Size idx = 0u; idx < len; ++idx) {
      if (lhs[idx] < rhs[idx]) { return Ordering::Less; }
      if (lhs[idx] > rhs[idx]) { return Ordering::Greater; }
    }

    if (lhsLen < rhsLen) { return Ordering::Less; }
    if (lhsLen > rhsLen) { return Ordering::Greater; }
    return Ordering::Equal;
  }

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
};
} // namespace impl
} // namespace cds

#include "../../common/StringHash.hpp"

#endif // CDS_PRIMITIVE_STRING_UTILS_HPP
