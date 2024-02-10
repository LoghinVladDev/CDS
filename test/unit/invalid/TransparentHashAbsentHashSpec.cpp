// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include <cds/functional/Hash>
#include "UnitTest.hpp"

namespace {
using cds::functional::Hash;
}

TEST(TransparentHashAbsentHashSpec, absent) {
  struct S{};
  Hash<S> const h;
  ASSERT_EQ(h(S{}), 0);
}
