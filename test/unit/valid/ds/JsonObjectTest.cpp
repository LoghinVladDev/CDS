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

TEST(JsonObjectTest, defCtr) {
  JsonObject arr;
  ASSERT_TRUE(arr.empty());
}

TEST(JsonObjectTest, iList) {
  JsonObject obj = {
      {"abc", 1},
      {"bcd", false},
      {"cde", "abc"},
      {"def", {1, false, "cbd"}},
      {"efg", {
          {"a", "b"},
          {"b", false},
          {"c", {1, false, "cbd"}}
      }}
  };

  ASSERT_EQ(5, obj.size());
  ASSERT_EQ(1, obj["abc"]);
  ASSERT_EQ(false, obj["bcd"]);
  ASSERT_EQ("abc", obj["cde"]);
  ASSERT_EQ(JsonArray({1, false, "cbd"}), obj["def"]);
  ASSERT_EQ(JsonObject({{"a", "b"}, {"b", false}, {"c", {1, false, "cbd"}}}), obj["efg"]);
}

// While some other tests are disabled for win32 due to MSVC
// not being capable to correctly parse raw strings (without experimental preprocessor)
// or some other reason, any format tests are disabled
// specifically due to the wonderfully "explained" C1054: Initializers nested too deeply.
// While the underlying format implementation is complicated due to
// c++11 compat, rewriting the whole implementation to comply with
// MSVC's "clear and obvious" limitation is pointless.
#if !CDS_ATTR(msvc)
TEST(JsonObjectTest, format) {
  JsonObject obj = {
      {"abc", 1},
      {"bcd", false},
      {"cde", "abc"},
      {"def", {1, false, "cbd"}},
      {"efg", {
          {"a", "b"},
          {"b", false},
          {"c", {1, false, "cbd"}}
      }}
  };

  ASSERT_EQ(
      R"({)"
          R"("abc": 1, )"
          R"("bcd": false, )"
          R"("cde": "abc", )"
          R"("def": [1, false, "cbd"], )"
          R"("efg": {)"
              R"("a": "b", )"
              R"("b": false, )"
              R"("c": [1, false, "cbd"])"
          R"(})"
      R"(})",
      cds::format("{}", obj));
}

TEST(JsonObjectTest, assignSub) {
  JsonObject obj = {
      {"a", 0},
      {"b", false},
      {"c", "abc"}
  };

  obj["d"] = {
      {"a", 1},
      {"b", true},
      {"c", {"a", "b", 2}}
  };

  obj["b"] = {
      {"a", 2},
      {"b", 4}
  };

  ASSERT_EQ(0, obj["a"]);
  ASSERT_EQ(2, obj["b"].getObject()["a"]);
  ASSERT_EQ(4, obj["b"].getObject()["b"]);
  ASSERT_EQ("abc", obj["c"]);
  ASSERT_EQ(1, obj["d"].getObject()["a"]);
  ASSERT_EQ(true, obj["d"].getObject()["b"]);
  ASSERT_TRUE(obj["d"].getObject()["c"].isArray());
  ASSERT_EQ("a", obj["d"].getObject()["c"].getArray()[0]);
  ASSERT_EQ("b", obj["d"].getObject()["c"].getArray()[1]);
  ASSERT_EQ(2, obj["d"].getObject()["c"].getArray()[2]);
}

TEST(JsonObjectTest, ctrFromStr1) {
  JsonObject obj = cds::String{R"({"a": false, "b": 123, "c": "abc"})"};
  ASSERT_EQ(R"({"a": false, "b": 123, "c": "abc"})", cds::format("{}", obj));
}

TEST(JsonObjectTest, ctrFromStr2) {
  JsonObject obj = cds::StringView{R"({"a": false, "b": 123, "c": "abc"})"};
  ASSERT_EQ(R"({"a": false, "b": 123, "c": "abc"})", cds::format("{}", obj));
}

TEST(JsonObjectTest, ctrFromStr3) {
  JsonObject obj = R"({"a": false, "b": 123, "c": "abc"})";
  ASSERT_EQ(R"({"a": false, "b": 123, "c": "abc"})", cds::format("{}", obj));
}

TEST(JsonObjectTest, ctrFromStrExcept) {
  try {
    JsonObject obj = R"({"a": false, b: 123, "c": "abc"})";
  } catch (cds::json::JsonParseException const& except) {
    ASSERT_EQ("Expected '\"', received 'b: 123, \"c\": \"ab...'", except.message());
  }
}

TEST(JsonObjectTest, fromLiteral) {
  using namespace cds::json;
  ASSERT_EQ(R"({"a": false, "b": 123, "c": "abc"})", cds::format("{}", R"({"a": false, "b": 123, "c": "abc"})"_json));
}

#ifdef DCR_SINCECPP20
constexpr void cpp20ConstexprTest() {
  static_assert(R"({"a": false, "b": 123, "c": "abc"})" == cds::format("{}", R"({"a": false, "b": 123, "c": "abc"})"_json));
}
#endif
#endif
