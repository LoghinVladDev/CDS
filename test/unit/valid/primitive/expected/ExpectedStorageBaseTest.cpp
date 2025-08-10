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

TEST(ExpectedStorageBaseTest, trivialDestructibleInPlaceArgsConstruct) {
  ExpectedStorageBase<TriviallyDestructible, int> object{InPlace{}, 1, 2, 3};
  ASSERT_EQ(1, object.value.a);
  ASSERT_EQ(2, object.value.b);
  ASSERT_EQ(3, object.value.c);
}

TEST(ExpectedStorageBaseTest, trivialDestructibleInPlaceIListArgsConstruct) {
  ExpectedStorageBase<TriviallyDestructible, int> object{InPlace{}, {1, 2, 3, 4}, 2, 3};
  ASSERT_EQ(4, object.value.a);
  ASSERT_EQ(2, object.value.b);
  ASSERT_EQ(3, object.value.c);
}

TEST(ExpectedStorageBaseTest, trivialDestructibleUnexpectArgs) {
  ExpectedStorageBase<int, TriviallyDestructible> object{Unexpect{}, 1, 2, 3};
  ASSERT_EQ(1, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, trivialDestructibleUnexpectIListArgs) {
  ExpectedStorageBase<int, TriviallyDestructible> object{Unexpect{}, {1, 2, 3, 4}, 2, 3};
  ASSERT_EQ(4, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, trivialDestructibleUninitialized) {
  ExpectedStorageBase<TriviallyDestructible, int> object{Uninitialized{}};
  ASSERT_EQ(0, object.uninitialized);
}

#ifdef DCR_SINCECPP11
static_assert(ExpectedStorageBase<TriviallyDestructible, int>{InPlace{}, 1, 2, 3}.value.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<TriviallyDestructible, int>{InPlace{}, 1, 2, 3}.value.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<TriviallyDestructible, int>{InPlace{}, 1, 2, 3}.value.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<TriviallyDestructible, int>{InPlace{}, {1, 2, 3, 4}, 2, 3}.value.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<TriviallyDestructible, int>{InPlace{}, {1, 2, 3, 4}, 2, 3}.value.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<TriviallyDestructible, int>{InPlace{}, {1, 2, 3, 4}, 2, 3}.value.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<int, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<int, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<TriviallyDestructible, int>{Uninitialized{}}.uninitialized == 0, "lifetime test failed");
static_assert(ExpectedStorageBase<int, TriviallyDestructible>{Uninitialized{}}.uninitialized == 0, "lifetime test failed");
#endif

namespace {
struct NonTriviallyDestructible {
  CDS_ATTR(constexpr(11)) NonTriviallyDestructible(int a, int b, int c) : a(a), b(b), c(c) {}
  CDS_ATTR(constexpr(11)) NonTriviallyDestructible(std::initializer_list<int> const& l, int b, int c) :\
      a(static_cast<int>(l.size())), b(b), c(c) {}

  CDS_ATTR(constexpr(20)) ~NonTriviallyDestructible() {}

  int a;
  int b;
  int c;
};
} // namespace

TEST(ExpectedStorageBaseTest, nonTrivialllyDestructibleInPlaceArgsConstruct) {
  ExpectedStorageBase<NonTriviallyDestructible, int> object{InPlace{}, 1, 2, 3};
  ASSERT_EQ(1, object.value.a);
  ASSERT_EQ(2, object.value.b);
  ASSERT_EQ(3, object.value.c);
}

TEST(ExpectedStorageBaseTest, nonTrivialllyDestructibleInPlaceIListArgsConstruct) {
  ExpectedStorageBase<NonTriviallyDestructible, int> object{InPlace{}, {1, 2, 3, 4}, 2, 3};
  ASSERT_EQ(4, object.value.a);
  ASSERT_EQ(2, object.value.b);
  ASSERT_EQ(3, object.value.c);
}

TEST(ExpectedStorageBaseTest, nonTrivialllyDestructibleUnexpectArgs) {
  ExpectedStorageBase<int, NonTriviallyDestructible> object{Unexpect{}, 1, 2, 3};
  ASSERT_EQ(1, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, nonTrivialllyDestructibleUnexpectIListArgs) {
  ExpectedStorageBase<int, NonTriviallyDestructible> object{Unexpect{}, {1, 2, 3, 4}, 2, 3};
  ASSERT_EQ(4, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, nonTrivialllyDestructibleUninitialized) {
  ExpectedStorageBase<NonTriviallyDestructible, int> object{Uninitialized{}};
  ASSERT_EQ(0, object.uninitialized);
}

#ifdef DCR_SINCECPP20
static_assert(ExpectedStorageBase<NonTriviallyDestructible, int>{InPlace{}, 1, 2, 3}.value.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<NonTriviallyDestructible, int>{InPlace{}, 1, 2, 3}.value.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<NonTriviallyDestructible, int>{InPlace{}, 1, 2, 3}.value.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<NonTriviallyDestructible, int>{InPlace{}, {1, 2, 3, 4}, 2, 3}.value.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<NonTriviallyDestructible, int>{InPlace{}, {1, 2, 3, 4}, 2, 3}.value.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<NonTriviallyDestructible, int>{InPlace{}, {1, 2, 3, 4}, 2, 3}.value.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<int, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<int, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<NonTriviallyDestructible, int>{Uninitialized{}}.uninitialized == 0, "lifetime test failed");
static_assert(ExpectedStorageBase<int, NonTriviallyDestructible>{Uninitialized{}}.uninitialized == 0, "lifetime test failed");
#endif

TEST(ExpectedStorageBaseTest, voidTrivialDestructibleInPlaceConstruct) {
  ExpectedStorageBase<void, TriviallyDestructible> object{InPlace{}};
  ASSERT_EQ(0, object.valueless);
}

TEST(ExpectedStorageBaseTest, voidTrivialDestructibleUnexpectArgs) {
  ExpectedStorageBase<void, TriviallyDestructible> object{Unexpect{}, 1, 2, 3};
  ASSERT_EQ(1, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, voidTrivialDestructibleUnexpectIListArgs) {
  ExpectedStorageBase<void, TriviallyDestructible> object{Unexpect{}, {1, 2, 3, 4}, 2, 3};
  ASSERT_EQ(4, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, voidTrivialDestructibleUninitialized) {
  ExpectedStorageBase<void, TriviallyDestructible> object{Uninitialized{}};
  ASSERT_EQ(0, object.uninitialized);
}

#ifdef DCR_SINCECPP11
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{InPlace{}}.valueless == 0, "lifetime test failed");

static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Uninitialized{}}.uninitialized == 0, "lifetime test failed");
#endif

TEST(ExpectedStorageBaseTest, voidNonTrivialllyDestructibleInPlaceArgsConstruct) {
  ExpectedStorageBase<void, NonTriviallyDestructible> object{InPlace{}};
  ASSERT_EQ(0, object.valueless);
}

TEST(ExpectedStorageBaseTest, voidNonTrivialllyDestructibleUnexpectArgs) {
  ExpectedStorageBase<void, NonTriviallyDestructible> object{Unexpect{}, 1, 2, 3};
  ASSERT_EQ(1, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, voidNonTrivialllyDestructibleUnexpectIListArgs) {
  ExpectedStorageBase<void, NonTriviallyDestructible> object{Unexpect{}, {1, 2, 3, 4}, 2, 3};
  ASSERT_EQ(4, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, voidNonTrivialllyDestructibleUninitialized)  {
  ExpectedStorageBase<void, NonTriviallyDestructible> object{Uninitialized{}};
  ASSERT_EQ(0, object.uninitialized);
}

#ifdef DCR_SINCECPP20
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{InPlace{}}.valueless == 0, "lifetime test failed");

static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Uninitialized{}}.uninitialized == 0, "lifetime test failed");
#endif
