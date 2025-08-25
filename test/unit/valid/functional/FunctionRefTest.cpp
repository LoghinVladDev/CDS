//
// Created by loghin on 8/24/25.
//

#include <cds/functional/FunctionRef>
#include <cds/String>

#include "UnitTest.hpp"

namespace {
using cds::functional::FunctionRef;

int f(int a) {
  return a * 2;
}
} // namespace

TEST(FunctionRefTest, ofFreestanding) {
  FunctionRef<int(int)> f0 = f;
  FunctionRef<int(int)> f1 = &f;

  ASSERT_EQ(4, f0(2));
  ASSERT_EQ(6, f1(3));
}

TEST(FunctionRefTest, ofFunctor) {
  auto aVariable = 3;
  auto fLambda = [&aVariable](int a) { return a * aVariable; };
  auto const fConstLambda = [&aVariable](int a) { return a * aVariable; };

  FunctionRef<int(int)> f0 = fLambda;
  ASSERT_EQ(6, f0(2));
  aVariable = 4;
  ASSERT_EQ(8, f0(2));

  aVariable = 3;
  FunctionRef<int(int) const> f1 = fConstLambda;
  ASSERT_EQ(6, f1(2));
  aVariable = 4;
  ASSERT_EQ(8, f1(2));

  aVariable = 3;
  FunctionRef<int(int) const> f2 = fLambda;
  ASSERT_EQ(6, f2(2));
  aVariable = 4;
  ASSERT_EQ(8, f2(2));
}

TEST(FunctionRefTest, ofFreestandingRef) {
  auto& x = f;
  auto const& y = f;
  FunctionRef<int(int)> f0 = x;
  FunctionRef<int(int)> f1 = y;

  ASSERT_EQ(4, f0(2));
  ASSERT_EQ(6, f1(3));
}

TEST(FunctionRefTest, values) {
  auto fn = [](cds::String& str, cds::String const& r, cds::String&& t) {
    str += r;
    str += std::move(t);
  };

  cds::String orig = "abcd";
  cds::String perm = "x";
  FunctionRef<void(cds::String&, cds::String const&, cds::String&&)> adder = fn;

  adder(orig, perm, "xyzt");
  adder(orig, "y", "aaaa");
  adder(orig, "z", std::move(perm));

  ASSERT_EQ(orig, "abcdxxyztyaaaazx");
}

TEST(FunctionRefTest, lifetime) {
  auto checker = [](int x, FunctionRef<bool(int)> check) {
    return check(x);
  };

  ASSERT_TRUE(checker(5, [](int x){ return x % 2 == 1; }));
}

#ifdef DCR_SINCECPP17
TEST(FunctionRefTest, ctad) {
  auto x = 4;
  auto g = [x](int y) { return x * y; };
  auto const h = [x](int z) { return x + z; };

  FunctionRef f0 = f;
  FunctionRef f1 = &f;
  FunctionRef f2 = g;
  FunctionRef f3 = h;

  ASSERT_EQ(6, f0(3));
  ASSERT_EQ(8, f0(4));
  ASSERT_EQ(12, f2(3));
  ASSERT_EQ(16, f3(12));
}
#endif
