// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11-2b

#include "cds/functional/FunctionalInterface"
#include "cds/meta/TypeTraits"
#include "UnitTest.hpp"

using namespace cds::meta;
using namespace cds::functional;

TEST(FunctionalInterface, PredicateFunction) {
  static_assert(IsSame<Decay<bool(int, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(int, float)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(double, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(int&, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<bool(int const&, int)>, PredicateFunction<int, int>>::value, "Failed Interface PredicateFunction");
  static_assert(!IsSame<Decay<int(int, int)>, PredicateFunction<int, int>>::value, "Faild Interface PredicateFunction");
}

TEST(FunctionalInterface, MapperFunction) {
  static_assert(IsSame<Decay<float(int, int)>, MapperFunction<float, int, int>>::value, "Failed Interface MapperFunction");
  static_assert(!IsSame<Decay<float(int&, int)>, MapperFunction<float, int, int>>::value, "Failed Interface MapperFunction");
}
