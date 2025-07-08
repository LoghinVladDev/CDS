// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "../../../src/ds/map/MapEntry.hpp"

#include <cds/meta/ObjectTraits>

#include <UnitTest.hpp>

namespace {
using cds::impl::MapEntry;
using cds::Tuple;
using cds::meta::IsAssignable;
using cds::meta::IsSame;
using cds::meta::RemoveCVRef;
using cds::meta::lvalue;

static_assert(!IsAssignable<decltype(lvalue<MapEntry<int, int>>())>::value, "unexpected failure");
static_assert(!IsAssignable<decltype(lvalue<MapEntry<int, int>>().key())>::value, "unexpected failure");
static_assert(!IsAssignable<decltype(cds::get<0>(lvalue<MapEntry<int, int>>()))>::value, "unexpected failure");
static_assert(IsAssignable<decltype(lvalue<MapEntry<int, int>>().value())>::value, "unexpected failure");
static_assert(IsAssignable<decltype(cds::get<1>(lvalue<MapEntry<int, int>>()))>::value, "unexpected failure");
} // namespace

TEST(MapEntryTest, kv) {
  MapEntry<int, int> entry {1, 2};
  ASSERT_EQ(1, entry.key());
  ASSERT_EQ(1, asConst(entry).key());
  ASSERT_EQ(2, entry.value());
  ASSERT_EQ(2, asConst(entry).value());

  MapEntry<int, int> entry1 {1, 2};
  ASSERT_EQ(1, std::move(entry1).key());
  MapEntry<int, int> entry2 {1, 2};
  ASSERT_EQ(2, std::move(entry2).value());
}

TEST(MapEntryTest, tupleDecay) {
  MapEntry<int, int> entry{1, 2};
  auto const& asTuple = static_cast<Tuple<int const, int> const&>(entry);
  static_assert(IsSame<RemoveCVRef<decltype(asTuple)>, Tuple<int const, int>>::value, "test");
  ASSERT_EQ(1, cds::get<0>(asTuple));
  ASSERT_EQ(2, cds::get<1>(asTuple));
}

TEST(MapEntryTest, ctrEmplaceEquiv) {
  struct X {
    X(int x, int y, int z) : a{x}, b{y}, c{z} {}

    int a; int b; int c;
    bool operator==(X const& other) const noexcept {
      return a == other.a && b == other.b && c == other.c;
    }
  };

  MapEntry<int, X> entry{1, 2, 3, 4};

  auto const equiv = X{2, 3, 4};
  ASSERT_EQ(1, entry.key());
  ASSERT_EQ(equiv, entry.value());
}

#if CDS_ATTR(cpp17)
TEST(MapEntryTest, strBinding) {
  MapEntry<int, int> entry{1, 2};
  auto& [k, v] = entry;

  static_assert(!IsAssignable<decltype(k)>::value, "test");
  static_assert(IsAssignable<decltype(v)>::value, "test");

  v = 3;
  ASSERT_EQ(3, entry.value());
}
#endif

#if CDS_ATTR(ctad)
TEST(MapEntryTest, ctad) {
  MapEntry entry{1, 2};
  static_assert(IsSame<RemoveCVRef<decltype(entry)>, MapEntry<int, int>>::value, "test");
}
#endif
