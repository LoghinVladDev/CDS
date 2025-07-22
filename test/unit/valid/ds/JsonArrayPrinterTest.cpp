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

TEST(JsonArrayPrinterTest, printEmptyDefault) {
  JsonArray arr;

  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[]", output);
}

TEST(JsonArrayPrinterTest, printEmptySpaceBeforeLB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.beforeLeftSquareBracket = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(" []", output);
}

TEST(JsonArrayPrinterTest, printEmptyNLBeforeLB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.beforeLeftSquareBracket = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("\n    []", output);
}

TEST(JsonArrayPrinterTest, printEmptySpaceAfterLB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.afterLeftSquareBracket = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[ ]", output);
}

TEST(JsonArrayPrinterTest, printEmptyNLAfterLB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.afterLeftSquareBracket = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[]", output);
}

TEST(JsonArrayPrinterTest, printArrayStartOnCont) {
  JsonArray arr;

  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printer.onLine = options.columnLimit - 1;
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("\n    []", output);
}

TEST(JsonArrayPrinterTest, printArraySpaceBeforeRB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.beforeRightSquareBracket = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[ ]", output);
}

TEST(JsonArrayPrinterTest, printArrayNLBeforeRB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.beforeRightSquareBracket = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[\n]", output);
}

TEST(JsonArrayPrinterTest, printArraySpaceAfterRB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.afterRightSquareBracket = SpacingKind::Space;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[] ", output);
}

TEST(JsonArrayPrinterTest, printArrayNLAfterRB) {
  JsonArray arr;

  JsonPrinterOptions options{};
  options.afterRightSquareBracket = SpacingKind::Newline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[]\n", output);
}

TEST(JsonArrayPrinterTest, printArrayEndOnCont) {
  JsonArray arr;

  JsonPrinterOptions options{};
  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};
  printer.onLine = options.columnLimit - 2;
  printJsonArray(printer, arr, ctx);

  ASSERT_EQ("[\n]", output);
}

TEST(JsonArrayPrinterTest, chopDown) {
  JsonArray arr = {1, "smol", 3.4, "this is a string", true, "str"};

  JsonPrinterOptions options{};
  options.columnLimit = 20;
  options.arrayBreakdown = RearrangeKind::ChopDownIfLong;
  options.afterLeftSquareBracket = SpacingKind::None;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(R"([1, "smol",
    3.400000,
    "this is a string",
    true, "str"])", output);
}

TEST(JsonArrayPrinterTest, chopDownSpcBeforeSep) {
  JsonArray arr = {1, "smol", 3.4, "this is a string", true, "str"};

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::Space;
  options.columnLimit = 20;
  options.arrayBreakdown = RearrangeKind::ChopDownIfLong;
  options.afterLeftSquareBracket = SpacingKind::None;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(R"([1 , "smol" ,
    3.400000 ,
    "this is a string" ,
    true , "str"])", output);
}

TEST(JsonArrayPrinterTest, spaceBeforeSep) {
  JsonArray arr = {1, false, "string"};

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::Space;
  options.afterSeparator = SpacingKind::None;
  options.arrayBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(R"([1 ,false ,"string"])", output);
}

TEST(JsonArrayPrinterTest, spaceAfterSep) {
  JsonArray arr = {1, false, "string"};

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::None;
  options.afterSeparator = SpacingKind::Space;
  options.arrayBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(R"([1, false, "string"])", output);
}

TEST(JsonArrayPrinterTest, nlBeforeSep) {
  JsonArray arr = {1, false, "string"};

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::Newline;
  options.afterSeparator = SpacingKind::None;
  options.arrayBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(R"([1
  ,false
  ,"string"])", output);
}

TEST(JsonArrayPrinterTest, nlAfterSep) {
  JsonArray arr = {1, false, "string"};

  JsonPrinterOptions options{};
  options.beforeSeparator = SpacingKind::None;
  options.afterSeparator = SpacingKind::Newline;
  options.arrayBreakdown = RearrangeKind::KeepInline;

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(R"([1,
  false,
  "string"])", output);
}

TEST(JsonArrayPrinterTest, customTokens) {
  JsonArray arr = {1, false, "string"};

  JsonPrinterOptions options{};
  options.arrayStartIndicator = "array<";
  options.arrayEndIndicator = ">array";
  options.arrayBreakdown = RearrangeKind::KeepInline;
  options.elementSeparator = "|-|";
  options.spacing = '.';

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  printJsonArray(printer, arr, ctx);

  ASSERT_EQ(R"(array<1|-|.false|-|."string">array)", output);
}
