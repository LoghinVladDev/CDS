// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/collection/HashMap>
#include <cds/collection/Vector>

#include <cds/Tuple>

#include <UnitTest.hpp>

#include "../Shared.hpp"

namespace {
using cds::Size;
using cds::HashMap;
using cds::Tuple;
using cds::Vector;
using cds::asConst;
using cds::tupleOf;

using testing::citeq;
} // namespace

// Table + element count + bucket count + load factor + rehash table index
static_assert(sizeof(HashMap<int, int>) == sizeof(void*) + 4 * sizeof(Size), "unexpected HashMap size");

TEST(HashMapTest, keys) {
  HashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(map.keys(), Vector<int>{1, 2, 3}));
}

TEST(HashMapTest, keysConst) {
  HashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(asConst(map).keys(), Vector<int>{1, 2, 3}));
}

TEST(HashMapTest, values) {
  HashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(map.values(), Vector<int>{2, 3, 4}));
}

TEST(HashMapTest, valuesConst) {
  HashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(asConst(map).values(), Vector<int>{2, 3, 4}));
}

TEST(HashMapTest, entries) {
  HashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(map.entries(), Vector<Tuple<int, int>>{{1, 2}, {2, 3}, {3, 4}}));
}

TEST(HashMapTest, entriesConst) {
  HashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(asConst(map).entries(), Vector<Tuple<int, int>>{{1, 2}, {2, 3}, {3, 4}}));
}

TEST(HashMapTest, entriesEmplace) {
  HashMap<int, int> map{{1, 2}, {2, 3}, {3, 4}};
  map.entries().emplace(5, 5);
  auto const equiv = HashMap<int, int>{{1, 2}, {2, 3}, {3, 4}, {5, 5}};
  ASSERT_EQ(equiv, map);
}

TEST(HashMapTest, keysRemove) {
  HashMap<int, int> map{{1, 2}, {2, 3}, {3, 4}};
  HashMap<int, int> const equiv{{1, 2}, {3, 4}};
  ASSERT_FALSE(map.keys().remove(4));
  ASSERT_TRUE(map.keys().remove(2));
  ASSERT_EQ(map, equiv);
}

TEST(HashMapTest, entriesRemove) {
  HashMap<int, int> map{{1, 2}, {2, 3}, {3, 4}};
  HashMap<int, int> const equiv{{1, 2}, {3, 4}};
  ASSERT_TRUE(map.entries().remove(tupleOf(2, 3)));
  ASSERT_EQ(map, equiv);
}
