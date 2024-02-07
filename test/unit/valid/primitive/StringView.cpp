// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "cds/StringView"
#include <cassert>
#include <iostream>

#include "UnitTest.hpp"

using namespace cds;

namespace {
int ptrCalls = 0;
int refCalls = 0;
struct CustomUtils : cds::impl::StringUtils<char, cds::meta::StringTraits<char>> {
public:
  template<typename T, meta::EnableIf<meta::Not<meta::IsBoundedArray<meta::RemoveCVRef<T>>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) static Size length(T &&l) {
    ++ptrCalls;
    return StringUtils::length(cds::forward<T>(l));
  }

  template<typename T, meta::EnableIf<meta::IsBoundedArray<meta::RemoveCVRef<T>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) static Size length(T &&l) {
    ++refCalls;
    return StringUtils::length(cds::forward<T>(l));
  }
};

class CustomSV : public cds::impl::BaseStringView<char, CustomUtils> {
  using cds::impl::BaseStringView<char, CustomUtils>::BaseStringView;
};
}

TEST(StringView, FromLiteralEnsureRefUsage) {
  refCalls = 0;
  ptrCalls = 0;
  CustomSV sv1("test");
  auto const* buf = "test2";
  char const buf2[] = "test3";
  CustomSV sv2(buf);
  CustomSV sv3(buf2);

  ASSERT_EQ(refCalls, 2);
  ASSERT_EQ(ptrCalls, 1);
}

TEST(StringView, BaseCopyMove) {
  refCalls = 0;
  ptrCalls = 0;
  CustomSV sv1;
  CustomSV sv2;
  ASSERT_EQ(sv1, sv2);

  CustomSV sv3("abcd");
  CustomSV sv4(sv3);
  CustomSV tbm(sv3);
  CustomSV sv5(std::move(tbm));
  ASSERT_EQ(sv3, sv4);
  ASSERT_EQ(sv4, sv5);
  ASSERT_EQ(sv5, sv3);

  ASSERT_EQ(ptrCalls, 0);
  ASSERT_EQ(refCalls, 1);
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
  refCalls = 0;
  ptrCalls = 0;
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

  ASSERT_EQ(refCalls, 2u);
  ASSERT_EQ(ptrCalls, 1u);
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
  StringView sv = "abcb";

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

  char const* sep4 = "  ";
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

  StringView str1{"abc  abc"};
  ASSERT_EQ(2, count(str1.split("  "), alwaysTrue));
  ASSERT_EQ(2, count(str1.split("  "), eq("abc")));

  ASSERT_EQ(1, count(str1.split("  ", 0), alwaysTrue));
  ASSERT_EQ(1, count(str1.split("  ", 0), eq("abc  abc")));

  ASSERT_EQ(2, count(str1.split(' ', 1), alwaysTrue));
  ASSERT_EQ(1, count(str1.split(' ', 1), eq("abc")));
  ASSERT_EQ(1, count(str1.split(' ', 1), eq(" abc")));
}

TEST(StringView, ostream) {
  std::stringstream oss;
  StringView sv{" abc "};
  oss << sv;
  ASSERT_EQ(oss.str(), " abc ");
}

#ifdef DCR_SINCECPP14
TEST(StringView, cpp14Constexpr) {
  static_assert(*StringView{"ab ab"}.split(' ').begin() == "ab", "constexpr failed");
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

TEST(StringView, cpp20Constexpr) {
  static_assert(*StringView{"ab  ab"}.split("  ").begin() == "ab", "constexpr failed");
}
#endif
