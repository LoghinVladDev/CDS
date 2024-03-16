// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include <cds/StringView>
#include <vector>

#include "UnitTest.hpp"
#include "../Shared.hpp"

TEST(StringViewFindNotOfStringSet, findNotOfCompileFail) {
  testing::citeq(StringView{"abc def ghi"}.findNotOf(std::vector<StringView>{"def"}), std::vector<int>{0, 7});
}
