// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>
#include <cds/Tuple>

namespace {
using cds::FormatException;
using cds::Tuple;

using cds::format;
using cds::ignore;
} // namespace

TEST(TupleFormatTest, tupleFormat) {
  ASSERT_EQ("(1, 2)", format("{}", Tuple<>::of(1, 2)));
  ASSERT_EQ("  (1, 2)  ", format("{:^10}", Tuple<>::of(1, 2)));
  ASSERT_EQ("    12    ", format("{:^10n}", Tuple<>::of(1, 2)));
  ASSERT_EQ("   1: 2   ", format("{:^10m}", Tuple<>::of(1, 2)));
  ASSERT_EQ("(_1_, 2)", format("{::_^3}", Tuple<>::of(1, 2)));
  ASSERT_EQ("(_1_, 2)", format("{::_^3:}", Tuple<>::of(1, 2)));
  ASSERT_EQ("(_1_, =2=)", format("{::_^3:=^3}", Tuple<>::of(1, 2)));
  ASSERT_EQ("(1, =2=)", format("{:::=^3}", Tuple<>::of(1, 2)));
  ASSERT_EQ("1: 2", format("{:m}", Tuple<>::of(1, 2)));
  ASSERT_EQ("12", format("{:n}", Tuple<>::of(1, 2)));
}

#ifndef DCR_SINCECPP20
TEST(TupleFormatTest, tupleParseExceptions) {
  try {
    ignore = format("{:m}", Tuple<>::of(1, 2, 3));
    ASSERT_FALSE(true);
  } catch (FormatException const& e) {
    ASSERT_EQ("Cannot use map-like tuple presentation type with a "
              "tuple-like without exactly two underlying types",
              e.message());
  }

  try {
    ignore = format("{:m}", Tuple<>::of(1));
    ASSERT_FALSE(true);
  } catch (FormatException const& e) {
    ASSERT_EQ("Cannot use map-like tuple presentation type with a "
              "tuple-like without exactly two underlying types",
              e.message());
  }

  try {
    ignore = format("{:mx}", Tuple<>::of(1, 2));
    ASSERT_FALSE(true);
  } catch (FormatException const& e) {
    ASSERT_EQ("Extraneous characters in format string",
              e.message());
  }

  try {
    ignore = format("{:m:::}", Tuple<>::of(1, 2));
    ASSERT_FALSE(true);
  } catch (FormatException const& e) {
    ASSERT_EQ("Number of format specifications exceeds tuple entry count and tuple specification",
              e.message());
  }
}
#endif // #ifndef DCR_SINCECPP20
