// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/Expected>
#include <cds/Format>

namespace {
using cds::Expected;
using cds::ExpectedValueException;
using cds::Unexpected;
using cds::Unexpect;
} // namespace

TEST(ExpectedVoidTest, unexpected) {}
