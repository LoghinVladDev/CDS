//
// Created by loghin on 6/17/25.
//

#include <cds/json/JSON>

#include <UnitTest.hpp>

#include "../../../src/format/JsonFormatters.hpp"

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
