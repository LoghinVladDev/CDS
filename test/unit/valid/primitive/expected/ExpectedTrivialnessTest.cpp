// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include "cds/Expected"
#include "cds/Format"

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

static_assert(IsTriviallyDefaultConstructible<Trivial>::value, "expected trivial base");
static_assert(IsTriviallyCopyConstructible<Trivial>::value, "expected trivial base");
static_assert(IsTriviallyMoveConstructible<Trivial>::value, "expected trivial base");
static_assert(IsTriviallyCopyAssignable<Trivial>::value, "expected trivial base");
static_assert(IsTriviallyMoveAssignable<Trivial>::value, "expected trivial base");
static_assert(IsTriviallyDestructible<Trivial>::value, "expected trivial base");

struct NonTrivial {
  NonTrivial();
  NonTrivial(NonTrivial const&);
  NonTrivial(NonTrivial&&);
  NonTrivial& operator=(NonTrivial const&);
  NonTrivial& operator=(NonTrivial&&);
  ~NonTrivial();
};

static_assert(!IsTriviallyDefaultConstructible<NonTrivial>::value, "expected non-trivial base");
static_assert(!IsTriviallyCopyConstructible<NonTrivial>::value, "expected non-trivial base");
static_assert(!IsTriviallyMoveConstructible<NonTrivial>::value, "expected non-trivial base");
static_assert(!IsTriviallyCopyAssignable<NonTrivial>::value, "expected non-trivial base");
static_assert(!IsTriviallyMoveAssignable<NonTrivial>::value, "expected non-trivial base");
static_assert(!IsTriviallyDestructible<NonTrivial>::value, "expected non-trivial base");

static_assert(IsDefaultConstructible<NonTrivial>::value, "expected non-trivial base");
static_assert(IsCopyConstructible<NonTrivial>::value, "expected non-trivial base");
static_assert(IsMoveConstructible<NonTrivial>::value, "expected non-trivial base");
static_assert(IsCopyAssignable<NonTrivial>::value, "expected non-trivial base");
static_assert(IsMoveAssignable<NonTrivial>::value, "expected non-trivial base");
static_assert(IsDestructible<NonTrivial>::value, "expected non-trivial base");

struct Deleted {
  Deleted() = delete;
  Deleted(Deleted const&) = delete;
  Deleted(Deleted&&) = delete;
  Deleted& operator=(Deleted const&) = delete;
  Deleted& operator=(Deleted&&) = delete;
  ~Deleted() = delete;
};

static_assert(!IsDefaultConstructible<Deleted>::value, "expected deleted base");
static_assert(!IsCopyConstructible<Deleted>::value, "expected deleted base");
static_assert(!IsMoveConstructible<Deleted>::value, "expected deleted base");
static_assert(!IsCopyAssignable<Deleted>::value, "expected deleted base");
static_assert(!IsMoveAssignable<Deleted>::value, "expected deleted base");
static_assert(!IsDestructible<Deleted>::value, "expected deleted base");

// trivial + trivial
static_assert(IsBaseOf<ExpectedDestructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyDestructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyConstructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveConstructible<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyAssignable<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<Trivial, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveAssignable<Expected<Trivial, Trivial>>::value, "expected resulting type to be trivial as well");

// void + trivial
static_assert(IsBaseOf<ExpectedDestructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyDestructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");\

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyConstructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveConstructible<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyCopyAssignable<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<void, Trivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Trivial>>::value, "expected branch to trivial");
static_assert(IsTriviallyMoveAssignable<Expected<void, Trivial>>::value, "expected resulting type to be trivial as well");

// trivial + non-trivial
static_assert(IsBaseOf<ExpectedDestructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyDestructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsDestructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveConstructible<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<Trivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<Trivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveAssignable<Expected<Trivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

// void + non-trivial
static_assert(IsBaseOf<ExpectedDestructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyDestructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsDestructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::Trivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveConstructible<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<void, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<void, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveAssignable<Expected<void, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

// non-trivial + trivial
static_assert(IsBaseOf<ExpectedDestructibleBase<NonTrivial, Trivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, Trivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyDestructible<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsDestructible<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<NonTrivial, Trivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, Trivial>>::value, "expected branch to non-trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<NonTrivial, Trivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, Trivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyConstructible<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyConstructible<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<NonTrivial, Trivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, Trivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveConstructible<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveConstructible<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<NonTrivial, Trivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, Trivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyAssignable<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyAssignable<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<NonTrivial, Trivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, Trivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveAssignable<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveAssignable<Expected<NonTrivial, Trivial>>::value, "expected resulting type to be non-trivial as well");

// non-trivial + non-trivial
static_assert(IsBaseOf<ExpectedDestructibleBase<NonTrivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyDestructible<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsDestructible<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<NonTrivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, NonTrivial>>::value, "expected branch to non-trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<NonTrivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyConstructible<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyConstructible<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<NonTrivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveConstructible<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveConstructible<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<NonTrivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyCopyAssignable<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsCopyAssignable<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<NonTrivial, NonTrivial, SpecialMemberFunctionInfoType::NonTrivial>, Expected<NonTrivial, NonTrivial>>::value, "expected branch to non-trivial");
static_assert(!IsTriviallyMoveAssignable<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");
static_assert(IsMoveAssignable<Expected<NonTrivial, NonTrivial>>::value, "expected resulting type to be non-trivial as well");

// trivial + deleted
static_assert(IsBaseOf<ExpectedDestructibleBase<Trivial, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<Trivial, Deleted>>::value, "expected branch to deleted");
static_assert(!IsDestructible<Expected<Trivial, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<Trivial, Deleted, SpecialMemberFunctionInfoType::Trivial>, Expected<Trivial, Deleted>>::value, "expected branch to trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<Trivial, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<Trivial, Deleted>>::value, "expected branch to deleted");
static_assert(!IsCopyConstructible<Expected<Trivial, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<Trivial, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<Trivial, Deleted>>::value, "expected branch to deleted");
static_assert(!IsMoveConstructible<Expected<Trivial, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<Trivial, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<Trivial, Deleted>>::value, "expected branch to deleted");
static_assert(!IsCopyAssignable<Expected<Trivial, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<Trivial, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<Trivial, Deleted>>::value, "expected branch to deleted");
static_assert(!IsMoveAssignable<Expected<Trivial, Deleted>>::value, "expected resulting type to be deleted as well");

// void + deleted
static_assert(IsBaseOf<ExpectedDestructibleBase<void, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<void, Deleted>>::value, "expected branch to deleted");
static_assert(!IsDestructible<Expected<void, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<void, Deleted, SpecialMemberFunctionInfoType::Trivial>, Expected<void, Deleted>>::value, "expected branch to trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<void, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<void, Deleted>>::value, "expected branch to deleted");
static_assert(!IsCopyConstructible<Expected<void, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<void, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<void, Deleted>>::value, "expected branch to deleted");
static_assert(!IsMoveConstructible<Expected<void, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<void, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<void, Deleted>>::value, "expected branch to deleted");
static_assert(!IsCopyAssignable<Expected<void, Deleted>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<void, Deleted, SpecialMemberFunctionInfoType::Deleted>, Expected<void, Deleted>>::value, "expected branch to deleted");
static_assert(!IsMoveAssignable<Expected<void, Deleted>>::value, "expected resulting type to be deleted as well");

// deleted + trivial
static_assert(IsBaseOf<ExpectedDestructibleBase<Deleted, Trivial, SpecialMemberFunctionInfoType::Deleted>, Expected<Deleted, Trivial>>::value, "expected branch to deleted");
static_assert(!IsDestructible<Expected<Deleted, Trivial>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedDefaultConstructibleBase<Deleted, Trivial, SpecialMemberFunctionInfoType::Deleted>, Expected<Deleted, Trivial>>::value, "expected branch to trivial");

static_assert(IsBaseOf<ExpectedCopyConstructibleBase<Deleted, Trivial, SpecialMemberFunctionInfoType::Deleted>, Expected<Deleted, Trivial>>::value, "expected branch to deleted");
static_assert(!IsCopyConstructible<Expected<Deleted, Trivial>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedMoveConstructibleBase<Deleted, Trivial, SpecialMemberFunctionInfoType::Deleted>, Expected<Deleted, Trivial>>::value, "expected branch to deleted");
static_assert(!IsMoveConstructible<Expected<Deleted, Trivial>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedCopyAssignableBase<Deleted, Trivial, SpecialMemberFunctionInfoType::Deleted>, Expected<Deleted, Trivial>>::value, "expected branch to deleted");
static_assert(!IsCopyAssignable<Expected<Deleted, Trivial>>::value, "expected resulting type to be deleted as well");

static_assert(IsBaseOf<ExpectedMoveAssignableBase<Deleted, Trivial, SpecialMemberFunctionInfoType::Deleted>, Expected<Deleted, Trivial>>::value, "expected branch to deleted");
static_assert(!IsMoveAssignable<Expected<Deleted, Trivial>>::value, "expected resulting type to be deleted as well");
} // namespace
