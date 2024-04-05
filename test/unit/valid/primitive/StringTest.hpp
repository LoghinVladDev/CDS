#include "../TrackerAllocator.hpp"

TEST(STRING_TEST_ID, construction) {
  String a = "abc";
  char const buf[] = "abc";
  String b = buf;
  String c = std::string("abc");
  String d = StringView("abc");

  String e = d;
  String f = cds::move(c);
  ASSERT_EQ(a, "abc");
  ASSERT_EQ(b, "abc");
  ASSERT_EQ(d, "abc");
  ASSERT_EQ(e, "abc");
  ASSERT_EQ(f, "abc");
}

TEST(STRING_TEST_ID, nonSbo) {
  String a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  String b = a;
  String c = cds::move(b);

  ASSERT_EQ(a, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  ASSERT_EQ(c, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}

TEST(STRING_TEST_ID, repeatedCopies) {
  StringView src = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  StringView src2 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  String a = src;
  ASSERT_EQ(a, src);
  a = src;
  ASSERT_EQ(a, src);
  a = src;
  ASSERT_EQ(a, src);
  a = src;
  ASSERT_EQ(a, src);

  a = "abc";
  ASSERT_EQ(a, "abc");

  a = src;
  ASSERT_EQ(a, src);

  a = src2;
  ASSERT_EQ(a, src2);
  a = src;
  ASSERT_EQ(a, src);
  a = src2;
  ASSERT_EQ(a, src2);
  a = "abc";
  ASSERT_EQ(a, "abc");
  a = src2;
  ASSERT_EQ(a, src2);
}

TEST(STRING_TEST_ID, Compare) {
  String n = nullptr;
  String a = "a";
  String b = "b";
  String c = "c";

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

TEST(STRING_TEST_ID, baseMembers) {
  String sv1;
  String sv2(sv1.data());
  String sv3("abcd");
  String sv4(sv3.data());

  ASSERT_NE(sv1.data(), nullptr);
  ASSERT_EQ(sv1.length(), 0u);
  ASSERT_EQ(sv1.size(), 0u);
  ASSERT_TRUE(sv1.empty());
  ASSERT_FALSE(sv1);

  ASSERT_NE(sv2.data(), nullptr);
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
  // ASSERT_EQ(sv4.data(), nullptr);
  ASSERT_EQ(sv4.size(), 0u);
  ASSERT_TRUE(sv4.empty());
  ASSERT_FALSE(sv4);
}

TEST(STRING_TEST_ID, iter) {
  String sv = "abcd";
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

TEST(STRING_TEST_ID, CompareCompatLiteral) {
  String sv = "abcd";
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

TEST(STRING_TEST_ID, Positionals) {
  String sv = "abcd";
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

TEST(STRING_TEST_ID, Sub) {
  String sv = "abcd";
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

TEST(STRING_TEST_ID, clearAndDestruct) {
  String a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  a.clear();
}

TEST(STRING_TEST_ID, contains) {
  String sv = "bC";
  ASSERT_FALSE(sv.contains('a'));
  ASSERT_TRUE(sv.contains('b'));
  ASSERT_TRUE(sv.contains('C'));
  ASSERT_FALSE(sv.contains('d'));

  ASSERT_FALSE(sv.contains('a', cds::meta::StringTraits<char>::lower));
  ASSERT_TRUE(sv.contains('b', cds::meta::StringTraits<char>::lower));
  ASSERT_TRUE(sv.contains('c', cds::meta::StringTraits<char>::lower));
  ASSERT_FALSE(sv.contains('d', cds::meta::StringTraits<char>::lower));
}

TEST(STRING_TEST_ID, containsString) {
  String sv = "abcd";
  ASSERT_TRUE(sv.contains("bc", testing::TrackerAllocator<cds::Size>()));
  ASSERT_FALSE(sv.contains("bd", testing::TrackerAllocator<cds::Size>()));
}

TEST(STRING_TEST_ID, containsOf) {
  String sv = "bC";
  ASSERT_FALSE(sv.containsAnyOf("ad"));
  ASSERT_TRUE(sv.containsAnyOf("bc"));
  ASSERT_TRUE(sv.containsAnyOf(StringView("bc")));
  ASSERT_TRUE(sv.containsAnyOf(String("bc")));
  ASSERT_TRUE(sv.containsAnyOf(std::string("bc")));
  ASSERT_TRUE(sv.containsAnyOf("BC", cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyOf(StringView("BC"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyOf(String("BC"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyOf(std::string("BC"), cds::meta::StringTraits<char>::upper));

  ASSERT_FALSE(sv.containsAnyNotOf("bC"));
  ASSERT_TRUE(sv.containsAnyNotOf("bc"));
  ASSERT_TRUE(sv.containsAnyNotOf("Bc"));
  ASSERT_TRUE(sv.containsAnyNotOf("BC"));
  ASSERT_TRUE(sv.containsAnyNotOf(StringView("bc")));
  ASSERT_TRUE(sv.containsAnyNotOf(String("bc")));
  ASSERT_TRUE(sv.containsAnyNotOf(std::string("bc")));
  ASSERT_TRUE(sv.containsAnyNotOf("C", cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(StringView("c"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(String("c"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(std::string("B"), cds::meta::StringTraits<char>::upper));

  ASSERT_FALSE(sv.containsAllOf("ac"));
  ASSERT_FALSE(sv.containsAllOf("ab"));
  ASSERT_TRUE(sv.containsAllOf("bC"));
  ASSERT_TRUE(sv.containsAllOf(StringView("bC")));
  ASSERT_TRUE(sv.containsAllOf(String("bC")));
  ASSERT_TRUE(sv.containsAllOf(std::string("bC")));
  ASSERT_TRUE(sv.containsAllOf("BC", cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAllOf(StringView("BC"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAllOf(String("BC"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsAllOf(std::string("BC"), cds::meta::StringTraits<char>::upper));

  ASSERT_FALSE(sv.containsNoneOf("bC"));
  ASSERT_FALSE(sv.containsNoneOf("bc"));
  ASSERT_FALSE(sv.containsNoneOf("BC"));
  ASSERT_TRUE(sv.containsNoneOf("ad"));
  ASSERT_TRUE(sv.containsNoneOf("ac"));
  ASSERT_TRUE(sv.containsNoneOf("Bc"));
  ASSERT_TRUE(sv.containsNoneOf(StringView("ad")));
  ASSERT_TRUE(sv.containsNoneOf(String("ad")));
  ASSERT_TRUE(sv.containsNoneOf(std::string("ad")));
  ASSERT_TRUE(sv.containsNoneOf("ad", cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsNoneOf(StringView("ad"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsNoneOf(String("ad"), cds::meta::StringTraits<char>::upper));
  ASSERT_TRUE(sv.containsNoneOf(std::string("ad"), cds::meta::StringTraits<char>::upper));
}

TEST(STRING_TEST_ID, find) {
  String const sv = "abcb";

  auto lRng = sv.find('b');
  auto lIt = lRng.begin();
  ASSERT_EQ(*lIt, 1);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(*lIt, 3);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = String("abcb").find('b');
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

TEST(STRING_TEST_ID, split) {
  using cds::functional::memFn;

  String sv1 = "  abc abc abc  abc abc   ";
  auto eq = [](StringView lhs){
    return [lhs](StringView const& rhs){ return lhs == rhs; };
  };

  auto alwaysTrue = [](StringView const&) { return true; };

  using namespace cds::impl;
  ASSERT_EQ(11, count(sv1.split(' '), alwaysTrue));
  ASSERT_EQ(6, count(sv1.split(' '), memFn(&StringView::empty)));
  ASSERT_EQ(5, count(sv1.split(' '), eq("abc")));

  ASSERT_EQ(2, count(String{"ab ab"}.split(' '), alwaysTrue));
  ASSERT_EQ(2, count(String{"ab ab"}.split(' '), eq("ab")));

  ASSERT_EQ(0, count(String{""}.split(' '), alwaysTrue));

  ASSERT_EQ(3, count(String{" ac ac"}.split(' '), alwaysTrue));
  ASSERT_EQ(1, count(String{" ac ac"}.split(' '), memFn(&StringView::empty)));
  ASSERT_EQ(2, count(String{" ac ac"}.split(' '), eq("ac")));

  ASSERT_EQ(4, count(String{"ad ad  "}.split(' '), alwaysTrue));
  ASSERT_EQ(2, count(String{"ad ad  "}.split(' '), memFn(&StringView::empty)));
  ASSERT_EQ(2, count(String{"ad ad  "}.split(' '), eq("ad")));

  auto e = memFn(&StringView::empty);
  ASSERT_EQ(4, count(String{"ae   ae"}.split(' '), alwaysTrue));
  ASSERT_EQ(2, count(String{"ae   ae"}.split(' '), e));
  ASSERT_EQ(2, count(String{"ae   ae"}.split(' '), eq("ae")));

  auto r = String{"a b"}.split(' ');
  ASSERT_EQ(2, count(r, alwaysTrue));
  ASSERT_EQ(1, count(r, eq("a")));
  ASSERT_EQ(1, count(r, eq("b")));

  ASSERT_EQ(10, count(String{"ae ; ae;ae ae; ae ;"}.split(std::vector<char>{' ', ';'}), alwaysTrue));
  ASSERT_EQ(5, count(String{"ae ; ae;ae ae; ae ;"}.split(std::vector<char>{' ', ';'}), e));
  ASSERT_EQ(5, count(String{"ae ; ae;ae ae; ae ;"}.split(std::vector<char>{' ', ';'}), eq("ae")));

  std::initializer_list<char> sep2 = {' ', ';'};
  ASSERT_EQ(10, count(String{"ae ; ae;ae ae; ae ;"}.split(sep2), alwaysTrue));
  ASSERT_EQ(5, count(String{"ae ; ae;ae ae; ae ;"}.split(sep2), e));
  ASSERT_EQ(5, count(String{"ae ; ae;ae ae; ae ;"}.split(sep2), eq("ae")));

  ASSERT_EQ(1, count(String{"  ab   ab   ab  "}.split(' ', 0), alwaysTrue));
  ASSERT_EQ(1, count(String{"  ab   ab   ab  "}.split(' ', 0), eq("  ab   ab   ab  ")));

  ASSERT_EQ(2, count(String{"  ab   ab   ab  "}.split(' ', 1), alwaysTrue));
  ASSERT_EQ(1, count(String{"  ab   ab   ab  "}.split(' ', 1), e));
  ASSERT_EQ(1, count(String{"  ab   ab   ab  "}.split(' ', 1), eq(" ab   ab   ab  ")));

  ASSERT_EQ(3, count(String{"ab  ab ab  ab"}.split("  "), alwaysTrue));
  ASSERT_EQ(1, count(String{"ab  ab ab  ab"}.split("  "), eq("ab ab")));
  ASSERT_EQ(2, count(String{"ab  ab ab  ab"}.split("  "), eq("ab")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split("  ",  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split("  ",  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split("  ",  1), eq("ac ac   ac  ")));

  ASSERT_EQ(3, count(String{"ab  ab ab  ab"}.split("  ", testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(String{"ab  ab ab  ab"}.split("  ", testing::TrackerAllocator<cds::Size>()), eq("ab ab")));
  ASSERT_EQ(2, count(String{"ab  ab ab  ab"}.split("  ", testing::TrackerAllocator<cds::Size>()), eq("ab")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split("  ",  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split("  ",  1, testing::TrackerAllocator<cds::Size>()), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split("  ",  1, testing::TrackerAllocator<cds::Size>()), eq("ac ac   ac  ")));

  char const sep3[] = "  ";
  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep3,  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep3,  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep3,  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep3,  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep3,  1, testing::TrackerAllocator<cds::Size>()), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep3,  1, testing::TrackerAllocator<cds::Size>()), eq("ac ac   ac  ")));

  auto const* sep4 = "  ";
  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep4,  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep4,  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep4,  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep4,  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep4,  1, testing::TrackerAllocator<cds::Size>()), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep4,  1, testing::TrackerAllocator<cds::Size>()), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(static_cast<char const*>(sep4),  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(static_cast<char const*>(sep4),  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(static_cast<char const*>(sep4),  1), eq("ac ac   ac  ")));

  char sep5[] = "  ";
  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep5,  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep5,  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep5,  1), eq("ac ac   ac  ")));

  char* sep6 = sep5;
  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep6,  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep6,  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep6,  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(static_cast<char*>(sep6),  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(static_cast<char*>(sep6),  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(static_cast<char*>(sep6),  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(String{"  "},  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(String{"  "},  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(String{"  "},  1), eq("ac ac   ac  ")));

  String sep7{"  "};
  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep7,  1), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep7,  1), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep7,  1), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(String{"ac  ac ac   ac  "}.split(sep7,  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep7,  1, testing::TrackerAllocator<cds::Size>()), eq("ac")));
  ASSERT_EQ(1, count(String{"ac  ac ac   ac  "}.split(sep7,  1, testing::TrackerAllocator<cds::Size>()), eq("ac ac   ac  ")));

  ASSERT_EQ(2, count(String{"ac  ac"}.split(String{"  "}), alwaysTrue));

  ASSERT_EQ(2, count(String{"ac  ac"}.split(std::string{"  "}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(2, count(String{"ac  ac"}.split(std::string_view{"  "}), alwaysTrue));
#endif

  String str1{"abc  abc"};
  ASSERT_EQ(2, count(str1.split("  "), alwaysTrue));
  ASSERT_EQ(2, count(str1.split("  "), eq("abc")));

  ASSERT_EQ(1, count(str1.split("  ", 0), alwaysTrue));
  ASSERT_EQ(1, count(str1.split("  ", 0), eq("abc  abc")));

  ASSERT_EQ(2, count(str1.split(' ', 1), alwaysTrue));
  ASSERT_EQ(1, count(str1.split(' ', 1), eq("abc")));
  ASSERT_EQ(1, count(str1.split(' ', 1), eq(" abc")));

  using ACAlloc = typename ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}), eq("abc")));
  ASSERT_EQ(2, count(String{"abc  abc1__abc"}.split(std::vector<String>{"  ", "__"}), eq("abc")));
  ASSERT_EQ(1, count(String{"abc  abc1__abc"}.split(std::vector<String>{"  ", "__"}), eq("abc1")));

  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}, ACAlloc()), alwaysTrue));
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}, ACAlloc()), eq("abc")));
  ASSERT_EQ(2, count(String{"abc  abc1__abc"}.split(std::vector<String>{"  ", "__"}, ACAlloc()), eq("abc")));
  ASSERT_EQ(1, count(String{"abc  abc1__abc"}.split(std::vector<String>{"  ", "__"}, ACAlloc()), eq("abc1")));

  String str2{"abc  abc__abc"};
  ASSERT_EQ(3, count(str2.split(std::vector<String>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(std::vector<String>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(3, count(str2.split(std::vector<String>{"  ", "__"}, ACAlloc()), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(std::vector<String>{"  ", "__"}, ACAlloc()), eq("abc")));

  std::vector<String> sepsStrs{"  ", "__"};
  ASSERT_EQ(3, count(str2.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(sepsStrs), eq("abc")));

  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(sepsStrs), eq("abc")));

  ASSERT_EQ(4, count(String{"  abc  abc__abc"}.split(std::vector<String>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(1, count(String{"  abc  abc__abc"}.split(std::vector<String>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(String{"  abc  abc__abc"}.split(std::vector<String>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(4, count(String{"abc  abc__abc__"}.split(std::vector<String>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(1, count(String{"abc  abc__abc__"}.split(std::vector<String>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(String{"abc  abc__abc__"}.split(std::vector<String>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(4, count(String{"abc  abc  __abc"}.split(std::vector<String>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(1, count(String{"abc  abc  __abc"}.split(std::vector<String>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(String{"abc  abc  __abc"}.split(std::vector<String>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(6, count(String{"__abc  abc  __abc  "}.split(std::vector<String>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(String{"__abc  abc  __abc  "}.split(std::vector<String>{"  ", "__"}), memFn(&StringView::empty)));
  ASSERT_EQ(3, count(String{"__abc  abc  __abc  "}.split(std::vector<String>{"  ", "__"}), eq("abc")));

  ASSERT_EQ(1, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}, 0), alwaysTrue));
  ASSERT_EQ(1, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}, 0), eq("abc  abc__abc")));

  ASSERT_EQ(2, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}, 1), alwaysTrue));
  ASSERT_EQ(1, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}, 1), eq("abc")));
  ASSERT_EQ(1, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}, 1), eq("abc__abc")));

  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<StringView>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<char const*>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<String>{"  ", "__"}), alwaysTrue));
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<std::string>{"  ", "__"}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(3, count(String{"abc  abc__abc"}.split(std::vector<std::string_view>{"  ", "__"}), alwaysTrue));
#endif
}

TEST(STRING_TEST_ID, ostream) {
  std::stringstream oss;
  String sv{" abc "};
  oss << sv;
  ASSERT_EQ(oss.str(), " abc ");
}

TEST(STRING_TEST_ID, findClient) {
  ASSERT_TRUE(testing::citeq(String{"abcb"}.find('b'), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(String{"abcb"}.find('d'), std::vector<int>{}));

  String sv {"test test test"};
  ASSERT_TRUE(testing::citeq(sv.find("test"), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"testtesttest"}.find("test"), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(String {"test test test"}.find("test"), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test test "}.find("test"), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test tes"}.find("test"), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(String {" test test test"}.find("test"), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {"est test test"}.find("test"), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {" test test test "}.find("test"), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {" test test tes"}.find("test"), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(String {"est test test "}.find("test"), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {"est test tes"}.find("test"), std::vector<int> {4}));

  ASSERT_TRUE(testing::citeq(sv.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"testtesttest"}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(String {"test test test"}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test test "}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test tes"}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(String {" test test test"}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {"est test test"}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {" test test test "}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {" test test tes"}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(String {"est test test "}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {"est test tes"}.find("test", testing::TrackerAllocator<cds::Size>()), std::vector<int> {4}));
}

TEST(STRING_TEST_ID, findProjectionClient) {
  ASSERT_TRUE(testing::citeq(String{"abcb"}.find('B', toupper), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(String{"abcb"}.find('D', toupper), std::vector<int>{}));

  String sv {"test test test"};
  ASSERT_TRUE(testing::citeq(sv.find("TEST", toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"testtesttest"}.find("TEST", toupper), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(String {"test test test"}.find("TEST", toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test test "}.find("TEST", toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test tes"}.find("TEST", toupper), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(String {" test test test"}.find("TEST", toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {"est test test"}.find("TEST", toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {" test test test "}.find("TEST", toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {" test test tes"}.find("TEST", toupper), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(String {"est test test "}.find("TEST", toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {"est test tes"}.find("TEST", toupper), std::vector<int> {4}));

  ASSERT_TRUE(testing::citeq(sv.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"testtesttest"}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(String {"test test test"}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test test "}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(String {"test test tes"}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(String {" test test test"}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {"est test test"}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {" test test test "}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(String {" test test tes"}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(String {"est test test "}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(String {"est test tes"}.find("TEST", toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {4}));
}

TEST(STRING_TEST_ID, findFirstClient) {
  ASSERT_EQ(String{"abcb"}.findFirst('b'), 1);
  ASSERT_EQ(String{"abcb"}.findFirst('d'), String::npos);
  ASSERT_EQ(String{"abcb"}.findFirst("bc"), 1);
  ASSERT_EQ(String{"abcb"}.findFirst("bd"), String::npos);

  ASSERT_EQ(String{"abcb"}.findFirst("bc", testing::TrackerAllocator<cds::Size>()), 1);
  ASSERT_EQ(String{"abcb"}.findFirst("bd", testing::TrackerAllocator<cds::Size>()), String::npos);
}

TEST(STRING_TEST_ID, findProjectionFirstClient) {
  ASSERT_EQ(String{"abcb"}.findFirst('B', toupper), 1);
  ASSERT_EQ(String{"abcb"}.findFirst('D', toupper), String::npos);
  ASSERT_EQ(String{"abcb"}.findFirst("BC", toupper), 1);
  ASSERT_EQ(String{"abcb"}.findFirst("BD", toupper), String::npos);

  ASSERT_EQ(String{"abcb"}.findFirst("BC", toupper, testing::TrackerAllocator<cds::Size>()), 1);
  ASSERT_EQ(String{"abcb"}.findFirst("BD", toupper, testing::TrackerAllocator<cds::Size>()), String::npos);
}

TEST(STRING_TEST_ID, findLastClient) {
  ASSERT_EQ(String{"abcb"}.findLast('b'), 3);
  ASSERT_EQ(String{"abcb"}.findLast('d'), String::npos);
  ASSERT_EQ(String{"abcbc"}.findLast("bc"), 3);
  ASSERT_EQ(String{"abcb"}.findLast("bd"), String::npos);

  ASSERT_EQ(String{"abcbc"}.findLast("bc", testing::TrackerAllocator<cds::Size>()), 3);
  ASSERT_EQ(String{"abcb"}.findLast("bd", testing::TrackerAllocator<cds::Size>()), String::npos);
}

TEST(STRING_TEST_ID, findProjectionLastClient) {
  ASSERT_EQ(String{"abcb"}.findLast('B', toupper), 3);
  ASSERT_EQ(String{"abcb"}.findLast('D', toupper), String::npos);
  ASSERT_EQ(String{"abcbc"}.findLast("BC", toupper), 3);
  ASSERT_EQ(String{"abcb"}.findLast("BD", toupper), String::npos);

  ASSERT_EQ(String{"abcbc"}.findLast("BC", toupper, testing::TrackerAllocator<cds::Size>()), 3);
  ASSERT_EQ(String{"abcb"}.findLast("BD", toupper, testing::TrackerAllocator<cds::Size>()), String::npos);
}

TEST(STRING_TEST_ID, findOfClient) {
  ASSERT_TRUE(testing::citeq(String{"abcb"}.findOf(std::vector<char>{'a', 'c'}), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(String{"abcb"}.findOf(std::vector<char>{'d'}), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(String{"abcb"}.findOf("ac"), std::vector<int>{0, 2}));

  String sv1 {"abc bcd cde def"};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<String>{"bc", "bcd", "def"}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"abc bcd cde def"}.findOf(std::vector<String>{"bc", "bcd", "def"}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def"}.findOf(std::vector<String>{"bc", "bcd", "def"}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"c bcd cde def"}.findOf(std::vector<String>{"bc", "bcd", "def"}), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def "}.findOf(std::vector<String>{"bc", "bcd", "def"}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde de"}.findOf(std::vector<String>{"bc", "bcd", "def"}), std::vector<int> {0, 3}));

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<String>{"bc", "bcd", "def"}, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"abc bcd cde def"}.findOf(std::vector<String>{"bc", "bcd", "def"}, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def"}.findOf(std::vector<String>{"bc", "bcd", "def"}, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"c bcd cde def"}.findOf(std::vector<String>{"bc", "bcd", "def"}, ACAlloc()), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def "}.findOf(std::vector<String>{"bc", "bcd", "def"}, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde de"}.findOf(std::vector<String>{"bc", "bcd", "def"}, ACAlloc()), std::vector<int> {0, 3}));
}

TEST(STRING_TEST_ID, findProjectedOfClient) {
  ASSERT_TRUE(testing::citeq(String{"abcb"}.findOf(std::vector<char>{'A', 'C'}, toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(String{"abcb"}.findOf(std::vector<char>{'D'}, toupper), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(String{"abcb"}.findOf("AC", toupper), std::vector<int>{0, 2}));

  String sv1 {"abc bcd cde def"};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"abc bcd cde def"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"c bcd cde def"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def "}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde de"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper), std::vector<int> {0, 3}));

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"abc bcd cde def"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"c bcd cde def"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper, ACAlloc()), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde def "}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(String{"bc bcd cde de"}.findOf(std::vector<String>{"BC", "BCD", "DEF"}, toupper, ACAlloc()), std::vector<int> {0, 3}));
}

TEST(STRING_TEST_ID, findFirstOfClient) {
  ASSERT_EQ(String{"abcb"}.findFirstOf(std::vector<char>{'c', 'b'}), 1);
  ASSERT_EQ(String{"abcb"}.findFirstOf("cb"), 1);
  ASSERT_EQ(String{"abcb"}.findFirstOf(std::vector<char>{'d'}), String::npos);
  ASSERT_EQ(String{"abcb"}.findFirstOf(std::vector<char>{}), String::npos);

  String sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"cde", "bcd", "def"}), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"ggg"}), String::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{}), String::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"cde", "bcd", "def"}, ACAlloc()), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"ggg"}, ACAlloc()), String::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{}, ACAlloc()), String::npos);
}

TEST(STRING_TEST_ID, findProjectedFirstOfClient) {
  ASSERT_EQ(String{"abcb"}.findFirstOf(std::vector<char>{'C', 'B'}, toupper), 1);
  ASSERT_EQ(String{"abcb"}.findFirstOf("CB", toupper), 1);
  ASSERT_EQ(String{"abcb"}.findFirstOf(std::vector<char>{'D'}, toupper), String::npos);
  ASSERT_EQ(String{"abcb"}.findFirstOf(std::vector<char>{}, toupper), String::npos);

  String sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"CDE", "BCD", "DEF"}, toupper), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"GGG"}, toupper), String::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{}, toupper), String::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"CDE", "BCD", "DEF"}, toupper, ACAlloc()), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{"GGG"}, toupper, ACAlloc()), String::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<String>{}, toupper, ACAlloc()), String::npos);
}

TEST(STRING_TEST_ID, findLastOfClient) {
  ASSERT_EQ(String{"abcb"}.findLastOf(std::vector<char>{'c', 'b'}), 3);
  ASSERT_EQ(String{"abcbc"}.findLastOf("cb"), 4);
  ASSERT_EQ(String{"abcb"}.findLastOf(std::vector<char>{'d'}), String::npos);
  ASSERT_EQ(String{"abcb"}.findLastOf(std::vector<char>{}), String::npos);

  String sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"cde", "bcd", "def"}), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"ggg"}), String::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{}), String::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"cde", "bcd", "def"}, ACAlloc()), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"ggg"}, ACAlloc()), String::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{}, ACAlloc()), String::npos);
}

TEST(STRING_TEST_ID, findProjectedLastOfClient) {
  ASSERT_EQ(String{"abcb"}.findLastOf(std::vector<char>{'C', 'B'}, toupper), 3);
  ASSERT_EQ(String{"abcbc"}.findLastOf("CB", toupper), 4);
  ASSERT_EQ(String{"abcb"}.findLastOf(std::vector<char>{'D'}, toupper), String::npos);
  ASSERT_EQ(String{"abcb"}.findLastOf(std::vector<char>{}, toupper), String::npos);

  String sv1 {"abc bcd cde def"};
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"CDE", "BCD", "DEF"}, toupper), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"GGG"}, toupper), String::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{}, toupper), String::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"CDE", "BCD", "DEF"}, toupper, ACAlloc()), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{"GGG"}, toupper, ACAlloc()), String::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<String>{}, toupper, ACAlloc()), String::npos);
}

TEST(STRING_TEST_ID, findNotOfClient) {
  ASSERT_TRUE(testing::citeq(String{"abc"}.findNotOf("b"), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(String{"abc"}.findNotOf(std::vector<int>{'b'}), std::vector<int>{0, 2}));
}

TEST(STRING_TEST_ID, findProjectedNotOfClient) {
  ASSERT_TRUE(testing::citeq(String{"abc"}.findNotOf("B", toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(String{"abc"}.findNotOf(std::vector<int>{'B'}, toupper), std::vector<int>{0, 2}));
}

TEST(STRING_TEST_ID, findFirstNotOfClient) {
  ASSERT_EQ(String{"abc"}.findFirstNotOf("a"), 1);
  ASSERT_EQ(String{"abc"}.findFirstNotOf("abc"), String::npos);
}

TEST(STRING_TEST_ID, findProjectedFirstNotOfClient) {
  ASSERT_EQ(String{"abc"}.findFirstNotOf("A", toupper), 1);
  ASSERT_EQ(String{"abc"}.findFirstNotOf("ABC", toupper), String::npos);
}

TEST(STRING_TEST_ID, findLastNotOfClient) {
  ASSERT_EQ(String{"abca"}.findLastNotOf("a"), 2);
  ASSERT_EQ(String{"abc"}.findLastNotOf("abc"), String::npos);
}

TEST(STRING_TEST_ID, findProjectedLastNotOfClient) {
  ASSERT_EQ(String{"abca"}.findLastNotOf("A", toupper), 2);
  ASSERT_EQ(String{"abc"}.findLastNotOf("ABC", toupper), String::npos);
}

TEST(STRING_TEST_ID, findExtraCov) {
  auto r1 = String{"abc"}.find("bc");
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

TEST(STRING_TEST_ID, findExtraCov2) {
  auto r1 = String{"abc"}.find("BC", toupper);
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

TEST(STRING_TEST_ID, loremIpsumFind) {
  auto r = String{R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.)"}
  .findOf(std::vector<String>{"Lorem", "ipsum", "dolor", "sit", "amet", "consectetur",
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

TEST(STRING_TEST_ID, loremIpsumFindTracked) {
  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<char>;
  auto r = String{R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.)"}
  .findOf(std::vector<String>{"Lorem", "ipsum", "dolor", "sit", "amet", "consectetur",
    "adipiscing", "elit",
    "sed", "do", "eiusmod", "tempor", "incididunt", "ut", "labore", "et", "dolore","magna", "aliqua",
"Ut", "enim", "ad", "minim", "veniam", "quis", "nostrud", "exercitation", "ullamco", "laboris",
"nisi", "ut", "aliquip", "ex", "ea", "commodo", "consequat"," Duis", "aute", "irure", "dolor", "in",
"reprehenderit", "in", "voluptate", "velit", "esse", "cillum", "dolore", "eu", "fugiat", "nulla",
    "pariatur",
"Excepteur", "sint", "occaecat", "cupidatat", "non", "proident",
"sunt", "in", "culpa", "qui", "officia", "deserunt", "mollit", "anim", "id", "est", "laborum"}, ACAlloc());

  for (auto it = r.begin(); it != r.end(); ++it) {
    // do nothing, loop check
    ASSERT_GE(*it, 0);
  }
}

TEST(STRING_TEST_ID, functional) {
  String const sv{"abcd"};

  int count = 0;
  sv.forEach([&count](char const c) {
    (void) c;
    ++count;
  });

  ASSERT_EQ(count, 4);

  using T = cds::meta::StringTraits<char>;
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

  String s1{"abcd"};
  auto isLower = [](char const c){ return c >= 'a' && c <= 'z'; };
  auto makeUpper = [](char& c) { c = toupper(c); };
  auto isUpper = [](char const c){ return c >= 'A' && c <= 'Z'; };
  ASSERT_TRUE(s1.all(isLower));
  s1.forEach(makeUpper);
  ASSERT_TRUE(s1.all(isUpper));
}

TEST(STRING_TEST_ID, containsAllocation) {
  String const sv {"abcd"};
  ASSERT_TRUE(sv.contains("bc", cds::Allocator<cds::Size>()));
  ASSERT_TRUE(sv.contains("BC", toupper, cds::Allocator<cds::Size>()));
}

TEST(STRING_TEST_ID, startsEndsWith) {
  String const sv {"abcd"};

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

TEST(STRING_TEST_ID, literal) {
  using namespace cds::literals;
  ASSERT_EQ("abcd"_s, "abcd");
  ASSERT_EQ(L"abcd"_s, L"abcd");
}

TEST(STRING_TEST_ID, constructions) {
  String const sv1 = "abcd";
  char const buf[] = "abcd";
  String const sv2 = buf;
  std::string str = "abcd";
  String const sv3 = str;
  ASSERT_EQ(sv1, sv2);
  ASSERT_EQ(sv1, sv3);
  StringView const str2 = "abcd";
  String const sv4 = str2;
  ASSERT_EQ(sv4, sv1);
}

TEST(STRING_TEST_ID, assignments) {
  String sv;
  sv = "abcd";
  ASSERT_EQ(sv, "abcd");
  char const buf[] = "abcd";
  sv = buf;
  ASSERT_EQ(sv, "abcd");
  std::string const sv3 = "abcd";
  sv = sv3;
  ASSERT_EQ(sv, "abcd");
  StringView const str2 = "abcd";
  sv = str2;
  ASSERT_EQ(sv, "abcd");
}

TEST(STRING_TEST_ID, largerAssignments) {
  String s;
  StringView bigData = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  StringView bigData2 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  s = bigData;
  ASSERT_EQ(s, bigData);
  String s2 = bigData;
  ASSERT_EQ(s2, bigData);

  s = cds::move(s2);
  ASSERT_EQ(s, bigData);

  String s3;
  s3 = s;
  ASSERT_EQ(s3, bigData);
  s = s3;
  ASSERT_EQ(s, bigData);
  s = s;
  ASSERT_EQ(s, bigData);

  s = cds::move(s3);
  ASSERT_EQ(s, bigData);

  s = bigData;
  ASSERT_EQ(s, bigData);
  s = bigData;
  ASSERT_EQ(s, bigData);
  s = bigData2;
  ASSERT_EQ(s, bigData2);
  s = bigData;
  ASSERT_EQ(s, bigData);

  s = "abcd";
  ASSERT_EQ(s, "abcd");
  s = "aaaaaaaaaaaaaaaaaaaaaaaa";
  ASSERT_EQ(s, "aaaaaaaaaaaaaaaaaaaaaaaa");
  s = "aaaaaaaaaaaaaaaaaaaaaaaa";
  ASSERT_EQ(s, "aaaaaaaaaaaaaaaaaaaaaaaa");
  s = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
  ASSERT_EQ(s, "aaaaaaaaaaaaaaaaaaaaaaaaaa");
  s = bigData2;
  ASSERT_EQ(s, bigData2);
}

TEST(STRING_TEST_ID, capacity) {
  StringView sboData = "aaaaaaaaaaaaaaaaaaaaaa";
  StringView nonSboData = "aaaaaaaaaaaaaaaaaaaaaaa";
  StringView nonSboData2 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  String s;
  ASSERT_EQ(s.capacity(), 22);
  String s2 = "abcd";
  ASSERT_EQ(s2.capacity(), 22);
  String s3 = sboData;
  ASSERT_EQ(s3.capacity(), 22);
  String s4 = nonSboData;
  ASSERT_EQ(s4.capacity(), 31);
  String s5 = nonSboData2;
  ASSERT_EQ(s5.capacity(), nonSboData2.size());
}

TEST(STRING_TEST_ID, ctorFill) {
  String a(0, 'a');
  String b(1, 'b');
  String c(2, 'c');

  ASSERT_EQ(a, "");
  ASSERT_EQ(b, "b");
  ASSERT_EQ(c, "cc");
}

TEST(STRING_TEST_ID, ctorBool) {
  String a(true);
  String b(false);

  ASSERT_EQ(a, "true");
  ASSERT_EQ(b, "false");
}

TEST(STRING_TEST_ID, ctorChar) {
  String a(' ');
  String b('a');
  String c('\0');

  ASSERT_EQ(a, " ");
  ASSERT_EQ(b, "a");
  ASSERT_EQ(c, "");
}

TEST(STRING_TEST_ID, ctorIntegral) {
  String x1(1);
  String x2(12);
  String x3(123);
  ASSERT_EQ(x1, "1");
  ASSERT_EQ(x2, "12");
  ASSERT_EQ(x3, "123");
  String x4(-1);
  String x5(-12);
  String x6(-123);
  String x7(-1234);
  ASSERT_EQ(x4, "-1");
  ASSERT_EQ(x5, "-12");
  ASSERT_EQ(x6, "-123");
  ASSERT_EQ(x7, "-1234");

  String a(0);
  String b(1234);
  String c(cds::limits::u64Max);
  String d(cds::limits::s64Min);

  ASSERT_EQ(a, "0");
  ASSERT_EQ(b, "1234");
  ASSERT_EQ(c, "18446744073709551615");
  ASSERT_EQ(d, "-9223372036854775808");
}

TEST(STRING_TEST_ID, ctorFloating) {
  String a(3.14f);
  String b(3.14);
  String c(3.14L);

  ASSERT_EQ(a, "3.140000");
  ASSERT_EQ(b, "3.140000");
  ASSERT_EQ(c, "3.140000");
}

TEST(STRING_TEST_ID, assignBool) {
  String a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  a = true;
  ASSERT_EQ(a, "true");
  a = false;
  ASSERT_EQ(a, "false");
}

TEST(STRING_TEST_ID, assignChar) {
  String a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  a = ' ';
  ASSERT_EQ(a, " ");
  a = 'b';
  ASSERT_EQ(a, "b");
  a = '\0';
  ASSERT_EQ(a, "");
}

TEST(STRING_TEST_ID, assignInt) {
  String a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  String b;
  a = 1;
  ASSERT_EQ(a, "1");
  a = 12;
  ASSERT_EQ(a, "12");
  a = 123;
  ASSERT_EQ(a, "123");
  a = -1;
  ASSERT_EQ(a, "-1");
  a = -12;
  ASSERT_EQ(a, "-12");
  a = -123;
  ASSERT_EQ(a, "-123");
  a = -1234;
  ASSERT_EQ(a, "-1234");

  b = 0;
  ASSERT_EQ(b, "0");
  b = 1234;
  ASSERT_EQ(b, "1234");
  b = cds::limits::u64Max;
  ASSERT_EQ(b, "18446744073709551615");
  b = cds::limits::s64Min;
  ASSERT_EQ(b, "-9223372036854775808");
}

TEST(STRING_TEST_ID, assignFloat) {
  String a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  String b;

  a = 3.14f;
  ASSERT_EQ(a, "3.140000");
  a = 3.14;
  ASSERT_EQ(a, "3.140000");
  a = 3.14L;
  ASSERT_EQ(a, "3.140000");

  b = 3.14f;
  ASSERT_EQ(b, "3.140000");
  b = 3.14;
  ASSERT_EQ(b, "3.140000");
  b = 3.14L;
  ASSERT_EQ(b, "3.140000");
}

TEST(STRING_TEST_ID, resize) {
  String a;
  a.resize(0, 'a');
  ASSERT_EQ(a, "");
  a.resize(4, 'a');
  ASSERT_EQ(a, "aaaa");
  a.resize(2, 'a');
  ASSERT_EQ(a, "aa");
  a.resize(4, 'b');
  ASSERT_EQ(a, "aabb");
  a.resize(3, 'c');
  ASSERT_EQ(a, "aab");
  a.resize(10, 'd');
  ASSERT_EQ(a, "aabddddddd");
  a.resize(20, '-');
  ASSERT_EQ(a, "aabddddddd"
               "----------");
  a.resize(30, '+');
  ASSERT_EQ(a, "aabddddddd"
               "----------"
               "++++++++++");
  a.resize(20, '=');
  ASSERT_EQ(a, "aabddddddd"
               "----------");
  ASSERT_EQ(a.capacity(), 22);
  a.resize(40, '+');
  ASSERT_EQ(a, "aabddddddd"
               "----------"
               "++++++++++"
               "++++++++++");
  a.resize(50, '=');
  ASSERT_EQ(a, "aabddddddd"
               "----------"
               "++++++++++"
               "++++++++++"
               "==========");
  a.resize(30, '+');
  ASSERT_EQ(a, "aabddddddd"
               "----------"
               "++++++++++");
  ASSERT_EQ(a.capacity(), 31);
  a.resize(31, '+');
  ASSERT_EQ(a, "aabddddddd"
               "----------"
               "++++++++++");
  ASSERT_EQ(a.capacity(), 31);
}

TEST(STRING_TEST_ID, reserve) {
  String a = "abcd";
  ASSERT_EQ(a.capacity(), 22);
  a.reserve(20);
  ASSERT_EQ(a.capacity(), 22);
  a.reserve(22);
  ASSERT_EQ(a.capacity(), 22);
  a.reserve(0);
  ASSERT_EQ(a.capacity(), 22);
  ASSERT_EQ(a, "abcd");
  a.reserve(23);
  ASSERT_EQ(a.capacity(), 31);
  ASSERT_EQ(a, "abcd");
  a.reserve(20);
  ASSERT_EQ(a.capacity(), 31);
  ASSERT_EQ(a, "abcd");
  a.reserve(31);
  ASSERT_EQ(a.capacity(), 31);
  ASSERT_EQ(a, "abcd");
  a.reserve(64);
  ASSERT_EQ(a.capacity(), 64);
  ASSERT_EQ(a, "abcd");
  a.reserve(30);
  ASSERT_EQ(a.capacity(), 64);
  ASSERT_EQ(a, "abcd");
}

TEST(STRING_TEST_ID, shrink) {
  String a = "abcd";
  a.shrink(20);
  ASSERT_EQ(a, "abcd");
  a.shrink(0);
  ASSERT_EQ(a, "abcd");
  a.shrink(10);
  ASSERT_EQ(a, "abcd");
  a = "0000000000"
      "1111111111"
      "2222222222";
  a.shrink(25);
  ASSERT_EQ(a, "0000000000"
               "1111111111"
               "22222");
  ASSERT_EQ(a.capacity(), 31);
  a.shrink(20);
  ASSERT_EQ(a, "0000000000"
               "1111111111");
  ASSERT_EQ(a.capacity(), 22);
  a = "abcd";
  a.reserve(64);
  a.shrink();
  ASSERT_EQ(a.capacity(), 22);
}

TEST(STRING_TEST_ID, operatorAppendStr) {
  String a;
  a += "abc";
  ASSERT_EQ(a, "abc");
  char const* str1 = "def";
  a += str1;
  ASSERT_EQ(a, "abcdef");
  char const str2[] = "ghi";
  a += str2;
  ASSERT_EQ(a, "abcdefghi");

  StringView str3 = "ABC";
  a += str3;
  ASSERT_EQ(a, "abcdefghiABC");
  std::string str4 = "DEF";
  a += str4;
  ASSERT_EQ(a, "abcdefghiABCDEF");
  StringView str5 = "1234";
  a += str5;
  ASSERT_EQ(a, "abcdefghiABCDEF"
               "1234");
  a += str5;
  a += str5;
  a += str5;
  a += str5;
  a += str5;
  ASSERT_EQ(a, "abcdefghiABCDEF"
               "123412341234"
               "123412341234");
  a += a;
  ASSERT_EQ(a, "abcdefghiABCDEF"
               "123412341234"
               "123412341234"
               "abcdefghiABCDEF"
               "123412341234"
               "123412341234");
}

TEST(STRING_TEST_ID, operatorAppendChar) {
  String a;
  std::string b;
  for (int i = 0; i < 100; ++i) {
    a += 'a';
    b += 'a';
    ASSERT_EQ(a, b);
  }
}

TEST(STRING_TEST_ID, operatorAppendBool) {
  String a;
  std::string b;
  for (int i = 0; i < 100; ++i) {
    a += static_cast<bool>(i % 2);
    b += (static_cast<bool>(i % 2) ? "true" : "false");
    ASSERT_EQ(a, b);
  }
}

TEST(STRING_TEST_ID, operatorAppendInt) {
  String a;
  std::string b;
  for (int i = 0; i < 100; ++i) {
    a += i;
    b += std::to_string(i);
    ASSERT_EQ(a, b);
  }
}

TEST(STRING_TEST_ID, operatorAppendFloating) {
  char equivBuf[1024];
  equivBuf[0] = 0;
  int equivBufLen = 0;
  float v = .5f;
  String a;
  for (int i = 0; i < 10; ++i) {
    a += v;
    std::snprintf(equivBuf, 1024, "%s%f", equivBuf, v);
    v += 1.1f;
    ASSERT_EQ(a, (char const*)equivBuf);
  }
}

#ifdef DCR_SINCECPP17
TEST(STRING_TEST_ID, construction17) {
  String a = std::string_view("abc");

  (void) a;
}
#endif
