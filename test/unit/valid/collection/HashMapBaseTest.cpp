// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"

#include "../../../../src/collection/hashMap/HashMapAllocator.hpp"
#include "../../../../src/collection/hashMap/HashMapBase.hpp"

#include <cds/functional/Comparator>

namespace {
using cds::impl::BaseHashMap;
using cds::impl::HashMapAllocator;
using cds::impl::MapEntry;
using cds::functional::Hash;
using cds::functional::Equal;

template <typename K, typename V> using HashMap = BaseHashMap<K, V, Hash<>, Equal<>, HashMapAllocator<K, V>>;
} // namespace

TEST(HashMapBaseTest, emplace) {
  HashMap<int, int> map;

  auto success0 = map.emplace(1, 1);
  ASSERT_TRUE(success0.get<1>());
  ASSERT_NE(map.end(), success0.get<0>());
  ASSERT_EQ((MapEntry<int, int>(1, 1)), *success0.get<0>());

  auto success1 = map.emplace(2, 1);
  ASSERT_TRUE(success1.get<1>());
  ASSERT_NE(map.end(), success1.get<0>());
  ASSERT_EQ((MapEntry<int, int>(2, 1)), *success1.get<0>());

  auto failure0 = map.emplace(1, 3);
  ASSERT_FALSE(failure0.get<1>());
  ASSERT_NE(map.end(), failure0.get<0>());
  ASSERT_EQ((MapEntry<int, int>(1, 1)), *failure0.get<0>());
}

TEST(HashMapBaseTest, multiArgEmplace) {
  struct X {
    X(int x, int y, int z) : a{x}, b{y}, c{z} {}
    int a; int b; int c;
    bool operator==(X const& o) const {
      return a == o.a && b == o.b && c == o.c;
    }
  };
  HashMap<int, X> map;

  auto success0 = map.emplace(1, 2, 3, 4);
  ASSERT_TRUE(success0.get<1>());
  ASSERT_NE(map.end(), success0.get<0>());
  ASSERT_EQ((MapEntry<int, X>(1, X{2, 3, 4})), *success0.get<0>());
}

TEST(HashMapBaseTest, indexOp) {
  HashMap<int, int> map;
  map[0] = 2;
  map[5] = 1;
  map[20] = 3;

  ASSERT_NE(map.end(), map.find(0));
  ASSERT_NE(map.end(), map.find(5));
  ASSERT_NE(map.end(), map.find(20));
  ASSERT_EQ(3u, map.size());

  ASSERT_EQ(2, map.find(0)->value());
  ASSERT_EQ(1, map.find(5)->value());
  ASSERT_EQ(3, map.find(20)->value());
}
