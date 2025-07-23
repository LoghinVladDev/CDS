// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include "UnitTest.hpp"

namespace {
using namespace cds::json;
} // namespace

TEST(JsonPrinterTest, printAsJson) {
  JsonObject obj = R"({)"
                   R"("abc": 1, )"
                   R"("bcd": false, )"
                   R"("cde": "abc", )"
                   R"("def": [1, false, "cbd"], )"
                   R"("efg": {)"
                   R"("a": "b", )"
                   R"("b": false, )"
                   R"("c": [1, false, "cbd"])"
                   R"(})"
                   R"(})";

  JsonStringPrinter printer;
  ASSERT_EQ(printer.write(obj).out(),
            R"({
  "abc": 1,
  "bcd": false,
  "cde": "abc",
  "def": [
    1,
    false,
    "cbd"
  ],
  "efg": {
    "a": "b",
    "b": false,
    "c": [
      1,
      false,
      "cbd"
    ]
  }
})"
  );
}

TEST(JsonPrinterTest, printAsJsonToStream) {
  JsonObject obj = R"({)"
                   R"("abc": 1, )"
                   R"("bcd": false, )"
                   R"("cde": "abc", )"
                   R"("def": [1, false, "cbd"], )"
                   R"("efg": {)"
                   R"("a": "b", )"
                   R"("b": false, )"
                   R"("c": [1, false, "cbd"])"
                   R"(})"
                   R"(})";

  std::stringstream buf;
  JsonStreamPrinter printer{buf};
  printer.write(obj);
  ASSERT_EQ(buf.str(),
            R"({
  "abc": 1,
  "bcd": false,
  "cde": "abc",
  "def": [
    1,
    false,
    "cbd"
  ],
  "efg": {
    "a": "b",
    "b": false,
    "c": [
      1,
      false,
      "cbd"
    ]
  }
})"
  );
}

TEST(JsonPrinterTest, printAsXML) {
  JsonObject obj = R"({)"
                   R"("abc": 1, )"
                   R"("bcd": false, )"
                   R"("cde": "abc", )"
                   R"("def": [1, false, "cbd"], )"
                   R"("efg": {)"
                   R"("a": "b", )"
                   R"("b": false, )"
                   R"("c": [1, false, "cbd"])"
                   R"(})"
                   R"(})";

  JsonPrinterOptions options{};
  options.afterLeftBrace = cds::json::impl::SpacingKind::None;
  options.afterLeftSquareBracket = cds::json::impl::SpacingKind::None;
  options.elementSeparator = "";
  options.arrayStartIndicator = "";
  options.arrayEndIndicator = "";
  options.objectStartIndicator = "";
  options.objectEndIndicator = "";
  options.arrayElementPresentation = R"(<${key}>${value}</${key}>)";
  options.objectEntryPresentation = R"(<${key}>${value}</${key}>)";
  JsonStringPrinter printer(options);

  // imperfect, but not a focus point
  ASSERT_EQ(printer.write(obj).out(),
            R"(
  <abc>1</abc>
  <bcd>false</bcd>
  <cde>"abc"</cde>
  <def>
    <def>1</def>
    <def>false</def>
    <def>"cbd"</def>
  </def>
  <efg>
    <a>"b"</a>
    <b>false</b>
    <c>
      <c>1</c>
      <c>false</c>
      <c>"cbd"</c>
    </c>
  </efg>
)");
}
