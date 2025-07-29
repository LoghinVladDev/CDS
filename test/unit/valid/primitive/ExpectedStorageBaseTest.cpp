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

TEST(ExpectedStorageBaseTest, nonDestructibleInPlaceArgsConstruct) {
  Byte buffer[sizeof(ExpectedStorageBase<NonDestructible, int>)];
  auto& object = *new (buffer) ExpectedStorageBase<NonDestructible, int> {InPlace{}, 1, 2 ,3};

  ASSERT_EQ(1, object.value.a);
  ASSERT_EQ(2, object.value.b);
  ASSERT_EQ(3, object.value.c);
}

TEST(ExpectedStorageBaseTest, nonDestructibleInPlaceIListArgsConstruct) {
  Byte buffer[sizeof(ExpectedStorageBase<NonDestructible, int>)];
  auto& object = *new (buffer) ExpectedStorageBase<NonDestructible, int> {InPlace{}, {1, 2, 3, 4}, 2 ,3};

  ASSERT_EQ(4, object.value.a);
  ASSERT_EQ(2, object.value.b);
  ASSERT_EQ(3, object.value.c);
}

TEST(ExpectedStorageBaseTest, nonDestructibleUnexpectArgs) {
  Byte buffer[sizeof(ExpectedStorageBase<int, NonDestructible>)];
  auto& object = *new (buffer) ExpectedStorageBase<int, NonDestructible> {Unexpect{}, 1, 2 ,3};
  ASSERT_EQ(1, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, nonDestructibleUnexpectIListArgs) {
  Byte buffer[sizeof(ExpectedStorageBase<int, NonDestructible>)];
  auto& object = *new (buffer) ExpectedStorageBase<int, NonDestructible> {Unexpect{}, {1, 2, 3, 4}, 2 ,3};
  ASSERT_EQ(4, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

#ifdef DCR_SINCECPP20
namespace {
consteval auto constexpr20NonDestructibleEvalInPlaceArgs() {
  Allocator<ExpectedStorageBase<NonDestructible, int>> allocator;
  auto buffer = allocator.allocate(1);
  auto& object = *construct(buffer, InPlace{}, 1, 2 ,3);

  auto const result = 1 == object.value.a
      && 2 == object.value.b
      && 3 == object.value.c;

  allocator.deallocate(buffer, 1);
  return result;
}

consteval auto constexpr20NonDestructibleErrorEvalInPlaceArgs() {
  Allocator<ExpectedStorageBase<int, NonDestructible>> allocator;
  auto buffer = allocator.allocate(1);
  auto& object = *construct(buffer, Unexpect{}, 1, 2 ,3);

  auto const result = 1 == object.error.a
      && 2 == object.error.b
      && 3 == object.error.c;

  allocator.deallocate(buffer, 1);
  return result;
}

consteval auto constexpr20NonDestructibleEvalInPlaceIListArgs() {
  Allocator<ExpectedStorageBase<NonDestructible, int>> allocator;
  auto buffer = allocator.allocate(1);
  std::initializer_list<int> args = {1, 2, 3, 4};
  auto &object = *construct(buffer, InPlace{}, args, 2, 3);

  auto const result = 4 == object.value.a
                      && 2 == object.value.b
                      && 3 == object.value.c;

  allocator.deallocate(buffer, 1);
  return result;
}

consteval auto constexpr20NonDestructibleErrorEvalInPlaceIListArgs() {
  Allocator<ExpectedStorageBase<int, NonDestructible>> allocator;
  auto buffer = allocator.allocate(1);
  std::initializer_list<int> args = {1, 2, 3, 4};
  auto& object = *construct(buffer, Unexpect{}, args, 2, 3);

  auto const result = 4 == object.error.a
                      && 2 == object.error.b
                      && 3 == object.error.c;

  allocator.deallocate(buffer, 1);
  return result;
}
} // namespace

static_assert(constexpr20NonDestructibleEvalInPlaceArgs());
static_assert(constexpr20NonDestructibleErrorEvalInPlaceArgs());
static_assert(constexpr20NonDestructibleEvalInPlaceIListArgs());
static_assert(constexpr20NonDestructibleErrorEvalInPlaceIListArgs());
#endif

TEST(ExpectedStorageBaseTest, voidTrivialDestructibleInPlaceConstruct) {
  ExpectedStorageBase<void, TriviallyDestructible> object{InPlace{}};
  ASSERT_EQ(0, object.uninitialized);
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

#ifdef DCR_SINCECPP11
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{InPlace{}}.uninitialized == 0, "lifetime test failed");

static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, TriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.c == 3, "lifetime test failed");
#endif

TEST(ExpectedStorageBaseTest, voidNonTrivialllyDestructibleInPlaceArgsConstruct) {
  ExpectedStorageBase<void, NonTriviallyDestructible> object{InPlace{}};
  ASSERT_EQ(0, object.uninitialized);
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

#ifdef DCR_SINCECPP20
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{InPlace{}}.uninitialized == 0, "lifetime test failed");

static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.a == 1, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, 1, 2, 3}.error.c == 3, "lifetime test failed");

static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.a == 4, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.b == 2, "lifetime test failed");
static_assert(ExpectedStorageBase<void, NonTriviallyDestructible>{Unexpect{}, {1, 2, 3, 4}, 2, 3}.error.c == 3, "lifetime test failed");
#endif

TEST(ExpectedStorageBaseTest, voidNonDestructibleInPlaceArgsConstruct) {
  Byte buffer[sizeof(ExpectedStorageBase<void, NonDestructible>)];
  auto& object = *new (buffer) ExpectedStorageBase<void, NonDestructible> {InPlace{}};

  ASSERT_EQ(0, object.uninitialized);
}

TEST(ExpectedStorageBaseTest, voidNonDestructibleUnexpectArgs) {
  Byte buffer[sizeof(ExpectedStorageBase<void, NonDestructible>)];
  auto& object = *new (buffer) ExpectedStorageBase<void, NonDestructible> {Unexpect{}, 1, 2 ,3};
  ASSERT_EQ(1, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

TEST(ExpectedStorageBaseTest, voidNonDestructibleUnexpectIListArgs) {
  Byte buffer[sizeof(ExpectedStorageBase<void, NonDestructible>)];
  auto& object = *new (buffer) ExpectedStorageBase<void, NonDestructible> {Unexpect{}, {1, 2, 3, 4}, 2 ,3};
  ASSERT_EQ(4, object.error.a);
  ASSERT_EQ(2, object.error.b);
  ASSERT_EQ(3, object.error.c);
}

#ifdef DCR_SINCECPP20
namespace {
consteval auto constexpr20VoidNonDestructibleEvalInPlaceArgs() {
  Allocator<ExpectedStorageBase<void, NonDestructible>> allocator;
  auto buffer = allocator.allocate(1);
  auto& object = *construct(buffer, InPlace{});

  auto const result = 0 == object.uninitialized;

  allocator.deallocate(buffer, 1);
  return result;
}

consteval auto constexpr20VoidNonDestructibleErrorEvalInPlaceArgs() {
  Allocator<ExpectedStorageBase<void, NonDestructible>> allocator;
  auto buffer = allocator.allocate(1);
  auto& object = *construct(buffer, Unexpect{}, 1, 2 ,3);

  auto const result = 1 == object.error.a
      && 2 == object.error.b
      && 3 == object.error.c;

  allocator.deallocate(buffer, 1);
  return result;
}

consteval auto constexpr20VoidNonDestructibleErrorEvalInPlaceIListArgs() {
  Allocator<ExpectedStorageBase<void, NonDestructible>> allocator;
  auto buffer = allocator.allocate(1);
  std::initializer_list<int> args = {1, 2, 3, 4};
  auto& object = *construct(buffer, Unexpect{}, args, 2 ,3);

  auto const result = 4 == object.error.a
                      && 2 == object.error.b
                      && 3 == object.error.c;

  allocator.deallocate(buffer, 1);
  return result;
}
} // namespace

static_assert(constexpr20VoidNonDestructibleEvalInPlaceArgs());
static_assert(constexpr20VoidNonDestructibleErrorEvalInPlaceArgs());
static_assert(constexpr20VoidNonDestructibleErrorEvalInPlaceIListArgs());
#endif
