// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/StringView>
#include "UnitTest.hpp"

using namespace cds::impl;
using U = StringUtils<char, StringTraits<char>>;
using A = StringAbstract<>;

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
