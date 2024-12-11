// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>
#include <cds/String>
#include <cds/StringView>
#include <cds/Tuple>
#include <cds/Union>
#include <cds/collection/Vector>
#include <cds/exception/FormatException>
#include "../Shared.hpp"

namespace {
using cds::FormatException;
using cds::StringView;
using cds::Tuple;
using cds::S16;
using cds::S32;
using cds::S64;
using cds::Union;
using cds::U16;
using cds::U32;
using cds::U64;
using cds::Vector;

using cds::format;
using cds::ignore;
using cds::nullopt;

using cds::impl::fmt::FormatAlignType;
using cds::impl::fmt::FormatFillAlignSpecification;
using cds::impl::fmt::FormatNumberSignType;
using cds::impl::fmt::FormatNumberSpecification;
using cds::impl::fmt::FormatSizeSpecification;
using cds::impl::fmt::FormatTypeFlags;
using cds::impl::fmt::FormatTypeFlagBits;
using cds::impl::fmt::FormatWidthSpecification;

using cds::impl::fmt::formatParseFillAlign;
using cds::impl::fmt::formatParseNumber;
using cds::impl::fmt::formatParseWidth;
using cds::impl::fmt::formatParseType;

template <typename T> auto tFlags(T flag) -> FormatTypeFlags {
  return static_cast<FormatTypeFlags>(flag);
}

template <typename F, typename... Ts> auto tFlags(F flag, Ts... flags) -> FormatTypeFlags {
  return static_cast<FormatTypeFlags>(flag) | tFlags(flags...);
}

template <typename T> auto fmtParseStringTypeTest() -> void {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), tFlags(FormatTypeFlagBits::String)),
            (formatParseType<T, char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "s";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, tFlags(FormatTypeFlagBits::String)),
            (formatParseType<T, char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "sd";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 1, tFlags(FormatTypeFlagBits::String)),
            (formatParseType<T, char>(cds::begin(str2), cds::end(str2))));

  try {
    char const stre[] = "d";
    ignore = formatParseType<T, char>(cds::begin(stre), cds::end(stre));
    ASSERT_FALSE(true);
  } catch (FormatException const& fmtE) {
    ASSERT_EQ("Presentation type specifier is invalid", fmtE.message());
  }

  char const str3[] = "?";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3) + 1, tFlags(FormatTypeFlagBits::String, FormatTypeFlagBits::Escaped)),
            (formatParseType<T, char>(cds::begin(str3), cds::end(str3))));
}

template <typename T> auto fmtParseIntegerTypeTest() -> void {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), tFlags(FormatTypeFlagBits::Decimal)),
            (formatParseType<T, char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "d";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, tFlags(FormatTypeFlagBits::Decimal)),
            (formatParseType<T, char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "ds";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 1, tFlags(FormatTypeFlagBits::Decimal)),
            (formatParseType<T, char>(cds::begin(str2), cds::end(str2))));

  try {
    char const stre[] = "s";
    ignore = formatParseType<T, char>(cds::begin(stre), cds::end(stre));
    ASSERT_FALSE(true);
  } catch (FormatException const& fmtE) {
    ASSERT_EQ("Presentation type specifier is invalid", fmtE.message());
  }

  char const str3[] = "b";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3) + 1, tFlags(FormatTypeFlagBits::Binary)),
            (formatParseType<T, char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "B";
  ASSERT_EQ(Tuple<>::of(cds::begin(str4) + 1, tFlags(FormatTypeFlagBits::Binary, FormatTypeFlagBits::Uppercase)),
            (formatParseType<T, char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = "c";
  ASSERT_EQ(Tuple<>::of(cds::begin(str5) + 1, tFlags(FormatTypeFlagBits::Character)),
            (formatParseType<T, char>(cds::begin(str5), cds::end(str5))));

  char const str6[] = "o";
  ASSERT_EQ(Tuple<>::of(cds::begin(str6) + 1, tFlags(FormatTypeFlagBits::Octal)),
            (formatParseType<T, char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = "x";
  ASSERT_EQ(Tuple<>::of(cds::begin(str7) + 1, tFlags(FormatTypeFlagBits::Hex)),
            (formatParseType<T, char>(cds::begin(str7), cds::end(str7))));

  char const str8[] = "X";
  ASSERT_EQ(Tuple<>::of(cds::begin(str8) + 1, tFlags(FormatTypeFlagBits::Hex, FormatTypeFlagBits::Uppercase)),
            (formatParseType<T, char>(cds::begin(str8), cds::end(str8))));
}

template <typename T> auto fmtParseFloatingTypeTest() -> void {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), tFlags(FormatTypeFlagBits::General)),
            (formatParseType<T, char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "g";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, tFlags(FormatTypeFlagBits::General)),
            (formatParseType<T, char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "gs";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 1, tFlags(FormatTypeFlagBits::General)),
            (formatParseType<T, char>(cds::begin(str2), cds::end(str2))));

  try {
    char const stre[] = "s";
    ignore = formatParseType<T, char>(cds::begin(stre), cds::end(stre));
    ASSERT_FALSE(true);
  } catch (FormatException const& fmtE) {
    ASSERT_EQ("Presentation type specifier is invalid", fmtE.message());
  }

  char const str3[] = "a";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3) + 1, tFlags(FormatTypeFlagBits::Hex)),
            (formatParseType<T, char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "A";
  ASSERT_EQ(Tuple<>::of(cds::begin(str4) + 1, tFlags(FormatTypeFlagBits::Hex, FormatTypeFlagBits::Uppercase)),
            (formatParseType<T, char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = "e";
  ASSERT_EQ(Tuple<>::of(cds::begin(str5) + 1, tFlags(FormatTypeFlagBits::Scientific)),
            (formatParseType<T, char>(cds::begin(str5), cds::end(str5))));

  char const str6[] = "E";
  ASSERT_EQ(Tuple<>::of(cds::begin(str6) + 1, tFlags(FormatTypeFlagBits::Scientific, FormatTypeFlagBits::Uppercase)),
            (formatParseType<T, char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = "f";
  ASSERT_EQ(Tuple<>::of(cds::begin(str7) + 1, tFlags(FormatTypeFlagBits::Fixed)),
            (formatParseType<T, char>(cds::begin(str7), cds::end(str7))));

  char const str8[] = "F";
  ASSERT_EQ(Tuple<>::of(cds::begin(str8) + 1, tFlags(FormatTypeFlagBits::Fixed, FormatTypeFlagBits::Uppercase)),
            (formatParseType<T, char>(cds::begin(str8), cds::end(str8))));

  char const str9[] = "G";
  ASSERT_EQ(Tuple<>::of(cds::begin(str9) + 1, tFlags(FormatTypeFlagBits::General, FormatTypeFlagBits::Uppercase)),
            (formatParseType<T, char>(cds::begin(str9), cds::end(str9))));
}


template <typename T> auto fmtParsePointerTypeTest() -> void {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), tFlags(FormatTypeFlagBits::Pointer)),
            (formatParseType<T, char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "p";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, tFlags(FormatTypeFlagBits::Pointer)),
            (formatParseType<T, char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "ps";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 1, tFlags(FormatTypeFlagBits::Pointer)),
            (formatParseType<T, char>(cds::begin(str2), cds::end(str2))));

  try {
    char const stre[] = "s";
    ignore = formatParseType<T, char>(cds::begin(stre), cds::end(stre));
    ASSERT_FALSE(true);
  } catch (FormatException const& fmtE) {
    ASSERT_EQ("Presentation type specifier is invalid", fmtE.message());
  }

  char const str3[] = "P";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3) + 1, tFlags(FormatTypeFlagBits::Pointer, FormatTypeFlagBits::Uppercase)),
            (formatParseType<T, char>(cds::begin(str3), cds::end(str3))));
}
} // namespace

TEST(StandardFormatSpecificationTest, formatParseFillAlign) {
  char const str0[] = "6";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str0), FormatFillAlignSpecification<char>(nullopt, ' ')),
      (formatParseFillAlign<int, char>(cds::begin(str0), cds::end(str0)))
  );
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str0), FormatFillAlignSpecification<char>(nullopt, ' ')),
      (formatParseFillAlign<char, char>(cds::begin(str0), cds::end(str0)))
  );
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str0), FormatFillAlignSpecification<char>(nullopt, ' ')),
      (formatParseFillAlign<bool, char>(cds::begin(str0), cds::end(str0)))
  );

  char const str1[] = "6d";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str1), FormatFillAlignSpecification<char>(nullopt, ' ')),
      (formatParseFillAlign<int, char>(cds::begin(str1), cds::end(str1)))
  );

  char const str2[] = "*<6";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str2) + 2, FormatFillAlignSpecification<char>(FormatAlignType::Leading, '*')),
      (formatParseFillAlign<int, char>(cds::begin(str2), cds::end(str2)))
  );

  char const str3[] = "*>6";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str3) + 2, FormatFillAlignSpecification<char>(FormatAlignType::Trailing, '*')),
      (formatParseFillAlign<int, char>(cds::begin(str3), cds::end(str3)))
  );

  char const str4[] = "*^6";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str4) + 2, FormatFillAlignSpecification<char>(FormatAlignType::Centre, '*')),
      (formatParseFillAlign<int, char>(cds::begin(str4), cds::end(str4)))
  );

  char const str5[] = "*^";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str5) + 2, FormatFillAlignSpecification<char>(FormatAlignType::Centre, '*')),
      (formatParseFillAlign<int, char>(cds::begin(str5), cds::end(str5)))
  );

  char const str6[] = "";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str6), FormatFillAlignSpecification<char>(nullopt, ' ')),
      (formatParseFillAlign<int, char>(cds::begin(str6), cds::end(str6)))
  );

  char const str7[] = "d";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str7), FormatFillAlignSpecification<char>(nullopt, ' ')),
      (formatParseFillAlign<int, char>(cds::begin(str7), cds::end(str7)))
  );

  char const str8[] = "^8";
  ASSERT_EQ(
      Tuple<>::of(cds::begin(str8) + 1, FormatFillAlignSpecification<char>(FormatAlignType::Centre, ' ')),
      (formatParseFillAlign<int, char>(cds::begin(str8), cds::end(str8)))
  );
}

TEST(StandardFormatSpecificationTest, formatParseNumber) {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), FormatNumberSpecification{FormatNumberSignType::Negative, false, false}),
            (formatParseNumber<char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "+";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, FormatNumberSpecification{FormatNumberSignType::PositiveNegative, false, false}),
            (formatParseNumber<char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "-";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 1, FormatNumberSpecification{FormatNumberSignType::Negative, false, false}),
            (formatParseNumber<char>(cds::begin(str2), cds::end(str2))));

  char const str3[] = " ";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3) + 1, FormatNumberSpecification{FormatNumberSignType::SpaceNegative, false, false}),
            (formatParseNumber<char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "#";
  ASSERT_EQ(Tuple<>::of(cds::begin(str4) + 1, FormatNumberSpecification{FormatNumberSignType::Negative, true, false}),
            (formatParseNumber<char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = " #";
  ASSERT_EQ(Tuple<>::of(cds::begin(str5) + 2, FormatNumberSpecification{FormatNumberSignType::SpaceNegative, true, false}),
            (formatParseNumber<char>(cds::begin(str5), cds::end(str5))));

  char const str6[] = "0";
  ASSERT_EQ(Tuple<>::of(cds::begin(str6) + 1, FormatNumberSpecification{FormatNumberSignType::Negative, false, true}),
            (formatParseNumber<char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = " 0";
  ASSERT_EQ(Tuple<>::of(cds::begin(str7) + 2, FormatNumberSpecification{FormatNumberSignType::SpaceNegative, false, true}),
            (formatParseNumber<char>(cds::begin(str7), cds::end(str7))));

  char const str8[] = "#0";
  ASSERT_EQ(Tuple<>::of(cds::begin(str8) + 2, FormatNumberSpecification{FormatNumberSignType::Negative, true, true}),
            (formatParseNumber<char>(cds::begin(str8), cds::end(str8))));

  char const str9[] = "+#0";
  ASSERT_EQ(Tuple<>::of(cds::begin(str9) + 3, FormatNumberSpecification{FormatNumberSignType::PositiveNegative, true, true}),
            (formatParseNumber<char>(cds::begin(str9), cds::end(str9))));

  char const str10[] = "+#1";
  ASSERT_EQ(Tuple<>::of(cds::begin(str10) + 2, FormatNumberSpecification{FormatNumberSignType::PositiveNegative, true, false}),
            (formatParseNumber<char>(cds::begin(str10), cds::end(str10))));
}

TEST(StandardFormatSpecificationTest, formatParseWidth) {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), FormatWidthSpecification{}),
            (formatParseWidth<char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "5";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, FormatWidthSpecification{5}),
            (formatParseWidth<char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "{}";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 2, FormatWidthSpecification{FormatSizeSpecification{}}),
            (formatParseWidth<char>(cds::begin(str2), cds::end(str2))));

  char const str3[] = "d";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3), FormatWidthSpecification{}),
            (formatParseWidth<char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "5d";
  ASSERT_EQ(Tuple<>::of(cds::begin(str4) + 1, FormatWidthSpecification{FormatSizeSpecification{5}}),
            (formatParseWidth<char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = "{1}";
  ASSERT_EQ(Tuple<>::of(cds::begin(str5) + 3, FormatWidthSpecification{FormatSizeSpecification{nullopt, 1}}),
            (formatParseWidth<char>(cds::begin(str5), cds::end(str5))));

  try {
    char const stre0[] = "{";
    ignore = formatParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field in width specifier not terminated",
        e.message()
    );
  }

  try {
    char const stre0[] = "{10";
    ignore = formatParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field in width specifier not terminated",
        e.message()
    );
  }

  try {
    char const stre0[] = "{10d";
    ignore = formatParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field in width specifier not terminated",
        e.message()
    );
  }

  try {
    char const stre0[] = "{n}";
    ignore = formatParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field with invalid explicit argument index",
        e.message()
    );
  }

  char const str6[] = ".5";
  ASSERT_EQ(Tuple<>::of(cds::begin(str6) + 2, FormatWidthSpecification{nullopt, FormatSizeSpecification{5}}),
            (formatParseWidth<char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = "10.5";
  ASSERT_EQ(Tuple<>::of(cds::begin(str7) + 4, FormatWidthSpecification{FormatSizeSpecification{10}, FormatSizeSpecification{5}}),
            (formatParseWidth<char>(cds::begin(str7), cds::end(str7))));

  try {
    char const stre0[] = ".";
    ignore = formatParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Precision specification not followed by precision",
        e.message()
    );
  }

  char const str8[] = "10.{}";
  ASSERT_EQ(Tuple<>::of(cds::begin(str8) + 5, FormatWidthSpecification{FormatSizeSpecification{10}, FormatSizeSpecification{}}),
            (formatParseWidth<char>(cds::begin(str8), cds::end(str8))));

  char const str9[] = "{}.{}";
  ASSERT_EQ(Tuple<>::of(cds::begin(str9) + 5, FormatWidthSpecification{FormatSizeSpecification{}, FormatSizeSpecification{}}),
            (formatParseWidth<char>(cds::begin(str9), cds::end(str9))));
}

TEST(StandardFormatSpecificationTest, fmtParseStringType) {
  fmtParseStringTypeTest<char*>();
  fmtParseStringTypeTest<char const*>();
  fmtParseStringTypeTest<char[]>();
  fmtParseStringTypeTest<char[20]>();
  fmtParseStringTypeTest<std::string>();
  fmtParseStringTypeTest<cds::String>();
  fmtParseStringTypeTest<cds::StringView>();
#if DCR_SINCECPP17
  fmtParseStringTypeTest<std::string_view>();
#endif
}

TEST(StandardFormatSpecificationTest, fmtParseIntegerType) {
  fmtParseIntegerTypeTest<int>();
  fmtParseIntegerTypeTest<S16>();
  fmtParseIntegerTypeTest<S32>();
  fmtParseIntegerTypeTest<S64>();
  fmtParseIntegerTypeTest<U16>();
  fmtParseIntegerTypeTest<U32>();
  fmtParseIntegerTypeTest<U64>();
}

TEST(StandardFormatSpecificationTest, fmtParseCharType) {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), tFlags(FormatTypeFlagBits::Character)),
            (formatParseType<char, char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "c";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, tFlags(FormatTypeFlagBits::Character)),
            (formatParseType<char, char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "cs";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 1, tFlags(FormatTypeFlagBits::Character)),
            (formatParseType<char, char>(cds::begin(str2), cds::end(str2))));

  try {
    char const stre[] = "s";
    ignore = formatParseType<char, char>(cds::begin(stre), cds::end(stre));
    ASSERT_FALSE(true);
  } catch (FormatException const& fmtE) {
    ASSERT_EQ("Presentation type specifier is invalid", fmtE.message());
  }

  char const str3[] = "b";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3) + 1, tFlags(FormatTypeFlagBits::Binary)),
            (formatParseType<char, char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "B";
  ASSERT_EQ(Tuple<>::of(cds::begin(str4) + 1, tFlags(FormatTypeFlagBits::Binary, FormatTypeFlagBits::Uppercase)),
            (formatParseType<char, char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = "d";
  ASSERT_EQ(Tuple<>::of(cds::begin(str5) + 1, tFlags(FormatTypeFlagBits::Decimal)),
            (formatParseType<char, char>(cds::begin(str5), cds::end(str5))));

  char const str6[] = "o";
  ASSERT_EQ(Tuple<>::of(cds::begin(str6) + 1, tFlags(FormatTypeFlagBits::Octal)),
            (formatParseType<char, char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = "x";
  ASSERT_EQ(Tuple<>::of(cds::begin(str7) + 1, tFlags(FormatTypeFlagBits::Hex)),
            (formatParseType<char, char>(cds::begin(str7), cds::end(str7))));

  char const str8[] = "X";
  ASSERT_EQ(Tuple<>::of(cds::begin(str8) + 1, tFlags(FormatTypeFlagBits::Hex, FormatTypeFlagBits::Uppercase)),
            (formatParseType<char, char>(cds::begin(str8), cds::end(str8))));

  char const str9[] = "?";
  ASSERT_EQ(Tuple<>::of(cds::begin(str9) + 1, tFlags(FormatTypeFlagBits::Character, FormatTypeFlagBits::Escaped)),
            (formatParseType<char, char>(cds::begin(str9), cds::end(str9))));
}

TEST(StandardFormatSpecificationTest, fmtParseBoolType) {
  char const str0[] = "";
  ASSERT_EQ(Tuple<>::of(cds::begin(str0), tFlags(FormatTypeFlagBits::String)),
            (formatParseType<bool, char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "s";
  ASSERT_EQ(Tuple<>::of(cds::begin(str1) + 1, tFlags(FormatTypeFlagBits::String)),
            (formatParseType<bool, char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "sc";
  ASSERT_EQ(Tuple<>::of(cds::begin(str2) + 1, tFlags(FormatTypeFlagBits::String)),
            (formatParseType<bool, char>(cds::begin(str2), cds::end(str2))));

  try {
    char const stre[] = "c";
    ignore = formatParseType<bool, char>(cds::begin(stre), cds::end(stre));
    ASSERT_FALSE(true);
  } catch (FormatException const& fmtE) {
    ASSERT_EQ("Presentation type specifier is invalid", fmtE.message());
  }

  char const str3[] = "b";
  ASSERT_EQ(Tuple<>::of(cds::begin(str3) + 1, tFlags(FormatTypeFlagBits::Binary)),
            (formatParseType<bool, char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "B";
  ASSERT_EQ(Tuple<>::of(cds::begin(str4) + 1, tFlags(FormatTypeFlagBits::Binary, FormatTypeFlagBits::Uppercase)),
            (formatParseType<bool, char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = "d";
  ASSERT_EQ(Tuple<>::of(cds::begin(str5) + 1, tFlags(FormatTypeFlagBits::Decimal)),
            (formatParseType<bool, char>(cds::begin(str5), cds::end(str5))));

  char const str6[] = "o";
  ASSERT_EQ(Tuple<>::of(cds::begin(str6) + 1, tFlags(FormatTypeFlagBits::Octal)),
            (formatParseType<bool, char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = "x";
  ASSERT_EQ(Tuple<>::of(cds::begin(str7) + 1, tFlags(FormatTypeFlagBits::Hex)),
            (formatParseType<bool, char>(cds::begin(str7), cds::end(str7))));

  char const str8[] = "X";
  ASSERT_EQ(Tuple<>::of(cds::begin(str8) + 1, tFlags(FormatTypeFlagBits::Hex, FormatTypeFlagBits::Uppercase)),
            (formatParseType<bool, char>(cds::begin(str8), cds::end(str8))));
}

TEST(StandardFormatSpecificationTest, fmtParseFloatingType) {
  fmtParseFloatingTypeTest<float>();
  fmtParseFloatingTypeTest<double>();
}

TEST(StandardFormatSpecificationTest, fmtParsePointerType) {
  fmtParsePointerTypeTest<void*>();
  fmtParsePointerTypeTest<void const*>();
  fmtParsePointerTypeTest<int*>();
}
