// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/StringView>
#include <cds/String>
#include <cassert>
#include <iostream>
#include <array>

#include "UnitTest.hpp"
#include "../../Shared.hpp"
#include "../../TrackerAllocator.hpp"

using namespace cds;

#define LATE_JOIN2(a, b) a ## b
#define LATE_JOIN(a, b) LATE_JOIN2(a, b)
#define STRING_VIEW_TEST_GROUP LATE_JOIN(StringView_, CHAR_TYPE)

namespace {
using testing::TrackerAllocator;
using SV = impl::BaseStringView<CHAR_TYPE>;
using S = impl::BaseString<CHAR_TYPE, impl::StringUtils<CHAR_TYPE, meta::StringTraits<CHAR_TYPE>>,
    TrackerAllocator<CHAR_TYPE>>;
using stds = std::basic_string<CHAR_TYPE>;
using oss = std::basic_stringstream<CHAR_TYPE>;
#ifdef DCR_SINCECPP17
using stdsv = std::basic_string_view<CHAR_TYPE>;
#endif
using T = meta::StringTraits<CHAR_TYPE>;
}

TEST(STRING_VIEW_TEST_GROUP, BaseCopyMove) {
  SV const sv1;
  SV const sv2;
  ASSERT_EQ(sv1, sv2);

  SV const sv3(LITERAL("abcd"));
  SV const sv4(sv3);
  SV tbm(sv3);
  SV const sv5(std::move(tbm));
  ASSERT_EQ(sv3, sv4);
  ASSERT_EQ(sv4, sv5);
  ASSERT_EQ(sv5, sv3);
}

TEST(STRING_VIEW_TEST_GROUP, Compare) {
  SV n = nullptr;
  SV a = LITERAL("a");
  SV b = LITERAL("b");
  SV c = LITERAL("c");

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

TEST(STRING_VIEW_TEST_GROUP, baseMembers) {
  SV const sv1;
  SV const sv2(sv1.data());
  SV const sv3(LITERAL("abcd"));
  SV sv4(sv3.data());

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

  ASSERT_EQ(sv3.data(), stds(LITERAL("abcd")));
  ASSERT_EQ(sv3.length(), 4u);
  ASSERT_EQ(sv3.size(), 4u);
  ASSERT_FALSE(sv3.empty());
  ASSERT_TRUE(sv3);

  ASSERT_EQ(sv4.data(), stds(LITERAL("abcd")));
  ASSERT_EQ(sv4.length(), 4u);
  ASSERT_EQ(sv4.size(), 4u);
  ASSERT_FALSE(sv4.empty());
  ASSERT_TRUE(sv4);

  sv4.clear();
  ASSERT_EQ(sv4.size(), 0u);
  ASSERT_TRUE(sv4.empty());
  ASSERT_FALSE(sv4);
}

TEST(STRING_VIEW_TEST_GROUP, assign) {
  SV sv1;
  ASSERT_EQ(sv1.size(), 0u);

  sv1 = LITERAL("abcd");
  ASSERT_EQ(sv1.size(), 4u);

  auto const* p = LITERAL("abcde");
  sv1 = p;
  ASSERT_EQ(sv1.size(), 5u);

  CHAR_TYPE const arr[] = LITERAL("abcdef");
  sv1 = arr;
  ASSERT_EQ(sv1.size(), 6u);
}

TEST(STRING_VIEW_TEST_GROUP, iter) {
  SV const sv = LITERAL("abcd");
  ASSERT_EQ(*begin(sv), LITERAL('a'));
  ASSERT_EQ(*(begin(sv) + 0), LITERAL('a'));
  ASSERT_EQ(*(begin(sv) + 1), LITERAL('b'));
  ASSERT_EQ(*(begin(sv) + 2), LITERAL('c'));
  ASSERT_EQ(*(begin(sv) + 3), LITERAL('d'));
  ASSERT_EQ(begin(sv) + 4, end(sv));

  ASSERT_EQ(*cbegin(sv), LITERAL('a'));
  ASSERT_EQ(*(cbegin(sv) + 0), LITERAL('a'));
  ASSERT_EQ(*(cbegin(sv) + 1), LITERAL('b'));
  ASSERT_EQ(*(cbegin(sv) + 2), LITERAL('c'));
  ASSERT_EQ(*(cbegin(sv) + 3), LITERAL('d'));
  ASSERT_EQ(cbegin(sv) + 4, cend(sv));

  ASSERT_EQ(*rbegin(sv), LITERAL('d'));
  ASSERT_EQ(*(rbegin(sv) + 0), LITERAL('d'));
  ASSERT_EQ(*(rbegin(sv) + 1), LITERAL('c'));
  ASSERT_EQ(*(rbegin(sv) + 2), LITERAL('b'));
  ASSERT_EQ(*(rbegin(sv) + 3), LITERAL('a'));
  ASSERT_EQ(rbegin(sv) + 4, rend(sv));

  ASSERT_EQ(*crbegin(sv), LITERAL('d'));
  ASSERT_EQ(*(crbegin(sv) + 0), LITERAL('d'));
  ASSERT_EQ(*(crbegin(sv) + 1), LITERAL('c'));
  ASSERT_EQ(*(crbegin(sv) + 2), LITERAL('b'));
  ASSERT_EQ(*(crbegin(sv) + 3), LITERAL('a'));
  ASSERT_EQ(crbegin(sv) + 4, crend(sv));
}

TEST(STRING_VIEW_TEST_GROUP, CompareCompatLiteral) {
  SV const sv = LITERAL("abcd");
  ASSERT_EQ(sv, LITERAL("abcd"));
  ASSERT_NE(sv, LITERAL("abce"));
  ASSERT_GT(sv, LITERAL("abc"));
  ASSERT_GT(sv, LITERAL("abcc"));
  ASSERT_LT(sv, LITERAL("abd"));
  ASSERT_LT(sv, LITERAL("abce"));
  ASSERT_GE(sv, LITERAL("abc"));
  ASSERT_GE(sv, LITERAL("abcc"));
  ASSERT_GE(sv, LITERAL("abcd"));
  ASSERT_LE(sv, LITERAL("abd"));
  ASSERT_LE(sv, LITERAL("abce"));
  ASSERT_LE(sv, LITERAL("abcd"));

  ASSERT_EQ(LITERAL("abcd"), sv);
  ASSERT_NE(LITERAL("abce"), sv);
  ASSERT_LT(LITERAL("abc"), sv);
  ASSERT_LT(LITERAL("abcc"), sv);
  ASSERT_GT(LITERAL("abd"), sv);
  ASSERT_GT(LITERAL("abce"), sv);
  ASSERT_LE(LITERAL("abc"), sv);
  ASSERT_LE(LITERAL("abcc"), sv);
  ASSERT_LE(LITERAL("abcd"), sv);
  ASSERT_GE(LITERAL("abd"), sv);
  ASSERT_GE(LITERAL("abce"), sv);
  ASSERT_GE(LITERAL("abcd"), sv);
}

TEST(STRING_VIEW_TEST_GROUP, Positionals) {
  SV const sv = LITERAL("abcd");
  ASSERT_EQ(sv[0], LITERAL('a'));
  ASSERT_EQ(sv[1], LITERAL('b'));
  ASSERT_EQ(sv[2], LITERAL('c'));
  ASSERT_EQ(sv[3], LITERAL('d'));

  ASSERT_EQ(sv.at(0), LITERAL('a'));
  ASSERT_EQ(sv.at(1), LITERAL('b'));
  ASSERT_EQ(sv.at(2), LITERAL('c'));
  ASSERT_EQ(sv.at(3), LITERAL('d'));

  ASSERT_EQ(sv.front(), LITERAL('a'));
  ASSERT_EQ(sv.back(), LITERAL('d'));
}

TEST(STRING_VIEW_TEST_GROUP, Sub) {
  SV const sv = LITERAL("abcd");
  ASSERT_EQ(sv.sub(0), LITERAL("abcd"));
  ASSERT_EQ(sv.sub(1), LITERAL("bcd"));
  ASSERT_EQ(sv.sub(2), LITERAL("cd"));
  ASSERT_EQ(sv.sub(3), LITERAL("d"));

  ASSERT_EQ(sv.sub(0, 4), LITERAL("abcd"));
  ASSERT_EQ(sv.sub(0, 3), LITERAL("abc"));
  ASSERT_EQ(sv.sub(0, 2), LITERAL("ab"));
  ASSERT_EQ(sv.sub(0, 1), LITERAL("a"));

  ASSERT_EQ(sv.sub(1, 4), LITERAL("bcd"));
  ASSERT_EQ(sv.sub(1, 3), LITERAL("bc"));
  ASSERT_EQ(sv.sub(1, 2), LITERAL("b"));

  ASSERT_EQ(sv.sub(2, 4), LITERAL("cd"));
  ASSERT_EQ(sv.sub(2, 3), LITERAL("c"));

  ASSERT_EQ(sv.sub(3, 4), LITERAL("d"));

  ASSERT_EQ(sv.sub(0, 0), LITERAL(""));
  ASSERT_EQ(sv.sub(1, 0), LITERAL(""));
  ASSERT_EQ(sv.sub(1, 1), LITERAL(""));
  ASSERT_EQ(sv.sub(2, 1), LITERAL(""));
  ASSERT_EQ(sv.sub(2, 2), LITERAL(""));
  ASSERT_EQ(sv.sub(3, 2), LITERAL(""));
  ASSERT_EQ(sv.sub(3, 3), LITERAL(""));
  ASSERT_EQ(sv.sub(4, 3), LITERAL(""));

  ASSERT_EQ(sv(0), LITERAL("abcd"));
  ASSERT_EQ(sv(1), LITERAL("bcd"));
  ASSERT_EQ(sv(2), LITERAL("cd"));
  ASSERT_EQ(sv(3), LITERAL("d"));

  ASSERT_EQ(sv(0, 4), LITERAL("abcd"));
  ASSERT_EQ(sv(0, 3), LITERAL("abc"));
  ASSERT_EQ(sv(0, 2), LITERAL("ab"));
  ASSERT_EQ(sv(0, 1), LITERAL("a"));

  ASSERT_EQ(sv(1, 4), LITERAL("bcd"));
  ASSERT_EQ(sv(1, 3), LITERAL("bc"));
  ASSERT_EQ(sv(1, 2), LITERAL("b"));

  ASSERT_EQ(sv(2, 4), LITERAL("cd"));
  ASSERT_EQ(sv(2, 3), LITERAL("c"));

  ASSERT_EQ(sv(3, 4), LITERAL("d"));

  ASSERT_EQ(sv(0, 0), LITERAL(""));
  ASSERT_EQ(sv(1, 0), LITERAL(""));
  ASSERT_EQ(sv(1, 1), LITERAL(""));
  ASSERT_EQ(sv(2, 1), LITERAL(""));
  ASSERT_EQ(sv(2, 2), LITERAL(""));
  ASSERT_EQ(sv(3, 2), LITERAL(""));
  ASSERT_EQ(sv(3, 3), LITERAL(""));
  ASSERT_EQ(sv(4, 3), LITERAL(""));
}

TEST(STRING_VIEW_TEST_GROUP, contains) {
  SV const sv = LITERAL("bC");
  ASSERT_FALSE(sv.contains(LITERAL('a')));
  ASSERT_TRUE(sv.contains(LITERAL('b')));
  ASSERT_TRUE(sv.contains(LITERAL('C')));
  ASSERT_FALSE(sv.contains(LITERAL('d')));

  ASSERT_FALSE(sv.contains(LITERAL('a'), T::lower));
  ASSERT_TRUE(sv.contains(LITERAL('b'), T::lower));
  ASSERT_TRUE(sv.contains(LITERAL('c'), T::lower));
  ASSERT_FALSE(sv.contains(LITERAL('d'), T::lower));
}

TEST(STRING_VIEW_TEST_GROUP, containsString) {
  SV const sv = LITERAL("abcd");
  ASSERT_TRUE(sv.contains(LITERAL("bc"), TrackerAllocator<Size>()));
  ASSERT_FALSE(sv.contains(LITERAL("bd"), TrackerAllocator<Size>()));
}

TEST(STRING_VIEW_TEST_GROUP, containsOf) {
  SV const sv = LITERAL("bC");
  ASSERT_FALSE(sv.containsAnyOf(LITERAL("ad")));
  ASSERT_TRUE(sv.containsAnyOf(LITERAL("bc")));
  ASSERT_TRUE(sv.containsAnyOf(SV(LITERAL("bc"))));
  ASSERT_TRUE(sv.containsAnyOf(S(LITERAL("bc"))));
  ASSERT_TRUE(sv.containsAnyOf(stds(LITERAL("bc"))));
  ASSERT_TRUE(sv.containsAnyOf(LITERAL("BC"), T::upper));
  ASSERT_TRUE(sv.containsAnyOf(SV(LITERAL("BC")), T::upper));
  ASSERT_TRUE(sv.containsAnyOf(S(LITERAL("BC")), T::upper));
  ASSERT_TRUE(sv.containsAnyOf(stds(LITERAL("BC")), T::upper));

  ASSERT_FALSE(sv.containsAnyNotOf(LITERAL("bC")));
  ASSERT_TRUE(sv.containsAnyNotOf(LITERAL("bc")));
  ASSERT_TRUE(sv.containsAnyNotOf(LITERAL("Bc")));
  ASSERT_TRUE(sv.containsAnyNotOf(LITERAL("BC")));
  ASSERT_TRUE(sv.containsAnyNotOf(SV(LITERAL("bc"))));
  ASSERT_TRUE(sv.containsAnyNotOf(S(LITERAL("bc"))));
  ASSERT_TRUE(sv.containsAnyNotOf(stds(LITERAL("bc"))));
  ASSERT_TRUE(sv.containsAnyNotOf(LITERAL("C"), T::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(SV(LITERAL("c")), T::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(S(LITERAL("c")), T::upper));
  ASSERT_TRUE(sv.containsAnyNotOf(stds(LITERAL("B")), T::upper));

  ASSERT_FALSE(sv.containsAllOf(LITERAL("ac")));
  ASSERT_FALSE(sv.containsAllOf(LITERAL("ab")));
  ASSERT_TRUE(sv.containsAllOf(LITERAL("bC")));
  ASSERT_TRUE(sv.containsAllOf(SV(LITERAL("bC"))));
  ASSERT_TRUE(sv.containsAllOf(S(LITERAL("bC"))));
  ASSERT_TRUE(sv.containsAllOf(stds(LITERAL("bC"))));
  ASSERT_TRUE(sv.containsAllOf(LITERAL("BC"), T::upper));
  ASSERT_TRUE(sv.containsAllOf(SV(LITERAL("BC")), T::upper));
  ASSERT_TRUE(sv.containsAllOf(S(LITERAL("BC")), T::upper));
  ASSERT_TRUE(sv.containsAllOf(stds(LITERAL("BC")), T::upper));

  ASSERT_FALSE(sv.containsNoneOf(LITERAL("bC")));
  ASSERT_FALSE(sv.containsNoneOf(LITERAL("bc")));
  ASSERT_FALSE(sv.containsNoneOf(LITERAL("BC")));
  ASSERT_TRUE(sv.containsNoneOf(LITERAL("ad")));
  ASSERT_TRUE(sv.containsNoneOf(LITERAL("ac")));
  ASSERT_TRUE(sv.containsNoneOf(LITERAL("Bc")));
  ASSERT_TRUE(sv.containsNoneOf(SV(LITERAL("ad"))));
  ASSERT_TRUE(sv.containsNoneOf(S(LITERAL("ad"))));
  ASSERT_TRUE(sv.containsNoneOf(stds(LITERAL("ad"))));
  ASSERT_TRUE(sv.containsNoneOf(LITERAL("ad"), T::upper));
  ASSERT_TRUE(sv.containsNoneOf(SV(LITERAL("ad")), T::upper));
  ASSERT_TRUE(sv.containsNoneOf(S(LITERAL("ad")), T::upper));
  ASSERT_TRUE(sv.containsNoneOf(stds(LITERAL("ad")), T::upper));
}

TEST(STRING_VIEW_TEST_GROUP, find) {
  SV const sv = LITERAL("abcb");

  auto lRng = sv.find(LITERAL('b'));
  auto lIt = lRng.begin();
  ASSERT_EQ(*lIt, 1);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(*lIt, 3);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = SV(LITERAL("abcb")).find(LITERAL('b'));
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

TEST(STRING_VIEW_TEST_GROUP, split) {
  using functional::memFn;

  SV sv1 = LITERAL("  abc abc abc  abc abc   ");
  auto eq = [](SV lhs){
    return [lhs](SV const& rhs){ return lhs == rhs; };
  };

  auto alwaysTrue = [](SV const&) { return true; };

  using namespace cds::impl;
  ASSERT_EQ(11, count(sv1.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(6, count(sv1.split(LITERAL(' ')), memFn(&SV::empty)));
  ASSERT_EQ(5, count(sv1.split(LITERAL(' ')), eq(LITERAL("abc"))));

  CHAR_TYPE sep = LITERAL(' ');
  ASSERT_EQ(11, count(sv1.split(sep), alwaysTrue));

  ASSERT_EQ(2, count(SV{LITERAL("ab ab")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(2, count(SV{LITERAL("ab ab")}.split(LITERAL(' ')), eq(LITERAL("ab"))));

  ASSERT_EQ(0, count(SV{LITERAL("")}.split(LITERAL(' ')), alwaysTrue));

  ASSERT_EQ(3, count(SV{LITERAL(" ac ac")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL(" ac ac")}.split(LITERAL(' ')), memFn(&SV::empty)));
  ASSERT_EQ(2, count(SV{LITERAL(" ac ac")}.split(LITERAL(' ')), eq(LITERAL("ac"))));

  ASSERT_EQ(4, count(SV{LITERAL("ad ad  ")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(2, count(SV{LITERAL("ad ad  ")}.split(LITERAL(' ')), memFn(&SV::empty)));
  ASSERT_EQ(2, count(SV{LITERAL("ad ad  ")}.split(LITERAL(' ')), eq(LITERAL("ad"))));

  auto e = memFn(&SV::empty);
  ASSERT_EQ(4, count(SV{LITERAL("ae   ae")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(2, count(SV{LITERAL("ae   ae")}.split(LITERAL(' ')), e));
  ASSERT_EQ(2, count(SV{LITERAL("ae   ae")}.split(LITERAL(' ')), eq(LITERAL("ae"))));

  auto r = SV{LITERAL("a b")}.split(LITERAL(' '));
  ASSERT_EQ(2, count(r, alwaysTrue));
  ASSERT_EQ(1, count(r, eq(LITERAL("a"))));
  ASSERT_EQ(1, count(r, eq(LITERAL("b"))));

  ASSERT_EQ(10, count(SV{LITERAL("ae ; ae;ae ae; ae ;")}.split(std::vector<CHAR_TYPE>{LITERAL(' '), LITERAL(';')}), alwaysTrue));
  ASSERT_EQ(5, count(SV{LITERAL("ae ; ae;ae ae; ae ;")}.split(std::vector<CHAR_TYPE>{LITERAL(' '), LITERAL(';')}), e));
  ASSERT_EQ(5, count(SV{LITERAL("ae ; ae;ae ae; ae ;")}.split(std::vector<CHAR_TYPE>{LITERAL(' '), LITERAL(';')}), eq(LITERAL("ae"))));

  std::initializer_list<CHAR_TYPE> sep2 = {LITERAL(' '), LITERAL(';')};
  ASSERT_EQ(10, count(SV{LITERAL("ae ; ae;ae ae; ae ;")}.split(sep2), alwaysTrue));
  ASSERT_EQ(5, count(SV{LITERAL("ae ; ae;ae ae; ae ;")}.split(sep2), e));
  ASSERT_EQ(5, count(SV{LITERAL("ae ; ae;ae ae; ae ;")}.split(sep2), eq(LITERAL("ae"))));

  ASSERT_EQ(1, count(SV{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 0), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 0), eq(LITERAL("  ab   ab   ab  "))));

  ASSERT_EQ(2, count(SV{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 1), e));
  ASSERT_EQ(1, count(SV{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 1), eq(LITERAL(" ab   ab   ab  "))));

  ASSERT_EQ(3, count(SV{LITERAL("ab  ab ab  ab")}.split(LITERAL("  ")), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ab  ab ab  ab")}.split(LITERAL("  ")), eq(LITERAL("ab ab"))));
  ASSERT_EQ(2, count(SV{LITERAL("ab  ab ab  ab")}.split(LITERAL("  ")), eq(LITERAL("ab"))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(3, count(SV{LITERAL("ab  ab ab  ab")}.split(LITERAL("  "), TrackerAllocator<Size>()), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ab  ab ab  ab")}.split(LITERAL("  "), TrackerAllocator<Size>()), eq(LITERAL("ab ab"))));
  ASSERT_EQ(2, count(SV{LITERAL("ab  ab ab  ab")}.split(LITERAL("  "), TrackerAllocator<Size>()), eq(LITERAL("ab"))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1, TrackerAllocator<Size>()), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1, TrackerAllocator<Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1, TrackerAllocator<Size>()), eq(LITERAL("ac ac   ac  "))));

  CHAR_TYPE const sep3[] = LITERAL("  ");
  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1, TrackerAllocator<Size>()), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1, TrackerAllocator<Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1, TrackerAllocator<Size>()), eq(LITERAL("ac ac   ac  "))));

  auto const* sep4 = LITERAL("  ");
  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1, TrackerAllocator<Size>()), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1, TrackerAllocator<Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1, TrackerAllocator<Size>()), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE const*>(sep4),  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE const*>(sep4),  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE const*>(sep4),  1), eq(LITERAL("ac ac   ac  "))));

  CHAR_TYPE sep5[] = LITERAL("  ");
  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep5,  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep5,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep5,  1), eq(LITERAL("ac ac   ac  "))));

  CHAR_TYPE* sep6 = sep5;
  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep6,  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep6,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep6,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE*>(sep6),  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE*>(sep6),  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE*>(sep6),  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(SV{LITERAL("  ")},  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(SV{LITERAL("  ")},  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(SV{LITERAL("  ")},  1), eq(LITERAL("ac ac   ac  "))));

  SV sep7{LITERAL("  ")};
  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1, TrackerAllocator<Size>()), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1, TrackerAllocator<Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(SV{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1, TrackerAllocator<Size>()), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac")}.split(S{LITERAL("  ")}), alwaysTrue));

  ASSERT_EQ(2, count(SV{LITERAL("ac  ac")}.split(stds{LITERAL("  ")}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(2, count(SV{LITERAL("ac  ac")}.split(stdsv{LITERAL("  ")}), alwaysTrue));
#endif

  SV str1{LITERAL("abc  abc")};
  ASSERT_EQ(2, count(str1.split(LITERAL("  ")), alwaysTrue));
  ASSERT_EQ(2, count(str1.split(LITERAL("  ")), eq(LITERAL("abc"))));

  ASSERT_EQ(1, count(str1.split(LITERAL("  "), 0), alwaysTrue));
  ASSERT_EQ(1, count(str1.split(LITERAL("  "), 0), eq(LITERAL("abc  abc"))));

  ASSERT_EQ(2, count(str1.split(LITERAL(' '), 1), alwaysTrue));
  ASSERT_EQ(1, count(str1.split(LITERAL(' '), 1), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(str1.split(LITERAL(' '), 1), eq(LITERAL(" abc"))));

  using ACAlloc = typename ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));
  ASSERT_EQ(2, count(SV{LITERAL("abc  abc1__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(SV{LITERAL("abc  abc1__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc1"))));

  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, ACAlloc()), alwaysTrue));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc"))));
  ASSERT_EQ(2, count(SV{LITERAL("abc  abc1__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(SV{LITERAL("abc  abc1__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc1"))));

  SV str2{LITERAL("abc  abc__abc")};
  ASSERT_EQ(3, count(str2.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(3, count(str2.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, ACAlloc()), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc"))));

  std::vector<SV> sepsStrs{LITERAL("  "), LITERAL("__")};
  ASSERT_EQ(3, count(str2.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(sepsStrs), eq(LITERAL("abc"))));

  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(sepsStrs), eq(LITERAL("abc"))));

  ASSERT_EQ(4, count(SV{LITERAL("  abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("  abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(SV{LITERAL("  abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(4, count(SV{LITERAL("abc  abc__abc__")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("abc  abc__abc__")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc__")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(4, count(SV{LITERAL("abc  abc  __abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("abc  abc  __abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc  __abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(6, count(SV{LITERAL("__abc  abc  __abc  ")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(SV{LITERAL("__abc  abc  __abc  ")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(SV{LITERAL("__abc  abc  __abc  ")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(1, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, 0), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, 0), eq(LITERAL("abc  abc__abc"))));

  ASSERT_EQ(2, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, 1), alwaysTrue));
  ASSERT_EQ(1, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, 1), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}, 1), eq(LITERAL("abc__abc"))));

  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<CHAR_TYPE const*>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<stds>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(3, count(SV{LITERAL("abc  abc__abc")}.split(std::vector<stdsv>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
#endif
}

TEST(STRING_VIEW_TEST_GROUP, ostream) {
  oss oss;
  SV const sv{LITERAL(" abc ")};
  oss << sv;
  ASSERT_EQ(oss.str(), LITERAL(" abc "));
}

TEST(STRING_VIEW_TEST_GROUP, findClient) {
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.find(LITERAL('b')), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.find(LITERAL('d')), std::vector<int>{}));

  SV const sv {LITERAL("test test test")};
  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("test")), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("testtesttest")}.find(LITERAL("test")), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test")}.find(LITERAL("test")), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test ")}.find(LITERAL("test")), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test tes")}.find(LITERAL("test")), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test")}.find(LITERAL("test")), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test")}.find(LITERAL("test")), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test ")}.find(LITERAL("test")), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test tes")}.find(LITERAL("test")), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test ")}.find(LITERAL("test")), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test tes")}.find(LITERAL("test")), std::vector<int> {4}));

  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("testtesttest")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test ")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test tes")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test ")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test tes")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test ")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test tes")}.find(LITERAL("test"), TrackerAllocator<Size>()), std::vector<int> {4}));
}

TEST(STRING_VIEW_TEST_GROUP, findProjectionClient) {
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.find(LITERAL('B'), toupper), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.find(LITERAL('D'), toupper), std::vector<int>{}));

  SV const sv {LITERAL("test test test")};
  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("testtesttest")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test ")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test tes")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test")}.find(LITERAL("TEST"), toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test")}.find(LITERAL("TEST"), toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test ")}.find(LITERAL("TEST"), toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test tes")}.find(LITERAL("TEST"), toupper), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test ")}.find(LITERAL("TEST"), toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test tes")}.find(LITERAL("TEST"), toupper), std::vector<int> {4}));

  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("testtesttest")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test test ")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("test test tes")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test test ")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL(" test test tes")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test test ")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(SV {LITERAL("est test tes")}.find(LITERAL("TEST"), toupper, TrackerAllocator<Size>()), std::vector<int> {4}));
}

TEST(STRING_VIEW_TEST_GROUP, findFirstClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL('b')), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL('d')), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("bc")), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("bd")), SV::npos);

  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("bc"), TrackerAllocator<Size>()), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("bd"), TrackerAllocator<Size>()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findProjectionFirstClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL('B'), toupper), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL('D'), toupper), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("BC"), toupper), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("BD"), toupper), SV::npos);

  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("BC"), toupper, TrackerAllocator<Size>()), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirst(LITERAL("BD"), toupper, TrackerAllocator<Size>()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findLastClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL('b')), 3);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL('d')), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcbc")}.findLast(LITERAL("bc")), 3);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL("bd")), SV::npos);

  ASSERT_EQ(SV{LITERAL("abcbc")}.findLast(LITERAL("bc"), TrackerAllocator<Size>()), 3);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL("bd"), TrackerAllocator<Size>()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findProjectionLastClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL('B'), toupper), 3);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL('D'), toupper), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcbc")}.findLast(LITERAL("BC"), toupper), 3);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL("BD"), toupper), SV::npos);

  ASSERT_EQ(SV{LITERAL("abcbc")}.findLast(LITERAL("BC"), toupper, TrackerAllocator<Size>()), 3);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLast(LITERAL("BD"), toupper, TrackerAllocator<Size>()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findOfClient) {
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('a'), LITERAL('c')}), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('d')}), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.findOf(LITERAL("ac")), std::vector<int>{0, 2}));

  SV const sv1 {LITERAL("abc bcd cde def")};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc bcd cde def")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("c bcd cde def")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def ")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde de")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {0, 3}));

  using ACAlloc = typename impl::ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc bcd cde def")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("c bcd cde def")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def ")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde de")}.findOf(std::vector<SV>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {0, 3}));
}

TEST(STRING_VIEW_TEST_GROUP, findProjectedOfClient) {
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('A'), LITERAL('C')}, toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('D')}, toupper), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(SV{LITERAL("abcb")}.findOf(LITERAL("AC"), toupper), std::vector<int>{0, 2}));

  SV const sv1 {LITERAL("abc bcd cde def")};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc bcd cde def")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("c bcd cde def")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def ")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde de")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {0, 3}));

  using ACAlloc = typename impl::ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc bcd cde def")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("c bcd cde def")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde def ")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("bc bcd cde de")}.findOf(std::vector<SV>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {0, 3}));
}

TEST(STRING_VIEW_TEST_GROUP, findFirstOfClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('c'), LITERAL('b')}), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(LITERAL("cb")), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('d')}), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{}), SV::npos);

  SV const sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("ggg")}), SV::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{}), SV::npos);

  using ACAlloc = typename impl::ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("ggg")}, ACAlloc()), SV::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{}, ACAlloc()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findProjectedFirstOfClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('C'), LITERAL('B')}, toupper), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(LITERAL("CB"), toupper), 1);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('D')}, toupper), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{}, toupper), SV::npos);

  SV sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("GGG")}, toupper), SV::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{}, toupper), SV::npos);

  using ACAlloc = typename impl::ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{LITERAL("GGG")}, toupper, ACAlloc()), SV::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<SV>{}, toupper, ACAlloc()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findLastOfClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('c'), LITERAL('b')}), 3);
  ASSERT_EQ(SV{LITERAL("abcbc")}.findLastOf(LITERAL("cb")), 4);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('d')}), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{}), SV::npos);

  SV const sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("ggg")}), SV::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{}), SV::npos);

  using ACAlloc = typename impl::ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("ggg")}, ACAlloc()), SV::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{}, ACAlloc()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findProjectedLastOfClient) {
  ASSERT_EQ(SV{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('C'), LITERAL('B')}, toupper), 3);
  ASSERT_EQ(SV{LITERAL("abcbc")}.findLastOf(LITERAL("CB"), toupper), 4);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('D')}, toupper), SV::npos);
  ASSERT_EQ(SV{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{}, toupper), SV::npos);

  SV const sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("GGG")}, toupper), SV::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{}, toupper), SV::npos);

  using ACAlloc = typename impl::ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{LITERAL("GGG")}, toupper, ACAlloc()), SV::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<SV>{}, toupper, ACAlloc()), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findNotOfClient) {
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc")}.findNotOf(LITERAL("b")), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc")}.findNotOf(std::vector<CHAR_TYPE>{LITERAL('b')}), std::vector<int>{0, 2}));
}

TEST(STRING_VIEW_TEST_GROUP, findProjectedNotOfClient) {
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc")}.findNotOf(LITERAL("B"), toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(SV{LITERAL("abc")}.findNotOf(std::vector<int>{LITERAL('B')}, toupper), std::vector<int>{0, 2}));
}

TEST(STRING_VIEW_TEST_GROUP, findFirstNotOfClient) {
  ASSERT_EQ(SV{LITERAL("abc")}.findFirstNotOf(LITERAL("a")), 1);
  ASSERT_EQ(SV{LITERAL("abc")}.findFirstNotOf(LITERAL("abc")), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findProjectedFirstNotOfClient) {
  ASSERT_EQ(SV{LITERAL("abc")}.findFirstNotOf(LITERAL("A"), toupper), 1);
  ASSERT_EQ(SV{LITERAL("abc")}.findFirstNotOf(LITERAL("ABC"), toupper), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findLastNotOfClient) {
  ASSERT_EQ(SV{LITERAL("abca")}.findLastNotOf(LITERAL("a")), 2);
  ASSERT_EQ(SV{LITERAL("abc")}.findLastNotOf(LITERAL("abc")), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findProjectedLastNotOfClient) {
  ASSERT_EQ(SV{LITERAL("abca")}.findLastNotOf(LITERAL("A"), toupper), 2);
  ASSERT_EQ(SV{LITERAL("abc")}.findLastNotOf(LITERAL("ABC"), toupper), SV::npos);
}

TEST(STRING_VIEW_TEST_GROUP, findExtraCov) {
  auto r1 = SV{LITERAL("abc")}.find(LITERAL("bc"));
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

TEST(STRING_VIEW_TEST_GROUP, findExtraCov2) {
  auto r1 = SV{LITERAL("abc")}.find(LITERAL("BC"), toupper);
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

TEST(STRING_VIEW_TEST_GROUP, loremIpsumFind) {
  auto r = SV{LITERAL(R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.)")}
  .findOf(std::vector<SV>{LITERAL("Lorem"), LITERAL("ipsum"), LITERAL("dolor"), LITERAL("sit"), LITERAL("amet"), LITERAL("consectetur"),
    LITERAL("adipiscing"), LITERAL("elit"),
    LITERAL("sed"), LITERAL("do"), LITERAL("eiusmod"), LITERAL("tempor"), LITERAL("incididunt"), LITERAL("ut"), LITERAL("labore"), LITERAL("et"), LITERAL("dolore"),LITERAL("magna"), LITERAL("aliqua"),
LITERAL("Ut"), LITERAL("enim"), LITERAL("ad"), LITERAL("minim"), LITERAL("veniam"), LITERAL("quis"), LITERAL("nostrud"), LITERAL("exercitation"), LITERAL("ullamco"), LITERAL("laboris"),
LITERAL("nisi"), LITERAL("ut"), LITERAL("aliquip"), LITERAL("ex"), LITERAL("ea"), LITERAL("commodo"), LITERAL("consequat"),LITERAL(" Duis"), LITERAL("aute"), LITERAL("irure"), LITERAL("dolor"), LITERAL("in"),
LITERAL("reprehenderit"), LITERAL("in"), LITERAL("voluptate"), LITERAL("velit"), LITERAL("esse"), LITERAL("cillum"), LITERAL("dolore"), LITERAL("eu"), LITERAL("fugiat"), LITERAL("nulla"),
    LITERAL("pariatur"),
LITERAL("Excepteur"), LITERAL("sint"), LITERAL("occaecat"), LITERAL("cupidatat"), LITERAL("non"), LITERAL("proident"),
LITERAL("sunt"), LITERAL("in"), LITERAL("culpa"), LITERAL("qui"), LITERAL("officia"), LITERAL("deserunt"), LITERAL("mollit"), LITERAL("anim"), LITERAL("id"), LITERAL("est"), LITERAL("laborum")});

  for (auto it = r.begin(); it != r.end(); ++it) {
    // do nothing, loop check
    ASSERT_GE(*it, 0);
  }
}

TEST(STRING_VIEW_TEST_GROUP, loremIpsumFindTracked) {
  using ACAlloc = typename impl::ahoCorasick::AhoCorasickAllocatorBuilder<TrackerAllocator>::Type<CHAR_TYPE>;
  auto r = SV{LITERAL(R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.)")}
  .findOf(std::vector<SV>{LITERAL("Lorem"), LITERAL("ipsum"), LITERAL("dolor"), LITERAL("sit"), LITERAL("amet"), LITERAL("consectetur"),
    LITERAL("adipiscing"), LITERAL("elit"),
    LITERAL("sed"), LITERAL("do"), LITERAL("eiusmod"), LITERAL("tempor"), LITERAL("incididunt"), LITERAL("ut"), LITERAL("labore"), LITERAL("et"), LITERAL("dolore"),LITERAL("magna"), LITERAL("aliqua"),
LITERAL("Ut"), LITERAL("enim"), LITERAL("ad"), LITERAL("minim"), LITERAL("veniam"), LITERAL("quis"), LITERAL("nostrud"), LITERAL("exercitation"), LITERAL("ullamco"), LITERAL("laboris"),
LITERAL("nisi"), LITERAL("ut"), LITERAL("aliquip"), LITERAL("ex"), LITERAL("ea"), LITERAL("commodo"), LITERAL("consequat"),LITERAL(" Duis"), LITERAL("aute"), LITERAL("irure"), LITERAL("dolor"), LITERAL("in"),
LITERAL("reprehenderit"), LITERAL("in"), LITERAL("voluptate"), LITERAL("velit"), LITERAL("esse"), LITERAL("cillum"), LITERAL("dolore"), LITERAL("eu"), LITERAL("fugiat"), LITERAL("nulla"),
    LITERAL("pariatur"),
LITERAL("Excepteur"), LITERAL("sint"), LITERAL("occaecat"), LITERAL("cupidatat"), LITERAL("non"), LITERAL("proident"),
LITERAL("sunt"), LITERAL("in"), LITERAL("culpa"), LITERAL("qui"), LITERAL("officia"), LITERAL("deserunt"), LITERAL("mollit"), LITERAL("anim"), LITERAL("id"), LITERAL("est"), LITERAL("laborum")}, ACAlloc());

  for (auto it = r.begin(); it != r.end(); ++it) {
    // do nothing, loop check
    ASSERT_GE(*it, 0);
  }
}

TEST(STRING_VIEW_TEST_GROUP, functional) {
  SV const sv{LITERAL("abcd")};

  int count = 0;
  sv.forEach([&count](CHAR_TYPE const c) {
    (void) c;
    ++count;
  });

  ASSERT_EQ(count, 4);

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

TEST(STRING_VIEW_TEST_GROUP, containsAllocation) {
  SV const sv {LITERAL("abcd")};
  ASSERT_TRUE(sv.contains(LITERAL("bc"), Allocator<Size>()));
  ASSERT_TRUE(sv.contains(LITERAL("BC"), toupper, Allocator<Size>()));
}

TEST(STRING_VIEW_TEST_GROUP, startsEndsWith) {
  SV const sv {LITERAL("abcd")};

  ASSERT_TRUE(sv.startsWith(LITERAL('a')));
  ASSERT_FALSE(sv.startsWith(LITERAL('b')));
  ASSERT_TRUE(sv.endsWith(LITERAL('d')));
  ASSERT_FALSE(sv.endsWith(LITERAL('c')));

  ASSERT_TRUE(sv.startsWith(LITERAL("ab")));
  ASSERT_FALSE(sv.startsWith(LITERAL("bb")));
  ASSERT_TRUE(sv.startsWith(LITERAL("")));
  ASSERT_FALSE(sv.startsWith(LITERAL("abcde")));
  ASSERT_TRUE(sv.endsWith(LITERAL("cd")));
  ASSERT_FALSE(sv.endsWith(LITERAL("dd")));
  ASSERT_TRUE(sv.endsWith(LITERAL("")));
  ASSERT_FALSE(sv.endsWith(LITERAL("aabcd")));
}

TEST(STRING_VIEW_TEST_GROUP, literal) {
  using namespace cds::literals;
  ASSERT_EQ(LITERAL_OP("abcd"), LITERAL("abcd"));
}

TEST(STRING_VIEW_TEST_GROUP, constructions) {
  SV const sv1 = LITERAL("abcd");
  CHAR_TYPE const buf[] = LITERAL("abcd");
  SV const sv2 = buf;
  stds str = LITERAL("abcd");
  SV const sv3 = str;
  ASSERT_EQ(sv1, sv2);
  ASSERT_EQ(sv1, sv3);
  S const str2 = LITERAL("abcd");
  SV const sv4 = str2;
  ASSERT_EQ(sv4, sv1);
}

TEST(STRING_VIEW_TEST_GROUP, assignments) {
  SV sv;
  sv = LITERAL("abcd");
  ASSERT_EQ(sv, LITERAL("abcd"));
  CHAR_TYPE const buf[] = LITERAL("abcd");
  sv = buf;
  ASSERT_EQ(sv, LITERAL("abcd"));
  stds const sv3 = LITERAL("abcd");
  sv = sv3;
  ASSERT_EQ(sv, LITERAL("abcd"));
  S const str2 = LITERAL("abcd");
  sv = str2;
  ASSERT_EQ(sv, LITERAL("abcd"));
}

TEST(STRING_VIEW_TEST_GROUP, strConv) {
  SV const sv {LITERAL("abcd")};
  ASSERT_EQ(sv.str(), LITERAL("abcd"));
  ASSERT_EQ(sv.toString(), LITERAL("abcd"));
}

TEST(STRING_VIEW_TEST_GROUP, ltrim) {
  SV const a1 = LITERAL("aabbaacc");
  ASSERT_EQ(a1.ltrim(LITERAL('a')), LITERAL("bbaacc"));
  CHAR_TYPE const* b = LITERAL("ab");
  ASSERT_EQ(a1.ltrim(b), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(LITERAL("ab")), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(SV{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(stds{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(S{LITERAL("ab")}), LITERAL("cc"));

  SV const a2 = LITERAL("  abcd");
  ASSERT_EQ(a2.ltrim(), LITERAL("abcd"));
}

TEST(STRING_VIEW_TEST_GROUP, rtrim) {
  SV const a1 = LITERAL("aabbaacc");
  ASSERT_EQ(a1.rtrim(LITERAL('c')), LITERAL("aabbaa"));
  CHAR_TYPE const* b = LITERAL("ac");
  ASSERT_EQ(a1.rtrim(b), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(LITERAL("ac")), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(SV{LITERAL("ac")}), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(stds{LITERAL("ac")}), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(S{LITERAL("ac")}), LITERAL("aabb"));

  SV const a2 = LITERAL("abcd  ");
  ASSERT_EQ(a2.rtrim(), LITERAL("abcd"));
}

TEST(STRING_VIEW_TEST_GROUP, trim) {
  SV const a1 = LITERAL("aabbccbbaa");
  ASSERT_EQ(a1.trim(LITERAL('a')), LITERAL("bbccbb"));
  CHAR_TYPE const* b = LITERAL("ab");
  ASSERT_EQ(a1.trim(b), LITERAL("cc"));
  ASSERT_EQ(a1.trim(LITERAL("ab")), LITERAL("cc"));
  ASSERT_EQ(a1.trim(SV{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.trim(stds{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.trim(S{LITERAL("ab")}), LITERAL("cc"));

  SV const a2 = LITERAL("  abcd  ");
  ASSERT_EQ(a2.trim(), LITERAL("abcd"));
}

TEST(STRING_VIEW_TEST_GROUP, removePrefix) {
  SV const a1 = LITERAL("abc");
  ASSERT_EQ(a1.removePrefix(LITERAL('a')), LITERAL("bc"));
  ASSERT_EQ(a1.removePrefix(LITERAL("ab")), LITERAL("c"));
  ASSERT_EQ(a1.removePrefix(LITERAL("ac")), LITERAL("abc"));
  ASSERT_EQ(a1.removePrefix(LITERAL("abc")), LITERAL(""));
  ASSERT_EQ(a1.removePrefix(LITERAL("abcd")), LITERAL("abc"));
  ASSERT_EQ(a1.removePrefix(LITERAL("abeg")), LITERAL("abc"));
}

TEST(STRING_VIEW_TEST_GROUP, removeSuffix) {
  SV const a1 = LITERAL("abc");
  ASSERT_EQ(a1.removeSuffix(LITERAL('c')), LITERAL("ab"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("bc")), LITERAL("a"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("ac")), LITERAL("abc"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("abc")), LITERAL(""));
  ASSERT_EQ(a1.removeSuffix(LITERAL("fabc")), LITERAL("abc"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("ffbc")), LITERAL("abc"));
}

#ifdef DCR_SINCECPP11
namespace cexpr {
namespace {
constexpr SV cxx11_def_ctr() {
  return SV{};
}

constexpr SV cxx11_copy_ctr(SV const& sv) {
  return SV{sv};
}

constexpr SV cxx11_move_ctr(SV&& sv) {
  return SV{cds::move(sv)};
}

template <typename C> constexpr SV cxx11_convertible_ctr(C&& convertible) {
  return SV{cds::forward<C>(convertible)};
}

constexpr CHAR_TYPE const* cxx11_data(SV const& sv) {
  return sv.data();
}

constexpr Size cxx11_length(SV const& sv) {
  return sv.length();
}

constexpr Size cxx11_size(SV const& sv) {
  return sv.size();
}

constexpr bool cxx11_empty(SV const& sv) {
  return sv.empty();
}

constexpr bool cxx11_operator_bool(SV const& sv) {
  return static_cast<bool>(sv);
}

constexpr typename SV::Iterator cxx11_begin(SV const& sv) {
  return sv.begin();
}

constexpr typename SV::Iterator cxx11_end(SV const& sv) {
  return sv.end();
}

constexpr typename SV::ConstIterator cxx11_cbegin(SV const& sv) {
  return sv.cbegin();
}

constexpr typename SV::ConstIterator cxx11_cend(SV const& sv) {
  return sv.cend();
}

constexpr typename SV::ReverseIterator cxx11_rbegin(SV const& sv) {
  return sv.rbegin();
}

constexpr typename SV::ReverseIterator cxx11_rend(SV const& sv) {
  return sv.rend();
}

constexpr typename SV::ConstReverseIterator cxx11_crbegin(SV const& sv) {
  return sv.crbegin();
}

constexpr typename SV::ConstReverseIterator cxx11_crend(SV const& sv) {
  return sv.crend();
}

constexpr CHAR_TYPE cxx11_operator_sqb(SV const& sv, int idx) {
  return sv[idx];
}

constexpr CHAR_TYPE cxx11_at(SV const& sv, int idx) {
  return sv.at(idx);
}

constexpr CHAR_TYPE cxx11_front(SV const& sv) {
  return sv.front();
}

constexpr CHAR_TYPE cxx11_back(SV const& sv) {
  return sv.back();
}
} // namespace SVCexpr
} // namespace cexpr

TEST(STRING_VIEW_TEST_GROUP, cpp11Constexpr) {
  using namespace cexpr;
  static_assert(cxx11_def_ctr().empty(), "failed constexpr");
  static_assert(cxx11_copy_ctr(SV{}).empty(), "failed constexpr");
  static_assert(cxx11_move_ctr(SV{}).empty(), "failed constexpr");
  static_assert(cxx11_convertible_ctr(LITERAL("")).empty(), "failed constexpr");
  static_assert(cxx11_convertible_ctr(LITERAL("abc")).length() == 3, "failed constexpr");
  static_assert(cxx11_convertible_ctr(nullptr).empty(), "failed constexpr");
  static_assert(cxx11_data(SV{nullptr}) == nullptr, "failed constexpr");
  static_assert(cxx11_length(SV{nullptr}) == 0u, "failed constexpr");
  static_assert(cxx11_length(SV{LITERAL("")}) == 0u, "failed constexpr");
  static_assert(cxx11_length(SV{LITERAL("abc")}) == 3u, "failed constexpr");
  static_assert(cxx11_size(SV{nullptr}) == 0u, "failed constexpr");
  static_assert(cxx11_size(SV{LITERAL("")}) == 0u, "failed constexpr");
  static_assert(cxx11_size(SV{LITERAL("abc")}) == 3u, "failed constexpr");
  static_assert(cxx11_empty(SV{nullptr}), "failed constexpr");
  static_assert(cxx11_empty(SV{LITERAL("")}), "failed constexpr");
  static_assert(!cxx11_empty(SV{LITERAL("abc")}), "failed constexpr");
  static_assert(!cxx11_operator_bool(SV{nullptr}), "failed constexpr");
  static_assert(!cxx11_operator_bool(SV{LITERAL("")}), "failed constexpr");
  static_assert(cxx11_operator_bool(SV{LITERAL("abc")}), "failed constexpr");
  static_assert(cxx11_begin(nullptr) == cxx11_end(nullptr), "failed constexpr");
  static_assert(cxx11_cbegin(nullptr) == cxx11_cend(nullptr), "failed constexpr");
  static_assert(cxx11_rbegin(nullptr) == cxx11_rend(nullptr), "failed constexpr");
  static_assert(cxx11_crbegin(nullptr) == cxx11_crend(nullptr), "failed constexpr");
  static_assert(cxx11_operator_sqb(LITERAL("abc"), 1) == LITERAL('b'), "failed constexpr");
  static_assert(cxx11_at(LITERAL("abc"), 1) == LITERAL('b'), "failed constexpr");
  static_assert(cxx11_front(LITERAL("abc")) == LITERAL('a'), "failed constexpr");
  static_assert(cxx11_back(LITERAL("abc")) == LITERAL('c'), "failed constexpr");

  using namespace cds::literals;
  static_assert(LITERAL_OP("").empty(), "failed constexpr");
  static_assert(!LITERAL_OP("abc").empty(), "failed constexpr");
}
#endif

#ifdef DCR_SINCECPP14
namespace cexpr {
namespace {
constexpr auto cxx14_copy_assign(SV const& data) {
  SV sv;
  sv = data;
  return sv == data;
}

constexpr auto cxx14_move_assign(SV data) {
  SV sv;
  sv = cds::move(data);
  return sv == data;
}

constexpr auto cxx14_clear(SV init) {
  init.clear();
  return init.empty();
}

constexpr auto cxx14_sub(SV const& sv, int idx) {
  return sv.sub(idx);
}

constexpr auto cxx14_sub(SV const& sv, int idx1, int idx2) {
  return sv.sub(idx1, idx2);
}

constexpr auto cxx14_operator_rnb(SV const& sv, int idx) {
  return sv(idx);
}

constexpr auto cxx14_operator_rnb(SV const& sv, int idx1, int idx2) {
  return sv(idx1, idx2);
}

template <typename N> constexpr auto cxx14_contains(SV sv, N&& needle) {
  return sv.contains(cds::forward<N>(needle));
}

template <typename N> constexpr auto cxx14_startsWith(SV sv, N&& needle) {
  return sv.startsWith(cds::forward<N>(needle));
}

template <typename N> constexpr auto cxx14_endsWith(SV sv, N&& needle) {
  return sv.endsWith(cds::forward<N>(needle));
}

template <typename N> constexpr auto cxx14_split(SV sv, N&& n, int cnt) {
  auto r = sv.split(cds::forward<N>(n));
  int i = 0;
  for (auto b = r.begin(); b != r.end(); ++b, ++i) {
    // nothing
  }
  return i == cnt;
}

template <typename N> constexpr auto cxx14_ltrim(SV sv, N&& n) {
  return sv.ltrim(cds::forward<N>(n));
}

template <typename N> constexpr auto cxx14_rtrim(SV sv, N&& n) {
  return sv.rtrim(cds::forward<N>(n));
}

template <typename N> constexpr auto cxx14_trim(SV sv, N&& n) {
  return sv.trim(cds::forward<N>(n));
}

template <typename N> constexpr auto cxx14_removePrefix(SV sv, N&& n) {
  return sv.removePrefix(cds::forward<N>(n));
}

template <typename N> constexpr auto cxx14_removeSuffix(SV sv, N&& n) {
  return sv.removeSuffix(cds::forward<N>(n));
}
} // namespace
} // namespace cexpr

TEST(STRING_VIEW_TEST_GROUP, cpp14Constexpr) {
  using namespace cexpr;
  static_assert(cxx14_copy_assign(nullptr), "constexpr failed");
  static_assert(cxx14_copy_assign(LITERAL("")), "constexpr failed");
  static_assert(cxx14_copy_assign(LITERAL("abc")), "constexpr failed");
  static_assert(cxx14_move_assign(nullptr), "constexpr failed");
  static_assert(cxx14_move_assign(LITERAL("")), "constexpr failed");
  static_assert(cxx14_move_assign(LITERAL("abc")), "constexpr failed");
  static_assert(cxx14_clear(nullptr), "constexpr failed");
  static_assert(cxx14_clear(LITERAL("")), "constexpr failed");
  static_assert(cxx14_clear(LITERAL("abc")), "constexpr failed");
  static_assert(cxx14_sub(LITERAL("abc"), 1) == LITERAL("bc"), "failed constexpr");
  static_assert(cxx14_sub(LITERAL("abc"), 1, 2) == LITERAL("b"), "failed constexpr");
  static_assert(cxx14_operator_rnb(LITERAL("abc"), 1) == LITERAL("bc"), "failed constexpr");
  static_assert(cxx14_operator_rnb(LITERAL("abc"), 1, 2) == LITERAL("b"), "failed constexpr");
  static_assert(!cxx14_contains(nullptr, LITERAL('a')), "constexpr failed");
  static_assert(!cxx14_contains(LITERAL(""), LITERAL('a')), "constexpr failed");
  static_assert(cxx14_contains(LITERAL("a"), LITERAL('a')), "constexpr failed");
  static_assert(!cxx14_contains(LITERAL("bcc"), LITERAL('a')), "constexpr failed");
  static_assert(cxx14_contains(LITERAL("babc"), LITERAL('a')), "constexpr failed");
  static_assert(cxx14_startsWith(LITERAL("ababc"), LITERAL('a')), "constexpr failed");
  static_assert(cxx14_endsWith(LITERAL("ababc"), LITERAL('c')), "constexpr failed");
  static_assert(cxx14_startsWith(LITERAL("ababc"), LITERAL("ab")), "constexpr failed");
  static_assert(cxx14_endsWith(LITERAL("ababc"), LITERAL("bc")), "constexpr failed");
  static_assert(cxx14_split(LITERAL("abcab"), LITERAL('b'), 3), "constexpr failed");
  static_assert(*SV{LITERAL("ab ab")}.split(LITERAL(' ')).begin() == LITERAL("ab"), "constexpr failed");
  static_assert(cxx14_ltrim(LITERAL("  ab"), LITERAL(' ')) == LITERAL("ab"), "constexpr failed");
  static_assert(cxx14_ltrim(LITERAL("  ab"), LITERAL(" ")) == LITERAL("ab"), "constexpr failed");
  static_assert(cxx14_rtrim(LITERAL("ab  "), LITERAL(' ')) == LITERAL("ab"), "constexpr failed");
  static_assert(cxx14_rtrim(LITERAL("ab  "), LITERAL(" ")) == LITERAL("ab"), "constexpr failed");
  static_assert(cxx14_trim(LITERAL("  ab  "), LITERAL(' ')) == LITERAL("ab"), "constexpr failed");
  static_assert(cxx14_trim(LITERAL("  ab  "), LITERAL(" ")) == LITERAL("ab"), "constexpr failed");
  static_assert(cxx14_removePrefix(LITERAL("   ab"), LITERAL("  ")) == LITERAL(" ab"), "constexpr failed");
  static_assert(cxx14_removeSuffix(LITERAL("ab   "), LITERAL("  ")) == LITERAL("ab "), "constexpr failed");
}
#endif

#ifdef DCR_SINCECPP17

TEST(STRING_VIEW_TEST_GROUP, constructions17) {
  stdsv strv = LITERAL("abcd");
  SV const sv4 = strv;
  ASSERT_EQ(sv4, LITERAL("abcd"));
}

TEST(STRING_VIEW_TEST_GROUP, assignments17) {
  SV sv;
  stdsv sv4 = LITERAL("abcd");
  sv = sv4;
  ASSERT_EQ(sv, LITERAL("abcd"));
}
#endif

#ifdef DCR_SINCECPP20
TEST(STRING_VIEW_TEST_GROUP, Spaceship) {
  CHAR_TYPE const a1[] = LITERAL("abcd");
  CHAR_TYPE const a2[] = LITERAL("abcd");
  assert(+a1 != +a2 && LITERAL("Something weird"));
  SV sv1 = a1;
  SV sv2 = a2;
  SV sv3 = LITERAL("abc");
  SV sv4 = LITERAL("abcde");

  ASSERT_EQ(sv1 <=> sv1, std::strong_ordering::equivalent);
  ASSERT_EQ(sv1 <=> sv2, std::strong_ordering::equal);
  ASSERT_EQ(sv1 <=> sv3, std::strong_ordering::greater);
  ASSERT_EQ(sv1 <=> sv4, std::strong_ordering::less);
}

TEST(STRING_VIEW_TEST_GROUP, SpaceshipCompatLiteral) {
  SV sv1 = LITERAL("abc");
  ASSERT_EQ(sv1 <=> LITERAL("abc"), std::strong_ordering::equal);
  ASSERT_EQ(sv1 <=> LITERAL("abcd"), std::strong_ordering::less);
  ASSERT_EQ(sv1 <=> LITERAL("ab"), std::strong_ordering::greater);
  ASSERT_EQ(LITERAL("abc") <=> sv1, std::strong_ordering::equal);
  ASSERT_EQ(LITERAL("abcd") <=> sv1, std::strong_ordering::greater);
  ASSERT_EQ(LITERAL("ab") <=> sv1, std::strong_ordering::less);
}

namespace {
consteval auto evaluate() {
  SV const sv{LITERAL("ab  ab1__ab")};
  std::array<SV, 2> const svr{LITERAL("  "), LITERAL("__")};
  auto const r = sv.split(svr);
  auto it = r.begin();
  ++it;
  auto const b = *it == LITERAL("ab1");
  return b;
}
}

namespace cexpr {
namespace {
consteval auto cxx20_str(SV sv) {
  auto s = sv.str();
  return s == sv;
}

consteval auto cxx20_toString(SV sv) {
  auto s = sv.toString();
  return s == sv;
}

consteval auto cxx20_contains(SV sv, auto n) {
  return sv.contains(n);
}

consteval auto cxx20_split_i(auto b, auto e) {
  return b == e;
}

consteval auto cxx20_split_i(auto b, auto e, auto f, auto... r) {
  return b != e && *b == f && cxx20_split_i(++b, e, r...);
}

consteval auto cxx20_split(SV sv, auto s, auto... t) {
  auto const r = sv.split(s);
  return cxx20_split_i(r.begin(), r.end(), t...);
}
} // namespace
} // namespace cexpr

TEST(STRING_VIEW_TEST_GROUP, cpp20Constexpr) {
  using namespace cexpr;
  static_assert(*SV{LITERAL("ab  ab")}.split(LITERAL("  ")).begin() == LITERAL("ab"), "constexpr failed");
  static_assert(evaluate(), "constexpr failed");
  static_assert(cxx20_str(nullptr), "constexpr failed");
  static_assert(cxx20_str(LITERAL("")), "constexpr failed");
  static_assert(cxx20_str(LITERAL("abc")), "constexpr failed");
  static_assert(cxx20_toString(nullptr), "constexpr failed");
  static_assert(cxx20_toString(LITERAL("")), "constexpr failed");
  static_assert(cxx20_toString(LITERAL("abc")), "constexpr failed");
  static_assert(cxx20_contains(LITERAL("abc"), LITERAL("ab")), "constexpr failed");
  static_assert(cxx20_split(LITERAL("a b c"), LITERAL(' '), LITERAL("a"), LITERAL("b"), LITERAL("c")));
  static_assert(cxx20_split(LITERAL("a b c"), LITERAL(" "), LITERAL("a"), LITERAL("b"), LITERAL("c")));
  std::array<CHAR_TYPE, 1> constexpr sep1 {LITERAL(' ')};
  std::array<SV, 1> constexpr sep2 {LITERAL(" ")};
  static_assert(cxx20_split(LITERAL("a b c"), sep1, LITERAL("a"), LITERAL("b"), LITERAL("c")));
  static_assert(cxx20_split(LITERAL("a b c"), sep2, LITERAL("a"), LITERAL("b"), LITERAL("c")));
}
#endif
