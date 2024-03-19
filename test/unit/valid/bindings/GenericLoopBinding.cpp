// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../../src/bindings/static/GenericLoopBinding.hpp"


#include "../../../../src/bindings/static/FindStaticBinding.hpp"
#include "UnitTest.hpp"
#include <algorithm>
#include <cds/Utility>
#include <cds/iterator/AddressIterator>
#include <vector>

namespace {
using namespace cds;
using namespace cds::meta;
using namespace cds::impl;
using namespace cds::impl::sel;
using namespace cds::impl::genericLoopDeriv;

template <typename T> class Loop_Imm;
template <typename T> class Loop_Mut;
template <typename T> class Loop_ImmMut;
}

namespace cds {
namespace meta {
template <typename T> struct IterableTraits<Loop_Imm<T>> {
  using Iterator = typename std::vector<T>::const_iterator;
  using ConstIterator = typename std::vector<T>::const_iterator;
  using ReverseIterator = typename std::vector<T>::const_reverse_iterator;
  using ConstReverseIterator = typename std::vector<T>::const_reverse_iterator;
};

template <typename T> struct IterableTraits<Loop_Mut<T>> {
  using Iterator = typename std::vector<T>::iterator;
  using ConstIterator = typename std::vector<T>::const_iterator;
  using ReverseIterator = typename std::vector<T>::reverse_iterator;
  using ConstReverseIterator = typename std::vector<T>::const_reverse_iterator;
};

template <typename T> struct IterableTraits<Loop_ImmMut<T>> {
  using Iterator = typename std::vector<T>::iterator;
  using ConstIterator = typename std::vector<T>::const_iterator;
  using ReverseIterator = typename std::vector<T>::reverse_iterator;
  using ConstReverseIterator = typename std::vector<T>::const_reverse_iterator;
};
}
}

namespace {
template <typename T> class Loop_Imm :
    public std::vector<T>, public GenericLoopBinding<Loop_Imm<T>, With<Immutable>> {
public:
  using std::vector<T>::vector;
};

template <typename T> class Loop_Mut :
    public std::vector<T>, public GenericLoopBinding<Loop_Mut<T>, With<Mutable>> {
public:
  using std::vector<T>::vector;
};

template <typename T> class Loop_ImmMut :
    public std::vector<T>, public GenericLoopBinding<Loop_ImmMut<T>, With<Mutable, Immutable>> {
public:
  using std::vector<T>::vector;
};

template <typename T> void testImmInt() {
  T value {1, 2, 3, 4, 5};
  int sum = 0;
  value.forEach([&sum](int const v) { sum += v; });
  ASSERT_EQ(sum, 15);

  auto even = [](int const x) { return x % 2 == 0; };
  ASSERT_TRUE(value.some(2, even));
  ASSERT_TRUE(value.atLeast(2, even));
  ASSERT_TRUE(value.atMost(2, even));
  ASSERT_TRUE(value.moreThan(1, even));
  ASSERT_TRUE(value.lessThan(3, even));
  ASSERT_EQ(value.count(even), 2);
  ASSERT_TRUE(value.any(even));
  ASSERT_FALSE(value.all(even));
  ASSERT_FALSE(value.none(even));
}

template <typename T> void testMutInt() {
  T value {0, 0, 0, 0, 0};
  int idx = 0;
  value.forEach([&idx](int& v) { v = ++idx; });

  auto even = [](int const x) { return x % 2 == 0; };
  ASSERT_TRUE(value.some(2, even));
  ASSERT_TRUE(value.atLeast(2, even));
  ASSERT_TRUE(value.atMost(2, even));
  ASSERT_TRUE(value.moreThan(1, even));
  ASSERT_TRUE(value.lessThan(3, even));
  ASSERT_EQ(value.count(even), 2);
  ASSERT_TRUE(value.any(even));
  ASSERT_FALSE(value.all(even));
  ASSERT_FALSE(value.none(even));
}

template <typename T> void testImmStr() {
  T value {"a", "", "a", "", "a"};

  ASSERT_TRUE(value.some(2, &std::string::empty));
  ASSERT_TRUE(value.atLeast(2, &std::string::empty));
  ASSERT_TRUE(value.atMost(2, &std::string::empty));
  ASSERT_TRUE(value.moreThan(1, &std::string::empty));
  ASSERT_TRUE(value.lessThan(3, &std::string::empty));
  ASSERT_EQ(value.count(&std::string::empty), 2);
  ASSERT_TRUE(value.any(&std::string::empty));
  ASSERT_FALSE(value.all(&std::string::empty));
  ASSERT_FALSE(value.none(&std::string::empty));
}

template <typename T> void testMutStr() {
  T value {"a", "", "a", "", "a"};

  ASSERT_TRUE(value.some(2, &std::string::empty));
  ASSERT_TRUE(value.atLeast(2, &std::string::empty));
  ASSERT_TRUE(value.atMost(2, &std::string::empty));
  ASSERT_TRUE(value.moreThan(1, &std::string::empty));
  ASSERT_TRUE(value.lessThan(3, &std::string::empty));
  ASSERT_EQ(value.count(&std::string::empty), 2);
  ASSERT_TRUE(value.any(&std::string::empty));
  ASSERT_FALSE(value.all(&std::string::empty));
  ASSERT_FALSE(value.none(&std::string::empty));
}
}

TEST(GenericLoopBinding, nonMemFnPred) {
  testImmInt<Loop_Imm<int>>();
  testMutInt<Loop_Mut<int>>();

  testImmInt<Loop_ImmMut<int>>();
  testMutInt<Loop_ImmMut<int>>();

  testImmStr<Loop_Imm<std::string>>();
  testMutStr<Loop_Mut<std::string>>();

  testImmStr<Loop_ImmMut<std::string>>();
  testMutStr<Loop_ImmMut<std::string>>();
}
