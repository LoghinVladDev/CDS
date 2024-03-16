// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include <cds/meta/Semantics>
#include "UnitTest.hpp"

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
}

TEST(Semantics, Forward) {
  fwd1 = 0;
  fwd2 = 0;
  fwd(A{});
  A obj;
  fwd(obj);

  ASSERT_EQ(fwd1, 1);
  ASSERT_EQ(fwd2, 1);
}

TEST(Semantics, Move) {
  fwd1 = 0;
  fwd2 = 0;
  A obj;
  fwd(move(obj));
  ASSERT_EQ(fwd1, 0);
  ASSERT_EQ(fwd2, 1);
}

TEST(Semantics, exchange) {
  int obj = 0;
  ASSERT_EQ(exchange(obj, 5), 0);
  ASSERT_EQ(obj, 5);
}

#ifdef DCR_SINCECPP14
struct Moveable {
  Moveable() noexcept = default;
  Moveable(Moveable&& m) = default;
  constexpr int f()&& { (void)this; return 1; }
  CDS_ATTR(nodiscard) constexpr int f() const& { (void)this; return 0; }
};

constexpr Moveable& mutateToNonMove(Moveable&& m) {
  return *static_cast<Moveable*>(&m);
}

TEST(Semantics, cpp14Constexpr) {
  static_assert(mutateToNonMove(Moveable()).f() == 0, "Failed Compile Time Move");
  static_assert(move(mutateToNonMove(Moveable())).f() == 1, "Failed Compile Time Move");
}
#endif // #ifdef DCR_SINCECPP14
