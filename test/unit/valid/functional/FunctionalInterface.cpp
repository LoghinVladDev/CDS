// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11-2b

#include <cds/functional/FunctionalInterface>
#include "UnitTest.hpp"

using namespace cds::meta;
using namespace cds::functional;

TEST(FunctionalInterface, PredicateFunction) {
  static_assert(IsSame<Decay<bool(int, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(int, float)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(double, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(int&, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(int const&, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<int(int, int)>, PredicateFunction<int, int>>::value, "Faild Interface PredicateFunction");
}

TEST(FunctionalInterface, MapperFunction) {
  static_assert(IsSame<Decay<float(int, int)>, ProjectionFunction<float, int, int>>::value, "Failed Interface MapperFunction");
  static_assert(!IsSame<Decay<float(int&, int)>, ProjectionFunction<float, int, int>>::value, "Failed Interface MapperFunction");
}

namespace {
bool eq(int x, int y) { return x == y; }
template <typename T, typename V> bool teq(T x, V y) { return x == y; }
}

TEST(FunctionalInterface, memFn) {
  struct X { int f() { return 1; } };
  ASSERT_EQ(memFn(&X::f)(X()), 1);
}

TEST(FunctionalInterface, notFn) {
  auto leq = [](int x, int y) { return x == y; };
  struct X {int x = 1; bool comp(int y) { return x == y; }};

  ASSERT_TRUE(notFn(eq)(1, 2));
  ASSERT_TRUE(notFn(teq<int, int>)(1, 2));
  ASSERT_TRUE(notFn(teq<int, double>)(1, 2));
  ASSERT_TRUE(notFn(leq)(1, 2));
  ASSERT_TRUE(notFn(&X::comp)(X(), 2));

  ASSERT_FALSE(notFn(eq)(1, 1));
  ASSERT_FALSE(notFn(teq<int, int>)(1, 1));
  ASSERT_FALSE(notFn(teq<int, double>)(1, 1));
  ASSERT_FALSE(notFn(leq)(1, 1));
  ASSERT_FALSE(notFn(&X::comp)(X(), 1));
}

#ifdef DCR_SINCECPP11
TEST(FunctionalInterface, cpp11Constexpr) {
  struct X { constexpr int f() { return 1; } constexpr bool isEven(int x) { return x % 2 == 0; } };
  static_assert(memFn(&X::f)(X()) == 1, "Failed Compile Time memFn");

  static_assert(!memFn(&X::isEven)(X(), 1), "Failed Compile Time memFn");
  static_assert(memFn(&X::isEven)(X(), 2), "Failed Compile Time memFn");
  static_assert(!notFn(&X::isEven)(X(), 2), "Failed Compile Time memFn");
  static_assert(notFn(&X::isEven)(X(), 1), "Failed Compile Time memFn");
  static_assert(notFn(memFn(&X::isEven))(X(), 1), "Failed Compile Time memFn");
  static_assert(!notFn(memFn(&X::isEven))(X(), 2), "Failed Compile Time memFn");
}
#endif
