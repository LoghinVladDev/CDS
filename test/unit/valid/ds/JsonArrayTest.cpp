// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include <cds/Format>

#include <UnitTest.hpp>

namespace {
using namespace cds::json;
} // namespace

TEST(JsonArrayTest, defCtr) {
  JsonArray arr;
  ASSERT_TRUE(arr.empty());
}

TEST(JsonArrayTest, iList) {
  JsonArray arr{1, false, "abc"};
  ASSERT_EQ(1, arr[0]);
  ASSERT_EQ(false, arr[1]);
  ASSERT_EQ("abc", arr[2]);
  ASSERT_EQ(3, arr.size());
}

TEST(JsonArrayTest, format) {
  JsonArray arr{1, false, "abc"};

  ASSERT_EQ(R"([1, false, "abc"])", cds::format("{}", arr));
}

TEST(JsonArrayTest, ctrFromString) {
  JsonArray arr = cds::String{R"([1, false, "abc"])"};
  ASSERT_EQ(R"([1, false, "abc"])", cds::format("{}", arr));
}

TEST(JsonArrayTest, ctrFromStringThrowing) {
  try {
    JsonArray arr = R"([1, fals, "abc"])";
    cds::ignore = arr;
    ASSERT_FALSE(true);
  } catch (cds::json::JsonParseException const& except) {
    ASSERT_EQ("Expected '<value>', received 'fals, \"abc\"]'", except.message());
  }
}

TEST(JsonArrayTest, fromLiteral) {
  using namespace cds::json;
  ASSERT_EQ(R"([12, false, "abc"])", cds::format("{}", R"([12, false, "abc"])"_json_array));
}
