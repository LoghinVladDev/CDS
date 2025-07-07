// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include <cds/Format>
#include <cds/meta/Platform>

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

// While some other tests are disabled for win32 due to MSVC
// not being capable to correctly parse raw strings (without experimental preprocessor)
// or some other reason, any format tests are disabled
// specifically due to the wonderfully "explained" C1054: Initializers nested too deeply.
// While the underlying format implementation is complicated due to
// c++11 compat, rewriting the whole implementation to comply with
// MSVC's "clear and obvious" limitation is pointless.
#if !CDS_ATTR(msvc)
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
#endif
