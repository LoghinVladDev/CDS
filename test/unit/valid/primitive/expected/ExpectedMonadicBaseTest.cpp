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

namespace {
Expected<int, int> thenDoubleInt(int const value) {
  return value * 2;
}

int doubleInt(int const value) {
  return value * 2;
}
} // namespace

TEST(ExpectedMonadicBaseTest, thenWithValue) {
  Expected<int, int> obj{5};
  auto const next = obj.then(thenDoubleInt);
  ASSERT_TRUE(next.hasValue());
  ASSERT_EQ(10, next.value());
}

TEST(ExpectedMonadicBaseTest, thenWithoutValue) {
  Expected<int, int> obj{Unexpect{}, 3};
  auto const next = obj.then(thenDoubleInt);
  ASSERT_TRUE(!next.hasValue());
  ASSERT_EQ(3, next.error());
}

TEST(ExpectedMonadicBaseTest, thenChangesType) {
  Expected<String, int> obj{"abcd"};
  auto const next = obj.then([](String const& str) -> Expected<int, float> {
    return str.length();
  });

  static_assert(IsSame<RemoveCVRef<decltype(next)>, Expected<int, float>>::value, "type change error");
  ASSERT_TRUE(next.hasValue());
  ASSERT_EQ(4, next.value());
}

TEST(ExpectedMonadicBaseTest, transformWithValue) {
  Expected<int, int> obj{5};
  auto const next = obj.transform(doubleInt);
  ASSERT_TRUE(next.hasValue());
  ASSERT_EQ(10, next.value());
}

TEST(ExpectedMonadicBaseTest, transformWithoutValue) {
  Expected<int, int> obj{Unexpect{}, 3};
  auto const next = obj.transform(doubleInt);
  ASSERT_TRUE(!next.hasValue());
  ASSERT_EQ(3, next.error());
}

TEST(ExpectedMonadicBaseTest, transformChangesType) {
  Expected<String, int> obj{"abcd"};
  auto const next = obj.transform([](String const& str) -> int {
    return str.length();
  });

  static_assert(IsSame<RemoveCVRef<decltype(next)>, Expected<int, int>>::value, "type change error");
  ASSERT_TRUE(next.hasValue());
  ASSERT_EQ(4, next.value());
}

TEST(ExpectedMonadicBaseTest, orElseValued) {
  Expected<String, int> obj{"abcd"};
  auto const next = obj.orElse([](int const value) -> Expected<String, int> {
    return String{value};
  });

  ASSERT_TRUE(next.hasValue());
  ASSERT_EQ("abcd", *next);
}

TEST(ExpectedMonadicBaseTest, orElseErr) {
  Expected<String, int> obj{Unexpect{}, 5};
  auto const next = obj.orElse([](int const value) -> Expected<String, int> {
    return String{value};
  });

  ASSERT_TRUE(next.hasValue());
  ASSERT_EQ("5", *next);
}

TEST(ExpectedMonadicBaseTest, transformErrorNoErr) {
  Expected<String, String> obj{"abcd"};
  auto const next = obj.transformError([](String const& err) -> int { return err.length(); });

  ASSERT_TRUE(next.hasValue());
  ASSERT_EQ("abcd", *next);
}

TEST(ExpectedMonadicBaseTest, transformErrorErr) {
  Expected<String, String> obj{Unexpect{}, "abcd"};
  auto const next = obj.transformError([](String const& err) -> int { return err.length(); });

  ASSERT_FALSE(next.hasValue());
  ASSERT_EQ(4, next.error());
}

TEST(ExpectedMonadicBaseTest, thenToVoid) {
  Expected<String, int> obj{"abcd"};
  Expected<String, int> err{Unexpect{}, 5};

  auto const fn = [](String const& val) -> Expected<void, int> {
    ignore = val;
    return {};
  };

  auto const nextObj = obj.then(fn);
  auto const nextErr = err.then(fn);

  ASSERT_TRUE(nextObj.hasValue());
  ASSERT_FALSE(nextErr.hasValue());
  ASSERT_EQ(5, nextErr.error());
}

TEST(ExpectedMonadicBaseTest, transformToVoid) {
  Expected<String, int> obj{"abcd"};
  Expected<String, int> err{Unexpect{}, 5};

  auto const fn = [](String const& val) -> void {
    ignore = val;
  };

  auto const nextObj = obj.transform(fn);
  auto const nextErr = err.transform(fn);

  ASSERT_TRUE(nextObj.hasValue());
  ASSERT_FALSE(nextErr.hasValue());
  ASSERT_EQ(5, nextErr.error());
}

TEST(ExpectedMonadicBase, transformToAndFromVoid) {
  Expected<String, int> obj{"abcd"};

  auto const next1 = obj.transform([](String const& str) {
    ignore = str;
  });
  auto const next2 = next1.transform([]() {
    // nothing
  });
  auto const next3 = next2.transform([]() -> String {
    return "bcef";
  });

  ASSERT_TRUE(next3.hasValue());
  ASSERT_EQ("bcef", *next3);
}

TEST(ExpectedMonadicBase, tupleExpectedAppliedThen) {
  Expected<Tuple<int, String, bool>, int> obj{5, "abcd", false};
  auto const next = obj.appliedThen([](int v0, String& v1, bool v2) -> Expected<int, int> {
    return v0 + v1.length() + static_cast<int>(v2);
  });
  ASSERT_EQ(9, next);
}

TEST(ExpectedMonadicBase, tupleExpectedAppliedTransform) {
  Expected<Tuple<int, String>, int> obj{5, "abcd"};

  auto const next = obj.appliedTransform([](int v0, String const& v1) {
    return tupleOf(v1, v0);
  });

  ASSERT_EQ(tupleOf("abcd", 5), next);
}
