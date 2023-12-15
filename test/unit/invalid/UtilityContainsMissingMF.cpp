// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11-2b
// EXPECTED[compile]: failure

#include <cds/Utility>
#include "UnitTest.hpp"

using namespace cds;

TEST(MetaBase, IsSame) {
  int data[3] = {1, 2, 3};
  ASSERT_TRUE(impl::contains(data, 1));
}
