// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include "UnitTest.hpp"
#include "../../../src/meta/Base.hpp"
#include <string>

using namespace cds;
using namespace cds::meta;

TEST(MetaBase, IsSame) {
  static_assert(IsSame<S32, S16>::value, "Failed IsSame");
}
