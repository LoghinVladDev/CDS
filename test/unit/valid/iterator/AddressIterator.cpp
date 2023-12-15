// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "cds/iterator/AddressIterator"
#include "UnitTest.hpp"

using namespace cds;

TEST(AddressIterator, constructionFwdParse) {
  int data[3] = {1, 2, 3};
  auto b1 = begin(data);
  auto e1 = end(data);
  ASSERT_NE(b1, e1);
  ASSERT_EQ(*b1, 1);
  ++ b1;
  ASSERT_NE(b1, e1);
  ASSERT_EQ(*b1, 2);
  ++ b1;
  ASSERT_NE(b1, e1);
  ASSERT_EQ(*b1, 3);
  ++ b1;
  ASSERT_EQ(b1, e1);

  static_assert(meta::IsSame<decltype(b1)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(b1)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(b1)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(decltype(b1)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(e1)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(e1)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(e1)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(decltype(e1)::forward, "Wrong forward");

  int const cdata[3] = {1, 2, 3};
  auto cb1 = begin(cdata);
  auto ce1 = end(cdata);
  ASSERT_NE(cb1, ce1);
  ASSERT_EQ(*cb1, 1);
  ++ cb1;
  ASSERT_NE(cb1, ce1);
  ASSERT_EQ(*cb1, 2);
  ++ cb1;
  ASSERT_NE(cb1, ce1);
  ASSERT_EQ(*cb1, 3);
  ++ cb1;
  ASSERT_EQ(cb1, ce1);

  static_assert(meta::IsSame<decltype(cb1)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(cb1)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(cb1)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(decltype(cb1)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(ce1)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(ce1)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(ce1)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(decltype(ce1)::forward, "Wrong forward");

  auto cb2 = begin(data);
  auto ce2 = cend(data);
  ASSERT_NE(cb2, ce2);
  ASSERT_EQ(*cb2, 1);
  ++ cb2;
  ASSERT_NE(cb2, ce2);
  ASSERT_EQ(*cb2, 2);
  ++ cb2;
  ASSERT_NE(cb2, ce2);
  ASSERT_EQ(*cb2, 3);
  ++ cb2;
  ASSERT_EQ(cb2, ce2);

  static_assert(meta::IsSame<decltype(cb2)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(cb2)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(cb2)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(decltype(cb2)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(ce2)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(ce2)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(ce2)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(decltype(ce2)::forward, "Wrong forward");

  auto cb3 = cbegin(data);
  auto ce3 = end(data);
  ASSERT_NE(cb3, ce3);
  ASSERT_EQ(*cb3, 1);
  ++ cb3;
  ASSERT_NE(cb3, ce3);
  ASSERT_EQ(*cb3, 2);
  ++ cb3;
  ASSERT_NE(cb3, ce3);
  ASSERT_EQ(*cb3, 3);
  ++ cb3;
  ASSERT_EQ(cb3, ce3);

  static_assert(meta::IsSame<decltype(cb3)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(cb3)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(cb3)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(decltype(cb3)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(ce3)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(ce3)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(ce3)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(decltype(ce3)::forward, "Wrong forward");
}

TEST(AddressIterator, constructionBwdParse) {
  int data[3] = {1, 2, 3};
  auto b1 = rbegin(data);
  auto e1 = rend(data);
  ASSERT_NE(b1, e1);
  ASSERT_EQ(*b1, 3);
  ++ b1;
  ASSERT_NE(b1, e1);
  ASSERT_EQ(*b1, 2);
  ++ b1;
  ASSERT_NE(b1, e1);
  ASSERT_EQ(*b1, 1);
  ++ b1;
  ASSERT_EQ(b1, e1);

  static_assert(meta::IsSame<decltype(b1)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(b1)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(b1)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(!decltype(b1)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(e1)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(e1)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(e1)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(!decltype(e1)::forward, "Wrong forward");

  int const cdata[3] = {1, 2, 3};
  auto cb1 = rbegin(cdata);
  auto ce1 = rend(cdata);
  ASSERT_NE(cb1, ce1);
  ASSERT_EQ(*cb1, 3);
  ++ cb1;
  ASSERT_NE(cb1, ce1);
  ASSERT_EQ(*cb1, 2);
  ++ cb1;
  ASSERT_NE(cb1, ce1);
  ASSERT_EQ(*cb1, 1);
  ++ cb1;
  ASSERT_EQ(cb1, ce1);

  static_assert(meta::IsSame<decltype(cb1)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(cb1)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(cb1)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(!decltype(cb1)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(ce1)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(ce1)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(ce1)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(!decltype(ce1)::forward, "Wrong forward");

  auto cb2 = rbegin(data);
  auto ce2 = crend(data);
  ASSERT_NE(cb2, ce2);
  ASSERT_EQ(*cb2, 3);
  ++ cb2;
  ASSERT_NE(cb2, ce2);
  ASSERT_EQ(*cb2, 2);
  ++ cb2;
  ASSERT_NE(cb2, ce2);
  ASSERT_EQ(*cb2, 1);
  ++ cb2;
  ASSERT_EQ(cb2, ce2);

  static_assert(meta::IsSame<decltype(cb2)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(cb2)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(cb2)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(!decltype(cb2)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(ce2)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(ce2)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(ce2)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(!decltype(ce2)::forward, "Wrong forward");

  auto cb3 = crbegin(data);
  auto ce3 = rend(data);
  ASSERT_NE(cb3, ce3);
  ASSERT_EQ(*cb3, 3);
  ++ cb3;
  ASSERT_NE(cb3, ce3);
  ASSERT_EQ(*cb3, 2);
  ++ cb3;
  ASSERT_NE(cb3, ce3);
  ASSERT_EQ(*cb3, 1);
  ++ cb3;
  ASSERT_EQ(cb3, ce3);

  static_assert(meta::IsSame<decltype(cb3)::Value, int const>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(cb3)::Address, int const*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(cb3)::Reference, int const&>::value, "Wrong ReferenceType");
  static_assert(!decltype(cb3)::forward, "Wrong forward");
  static_assert(meta::IsSame<decltype(ce3)::Value, int>::value, "Wrong ValueType");
  static_assert(meta::IsSame<decltype(ce3)::Address, int*>::value, "Wrong AddressType");
  static_assert(meta::IsSame<decltype(ce3)::Reference, int&>::value, "Wrong ReferenceType");
  static_assert(!decltype(ce3)::forward, "Wrong forward");
}

TEST(AddressIterator, Access) {
  std::string const arr[3] = {"a", "bb", "ccc"};
  auto b = cds::begin(arr);
  auto e = cds::end(arr);

  ASSERT_NE(b, e);
  ASSERT_EQ(*b, "a");
  ASSERT_EQ(b->size(), 1);
  ++b;

  ASSERT_NE(b, e);
  ASSERT_EQ(*b, "bb");
  ASSERT_EQ(b->size(), 2);
  ++b;

  ASSERT_NE(b, e);
  ASSERT_EQ(*b, "ccc");
  ASSERT_EQ(b->size(), 3);
  ++b;
  ASSERT_EQ(b, e);
}

TEST(AddressIterator, Comparison) {
  int data[3] = {1, 2, 3};
  auto first = begin(data);
  auto second = first;
  ++ second;
  auto third = second;
  ++ third;

  ASSERT_FALSE(first < first);
  ASSERT_LT(first, second);
  ASSERT_LT(first, third);
  ASSERT_FALSE(second < first);
  ASSERT_FALSE(second < second);
  ASSERT_LT(second, third);
  ASSERT_FALSE(third < first);
  ASSERT_FALSE(third < second);
  ASSERT_FALSE(third < third);

  ASSERT_LE(first, first);
  ASSERT_LE(first, second);
  ASSERT_LE(first, third);
  ASSERT_FALSE(second <= first);
  ASSERT_LE(second, second);
  ASSERT_LE(second, third);
  ASSERT_FALSE(third <= first);
  ASSERT_FALSE(third <= second);
  ASSERT_LE(third, third);

  ASSERT_GT(third, first);
  ASSERT_GT(third, second);
  ASSERT_FALSE(third > third);
  ASSERT_GT(second, first);
  ASSERT_FALSE(second > second);
  ASSERT_FALSE(second > third);
  ASSERT_FALSE(first > first);
  ASSERT_FALSE(first > second);
  ASSERT_FALSE(first > third);

  ASSERT_GE(first, first);
  ASSERT_FALSE(first >= second);
  ASSERT_FALSE(first >= third);
  ASSERT_GE(second, first);
  ASSERT_GE(second, second);
  ASSERT_FALSE(second >= third);
  ASSERT_GE(third, first);
  ASSERT_GE(third, second);
  ASSERT_GE(third, third);
}

TEST(AddressIterator, RComparison) {
  int data[3] = {1, 2, 3};
  auto first = rbegin(data);
  auto second = first;
  ++ second;
  auto third = second;
  ++ third;

  ASSERT_FALSE(first < first);
  ASSERT_LT(first, second);
  ASSERT_LT(first, third);
  ASSERT_FALSE(second < first);
  ASSERT_FALSE(second < second);
  ASSERT_LT(second, third);
  ASSERT_FALSE(third < first);
  ASSERT_FALSE(third < second);
  ASSERT_FALSE(third < third);

  ASSERT_LE(first, first);
  ASSERT_LE(first, second);
  ASSERT_LE(first, third);
  ASSERT_FALSE(second <= first);
  ASSERT_LE(second, second);
  ASSERT_LE(second, third);
  ASSERT_FALSE(third <= first);
  ASSERT_FALSE(third <= second);
  ASSERT_LE(third, third);

  ASSERT_GT(third, first);
  ASSERT_GT(third, second);
  ASSERT_FALSE(third > third);
  ASSERT_GT(second, first);
  ASSERT_FALSE(second > second);
  ASSERT_FALSE(second > third);
  ASSERT_FALSE(first > first);
  ASSERT_FALSE(first > second);
  ASSERT_FALSE(first > third);

  ASSERT_GE(first, first);
  ASSERT_FALSE(first >= second);
  ASSERT_FALSE(first >= third);
  ASSERT_GE(second, first);
  ASSERT_GE(second, second);
  ASSERT_FALSE(second >= third);
  ASSERT_GE(third, first);
  ASSERT_GE(third, second);
  ASSERT_GE(third, third);
}

TEST(AddressIterator, ItDiff) {
  int data[3] = {1, 2, 3};
  auto b = begin(data);
  auto e = end(data);
  auto rb = rbegin(data);
  auto re = rend(data);

  ASSERT_EQ(b - e, 3);
  ASSERT_EQ(e - b, 3);
  ++b;
  ASSERT_EQ(b - e, 2);
  ASSERT_EQ(e - b, 2);
  --e;
  ASSERT_EQ(b - e, 1);
  ASSERT_EQ(e - b, 1);
  ++b;
  ASSERT_EQ(b - e, 0);
  ASSERT_EQ(e - b, 0);
  --e;
  ASSERT_EQ(b - e, 1);
  ASSERT_EQ(e - b, 1);

  ASSERT_EQ(rb - re, 3);
  ASSERT_EQ(re - rb, 3);
  ++rb;
  ASSERT_EQ(rb - re, 2);
  ASSERT_EQ(re - rb, 2);
  --re;
  ASSERT_EQ(rb - re, 1);
  ASSERT_EQ(re - rb, 1);
  ++rb;
  ASSERT_EQ(rb - re, 0);
  ASSERT_EQ(re - rb, 0);
  --re;
  ASSERT_EQ(rb - re, 1);
  ASSERT_EQ(re - rb, 1);
}

TEST(AddressIterator, ItPost) {
  int data[3] = {1, 2, 3};
  auto b = begin(data);
  auto e = end(data);
  auto rb = rbegin(data);
  auto re = rend(data);

  ASSERT_EQ(*b, 1);
  ASSERT_NE(b, e);
  ASSERT_EQ(*(b++), 1);
  ASSERT_EQ(*b, 2);
  ASSERT_NE(b, e);
  ASSERT_EQ(*(b++), 2);
  ASSERT_EQ(*b, 3);
  ASSERT_NE(b, e);
  ASSERT_EQ(*(b++), 3);
  ASSERT_EQ(b--, e);
  ASSERT_NE(b, e);
  ASSERT_EQ(*(b--), 3);
  ASSERT_NE(b, e);
  ASSERT_EQ(*(b--), 2);
  ASSERT_NE(b, e);
  ASSERT_EQ(b, begin(data));
  ASSERT_EQ(*(b--), 1);

  ASSERT_EQ(*rb, 3);
  ASSERT_NE(rb, re);
  ASSERT_EQ(*(rb++), 3);
  ASSERT_EQ(*rb, 2);
  ASSERT_NE(rb, re);
  ASSERT_EQ(*(rb++), 2);
  ASSERT_EQ(*rb, 1);
  ASSERT_NE(rb, re);
  ASSERT_EQ(*(rb++), 1);
  ASSERT_EQ(rb--, re);
  ASSERT_NE(rb, re);
  ASSERT_EQ(*(rb--), 1);
  ASSERT_NE(rb, re);
  ASSERT_EQ(*(rb--), 2);
  ASSERT_NE(rb, re);
  ASSERT_EQ(rb, rbegin(data));
  ASSERT_EQ(*(rb--), 3);
}

TEST(AddressIterator, ItSkip) {
  int data[3] = {1, 2, 3};
  auto b = begin(data);
  auto e = end(data);
  auto rb = rbegin(data);
  auto re = rend(data);

  ASSERT_EQ((b + 0), b);
  ASSERT_NE(b + 0, e);
  ASSERT_EQ(*(b + 0), 1);
  ASSERT_NE(b + 1, e);
  ASSERT_EQ(*(b + 1), 2);
  ASSERT_NE(b + 2, e);
  ASSERT_EQ(*(b + 2), 3);
  ASSERT_EQ(b + 3, e);

  ASSERT_EQ(e - 0, e);
  ASSERT_NE(e - 1, e);
  ASSERT_NE(e - 1, b);
  ASSERT_EQ(*(e - 1), 3);
  ASSERT_NE(e - 2, b);
  ASSERT_EQ(*(e - 2), 2);
  ASSERT_EQ(e - 3, b);
  ASSERT_EQ(*(e - 3), 1);

  ASSERT_EQ((rb + 0), rb);
  ASSERT_NE(rb + 0, re);
  ASSERT_EQ(*(rb + 0), 3);
  ASSERT_NE(rb + 1, re);
  ASSERT_EQ(*(rb + 1), 2);
  ASSERT_NE(rb + 2, re);
  ASSERT_EQ(*(rb + 2), 1);
  ASSERT_EQ(rb + 3, re);

  ASSERT_EQ(re - 0, re);
  ASSERT_NE(re - 1, re);
  ASSERT_NE(re - 1, rb);
  ASSERT_EQ(*(re - 1), 1);
  ASSERT_NE(re - 2, rb);
  ASSERT_EQ(*(re - 2), 2);
  ASSERT_EQ(re - 3, rb);
  ASSERT_EQ(*(re - 3), 3);
}

TEST(AddressIterator, subscript) {
  int data[3] = {1, 2, 3};
  auto b = begin(data);

  ASSERT_EQ(b[0], data[0]);
  ASSERT_EQ(b[1], data[1]);
  ASSERT_EQ(b[2], data[2]);
  ++ b;
  ASSERT_EQ(b[0], data[1]);
  ASSERT_EQ(b[1], data[2]);
  ++ b;
  ASSERT_EQ(b[0], data[2]);
}

#ifdef DCR_SINCECPP11
struct F {
  constexpr F() = default;
  constexpr bool f() const noexcept { return true; }
};

TEST(AddressIterator, compileTimeCpp11) {
  constexpr int data[3] = {1, 2, 3};
  constexpr F fdata[3] = {F(), F(), F()};
  static_assert(ForwardAddressIterator<int>() == ForwardAddressIterator<int>(), "Failed Cpp11 Compile Time Test");
  static_assert(*begin(data) == 1, "Failed Cpp11 Compile Time Test");
  static_assert(*ForwardAddressIterator<int const>(begin(data)) == 1, "Failed Cpp11 Compile Time Test");
  static_assert(*ForwardAddressIterator<int const>(std::move(begin(data))) == 1, "Failed Cpp11 Compile Time Test");
  static_assert(begin(fdata)->f(), "Failed Cpp11 Compile Time Test");
  static_assert(begin(data)[1] == data[1], "Failed Cpp11 Compile Time Test");
  static_assert(begin(data) == begin(data), "Failed Cpp11 Compile Time Test");
  static_assert(begin(data) != end(data), "Failed Cpp11 Compile Time Test");
  static_assert(begin(data) < end(data), "Failed Cpp11 Compile Time Test");
  static_assert(begin(data) <= end(data), "Failed Cpp11 Compile Time Test");
  static_assert(begin(data) <= begin(data), "Failed Cpp11 Compile Time Test");
  static_assert(end(data) > begin(data), "Failed Cpp11 Compile Time Test");
  static_assert(end(data) >= begin(data), "Failed Cpp11 Compile Time Test");
  static_assert(end(data) >= end(data), "Failed Cpp11 Compile Time Test");
  static_assert(end(data) - begin(data) == 3, "Failed Cpp11 Compile Time Test");
  static_assert(begin(data) + 3 == end(data), "Failed Cpp11 Compile Time Test");
  static_assert(end(data) - 3 == begin(data), "Failed Cpp11 Compile Time Test");
}
#endif

#ifdef DCR_SINCECPP14
constexpr bool validateCpp14CompileTime() {
  int data[3] = {1, 2, 3};

  auto b1 = begin(data);
  bool preIncValid =
      ++b1 != begin(data) &&
      ++b1 != begin(data) &&
      ++b1 != begin(data) &&
      b1 == end(data);

  auto b2 = begin(data);
  bool preDecValid =
      b2++ == begin(data) &&
      b2++ != begin(data) &&
      b2++ != begin(data) &&
      b2 == end(data);

  auto e1 = end(data);
  bool postIncValid =
      --e1 != end(data) &&
      --e1 != end(data) &&
      --e1 != end(data) &&
      e1 == begin(data);

  auto e2 = end(data);
  bool postDecValid =
      e2-- == end(data) &&
      e2-- != end(data) &&
      e2-- != end(data) &&
      e2 == begin(data);

  return preIncValid && preDecValid && postIncValid && postDecValid;
}

TEST(AddressIterator, compileTimeCpp14) {
  static_assert(validateCpp14CompileTime(), "Failed Cpp14 Compile Time Test");
}
#endif

#ifdef DCR_SINCECPP20
TEST(AddressIterator, Spaceship) {
  int data[3] = {1, 2, 3};
  auto first = begin(data);
  auto second = first;
  ++ second;
  auto third = second;
  ++ third;

  auto r11 = first <=> first;
  auto r12 = first <=> second;
  auto r13 = first <=> third;
  auto r21 = second <=> first;
  auto r22 = second <=> second;
  auto r23 = second <=> third;
  auto r31 = third <=> first;
  auto r32 = third <=> second;
  auto r33 = third <=> third;

  ASSERT_EQ(r11, std::strong_ordering::equal);
  ASSERT_EQ(r12, std::strong_ordering::less);
  ASSERT_EQ(r13, std::strong_ordering::less);

  ASSERT_EQ(r21, std::strong_ordering::greater);
  ASSERT_EQ(r22, std::strong_ordering::equal);
  ASSERT_EQ(r23, std::strong_ordering::less);

  ASSERT_EQ(r31, std::strong_ordering::greater);
  ASSERT_EQ(r32, std::strong_ordering::greater);
  ASSERT_EQ(r33, std::strong_ordering::equal);
}

TEST(AddressIterator, RSpaceship) {
  int data[3] = {1, 2, 3};
  auto first = rbegin(data);
  auto second = first;
  ++ second;
  auto third = second;
  ++ third;

  auto r11 = first <=> first;
  auto r12 = first <=> second;
  auto r13 = first <=> third;
  auto r21 = second <=> first;
  auto r22 = second <=> second;
  auto r23 = second <=> third;
  auto r31 = third <=> first;
  auto r32 = third <=> second;
  auto r33 = third <=> third;

  ASSERT_EQ(r11, std::strong_ordering::equal);
  ASSERT_EQ(r12, std::strong_ordering::less);
  ASSERT_EQ(r13, std::strong_ordering::less);

  ASSERT_EQ(r21, std::strong_ordering::greater);
  ASSERT_EQ(r22, std::strong_ordering::equal);
  ASSERT_EQ(r23, std::strong_ordering::less);

  ASSERT_EQ(r31, std::strong_ordering::greater);
  ASSERT_EQ(r32, std::strong_ordering::greater);
  ASSERT_EQ(r33, std::strong_ordering::equal);
}

TEST(AddressIterator, compileTimeCpp20) {
  constexpr int data[3] = {1, 2, 3};
  static_assert((begin(data) <=> begin(data)) == std::strong_ordering::equal, "Failed Cpp20 Compile Time Test");
  static_assert((begin(data) <=> end(data)) == std::strong_ordering::less, "Failed Cpp20 Compile Time Test");
  static_assert((end(data) <=> begin(data)) == std::strong_ordering::greater, "Failed Cpp20 Compile Time Test");
  static_assert((end(data) <=> end(data)) == std::strong_ordering::equal, "Failed Cpp20 Compile Time Test");
}
#endif
