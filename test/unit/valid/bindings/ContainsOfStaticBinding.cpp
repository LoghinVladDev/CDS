// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/shared/bindings/static/ContainsOfStaticBinding.hpp"
#include "UnitTest.hpp"
#include <vector>
#include <algorithm>

using namespace cds;
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

struct A_ContainsMember : public impl::ContainsOfStaticBinding<A_ContainsMember> {
  bool contains(int a) const { return std::find(data.begin(), data.end(), a) != data.end(); }
  std::vector<int>::const_iterator begin() const { return data.begin(); }
  std::vector<int>::const_iterator end() const { return data.end(); }
  std::vector<int> data;
  A_ContainsMember(std::initializer_list<int> const& i) : data(i) {}
};

struct A_ContainsSelectedMember : public impl::ContainsSelectedOfStaticBinding<A_ContainsSelectedMember> {
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
  A_ContainsSelectedMember(std::initializer_list<int> const& i) : data(i) {}
};

struct A_ContainsContainsSelectedMember :
    public impl::ContainsOfStaticBinding<A_ContainsContainsSelectedMember>,
    public impl::ContainsSelectedOfStaticBinding<A_ContainsContainsSelectedMember> {
  using impl::ContainsOfStaticBinding<A_ContainsContainsSelectedMember>::containsAnyOf;
  using impl::ContainsOfStaticBinding<A_ContainsContainsSelectedMember>::containsAnyNotOf;
  using impl::ContainsOfStaticBinding<A_ContainsContainsSelectedMember>::containsNoneOf;
  using impl::ContainsOfStaticBinding<A_ContainsContainsSelectedMember>::containsAllOf;
  using impl::ContainsSelectedOfStaticBinding<A_ContainsContainsSelectedMember>::containsAnyOf;
  using impl::ContainsSelectedOfStaticBinding<A_ContainsContainsSelectedMember>::containsAnyNotOf;
  using impl::ContainsSelectedOfStaticBinding<A_ContainsContainsSelectedMember>::containsNoneOf;
  using impl::ContainsSelectedOfStaticBinding<A_ContainsContainsSelectedMember>::containsAllOf;

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
  A_ContainsContainsSelectedMember(std::initializer_list<int> const& i) : data(i) {}
};

TEST(ContainsOfStaticBinding, ContainsAnyOf) {
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({3, 4})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1, 2})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1, 3})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({3, 1})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyOf(A_ContainsMember({1, 2, 3})));
}

TEST(ContainsOfStaticBinding, ContainsAnyNotOf) {
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({2})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({3})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1, 3})));
  ASSERT_TRUE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({2, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1, 2})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsMember({1, 2}).containsAnyNotOf(A_ContainsMember({4, 1, 2})));
}

TEST(ContainsOfStaticBinding, ContainsAllOf) {
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

TEST(ContainsOfStaticBinding, ContainsNoneOf) {
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

int doubled(int x) { return x * 2; }
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

TEST(ContainsOfStaticBinding, BothContainsAnyOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3, 4})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1, 2})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1, 3})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({3, 1})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyOf(A_ContainsContainsSelectedMember({1, 2, 3})));
}

TEST(ContainsOfStaticBinding, BothContainsAnyNotOf) {
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({2})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({3})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1, 3})));
  ASSERT_TRUE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({2, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1, 2})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({1, 2, 3})));
  ASSERT_FALSE(A_ContainsContainsSelectedMember({1, 2}).containsAnyNotOf(A_ContainsContainsSelectedMember({4, 1, 2})));
}

TEST(ContainsOfStaticBinding, BothContainsAllOf) {
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

TEST(ContainsOfStaticBinding, BothContainsNoneOf) {
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
