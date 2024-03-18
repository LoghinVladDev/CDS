// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../../src/algorithm/GenericLoop.hpp"
#include "UnitTest.hpp"
#include "../Shared.hpp"

#include <cds/functional/FunctionalInterface>

#include <vector>

namespace {
using cds::impl::forEach;
using cds::impl::some;
using cds::impl::atLeast;
using cds::impl::atMost;
using cds::impl::moreThan;
using cds::impl::lessThan;
using cds::impl::count;
using cds::impl::any;
using cds::impl::all;
using cds::impl::none;
using testing::citeq;
using cds::functional::memFn;
using cds::functional::notFn;
}

namespace {
struct X {
  int x;
  void plusX() { x *= 2; }
  bool even() const { return x % 2 == 0; }
};

auto operator==(X const& lhs, int rhs) -> bool { return lhs.x == rhs; }
auto operator==(int lhs, X const& rhs) -> bool { return lhs == rhs.x; }
auto operator!=(X const& lhs, int rhs) -> bool { return lhs.x != rhs; }
auto operator!=(int lhs, X const& rhs) -> bool { return lhs != rhs.x; }
auto even(X const& x) -> bool { return x.x % 2 == 0; }
} // namespace

TEST(GenericLoop, forEach) {
  int v[3] = {1, 2, 3};
  forEach(cds::begin(v), cds::end(v), [](int& e) { e *= 2; });
  ASSERT_TRUE(citeq(v, std::vector<int>{2, 4, 6}));
}

TEST(GenericLoop, forEachMember) {
  X v[3] = {{1}, {2}, {3}};
  forEach(cds::begin(v), cds::end(v), &X::plusX);
  ASSERT_TRUE(citeq(v, std::vector<int>{2, 4, 6}));
}

TEST(GenericLoop, forEachPtr) {
  X a {1};
  X b {2};
  X c {3};
  X* v[3] = {&a, &b, &c};
  forEach(cds::begin(v), cds::end(v), &X::plusX);

  ASSERT_EQ(a, 2);
  ASSERT_EQ(b, 4);
  ASSERT_EQ(c, 6);
}

TEST(GenericLoop, some) {
  X v[] = {{1}, {2}, {3}, {4}, {5}};
  ASSERT_TRUE(some(cds::begin(v), cds::end(v), 2, even));
  ASSERT_TRUE(some(cds::begin(v), cds::end(v), 2, &X::even));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 3, even));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 3, &X::even));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 1, even));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 1, &X::even));

  ASSERT_TRUE(some(cds::begin(v), cds::end(v), 3, notFn(even)));
  ASSERT_TRUE(some(cds::begin(v), cds::end(v), 3, notFn(&X::even)));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 4, notFn(even)));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 4, notFn(&X::even)));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 2, notFn(even)));
  ASSERT_FALSE(some(cds::begin(v), cds::end(v), 2, notFn(&X::even)));
}

TEST(GenericLoop, atLeast) {
  X v[] = {{1}, {2}, {3}, {4}, {5}};
  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 2, even));
  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 2, &X::even));
  ASSERT_FALSE(atLeast(cds::begin(v), cds::end(v), 3, even));
  ASSERT_FALSE(atLeast(cds::begin(v), cds::end(v), 3, &X::even));
  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 1, even));
  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 1, &X::even));

  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 3, notFn(even)));
  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 3, notFn(&X::even)));
  ASSERT_FALSE(atLeast(cds::begin(v), cds::end(v), 4, notFn(even)));
  ASSERT_FALSE(atLeast(cds::begin(v), cds::end(v), 4, notFn(&X::even)));
  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 2, notFn(even)));
  ASSERT_TRUE(atLeast(cds::begin(v), cds::end(v), 2, notFn(&X::even)));
}

TEST(GenericLoop, atMost) {
  X v[] = {{1}, {2}, {3}, {4}, {5}};
  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 2, even));
  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 2, &X::even));
  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 3, even));
  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 3, &X::even));
  ASSERT_FALSE(atMost(cds::begin(v), cds::end(v), 1, even));
  ASSERT_FALSE(atMost(cds::begin(v), cds::end(v), 1, &X::even));

  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 3, notFn(even)));
  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 3, notFn(&X::even)));
  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 4, notFn(even)));
  ASSERT_TRUE(atMost(cds::begin(v), cds::end(v), 4, notFn(&X::even)));
  ASSERT_FALSE(atMost(cds::begin(v), cds::end(v), 2, notFn(even)));
  ASSERT_FALSE(atMost(cds::begin(v), cds::end(v), 2, notFn(&X::even)));
}

TEST(GenericLoop, moreThan) {
  X v[] = {{1}, {2}, {3}, {4}, {5}};
  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 2, even));
  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 2, &X::even));
  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 3, even));
  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 3, &X::even));
  ASSERT_TRUE(moreThan(cds::begin(v), cds::end(v), 1, even));
  ASSERT_TRUE(moreThan(cds::begin(v), cds::end(v), 1, &X::even));

  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 3, notFn(even)));
  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 3, notFn(&X::even)));
  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 4, notFn(even)));
  ASSERT_FALSE(moreThan(cds::begin(v), cds::end(v), 4, notFn(&X::even)));
  ASSERT_TRUE(moreThan(cds::begin(v), cds::end(v), 2, notFn(even)));
  ASSERT_TRUE(moreThan(cds::begin(v), cds::end(v), 2, notFn(&X::even)));
}

TEST(GenericLoop, lessThan) {
  X v[] = {{1}, {2}, {3}, {4}, {5}};
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 2, even));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 2, &X::even));
  ASSERT_TRUE(lessThan(cds::begin(v), cds::end(v), 3, even));
  ASSERT_TRUE(lessThan(cds::begin(v), cds::end(v), 3, &X::even));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 1, even));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 1, &X::even));

  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 3, notFn(even)));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 3, notFn(&X::even)));
  ASSERT_TRUE(lessThan(cds::begin(v), cds::end(v), 4, notFn(even)));
  ASSERT_TRUE(lessThan(cds::begin(v), cds::end(v), 4, notFn(&X::even)));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 2, notFn(even)));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 2, notFn(&X::even)));

  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 0, even));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 0, &X::even));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 0, notFn(even)));
  ASSERT_FALSE(lessThan(cds::begin(v), cds::end(v), 0, notFn(&X::even)));
}

TEST(GenericLoop, count) {
  X v[] = {{1}, {2}, {3}, {4}, {5}};
  ASSERT_EQ(count(cds::begin(v), cds::end(v), even), 2);
  ASSERT_EQ(count(cds::begin(v), cds::end(v), &X::even), 2);
  ASSERT_EQ(count(cds::begin(v), cds::end(v), notFn(even)), 3);
  ASSERT_EQ(count(cds::begin(v), cds::end(v), notFn(&X::even)), 3);
}

TEST(GenericLoop, any) {
  X m[] = {{1}, {2}};
  X e[] = {{2}, {4}};
  X n[] = {{1}, {3}};

  ASSERT_TRUE(any(cds::begin(m), cds::end(m), even));
  ASSERT_TRUE(any(cds::begin(m), cds::end(m), notFn(even)));
  ASSERT_TRUE(any(cds::begin(m), cds::end(m), &X::even));
  ASSERT_TRUE(any(cds::begin(m), cds::end(m), notFn(&X::even)));

  ASSERT_TRUE(any(cds::begin(e), cds::end(e), even));
  ASSERT_FALSE(any(cds::begin(e), cds::end(e), notFn(even)));
  ASSERT_TRUE(any(cds::begin(e), cds::end(e), &X::even));
  ASSERT_FALSE(any(cds::begin(e), cds::end(e), notFn(&X::even)));

  ASSERT_FALSE(any(cds::begin(n), cds::end(n), even));
  ASSERT_TRUE(any(cds::begin(n), cds::end(n), notFn(even)));
  ASSERT_FALSE(any(cds::begin(n), cds::end(n), &X::even));
  ASSERT_TRUE(any(cds::begin(n), cds::end(n), notFn(&X::even)));
}

TEST(GenericLoop, all) {
  X m[] = {{1}, {2}};
  X e[] = {{2}, {4}};
  X n[] = {{1}, {3}};

  ASSERT_FALSE(all(cds::begin(m), cds::end(m), even));
  ASSERT_FALSE(all(cds::begin(m), cds::end(m), notFn(even)));
  ASSERT_FALSE(all(cds::begin(m), cds::end(m), &X::even));
  ASSERT_FALSE(all(cds::begin(m), cds::end(m), notFn(&X::even)));

  ASSERT_TRUE(all(cds::begin(e), cds::end(e), even));
  ASSERT_FALSE(all(cds::begin(e), cds::end(e), notFn(even)));
  ASSERT_TRUE(all(cds::begin(e), cds::end(e), &X::even));
  ASSERT_FALSE(all(cds::begin(e), cds::end(e), notFn(&X::even)));

  ASSERT_FALSE(all(cds::begin(n), cds::end(n), even));
  ASSERT_TRUE(all(cds::begin(n), cds::end(n), notFn(even)));
  ASSERT_FALSE(all(cds::begin(n), cds::end(n), &X::even));
  ASSERT_TRUE(all(cds::begin(n), cds::end(n), notFn(&X::even)));
}

TEST(GenericLoop, none) {
  X m[] = {{1}, {2}};
  X e[] = {{2}, {4}};
  X n[] = {{1}, {3}};

  ASSERT_FALSE(none(cds::begin(m), cds::end(m), even));
  ASSERT_FALSE(none(cds::begin(m), cds::end(m), notFn(even)));
  ASSERT_FALSE(none(cds::begin(m), cds::end(m), &X::even));
  ASSERT_FALSE(none(cds::begin(m), cds::end(m), notFn(&X::even)));

  ASSERT_FALSE(none(cds::begin(e), cds::end(e), even));
  ASSERT_TRUE(none(cds::begin(e), cds::end(e), notFn(even)));
  ASSERT_FALSE(none(cds::begin(e), cds::end(e), &X::even));
  ASSERT_TRUE(none(cds::begin(e), cds::end(e), notFn(&X::even)));

  ASSERT_TRUE(none(cds::begin(n), cds::end(n), even));
  ASSERT_FALSE(none(cds::begin(n), cds::end(n), notFn(even)));
  ASSERT_TRUE(none(cds::begin(n), cds::end(n), &X::even));
  ASSERT_FALSE(none(cds::begin(n), cds::end(n), notFn(&X::even)));
}
