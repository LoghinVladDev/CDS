// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>

#include "UnitTest.hpp"

namespace {
using cds::String;
using cds::StringView;

using cds::json::JsonNode;

using cds::json::impl::CodePointParser;
using cds::json::impl::JsonParseError;
using cds::json::impl::JsonParseOptions;
using cds::json::impl::JsonString;

using cds::json::impl::parseErrorAsString;
using cds::json::impl::parseJsonNumber;
using cds::json::impl::parseJsonString;
using cds::json::impl::throwIfErroneous;
} // namespace

#if !CDS_ATTR(msvc)
TEST(JsonCommonParsersTest, codePointParser) {
  String str;
  CodePointParser<char> parser;

  parser(str, 0x0061u);
  parser(str, 0x0170u);
  parser(str, 0x3fac);

  ASSERT_EQ("\u0061\u0170\u3fac", str);
}
#endif

TEST(JsonCommonParsersTest, parseJsonNumberErrorFractionBeforeIntegral) {
  JsonNode n;
  JsonParseOptions opt{};

  opt.readFloatingStartingWithFraction = false;
  auto res = parseJsonNumber(n, StringView{".5"}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberNoIntegralBeforeFraction, cds::get<1>(res));
  ASSERT_EQ(".5", cds::get<0>(res));
}

TEST(JsonCommonParsersTest, parseJsonNumberErrorChars) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"x"}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberInvalid, cds::get<1>(res));
  ASSERT_EQ("x", cds::get<0>(res));
}

TEST(JsonCommonParsersTest, parseJsonNumberErrorNoChars) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{""}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberInvalid, cds::get<1>(res));
  ASSERT_EQ("", cds::get<0>(res));
}

TEST(JsonCommonParsersTest, parseJsonNumberErrorNoNumbersInFraction) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"1.x"}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberNoDigitsAfterFraction, cds::get<1>(res));
  ASSERT_EQ("1.x", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralZero) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"0ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralNegZero) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"-0ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegral) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"123ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(123, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberNegIntegral) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"-123ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(-123, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberNegSpaceIntegral) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"-   123ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(-123, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralHexNoOpt) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"0x1fabg"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("x1fabg", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralHexOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"0x1fabg"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0x1fab, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralHexNegOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"-0x1fabg"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(-0x1fab, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralHexOptUpper) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"0X1FABg"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0x1fab, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralOctNoOpt) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"067g"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(67, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralOctOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"067g"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(067, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralNeghOctOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"-067g"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(-067, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralBinNoOpt) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"0b0111g"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("b0111g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralBinOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"0b011101g"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0b011101, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralNegBinOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"-0b011101g"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(-0b011101, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberIntegralBinOptUpper) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readNonBase10Integrals = true;

  auto res = parseJsonNumber(n, StringView{"0B011101g"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("g", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(0b011101, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonNumberFloatingNeg) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"-1.5x"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("x", cds::get<0>(res));
  ASSERT_TRUE(n.isFloating());
  ASSERT_LT(n.getDouble(), -1.4);
  ASSERT_GT(n.getDouble(), -1.6);
}

TEST(JsonCommonParserTest, parseJsonNumberFloating) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"1.5x"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("x", cds::get<0>(res));
  ASSERT_TRUE(n.isFloating());
  ASSERT_GT(n.getDouble(), 1.4);
  ASSERT_LT(n.getDouble(), 1.6);
}

TEST(JsonCommonParserTest, parseJsonNumberFloatingWithoutIntegralOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readFloatingStartingWithFraction = true;

  auto res = parseJsonNumber(n, StringView{".5x"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("x", cds::get<0>(res));
  ASSERT_TRUE(n.isFloating());
  ASSERT_GT(n.getDouble(), .4);
  ASSERT_LT(n.getDouble(), .6);
}

TEST(JsonCommonParserTest, parseJsonNumberFloatingWithoutIntegralOptNeg) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readFloatingStartingWithFraction = true;

  auto res = parseJsonNumber(n, StringView{"-.5x"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("x", cds::get<0>(res));
  ASSERT_TRUE(n.isFloating());
  ASSERT_LT(n.getDouble(), -.4);
  ASSERT_GT(n.getDouble(), -.6);
}

TEST(JsonCommonParserTest, parseJsonNumberErrorNoCharAfterSign1) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"-x"}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberInvalid, cds::get<1>(res));
  ASSERT_EQ("-x", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonNumberErrorNoCharAfterSign2) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"-"}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberInvalid, cds::get<1>(res));
  ASSERT_EQ("-", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonNumberErrorNoCharAfterSignOptPlus) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readPlusSign = true;

  auto res = parseJsonNumber(n, StringView{"+x"}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberInvalid, cds::get<1>(res));
  ASSERT_EQ("+x", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonNumberPlusNoOpt) {
  JsonNode n;
  JsonParseOptions opt{};

  auto res = parseJsonNumber(n, StringView{"+12x"}, opt);

  ASSERT_EQ(JsonParseError::ErrorNumberInvalid, cds::get<1>(res));
  ASSERT_EQ("+12x", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonNumberPlusOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readPlusSign = true;

  auto res = parseJsonNumber(n, StringView{"+12x"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("x", cds::get<0>(res));
  ASSERT_TRUE(n.isIntegral());
  ASSERT_EQ(12, n.getInt());
}

TEST(JsonCommonParserTest, parseJsonStringErrorNoQuoteEmpty) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{""}, opt);

  ASSERT_EQ(JsonParseError::ErrorStringWithoutStartingQuote, cds::get<1>(res));
  ASSERT_EQ("", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonStringErrorNoQuote) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{"xyz"}, opt);

  ASSERT_EQ(JsonParseError::ErrorStringWithoutStartingQuote, cds::get<1>(res));
  ASSERT_EQ("xyz", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonStringErrorQuoteUnterminated) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{"\"xyz"}, opt);

  ASSERT_EQ(JsonParseError::ErrorStringWithoutEndingQuote, cds::get<1>(res));
  ASSERT_EQ("\"xyz", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonStringErrorUTF8CodePointTooShort) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{R"("ab\u12")"}, opt);

  ASSERT_EQ(JsonParseError::ErrorUTFCodePointTooShort, cds::get<1>(res));
  ASSERT_EQ(R"("ab\u12")", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonStringErrorUTF8CodePointInvalid) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{R"("ab\u12xyzt")"}, opt);

  ASSERT_EQ(JsonParseError::ErrorUTFCodePointInvalid, cds::get<1>(res));
  ASSERT_EQ(R"("ab\u12xyzt")", cds::get<0>(res));
}

#if !CDS_ATTR(msvc)
TEST(JsonCommonParserTest, parseJsonStringErrorEscapeUnterminated0) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{R"("\)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorStringWithoutEndingQuote, cds::get<1>(res));
  ASSERT_EQ(R"("\)", cds::get<0>(res));
}

TEST(JsonCommonParserTest, parseJsonStringErrorEscapeUnterminated1) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{R"("\")"}, opt);

  ASSERT_EQ(JsonParseError::ErrorStringWithoutEndingQuote, cds::get<1>(res));
  ASSERT_EQ(R"("\")", cds::get<0>(res));
}
#endif

TEST(JsonCommonParserTest, parseJsonStringEscaping) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{R"(" \" \\ \/ / \b b \t t \f f \r r \n n ")"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("", cds::get<0>(res));
  ASSERT_EQ(" \" \\ / / \b b \t t \f f \r r \n n ", str);
}

#if !CDS_ATTR(msvc)
TEST(JsonCommonParserTest, parseJsonStringEscapingUtf) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{R"("\u0067\u01ff\u07ff\ubbff")"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("", cds::get<0>(res));
  ASSERT_EQ("\u0067\u01ff\u07ff\ubbff", str);
}
#endif

TEST(JsonCommonParserTest, parseJsonStringAfterQuotePreserve) {
  JsonString str;
  JsonParseOptions opt{};

  auto res = parseJsonString(str, StringView{R"("abc"def)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("def", cds::get<0>(res));
  ASSERT_EQ("abc", str);
}

TEST(JsonCommonParserTest, parseErrorAsString) {
  auto const loc = StringView{"<loc>"};

  ASSERT_EQ("", parseErrorAsString(JsonParseError::None, loc));
  ASSERT_EQ(
      "Expected integral before '.', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorNumberNoIntegralBeforeFraction, loc)
  );
  ASSERT_EQ(
      "Expected number, received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorNumberInvalid, loc)
  );
  ASSERT_EQ(
      "Expected fraction digits after '.', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorNumberNoDigitsAfterFraction, loc)
  );
  ASSERT_EQ(
      "Expected '\"', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorStringWithoutStartingQuote, loc)
  );
  ASSERT_EQ(
      "Unterminated string, expected '\"', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorStringWithoutEndingQuote, loc)
  );
  ASSERT_EQ(
      "Expected '\\u<digit><digit><digit><digit>', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorUTFCodePointTooShort, loc)
  );
  ASSERT_EQ(
      "Expected '\\u<digit><digit><digit><digit>', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorUTFCodePointInvalid, loc)
  );
  ASSERT_EQ(
      "Expected '<value>', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorValueInvalid, loc)
  );
  ASSERT_EQ(
      "Expected array starting bracket '[', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorArrayWithoutStartingBracket, loc)
  );
  ASSERT_EQ(
      "Unterminated array, expected ']', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorArrayWithoutEndingBracket, loc)
  );
  ASSERT_EQ(
      "Expected array element separator ',', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorArrayWithoutElementSeparator, loc)
  );
  ASSERT_EQ(
      "Expected object starting brace '{', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorObjectWithoutStartingBrace, loc)
  );
  ASSERT_EQ(
      "Unterminated object, expected '}', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorObjectWithoutEndingBrace, loc)
  );
  ASSERT_EQ(
      "Expected object member separator ',', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorObjectWithoutMemberSeparator, loc)
  );
  ASSERT_EQ(
      "Expected object member key-value separator ':', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorObjectMemberWithoutKeyValueSeparator, loc)
  );
  ASSERT_EQ(
      "Invalid escape sequence after '\\', received '<loc>'",
      parseErrorAsString(JsonParseError::ErrorStringInvalidEscapeSequence, loc)
  );
}

TEST(JsonCommonParserTest, parseErrorTruncateLoc) {
  auto const loc = StringView{"<long-location-that-will-be-truncated>"};

  try {
    throwIfErroneous(cds::tupleOf(loc, JsonParseError::ErrorNumberInvalid));
  } catch (cds::json::JsonParseException const& except) {
    ASSERT_EQ("Expected number, received '<long-location-t...'", except.message());
  }
}
