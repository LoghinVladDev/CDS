// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include "UnitTest.hpp"
#include <sstream>

namespace {
using namespace cds;
using namespace cds::json;
using namespace cds::json::impl;
} // namespace

TEST(JsonPrinterOutputStreamTest, forceWriteChar) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWrite('a');
  out.forceWrite('b');
  out.forceWrite('c');

  ASSERT_EQ("abc", buf.str());
  ASSERT_EQ(3, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteStringView) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWrite(StringView{"abc"});
  out.forceWrite(StringView{"x"});
  out.forceWrite(StringView{"tuv"});

  ASSERT_EQ("abcxtuv", buf.str());
  ASSERT_EQ(7, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteLiteral) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWrite("abc");
  out.forceWrite("x");
  out.forceWrite("tuv");

  ASSERT_EQ("abcxtuv", buf.str());
  ASSERT_EQ(7, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteBool) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWrite(true);
  out.forceWrite(false);

  ASSERT_EQ("truefalse", buf.str());
  ASSERT_EQ(9, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteIntegral) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWrite(1234);
  out.forceWrite(1000);
  out.forceWrite(-500);

  ASSERT_EQ("12341000-500", buf.str());
  ASSERT_EQ(12, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteFloating) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWrite(3.14);
  out.forceWrite(3.4);
  out.forceWrite(5.3f);

  ASSERT_EQ("3.143.45.3", buf.str());
  ASSERT_EQ(10, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscaped) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWriteEscaped("abc\t\n\r\f\\abc");

  ASSERT_EQ(R"("abc\t\n\r\f\\abc")", buf.str());
  ASSERT_EQ(18, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscapedUTFOpt) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  opt.printNonAsciiAsUTFCodePoints = true;
  out.forceWriteEscaped("abc\t\n\r\f\\abc\u01ab\u1ab1abc");

  ASSERT_EQ(R"("abc\t\n\r\f\\abc\u01ab\u1ab1abc")", buf.str());
  ASSERT_EQ(33, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscapedUTF) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  out.forceWriteEscapedUTF("abc\t\n\r\f\\abc\u01ab\u1ab1abc");

  ASSERT_EQ(R"("abc\t\n\r\f\\abc\u01ab\u1ab1abc")", buf.str());
  ASSERT_EQ(33, out.onLine);
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscapedUTFInvalid2bEncodingTooShort) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  try {
    U8 buffer[] = {0xC0u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 1});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscapedUTFInvalid2bEncoding) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  try {
    U8 buffer[] = {0xC0u, 0xC0u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 2});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscapedUTFInvalid3bEncodingTooShort) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  try {
    U8 buffer[] = {0xE0u, 0x80u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 2});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscapedUTFInvalid3bEncoding) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  try {
    U8 buffer[] = {0xE0u, 0x80u, 0xC0u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 3});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStreamTest, forceWriteEscapedUTFUnsupported4BytesEncoding) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  try {
    U8 buffer[] = {0xF0u, 0x80u, 0x80u, 0x80u};
    out.forceWriteEscapedUTF(StringView {static_cast<char const*>(static_cast<void const*>(buffer)), 4});
    ASSERT_FALSE(true);
  } catch (InvalidUTF8EncodingException const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(JsonPrinterOutputStreamTest, fitsSize) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  opt.columnLimit = 20;

  ASSERT_TRUE(out.fits(Size(20)));
  out.forceWrite("abcde");
  ASSERT_FALSE(out.fits(Size(20)));
  ASSERT_FALSE(out.fits(Size(16)));
  ASSERT_TRUE(out.fits(Size(15)));
}

TEST(JsonPrinterOutputStreamTest, fitsChar) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  opt.columnLimit = 6;

  ASSERT_TRUE(out.fits('a'));
  out.forceWrite("abcde");
  ASSERT_TRUE(out.fits('a'));
  out.forceWrite("f");
  ASSERT_FALSE(out.fits('a'));
}

TEST(JsonPrinterOutputStreamTest, fitsStringView) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  opt.columnLimit = 5;

  ASSERT_TRUE(out.fits("abcd"));
  out.forceWrite("a");
  ASSERT_TRUE(out.fits("abcd"));
  out.forceWrite("a");
  ASSERT_FALSE(out.fits("abcd"));
  ASSERT_TRUE(out.fits("abc"));
}

TEST(JsonPrinterOutputStreamTest, writeChar) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  opt.columnLimit = 5;
  out.forceWrite("abcd");
  ASSERT_EQ("abcd", buf.str());

  ASSERT_TRUE(out.write('e'));
  ASSERT_EQ("abcde", buf.str());
  ASSERT_FALSE(out.write('f'));
  ASSERT_EQ("abcde", buf.str());
}

TEST(JsonPrinterOutputStreamTest, writeStr) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  opt.columnLimit = 6;
  out.forceWrite("abcd");
  ASSERT_EQ("abcd", buf.str());

  ASSERT_FALSE(out.write("efg"));
  ASSERT_EQ("abcd", buf.str());
  ASSERT_TRUE(out.write("ef"));
  ASSERT_EQ("abcdef", buf.str());
}

TEST(JsonPrinterOutputStreamTest, finishLine) {
  std::stringstream buf;
  JsonPrinterOptions opt{};
  JsonPrinterContext ctx{opt};
  JsonPrinterOutput<std::ostream> out{ctx, buf};

  opt.columnLimit = 6;
  out.forceWrite("abcd");
  ASSERT_EQ("abcd", buf.str());
  ASSERT_EQ(4, out.onLine);

  out.finishLine(opt.newLine);
  ASSERT_EQ("abcd\n", buf.str());
  ASSERT_EQ(0, out.onLine);
}
