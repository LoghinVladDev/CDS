// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "../../../src/ds/map/MapBase.hpp"

#include <cds/collection/Vector>

#include <UnitTest.hpp>

namespace {
using cds::Size;
using cds::Tuple;
using cds::ignore;
using cds::impl::BaseMap;
using cds::impl::MapEntry;
using cds::meta::Null;

struct BaseMapImplMockIterator {};

struct BaseMapImplMockConstIterator {};

bool operator==(BaseMapImplMockIterator lhs, BaseMapImplMockIterator rhs) {
  return true;
}

bool operator!=(BaseMapImplMockIterator lhs, BaseMapImplMockIterator rhs) {
  return false;
}

bool operator==(BaseMapImplMockConstIterator lhs, BaseMapImplMockConstIterator rhs) {
  return true;
}

bool operator!=(BaseMapImplMockConstIterator lhs, BaseMapImplMockConstIterator rhs) {
  return false;
}

struct BaseMapImplMock {
  using Iterator = BaseMapImplMockIterator;
  using ConstIterator = BaseMapImplMockConstIterator;

  CDS_ATTR(nodiscard) auto begin() noexcept -> Iterator {
    ++calls.beginCalls;
    return {};
  }

  CDS_ATTR(nodiscard) auto end() noexcept -> Iterator {
    ++calls.endCalls;
    return {};
  }

  CDS_ATTR(nodiscard) auto end() const noexcept -> ConstIterator {
    ++calls.cendCalls;
    return {};
  }

  CDS_ATTR(nodiscard) auto cbegin() const noexcept -> ConstIterator {
    ++calls.cbeginCalls;
    return {};
  }

  CDS_ATTR(nodiscard) auto cend() const noexcept -> ConstIterator {
    ++calls.cendCalls;
    return {};
  }

  void clear() noexcept {
    ++calls.clearCalls;
  }

  template <typename... A> auto emplace(A&&...) noexcept -> Tuple<Iterator, bool> {
    ++calls.emplaceCalls;
    return {Iterator{}, false};
  }

  auto empty() const noexcept -> bool {
    ++calls.emptyCalls;
    return true;
  }

  auto find(int) const noexcept -> ConstIterator {
    ++calls.findCalls;
    return {};
  }

  auto remove(int) noexcept -> bool {
    ++calls.removeCalls;
    return {};
  }

  auto size() const noexcept -> Size {
    ++calls.sizeCalls;
    return 0;
  }

  auto operator[](int) noexcept -> int& {
    return ++calls.indexCalls;
  }

  struct CallCtr {
    int beginCalls{0};
    int endCalls{0};
    int cbeginCalls{0};
    int cendCalls{0};
    int clearCalls{0};
    int emplaceCalls{0};
    int emptyCalls{0};
    int findCalls{0};
    int removeCalls{0};
    int sizeCalls{0};
    int indexCalls{0};
  };

  auto operator[](Null) const noexcept -> CallCtr const& {
    return calls;
  }

  CallCtr mutable calls{};
};

template <typename K, typename V> using BaseMapMock = BaseMap<K, V, BaseMapImplMock>;
} // namespace

TEST(MapBaseTest, ctrFromIters) {
  Tuple<int, int> const tuples[]{{1, 1}, {2, 2}, {3, 3}};
  BaseMapMock<int, int> map(tuples, tuples + 3);
  ASSERT_EQ(3, map[nullptr].emplaceCalls);
}

TEST(MapBaseTest, ctrFromRange) {
  Tuple<int, int> const tuples[]{{1, 1}, {2, 2}, {3, 3}};
  BaseMapMock<int, int> map(tuples);
  ASSERT_EQ(3, map[nullptr].emplaceCalls);
}

TEST(MapBaseTest, ctrFromIList) {
  BaseMapMock<int, int> map{MapEntry<int, int>{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(3, map[nullptr].emplaceCalls);
}

TEST(MapBaseTest, assignFromRange) {
  BaseMapMock<int, int> map;
  ignore = map;
  Tuple<int, int> const tuples[]{{1, 1}, {2, 2}, {3, 3}};
  map = tuples;
  ASSERT_EQ(3, map[nullptr].emplaceCalls);
  ASSERT_EQ(1, map[nullptr].clearCalls);
}

TEST(MapBaseTest, assignFromIList) {
  BaseMapMock<int, int> map;
  ignore = map;
  map = {MapEntry<int, int>{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(3, map[nullptr].emplaceCalls);
  ASSERT_EQ(1, map[nullptr].clearCalls);
}

TEST(MapBaseTest, operatorBool) {
  BaseMapMock<int, int> map;
  ASSERT_FALSE(static_cast<bool>(map));
  ASSERT_EQ(1, map[nullptr].emptyCalls);
}

TEST(MapBaseTest, contains) {
  BaseMapMock<int, int> map;
  ASSERT_FALSE(map.contains(2));
  ASSERT_EQ(1, map[nullptr].cendCalls);
  ASSERT_EQ(1, map[nullptr].findCalls);
}

TEST(MapBaseTest, keys) {
}
