// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/StringView>
#include "UnitTest.hpp"

using namespace cds::impl;
using U = StringUtils<char, StringTraits<char>>;
using A = StringAbstract<>;
using WU = StringUtils<wchar_t, StringTraits<wchar_t>>;

static_assert('a' == L'a', "unexpected encoding");
static_assert('a' == u'a', "unexpected encoding");
static_assert('a' == U'a', "unexpected encoding");

#ifdef DCR_SINCECPP20
static_assert('a' == u8'a', "unexpected encoding");
#endif

TEST(StringUtils, StartsWith) {
  char const n[] = "abc";
  char const a[] = "";
  char const b[] = "ab";
  char const c[] = "abc";
  char const d[] = "abcd";
  char const e[] = "abbc";
  char const f[] = "babcd";

  ASSERT_FALSE(U::startsWith(A::data(a), A::length(a), 'b'));
  ASSERT_FALSE(U::startsWith(A::data(c), A::length(c), 'b'));
  ASSERT_TRUE(U::startsWith(A::data(c), A::length(c), 'a'));
  ASSERT_FALSE(U::startsWith(A::data(a), A::length(a), n));
  ASSERT_FALSE(U::startsWith(A::data(b), A::length(b), n));
  ASSERT_TRUE(U::startsWith(A::data(c), A::length(c), n));
  ASSERT_TRUE(U::startsWith(A::data(d), A::length(d), n));
  ASSERT_FALSE(U::startsWith(A::data(e), A::length(e), n));
  ASSERT_FALSE(U::startsWith(A::data(f), A::length(f), n));
}

TEST(StringUtils, EndsWith) {
  char const n[] = "abc";
  char const a[] = "";
  char const b[] = "ab";
  char const c[] = "abc";
  char const d[] = "dabc";
  char const e[] = "dabbc";
  char const f[] = "dabcb";

  ASSERT_FALSE(U::endsWith(A::data(a), A::length(a), 'b'));
  ASSERT_FALSE(U::endsWith(A::data(c), A::length(c), 'b'));
  ASSERT_TRUE(U::endsWith(A::data(c), A::length(c), 'c'));
  ASSERT_FALSE(U::endsWith(A::data(a), A::length(a), n));
  ASSERT_FALSE(U::endsWith(A::data(b), A::length(b), n));
  ASSERT_TRUE(U::endsWith(A::data(c), A::length(c), n));
  ASSERT_TRUE(U::endsWith(A::data(d), A::length(d), n));
  ASSERT_FALSE(U::endsWith(A::data(e), A::length(e), n));
  ASSERT_FALSE(U::endsWith(A::data(f), A::length(f), n));
}

TEST(StringUtils, WideStartsWith) {
  wchar_t const n[] = L"abc";
  wchar_t const a[] = L"";
  wchar_t const b[] = L"ab";
  wchar_t const c[] = L"abc";
  wchar_t const d[] = L"abcd";
  wchar_t const e[] = L"abbc";
  wchar_t const f[] = L"babcd";

  ASSERT_FALSE(WU::startsWith(A::data(a), A::length(a), L'b'));
  ASSERT_FALSE(WU::startsWith(A::data(c), A::length(c), L'b'));
  ASSERT_TRUE(WU::startsWith(A::data(c), A::length(c), L'a'));
  ASSERT_FALSE(WU::startsWith(A::data(a), A::length(a), n));
  ASSERT_FALSE(WU::startsWith(A::data(b), A::length(b), n));
  ASSERT_TRUE(WU::startsWith(A::data(c), A::length(c), n));
  ASSERT_TRUE(WU::startsWith(A::data(d), A::length(d), n));
  ASSERT_FALSE(WU::startsWith(A::data(e), A::length(e), n));
  ASSERT_FALSE(WU::startsWith(A::data(f), A::length(f), n));
}

TEST(StringUtils, WideEndsWith) {
  wchar_t const n[] = L"abc";
  wchar_t const a[] = L"";
  wchar_t const b[] = L"ab";
  wchar_t const c[] = L"abc";
  wchar_t const d[] = L"dabc";
  wchar_t const e[] = L"dabbc";
  wchar_t const f[] = L"dabcb";

  ASSERT_FALSE(WU::endsWith(A::data(a), A::length(a), L'b'));
  ASSERT_FALSE(WU::endsWith(A::data(c), A::length(c), L'b'));
  ASSERT_TRUE(WU::endsWith(A::data(c), A::length(c), L'c'));
  ASSERT_FALSE(WU::endsWith(A::data(a), A::length(a), n));
  ASSERT_FALSE(WU::endsWith(A::data(b), A::length(b), n));
  ASSERT_TRUE(WU::endsWith(A::data(c), A::length(c), n));
  ASSERT_TRUE(WU::endsWith(A::data(d), A::length(d), n));
  ASSERT_FALSE(WU::endsWith(A::data(e), A::length(e), n));
  ASSERT_FALSE(WU::endsWith(A::data(f), A::length(f), n));
}

TEST(StringUtils, intLength) {
  ASSERT_EQ(U::intLength(0b11001100, 2), 8);
  ASSERT_EQ(U::intLength(-0b11001100, 2), 9);
  ASSERT_EQ(U::intLength(023512, 8), 5);
  ASSERT_EQ(U::intLength(-023512, 8), 6);
  ASSERT_EQ(U::intLength(1205400, 10), 7);
  ASSERT_EQ(U::intLength(-1205400, 10), 8);
  ASSERT_EQ(U::intLength(0xafbef41, 16), 7);
  ASSERT_EQ(U::intLength(-0xafbef41, 16), 8);

  ASSERT_EQ(U::intLength(0b0, 2), 1);
  ASSERT_EQ(U::intLength(-0b0, 2), 1);
  ASSERT_EQ(U::intLength(00, 8), 1);
  ASSERT_EQ(U::intLength(-00, 8), 1);
  ASSERT_EQ(U::intLength(0, 10), 1);
  ASSERT_EQ(U::intLength(-0, 10), 1);
  ASSERT_EQ(U::intLength(0x0, 16), 1);
  ASSERT_EQ(U::intLength(-0x0, 16), 1);

  ASSERT_EQ(U::intLength(1, 10), 1);
  ASSERT_EQ(U::intLength(11, 10), 2);
  ASSERT_EQ(U::intLength(111, 10), 3);
  ASSERT_EQ(U::intLength(1111, 10), 4);
  ASSERT_EQ(U::intLength(11111, 10), 5);
  ASSERT_EQ(U::intLength(111111, 10), 6);
  ASSERT_EQ(U::intLength(1111111, 10), 7);
  ASSERT_EQ(U::intLength(11111111, 10), 8);
  ASSERT_EQ(U::intLength(111111111, 10), 9);
  ASSERT_EQ(U::intLength(1111111111, 10), 10);
  ASSERT_EQ(U::intLength(11111111111, 10), 11);
}

TEST(StringUtils, wideIntLength) {
  ASSERT_EQ(WU::intLength(0b11001100, 2), 8);
  ASSERT_EQ(WU::intLength(-0b11001100, 2), 9);
  ASSERT_EQ(WU::intLength(023512, 8), 5);
  ASSERT_EQ(WU::intLength(-023512, 8), 6);
  ASSERT_EQ(WU::intLength(1205400, 10), 7);
  ASSERT_EQ(WU::intLength(-1205400, 10), 8);
  ASSERT_EQ(WU::intLength(0xafbef41, 16), 7);
  ASSERT_EQ(WU::intLength(-0xafbef41, 16), 8);

  ASSERT_EQ(WU::intLength(0b0, 2), 1);
  ASSERT_EQ(WU::intLength(-0b0, 2), 1);
  ASSERT_EQ(WU::intLength(00, 8), 1);
  ASSERT_EQ(WU::intLength(-00, 8), 1);
  ASSERT_EQ(WU::intLength(0, 10), 1);
  ASSERT_EQ(WU::intLength(-0, 10), 1);
  ASSERT_EQ(WU::intLength(0x0, 16), 1);
  ASSERT_EQ(WU::intLength(-0x0, 16), 1);

  ASSERT_EQ(WU::intLength(1, 10), 1);
  ASSERT_EQ(WU::intLength(11, 10), 2);
  ASSERT_EQ(WU::intLength(111, 10), 3);
  ASSERT_EQ(WU::intLength(1111, 10), 4);
  ASSERT_EQ(WU::intLength(11111, 10), 5);
  ASSERT_EQ(WU::intLength(111111, 10), 6);
  ASSERT_EQ(WU::intLength(1111111, 10), 7);
  ASSERT_EQ(WU::intLength(11111111, 10), 8);
  ASSERT_EQ(WU::intLength(111111111, 10), 9);
  ASSERT_EQ(WU::intLength(1111111111, 10), 10);
  ASSERT_EQ(WU::intLength(11111111111, 10), 11);
}
