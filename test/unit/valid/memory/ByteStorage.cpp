// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/memory/ByteStorage>
#include "UnitTest.hpp"

namespace {
using cds::impl::ByteStorage;
} // namespace

TEST(ByteStorage, primitive) {
  ByteStorage<int> intStorage;
  intStorage.obj() = 3;
  ASSERT_EQ(intStorage.obj(), 3);

  static_assert(sizeof(intStorage) == sizeof(int), "Expected eq size");
}

TEST(ByteStorage, nonPrimitive) {
  int ctorCalls = 0;
  int dtorCalls = 0;

  class S {
  public:
    S(int& c, int& d) noexcept : _c(c), _d(d) {++_c;}
    ~S() noexcept { ++_d; }
  private:
    int& _c;
    int& _d;
  };

  ByteStorage<S> d;
  ASSERT_EQ(ctorCalls, 0);
  ASSERT_EQ(dtorCalls, 0);
  d.construct(ctorCalls, dtorCalls);
  ASSERT_EQ(ctorCalls, 1);
  ASSERT_EQ(dtorCalls, 0);
  d.destruct();
  ASSERT_EQ(ctorCalls, 1);
  ASSERT_EQ(dtorCalls, 1);

  static_assert(sizeof(d) == sizeof(S), "Expected eq size");
}

TEST(ByteStorage, arr) {
  ByteStorage<int[2]> arrStorage;
  arrStorage.obj()[0] = 1;
  arrStorage.obj()[1] = 2;
  ASSERT_EQ(arrStorage.obj()[0], 1);
  ASSERT_EQ(arrStorage.obj()[1], 2);

  static_assert(sizeof(arrStorage) == 2*sizeof(int), "Expected eq size");
  static_assert(sizeof(arrStorage) == sizeof(int[2]), "Expected eq size");
}
