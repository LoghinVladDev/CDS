// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/StringView>
#include <cassert>
#include <iostream>
#include <array>

#include "UnitTest.hpp"
#include "../Shared.hpp"

using namespace cds;

namespace {
using CustomSV = impl::BaseStringView<char, impl::StringUtils<char, impl::StringTraits<char>>>;
}

TEST(StringView, BaseCopyMove) {
  CustomSV const sv1;
  CustomSV const sv2;
  ASSERT_EQ(sv1, sv2);

  CustomSV const sv3("abcd");
  CustomSV const sv4(sv3);
  CustomSV tbm(sv3);
  CustomSV const sv5(std::move(tbm));
  ASSERT_EQ(sv3, sv4);
  ASSERT_EQ(sv4, sv5);
  ASSERT_EQ(sv5, sv3);
}

TEST(StringView, Compare) {
  CustomSV n = nullptr;
  CustomSV a = "a";
  CustomSV b = "b";
  CustomSV c = "c";

  ASSERT_EQ(a, a);
  ASSERT_EQ(b, b);
  ASSERT_EQ(c, c);

  ASSERT_NE(a, n);
  ASSERT_NE(a, b);
  ASSERT_NE(a, c);

  ASSERT_NE(b, n);
  ASSERT_NE(b, a);
  ASSERT_NE(b, c);

  ASSERT_NE(c, n);
  ASSERT_NE(c, a);
  ASSERT_NE(c, b);

  ASSERT_NE(n, a);
  ASSERT_NE(n, b);
  ASSERT_NE(n, c);

  ASSERT_LT(n, a);
  ASSERT_LT(n, b);
  ASSERT_LT(n, b);
  ASSERT_LT(a, b);
  ASSERT_LT(a, c);
  ASSERT_LT(b, c);

  ASSERT_LE(n, n);
  ASSERT_LE(n, a);
  ASSERT_LE(n, b);
  ASSERT_LE(n, b);
  ASSERT_LE(a, a);
  ASSERT_LE(a, b);
  ASSERT_LE(a, c);
  ASSERT_LE(b, b);
  ASSERT_LE(b, c);

  ASSERT_GT(a, n);
  ASSERT_GT(b, n);
  ASSERT_GT(c, n);
  ASSERT_GT(b, a);
  ASSERT_GT(c, a);
  ASSERT_GT(c, b);

  ASSERT_GE(n, n);
  ASSERT_GE(a, n);
  ASSERT_GE(b, n);
  ASSERT_GE(c, n);
  ASSERT_GE(b, a);
  ASSERT_GE(b, b);
  ASSERT_GE(c, a);
  ASSERT_GE(c, b);
  ASSERT_GE(c, c);
}

TEST(StringView, baseMembers) {
  StringView sv1;
  StringView sv2(sv1.data());
  StringView sv3("abcd");
  StringView sv4(sv3.data());

  ASSERT_EQ(sv1.data(), nullptr);
  ASSERT_EQ(sv1.length(), 0u);
  ASSERT_EQ(sv1.size(), 0u);
  ASSERT_TRUE(sv1.empty());
  ASSERT_FALSE(sv1);

  ASSERT_EQ(sv2.data(), nullptr);
  ASSERT_EQ(sv2.length(), 0u);
  ASSERT_EQ(sv2.size(), 0u);
  ASSERT_TRUE(sv2.empty());
  ASSERT_FALSE(sv2);

  ASSERT_EQ(sv3.data(), std::string("abcd"));
  ASSERT_EQ(sv3.length(), 4u);
  ASSERT_EQ(sv3.size(), 4u);
  ASSERT_FALSE(sv3.empty());
  ASSERT_TRUE(sv3);

  ASSERT_EQ(sv4.data(), std::string("abcd"));
  ASSERT_EQ(sv4.length(), 4u);
  ASSERT_EQ(sv4.size(), 4u);
  ASSERT_FALSE(sv4.empty());
  ASSERT_TRUE(sv4);

  sv4.clear();
  ASSERT_EQ(sv4.data(), nullptr);
  ASSERT_EQ(sv4.size(), 0u);
  ASSERT_TRUE(sv4.empty());
  ASSERT_FALSE(sv4);
}

TEST(StringView, assign) {
  CustomSV sv1;
  ASSERT_EQ(sv1.size(), 0u);

  sv1 = "abcd";
  ASSERT_EQ(sv1.size(), 4u);

  auto const* p = "abcde";
  sv1 = p;
  ASSERT_EQ(sv1.size(), 5u);

  char const arr[] = "abcdef";
  sv1 = arr;
  ASSERT_EQ(sv1.size(), 6u);
}

TEST(StringView, iter) {
  StringView sv = "abcd";
  ASSERT_EQ(*begin(sv), 'a');
  ASSERT_EQ(*(begin(sv) + 0), 'a');
  ASSERT_EQ(*(begin(sv) + 1), 'b');
  ASSERT_EQ(*(begin(sv) + 2), 'c');
  ASSERT_EQ(*(begin(sv) + 3), 'd');
  ASSERT_EQ(begin(sv) + 4, end(sv));

  ASSERT_EQ(*cbegin(sv), 'a');
  ASSERT_EQ(*(cbegin(sv) + 0), 'a');
  ASSERT_EQ(*(cbegin(sv) + 1), 'b');
  ASSERT_EQ(*(cbegin(sv) + 2), 'c');
  ASSERT_EQ(*(cbegin(sv) + 3), 'd');
  ASSERT_EQ(cbegin(sv) + 4, cend(sv));

  ASSERT_EQ(*rbegin(sv), 'd');
  ASSERT_EQ(*(rbegin(sv) + 0), 'd');
  ASSERT_EQ(*(rbegin(sv) + 1), 'c');
  ASSERT_EQ(*(rbegin(sv) + 2), 'b');
  ASSERT_EQ(*(rbegin(sv) + 3), 'a');
  ASSERT_EQ(rbegin(sv) + 4, rend(sv));

  ASSERT_EQ(*crbegin(sv), 'd');
  ASSERT_EQ(*(crbegin(sv) + 0), 'd');
  ASSERT_EQ(*(crbegin(sv) + 1), 'c');
  ASSERT_EQ(*(crbegin(sv) + 2), 'b');
  ASSERT_EQ(*(crbegin(sv) + 3), 'a');
  ASSERT_EQ(crbegin(sv) + 4, crend(sv));
}

TEST(StringView, CompareCompatLiteral) {
  StringView sv = "abcd";
  ASSERT_EQ(sv, "abcd");
  ASSERT_NE(sv, "abce");
  ASSERT_GT(sv, "abc");
  ASSERT_GT(sv, "abcc");
  ASSERT_LT(sv, "abd");
  ASSERT_LT(sv, "abce");
  ASSERT_GE(sv, "abc");
  ASSERT_GE(sv, "abcc");
  ASSERT_GE(sv, "abcd");
  ASSERT_LE(sv, "abd");
  ASSERT_LE(sv, "abce");
  ASSERT_LE(sv, "abcd");

  ASSERT_EQ("abcd", sv);
  ASSERT_NE("abce", sv);
  ASSERT_LT("abc", sv);
  ASSERT_LT("abcc", sv);
  ASSERT_GT("abd", sv);
  ASSERT_GT("abce", sv);
  ASSERT_LE("abc", sv);
  ASSERT_LE("abcc", sv);
  ASSERT_LE("abcd", sv);
  ASSERT_GE("abd", sv);
  ASSERT_GE("abce", sv);
  ASSERT_GE("abcd", sv);
}

TEST(StringView, Positionals) {
  StringView sv = "abcd";
  ASSERT_EQ(sv[0], 'a');
  ASSERT_EQ(sv[1], 'b');
  ASSERT_EQ(sv[2], 'c');
  ASSERT_EQ(sv[3], 'd');

  ASSERT_EQ(sv.at(0), 'a');
  ASSERT_EQ(sv.at(1), 'b');
  ASSERT_EQ(sv.at(2), 'c');
  ASSERT_EQ(sv.at(3), 'd');

  ASSERT_EQ(sv.front(), 'a');
  ASSERT_EQ(sv.back(), 'd');
}

TEST(StringView, Sub) {
  StringView sv = "abcd";
  ASSERT_EQ(sv.sub(0), "abcd");
  ASSERT_EQ(sv.sub(1), "bcd");
  ASSERT_EQ(sv.sub(2), "cd");
  ASSERT_EQ(sv.sub(3), "d");

  ASSERT_EQ(sv.sub(0, 4), "abcd");
  ASSERT_EQ(sv.sub(0, 3), "abc");
  ASSERT_EQ(sv.sub(0, 2), "ab");
  ASSERT_EQ(sv.sub(0, 1), "a");

  ASSERT_EQ(sv.sub(1, 4), "bcd");
  ASSERT_EQ(sv.sub(1, 3), "bc");
  ASSERT_EQ(sv.sub(1, 2), "b");

  ASSERT_EQ(sv.sub(2, 4), "cd");
  ASSERT_EQ(sv.sub(2, 3), "c");

  ASSERT_EQ(sv.sub(3, 4), "d");

  ASSERT_EQ(sv.sub(0, 0), "");
  ASSERT_EQ(sv.sub(1, 0), "");
  ASSERT_EQ(sv.sub(1, 1), "");
  ASSERT_EQ(sv.sub(2, 1), "");
  ASSERT_EQ(sv.sub(2, 2), "");
  ASSERT_EQ(sv.sub(3, 2), "");
  ASSERT_EQ(sv.sub(3, 3), "");
  ASSERT_EQ(sv.sub(4, 3), "");

  ASSERT_EQ(sv(0), "abcd");
  ASSERT_EQ(sv(1), "bcd");
  ASSERT_EQ(sv(2), "cd");
  ASSERT_EQ(sv(3), "d");

  ASSERT_EQ(sv(0, 4), "abcd");
  ASSERT_EQ(sv(0, 3), "abc");
  ASSERT_EQ(sv(0, 2), "ab");
  ASSERT_EQ(sv(0, 1), "a");

  ASSERT_EQ(sv(1, 4), "bcd");
  ASSERT_EQ(sv(1, 3), "bc");
  ASSERT_EQ(sv(1, 2), "b");

  ASSERT_EQ(sv(2, 4), "cd");
  ASSERT_EQ(sv(2, 3), "c");

  ASSERT_EQ(sv(3, 4), "d");

  ASSERT_EQ(sv(0, 0), "");
  ASSERT_EQ(sv(1, 0), "");
  ASSERT_EQ(sv(1, 1), "");
  ASSERT_EQ(sv(2, 1), "");
  ASSERT_EQ(sv(2, 2), "");
  ASSERT_EQ(sv(3, 2), "");
  ASSERT_EQ(sv(3, 3), "");
  ASSERT_EQ(sv(4, 3), "");
}

TEST(StringView, contains) {
  StringView sv = "bC";
  ASSERT_FALSE(sv.contains('a'));
  ASSERT_TRUE(sv.contains('b'));
  ASSERT_TRUE(sv.contains('C'));
  ASSERT_FALSE(sv.contains('d'));

  ASSERT_FALSE(sv.contains('a', meta::StringTraits<char>::lower));
  ASSERT_TRUE(sv.contains('b', meta::StringTraits<char>::lower));
  ASSERT_TRUE(sv.contains('c', meta::StringTraits<char>::lower));
  ASSERT_FALSE(sv.contains('d', meta::StringTraits<char>::lower));
}

TEST(StringView, containsString) {
  StringView sv = "abcd";
  ASSERT_TRUE(sv.contains("bc"));
  ASSERT_FALSE(sv.contains("bd"));
}

TEST(StringView, containsOf) {
  StringView sv = "bC";
  ASSERT_FALSE(sv.containsAnyOf("ad"));
  ASSERT_TRUE(sv.containsAnyOf("bc"));
  ASSERT_TRUE(sv.containsAnyOf(StringView("bc")));
  ASSERT_TRUE(sv.containsAnyOf(std::string("bc")));
  ASSERT_TRUE(sv.containsAnyOf("BC", meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyOf(StringView("BC"), meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyOf(std::string("BC"), meta::StringTraits<char>::upper));

  ASSERT_FALSE(sv.containsAnyNotOf("bC"));
  ASSERT_TRUE(sv.containsAnyNotOf("bc"));
  ASSERT_TRUE(sv.containsAnyNotOf("Bc"));
  ASSERT_TRUE(sv.containsAnyNotOf("BC"));
  ASSERT_TRUE(sv.containsAnyNotOf(StringView("bc")));
  ASSERT_TRUE(sv.containsAnyNotOf(std::string("bc")));
  ASSERT_TRUE(sv.containsAnyNotOf("C", meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(StringView("c"), meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(std::string("B"), meta::StringTraits<char>::upper));

  ASSERT_FALSE(sv.containsAllOf("ac"));
  ASSERT_FALSE(sv.containsAllOf("ab"));
  ASSERT_TRUE(sv.containsAllOf("bC"));
  ASSERT_TRUE(sv.containsAllOf(StringView("bC")));
  ASSERT_TRUE(sv.containsAllOf(std::string("bC")));
  ASSERT_TRUE(sv.containsAllOf("BC", meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAllOf(StringView("BC"), meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAllOf(std::string("BC"), meta::StringTraits<char>::upper));

  ASSERT_FALSE(sv.containsNoneOf("bC"));
  ASSERT_FALSE(sv.containsNoneOf("bc"));
  ASSERT_FALSE(sv.containsNoneOf("BC"));
  ASSERT_TRUE(sv.containsNoneOf("ad"));
  ASSERT_TRUE(sv.containsNoneOf("ac"));
  ASSERT_TRUE(sv.containsNoneOf("Bc"));
  ASSERT_TRUE(sv.containsNoneOf(StringView("ad")));
  ASSERT_TRUE(sv.containsNoneOf(std::string("ad")));
  ASSERT_TRUE(sv.containsNoneOf("ad", meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsNoneOf(StringView("ad"), meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsNoneOf(std::string("ad"), meta::StringTraits<char>::upper));
}

TEST(StringView, find) {
  StringView const sv = "abcb";

  auto lRng = sv.find('b');
  auto lIt = lRng.begin();
  ASSERT_EQ(*lIt, 1);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(*lIt, 3);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = StringView("abcb").find('b');
  auto rIt = rRng.begin();
  ASSERT_EQ(*rIt, 1);
  ASSERT_NE(rIt, rRng.end());
  ++rIt;
  ASSERT_EQ(*rIt, 3);
  ASSERT_NE(rIt, rRng.end());
  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

namespace {
template <typename Range, typename P> auto count(Range&& rng, P const& pred) -> int {
  int count = 0;
  for (auto e : cds::forward<Range>(rng)) {
    if (pred(e)) {
      ++count;
    }
  }
  return count;
}
}

TEST(StringView, split) {
  using functional::memFn;

  StringView sv1 = "  abc abc abc  abc abc   ";
  auto eq = [](StringView lhs){
    return [lhs](StringView const& rhs){ return lhs == rhs; };
  };

  auto alwaysTrue = [](StringView const&) { return true; };

  using namespace cds::impl;
  ASSERT_EQ(11, count(sv1.split(' '), alwaysTrue));
  ASSERT_EQ(6, count(sv1.split(' '), memFn(&StringView::empty)));
  ASSERT_EQ(5, count(sv1.split(' '), eq("abc")));

  ASSERT_EQ(2, count(StringView{"ab ab"}.split(' '), alwaysTrue));
  ASSERT_EQ(2, count(StringView{"ab ab"}.split(' '), eq("ab")));

  ASSERT_EQ(0, count(StringView{""}.split(' '), alwaysTrue));

  ASSERT_EQ(3, count(StringView{" ac ac"}.split(' '), alwaysTrue));
  ASSERT_EQ(1, count(StringView{" ac ac"}.split(' '), memFn(&StringView::empty)));
  ASSERT_EQ(2, count(StringView{" ac ac"}.split(' '), eq("ac")));

  ASSERT_EQ(4, count(StringView{"ad ad  "}.split(' '), alwaysTrue));
  ASSERT_EQ(2, count(StringView{"ad ad  "}.split(' '), memFn(&StringView::empty)));
  ASSERT_EQ(2, count(StringView{"ad ad  "}.split(' '), eq("ad")));

  auto e = memFn(&StringView::empty);
  ASSERT_EQ(4, count(StringView{"ae   ae"}.split(' '), alwaysTrue));
  ASSERT_EQ(2, count(StringView{"ae   ae"}.split(' '), e));
  ASSERT_EQ(2, count(StringView{"ae   ae"}.split(' '), eq("ae")));

  auto r = StringView{"a b"}.split(' ');
  ASSERT_EQ(2, count(r, alwaysTrue));
  ASSERT_EQ(1, count(r, eq("a")));
  ASSERT_EQ(1, count(r, eq("b")));

  ASSERT_EQ(10, count(StringView{"ae ; ae;ae ae; ae ;"}.split(std::vector<char>{' ', ';'}), alwaysTrue));
  ASSERT_EQ(5, count(StringView{"ae ; ae;ae ae; ae ;"}.split(std::vector<char>{' ', ';'}), e));
  ASSERT_EQ(5, count(StringView{"ae ; ae;ae ae; ae ;"}.split(std::vector<char>{' ', ';'}), eq("ae")));

  std::initializer_list<char> sep2 = {' ', ';'};
  ASSERT_EQ(10, count(StringView{"ae ; ae;ae ae; ae ;"}.split(sep2), alwaysTrue));
  ASSERT_EQ(5, count(StringView{"ae ; ae;ae ae; ae ;"}.split(sep2), e));
  ASSERT_EQ(5, count(StringView{"ae ; ae;ae ae; ae ;"}.split(sep2), eq("ae")));

  ASSERT_EQ(1, count(StringView{"  ab   ab   ab  "}.split(' ', 0), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"  ab   ab   ab  "}.split(' ', 0), eq("  ab   ab   ab  ")));

  ASSERT_EQ(2, count(StringView{"  ab   ab   ab  "}.split(' ', 1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"  ab   ab   ab  "}.split(' ', 1), e));
  ASSERT_EQ(1, count(StringView{"  ab   ab   ab  "}.split(' ', 1), eq(" ab   ab   ab  ")));

  ASSERT_EQ(3, count(StringView{"ab  ab ab  ab"}.split("  "), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ab  ab ab  ab"}.split("  "), eq("ab ab")));
  ASSERT_EQ(2, count(StringView{"ab  ab ab  ab"}.split("  "), eq("ab")));

  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split("  ",  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split("  ",  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split("  ",  1), eq("ac ac   ac  ")));

  char const sep3[] = "  ";
  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(sep3,  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep3,  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep3,  1), eq("ac ac   ac  ")));

  auto const* sep4 = "  ";
  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(sep4,  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep4,  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep4,  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(static_cast<char const*>(sep4),  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(static_cast<char const*>(sep4),  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(static_cast<char const*>(sep4),  1), eq("ac ac   ac  ")));

  char sep5[] = "  ";
  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(sep5,  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep5,  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep5,  1), eq("ac ac   ac  ")));

  char* sep6 = sep5;
  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(sep6,  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep6,  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep6,  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(static_cast<char*>(sep6),  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(static_cast<char*>(sep6),  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(static_cast<char*>(sep6),  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(StringView{"  "},  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(StringView{"  "},  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(StringView{"  "},  1), eq("ac ac   ac  ")));

  StringView sep7{"  "};
  ASSERT_EQ(2, count(StringView{"ac  ac ac   ac  "}.split(sep7,  1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep7,  1), eq("ac")));
  ASSERT_EQ(1, count(StringView{"ac  ac ac   ac  "}.split(sep7,  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(StringView{"ac  ac"}.split(std::string{"  "}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(2, count(StringView{"ac  ac"}.split(std::string_view{"  "}), alwaysTrue));
#endif

  StringView str1{"abc  abc"};
  ASSERT_EQ(2, count(str1.split("  "), alwaysTrue));
  ASSERT_EQ(2, count(str1.split("  "), eq("abc")));

  ASSERT_EQ(1, count(str1.split("  ", 0), alwaysTrue));
  ASSERT_EQ(1, count(str1.split("  ", 0), eq("abc  abc")));

  ASSERT_EQ(2, count(str1.split(' ', 1), alwaysTrue));
  ASSERT_EQ(1, count(str1.split(' ', 1), eq("abc")));
  ASSERT_EQ(1, count(str1.split(' ', 1), eq(" abc")));

  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}), eq("abc")));
  ASSERT_EQ(2, count(StringView{"abc  abc1__abc"}.split(std::vector<StringView>{"  ", "__"}), eq("abc")));
  ASSERT_EQ(1, count(StringView{"abc  abc1__abc"}.split(std::vector<StringView>{"  ", "__"}), eq("abc1")));

  StringView str2{"abc  abc__abc"};
  ASSERT_EQ(3, count(str2.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(std::vector<StringView>{"  ", "__"}), eq("abc")));

  std::vector<StringView> sepsStrs{"  ", "__"};
  ASSERT_EQ(3, count(str2.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(sepsStrs), eq("abc")));

  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(sepsStrs), eq("abc")));

  ASSERT_EQ(4, count(StringView{"  abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"  abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(StringView{"  abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(4, count(StringView{"abc  abc__abc__"}.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"abc  abc__abc__"}.split(std::vector<StringView>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(StringView{"abc  abc__abc__"}.split(std::vector<StringView>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(4, count(StringView{"abc  abc  __abc"}.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"abc  abc  __abc"}.split(std::vector<StringView>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(StringView{"abc  abc  __abc"}.split(std::vector<StringView>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(6, count(StringView{"__abc  abc  __abc  "}.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(StringView{"__abc  abc  __abc  "}.split(std::vector<StringView>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(StringView{"__abc  abc  __abc  "}.split(std::vector<StringView>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(1, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}, 0), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}, 0), eq("abc  abc__abc")));

  ASSERT_EQ(2, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}, 1), alwaysTrue));
  ASSERT_EQ(1, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}, 1), eq("abc")));
  ASSERT_EQ(1, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}, 1), eq("abc__abc")));

  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(std::vector<char const*>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(std::vector<std::string>{"  ", "__"}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(3, count(StringView{"abc  abc__abc"}.split(std::vector<std::string_view>{"  ", "__"}), alwaysTrue));
#endif
}

TEST(StringView, ostream) {
  std::stringstream oss;
  StringView sv{" abc "};
  oss << sv;
  ASSERT_EQ(oss.str(), " abc ");
}

TEST(StringView, findClient) {
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.find('b'), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.find('d'), std::vector<int>{}));

  StringView sv {"test test test"};
  ASSERT_TRUE(testing::citeq(sv.find("test"), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(StringView {"testtesttest"}.find("test"), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(StringView {"test test test"}.find("test"), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(StringView {"test test test "}.find("test"), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(StringView {"test test tes"}.find("test"), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(StringView {" test test test"}.find("test"), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(StringView {"est test test"}.find("test"), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(StringView {" test test test "}.find("test"), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(StringView {" test test tes"}.find("test"), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(StringView {"est test test "}.find("test"), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(StringView {"est test tes"}.find("test"), std::vector<int> {4}));
}

TEST(StringView, findProjectionClient) {
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.find('B', toupper), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.find('D', toupper), std::vector<int>{}));

  StringView sv {"test test test"};
  ASSERT_TRUE(testing::citeq(sv.find("TEST", toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(StringView {"testtesttest"}.find("TEST", toupper), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(StringView {"test test test"}.find("TEST", toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(StringView {"test test test "}.find("TEST", toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(StringView {"test test tes"}.find("TEST", toupper), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(StringView {" test test test"}.find("TEST", toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(StringView {"est test test"}.find("TEST", toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(StringView {" test test test "}.find("TEST", toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(StringView {" test test tes"}.find("TEST", toupper), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(StringView {"est test test "}.find("TEST", toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(StringView {"est test tes"}.find("TEST", toupper), std::vector<int> {4}));
}

TEST(StringView, findFirstClient) {
  ASSERT_EQ(StringView{"abcb"}.findFirst('b'), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirst('d'), StringView::npos);
  ASSERT_EQ(StringView{"abcb"}.findFirst("bc"), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirst("bd"), StringView::npos);
}

TEST(StringView, findProjectionFirstClient) {
  ASSERT_EQ(StringView{"abcb"}.findFirst('B', toupper), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirst('D', toupper), StringView::npos);
  ASSERT_EQ(StringView{"abcb"}.findFirst("BC", toupper), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirst("BD", toupper), StringView::npos);
}

TEST(StringView, findLastClient) {
  ASSERT_EQ(StringView{"abcb"}.findLast('b'), 3);
  ASSERT_EQ(StringView{"abcb"}.findLast('d'), StringView::npos);
  ASSERT_EQ(StringView{"abcbc"}.findLast("bc"), 3);
  ASSERT_EQ(StringView{"abcb"}.findLast("bd"), StringView::npos);
}

TEST(StringView, findProjectionLastClient) {
  ASSERT_EQ(StringView{"abcb"}.findLast('B', toupper), 3);
  ASSERT_EQ(StringView{"abcb"}.findLast('D', toupper), StringView::npos);
  ASSERT_EQ(StringView{"abcbc"}.findLast("BC", toupper), 3);
  ASSERT_EQ(StringView{"abcb"}.findLast("BD", toupper), StringView::npos);
}

TEST(StringView, findOfClient) {
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.findOf(std::vector<char>{'a', 'c'}), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.findOf(std::vector<char>{'d'}), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.findOf("ac"), std::vector<int>{0, 2}));

  StringView sv1 {"abc bcd cde def"};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<StringView>{"bc", "bcd", "def"}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(StringView{"abc bcd cde def"}.findOf(std::vector<StringView>{"bc", "bcd", "def"}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(StringView{"bc bcd cde def"}.findOf(std::vector<StringView>{"bc", "bcd", "def"}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(StringView{"c bcd cde def"}.findOf(std::vector<StringView>{"bc", "bcd", "def"}), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(StringView{"bc bcd cde def "}.findOf(std::vector<StringView>{"bc", "bcd", "def"}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(StringView{"bc bcd cde de"}.findOf(std::vector<StringView>{"bc", "bcd", "def"}), std::vector<int> {0, 3}));
}

TEST(StringView, findProjectedOfClient) {
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.findOf(std::vector<char>{'A', 'C'}, toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.findOf(std::vector<char>{'D'}, toupper), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(StringView{"abcb"}.findOf("AC", toupper), std::vector<int>{0, 2}));

  StringView sv1 {"abc bcd cde def"};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<StringView>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(StringView{"abc bcd cde def"}.findOf(std::vector<StringView>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(StringView{"bc bcd cde def"}.findOf(std::vector<StringView>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(StringView{"c bcd cde def"}.findOf(std::vector<StringView>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(StringView{"bc bcd cde def "}.findOf(std::vector<StringView>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(StringView{"bc bcd cde de"}.findOf(std::vector<StringView>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {0, 3}));
}

TEST(StringView, findFirstOfClient) {
  ASSERT_EQ(StringView{"abcb"}.findFirstOf(std::vector<char>{'c', 'b'}), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirstOf("cb"), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirstOf(std::vector<char>{'d'}), StringView::npos);
  ASSERT_EQ(StringView{"abcb"}.findFirstOf(std::vector<char>{}), StringView::npos);

  StringView sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findFirstOf(std::vector<StringView>{"cde", "bcd", "def"}), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<StringView>{"ggg"}), StringView::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<StringView>{}), StringView::npos);
}

TEST(StringView, findProjectedFirstOfClient) {
  ASSERT_EQ(StringView{"abcb"}.findFirstOf(std::vector<char>{'C', 'B'}, toupper), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirstOf("CB", toupper), 1);
  ASSERT_EQ(StringView{"abcb"}.findFirstOf(std::vector<char>{'D'}, toupper), StringView::npos);
  ASSERT_EQ(StringView{"abcb"}.findFirstOf(std::vector<char>{}, toupper), StringView::npos);

  StringView sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findFirstOf(std::vector<StringView>{"CDE", "BCD", "DEF"}, toupper), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<StringView>{"GGG"}, toupper), StringView::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<StringView>{}, toupper), StringView::npos);
}

TEST(StringView, findLastOfClient) {
  ASSERT_EQ(StringView{"abcb"}.findLastOf(std::vector<char>{'c', 'b'}), 3);
  ASSERT_EQ(StringView{"abcbc"}.findLastOf("cb"), 4);
  ASSERT_EQ(StringView{"abcb"}.findLastOf(std::vector<char>{'d'}), StringView::npos);
  ASSERT_EQ(StringView{"abcb"}.findLastOf(std::vector<char>{}), StringView::npos);

  StringView sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findLastOf(std::vector<StringView>{"cde", "bcd", "def"}), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<StringView>{"ggg"}), StringView::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<StringView>{}), StringView::npos);
}

TEST(StringView, findProjectedLastOfClient) {
  ASSERT_EQ(StringView{"abcb"}.findLastOf(std::vector<char>{'C', 'B'}, toupper), 3);
  ASSERT_EQ(StringView{"abcbc"}.findLastOf("CB", toupper), 4);
  ASSERT_EQ(StringView{"abcb"}.findLastOf(std::vector<char>{'D'}, toupper), StringView::npos);
  ASSERT_EQ(StringView{"abcb"}.findLastOf(std::vector<char>{}, toupper), StringView::npos);

  StringView sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findLastOf(std::vector<StringView>{"CDE", "BCD", "DEF"}, toupper), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<StringView>{"GGG"}, toupper), StringView::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<StringView>{}, toupper), StringView::npos);
}

TEST(StringView, findNotOfClient) {
  ASSERT_TRUE(testing::citeq(StringView{"abc"}.findNotOf("b"), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(StringView{"abc"}.findNotOf(std::vector<int>{'b'}), std::vector<int>{0, 2}));
}

TEST(StringView, findProjectedNotOfClient) {
  ASSERT_TRUE(testing::citeq(StringView{"abc"}.findNotOf("B", toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(StringView{"abc"}.findNotOf(std::vector<int>{'B'}, toupper), std::vector<int>{0, 2}));
}

TEST(StringView, findFirstNotOfClient) {
  ASSERT_EQ(StringView{"abc"}.findFirstNotOf("a"), 1);
  ASSERT_EQ(StringView{"abc"}.findFirstNotOf("abc"), StringView::npos);
}

TEST(StringView, findProjectedFirstNotOfClient) {
  ASSERT_EQ(StringView{"abc"}.findFirstNotOf("A", toupper), 1);
  ASSERT_EQ(StringView{"abc"}.findFirstNotOf("ABC", toupper), StringView::npos);
}

TEST(StringView, findLastNotOfClient) {
  ASSERT_EQ(StringView{"abca"}.findLastNotOf("a"), 2);
  ASSERT_EQ(StringView{"abc"}.findLastNotOf("abc"), StringView::npos);
}

TEST(StringView, findProjectedLastNotOfClient) {
  ASSERT_EQ(StringView{"abca"}.findLastNotOf("A", toupper), 2);
  ASSERT_EQ(StringView{"abc"}.findLastNotOf("ABC", toupper), StringView::npos);
}

TEST(StringView, findExtraCov) {
  auto r1 = StringView{"abc"}.find("bc");
  auto b = r1.begin();
  auto b1 = std::move(b);
  auto e1 = r1.end();

  b1 = b1;
  b1 = std::move(b1);
  auto b2 = r1.begin();
  b2 = std::move(b1);

  /// By design
  ASSERT_NE(b2, r1.begin());
  ASSERT_FALSE(b2 == r1.begin());

  (void) e1;
}

TEST(StringView, findExtraCov2) {
  auto r1 = StringView{"abc"}.find("BC", toupper);
  auto b = r1.begin();
  auto b1 = std::move(b);
  auto e1 = r1.end();

  b1 = b1;
  b1 = std::move(b1);
  auto b2 = r1.begin();
  b2 = std::move(b1);

  /// By design
  ASSERT_NE(b2, r1.begin());
  ASSERT_FALSE(b2 == r1.begin());

  (void) e1;
}

TEST(StringView, loremIpsumFind) {
  auto r = StringView{R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.)"}
  .findOf(std::vector<StringView>{"Lorem", "ipsum", "dolor", "sit", "amet", "consectetur",
    "adipiscing", "elit",
    "sed", "do", "eiusmod", "tempor", "incididunt", "ut", "labore", "et", "dolore","magna", "aliqua",
"Ut", "enim", "ad", "minim", "veniam", "quis", "nostrud", "exercitation", "ullamco", "laboris",
"nisi", "ut", "aliquip", "ex", "ea", "commodo", "consequat"," Duis", "aute", "irure", "dolor", "in",
"reprehenderit", "in", "voluptate", "velit", "esse", "cillum", "dolore", "eu", "fugiat", "nulla",
    "pariatur",
"Excepteur", "sint", "occaecat", "cupidatat", "non", "proident",
"sunt", "in", "culpa", "qui", "officia", "deserunt", "mollit", "anim", "id", "est", "laborum"});

  for (auto it = r.begin(); it != r.end(); ++it) {
    // do nothing, loop check
    ASSERT_GE(*it, 0);
  }
}

TEST(StringView, functional) {
  StringView const sv{"abcd"};

  int count = 0;
  sv.forEach([&count](char const c) {
    (void) c;
    ++count;
  });

  ASSERT_EQ(count, 4);

  using T = meta::StringTraits<char>;
  ASSERT_TRUE(sv.some(1, T::isVowel));
  ASSERT_TRUE(sv.atLeast(1, T::isVowel));
  ASSERT_TRUE(sv.atMost(1, T::isVowel));
  ASSERT_TRUE(sv.moreThan(0, T::isVowel));
  ASSERT_TRUE(sv.lessThan(2, T::isVowel));
  ASSERT_EQ(sv.count(T::isVowel), 1);
  ASSERT_TRUE(sv.any(T::isVowel));
  ASSERT_FALSE(sv.all(T::isVowel));
  ASSERT_TRUE(sv.all(T::isLetter));
  ASSERT_TRUE(sv.none(T::isDigit));
  ASSERT_FALSE(sv.none(T::isVowel));
}

TEST(StringView, containsAllocation) {
  StringView const sv {"abcd"};
  ASSERT_TRUE(sv.contains("bc", Allocator<Size>()));
  ASSERT_TRUE(sv.contains("BC", toupper, Allocator<Size>()));
}

TEST(StringView, startsEndsWith) {
  StringView const sv {"abcd"};

  ASSERT_TRUE(sv.startsWith('a'));
  ASSERT_FALSE(sv.startsWith('b'));
  ASSERT_TRUE(sv.endsWith('d'));
  ASSERT_FALSE(sv.endsWith('c'));

  ASSERT_TRUE(sv.startsWith("ab"));
  ASSERT_FALSE(sv.startsWith("bb"));
  ASSERT_TRUE(sv.startsWith(""));
  ASSERT_FALSE(sv.startsWith("abcde"));
  ASSERT_TRUE(sv.endsWith("cd"));
  ASSERT_FALSE(sv.endsWith("dd"));
  ASSERT_TRUE(sv.endsWith(""));
  ASSERT_FALSE(sv.endsWith("aabcd"));
}

TEST(StringView, literal) {
  using namespace cds::literals;
  ASSERT_EQ("abcd"_sv, "abcd");
  ASSERT_EQ(L"abcd"_sv, L"abcd");
}

TEST(StringView, constructions) {
  StringView const sv1 = "abcd";
  char const buf[] = "abcd";
  StringView const sv2 = buf;
  std::string str = "abcd";
  StringView const sv3 = str;
  ASSERT_EQ(sv1, sv2);
  ASSERT_EQ(sv1, sv3);
}

TEST(StringView, assignments) {
  StringView sv;
  sv = "abcd";
  ASSERT_EQ(sv, "abcd");
  char const buf[] = "abcd";
  sv = buf;
  ASSERT_EQ(sv, "abcd");
  std::string const sv3 = "abcd";
  sv = sv3;
  ASSERT_EQ(sv, "abcd");
}

#ifdef DCR_SINCECPP14
TEST(StringView, cpp14Constexpr) {
  static_assert(*StringView{"ab ab"}.split(' ').begin() == "ab", "constexpr failed");
}
#endif

#ifdef DCR_SINCECPP17

TEST(StringView, constructions17) {
  std::string_view strv = "abcd";
  StringView const sv4 = strv;
  ASSERT_EQ(sv4, "abcd");
}

TEST(StringView, assignments17) {
  StringView sv;
  std::string_view sv4 = "abcd";
  sv = sv4;
  ASSERT_EQ(sv, "abcd");
}
#endif

#ifdef DCR_SINCECPP20
TEST(StringView, Spaceship) {
  char const a1[] = "abcd";
  char const a2[] = "abcd";
  assert(+a1 != +a2 && "Something weird");
  StringView sv1 = a1;
  StringView sv2 = a2;
  StringView sv3 = "abc";
  StringView sv4 = "abcde";

  ASSERT_EQ(sv1 <=> sv1, std::strong_ordering::equivalent);
  ASSERT_EQ(sv1 <=> sv2, std::strong_ordering::equal);
  ASSERT_EQ(sv1 <=> sv3, std::strong_ordering::greater);
  ASSERT_EQ(sv1 <=> sv4, std::strong_ordering::less);
}

TEST(StringView, SpaceshipCompatLiteral) {
  StringView sv1 = "abc";
  ASSERT_EQ(sv1 <=> "abc", std::strong_ordering::equal);
  ASSERT_EQ(sv1 <=> "abcd", std::strong_ordering::less);
  ASSERT_EQ(sv1 <=> "ab", std::strong_ordering::greater);
  ASSERT_EQ("abc" <=> sv1, std::strong_ordering::equal);
  ASSERT_EQ("abcd" <=> sv1, std::strong_ordering::greater);
  ASSERT_EQ("ab" <=> sv1, std::strong_ordering::less);
}

namespace {
consteval auto evaluate() {
  StringView sv{"ab  ab1__ab"};
  std::array<StringView, 2> svr{"  ", "__"};
  auto r = sv.split(svr);
  auto it = r.begin();
  ++it;
  auto const b = *it == "ab1";
  return b;
}
}

TEST(StringView, cpp20Constexpr) {
  static_assert(*StringView{"ab  ab"}.split("  ").begin() == "ab", "constexpr failed");
  static_assert(evaluate(), "constexpr failed");
}
#endif