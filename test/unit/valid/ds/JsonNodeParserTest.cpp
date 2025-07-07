// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>

#include "UnitTest.hpp"

namespace {
using cds::StringView;

using cds::json::JsonNode;

using cds::json::impl::JsonParseError;
using cds::json::impl::JsonParseOptions;

using cds::json::impl::parseJsonNode;
} // namespace

TEST(JsonNodeParserTest, parseJsonNodeErrorEmpty) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{""}, opt);

  ASSERT_EQ(JsonParseError::ErrorValueInvalid, cds::get<1>(res));
  ASSERT_EQ("", cds::get<0>(res));
}

TEST(JsonNodeParserTest, parseJsonNodeParseArray) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{"[]ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(n.isArray());
  ASSERT_TRUE(n.getArray().empty());
}

TEST(JsonNodeParserTest, parseJsonNodeParseObject) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{"{}ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(n.isObject());
  ASSERT_TRUE(n.getObject().empty());
}

TEST(JsonNodeParserTest, parseJsonNodeParseString) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"("ab"xy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_EQ("ab", n);
}

TEST(JsonNodeParserTest, parseJsonNodeParseNumber0) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(12xy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_EQ(12, n);
}

TEST(JsonNodeParserTest, parseJsonNodeParseNumber1) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(-12xy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_EQ(-12, n);
}

TEST(JsonNodeParserTest, parseJsonNodeParseNumberErrPlusSignNoOpt) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(+12xy)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorValueInvalid, cds::get<1>(res));
  ASSERT_EQ("+12xy", cds::get<0>(res));
}

TEST(JsonNodeParserTest, parseJsonNodeParseNumberPlusSignOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readPlusSign = true;

  auto const res = parseJsonNode(n, StringView{R"(+12xy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_EQ(12, n);
}

TEST(JsonNodeParserTest, parseJsonNodeParseNumberErrFractionNoOpt) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(.5xy)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorValueInvalid, cds::get<1>(res));
  ASSERT_EQ(".5xy", cds::get<0>(res));
}

TEST(JsonNodeParserTest, parseJsonNodeParseNumberFractionOpt) {
  JsonNode n;
  JsonParseOptions opt{};
  opt.readFloatingStartingWithFraction = true;

  auto const res = parseJsonNode(n, StringView{R"(.5xy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_TRUE(n.isFloating());
  ASSERT_LT(.4, n.getDouble());
  ASSERT_GT(.6, n.getDouble());
}

TEST(JsonNodeParserTest, parseJsonNodeParseFalse) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(falsexy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_TRUE(n.isBool());
  ASSERT_FALSE(n.getBool());
}

TEST(JsonNodeParserTest, parseJsonNodeParseTrue) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(truexy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_TRUE(n.isBool());
  ASSERT_TRUE(n.getBool());
}

TEST(JsonNodeParserTest, parseJsonNodeParseNull) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(nullxy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xy", cds::get<0>(res));
  ASSERT_TRUE(n.isNull());
}

TEST(JsonNodeParserTest, parseJsonNodeErrorInvalid) {
  JsonNode n;
  JsonParseOptions opt{};

  auto const res = parseJsonNode(n, StringView{R"(this-is-not-a-keyword)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorValueInvalid, cds::get<1>(res));
  ASSERT_EQ("this-is-not-a-keyword", cds::get<0>(res));
}
