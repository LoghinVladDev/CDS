// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "../../../src/bindings/BindingSelectors.hpp"

namespace {
using namespace cds::impl::sel;

static_assert(Matches<Projector, Projector>::value, "test failure");
static_assert(!Matches<Projector, Immutable>::value, "test failure");

static_assert(TMatches<IsSame, IsSame<void, void>>::value, "test failure");
static_assert(!TMatches<IsSame, Conditional<True, void, void>>::value, "test failure");

static_assert(!AppearsIn<void>::value, "test failure");
static_assert(!AppearsIn<void, int>::value, "test failure");
static_assert(AppearsIn<void, int, void>::value, "test failure");
static_assert(AppearsIn<void, int, float, void>::value, "test failure");

static_assert(!TAppearsIn<IsSame>::value, "test failure");
static_assert(!TAppearsIn<IsSame, Conditional<True, void, void>>::value, "test failure");
static_assert(TAppearsIn<IsSame, Conditional<True, void, void>, IsSame<void, int>>::value, "test failure");

static_assert(!ContainsSelector<With<>, Value>::value, "test failure");
static_assert(!ContainsSelector<With<Projector>, Value>::value, "test failure");
static_assert(ContainsSelector<With<Projector, Value>, Value>::value, "test failure");
static_assert(ContainsSelector<With<Value, Projector>, Value>::value, "test failure");
static_assert(ContainsSelector<With<Projector, Projector, Projector, Value>, Value>::value, "test failure");
static_assert(ContainsSelector<With<Value, Projector, Projector, Projector>, Value>::value, "test failure");

static_assert(!ContainsAllSelectors<With<>, Value>::value, "test failure");
static_assert(!ContainsAllSelectors<With<Projector>, Value>::value, "test failure");
static_assert(!ContainsAllSelectors<With<Projector>, Value, Projector>::value, "test failure");
static_assert(ContainsAllSelectors<With<Projector, Value>, Value, Projector>::value, "test failure");
static_assert(ContainsAllSelectors<With<Projector, Immutable, Value>, Value, Projector>::value, "test failure");
} // namespace

#include <cds/collection/Vector>
#include <UnitTest.hpp>

int f(int x) {

}

TEST(a, b) {
  cds::impl::IsProjector<cds::Vector<int>, decltype(f)>::value;
}
