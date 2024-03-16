// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include "../../../../src/ds/linkedList/SingleLinkedListBase.hpp"
#include "../Shared.hpp"
#include "UnitTest.hpp"
#include "cds/Utility"
#include <cds/memory/Allocator>

namespace {
using cds::impl::SingleLinkedListBase;
using cds::functional::Equal;
using cds::Allocator;
using cds::impl::FwdNode;
using cds::asConst;
template <typename T> class SLL : public SingleLinkedListBase<T, Equal<>, Allocator<FwdNode<T>>> {
  using Base = SingleLinkedListBase<T, Equal<>, Allocator<FwdNode<T>>>;
public:
  using Base::front;
  using Base::back;
  using Base::copy;
  using Base::move;
};
} // namespace

TEST(SingleLinkedListBase, construct) {
  SLL<int> l;
  l.emplaceBack(1);
  l.emplaceBack(2);
  l.emplaceBack(3);
  l.emplaceFront(2);
  l.emplaceFront(3);

  ASSERT_TRUE(testing::citeq(l, std::vector<int>{3, 2, 1, 2, 3}));

  auto c = l;
  ASSERT_TRUE(testing::citeq(l, std::vector<int>{3, 2, 1, 2, 3}));
  ASSERT_TRUE(testing::citeq(c, std::vector<int>{3, 2, 1, 2, 3}));

  auto m = std::move(c);
  ASSERT_TRUE(testing::citeq(l, std::vector<int>{3, 2, 1, 2, 3}));
  ASSERT_TRUE(testing::citeq(c, std::vector<int>{}));
  ASSERT_TRUE(testing::citeq(m, std::vector<int>{3, 2, 1, 2, 3}));
}

TEST(SingleLinkedListBase, constIt) {
  SLL<int> l;
  l.emplaceBack(1);
  l.emplaceBack(2);
  l.emplaceBack(3);
  l.emplaceFront(2);
  l.emplaceFront(3);

  ASSERT_TRUE(testing::citeq(asConst(l), std::vector<int>{3, 2, 1, 2, 3}));
  auto equiv = std::vector<int>{3, 2, 1, 2, 3};
  ASSERT_TRUE(testing::iteq(l.begin(), l.end(), equiv.begin(), equiv.end()));
  ASSERT_TRUE(testing::iteq(asConst(l).begin(), asConst(l).end(), equiv.begin(), equiv.end()));
  ASSERT_TRUE(testing::iteq(asConst(l).cbegin(), asConst(l).cend(), equiv.begin(), equiv.end()));
}

TEST(SingleLinkedListBase, frontBack) {
  SLL<int> l;
  ASSERT_EQ(l.front(), nullptr);
  ASSERT_EQ(l.back(), nullptr);
  ASSERT_EQ(asConst(l).front(), nullptr);
  ASSERT_EQ(asConst(l).back(), nullptr);

  l.emplaceBack(1);
  l.emplaceBack(2);
  l.emplaceBack(3);

  ASSERT_NE(l.front(), nullptr);
  ASSERT_NE(l.back(), nullptr);
  ASSERT_NE(asConst(l).front(), nullptr);
  ASSERT_NE(asConst(l).back(), nullptr);
  ASSERT_EQ(*l.front(), 1);
  ASSERT_EQ(*l.back(), 3);
  ASSERT_EQ(*asConst(l).front(), 1);
  ASSERT_EQ(*asConst(l).back(), 3);
}

TEST(SingleLinkedListBase, copyMove) {
  SLL<int> l;
  l.emplaceBack(1);
  l.emplaceBack(2);
  l.emplaceBack(3);

  ASSERT_TRUE(testing::citeq(l, std::vector<int>{1, 2, 3}));

  SLL<int> c;
  c.copy(l);
  c.copy(c);
  ASSERT_TRUE(testing::citeq(l, std::vector<int>{1, 2, 3}));
  ASSERT_TRUE(testing::citeq(c, std::vector<int>{1, 2, 3}));

  SLL<int> m;
  m.move(std::move(c));
  ASSERT_TRUE(testing::citeq(l, std::vector<int>{1, 2, 3}));
  ASSERT_TRUE(testing::citeq(m, std::vector<int>{1, 2, 3}));
  ASSERT_TRUE(testing::citeq(c, std::vector<int>{}));

  m.move(std::move(m));
  ASSERT_TRUE(testing::citeq(m, std::vector<int>{1, 2, 3}));
}

TEST(SingleLinkedListBase, pop) {
  SLL<int> l;
  ASSERT_TRUE(l.empty());
  l.pop();
  ASSERT_TRUE(l.empty());

  l.emplaceBack(1);
  l.emplaceBack(2);
  l.emplaceBack(3);

  ASSERT_FALSE(l.empty());
  l.pop();
  ASSERT_FALSE(l.empty());
  l.pop();
  ASSERT_FALSE(l.empty());
  l.pop();
  ASSERT_TRUE(l.empty());
  l.pop();
  ASSERT_TRUE(l.empty());
}

#ifdef DCR_SINCECPP20
namespace {
consteval auto cexpr20eval() {
  SLL<int> sll;
  auto const empty = sll.empty();
  sll.emplaceBack(1);
  sll.emplaceBack(2);
  sll.emplaceBack(3);

  auto const nempty = !sll.empty();

  return empty && nempty;
}
}

TEST(SingleLinkedListBase, constexpr20) {
  static_assert(cexpr20eval(), "failed constexpr test");
}
#endif
