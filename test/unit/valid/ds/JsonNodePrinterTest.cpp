// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include "UnitTest.hpp"

#include <cds/collection/Vector>

namespace {
using namespace cds;
using namespace cds::json;
using namespace cds::json::impl;
} // namespace

TEST(JsonNodePrinterTest, printNull) {
  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonNode node = nullptr;
  printJsonNode(printer, node, ctx);

  ASSERT_EQ("null", output);
}

TEST(JsonNodePrinterTest, printBool) {
  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonNode node = true;
  printJsonNode(printer, node, ctx);

  ASSERT_EQ("true", output);
}

TEST(JsonNodePrinterTest, printInt) {
  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonNode node = 512;
  printJsonNode(printer, node, ctx);

  ASSERT_EQ("512", output);
}

TEST(JsonNodePrinterTest, printFloating) {
  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonNode node = 3.14;
  printJsonNode(printer, node, ctx);

  ASSERT_EQ("3.140000", output);
}

TEST(JsonNodePrinterTest, printString) {
  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonNode node = R"(abc
def
  ghi)";
  printJsonNode(printer, node, ctx);

  ASSERT_EQ(R"("abc\ndef\n  ghi")", output);
}

TEST(JsonNodePrinterTest, printArray) {
  JsonPrinterOptions options{};
  options.arrayBreakdown = RearrangeKind::KeepInline;
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonNode node = {5, false, "abc"};
  printJsonNode(printer, node, ctx);

  ASSERT_EQ(R"([5, false, "abc"])", output);
}

TEST(JsonNodePrinterTest, printObject) {
  JsonPrinterOptions options{};
  options.objectBreakdown = RearrangeKind::KeepInline;
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonNode node = {
      {"a", 5},
      {"b", false},
      {"c", "abc"}
  };
  printJsonNode(printer, node, ctx);

  ASSERT_EQ(R"({"a": 5, "b": false, "c": "abc"})", output);
}
