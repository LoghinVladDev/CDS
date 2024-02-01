// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/bindings/static/FindStaticBinding.hpp"
#include "UnitTest.hpp"
#include <vector>
#include <algorithm>
#include <cds/Utility>

namespace {
using namespace cds;
using namespace cds::meta;
using namespace cds::impl;
using namespace cds::impl::sel;
using namespace cds::impl::findDeriv;

class Find_FwdValImm;
class Find_FwdValMut;
class Find_FwdValImmMut;
class Find_FwdSelImm;
class Find_FwdSelMut;
class Find_FwdSelImmMut;
class Find_FwdValSelImm;
class Find_FwdValSelMut;
class Find_FwdValSelImmMut;

class Find_BwdValImm;
class Find_BwdValMut;
class Find_BwdValImmMut;
class Find_BwdSelImm;
class Find_BwdSelMut;
class Find_BwdSelImmMut;
class Find_BwdValSelImm;
class Find_BwdValSelMut;
class Find_BwdValSelImmMut;

class Find_FwdBwdValImm;
class Find_FwdBwdValMut;
class Find_FwdBwdValImmMut;
class Find_FwdBwdSelImm;
class Find_FwdBwdSelMut;
class Find_FwdBwdSelImmMut;
class Find_FwdBwdValSelImm;
class Find_FwdBwdValSelMut;
class Find_FwdBwdValSelImmMut;
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

template <> struct IterableTraits<Find_BwdValImm> { using Value = int; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_BwdValMut> { using Value = int; using ReverseIterator = typename std::vector<int>::reverse_iterator; };
template <> struct IterableTraits<Find_BwdValImmMut> { using Value = int; using ReverseIterator = typename std::vector<int>::reverse_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_BwdSelImm> { using Value = int; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_BwdSelMut> { using Value = int; using ReverseIterator = typename std::vector<int>::reverse_iterator; };
template <> struct IterableTraits<Find_BwdSelImmMut> { using Value = int; using ReverseIterator = typename std::vector<int>::reverse_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_BwdValSelImm> { using Value = int; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_BwdValSelMut> { using Value = int; using ReverseIterator = typename std::vector<int>::reverse_iterator; };
template <> struct IterableTraits<Find_BwdValSelImmMut> { using Value = int; using ReverseIterator = typename std::vector<int>::reverse_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };

template <> struct IterableTraits<Find_FwdBwdValImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdValMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ReverseIterator = typename std::vector<int>::reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdValImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; using ReverseIterator = typename std::vector<int>::reverse_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdSelImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdSelMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ReverseIterator = typename std::vector<int>::reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdSelImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; using ReverseIterator = typename std::vector<int>::reverse_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdValSelImm> { using Value = int; using ConstIterator = typename std::vector<int>::const_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdValSelMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ReverseIterator = typename std::vector<int>::reverse_iterator; };
template <> struct IterableTraits<Find_FwdBwdValSelImmMut> { using Value = int; using Iterator = typename std::vector<int>::iterator; using ConstIterator = typename std::vector<int>::const_iterator; using ReverseIterator = typename std::vector<int>::reverse_iterator; using ConstReverseIterator = typename std::vector<int>::const_reverse_iterator; };
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

class Find_FwdValImm : public TCommonFwdImm, public FindStaticBinding<Find_FwdValImm, With<Forward, Value, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
};

class Find_FwdValMut : public TCommonFwdMut, public FindStaticBinding<Find_FwdValMut, With<Forward, Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
};

class Find_FwdValImmMut : public TCommonFwdImmMut, public FindStaticBinding<Find_FwdValImmMut, With<Forward, Value, Mutable, Immutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
};

class Find_FwdSelImm : public TCommonFwdImm, public FindStaticBinding<Find_FwdSelImm, With<Forward, Selector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
};

class Find_FwdSelMut : public TCommonFwdMut, public FindStaticBinding<Find_FwdSelMut, With<Forward, Selector, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
};

class Find_FwdSelImmMut : public TCommonFwdImmMut, public FindStaticBinding<Find_FwdSelImmMut, With<Forward, Selector, Immutable, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
};

class Find_FwdValSelImm : public TCommonFwdImm, public FindStaticBinding<Find_FwdValSelImm, With<Forward, Value, Selector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
};

class Find_FwdValSelMut : public TCommonFwdMut, public FindStaticBinding<Find_FwdValSelMut, With<Selector, Forward, Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
};

class Find_FwdValSelImmMut : public TCommonFwdImmMut, public FindStaticBinding<Find_FwdValSelImmMut, With<Selector, Value, Immutable, Forward, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
};



class Find_BwdValImm : public TCommonBwdImm, public FindStaticBinding<Find_BwdValImm, With<Backward, Value, Immutable>> {
public:
  using TCommonBwdImm::TCommonBwdImm;
};

class Find_BwdValMut : public TCommonBwdMut, public FindStaticBinding<Find_BwdValMut, With<Value, Backward, Mutable>> {
public:
  using TCommonBwdMut::TCommonBwdMut;
};

class Find_BwdValImmMut : public TCommonBwdImmMut, public FindStaticBinding<Find_BwdValImmMut, With<Value, Mutable, Immutable, Backward>> {
public:
  using TCommonBwdImmMut::TCommonBwdImmMut;
};

class Find_BwdSelImm : public TCommonBwdImm, public FindStaticBinding<Find_BwdSelImm, With<Backward, Selector, Immutable>> {
public:
  using TCommonBwdImm::TCommonBwdImm;
};

class Find_BwdSelMut : public TCommonBwdMut, public FindStaticBinding<Find_BwdSelMut, With<Backward, Selector, Mutable>> {
public:
  using TCommonBwdMut::TCommonBwdMut;
};

class Find_BwdSelImmMut : public TCommonBwdImmMut, public FindStaticBinding<Find_BwdSelImmMut, With<Backward, Selector, Immutable, Mutable>> {
public:
  using TCommonBwdImmMut::TCommonBwdImmMut;
};

class Find_BwdValSelImm : public TCommonBwdImm, public FindStaticBinding<Find_BwdValSelImm, With<Backward, Value, Selector, Immutable>> {
public:
  using TCommonBwdImm::TCommonBwdImm;
};

class Find_BwdValSelMut : public TCommonBwdMut, public FindStaticBinding<Find_BwdValSelMut, With<Selector, Backward, Value, Mutable>> {
public:
  using TCommonBwdMut::TCommonBwdMut;
};

class Find_BwdValSelImmMut : public TCommonBwdImmMut, public FindStaticBinding<Find_BwdValSelImmMut, With<Selector, Value, Immutable, Backward, Mutable>> {
public:
  using TCommonBwdImmMut::TCommonBwdImmMut;
};



class Find_FwdBwdValImm : public TCommonFwdBwdImm, public FindStaticBinding<Find_FwdBwdValImm, With<Backward, Value, Immutable, Forward>> {
public:
  using TCommonFwdBwdImm::TCommonFwdBwdImm;
};

class Find_FwdBwdValMut : public TCommonFwdBwdMut, public FindStaticBinding<Find_FwdBwdValMut, With<Value, Forward, Backward, Mutable>> {
public:
  using TCommonFwdBwdMut::TCommonFwdBwdMut;
};

class Find_FwdBwdValImmMut : public TCommonFwdBwdImmMut, public FindStaticBinding<Find_FwdBwdValImmMut, With<Value, Mutable, Immutable, Forward, Backward>> {
public:
  using TCommonFwdBwdImmMut::TCommonFwdBwdImmMut;
};

class Find_FwdBwdSelImm : public TCommonFwdBwdImm, public FindStaticBinding<Find_FwdBwdSelImm, With<Backward, Selector, Forward, Immutable>> {
public:
  using TCommonFwdBwdImm::TCommonFwdBwdImm;
};

class Find_FwdBwdSelMut : public TCommonFwdBwdMut, public FindStaticBinding<Find_FwdBwdSelMut, With<Backward, Forward, Selector, Mutable>> {
public:
  using TCommonFwdBwdMut::TCommonFwdBwdMut;
};

class Find_FwdBwdSelImmMut : public TCommonFwdBwdImmMut, public FindStaticBinding<Find_FwdBwdSelImmMut, With<Backward, Forward, Selector, Immutable, Mutable>> {
public:
  using TCommonFwdBwdImmMut::TCommonFwdBwdImmMut;
};

class Find_FwdBwdValSelImm : public TCommonFwdBwdImm, public FindStaticBinding<Find_FwdBwdValSelImm, With<Backward, Value, Selector, Forward, Immutable>> {
public:
  using TCommonFwdBwdImm::TCommonFwdBwdImm;
};

class Find_FwdBwdValSelMut : public TCommonFwdBwdMut, public FindStaticBinding<Find_FwdBwdValSelMut, With<Selector, Forward, Backward, Value, Mutable>> {
public:
  using TCommonFwdBwdMut::TCommonFwdBwdMut;
};

class Find_FwdBwdValSelImmMut : public TCommonFwdBwdImmMut, public FindStaticBinding<Find_FwdBwdValSelImmMut, With<Selector, Value, Immutable, Backward, Forward, Mutable>> {
public:
  using TCommonFwdBwdImmMut::TCommonFwdBwdImmMut;
};

int doubled(int v) { return v * 2; }

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

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);

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

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);

  ++rIt;
  ASSERT_NE(rIt, rRng.end());
  ASSERT_EQ(*rIt, 2);

  *lIt = 4;
  ASSERT_EQ(*lIt, 4);

  ++rIt;
  ASSERT_EQ(rIt, rRng.end());
}

template <typename T> void doBasicBwdValImmTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(1), --cds::rend(obj));
  ASSERT_EQ(obj.findLast(2), cds::rbegin(obj));
  ASSERT_EQ(obj.findLast(4), cds::rend(obj));
}

template <typename T> void doBasicBwdValMutTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(1), --cds::rend(obj));
  ASSERT_EQ(obj.findLast(2), cds::rbegin(obj));
  ASSERT_EQ(obj.findLast(4), cds::rend(obj));

  *obj.findLast(2) = 5;
  ASSERT_EQ(obj[3], 5);
}

template <typename T> void doBasicBwdSelImmTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(2, doubled), --cds::rend(obj));
  ASSERT_EQ(obj.findLast(4, doubled), cds::rbegin(obj));
  ASSERT_EQ(obj.findLast(7, doubled), cds::rend(obj));
}

template <typename T> void doBasicBwdSelMutTest() {
  T obj({1, 2, 3, 2});
  ASSERT_EQ(obj.findLast(2, doubled), --cds::rend(obj));
  ASSERT_EQ(obj.findLast(4, doubled), cds::rbegin(obj));
  ASSERT_EQ(obj.findLast(7, doubled), cds::rend(obj));

  *obj.findLast(4, doubled) = 5;
  ASSERT_EQ(obj[3], 5);
}
}

TEST(FindStaticBinding, find) {
  doBasicFwdValImmTest<Find_FwdValImm>();
  doBasicFwdValImmTest<Find_FwdValImmMut>();
  doBasicFwdValImmTest<Find_FwdValSelImm>();
  doBasicFwdValImmTest<Find_FwdValSelImmMut>();
  doBasicFwdValImmTest<Find_FwdBwdValImm>();
  doBasicFwdValImmTest<Find_FwdBwdValImmMut>();
  doBasicFwdValImmTest<Find_FwdBwdValSelImm>();
  doBasicFwdValImmTest<Find_FwdBwdValSelImmMut>();

  doBasicFwdValMutTest<Find_FwdValMut>();
  doBasicFwdValMutTest<Find_FwdValImmMut>();
  doBasicFwdValMutTest<Find_FwdValSelMut>();
  doBasicFwdValMutTest<Find_FwdValSelImmMut>();
  doBasicFwdValMutTest<Find_FwdBwdValMut>();
  doBasicFwdValMutTest<Find_FwdBwdValImmMut>();
  doBasicFwdValMutTest<Find_FwdBwdValSelMut>();
  doBasicFwdValMutTest<Find_FwdBwdValSelImmMut>();

  doBasicFwdSelImmTest<Find_FwdSelImm>();
  doBasicFwdSelImmTest<Find_FwdSelImmMut>();
  doBasicFwdSelImmTest<Find_FwdValSelImm>();
  doBasicFwdSelImmTest<Find_FwdValSelImmMut>();
  doBasicFwdSelImmTest<Find_FwdBwdSelImm>();
  doBasicFwdSelImmTest<Find_FwdBwdSelImmMut>();
  doBasicFwdSelImmTest<Find_FwdBwdValSelImm>();
  doBasicFwdSelImmTest<Find_FwdBwdValSelImmMut>();

  doBasicFwdSelMutTest<Find_FwdSelMut>();
  doBasicFwdSelMutTest<Find_FwdSelImmMut>();
  doBasicFwdSelMutTest<Find_FwdValSelMut>();
  doBasicFwdSelMutTest<Find_FwdValSelImmMut>();
  doBasicFwdSelMutTest<Find_FwdBwdSelMut>();
  doBasicFwdSelMutTest<Find_FwdBwdSelImmMut>();
  doBasicFwdSelMutTest<Find_FwdBwdValSelMut>();
  doBasicFwdSelMutTest<Find_FwdBwdValSelImmMut>();

  doBasicBwdValImmTest<Find_BwdValImm>();
  doBasicBwdValImmTest<Find_BwdValImmMut>();
  doBasicBwdValImmTest<Find_BwdValSelImm>();
  doBasicBwdValImmTest<Find_BwdValSelImmMut>();
  doBasicBwdValImmTest<Find_FwdBwdValImm>();
  doBasicBwdValImmTest<Find_FwdBwdValImmMut>();
  doBasicBwdValImmTest<Find_FwdBwdValSelImm>();
  doBasicBwdValImmTest<Find_FwdBwdValSelImmMut>();

  doBasicBwdValMutTest<Find_BwdValMut>();
  doBasicBwdValMutTest<Find_BwdValImmMut>();
  doBasicBwdValMutTest<Find_BwdValSelMut>();
  doBasicBwdValMutTest<Find_BwdValSelImmMut>();
  doBasicBwdValMutTest<Find_FwdBwdValMut>();
  doBasicBwdValMutTest<Find_FwdBwdValImmMut>();
  doBasicBwdValMutTest<Find_FwdBwdValSelMut>();
  doBasicBwdValMutTest<Find_FwdBwdValSelImmMut>();

  doBasicBwdSelImmTest<Find_BwdSelImm>();
  doBasicBwdSelImmTest<Find_BwdSelImmMut>();
  doBasicBwdSelImmTest<Find_BwdValSelImm>();
  doBasicBwdSelImmTest<Find_BwdValSelImmMut>();
  doBasicBwdSelImmTest<Find_FwdBwdSelImm>();
  doBasicBwdSelImmTest<Find_FwdBwdSelImmMut>();
  doBasicBwdSelImmTest<Find_FwdBwdValSelImm>();
  doBasicBwdSelImmTest<Find_FwdBwdValSelImmMut>();

  doBasicBwdSelMutTest<Find_BwdSelMut>();
  doBasicBwdSelMutTest<Find_BwdSelImmMut>();
  doBasicBwdSelMutTest<Find_BwdValSelMut>();
  doBasicBwdSelMutTest<Find_BwdValSelImmMut>();
  doBasicBwdSelMutTest<Find_FwdBwdSelMut>();
  doBasicBwdSelMutTest<Find_FwdBwdSelImmMut>();
  doBasicBwdSelMutTest<Find_FwdBwdValSelMut>();
  doBasicBwdSelMutTest<Find_FwdBwdValSelImmMut>();
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

struct B : public FindStaticBinding<B, With<Forward, Backward, Value, Selector, Immutable, Mutable>> {
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

struct B_WithAdapt : public FindStaticBinding<B_WithAdapt, With<Forward, Backward, Value, Selector, Immutable, Mutable>, FindResultTransformer<>, FindResultTransformer<>> {
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

constexpr bool evaluateFind() {
  B obj;
  auto rng = obj.find(1);
  auto it = rng.begin();

  bool lIsOne = *it == 1;
  ++it;
  bool isEnd = it == rng.end();

  auto rRng = B().find(1);
  auto rIt = rRng.begin();

  bool rIsOne = *rIt == 1;
  ++rIt;
  bool rIsEnd = rIt == rRng.end();

  return lIsOne && isEnd && rIsOne && rIsEnd;
}

constexpr bool evaluateFindFirst() {
  B obj;
  return obj.findFirst(1) == obj.begin()
      && obj.findFirst(3) == obj.end();
}

constexpr bool evaluateFindLast() {
  B obj;
  return obj.findLast(2) == obj.rbegin()
      && obj.findLast(3) == obj.rend();
}

TEST(FindStaticBinding, cpp14Constexpr) {
  static_assert(evaluateFind(), "Failed to evaluate constexpr");
  static_assert(evaluateFindFirst(), "Failed to evaluate constexpr");
  static_assert(evaluateFindLast(), "Failed to evaluate constexpr");
}
#endif
