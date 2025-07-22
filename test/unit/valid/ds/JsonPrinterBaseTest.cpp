// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include "UnitTest.hpp"

namespace {
using namespace cds;
using namespace cds::json;
using namespace cds::json::impl;

class DerivedPrinter : public JsonPrinterBase<DerivedPrinter> {
public:
  using JsonPrinterBase<DerivedPrinter>::JsonPrinterBase;

  auto printer(JsonPrinterContext& ctx) noexcept -> JsonPrinterOutput<String> {
    return {ctx, buffer};
  }

  String buffer;
};
} // namespace

TEST(JsonPrinterBaseTest, optionsCtr) {
  JsonPrinterOptions opt{};
  opt.columnLimit = 100;

  auto printer = DerivedPrinter{opt};
  ASSERT_EQ(100, printer.options().columnLimit);
}

TEST(JsonPrinterBaseTest, writeArray) {
  JsonPrinterOptions opt{};
  auto printer = DerivedPrinter{opt};

  JsonArray arr = {1, false, "abc"};

  printer.write(arr);
  ASSERT_EQ(printer.buffer, R"([
  1,
  false,
  "abc"
])");
}

TEST(JsonPrinterBaseTest, writeObject) {
  JsonPrinterOptions opt{};
  auto printer = DerivedPrinter{opt};

  JsonObject obj = {
      {"a", 1},
      {"b", false},
      {"c", "abc"}
  };

  printer.write(obj);
  ASSERT_EQ(printer.buffer, R"({
  "a": 1,
  "b": false,
  "c": "abc"
})");
}
