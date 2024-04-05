// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include "../TrackerAllocator.hpp"

TEST(TrackerAllocator, Allocation) {
  testing::TrackerAllocator<int> ta(false);
  auto p = ta.allocate(64);

  ASSERT_EQ(ta.committed(), 64 * sizeof(int));
  (void)p;
  // ta.deallocate(p, 64);
}

TEST(TrackerAllocator, Copy) {
  testing::TrackerAllocator<int> ta(false);

  auto p = ta.allocate(64);
  auto cta = ta;
  auto p2 = cta.allocate(32);

  ASSERT_EQ(ta.committed(), 64 * sizeof(int));
  ASSERT_EQ(cta.committed(), 32 * sizeof(int));
}

TEST(TrackerAllocator, Move) {
  testing::TrackerAllocator<int> ta(false);

  auto p = ta.allocate(64);
  auto cta = cds::move(ta);
  auto p2 = cta.allocate(32);

  ASSERT_EQ(ta.committed(), 0 * sizeof(int));
  ASSERT_EQ(cta.committed(), 96 * sizeof(int));
}
