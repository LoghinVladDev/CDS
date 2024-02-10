// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/policy/RehashPolicy.hpp"
#include "UnitTest.hpp"

namespace {
using cds::Size;
using cds::impl::PrimeRehashPolicy;
}

TEST(RehashPolicy, PrimeRehashPolicy) {
  PrimeRehashPolicy<> policy;
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

  auto r1 = policy.balance(0, 13, 1);
  ASSERT_EQ(r1.type, BT::Required);
  ASSERT_EQ(r1.size, 29);

  auto r2 = policy.balance(29, 29, 1);
  ASSERT_EQ(r2.type, BT::Required);
  ASSERT_EQ(r2.size, 59);

  (void) policy.balance(59, 282800996033ULL, 1);
  auto r3 = policy.balance(282800996033ULL, 282800996033ULL, 1);
  ASSERT_EQ(r3.type, BT::Impossible);
  ASSERT_EQ(r3.size, 282800996033ULL);
  ASSERT_EQ(policy.load(), 1);

  policy.reset();
  auto r4 = policy.balance(13, 13, 50);
  ASSERT_EQ(r4.type, BT::Required);
  ASSERT_EQ(r4.size, 127);

  auto policyCopy = policy;
  ASSERT_EQ(policyCopy.load(), 1);
  ASSERT_EQ(policyCopy.current(), 127);
}

TEST(RehashPolicy, LoadFactorPrimeRehashPolicy) {
  PrimeRehashPolicy<> policy(2);
  using BT = decltype(policy)::BalanceType;

  ASSERT_EQ(policy.current(), 13);
  ASSERT_EQ(policy.load(), 2);

  auto r1 = policy.balance(13, 25, 1);
  ASSERT_EQ(r1.type, BT::Stable);
  ASSERT_EQ(r1.size, 13);

  auto r2 = policy.balance(13, 26, 1);
  ASSERT_EQ(r2.type, BT::Required);
  ASSERT_EQ(r2.size, 29);
}

#if DCR_SINCECPP11
TEST(RehashPolicy, constexpr11) {
  constexpr PrimeRehashPolicy<> policy;
  constexpr PrimeRehashPolicy<> loadedPolicy(2);
  static_assert(policy.load() == 1, "Failed constexpr test");
  static_assert(loadedPolicy.load() == 2, "Failed constexpr test");
}
#endif

#if DCR_SINCECPP17
constexpr bool constexpr17Cont() {
  PrimeRehashPolicy<> policy;
  using T = decltype(policy)::BalanceType;
  auto sOk = policy.current() == 13;
  auto r1 = policy.balance(0, 1, 1);
  auto ftOk = r1.type == T::Required;
  auto fsOk = r1.size == 13;
  auto r2 = policy.balance(13, 12, 1);
  auto stOk = r2.type == T::Stable;
  auto ssOk = r2.size == 13;
  auto r3 = policy.balance(13, 13, 1);
  auto ttOk = r3.type == T::Required;
  auto tsOk = r3.size == 29;

  auto cbr = policy.current() == 29;
  policy.reset();
  auto car = policy.current() == 13;
  return sOk && ftOk && fsOk && stOk && ssOk && ttOk && tsOk && cbr && car;
}

TEST(RehashPolicy, constexpr17) {
  static_assert(constexpr17Cont(), "Failed constexpr test");
}
#endif
