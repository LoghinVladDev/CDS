//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_UTILS_HPP
#define CDS_PRIMITIVE_STRING_UTILS_HPP
#pragma once

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::IsBoundedArray;
using meta::RemoveCVRef;

template <typename C, typename T> class StringUtils {
public:
  using Traits = T;

  enum class Ordering { Less, Equal, Greater };

  template <typename ST, EnableIf<Not<IsBoundedArray<RemoveCVRef<ST>>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) static auto length(ST&& l) noexcept -> Size {
    return ptrLength(cds::forward<ST>(l));
  }

  template <typename ST, EnableIf<IsBoundedArray<RemoveCVRef<ST>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(ST&& l) noexcept -> Size {
    return refLength(cds::forward<ST>(l));
  }

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

private:
  CDS_ATTR(2(nodiscard, constexpr(14))) static auto ptrLength(C const* const buf) noexcept -> Size {
    if (buf == nullptr) {
      return 0u;
    }

    auto head = buf;
    for (; *head != '\0'; ++head);
    return head - buf;
  }

  template <Size len> CDS_ATTR(2(nodiscard, constexpr(11))) static auto refLength(C const (&)[len]) noexcept -> Size {
    return len - 1;
  }
};
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_UTILS_HPP
