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

TEST(JsonPrinterOutputStringTest, forceWriteChar) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWrite('a');
  out.forceWrite('b');
  out.forceWrite('c');

  ASSERT_EQ("abc", buf);
  ASSERT_EQ(3, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteStringView) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWrite(StringView{"abc"});
  out.forceWrite(StringView{"x"});
  out.forceWrite(StringView{"tuv"});

  ASSERT_EQ("abcxtuv", buf);
  ASSERT_EQ(7, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteLiteral) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWrite("abc");
  out.forceWrite("x");
  out.forceWrite("tuv");

  ASSERT_EQ("abcxtuv", buf);
  ASSERT_EQ(7, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteBool) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWrite(true);
  out.forceWrite(false);

  ASSERT_EQ("truefalse", buf);
  ASSERT_EQ(9, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteIntegral) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWrite(1234);
  out.forceWrite(1000);
  out.forceWrite(-500);

  ASSERT_EQ("12341000-500", buf);
  ASSERT_EQ(12, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteFloating) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWrite(3.14);
  out.forceWrite(3.4);
  out.forceWrite(5.3f);

  ASSERT_EQ("3.1400003.4000005.300000", buf);
  ASSERT_EQ(24, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteEscaped) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWriteEscaped("abc\t\n\r\f\\abc");

  ASSERT_EQ(R"("abc\t\n\r\f\\abc")", buf);
  ASSERT_EQ(18, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteEscapedUTFOpt) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  opt.printNonAsciiAsUTFCodePoints = true;
  out.forceWriteEscaped("abc\t\n\r\f\\abc\u01ab\u1ab1abc");

  ASSERT_EQ(R"("abc\t\n\r\f\\abc\u01ab\u1ab1abc")", buf);
  ASSERT_EQ(33, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteEscapedUTF) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  out.forceWriteEscapedUTF("abc\t\n\r\f\\abc\u01ab\u1ab1abc");

  ASSERT_EQ(R"("abc\t\n\r\f\\abc\u01ab\u1ab1abc")", buf);
  ASSERT_EQ(33, out.onLine);
}

TEST(JsonPrinterOutputStringTest, forceWriteEscapedUTFInvalid2bEncodingTooShort) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  try {
    U8 buffer[] = {0xC0u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 1});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStringTest, forceWriteEscapedUTFInvalid2bEncoding) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  try {
    U8 buffer[] = {0xC0u, 0xC0u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 2});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStringTest, forceWriteEscapedUTFInvalid3bEncodingTooShort) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  try {
    U8 buffer[] = {0xE0u, 0x80u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 2});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStringTest, forceWriteEscapedUTFInvalid3bEncoding) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  try {
    U8 buffer[] = {0xE0u, 0x80u, 0xC0u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 3});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStringTest, forceWriteEscapedUTFUnsupported4BytesEncoding) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  try {
    U8 buffer[] = {0xF0u, 0x80u, 0x80u, 0x80u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 4});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStringTest, fitsSize) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  opt.columnLimit = 20;

  ASSERT_TRUE(out.fits(Size(20)));
  out.forceWrite("abcde");
  ASSERT_FALSE(out.fits(Size(20)));
  ASSERT_FALSE(out.fits(Size(16)));
  ASSERT_TRUE(out.fits(Size(15)));
}

TEST(JsonPrinterOutputStringTest, fitsChar) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  opt.columnLimit = 6;

  ASSERT_TRUE(out.fits('a'));
  out.forceWrite("abcde");
  ASSERT_TRUE(out.fits('a'));
  out.forceWrite("f");
  ASSERT_FALSE(out.fits('a'));
}

TEST(JsonPrinterOutputStringTest, fitsStringView) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  opt.columnLimit = 5;

  ASSERT_TRUE(out.fits("abcd"));
  out.forceWrite("a");
  ASSERT_TRUE(out.fits("abcd"));
  out.forceWrite("a");
  ASSERT_FALSE(out.fits("abcd"));
  ASSERT_TRUE(out.fits("abc"));
}

TEST(JsonPrinterOutputStringTest, writeChar) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  opt.columnLimit = 5;
  out.forceWrite("abcd");
  ASSERT_EQ("abcd", buf);

  ASSERT_TRUE(out.write('e'));
  ASSERT_EQ("abcde", buf);
  ASSERT_FALSE(out.write('f'));
  ASSERT_EQ("abcde", buf);
}

TEST(JsonPrinterOutputStringTest, writeStr) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  opt.columnLimit = 6;
  out.forceWrite("abcd");
  ASSERT_EQ("abcd", buf);

  ASSERT_FALSE(out.write("efg"));
  ASSERT_EQ("abcd", buf);
  ASSERT_TRUE(out.write("ef"));
  ASSERT_EQ("abcdef", buf);
}

TEST(JsonPrinterOutputStringTest, finishLine) {
  String buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<String> out{ctx, buf};

  opt.columnLimit = 6;
  out.forceWrite("abcd");
  ASSERT_EQ("abcd", buf);
  ASSERT_EQ(4, out.onLine);

  out.finishLine(opt.newLine);
  ASSERT_EQ("abcd\n", buf);
  ASSERT_EQ(0, out.onLine);
}
