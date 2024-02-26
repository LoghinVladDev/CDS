// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/bindings/static/FindOfStaticBinding.hpp"
#include "UnitTest.hpp"
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <cds/Utility>

namespace {
using namespace cds;
using namespace cds::meta;
using namespace cds::impl;
using namespace cds::impl::sel;
using namespace cds::impl::findOfDeriv;

class Find_FwdValImm;
class Find_FwdValMut;
class Find_FwdValImmMut;
class Find_FwdSelImm;
class Find_FwdSelMut;
class Find_FwdSelImmMut;
class Find_FwdValSelImm;
class Find_FwdValSelMut;
class Find_FwdValSelImmMut;
}

namespace cds {
namespace meta {
template <> struct IterableTraits<Find_FwdValImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_FwdValMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; };
template <> struct IterableTraits<Find_FwdValImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_FwdSelImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_FwdSelMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; };
template <> struct IterableTraits<Find_FwdSelImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_FwdValSelImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_FwdValSelMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; };
template <> struct IterableTraits<Find_FwdValSelImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; };
}
}

namespace {
struct TCommonFwdImm : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonFwdMut : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

struct TCommonFwdImmMut : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::begin;
  using std::vector<int>::end;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonBwdImm : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
};

struct TCommonBwdMut : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
};

struct TCommonBwdImmMut : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
};

struct TCommonFwdBwdImm : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonFwdBwdMut : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

struct TCommonFwdBwdImmMut : private std::vector<int> {
public:
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
  using std::vector<int>::begin;
  using std::vector<int>::end;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

class Find_FwdValImm : public TCommonFwdImm, public FindOfStaticBinding<Find_FwdValImm, With<Value, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
};

class Find_FwdValMut : public TCommonFwdMut, public FindOfStaticBinding<Find_FwdValMut, With<Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
};

class Find_FwdValImmMut : public TCommonFwdImmMut, public FindOfStaticBinding<Find_FwdValImmMut, With<Value, Mutable, Immutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
};

template <typename I, typename V, typename S>
auto lfind(I&& b, I&& e, V&& v, S&& s) noexcept -> I {
  for (auto i = cds::forward<I>(b); i < cds::forward<I>(e); ++i) {
    if (cds::forward<S>(s)(*i) == cds::forward<V>(v)) {
      return i;
    }
  }
  return cds::forward<I>(e);
}

class Find_FwdSelImm : public TCommonFwdImm, public FindOfStaticBinding<Find_FwdSelImm, With<Projector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
};

class Find_FwdSelMut : public TCommonFwdMut, public FindOfStaticBinding<Find_FwdSelMut, With<Projector, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdSelImmMut : public TCommonFwdImmMut, public FindOfStaticBinding<Find_FwdSelImmMut, With<Projector, Immutable, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdValSelImm : public TCommonFwdImm, public FindOfStaticBinding<Find_FwdValSelImm, With<Value, Projector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
};

class Find_FwdValSelMut : public TCommonFwdMut, public FindOfStaticBinding<Find_FwdValSelMut, With<Projector, Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdValSelImmMut : public TCommonFwdImmMut, public FindOfStaticBinding<Find_FwdValSelImmMut, With<Projector, Value, Immutable, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

int doubled(int v) { return v * 2; }

template <typename T> void doBasicAllValImmTest() {
  T obj({1, 2, 3, 4});
  T obj2({2, 4});

  auto lRng = obj.findOf(obj2);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 4);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findOf(T{2, 4});
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 4);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicNotAllValImmTest() {
  T obj({1, 2, 3, 4});
  T obj2({2, 4});

  auto lRng = obj.findNotOf(obj2);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 1);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 3);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findNotOf(T{2, 4});
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 1);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 3);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicAllValMutTest() {
  T obj({1, 2, 3, 4});
  T obj2({2, 4});

  auto lRng = obj.findOf(obj2);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);
  *lIt = 12;
  ASSERT_EQ(*lIt, 12);
  ASSERT_EQ(obj[1], 12);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 4);
  *lIt = 14;
  ASSERT_EQ(*lIt, 14);
  ASSERT_EQ(obj[3], 14);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findOf(T{2, 4});
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);
  *rIt = 12;
  ASSERT_EQ(*rIt, 12);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 4);
  *rIt = 14;
  ASSERT_EQ(*rIt, 14);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicNotAllValMutTest() {
  T obj({1, 2, 3, 4});
  T obj2({1, 3});

  auto lRng = obj.findNotOf(obj2);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);
  *lIt = 12;
  ASSERT_EQ(*lIt, 12);
  ASSERT_EQ(obj[1], 12);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 4);
  *lIt = 14;
  ASSERT_EQ(*lIt, 14);
  ASSERT_EQ(obj[3], 14);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findNotOf(T{1, 3});
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);
  *rIt = 12;
  ASSERT_EQ(*rIt, 12);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 4);
  *rIt = 14;
  ASSERT_EQ(*rIt, 14);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicAllSelImmTest() {
  T obj({1, 2, 3, 4});
  T obj2({2, 4});

  auto lRng = obj.findOf(obj2, doubled);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 1);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findOf(T{2, 4}, doubled);
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 1);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicNotAllSelImmTest() {
  T obj({1, 2, 3, 4});
  T obj2({2, 4});

  auto lRng = obj.findNotOf(obj2, doubled);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 3);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 4);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findNotOf(T{2, 4}, doubled);
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 3);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 4);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicAllSelMutTest() {
  T obj({1, 2, 3, 4});
  T obj2({2, 4});

  auto lRng = obj.findOf(obj2, doubled);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 1);
  *lIt = 12;
  ASSERT_EQ(*lIt, 12);
  ASSERT_EQ(obj[0], 12);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);
  *lIt = 14;
  ASSERT_EQ(*lIt, 14);
  ASSERT_EQ(obj[1], 14);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findOf(T{2, 4}, doubled);
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 1);
  *rIt = 12;
  ASSERT_EQ(*rIt, 12);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);
  *rIt = 14;
  ASSERT_EQ(*rIt, 14);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicNotAllSelMutTest() {
  T obj({1, 2, 3, 4});
  T obj2({2, 4});

  auto lRng = obj.findNotOf(obj2, doubled);
  auto lIt = lRng.begin();
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 3);
  *lIt = 12;
  ASSERT_EQ(*lIt, 12);
  ASSERT_EQ(obj[2], 12);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 4);
  *lIt = 14;
  ASSERT_EQ(*lIt, 14);
  ASSERT_EQ(obj[3], 14);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T{1, 2, 3, 4}.findNotOf(T{2, 4}, doubled);
  auto rIt = rRng.begin();
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 3);
  *rIt = 12;
  ASSERT_EQ(*rIt, 12);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 4);
  *rIt = 14;
  ASSERT_EQ(*rIt, 14);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicFwdValImmTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(*obj.findFirstOf(T({3, 1})), 1);
  ASSERT_EQ(obj.findFirstOf(T({4})), obj.cend());
  ASSERT_EQ(*obj.findFirstNotOf(T({3, 1})), 2);
  ASSERT_EQ(obj.findFirstNotOf(T({3, 1, 2})), obj.cend());
}

template <typename T> void doBasicFwdValMutTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(*obj.findFirstOf(T({3, 1})), 1);
  ASSERT_EQ(obj.findFirstOf(T({4})), obj.end());
  ASSERT_EQ(*obj.findFirstNotOf(T({3, 1})), 2);
  ASSERT_EQ(obj.findFirstNotOf(T({3, 1, 2})), obj.end());
}

template <typename T> void doBasicFwdSelImmTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(obj.findFirstOf(T({3, 1}), doubled), obj.cend());
  ASSERT_EQ(*obj.findFirstOf(T({4}), doubled), 2);
  ASSERT_EQ(*obj.findFirstNotOf(T({3, 1}), doubled), 1);
  ASSERT_EQ(*obj.findFirstNotOf(T({3, 1, 2}), doubled), 2);
  ASSERT_EQ(obj.findFirstNotOf(T({2, 4, 6}), doubled), obj.cend());
}

template <typename T> void doBasicFwdSelMutTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(obj.findFirstOf(T({3, 1}), doubled), obj.end());
  ASSERT_EQ(*obj.findFirstOf(T({4}), doubled), 2);
  ASSERT_EQ(*obj.findFirstNotOf(T({3, 1}), doubled), 1);
  ASSERT_EQ(*obj.findFirstNotOf(T({3, 1, 2}), doubled), 2);
  ASSERT_EQ(obj.findFirstNotOf(T({2, 4, 6}), doubled), obj.end());
}

template <typename T> void doBasicBwdValImmTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(*obj.findLastOf(T({3, 1})), 3);
  ASSERT_EQ(obj.findLastOf(T({4})), obj.cend());
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1})), 2);
  ASSERT_EQ(obj.findLastNotOf(T({3, 1, 2})), obj.cend());
}

template <typename T> void doBasicBwdValMutTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(*obj.findLastOf(T({3, 1})), 3);
  ASSERT_EQ(obj.findLastOf(T({4})), obj.end());
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1})), 2);
  ASSERT_EQ(obj.findLastNotOf(T({3, 1, 2})), obj.end());
}

template <typename T> void doBasicBwdSelImmTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(obj.findLastOf(T({3, 1}), doubled), obj.cend());
  ASSERT_EQ(*obj.findLastOf(T({4}), doubled), 2);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1}), doubled), 3);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1, 2}), doubled), 3);
  ASSERT_EQ(obj.findLastNotOf(T({2, 4, 6}), doubled), obj.cend());
}

template <typename T> void doBasicBwdSelMutTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(obj.findLastOf(T({3, 1}), doubled), obj.end());
  ASSERT_EQ(*obj.findLastOf(T({4}), doubled), 2);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1}), doubled), 3);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1, 2}), doubled), 3);
  ASSERT_EQ(obj.findLastNotOf(T({2, 4, 6}), doubled), obj.end());
}
}

TEST(FindOfStaticBinding, findOf) {
  doBasicAllValImmTest<Find_FwdValImm>();
  doBasicAllValImmTest<Find_FwdValImmMut>();
  doBasicAllValImmTest<Find_FwdValSelImm>();
  doBasicAllValImmTest<Find_FwdValSelImmMut>();

  doBasicAllValMutTest<Find_FwdValMut>();
  doBasicAllValMutTest<Find_FwdValImmMut>();
  doBasicAllValMutTest<Find_FwdValSelMut>();
  doBasicAllValMutTest<Find_FwdValSelImmMut>();

  doBasicNotAllValImmTest<Find_FwdValImm>();
  doBasicNotAllValImmTest<Find_FwdValImmMut>();
  doBasicNotAllValImmTest<Find_FwdValSelImm>();
  doBasicNotAllValImmTest<Find_FwdValSelImmMut>();

  doBasicNotAllValMutTest<Find_FwdValMut>();
  doBasicNotAllValMutTest<Find_FwdValImmMut>();
  doBasicNotAllValMutTest<Find_FwdValSelMut>();
  doBasicNotAllValMutTest<Find_FwdValSelImmMut>();

  doBasicAllSelImmTest<Find_FwdSelImm>();
  doBasicAllSelImmTest<Find_FwdSelImmMut>();
  doBasicAllSelImmTest<Find_FwdValSelImm>();
  doBasicAllSelImmTest<Find_FwdValSelImmMut>();

  doBasicAllSelMutTest<Find_FwdSelMut>();
  doBasicAllSelMutTest<Find_FwdSelImmMut>();
  doBasicAllSelMutTest<Find_FwdValSelMut>();
  doBasicAllSelMutTest<Find_FwdValSelImmMut>();

  doBasicNotAllSelImmTest<Find_FwdSelImm>();
  doBasicNotAllSelImmTest<Find_FwdSelImmMut>();
  doBasicNotAllSelImmTest<Find_FwdValSelImm>();
  doBasicNotAllSelImmTest<Find_FwdValSelImmMut>();

  doBasicNotAllSelMutTest<Find_FwdSelMut>();
  doBasicNotAllSelMutTest<Find_FwdSelImmMut>();
  doBasicNotAllSelMutTest<Find_FwdValSelMut>();
  doBasicNotAllSelMutTest<Find_FwdValSelImmMut>();

  doBasicFwdValImmTest<Find_FwdValImm>();
  doBasicFwdValImmTest<Find_FwdValImmMut>();
  doBasicFwdValImmTest<Find_FwdValSelImm>();
  doBasicFwdValImmTest<Find_FwdValSelImmMut>();

  doBasicFwdValMutTest<Find_FwdValMut>();
  doBasicFwdValMutTest<Find_FwdValImmMut>();
  doBasicFwdValMutTest<Find_FwdValSelMut>();
  doBasicFwdValMutTest<Find_FwdValSelImmMut>();

  doBasicFwdSelImmTest<Find_FwdSelImm>();
  doBasicFwdSelImmTest<Find_FwdSelImmMut>();
  doBasicFwdSelImmTest<Find_FwdValSelImm>();
  doBasicFwdSelImmTest<Find_FwdValSelImmMut>();

  doBasicFwdSelMutTest<Find_FwdSelMut>();
  doBasicFwdSelMutTest<Find_FwdSelImmMut>();
  doBasicFwdSelMutTest<Find_FwdValSelMut>();
  doBasicFwdSelMutTest<Find_FwdValSelImmMut>();

  doBasicBwdValImmTest<Find_FwdValImm>();
  doBasicBwdValImmTest<Find_FwdValImmMut>();
  doBasicBwdValImmTest<Find_FwdValSelImm>();
  doBasicBwdValImmTest<Find_FwdValSelImmMut>();

  doBasicBwdValMutTest<Find_FwdValMut>();
  doBasicBwdValMutTest<Find_FwdValImmMut>();
  doBasicBwdValMutTest<Find_FwdValSelMut>();
  doBasicBwdValMutTest<Find_FwdValSelImmMut>();

  doBasicBwdSelImmTest<Find_FwdSelImm>();
  doBasicBwdSelImmTest<Find_FwdSelImmMut>();
  doBasicBwdSelImmTest<Find_FwdValSelImm>();
  doBasicBwdSelImmTest<Find_FwdValSelImmMut>();

  doBasicBwdSelMutTest<Find_FwdSelMut>();
  doBasicBwdSelMutTest<Find_FwdSelImmMut>();
  doBasicBwdSelMutTest<Find_FwdValSelMut>();
  doBasicBwdSelMutTest<Find_FwdValSelImmMut>();
}

#ifdef DCR_SINCECPP14
struct B;
struct B_WithAdapt;
namespace cds {
namespace meta {
template <> struct IterableTraits<B> {
  using Value = int;
  using Iterator = iterator::ForwardAddressIterator<int>;
  using ConstIterator = iterator::ForwardAddressIterator<int const*>;
  using ReverseIterator = iterator::BackwardAddressIterator<int>;
  using ConstReverseIterator = iterator::BackwardAddressIterator<int const*>;
};

template <> struct IterableTraits<B_WithAdapt> {
  using Value = int;
  using Iterator = iterator::ForwardAddressIterator<int>;
  using ConstIterator = iterator::ForwardAddressIterator<int const*>;
  using ReverseIterator = iterator::BackwardAddressIterator<int>;
  using ConstReverseIterator = iterator::BackwardAddressIterator<int const*>;
};
}
}

struct B : public FindOfStaticBinding<B, With<Value, Projector, Immutable, Mutable>> {
  constexpr bool contains(int x) const { return x == 1 || x == 2; }
  template <typename S> constexpr bool contains(int x, S&& s) {
    return cds::forward<S>(s)(x) == 2 || cds::forward<S>(s)(x) == 2; }

  constexpr iterator::ForwardAddressIterator<int> begin() {
    return iterator::ForwardAddressIterator<int>{data + 1};
  }

  constexpr iterator::ForwardAddressIterator<int> end() {
    return iterator::ForwardAddressIterator<int>{data + 3};
  }

  constexpr iterator::ForwardAddressIterator<int const> cbegin() const {
    return iterator::ForwardAddressIterator<int const>{data + 1};
  }

  constexpr iterator::ForwardAddressIterator<int const> cend() const {
    return iterator::ForwardAddressIterator<int const>{data + 3};
  }

  constexpr iterator::BackwardAddressIterator<int> rbegin() {
    return iterator::BackwardAddressIterator<int>{data + 2};
  }

  constexpr iterator::BackwardAddressIterator<int> rend() {
    return iterator::BackwardAddressIterator<int>{data};
  }

  constexpr iterator::BackwardAddressIterator<int const> crbegin() const {
    return iterator::BackwardAddressIterator<int const>{data + 2};
  }

  constexpr iterator::BackwardAddressIterator<int const> crend() const {
    return iterator::BackwardAddressIterator<int const>{data};
  }

  int data[4] = {-1, 1, 2, -1}; // padding to allow first and last elem to allow constexpr
};

struct B_WithAdapt : public FindOfStaticBinding<B_WithAdapt, With<Value, Projector, Immutable, Mutable>, FindResultTransformer<>, FindResultTransformer<>> {
  constexpr bool contains(int x) const { return x == 1 || x == 2; }
  template <typename S> constexpr bool contains(int x, S&& s) {
    return cds::forward<S>(s)(x) == 2 || cds::forward<S>(s)(x) == 2; }

  constexpr iterator::ForwardAddressIterator<int> begin() {
    return iterator::ForwardAddressIterator<int>{data + 1};
  }

  constexpr iterator::ForwardAddressIterator<int> end() {
    return iterator::ForwardAddressIterator<int>{data + 3};
  }

  constexpr iterator::ForwardAddressIterator<int const> cbegin() const {
    return iterator::ForwardAddressIterator<int const>{data + 1};
  }

  constexpr iterator::ForwardAddressIterator<int const> cend() const {
    return iterator::ForwardAddressIterator<int const>{data + 3};
  }

  constexpr iterator::BackwardAddressIterator<int> rbegin() {
    return iterator::BackwardAddressIterator<int>{data + 2};
  }

  constexpr iterator::BackwardAddressIterator<int> rend() {
    return iterator::BackwardAddressIterator<int>{data};
  }

  constexpr iterator::BackwardAddressIterator<int const> crbegin() const {
    return iterator::BackwardAddressIterator<int const>{data + 2};
  }

  constexpr iterator::BackwardAddressIterator<int const> crend() const {
    return iterator::BackwardAddressIterator<int const>{data};
  }

  int data[4] = {-1, 1, 2, -1}; // padding to allow first and last elem to allow constexpr
};

constexpr int cdoubled(int x) { return x * 2; }

constexpr bool evaluateFindOf() {
  B obj;
  auto rng = obj.findOf(obj);
  auto it = rng.begin();
  auto lIsOne = *it == 1;
  ++it;
  auto lIsTwo = *it == 2;
  ++it;
  auto lIsEnd = it == rng.end();

  auto rRng = B().findOf(obj);
  auto rIt = rRng.begin();
  auto rIsOne = *rIt == 1;
  ++rIt;
  auto rIsTwo = *rIt == 2;
  ++rIt;
  auto rIsEnd = rIt == rRng.end();

  return lIsOne && lIsTwo && lIsEnd && rIsOne && rIsTwo && rIsEnd;
}

constexpr bool evaluationCtx() {
  B obj;
  return
      evaluateFindOf() &&
      *obj.findFirstOf(B()) == 1 &&
      *obj.findFirstOf(B(), cdoubled) == 1 &&
      *obj.findFirstOf(B(), &cdoubled) == 1 &&
      obj.findFirstNotOf(B()) == obj.end() &&
      obj.findFirstNotOf(B()) == obj.cend() &&
      *obj.findFirstNotOf(B(), cdoubled) == 2 &&
      *obj.findFirstNotOf(B(), &cdoubled) == 2 &&
      *obj.findLastOf(B()) == 2 &&
      *obj.findLastOf(B(), cdoubled) == 1 &&
      *obj.findLastOf(B(), &cdoubled) == 1 &&
      obj.findLastNotOf(B()) == obj.end() &&
      obj.findLastNotOf(B()) == obj.end() &&
      *obj.findLastNotOf(B(), cdoubled) == 2 &&
      *obj.findLastNotOf(B(), &cdoubled) == 2;
}

TEST(FindOfStaticBinding, cpp14Constexpr) {
  static_assert(evaluationCtx(), "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findFirstOf(B_WithAdapt()) == 1, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findFirstNotOf(B_WithAdapt()) == -1, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findLastOf(B_WithAdapt()) == 2, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findLastNotOf(B_WithAdapt()) == -1, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findFirstOf(B_WithAdapt(), cdoubled) == 1, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findFirstNotOf(B_WithAdapt(), cdoubled) == 2, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findLastOf(B_WithAdapt(), cdoubled) == 1, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findLastNotOf(B_WithAdapt(), cdoubled) == 2, "Failed to evaluate constexpr");
}
#endif
