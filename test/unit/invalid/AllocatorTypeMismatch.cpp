// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include <cds/memory/Allocator>
#include "UnitTest.hpp"

namespace {
using cds::Allocator;
}

TEST(AllocatorTypeMismatch, mismatch) {
  auto alloc = Allocator<int>();
  int** p;
  alloc.deallocate(p, 0);
}
