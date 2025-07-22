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

TEST(JsonPrinterContextTest, imbueForArray) {
  JsonPrinterOptions options{};
  options.arrayElementPresentation = "[${index}] = ${value}";

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonArray array = {1, false, "abc"};

  auto presenter0 = ctx.imbuePresenterFor(0);
  presenter0(printer, array[0], ctx);
  ASSERT_EQ("[0] = 1", output);

  output.clear();
  auto presenter1 = ctx.imbuePresenterFor(1);
  presenter1(printer, array[1], ctx);
  ASSERT_EQ("[1] = false", output);

  output.clear();
  auto presenter2 = ctx.imbuePresenterFor(2);
  presenter2(printer, array[2], ctx);
  ASSERT_EQ(R"([2] = "abc")", output);
}

TEST(JsonPrinterContextTest, imbueForObject) {
  JsonPrinterOptions options{};
  options.objectEntryPresentation = "[${key}] = ${value}";

  JsonPrinterContext ctx{options};
  String output;
  JsonPrinterOutput<String> printer{ctx, output};

  JsonObject obj = {
      {"a", 1},
      {"b", false},
      {"c", "abc"}
  };

  auto presenter0 = ctx.imbuePresenterFor("a");
  presenter0(printer, obj["a"], ctx);
  ASSERT_EQ("[a] = 1", output);

  output.clear();
  auto presenter1 = ctx.imbuePresenterFor("b");
  presenter1(printer, obj["b"], ctx);
  ASSERT_EQ("[b] = false", output);

  output.clear();
  auto presenter2 = ctx.imbuePresenterFor("c");
  presenter2(printer, obj["c"], ctx);
  ASSERT_EQ(R"([c] = "abc")", output);
}
