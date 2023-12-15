// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "cds/StringView"
#include "UnitTest.hpp"

using namespace cds::impl;
using U = StringUtils<char, cds::meta::StringTraits<char>>;

TEST(StringUtils, Length) {
  ASSERT_EQ(U::length(nullptr), 0u);
  ASSERT_EQ(U::length("test"), 4u);
  char const* ptr = "test";
  ASSERT_EQ(U::length(ptr), 4u);
}

TEST(StringUtils, Compare) {
  char const buf1[] = "a";
  char const buf2[] = "a";
  ASSERT_EQ(U::compare(nullptr, 0u, nullptr, 0u), U::Ordering::Equal);
  ASSERT_EQ(U::compare(buf1, 0u, nullptr, 0u), U::Ordering::Equal);
  ASSERT_EQ(U::compare(buf1, 0u, buf2, 0u), U::Ordering::Equal);

  ASSERT_EQ(U::compare(nullptr, 0u, buf1, U::length(buf1)), U::Ordering::Less);
  ASSERT_EQ(U::compare(buf1, U::length(buf1), nullptr, 0u), U::Ordering::Greater);

  char const buf3[] = "aa";
  char const buf4[] = "ab";
  ASSERT_EQ(U::compare(buf3, U::length(buf3), buf4, U::length(buf4)), U::Ordering::Less);
  ASSERT_EQ(U::compare(buf4, U::length(buf4), buf3, U::length(buf3)), U::Ordering::Greater);

  char const buf5[] = "aab";
  ASSERT_EQ(U::compare(buf3, U::length(buf3), buf5, U::length(buf5)), U::Ordering::Less);
  ASSERT_EQ(U::compare(buf5, U::length(buf5), buf3, U::length(buf3)), U::Ordering::Greater);
  ASSERT_EQ(U::compare(buf3, U::length(buf3), buf3, U::length(buf3)), U::Ordering::Equal);
}
