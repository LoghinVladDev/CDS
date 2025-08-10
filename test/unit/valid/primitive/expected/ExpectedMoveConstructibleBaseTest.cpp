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

template <typename T, typename E> struct BasePeeker : ExpectedMoveConstructibleBase<T, E> {
  using Base = ExpectedMoveConstructibleBase<T, E>;
  using Base::Base;
  using Base::data;
  using Base::destroy;
  using Base::state;
  using Base::operator=;

  using Base::assignFrom;
  using Base::constructFrom;

  CDS_ATTR(2(explicit, constexpr(11))) BasePeeker(Uninitialized) noexcept : Base{Uninitialized{}} {}
};

struct TriviallyMovable {
  int x; int y; int z;
  TriviallyMovable(TriviallyMovable&&) = default;
  TriviallyMovable(int x, int y, int z) : x{x}, y{y}, z{z} {}
};

struct NonTriviallyMovable {
  int x; int y; int z;
  NonTriviallyMovable(NonTriviallyMovable&& obj) : x{obj.x}, y{obj.y}, z{obj.z} {}
  NonTriviallyMovable(int x, int y, int z) : x{x}, y{y}, z{z} {}
};
} // namespace

TEST(ExpectedMoveConstructibleBaseTest, trivialCopyAsValue) {
  BasePeeker<TriviallyMovable, int> orig{1, 2, 3};
  BasePeeker<TriviallyMovable, int> copy{mv(orig)};

  ASSERT_EQ(ExpectedState::Value, copy.state());
  ASSERT_EQ(1, copy.data().value.x);
  ASSERT_EQ(2, copy.data().value.y);
  ASSERT_EQ(3, copy.data().value.z);
}

TEST(ExpectedMoveConstructibleBaseTest, trivialCopyAsError) {
  BasePeeker<int, TriviallyMovable> orig{Unexpect{}, 1, 2, 3};
  BasePeeker<int, TriviallyMovable> copy{mv(orig)};

  ASSERT_EQ(ExpectedState::Error, copy.state());
  ASSERT_EQ(1, copy.data().error.x);
  ASSERT_EQ(2, copy.data().error.y);
  ASSERT_EQ(3, copy.data().error.z);
}

TEST(ExpectedMoveConstructibleBaseTest, nonTrivialCopyAsValue) {
  BasePeeker<NonTriviallyMovable, int> orig{1, 2, 3};
  BasePeeker<NonTriviallyMovable, int> copy{mv(orig)};

  ASSERT_EQ(ExpectedState::Value, copy.state());
  ASSERT_EQ(1, copy.data().value.x);
  ASSERT_EQ(2, copy.data().value.y);
  ASSERT_EQ(3, copy.data().value.z);
}

TEST(ExpectedMoveConstructibleBaseTest, nonTrivialCopyAsError) {
  BasePeeker<int, NonTriviallyMovable> orig{Unexpect{}, 1, 2, 3};
  BasePeeker<int, NonTriviallyMovable> copy{mv(orig)};

  ASSERT_EQ(ExpectedState::Error, copy.state());
  ASSERT_EQ(1, copy.data().error.x);
  ASSERT_EQ(2, copy.data().error.y);
  ASSERT_EQ(3, copy.data().error.z);
}

TEST(ExpectedMoveConstructibleBaseTest, voidNonTrivialCopyAsValue) {
  BasePeeker<void, NonTriviallyMovable> orig{};
  BasePeeker<void, NonTriviallyMovable> copy{mv(orig)};

  ASSERT_EQ(ExpectedState::Value, copy.state());
}

TEST(ExpectedMoveConstructibleBaseTest, voidNonTrivialCopyAsError) {
  BasePeeker<void, NonTriviallyMovable> orig{Unexpect{}, 1, 2, 3};
  BasePeeker<void, NonTriviallyMovable> copy{mv(orig)};

  ASSERT_EQ(ExpectedState::Error, copy.state());
  ASSERT_EQ(1, copy.data().error.x);
  ASSERT_EQ(2, copy.data().error.y);
  ASSERT_EQ(3, copy.data().error.z);
}
