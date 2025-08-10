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

template <typename T, typename E> struct BasePeeker : ExpectedDestructibleBase<T, E> {
  using Base = ExpectedDestructibleBase<T, E>;
  using Base::Base;
  using Base::state;
  using Base::data;
  using Base::destroy;

  CDS_ATTR(2(explicit, constexpr(11))) BasePeeker(Uninitialized) : Base{Uninitialized{}} {}
};
} // namespace

namespace {
struct TriviallyDestructible {
  CDS_ATTR(constexpr(11)) TriviallyDestructible(int a, int b, int c) : a(a), b(b), c(c) {}
  CDS_ATTR(constexpr(11)) TriviallyDestructible(std::initializer_list<int> const& l, int b, int c) :
      a(static_cast<int>(l.size())), b(b), c(c) {}

  ~TriviallyDestructible() = default;

  int a;
  int b;
  int c;
};
} // namespace

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleArgsConstruct) {
  BasePeeker<TriviallyDestructible, int> obj(1, 2, 3);
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleIListArgsConstruct) {
  BasePeeker<TriviallyDestructible, int> obj({1, 2, 3, 4}, 2, 3);
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(4, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleErrorArgsConstruct) {
  BasePeeker<int, TriviallyDestructible> obj(Unexpect{}, 1, 2, 3);
  ASSERT_EQ(ExpectedState::Error, obj.state());
  ASSERT_EQ(1, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleErrorIListArgsConstruct) {
  BasePeeker<int, TriviallyDestructible> obj(Unexpect{}, {1, 2, 3, 4}, 2, 3);
  ASSERT_EQ(ExpectedState::Error, obj.state());
  ASSERT_EQ(4, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDestroyDisengages) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  obj.destroy();
  ASSERT_EQ(ExpectedState::Uninitialized, obj.state());
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleEngagedConst) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleEngagedMutability) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  obj.state() = ExpectedState::Error;
  ASSERT_EQ(ExpectedState::Error, obj.state());
  obj.state() = ExpectedState::Value;
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataRef) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int>&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataCref) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int> const&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataXRef) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int>&&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataCXRef) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int> const&&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleUninitializedConstruct) {
  BasePeeker<TriviallyDestructible, int> obj{Uninitialized{}};
  ASSERT_EQ(ExpectedState::Uninitialized, obj.state());
  ASSERT_EQ(0, (static_cast<BasePeeker<TriviallyDestructible, int> const&&>(obj).data().uninitialized));
}

#ifdef DCR_SINCECPP14
static_assert(ExpectedState::Value == BasePeeker<TriviallyDestructible, int>{1, 2, 3}.state(), "lifetime test failure");

static_assert(1 == BasePeeker<TriviallyDestructible, int>{1, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<TriviallyDestructible, int>{1, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<TriviallyDestructible, int>{1, 2, 3}.data().value.c, "lifetime test failure");

static_assert(4 == BasePeeker<TriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<TriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<TriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.c, "lifetime test failure");

static_assert(ExpectedState::Error == BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.state(), "lifetime test failure");

static_assert(1 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.c, "lifetime test failure");

static_assert(4 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.c, "lifetime test failure");

static_assert(ExpectedState::Uninitialized == BasePeeker<TriviallyDestructible, int>{Uninitialized{}}.state(), "lifetime test failure");
static_assert(ExpectedState::Uninitialized == BasePeeker<int, TriviallyDestructible>{Uninitialized{}}.state(), "lifetime test failure");
static_assert(0 == BasePeeker<TriviallyDestructible, int>{Uninitialized{}}.data().uninitialized, "lifetime test failure");
static_assert(0 == BasePeeker<int, TriviallyDestructible>{Uninitialized{}}.data().uninitialized, "lifetime test failure");
#endif

namespace {
struct NonTriviallyDestructible {
  CDS_ATTR(constexpr(11)) NonTriviallyDestructible(int a, int b, int c) : a(a), b(b), c(c) {}
  CDS_ATTR(constexpr(11)) NonTriviallyDestructible(std::initializer_list<int> const& l, int b, int c) :
      a(static_cast<int>(l.size())), b(b), c(c) {}

  CDS_ATTR(constexpr(20)) ~NonTriviallyDestructible() {}

  int a;
  int b;
  int c;
};
} // namespace

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleArgsConstruct) {
  BasePeeker<NonTriviallyDestructible, int> obj(1, 2, 3);
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleIListArgsConstruct) {
  BasePeeker<NonTriviallyDestructible, int> obj({1, 2, 3, 4}, 2, 3);
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(4, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleErrorArgsConstruct) {
  BasePeeker<int, NonTriviallyDestructible> obj(Unexpect{}, 1, 2, 3);
  ASSERT_EQ(ExpectedState::Error, obj.state());
  ASSERT_EQ(1, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleErrorIListArgsConstruct) {
  BasePeeker<int, NonTriviallyDestructible> obj(Unexpect{}, {1, 2, 3, 4}, 2, 3);
  ASSERT_EQ(ExpectedState::Error, obj.state());
  ASSERT_EQ(4, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDestroyDisengages) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  obj.destroy();
  ASSERT_EQ(ExpectedState::Uninitialized, obj.state());
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleEngagedMutability) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  obj.state() = ExpectedState::Error;
  ASSERT_EQ(ExpectedState::Error, obj.state());
  obj.state() = ExpectedState::Value;
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleEngagedConst) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, asConst(obj).state());
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataRef) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int>&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataCref) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int> const&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataXRef) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int>&&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataCXRef) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, obj.state());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int> const&&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleUninitializedConstruct) {
  BasePeeker<NonTriviallyDestructible, int> obj{Uninitialized{}};
  ASSERT_EQ(ExpectedState::Uninitialized, obj.state());
  ASSERT_EQ(0, (static_cast<BasePeeker<NonTriviallyDestructible, int> const&&>(obj).data().uninitialized));
}

#ifdef DCR_SINCECPP20
static_assert(ExpectedState::Value == BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.state(), "lifetime test failure");

static_assert(1 == BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.data().value.c, "lifetime test failure");

static_assert(4 == BasePeeker<NonTriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<NonTriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<NonTriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.c, "lifetime test failure");

static_assert(ExpectedState::Error == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.state(), "lifetime test failure");

static_assert(1 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.c, "lifetime test failure");

static_assert(4 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.c, "lifetime test failure");

static_assert(0 == BasePeeker<NonTriviallyDestructible, int>{Uninitialized{}}.data().uninitialized, "lifetime test failure");
static_assert(0 == BasePeeker<int, NonTriviallyDestructible>{Uninitialized{}}.data().uninitialized, "lifetime test failure");

static_assert(ExpectedState::Uninitialized == BasePeeker<int, NonTriviallyDestructible>{Uninitialized{}}.state(), "lifetime test failure");
static_assert(ExpectedState::Uninitialized == BasePeeker<NonTriviallyDestructible, int>{Uninitialized{}}.state(), "lifetime test failure");
#endif
