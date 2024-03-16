// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include <cds/meta/Base>
#include "UnitTest.hpp"
#include <string>

using namespace cds;
using namespace cds::meta;

TEST(MetaBase, SingleIntegralAnd) {
  static_assert(Eq<And<False>, False>::value, "Failed And");
}
