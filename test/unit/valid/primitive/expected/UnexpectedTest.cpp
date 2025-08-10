// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/Expected>
#include <cds/Format>

namespace {
using cds::meta::Default;

using cds::Expected;
using cds::ExpectedValueException;
using cds::Unexpected;
using cds::Unexpect;
using cds::unexpectedOf;

static_assert(!cds::meta::IsDefaultConstructible<Unexpected<int>>::value,
    "Unexpected should not be default constructible");

using cds::mv;
using cds::xch;

struct X {
  X() : x(2) {}
  X(int value) : x(value) {}
  X(X const& v) : x(v.x) {}
  X(X&& v) : x(xch(v.x, 0)) {}
  X(std::initializer_list<int> const& vals) noexcept : x(0) {
    for (auto const& val: vals) {
      x += val;
    }
  }
  X(int a, int b) : x(a + b) {}
  int x;
};

} // namespace

TEST(UnexpectedTest, constructByValue) {
  auto u = Unexpected<int>{5};
  ASSERT_EQ(5, u.error());
}

TEST(UnexpectedTest, constructByExplicitDefault) {
  auto u = Unexpected<X>{Default{}};
  ASSERT_EQ(2, u.error().x);
}

TEST(UnexpectedTest, constructByCopy) {
  X obj{5};
  auto u = Unexpected<X>{obj};
  ASSERT_EQ(5, u.error().x);
  ASSERT_EQ(5, obj.x);
}

TEST(UnexpectedTest, constructByMove) {
  X obj{5};
  auto u = Unexpected<X>{mv(obj)};
  ASSERT_EQ(5, u.error().x);
  ASSERT_EQ(0, obj.x);
}

TEST(UnexpectedTest, constructByIList) {
  auto u = Unexpected<X>{{1, 2, 3, 4}};
  ASSERT_EQ(10, u.error().x);
}

TEST(UnexpectedTest, constructByFunction) {
  auto u = unexpectedOf(5);
  ASSERT_EQ(5, u.error());
}

TEST(UnexpectedTest, constructByFunction2) {
  auto u = unexpectedOf<int>(5);
  ASSERT_EQ(5, u.error());
}

TEST(UnexpectedTest, constructByFunctionEmplace) {
  auto u = unexpectedOf<X>(2, 4);
  ASSERT_EQ(6, u.error().x);
}

TEST(UnexpectedTest, cmp) {
  auto u1 = unexpectedOf(5);
  auto u2 = unexpectedOf(5);
  auto u3 = unexpectedOf(6);
  auto u4 = unexpectedOf(7);

  ASSERT_TRUE(u1 == u1);
  ASSERT_TRUE(u1 == u2);
  ASSERT_FALSE(u1 == u3);
  ASSERT_FALSE(u1 == u4);

  ASSERT_TRUE(u2 == u1);
  ASSERT_TRUE(u2 == u2);
  ASSERT_FALSE(u2 == u3);
  ASSERT_FALSE(u2 == u4);

  ASSERT_FALSE(u3 == u1);
  ASSERT_FALSE(u3 == u2);
  ASSERT_TRUE(u3 == u3);
  ASSERT_FALSE(u3 == u4);

  ASSERT_FALSE(u4 == u1);
  ASSERT_FALSE(u4 == u2);
  ASSERT_FALSE(u4 == u3);
  ASSERT_TRUE(u4 == u4);

  ASSERT_FALSE(u1 != u1);
  ASSERT_FALSE(u1 != u2);
  ASSERT_TRUE(u1 != u3);
  ASSERT_TRUE(u1 != u4);

  ASSERT_FALSE(u2 != u1);
  ASSERT_FALSE(u2 != u2);
  ASSERT_TRUE(u2 != u3);
  ASSERT_TRUE(u2 != u4);

  ASSERT_TRUE(u3 != u1);
  ASSERT_TRUE(u3 != u2);
  ASSERT_FALSE(u3 != u3);
  ASSERT_TRUE(u3 != u4);

  ASSERT_TRUE(u4 != u1);
  ASSERT_TRUE(u4 != u2);
  ASSERT_TRUE(u4 != u3);
  ASSERT_FALSE(u4 != u4);
}

#if DCR_SINCECPP17
TEST(UnexpectedTest, ctad) {
  auto u = Unexpected{5};
  ASSERT_EQ(5, u.error());
}
#endif
