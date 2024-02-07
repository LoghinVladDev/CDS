// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11

#include <cds/meta/StdLib>
#include "UnitTest.hpp"

TEST(MetaBase, InConstexpr) {
  ASSERT_FALSE(cds::meta::inConstexpr());
}
