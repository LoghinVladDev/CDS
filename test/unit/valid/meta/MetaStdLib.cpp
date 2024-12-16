// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:clang;apple:clang)
// STD: 11

#include <cds/meta/StdLib>
#include "UnitTest.hpp"

constexpr bool validation() {
  return cds::meta::inConstexpr();
}

TEST(MetaBase, InConstexpr) {
  static_assert(validation(), "Failed actual in-constexpr detection");
#if CDS_ATTR(emulated_in_constexpr)
  ASSERT_TRUE(cds::meta::inConstexpr());
#else
  ASSERT_FALSE(cds::meta::inConstexpr());
#endif
}
