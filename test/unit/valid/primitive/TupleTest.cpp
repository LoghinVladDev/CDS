// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/Tuple>
#include <cds/String>
#include <cds/StringView>

namespace {
using cds::Tuple;
using cds::String;
using cds::StringView;
using cds::impl::get;
} // namespace

TEST(TupleTest, TupleNodeConstructAcquireTest) {
  Tuple<int, float, String> node {1, 3.4f, "abcd"};
  ASSERT_EQ(1, get<0u>(node));
  ASSERT_LT(3.3f, get<1u>(node));
  ASSERT_GT(3.5f, get<1u>(node));
  ASSERT_EQ("abcd", get<2u>(node));
}

TEST(TupleTest, TupleNodeModifyTest) {
  Tuple<int, String> node;

  get<0u>(node) = 3;
  get<1u>(node) = "abcd";

  ASSERT_EQ(3, get<0u>(node));
  ASSERT_EQ("abcd", get<1u>(node));
}

TEST(TupleTest, hash) {
  Tuple <int, int, int> t1 {4, 5, 6};
  ASSERT_EQ(4 + (5 + 6 * 31) * 31, cds::functional::Hash<>()(t1));
}

TEST(TupleTest, toString) {
  Tuple <int, String> t {3, "abcd"};
  ASSERT_EQ("(3, abcd)", t.toString());
}

TEST(TupleTest, tupleOf) {
  auto t = cds::tupleOf(2, "abcd", 4, "def", 3);
  ASSERT_EQ(2, get<0>(t));
  ASSERT_EQ(StringView{"abcd"}, get<1>(t));
  ASSERT_EQ(4, get<2>(t));
  ASSERT_EQ(StringView{"def"}, get<3>(t));
  ASSERT_EQ(3, get<4>(t));
}

TEST(TupleTest, of) {
  auto t = Tuple<>::of(2, "abcd", 4, "def", 3);
  ASSERT_EQ(2, get<0>(t));
  ASSERT_EQ(StringView{"abcd"}, get<1>(t));
  ASSERT_EQ(4, get<2>(t));
  ASSERT_EQ(StringView{"def"}, get<3>(t));
  ASSERT_EQ(3, get<4>(t));
}

#if DCR_SINCECPP11
namespace cxx11 {
template <cds::Size idx, typename T> constexpr auto get(T const& tuple) noexcept -> decltype(tuple.template get<idx>()) {
  return tuple.template get<idx>();
}
} // namespace cxx11

TEST(TupleTest, constexprCpp11) {
  static_assert(cxx11::get<0>(Tuple<int, long>{1, 3L}) == 1, "constexpr11 construct&get failed");
  static_assert(cxx11::get<0>(Tuple<int, long>{1, 3L}) == 1, "constexpr11 construct&get failed");
  static_assert(cxx11::get<1>(Tuple<int, long>{1, 3L}) == 3L, "constexpr11 construct&get failed");
  static_assert(Tuple<int, long>{1, 3L} == Tuple<int, long>{1, 3L}, "constexpr11 construct&op== failed");
  static_assert(Tuple<int, long>{1, 3L} != Tuple<int, long>{2, 3L}, "constexpr11 construct&op!= failed");
  static_assert(Tuple<int, long>{1, 3L} != Tuple<int, long>{1, 2L}, "constexpr11 construct&op!= failed");
  static_assert(cds::functional::Hash<>()(Tuple<int, int>{1, 1}) == 32, "constexpr11 hash failed");
  static_assert(cds::tupleOf(1, 3L) == Tuple<int, long>{1, 3L}, "constexpr11 makeTuple failed");
  static_assert(cds::tupleOf(1, 3) == Tuple<int, long>{1, 3L}, "constexpr11 makeTuple failed");
  static_assert(cds::tupleOf(1, 3) != Tuple<int, long>{1, 2L}, "constexpr11 makeTuple failed");
}
#endif

#if DCR_SINCECPP14
TEST(TupleTest, constexprCpp14) {
  static_assert(get<0>(Tuple<int, long>{1, 3L}) == 1, "constexpr14 construct&get failed");
  static_assert(get<1>(Tuple<int, long>{1, 3L}) == 3L, "constexpr14 construct&get failed");
}
#endif

#if DCR_SINCECPP17
TEST(TupleTest, TupleNodeUnpackBindings) {
  auto [x, y] = Tuple<int, String> {3, "abcd"};
  ASSERT_EQ(3, x);
  ASSERT_EQ("abcd", y);

  Tuple<int, String> t1;
  auto& [x1, y1] = t1;
  x1 = 5;
  y1 = "xyzt";

  ASSERT_EQ(5, get<0u>(t1));
  ASSERT_EQ("xyzt", get<1u>(t1));

  auto const& [x2, y2] = t1;
  ASSERT_EQ(5, x2);
  ASSERT_EQ("xyzt", y2);

  auto const t2 = t1;
  auto& [x3, y3] = t2;
  ASSERT_EQ(5, x3);
  ASSERT_EQ("xyzt", y3);

  auto const& [x4, y4] = t2;
  ASSERT_EQ(5, x4);
  ASSERT_EQ("xyzt", y4);
}
#endif // DCR_SINCECPP17

#if DCR_SINCECPP20
TEST(TupleTest, constexprCpp20) {
  static_assert(cds::tupleOf(1, "abcd").toString() == "(1, abcd)", "constexpr20 toString failed");
}
#endif // DCR_SINCECPP20
