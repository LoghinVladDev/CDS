// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../../src/bindings/static/FindStaticBinding.hpp"
#include "UnitTest.hpp"
#include <vector>
#include <algorithm>
#include <cds/Utility>
#include <cds/iterator/AddressIterator>

namespace {
using namespace cds;
using namespace cds::meta;
using namespace cds::impl;
using namespace cds::impl::sel;
using namespace cds::impl::findDeriv;

class Find_ValImm;
class Find_ValMut;
class Find_ValImmMut;
class Find_SelImm;
class Find_SelMut;
class Find_SelImmMut;
class Find_ValSelImm;
class Find_ValSelMut;
class Find_ValSelImmMut;
}

namespace cds {
namespace meta {
template <> struct IterableTraits<Find_ValImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_ValMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; };
template <> struct IterableTraits<Find_ValImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_SelImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_SelMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; };
template <> struct IterableTraits<Find_SelImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_ValSelImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; };
template <> struct IterableTraits<Find_ValSelMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; };
template <> struct IterableTraits<Find_ValSelImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; };
}
}

namespace {
struct TCommonFwdImm : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonFwdMut : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

struct TCommonFwdImmMut : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::begin;
  using std::vector<int>::end;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonBwdImm : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
};

struct TCommonBwdMut : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
};

struct TCommonBwdImmMut : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
};

struct TCommonFwdBwdImm : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonFwdBwdMut : private std::vector<int> {
  using std::vector<int>::operator[];
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

struct TCommonFwdBwdImmMut : private std::vector<int> {
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

class Find_FwdValImm : public TCommonFwdImm, public FindStaticBinding<Find_FwdValImm, With<Value, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
};

class Find_FwdValMut : public TCommonFwdMut, public FindStaticBinding<Find_FwdValMut, With<Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
};

class Find_FwdValImmMut : public TCommonFwdImmMut, public FindStaticBinding<Find_FwdValImmMut, With<Value, Mutable, Immutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
};

class Find_FwdSelImm : public TCommonFwdImm, public FindStaticBinding<Find_FwdSelImm, With<Projector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
};

class Find_FwdSelMut : public TCommonFwdMut, public FindStaticBinding<Find_FwdSelMut, With<Projector, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
};

class Find_FwdSelImmMut : public TCommonFwdImmMut, public FindStaticBinding<Find_FwdSelImmMut, With<Projector, Immutable, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
};

class Find_FwdValSelImm : public TCommonFwdImm, public FindStaticBinding<Find_FwdValSelImm, With<Value, Projector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
};

class Find_FwdValSelMut : public TCommonFwdMut, public FindStaticBinding<Find_FwdValSelMut, With<Projector, Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
};

class Find_FwdValSelImmMut : public TCommonFwdImmMut, public FindStaticBinding<Find_FwdValSelImmMut, With<Projector, Value, Immutable, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
};

int doubled(int const v) { return v * 2; }

template <typename T> void doBasicFwdValImmTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findFirst(1), cds::begin(obj));
  ASSERT_EQ(obj.findFirst(2), ++cds::begin(obj));
  ASSERT_EQ(obj.findFirst(4), cds::end(obj));

  auto lRng = obj.find(2);
  auto lIt = lRng.begin();

  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T({1, 2, 3, 2}).find(2);
  auto rIt = rRng.begin();

  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicFwdValMutTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findFirst(1), cds::begin(obj));
  ASSERT_EQ(obj.findFirst(2), ++cds::begin(obj));
  ASSERT_EQ(obj.findFirst(4), cds::end(obj));

  *obj.findFirst(3) = 4;
  ASSERT_EQ(obj[2], 4);
  obj[2] = 3;

  auto lRng = obj.find(2);
  auto lIt = lRng.begin();

  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);
  ASSERT_EQ(obj[1], 4);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);
  ASSERT_EQ(obj[3], 4);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T({1, 2, 3, 2}).find(2);
  auto rIt = rRng.begin();

  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  *rIt = 4;
  ASSERT_EQ(*rIt, 4);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  *rIt = 4;
  ASSERT_EQ(*rIt, 4);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicFwdSelImmTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findFirst(2, doubled), obj.cbegin());
  ASSERT_EQ(obj.findFirst(4, doubled), ++obj.cbegin());
  ASSERT_EQ(obj.findFirst(5, doubled), obj.cend());

  auto lRng = obj.find(4, doubled);
  auto lIt = lRng.begin();

  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T({1, 2, 3, 2}).find(4, doubled);
  auto rIt = rRng.begin();

  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicFwdSelMutTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findFirst(2, doubled), obj.begin());
  ASSERT_EQ(obj.findFirst(4, doubled), ++obj.begin());
  ASSERT_EQ(obj.findFirst(5, doubled), obj.end());

  *obj.findFirst(4, doubled) = 6;
  ASSERT_EQ(obj[1], 6);
  obj[1] = 2;

  auto lRng = obj.find(4, doubled);
  auto lIt = lRng.begin();

  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);
  ASSERT_EQ(obj[1], 4);

  ++lIt;
  ASSERT_NE(lIt, lRng.end());
  ASSERT_EQ(*lIt, 2);

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);
  ASSERT_EQ(obj[3], 4);

  ++lIt;
  ASSERT_EQ(lIt, lRng.end());

  auto rRng = T({1, 2, 3, 2}).find(4, doubled);
  auto rIt = rRng.begin();

  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  *rIt = 4;
  ASSERT_EQ(*rIt, 4);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  *rIt = 4;
  ASSERT_EQ(*rIt, 4);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicBwdValImmTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(1), cds::begin(obj));
  ASSERT_EQ(obj.findLast(2), --cds::end(obj));
  ASSERT_EQ(obj.findLast(4), cds::end(obj));
}

template <typename T> void doBasicBwdValMutTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(1), cds::begin(obj));
  ASSERT_EQ(obj.findLast(2), --cds::end(obj));
  ASSERT_EQ(obj.findLast(4), cds::end(obj));

  *obj.findLast(2) = 5;
  ASSERT_EQ(obj[3], 5);
}

template <typename T> void doBasicBwdSelImmTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(2, doubled), cds::begin(obj));
  ASSERT_EQ(obj.findLast(4, doubled), --cds::end(obj));
  ASSERT_EQ(obj.findLast(7, doubled), cds::end(obj));
}

template <typename T> void doBasicBwdSelMutTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(2, doubled), cds::begin(obj));
  ASSERT_EQ(obj.findLast(4, doubled), --cds::end(obj));
  ASSERT_EQ(obj.findLast(7, doubled), cds::end(obj));

  *obj.findLast(4, doubled) = 5;
  ASSERT_EQ(obj[3], 5);
}
}

TEST(FindStaticBinding, find) {
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

struct B : public FindStaticBinding<B, With<Value, Projector, Immutable, Mutable>> {
  constexpr iterator::ForwardAddressIterator<int> begin() {
    return iterator::ForwardAddressIterator<int>{data + 1};
  }

  constexpr iterator::ForwardAddressIterator<int> end() {
    return iterator::ForwardAddressIterator<int>{data + 3};
  }

  CDS_ATTR(nodiscard) constexpr iterator::ForwardAddressIterator<int const> cbegin() const {
    return iterator::ForwardAddressIterator<int const>{data + 1};
  }

  CDS_ATTR(nodiscard) constexpr iterator::ForwardAddressIterator<int const> cend() const {
    return iterator::ForwardAddressIterator<int const>{data + 3};
  }

  constexpr iterator::BackwardAddressIterator<int> rbegin() {
    return iterator::BackwardAddressIterator<int>{data + 2};
  }

  constexpr iterator::BackwardAddressIterator<int> rend() {
    return iterator::BackwardAddressIterator<int>{data};
  }

  CDS_ATTR(nodiscard) constexpr iterator::BackwardAddressIterator<int const> crbegin() const {
    return iterator::BackwardAddressIterator<int const>{data + 2};
  }

  CDS_ATTR(nodiscard) constexpr iterator::BackwardAddressIterator<int const> crend() const {
    return iterator::BackwardAddressIterator<int const>{data};
  }

  int data[4] = {-1, 1, 2, -1}; // padding to allow first and last elem to allow constexpr
};

struct B_WithAdapt : public FindStaticBinding<B_WithAdapt, With<Value, Projector, Immutable, Mutable>, FindResultTransformer<>, FindResultTransformer<>> {
  constexpr iterator::ForwardAddressIterator<int> begin() {
    return iterator::ForwardAddressIterator<int>{data + 1};
  }

  constexpr iterator::ForwardAddressIterator<int> end() {
    return iterator::ForwardAddressIterator<int>{data + 3};
  }

  CDS_ATTR(nodiscard) constexpr iterator::ForwardAddressIterator<int const> cbegin() const {
    return iterator::ForwardAddressIterator<int const>{data + 1};
  }

  CDS_ATTR(nodiscard) constexpr iterator::ForwardAddressIterator<int const> cend() const {
    return iterator::ForwardAddressIterator<int const>{data + 3};
  }

  constexpr iterator::BackwardAddressIterator<int> rbegin() {
    return iterator::BackwardAddressIterator<int>{data + 2};
  }

  constexpr iterator::BackwardAddressIterator<int> rend() {
    return iterator::BackwardAddressIterator<int>{data};
  }

  CDS_ATTR(nodiscard) constexpr iterator::BackwardAddressIterator<int const> crbegin() const {
    return iterator::BackwardAddressIterator<int const>{data + 2};
  }

  CDS_ATTR(nodiscard) constexpr iterator::BackwardAddressIterator<int const> crend() const {
    return iterator::BackwardAddressIterator<int const>{data};
  }

  int data[4] = {-1, 1, 2, -1}; // padding to allow first and last elem to allow constexpr
};

constexpr int cdoubled(int const x) { return x * 2; }

constexpr bool evaluateFind() {
  B obj;
  auto rng = obj.find(1);
  auto it = rng.begin();

  bool const lIsOne = *it == 1;
  ++it;
  bool const isEnd = it == rng.end();

  auto rRng = B().find(1);
  auto rIt = rRng.begin();

  bool const rIsOne = *rIt == 1;
  ++rIt;
  bool const rIsEnd = rIt == rRng.end();

  return lIsOne && isEnd && rIsOne && rIsEnd;
}

constexpr bool evaluateFindFirst() {
  B obj;
  return obj.findFirst(1) == obj.begin()
      && obj.findFirst(3) == obj.end();
}

constexpr bool evaluateFindLast() {
  B obj;
  return obj.findLast(2) == (obj.end() - 1)
      && obj.findLast(3) == obj.end();
}

TEST(FindStaticBinding, cpp14Constexpr) {
  static_assert(evaluateFind(), "Failed to evaluate constexpr");
  static_assert(evaluateFindFirst(), "Failed to evaluate constexpr");
  static_assert(evaluateFindLast(), "Failed to evaluate constexpr");
}
#endif
