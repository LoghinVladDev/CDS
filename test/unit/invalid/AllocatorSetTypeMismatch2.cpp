// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include <cds/memory/Allocator>
#include "UnitTest.hpp"

namespace {
using cds::Allocator;
using cds::AllocatorSet;
}

TEST(AllocatorTypeMismatch2, mismatch) {
  auto alloc = AllocatorSet<Allocator<int>, Allocator<float>>();
  auto p = alloc.template get<int>().allocate(1);
  alloc.template get<float>().deallocate(p, 0);
}
