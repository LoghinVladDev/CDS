// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11+

#include <cds/functional/Invoke>
#include "UnitTest.hpp"

namespace {
using cds::functional::invoke;
} // namespace

namespace {
int f1() { return 1; }
int f2(int a, int const b) { return a + b; }
void f3(int& a, int const b) { a += b; }
int& f4(int& a) { return a; }
} // namespace

TEST(Invoke, global) {
  ASSERT_EQ(invoke(f1), 1);
  ASSERT_EQ(invoke(f2, 1, 2), 3);

  int x = 5;
  invoke(f3, x, 100);
  ASSERT_EQ(x, 105);

  int a = 10;
  auto& b = invoke(f4, a);
  b += 15;
  ASSERT_EQ(a, 25);

  ASSERT_EQ(invoke(&f1), 1);
}

TEST(Invoke, lambda) {
  ASSERT_EQ(invoke([](int const x){ return x; }, 1), 1);
  ASSERT_EQ(invoke([](int const x){ return x + 2; }, 1), 3);
  ASSERT_EQ(invoke([](int const x, int const y){ return x + y; }, 5, 10), 15);
}

TEST(Invoke, callable) {
  struct X {
    int operator()(int const x) const { return x; }
    int operator()(int const x, int const y) const { return x + y; }
  };

  ASSERT_EQ(invoke(X{}, 2), 2);
  ASSERT_EQ(invoke(X{}, 2, 3), 5);
}

namespace {
struct XGen {
  int operator()() const { return 0; }
  template <typename F, typename... T> int operator()(F&& f, T&&... args) const {
    return cds::forward<F>(f) + (*this)(cds::forward<T>(args)...);
  }
};
}

TEST(Invoke, genericCallable) {
  ASSERT_EQ(invoke(XGen{}), 0);
  ASSERT_EQ(invoke(XGen{}, 1, 2, 3), 6);
}

TEST(Invoke, memFn) {
  struct X {
    CDS_ATTR(nodiscard) auto f() const -> int { return z; }
    CDS_ATTR(nodiscard) auto g(int const x, int const y) const -> int { return x + y + z; }
    explicit X(int const x) : z(x) {}

    int z;
  };

  ASSERT_EQ(invoke(&X::f, X{5}), 5);
  ASSERT_EQ(invoke(&X::g, X{1}, 2, 3), 6);

  X obj {1};
  ASSERT_EQ(invoke(&X::f, obj), 1);
  ASSERT_EQ(invoke(&X::g, obj, 2, 3), 6);
  ASSERT_EQ(invoke(&X::f, &obj), 1);
  ASSERT_EQ(invoke(&X::g, &obj, 2, 3), 6);

  struct Y : X {
    using X::X;
  };
  ASSERT_EQ(invoke(&X::f, Y{5}), 5);
  ASSERT_EQ(invoke(&X::g, Y{1}, 2, 3), 6);
  ASSERT_EQ(invoke(&Y::f, Y{5}), 5);
  ASSERT_EQ(invoke(&Y::g, Y{1}, 2, 3), 6);
}

#ifdef DCR_SINCECPP11
constexpr int dval(int const x) { return x * 2; }

TEST(Invoke, constexpr11) {
  struct X { CDS_ATTR(nodiscard) constexpr int val(int const x) const { return x * z; } int const z; };

  static_assert(invoke(dval, 1) == 2, "Failed constexpr11");
  static_assert(invoke(&X::val, X{4}, 2) == 8, "Failed constexpr11");
}
#endif

#ifdef DCR_SINCECPP14
TEST(Invoke, genericLambda) {
  ASSERT_EQ(invoke([](auto x, auto y){ return x + y; }, 5, 10), 15);

  auto l = [](auto& x) -> auto& { return x; };
  int y = 10;
  auto& z = l(y);
  z += 15;
  ASSERT_EQ(y, 25);
}
#endif
