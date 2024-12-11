// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>
#include <cds/exception/FormatException>

namespace {
using cds::FormatException;

using cds::format;
} // namespace

TEST(FormatTest, fmtStandardFormatSpecExamples) {
  char c = 120;
  ASSERT_EQ(format("{:6}", 42),    "    42");
  ASSERT_EQ(format("{:6}", 'x'),   "x     ");
  ASSERT_EQ(format("{:*<6}", 'x'), "x*****");
  ASSERT_EQ(format("{:*>6}", 'x'), "*****x");
  ASSERT_EQ(format("{:*^6}", 'x'), "**x***");
  ASSERT_EQ(format("{:6d}", c),"   120");
  ASSERT_EQ(format("{:6}", true),  "true  ");

  ASSERT_EQ(format("{0:},{0:+},{0:-},{0: }", 1),  "1,+1,1, 1");
  ASSERT_EQ(format("{0:},{0:+},{0:-},{0: }", 1u), "1,+1,1, 1");
  ASSERT_EQ(format("{0:},{0:+},{0:-},{0: }", -1), "-1,-1,-1,-1");

  ASSERT_EQ(format("{:+06d}", c), "+00120");
  ASSERT_EQ(format("{:#06x}", 0xa),   "0x000a");
  ASSERT_EQ(format("{:<06}", -42),    "-42   ");

  ASSERT_EQ(format("[{:?}]", "h\tllo"), "[h\\tllo]");
  ASSERT_EQ(format("[{:?}] [{:?}]", '\'', '"'), "[\\'] [\"]");
  ASSERT_EQ(format("[{:?}] [{:?}]", "'", "\""), "['] [\\\"]");
}
