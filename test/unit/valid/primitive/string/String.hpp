#include <cds/String>
#include <cds/StringView>
#include <cds/functional/Invoke>
#include <cds/functional/FunctionalInterface>
#include <cassert>
#include <iostream>
#include <array>

#include "UnitTest.hpp"
#include "../../Shared.hpp"
#include "../../TrackerAllocator.hpp"

#if CDS_ATTR(emulated_in_constexpr) && CDS_ATTR(cpp20)
#undef SBO_CAPACITY
#define SBO_CAPACITY 0
#endif

#define LATE_JOIN2(a, b) a ## b
#define LATE_JOIN(a, b) LATE_JOIN2(a, b)

#if CDS_ATTR(emulated_in_constexpr)
#define STRING_TEST_GROUP LATE_JOIN(LATE_JOIN(LATE_JOIN(S_, CHAR_TYPE), ALLOCATOR_TYPE), true)
#else
#define STRING_TEST_GROUP LATE_JOIN(LATE_JOIN(LATE_JOIN(S_, CHAR_TYPE), ALLOCATOR_TYPE), false)
#endif

namespace {
using cds::Allocator;
using testing::TrackerAllocator;
using SV = cds::impl::BaseStringView<CHAR_TYPE>;
using S = cds::impl::BaseString<CHAR_TYPE, cds::impl::StringUtils<CHAR_TYPE, cds::meta::StringTraits<CHAR_TYPE>>,
    ALLOCATOR_TYPE<CHAR_TYPE>>;
using stds = std::basic_string<CHAR_TYPE>;
using oss = std::basic_stringstream<CHAR_TYPE>;
#ifdef DCR_SINCECPP17
using stdsv = std::basic_string_view<CHAR_TYPE>;
#endif
using T = cds::meta::StringTraits<CHAR_TYPE>;
using cds::fwd;
using cds::mv;
using cds::xch;
} // namespace

TEST(STRING_TEST_GROUP, construction) {
  S const a = LITERAL("abc");
  CHAR_TYPE const buf[] = LITERAL("abc");
  S const b = buf;
  S c = stds(LITERAL("abc"));
  S const d = SV(LITERAL("abc"));

  S const e = d;
  S const f = mv(c);
  ASSERT_EQ(a, LITERAL("abc"));
  ASSERT_EQ(b, LITERAL("abc"));
  ASSERT_EQ(d, LITERAL("abc"));
  ASSERT_EQ(e, LITERAL("abc"));
  ASSERT_EQ(f, LITERAL("abc"));
}

TEST(STRING_TEST_GROUP, nonSbo) {
  S a = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  S b = a;
  S c = mv(b);

  ASSERT_EQ(a, LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
  ASSERT_EQ(c, LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}

TEST(STRING_TEST_GROUP, repeatedCopies) {
  SV src = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  SV src2 = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
            LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  S a = src;
  ASSERT_EQ(a, src);
  a = src;
  ASSERT_EQ(a, src);
  a = src;
  ASSERT_EQ(a, src);
  a = src;
  ASSERT_EQ(a, src);

  a = LITERAL("abc");
  ASSERT_EQ(a, LITERAL("abc"));

  a = src;
  ASSERT_EQ(a, src);

  a = src2;
  ASSERT_EQ(a, src2);
  a = src;
  ASSERT_EQ(a, src);
  a = src2;
  ASSERT_EQ(a, src2);
  a = LITERAL("abc");
  ASSERT_EQ(a, LITERAL("abc"));
  a = src2;
  ASSERT_EQ(a, src2);
}

TEST(STRING_TEST_GROUP, Compare) {
  S n = nullptr;
  S a = LITERAL("a");
  S b = LITERAL("b");
  S c = LITERAL("c");

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

TEST(STRING_TEST_GROUP, baseMembers) {
  S sv1;
  S sv2(sv1.data());
  S sv3(LITERAL("abcd"));
  S sv4(sv3.data());

  // x86 wchar_t and char32_t does not use SBO
  // ASSERT_NE(sv1.data(), nullptr);
  ASSERT_EQ(sv1.length(), 0u);
  ASSERT_EQ(sv1.size(), 0u);
  ASSERT_TRUE(sv1.empty());
  ASSERT_FALSE(sv1);

  // x86 wchar_t and char32_t does not use SBO
  // ASSERT_NE(sv2.data(), nullptr);
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

TEST(STRING_TEST_GROUP, iter) {
  S sv = LITERAL("abcd");
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

TEST(STRING_TEST_GROUP, CompareCompatLiteral) {
  S sv = LITERAL("abcd");
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

TEST(STRING_TEST_GROUP, Positionals) {
  S sv = LITERAL("abcd");
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

TEST(STRING_TEST_GROUP, Sub) {
  S sv = LITERAL("abcd");
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

TEST(STRING_TEST_GROUP, clearAndDestruct) {
  S a = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  a.clear();
}

TEST(STRING_TEST_GROUP, contains) {
  S sv = LITERAL("bC");
  ASSERT_FALSE(sv.contains(LITERAL('a')));
  ASSERT_TRUE(sv.contains(LITERAL('b')));
  ASSERT_TRUE(sv.contains(LITERAL('C')));
  ASSERT_FALSE(sv.contains(LITERAL('d')));

  ASSERT_FALSE(sv.contains(LITERAL('a'), T::lower));
  ASSERT_TRUE(sv.contains(LITERAL('b'), T::lower));
  ASSERT_TRUE(sv.contains(LITERAL('c'), T::lower));
  ASSERT_FALSE(sv.contains(LITERAL('d'), T::lower));
}

TEST(STRING_TEST_GROUP, containsS) {
  S sv = LITERAL("abcd");
  ASSERT_TRUE(sv.contains(LITERAL("bc"), testing::TrackerAllocator<cds::Size>()));
  ASSERT_FALSE(sv.contains(LITERAL("bd"), testing::TrackerAllocator<cds::Size>()));
}

TEST(STRING_TEST_GROUP, containsOf) {
  S sv = LITERAL("bC");
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

TEST(STRING_TEST_GROUP, find) {
  S const sv = LITERAL("abcb");

  auto lRng = sv.find(LITERAL('b'));
  auto lIt = lRng.begin();
  ASSERT_EQ(*lIt, 1);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(*lIt, 3);
  ASSERT_NE(lIt, lRng.end());
  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = S(LITERAL("abcb")).find(LITERAL('b'));
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
  for (auto e : fwd<Range>(rng)) {
    if (pred(e)) {
      ++count;
    }
  }
  return count;
}
}

TEST(STRING_TEST_GROUP, split) {
  using cds::functional::memFn;

  S sv1 = LITERAL("  abc abc abc  abc abc   ");
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

  S a{LITERAL("ab ab")};
  ASSERT_EQ(2, count(S{LITERAL("ab ab")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(2, count(S{LITERAL("ab ab")}.split(LITERAL(' ')), eq(LITERAL("ab"))));

  ASSERT_EQ(0, count(S{LITERAL("")}.split(LITERAL(' ')), alwaysTrue));

  ASSERT_EQ(3, count(S{LITERAL(" ac ac")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL(" ac ac")}.split(LITERAL(' ')), memFn(&SV::empty)));
  ASSERT_EQ(2, count(S{LITERAL(" ac ac")}.split(LITERAL(' ')), eq(LITERAL("ac"))));

  ASSERT_EQ(4, count(S{LITERAL("ad ad  ")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(2, count(S{LITERAL("ad ad  ")}.split(LITERAL(' ')), memFn(&SV::empty)));
  ASSERT_EQ(2, count(S{LITERAL("ad ad  ")}.split(LITERAL(' ')), eq(LITERAL("ad"))));

  auto e = memFn(&SV::empty);
  ASSERT_EQ(4, count(S{LITERAL("ae   ae")}.split(LITERAL(' ')), alwaysTrue));
  ASSERT_EQ(2, count(S{LITERAL("ae   ae")}.split(LITERAL(' ')), e));
  ASSERT_EQ(2, count(S{LITERAL("ae   ae")}.split(LITERAL(' ')), eq(LITERAL("ae"))));

  auto r = S{LITERAL("a b")}.split(LITERAL(' '));
  ASSERT_EQ(2, count(r, alwaysTrue));
  ASSERT_EQ(1, count(r, eq(LITERAL("a"))));
  ASSERT_EQ(1, count(r, eq(LITERAL("b"))));

  ASSERT_EQ(10, count(S{LITERAL("ae ; ae;ae ae; ae ;")}.split(std::vector<CHAR_TYPE>{LITERAL(' '), LITERAL(';')}), alwaysTrue));
  ASSERT_EQ(5, count(S{LITERAL("ae ; ae;ae ae; ae ;")}.split(std::vector<CHAR_TYPE>{LITERAL(' '), LITERAL(';')}), e));
  ASSERT_EQ(5, count(S{LITERAL("ae ; ae;ae ae; ae ;")}.split(std::vector<CHAR_TYPE>{LITERAL(' '), LITERAL(';')}), eq(LITERAL("ae"))));

  std::initializer_list<CHAR_TYPE> sep2 = {LITERAL(' '), LITERAL(';')};
  ASSERT_EQ(10, count(S{LITERAL("ae ; ae;ae ae; ae ;")}.split(sep2), alwaysTrue));
  ASSERT_EQ(5, count(S{LITERAL("ae ; ae;ae ae; ae ;")}.split(sep2), e));
  ASSERT_EQ(5, count(S{LITERAL("ae ; ae;ae ae; ae ;")}.split(sep2), eq(LITERAL("ae"))));

  ASSERT_EQ(1, count(S{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 0), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 0), eq(LITERAL("  ab   ab   ab  "))));

  ASSERT_EQ(2, count(S{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 1), e));
  ASSERT_EQ(1, count(S{LITERAL("  ab   ab   ab  ")}.split(LITERAL(' '), 1), eq(LITERAL(" ab   ab   ab  "))));

  ASSERT_EQ(3, count(S{LITERAL("ab  ab ab  ab")}.split(LITERAL("  ")), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ab  ab ab  ab")}.split(LITERAL("  ")), eq(LITERAL("ab ab"))));
  ASSERT_EQ(2, count(S{LITERAL("ab  ab ab  ab")}.split(LITERAL("  ")), eq(LITERAL("ab"))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(3, count(S{LITERAL("ab  ab ab  ab")}.split(LITERAL("  "), testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ab  ab ab  ab")}.split(LITERAL("  "), testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ab ab"))));
  ASSERT_EQ(2, count(S{LITERAL("ab  ab ab  ab")}.split(LITERAL("  "), testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ab"))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(LITERAL("  "),  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac ac   ac  "))));

  CHAR_TYPE const sep3[] = LITERAL("  ");
  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep3,  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac ac   ac  "))));

  auto const* sep4 = LITERAL("  ");
  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep4,  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE const*>(sep4),  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE const*>(sep4),  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE const*>(sep4),  1), eq(LITERAL("ac ac   ac  "))));

  CHAR_TYPE sep5[] = LITERAL("  ");
  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep5,  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep5,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep5,  1), eq(LITERAL("ac ac   ac  "))));

  CHAR_TYPE* sep6 = sep5;
  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep6,  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep6,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep6,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE*>(sep6),  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE*>(sep6),  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(static_cast<CHAR_TYPE*>(sep6),  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(S{LITERAL("  ")},  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(S{LITERAL("  ")},  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(S{LITERAL("  ")},  1), eq(LITERAL("ac ac   ac  "))));

  S sep7{LITERAL("  ")};
  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1, testing::TrackerAllocator<cds::Size>()), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac"))));
  ASSERT_EQ(1, count(S{LITERAL("ac  ac ac   ac  ")}.split(sep7,  1, testing::TrackerAllocator<cds::Size>()), eq(LITERAL("ac ac   ac  "))));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac")}.split(S{LITERAL("  ")}), alwaysTrue));

  ASSERT_EQ(2, count(S{LITERAL("ac  ac")}.split(stds{LITERAL("  ")}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(2, count(S{LITERAL("ac  ac")}.split(stdsv{LITERAL("  ")}), alwaysTrue));
#endif

  S str1{LITERAL("abc  abc")};
  ASSERT_EQ(2, count(str1.split(LITERAL("  ")), alwaysTrue));
  ASSERT_EQ(2, count(str1.split(LITERAL("  ")), eq(LITERAL("abc"))));

  ASSERT_EQ(1, count(str1.split(LITERAL("  "), 0), alwaysTrue));
  ASSERT_EQ(1, count(str1.split(LITERAL("  "), 0), eq(LITERAL("abc  abc"))));

  ASSERT_EQ(2, count(str1.split(LITERAL(' '), 1), alwaysTrue));
  ASSERT_EQ(1, count(str1.split(LITERAL(' '), 1), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(str1.split(LITERAL(' '), 1), eq(LITERAL(" abc"))));

  using ACAlloc = typename ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));
  ASSERT_EQ(2, count(S{LITERAL("abc  abc1__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(S{LITERAL("abc  abc1__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc1"))));

  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, ACAlloc()), alwaysTrue));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc"))));
  ASSERT_EQ(2, count(S{LITERAL("abc  abc1__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(S{LITERAL("abc  abc1__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc1"))));

  S str2{LITERAL("abc  abc__abc")};
  ASSERT_EQ(3, count(str2.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(3, count(str2.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, ACAlloc()), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, ACAlloc()), eq(LITERAL("abc"))));

  std::vector<S> sepsStrs{LITERAL("  "), LITERAL("__")};
  ASSERT_EQ(3, count(str2.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(str2.split(sepsStrs), eq(LITERAL("abc"))));

  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(sepsStrs), alwaysTrue));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(sepsStrs), eq(LITERAL("abc"))));

  ASSERT_EQ(4, count(S{LITERAL("  abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("  abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(S{LITERAL("  abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(4, count(S{LITERAL("abc  abc__abc__")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("abc  abc__abc__")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc__")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(4, count(S{LITERAL("abc  abc  __abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("abc  abc  __abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc  __abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(6, count(S{LITERAL("__abc  abc  __abc  ")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(S{LITERAL("__abc  abc  __abc  ")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), memFn(&SV::empty)));
  ASSERT_EQ(3, count(S{LITERAL("__abc  abc  __abc  ")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), eq(LITERAL("abc"))));

  ASSERT_EQ(1, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, 0), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, 0), eq(LITERAL("abc  abc__abc"))));

  ASSERT_EQ(2, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, 1), alwaysTrue));
  ASSERT_EQ(1, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, 1), eq(LITERAL("abc"))));
  ASSERT_EQ(1, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}, 1), eq(LITERAL("abc__abc"))));

  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<SV>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<CHAR_TYPE const*>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<S>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<stds>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
#if CDS_ATTR(cpp17)
  ASSERT_EQ(3, count(S{LITERAL("abc  abc__abc")}.split(std::vector<stdsv>{LITERAL("  "), LITERAL("__")}), alwaysTrue));
#endif
}

TEST(STRING_TEST_GROUP, ostream) {
  oss s;
  S const sv{LITERAL(" abc ")};
  s << sv;
  ASSERT_EQ(s.str(), LITERAL(" abc "));
}

TEST(STRING_TEST_GROUP, findClient) {
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.find(LITERAL('b')), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.find(LITERAL('d')), std::vector<int>{}));

  S sv {LITERAL("test test test")};
  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("test")), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("testtesttest")}.find(LITERAL("test")), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test")}.find(LITERAL("test")), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test ")}.find(LITERAL("test")), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test tes")}.find(LITERAL("test")), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test")}.find(LITERAL("test")), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test")}.find(LITERAL("test")), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test ")}.find(LITERAL("test")), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test tes")}.find(LITERAL("test")), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test ")}.find(LITERAL("test")), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test tes")}.find(LITERAL("test")), std::vector<int> {4}));

  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("testtesttest")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test ")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test tes")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test ")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test tes")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test ")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test tes")}.find(LITERAL("test"), testing::TrackerAllocator<cds::Size>()), std::vector<int> {4}));
}

TEST(STRING_TEST_GROUP, findProjectionClient) {
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.find(LITERAL('B'), toupper), std::vector<int>{1, 3}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.find(LITERAL('D'), toupper), std::vector<int>{}));

  S sv {LITERAL("test test test")};
  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("testtesttest")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test ")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test tes")}.find(LITERAL("TEST"), toupper), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test")}.find(LITERAL("TEST"), toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test")}.find(LITERAL("TEST"), toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test ")}.find(LITERAL("TEST"), toupper), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test tes")}.find(LITERAL("TEST"), toupper), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test ")}.find(LITERAL("TEST"), toupper), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test tes")}.find(LITERAL("TEST"), toupper), std::vector<int> {4}));

  ASSERT_TRUE(testing::citeq(sv.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("testtesttest")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 4, 8}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test test ")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5, 10}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("test test tes")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {0, 5}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test test ")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6, 11}));
  ASSERT_TRUE(testing::citeq(S {LITERAL(" test test tes")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {1, 6}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test test ")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {4, 9}));
  ASSERT_TRUE(testing::citeq(S {LITERAL("est test tes")}.find(LITERAL("TEST"), toupper, testing::TrackerAllocator<cds::Size>()), std::vector<int> {4}));
}

TEST(STRING_TEST_GROUP, findFirstClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL('b')), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL('d')), S::npos);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("bc")), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("bd")), S::npos);

  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("bc"), testing::TrackerAllocator<cds::Size>()), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("bd"), testing::TrackerAllocator<cds::Size>()), S::npos);
}

TEST(STRING_TEST_GROUP, findProjectionFirstClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL('B'), toupper), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL('D'), toupper), S::npos);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("BC"), toupper), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("BD"), toupper), S::npos);

  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("BC"), toupper, testing::TrackerAllocator<cds::Size>()), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirst(LITERAL("BD"), toupper, testing::TrackerAllocator<cds::Size>()), S::npos);
}

TEST(STRING_TEST_GROUP, findLastClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL('b')), 3);
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL('d')), S::npos);
  ASSERT_EQ(S{LITERAL("abcbc")}.findLast(LITERAL("bc")), 3);
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL("bd")), S::npos);

  ASSERT_EQ(S{LITERAL("abcbc")}.findLast(LITERAL("bc"), testing::TrackerAllocator<cds::Size>()), 3);
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL("bd"), testing::TrackerAllocator<cds::Size>()), S::npos);
}

TEST(STRING_TEST_GROUP, findProjectionLastClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL('B'), toupper), 3);
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL('D'), toupper), S::npos);
  ASSERT_EQ(S{LITERAL("abcbc")}.findLast(LITERAL("BC"), toupper), 3);
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL("BD"), toupper), S::npos);

  ASSERT_EQ(S{LITERAL("abcbc")}.findLast(LITERAL("BC"), toupper, testing::TrackerAllocator<cds::Size>()), 3);
  ASSERT_EQ(S{LITERAL("abcb")}.findLast(LITERAL("BD"), toupper, testing::TrackerAllocator<cds::Size>()), S::npos);
}

TEST(STRING_TEST_GROUP, findOfClient) {
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('a'), LITERAL('c')}), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('d')}), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.findOf(LITERAL("ac")), std::vector<int>{0, 2}));

  S sv1 {LITERAL("abc bcd cde def")};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc bcd cde def")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("c bcd cde def")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def ")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde de")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}), std::vector<int> {0, 3}));

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc bcd cde def")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("c bcd cde def")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def ")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde de")}.findOf(std::vector<S>{LITERAL("bc"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), std::vector<int> {0, 3}));
}

TEST(STRING_TEST_GROUP, findProjectedOfClient) {
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('A'), LITERAL('C')}, toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.findOf(std::vector<CHAR_TYPE>{LITERAL('D')}, toupper), std::vector<int>{}));

  ASSERT_TRUE(testing::citeq(S{LITERAL("abcb")}.findOf(LITERAL("AC"), toupper), std::vector<int>{0, 2}));

  S sv1 {LITERAL("abc bcd cde def")};
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc bcd cde def")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("c bcd cde def")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def ")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde de")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper), std::vector<int> {0, 3}));

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_TRUE(testing::citeq(sv1.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc bcd cde def")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {1, 4, 12}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("c bcd cde def")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {2, 10}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde def ")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {0, 3, 11}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("bc bcd cde de")}.findOf(std::vector<S>{LITERAL("BC"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), std::vector<int> {0, 3}));
}

TEST(STRING_TEST_GROUP, findFirstOfClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('c'), LITERAL('b')}), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(LITERAL("cb")), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('d')}), S::npos);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{}), S::npos);

  S sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("ggg")}), S::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{}), S::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("ggg")}, ACAlloc()), S::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{}, ACAlloc()), S::npos);
}

TEST(STRING_TEST_GROUP, findProjectedFirstOfClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('C'), LITERAL('B')}, toupper), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(LITERAL("CB"), toupper), 1);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{LITERAL('D')}, toupper), S::npos);
  ASSERT_EQ(S{LITERAL("abcb")}.findFirstOf(std::vector<CHAR_TYPE>{}, toupper), S::npos);

  S sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("GGG")}, toupper), S::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{}, toupper), S::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), 4);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{LITERAL("GGG")}, toupper, ACAlloc()), S::npos);
  ASSERT_EQ(sv1.findFirstOf(std::vector<S>{}, toupper, ACAlloc()), S::npos);
}

TEST(STRING_TEST_GROUP, findLastOfClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('c'), LITERAL('b')}), 3);
  ASSERT_EQ(S{LITERAL("abcbc")}.findLastOf(LITERAL("cb")), 4);
  ASSERT_EQ(S{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('d')}), S::npos);
  ASSERT_EQ(S{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{}), S::npos);

  S sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("ggg")}), S::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{}), S::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("cde"), LITERAL("bcd"), LITERAL("def")}, ACAlloc()), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("ggg")}, ACAlloc()), S::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{}, ACAlloc()), S::npos);
}

TEST(STRING_TEST_GROUP, findProjectedLastOfClient) {
  ASSERT_EQ(S{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('C'), LITERAL('B')}, toupper), 3);
  ASSERT_EQ(S{LITERAL("abcbc")}.findLastOf(LITERAL("CB"), toupper), 4);
  ASSERT_EQ(S{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{LITERAL('D')}, toupper), S::npos);
  ASSERT_EQ(S{LITERAL("abcb")}.findLastOf(std::vector<CHAR_TYPE>{}, toupper), S::npos);

  S sv1 {LITERAL("abc bcd cde def")};
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("GGG")}, toupper), S::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{}, toupper), S::npos);

  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("CDE"), LITERAL("BCD"), LITERAL("DEF")}, toupper, ACAlloc()), 12);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{LITERAL("GGG")}, toupper, ACAlloc()), S::npos);
  ASSERT_EQ(sv1.findLastOf(std::vector<S>{}, toupper, ACAlloc()), S::npos);
}

TEST(STRING_TEST_GROUP, findNotOfClient) {
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc")}.findNotOf(LITERAL("b")), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc")}.findNotOf(std::vector<int>{LITERAL('b')}), std::vector<int>{0, 2}));
}

TEST(STRING_TEST_GROUP, findProjectedNotOfClient) {
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc")}.findNotOf(LITERAL("B"), toupper), std::vector<int>{0, 2}));
  ASSERT_TRUE(testing::citeq(S{LITERAL("abc")}.findNotOf(std::vector<int>{LITERAL('B')}, toupper), std::vector<int>{0, 2}));
}

TEST(STRING_TEST_GROUP, findFirstNotOfClient) {
  ASSERT_EQ(S{LITERAL("abc")}.findFirstNotOf(LITERAL("a")), 1);
  ASSERT_EQ(S{LITERAL("abc")}.findFirstNotOf(LITERAL("abc")), S::npos);
}

TEST(STRING_TEST_GROUP, findProjectedFirstNotOfClient) {
  ASSERT_EQ(S{LITERAL("abc")}.findFirstNotOf(LITERAL("A"), toupper), 1);
  ASSERT_EQ(S{LITERAL("abc")}.findFirstNotOf(LITERAL("ABC"), toupper), S::npos);
}

TEST(STRING_TEST_GROUP, findLastNotOfClient) {
  ASSERT_EQ(S{LITERAL("abca")}.findLastNotOf(LITERAL("a")), 2);
  ASSERT_EQ(S{LITERAL("abc")}.findLastNotOf(LITERAL("abc")), S::npos);
}

TEST(STRING_TEST_GROUP, findProjectedLastNotOfClient) {
  ASSERT_EQ(S{LITERAL("abca")}.findLastNotOf(LITERAL("A"), toupper), 2);
  ASSERT_EQ(S{LITERAL("abc")}.findLastNotOf(LITERAL("ABC"), toupper), S::npos);
}

TEST(STRING_TEST_GROUP, findExtraCov) {
  auto r1 = S{LITERAL("abc")}.find(LITERAL("bc"));
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

TEST(STRING_TEST_GROUP, findExtraCov2) {
  auto r1 = S{LITERAL("abc")}.find(LITERAL("BC"), toupper);
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

TEST(STRING_TEST_GROUP, loremIpsumFind) {
  auto r = S{LITERAL(R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.)")}
  .findOf(std::vector<S>{LITERAL("Lorem"), LITERAL("ipsum"), LITERAL("dolor"), LITERAL("sit"), LITERAL("amet"), LITERAL("consectetur"),
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

TEST(STRING_TEST_GROUP, loremIpsumFindTracked) {
  using ACAlloc = typename cds::impl::ahoCorasick::AhoCorasickAllocatorBuilder<testing::TrackerAllocator>::Type<CHAR_TYPE>;
  auto r = S{LITERAL(R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.)")}
  .findOf(std::vector<S>{LITERAL("Lorem"), LITERAL("ipsum"), LITERAL("dolor"), LITERAL("sit"), LITERAL("amet"), LITERAL("consectetur"),
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

TEST(STRING_TEST_GROUP, functional) {
  S const sv{LITERAL("abcd")};

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

  S s1{LITERAL("abcd")};
  auto isLower = [](CHAR_TYPE const c){ return c >= LITERAL('a') && c <= LITERAL('z'); };
  auto makeUpper = [](CHAR_TYPE& c) { c = static_cast<CHAR_TYPE>(toupper(static_cast<int>(c))); };
  auto isUpper = [](CHAR_TYPE const c){ return c >= LITERAL('A') && c <= LITERAL('Z'); };
  ASSERT_TRUE(s1.all(isLower));
  s1.forEach(makeUpper);
  ASSERT_TRUE(s1.all(isUpper));
}

TEST(STRING_TEST_GROUP, containsAllocation) {
  S const sv {LITERAL("abcd")};
  ASSERT_TRUE(sv.contains(LITERAL("bc"), cds::Allocator<cds::Size>()));
  ASSERT_TRUE(sv.contains(LITERAL("BC"), toupper, cds::Allocator<cds::Size>()));
}

TEST(STRING_TEST_GROUP, startsEndsWith) {
  S const sv {LITERAL("abcd")};

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

TEST(STRING_TEST_GROUP, literal) {
  using namespace cds::literals;
  ASSERT_EQ(LITERAL_OP("abcd"), LITERAL("abcd"));
}

TEST(STRING_TEST_GROUP, constructions) {
  S const sv1 = LITERAL("abcd");
  CHAR_TYPE const buf[] = LITERAL("abcd");
  S const sv2 = buf;
  stds str = LITERAL("abcd");
  S const sv3 = str;
  ASSERT_EQ(sv1, sv2);
  ASSERT_EQ(sv1, sv3);
  SV const str2 = LITERAL("abcd");
  S const sv4 = str2;
  ASSERT_EQ(sv4, sv1);
}

TEST(STRING_TEST_GROUP, assignments) {
  S sv;
  sv = LITERAL("abcd");
  ASSERT_EQ(sv, LITERAL("abcd"));
  CHAR_TYPE const buf[] = LITERAL("abcd");
  sv = buf;
  ASSERT_EQ(sv, LITERAL("abcd"));
  stds const sv3 = LITERAL("abcd");
  sv = sv3;
  ASSERT_EQ(sv, LITERAL("abcd"));
  SV const str2 = LITERAL("abcd");
  sv = str2;
  ASSERT_EQ(sv, LITERAL("abcd"));
}

TEST(STRING_TEST_GROUP, largerAssignments) {
  S s;
  SV bigData = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  SV bigData2 = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
                        LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  s = bigData;
  ASSERT_EQ(s, bigData);
  S s2 = bigData;
  ASSERT_EQ(s2, bigData);

  s = mv(s2);
  ASSERT_EQ(s, bigData);

  S s3;
  s3 = s;
  ASSERT_EQ(s3, bigData);
  s = s3;
  ASSERT_EQ(s, bigData);
  s = s;
  ASSERT_EQ(s, bigData);

  s = mv(s3);
  ASSERT_EQ(s, bigData);

  s = bigData;
  ASSERT_EQ(s, bigData);
  s = bigData;
  ASSERT_EQ(s, bigData);
  s = bigData2;
  ASSERT_EQ(s, bigData2);
  s = bigData;
  ASSERT_EQ(s, bigData);

  s = LITERAL("abcd");
  ASSERT_EQ(s, LITERAL("abcd"));
  s = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaa");
  ASSERT_EQ(s, LITERAL("aaaaaaaaaaaaaaaaaaaaaaaa"));
  s = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaa");
  ASSERT_EQ(s, LITERAL("aaaaaaaaaaaaaaaaaaaaaaaa"));
  s = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaa");
  ASSERT_EQ(s, LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaa"));
  s = bigData2;
  ASSERT_EQ(s, bigData2);
}

TEST(STRING_TEST_GROUP, capacity) {
  SV sboData = LITERAL("aaaaaaaaaaaaaaaaaaaaaa");
  SV nonSboData = LITERAL("aaaaaaaaaaaaaaaaaaaaaaa");
  SV nonSboData2 = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  S s;
  ASSERT_EQ(s.capacity(), SBO_CAPACITY == 0 ? 0 : SBO_CAPACITY);
  S s2 = LITERAL("abcd");
  ASSERT_EQ(s2.capacity(), SBO_CAPACITY == 0 ? 31 : SBO_CAPACITY);
  S s3 = sboData;
  ASSERT_EQ(s3.capacity(), SBO_CAPACITY == 22 ? 22 : 31);
  S s4 = nonSboData;
  ASSERT_EQ(s4.capacity(), 31);
  S s5 = nonSboData2;
  ASSERT_EQ(s5.capacity(), nonSboData2.size());
}

TEST(STRING_TEST_GROUP, ctorFill) {
  S a(0, LITERAL('a'));
  S b(1, LITERAL('b'));
  S c(2, LITERAL('c'));

  ASSERT_EQ(a, LITERAL(""));
  ASSERT_EQ(b, LITERAL("b"));
  ASSERT_EQ(c, LITERAL("cc"));
}

TEST(STRING_TEST_GROUP, ctorBool) {
  S a(true);
  S b(false);

  ASSERT_EQ(a, LITERAL("true"));
  ASSERT_EQ(b, LITERAL("false"));
}

TEST(STRING_TEST_GROUP, ctorChar) {
  S a(LITERAL(' '));
  S b(LITERAL('a'));
  S c(LITERAL('\0'));

  ASSERT_EQ(a, LITERAL(" "));
  ASSERT_EQ(b, LITERAL("a"));
  ASSERT_EQ(c, LITERAL(""));
}

TEST(STRING_TEST_GROUP, ctorIntegral) {
  S x1(1);
  S x2(12);
  S x3(123);
  ASSERT_EQ(x1, LITERAL("1"));
  ASSERT_EQ(x2, LITERAL("12"));
  ASSERT_EQ(x3, LITERAL("123"));
  S x4(-1);
  S x5(-12);
  S x6(-123);
  S x7(-1234);
  ASSERT_EQ(x4, LITERAL("-1"));
  ASSERT_EQ(x5, LITERAL("-12"));
  ASSERT_EQ(x6, LITERAL("-123"));
  ASSERT_EQ(x7, LITERAL("-1234"));

  S a(0);
  S b(1234);
  S c(cds::limits::u64Max);
  S d(cds::limits::s64Min);

  ASSERT_EQ(a, LITERAL("0"));
  ASSERT_EQ(b, LITERAL("1234"));
  ASSERT_EQ(c, LITERAL("18446744073709551615"));
  ASSERT_EQ(d, LITERAL("-9223372036854775808"));
}

TEST(STRING_TEST_GROUP, ctorFloating) {
  S a(3.14f);
  S b(3.14);
  S c(3.14L);

  ASSERT_EQ(a, LITERAL("3.140000"));
  ASSERT_EQ(b, LITERAL("3.140000"));
  ASSERT_EQ(c, LITERAL("3.140000"));
}

TEST(STRING_TEST_GROUP, assignBool) {
  S a = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  a = true;
  ASSERT_EQ(a, LITERAL("true"));
  a = false;
  ASSERT_EQ(a, LITERAL("false"));
}

TEST(STRING_TEST_GROUP, assignChar) {
  S a = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  a = LITERAL(' ');
  ASSERT_EQ(a, LITERAL(" "));
  a = LITERAL('b');
  ASSERT_EQ(a, LITERAL("b"));
  a = LITERAL('\0');
  ASSERT_EQ(a, LITERAL(""));
}

TEST(STRING_TEST_GROUP, assignInt) {
  S a = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  S b;
  a = 1;
  ASSERT_EQ(a, LITERAL("1"));
  a = 12;
  ASSERT_EQ(a, LITERAL("12"));
  a = 123;
  ASSERT_EQ(a, LITERAL("123"));
  a = -1;
  ASSERT_EQ(a, LITERAL("-1"));
  a = -12;
  ASSERT_EQ(a, LITERAL("-12"));
  a = -123;
  ASSERT_EQ(a, LITERAL("-123"));
  a = -1234;
  ASSERT_EQ(a, LITERAL("-1234"));

  b = 0;
  ASSERT_EQ(b, LITERAL("0"));
  b = 1234;
  ASSERT_EQ(b, LITERAL("1234"));
  b = cds::limits::u64Max;
  ASSERT_EQ(b, LITERAL("18446744073709551615"));
  b = cds::limits::s64Min;
  ASSERT_EQ(b, LITERAL("-9223372036854775808"));
}

TEST(STRING_TEST_GROUP, assignFloat) {
  S a = LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
             LITERAL("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  S b;

  a = 3.14f;
  ASSERT_EQ(a, LITERAL("3.140000"));
  a = 3.14;
  ASSERT_EQ(a, LITERAL("3.140000"));
  a = 3.14L;
  ASSERT_EQ(a, LITERAL("3.140000"));

  b = 3.14f;
  ASSERT_EQ(b, LITERAL("3.140000"));
  b = 3.14;
  ASSERT_EQ(b, LITERAL("3.140000"));
  b = 3.14L;
  ASSERT_EQ(b, LITERAL("3.140000"));
}

TEST(STRING_TEST_GROUP, resize) {
  S a;
  a.resize(0, LITERAL('a'));
  ASSERT_EQ(a, LITERAL(""));
  a.resize(4, LITERAL('a'));
  ASSERT_EQ(a, LITERAL("aaaa"));
  a.resize(2, LITERAL('a'));
  ASSERT_EQ(a, LITERAL("aa"));
  a.resize(4, LITERAL('b'));
  ASSERT_EQ(a, LITERAL("aabb"));
  a.resize(3, LITERAL('c'));
  ASSERT_EQ(a, LITERAL("aab"));
  a.resize(10, LITERAL('d'));
  ASSERT_EQ(a, LITERAL("aabddddddd"));
  a.resize(20, LITERAL('-'));
  ASSERT_EQ(a, LITERAL("aabddddddd")
               LITERAL("----------"));
  a.resize(30, LITERAL('+'));
  ASSERT_EQ(a, LITERAL("aabddddddd")
               LITERAL("----------")
               LITERAL("++++++++++"));
  a.resize(20, LITERAL('='));
  ASSERT_EQ(a, LITERAL("aabddddddd")
               LITERAL("----------"));
  ASSERT_EQ(a.capacity(), SBO_CAPACITY == 22 ? 22 : 31);
  a.resize(40, LITERAL('+'));
  ASSERT_EQ(a, LITERAL("aabddddddd")
               LITERAL("----------")
               LITERAL("++++++++++")
               LITERAL("++++++++++"));
  a.resize(50, LITERAL('='));
  ASSERT_EQ(a, LITERAL("aabddddddd")
               LITERAL("----------")
               LITERAL("++++++++++")
               LITERAL("++++++++++")
               LITERAL("=========="));
  a.resize(30, LITERAL('+'));
  ASSERT_EQ(a, LITERAL("aabddddddd")
               LITERAL("----------")
               LITERAL("++++++++++"));
  ASSERT_EQ(a.capacity(), 31);
  a.resize(31, LITERAL('+'));
  ASSERT_EQ(a, LITERAL("aabddddddd")
               LITERAL("----------")
               LITERAL("+++++++++++"));
  ASSERT_EQ(a.capacity(), 31);
}

TEST(STRING_TEST_GROUP, reserve) {
  S a = LITERAL("abcd");
  ASSERT_EQ(a.capacity(), SBO_CAPACITY == 0 ? 31 : SBO_CAPACITY);
  a.reserve(20);
  ASSERT_EQ(a.capacity(), SBO_CAPACITY == 22 ? 22 : 31);
  a.reserve(22);
  ASSERT_EQ(a.capacity(), SBO_CAPACITY == 22 ? 22 : 31);
  a.reserve(0);
  ASSERT_EQ(a.capacity(), SBO_CAPACITY == 22 ? 22 : 31);
  ASSERT_EQ(a, LITERAL("abcd"));
  a.reserve(23);
  ASSERT_EQ(a.capacity(), 31);
  ASSERT_EQ(a, LITERAL("abcd"));
  a.reserve(20);
  ASSERT_EQ(a.capacity(), 31);
  ASSERT_EQ(a, LITERAL("abcd"));
  a.reserve(31);
  ASSERT_EQ(a.capacity(), 31);
  ASSERT_EQ(a, LITERAL("abcd"));
  a.reserve(64);
  ASSERT_EQ(a.capacity(), 64);
  ASSERT_EQ(a, LITERAL("abcd"));
  a.reserve(30);
  ASSERT_EQ(a.capacity(), 64);
  ASSERT_EQ(a, LITERAL("abcd"));
}

TEST(STRING_TEST_GROUP, shrink) {
  S a = LITERAL("abcd");
  a.shrink(20);
  ASSERT_EQ(a, LITERAL("abcd"));
  a.shrink(0);
  ASSERT_EQ(a, LITERAL(""));
  a.shrink(10);
  ASSERT_EQ(a, LITERAL(""));
  a = LITERAL("0000000000")
      LITERAL("1111111111")
      LITERAL("2222222222");
  a.shrink(25);
  ASSERT_EQ(a, LITERAL("0000000000")
               LITERAL("1111111111")
               LITERAL("22222"));
  ASSERT_EQ(a.capacity(), 31);
  a.shrink(20);
  ASSERT_EQ(a, LITERAL("0000000000")
               LITERAL("1111111111"));
  ASSERT_EQ(a.capacity(), SBO_CAPACITY == 22 ? 22 : 31);
  a = LITERAL("abcd");
  a.reserve(64);
  a.shrink();
  ASSERT_EQ(a.capacity(), SBO_CAPACITY == 0 ? 31 : SBO_CAPACITY);
}

TEST(STRING_TEST_GROUP, operatorAppendStr) {
  S a;
  a += LITERAL("abc");
  ASSERT_EQ(a, LITERAL("abc"));
  CHAR_TYPE const* str1 = LITERAL("def");
  a += str1;
  ASSERT_EQ(a, LITERAL("abcdef"));
  CHAR_TYPE const str2[] = LITERAL("ghi");
  a += str2;
  ASSERT_EQ(a, LITERAL("abcdefghi"));

  SV str3 = LITERAL("ABC");
  a += str3;
  ASSERT_EQ(a, LITERAL("abcdefghiABC"));
  stds str4 = LITERAL("DEF");
  a += str4;
  ASSERT_EQ(a, LITERAL("abcdefghiABCDEF"));
  SV str5 = LITERAL("1234");
  a += str5;
  ASSERT_EQ(a, LITERAL("abcdefghiABCDEF")
               LITERAL("1234"));
  a += str5;
  a += str5;
  a += str5;
  a += str5;
  a += str5;
  ASSERT_EQ(a, LITERAL("abcdefghiABCDEF")
               LITERAL("123412341234")
               LITERAL("123412341234"));
  a += a;
  ASSERT_EQ(a, LITERAL("abcdefghiABCDEF")
               LITERAL("123412341234")
               LITERAL("123412341234")
               LITERAL("abcdefghiABCDEF")
               LITERAL("123412341234")
               LITERAL("123412341234"));
}

TEST(STRING_TEST_GROUP, operatorAppendChar) {
  S a;
  stds b;
  for (int i = 0; i < 100; ++i) {
    a += LITERAL('a');
    b += LITERAL('a');
    ASSERT_EQ(a, b);
  }
}

TEST(STRING_TEST_GROUP, operatorAppendBool) {
  S a;
  stds b;
  for (int i = 0; i < 100; ++i) {
    a += static_cast<bool>(i % 2);
    b += (static_cast<bool>(i % 2) ? LITERAL("true") : LITERAL("false"));
    ASSERT_EQ(a, b);
  }
}

namespace {
template <typename D, typename S, typename N>
void unsafe_strncat(D dest, S src, N count) {
  N internalCnt = 0;
  for (; internalCnt < count && *dest != 0; ++dest, ++internalCnt) {
    // empty
  }

  for (; internalCnt < count && *src != 0; ++dest, ++src, ++internalCnt) {
    *dest = static_cast<CHAR_TYPE>(*src);
  }

  *dest = 0;
}
}

TEST(STRING_TEST_GROUP, operatorAppendInt) {
  S a;
  stds b;
  for (int i = 0; i < 100; ++i) {
    a += i;
    auto c = std::to_string(i);
    b.resize(b.length() + c.length());
    unsafe_strncat(&b[0], c.data(), 1024);

    ASSERT_EQ(a, b);
  }
}

TEST(STRING_TEST_GROUP, operatorAppendFloating) {
  CHAR_TYPE equivBuf[1024];
  char newBuf[1024];
  equivBuf[0] = 0;
  float v = .5f;
  S a;
  for (int i = 0; i < 10; ++i) {
    a += v;
    std::snprintf(newBuf, 1024, "%f", v);
    unsafe_strncat(equivBuf, newBuf, 1024);
    v += 1.1f;
    ASSERT_EQ(a, (CHAR_TYPE const*)equivBuf);
  }
}

TEST(STRING_TEST_GROUP, operatorPlusStr) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("aaaabbbbccccddddeeee");
  S a4 = LITERAL("aaaabbbbccccddddeeeeffff");
  S a5 = LITERAL("aaaabbbbccccddddeeeeffffgggghhhhh");

  CHAR_TYPE const* b1 = LITERAL("abcd");
  CHAR_TYPE const b2[] = LITERAL("abcd");
  stds b3 = LITERAL("abcd");
  SV b4 = LITERAL("abcd");

  ASSERT_EQ(a1 + a2, LITERAL("abcd"));
  ASSERT_EQ(a1 + LITERAL("abcd"), LITERAL("abcd"));
  ASSERT_EQ(a1 + b1, LITERAL("abcd"));
  ASSERT_EQ(a1 + b2, LITERAL("abcd"));
  ASSERT_EQ(a1 + b3, LITERAL("abcd"));
  ASSERT_EQ(a1 + b4, LITERAL("abcd"));

  ASSERT_EQ(b1 + a1, LITERAL("abcd"));
  ASSERT_EQ(b2 + a1, LITERAL("abcd"));
  ASSERT_EQ(b3 + a1, LITERAL("abcd"));
  ASSERT_EQ(b4 + a1, LITERAL("abcd"));

  ASSERT_EQ(a1 + LITERAL("abcd"), LITERAL("abcd"));
  ASSERT_EQ(a2 + LITERAL("abcd"), LITERAL("abcdabcd"));
  ASSERT_EQ(a3 + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeabcd"));
  ASSERT_EQ(a4 + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeffffabcd"));
  ASSERT_EQ(a5 + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeffffgggghhhhhabcd"));

  ASSERT_EQ(LITERAL("abcd") + a1, LITERAL("abcd"));
  ASSERT_EQ(LITERAL("abcd") + a2, LITERAL("abcdabcd"));
  ASSERT_EQ(LITERAL("abcd") + a3, LITERAL("abcdaaaabbbbccccddddeeee"));
  ASSERT_EQ(LITERAL("abcd") + a4, LITERAL("abcdaaaabbbbccccddddeeeeffff"));
  ASSERT_EQ(LITERAL("abcd") + a5, LITERAL("abcdaaaabbbbccccddddeeeeffffgggghhhhh"));

  ASSERT_EQ(mv(a1) + LITERAL("abcd"), LITERAL("abcd"));
  ASSERT_EQ(mv(a2) + LITERAL("abcd"), LITERAL("abcdabcd"));
  ASSERT_EQ(mv(a3) + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeabcd"));
  ASSERT_EQ(mv(a4) + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeffffabcd"));
  ASSERT_EQ(mv(a5) + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeffffgggghhhhhabcd"));

  ASSERT_EQ(S{} + LITERAL("abcd"), LITERAL("abcd"));
  ASSERT_EQ(S{LITERAL("abcd")} + LITERAL("abcd"), LITERAL("abcdabcd"));
  ASSERT_EQ(S{LITERAL("aaaabbbbccccddddeeee")} + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeabcd"));
  ASSERT_EQ(S{LITERAL("aaaabbbbccccddddeeeeffff")} + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeffffabcd"));
  ASSERT_EQ(S{LITERAL("aaaabbbbccccddddeeeeffffgggghhhhh")} + LITERAL("abcd"), LITERAL("aaaabbbbccccddddeeeeffffgggghhhhhabcd"));
}

TEST(STRING_TEST_GROUP, operatorPlusChar) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("abcdabcdabcdabcdabcdab");
  S a4 = LITERAL("abcdabcdabcdabcdabcdabcd");
  S a5 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd");

  ASSERT_EQ(a1 + LITERAL('e'), LITERAL("e"));
  ASSERT_EQ(a2 + LITERAL('e'), LITERAL("abcde"));
  ASSERT_EQ(a3 + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabe"));
  ASSERT_EQ(a4 + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabcde"));
  ASSERT_EQ(a5 + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcde"));

  ASSERT_EQ(LITERAL('e') + a1, LITERAL("e"));
  ASSERT_EQ(LITERAL('e') + a2, LITERAL("eabcd"));
  ASSERT_EQ(LITERAL('e') + a3, LITERAL("eabcdabcdabcdabcdabcdab"));
  ASSERT_EQ(LITERAL('e') + a4, LITERAL("eabcdabcdabcdabcdabcdabcd"));
  ASSERT_EQ(LITERAL('e') + a5, LITERAL("eabcdabcdabcdabcdabcdabcdabcdabcdabcd"));

  ASSERT_EQ(mv(a1) + LITERAL('e'), LITERAL("e"));
  ASSERT_EQ(mv(a2) + LITERAL('e'), LITERAL("abcde"));
  ASSERT_EQ(mv(a3) + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabe"));
  ASSERT_EQ(mv(a4) + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabcde"));
  ASSERT_EQ(mv(a5) + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcde"));

  ASSERT_EQ(S{} + LITERAL('e'), LITERAL("e"));
  ASSERT_EQ(S{LITERAL("abcd")} + LITERAL('e'), LITERAL("abcde"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdab")} + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabe"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcd")} + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabcde"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd")} + LITERAL('e'), LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcde"));
}

TEST(STRING_TEST_GROUP, operatorPlusBool) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("abcdabcdabcdabcdabcdab");
  S a4 = LITERAL("abcdabcdabcdabcdabcdabcd");
  S a5 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd");

  ASSERT_EQ(a1 + true, LITERAL("true"));
  ASSERT_EQ(a2 + true, LITERAL("abcdtrue"));
  ASSERT_EQ(a3 + true, LITERAL("abcdabcdabcdabcdabcdabtrue"));
  ASSERT_EQ(a4 + true, LITERAL("abcdabcdabcdabcdabcdabcdtrue"));
  ASSERT_EQ(a5 + true, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdtrue"));

  ASSERT_EQ(a1 + false, LITERAL("false"));
  ASSERT_EQ(a2 + false, LITERAL("abcdfalse"));
  ASSERT_EQ(a3 + false, LITERAL("abcdabcdabcdabcdabcdabfalse"));
  ASSERT_EQ(a4 + false, LITERAL("abcdabcdabcdabcdabcdabcdfalse"));
  ASSERT_EQ(a5 + false, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdfalse"));

  ASSERT_EQ(true + a1, LITERAL("true"));
  ASSERT_EQ(true + a2, LITERAL("trueabcd"));
  ASSERT_EQ(true + a3, LITERAL("trueabcdabcdabcdabcdabcdab"));
  ASSERT_EQ(true + a4, LITERAL("trueabcdabcdabcdabcdabcdabcd"));
  ASSERT_EQ(true + a5, LITERAL("trueabcdabcdabcdabcdabcdabcdabcdabcdabcd"));

  ASSERT_EQ(false + a1, LITERAL("false"));
  ASSERT_EQ(false + a2, LITERAL("falseabcd"));
  ASSERT_EQ(false + a3, LITERAL("falseabcdabcdabcdabcdabcdab"));
  ASSERT_EQ(false + a4, LITERAL("falseabcdabcdabcdabcdabcdabcd"));
  ASSERT_EQ(false + a5, LITERAL("falseabcdabcdabcdabcdabcdabcdabcdabcdabcd"));

  ASSERT_EQ(mv(a1) + true, LITERAL("true"));
  ASSERT_EQ(mv(a2) + true, LITERAL("abcdtrue"));
  ASSERT_EQ(mv(a3) + true, LITERAL("abcdabcdabcdabcdabcdabtrue"));
  ASSERT_EQ(mv(a4) + true, LITERAL("abcdabcdabcdabcdabcdabcdtrue"));
  ASSERT_EQ(mv(a5) + true, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdtrue"));

  a1 = LITERAL("");
  a2 = LITERAL("abcd");
  a3 = LITERAL("abcdabcdabcdabcdabcdab");
  a4 = LITERAL("abcdabcdabcdabcdabcdabcd");
  a5 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd");

  ASSERT_EQ(mv(a1) + false, LITERAL("false"));
  ASSERT_EQ(mv(a2) + false, LITERAL("abcdfalse"));
  ASSERT_EQ(mv(a3) + false, LITERAL("abcdabcdabcdabcdabcdabfalse"));
  ASSERT_EQ(mv(a4) + false, LITERAL("abcdabcdabcdabcdabcdabcdfalse"));
  ASSERT_EQ(mv(a5) + false, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdfalse"));

  ASSERT_EQ(S{} + true, LITERAL("true"));
  ASSERT_EQ(S{LITERAL("abcd")} + true, LITERAL("abcdtrue"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdab")} + true, LITERAL("abcdabcdabcdabcdabcdabtrue"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcd")} + true, LITERAL("abcdabcdabcdabcdabcdabcdtrue"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd")} + true, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdtrue"));

  ASSERT_EQ(S{} + false, LITERAL("false"));
  ASSERT_EQ(S{LITERAL("abcd")} + false, LITERAL("abcdfalse"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdab")} + false, LITERAL("abcdabcdabcdabcdabcdabfalse"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcd")} + false, LITERAL("abcdabcdabcdabcdabcdabcdfalse"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd")} + false, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdfalse"));
}

TEST(STRING_TEST_GROUP, operatorPlusInt) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("abcdabcdabcdabcdabcdab");
  S a4 = LITERAL("abcdabcdabcdabcdabcdabcd");
  S a5 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd");

  ASSERT_EQ(a1 + 1234, LITERAL("1234"));
  ASSERT_EQ(a2 + 1234, LITERAL("abcd1234"));
  ASSERT_EQ(a3 + 1234, LITERAL("abcdabcdabcdabcdabcdab1234"));
  ASSERT_EQ(a4 + 1234, LITERAL("abcdabcdabcdabcdabcdabcd1234"));
  ASSERT_EQ(a5 + 1234, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd1234"));

  ASSERT_EQ(1234 + a1, LITERAL("1234"));
  ASSERT_EQ(1234 + a2, LITERAL("1234abcd"));
  ASSERT_EQ(1234 + a3, LITERAL("1234abcdabcdabcdabcdabcdab"));
  ASSERT_EQ(1234 + a4, LITERAL("1234abcdabcdabcdabcdabcdabcd"));
  ASSERT_EQ(1234 + a5, LITERAL("1234abcdabcdabcdabcdabcdabcdabcdabcdabcd"));

  ASSERT_EQ(mv(a1) + 1234, LITERAL("1234"));
  ASSERT_EQ(mv(a2) + 1234, LITERAL("abcd1234"));
  ASSERT_EQ(mv(a3) + 1234, LITERAL("abcdabcdabcdabcdabcdab1234"));
  ASSERT_EQ(mv(a4) + 1234, LITERAL("abcdabcdabcdabcdabcdabcd1234"));
  ASSERT_EQ(mv(a5) + 1234, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd1234"));

  ASSERT_EQ(S{} + 1234, LITERAL("1234"));
  ASSERT_EQ(S{LITERAL("abcd")} + 1234, LITERAL("abcd1234"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdab")} + 1234, LITERAL("abcdabcdabcdabcdabcdab1234"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcd")} + 1234, LITERAL("abcdabcdabcdabcdabcdabcd1234"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd")} + 1234, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd1234"));
}

TEST(STRING_TEST_GROUP, operatorPlusFloating) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("abcdabcdabcdabcdabcdab");
  S a4 = LITERAL("abcdabcdabcdabcdabcdabcd");
  S a5 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd");

  ASSERT_EQ(a1 + 1.5, LITERAL("1.500000"));
  ASSERT_EQ(a2 + 1.5, LITERAL("abcd1.500000"));
  ASSERT_EQ(a3 + 1.5, LITERAL("abcdabcdabcdabcdabcdab1.500000"));
  ASSERT_EQ(a4 + 1.5, LITERAL("abcdabcdabcdabcdabcdabcd1.500000"));
  ASSERT_EQ(a5 + 1.5, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd1.500000"));

  ASSERT_EQ(1.5 + a1, LITERAL("1.500000"));
  ASSERT_EQ(1.5 + a2, LITERAL("1.500000abcd"));
  ASSERT_EQ(1.5 + a3, LITERAL("1.500000abcdabcdabcdabcdabcdab"));
  ASSERT_EQ(1.5 + a4, LITERAL("1.500000abcdabcdabcdabcdabcdabcd"));
  ASSERT_EQ(1.5 + a5, LITERAL("1.500000abcdabcdabcdabcdabcdabcdabcdabcdabcd"));

  ASSERT_EQ(mv(a1) + 1.5, LITERAL("1.500000"));
  ASSERT_EQ(mv(a2) + 1.5, LITERAL("abcd1.500000"));
  ASSERT_EQ(mv(a3) + 1.5, LITERAL("abcdabcdabcdabcdabcdab1.500000"));
  ASSERT_EQ(mv(a4) + 1.5, LITERAL("abcdabcdabcdabcdabcdabcd1.500000"));
  ASSERT_EQ(mv(a5) + 1.5, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd1.500000"));

  ASSERT_EQ(S{} + 1.5, LITERAL("1.500000"));
  ASSERT_EQ(S{LITERAL("abcd")} + 1.5, LITERAL("abcd1.500000"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdab")} + 1.5, LITERAL("abcdabcdabcdabcdabcdab1.500000"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcd")} + 1.5, LITERAL("abcdabcdabcdabcdabcdabcd1.500000"));
  ASSERT_EQ(S{LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd")} + 1.5, LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcd1.500000"));
}

TEST(STRING_TEST_GROUP, ltrim) {
  S a1 = LITERAL("aabbaacc");
  ASSERT_EQ(a1.ltrim(LITERAL('a')), LITERAL("bbaacc"));
  CHAR_TYPE const* b = LITERAL("ab");
  ASSERT_EQ(a1.ltrim(b), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(LITERAL("ab")), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(SV{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(stds{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.ltrim(S{LITERAL("ab")}), LITERAL("cc"));

  S a2 = LITERAL("  abcd");
  ASSERT_EQ(a2.ltrim(), LITERAL("abcd"));
}

TEST(STRING_TEST_GROUP, rtrim) {
  S a1 = LITERAL("aabbaacc");
  ASSERT_EQ(a1.rtrim(LITERAL('c')), LITERAL("aabbaa"));
  CHAR_TYPE const* b = LITERAL("ac");
  ASSERT_EQ(a1.rtrim(b), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(LITERAL("ac")), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(SV{LITERAL("ac")}), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(stds{LITERAL("ac")}), LITERAL("aabb"));
  ASSERT_EQ(a1.rtrim(S{LITERAL("ac")}), LITERAL("aabb"));

  S a2 = LITERAL("abcd  ");
  ASSERT_EQ(a2.rtrim(), LITERAL("abcd"));
}

TEST(STRING_TEST_GROUP, trim) {
  S a1 = LITERAL("aabbccbbaa");
  ASSERT_EQ(a1.trim(LITERAL('a')), LITERAL("bbccbb"));
  CHAR_TYPE const* b = LITERAL("ab");
  ASSERT_EQ(a1.trim(b), LITERAL("cc"));
  ASSERT_EQ(a1.trim(LITERAL("ab")), LITERAL("cc"));
  ASSERT_EQ(a1.trim(SV{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.trim(stds{LITERAL("ab")}), LITERAL("cc"));
  ASSERT_EQ(a1.trim(S{LITERAL("ab")}), LITERAL("cc"));

  S a2 = LITERAL("  abcd  ");
  ASSERT_EQ(a2.trim(), LITERAL("abcd"));
}

TEST(STRING_TEST_GROUP, ljust) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("abcdefghabcdefghabcdef");

  ASSERT_EQ(a1.ljust(4), LITERAL("    "));
  ASSERT_EQ(a2.ljust(2), LITERAL("abcd"));
  ASSERT_EQ(a2.ljust(4), LITERAL("abcd"));
  ASSERT_EQ(a2.ljust(6), LITERAL("  abcd"));
  ASSERT_EQ(a3.ljust(24), LITERAL("  abcdefghabcdefghabcdef"));

  ASSERT_EQ(S{LITERAL("abcd")}.ljust(2), LITERAL("abcd"));
  ASSERT_EQ(S{LITERAL("abcd")}.ljust(6), LITERAL("  abcd"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdef")}.ljust(21), LITERAL("abcdefghabcdefghabcdef"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdef")}.ljust(24), LITERAL("  abcdefghabcdefghabcdef"));
}

TEST(STRING_TEST_GROUP, rjust) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("abcdefghabcdefghabcdef");

  ASSERT_EQ(a1.rjust(4), LITERAL("    "));
  ASSERT_EQ(a2.rjust(2), LITERAL("abcd"));
  ASSERT_EQ(a2.rjust(4), LITERAL("abcd"));
  ASSERT_EQ(a2.rjust(6), LITERAL("abcd  "));
  ASSERT_EQ(a3.rjust(24), LITERAL("abcdefghabcdefghabcdef  "));

  ASSERT_EQ(S{LITERAL("abcd")}.rjust(2), LITERAL("abcd"));
  ASSERT_EQ(S{LITERAL("abcd")}.rjust(6), LITERAL("abcd  "));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdef")}.rjust(21), LITERAL("abcdefghabcdefghabcdef"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdef")}.rjust(24), LITERAL("abcdefghabcdefghabcdef  "));
}

TEST(STRING_TEST_GROUP, replace) {
  S a1;
  S a2 = LITERAL("abcd");
  S a3 = LITERAL("abcdefghabcdefghabcdefghi");

  ASSERT_EQ(a1.replace(0, 0, LITERAL("test")), LITERAL("test"));
  ASSERT_EQ(a2.replace(2, 1, LITERAL("AB")), LITERAL("abcd"));
  ASSERT_EQ(a2.replace(1, 2, LITERAL("AB")), LITERAL("aABcd"));
  ASSERT_EQ(a2.replace(0, 2, LITERAL("AB")), LITERAL("ABcd"));
  ASSERT_EQ(a2.replace(2, 4, LITERAL("AB")), LITERAL("abAB"));
  ASSERT_EQ(a3.replace(0, 3, LITERAL("ABCDEFGH")), LITERAL("ABCDEFGHdefghabcdefghabcdefghi"));
  ASSERT_EQ(a3.replace(3, 6, LITERAL("ABCDEFGH")), LITERAL("abcABCDEFGHghabcdefghabcdefghi"));
  ASSERT_EQ(a3.replace(22, 25, LITERAL("ABCDEFGH")), LITERAL("abcdefghabcdefghabcdefABCDEFGH"));
  ASSERT_EQ(a3.replace(25, 25, LITERAL("ABCDEFGH")), LITERAL("abcdefghabcdefghabcdefghiABCDEFGH"));
  ASSERT_EQ(a3.replace(0, 0, LITERAL("ABCDEFGH")), LITERAL("ABCDEFGHabcdefghabcdefghabcdefghi"));

  ASSERT_EQ(S{}.replace(0, 0, LITERAL("test")), LITERAL("test"));
  ASSERT_EQ(S{LITERAL("abcd")}.replace(2, 1, LITERAL("AB")), LITERAL("abcd"));
  ASSERT_EQ(S{LITERAL("abcd")}.replace(1, 2, LITERAL("AB")), LITERAL("aABcd"));
  ASSERT_EQ(S{LITERAL("abcd")}.replace(1, 4, LITERAL("AB")), LITERAL("aAB"));
  ASSERT_EQ(S{LITERAL("abcdef")}.replace(0, 3, LITERAL("AB")), LITERAL("ABdef"));
  ASSERT_EQ(S{LITERAL("abcdef")}.replace(1, 3, LITERAL("AB")), LITERAL("aABdef"));
  ASSERT_EQ(S{LITERAL("abcdef")}.replace(1, 2, LITERAL("AB")), LITERAL("aABcdef"));
  ASSERT_EQ(S{LITERAL("abcdef")}.replace(1, 4, LITERAL("AB")), LITERAL("aABef"));
  ASSERT_EQ(S{LITERAL("abcd")}.replace(0, 3, LITERAL("AB")), LITERAL("ABd"));
  ASSERT_EQ(S{LITERAL("abcd")}.replace(0, 2, LITERAL("AB")), LITERAL("ABcd"));
  ASSERT_EQ(S{LITERAL("abcd")}.replace(2, 4, LITERAL("AB")), LITERAL("abAB"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdefghi")}.replace(0, 3, LITERAL("ABCDEFGH")), LITERAL("ABCDEFGHdefghabcdefghabcdefghi"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdefghi")}.replace(3, 6, LITERAL("ABCDEFGH")), LITERAL("abcABCDEFGHghabcdefghabcdefghi"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdefghi")}.replace(3, 20, LITERAL("ABCDEFGH")), LITERAL("abcABCDEFGHefghi"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdefghi")}.replace(22, 25, LITERAL("ABCDEFGH")), LITERAL("abcdefghabcdefghabcdefABCDEFGH"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdefghi")}.replace(25, 25, LITERAL("ABCDEFGH")), LITERAL("abcdefghabcdefghabcdefghiABCDEFGH"));
  ASSERT_EQ(S{LITERAL("abcdefghabcdefghabcdefghi")}.replace(0, 0, LITERAL("ABCDEFGH")), LITERAL("ABCDEFGHabcdefghabcdefghabcdefghi"));
}

TEST(STRING_TEST_GROUP, join) {
    ASSERT_EQ(S::join(LITERAL(";"), LITERAL("a"), LITERAL("b"), LITERAL("c")), LITERAL("a;b;c"));
    ASSERT_EQ(S::join(LITERAL(";"), std::vector<SV>{LITERAL("a"), LITERAL("b"), LITERAL("c")}), LITERAL("a;b;c"));
    ASSERT_EQ(S::join(LITERAL(";"), std::vector<SV>{LITERAL("a"), LITERAL("b"), LITERAL("c")}, LITERAL("d"), std::vector<S>{LITERAL("e"), LITERAL("f"), LITERAL("g")}), LITERAL("a;b;c;d;e;f;g"));
}

TEST(STRING_TEST_GROUP, removePrefix) {
  S const a1 = LITERAL("abc");
  ASSERT_EQ(a1.removePrefix(LITERAL('a')), LITERAL("bc"));
  ASSERT_EQ(a1.removePrefix(LITERAL("ab")), LITERAL("c"));
  ASSERT_EQ(a1.removePrefix(LITERAL("ac")), LITERAL("abc"));
  ASSERT_EQ(a1.removePrefix(LITERAL("abc")), LITERAL(""));
  ASSERT_EQ(a1.removePrefix(LITERAL("abcd")), LITERAL("abc"));
  ASSERT_EQ(a1.removePrefix(LITERAL("abeg")), LITERAL("abc"));
}

TEST(STRING_TEST_GROUP, removeSuffix) {
  S const a1 = LITERAL("abc");
  ASSERT_EQ(a1.removeSuffix(LITERAL('c')), LITERAL("ab"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("bc")), LITERAL("a"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("ac")), LITERAL("abc"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("abc")), LITERAL(""));
  ASSERT_EQ(a1.removeSuffix(LITERAL("fabc")), LITERAL("abc"));
  ASSERT_EQ(a1.removeSuffix(LITERAL("ffbc")), LITERAL("abc"));
}

#ifdef DCR_SINCECPP17
TEST(STRING_TEST_GROUP, construction17) {
  S a = stdsv(LITERAL("abc"));

  (void) a;
}
#endif

#ifdef DCR_SINCECPP20
namespace cexpr {
namespace i = cds::impl;
namespace m = cds::meta;
using CS = i::BaseString<CHAR_TYPE, i::StringUtils<CHAR_TYPE, m::StringTraits<CHAR_TYPE>>, cds::Allocator<CHAR_TYPE>>;
namespace {
namespace f = cds::functional;
consteval auto cxx20_def_ctr(auto p) {
  return f::invoke(p, CS{});
}

consteval auto cxx20_ptr_len_ctr(auto p, auto a, cds::Size l) {
  return f::invoke(p, CS{a, l});
}

consteval auto cxx20_copy_ctr(auto p, CS const& s) {
  return f::invoke(p, CS{s});
}

consteval auto cxx20_move_ctr(auto p, CS&& s) {
  return f::invoke(p, CS{mv(s)});
}

consteval auto cxx20_conv_ctr(auto p, auto&& conv) {
  return f::invoke(p, CS{fwd<decltype(conv)>(conv)});
}

consteval auto cxx20_sized_ctr(auto p, cds::Size l, CHAR_TYPE f) {
  return f::invoke(p, CS{l, f});
}

consteval auto cxx20_bool_ctr(auto p, bool v) {
  return f::invoke(p, CS{v});
}

consteval auto cxx20_int_ctr(auto p, auto n) {
  return f::invoke(p, CS{n});
}

consteval auto cxx20_copy_assign(CS const& s, auto compare) {
  CS orig1;
  CS orig2 = LITERAL("ab");
  CS orig3 = LITERAL("abcdabcdabcdabcd");
  CS orig4 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd");
  orig1 = s;
  orig2 = s;
  orig3 = s;
  orig4 = s;
  return orig1 == compare && orig2 == compare && orig3 == compare && orig4 == compare;
}

consteval auto cxx20_move_assign(CS const& s, auto compare) {
  CS orig1;
  CS orig2 = LITERAL("ab");
  CS orig3 = LITERAL("abcdabcdabcdabcd");
  CS orig4 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd");
  CS m1 = s;
  CS m2 = s;
  CS m3 = s;
  CS m4 = s;
  orig1 = mv(m1);
  orig2 = mv(m2);
  orig3 = mv(m3);
  orig4 = mv(m4);
  return orig1 == compare && orig2 == compare && orig3 == compare && orig4 == compare;
}

consteval auto cxx20_conv_assign(auto&& conv, auto compare) {
  CS orig1;
  CS orig2 = LITERAL("ab");
  CS orig3 = LITERAL("abcdabcdabcdabcd");
  CS orig4 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd");
  orig1 = fwd<decltype(conv)>(conv);
  orig2 = fwd<decltype(conv)>(conv);
  orig3 = fwd<decltype(conv)>(conv);
  orig4 = fwd<decltype(conv)>(conv);
  return orig1 == compare && orig2 == compare && orig3 == compare && orig4 == compare;
}

consteval auto cxx20_bool_assign(bool val, auto compare) {
  CS orig1;
  CS orig2 = LITERAL("ab");
  CS orig3 = LITERAL("abcdabcdabcdabcd");
  CS orig4 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd");
  orig1 = val;
  orig2 = val;
  orig3 = val;
  orig4 = val;
  return orig1 == compare && orig2 == compare && orig3 == compare && orig4 == compare;
}

consteval auto cxx20_int_assign(auto val, auto compare) {
  CS orig1;
  CS orig2 = LITERAL("ab");
  CS orig3 = LITERAL("abcdabcdabcdabcd");
  CS orig4 = LITERAL("abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd");
  orig1 = val;
  orig2 = val;
  orig3 = val;
  orig4 = val;
  return orig1 == compare && orig2 == compare && orig3 == compare && orig4 == compare;
}

consteval auto cxx11_elevated_cxx20_data(CS const& s) {
  return s.data();
}

consteval auto cxx11_elevated_cxx20_length(CS const& s) {
  return s.length();
}

consteval auto cxx11_elevated_cxx20_datalen(CS const& s, auto comp) {
  return i::Ordering::Equal == i::compare(cxx11_elevated_cxx20_data(s), cxx11_elevated_cxx20_data(s) + cxx11_elevated_cxx20_length(s), comp, comp + i::StringAbstract<>::length(comp));
}

consteval auto cxx11_elevated_cxx20_size(CS const& s) {
  return s.size();
}

consteval auto cxx11_elevated_cxx20_capacity(CS const& s) {
  return s.capacity();
}

consteval auto cxx11_elevated_cxx20_empty(CS const& s) {
  return s.empty();
}

consteval auto cxx11_elevated_cxx20_op_bool(CS const& s) {
  return static_cast<bool>(s);
}

consteval auto cxx11_elevated_cxx20_iteration() {
  CS s = LITERAL("ab");
  auto it1 = s.begin();
  auto it2 = it1 + 1;
  auto it3 = it1 + 2;
  return it1 == s.begin() && it1 != s.end() && *it1 == LITERAL('a')
      && it2 != s.begin() && it2 != s.end() && *it2 == LITERAL('b')
      && it3 != s.begin() && it3 == s.end();
}

consteval auto cxx11_elevated_cxx20_citeration() {
  CS s = LITERAL("ab");
  auto it1 = s.cbegin();
  auto it2 = it1 + 1;
  auto it3 = it1 + 2;
  return it1 == s.cbegin() && it1 != s.cend() && *it1 == LITERAL('a')
      && it2 != s.cbegin() && it2 != s.cend() && *it2 == LITERAL('b')
      && it3 != s.cbegin() && it3 == s.cend();
}

consteval auto cxx11_elevated_cxx20_riteration() {
  CS s = LITERAL("ab");
  auto it1 = s.rbegin();
  auto it2 = it1 + 1;
  auto it3 = it1 + 2;
  return it1 == s.rbegin() && it1 != s.rend() && *it1 == LITERAL('b')
      && it2 != s.rbegin() && it2 != s.rend() && *it2 == LITERAL('a')
      && it3 != s.rbegin() && it3 == s.rend();
}

consteval auto cxx11_elevated_cxx20_criteration() {
  CS s = LITERAL("ab");
  auto it1 = s.crbegin();
  auto it2 = it1 + 1;
  auto it3 = it1 + 2;
  return it1 == s.crbegin() && it1 != s.crend() && *it1 == LITERAL('b')
      && it2 != s.crbegin() && it2 != s.crend() && *it2 == LITERAL('a')
      && it3 != s.crbegin() && it3 == s.crend();
}

consteval auto cxx11_elevated_cxx20_op_sqb(CS const& s, auto idx) {
  return s[idx];
}

consteval auto cxx11_elevated_cxx20_at(CS const& s, auto idx) {
  return s.at(idx);
}

consteval auto cxx11_elevated_cxx20_front(CS const& s) {
  return s.front();
}

consteval auto cxx11_elevated_cxx20_back(CS const& s) {
  return s.back();
}

consteval auto cxx14_elevated_cxx20_sub(auto p, CS const& s, int from) {
  return f::invoke(p, s.sub(from));
}

consteval auto cxx14_elevated_cxx20_sub(auto p, CS const& s, int from, int to) {
  return f::invoke(p, s.sub(from, to));
}

consteval auto cxx14_elevated_cxx20_op_rnb(auto p, CS const& s, int from) {
  return f::invoke(p, s(from));
}

consteval auto cxx14_elevated_cxx20_op_rnb(auto p, CS const& s, int from, int to) {
  return f::invoke(p, s(from, to));
}

consteval auto cxx14_elevated_cxx20_contains(CS const& s, auto n) {
  return s.contains(n);
}

consteval auto cxx14_elevated_cxx20_startsWith(CS const& s, auto n) {
  return s.startsWith(n);
}

consteval auto cxx14_elevated_cxx20_endsWith(CS const& s, auto n) {
  return s.endsWith(n);
}

consteval auto cxx20_split_i(auto b, auto e) {
  return b == e;
}

consteval auto cxx20_split_i(auto b, auto e, auto f, auto... r) {
  return b != e && *b == f && cxx20_split_i(++b, e, r...);
}

consteval auto cxx20_split(CS sv, auto s, auto... t) {
  auto const r = sv.split(s);
  return cxx20_split_i(r.begin(), r.end(), t...);
}

consteval auto cxx20_resize() {
  CS s;
  for (auto i = 0; i < 128; ++i) {
    s.resize(i, LITERAL('0'));
    for (int j = 0; j < i; ++j) {
      if (s[j] != LITERAL('0')) {
        return false;
      }
    }
  }
  for (auto i = 128; i >= 0; --i) {
    s.resize(i, LITERAL('0'));
    for (int j = 0; j < i; ++j) {
      if (s[j] != LITERAL('0')) {
        return false;
      }
    }
  }
  return true;
}

consteval auto cxx20_reserve() {
  CS s = LITERAL("abc");
  for (auto i = 0; i < 48; ++i) {
    s.reserve(i);
    if (s != LITERAL("abc")) {
      return false;
    }
  }

  for (auto i = 48; i >= 0; --i) {
    s.reserve(i);
    if (s != LITERAL("abc")) {
      return false;
    }
  }

  return true;
}

consteval auto cxx20_shrink() {
  CS s = LITERAL("abc");
  for (auto i = 3; i < 48; ++i) {
    s.shrink(i);
    if (s != LITERAL("abc")) {
      return false;
    }
  }

  for (auto i = 48; i >= 3; --i) {
    s.shrink(i);
    if (s != LITERAL("abc")) {
      return false;
    }
  }

  s.shrink(2);
  if (s != LITERAL("ab")) {
    return false;
  }

  s.shrink(1);
  if (s != LITERAL("a")) {
    return false;
  }

  s.shrink(0);
  if (s != LITERAL("")) {
    return false;
  }

  s.shrink(1);
  if (s != LITERAL("")) {
    return false;
  }

  s.shrink(32);
  if (s != LITERAL("")) {
    return false;
  }

  return true;
}

consteval auto cxx20_clear() {
  CS s1 = LITERAL("abc");
  CS s2;
  s1.clear();
  s2.clear();
  return s1.empty() && s2.empty();
}

consteval auto cxx20_append_move_or_temp_str() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  o1 += CS{LITERAL("xyzt")};
  o2 += CS{LITERAL("xyzt")};
  o3 += CS{LITERAL("xyzt")};
  o4 += CS{LITERAL("xyzt")};

  return o1 == LITERAL("xyzt")
      && o2 == LITERAL("axyzt")
      && o3 == LITERAL("abcdefghxyzt")
      && o4 == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghxyzt");
}

consteval auto cxx20_append_strlike() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  o1 += LITERAL("xyzt");
  o1 += stdsv{LITERAL("xyzt")};
  o1 += stds{LITERAL("xyzt")};
  o1 += SV{LITERAL("xyzt")};

  o2 += LITERAL("xyzt");
  o2 += stdsv{LITERAL("xyzt")};
  o2 += stds{LITERAL("xyzt")};
  o2 += SV{LITERAL("xyzt")};

  o3 += LITERAL("xyzt");
  o3 += stdsv{LITERAL("xyzt")};
  o3 += stds{LITERAL("xyzt")};
  o3 += SV{LITERAL("xyzt")};

  o4 += LITERAL("xyzt");
  o4 += stdsv{LITERAL("xyzt")};
  o4 += stds{LITERAL("xyzt")};
  o4 += SV{LITERAL("xyzt")};

  return o1 == LITERAL("xyztxyztxyztxyzt")
      && o2 == LITERAL("axyztxyztxyztxyzt")
      && o3 == LITERAL("abcdefghxyztxyztxyztxyzt")
      && o4 == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghxyztxyztxyztxyzt");
}

consteval auto cxx20_append_char() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  o1 += LITERAL('x');
  o2 += LITERAL('x');
  o3 += LITERAL('x');
  o4 += LITERAL('x');

  return o1 == LITERAL("x")
      && o2 == LITERAL("ax")
      && o3 == LITERAL("abcdefghx")
      && o4 == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghx");
}

consteval auto cxx20_append_bool() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  o1 += true;
  o1 += false;
  o2 += true;
  o2 += false;
  o3 += true;
  o3 += false;
  o4 += true;
  o4 += false;

  return o1 == LITERAL("truefalse")
      && o2 == LITERAL("atruefalse")
      && o3 == LITERAL("abcdefghtruefalse")
      && o4 == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghtruefalse");
}

consteval auto cxx20_append_int() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  o1 += 0;
  o1 += 123;
  o1 += -234;

  o2 += 0;
  o2 += 123;
  o2 += -234;

  o3 += 0;
  o3 += 123;
  o3 += -234;

  o4 += 0;
  o4 += 123;
  o4 += -234;

  return o1 == LITERAL("0123-234")
      && o2 == LITERAL("a0123-234")
      && o3 == LITERAL("abcdefgh0123-234")
      && o4 == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh0123-234");
}

consteval auto cxx20_append2_move_or_temp_str() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return o1 + CS{LITERAL("xyzt")} == LITERAL("xyzt")
      && o2 + CS{LITERAL("xyzt")} == LITERAL("axyzt")
      && o3 + CS{LITERAL("xyzt")} == LITERAL("abcdefghxyzt")
      && o4 + CS{LITERAL("xyzt")} == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghxyzt");
}

consteval auto cxx20_append2_strlike() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return o1 + LITERAL("xyzt") + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} == LITERAL("xyztxyztxyztxyzt")
      && o2 + LITERAL("xyzt") + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} == LITERAL("axyztxyztxyztxyzt")
      && o3 + LITERAL("xyzt") + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} == LITERAL("abcdefghxyztxyztxyztxyzt")
      && o4 + LITERAL("xyzt") + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghxyztxyztxyztxyzt");
}

consteval auto cxx20_append2_char() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return o1 + LITERAL('x') == LITERAL("x")
      && o2 + LITERAL('x') == LITERAL("ax")
      && o3 + LITERAL('x') == LITERAL("abcdefghx")
      && o4 + LITERAL('x') == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghx");
}

consteval auto cxx20_append2_bool() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return o1 + true + false == LITERAL("truefalse")
      && o2 + true + false == LITERAL("atruefalse")
      && o3 + true + false == LITERAL("abcdefghtruefalse")
      && o4 + true + false == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghtruefalse");
}

consteval auto cxx20_append2_int() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return o1 + 0 + 123 + -234 == LITERAL("0123-234")
      && o2 + 0 + 123 + -234 == LITERAL("a0123-234")
      && o3 + 0 + 123 + -234 == LITERAL("abcdefgh0123-234")
      && o4 + 0 + 123 + -234 == LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh0123-234");
}

consteval auto cxx20_append3_move_or_temp_str() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return CS{LITERAL("xyzt")} + o1== LITERAL("xyzt")
      && CS{LITERAL("xyzt")} + o2== LITERAL("xyzta")
      && CS{LITERAL("xyzt")} + o3== LITERAL("xyztabcdefgh")
      && CS{LITERAL("xyzt")} + o4== LITERAL("xyztabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");
}

consteval auto cxx20_append3_strlike() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return LITERAL("xyzt") + CS{} + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} + o1 == LITERAL("xyztxyztxyztxyzt")
      && LITERAL("xyzt") + CS{} + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} + o2 == LITERAL("xyztxyztxyztxyzta")
      && LITERAL("xyzt") + CS{} + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} + o3 == LITERAL("xyztxyztxyztxyztabcdefgh")
      && LITERAL("xyzt") + CS{} + stdsv{LITERAL("xyzt")} + stds{LITERAL("xyzt")} + SV{LITERAL("xyzt")} + o4 == LITERAL("xyztxyztxyztxyztabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");
}

consteval auto cxx20_append3_char() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return LITERAL('x') + o1 == LITERAL("x")
      && LITERAL('x') + o2 == LITERAL("xa")
      && LITERAL('x') + o3 == LITERAL("xabcdefgh")
      && LITERAL('x') + o4 == LITERAL("xabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");
}

consteval auto cxx20_append3_bool() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return true + o1 + false == LITERAL("truefalse")
      && true + o2 + false == LITERAL("trueafalse")
      && true + o3 + false == LITERAL("trueabcdefghfalse")
      && true + o4 + false == LITERAL("trueabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghfalse");
}

consteval auto cxx20_append3_int() {
  CS o1;
  CS o2 = LITERAL("a");
  CS o3 = LITERAL("abcdefgh");
  CS o4 = LITERAL("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh");

  return  0 + o1 + 123 + -234 == LITERAL("0123-234")
      &&  0 + o2 + 123 + -234 == LITERAL("0a123-234")
      &&  0 + o3 + 123 + -234 == LITERAL("0abcdefgh123-234")
      &&  0 + o4 + 123 + -234 == LITERAL("0abcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh123-234");
}

template <typename N> constexpr auto cxx14_elevated_cxx20_ltrim(CS sv, N&& n) {
  return CS{sv.ltrim(fwd<N>(n))};
}

template <typename N> constexpr auto cxx14_elevated_cxx20_rtrim(CS sv, N&& n) {
  return CS{sv.rtrim(fwd<N>(n))};
}

template <typename N> constexpr auto cxx14_elevated_cxx20_trim(CS sv, N&& n) {
  return CS{sv.trim(fwd<N>(n))};
}

template <typename N> constexpr auto cxx14_elevated_cxx20_removePrefix(CS sv, N&& n) {
  return CS{sv.removePrefix(fwd<N>(n))};
}

template <typename N> constexpr auto cxx14_elevated_cxx20_removeSuffix(CS sv, N&& n) {
  return CS{sv.removeSuffix(fwd<N>(n))};
}
} // namespace
} // namespace cexpr
TEST(STRING_TEST_GROUP, cxx20Constexpr) {
  using namespace cexpr;
  auto eqTo = [](auto p) constexpr {
    return [p](auto const& s) constexpr {
      return s == p;
    };
  };

  static_assert(cxx20_def_ctr(&CS::empty), "Failed constexpr");
  static_assert(cxx20_ptr_len_ctr(&CS::empty, nullptr, 0), "Failed constexpr");
  static_assert(cxx20_ptr_len_ctr(&CS::empty, LITERAL(""), 0), "Failed constexpr");
  static_assert(cxx20_ptr_len_ctr(f::notFn(&CS::empty), LITERAL("abc"), 3), "Failed constexpr");
  static_assert(cxx20_copy_ctr(&CS::empty, nullptr), "Failed constexpr");
  static_assert(cxx20_copy_ctr(&CS::empty, LITERAL("")), "Failed constexpr");
  static_assert(!cxx20_copy_ctr(&CS::empty, LITERAL("abc")), "Failed constexpr");
  static_assert(cxx20_move_ctr(&CS::empty, CS{nullptr}), "Failed constexpr");
  static_assert(cxx20_move_ctr(&CS::empty, CS{LITERAL("")}), "Failed constexpr");
  static_assert(cxx20_move_ctr(f::notFn(&CS::empty), CS{LITERAL("abc")}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, nullptr), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, LITERAL("")), "Failed constexpr");
  static_assert(cxx20_conv_ctr(f::notFn(&CS::empty), LITERAL("abc")), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, SV{}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, SV{nullptr}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, SV{LITERAL("")}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(f::notFn(&CS::empty), SV{LITERAL("abc")}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, stdsv{}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, stdsv{LITERAL("")}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(f::notFn(&CS::empty), stdsv{LITERAL("abc")}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, stds{}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(&CS::empty, stds{LITERAL("")}), "Failed constexpr");
  static_assert(cxx20_conv_ctr(f::notFn(&CS::empty), stds{LITERAL("abc")}), "Failed constexpr");
  static_assert(cxx20_sized_ctr(&CS::empty, 0, LITERAL(' ')), "Failed constexpr");
  static_assert(cxx20_sized_ctr(f::notFn(&CS::empty), 1, LITERAL(' ')), "Failed constexpr");
  static_assert(cxx20_bool_ctr(eqTo(LITERAL("true")), true), "Failed constexpr");
  static_assert(cxx20_bool_ctr(eqTo(LITERAL("false")), false), "Failed constexpr");
  static_assert(cxx20_int_ctr(eqTo(LITERAL("0")), 0), "Failed constexpr");
  static_assert(cxx20_int_ctr(eqTo(LITERAL("-1234")), -1234), "Failed constexpr");
  static_assert(cxx20_int_ctr(eqTo(LITERAL("234")), 234), "Failed constexpr");
  // static_assert(cxx20_copy_assign(nullptr, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_copy_assign(LITERAL(""), LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_copy_assign(LITERAL("a"), LITERAL("a")), "Failed constexpr");
  // static_assert(cxx20_copy_assign(LITERAL("abcd"), LITERAL("abcd")), "Failed constexpr");
  // static_assert(cxx20_copy_assign(LITERAL("abcdefghijk"), LITERAL("abcdefghijk")), "Failed constexpr");
  // static_assert(cxx20_move_assign(nullptr, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_move_assign(LITERAL(""), LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_move_assign(LITERAL("a"), LITERAL("a")), "Failed constexpr");
  // static_assert(cxx20_move_assign(LITERAL("abcd"), LITERAL("abcd")), "Failed constexpr");
  // static_assert(cxx20_move_assign(LITERAL("abcdefghijk"), LITERAL("abcdefghijk")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(nullptr, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(LITERAL(""), LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(LITERAL("abc"), LITERAL("abc")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(SV{}, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(SV{nullptr}, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(SV{LITERAL("")}, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(SV{LITERAL("abc")}, LITERAL("abc")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(stdsv{}, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(stdsv{LITERAL("")}, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(stdsv{LITERAL("abc")}, LITERAL("abc")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(stds{}, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(stds{LITERAL("")}, LITERAL("")), "Failed constexpr");
  // static_assert(cxx20_conv_assign(stds{LITERAL("abc")}, LITERAL("abc")), "Failed constexpr");
  // static_assert(cxx20_bool_assign(false, LITERAL("false")), "Failed constexpr");
  // static_assert(cxx20_bool_assign(true, LITERAL("true")), "Failed constexpr");
  // static_assert(cxx20_int_assign(0, LITERAL("0")), "Failed constexpr");
  // static_assert(cxx20_int_assign(-123, LITERAL("-123")), "Failed constexpr");
  // static_assert(cxx20_int_assign(452, LITERAL("452")), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_datalen(nullptr, LITERAL("")), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_datalen(LITERAL(""), LITERAL("")), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_datalen(LITERAL("abc"), LITERAL("abc")), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_length(nullptr) == 0, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_length(LITERAL("")) == 0, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_length(LITERAL("abc")) == 3, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_size(nullptr) == 0, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_size(LITERAL("")) == 0, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_size(LITERAL("abc")) == 3, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_capacity(nullptr) == 31, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_capacity(LITERAL("")) == 31, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_capacity(LITERAL("abc")) == 31, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_capacity(LITERAL("abc abc abc abc abc abc abc abc abc abc abc abc abc abc abc abc abc abc abc abc")) == 79, "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_empty(nullptr), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_empty(LITERAL("")), "Failed constexpr");
  // static_assert(!cxx11_elevated_cxx20_empty(LITERAL("abc")), "Failed constexpr");
  // static_assert(!cxx11_elevated_cxx20_op_bool(nullptr), "Failed constexpr");
  // static_assert(!cxx11_elevated_cxx20_op_bool(LITERAL("")), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_op_bool(LITERAL("abc")), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_iteration(), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_citeration(), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_riteration(), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_criteration(), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_op_sqb(LITERAL("abc"), 1) == LITERAL('b'), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_at(LITERAL("abc"), 1) == LITERAL('b'), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_front(LITERAL("abc")) == LITERAL('a'), "Failed constexpr");
  // static_assert(cxx11_elevated_cxx20_back(LITERAL("abc")) == LITERAL('c'), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_sub(eqTo(LITERAL("bc")), LITERAL("abc"), 1), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_sub(eqTo(LITERAL("b")), LITERAL("abc"), 1, 2), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_op_rnb(eqTo(LITERAL("bc")), LITERAL("abc"), 1), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_op_rnb(eqTo(LITERAL("b")), LITERAL("abc"), 1, 2), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_contains(nullptr, LITERAL("ab")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_contains(LITERAL(""), LITERAL("ab")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_contains(LITERAL("c"), LITERAL("ab")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_contains(LITERAL("a"), LITERAL("ab")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_contains(LITERAL("b"), LITERAL("ab")), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_contains(LITERAL("ab"), LITERAL("a")), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_contains(LITERAL("ab"), LITERAL("b")), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_contains(LITERAL("ab"), LITERAL('b')), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_contains(LITERAL("ab"), LITERAL("ab")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_startsWith(nullptr, LITERAL('a')), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_startsWith(nullptr, LITERAL("a")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_startsWith(LITERAL(""), LITERAL('a')), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_startsWith(LITERAL(""), LITERAL("a")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_startsWith(LITERAL("ba"), LITERAL('a')), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_startsWith(LITERAL("ba"), LITERAL("a")), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_startsWith(LITERAL("ab"), LITERAL('a')), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_startsWith(LITERAL("ab"), LITERAL("a")), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_startsWith(LITERAL("ab"), LITERAL("ab")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_startsWith(LITERAL("ab"), LITERAL("abc")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_endsWith(nullptr, LITERAL('a')), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_endsWith(nullptr, LITERAL("a")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_endsWith(LITERAL(""), LITERAL('a')), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_endsWith(LITERAL(""), LITERAL("a")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_endsWith(LITERAL("ab"), LITERAL('a')), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_endsWith(LITERAL("ab"), LITERAL("a")), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_endsWith(LITERAL("ba"), LITERAL('a')), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_endsWith(LITERAL("ba"), LITERAL("a")), "Failed constexpr");
  // static_assert(cxx14_elevated_cxx20_endsWith(LITERAL("ab"), LITERAL("ab")), "Failed constexpr");
  // static_assert(!cxx14_elevated_cxx20_endsWith(LITERAL("ab"), LITERAL("cab")), "Failed constexpr");
  // static_assert(cxx20_split(LITERAL("a b c"), LITERAL(' '), LITERAL("a"), LITERAL("b"), LITERAL("c")), "failed constexpr");
  // static_assert(cxx20_split(LITERAL("a b c"), LITERAL(" "), LITERAL("a"), LITERAL("b"), LITERAL("c")), "failed constexpr");
  // std::array<CHAR_TYPE, 1> constexpr sep1 {LITERAL(' ')};
  // std::array<SV, 1> constexpr sep2 {LITERAL(" ")};
  // static_assert(cxx20_split(LITERAL("a b c"), sep1, LITERAL("a"), LITERAL("b"), LITERAL("c")), "failed constexpr");
  // static_assert(cxx20_split(LITERAL("a b c"), sep2, LITERAL("a"), LITERAL("b"), LITERAL("c")), "failed constexpr");
  // static_assert(cxx20_resize(), "failed constexpr");
  // static_assert(cxx20_reserve(), "failed constexpr");
  // static_assert(cxx20_shrink(), "failed constexpr");
  // static_assert(cxx20_clear(), "failed constexpr");
  // static_assert(cxx20_append_move_or_temp_str(), "failed constexpr");
  // static_assert(cxx20_append_strlike(), "failed constexpr");
  // static_assert(cxx20_append_char(), "failed constexpr");
  // static_assert(cxx20_append_bool(), "failed constexpr");
  // static_assert(cxx20_append_int(), "failed constexpr");
  // static_assert(cxx20_append2_move_or_temp_str(), "failed constexpr");
  // static_assert(cxx20_append2_strlike(), "failed constexpr");
  // static_assert(cxx20_append2_char(), "failed constexpr");
  // static_assert(cxx20_append2_bool(), "failed constexpr");
  // static_assert(cxx20_append2_int(), "failed constexpr");
  // static_assert(cxx20_append3_move_or_temp_str(), "failed constexpr");
  // static_assert(cxx20_append3_strlike(), "failed constexpr");
  // static_assert(cxx20_append3_char(), "failed constexpr");
  // static_assert(cxx20_append3_bool(), "failed constexpr");
  // static_assert(cxx20_append3_int(), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_ltrim(LITERAL("abc"), LITERAL('a')) == LITERAL("bc"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_ltrim(LITERAL("abc"), LITERAL("ab")) == LITERAL("c"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_rtrim(LITERAL("abc"), LITERAL('c')) == LITERAL("ab"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_rtrim(LITERAL("abc"), LITERAL("bc")) == LITERAL("a"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_trim(LITERAL("abcab"), LITERAL("ab")) == LITERAL("c"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_trim(LITERAL("abcab"), LITERAL('a')) == LITERAL("bcab"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_ltrim(LITERAL("abc"), LITERAL("ac")) == LITERAL("bc"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_rtrim(LITERAL("abc"), LITERAL("ac")) == LITERAL("ab"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_trim(LITERAL("abcab"), LITERAL("ac")) == LITERAL("bcab"), "failed constexpr");
  // static_assert(cxx14_elevated_cxx20_removePrefix(LITERAL("   ab"), LITERAL("  ")) == LITERAL(" ab"), "constexpr failed");
  // static_assert(cxx14_elevated_cxx20_removeSuffix(LITERAL("ab   "), LITERAL("  ")) == LITERAL("ab "), "constexpr failed");
  // using namespace cds::literals;
  // static_assert(LITERAL_OP("") == LITERAL(""), "constexpr failed");
  // static_assert(LITERAL_OP("abc") == LITERAL("abc"), "constexpr failed");
}
#endif
