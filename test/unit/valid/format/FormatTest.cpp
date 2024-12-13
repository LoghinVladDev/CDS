// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>
#include <cds/exception/FormatException>

namespace {
using cds::Address;
using cds::FormatException;
using cds::String;

using cds::bitCast;
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

  float pi = 3.14f;
  ASSERT_EQ(format("{:10f}", pi),   "  3.140000");
  ASSERT_EQ(format("{:.5f}", pi),   "3.14000");
  ASSERT_EQ(format("{:10.5f}", pi), "   3.14000");

  ASSERT_EQ(format("[{:?}]", "h\tllo"), "[h\\tllo]");
  ASSERT_EQ(format("[{:?}] [{:?}]", '\'', '"'), "[\\'] [\"]");
  ASSERT_EQ(format("[{:?}] [{:?}]", "'", "\""), "['] [\\\"]");
}

TEST(FormatTest, dynamicFormat) {
  String fmt = "ab{:#06x}cd";
  ASSERT_EQ(vformat(fmt, 255), "ab0x00ffcd");
}

TEST(FormatTest, callableString) {
  using namespace cds::literals;
  ASSERT_EQ("ab{:#06x}cd"_f(255), "ab0x00ffcd");
}

TEST(FormatTest, pointerTest) {
  Address addr = 0xabcdef0123456789;
  auto asPtr = bitCast<void const*>(addr);
  ASSERT_EQ(format("{}", asPtr), "0xabcdef0123456789");
  ASSERT_EQ(format("{:p}", asPtr), "0xabcdef0123456789");
  ASSERT_EQ(format("{:P}", asPtr), "0XABCDEF0123456789");
  ASSERT_EQ(format("{:<20p}", asPtr), "0xabcdef0123456789  ");
  ASSERT_EQ(format("{:^20p}", asPtr), " 0xabcdef0123456789 ");
  ASSERT_EQ(format("{:>20p}", asPtr), "  0xabcdef0123456789");
}
