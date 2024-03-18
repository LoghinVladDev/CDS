// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../../src/algorithm/GenericFind.hpp"
#include "UnitTest.hpp"
#include <cds/meta/Semantics>
#include <cds/functional/Comparator>
#include <vector>

namespace {
using namespace cds;
using namespace cds::impl;
using namespace cds::functional;
using iterator::impl::FindResultTransformer;
using iterator::impl::FindPreserveTransformer;
} // namespace

namespace {
template <typename I, typename V> CDS_ATTR(constexpr(14)) auto find(I&& iter, V&& val) noexcept(noexcept(
    impl::find(cds::forward<I>(iter), cds::forward<V>(val), functional::Equal<>(), FindResultTransformer<>())
)) -> decltype(
    impl::find(cds::forward<I>(iter), cds::forward<V>(val), functional::Equal<>(), FindResultTransformer<>())
) {
  return
      impl::find(cds::forward<I>(iter), cds::forward<V>(val), functional::Equal<>(), FindResultTransformer<>());
}
} // namespace

namespace {
template <typename I, typename V, typename P> CDS_ATTR(constexpr(14)) auto find(I&& iter, V&& val, P&& projector)
    noexcept(noexcept(impl::find(
        cds::forward<I>(iter), cds::forward<V>(val), cds::forward<P>(projector),
        functional::Equal<>(), FindResultTransformer<>()
    ))) -> decltype(impl::find(
        cds::forward<I>(iter), cds::forward<V>(val), cds::forward<P>(projector),
        functional::Equal<>(), FindResultTransformer<>()
    )) {
  return impl::find(
      cds::forward<I>(iter), cds::forward<V>(val), cds::forward<P>(projector),
      functional::Equal<>(), FindResultTransformer<>()
  );
}
} // namespace

TEST(GenericFind, ownership) {
  std::vector<int> i {1, 2, 3};
  auto v = 2;

  auto l1 = find(i, v);
  auto l2 = find(i, 2);
  auto l3 = find(std::vector<int>{1, 2, 3}, v);
  auto l4 = find(std::vector<int>{1, 2, 3}, 2);

  auto b1 = l1.begin();
  auto b2 = l2.begin();
  auto b3 = l3.begin();
  auto b4 = l4.begin();

  ASSERT_NE(b1, l1.end());
  ASSERT_NE(b2, l2.end());
  ASSERT_NE(b3, l3.end());
  ASSERT_NE(b4, l4.end());
  ASSERT_EQ(*b1, 2);
  ASSERT_EQ(*b2, 2);
  ASSERT_EQ(*b3, 2);
  ASSERT_EQ(*b4, 2);
  ++b1;
  ++b2;
  ++b3;
  ++b4;
  ASSERT_EQ(b1, l1.end());
  ASSERT_EQ(b2, l2.end());
  ASSERT_EQ(b3, l3.end());
  ASSERT_EQ(b4, l4.end());

  std::vector<int> const ci {1, 2, 3};
  auto cv = 2;

  auto cl1 = find(ci, cv);
  auto cl2 = find(ci, (const int)2);
  auto cl3 = find(std::vector<int>{1, 2, 3}, cv);
  auto cl4 = find(std::vector<int>{1, 2, 3}, (const int)2);

  auto cb1 = cl1.begin();
  auto cb2 = cl2.begin();
  auto cb3 = cl3.begin();
  auto cb4 = cl4.begin();

  ASSERT_NE(cb1, cl1.end());
  ASSERT_NE(cb2, cl2.end());
  ASSERT_NE(cb3, cl3.end());
  ASSERT_NE(cb4, cl4.end());
  ASSERT_EQ(*cb1, 2);
  ASSERT_EQ(*cb2, 2);
  ASSERT_EQ(*cb3, 2);
  ASSERT_EQ(*cb4, 2);
  ++cb1;
  ++cb2;
  ++cb3;
  ++cb4;
  ASSERT_EQ(cb1, cl1.end());
  ASSERT_EQ(cb2, cl2.end());
  ASSERT_EQ(cb3, cl3.end());
  ASSERT_EQ(cb4, cl4.end());
}

namespace {int doubled(int v){ return v * 2; }}
TEST(GenericFind, find) {
  std::vector<int> v {1, 2, 3, 2, 1};
  auto locs1 = find(v, 1);
  auto b1 = locs1.begin();
  ASSERT_NE(b1, locs1.end());
  ASSERT_EQ(*b1, 1);
  ++b1;
  ASSERT_NE(b1, locs1.end());
  ASSERT_EQ(*b1, 1);
  ++b1;
  ASSERT_EQ(b1, locs1.end());

  auto locs2 = find(v, 2);
  auto b2 = locs2.begin();
  ASSERT_NE(b2, locs2.end());
  ASSERT_EQ(*b2, 2);
  ++b2;
  ASSERT_NE(b2, locs2.end());
  ASSERT_EQ(*b2, 2);
  ++b2;
  ASSERT_EQ(b2, locs2.end());

  auto locs3 = find(v, 3);
  auto b3 = locs3.begin();
  ASSERT_NE(b3, locs3.end());
  ASSERT_EQ(*b3, 3);
  ++b3;
  ASSERT_EQ(b3, locs3.end());

  auto locs4 = find(v, 4);
  ASSERT_EQ(locs4.begin(), locs4.end());

  auto locs1Doubled = find(v, 2, doubled);
  auto b1d = locs1Doubled.begin();
  ASSERT_NE(b1d, locs1Doubled.end());
  ASSERT_EQ(*b1d, 1);
  ++b1d;
  ASSERT_NE(b1d, locs1Doubled.end());
  ASSERT_EQ(*b1d, 1);
  ++b1d;
  ASSERT_EQ(b1d, locs1Doubled.end());

  auto locsInvalid = find(v, 3, doubled);
  ASSERT_EQ(locsInvalid.begin(), locsInvalid.end());

  auto m1 = std::move(b1);
  auto m2 = std::move(b1d);
  (void) m1;
  (void) m2;

  m1 = b2;
  (void) m1;
  m1 = std::move(b2);

  auto b2d = locs1Doubled.begin();
  m2 = b2d;
  (void) m2;
  m2 = std::move(b2d);

  (void) m1;
  (void) m2;

  m1 = m1;
  m1 = std::move(m1);

  m2 = m2;
  m2 = std::move(m2);

  ASSERT_EQ(m1, m1);
  ASSERT_FALSE(m1 != m1);

  ASSERT_EQ(m2, m2);
  ASSERT_FALSE(m2 != m2);
}

TEST(GenericFind, constant) {
  std::vector<int> v {1, 2, 3};
  auto const r1 = find(v, 2);
  auto it = r1.begin();
  ASSERT_NE(it, r1.end());
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(it, r1.end());

  auto const r2 = find(v, 4, doubled);
  auto it1 = r2.begin();
  ASSERT_NE(it1, r2.end());
  ASSERT_EQ(*it1, 2);
  ++it1;
  ASSERT_EQ(it1, r2.end());
}

struct X : private std::vector<int> {
  X() : std::vector<int>{1, 2, 3} {}
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

namespace cds {
namespace impl {
template <> struct GenericFindEnabledFor<X, int, Equal<>> : False {};
template <> struct GenericFindFirstUsingFind<X, int, Equal<>> : True {};
template <> struct GenericFindLastUsingFind<X, int, Equal<>> : True {};
template <> struct FindUsesAllocation<X, int, Equal<>> : False {};
}
}

template <
    typename V, typename E, typename T,
    typename R = FindIterableRange<X const&, Extend<V>, E, T>
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    X const& iterable, V&& value, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(iterable, cds::forward<V>(value))))) -> R {
  return R(iterable, cds::forward<V>(value));
}

template <
    typename V, typename E, typename P, typename T,
    typename R = FindSelectIterableRange<X const&, Extend<V>, Extend<P>, E, T>
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    X const& iterable, V&& value, P&& projector, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(iterable, cds::forward<V>(value), cds::forward<P>(projector))))) -> R {
  return R(iterable, cds::forward<V>(value), cds::forward<P>(projector));
}

TEST(GenericFind, genericFirstFromSpecialized) {
  auto const x = X{};
  auto const it = impl::findFirst(x, 2, Equal<>(), FindPreserveTransformer<>());
  ASSERT_NE(it, x.end());
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(impl::findFirst(x, 4, Equal<>(), FindPreserveTransformer<>()), x.end());
  auto const it2 = findFirst(x, 4, doubled, Equal<>(), FindPreserveTransformer<>());
  ASSERT_NE(it2, x.end());
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(findFirst(x, 3, doubled, Equal<>(), FindPreserveTransformer<>()), x.end());
}

TEST(GenericFind, genericLastFromSpecialized) {
  auto const x = X{};
  auto const it = impl::findLast(x, 2, Equal<>(), FindPreserveTransformer<>());
  ASSERT_NE(it, x.end());
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(impl::findLast(x, 4, Equal<>(), FindPreserveTransformer<>()), x.end());
  auto const it2 = findLast(x, 4, doubled, Equal<>(), FindPreserveTransformer<>());
  ASSERT_NE(it2, x.end());
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(findLast(x, 3, doubled, Equal<>(), FindPreserveTransformer<>()), x.end());
}
