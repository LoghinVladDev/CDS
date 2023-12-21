// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/bindings/static/ContainsOfStaticBinding.hpp"
#include "UnitTest.hpp"
#include <vector>
#include <algorithm>

using namespace cds;
using namespace cds::impl::sel;
struct A_ContainsMember;
struct A_ContainsSelectedMember;
struct A_ContainsContainsSelectedMember;

namespace cds {
namespace meta {
template <> struct IterableTraits<A_ContainsMember> { using Value = int; };
template <> struct IterableTraits<A_ContainsSelectedMember> { using Value = int; };
template <> struct IterableTraits<A_ContainsContainsSelectedMember> { using Value = int; };
}
}

struct A_ContainsMember : public impl::ContainsOfStaticBinding<A_ContainsMember, With<Value>> {
  bool contains(int a) const { return std::find(data.begin(), data.end(), a) != data.end(); }
  std::vector<int>::const_iterator begin() const { return data.begin(); }
  std::vector<int>::const_iterator end() const { return data.end(); }
  std::vector<int> data;
  explicit A_ContainsMember(std::initializer_list<int> const& i) : data(i) {}
};

struct A_ContainsSelectedMember : public impl::ContainsOfStaticBinding<A_ContainsSelectedMember, With<Selector>> {
  template <typename S> bool contains(int a, S&& s) const {
    for (int v : data) {
      if (a == cds::forward<S>(s)(v)) {
        return true;
      }
    }
    return false;
  }
  std::vector<int>::const_iterator begin() const { return data.begin(); }
  std::vector<int>::const_iterator end() const { return data.end(); }
  std::vector<int> data;
  explicit A_ContainsSelectedMember(std::initializer_list<int> const& i) : data(i) {}
};

struct A_ContainsContainsSelectedMember :
    public impl::ContainsOfStaticBinding<A_ContainsContainsSelectedMember, With<Value, Selector>> {
  bool contains(int a) const { return std::find(data.begin(), data.end(), a) != data.end(); }
  template <typename S> bool contains(int a, S&& s) const {
    for (int v : data) {
      if (a == cds::forward<S>(s)(v)) {
        return true;
      }
    }
    return false;
  }

  std::vector<int>::const_iterator begin() const { return data.begin(); }
  std::vector<int>::const_iterator end() const { return data.end(); }
  std::vector<int> data;
  explicit A_ContainsContainsSelectedMember(std::initializer_list<int> const& i) : data(i) {}
};

TEST(ContainsByValueOfStaticBinding, ContainsAnyOf) {
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({3, 4})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1, 2})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1, 3})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({3, 1})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1, 2, 3})));
}

TEST(ContainsByValueOfStaticBinding, ContainsAnyNotOf) {
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({2})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({3})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1, 3})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({2, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1, 2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({4, 1, 2})));
}

TEST(ContainsByValueOfStaticBinding, ContainsAllOf) {
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({1})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({2})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({1, 2})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({1, 1, 2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({3, 1, 2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({3, 1})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({3, 2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({1, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAllOf(A_ContainsMember({3})));
}

TEST(ContainsByValueOfStaticBinding, ContainsNoneOf) {
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({3})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({3, 4})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({1, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({3, 1})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({2, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({1, 2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({1})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsNoneOf(A_ContainsMember({2})));
}

namespace {int doubled(int x) { return x * 2; }}
TEST(ContainsSelectedStaticBinding, ContainsAnyOf) {
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({2}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({4}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({1}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({3}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({6}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({3, 5}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({2, 4}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({2, 6}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({3, 2}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsSelectedMember({2, 4, 3}), doubled));
}

TEST(ContainsSelectedStaticBinding, ContainsAnyNotOf) {
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({2}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({4}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({6}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({4, 3}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({4, 3}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({2, 4}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({2, 4, 6}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsSelectedMember({6, 2, 4}), doubled));
}

TEST(ContainsSelectedStaticBinding, ContainsAllOf) {
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({2}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({4}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({4, 2}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({4, 4, 2}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({2, 4, 6}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({6, 2, 4}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({6, 2}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({6, 4}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({2, 6}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsAllOf(A_ContainsSelectedMember({6}), doubled));
}

TEST(ContainsSelectedStaticBinding, ContainsNoneOf) {
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({6}), doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({6, 8}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({2, 6}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({6, 2}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({4, 6}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({2, 4}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({2, 4, 6}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({2}), doubled));
  ASSERT_FALSE(A_ContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsSelectedMember({4}), doubled));
}

TEST(ContainsByValueOfStaticBinding, BothContainsAnyOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3, 4})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1, 2})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1, 3})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3, 1})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1, 2, 3})));
}

TEST(ContainsByValueOfStaticBinding, BothContainsAnyNotOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({2})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({3})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1, 3})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({2, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1, 2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({4, 1, 2})));
}

TEST(ContainsByValueOfStaticBinding, BothContainsAllOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({1})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({2})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({1, 2})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({1, 1, 2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({3, 1, 2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({3, 1})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({3, 2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({1, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({3})));
}

TEST(ContainsByValueOfStaticBinding, BothContainsNoneOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({3})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({3, 4})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({1, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({3, 1})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({2, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({1, 2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({1})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({2})));
}

TEST(ContainsSelectedStaticBinding, BothContainsAnyOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({2}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({4}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({6}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3, 5}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({2, 4}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({2, 6}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3, 2}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({2, 4, 3}), doubled));
}

TEST(ContainsSelectedStaticBinding, BothContainsAnyNotOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({2}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({4}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({6}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({4, 3}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({4, 3}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({2, 4}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({2, 4, 6}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({6, 2, 4}), doubled));
}

TEST(ContainsSelectedStaticBinding, BothContainsAllOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({2}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({4}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({4, 2}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({4, 4, 2}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({2, 4, 6}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({6, 2, 4}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({6, 2}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({6, 4}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({2, 6}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf(A_ContainsContainsSelectedMember({6}), doubled));
}

TEST(ContainsSelectedStaticBinding, BothContainsNoneOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({6}), doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({6, 8}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({2, 6}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({6, 2}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({4, 6}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({2, 4}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({2, 4, 6}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({2}), doubled));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf(A_ContainsContainsSelectedMember({4}), doubled));
}

TEST(ContainsByValueOfStaticBinding, initList) {
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf({1}));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf({1}));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAllOf({1}));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsNoneOf({}));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyOf({2}, doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAnyNotOf({2}, doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsAllOf({2}, doubled));
  ASSERT_TRUE(A_ContainsSelectedMember({1, 2}).containsNoneOf({}, doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf({1}));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf({1}));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf({1}));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf({}));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf({2}, doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf({2}, doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAllOf({2}, doubled));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsNoneOf({}, doubled));
}

#ifdef DCR_SINCECPP14
struct B;

namespace cds {
namespace meta {
template <> struct IterableTraits<B> { using Value = int; };
} // namespace meta
} // namespace cds

struct B : public impl::ContainsOfStaticBinding<B, With<Value, Selector>> {
  constexpr bool contains(int x) const { return x == 1 || x == 2; }
  constexpr int const* begin() const { return data; }
  constexpr int const* end() const { return data + 2; }
  int const data[2] = {1, 2};
};

constexpr int cdoubled(int x) { return x * 2; }
TEST(ContainsByValueOfStaticBinding, cpp14Constexpr) {
  static_assert(B().containsAnyOf(B()), "failed compile time ContainsOf");
  static_assert(!B().containsAnyNotOf(B()), "failed compile time ContainsOf");
  static_assert(!B().containsNoneOf(B()), "failed compile time ContainsOf");
  static_assert(B().containsAllOf(B()), "failed compile time ContainsOf");
  static_assert(B().containsAnyOf(B(), cdoubled), "failed compile time ContainsOf");
  static_assert(B().containsAnyNotOf(B(), cdoubled), "failed compile time ContainsOf");
  static_assert(!B().containsNoneOf(B(), cdoubled), "failed compile time ContainsOf");
  static_assert(!B().containsAllOf(B(), cdoubled), "failed compile time ContainsOf");
}
#endif
