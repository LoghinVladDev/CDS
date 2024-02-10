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

TEST(AllocatorTypeMismatch1, mismatch) {
  auto alloc = AllocatorSet<Allocator<int>, Allocator<float>>();
  double* p;
  alloc.template get<double>().deallocate(p, 0);
}
