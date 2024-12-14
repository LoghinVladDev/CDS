// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>
#include <cds/collection/Vector>

namespace {
using cds::meta::Common;

using cds::FormatException;
using cds::Vector;

using cds::format;
using cds::ignore;
using cds::makeTuple;
using cds::impl::fwd;

template <typename... Ts> auto makeVector(Ts&&... values) -> Vector<Common<Ts...>> {
  return Vector<Common<Ts...>>{fwd<Ts>(values)...};
}
} // namespace

TEST(RangeFormatTest, vectorFormat) {
  ASSERT_EQ("[1, 2, 3, 4]", format("{}", makeVector(1, 2, 3, 4)));
  ASSERT_EQ("1, 2, 3, 4", format("{:n}", makeVector(1, 2, 3, 4)));

  auto ints = makeVector(12, 10, 15, 14);
  ASSERT_EQ("[12, 10, 15, 14]", format("{}", ints));
  ASSERT_EQ("[C, A, F, E]", format("{::X}", ints));
  ASSERT_EQ("_12_, _10_, _15_, _14_", format("{:n:_^4}", ints));

  auto charTuples = makeVector(makeTuple('A', 5), makeTuple('B', 10), makeTuple('C', 12));
  ASSERT_EQ("[(A, 5), (B, 10), (C, 12)]", format("{}", charTuples));
  ASSERT_EQ("{A: 5, B: 10, C: 12}", format("{:m}", charTuples));
}
