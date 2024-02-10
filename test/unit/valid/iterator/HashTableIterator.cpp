// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/iterator/HashTableIterator>
#include "UnitTest.hpp"

namespace {
using cds::Size;
using cds::meta::Nullptr;
using cds::iterator::HashTableIterator;
template <typename T> using Node = cds::impl::FwdNode<T>;

template <typename = void> auto l() noexcept -> Nullptr {
  return nullptr;
}

template <typename I, typename F, typename... T> auto l(F&& first, T&&... ints) noexcept -> Node<I>* {
  return new Node<I> {l<I>(std::forward<T>(ints)...), std::forward<F>(first)};
}

template <typename A> auto pushArr(A&&) noexcept -> void {
  // do nothing
}

template <typename A, typename F, typename... T> auto pushArr(A&& arr, F&& first, T&&... rest) noexcept -> void {
  *std::forward<A>(arr) = std::forward<F>(first);
  pushArr(std::forward<A>(arr) + 1, std::forward<T>(rest)...);
}

template <typename T> struct MapFixture { Node<T>** buckets; Size count; };
template <typename I, typename... T> auto b(T&&... nodes) noexcept -> MapFixture<I> {
  auto arr = new Node<I>*[sizeof...(T)];
  pushArr(arr, std::forward<T>(nodes)...);
  return {arr, sizeof...(T)};
}

template <typename T> auto release(MapFixture<T> mf) noexcept -> void {
  for (Size i = 0; i < mf.count; ++i) {
    auto f = mf.buckets[i];
    while (f) {
      auto c = f;
      f = f->next;
      delete c;
    }
  }
  delete[] mf.buckets;
}

template <typename T> class MapFixtureHolder {
public:
  MapFixtureHolder(MapFixture<T> f) noexcept : _f(f) {}
  ~MapFixtureHolder() noexcept { release(_f); }
  operator MapFixture<T>() const noexcept {
    return _f;
  }

  auto begin() -> HashTableIterator<T> {
    return {_f.buckets, _f.count};
  }

  auto end() -> HashTableIterator<T> {
    return {nullptr};
  }

private:
  MapFixture<T> _f;
};
} // namespace

TEST(HashTableIterator, smf) {
  MapFixtureHolder<int> obj = b<int>(
      l<int>(1, 2, 3),
      l<int>(4, 5, 6)
  );

  auto b = obj.begin();
  auto e = obj.end();
  ASSERT_NE(b, e);

  MapFixture<int> mf = obj;
  auto it = HashTableIterator<int>(mf.buckets, mf.count, mf.buckets[0], nullptr, 0);
  ASSERT_EQ(it, b);
  ASSERT_NE(it, e);

  HashTableIterator<int> copyB{b};
  ASSERT_EQ(copyB, b);
  HashTableIterator<int> copyE{e};
  ASSERT_EQ(copyE, e);
  ASSERT_NE(copyE, copyB);
  copyE = b;
  ASSERT_EQ(copyB, copyE);
  ASSERT_NE(copyE, e);

  copyE = std::move(e);
  ASSERT_NE(copyB, copyE);
  auto mb{std::move(b)};
  ASSERT_NE(mb, copyE);
  ASSERT_EQ(copyB, mb);
}

TEST(HashTableIterator, valueAdvance) {
  MapFixtureHolder<int> obj = b<int>(
      l(),
      l<int>(1, 2, 3),
      l(),
      l(),
      l<int>(4, 5),
      l(),
      l<int>(6),
      l()
  );

  auto b = obj.begin();
  auto e = obj.end();

  ASSERT_EQ(*b, 1);
  ASSERT_NE(b, e);
  ++b;

  ASSERT_EQ(*b, 2);
  ASSERT_NE(b, e);
  ++b;

  ASSERT_EQ(*b, 3);
  ASSERT_NE(b, e);
  ++b;

  ASSERT_EQ(*b, 4);
  ASSERT_NE(b, e);
  (void) b++;

  ASSERT_EQ(*b, 5);
  ASSERT_NE(b, e);
  (void) b++;


  ASSERT_EQ(*b, 6);
  ASSERT_NE(b, e);
  ++b;

  ASSERT_EQ(b, e);
  ++b;
  ASSERT_EQ(b, e);
}

TEST(HashTableIterator, valueAdvancedAddr) {
  MapFixtureHolder<std::string> obj = b<std::string>(
      l<std::string>("a", "b"),
      l(),
      l<std::string>("c"),
      l(),
      l(),
      l<std::string>("d", "e")
  );

  auto begin = obj.begin();
  auto end = obj.end();

  ASSERT_NE(begin, end);
  ASSERT_EQ(*begin, "a");
  ASSERT_EQ(begin->length(), 1);
  ++begin;

  ASSERT_NE(begin, end);
  ASSERT_EQ(*begin, "b");
  ASSERT_EQ(begin->length(), 1);
  (void) begin++;

  ASSERT_NE(begin, end);
  ASSERT_EQ(*begin, "c");
  ASSERT_EQ(begin->length(), 1);
  ++begin;

  ASSERT_NE(begin, end);
  ASSERT_EQ(*begin, "d");
  ASSERT_EQ(begin->length(), 1);
  (void) begin++;

  ASSERT_NE(begin, end);
  ASSERT_EQ(*begin, "e");
  ASSERT_EQ(begin->length(), 1);
  ++begin;

  ASSERT_EQ(begin, end);
  (void) begin++;
  ++begin;
  ASSERT_EQ(begin, end);
  (void) end++;
  ++end;
  ASSERT_EQ(begin, end);
}
