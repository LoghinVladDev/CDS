// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11
// EXPECTED[compile]: failure

#include <StringView>
#include <initializer_list>

TEST(StringView, SplitUnextendableTemporary) {
  for (auto token : StringView{"ae ; ae;ae ae; ae ;"}.split(std::initializer_list<char>{' ', ';'})) {
    (void) token;
  }
}
