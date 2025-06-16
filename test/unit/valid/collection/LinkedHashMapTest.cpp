// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/collection/LinkedHashMap>
#include <cds/collection/Vector>

#include <cds/Tuple>

#include <UnitTest.hpp>

#include "../Shared.hpp"

namespace {
using cds::Size;
using cds::LinkedHashMap;
using cds::Tuple;
using cds::Vector;
using cds::asConst;
using cds::tupleOf;

using testing::citeq;
} // namespace

// Table + element count + bucket count + load factor + rehash table index + head + tail of ll
static_assert(sizeof(LinkedHashMap<int, int>) == sizeof(void*) + 4 * sizeof(Size) + 2 * sizeof(void*),
              "unexpected LinkedHashMap size");

TEST(LinkedHashMapTest, keys) {
  LinkedHashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(map.keys(), Vector<int>{1, 2, 3}));
}

TEST(LinkedHashMapTest, keysConst) {
  LinkedHashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(asConst(map).keys(), Vector<int>{1, 2, 3}));
}

TEST(LinkedHashMapTest, values) {
  LinkedHashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(map.values(), Vector<int>{2, 3, 4}));
}

TEST(LinkedHashMapTest, valuesConst) {
  LinkedHashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(asConst(map).values(), Vector<int>{2, 3, 4}));
}

TEST(LinkedHashMapTest, entries) {
  LinkedHashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(map.entries(), Vector<Tuple<int, int>>{{1, 2}, {2, 3}, {3, 4}}));
}

TEST(LinkedHashMapTest, entriesConst) {
  LinkedHashMap<int, int>map {{1, 2}, {2, 3}, {3, 4}};
  ASSERT_TRUE(citeq(asConst(map).entries(), Vector<Tuple<int, int>>{{1, 2}, {2, 3}, {3, 4}}));
}

TEST(LinkedHashMapTest, entriesEmplace) {
  LinkedHashMap<int, int> map{{1, 2}, {2, 3}, {3, 4}};
  map.entries().emplace(5, 5);
  auto const equiv = LinkedHashMap<int, int>{{1, 2}, {2, 3}, {3, 4}, {5, 5}};
  ASSERT_EQ(equiv, map);
}

TEST(LinkedHashMapTest, keysRemove) {
  LinkedHashMap<int, int> map{{1, 2}, {2, 3}, {3, 4}};
  LinkedHashMap<int, int> const equiv{{1, 2}, {3, 4}};
  ASSERT_FALSE(map.keys().remove(4));
  ASSERT_TRUE(map.keys().remove(2));
  ASSERT_EQ(map, equiv);
}

TEST(LinkedHashMapTest, entriesRemove) {
  LinkedHashMap<int, int> map{{1, 2}, {2, 3}, {3, 4}};
  LinkedHashMap<int, int> const equiv{{1, 2}, {3, 4}};
  ASSERT_TRUE(map.entries().remove(tupleOf(2, 3)));
  ASSERT_EQ(map, equiv);
}
