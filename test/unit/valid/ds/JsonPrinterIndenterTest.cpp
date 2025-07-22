// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include "UnitTest.hpp"

namespace {
using namespace cds;
using namespace cds::json;
using namespace cds::json::impl;
} // namespace

TEST(JsonPrinterIndenterTest, addRemoveIndent) {
  JsonPrinterOptions options;
  options.indent = '.';
  options.indentWidth = 3;

  JsonPrinterContext ctx{options};
  ASSERT_EQ("", ctx.currentIndentBuffer);

  addIndent(ctx);
  ASSERT_EQ("...", ctx.currentIndentBuffer);

  addIndent(ctx);
  ASSERT_EQ("......", ctx.currentIndentBuffer);

  removeIndent(ctx);
  ASSERT_EQ("...", ctx.currentIndentBuffer);
}

TEST(JsonPrinterIndenterTest, addRemoveContIndent) {
  JsonPrinterOptions options;
  options.indent = '.';
  options.continuationIndentWidth = 5;

  JsonPrinterContext ctx{options};
  ASSERT_EQ("", ctx.currentIndentBuffer);

  addContinuationIndent(ctx);
  ASSERT_EQ(".....", ctx.currentIndentBuffer);

  addContinuationIndent(ctx);
  ASSERT_EQ("..........", ctx.currentIndentBuffer);

  removeContinuationIndent(ctx);
  ASSERT_EQ(".....", ctx.currentIndentBuffer);
}

TEST(JsonPrinterIndenterTest, constructAndRevert) {
  JsonPrinterOptions options;
  options.indent = '.';
  options.indentWidth = 3;

  JsonPrinterContext ctx{options};
  ASSERT_EQ("", ctx.currentIndentBuffer);

  addContinuationIndent(ctx);
  ASSERT_EQ("....", ctx.currentIndentBuffer);

  {
    String buffer;
    JsonPrinterOutput<String> printer{ctx, buffer};
    auto indenter = printer.indenter();

    indenter.newLineIndent();
    ASSERT_EQ("\n.......", buffer);
    ASSERT_EQ(".......", ctx.currentIndentBuffer);

    indenter.newLineContinuation();
    ASSERT_EQ("\n.......\n...........", buffer);
    ASSERT_EQ("...........", ctx.currentIndentBuffer);
  }

  ASSERT_EQ("....", ctx.currentIndentBuffer);
}

TEST(JsonPrinterIndenterTest, newLine) {
  JsonPrinterOptions options;
  options.indent = '.';
  JsonPrinterContext ctx{options};

  String buffer;
  JsonPrinterOutput<String> printer{ctx, buffer};
  auto indenter = printer.indenter();

  indenter.newLine();
  ASSERT_EQ("\n", buffer);
}

TEST(JsonPrinterIndenterTest, indent) {
  JsonPrinterOptions options;
  options.indent = '.';
  JsonPrinterContext ctx{options};
  ctx.currentIndentBuffer = "abc";

  String buffer;
  JsonPrinterOutput<String> printer{ctx, buffer};
  auto indenter = printer.indenter();

  indenter.indent();
  ASSERT_EQ("abc", buffer);
}

TEST(JsonPrinterIndenterTest, nlPreserve) {
  JsonPrinterOptions options;
  options.indent = '.';
  JsonPrinterContext ctx{options};
  ctx.currentIndentBuffer = "....";

  String buffer;
  JsonPrinterOutput<String> printer{ctx, buffer};
  auto indenter = printer.indenter();

  indenter.newLinePreserveIndent();
  ASSERT_EQ("\n....", buffer);
}

TEST(JsonPrinterIndenterTest, nlIndent) {
  JsonPrinterOptions options;
  options.indent = '_';
  JsonPrinterContext ctx{options};
  ctx.currentIndentBuffer = "....";

  String buffer;
  JsonPrinterOutput<String> printer{ctx, buffer};
  auto indenter = printer.indenter();

  indenter.newLineIndent();
  ASSERT_EQ("\n....__", buffer);
}

TEST(JsonPrinterIndenterTest, nlContIndent) {
  JsonPrinterOptions options;
  options.indent = '_';
  JsonPrinterContext ctx{options};
  ctx.currentIndentBuffer = "....";

  String buffer;
  JsonPrinterOutput<String> printer{ctx, buffer};
  auto indenter = printer.indenter();

  indenter.newLineContinuation();
  ASSERT_EQ("\n....____", buffer);
}

TEST(JsonPrinterIndenterTest, storeAndRestore) {
  JsonPrinterOptions options;
  options.indent = '_';
  JsonPrinterContext ctx{options};
  ctx.currentIndentBuffer = "....";

  String buffer;
  JsonPrinterOutput<String> printer{ctx, buffer};
  auto indenter = printer.indenter();

  indenter.newLineContinuation();
  ASSERT_EQ("\n....____", buffer);

  auto state = indenter.store();
  indenter.newLineContinuation();
  indenter.newLineContinuation();
  ASSERT_EQ("\n....____\n....________\n....____________", buffer);

  indenter.restore(state);
  indenter.newLinePreserveIndent();
  ASSERT_EQ("\n....____\n....________\n....____________\n....____", buffer);
}
