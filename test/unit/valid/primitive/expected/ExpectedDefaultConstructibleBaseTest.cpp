// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include "cds/Expected"
#include "cds/Format"

#include "cds/memory/Allocator"

namespace {
using namespace cds;
using namespace cds::meta;
using namespace cds::impl;

template <typename T, typename E> struct BasePeeker : ExpectedDefaultConstructibleBase<T, E> {
  using Base = ExpectedDefaultConstructibleBase<T, E>;
  using Base::Base;
  using Base::state;
  using Base::data;
  using Base::destroy;

  CDS_ATTR(2(explicit, constexpr(11))) BasePeeker(Uninitialized) : Base{Uninitialized{}} {}
};

struct DefaultConstructible {
  DefaultConstructible() = default;
};

struct NonDefaultConstructible {
  NonDefaultConstructible() = delete;
  NonDefaultConstructible(int) {}
};
} // namespace

TEST(ExpectedDefaultConstructibleBaseTest, defaultCtrPresent) {
  BasePeeker<DefaultConstructible, int> value{};
  ASSERT_EQ(ExpectedState::Value, value.state());

  static_assert(IsBaseOf<
      ExpectedDefaultConstructibleBase<DefaultConstructible, int, SpecialMemberFunctionInfoType::Trivial>,
      BasePeeker<DefaultConstructible, int>
  >::value, "inheritance branching error");
}

TEST(ExpectedDefaultConstructibleBaseTest, defaultCtrAbsent) {
  BasePeeker<NonDefaultConstructible, int> value{0};
  ASSERT_EQ(ExpectedState::Value, value.state());

  static_assert(IsBaseOf<
      ExpectedDefaultConstructibleBase<NonDefaultConstructible, int, SpecialMemberFunctionInfoType::Deleted>,
      BasePeeker<NonDefaultConstructible, int>
  >::value, "inheritance branching error");
}

