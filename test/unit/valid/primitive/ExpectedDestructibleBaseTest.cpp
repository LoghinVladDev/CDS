// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/Expected>
#include <cds/Format>

#include <cds/memory/Allocator>

namespace {
using namespace cds;
using namespace cds::meta;
using namespace cds::impl;

template <typename T, typename E> struct BasePeeker : ExpectedDestructibleBase<T, E> {
  using Base = ExpectedDestructibleBase<T, E>;
  using Base::Base;
  using Base::engaged;
  using Base::data;
  using Base::destroy;
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
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleIListArgsConstruct) {
  BasePeeker<TriviallyDestructible, int> obj({1, 2, 3, 4}, 2, 3);
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(4, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleErrorArgsConstruct) {
  BasePeeker<int, TriviallyDestructible> obj(Unexpect{}, 1, 2, 3);
  ASSERT_FALSE(obj.engaged());
  ASSERT_EQ(1, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleErrorIListArgsConstruct) {
  BasePeeker<int, TriviallyDestructible> obj(Unexpect{}, {1, 2, 3, 4}, 2, 3);
  ASSERT_FALSE(obj.engaged());
  ASSERT_EQ(4, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDestroyDisengages) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  obj.destroy();
  ASSERT_FALSE(obj.engaged());
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleEngagedConst) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(asConst(obj).engaged());
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleEngagedMutability) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  obj.engaged() = false;
  ASSERT_FALSE(obj.engaged());
  obj.engaged() = true;
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataRef) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int>&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataCref) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int> const&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataXRef) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int>&&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, triviallyDestructibleDataCXRef) {
  BasePeeker<TriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<TriviallyDestructible, int> const&&>(obj).data().value.a));
}

#ifdef DCR_SINCECPP11
static_assert(BasePeeker<TriviallyDestructible, int>{1, 2, 3}.engaged(), "lifetime test failure");

static_assert(1 == BasePeeker<TriviallyDestructible, int>{1, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<TriviallyDestructible, int>{1, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<TriviallyDestructible, int>{1, 2, 3}.data().value.c, "lifetime test failure");

static_assert(4 == BasePeeker<TriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<TriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<TriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.c, "lifetime test failure");

static_assert(!BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.engaged(), "lifetime test failure");

static_assert(1 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.c, "lifetime test failure");

static_assert(4 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.c, "lifetime test failure");
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
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleIListArgsConstruct) {
  BasePeeker<NonTriviallyDestructible, int> obj({1, 2, 3, 4}, 2, 3);
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(4, obj.data().value.a);
  ASSERT_EQ(2, obj.data().value.b);
  ASSERT_EQ(3, obj.data().value.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleErrorArgsConstruct) {
  BasePeeker<int, NonTriviallyDestructible> obj(Unexpect{}, 1, 2, 3);
  ASSERT_FALSE(obj.engaged());
  ASSERT_EQ(1, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleErrorIListArgsConstruct) {
  BasePeeker<int, NonTriviallyDestructible> obj(Unexpect{}, {1, 2, 3, 4}, 2, 3);
  ASSERT_FALSE(obj.engaged());
  ASSERT_EQ(4, obj.data().error.a);
  ASSERT_EQ(2, obj.data().error.b);
  ASSERT_EQ(3, obj.data().error.c);
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDestroyDisengages) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  obj.destroy();
  ASSERT_FALSE(obj.engaged());
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleEngagedMutability) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  obj.engaged() = false;
  ASSERT_FALSE(obj.engaged());
  obj.engaged() = true;
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleEngagedConst) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(asConst(obj).engaged());
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataRef) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int>&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataCref) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int> const&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataXRef) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int>&&>(obj).data().value.a));
}

TEST(ExpectedDestructibleBaseTest, nonTriviallyDestructibleDataCXRef) {
  BasePeeker<NonTriviallyDestructible, int> obj{1, 2, 3};
  ASSERT_TRUE(obj.engaged());
  ASSERT_EQ(1, (static_cast<BasePeeker<NonTriviallyDestructible, int> const&&>(obj).data().value.a));
}

#ifdef DCR_SINCECPP20
static_assert(BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.engaged(), "lifetime test failure");

static_assert(1 == BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<NonTriviallyDestructible, int>{1, 2, 3}.data().value.c, "lifetime test failure");

static_assert(4 == BasePeeker<NonTriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.a, "lifetime test failure");
static_assert(2 == BasePeeker<NonTriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.b, "lifetime test failure");
static_assert(3 == BasePeeker<NonTriviallyDestructible, int>{{1, 2, 3, 4}, 2, 3}.data().value.c, "lifetime test failure");

static_assert(!BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.engaged(), "lifetime test failure");

static_assert(1 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.data().error.c, "lifetime test failure");

static_assert(4 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.a, "lifetime test failure");
static_assert(2 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.b, "lifetime test failure");
static_assert(3 == BasePeeker<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.data().error.c, "lifetime test failure");
#endif

namespace {
struct NonDestructible {
  CDS_ATTR(constexpr(11)) NonDestructible(int a, int b, int c) : a(a), b(b), c(c) {}
  CDS_ATTR(constexpr(11)) NonDestructible(std::initializer_list<int> const& l, int b, int c) :
      a(static_cast<int>(l.size())), b(b), c(c) {}

  ~NonDestructible() = delete;

  int a;
  int b;
  int c;
};
} // namespace

//TEST(ExpectedDestructibleBaseTest, nonDestructibleArgsConstruct) {
//  Byte buffer[sizeof(BasePeeker<NonDestructible, int>)];
//  auto& obj = *new (buffer) BasePeeker<NonDestructible, int>{1, 2, 3};
//  ASSERT_TRUE(obj.engaged());
//  ASSERT_EQ(1, obj.data().value.a);
//  ASSERT_EQ(2, obj.data().value.b);
//  ASSERT_EQ(3, obj.data().value.c);
//}

//TEST(ExpectedDestructibleBaseTest, nonDestructibleIListArgsConstruct) {
//  BasePeeker<NonDestructible, int> obj({1, 2, 3, 4}, 2, 3);
//  ASSERT_TRUE(obj.engaged());
//  ASSERT_EQ(4, obj.data().value.a);
//  ASSERT_EQ(2, obj.data().value.b);
//  ASSERT_EQ(3, obj.data().value.c);
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleErrorArgsConstruct) {
//  BasePeeker<int, NonDestructible> obj(Unexpect{}, 1, 2, 3);
//  ASSERT_FALSE(obj.engaged());
//  ASSERT_EQ(1, obj.data().error.a);
//  ASSERT_EQ(2, obj.data().error.b);
//  ASSERT_EQ(3, obj.data().error.c);
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleErrorIListArgsConstruct) {
//  BasePeeker<int, NonDestructible> obj(Unexpect{}, {1, 2, 3, 4}, 2, 3);
//  ASSERT_FALSE(obj.engaged());
//  ASSERT_EQ(4, obj.data().error.a);
//  ASSERT_EQ(2, obj.data().error.b);
//  ASSERT_EQ(3, obj.data().error.c);
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleDestroyDisengages) {
//  BasePeeker<NonDestructible, int> obj{1, 2, 3};
//  ASSERT_TRUE(obj.engaged());
//  obj.destroy();
//  ASSERT_FALSE(obj.engaged());
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleEngagedMutability) {
//  BasePeeker<NonDestructible, int> obj{1, 2, 3};
//  ASSERT_TRUE(obj.engaged());
//  obj.engaged() = false;
//  ASSERT_FALSE(obj.engaged());
//  obj.engaged() = true;
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleEngagedConst) {
//  BasePeeker<NonDestructible, int> obj{1, 2, 3};
//  ASSERT_TRUE(asConst(obj).engaged());
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleDataRef) {
//  BasePeeker<NonDestructible, int> obj{1, 2, 3};
//  ASSERT_TRUE(obj.engaged());
//  ASSERT_EQ(1, (static_cast<BasePeeker<NonDestructible, int>&>(obj).data().value.a));
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleDataCref) {
//  BasePeeker<NonDestructible, int> obj{1, 2, 3};
//  ASSERT_TRUE(obj.engaged());
//  ASSERT_EQ(1, (static_cast<BasePeeker<NonDestructible, int> const&>(obj).data().value.a));
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleDataXRef) {
//  BasePeeker<NonDestructible, int> obj{1, 2, 3};
//  ASSERT_TRUE(obj.engaged());
//  ASSERT_EQ(1, (static_cast<BasePeeker<NonDestructible, int>&&>(obj).data().value.a));
//}
//
//TEST(ExpectedDestructibleBaseTest, nonDestructibleDataCXRef) {
//  BasePeeker<NonDestructible, int> obj{1, 2, 3};
//  ASSERT_TRUE(obj.engaged());
//  ASSERT_EQ(1, (static_cast<BasePeeker<NonDestructible, int> const&&>(obj).data().value.a));
//}
