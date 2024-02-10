//
// Created by loghin on 2/10/24.
//

#ifndef CDS_TEST_SHARED_HPP
#define CDS_TEST_SHARED_HPP

#include <cds/iterator/AddressIterator>
#include <cds/Utility>

namespace testing {
template <typename I1, typename S1, typename I2, typename S2> CDS_ATTR(2(nodiscard, constexpr(14)))
auto iteq(I1 b1, S1 e1, I2 b2, S2 e2) noexcept -> bool {
  for (; b1 != e1 && b2 != e2; ++b1, ++b2) {
    if (*b1 != *b2) {
      return false;
    }
  }

  return b1 == e1 && b2 == e2;
}

template <typename L, typename R> CDS_ATTR(2(nodiscard, constexpr(14)))
auto citeq(L&& lhs, R&& rhs) noexcept -> bool {
  return iteq(cds::begin(cds::forward<L>(lhs)), cds::end(cds::forward<L>(lhs)),
              cds::begin(cds::forward<R>(rhs)), cds::end(cds::forward<R>(rhs)));
}
} // namespace testing

#endif // CDS_TEST_SHARED_HPP
