// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/shared/bindings/static/ContainsOfStaticBinding.hpp"
#include "UnitTest.hpp"
#include <vector>
#include <algorithm>

using namespace cds;
struct A_Members;

namespace cds {
namespace meta {
template <> struct IterableTraits<A_Members> {
  using Value = int;
};
}
}

struct A_Members : public impl::ContainsOfStaticBinding<A_Members> {
  bool contains(int a) const { return std::find(data.begin(), data.end(), a) != data.end(); }
  std::vector<int>::const_iterator begin() const { return data.begin(); }
  std::vector<int>::const_iterator end() const { return data.end(); }
  std::vector<int> data;
  A_Members(std::initializer_list<int> const& i) : data(i) {}
};

TEST(ContainsOfStaticBinding, ContainsAnyOf) {
  ASSERT_TRUE(A_Members({1, 2}).containsAnyOf(A_Members({1})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyOf(A_Members({2})));
  ASSERT_FALSE(A_Members({1, 2}).containsAnyOf(A_Members({3})));
  ASSERT_FALSE(A_Members({1, 2}).containsAnyOf(A_Members({3, 4})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyOf(A_Members({1, 2})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyOf(A_Members({1, 3})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyOf(A_Members({3, 1})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyOf(A_Members({1, 2, 3})));
}

TEST(ContainsOfStaticBinding, ContainsAnyNotOf) {
  ASSERT_TRUE(A_Members({1, 2}).containsAnyNotOf(A_Members({1})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyNotOf(A_Members({2})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyNotOf(A_Members({3})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyNotOf(A_Members({1, 3})));
  ASSERT_TRUE(A_Members({1, 2}).containsAnyNotOf(A_Members({2, 3})));
  ASSERT_FALSE(A_Members({1, 2}).containsAnyNotOf(A_Members({1, 2})));
  ASSERT_FALSE(A_Members({1, 2}).containsAnyNotOf(A_Members({1, 2, 3})));
  ASSERT_FALSE(A_Members({1, 2}).containsAnyNotOf(A_Members({4, 1, 2})));
}

TEST(ContainsOfStaticBinding, ContainsAllOf) {
  ASSERT_TRUE(A_Members({1, 2}).containsAllOf(A_Members({1})));
  ASSERT_TRUE(A_Members({1, 2}).containsAllOf(A_Members({2})));
  ASSERT_TRUE(A_Members({1, 2}).containsAllOf(A_Members({1, 2})));
  ASSERT_TRUE(A_Members({1, 2}).containsAllOf(A_Members({1, 1, 2})));
  ASSERT_FALSE(A_Members({1, 2}).containsAllOf(A_Members({1, 2, 3})));
  ASSERT_FALSE(A_Members({1, 2}).containsAllOf(A_Members({3, 1, 2})));
  ASSERT_FALSE(A_Members({1, 2}).containsAllOf(A_Members({3, 1})));
  ASSERT_FALSE(A_Members({1, 2}).containsAllOf(A_Members({3, 2})));
  ASSERT_FALSE(A_Members({1, 2}).containsAllOf(A_Members({1, 3})));
  ASSERT_FALSE(A_Members({1, 2}).containsAllOf(A_Members({3})));
}

TEST(ContainsOfStaticBinding, ContainsNoneOf) {
  ASSERT_TRUE(A_Members({1, 2}).containsNoneOf(A_Members({})));
  ASSERT_TRUE(A_Members({1, 2}).containsNoneOf(A_Members({3})));
  ASSERT_TRUE(A_Members({1, 2}).containsNoneOf(A_Members({3, 4})));
  ASSERT_FALSE(A_Members({1, 2}).containsNoneOf(A_Members({1, 3})));
  ASSERT_FALSE(A_Members({1, 2}).containsNoneOf(A_Members({3, 1})));
  ASSERT_FALSE(A_Members({1, 2}).containsNoneOf(A_Members({2, 3})));
  ASSERT_FALSE(A_Members({1, 2}).containsNoneOf(A_Members({1, 2})));
  ASSERT_FALSE(A_Members({1, 2}).containsNoneOf(A_Members({1, 2, 3})));
  ASSERT_FALSE(A_Members({1, 2}).containsNoneOf(A_Members({1})));
  ASSERT_FALSE(A_Members({1, 2}).containsNoneOf(A_Members({2})));
}
