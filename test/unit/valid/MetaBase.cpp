// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11

#include "UnitTest.hpp"
#include "../../../src/meta/Base.hpp"

using namespace cds;
using namespace cds::meta;

TEST(MetaBase, IsSame) {
  static_assert(IsSame<S32, S32>::value, "Failed IsSame");
}

TEST(MetaBase, Integral) {
  using I = Integral<int, 5>;
  static_assert(I::value == 5, "Failed Integral");
  static_assert(IsSame<I::ValueType, int>::value, "Failed Integral");
  static_assert(IsSame<I::Type, I>::value, "Failed Integral");
}

TEST(MetaBase, Bool) {
  static_assert(IsSame<Bool<true>, True>::value, "Failed Bool");
  static_assert(IsSame<Bool<false>, False>::value, "Failed Bool");
}
