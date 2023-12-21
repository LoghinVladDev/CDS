// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/bindings/static/FindOfStaticBinding.hpp"
#include "UnitTest.hpp"
#include <initializer_list>
#include <vector>
#include <algorithm>

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

struct TCommonFwdImm : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonFwdMut : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

struct TCommonFwdImmMut : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::begin;
  using std::vector<int>::end;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonBwdImm : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
};

struct TCommonBwdMut : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
};

struct TCommonBwdImmMut : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
};

struct TCommonFwdBwdImm : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::crbegin;
  using std::vector<int>::crend;
  using std::vector<int>::cbegin;
  using std::vector<int>::cend;
};

struct TCommonFwdBwdMut : private std::vector<int> {
public:
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

struct TCommonFwdBwdImmMut : private std::vector<int> {
public:
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

class Find_FwdValImm : public TCommonFwdImm, public FindOfStaticBinding<Find_FwdValImm, With<Forward, Value, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
};

class Find_FwdValMut : public TCommonFwdMut, public FindOfStaticBinding<Find_FwdValMut, With<Forward, Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
};

class Find_FwdValImmMut : public TCommonFwdImmMut, public FindOfStaticBinding<Find_FwdValImmMut, With<Forward, Value, Mutable, Immutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
};

template <typename I, typename V, typename S>
auto lfind(I&& b, I&& e, V&& v, S&& s) noexcept -> bool {
  for (auto i = cds::forward<I>(b); i < cds::forward<I>(e); ++i) {
    if (cds::forward<S>(s)(*i) == cds::forward<V>(v)) {
      return i;
    }
  }
  return cds::forward<I>(e);
}

class Find_FwdSelImm : public TCommonFwdImm, public FindOfStaticBinding<Find_FwdSelImm, With<Forward, Selector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
};

class Find_FwdSelMut : public TCommonFwdMut, public FindOfStaticBinding<Find_FwdSelMut, With<Forward, Selector, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdSelImmMut : public TCommonFwdImmMut, public FindOfStaticBinding<Find_FwdSelImmMut, With<Forward, Selector, Immutable, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdValSelImm : public TCommonFwdImm, public FindOfStaticBinding<Find_FwdValSelImm, With<Forward, Value, Selector, Immutable>> {
public:
  using TCommonFwdImm::TCommonFwdImm;
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
};

class Find_FwdValSelMut : public TCommonFwdMut, public FindOfStaticBinding<Find_FwdValSelMut, With<Selector, Forward, Value, Mutable>> {
public:
  using TCommonFwdMut::TCommonFwdMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdValSelImmMut : public TCommonFwdImmMut, public FindOfStaticBinding<Find_FwdValSelImmMut, With<Selector, Value, Immutable, Forward, Mutable>> {
public:
  using TCommonFwdImmMut::TCommonFwdImmMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};



class Find_BwdValImm : public TCommonBwdImm, public FindOfStaticBinding<Find_BwdValImm, With<Backward, Value, Immutable>> {
public:
  using TCommonBwdImm::TCommonBwdImm;
  bool contains(int a) const { return std::find(crbegin(), crend(), a) != crend(); }
};

class Find_BwdValMut : public TCommonBwdMut, public FindOfStaticBinding<Find_BwdValMut, With<Value, Backward, Mutable>> {
public:
  using TCommonBwdMut::TCommonBwdMut;
  bool contains(int a) { return std::find(rbegin(), rend(), a) != rend(); }
};

class Find_BwdValImmMut : public TCommonBwdImmMut, public FindOfStaticBinding<Find_BwdValImmMut, With<Value, Mutable, Immutable, Backward>> {
public:
  using TCommonBwdImmMut::TCommonBwdImmMut;
  bool contains(int a) { return std::find(rbegin(), rend(), a) != rend(); }
  bool contains(int a) const { return std::find(crbegin(), crend(), a) != crend(); }
};

class Find_BwdSelImm : public TCommonBwdImm, public FindOfStaticBinding<Find_BwdSelImm, With<Backward, Selector, Immutable>> {
public:
  using TCommonBwdImm::TCommonBwdImm;
  template <typename S> bool contains(int a, S&& s) const { return lfind(crbegin(), crend(), a, cds::forward<S>(s)) != crend(); }
};

class Find_BwdSelMut : public TCommonBwdMut, public FindOfStaticBinding<Find_BwdSelMut, With<Backward, Selector, Mutable>> {
public:
  using TCommonBwdMut::TCommonBwdMut;
  template <typename S> bool contains(int a, S&& s) { return lfind(rbegin(), rend(), a, cds::forward<S>(s)) != rend(); }
};

class Find_BwdSelImmMut : public TCommonBwdImmMut, public FindOfStaticBinding<Find_BwdSelImmMut, With<Backward, Selector, Immutable, Mutable>> {
public:
  using TCommonBwdImmMut::TCommonBwdImmMut;
  template <typename S> bool contains(int a, S&& s) const { return lfind(crbegin(), crend(), a, cds::forward<S>(s)) != crend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(rbegin(), rend(), a, cds::forward<S>(s)) != rend(); }
};

class Find_BwdValSelImm : public TCommonBwdImm, public FindOfStaticBinding<Find_BwdValSelImm, With<Backward, Value, Selector, Immutable>> {
public:
  using TCommonBwdImm::TCommonBwdImm;
  bool contains(int a) const { return std::find(crbegin(), crend(), a) != crend(); }
  template <typename S> bool contains(int a, S&& s) const { return lfind(crbegin(), crend(), a, cds::forward<S>(s)) != crend(); }
};

class Find_BwdValSelMut : public TCommonBwdMut, public FindOfStaticBinding<Find_BwdValSelMut, With<Selector, Backward, Value, Mutable>> {
public:
  using TCommonBwdMut::TCommonBwdMut;
  bool contains(int a) { return std::find(rbegin(), rend(), a) != rend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(rbegin(), rend(), a, cds::forward<S>(s)) != rend(); }
};

class Find_BwdValSelImmMut : public TCommonBwdImmMut, public FindOfStaticBinding<Find_BwdValSelImmMut, With<Selector, Value, Immutable, Backward, Mutable>> {
public:
  using TCommonBwdImmMut::TCommonBwdImmMut;
  bool contains(int a) { return std::find(rbegin(), rend(), a) != rend(); }
  bool contains(int a) const { return std::find(crbegin(), crend(), a) != crend(); }
};



class Find_FwdBwdValImm : public TCommonFwdBwdImm, public FindOfStaticBinding<Find_FwdBwdValImm, With<Backward, Value, Immutable, Forward>> {
public:
  using TCommonFwdBwdImm::TCommonFwdBwdImm;
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
};

class Find_FwdBwdValMut : public TCommonFwdBwdMut, public FindOfStaticBinding<Find_FwdBwdValMut, With<Value, Forward, Backward, Mutable>> {
public:
  using TCommonFwdBwdMut::TCommonFwdBwdMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
};

class Find_FwdBwdValImmMut : public TCommonFwdBwdImmMut, public FindOfStaticBinding<Find_FwdBwdValImmMut, With<Value, Mutable, Immutable, Forward, Backward>> {
public:
  using TCommonFwdBwdImmMut::TCommonFwdBwdImmMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
};

class Find_FwdBwdSelImm : public TCommonFwdBwdImm, public FindOfStaticBinding<Find_FwdBwdSelImm, With<Backward, Selector, Forward, Immutable>> {
public:
  using TCommonFwdBwdImm::TCommonFwdBwdImm;
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
};

class Find_FwdBwdSelMut : public TCommonFwdBwdMut, public FindOfStaticBinding<Find_FwdBwdSelMut, With<Backward, Forward, Selector, Mutable>> {
public:
  using TCommonFwdBwdMut::TCommonFwdBwdMut;
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdBwdSelImmMut : public TCommonFwdBwdImmMut, public FindOfStaticBinding<Find_FwdBwdSelImmMut, With<Backward, Forward, Selector, Immutable, Mutable>> {
public:
  using TCommonFwdBwdImmMut::TCommonFwdBwdImmMut;
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdBwdValSelImm : public TCommonFwdBwdImm, public FindOfStaticBinding<Find_FwdBwdValSelImm, With<Backward, Value, Selector, Forward, Immutable>> {
public:
  using TCommonFwdBwdImm::TCommonFwdBwdImm;
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
};

class Find_FwdBwdValSelMut : public TCommonFwdBwdMut, public FindOfStaticBinding<Find_FwdBwdValSelMut, With<Selector, Forward, Backward, Value, Mutable>> {
public:
  using TCommonFwdBwdMut::TCommonFwdBwdMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

class Find_FwdBwdValSelImmMut : public TCommonFwdBwdImmMut, public FindOfStaticBinding<Find_FwdBwdValSelImmMut, With<Selector, Value, Immutable, Backward, Forward, Mutable>> {
public:
  using TCommonFwdBwdImmMut::TCommonFwdBwdImmMut;
  bool contains(int a) { return std::find(begin(), end(), a) != end(); }
  bool contains(int a) const { return std::find(cbegin(), cend(), a) != cend(); }
  template <typename S> bool contains(int a, S&& s) const { return lfind(cbegin(), cend(), a, cds::forward<S>(s)) != cend(); }
  template <typename S> bool contains(int a, S&& s) { return lfind(begin(), end(), a, cds::forward<S>(s)) != end(); }
};

int doubled(int v) { return v * 2; }

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
  ASSERT_EQ(obj.findLastOf(T({4})), obj.crend());
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1})), 2);
  ASSERT_EQ(obj.findLastNotOf(T({3, 1, 2})), obj.crend());
}

template <typename T> void doBasicBwdValMutTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(*obj.findLastOf(T({3, 1})), 3);
  ASSERT_EQ(obj.findLastOf(T({4})), obj.rend());
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1})), 2);
  ASSERT_EQ(obj.findLastNotOf(T({3, 1, 2})), obj.rend());
}

template <typename T> void doBasicBwdSelImmTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(obj.findLastOf(T({3, 1}), doubled), obj.crend());
  ASSERT_EQ(*obj.findLastOf(T({4}), doubled), 2);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1}), doubled), 3);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1, 2}), doubled), 3);
  ASSERT_EQ(obj.findLastNotOf(T({2, 4, 6}), doubled), obj.crend());
}

template <typename T> void doBasicBwdSelMutTest() {
  T obj({1, 2, 3});
  ASSERT_EQ(obj.findLastOf(T({3, 1}), doubled), obj.rend());
  ASSERT_EQ(*obj.findLastOf(T({4}), doubled), 2);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1}), doubled), 3);
  ASSERT_EQ(*obj.findLastNotOf(T({3, 1, 2}), doubled), 3);
  ASSERT_EQ(obj.findLastNotOf(T({2, 4, 6}), doubled), obj.rend());
}

TEST(FindOfStaticBinding, findOf) {
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

struct B : public FindOfStaticBinding<B, With<Forward, Backward, Value, Selector, Immutable, Mutable>> {
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

  int data[4] = {0, 1, 2, 0}; // padding to allow first and last elem to allow constexpr
};

namespace cds {
namespace impl {
template <> struct FindOfResultMappingTraits<B_WithAdapt> {
  template <typename T, meta::EnableIf<meta::impl::IsIterator<T>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto adapt(B_WithAdapt const& string, T&& iterator) -> Idx;
  template <typename T, meta::EnableIf<meta::impl::IsReverseIterator<T>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto adapt(B_WithAdapt const& string, T&& iterator) -> Idx;
};
}
}

struct B_WithAdapt : public FindOfStaticBinding<B_WithAdapt, With<Forward, Backward, Value, Selector, Immutable, Mutable>> {
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

  int data[4] = {0, 1, 2, 0}; // padding to allow first and last elem to allow constexpr
};

namespace cds {
namespace impl {
template <typename T, meta::EnableIf<meta::impl::IsIterator<T>>>
CDS_ATTR(constexpr(11)) auto FindOfResultMappingTraits<B_WithAdapt>::adapt(B_WithAdapt const& string, T&& iterator) -> Idx {
  return cend(string) == cds::forward<T>(iterator)
      ? -1
      : (cds::forward<T>(iterator) - cbegin(string));
}

template <typename T, meta::EnableIf<meta::impl::IsReverseIterator<T>>>
CDS_ATTR(constexpr(11)) auto FindOfResultMappingTraits<B_WithAdapt>::adapt(B_WithAdapt const& string, T&& iterator) -> Idx {
  return crend(string) == cds::forward<T>(iterator)
      ? -1
      : (2 - (cds::forward<T>(iterator) - crbegin(string) + 1));
}
}
}

constexpr int cdoubled(int x) { return x * 2; }
constexpr bool evaluationCtx() {
  B obj;
  return
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
      obj.findLastNotOf(B()) == obj.rend() &&
      obj.findLastNotOf(B()) == obj.rend() &&
      *obj.findLastNotOf(B(), cdoubled) == 2 &&
      *obj.findLastNotOf(B(), &cdoubled) == 2;
}

TEST(FindOfStaticBinding, cpp14Constexpr) {
  B_WithAdapt x;
  static_assert(evaluationCtx(), "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findFirstOf(B_WithAdapt()) == 0, "Failed to evaluate constexpr");
  static_assert(B_WithAdapt().findLastOf(B_WithAdapt()) == 1, "Failed to evaluate constexpr");
}
#endif
