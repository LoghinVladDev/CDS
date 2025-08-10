// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Expected>
#include <cds/Format>
#include <cds/String>

#include <cds/memory/Allocator>

namespace {
using namespace cds;
using namespace cds::meta;
using namespace cds::impl;
} // namespace

TEST(ExpectedObservableBaseTest, hasValue) {
  Expected<int, int> wVal{0};
  Expected<int, int> woVal{Unexpect{}, 0};
  Expected<void, int> voidVal{};
  Expected<void, int> voidWoVal{Unexpect{}, 0};

  ASSERT_TRUE(wVal.hasValue());
  ASSERT_FALSE(woVal.hasValue());

  ASSERT_TRUE(voidVal.hasValue());
  ASSERT_FALSE(voidWoVal.hasValue());

  ASSERT_TRUE(static_cast<bool>(wVal));
  ASSERT_FALSE(static_cast<bool>(woVal));

  ASSERT_TRUE(static_cast<bool>(voidVal));
  ASSERT_FALSE(static_cast<bool>(voidWoVal));
}

TEST(ExpectedObservableBaseTest, observerOps) {
  Expected<String, int> const val = "abcd";

  ASSERT_EQ(*val, "abcd");
  ASSERT_EQ(val->length(), 4);
}

TEST(ExpectedObservableBaseTest, observerExtractVal) {
  Expected<String, int> val = "abcd";

  auto&& extracted = *mv(val);
  ASSERT_EQ(extracted, "abcd");
}

TEST(ExpectedObservableBaseTest, observerExtractAddr) {
  Expected<String, int> val = "abcd";

  auto&& extracted = mv(val)->length();
  ASSERT_EQ(4, extracted);
}

TEST(ExpectedObservableBaseTest, getValue) {
  Expected<String, int> val = "abcd";
  Expected<String, int> valErr{Unexpect{}, 5};

  ASSERT_EQ("abcd", val.value());

  try {
    ignore = valErr.value();
    ASSERT_FALSE(true);
  } catch (ExpectedValueException<int> const& e) {
    ASSERT_EQ(5, e.error());
  }
}

TEST(ExpectedObservableBaseTest, getError) {
  Expected<String, int> valErr{Unexpect{}, 5};
  Expected<void, int> voidErr{Unexpect{}, 10};

  ASSERT_EQ(5, valErr.error());
  ASSERT_EQ(10, voidErr.error());
}

TEST(ExpectedObservableBaseTest, valueOr) {
  Expected<String, int> val = "abcd";
  Expected<String, int> valErr{Unexpect{}, 5};

  ASSERT_EQ("abcd", val.valueOr("bcde"));
  ASSERT_EQ("bcde", valErr.valueOr("bcde"));
}

TEST(ExpectedObservableBaseTest, errorOr) {
  Expected<String, int> val = "abcd";
  Expected<String, int> valErr{Unexpect{}, 5};
  Expected<void, int> voidVal{};
  Expected<void, int> voidValErr{Unexpect{}, 10};

  ASSERT_EQ(3, val.errorOr(3));
  ASSERT_EQ(5, valErr.errorOr(3));
  ASSERT_EQ(3, voidVal.errorOr(3));
  ASSERT_EQ(10, voidValErr.errorOr(3));
}
