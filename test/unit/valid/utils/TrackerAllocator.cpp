// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
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
  ignore = p;
}

TEST(TrackerAllocator, Copy) {
  testing::TrackerAllocator<int> ta(false);
  auto p = ta.allocate(64);
  auto cta = ta;
  auto p2 = cta.allocate(32);

  ASSERT_EQ(ta.committed(), 64 * sizeof(int));
  ASSERT_EQ(cta.committed(), 32 * sizeof(int));
  ignore = p;
  ignore = p2;
}

TEST(TrackerAllocator, Move) {
  testing::TrackerAllocator<int> ta(false);

  auto p = ta.allocate(64);
  auto cta = cds::move(ta);
  auto p2 = cta.allocate(32);

  ASSERT_EQ(ta.committed(), 0 * sizeof(int));
  ASSERT_EQ(cta.committed(), 96 * sizeof(int));
  ignore = p;
  ignore = p2;
}
