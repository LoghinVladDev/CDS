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

template <typename T, typename E> struct BasePeeker : ExpectedCopyConstructibleBase<T, E> {
  using Base = ExpectedCopyConstructibleBase<T, E>;
  using Base::Base;
  using Base::data;
  using Base::destroy;
  using Base::state;
  using Base::operator=;

  using Base::assignFrom;
  using Base::constructFrom;

  CDS_ATTR(2(explicit, constexpr(11))) BasePeeker(Uninitialized) noexcept : Base{Uninitialized{}} {}
};

struct TriviallyCopyable {
  int x; int y; int z;
  TriviallyCopyable(TriviallyCopyable const&) = default;
  TriviallyCopyable(int x, int y, int z) : x{x}, y{y}, z{z} {}
};

struct NonTriviallyCopyable {
  int x; int y; int z;
  NonTriviallyCopyable(NonTriviallyCopyable const& obj) : x{obj.x}, y{obj.y}, z{obj.z} {}
  NonTriviallyCopyable(int x, int y, int z) : x{x}, y{y}, z{z} {}
};
} // namespace

TEST(ExpectedCopyConstructibleBaseTest, trivialCopyAsValue) {
  BasePeeker<TriviallyCopyable, int> orig{1, 2, 3};
  BasePeeker<TriviallyCopyable, int> copy{orig};

  ASSERT_EQ(ExpectedState::Value, copy.state());
  ASSERT_EQ(1, copy.data().value.x);
  ASSERT_EQ(2, copy.data().value.y);
  ASSERT_EQ(3, copy.data().value.z);
}

TEST(ExpectedCopyConstructibleBaseTest, trivialCopyAsError) {
  BasePeeker<int, TriviallyCopyable> orig{Unexpect{}, 1, 2, 3};
  BasePeeker<int, TriviallyCopyable> copy{orig};

  ASSERT_EQ(ExpectedState::Error, copy.state());
  ASSERT_EQ(1, copy.data().error.x);
  ASSERT_EQ(2, copy.data().error.y);
  ASSERT_EQ(3, copy.data().error.z);
}

TEST(ExpectedCopyConstructibleBaseTest, nonTrivialCopyAsValue) {
  BasePeeker<NonTriviallyCopyable, int> orig{1, 2, 3};
  BasePeeker<NonTriviallyCopyable, int> copy{orig};

  ASSERT_EQ(ExpectedState::Value, copy.state());
  ASSERT_EQ(1, copy.data().value.x);
  ASSERT_EQ(2, copy.data().value.y);
  ASSERT_EQ(3, copy.data().value.z);
}

TEST(ExpectedCopyConstructibleBaseTest, nonTrivialCopyAsError) {
  BasePeeker<int, NonTriviallyCopyable> orig{Unexpect{}, 1, 2, 3};
  BasePeeker<int, NonTriviallyCopyable> copy{orig};

  ASSERT_EQ(ExpectedState::Error, copy.state());
  ASSERT_EQ(1, copy.data().error.x);
  ASSERT_EQ(2, copy.data().error.y);
  ASSERT_EQ(3, copy.data().error.z);
}

TEST(ExpectedCopyConstructibleBaseTest, voidNonTrivialCopyAsValue) {
  BasePeeker<void, NonTriviallyCopyable> orig{};
  BasePeeker<void, NonTriviallyCopyable> copy{orig};

  ASSERT_EQ(ExpectedState::Value, copy.state());
}

TEST(ExpectedCopyConstructibleBaseTest, voidNonTrivialCopyAsError) {
  BasePeeker<void, NonTriviallyCopyable> orig{Unexpect{}, 1, 2, 3};
  BasePeeker<void, NonTriviallyCopyable> copy{orig};

  ASSERT_EQ(ExpectedState::Error, copy.state());
  ASSERT_EQ(1, copy.data().error.x);
  ASSERT_EQ(2, copy.data().error.y);
  ASSERT_EQ(3, copy.data().error.z);
}
