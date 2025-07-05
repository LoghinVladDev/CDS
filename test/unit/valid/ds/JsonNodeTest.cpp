//
// Created by loghin on 6/17/25.
//

#include <cds/json/JSON>

#include <UnitTest.hpp>

#include "../../../src/format/JsonFormatters.hpp"

namespace {
using namespace cds::json;

void copyOverTest(JsonNode& dst) {
  JsonNode asBool;
  asBool = true;
  dst = asBool;
  ASSERT_TRUE(dst.isBool());
  ASSERT_TRUE(dst.getBool());

  JsonNode asInt;
  asInt = 4;
  dst = asInt;
  ASSERT_TRUE(dst.isIntegral());
  ASSERT_EQ(4, dst.getInt());

  JsonNode asFloating;
  asFloating = 4.5;
  dst = asFloating;
  ASSERT_TRUE(dst.isFloating());
  ASSERT_LT(4.0, dst.getDouble());
  ASSERT_GT(5.0, dst.getDouble());

  JsonNode asString;
  asString = "abc";
  dst = asString;
  ASSERT_TRUE(dst.isString());
  ASSERT_EQ("abc", dst.getString());

  JsonNode asNull;
  asNull = nullptr;
  dst = asNull;
  ASSERT_TRUE(dst.isNull());
}
} // namespace

TEST(JsonNodeTest, ctrFromNull) {
  JsonNode node = nullptr;
  ASSERT_TRUE(node.isNull());
}

TEST(JsonNodeTest, ctrFromBool) {
  JsonNode node = true;
  ASSERT_TRUE(node.isBool());
  ASSERT_TRUE(node.getBool());
}

TEST(JsonNodeTest, ctrFromInt) {
  JsonNode node = 4;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(4, node.getInt());
}

TEST(JsonNodeTest, ctrFromFloating) {
  JsonNode node = 4.5;
  ASSERT_TRUE(node.isFloating());
  ASSERT_LT(4.0, node.getDouble());
  ASSERT_GT(5.0, node.getDouble());
}

TEST(JsonNodeTest, ctrFromString) {
  JsonNode node = "abcd";
  ASSERT_TRUE(node.isString());
  ASSERT_EQ("abcd", node.getString());
}

TEST(JsonNodeTest, ctrFromArray) {
  JsonNode node = JsonArray{1, false, "abc"};
  ASSERT_TRUE(node.isArray());
  ASSERT_EQ(node.getArray()[0], 1);
  ASSERT_EQ(node.getArray()[1], false);
  ASSERT_EQ(node.getArray()[2], "abc");
}

TEST(JsonNodeTest, copyCtr) {
  JsonNode nullNode = nullptr;
  JsonNode const nullCopy = nullNode;
  ASSERT_TRUE(nullCopy.isNull());

  JsonNode boolNode = true;
  JsonNode const boolCopy = boolNode;
  ASSERT_TRUE(boolCopy.isBool());
  ASSERT_TRUE(boolCopy.getBool());

  JsonNode intNode = 4;
  JsonNode const intCopy = intNode;
  ASSERT_TRUE(intCopy.isIntegral());
  ASSERT_EQ(4, intCopy.getInt());

  JsonNode floatNode = 4.5;
  JsonNode const floatCopy = floatNode;
  ASSERT_TRUE(floatCopy.isFloating());
  ASSERT_LT(4.0, floatCopy.getDouble());
  ASSERT_GT(5.0, floatCopy.getDouble());

  JsonNode stringNode = "abcd";
  JsonNode const stringCopy = stringNode;
  ASSERT_TRUE(stringCopy.isString());
  ASSERT_EQ("abcd", stringCopy.getString());
}

TEST(JsonNodeTest, moveCtr) {
  JsonNode nullNode = nullptr;
  JsonNode nullCopy = mv(nullNode);
  ASSERT_TRUE(nullCopy.isNull());

  JsonNode boolNode = true;
  JsonNode boolCopy = mv(boolNode);
  ASSERT_TRUE(boolCopy.isBool());
  ASSERT_TRUE(boolCopy.getBool());

  JsonNode intNode = 4;
  JsonNode intCopy = mv(intNode);
  ASSERT_TRUE(intCopy.isIntegral());
  ASSERT_EQ(4, intCopy.getInt());

  JsonNode floatNode = 4.5;
  JsonNode floatCopy = mv(floatNode);
  ASSERT_TRUE(floatCopy.isFloating());
  ASSERT_LT(4.0, floatCopy.getDouble());
  ASSERT_GT(5.0, floatCopy.getDouble());

  JsonNode stringNode = "abcd";
  JsonNode stringCopy = mv(stringNode);
  ASSERT_TRUE(stringCopy.isString());
  ASSERT_EQ("abcd", stringCopy.getString());
}

TEST(JsonNodeTest, nodeFromNull) {
  JsonNode node;

  node = nullptr;
  ASSERT_TRUE(node.isNull());
}

TEST(JsonNodeTest, nodeFromBool) {
  JsonNode node;

  node = true;
  ASSERT_TRUE(node.isBool());
  ASSERT_TRUE(node.getBool());
  node = false;
  ASSERT_TRUE(node.isBool());
  ASSERT_FALSE(node.getBool());
}

TEST(JsonNodeTest, nodeFromIntegral) {
  JsonNode node;

  node = 4;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(4, node.getInt());

  node = 10u;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(10, node.getLong());

  node = -5;
  ASSERT_TRUE(node.isIntegral());
  ASSERT_EQ(-5, node.getInt());
}

TEST(JsonNodeTest, nodeFromFloating) {
  JsonNode node;

  node = 3.4;
  ASSERT_TRUE(node.isFloating());
  ASSERT_GT(node.getDouble(), 3.0);
  ASSERT_LT(node.getDouble(), 4.0);
}

TEST(JsonNodeTest, nodeFromString) {
  JsonNode node;

  node = "abc";
  ASSERT_TRUE(node.isString());
  ASSERT_EQ("abc", node.getString());

  node.getString() = "ab";
  ASSERT_EQ("ab", node.getString());
}

TEST(JsonNodeTest, copyOverNull) {
  JsonNode dst;
  dst = nullptr;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverBool) {
  JsonNode dst;
  dst = false;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverInt) {
  JsonNode dst;
  dst = 34;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverFloating) {
  JsonNode dst;
  dst = 3.4;
  copyOverTest(dst);
}

TEST(JsonNodeTest, copyOverString) {
  JsonNode dst;
  dst = 3.4;
  copyOverTest(dst);

  dst = "abc";
  JsonNode directStr;
  directStr = "bcd";
  dst = directStr;
  ASSERT_TRUE(dst.isString());
  ASSERT_EQ("bcd", dst.getString());
}

TEST(JsonNodeTest, isNumber) {
  JsonNode node;
  ASSERT_FALSE(node.isNumber());
  node = 3;
  ASSERT_TRUE(node.isNumber());
  node = 3.4;
  ASSERT_TRUE(node.isNumber());
  node = false;
  ASSERT_FALSE(node.isNumber());
}

TEST(JsonNodeTest, eqNullNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_TRUE(nullNode == nullNode);
  ASSERT_FALSE(nullNode == boolNode0);
  ASSERT_FALSE(nullNode == boolNode1);
  ASSERT_FALSE(nullNode == intNode0);
  ASSERT_FALSE(nullNode == intNode1);
  ASSERT_FALSE(nullNode == floatNode0);
  ASSERT_FALSE(nullNode == floatNode1);
  ASSERT_FALSE(nullNode == stringNode0);
  ASSERT_FALSE(nullNode == stringNode1);

  ASSERT_FALSE(nullNode != nullNode);
  ASSERT_TRUE(nullNode != boolNode0);
  ASSERT_TRUE(nullNode != boolNode1);
  ASSERT_TRUE(nullNode != intNode0);
  ASSERT_TRUE(nullNode != intNode1);
  ASSERT_TRUE(nullNode != floatNode0);
  ASSERT_TRUE(nullNode != floatNode1);
  ASSERT_TRUE(nullNode != stringNode0);
  ASSERT_TRUE(nullNode != stringNode1);
}

TEST(JsonNodeTest, eqBoolNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_FALSE(boolNode0 == nullNode);
  ASSERT_TRUE(boolNode0 == boolNode0);
  ASSERT_FALSE(boolNode0 == boolNode1);
  ASSERT_FALSE(boolNode0 == intNode0);
  ASSERT_FALSE(boolNode0 == intNode1);
  ASSERT_FALSE(boolNode0 == floatNode0);
  ASSERT_FALSE(boolNode0 == floatNode1);
  ASSERT_FALSE(boolNode0 == stringNode0);
  ASSERT_FALSE(boolNode0 == stringNode1);

  ASSERT_TRUE(boolNode0 != nullNode);
  ASSERT_FALSE(boolNode0 != boolNode0);
  ASSERT_TRUE(boolNode0 != boolNode1);
  ASSERT_TRUE(boolNode0 != intNode0);
  ASSERT_TRUE(boolNode0 != intNode1);
  ASSERT_TRUE(boolNode0 != floatNode0);
  ASSERT_TRUE(boolNode0 != floatNode1);
  ASSERT_TRUE(boolNode0 != stringNode0);
  ASSERT_TRUE(boolNode0 != stringNode1);

  ASSERT_FALSE(boolNode1 == nullNode);
  ASSERT_FALSE(boolNode1 == boolNode0);
  ASSERT_TRUE(boolNode1 == boolNode1);
  ASSERT_FALSE(boolNode1 == intNode0);
  ASSERT_FALSE(boolNode1 == intNode1);
  ASSERT_FALSE(boolNode1 == floatNode0);
  ASSERT_FALSE(boolNode1 == floatNode1);
  ASSERT_FALSE(boolNode1 == stringNode0);
  ASSERT_FALSE(boolNode1 == stringNode1);

  ASSERT_TRUE(boolNode1 != nullNode);
  ASSERT_TRUE(boolNode1 != boolNode0);
  ASSERT_FALSE(boolNode1 != boolNode1);
  ASSERT_TRUE(boolNode1 != intNode0);
  ASSERT_TRUE(boolNode1 != intNode1);
  ASSERT_TRUE(boolNode1 != floatNode0);
  ASSERT_TRUE(boolNode1 != floatNode1);
  ASSERT_TRUE(boolNode1 != stringNode0);
  ASSERT_TRUE(boolNode1 != stringNode1);
}

TEST(JsonNodeTest, eqIntNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_FALSE(intNode0 == nullNode);
  ASSERT_FALSE(intNode0 == boolNode0);
  ASSERT_FALSE(intNode0 == boolNode1);
  ASSERT_TRUE(intNode0 == intNode0);
  ASSERT_FALSE(intNode0 == intNode1);
  ASSERT_FALSE(intNode0 == floatNode0);
  ASSERT_FALSE(intNode0 == floatNode1);
  ASSERT_FALSE(intNode0 == stringNode0);
  ASSERT_FALSE(intNode0 == stringNode1);

  ASSERT_TRUE(intNode0 != nullNode);
  ASSERT_TRUE(intNode0 != boolNode0);
  ASSERT_TRUE(intNode0 != boolNode1);
  ASSERT_FALSE(intNode0 != intNode0);
  ASSERT_TRUE(intNode0 != intNode1);
  ASSERT_TRUE(intNode0 != floatNode0);
  ASSERT_TRUE(intNode0 != floatNode1);
  ASSERT_TRUE(intNode0 != stringNode0);
  ASSERT_TRUE(intNode0 != stringNode1);

  ASSERT_FALSE(intNode1 == nullNode);
  ASSERT_FALSE(intNode1 == boolNode0);
  ASSERT_FALSE(intNode1 == boolNode1);
  ASSERT_FALSE(intNode1 == intNode0);
  ASSERT_TRUE(intNode1 == intNode1);
  ASSERT_FALSE(intNode1 == floatNode0);
  ASSERT_FALSE(intNode1 == floatNode1);
  ASSERT_FALSE(intNode1 == stringNode0);
  ASSERT_FALSE(intNode1 == stringNode1);

  ASSERT_TRUE(intNode1 != nullNode);
  ASSERT_TRUE(intNode1 != boolNode0);
  ASSERT_TRUE(intNode1 != boolNode1);
  ASSERT_TRUE(intNode1 != intNode0);
  ASSERT_FALSE(intNode1 != intNode1);
  ASSERT_TRUE(intNode1 != floatNode0);
  ASSERT_TRUE(intNode1 != floatNode1);
  ASSERT_TRUE(intNode1 != stringNode0);
  ASSERT_TRUE(intNode1 != stringNode1);
}

TEST(JsonNodeTest, eqStrNode) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode0 = 4;
  JsonNode intNode1 = 5;
  JsonNode floatNode0 = 3.4;
  JsonNode floatNode1 = 5.4;
  JsonNode stringNode0 = "abc";
  JsonNode stringNode1 = "bcd";

  ASSERT_FALSE(stringNode0 == nullNode);
  ASSERT_FALSE(stringNode0 == boolNode0);
  ASSERT_FALSE(stringNode0 == boolNode1);
  ASSERT_FALSE(stringNode0 == intNode0);
  ASSERT_FALSE(stringNode0 == intNode1);
  ASSERT_FALSE(stringNode0 == floatNode0);
  ASSERT_FALSE(stringNode0 == floatNode1);
  ASSERT_TRUE(stringNode0 == stringNode0);
  ASSERT_FALSE(stringNode0 == stringNode1);

  ASSERT_TRUE(stringNode0 != nullNode);
  ASSERT_TRUE(stringNode0 != boolNode0);
  ASSERT_TRUE(stringNode0 != boolNode1);
  ASSERT_TRUE(stringNode0 != intNode0);
  ASSERT_TRUE(stringNode0 != intNode1);
  ASSERT_TRUE(stringNode0 != floatNode0);
  ASSERT_TRUE(stringNode0 != floatNode1);
  ASSERT_FALSE(stringNode0 != stringNode0);
  ASSERT_TRUE(stringNode0 != stringNode1);

  ASSERT_FALSE(stringNode1 == nullNode);
  ASSERT_FALSE(stringNode1 == boolNode0);
  ASSERT_FALSE(stringNode1 == boolNode1);
  ASSERT_FALSE(stringNode1 == intNode0);
  ASSERT_FALSE(stringNode1 == intNode1);
  ASSERT_FALSE(stringNode1 == floatNode0);
  ASSERT_FALSE(stringNode1 == floatNode1);
  ASSERT_FALSE(stringNode1 == stringNode0);
  ASSERT_TRUE(stringNode1 == stringNode1);

  ASSERT_TRUE(stringNode1 != nullNode);
  ASSERT_TRUE(stringNode1 != boolNode0);
  ASSERT_TRUE(stringNode1 != boolNode1);
  ASSERT_TRUE(stringNode1 != intNode0);
  ASSERT_TRUE(stringNode1 != intNode1);
  ASSERT_TRUE(stringNode1 != floatNode0);
  ASSERT_TRUE(stringNode1 != floatNode1);
  ASSERT_TRUE(stringNode1 != stringNode0);
  ASSERT_FALSE(stringNode1 != stringNode1);
}

TEST(JsonNodeTest, directNullComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_TRUE(nullNode == nullptr);
  ASSERT_FALSE(boolNode == nullptr);
  ASSERT_FALSE(intNode == nullptr);
  ASSERT_FALSE(floatNode == nullptr);
  ASSERT_FALSE(strNode == nullptr);

  ASSERT_TRUE(nullptr == nullNode);
  ASSERT_FALSE(nullptr == boolNode);
  ASSERT_FALSE(nullptr == intNode);
  ASSERT_FALSE(nullptr == floatNode);
  ASSERT_FALSE(nullptr == strNode);

  ASSERT_FALSE(nullNode != nullptr);
  ASSERT_TRUE(boolNode != nullptr);
  ASSERT_TRUE(intNode != nullptr);
  ASSERT_TRUE(floatNode != nullptr);
  ASSERT_TRUE(strNode != nullptr);

  ASSERT_FALSE(nullptr != nullNode);
  ASSERT_TRUE(nullptr != boolNode);
  ASSERT_TRUE(nullptr != intNode);
  ASSERT_TRUE(nullptr != floatNode);
  ASSERT_TRUE(nullptr != strNode);
}

TEST(JsonNodeTest, directBoolComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode0 = false;
  JsonNode boolNode1 = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == false);
  ASSERT_FALSE(nullNode == true);
  ASSERT_FALSE(boolNode0 == true);
  ASSERT_TRUE(boolNode0 == false);
  ASSERT_FALSE(boolNode1 == false);
  ASSERT_TRUE(boolNode1 == true);
  ASSERT_FALSE(intNode == false);
  ASSERT_FALSE(intNode == true);
  ASSERT_FALSE(floatNode == false);
  ASSERT_FALSE(floatNode == true);
  ASSERT_FALSE(strNode == false);
  ASSERT_FALSE(strNode == true);

  ASSERT_FALSE(false == nullNode);
  ASSERT_FALSE(true == nullNode);
  ASSERT_FALSE(true == boolNode0);
  ASSERT_TRUE(false == boolNode0);
  ASSERT_FALSE(false == boolNode1);
  ASSERT_TRUE(true == boolNode1);
  ASSERT_FALSE(false == intNode);
  ASSERT_FALSE(true == intNode);
  ASSERT_FALSE(false == floatNode);
  ASSERT_FALSE(true == floatNode);
  ASSERT_FALSE(false == strNode);
  ASSERT_FALSE(true == strNode);

  ASSERT_TRUE(nullNode != false);
  ASSERT_TRUE(nullNode != true);
  ASSERT_TRUE(boolNode0 != true);
  ASSERT_FALSE(boolNode0 != false);
  ASSERT_TRUE(boolNode1 != false);
  ASSERT_FALSE(boolNode1 != true);
  ASSERT_TRUE(intNode != false);
  ASSERT_TRUE(intNode != true);
  ASSERT_TRUE(floatNode != false);
  ASSERT_TRUE(floatNode != true);
  ASSERT_TRUE(strNode != false);
  ASSERT_TRUE(strNode != true);

  ASSERT_TRUE(false != nullNode);
  ASSERT_TRUE(true != nullNode);
  ASSERT_TRUE(true != boolNode0);
  ASSERT_FALSE(false != boolNode0);
  ASSERT_TRUE(false != boolNode1);
  ASSERT_FALSE(true != boolNode1);
  ASSERT_TRUE(false != intNode);
  ASSERT_TRUE(true != intNode);
  ASSERT_TRUE(false != floatNode);
  ASSERT_TRUE(true != floatNode);
  ASSERT_TRUE(false != strNode);
  ASSERT_TRUE(true != strNode);
}

TEST(JsonNodeTest, directIntComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == 4);
  ASSERT_FALSE(boolNode == 4);
  ASSERT_FALSE(intNode == 5);
  ASSERT_TRUE(intNode == 4);
  ASSERT_FALSE(floatNode == 4);
  ASSERT_FALSE(strNode == 4);

  ASSERT_FALSE(4 == nullNode);
  ASSERT_FALSE(4 == boolNode);
  ASSERT_FALSE(5 == intNode);
  ASSERT_TRUE(4 == intNode);
  ASSERT_FALSE(4 == floatNode);
  ASSERT_FALSE(4 == strNode);

  ASSERT_TRUE(nullNode != 4);
  ASSERT_TRUE(boolNode != 4);
  ASSERT_TRUE(intNode != 5);
  ASSERT_FALSE(intNode != 4);
  ASSERT_TRUE(floatNode != 4);
  ASSERT_TRUE(strNode != 4);

  ASSERT_TRUE(4 != nullNode);
  ASSERT_TRUE(4 != boolNode);
  ASSERT_TRUE(5 != intNode);
  ASSERT_FALSE(4 != intNode);
  ASSERT_TRUE(4 != floatNode);
  ASSERT_TRUE(4 != strNode);
}

TEST(JsonNodeTest, directFloatComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == 3.4);
  ASSERT_FALSE(boolNode == 3.4);
  ASSERT_FALSE(intNode == 3.4);
  ASSERT_FALSE(floatNode == 4.5);
  ASSERT_TRUE(floatNode == 3.4);
  ASSERT_FALSE(strNode == 3.4);

  ASSERT_FALSE(3.4 == nullNode);
  ASSERT_FALSE(3.4 == boolNode);
  ASSERT_FALSE(3.4 == intNode);
  ASSERT_FALSE(4.5 == floatNode);
  ASSERT_TRUE(3.4 == floatNode);
  ASSERT_FALSE(3.4 == strNode);

  ASSERT_TRUE(nullNode != 3.4);
  ASSERT_TRUE(boolNode != 3.4);
  ASSERT_TRUE(intNode != 3.4);
  ASSERT_TRUE(floatNode != 4.5);
  ASSERT_FALSE(floatNode != 3.4);
  ASSERT_TRUE(strNode != 3.4);

  ASSERT_TRUE(3.4 != nullNode);
  ASSERT_TRUE(3.4 != boolNode);
  ASSERT_TRUE(3.4 != intNode);
  ASSERT_TRUE(4.5 != floatNode);
  ASSERT_FALSE(3.4 != floatNode);
  ASSERT_TRUE(3.4 != strNode);
}

TEST(JsonNodeTest, directStrComp) {
  JsonNode nullNode = nullptr;
  JsonNode boolNode = true;
  JsonNode intNode = 4;
  JsonNode floatNode = 3.4;
  JsonNode strNode = "abc";

  ASSERT_FALSE(nullNode == "abc");
  ASSERT_FALSE(boolNode == "abc");
  ASSERT_FALSE(intNode == "abc");
  ASSERT_FALSE(floatNode == "abc");
  ASSERT_FALSE(strNode == "bcd");
  ASSERT_TRUE(strNode == "abc");

  ASSERT_FALSE("abc" == nullNode);
  ASSERT_FALSE("abc" == boolNode);
  ASSERT_FALSE("abc" == intNode);
  ASSERT_FALSE("abc" == floatNode);
  ASSERT_FALSE("bcd" == strNode);
  ASSERT_TRUE("abc" == strNode);

  ASSERT_TRUE(nullNode != "abc");
  ASSERT_TRUE(boolNode != "abc");
  ASSERT_TRUE(intNode != "abc");
  ASSERT_TRUE(floatNode != "abc");
  ASSERT_TRUE(strNode != "bcd");
  ASSERT_FALSE(strNode != "abc");

  ASSERT_TRUE("abc" != nullNode);
  ASSERT_TRUE("abc" != boolNode);
  ASSERT_TRUE("abc" != intNode);
  ASSERT_TRUE("abc" != floatNode);
  ASSERT_TRUE("bcd" != strNode);
  ASSERT_FALSE("abc" != strNode);
}

TEST(JsonNodeTest, formatNull) {
  ASSERT_EQ("null", cds::format("{}", JsonNode(nullptr)));
  ASSERT_EQ("null", cds::format("{:p}", JsonNode(nullptr)));
  ASSERT_EQ("NULL", cds::format("{:P}", JsonNode(nullptr)));
}

TEST(JsonNodeTest, formatBool) {
  ASSERT_EQ("false", cds::format("{}", JsonNode(false)));
  ASSERT_EQ("true", cds::format("{}", JsonNode(true)));
  ASSERT_EQ("false", cds::format("{:s}", JsonNode(false)));
  ASSERT_EQ("true", cds::format("{:s}", JsonNode(true)));
}

TEST(JsonNodeTest, formatInt) {
  ASSERT_EQ("20", cds::format("{}", JsonNode(20)));
  ASSERT_EQ("20", cds::format("{}", JsonNode(20)));
  ASSERT_EQ("0x14", cds::format("{:#x}", JsonNode(20)));
  ASSERT_EQ("0X14", cds::format("{:#X}", JsonNode(20)));
}

TEST(JsonNodeTest, formatFloating) {
  ASSERT_EQ("3.4", cds::format("{}", JsonNode(3.4)));
  ASSERT_EQ("3.4", cds::format("{}", JsonNode(3.4)));
  ASSERT_EQ("3.400000e+00", cds::format("{:e}", JsonNode(3.4)));
  ASSERT_EQ("3.400000E+00", cds::format("{:E}", JsonNode(3.4)));
}

TEST(JsonNodeTest, formatString) {
  ASSERT_EQ("abc", cds::format("{}", JsonNode("abc")));
  ASSERT_EQ("a\tbc", cds::format("{}", JsonNode("a\tbc")));
  ASSERT_EQ("abc", cds::format("{:?}", JsonNode("abc")));
  ASSERT_EQ("a\\tbc", cds::format("{:?}", JsonNode("a\tbc")));
}
