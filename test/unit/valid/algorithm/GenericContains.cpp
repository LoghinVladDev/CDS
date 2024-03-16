// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "../../../../src/algorithm/GenericContains.hpp"
#include "UnitTest.hpp"
#include <cds/StringView>
#include <vector>

namespace {
using namespace cds;
}

namespace {
template <typename I, typename V> CDS_ATTR(constexpr(14)) auto contains(I&& obj, V&& val) noexcept(noexcept(
    impl::contains(cds::forward<I>(obj), cds::forward<V>(val), functional::Equal<>())
)) -> decltype(impl::contains(cds::forward<I>(obj), cds::forward<V>(val), functional::Equal<>())) {
  return impl::contains(cds::forward<I>(obj), cds::forward<V>(val), functional::Equal<>());
}
} // namespace

TEST(GenericContains, contains) {
  struct A_eximpl { CDS_ATTR(nodiscard) bool contains(int const x) const { (void) this; return x == 1 || x == 2 || x == 3; } };
  struct A_noex { CDS_ATTR(nodiscard) bool contains(int const x) const noexcept { (void) this; return x == 1 || x == 2 || x == 3; } };
  struct A_ex { CDS_ATTR(nodiscard) bool contains(int const x) const noexcept(false) { (void) this; return x == 1 || x == 2 || x == 3; } };

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
  template <typename P>
  bool contains(int x, P&& projector) {
    if (cds::forward<P>(projector)(data[0]) == x) { return true; }
    if (cds::forward<P>(projector)(data[1]) == x) { return true; }
    if (cds::forward<P>(projector)(data[2]) == x) { return true; }
    return false;
  }

  std::string const data[3] = {"a", "bb", "ccc"};
};

namespace {
template <typename I, typename V, typename P> CDS_ATTR(constexpr(14)) auto contains(I&& obj, V&& val, P&& sel) noexcept(noexcept(
    impl::contains(cds::forward<I>(obj), cds::forward<V>(val), cds::forward<P>(sel), functional::Equal<>())
)) -> decltype(
    impl::contains(cds::forward<I>(obj), cds::forward<V>(val), cds::forward<P>(sel), functional::Equal<>())
) {
  return impl::contains(cds::forward<I>(obj), cds::forward<V>(val), cds::forward<P>(sel), functional::Equal<>());
}
} // namespace

TEST(GenericContains, containsSelected) {
  ASSERT_FALSE(contains(A_eximpl_sel(), 0, functional::memFn(&std::string::length)));
  ASSERT_TRUE(contains(A_eximpl_sel(), 1, functional::memFn(&std::string::length)));
  ASSERT_TRUE(contains(A_eximpl_sel(), 2, functional::memFn(&std::string::length)));
  ASSERT_TRUE(contains(A_eximpl_sel(), 3, functional::memFn(&std::string::length)));
  ASSERT_FALSE(contains(A_eximpl_sel(), 4, functional::memFn(&std::string::length)));
}

TEST(GenericContains, containsWithoutContainsMem) {
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 0));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 1));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 2));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 3));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 4));
}

namespace {int doubled(int const v){ return v * 2; }}
TEST(GenericContains, containsSelWithoutContainsMem) {
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 0, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 1, doubled));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 2, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 3, doubled));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 4, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 5, doubled));
  ASSERT_TRUE(contains(std::vector<int>{1, 2, 3}, 6, doubled));
  ASSERT_FALSE(contains(std::vector<int>{1, 2, 3}, 7, doubled));
}

TEST(GenericContains, containsPrefsContains) {
  struct X {
    CDS_ATTR(nodiscard) bool contains(int const x) const { (void) this; return x == 1; }
    CDS_ATTR(nodiscard) int const* begin() const { (void) this; return nullptr; }
    CDS_ATTR(nodiscard) int const* end() const { (void) this; return nullptr; }
  };

  ASSERT_FALSE(contains(X(), 0));
  ASSERT_TRUE(contains(X(), 1));
}

struct XF : private std::vector<int> {
  using std::vector<int>::vector;
  using std::vector<int>::begin;
  using std::vector<int>::end;
};

struct XR : private std::vector<int> {
  using std::vector<int>::vector;
  using std::vector<int>::rbegin;
  using std::vector<int>::rend;
};

TEST(GenericContains, containsFromReverse) {
  ASSERT_FALSE(contains(XR{1, 2, 3}, 0));
  ASSERT_TRUE(contains(XR{1, 2, 3}, 1));
  ASSERT_TRUE(contains(XR{1, 2, 3}, 2));
  ASSERT_TRUE(contains(XR{1, 2, 3}, 3));
  ASSERT_FALSE(contains(XR{1, 2, 3}, 4));
}

TEST(GenericContains, projectedContains) {
  ASSERT_FALSE(contains(XF{1, 2, 3}, 0, doubled));
  ASSERT_TRUE(contains(XF{1, 2, 3}, 2, doubled));
  ASSERT_FALSE(contains(XF{1, 2, 3}, 3, doubled));
  ASSERT_TRUE(contains(XF{1, 2, 3}, 4, doubled));
  ASSERT_FALSE(contains(XF{1, 2, 3}, 5, doubled));
  ASSERT_TRUE(contains(XF{1, 2, 3}, 6, doubled));
  ASSERT_FALSE(contains(XF{1, 2, 3}, 7, doubled));

  ASSERT_FALSE(contains(XR{1, 2, 3}, 0, doubled));
  ASSERT_TRUE(contains(XR{1, 2, 3}, 2, doubled));
  ASSERT_FALSE(contains(XR{1, 2, 3}, 3, doubled));
  ASSERT_TRUE(contains(XR{1, 2, 3}, 4, doubled));
  ASSERT_FALSE(contains(XR{1, 2, 3}, 5, doubled));
  ASSERT_TRUE(contains(XR{1, 2, 3}, 6, doubled));
  ASSERT_FALSE(contains(XR{1, 2, 3}, 7, doubled));
}

TEST(GenericContains, FunctionalSelected) {
  impl::Contains<impl::Equal<>> const c;
  auto const ce = impl::Contains<impl::Equal<>>{impl::Equal<>()};

  ASSERT_TRUE(c(XF{1, 2, 3}, 1));
  ASSERT_FALSE(c(XF{1, 2, 3}, 0));
  ASSERT_TRUE(c(XF{1, 2, 3}, 2, doubled));
  ASSERT_FALSE(c(XF{1, 2, 3}, 1, doubled));
  ASSERT_TRUE(ce(XF{1, 2, 3}, 1));
  ASSERT_FALSE(ce(XF{1, 2, 3}, 0));
  ASSERT_TRUE(ce(XF{1, 2, 3}, 2, doubled));
  ASSERT_FALSE(ce(XF{1, 2, 3}, 1, doubled));

  impl::NotContains<impl::Equal<>> const nc;
  auto const nce = impl::NotContains<impl::Equal<>>{impl::Equal<>()};

  ASSERT_FALSE(nc(XF{1, 2, 3}, 1));
  ASSERT_TRUE(nc(XF{1, 2, 3}, 0));
  ASSERT_FALSE(nc(XF{1, 2, 3}, 2, doubled));
  ASSERT_TRUE(nc(XF{1, 2, 3}, 1, doubled));
  ASSERT_FALSE(nce(XF{1, 2, 3}, 1));
  ASSERT_TRUE(nce(XF{1, 2, 3}, 0));
  ASSERT_FALSE(nce(XF{1, 2, 3}, 2, doubled));
  ASSERT_TRUE(nce(XF{1, 2, 3}, 1, doubled));
}

#ifdef DCR_SINCECPP14
struct A_eximpl_sel_c {
  template <typename P>
  constexpr bool contains(int x, P&& projector) {
    if (cds::forward<P>(projector)(data[0]) == x) { return true; }
    if (cds::forward<P>(projector)(data[1]) == x) { return true; }
    if (cds::forward<P>(projector)(data[2]) == x) { return true; }
    return false;
  }

  StringView const data[3] = {"a", "bb", "ccc"};
};

TEST(GenericContains, cpp14Constexpr) {
  struct A_eximpl_c { CDS_ATTR(nodiscard) constexpr bool contains(int x) const { (void) this; return x == 1 || x == 2 || x == 3; } };
  static_assert(!contains(A_eximpl_c(), 0), "constexpr contains failed");
  static_assert(contains(A_eximpl_c(), 1), "constexpr contains failed");
  static_assert(!contains(A_eximpl_sel_c(), 0, functional::memFn(&StringView::length)), "constexpr contains by projector failure");
  static_assert(contains(A_eximpl_sel_c(), 1, functional::memFn(&StringView::length)), "constexpr contains by projector failure");

  struct X {
    CDS_ATTR(nodiscard) constexpr bool contains(int x) const { (void) this; return x == 1; }
    CDS_ATTR(nodiscard) int const* begin() const { (void) this; return nullptr; }
    CDS_ATTR(nodiscard) int const* end() const { (void) this; return nullptr; }
  };
  static_assert(contains(X(), 1), "constexpr contains failed");
  constexpr int arr[2] = {1, 2};
  static_assert(!contains(arr, 0), "constexpr contains failed");
  static_assert(contains(arr, 1), "constexpr contains failed");
}
#endif // #ifdef DCR_SINCECPP14
