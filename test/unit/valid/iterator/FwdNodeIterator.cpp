// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/iterator/FwdNodeIterator>
#include "UnitTest.hpp"

namespace {
using cds::impl::FwdNode;
using cds::iterator::FwdNodeIterator;
} // namespace

TEST(FwdNodeIterator, parse) {
  FwdNode<int> n4 {nullptr, 4};
  FwdNode<int> n3 {&n4, 3};
  FwdNode<int> n2 {&n3, 2};
  FwdNode<int> n1 {&n2, 1};

  FwdNodeIterator<int> emptyIt;
  ASSERT_EQ(emptyIt, FwdNodeIterator<int>{nullptr});

  FwdNodeIterator<int> it{&n1};
  FwdNodeIterator<int> end;
  ASSERT_NE(it, end);
  ASSERT_EQ(*it, 1);
  ++it;

  ASSERT_NE(it, end);
  ASSERT_EQ(*it, 2);
  ++it;

  ASSERT_NE(it, end);
  ASSERT_EQ(*it, 3);
  ++it;

  ASSERT_NE(it, end);
  ASSERT_EQ(*it, 4);
  ++it;

  ASSERT_EQ(it, end);

  FwdNodeIterator<int> it2{&n1};
  it = it2;
  ASSERT_EQ(it, it2);
  ASSERT_NE(it, end);
  ASSERT_NE(it2, end);
  ++it;
  (void) it2++;
  ASSERT_EQ(it, it2);
  ASSERT_NE(it, end);
  ASSERT_NE(it2, end);
  ++it;
  (void) it2++;
  ASSERT_EQ(it, it2);
  ASSERT_NE(it, end);
  ASSERT_NE(it2, end);
  ++it;
  (void) it2++;
  ASSERT_EQ(it, it2);
  ASSERT_NE(it, end);
  ASSERT_NE(it2, end);
  ++it;
  (void) it2++;
  ASSERT_EQ(it, it2);
  ASSERT_EQ(it, end);
  ASSERT_EQ(it2, end);
}

TEST(FwdNodeIterator, addr) {
  FwdNode<std::string> strNode{nullptr, "abcd"};
  FwdNodeIterator<std::string> const strNodeIt{&strNode};
  ASSERT_EQ(strNodeIt->length(), 4);
}
