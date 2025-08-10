// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/Expected>
#include <cds/Format>
#include <cds/String>
#include <cds/collection/Vector>

#include "UnitTest.hpp"

namespace {
using namespace cds;
} // namespace

TEST(ExpectedTest, constructFromValue) {
  Expected<String, int> value = "abcd";

  ASSERT_TRUE(value.hasValue());
  ASSERT_EQ("abcd", value);
}

TEST(ExpectedTest, constructFromUnexpected) {
  Expected<String, int> value = Unexpected<int>{5};

  ASSERT_FALSE(value.hasValue());
  ASSERT_EQ(5, value.error());
}

TEST(ExpectedTest, constructFromUtility) {
  auto value = unexpectedOf(5);
  ASSERT_EQ(5, value.error());

  auto castedValue = unexpectedOf<U8>(5);
  ASSERT_EQ(5u, castedValue.error());
}

TEST(ExpectedTest, formatUnexpected) {
  auto value = unexpectedOf(5);
  ASSERT_EQ("unexpected<5>", cds::format("{}", value));
}

TEST(ExpectedTest, formatExpectedError) {
  Expected<String, int> value = unexpectedOf(5);
  ASSERT_EQ("unexpected<5>", cds::format("{}", value));
}

TEST(ExpectedTest, formatExpectedValue) {
  Expected<String, int> value = "abcd";
  ASSERT_EQ("abcd", cds::format("{}", value));
}

TEST(ExpectedTest, tieExpectedAllOk) {
  Expected<String, int> first = "abcd";
  Expected<int, int> second = 20;
  Expected<Vector<int>, int> third {{1, 2, 3}};

  auto result = tie(first, second, third).transform([](Tuple<String&, int&, Vector<int>&> const& values) {
    return get<0>(values).length() + get<1>(values) + get<2>(values).size();
  });

  ASSERT_TRUE(result.hasValue());
  ASSERT_EQ(27, result);
}

TEST(ExpectedTest, tieExpectedErrors) {
  Expected<String, int> first = "abcd";
  Expected<int, int> second = 20;
  Expected<Vector<int>, int> third {{1, 2, 3}};
  Expected<String, int> firstErr = Unexpected<int>{4};
  Expected<int, int> secondErr = Unexpected<int>{5};
  Expected<Vector<int>, int> thirdErr = Unexpected<int>{6};

  auto const fn = [](Tuple<String&, int&, Vector<int>&> const& values) {
    return get<0>(values).length() + get<1>(values) + get<2>(values).size();
  };

  auto result0 = tie(firstErr, second, third).transform(fn);
  ASSERT_FALSE(result0.hasValue());
  ASSERT_EQ(4, result0.error());

  auto result1 = tie(first, secondErr, third).transform(fn);
  ASSERT_FALSE(result1.hasValue());
  ASSERT_EQ(5, result1.error());

  auto result2 = tie(first, second, thirdErr).transform(fn);
  ASSERT_FALSE(result2.hasValue());
  ASSERT_EQ(6, result2.error());

  auto result3 = tie(firstErr, second, thirdErr).transform(fn);
  ASSERT_FALSE(result3.hasValue());
  ASSERT_EQ(4, result3.error());
}

#ifdef DCR_SINCECPP20
static_assert("unexpected<5>" == cds::format("{}", unexpectedOf(5)));
static_assert("unexpected<5>" == cds::format("{}", Expected<String, int>{Unexpect{}, 5}));
static_assert("abcd" == cds::format("{}", Expected<String, int>{"abcd"}));
#endif
