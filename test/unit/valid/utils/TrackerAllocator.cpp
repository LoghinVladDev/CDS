// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include "../TrackerAllocator.hpp"
#include <cds/Utility>

namespace {
using cds::impl::ignore;
}

TEST(TrackerAllocator, Allocation) {
  testing::TrackerAllocator<int> ta(false);
  auto p = ta.allocate(64);

  ASSERT_EQ(ta.committed(), 64 * sizeof(int));

  ta.deallocate(p, 64);
  // comment the above to check if memcheck tools detect leaks
}

TEST(TrackerAllocator, Copy) {
  testing::TrackerAllocator<int> ta(false);
  auto p = ta.allocate(64);
  auto cta = ta;
  auto p2 = cta.allocate(32);

  ASSERT_EQ(ta.committed(), 64 * sizeof(int));
  ASSERT_EQ(cta.committed(), 32 * sizeof(int));

  ta.deallocate(p, 64);
  cta.deallocate(p2, 32);
  // comment the above to check if memcheck tools detect leaks
}

TEST(TrackerAllocator, Move) {
  testing::TrackerAllocator<int> ta(false);

  auto p = ta.allocate(64);
  auto cta = mv(ta);
  auto p2 = cta.allocate(32);

  ASSERT_EQ(ta.committed(), 0 * sizeof(int));
  ASSERT_EQ(cta.committed(), 96 * sizeof(int));

  cta.deallocate(p, 64);
  cta.deallocate(p2, 32);
  // comment the above to check if memcheck tools detect leaks
}
