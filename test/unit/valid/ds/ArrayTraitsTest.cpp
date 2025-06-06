// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "../../../src/ds/array/ArrayTraits.hpp"

namespace {
using cds::impl::ArrayTraits;

static_assert(ArrayTraits<int>::minCapacity == 32u, "unexpected default starting capacity");
static_assert(ArrayTraits<int>::scalingMultiplier == 2u, "unexpected default scaling multiplier");
} // namespace
