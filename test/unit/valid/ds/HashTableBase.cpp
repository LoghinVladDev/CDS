// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../../src/ds/hashTable/HashTableBase.hpp"
#include "../../../../src/policy/RehashPolicy.hpp"
#include <cds/functional/Comparator>
#include <cds/functional/Hash>
#include <cds/functional/Transformer>
#include <cds/memory/Allocator>
#include "UnitTest.hpp"
#include "../Shared.hpp"

namespace {
using cds::Size;
using cds::Allocator;
using cds::AllocatorSet;
using cds::functional::Equal;
using cds::functional::Hash;
using cds::functional::impl::Identity;
using cds::impl::HashTableBase;
using cds::impl::TableRehashPolicy;
using cds::impl::PrimeRehashTable;
using cds::impl::FwdNode;

using cds::asConst;
using cds::begin;
using cds::end;
using cds::cbegin;
using cds::cend;
using cds::impl::construct;

using testing::iteq;
using testing::citeq;

template <typename T> using Node = FwdNode<T>;
template <typename T> using NodeAllocator = Allocator<Node<T>>;
template <typename T> using BucketAllocator = Allocator<Node<T>*>;
template <typename T> using HashTableAllocator
    = AllocatorSet<NodeAllocator<T>, BucketAllocator<T>>;

template <typename T, typename K, typename KP> class DefaultHashTable :
    public HashTableBase<T, K, Hash<>, TableRehashPolicy<PrimeRehashTable<>>, KP, Equal<>, HashTableAllocator<T>> {
public:
  using Base = HashTableBase<T, K, Hash<>, TableRehashPolicy<PrimeRehashTable<>>, KP, Equal<>, HashTableAllocator<T>>;
  using HashTableBase<T, K, Hash<>, TableRehashPolicy<PrimeRehashTable<>>, KP, Equal<>, HashTableAllocator<T>>::HashTableBase;
  using Base::at;
  using Base::copy;
  using Base::move;
  using Base::get;
};
}

TEST(HashTableBase, construct) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();
  auto ihs2 = DefaultHashTable<int, int, Identity<>>(Hash<>());
  (void) ihs;
  (void) ihs2;
}

TEST(HashTableBase, emplaceAndGet) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();

  ASSERT_EQ(ihs.bucketCount(), 0);
  ASSERT_EQ(ihs.size(), 0);

  ASSERT_EQ(ihs.at(1), nullptr);
  ASSERT_EQ(ihs.at(2), nullptr);
  ASSERT_EQ(asConst(ihs).at(1), nullptr);
  ASSERT_EQ(asConst(ihs).at(2), nullptr);
  ASSERT_EQ(ihs.tryEmplace(1), 1);
  ASSERT_EQ(ihs.bucketCount(), 13);
  ASSERT_EQ(ihs.size(), 1);
  ASSERT_EQ(ihs.tryEmplace(1), 1);
  ASSERT_EQ(ihs.size(), 1);
  ASSERT_NE(ihs.at(1), nullptr);
  ASSERT_EQ(ihs.at(2), nullptr);
  ASSERT_EQ(*ihs.at(1), 1);
  ASSERT_NE(asConst(ihs).at(1), nullptr);
  ASSERT_EQ(asConst(ihs).at(2), nullptr);
  ASSERT_EQ(*asConst(ihs).at(1), 1);

  ASSERT_EQ(ihs.tryEmplace(5), 5);
  ASSERT_EQ(ihs.size(), 2);

  ASSERT_EQ(ihs.tryEmplace(14), 14);
  ASSERT_EQ(ihs.tryEmplace(27), 27);
  ASSERT_EQ(ihs.size(), 4);
  ASSERT_EQ(ihs.bucketCount(), 13);

  for (int i = 50; i < 70; ++i) {
    ASSERT_EQ(ihs.tryEmplace(i), i);
  }

  ASSERT_EQ(ihs.bucketCount(), 29);
  ASSERT_EQ(ihs.size(), 24);

  ASSERT_NE(ihs.at(1), nullptr);
  ASSERT_NE(ihs.at(5), nullptr);
  ASSERT_NE(ihs.at(14), nullptr);
  ASSERT_NE(ihs.at(27), nullptr);
  ASSERT_EQ(*ihs.at(1), 1);
  ASSERT_EQ(*ihs.at(5), 5);
  ASSERT_EQ(*ihs.at(14), 14);
  ASSERT_EQ(*ihs.at(27), 27);
  ASSERT_NE(asConst(ihs).at(1), nullptr);
  ASSERT_NE(asConst(ihs).at(5), nullptr);
  ASSERT_NE(asConst(ihs).at(14), nullptr);
  ASSERT_NE(asConst(ihs).at(27), nullptr);
  ASSERT_EQ(*asConst(ihs).at(1), 1);
  ASSERT_EQ(*asConst(ihs).at(5), 5);
  ASSERT_EQ(*asConst(ihs).at(14), 14);
  ASSERT_EQ(*asConst(ihs).at(27), 27);

  for (int i = 50; i < 70; ++i) {
    ASSERT_NE(ihs.at(i), nullptr);
    ASSERT_EQ(*ihs.at(i), i);
    ASSERT_NE(asConst(ihs).at(i), nullptr);
    ASSERT_EQ(*asConst(ihs).at(i), i);
  }

  for (int i = 29; i <= 29 * 6; i += 29) {
    ASSERT_EQ(ihs.tryEmplace(i), i);
  }

  ASSERT_EQ(ihs.size(), 29);
  ASSERT_EQ(ihs.bucketCount(), 59);
}

TEST(HashTableBase, Iteration) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();
  std::vector<int> equiv;
  for (int i = 0; i < 10; ++i) {
    ihs.tryEmplace(i);
    equiv.emplace_back(i);
  }

  ASSERT_TRUE(citeq(ihs, equiv));
  ASSERT_TRUE(citeq(asConst(ihs), equiv));
  ASSERT_TRUE(iteq(ihs.begin(), ihs.end(), equiv.begin(), equiv.end()));
  ASSERT_TRUE(iteq(ihs.cbegin(), ihs.cend(), equiv.begin(), equiv.end()));
  ASSERT_TRUE(iteq(begin(ihs), end(ihs), begin(equiv), end(equiv)));
  ASSERT_TRUE(iteq(cbegin(ihs), cend(ihs), cbegin(equiv), cend(equiv)));
}

TEST(HashTableBase, copyCtr) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();
  std::vector<int> equiv;
  equiv.emplace_back(59*2);
  equiv.emplace_back(59);
  equiv.emplace_back(0);
  for (int i = 1; i < 50; ++i) {
    ihs.tryEmplace(i);
    equiv.emplace_back(i);
  }
  ihs.tryEmplace(0);
  ihs.tryEmplace(59);
  ihs.tryEmplace(59*2);

  auto ihsCopy = ihs;
  ASSERT_TRUE(citeq(ihsCopy, equiv));
  ASSERT_EQ(ihsCopy.bucketCount(), 59);

  auto eihs = DefaultHashTable<int, int, Identity<>>();
  auto eihsCopy = eihs;
  ASSERT_TRUE(eihsCopy.empty());
  ASSERT_TRUE(citeq(ihsCopy, equiv));
  ASSERT_EQ(ihsCopy.bucketCount(), 59);
}

TEST(HashTableBase, copy) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();
  std::vector<int> equiv;
  equiv.emplace_back(59*2);
  equiv.emplace_back(59);
  equiv.emplace_back(0);
  for (int i = 1; i < 50; ++i) {
    ihs.tryEmplace(i);
    equiv.emplace_back(i);
  }
  ihs.tryEmplace(0);
  ihs.tryEmplace(59);
  ihs.tryEmplace(59*2);

  auto ihsCopy = DefaultHashTable<int, int, Identity<>>();
  ihsCopy.copy(ihs);
  ihsCopy.copy(ihsCopy);
  ASSERT_TRUE(citeq(ihsCopy, equiv));
  ASSERT_EQ(ihsCopy.bucketCount(), 59);

  auto eihs = DefaultHashTable<int, int, Identity<>>();
  auto eihsCopy = DefaultHashTable<int, int, Identity<>>();
  eihsCopy.copy(eihs);
  ASSERT_TRUE(eihsCopy.empty());
  ASSERT_TRUE(citeq(ihsCopy, equiv));
  ASSERT_EQ(ihsCopy.bucketCount(), 59);
}

TEST(HashTableBase, moveCtr) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();
  std::vector<int> equiv;
  equiv.emplace_back(59*2);
  equiv.emplace_back(59);
  equiv.emplace_back(0);
  for (int i = 1; i < 50; ++i) {
    ihs.tryEmplace(i);
    equiv.emplace_back(i);
  }
  ihs.tryEmplace(0);
  ihs.tryEmplace(59);
  ihs.tryEmplace(59*2);

  auto ihsCopy = cds::move(ihs);
  ASSERT_TRUE(citeq(ihsCopy, equiv));
  ASSERT_EQ(ihsCopy.bucketCount(), 59);
  ASSERT_TRUE(ihs.empty());
  ASSERT_EQ(ihs.size(), 0);
  ASSERT_EQ(ihs.bucketCount(), 0);
}

TEST(HashTableBase, move) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();
  std::vector<int> equiv;
  equiv.emplace_back(59*2);
  equiv.emplace_back(59);
  equiv.emplace_back(0);
  for (int i = 1; i < 50; ++i) {
    ihs.tryEmplace(i);
    equiv.emplace_back(i);
  }
  ihs.tryEmplace(0);
  ihs.tryEmplace(59);
  ihs.tryEmplace(59*2);

  auto ihsCopy = DefaultHashTable<int, int, Identity<>>();
  ihsCopy.move(cds::move(ihs));
  ihsCopy.move(cds::move(ihsCopy));
  ASSERT_TRUE(citeq(ihsCopy, equiv));
  ASSERT_EQ(ihsCopy.bucketCount(), 59);
  ASSERT_TRUE(ihs.empty());
  ASSERT_EQ(ihs.size(), 0);
  ASSERT_EQ(ihs.bucketCount(), 0);
}

TEST(HashTableBase, get) {
  auto ihs = DefaultHashTable<int, int, Identity<>>();

  ASSERT_EQ(asConst(ihs).get(1), nullptr);
  auto r1 = ihs.get(1);
  ASSERT_EQ(r1.alive, false);
  ASSERT_NE(r1.data, nullptr);
  construct(r1.data, 1);
  ASSERT_NE(asConst(ihs).get(1), nullptr);
  ASSERT_EQ(*asConst(ihs).get(1), 1);

  auto r2 = ihs.get(1);
  ASSERT_EQ(r2.alive, true);
  ASSERT_EQ(*r2.data, 1);

  auto r3 = ihs.get(14);
  ASSERT_EQ(r3.alive, false);
  ASSERT_NE(r3.data, nullptr);
  construct(r3.data, 14);
  ASSERT_NE(asConst(ihs).get(14), nullptr);
  ASSERT_EQ(*asConst(ihs).get(14), 14);
  ASSERT_NE(asConst(ihs).get(1), nullptr);
  ASSERT_EQ(*asConst(ihs).get(1), 1);

  ASSERT_EQ(ihs.size(), 2);
  ASSERT_EQ(ihs.bucketCount(), 13);

  std::vector<int> equiv {14, 1};
  ASSERT_TRUE(citeq(ihs, equiv));

  for (int i = 20; i < 50; ++i) {
    auto r = ihs.get(i);
    ASSERT_EQ(r.alive, false);
    ASSERT_NE(r.data, nullptr);
    construct(r.data, i);
    ASSERT_NE(asConst(ihs).get(i), nullptr);
    ASSERT_EQ(*asConst(ihs).get(i), i);
  }

  equiv = {1, 14, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
           34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};
  ASSERT_TRUE(citeq(equiv, ihs));

  ASSERT_EQ(asConst(ihs).get(1000), nullptr);
}

#ifdef DCR_SINCECPP20
consteval auto evalConstexpr20() {
  auto ihs1 = DefaultHashTable<int, int, Identity<>>();
  auto ihs2 = DefaultHashTable<int, int, Identity<>>(Hash<>());

  ihs1.tryEmplace(1);
  ihs1.tryEmplace(2);
  ihs1.tryEmplace(3);

  bool e = ihs1.at(2) != nullptr;
  bool ev = *ihs1.at(2) == 2;
  bool ne = ihs1.at(4) == nullptr;

  std::vector<int> equiv{1, 2, 3};
  bool iseq = citeq(equiv, ihs1);
  return iseq && e && ev && ne;
}

TEST(HashTableBase, constexpr20Test) {
  static_assert(evalConstexpr20(), "Failed constexpr test");
}
#endif
