// DCR-TEST
// STEPS: compile(linux:clang;linux:gcc),run(linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include "../../../src/meta/Compiler.hpp"

TEST(Test, Test) {
  ASSERT_EQ(f(), 5);
}
