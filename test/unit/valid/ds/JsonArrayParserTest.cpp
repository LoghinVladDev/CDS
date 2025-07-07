// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>

#include "UnitTest.hpp"

namespace {
using cds::StringView;

using cds::json::JsonArray;

using cds::json::impl::JsonParseError;
using cds::json::impl::JsonParseOptions;

using cds::json::impl::parseJsonArray;
} // namespace

TEST(JsonArrayParserTest, errorNoStartingBracket) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"ab"}, opt);

  ASSERT_EQ(JsonParseError::ErrorArrayWithoutStartingBracket, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
}

TEST(JsonArrayParserTest, errorNoEnding) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"[ "}, opt);

  ASSERT_EQ(JsonParseError::ErrorArrayWithoutEndingBracket, cds::get<1>(res));
  ASSERT_EQ("[ ", cds::get<0>(res));
}

TEST(JsonArrayParserTest, emptyArray) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"[  ]ab"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
  ASSERT_TRUE(arr.empty());
}

TEST(JsonArrayParserTest, errReadingFirst) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"[test"}, opt);

  ASSERT_EQ(JsonParseError::ErrorValueInvalid, cds::get<1>(res));
  ASSERT_EQ("test", cds::get<0>(res));
  ASSERT_TRUE(arr.empty());
}

TEST(JsonArrayParserTest, errNoSeparator) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"[trueab"}, opt);

  ASSERT_EQ(JsonParseError::ErrorArrayWithoutElementSeparator, cds::get<1>(res));
  ASSERT_EQ("ab", cds::get<0>(res));
}

TEST(JsonArrayParserTest, errReadingNext) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"[true,test"}, opt);

  ASSERT_EQ(JsonParseError::ErrorValueInvalid, cds::get<1>(res));
  ASSERT_EQ("test", cds::get<0>(res));
}

TEST(JsonArrayParserTest, errUnterminated0) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"[true,"}, opt);

  ASSERT_EQ(JsonParseError::ErrorArrayWithoutEndingBracket, cds::get<1>(res));
  ASSERT_EQ("", cds::get<0>(res));
}

TEST(JsonArrayParserTest, errUnterminated1) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{"[true,123"}, opt);

  ASSERT_EQ(JsonParseError::ErrorArrayWithoutEndingBracket, cds::get<1>(res));
  ASSERT_EQ("", cds::get<0>(res));
}

TEST(JsonArrayParserTest, valid) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{R"([true,123,"abc"]xyz)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xyz", cds::get<0>(res));
  ASSERT_EQ(3, arr.size());
  ASSERT_EQ(true, arr[0]);
  ASSERT_EQ(123, arr[1]);
  ASSERT_EQ("abc", arr[2]);
}

TEST(JsonArrayParserTest, validWs) {
  JsonArray arr;
  JsonParseOptions opt{};

  auto res = parseJsonArray(arr, StringView{R"([    true   ,   123 , "abc"   ]xyz)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ("xyz", cds::get<0>(res));
  ASSERT_EQ(3, arr.size());
  ASSERT_EQ(true, arr[0]);
  ASSERT_EQ(123, arr[1]);
  ASSERT_EQ("abc", arr[2]);
}
