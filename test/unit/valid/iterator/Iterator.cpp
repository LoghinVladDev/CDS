// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/iterator/Iterator>
#include "UnitTest.hpp"
#include <cds/StringView>

using namespace cds;

TEST(Iterator, IsIterable) {
  static_assert(meta::IsIterable<int[10]>::value, "Failed is iterable");
  static_assert(meta::IsIterable<std::string>::value, "Failed is iterable");
  static_assert(meta::IsIterable<std::vector<int>>::value, "Failed is iterable");
  static_assert(meta::IsIterable<StringView>::value, "Failed is iterable");
  static_assert(meta::IsIterable<StringView>::value, "Failed is iterable");
  struct noend { CDS_ATTR(nodiscard) int const* begin() const { (void)this; return nullptr; } };
  struct correct { CDS_ATTR(nodiscard) int const* begin() const { (void)this;return nullptr; } CDS_ATTR(nodiscard) int const* end() const { (void)this;return nullptr; } };
  static_assert(!meta::IsIterable<noend>::value, "Failed is iterable");
  static_assert(meta::IsIterable<correct>::value, "Failed is iterable");
  static_assert(!meta::IsIterable<int*>::value, "Failed is iterable");
}

TEST(Iterator, IsReverseIterable) {
  static_assert(meta::IsReverseIterable<int[10]>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<std::string>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<std::vector<int>>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<StringView>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<StringView>::value, "Failed is iterable");
  struct noend { CDS_ATTR(nodiscard)int const* rbegin() const { (void)this;return nullptr; } };
  struct correct { CDS_ATTR(nodiscard)int const* rbegin() const { (void)this;return nullptr; } CDS_ATTR(nodiscard)int const* rend() const { (void)this;return nullptr; } };
  static_assert(!meta::IsReverseIterable<noend>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<correct>::value, "Failed is iterable");
  static_assert(!meta::IsReverseIterable<int*>::value, "Failed is iterable");
}

TEST(Iterator, iterable) {
  struct Iterable {
    int* begin() { return data; }
    int* end() { return data + 2; }
    CDS_ATTR(nodiscard)int const* cbegin() const { return data; }
    CDS_ATTR(nodiscard)int const* cend() const { return data + 2; }
    int* rbegin() { return data + 1; }
    int* rend() { return data - 1; }
    CDS_ATTR(nodiscard)int const* crbegin() const { return data + 1; }
    CDS_ATTR(nodiscard)int const* crend() const { return data - 1; }
    int data[2] = {1, 2};
  };

  Iterable iterable;
  auto* i = begin(iterable);
  auto const* ci = cbegin(iterable);
  auto* ri = rbegin(iterable);
  auto const* cri = crbegin(iterable);

  ASSERT_EQ(*i, 1);
  ASSERT_NE(i, end(iterable));
  ++i;
  ASSERT_EQ(*i, 2);
  ASSERT_NE(i, end(iterable));
  ++i;
  ASSERT_EQ(i, end(iterable));

  ASSERT_EQ(*ci, 1);
  ASSERT_NE(ci, cend(iterable));
  ++ci;
  ASSERT_EQ(*ci, 2);
  ASSERT_NE(ci, cend(iterable));
  ++ci;
  ASSERT_EQ(ci, cend(iterable));

  ASSERT_EQ(*ri, 2);
  ASSERT_NE(ri, rend(iterable));
  --ri;
  ASSERT_EQ(*ri, 1);
  ASSERT_NE(ri, rend(iterable));
  --ri;
  ASSERT_EQ(ri, rend(iterable));

  ASSERT_EQ(*cri, 2);
  ASSERT_NE(cri, crend(iterable));
  --cri;
  ASSERT_EQ(*cri, 1);
  ASSERT_NE(cri, crend(iterable));
  --cri;
  ASSERT_EQ(cri, crend(iterable));
}

TEST(Iterable, reverseConstButNotConst) {
  struct X : private std::vector<int> {
    X() : std::vector<int>{1, 2} {}
    using std::vector<int>::crbegin;
    using std::vector<int>::crend;
  };

  X x;
  ASSERT_NE(cds::rbegin(x), cds::rend(x));
  ASSERT_EQ(*cds::rbegin(x), 2);
  auto it = cds::rbegin(x);
  ++it;
  ASSERT_NE(it, cds::rend(x));
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(it, cds::rend(x));
}

#ifdef DCR_SINCECPP11
template <typename T, typename V> constexpr auto sum(T&& lhs, V&& rhs) -> decltype(meta::rvalue<T>() + meta::rvalue<V>()) {
  return cds::forward<T>(lhs) + cds::forward<V>(rhs);
}

TEST(Iterator, cpp11Constexpr) {
  static_assert(sum(1, 2) == 3, "Failed Compile Time Fwd");
  static_assert(minOf(1, 2) == 1, "Failed Compile Time Min");
  static_assert(minOf(1, 2, 0) == 0, "Failed Compile Time Min");
  static_assert(maxOf(1, 2) == 2, "Failed Compile Time Max");
  static_assert(maxOf(1, 2, 3) == 3, "Failed Compile Time Max");

  struct Iterable {
    CDS_ATTR(nodiscard)constexpr int cbegin() const { return 3; }
    CDS_ATTR(nodiscard)constexpr int cend() const { return 4; }
    CDS_ATTR(nodiscard)constexpr int crbegin() const { return 7; }
    CDS_ATTR(nodiscard)constexpr int crend() const { return 8; }
  };

  static_assert(cbegin(Iterable()) == 3, "Failed Compile Time iterablefns");
  static_assert(cend(Iterable()) == 4, "Failed Compile Time iterablefns");
  static_assert(crbegin(Iterable()) == 7, "Failed Compile Time iterablefns");
  static_assert(crend(Iterable()) == 8, "Failed Compile Time iterablefns");
}
#endif // #ifdef DCR_SINCECPP11

#ifdef DCR_SINCECPP14
TEST(Iterator, cpp14Constexpr) {

  struct Iterable {
    constexpr int begin() { (void)this; return 1; }
    constexpr int end() { (void)this; return 2; }
    constexpr int rbegin() { (void)this; return 5; }
    constexpr int rend() { (void)this; return 6; }
  };

  static_assert(begin(Iterable()) == 1, "Failed Compile Time iterablefns");
  static_assert(end(Iterable()) == 2, "Failed Compile Time iterablefns");
  static_assert(rbegin(Iterable()) == 5, "Failed Compile Time iterablefns");
  static_assert(rend(Iterable()) == 6, "Failed Compile Time iterablefns");
}
#endif // #ifdef DCR_SINCECPP14
