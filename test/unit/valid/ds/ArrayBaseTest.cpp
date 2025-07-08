// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"

#include "../../../src/ds/array/ArrayBase.hpp"

#include <cds/functional/Comparator>
#include <cds/memory/Allocator>

#include "../Shared.hpp"

#include <sstream>

namespace {
using cds::Allocator;
using cds::meta::Null;
using cds::functional::Equal;
using cds::impl::ArrayBase;
using cds::asConst;

using testing::citeq;
using testing::rciteq;

template <typename T> struct MockScalingBase {
  MockScalingBase() = default;

  MockScalingBase(std::initializer_list<T> const& list) {
    auto it = list.begin();
    for (auto i = 0; i < 3 && it != list.end(); ++i, ++it) {
      elems[cnt++] = *it;
    }
  }

  T* head() {
    return elems;
  }

  T* tail() {
    return elems + cnt;
  }

  CDS_ATTR(nodiscard) T const* head() const {
    return elems;
  }

  CDS_ATTR(nodiscard) T const* tail() const {
    return elems + cnt;
  }

  T* makeSpaceAt(cds::Size eCnt, T* p) {
    auto p1 = p;
    cnt += eCnt;
    return p1;
  }

  void resizeImpl(cds::Size size) {
    cnt = size;
  }

  void resizeImpl(cds::Size size, T val) {
    for (auto i = cnt; i < size; ++i) {
      elems[i] = val;
    }
    cnt = size;
  }

  CDS_ATTR(nodiscard) cds::Size size() const {
    return cnt;
  }

  CDS_ATTR(nodiscard) T* eraseRegion(T* f, T* t) {
    cnt -= static_cast<cds::Size>(t - f);
    return f;
  }

  CDS_ATTR(nodiscard) cds::Size capacity() const {
    return 3;
  }

  void clear() {
    cnt = 0;
  }

  T* data() {
    return elems;
  }

  void forceShrinkTo(cds::Size s) {
    cnt = cds::minOf(cnt, s);
  }

  void popBack() {
    --cnt;
  }

  void reserve(int) {

  }

  void shrinkTo(int n) {
    return forceShrinkTo(n);
  }

  int takeBack() {
    auto e = elems[cnt - 1];
    popBack();
    return e;
  }

  T elems[3]{};
  cds::Size cnt{0};
};

template <typename T> using MockArrayBase = ArrayBase<T, Equal<>, Allocator<T>, MockScalingBase<T>>;
} // namespace

TEST(ArrayBaseTest, it) {
  MockArrayBase<int> array{1, 2, 3};
  auto const equiv = {1, 2, 3};
  ASSERT_TRUE(citeq(array, equiv));
  ASSERT_TRUE(citeq(asConst(array), equiv));
}

TEST(ArrayBaseTest, rit) {
  MockArrayBase<int> array{1, 2, 3};
  auto const equiv = {3, 2, 1};
  ASSERT_TRUE(rciteq(array, equiv));
  ASSERT_TRUE(rciteq(asConst(array), equiv));
}

TEST(ArrayBaseTest, empty) {
  MockArrayBase<int> array{1, 2, 3};
  MockArrayBase<int> emptyArray;

  ASSERT_FALSE(array.empty());
  ASSERT_TRUE(emptyArray.empty());
}

TEST(ArrayBaseTest, frontBack) {
  MockArrayBase<int> array{1, 2};

  ASSERT_EQ(1, array.front());
  ASSERT_EQ(1, asConst(array).front());
  ASSERT_EQ(2, array.back());
  ASSERT_EQ(2, asConst(array).back());

  array.front() = 4;
  array.back() = 5;
  ASSERT_EQ(4, array.data()[0]);
  ASSERT_EQ(5, array.data()[1]);
}

TEST(ArrayBaseTest, idx) {
  MockArrayBase<int> array{1, 2};

  ASSERT_EQ(1, array[0u]);
  ASSERT_EQ(1, asConst(array)[0]);
  ASSERT_EQ(2, array[1]);
  ASSERT_EQ(2, asConst(array)[1]);

  array[0] = 4;
  array[1] = 5;
  ASSERT_EQ(4, array.data()[0]);
  ASSERT_EQ(5, array.data()[1]);
}

TEST(ArrayBaseTest, at) {
  MockArrayBase<int> array{1, 2};

  ASSERT_EQ(1, array.at(0));
  ASSERT_EQ(1, asConst(array).at(0));
  ASSERT_EQ(2, array.at(1));
  ASSERT_EQ(2, asConst(array).at(1));

  array.at(0) = 4;
  array.at(1) = 5;
  ASSERT_EQ(4, array.data()[0]);
  ASSERT_EQ(5, array.data()[1]);
}

TEST(ArrayBaseTest, resize) {
  MockArrayBase<int> array{1, 2, 3};
  array.resize(1);
  ASSERT_EQ(1u, array.size());
}

TEST(ArrayBaseTest, resizeInit) {
  MockArrayBase<int> array{1};
  auto const equiv = {1, 2, 2};
  array.resize(3, 2);
  ASSERT_TRUE(citeq(equiv, array));
}

TEST(ArrayBaseTest, emplace) {
  struct X {
    int a; int b; int c;
    X() = default;
    X(int aa, int bb, int cc) : a(aa), b(bb), c(cc) {}
    bool operator==(X const& obj) const {
      return a == obj.a && b == obj.b && c == obj.c;
    }
    bool operator!=(X const& obj) const {
      return !operator==(obj);
    }
  };

  MockArrayBase<X> array;
  auto const equiv = {X{1, 2, 3}, X{4, 5, 6}};

  ASSERT_EQ((X{1, 2, 3}), array.emplace(array.begin(), 1, 2, 3));
  ASSERT_EQ((X{4, 5, 6}), array.emplaceBack(4, 5, 6));

  ASSERT_TRUE(citeq(equiv, array));
}

TEST(ArrayBaseTest, insert) {
  MockArrayBase<int> array{1};
  auto const equiv = {1, 2, 2};
  array.insert(array.end(), 2, 2);
  ASSERT_TRUE(citeq(array, equiv));
}

TEST(ArrayBaseTest, insertRng) {
  MockArrayBase<int> array{};
  auto const equiv = {1, 2, 3};
  array.insert(array.end(), equiv.begin(), equiv.end());
  ASSERT_TRUE(citeq(array, equiv));
}

TEST(ArrayBaseTest, pushBack) {
  struct X {
    int a;
    bool operator==(X const& x) const {return a == x.a;}
    bool operator!=(X const& x) const {return a != x.a;}
    X(X const& o) = default;
    X(X&& o) noexcept : a(o.a) {}
    explicit X(int v) : a(v) {}
    X() = default;
  };
  MockArrayBase<X> array{};
  auto const equiv = {X{1}, X{2}};
  X const x1{1};
  array.pushBack(x1);
  X x2{2};
  array.pushBack(cds::mv(x2));
  ASSERT_TRUE(citeq(array, equiv));
}

TEST(ArrayBaseTest, remove) {
  MockArrayBase<int> array{1, 2, 3};
  auto const equiv = {1, 2};
  array.remove(array.end() - 1);
  ASSERT_TRUE(citeq(equiv, array));
}

TEST(ArrayBaseTest, removeRng) {
  MockArrayBase<int> array{1, 2, 3};
  auto const equiv = {1};
  array.remove(array.end() - 2, array.end());
  ASSERT_TRUE(citeq(equiv, array));
}

TEST(ArrayBaseTest, contains) {
  MockArrayBase<int> array{1, 2, 3};
  ASSERT_TRUE(array.contains(2));
  ASSERT_FALSE(array.contains(4));
  ASSERT_TRUE(array.contains(6, [](int x){return x * 2;}));
  ASSERT_FALSE(array.contains(7, [](int x){return x * 2;}));
}

TEST(ArrayBaseTest, boolConv) {
  MockArrayBase<int> array{1, 2, 3};
  MockArrayBase<int> emptyArr{};

  ASSERT_TRUE(static_cast<bool>(array));
  ASSERT_FALSE(static_cast<bool>(emptyArr));
}

TEST(ArrayBaseTest, ostream) {
  std::ostringstream oss;
  MockArrayBase<int> array{1, 2, 3};
  oss << array;
  ASSERT_EQ("[1, 2, 3]", oss.str());
}

TEST(ArrayBaseTest, ostreamEmpty) {
  std::ostringstream oss;
  MockArrayBase<int> array{};
  oss << array;
  ASSERT_EQ("[]", oss.str());
}

TEST(ArrayBaseTest, cmp) {
  ASSERT_EQ((MockArrayBase<int>{1, 2, 3}), (MockArrayBase<int>{1, 2, 3}));
  ASSERT_NE((MockArrayBase<int>{1, 2, 3}), (MockArrayBase<int>{1, 3, 3}));
  ASSERT_NE((MockArrayBase<int>{1, 3, 3}), (MockArrayBase<int>{1, 2, 3}));
  ASSERT_NE((MockArrayBase<int>{1, 3, 3}), (MockArrayBase<int>{1, 2}));

  auto const arr = MockArrayBase<int> {1, 2, 3};
  ASSERT_EQ(arr, arr);
}
