// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include <cds/Utility>
#include <cds/functional/FunctionalInterface>
#include "UnitTest.hpp"
#include <cds/StringView>
#include <chrono>
#include <iostream>
#include "../Shared.hpp"

using namespace cds;

namespace {
auto fwd1 = 0;
auto fwd2 = 0;

struct A {};
void tgt(A const&) {
  fwd1 = 1;
}
void tgt(A&&) {
  fwd2 = 1;
}

template <typename T> void fwd(T&& obj) {
  tgt(cds::forward<T>(obj));
}

using testing::iteq;
using testing::citeq;
} // namespace

TEST(Utility, Forward) {
  fwd1 = 0;
  fwd2 = 0;
  fwd(A{});
  A obj;
  fwd(obj);

  ASSERT_EQ(fwd1, 1);
  ASSERT_EQ(fwd2, 1);
}

TEST(Utility, Move) {
  fwd1 = 0;
  fwd2 = 0;
  A obj;
  fwd(move(obj));
  ASSERT_EQ(fwd1, 0);
  ASSERT_EQ(fwd2, 1);
}

TEST(Utility, exchange) {
  int obj = 0;
  ASSERT_EQ(exchange(obj, 5), 0);
  ASSERT_EQ(obj, 5);
}

TEST(Utility, minOf) {
  ASSERT_EQ(minOf(1, 2), 1);
  ASSERT_EQ(minOf(1, 2, 3), 1);
  ASSERT_EQ(minOf(1, 2, 3, 4), 1);
  ASSERT_EQ(minOf(4, 2, 1, 3), 1);
}

TEST(Utility, maxOf) {
  ASSERT_EQ(maxOf(1, 2), 2);
  ASSERT_EQ(maxOf(1, 2, 3), 3);
  ASSERT_EQ(maxOf(1, 2, 3, 4), 4);
  ASSERT_EQ(maxOf(4, 2, 1, 3), 4);
}

TEST(Utility, iterable) {
  struct Iterable {
    int* begin() { return data; }
    int* end() { return data + 2; }
    int const* cbegin() const { return data; }
    int const* cend() const { return data + 2; }
    int* rbegin() { return data + 1; }
    int* rend() { return data - 1; }
    int const* crbegin() const { return data + 1; }
    int const* crend() const { return data - 1; }
    int data[2] = {1, 2};
  };

  Iterable iterable;
  auto i = begin(iterable);
  auto ci = cbegin(iterable);
  auto ri = rbegin(iterable);
  auto cri = crbegin(iterable);

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

namespace {
template <typename I, typename V> CDS_ATTR(constexpr(14)) auto contains(I&& obj, V&& val) noexcept(noexcept(
    impl::contains(cds::forward<I>(obj), cds::forward<V>(val), functional::Equal<>())
)) -> decltype(impl::contains(cds::forward<I>(obj), cds::forward<V>(val), functional::Equal<>())) {
  return impl::contains(cds::forward<I>(obj), cds::forward<V>(val), functional::Equal<>());
}
} // namespace

TEST(Utility, contains) {
  struct A_eximpl { bool contains(int x) const { return x == 1 || x == 2 || x == 3; } };
  struct A_noex { bool contains(int x) const noexcept { return x == 1 || x == 2 || x == 3; } };
  struct A_ex { bool contains(int x) const noexcept(false) { return x == 1 || x == 2 || x == 3; } };

  ASSERT_FALSE(contains(A_eximpl(), 0));
  ASSERT_TRUE(contains(A_eximpl(), 1));
  ASSERT_TRUE(contains(A_eximpl(), 2));
  ASSERT_TRUE(contains(A_eximpl(), 3));
  ASSERT_FALSE(contains(A_eximpl(), 4));

  ASSERT_FALSE(contains(A_noex(), 0));
  ASSERT_TRUE(contains(A_noex(), 1));
  ASSERT_TRUE(contains(A_noex(), 2));
  ASSERT_TRUE(contains(A_noex(), 3));
  ASSERT_FALSE(contains(A_noex(), 4));

  ASSERT_FALSE(contains(A_ex(), 0));
  ASSERT_TRUE(contains(A_ex(), 1));
  ASSERT_TRUE(contains(A_ex(), 2));
  ASSERT_TRUE(contains(A_ex(), 3));
  ASSERT_FALSE(contains(A_ex(), 4));

  ASSERT_EQ(noexcept(contains(A_eximpl(), 0)), false);
  ASSERT_EQ(noexcept(contains(A_noex(), 0)), true);
  ASSERT_EQ(noexcept(contains(A_ex(), 0)), false);
}

struct A_eximpl_sel {
  template <typename S>
  bool contains(int x, S&& selector) {
    if (cds::forward<S>(selector)(data[0]) == x) { return true; }
    if (cds::forward<S>(selector)(data[1]) == x) { return true; }
    if (cds::forward<S>(selector)(data[2]) == x) { return true; }
    return false;
  }

  std::string const data[3] = {"a", "bb", "ccc"};
};

namespace {
template <typename I, typename V, typename S> CDS_ATTR(constexpr(14)) auto contains(I&& obj, V&& val, S&& sel) noexcept(noexcept(
    impl::contains(cds::forward<I>(obj), cds::forward<V>(val), cds::forward<S>(sel), functional::Equal<>())
)) -> decltype(
    impl::contains(cds::forward<I>(obj), cds::forward<V>(val), cds::forward<S>(sel), functional::Equal<>())
) {
  return impl::contains(cds::forward<I>(obj), cds::forward<V>(val), cds::forward<S>(sel), functional::Equal<>());
}
} // namespace

TEST(Utility, containsSelected) {
  ASSERT_FALSE(contains(A_eximpl_sel(), 0, functional::memFn(&std::string::length)));
  ASSERT_TRUE(contains(A_eximpl_sel(), 1, functional::memFn(&std::string::length)));
  ASSERT_TRUE(contains(A_eximpl_sel(), 2, functional::memFn(&std::string::length)));
  ASSERT_TRUE(contains(A_eximpl_sel(), 3, functional::memFn(&std::string::length)));
  ASSERT_FALSE(contains(A_eximpl_sel(), 4, functional::memFn(&std::string::length)));
}

TEST(Utility, IsIterable) {
  static_assert(meta::IsIterable<int[10]>::value, "Failed is iterable");
  static_assert(meta::IsIterable<std::string>::value, "Failed is iterable");
  static_assert(meta::IsIterable<std::vector<int>>::value, "Failed is iterable");
  static_assert(meta::IsIterable<StringView>::value, "Failed is iterable");
  static_assert(meta::IsIterable<StringView>::value, "Failed is iterable");
  struct noend { int const* begin() const { return nullptr; } };
  struct correct { int const* begin() const { return nullptr; } int const* end() const { return nullptr; } };
  static_assert(!meta::IsIterable<noend>::value, "Failed is iterable");
  static_assert(meta::IsIterable<correct>::value, "Failed is iterable");
  static_assert(!meta::IsIterable<int*>::value, "Failed is iterable");
}

TEST(Utility, IsReverseIterable) {
  static_assert(meta::IsReverseIterable<int[10]>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<std::string>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<std::vector<int>>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<StringView>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<StringView>::value, "Failed is iterable");
  struct noend { int const* rbegin() const { return nullptr; } };
  struct correct { int const* rbegin() const { return nullptr; } int const* rend() const { return nullptr; } };
  static_assert(!meta::IsReverseIterable<noend>::value, "Failed is iterable");
  static_assert(meta::IsReverseIterable<correct>::value, "Failed is iterable");
  static_assert(!meta::IsReverseIterable<int*>::value, "Failed is iterable");
}

TEST(Utility, containsWithoutContainsMem) {
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 0));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 1));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 2));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 3));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 4));
}

namespace {int doubled(int v){ return v * 2; }}
TEST(Utility, containsSelWithoutContainsMem) {
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 0, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 1, doubled));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 2, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 3, doubled));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 4, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 5, doubled));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 6, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 7, doubled));
}

TEST(Utility, containsPrefsContains) {
  struct X {
    bool contains(int x) const { return x == 1; }
    int const* begin() const { return nullptr; }
    int const* end() const { return nullptr; }
  };

  ASSERT_FALSE(contains(X(), 0));
  ASSERT_TRUE(contains(X(), 1));
}

namespace {
template <typename I, typename V> CDS_ATTR(constexpr(14)) auto find(I&& iter, V&& val) noexcept(noexcept(
    impl::find(cds::forward<I>(iter), cds::forward<V>(val), functional::Equal<>(), impl::FindResultTransformer<>())
)) -> decltype(
    impl::find(cds::forward<I>(iter), cds::forward<V>(val), functional::Equal<>(), impl::FindResultTransformer<>())
) {
  return
      impl::find(cds::forward<I>(iter), cds::forward<V>(val), functional::Equal<>(), impl::FindResultTransformer<>());
}
} // namespace

TEST(Utility, ownership) {
  std::vector<int> i {1, 2, 3};
  auto v = 2;

  auto l1 = find(i, v);
  auto l2 = find(i, 2);
  auto l3 = find(std::vector<int>{1, 2, 3}, v);
  auto l4 = find(std::vector<int>{1, 2, 3}, 2);

  auto b1 = l1.begin();
  auto b2 = l2.begin();
  auto b3 = l3.begin();
  auto b4 = l4.begin();

  ASSERT_NE(b1, l1.end());
  ASSERT_NE(b2, l2.end());
  ASSERT_NE(b3, l3.end());
  ASSERT_NE(b4, l4.end());
  ASSERT_EQ(*b1, 2);
  ASSERT_EQ(*b2, 2);
  ASSERT_EQ(*b3, 2);
  ASSERT_EQ(*b4, 2);
  ++b1;
  ++b2;
  ++b3;
  ++b4;
  ASSERT_EQ(b1, l1.end());
  ASSERT_EQ(b2, l2.end());
  ASSERT_EQ(b3, l3.end());
  ASSERT_EQ(b4, l4.end());

  std::vector<int> const ci {1, 2, 3};
  auto cv = 2;

  auto cl1 = find(ci, cv);
  auto cl2 = find(ci, (const int)2);
  auto cl3 = find(std::vector<int>{1, 2, 3}, cv);
  auto cl4 = find(std::vector<int>{1, 2, 3}, (const int)2);

  auto cb1 = cl1.begin();
  auto cb2 = cl2.begin();
  auto cb3 = cl3.begin();
  auto cb4 = cl4.begin();

  ASSERT_NE(cb1, cl1.end());
  ASSERT_NE(cb2, cl2.end());
  ASSERT_NE(cb3, cl3.end());
  ASSERT_NE(cb4, cl4.end());
  ASSERT_EQ(*cb1, 2);
  ASSERT_EQ(*cb2, 2);
  ASSERT_EQ(*cb3, 2);
  ASSERT_EQ(*cb4, 2);
  ++cb1;
  ++cb2;
  ++cb3;
  ++cb4;
  ASSERT_EQ(cb1, cl1.end());
  ASSERT_EQ(cb2, cl2.end());
  ASSERT_EQ(cb3, cl3.end());
  ASSERT_EQ(cb4, cl4.end());
}

namespace {
template <typename I, typename V, typename S> CDS_ATTR(constexpr(14)) auto find(I&& iter, V&& val, S&& selector)
    noexcept(noexcept(impl::find(
        cds::forward<I>(iter), cds::forward<V>(val), cds::forward<S>(selector),
        functional::Equal<>(), impl::FindResultTransformer<>()
    ))) -> decltype(impl::find(
        cds::forward<I>(iter), cds::forward<V>(val), cds::forward<S>(selector),
        functional::Equal<>(), impl::FindResultTransformer<>()
    )) {
  return impl::find(
      cds::forward<I>(iter), cds::forward<V>(val), cds::forward<S>(selector),
      functional::Equal<>(), impl::FindResultTransformer<>()
  );
}
} // namespace

TEST(Utility, find) {
  std::vector<int> v {1, 2, 3, 2, 1};
  auto locs1 = find(v, 1);
  auto b1 = locs1.begin();
  ASSERT_NE(b1, locs1.end());
  ASSERT_EQ(*b1, 1);
  ++b1;
  ASSERT_NE(b1, locs1.end());
  ASSERT_EQ(*b1, 1);
  ++b1;
  ASSERT_EQ(b1, locs1.end());

  auto locs2 = find(v, 2);
  auto b2 = locs2.begin();
  ASSERT_NE(b2, locs2.end());
  ASSERT_EQ(*b2, 2);
  ++b2;
  ASSERT_NE(b2, locs2.end());
  ASSERT_EQ(*b2, 2);
  ++b2;
  ASSERT_EQ(b2, locs2.end());

  auto locs3 = find(v, 3);
  auto b3 = locs3.begin();
  ASSERT_NE(b3, locs3.end());
  ASSERT_EQ(*b3, 3);
  ++b3;
  ASSERT_EQ(b3, locs3.end());

  auto locs4 = find(v, 4);
  ASSERT_EQ(locs4.begin(), locs4.end());

  auto locs1Doubled = find(v, 2, doubled);
  auto b1d = locs1Doubled.begin();
  ASSERT_NE(b1d, locs1Doubled.end());
  ASSERT_EQ(*b1d, 1);
  ++b1d;
  ASSERT_NE(b1d, locs1Doubled.end());
  ASSERT_EQ(*b1d, 1);
  ++b1d;
  ASSERT_EQ(b1d, locs1Doubled.end());

  auto locsInvalid = find(v, 3, doubled);
  ASSERT_EQ(locsInvalid.begin(), locsInvalid.end());
}

CDS_ATTR(constexpr(14)) auto testCopy() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto e = impl::copy(begin(srcBuf), end(srcBuf), begin(dstBuf));
  auto reachedExpected = e == end(dstBuf);
  auto eqAtEnd = citeq(srcBuf, dstBuf);
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testCopyPartial() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto e = impl::copy(begin(srcBuf), end(srcBuf) - 2, begin(dstBuf));
  auto reachedExpected = e == end(dstBuf) - 2;
  auto eqAtEndFull = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));
  auto eqAtEndPartial = iteq(begin(srcBuf), end(srcBuf) - 2, begin(dstBuf), end(dstBuf) - 2);

  return !eqAtStart1 && !eqAtStart2 && reachedExpected && !eqAtEndFull && eqAtEndPartial;
}

CDS_ATTR(constexpr(14)) auto testCopyN() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto e = impl::copyN(begin(srcBuf), 4, begin(dstBuf));
  auto reachedExpected = e == end(dstBuf);
  auto eqAtEnd = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testCopyNPartial() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto e = impl::copyN(begin(srcBuf), 2, begin(dstBuf));
  auto reachedExpected = e == end(dstBuf) - 2;
  auto eqAtEndFull = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));
  auto eqAtEndPartial = iteq(begin(srcBuf), end(srcBuf) - 2, begin(dstBuf), end(dstBuf) - 2);

  return !eqAtStart1 && !eqAtStart2 && reachedExpected && !eqAtEndFull && eqAtEndPartial;
}

CDS_ATTR(constexpr(14)) auto testFill() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto e = impl::fill(begin(dstBuf), end(dstBuf), 1);
  auto reachedExpected = e == end(dstBuf);
  auto eqAtEnd = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testFillPartial() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto e = impl::fill(begin(dstBuf) + 1, end(dstBuf) - 1, 1);
  auto reachedExpected = e == end(dstBuf) - 1;
  auto eqAtEndFull = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  auto eqAtEndPartial = iteq(begin(cmpAfter), end(cmpAfter) - 2, begin(dstBuf) + 1, end(dstBuf) - 1);
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && !eqAtEndFull && eqAtEndPartial;
}

CDS_ATTR(constexpr(14)) auto testFillN() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto e = impl::fillN(begin(dstBuf), 4, 1);
  auto reachedExpected = e == end(dstBuf);
  auto eqAtEnd = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testFillNPartial() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto e = impl::fillN(begin(dstBuf), 2, 1);
  auto reachedExpected = e == end(dstBuf) - 2;
  auto eqAtEndFull = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  auto eqAtEndPartial = iteq(begin(cmpAfter), end(cmpAfter) - 2, begin(dstBuf), end(dstBuf) - 2);

  return !eqAtStart1 && !eqAtStart2 && reachedExpected && !eqAtEndFull && eqAtEndPartial;
}

TEST(Utility, copy) {
  ASSERT_TRUE(testCopy());
}

TEST(Utility, copyPartial) {
  ASSERT_TRUE(testCopyPartial());
}

TEST(Utility, copyN) {
  ASSERT_TRUE(testCopyN());
}

TEST(Utility, copyNPartial) {
  ASSERT_TRUE(testCopyNPartial());
}

TEST(Utility, fill) {
  ASSERT_TRUE(testFill());
}

TEST(Utility, fillPartial) {
  ASSERT_TRUE(testFillPartial());
}

TEST(Utility, fillN) {
  ASSERT_TRUE(testFillN());
}

TEST(Utility, fillNPartial) {
  ASSERT_TRUE(testFillNPartial());
}

TEST(Utility, timing) {
//   auto timed = [](auto name, auto callable) {
//     auto begin = std::chrono::high_resolution_clock::now();
//     callable();
//     auto end = std::chrono::high_resolution_clock::now();
//     auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//     std::cout << "Duration of '" << name << "': " << diff.count() << "ns\n";
//   };
//
//   int n = 10000000;
//   char const svCstr[] = "abcdefghijklmnop";
//   StringView sv = "abcdefghijklmnop";
//   using impl::findFirst;
//
// ////  timed("sv", [&]{
// ///    for (int i = 0; i < n; ++i) {
// ///      auto volatile r = impl::FF1<>::findFirst(sv, 'b');
// ///    }
// ///  });
//
//   auto findFirstCStr = []<int s>(char const(&str)[s], char v) {
//     for (auto idx = 0; idx + 1 < s; ++idx) {
//       if (str[idx] == v) {
//         return idx;
//       }
//     }
//     return -1;
//   };
//
//   timed("sv1", [&]{
//     for (int i = 0; i < n; ++i) {
//       auto volatile r = findFirstCStr(svCstr, 'm');
//     }
//   });
//
//   timed("sv2", [&]{
//     for (int i = 0; i < n; ++i) {
//       auto volatile r = sv.findFirst('m');
//     }
//   });
//
//   timed("sv3", [&]{
//     for (int i = 0; i < n; ++i) {
//       auto volatile r = findFirst(sv, 'm', functional::Equal<>(), impl::FindStringTransformer<char, impl::StringUtils<char, meta::StringTraits<char>>>());
//     }
//   });
////
////   timed("sv", [&]{
////     for (int i = 0; i < n; ++i) {
////       auto volatile r = findFirstA(sv, 'b');
////     }
////   });
////
////   timed("sv", [&]{
////     for (int i = 0; i < n; ++i) {
////       static constexpr impl::FF<> ff;
////       auto volatile r = ff.findFirst(sv, 'b');
////     }
////   });
////
////   timed("sv", [&]{
////     for (int i = 0; i < n; ++i) {
////       auto volatile r = findFirstB(sv, 'b');
////     }
////   });
}

#ifdef DCR_SINCECPP11
template <typename T, typename V> constexpr auto sum(T&& lhs, V&& rhs) -> decltype(meta::rvalue<T>() + meta::rvalue<V>()) {
  return cds::forward<T>(lhs) + cds::forward<V>(rhs);
}

TEST(Utility, cpp11Constexpr) {
  static_assert(sum(1, 2) == 3, "Failed Compile Time Fwd");
  static_assert(minOf(1, 2) == 1, "Failed Compile Time Min");
  static_assert(minOf(1, 2, 0) == 0, "Failed Compile Time Min");
  static_assert(maxOf(1, 2) == 2, "Failed Compile Time Max");
  static_assert(maxOf(1, 2, 3) == 3, "Failed Compile Time Max");

  struct Iterable {
    constexpr int cbegin() const { return 3; }
    constexpr int cend() const { return 4; }
    constexpr int crbegin() const { return 7; }
    constexpr int crend() const { return 8; }
  };

  static_assert(cbegin(Iterable()) == 3, "Failed Compile Time iterablefns");
  static_assert(cend(Iterable()) == 4, "Failed Compile Time iterablefns");
  static_assert(crbegin(Iterable()) == 7, "Failed Compile Time iterablefns");
  static_assert(crend(Iterable()) == 8, "Failed Compile Time iterablefns");
}
#endif

#ifdef DCR_SINCECPP14
struct A_eximpl_sel_c {
  template <typename S>
  constexpr bool contains(int x, S&& selector) {
    if (cds::forward<S>(selector)(data[0]) == x) { return true; }
    if (cds::forward<S>(selector)(data[1]) == x) { return true; }
    if (cds::forward<S>(selector)(data[2]) == x) { return true; }
    return false;
  }

  StringView const data[3] = {"a", "bb", "ccc"};
};

struct Moveable {
  Moveable() noexcept = default;
  Moveable(Moveable&& m) = default;
  constexpr int f()&& { return 1; }
  constexpr int f() const& { return 0; }
};

constexpr Moveable& mutateToNonMove(Moveable&& m) {
  return *static_cast<Moveable*>(&m);
}

TEST(Utility, cpp14Constexpr) {
  static_assert(mutateToNonMove(Moveable()).f() == 0, "Failed Compile Time Move");
  static_assert(move(mutateToNonMove(Moveable())).f() == 1, "Failed Compile Time Move");

  struct Iterable {
    constexpr int begin() { return 1; }
    constexpr int end() { return 2; }
    constexpr int rbegin() { return 5; }
    constexpr int rend() { return 6; }
  };

  static_assert(begin(Iterable()) == 1, "Failed Compile Time iterablefns");
  static_assert(end(Iterable()) == 2, "Failed Compile Time iterablefns");
  static_assert(rbegin(Iterable()) == 5, "Failed Compile Time iterablefns");
  static_assert(rend(Iterable()) == 6, "Failed Compile Time iterablefns");

  struct A_eximpl_c { constexpr bool contains(int x) const { return x == 1 || x == 2 || x == 3; } };
  static_assert(!contains(A_eximpl_c(), 0), "constexpr contains failed");
  static_assert(contains(A_eximpl_c(), 1), "constexpr contains failed");
  static_assert(!contains(A_eximpl_sel_c(), 0, functional::memFn(&StringView::length)), "constexpr contains by selector failure");
  static_assert(contains(A_eximpl_sel_c(), 1, functional::memFn(&StringView::length)), "constexpr contains by selector failure");

  struct X {
    constexpr bool contains(int x) const { return x == 1; }
    int const* begin() const { return nullptr; }
    int const* end() const { return nullptr; }
  };
  static_assert(contains(X(), 1), "constexpr contains failed");
  constexpr int arr[2] = {1, 2};
  static_assert(!contains(arr, 0), "constexpr contains failed");
  static_assert(contains(arr, 1), "constexpr contains failed");

  static_assert(testCopy(), "constexpr copy failed");
  static_assert(testCopyPartial(), "constexpr copy partial failed");
  static_assert(testCopyN(), "constexpr copyN failed");
  static_assert(testCopyNPartial(), "constexpr copyN partial failed");

  static_assert(testFill(), "constexpr fill failed");
  static_assert(testFillPartial(), "constexpr fill partial failed");
  static_assert(testFillN(), "constexpr fillN failed");
  static_assert(testFillNPartial(), "constexpr fillN partial failed");
}
#endif
