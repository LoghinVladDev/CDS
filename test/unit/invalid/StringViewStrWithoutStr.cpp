// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include <cds/StringView>
#include "UnitTest.hpp"

TEST(StringView, withoutStringInclude) {
  StringView {"abc"}.str();
}
