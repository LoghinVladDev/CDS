// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/collection/Vector>
#include <cds/collection/VectorView>
#include "../Shared.hpp"

namespace {
using testing::iteq;
using testing::citeq;
using cds::Size;
using cds::Vector;
using cds::VectorView;
using cds::makeView;
using cds::asConst;
using cds::ignore;

using cds::meta::IsSame;
using cds::meta::RemoveCVRef;

// head
static_assert(sizeof(VectorView<int, 10>) == sizeof(void*), "unexpected bounded VectorView size");

// head, tail
static_assert(sizeof(VectorView<int>) == sizeof(void*) * 2, "unexpected unbounded VectorView size");
} // namespace

TEST(VectorView, ctFromArray) {
  int nums[5] = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_TRUE(citeq(nums, view));
  static_assert(IsSame<RemoveCVRef<decltype(view)>, VectorView<int, 5>>::value, "Expected bounded");
}

TEST(VectorView, ctFromArrayConst) {
  int const nums[5] = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_TRUE(citeq(nums, view));
  static_assert(IsSame<RemoveCVRef<decltype(view)>, VectorView<int const, 5>>::value, "Expected bounded const");
}

TEST(VectorView, ctFromVector) {
  Vector<int> nums = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_TRUE(citeq(nums, view));
  static_assert(IsSame<RemoveCVRef<decltype(view)>, VectorView<int>>::value, "Expected unbounded");
}

TEST(VectorView, ctFromVectorConst) {
  Vector<int> const nums = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_TRUE(citeq(nums, view));
  static_assert(IsSame<RemoveCVRef<decltype(view)>, VectorView<int const>>::value, "Expected unbounded const");
}

TEST(VectorView, ctFromIList) {
  auto const list = {1, 2, 3, 4, 5};
  auto view = makeView(list);
  ASSERT_TRUE(citeq(list, view));
  static_assert(IsSame<RemoveCVRef<decltype(view)>, VectorView<int const>>::value, "Expected unbounded const");
}

TEST(VectorView, staticVecViewIterFns) {
  int nums[5] = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_TRUE(citeq(view, nums));
  ASSERT_TRUE(citeq(asConst(view), nums));
  ASSERT_TRUE(iteq(view.begin(), view.end(), nums, nums + 5));
  ASSERT_TRUE(iteq(view.cbegin(), view.cend(), nums, nums + 5));
  ASSERT_TRUE(iteq(view.rbegin(), view.rend(), cds::rbegin(nums), cds::rend(nums)));
  ASSERT_TRUE(iteq(view.crbegin(), view.crend(), cds::rbegin(nums), cds::rend(nums)));
}

TEST(VectorView, staticVecViewObsFns) {
  int nums[5] = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_EQ(5u, view.size());
  ASSERT_FALSE(view.empty());
  ASSERT_TRUE(view);

  ASSERT_EQ(1, view.front());
  ASSERT_EQ(5, view.back());

  view.front() = 6;
  view.back() = 7;
  ASSERT_EQ(6, nums[0]);
  ASSERT_EQ(7, nums[4]);

  ASSERT_EQ(3, view[2]);
  ASSERT_EQ(3, view.at(2));

  view[3] = 10;
  ASSERT_EQ(10, nums[3]);

  ASSERT_EQ(view.data(), &nums[0]);
}

TEST(VectorView, staticVecViewRangeFns) {
  int nums[5] = {1, 2, 3, 4, 5};
  auto view = makeView(nums);

  ASSERT_TRUE(citeq(view.first<3>(), Vector<int>{1, 2, 3}));
  ASSERT_TRUE(citeq(view.last<3>(), Vector<int>{3, 4, 5}));
  ASSERT_TRUE(citeq(view.sub<1, 3>(), Vector<int>{2, 3, 4}));
  ASSERT_TRUE(citeq(view.first(3), Vector<int>{1, 2, 3}));
  ASSERT_TRUE(citeq(view.last(3), Vector<int>{3, 4, 5}));
  ASSERT_TRUE(citeq(view.sub(1, 3), Vector<int>{2, 3, 4}));
}

TEST(VectorView, dynVecViewIterFns) {
  Vector<int> nums = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_TRUE(citeq(view, nums));
  ASSERT_TRUE(citeq(asConst(view), nums));
  ASSERT_TRUE(iteq(view.begin(), view.end(), nums.begin(), nums.end()));
  ASSERT_TRUE(iteq(view.cbegin(), view.cend(), nums.begin(), nums.end()));
  ASSERT_TRUE(iteq(view.rbegin(), view.rend(), cds::rbegin(nums), cds::rend(nums)));
  ASSERT_TRUE(iteq(view.crbegin(), view.crend(), cds::rbegin(nums), cds::rend(nums)));
}

TEST(VectorView, dynVecViewObsFns) {
  Vector<int> nums = {1, 2, 3, 4, 5};
  auto view = makeView(nums);
  ASSERT_EQ(5u, view.size());
  ASSERT_FALSE(view.empty());
  ASSERT_TRUE(view);

  ASSERT_EQ(1, view.front());
  ASSERT_EQ(5, view.back());

  view.front() = 6;
  view.back() = 7;
  ASSERT_EQ(6, nums[0]);
  ASSERT_EQ(7, nums[4]);

  ASSERT_EQ(3, view[2]);
  ASSERT_EQ(3, view.at(2));

  view[3] = 10;
  ASSERT_EQ(10, nums[3]);

  ASSERT_EQ(view.data(), &nums[0]);
}

TEST(VectorView, dynVecViewRangeFns) {
  Vector<int> nums = {1, 2, 3, 4, 5};
  auto view = makeView(nums);

  ASSERT_TRUE(citeq(view.first<3>(), Vector<int>{1, 2, 3}));
  ASSERT_TRUE(citeq(view.last<3>(), Vector<int>{3, 4, 5}));
  ASSERT_TRUE(citeq(view.sub<1, 3>(), Vector<int>{2, 3, 4}));
  ASSERT_TRUE(citeq(view.first(3), Vector<int>{1, 2, 3}));
  ASSERT_TRUE(citeq(view.last(3), Vector<int>{3, 4, 5}));
  ASSERT_TRUE(citeq(view.sub(1, 3), Vector<int>{2, 3, 4}));
}
