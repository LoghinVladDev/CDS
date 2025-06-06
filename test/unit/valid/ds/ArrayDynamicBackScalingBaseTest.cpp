// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"

#include "../../../src/ds/array/ArrayDynamicBackScalingBase.hpp"
#include "../../../src/ds/array/ArrayTraits.hpp"

#include <cds/functional/Comparator>
#include <cds/memory/Allocator>

#include <list>

namespace {
using cds::Allocator;
using cds::Size;
using cds::impl::ArrayTraits;
using cds::impl::ArrayDynamicBackScalingBase;

using cds::functional::Equal;

using cds::ignore;

template <typename T> class MockDynamicBackScalingBase :
    public ArrayDynamicBackScalingBase<T, Equal<>, Allocator<T>, ArrayTraits<T>> {
public:
  using ArrayDynamicBackScalingBase<T, Equal<>, Allocator<T>, ArrayTraits<T>>::ArrayDynamicBackScalingBase;
  using ArrayDynamicBackScalingBase<T, Equal<>, Allocator<T>, ArrayTraits<T>>::operator=;
};
} // namespace

TEST(ArrayDynamicBackScalingBaseTest, usingCustomAlloc) {
  int buffer[3] {1, 2, 3};
  struct LocalAlloc {
    CDS_ATTR(nodiscard) int* allocate(int) const {
      return buf;
    }

    void deallocate(int*, int) const {
      ignore = this;
    }

    int* buf;
  };

  LocalAlloc const alloc{buffer};
  ArrayDynamicBackScalingBase<int, Equal<>, LocalAlloc, ArrayTraits<int>> theArray(alloc);

  theArray.reserve(2);
  ASSERT_EQ(alloc.buf, theArray.data());

  theArray.makeSpaceAt(1, theArray.data());
  theArray.data()[0] = 5;
  ASSERT_EQ(5, buffer[0]);
  ASSERT_EQ(1, theArray.size());
}

TEST(ArrayDynamicBackScalingBaseTest, copyCtr) {
  int buffer[3] {1, 2, 3};
  struct LocalAlloc {
    CDS_ATTR(nodiscard) int* allocate(int) const {
      return buf;
    }

    void deallocate(int*, int) const {
      ignore = this;
    }

    int* buf;
  };

  LocalAlloc const alloc{buffer};
  ArrayDynamicBackScalingBase<int, Equal<>, LocalAlloc, ArrayTraits<int>> theArray(alloc);

  theArray.reserve(2);
  ASSERT_EQ(alloc.buf, theArray.data());

  theArray.makeSpaceAt(1, theArray.data());
  theArray.data()[0] = 5;
  ASSERT_EQ(5, buffer[0]);
  ASSERT_EQ(1, theArray.size());

  auto aCopy = theArray;
  ASSERT_EQ(buffer, aCopy.data());
  ASSERT_EQ(1, aCopy.size());
}

TEST(ArrayDynamicBackScalingBaseTest, copyCtr2) {
  MockDynamicBackScalingBase<int> anArray;
  anArray.makeSpaceAt(5, nullptr);

  ASSERT_EQ(anArray.capacity(), ArrayTraits<int>::minCapacity);
  anArray.data()[0] = 7;
  anArray.data()[2] = 5;
  anArray.data()[4] = 3;

  auto const aCopy = anArray;
  ASSERT_EQ(aCopy.capacity(), ArrayTraits<int>::minCapacity);
  ASSERT_NE(anArray.data(), aCopy.data());
  ASSERT_EQ(7, aCopy.data()[0]);
  ASSERT_EQ(5, aCopy.data()[2]);
  ASSERT_EQ(3, aCopy.data()[4]);
}

TEST(ArrayDynamicBackScalingBaseTest, copyCtr3) {
  MockDynamicBackScalingBase<int> anEmptyArray;

  ASSERT_EQ(0, anEmptyArray.capacity());
  ASSERT_EQ(nullptr, anEmptyArray.data());

  auto const aCopy{anEmptyArray};
  ASSERT_EQ(0, aCopy.capacity());
  ASSERT_EQ(nullptr, aCopy.data());
}

TEST(ArrayDynamicBackScalingBaseTest, moveCtr) {
  MockDynamicBackScalingBase<int> anArray;
  anArray.makeSpaceAt(5, nullptr);

  ASSERT_EQ(anArray.capacity(), ArrayTraits<int>::minCapacity);
  anArray.data()[0] = 7;
  anArray.data()[2] = 5;
  anArray.data()[4] = 3;

  auto oldData = anArray.data();
  auto theNewArray{std::move(anArray)};

  ASSERT_EQ(nullptr, anArray.data());
  ASSERT_EQ(oldData, theNewArray.data());
  ASSERT_EQ(ArrayTraits<int>::minCapacity, theNewArray.capacity());
}

TEST(ArrayDynamicBackScalingBaseTest, iterSizedCtr) {
  int const nums[]{1, 2, 3, 4, 5};
  MockDynamicBackScalingBase<int> anArray(cds::begin(nums), 3);

  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, sizedCtr) {
  MockDynamicBackScalingBase<int> anArray(3);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
}

TEST(ArrayDynamicBackScalingBaseTest, sizedValCtr) {
  MockDynamicBackScalingBase<int> anArray(3, 5);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(5, anArray.data()[0]);
  ASSERT_EQ(5, anArray.data()[1]);
  ASSERT_EQ(5, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, iterCtr) {
  int const nums[]{1, 2, 3};
  MockDynamicBackScalingBase<int> anArray(nums, nums + 3);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, sizedRngCtr) {
  int const nums[] = {1, 2, 3};
  MockDynamicBackScalingBase<int> anArray(nums);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, nonSizedRngCtr) {
  std::list<int> nums = {1, 2, 3};
  MockDynamicBackScalingBase<int> anArray(nums);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, initListCtr) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, copy) {
  MockDynamicBackScalingBase<int> const origArray{1, 2, 3};
  MockDynamicBackScalingBase<int> anArray;
  ignore = anArray;
  anArray = origArray;
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, move) {
  MockDynamicBackScalingBase<int> origArray{1, 2, 3};
  MockDynamicBackScalingBase<int> anArray;
  ignore = anArray;
  anArray = std::move(origArray);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
  ASSERT_EQ(nullptr, origArray.data());
}

TEST(ArrayDynamicBackScalingBaseTest, iterAssign) {
  MockDynamicBackScalingBase<int> anArray;
  ignore = anArray;
  anArray = {1, 2, 3};
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, iterAssignNonSized) {
  MockDynamicBackScalingBase<int> anArray;
  ignore = anArray;
  anArray = std::list<int>{1, 2, 3};
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, iterAssignSized) {
  MockDynamicBackScalingBase<int> anArray;
  ignore = anArray;
  int const nums[]{1, 2, 3};
  anArray = nums;
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}

TEST(ArrayDynamicBackScalingBaseTest, clearDestructs) {
  int alive = 0;
  struct X {
    X(int& a) : alive{a} {alive++;}
    X(X const& a) : alive{a.alive} {alive++;}
    ~X() {alive--;}

  private:
    int& alive;
  };

  MockDynamicBackScalingBase<X> anArray;
  anArray.makeSpaceAt(3, nullptr);
  cds::impl::construct(anArray.data(), alive);
  cds::impl::construct(anArray.data() + 1, alive);
  cds::impl::construct(anArray.data() + 2, alive);

  ASSERT_EQ(3, alive);
  ASSERT_EQ(3, anArray.size());
  anArray.clear();
  ASSERT_EQ(0, anArray.size());
  ASSERT_EQ(0, alive);
}

TEST(ArrayDynamicBackScalingBaseTest, capacity) {
  MockDynamicBackScalingBase<int> anArray(40);
  ASSERT_EQ(40, anArray.capacity());
  MockDynamicBackScalingBase<int> anotherArray(5);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anotherArray.capacity());
  MockDynamicBackScalingBase<int> emptyArray;
  ASSERT_EQ(0, emptyArray.capacity());
}

TEST(ArrayDynamicBackScalingBaseTest, size) {
  MockDynamicBackScalingBase<int> anArray(40);
  ASSERT_EQ(40, anArray.size());
  MockDynamicBackScalingBase<int> anotherArray(5);
  ASSERT_EQ(5, anotherArray.size());
  MockDynamicBackScalingBase<int> emptyArray;
  ASSERT_EQ(0, emptyArray.size());
}

TEST(ArrayDynamicBackScalingBaseTest, data) {
  MockDynamicBackScalingBase<int> anArray(40);
  ASSERT_NE(nullptr, anArray.data());
  MockDynamicBackScalingBase<int> anotherArray(5);
  ASSERT_NE(nullptr, anotherArray.data());
  MockDynamicBackScalingBase<int> emptyArray;
  ASSERT_EQ(nullptr, emptyArray.data());
}

TEST(ArrayDynamicBackScalingBaseTest, headTail) {
  MockDynamicBackScalingBase<int> anArray(40);
  ASSERT_NE(nullptr, anArray.head());
  ASSERT_NE(nullptr, anArray.tail());
  ASSERT_EQ(40, anArray.tail() - anArray.head());
  MockDynamicBackScalingBase<int> anotherArray(5);
  ASSERT_NE(nullptr, anotherArray.head());
  ASSERT_NE(nullptr, anotherArray.tail());
  ASSERT_EQ(5, anotherArray.tail() - anotherArray.head());
  MockDynamicBackScalingBase<int> emptyArray;
  ASSERT_EQ(nullptr, emptyArray.head());
  ASSERT_EQ(nullptr, emptyArray.tail());
  MockDynamicBackScalingBase<int> reservedArray;
  reservedArray.reserve(5);
  ASSERT_NE(nullptr, reservedArray.data());
  ASSERT_EQ(reservedArray.head(), reservedArray.tail());
}

TEST(ArrayDynamicBackScalingBaseTest, popBack) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
  anArray.popBack();
  ASSERT_EQ(2, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  anArray.popBack();
  ASSERT_EQ(1, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  anArray.popBack();
  ASSERT_EQ(0, anArray.size());
}

TEST(ArrayDynamicBackScalingBaseTest, takeBack) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
  ASSERT_EQ(3, anArray.takeBack());
  ASSERT_EQ(2, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(2, anArray.takeBack());
  ASSERT_EQ(1, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(1, anArray.takeBack());
  ASSERT_EQ(0, anArray.size());
}

TEST(ArrayDynamicBackScalingBaseTest, reserve) {
  MockDynamicBackScalingBase<int> anArray;
  ASSERT_EQ(0, anArray.capacity());
  ASSERT_EQ(nullptr, anArray.data());

  anArray.reserve(5);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  ASSERT_NE(nullptr, anArray.data());

  anArray.reserve(40);
  ASSERT_EQ(40, anArray.capacity());
  ASSERT_NE(nullptr, anArray.data());

  auto const oldData = anArray.data();
  anArray.reserve(20);
  ASSERT_EQ(40, anArray.capacity());
  ASSERT_EQ(oldData, anArray.data());
}

TEST(ArrayDynamicBackScalingBaseTest, shrinkTo) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
  anArray.shrinkTo(1);
  ASSERT_EQ(1, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
}

TEST(ArrayDynamicBackScalingBaseTest, forceShinkTo) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};
  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
  ASSERT_EQ(ArrayTraits<int>::minCapacity, anArray.capacity());
  anArray.forceShrinkTo(1);
  ASSERT_EQ(1, anArray.capacity());
  ASSERT_EQ(1, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
}

TEST(ArrayDynamicBackScalingBaseTest, resizeImpl) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};
  ASSERT_EQ(3, anArray.size());
  anArray.resizeImpl(1);
  ASSERT_EQ(1, anArray.size());
  anArray.resizeImpl(5, 10);
  ASSERT_EQ(5, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(10, anArray.data()[1]);
  ASSERT_EQ(10, anArray.data()[2]);
  ASSERT_EQ(10, anArray.data()[3]);
  ASSERT_EQ(10, anArray.data()[4]);
}

TEST(ArrayDynamicBackScalingBaseTest, makeSpaceAt) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};

  cds::impl::fillNInitialize(anArray.makeSpaceAt(2, anArray.data() + 3), 2, 10);
  cds::impl::fillNInitialize(anArray.makeSpaceAt(2, anArray.data() + 2), 2, 20);
  cds::impl::fillNInitialize(anArray.makeSpaceAt(2, anArray.data()), 2, 30);

  ASSERT_EQ(9, anArray.size());
  ASSERT_EQ(30, anArray.data()[0]);
  ASSERT_EQ(30, anArray.data()[1]);
  ASSERT_EQ(1, anArray.data()[2]);
  ASSERT_EQ(2, anArray.data()[3]);
  ASSERT_EQ(20, anArray.data()[4]);
  ASSERT_EQ(20, anArray.data()[5]);
  ASSERT_EQ(3, anArray.data()[6]);
  ASSERT_EQ(10, anArray.data()[7]);
  ASSERT_EQ(10, anArray.data()[8]);
}

TEST(ArrayDynamicBackScalingBaseTest, eraseRegion) {
  MockDynamicBackScalingBase<int> anArray{1, 2, 3};

  cds::impl::fillNInitialize(anArray.makeSpaceAt(2, anArray.data() + 3), 2, 10);
  cds::impl::fillNInitialize(anArray.makeSpaceAt(2, anArray.data() + 2), 2, 20);
  cds::impl::fillNInitialize(anArray.makeSpaceAt(2, anArray.data()), 2, 30);

  anArray.eraseRegion(anArray.data() + 7, anArray.data() + 9);
  anArray.eraseRegion(anArray.data() + 4, anArray.data() + 6);
  anArray.eraseRegion(anArray.data(), anArray.data() + 2);

  ASSERT_EQ(3, anArray.size());
  ASSERT_EQ(1, anArray.data()[0]);
  ASSERT_EQ(2, anArray.data()[1]);
  ASSERT_EQ(3, anArray.data()[2]);
}
