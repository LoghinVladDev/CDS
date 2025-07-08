// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include "../Shared.hpp"
#include "../TrackerAllocator.hpp"

#include <array>
#include <list>
#include <vector>

#include <cds/collection/Vector>

namespace {
using std::array;
using std::list;
using std::vector;

using testing::iteq;
using testing::citeq;
using testing::TrackerAllocator;

using cds::Size;

using cds::functional::Equal;

using cds::impl::ArrayTraits;
using cds::impl::ArrayDynamicBackScalingBase;
using cds::impl::Vector;
using cds::impl::BaseVector;

template <typename T> using TestVector = BaseVector<
    T, Equal<>, TrackerAllocator<T>,
    ArrayDynamicBackScalingBase<T, Equal<>, TrackerAllocator<T>, ArrayTraits<T>>
>;

template <typename T> class NonSizedVector : private std::vector<T> {
public:
  using std::vector<T>::vector;
  using std::vector<T>::begin;
  using std::vector<T>::end;
};

template <typename T> class NonSizedList : private std::list<T> {
public:
  using std::list<T>::list;
  using std::list<T>::begin;
  using std::list<T>::end;
};

// head + tail + capacity
static_assert(sizeof(Vector<int>) == 2 * sizeof(void*) + sizeof(Size), "unexpected Vector size");
} // namespace

TEST(VectorTest, DefCtr) {
  TestVector<int> v;
  ASSERT_TRUE(v.empty());
  ASSERT_TRUE(citeq(v, array<int, 0u>{}));
  ASSERT_EQ(nullptr, v.data());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
}

TEST(VectorTest, IterCtr) {
  array<int, 3> from {1, 2, 3};
  TestVector<int> v {from.begin(), from.end()};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, from));
}

TEST(VectorTest, EmptyIterCtr) {
  array<int, 0> empty {};
  TestVector<int> v {empty.begin(), empty.end()};
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
  ASSERT_TRUE(citeq(v, array<int, 0>{}));
}

TEST(VectorTest, CopyCtr) {
  array<int, 3> from {1, 2, 3};
  TestVector<int> v0 {from.begin(), from.end()};
  TestVector<int> v1 {v0};

  ASSERT_FALSE(v0.empty());
  ASSERT_NE(v0.data(), v1.data());
  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(3u, v1.size());
  ASSERT_TRUE(citeq(v1, from));

  TestVector<int> v2;
  TestVector<int> v3 {v2};

  ASSERT_TRUE(v2.empty());
  ASSERT_TRUE(v3.empty());
  ASSERT_EQ(nullptr, v2.data());
  ASSERT_EQ(0u, v2.size());
  ASSERT_EQ(0u, v2.capacity());
  ASSERT_EQ(nullptr, v3.data());
  ASSERT_EQ(0u, v3.size());
  ASSERT_EQ(0u, v3.capacity());
}

TEST(VectorTest, MoveCtr) {
  array<int, 3> from {1, 2, 3};
  TestVector<int> v0 {from.begin(), from.end()};
  auto v0p = v0.data();
  TestVector<int> v1 {std::move(v0)};

  ASSERT_EQ(v1.data(), v0p);
  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(3u, v1.size());
  ASSERT_TRUE(citeq(v1, from));

  TestVector<int> v2;
  TestVector<int> v3 {std::move(v2)};

  ASSERT_TRUE(v3.empty());
  ASSERT_EQ(nullptr, v3.data());
  ASSERT_EQ(0u, v3.size());
  ASSERT_EQ(0u, v3.capacity());
}

TEST(VectorTest, ItCtrSized) {
  array<int, 3> values {1, 2, 3};
  TestVector<int> v {values.begin(), 2};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(2u, v.size());
  ASSERT_TRUE(iteq(v.begin(), v.end(), values.begin(), values.begin() + 2));
}

TEST(VectorTest, ItCtrSizedEmpty) {
  vector<int> values {};
  TestVector<int> v {values.begin(), 0};
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
  ASSERT_TRUE(citeq(v, vector<int>{}));
}

TEST(VectorTest, SizedRngCtr) {
  vector<int> values {1, 2, 3};
  TestVector<int> v {values};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, SizedRngCtrEmpty) {
  vector<int> values {};
  TestVector<int> v {values};
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, SizedRngCtrNoRAIT) {
  list<int> values {1, 2, 3};
  TestVector<int> v {values};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, SizedRngCtrEmptyNORAIT) {
  list<int> values {};
  TestVector<int> v {values};
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, NonSizedRngCtr) {
  NonSizedVector<int> values {1, 2, 3};
  TestVector<int> v {values};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, NonSizedRngCtrEmpty) {
  NonSizedVector<int> values {};
  TestVector<int> v {values};
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, NonSizedRngCtrNoRAIT) {
  NonSizedList<int> values {1, 2, 3};
  TestVector<int> v {values};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, NonSizedRngCtrEmptyNORAIT) {
  NonSizedList<int> values {};
  TestVector<int> v {values};
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
  ASSERT_TRUE(citeq(v, values));
}

TEST(VectorTest, SizeDefCtr) {
  TestVector<int> v (5);
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(5u, v.size());
}

TEST(VectorTest, SizeDefCtrEmpty) {
  TestVector<int> v (0);
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
}

TEST(VectorTest, SizeCopyCtr) {
  TestVector<int> v (5, 3);
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(5u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{3, 3, 3, 3, 3}));
}

TEST(VectorTest, SizeCopyCtrEmpty) {
  TestVector<int> v (0, 3);
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(0u, v.size());
  ASSERT_EQ(0u, v.capacity());
  ASSERT_EQ(nullptr, v.data());
}

TEST(VectorTest, InitListCtr) {
  TestVector<int> v {1, 2, 3, 4};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 4}));
}

TEST(VectorTest, CopyAssign) {
  TestVector<int> base0 (8, 1);
  TestVector<int> base1 (32, 2);
  TestVector<int> base2 (128, 3);
  TestVector<int> base3 (128, 3);
  TestVector<int> v;
  v = base1;
  ASSERT_TRUE(citeq(v, base1));
  v = base0;
  ASSERT_TRUE(citeq(v, base0));
  v = base2;
  ASSERT_TRUE(citeq(v, base2));
  v = base3;
  ASSERT_TRUE(citeq(v, base3));
}

TEST(VectorTest, MoveAssign) {
  TestVector<int> base0 (8, 1);
  TestVector<int> base1 (32, 2);
  TestVector<int> base2 (128, 3);
  TestVector<int> base3 (128, 3);

  TestVector<int> v;
  v = TestVector<int> {base1};
  ASSERT_TRUE(citeq(v, base1));
  v = TestVector<int> {base0};
  ASSERT_TRUE(citeq(v, base0));
  v = TestVector<int> {base2};
  ASSERT_TRUE(citeq(v, base2));
  v = TestVector<int> {base3};
  ASSERT_TRUE(citeq(v, base3));
}

TEST(VectorTest, SizedIterAssignRAIT) {
  vector<int> base0 (8, 1);
  vector<int> base1 (32, 2);
  vector<int> base2 (128, 3);
  vector<int> base3 (128, 3);

  TestVector<int> v;
  v = base1;
  ASSERT_TRUE(citeq(v, base1));
  v = base0;
  ASSERT_TRUE(citeq(v, base0));
  v = base2;
  ASSERT_TRUE(citeq(v, base2));
  v = base3;
  ASSERT_TRUE(citeq(v, base3));
}

TEST(VectorTest, izedIterAssignNoRAIT) {
  list<int> base0 (8, 1);
  list<int> base1 (32, 2);
  list<int> base2 (128, 3);
  list<int> base3 (128, 3);

  TestVector<int> v;
  v = base1;
  ASSERT_TRUE(citeq(v, base1));
  v = base0;
  ASSERT_TRUE(citeq(v, base0));
  v = base2;
  ASSERT_TRUE(citeq(v, base2));
  v = base3;
  ASSERT_TRUE(citeq(v, base3));
}

TEST(VectorTest, NonSizedIterAssignRAIT) {
  NonSizedVector<int> base0 (8, 1);
  NonSizedVector<int> base1 (32, 2);
  NonSizedVector<int> base2 (128, 3);
  NonSizedVector<int> base3 (128, 3);

  TestVector<int> v;
  v = base1;
  ASSERT_TRUE(citeq(v, base1));
  v = base0;
  ASSERT_TRUE(citeq(v, base0));
  v = base2;
  ASSERT_TRUE(citeq(v, base2));
  v = base3;
  ASSERT_TRUE(citeq(v, base3));
}

TEST(VectorTest, NonSizedIterAssignNoRAIT) {
  NonSizedList<int> base0 (8, 1);
  NonSizedList<int> base1 (32, 2);
  NonSizedList<int> base2 (128, 3);
  NonSizedList<int> base3 (128, 3);

  TestVector<int> v;
  v = base1;
  ASSERT_TRUE(citeq(v, base1));
  v = base0;
  ASSERT_TRUE(citeq(v, base0));
  v = base2;
  ASSERT_TRUE(citeq(v, base2));
  v = base3;
  ASSERT_TRUE(citeq(v, base3));
}

TEST(VectorTest, InitListAssign) {
  TestVector<int> v;
  v = {1, 2, 3};
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
  v = {1, 2, 3, 4};
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 4}));
  v = {1, 2};
  ASSERT_TRUE(citeq(v, vector<int>{1, 2}));

  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
       11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
       21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
       31, 32, 33};
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                   11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                                   21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                                   31, 32, 33}));
}

TEST(VectorTest, SelfAssign) {
  TestVector<int> v {1, 2, 3};
  v = v;
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
  v = std::move(v);
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
}

TEST(VectorTest, BaseMemFn) {
  using namespace cds::meta;
  TestVector<int> v {1, 2, 3, 4, 5};

  ASSERT_EQ(5u, v.size());
  ASSERT_EQ(5u, asConst(v).size());
  ASSERT_LE(5u, v.capacity());
  ASSERT_LE(5u, asConst(v).capacity());
  ASSERT_NE(nullptr, v.data());
  ASSERT_NE(nullptr, asConst(v).data());

  static_assert(IsSame<int*, decltype(v.data())>::value, "_");
  static_assert(IsSame<int const*, decltype(asConst(v).data())>::value, "_");
}

TEST(VectorTest, PopBack) {
  TestVector<int> v {1, 2, 3, 4, 5};
  ASSERT_EQ(5u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 4, 5}));
  v.popBack();
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 4}));
  v.popBack();
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
}

TEST(VectorTest, TakeBack) {
  TestVector<int> v {2, 3, 4, 5, 6};
  ASSERT_EQ(5u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{2, 3, 4, 5, 6}));
  ASSERT_EQ(6, v.takeBack());
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{2, 3, 4, 5}));
  ASSERT_EQ(5, v.takeBack());
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{2, 3, 4}));
}

TEST(VectorTest, Iteration) {
  TestVector<int> v {1, 2, 3};
  vector<int> e {1, 2, 3};
  ASSERT_TRUE(iteq(v.begin(), v.end(), e.begin(), e.end()));
  ASSERT_TRUE(iteq(asConst(v).begin(), asConst(v).end(), e.begin(), e.end()));
  ASSERT_TRUE(iteq(v.cbegin(), v.cend(), e.begin(), e.end()));
  ASSERT_TRUE(iteq(asConst(v).cbegin(), asConst(v).cend(), e.begin(), e.end()));
  ASSERT_TRUE(iteq(v.rbegin(), v.rend(), e.rbegin(), e.rend()));
  ASSERT_TRUE(iteq(asConst(v).rbegin(), asConst(v).rend(), e.rbegin(), e.rend()));
  ASSERT_TRUE(iteq(v.crbegin(), v.crend(), e.rbegin(), e.rend()));
  ASSERT_TRUE(iteq(asConst(v).crbegin(), asConst(v).crend(), e.rbegin(), e.rend()));
}

TEST(VectorTest, Positionals) {
  TestVector<int> v {1, 2, 3};
  ASSERT_EQ(1, v.front());
  ASSERT_EQ(1, asConst(v).front());
  ASSERT_EQ(3, v.back());
  ASSERT_EQ(3, asConst(v).back());

  v.front() = 4;
  v.back() = 0;

  ASSERT_TRUE(citeq(v, vector<int>{4, 2, 0}));
  ASSERT_EQ(4, v[0]);
  ASSERT_EQ(2, v[1]);
  ASSERT_EQ(0, v[2]);
  ASSERT_EQ(4, asConst(v)[0]);
  ASSERT_EQ(2, asConst(v)[1]);
  ASSERT_EQ(0, asConst(v)[2]);

  v[0] = 5;
  v[1] = 4;
  v[2] = 3;
  ASSERT_TRUE(citeq(v, vector<int>{5, 4, 3}));
}

TEST(VectorTest, Reserve) {
  TestVector<int> v;
  ASSERT_EQ(0u, v.capacity());
  v.reserve(10u);
  auto oldCap = v.capacity();
  auto oldP = v.data();
  ASSERT_LE(10u, v.capacity());
  ASSERT_NE(nullptr, v.data());
  ASSERT_EQ(0u, v.size());

  v.reserve(9);
  ASSERT_EQ(v.capacity(), oldCap);
  ASSERT_EQ(v.data(), oldP);

  v.reserve(100);
  ASSERT_EQ(100u, v.capacity());
  ASSERT_NE(v.data(), oldP);
  ASSERT_NE(nullptr, v.data());
  ASSERT_EQ(0u, v.size());
}

TEST(VectorTest, ResizeDefVal) {
  TestVector<int> v1;
  v1.resize(50, 1);
  ASSERT_TRUE(citeq(v1, vector<int>(50, 1)));
  v1.resize(40, 2);
  ASSERT_TRUE(citeq(v1, vector<int>(40, 1)));
  v1.resize(40, 2);
  ASSERT_TRUE(citeq(v1, vector<int>(40, 1)));
  v1.resize(60, 1);
  ASSERT_TRUE(citeq(v1, vector<int>(60, 1)));

  TestVector<int> v2;
  v2.resize(3, 1);
  ASSERT_EQ(3u, v2.size());
  ASSERT_TRUE(citeq(v2, vector<int>{1, 1, 1}));
  v2.resize(4, 2);
  ASSERT_EQ(4u, v2.size());
  ASSERT_TRUE(citeq(v2, vector<int>{1, 1, 1, 2}));
  v2.resize(3, 3);
  ASSERT_EQ(3u, v2.size());
  ASSERT_TRUE(citeq(v2, vector<int>{1, 1, 1}));
  v2.resize(5, 4);
  ASSERT_EQ(5u, v2.size());
  ASSERT_TRUE(citeq(v2, vector<int>{1, 1, 1, 4, 4}));
}

TEST(VectorTest, Resize) {
  TestVector<int> v;
  v.resize(3);
  ASSERT_EQ(3u, v.size());
  v.resize(4);
  ASSERT_EQ(4u, v.size());
  v.resize(3);
  ASSERT_EQ(3u, v.size());
  v.resize(5);
  ASSERT_EQ(5u, v.size());
}

TEST(VectorTest, ShrinkTo) {
  TestVector<int> v {1, 2, 3, 4, 5};
  v.shrinkTo(3);
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
  v.shrinkTo(7);
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
}

TEST(VectorTest, ForceShrinkTo) {
  TestVector<int> v {1, 2, 3, 4, 5};
  v.forceShrinkTo(3);
  ASSERT_EQ(3u, v.size());
  ASSERT_EQ(3u, v.capacity());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
  v.forceShrinkTo(7);
  ASSERT_EQ(3u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
}

TEST(VectorTest, ForceShrinkToFit) {
  vector<int> a;
  a.insert(a.begin(), 45);
  TestVector<int> v {1, 2, 3, 4, 5};
  auto oldP = v.data();
  v.popBack();
  v.popBack();
  v.forceShrink();
  ASSERT_NE(oldP, v.data());
  ASSERT_EQ(3u, v.size());
  ASSERT_EQ(3u, v.capacity());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3}));
}

TEST(VectorTest, EmplaceI0) {
  TestVector<int> v {1, 2, 3};
  v.emplace(0u, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5, 1, 2, 3}));
}

TEST(VectorTest, EmplaceI1) {
  TestVector<int> v {1, 2, 3};
  v.emplace(1u, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 5, 2, 3}));
}

TEST(VectorTest, EmplaceI2) {
  TestVector<int> v {1, 2, 3};
  v.emplace(2u, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 5, 3}));
}

TEST(VectorTest, EmplaceI3) {
  TestVector<int> v {1, 2, 3};
  v.emplace(3u, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 5}));
}

TEST(VectorTest, EmplaceBegin0) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.begin(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5, 1, 2, 3}));
}

TEST(VectorTest, EmplaceBegin1) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.begin() + 1, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 5, 2, 3}));
}

TEST(VectorTest, EmplaceBegin2) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.begin() + 2, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 5, 3}));
}

TEST(VectorTest, EmplaceBegin3) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.begin() + 3, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 5}));
}

TEST(VectorTest, EmplaceEnd) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.end(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 5}));
}

TEST(VectorTest, EmplaceCBegin0) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.cbegin(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5, 1, 2, 3}));
}

TEST(VectorTest, EmplaceCBegin1) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.cbegin() + 1, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 5, 2, 3}));
}

TEST(VectorTest, EmplaceCBegin2) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.cbegin() + 2, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 5, 3}));
}

TEST(VectorTest, EmplaceCBegin3) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.cbegin() + 3, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 5}));
}

TEST(VectorTest, EmplaceCEnd) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.cend(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 5}));
}

TEST(VectorTest, EmplaceRBegin0) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.rbegin(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 5}));
}

TEST(VectorTest, EmplaceRBegin1) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.rbegin() + 1, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 5, 3}));
}

TEST(VectorTest, EmplaceRBegin2) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.rbegin() + 2, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 5, 2, 3}));
}

TEST(VectorTest, EmplaceRBegin3) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.rbegin() + 3, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5, 1, 2, 3}));
}

TEST(VectorTest, EmplaceREnd) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.rend(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5, 1, 2, 3}));
}

TEST(VectorTest, EmplaceCRBegin0) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.crbegin(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 3, 5}));
}

TEST(VectorTest, EmplaceCRBegin1) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.crbegin() + 1, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 2, 5, 3}));
}

TEST(VectorTest, EmplaceCRBegin2) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.crbegin() + 2, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{1, 5, 2, 3}));
}

TEST(VectorTest, EmplaceCRBegin3) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.crbegin() + 3, 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5, 1, 2, 3}));
}

TEST(VectorTest, EmplaceCREnd) {
  TestVector<int> v {1, 2, 3};
  v.emplace(v.crend(), 5);
  ASSERT_EQ(4u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5, 1, 2, 3}));
}

TEST(VectorTest, EmplaceEmpty) {
  TestVector<int> v;
  v.emplace(v.begin(), 5);
  ASSERT_EQ(1u, v.size());
  ASSERT_TRUE(citeq(v, vector<int>{5}));
}

TEST(VectorTest, EmplaceResize) {
  TestVector<int> v;
  vector<int> equiv;
  for (auto val = 0; val < 128; ++val) {
    v.emplace(v.end(), val);
    equiv.emplace_back(val);
  }

  ASSERT_EQ(128u, v.size());
  ASSERT_TRUE(citeq(v, equiv));
}

TEST(VectorTest, Functional) {
  TestVector<int> v {1, 2, 3};

  unsigned count = 0;
  v.forEach([&count](int) { ++count; });
  ASSERT_EQ(3u, count);

  auto even = [](int v0) { return v0 % 2 == 0; };
  ASSERT_EQ(1u, v.count(even));
  ASSERT_TRUE(v.some(1, even));
  ASSERT_TRUE(v.atMost(2, even));
  ASSERT_TRUE(v.atLeast(1, even));
  ASSERT_TRUE(v.moreThan(0, even));
  ASSERT_TRUE(v.lessThan(2, even));
  ASSERT_TRUE(v.any(even));
  ASSERT_FALSE(v.all(even));
  ASSERT_FALSE(v.none(even));
}

#include <variant>

TEST(VectorTest, ContainsOf) {
  TestVector<int> v {1, 2, 3};
  ASSERT_TRUE(v.containsAnyOf({2, 4, 6}));
  ASSERT_FALSE(v.containsAnyOf({4, 6, 8}));
  ASSERT_TRUE(v.containsAllOf({1, 2, 3}));
  ASSERT_FALSE(v.containsAllOf({1, 2, 3, 4}));
  ASSERT_TRUE(v.containsAnyNotOf({2, 3, 4}));
  ASSERT_FALSE(v.containsAnyNotOf({1, 2, 3}));
  ASSERT_TRUE(v.containsNoneOf({4, 6, 8}));
  ASSERT_FALSE(v.containsNoneOf({2, 4, 6}));
}


