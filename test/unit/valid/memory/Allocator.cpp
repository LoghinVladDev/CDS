// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/meta/StdLib>
#include <cds/memory/Allocator>
#include <cds/Utility>
#include "UnitTest.hpp"

namespace {
using cds::Allocator;
using cds::AllocatorSet;
}

TEST(Allocator, singleAllocator) {
  auto alloc = Allocator<int>();
  auto* obj = alloc.allocate(1);
  *obj = 2;
  alloc.deallocate(obj, 1);
}

TEST(Allocator, objUninitConsistency) {
  int ctorCalls = 0;
  int dtorCalls = 0;

  class S {
  public:
    S(int& c, int& d) noexcept : _c(c), _d(d) {++_c;}
    ~S() noexcept { ++_d; }
  private:
    int& _c;
    int& _d;
  };

  auto alloc = Allocator<S>();

  ASSERT_EQ(ctorCalls, 0);
  ASSERT_EQ(dtorCalls, 0);
  auto* ps1 = alloc.allocate(1);
  alloc.deallocate(ps1, 1);
  ASSERT_EQ(ctorCalls, 0);
  ASSERT_EQ(dtorCalls, 0);

  auto* ps2 = alloc.allocate(1);
  ASSERT_EQ(ctorCalls, 0);
  ASSERT_EQ(dtorCalls, 0);
  new (ps2) S(ctorCalls, dtorCalls);
  ASSERT_EQ(ctorCalls, 1);
  ASSERT_EQ(dtorCalls, 0);
  ps2->~S();
  alloc.deallocate(ps2, 1);
  ASSERT_EQ(ctorCalls, 1);
  ASSERT_EQ(dtorCalls, 1);
}

TEST(Allocator, allocSet) {
  auto allocSet = AllocatorSet<Allocator<int>, Allocator<float>>();
  auto pInt = allocSet.template get<int>().allocate(1);
  auto pFloat = allocSet.template get<float>().allocate(1);
  ASSERT_NE(static_cast<void*>(pInt), static_cast<void*>(pFloat));
  allocSet.template get<int>().deallocate(pInt, 1);
  allocSet.template get<float>().deallocate(pFloat, 1);
}

namespace {
using cds::Size;
using cds::Byte;
template <typename T, Size size> class StaticPoolAllocator {
public:
  using Type = T;

  T* allocate(Size n) {
    if (n * sizeof(T) > cds::maxOf(size, sizeof(T))) {
      throw std::bad_alloc();
    }

    return static_cast<T*>(static_cast<void*>(pool));
  }

  void deallocate(CDS_ATTR(unused) T*, CDS_ATTR(unused) Size) noexcept {
    // empty
  }

private:
  alignas(T) Byte pool[cds::maxOf(size, sizeof(T))];
};
} // namespace

TEST(Allocator, allocSetMixed) {
  auto allocSet = AllocatorSet<Allocator<int>, StaticPoolAllocator<float, 1024>>();
  auto pInt = allocSet.template get<int>().allocate(1);
  auto pFloat = allocSet.template get<float>().allocate(1);
  ASSERT_NE(static_cast<void*>(pInt), static_cast<void*>(pFloat));
  allocSet.template get<int>().deallocate(pInt, 1);
  allocSet.template get<float>().deallocate(pFloat, 1);
}

#ifdef DCR_SINCECPP20
consteval auto dynUser() -> bool {
  auto a = Allocator<int>();
  auto p = a.allocate(4);
  a.deallocate(p, 4);

  struct S {int x; int y;};
  auto a2 = Allocator<S>();
  auto p1 = a2.allocate(1);
  cds::impl::construct(p1, 1, 2);
  bool v = p1->x == 1 && p1->y == 2;
  cds::impl::destruct(p1);
  a2.deallocate(p1, 1);

  return v;
}

TEST(Allocator, constexpr20) {
  static_assert(dynUser(), "failed constexpr20");
}
#endif
