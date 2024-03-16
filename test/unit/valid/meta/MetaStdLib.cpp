// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11

#include <cds/meta/StdLib>
#include "UnitTest.hpp"

constexpr bool validation() {
  return cds::meta::inConstexpr();
}

TEST(MetaBase, InConstexpr) {
  static_assert(validation(), "Failed actual in-constexpr detection");
  ASSERT_FALSE(cds::meta::inConstexpr());
}
