// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11+

#include <cds/meta/StringTraits>
#include "UnitTest.hpp"
#include <cds/functional/FunctionalInterface>

using namespace cds::meta;

namespace {
template <typename T> bool neverSkip(T) { return false; }

template <typename T, typename F = decltype(&neverSkip<T>)>
auto validateCharRange(T const s, T const e, T const* p, F skip = &neverSkip<T>) -> bool {
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

  return *p == StringTraits<T>::nullChar;
}

template <typename T, typename F> auto validateCharRange(T const s, T const e, F fn) -> bool {
  for (auto i = s; i <= e; ++i) {
    if (!fn(i)) {
      return false;
    }
  }

  return true;
}

template <typename C> bool charRangeEvaluation(C h1, C const t1, char h2, char const t2) {
  for (; h1 != t1 && h2 != t2; ++h1, ++h2) {
    if (static_cast<int>(h1) != static_cast<int>(h2)) {
      return false;
    }
  }
  return h1 == t1 && h2 == t2 && static_cast<int>(h1) == static_cast<int>(h2);
}
}

TEST(MetaStringTraits, charRangeEvaluationWChar) {
  ASSERT_TRUE(charRangeEvaluation(L'A', L'Z', 'A', 'Z'));
  ASSERT_TRUE(charRangeEvaluation(L'a', L'z', 'a', 'z'));
  ASSERT_TRUE(charRangeEvaluation(L'0', L'9', '0', '9'));
}

TEST(MetaStringTraits, charRangeEvaluationChar16) {
  ASSERT_TRUE(charRangeEvaluation(u'A', u'Z', 'A', 'Z'));
  ASSERT_TRUE(charRangeEvaluation(u'a', u'z', 'a', 'z'));
  ASSERT_TRUE(charRangeEvaluation(u'0', u'9', '0', '9'));
}

TEST(MetaStringTraits, charRangeEvaluationChar32) {
  ASSERT_TRUE(charRangeEvaluation(U'A', U'Z', 'A', 'Z'));
  ASSERT_TRUE(charRangeEvaluation(U'a', U'z', 'a', 'z'));
  ASSERT_TRUE(charRangeEvaluation(U'0', U'9', '0', '9'));
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
  /// cast to force ODR
  ASSERT_EQ(static_cast<char>(T::nullChar), '\0');

  ASSERT_TRUE(validateCharRange('0', '9', T::digits));
  ASSERT_TRUE(validateCharRange('a', 'z', T::lowercaseAlphabet));
  ASSERT_TRUE(validateCharRange('A', 'Z', T::uppercaseAlphabet));
  ASSERT_EQ(std::string(T::vowels), "AEIOUaeiou");
  ASSERT_TRUE(validateCharRange('A', 'z', T::consonants, [](char const c) {
    return !(c >= 'a' && c <= 'z'
        || c >= 'A' && c <= 'Z')
        || (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        || (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
  }));
  ASSERT_EQ(std::string(T::whitespace), " \t\n\r\f");
  ASSERT_TRUE(validateCharRange<char>('\0', 'A' - 1, notFn(T::isUpper)));
  ASSERT_TRUE(validateCharRange<char>('A', 'Z', T::isUpper));
  ASSERT_TRUE(validateCharRange<char>('Z' + 1, 126, notFn(T::isUpper)));

  ASSERT_TRUE(validateCharRange<char>('\0', 'a' - 1, notFn(T::isLower)));
  ASSERT_TRUE(validateCharRange<char>('a', 'z', T::isLower));
  ASSERT_TRUE(validateCharRange<char>('z' + 1, 126, notFn(T::isLower)));
}

TEST(MetaStringTraits, wideCharUtils) {
  ASSERT_TRUE(StringTraits<wchar_t>::isUpper(L'A'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isUpper(L'a'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isUpper(L'.'));
  ASSERT_TRUE(StringTraits<wchar_t>::isLower(L'a'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isLower(L'A'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isLower(L'.'));
  ASSERT_TRUE(StringTraits<wchar_t>::isDigit(L'0'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isDigit(L'a'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isDigit(L'A'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isDigit(L'.'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isLetter(L'.'));
  ASSERT_TRUE(StringTraits<wchar_t>::isLetter(L'a'));
  ASSERT_TRUE(StringTraits<wchar_t>::isLetter(L'A'));
  ASSERT_TRUE(StringTraits<wchar_t>::isAlpha(L'A'));
  ASSERT_TRUE(StringTraits<wchar_t>::isAlpha(L'a'));
  ASSERT_TRUE(StringTraits<wchar_t>::isAlpha(L'1'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isAlpha(L'.'));
  ASSERT_TRUE(StringTraits<wchar_t>::isVowel(L'a'));
  ASSERT_TRUE(StringTraits<wchar_t>::isVowel(L'e'));
  ASSERT_TRUE(StringTraits<wchar_t>::isVowel(L'i'));
  ASSERT_TRUE(StringTraits<wchar_t>::isVowel(L'o'));
  ASSERT_TRUE(StringTraits<wchar_t>::isVowel(L'u'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isVowel(L'b'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isVowel(L'.'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isConsonant(L'a'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isConsonant(L'e'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isConsonant(L'i'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isConsonant(L'o'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isConsonant(L'u'));
  ASSERT_TRUE(StringTraits<wchar_t>::isConsonant(L'b'));
  ASSERT_TRUE(!StringTraits<wchar_t>::isConsonant(L'.'));
  ASSERT_TRUE(StringTraits<wchar_t>::lower(L'a') == L'a');
  ASSERT_TRUE(StringTraits<wchar_t>::lower(L'A') == L'a');
  ASSERT_TRUE(StringTraits<wchar_t>::lower(L'.') == L'.');
  ASSERT_TRUE(StringTraits<wchar_t>::upper(L'a') == L'A');
  ASSERT_TRUE(StringTraits<wchar_t>::upper(L'A') == L'A');
  ASSERT_TRUE(StringTraits<wchar_t>::upper(L'.') == L'.');

  using T = StringTraits<wchar_t>;
  ASSERT_EQ(std::wstring(T::emptyString), L"");
  /// cast to force ODR
  ASSERT_EQ(static_cast<wchar_t>(T::nullChar), L'\0');

  ASSERT_TRUE(validateCharRange(L'0', L'9', T::digits));
  ASSERT_TRUE(validateCharRange(L'a', L'z', T::lowercaseAlphabet));
  ASSERT_TRUE(validateCharRange(L'A', L'Z', T::uppercaseAlphabet));
  ASSERT_EQ(std::wstring(T::vowels), L"AEIOUaeiou");
  ASSERT_TRUE(validateCharRange(L'A', L'z', T::consonants, [](wchar_t const c) {
    return !(c >= L'a' && c <= L'z'
        || c >= L'A' && c <= L'Z')
        || (c == L'a' || c == L'e' || c == L'i' || c == L'o' || c == L'u')
        || (c == L'A' || c == L'E' || c == L'I' || c == L'O' || c == L'U');
  }));
  ASSERT_EQ(std::wstring(T::whitespace), L" \t\n\r\f");
  ASSERT_TRUE(validateCharRange<wchar_t>(L'\0', L'A' - 1, notFn(T::isUpper)));
  ASSERT_TRUE(validateCharRange<wchar_t>(L'A', L'Z', T::isUpper));
  ASSERT_TRUE(validateCharRange<wchar_t>('Z' + 1, 126, notFn(T::isUpper)));

  ASSERT_TRUE(validateCharRange<wchar_t>(L'\0', L'a' - 1, notFn(T::isLower)));
  ASSERT_TRUE(validateCharRange<wchar_t>(L'a', L'z', T::isLower));
  ASSERT_TRUE(validateCharRange<wchar_t>('z' + 1, 126, notFn(T::isLower)));
}

TEST(MetaStringTraits, char16Utils) {
  ASSERT_TRUE(StringTraits<char16_t>::isUpper(u'A'));
  ASSERT_TRUE(!StringTraits<char16_t>::isUpper(u'a'));
  ASSERT_TRUE(!StringTraits<char16_t>::isUpper(u'.'));
  ASSERT_TRUE(StringTraits<char16_t>::isLower(u'a'));
  ASSERT_TRUE(!StringTraits<char16_t>::isLower(u'A'));
  ASSERT_TRUE(!StringTraits<char16_t>::isLower(u'.'));
  ASSERT_TRUE(StringTraits<char16_t>::isDigit(u'0'));
  ASSERT_TRUE(!StringTraits<char16_t>::isDigit(u'a'));
  ASSERT_TRUE(!StringTraits<char16_t>::isDigit(u'A'));
  ASSERT_TRUE(!StringTraits<char16_t>::isDigit(u'.'));
  ASSERT_TRUE(!StringTraits<char16_t>::isLetter(u'.'));
  ASSERT_TRUE(StringTraits<char16_t>::isLetter(u'a'));
  ASSERT_TRUE(StringTraits<char16_t>::isLetter(u'A'));
  ASSERT_TRUE(StringTraits<char16_t>::isAlpha(u'A'));
  ASSERT_TRUE(StringTraits<char16_t>::isAlpha(u'a'));
  ASSERT_TRUE(StringTraits<char16_t>::isAlpha(u'1'));
  ASSERT_TRUE(!StringTraits<char16_t>::isAlpha(u'.'));
  ASSERT_TRUE(StringTraits<char16_t>::isVowel(u'a'));
  ASSERT_TRUE(StringTraits<char16_t>::isVowel(u'e'));
  ASSERT_TRUE(StringTraits<char16_t>::isVowel(u'i'));
  ASSERT_TRUE(StringTraits<char16_t>::isVowel(u'o'));
  ASSERT_TRUE(StringTraits<char16_t>::isVowel(u'u'));
  ASSERT_TRUE(!StringTraits<char16_t>::isVowel(u'b'));
  ASSERT_TRUE(!StringTraits<char16_t>::isVowel(u'.'));
  ASSERT_TRUE(!StringTraits<char16_t>::isConsonant(u'a'));
  ASSERT_TRUE(!StringTraits<char16_t>::isConsonant(u'e'));
  ASSERT_TRUE(!StringTraits<char16_t>::isConsonant(u'i'));
  ASSERT_TRUE(!StringTraits<char16_t>::isConsonant(u'o'));
  ASSERT_TRUE(!StringTraits<char16_t>::isConsonant(u'u'));
  ASSERT_TRUE(StringTraits<char16_t>::isConsonant(u'b'));
  ASSERT_TRUE(!StringTraits<char16_t>::isConsonant(u'.'));
  ASSERT_TRUE(StringTraits<char16_t>::lower(u'a') == u'a');
  ASSERT_TRUE(StringTraits<char16_t>::lower(u'A') == u'a');
  ASSERT_TRUE(StringTraits<char16_t>::lower(u'.') == u'.');
  ASSERT_TRUE(StringTraits<char16_t>::upper(u'a') == u'A');
  ASSERT_TRUE(StringTraits<char16_t>::upper(u'A') == u'A');
  ASSERT_TRUE(StringTraits<char16_t>::upper(u'.') == u'.');

  using T = StringTraits<char16_t>;
  ASSERT_EQ(std::u16string(T::emptyString), u"");
  /// cast to force ODR
  ASSERT_EQ(static_cast<char16_t>(T::nullChar), u'\0');

  ASSERT_TRUE(validateCharRange(u'0', u'9', T::digits));
  ASSERT_TRUE(validateCharRange(u'a', u'z', T::lowercaseAlphabet));
  ASSERT_TRUE(validateCharRange(u'A', u'Z', T::uppercaseAlphabet));
  ASSERT_EQ(std::u16string(T::vowels), u"AEIOUaeiou");
  ASSERT_TRUE(validateCharRange(u'A', u'z', T::consonants, [](char16_t const c) {
    return !(c >= u'a' && c <= u'z'
        || c >= u'A' && c <= u'Z')
        || (c == u'a' || c == u'e' || c == u'i' || c == u'o' || c == u'u')
        || (c == u'A' || c == u'E' || c == u'I' || c == u'O' || c == u'U');
  }));
  ASSERT_EQ(std::u16string(T::whitespace), u" \t\n\r\f");
  ASSERT_TRUE(validateCharRange<char16_t>(u'\0', u'A' - 1, notFn(T::isUpper)));
  ASSERT_TRUE(validateCharRange<char16_t>(u'A', u'Z', T::isUpper));
  ASSERT_TRUE(validateCharRange<char16_t>(u'Z' + 1, 126, notFn(T::isUpper)));

  ASSERT_TRUE(validateCharRange<char16_t>(u'\0', u'a' - 1, notFn(T::isLower)));
  ASSERT_TRUE(validateCharRange<char16_t>(u'a', u'z', T::isLower));
  ASSERT_TRUE(validateCharRange<char16_t>(u'z' + 1, 126, notFn(T::isLower)));
}

TEST(MetaStringTraits, char32Utils) {
  ASSERT_TRUE(StringTraits<char32_t>::isUpper(U'A'));
  ASSERT_TRUE(!StringTraits<char32_t>::isUpper(U'a'));
  ASSERT_TRUE(!StringTraits<char32_t>::isUpper(U'.'));
  ASSERT_TRUE(StringTraits<char32_t>::isLower(U'a'));
  ASSERT_TRUE(!StringTraits<char32_t>::isLower(U'A'));
  ASSERT_TRUE(!StringTraits<char32_t>::isLower(U'.'));
  ASSERT_TRUE(StringTraits<char32_t>::isDigit(U'0'));
  ASSERT_TRUE(!StringTraits<char32_t>::isDigit(U'a'));
  ASSERT_TRUE(!StringTraits<char32_t>::isDigit(U'A'));
  ASSERT_TRUE(!StringTraits<char32_t>::isDigit(U'.'));
  ASSERT_TRUE(!StringTraits<char32_t>::isLetter(U'.'));
  ASSERT_TRUE(StringTraits<char32_t>::isLetter(U'a'));
  ASSERT_TRUE(StringTraits<char32_t>::isLetter(U'A'));
  ASSERT_TRUE(StringTraits<char32_t>::isAlpha(U'A'));
  ASSERT_TRUE(StringTraits<char32_t>::isAlpha(U'a'));
  ASSERT_TRUE(StringTraits<char32_t>::isAlpha(U'1'));
  ASSERT_TRUE(!StringTraits<char32_t>::isAlpha(U'.'));
  ASSERT_TRUE(StringTraits<char32_t>::isVowel(U'a'));
  ASSERT_TRUE(StringTraits<char32_t>::isVowel(U'e'));
  ASSERT_TRUE(StringTraits<char32_t>::isVowel(U'i'));
  ASSERT_TRUE(StringTraits<char32_t>::isVowel(U'o'));
  ASSERT_TRUE(StringTraits<char32_t>::isVowel(U'U'));
  ASSERT_TRUE(!StringTraits<char32_t>::isVowel(U'b'));
  ASSERT_TRUE(!StringTraits<char32_t>::isVowel(U'.'));
  ASSERT_TRUE(!StringTraits<char32_t>::isConsonant(U'a'));
  ASSERT_TRUE(!StringTraits<char32_t>::isConsonant(U'e'));
  ASSERT_TRUE(!StringTraits<char32_t>::isConsonant(U'i'));
  ASSERT_TRUE(!StringTraits<char32_t>::isConsonant(U'o'));
  ASSERT_TRUE(!StringTraits<char32_t>::isConsonant(U'U'));
  ASSERT_TRUE(StringTraits<char32_t>::isConsonant(U'b'));
  ASSERT_TRUE(!StringTraits<char32_t>::isConsonant(U'.'));
  ASSERT_TRUE(StringTraits<char32_t>::lower(U'a') == U'a');
  ASSERT_TRUE(StringTraits<char32_t>::lower(U'A') == U'a');
  ASSERT_TRUE(StringTraits<char32_t>::lower(U'.') == U'.');
  ASSERT_TRUE(StringTraits<char32_t>::upper(U'a') == U'A');
  ASSERT_TRUE(StringTraits<char32_t>::upper(U'A') == U'A');
  ASSERT_TRUE(StringTraits<char32_t>::upper(U'.') == U'.');

  using T = StringTraits<char32_t>;
  ASSERT_EQ(std::u32string(T::emptyString), U"");
  /// cast to force ODR
  ASSERT_EQ(static_cast<char32_t>(T::nullChar), U'\0');

  ASSERT_TRUE(validateCharRange(U'0', U'9', T::digits));
  ASSERT_TRUE(validateCharRange(U'a', U'z', T::lowercaseAlphabet));
  ASSERT_TRUE(validateCharRange(U'A', U'Z', T::uppercaseAlphabet));
  ASSERT_EQ(std::u32string(T::vowels), U"AEIOUaeiou");
  ASSERT_TRUE(validateCharRange(U'A', U'z', T::consonants, [](char32_t const c) {
    return !(c >= U'a' && c <= U'z'
        || c >= U'A' && c <= U'Z')
        || (c == U'a' || c == U'e' || c == U'i' || c == U'o' || c == U'u')
        || (c == U'A' || c == U'E' || c == U'I' || c == U'O' || c == U'U');
  }));
  ASSERT_EQ(std::u32string(T::whitespace), U" \t\n\r\f");
  ASSERT_TRUE(validateCharRange<char32_t>(U'\0', U'A' - 1, notFn(T::isUpper)));
  ASSERT_TRUE(validateCharRange<char32_t>(U'A', U'Z', T::isUpper));
  ASSERT_TRUE(validateCharRange<char32_t>(U'Z' + 1, 126, notFn(T::isUpper)));

  ASSERT_TRUE(validateCharRange<char32_t>(U'\0', U'a' - 1, notFn(T::isLower)));
  ASSERT_TRUE(validateCharRange<char32_t>(U'a', U'z', T::isLower));
  ASSERT_TRUE(validateCharRange<char32_t>(U'z' + 1, 126, notFn(T::isLower)));
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

TEST(MetaStringTraits, wcharUtilsConstexpr) {
  static_assert(StringTraits<wchar_t>::isUpper(L'A'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isUpper(L'a'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isUpper(L'.'), "Failed StringTraits");

  static_assert(StringTraits<wchar_t>::isLower(L'a'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isLower(L'A'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isLower(L'.'), "Failed StringTraits");

  static_assert(StringTraits<wchar_t>::isDigit(L'0'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isDigit(L'a'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isDigit(L'A'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isDigit(L'.'), "Failed StringTraits");

  static_assert(!StringTraits<wchar_t>::isLetter(L'.'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isLetter(L'a'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isLetter(L'A'), "Failed StringTraits");

  static_assert(StringTraits<wchar_t>::isAlpha(L'A'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isAlpha(L'a'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isAlpha(L'1'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isAlpha(L'.'), "Failed StringTraits");

  static_assert(StringTraits<wchar_t>::isVowel(L'a'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isVowel(L'e'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isVowel(L'i'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isVowel(L'o'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isVowel(L'u'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isVowel(L'b'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isVowel(L'.'), "Failed StringTraits");

  static_assert(!StringTraits<wchar_t>::isConsonant(L'a'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isConsonant(L'e'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isConsonant(L'i'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isConsonant(L'o'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isConsonant(L'u'), "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::isConsonant(L'b'), "Failed StringTraits");
  static_assert(!StringTraits<wchar_t>::isConsonant(L'.'), "Failed StringTraits");

  static_assert(StringTraits<wchar_t>::lower(L'a') == L'a', "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::lower(L'A') == L'a', "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::lower(L'.') == L'.', "Failed StringTraits");

  static_assert(StringTraits<wchar_t>::upper(L'a') == L'A', "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::upper(L'A') == L'A', "Failed StringTraits");
  static_assert(StringTraits<wchar_t>::upper(L'.') == L'.', "Failed StringTraits");
}

TEST(MetaStringTraits, char16UtilsConstexpr) {
  static_assert(StringTraits<char16_t>::isUpper(u'A'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isUpper(u'a'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isUpper(u'.'), "Failed StringTraits");

  static_assert(StringTraits<char16_t>::isLower(u'a'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isLower(u'A'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isLower(u'.'), "Failed StringTraits");

  static_assert(StringTraits<char16_t>::isDigit(u'0'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isDigit(u'a'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isDigit(u'A'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isDigit(u'.'), "Failed StringTraits");

  static_assert(!StringTraits<char16_t>::isLetter(u'.'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isLetter(u'a'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isLetter(u'A'), "Failed StringTraits");

  static_assert(StringTraits<char16_t>::isAlpha(u'A'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isAlpha(u'a'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isAlpha(u'1'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isAlpha(u'.'), "Failed StringTraits");

  static_assert(StringTraits<char16_t>::isVowel(u'a'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isVowel(u'e'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isVowel(u'i'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isVowel(u'o'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isVowel(u'u'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isVowel(u'b'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isVowel(u'.'), "Failed StringTraits");

  static_assert(!StringTraits<char16_t>::isConsonant(u'a'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isConsonant(u'e'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isConsonant(u'i'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isConsonant(u'o'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isConsonant(u'u'), "Failed StringTraits");
  static_assert(StringTraits<char16_t>::isConsonant(u'b'), "Failed StringTraits");
  static_assert(!StringTraits<char16_t>::isConsonant(u'.'), "Failed StringTraits");

  static_assert(StringTraits<char16_t>::lower(u'a') == u'a', "Failed StringTraits");
  static_assert(StringTraits<char16_t>::lower(u'A') == u'a', "Failed StringTraits");
  static_assert(StringTraits<char16_t>::lower(u'.') == u'.', "Failed StringTraits");

  static_assert(StringTraits<char16_t>::upper(u'a') == u'A', "Failed StringTraits");
  static_assert(StringTraits<char16_t>::upper(u'A') == u'A', "Failed StringTraits");
  static_assert(StringTraits<char16_t>::upper(u'.') == u'.', "Failed StringTraits");
}

TEST(MetaStringTraits, char32UtilsConstexpr) {
  static_assert(StringTraits<char32_t>::isUpper(U'A'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isUpper(U'a'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isUpper(U'.'), "Failed StringTraits");

  static_assert(StringTraits<char32_t>::isLower(U'a'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isLower(U'A'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isLower(U'.'), "Failed StringTraits");

  static_assert(StringTraits<char32_t>::isDigit(U'0'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isDigit(U'a'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isDigit(U'A'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isDigit(U'.'), "Failed StringTraits");

  static_assert(!StringTraits<char32_t>::isLetter(U'.'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isLetter(U'a'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isLetter(U'A'), "Failed StringTraits");

  static_assert(StringTraits<char32_t>::isAlpha(U'A'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isAlpha(U'a'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isAlpha(U'1'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isAlpha(U'.'), "Failed StringTraits");

  static_assert(StringTraits<char32_t>::isVowel(U'a'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isVowel(U'e'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isVowel(U'i'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isVowel(U'o'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isVowel(U'u'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isVowel(U'b'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isVowel(U'.'), "Failed StringTraits");

  static_assert(!StringTraits<char32_t>::isConsonant(U'a'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isConsonant(U'e'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isConsonant(U'i'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isConsonant(U'o'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isConsonant(U'u'), "Failed StringTraits");
  static_assert(StringTraits<char32_t>::isConsonant(U'b'), "Failed StringTraits");
  static_assert(!StringTraits<char32_t>::isConsonant(U'.'), "Failed StringTraits");

  static_assert(StringTraits<char32_t>::lower(U'a') == U'a', "Failed StringTraits");
  static_assert(StringTraits<char32_t>::lower(U'A') == U'a', "Failed StringTraits");
  static_assert(StringTraits<char32_t>::lower(U'.') == U'.', "Failed StringTraits");

  static_assert(StringTraits<char32_t>::upper(U'a') == U'A', "Failed StringTraits");
  static_assert(StringTraits<char32_t>::upper(U'A') == U'A', "Failed StringTraits");
  static_assert(StringTraits<char32_t>::upper(U'.') == U'.', "Failed StringTraits");
}
#endif

#if DCR_SINCECPP20
TEST(MetaStringTraits, charRangeEvaluationChar8) {
  ASSERT_TRUE(charRangeEvaluation(u8'A', u8'Z', 'A', 'Z'));
  ASSERT_TRUE(charRangeEvaluation(u8'a', u8'z', 'a', 'z'));
  ASSERT_TRUE(charRangeEvaluation(u8'0', u8'9', '0', '9'));
}

TEST(MetaStringTraits, char8Utils) {
  ASSERT_TRUE(StringTraits<char8_t>::isUpper(u8'A'));
  ASSERT_TRUE(!StringTraits<char8_t>::isUpper(u8'a'));
  ASSERT_TRUE(!StringTraits<char8_t>::isUpper(u8'.'));
  ASSERT_TRUE(StringTraits<char8_t>::isLower(u8'a'));
  ASSERT_TRUE(!StringTraits<char8_t>::isLower(u8'A'));
  ASSERT_TRUE(!StringTraits<char8_t>::isLower(u8'.'));
  ASSERT_TRUE(StringTraits<char8_t>::isDigit(u8'0'));
  ASSERT_TRUE(!StringTraits<char8_t>::isDigit(u8'a'));
  ASSERT_TRUE(!StringTraits<char8_t>::isDigit(u8'A'));
  ASSERT_TRUE(!StringTraits<char8_t>::isDigit(u8'.'));
  ASSERT_TRUE(!StringTraits<char8_t>::isLetter(u8'.'));
  ASSERT_TRUE(StringTraits<char8_t>::isLetter(u8'a'));
  ASSERT_TRUE(StringTraits<char8_t>::isLetter(u8'A'));
  ASSERT_TRUE(StringTraits<char8_t>::isAlpha(u8'A'));
  ASSERT_TRUE(StringTraits<char8_t>::isAlpha(u8'a'));
  ASSERT_TRUE(StringTraits<char8_t>::isAlpha(u8'1'));
  ASSERT_TRUE(!StringTraits<char8_t>::isAlpha(u8'.'));
  ASSERT_TRUE(StringTraits<char8_t>::isVowel(u8'a'));
  ASSERT_TRUE(StringTraits<char8_t>::isVowel(u8'e'));
  ASSERT_TRUE(StringTraits<char8_t>::isVowel(u8'i'));
  ASSERT_TRUE(StringTraits<char8_t>::isVowel(u8'o'));
  ASSERT_TRUE(StringTraits<char8_t>::isVowel(u8'u'));
  ASSERT_TRUE(!StringTraits<char8_t>::isVowel(u8'b'));
  ASSERT_TRUE(!StringTraits<char8_t>::isVowel(u8'.'));
  ASSERT_TRUE(!StringTraits<char8_t>::isConsonant(u8'a'));
  ASSERT_TRUE(!StringTraits<char8_t>::isConsonant(u8'e'));
  ASSERT_TRUE(!StringTraits<char8_t>::isConsonant(u8'i'));
  ASSERT_TRUE(!StringTraits<char8_t>::isConsonant(u8'o'));
  ASSERT_TRUE(!StringTraits<char8_t>::isConsonant(u8'u'));
  ASSERT_TRUE(StringTraits<char8_t>::isConsonant(u8'b'));
  ASSERT_TRUE(!StringTraits<char8_t>::isConsonant(u8'.'));
  ASSERT_TRUE(StringTraits<char8_t>::lower(u8'a') == u8'a');
  ASSERT_TRUE(StringTraits<char8_t>::lower(u8'A') == u8'a');
  ASSERT_TRUE(StringTraits<char8_t>::lower(u8'.') == u8'.');
  ASSERT_TRUE(StringTraits<char8_t>::upper(u8'a') == u8'A');
  ASSERT_TRUE(StringTraits<char8_t>::upper(u8'A') == u8'A');
  ASSERT_TRUE(StringTraits<char8_t>::upper(u8'.') == u8'.');

  using T = StringTraits<char8_t>;
  ASSERT_EQ(std::u8string(T::emptyString), u8"");
  /// cast to force ODR
  ASSERT_EQ(static_cast<char8_t>(T::nullChar), u8'\0');

  ASSERT_TRUE(validateCharRange(u8'0', u8'9', T::digits));
  ASSERT_TRUE(validateCharRange(u8'a', u8'z', T::lowercaseAlphabet));
  ASSERT_TRUE(validateCharRange(u8'A', u8'Z', T::uppercaseAlphabet));
  ASSERT_EQ(std::u8string(T::vowels), u8"AEIOUaeiou");
  ASSERT_TRUE(validateCharRange(u8'A', u8'z', T::consonants, [](char8_t const c) {
    return !(c >= u8'a' && c <= u8'z'
        || c >= u8'A' && c <= u8'Z')
        || (c == u8'a' || c == u8'e' || c == u8'i' || c == u8'o' || c == u8'u')
        || (c == u8'A' || c == u8'E' || c == u8'I' || c == u8'O' || c == u8'U');
  }));
  ASSERT_EQ(std::u8string(T::whitespace), u8" \t\n\r\f");
  ASSERT_TRUE(validateCharRange<char8_t>(u8'\0', u8'A' - 1, notFn(T::isUpper)));
  ASSERT_TRUE(validateCharRange<char8_t>(u8'A', u8'Z', T::isUpper));
  ASSERT_TRUE(validateCharRange<char8_t>(u8'Z' + 1, 126, notFn(T::isUpper)));

  ASSERT_TRUE(validateCharRange<char8_t>(u8'\0', u8'a' - 1, notFn(T::isLower)));
  ASSERT_TRUE(validateCharRange<char8_t>(u8'a', u8'z', T::isLower));
  ASSERT_TRUE(validateCharRange<char8_t>(u8'z' + 1, 126, notFn(T::isLower)));
}

TEST(MetaStringTraits, char8UtilsConstexpr) {
  static_assert(StringTraits<char8_t>::isUpper(u8'A'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isUpper(u8'a'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isUpper(u8'.'), "Failed StringTraits");

  static_assert(StringTraits<char8_t>::isLower(u8'a'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isLower(u8'A'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isLower(u8'.'), "Failed StringTraits");

  static_assert(StringTraits<char8_t>::isDigit(u8'0'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isDigit(u8'a'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isDigit(u8'A'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isDigit(u8'.'), "Failed StringTraits");

  static_assert(!StringTraits<char8_t>::isLetter(u8'.'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isLetter(u8'a'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isLetter(u8'A'), "Failed StringTraits");

  static_assert(StringTraits<char8_t>::isAlpha(u8'A'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isAlpha(u8'a'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isAlpha(u8'1'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isAlpha(u8'.'), "Failed StringTraits");

  static_assert(StringTraits<char8_t>::isVowel(u8'a'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isVowel(u8'e'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isVowel(u8'i'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isVowel(u8'o'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isVowel(u8'u'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isVowel(u8'b'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isVowel(u8'.'), "Failed StringTraits");

  static_assert(!StringTraits<char8_t>::isConsonant(u8'a'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isConsonant(u8'e'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isConsonant(u8'i'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isConsonant(u8'o'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isConsonant(u8'u'), "Failed StringTraits");
  static_assert(StringTraits<char8_t>::isConsonant(u8'b'), "Failed StringTraits");
  static_assert(!StringTraits<char8_t>::isConsonant(u8'.'), "Failed StringTraits");

  static_assert(StringTraits<char8_t>::lower(u8'a') == u8'a', "Failed StringTraits");
  static_assert(StringTraits<char8_t>::lower(u8'A') == u8'a', "Failed StringTraits");
  static_assert(StringTraits<char8_t>::lower(u8'.') == u8'.', "Failed StringTraits");

  static_assert(StringTraits<char8_t>::upper(u8'a') == u8'A', "Failed StringTraits");
  static_assert(StringTraits<char8_t>::upper(u8'A') == u8'A', "Failed StringTraits");
  static_assert(StringTraits<char8_t>::upper(u8'.') == u8'.', "Failed StringTraits");
}
#endif
