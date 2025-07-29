// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/Expected>
#include <cds/Format>

namespace {
using cds::Expected;
using cds::ExpectedValueException;
using cds::Unexpected;
using cds::Unexpect;

using namespace cds::meta;
using namespace cds::impl;

// trivial + non trivial combos
struct Trivial {
  Trivial() = default;
  Trivial(Trivial const&) = default;
  Trivial(Trivial&&) = default;
  Trivial& operator=(Trivial const&) = default;
  Trivial& operator=(Trivial&&) = default;
  ~Trivial() = default;
};

struct NonTrivial {
  NonTrivial();
  NonTrivial(NonTrivial const&);
  NonTrivial(NonTrivial&&);
  NonTrivial& operator=(NonTrivial const&);
  NonTrivial& operator=(NonTrivial&&);
  ~NonTrivial();
};

struct Deleted {
  Deleted() = delete;
  Deleted(Deleted const&) = delete;
  Deleted(Deleted&&) = delete;
  Deleted& operator=(Deleted const&) = delete;
  Deleted& operator=(Deleted&&) = delete;
  ~Deleted() = delete;
};

// trivial + trivial
static_assert(IsTriviallyDestructible<Trivial>::value, "expected base type to be trivial");
static_assert(IsBaseOf<ExpectedDestructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyDestructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(IsBaseOf<ExpectedDestructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyDestructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsTriviallyDefaultConstructible<Trivial>::value, "expected base type to be trivial");
static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");

static_assert(IsTriviallyCopyConstructible<Trivial>::value, "expected base type to be trivial");
static_assert(IsBaseOf<ExpectedCopyConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyConstructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(IsBaseOf<ExpectedCopyConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyConstructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsTriviallyMoveConstructible<Trivial>::value, "expected base type to be trivial");
static_assert(IsBaseOf<ExpectedMoveConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveConstructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(IsBaseOf<ExpectedMoveConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveConstructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsTriviallyCopyAssignable<Trivial>::value, "expected base type to be trivial");
static_assert(IsBaseOf<ExpectedCopyAssignableBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyAssignable<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(IsBaseOf<ExpectedCopyAssignableBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyAssignable<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsTriviallyMoveAssignable<Trivial>::value, "expected base type to be trivial");
static_assert(IsBaseOf<ExpectedMoveAssignableBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveAssignable<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(IsBaseOf<ExpectedMoveAssignableBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveAssignable<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

// trivial + non-trivial
static_assert(IsTriviallyDestructible<Trivial>::value, "expected base type to be trivial");
static_assert(!IsTriviallyDestructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsDestructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsBaseOf<ExpectedDestructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyDestructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsDestructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsBaseOf<ExpectedDestructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyDestructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsDestructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsTriviallyDefaultConstructible<Trivial>::value, "expected base type to be trivial");
static_assert(!IsTriviallyDefaultConstructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsDefaultConstructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");

static_assert(IsTriviallyCopyConstructible<Trivial>::value, "expected base type to be trivial");
static_assert(!IsTriviallyCopyConstructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsCopyConstructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsBaseOf<ExpectedCopyConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedCopyConstructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyCopyConstructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyCopyConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsBaseOf<ExpectedCopyConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedCopyConstructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyCopyConstructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyCopyConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsTriviallyMoveConstructible<Trivial>::value, "expected base type to be trivial");
static_assert(!IsTriviallyMoveConstructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsMoveConstructible<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsBaseOf<ExpectedMoveConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedMoveConstructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyMoveConstructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyMoveConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsBaseOf<ExpectedMoveConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedMoveConstructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyMoveConstructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyMoveConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsTriviallyCopyAssignable<Trivial>::value, "expected base type to be trivial");
static_assert(!IsTriviallyCopyAssignable<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsCopyAssignable<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsBaseOf<ExpectedCopyAssignableBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedCopyAssignableBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyCopyAssignable<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyCopyAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsBaseOf<ExpectedCopyAssignableBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedCopyAssignableBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyCopyAssignable<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyCopyAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsTriviallyMoveAssignable<Trivial>::value, "expected base type to be trivial");
static_assert(!IsTriviallyMoveAssignable<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsMoveAssignable<NonTrivial>::value, "expected base type to be non-trivial");
static_assert(IsBaseOf<ExpectedMoveAssignableBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedMoveAssignableBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyMoveAssignable<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyMoveAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsBaseOf<ExpectedMoveAssignableBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsBaseOf<ExpectedMoveAssignableBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(IsTriviallyMoveAssignable<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");
static_assert(!IsTriviallyMoveAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
} // namespace
