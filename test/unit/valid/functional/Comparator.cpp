// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11-2b

#include <cds/functional/Comparator>
#include "UnitTest.hpp"

namespace {
using cds::functional::Equal;
}

TEST(Comparator, equal) {
  Equal<int> const eq1;
  Equal<int, int> const eq2;
  Equal<int, long> const eq3;

  ASSERT_TRUE(eq1(1, 1));
  ASSERT_FALSE(eq1(1, 2));
  ASSERT_FALSE(eq1(2, 1));
  ASSERT_TRUE(eq2(1, 1));
  ASSERT_FALSE(eq2(1, 2));
  ASSERT_FALSE(eq2(2, 1));
  ASSERT_TRUE(eq3(1, 1));
  ASSERT_FALSE(eq3(1, 2));
  ASSERT_FALSE(eq3(2, 1));
}

TEST(Comparator, transparent) {
  Equal<> const eq;

  ASSERT_TRUE(eq(1, 1));
  ASSERT_TRUE(eq(1, 1LLU));
}

#ifdef DCR_SINCECPP11
TEST(Comparator, constexpr11) {
  constexpr Equal<> eq;
  static_assert(eq(1, 1), "Failed constexpr");
  static_assert(!eq(0, 1), "Failed constexpr");
  static_assert(!eq(1, 0), "Failed constexpr");
}
#endif
