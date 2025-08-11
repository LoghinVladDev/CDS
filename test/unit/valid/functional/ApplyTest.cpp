// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11+

#include <cds/functional/Apply>
#include <cds/Tuple>
#include <cds/String>
#include <cds/collection/Vector>

#include "UnitTest.hpp"

namespace {
using cds::String;
using cds::Tuple;
using cds::Vector;

namespace fn = cds::functional;
} // namespace

TEST(ApplyTest, tuple) {
  Tuple<int, String, Vector<int>> t {5, "abcd", std::initializer_list<int>{1, 2, 3}};
  auto const fn = [](int v1, String const& v2, Vector<int>& v3) {
    return v1 + v2.length() + v3.count([](int val) { return val % 2 == 1; });
  };
  auto res = fn::apply(fn, t);
  ASSERT_EQ(11, res);
}

TEST(ApplyTest, tupleMember) {
  Tuple<int, String, Vector<int>> t {5, "abcd", std::initializer_list<int>{1, 2, 3}};
  auto const fn = [](int v1, String const& v2, Vector<int>& v3) {
    return v1 + v2.length() + v3.count([](int val) { return val % 2 == 1; });
  };
  auto res = t.apply(fn);
  ASSERT_EQ(11, res);
}
