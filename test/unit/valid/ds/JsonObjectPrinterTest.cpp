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

TEST(JsonObjectPrinterTest, printEmptyDefault) {
  JsonObject arr;

  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{}", output);
}

TEST(JsonObjectPrinterTest, printEmptySpaceBeforeLB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.beforeLeftBrace = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(" {}", output);
}

TEST(JsonObjectPrinterTest, printEmptyNLBeforeLB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.beforeLeftBrace = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("\n    {}", output);
}

TEST(JsonObjectPrinterTest, printEmptySpaceAfterLB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.afterLeftBrace = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{ }", output);
}

TEST(JsonObjectPrinterTest, printEmptyNLAfterLB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.afterLeftBrace = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{}", output);
}

TEST(JsonObjectPrinterTest, printObjectStartOnCont) {
  JsonObject arr;

  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printer.onLine = options.columnLimit;
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("\n    {}", output);
}

TEST(JsonObjectPrinterTest, printObjectSpaceBeforeRB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.beforeRightBrace = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{ }", output);
}

TEST(JsonObjectPrinterTest, printObjectNLBeforeRB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.beforeRightBrace = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{\n}", output);
}

TEST(JsonObjectPrinterTest, printObjectSpaceAfterRB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.afterRightBrace = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{} ", output);
}

TEST(JsonObjectPrinterTest, printObjectNLAfterRB) {
  JsonObject arr;

  JsonPrinterOptions options{};
  options.afterRightBrace = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{}\n", output);
}

TEST(JsonObjectPrinterTest, printObjectEndOnCont) {
  JsonObject arr;

  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printer.onLine = options.columnLimit - 1;
  printJsonObject(printer, arr, ctx);

  ASSERT_EQ("{\n}", output);
}

TEST(JsonObjectPrinterTest, chopDown) {
  JsonObject arr = {
    {"a", 1},
    {"b", "smol"},
    {"c", 3.4},
    {"d", "this is a string"},
    {"e", true},
    {"f", "str"},
  };

  JsonPrinterOptions options{};
  options.columnLimit = 30;
  options.objectBreakdown = RearrangeKind::ChopDownIfLong;
  options.afterLeftBrace = SpacingKind::None;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(R"({"a": 1, "b": "smol",
    "c": 3.400000,
    "d": "this is a string",
    "e": true, "f": "str"})", output);
}

TEST(JsonObjectPrinterTest, chopDownSpcBeforeSep) {
  JsonObject arr = {
    {"a", 1},
    {"b", "smol"},
    {"c", 3.4},
    {"d", "this is a string"},
    {"e", true},
    {"f", "str"},
  };

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::Space;
  options.columnLimit = 30;
  options.objectBreakdown = RearrangeKind::ChopDownIfLong;
  options.afterLeftBrace = SpacingKind::None;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(R"({"a": 1 , "b": "smol" ,
    "c": 3.400000 ,
    "d": "this is a string" ,
    "e": true , "f": "str"})", output);
}

TEST(JsonObjectPrinterTest, spaceBeforeSep) {
  JsonObject arr = {
    {"a", 1},
    {"b", false},
    {"c", "string"},
  };

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::Space;
  options.afterSeparator = SpacingKind::None;
  options.objectBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(R"({"a": 1 ,"b": false ,"c": "string"})", output);
}

TEST(JsonObjectPrinterTest, spaceAfterSep) {
  JsonObject arr = {
      {"a", 1},
      {"b", false},
      {"c", "string"},
  };

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::None;
  options.afterSeparator = SpacingKind::Space;
  options.objectBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(R"({"a": 1, "b": false, "c": "string"})", output);
}

TEST(JsonObjectPrinterTest, nlBeforeSep) {
  JsonObject arr = {
      {"a", 1},
      {"b", false},
      {"c", "string"},
  };

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::Newline;
  options.afterSeparator = SpacingKind::None;
  options.objectBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(R"({"a": 1
  ,"b": false
  ,"c": "string"})", output);
}

TEST(JsonObjectPrinterTest, nlAfterSep) {
  JsonObject arr = {
      {"a", 1},
      {"b", false},
      {"c", "string"},
  };

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::None;
  options.afterSeparator = SpacingKind::Newline;
  options.objectBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(R"({"a": 1,
  "b": false,
  "c": "string"})", output);
}

TEST(JsonObjectPrinterTest, customTokens) {
  JsonObject arr = {
      {"a", 1},
      {"b", false},
      {"c", "string"},
  };

  JsonPrinterOptions options{};
  options.objectStartIndicator = "obj<";
  options.objectEndIndicator = ">obj";
  options.objectBreakdown = RearrangeKind::KeepInline;
  options.elementSeparator = "|-|";
  options.spacing = '.';

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonObject(printer, arr, ctx);

  ASSERT_EQ(R"(obj<"a": 1|-|."b": false|-|."c": "string">obj)", output);
}
