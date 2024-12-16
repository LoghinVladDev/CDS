// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>

namespace {
using cds::format;
}

TEST(StandardFormatSpecificationExtTest, quotedChar) {
  ASSERT_EQ("a", format("{}", 'a'));
  ASSERT_EQ("'a'", format("{:#}", 'a'));
}

TEST(StandardFormatSpecificationExtTest, quotedString) {
  ASSERT_EQ("abcd", format("{}", "abcd"));
  ASSERT_EQ("\"abcd\"", format("{:#}", "abcd"));
}
