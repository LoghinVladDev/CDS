// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../src/primitive/string/StringAbstract.hpp"
#include "UnitTest.hpp"

#include <cds/StringView>

#include <string>

namespace {
using cds::StringView;
using cds::impl::StringAbstract;
}

TEST(StringAbstract, Array) {
  char const buffer[] = "abcd";
  using A = StringAbstract<decltype(buffer)>;

  ASSERT_EQ(A::length(buffer), 4);
  ASSERT_EQ(A::data(buffer), buffer);
}

TEST(StringAbstract, Pointer) {
  char const* buffer = "abcd";
  using A = StringAbstract<decltype(buffer)>;

  ASSERT_EQ(A::length(buffer), 4);
  ASSERT_EQ(A::data(buffer), buffer);
}

TEST(StringAbstract, StringView) {
  StringView buffer = "abcd";
  using A = StringAbstract<decltype(buffer)>;

  ASSERT_EQ(A::length(buffer), 4);
  ASSERT_EQ(A::data(buffer), buffer.data());
}

TEST(StringAbstract, stdstring) {
  std::string buffer = "abcd";
  using A = StringAbstract<decltype(buffer)>;

  ASSERT_EQ(A::length(buffer), 4);
  ASSERT_EQ(A::data(buffer), buffer.c_str());
}

TEST(StringAbstract, null) {
  auto buffer = nullptr;
  using A = StringAbstract<decltype(buffer)>;

  ASSERT_EQ(A::length(buffer), 0);
  ASSERT_EQ(A::data(buffer), nullptr);
}

TEST(StringAbstract, transparent) {
  char const buf1[] = "abcd";
  char const* buf2 = "abcd";
  StringView buf3 = "abcd";
  std::string buf4 = "abcd";
  using A = StringAbstract<>;

  ASSERT_EQ(A::length(buf1), 4);
  ASSERT_EQ(A::length(buf2), 4);
  ASSERT_EQ(A::length(buf3), 4);
  ASSERT_EQ(A::length(buf4), 4);
  ASSERT_EQ(A::length(nullptr), 0);

  ASSERT_EQ(A::data(buf1), buf1);
  ASSERT_EQ(A::data(buf2), buf2);
  ASSERT_EQ(A::data(buf3), buf3.data());
  ASSERT_EQ(A::data(buf4), buf4.c_str());
  ASSERT_EQ(A::data(nullptr), nullptr);
}

#ifdef DCR_SINCECPP17
#include <string_view>

TEST(StringAbstract, stdstringview) {
  std::string_view buffer = "abcd";
  using A = StringAbstract<decltype(buffer)>;

  ASSERT_EQ(A::length(buffer), 4);
  ASSERT_EQ(A::data(buffer), buffer.data());
}
#endif
