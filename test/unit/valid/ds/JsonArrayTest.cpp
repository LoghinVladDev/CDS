//
// Created by loghin on 6/17/25.
//

#include <cds/json/JSON>

#include <UnitTest.hpp>

#include "../../../src/format/JsonFormatters.hpp"

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
