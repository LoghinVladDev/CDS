// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../../src/policy/RehashPolicy.hpp"
#include "UnitTest.hpp"

namespace {
using cds::Size;
using cds::impl::TableRehashPolicy;
using cds::impl::PrimeRehashTable;
}

TEST(RehashPolicy, PrimeRehashPolicy) {
  TableRehashPolicy<PrimeRehashTable<>> policy;
  using BT = decltype(policy)::BalanceType;

  ASSERT_EQ(policy.current(), 13);
  ASSERT_EQ(policy.load(), 1);
  ASSERT_EQ(policy.balance(0, 0, 1).type, BT::Required);
  ASSERT_EQ(policy.balance(0, 0, 1).size, 13);
  ASSERT_EQ(policy.balance(0, 12, 1).type, BT::Required);
  ASSERT_EQ(policy.balance(0, 12, 1).size, 13);
  ASSERT_EQ(policy.balance(13, 0, 1).type, BT::Stable);
  ASSERT_EQ(policy.balance(13, 12, 1).type, BT::Stable);
  ASSERT_EQ(policy.balance(13, 4, 9).type, BT::Stable);

  auto const r1 = policy.balance(0, 13, 1);
  ASSERT_EQ(r1.type, BT::Required);
  ASSERT_EQ(r1.size, 29);

  auto const r2 = policy.balance(29, 29, 1);
  ASSERT_EQ(r2.type, BT::Required);
  ASSERT_EQ(r2.size, 59);

  using Table = cds::impl::prp::PrimeRehashTable<Size>;
  auto const tableEnd = Table::_ft[Table::_fts - 1];
  (void) policy.balance(59, tableEnd, 1);
  auto const r3 = policy.balance(tableEnd, tableEnd, 1);
  ASSERT_EQ(r3.type, BT::Impossible);
  ASSERT_EQ(r3.size, tableEnd);
  ASSERT_EQ(policy.load(), 1);

  policy.reset();
  auto const r4 = policy.balance(13, 13, 50);
  ASSERT_EQ(r4.type, BT::Required);
  ASSERT_EQ(r4.size, 127);

  auto policyCopy = policy;
  ASSERT_EQ(policyCopy.load(), 1);
  ASSERT_EQ(policyCopy.current(), 127);
}

TEST(RehashPolicy, LoadFactorPrimeRehashPolicy) {
  TableRehashPolicy<PrimeRehashTable<>> policy(2);
  using BT = decltype(policy)::BalanceType;

  ASSERT_EQ(policy.current(), 13);
  ASSERT_EQ(policy.load(), 2);

  auto const r1 = policy.balance(13, 25, 1);
  ASSERT_EQ(r1.type, BT::Stable);
  ASSERT_EQ(r1.size, 13);

  auto const r2 = policy.balance(13, 26, 1);
  ASSERT_EQ(r2.type, BT::Required);
  ASSERT_EQ(r2.size, 29);
}

#if DCR_SINCECPP11
TEST(RehashPolicy, constexpr11) {
  constexpr TableRehashPolicy<PrimeRehashTable<>> policy;
  constexpr TableRehashPolicy<PrimeRehashTable<>> loadedPolicy(2);
  static_assert(policy.load() == 1, "Failed constexpr test");
  static_assert(loadedPolicy.load() == 2, "Failed constexpr test");
}
#endif

#if DCR_SINCECPP17
constexpr bool constexpr17Cont() {
  TableRehashPolicy<PrimeRehashTable<>> policy;
  using T = decltype(policy)::BalanceType;
  auto const sOk = policy.current() == 13;
  auto const [s1, t1] = policy.balance(0, 1, 1);
  auto const ftOk = t1 == T::Required;
  auto const fsOk = s1 == 13;
  auto const [s2, t2] = policy.balance(13, 12, 1);
  auto const stOk = t2 == T::Stable;
  auto const ssOk = s2 == 13;
  auto const [s3, t3] = policy.balance(13, 13, 1);
  auto const ttOk = t3 == T::Required;
  auto const tsOk = s3 == 29;

  auto const cbr = policy.current() == 29;
  policy.reset();
  auto const car = policy.current() == 13;
  return sOk && ftOk && fsOk && stOk && ssOk && ttOk && tsOk && cbr && car;
}

TEST(RehashPolicy, constexpr17) {
  static_assert(constexpr17Cont(), "Failed constexpr test");
}
#endif
