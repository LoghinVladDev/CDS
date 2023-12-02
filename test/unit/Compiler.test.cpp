// DCR-TEST
// STEPS: compile,run
// STD: 11+
// EXPECTED[compile]: success

#include "UnitTest.hpp"
#include "../../src/meta/Compiler.hpp"

TEST(Test, Test) {
  ASSERT_EQ(f(), 5);
}
