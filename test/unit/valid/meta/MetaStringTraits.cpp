// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11-2b

#include <cds/meta/StringTraits>
#include "UnitTest.hpp"
#include <cds/functional/FunctionalInterface>

using namespace cds::meta;

namespace {
bool neverSkip(char) { return false; }
template <typename F = decltype(&neverSkip)> auto validateCharRange(char s, char e, char const* p, F skip = &neverSkip) -> bool {
  for (auto i = s; i <= e;) {
    if (skip(i)) {
      ++i;
      continue;
    }

    if (*p != i) {
      return false;
    }
    ++i;
    ++p;
  }

  return *p == '\0';
}

template <typename F> auto validateCharRange(char s, char e, F fn) -> bool {
  for (auto i = s; i <= e; ++i) {
    if (!fn(i)) {
      return false;
    }
  }

  return true;
}
}

using namespace cds::functional;
TEST(MetaStringTraits, charUtils) {
  ASSERT_TRUE(StringTraits<char>::isUpper('A'));
  ASSERT_TRUE(!StringTraits<char>::isUpper('a'));
  ASSERT_TRUE(!StringTraits<char>::isUpper('.'));
  ASSERT_TRUE(StringTraits<char>::isLower('a'));
  ASSERT_TRUE(!StringTraits<char>::isLower('A'));
  ASSERT_TRUE(!StringTraits<char>::isLower('.'));
  ASSERT_TRUE(StringTraits<char>::isDigit('0'));
  ASSERT_TRUE(!StringTraits<char>::isDigit('a'));
  ASSERT_TRUE(!StringTraits<char>::isDigit('A'));
  ASSERT_TRUE(!StringTraits<char>::isDigit('.'));
  ASSERT_TRUE(!StringTraits<char>::isLetter('.'));
  ASSERT_TRUE(StringTraits<char>::isLetter('a'));
  ASSERT_TRUE(StringTraits<char>::isLetter('A'));
  ASSERT_TRUE(StringTraits<char>::isAlpha('A'));
  ASSERT_TRUE(StringTraits<char>::isAlpha('a'));
  ASSERT_TRUE(StringTraits<char>::isAlpha('1'));
  ASSERT_TRUE(!StringTraits<char>::isAlpha('.'));
  ASSERT_TRUE(StringTraits<char>::isVowel('a'));
  ASSERT_TRUE(StringTraits<char>::isVowel('e'));
  ASSERT_TRUE(StringTraits<char>::isVowel('i'));
  ASSERT_TRUE(StringTraits<char>::isVowel('o'));
  ASSERT_TRUE(StringTraits<char>::isVowel('u'));
  ASSERT_TRUE(!StringTraits<char>::isVowel('b'));
  ASSERT_TRUE(!StringTraits<char>::isVowel('.'));
  ASSERT_TRUE(!StringTraits<char>::isConsonant('a'));
  ASSERT_TRUE(!StringTraits<char>::isConsonant('e'));
  ASSERT_TRUE(!StringTraits<char>::isConsonant('i'));
  ASSERT_TRUE(!StringTraits<char>::isConsonant('o'));
  ASSERT_TRUE(!StringTraits<char>::isConsonant('u'));
  ASSERT_TRUE(StringTraits<char>::isConsonant('b'));
  ASSERT_TRUE(!StringTraits<char>::isConsonant('.'));
  ASSERT_TRUE(StringTraits<char>::lower('a') == 'a');
  ASSERT_TRUE(StringTraits<char>::lower('A') == 'a');
  ASSERT_TRUE(StringTraits<char>::lower('.') == '.');
  ASSERT_TRUE(StringTraits<char>::upper('a') == 'A');
  ASSERT_TRUE(StringTraits<char>::upper('A') == 'A');
  ASSERT_TRUE(StringTraits<char>::upper('.') == '.');

  using T = StringTraits<char>;
  ASSERT_EQ(std::string(T::emptyString), "");
  ASSERT_EQ(static_cast<char>(T::nullChar), '\0');

  ASSERT_TRUE(validateCharRange('0', '9', T::digits));
  ASSERT_TRUE(validateCharRange('a', 'z', T::lowercaseAlphabet));
  ASSERT_TRUE(validateCharRange('A', 'Z', T::uppercaseAlphabet));
  ASSERT_EQ(std::string(T::vowels), "AEIOUaeiou");
  ASSERT_TRUE(validateCharRange('A', 'z', T::consonants, [](char c) {
    return !(c >= 'a' && c <= 'z'
        || c >= 'A' && c <= 'Z')
        || (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        || (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
  }));
  ASSERT_EQ(std::string(T::whitespace), " \t\n\r\f");
  ASSERT_TRUE(validateCharRange('\0', 'A' - 1, notFn(T::isUpper)));
  ASSERT_TRUE(validateCharRange('A', 'Z', T::isUpper));
  ASSERT_TRUE(validateCharRange('Z' + 1, 126, notFn(T::isUpper)));

  ASSERT_TRUE(validateCharRange('\0', 'a' - 1, notFn(T::isLower)));
  ASSERT_TRUE(validateCharRange('a', 'z', T::isLower));
  ASSERT_TRUE(validateCharRange('z' + 1, 126, notFn(T::isLower)));
}

#ifdef DCR_SINCECPP11
TEST(MetaStringTraits, charUtilsConstexpr) {
  static_assert(StringTraits<char>::isUpper('A'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isUpper('a'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isUpper('.'), "Failed StringTraits");

  static_assert(StringTraits<char>::isLower('a'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isLower('A'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isLower('.'), "Failed StringTraits");

  static_assert(StringTraits<char>::isDigit('0'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isDigit('a'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isDigit('A'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isDigit('.'), "Failed StringTraits");

  static_assert(!StringTraits<char>::isLetter('.'), "Failed StringTraits");
  static_assert(StringTraits<char>::isLetter('a'), "Failed StringTraits");
  static_assert(StringTraits<char>::isLetter('A'), "Failed StringTraits");

  static_assert(StringTraits<char>::isAlpha('A'), "Failed StringTraits");
  static_assert(StringTraits<char>::isAlpha('a'), "Failed StringTraits");
  static_assert(StringTraits<char>::isAlpha('1'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isAlpha('.'), "Failed StringTraits");

  static_assert(StringTraits<char>::isVowel('a'), "Failed StringTraits");
  static_assert(StringTraits<char>::isVowel('e'), "Failed StringTraits");
  static_assert(StringTraits<char>::isVowel('i'), "Failed StringTraits");
  static_assert(StringTraits<char>::isVowel('o'), "Failed StringTraits");
  static_assert(StringTraits<char>::isVowel('u'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isVowel('b'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isVowel('.'), "Failed StringTraits");

  static_assert(!StringTraits<char>::isConsonant('a'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isConsonant('e'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isConsonant('i'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isConsonant('o'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isConsonant('u'), "Failed StringTraits");
  static_assert(StringTraits<char>::isConsonant('b'), "Failed StringTraits");
  static_assert(!StringTraits<char>::isConsonant('.'), "Failed StringTraits");

  static_assert(StringTraits<char>::lower('a') == 'a', "Failed StringTraits");
  static_assert(StringTraits<char>::lower('A') == 'a', "Failed StringTraits");
  static_assert(StringTraits<char>::lower('.') == '.', "Failed StringTraits");

  static_assert(StringTraits<char>::upper('a') == 'A', "Failed StringTraits");
  static_assert(StringTraits<char>::upper('A') == 'A', "Failed StringTraits");
  static_assert(StringTraits<char>::upper('.') == '.', "Failed StringTraits");
}
#endif
