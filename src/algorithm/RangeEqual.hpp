//
// Created by loghin on 6/5/25.
//

#ifndef CDS_ALGORITHM_RANGE_EQUAL_HPP
#define CDS_ALGORITHM_RANGE_EQUAL_HPP
#pragma once

#include <cds/functional/Comparator>

namespace cds {
namespace impl {
using functional::Equal;

template <typename I0, typename I1, typename S0, typename S1, typename E = Equal<>>
CDS_ATTR(2(nodiscard, constexpr(14))) auto equal(I0 i0, S0 e0, I1 i1, S1 e1, E const& eq = {}) noexcept -> bool {
  for (; i0 != e0 && i1 != e1; ++i0, ++i1) {
    if (!eq(*i0, *i1)) {
      return false;
    }
  }

  return i0 == e0 && i1 == e1;
}
} // namespace impl
} // namespace cds

#endif // CDS_ALGORITHM_RANGE_EQUAL_HPP
