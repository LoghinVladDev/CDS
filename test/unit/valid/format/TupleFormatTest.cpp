// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>
#include <cds/Tuple>

namespace {
using cds::Tuple;

using cds::format;
} // namespace

TEST(FormatTest, tupleFormat) {
  ASSERT_EQ("(1, 2)", format("{}", Tuple<>::of(1, 2)));
  ASSERT_EQ("  (1, 2)  ", format("{:^10}", Tuple<>::of(1, 2)));
  ASSERT_EQ("    12    ", format("{:^10n}", Tuple<>::of(1, 2)));
  ASSERT_EQ("   1: 2   ", format("{:^10m}", Tuple<>::of(1, 2)));
//  ASSERT_EQ("(_1_, =2=)", format("{:_^3:=^3}", Tuple<>::of(1, 2)));
}
