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

template <typename T, typename E> struct BasePeeker : ExpectedConstructionBase<T, E> {
  using Base = ExpectedConstructionBase<T, E>;
  using Base::Base;
  using Base::data;
  using Base::destroy;
  using Base::state;
  using Base::operator=;
  
  using Base::assignFrom;
  using Base::constructFrom;

  CDS_ATTR(2(explicit, constexpr(11))) BasePeeker(Uninitialized) noexcept : Base{Uninitialized{}} {}
};

struct X {
  int a; int b; int c;
  X(X const&) = default;
  X(X&&) = default;
  CDS_ATTR(constexpr(11)) X(int a, int b, int c) : a(a), b(b), c(c) {}
  CDS_ATTR(constexpr(11)) X(std::initializer_list<int> const& list, int b, int c) : a(static_cast<int>(list.size())), b(b), c(c) {}
  CDS_ATTR(constexpr(14)) X& operator=(X const& obj) noexcept = default;
  CDS_ATTR(constexpr(14)) X& operator=(X&& obj) noexcept = default;
};
} // namespace

TEST(ExpectedConstructionBaseTest, emplaceArgs) {
  BasePeeker<X, int> value{Unexpect{}, 0};
  ASSERT_EQ(ExpectedState::Error, value.state());
  auto& rval = value.emplace(1, 2, 3);
  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(&rval, &value.data().value);
  ASSERT_EQ(1, value.data().value.a);
  ASSERT_EQ(2, value.data().value.b);
  ASSERT_EQ(3, value.data().value.c);
}

TEST(ExpectedConstructionBaseTest, emplaceIListArgs) {
  BasePeeker<X, int> value{Unexpect{}, 0};
  ASSERT_EQ(ExpectedState::Error, value.state());
  auto& rval = value.emplace({1, 2, 3, 4}, 2, 3);
  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(&rval, &value.data().value);
  ASSERT_EQ(4, value.data().value.a);
  ASSERT_EQ(2, value.data().value.b);
  ASSERT_EQ(3, value.data().value.c);
}

#ifdef DCR_SINCECPP20
namespace {
constexpr bool emplaceArgsConstexpr20() {
  BasePeeker<X, int> value{Unexpect{}, 0};
  auto engaged0 = ExpectedState::Error == value.state();
  auto& rval = value.emplace(1, 2, 3);
  auto engaged1 = ExpectedState::Value == value.state();
  auto id0 = &rval == &value.data().value;
  auto eq1 = 1 == value.data().value.a;
  auto eq2 = 2 == value.data().value.b;
  auto eq3 = 3 == value.data().value.c;
  return engaged0 && engaged1 && id0 && eq1 && eq2 && eq3;
}

constexpr bool emplaceIListArgsConstexpr20() {
  BasePeeker<X, int> value{Unexpect{}, 0};
  auto engaged0 = ExpectedState::Error == value.state();
  auto& rval = value.emplace({1, 2, 3, 4}, 2, 3);
  auto engaged1 = ExpectedState::Value == value.state();
  auto id0 = &rval == &value.data().value;
  auto eq1 = 4 == value.data().value.a;
  auto eq2 = 2 == value.data().value.b;
  auto eq3 = 3 == value.data().value.c;
  return engaged0 && engaged1 && id0 && eq1 && eq2 && eq3;
}

static_assert(emplaceArgsConstexpr20(), "failed emplace constexpr test");
static_assert(emplaceIListArgsConstexpr20(), "failed emplace constexpr test");
} // namespace
#endif

TEST(ExpectedConstructionBaseTest, assignUnengaged) {
  BasePeeker<X, int> value{Unexpect{}, 0};
  ASSERT_EQ(ExpectedState::Error, value.state());
  value = X{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(1, value.data().value.a);
  ASSERT_EQ(2, value.data().value.b);
  ASSERT_EQ(3, value.data().value.c);
}

TEST(ExpectedConstructionBaseTest, assignEngaged) {
  BasePeeker<X, int> value{2, 4, 6};
  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(2, value.data().value.a);
  ASSERT_EQ(4, value.data().value.b);
  ASSERT_EQ(6, value.data().value.c);
  value = X{1, 2, 3};
  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(1, value.data().value.a);
  ASSERT_EQ(2, value.data().value.b);
  ASSERT_EQ(3, value.data().value.c);
}

#ifdef DCR_SINCECPP20
namespace {
constexpr bool assignUnengagedConstexpr20() {
  BasePeeker<X, int> value{Unexpect{}, 0};
  auto s0 = ExpectedState::Error == value.state();
  value = X{1, 2, 3};
  auto s1 = ExpectedState::Value == value.state();
  auto s2 = 1 == value.data().value.a;
  auto s3 = 2 == value.data().value.b;
  auto s4 = 3 == value.data().value.c;
  return s0 && s1 && s2 && s3 && s4;
}

constexpr bool assignEngagedConstexpr20() {
  BasePeeker<X, int> value{2, 4, 6};
  auto s0 = ExpectedState::Value == value.state();
  auto s5 = 2 == value.data().value.a;
  auto s6 = 4 == value.data().value.b;
  auto s7 = 6 == value.data().value.c;
  value = X{1, 2, 3};
  auto s1 = ExpectedState::Value == value.state();
  auto s2 = 1 == value.data().value.a;
  auto s3 = 2 == value.data().value.b;
  auto s4 = 3 == value.data().value.c;
  return s0 && s1 && s2 && s3 && s4 && s5 && s6 && s7;
}

static_assert(assignUnengagedConstexpr20(), "failed emplace constexpr test");
static_assert(assignEngagedConstexpr20(), "failed emplace constexpr test");
} // namespace
#endif

namespace {
struct Tracker {
  int& copies; int& moves; int& destructions;
  CDS_ATTR(constexpr(11)) Tracker(int& copies, int& moves, int& destructions) : copies{copies}, moves{moves}, destructions{destructions} {}
  CDS_ATTR(constexpr(14)) Tracker(Tracker const& obj) : copies{obj.copies}, moves{obj.moves}, destructions{obj.destructions} {
    ++copies;
  }

  CDS_ATTR(constexpr(14)) Tracker(Tracker&& obj) noexcept : copies{obj.copies}, moves{obj.moves}, destructions{obj.destructions} {
    ++moves;
  }

  CDS_ATTR(constexpr(14)) Tracker& operator=(Tracker const&) {
    ++copies;
    return *this;
  }

  CDS_ATTR(constexpr(14)) Tracker& operator=(Tracker&& obj) noexcept {
    ++moves;
    return *this;
  }

  ~Tracker() noexcept {
    ++destructions;
  }
};
} // namespace

TEST(ExpectedConstructionBaseTest, constructValueFromCopy) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, int> value{Unexpect{}, 0};
  BasePeeker<Tracker, int> engagedToCopy{copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Value, engagedToCopy.state());
  value.constructFrom(asConst(engagedToCopy));

  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Value, value.state());
}

TEST(ExpectedConstructionBaseTest, constructValueFromMove) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, int> value{Unexpect{}, 0};
  BasePeeker<Tracker, int> engagedToMove{copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Value, engagedToMove.state());
  value.constructFrom(mv(engagedToMove));

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore + 1, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Value, value.state());
}

TEST(ExpectedConstructionBaseTest, constructErrorFromCopy) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<int, Tracker> value{0};
  BasePeeker<int, Tracker> errorToCopy{Unexpect{}, copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(ExpectedState::Error, errorToCopy.state());
  value.constructFrom(asConst(errorToCopy));

  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Error, value.state());
}

TEST(ExpectedConstructionBaseTest, constructErrorFromMove) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<int, Tracker> value{0};
  BasePeeker<int, Tracker> errorToMove{Unexpect{}, copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(ExpectedState::Error, errorToMove.state());
  value.constructFrom(mv(errorToMove));

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore + 1, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Error, value.state());
}

TEST(ExpectedConstructionBaseTest, assignValueCopyValue) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, int> value{copies, moves, destructions};
  BasePeeker<Tracker, int> toCopy{copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(ExpectedState::Value, toCopy.state());
  value.assignFrom(toCopy);

  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Value, value.state());
}

TEST(ExpectedConstructionBaseTest, assignValueCopyError) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, Tracker> value{copies, moves, destructions};
  BasePeeker<Tracker, Tracker> toCopy{Unexpect{}, copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(ExpectedState::Error, toCopy.state());
  value.assignFrom(toCopy);

  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore + 1, destructions);
  ASSERT_EQ(ExpectedState::Error, value.state());
}

TEST(ExpectedConstructionBaseTest, assignErrorCopyValue) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, Tracker> value{Unexpect{}, copies, moves, destructions};
  BasePeeker<Tracker, Tracker> toCopy{copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Value, toCopy.state());
  value.assignFrom(toCopy);

  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore + 1, destructions);
  ASSERT_EQ(ExpectedState::Value, value.state());
}

TEST(ExpectedConstructionBaseTest, assignErrorCopyError) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, Tracker> value{Unexpect{}, copies, moves, destructions};
  BasePeeker<Tracker, Tracker> toCopy{Unexpect{}, copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Error, toCopy.state());
  value.assignFrom(toCopy);

  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Error, value.state());
}

TEST(ExpectedConstructionBaseTest, assignValueMoveValue) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, int> value{copies, moves, destructions};
  BasePeeker<Tracker, int> toMove{copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(ExpectedState::Value, toMove.state());
  value.assignFrom(mv(toMove));

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore + 1, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Value, value.state());
}

TEST(ExpectedConstructionBaseTest, assignValueMoveError) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, Tracker> value{copies, moves, destructions};
  BasePeeker<Tracker, Tracker> toMove{Unexpect{}, copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(ExpectedState::Error, toMove.state());
  value.assignFrom(mv(toMove));

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore + 1, moves);
  ASSERT_EQ(destructionsBefore + 1, destructions);
  ASSERT_EQ(ExpectedState::Error, value.state());
}

TEST(ExpectedConstructionBaseTest, assignErrorMoveValue) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, Tracker> value{Unexpect{}, copies, moves, destructions};
  BasePeeker<Tracker, Tracker> toMove{copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Value, toMove.state());
  value.assignFrom(mv(toMove));

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore + 1, moves);
  ASSERT_EQ(destructionsBefore + 1, destructions);
  ASSERT_EQ(ExpectedState::Value, value.state());
}

TEST(ExpectedConstructionBaseTest, assignErrorMoveError) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<Tracker, Tracker> value{Unexpect{}, copies, moves, destructions};
  BasePeeker<Tracker, Tracker> toMove{Unexpect{}, copies, moves, destructions};

  auto copiesBefore = copies;
  auto movesBefore = moves;
  auto destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Error, toMove.state());
  value.assignFrom(mv(toMove));

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore + 1, moves);
  ASSERT_EQ(destructionsBefore, destructions);
  ASSERT_EQ(ExpectedState::Error, value.state());
}

TEST(ExpectedConstructionBaseTest, voidEmplace) {
  BasePeeker<void, int> value{Unexpect{}, 0};
  ASSERT_EQ(value.state(), ExpectedState::Error);
  value.emplace();
  ASSERT_EQ(value.state(), ExpectedState::Value);
}

TEST(ExpectedConstructionBaseTest, voidCopyConstructFromValue) {
  BasePeeker<void, int> toCopy{};
  BasePeeker<void, int> value{Uninitialized{}};

  ASSERT_EQ(toCopy.state(), ExpectedState::Value);
  ASSERT_EQ(value.state(), ExpectedState::Uninitialized);
  value.constructFrom(toCopy);
  ASSERT_EQ(value.state(), ExpectedState::Value);
}

TEST(ExpectedConstructionBaseTest, voidCopyConstructFromError) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<void, Tracker> toCopy{Unexpect{}, copies, moves, destructions};
  BasePeeker<void, Tracker> value{Uninitialized{}};

  auto const copiesBefore = copies;
  auto const movesBefore = moves;
  auto const destructionsBefore = destructions;

  ASSERT_EQ(toCopy.state(), ExpectedState::Error);
  ASSERT_EQ(value.state(), ExpectedState::Uninitialized);
  value.constructFrom(toCopy);
  ASSERT_EQ(value.state(), ExpectedState::Error);
  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore, destructions);
}

TEST(ExpectedConstructionBaseTest, voidValueAssignCopyValue) {
  BasePeeker<void, int> value{};
  BasePeeker<void, int> toCopy{};

  ASSERT_EQ(ExpectedState::Value, value.state());
  ASSERT_EQ(ExpectedState::Value, toCopy.state());
  value.assignFrom(toCopy);
  ASSERT_EQ(ExpectedState::Value, value.state());
}

TEST(ExpectedConstructionBaseTest, voidErrorAssignCopyError) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<void, Tracker> value{Unexpect{}, copies, moves, destructions};
  BasePeeker<void, Tracker> toCopy{Unexpect{}, copies, moves, destructions};

  auto const copiesBefore = copies;
  auto const movesBefore = moves;
  auto const destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Error, toCopy.state());
  value.assignFrom(toCopy);
  ASSERT_EQ(ExpectedState::Error, value.state());

  ASSERT_EQ(copiesBefore + 1, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore, destructions);
}

TEST(ExpectedConstructionBaseTest, voidErrorAssignMoveError) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<void, Tracker> value{Unexpect{}, copies, moves, destructions};
  BasePeeker<void, Tracker> toMove{Unexpect{}, copies, moves, destructions};

  auto const copiesBefore = copies;
  auto const movesBefore = moves;
  auto const destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Error, toMove.state());
  value.assignFrom(mv(toMove));
  ASSERT_EQ(ExpectedState::Error, value.state());

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore + 1, moves);
  ASSERT_EQ(destructionsBefore, destructions);
}

TEST(ExpectedConstructionBaseTest, voidErrorAssignValue) {
  int copies = 0;
  int moves = 0;
  int destructions = 0;

  BasePeeker<void, Tracker> value{Unexpect{}, copies, moves, destructions};
  BasePeeker<void, Tracker> toCopy{};

  auto const copiesBefore = copies;
  auto const movesBefore = moves;
  auto const destructionsBefore = destructions;

  ASSERT_EQ(ExpectedState::Error, value.state());
  ASSERT_EQ(ExpectedState::Value, toCopy.state());
  value.assignFrom(mv(toCopy));
  ASSERT_EQ(ExpectedState::Value, value.state());

  ASSERT_EQ(copiesBefore, copies);
  ASSERT_EQ(movesBefore, moves);
  ASSERT_EQ(destructionsBefore + 1, destructions);
}
