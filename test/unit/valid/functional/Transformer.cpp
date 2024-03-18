// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11+

#include <cds/functional/Transformer>
#include "UnitTest.hpp"

namespace {
using cds::functional::impl::Identity;
}

class S {
public:
  CDS_ATTR(constexpr(11)) S(int const x) : _x(x) {}
  CDS_ATTR(constexpr(11)) bool operator==(S const& obj) const { return _x == obj._x; }
private:
  int _x;
};

TEST(Transformer, identity) {
  Identity<int> const id1;
  Identity<S> const id2;
  ASSERT_EQ(id1(5), 5);
  ASSERT_EQ(id2(S(5)), S(5));
}

TEST(Transformer, transparency) {
  Identity<> const id;
  ASSERT_EQ(id(5), 5);
  ASSERT_EQ(id(S(5)), S(5));
}

#ifdef DCR_SINCECPP11
TEST(Transformer, constexpr11) {
  constexpr Identity<> id;
  static_assert(id(5) == 5, "Failed constexpr test");
  static_assert(id(S(5)) == S(5), "Failed constexpr test");
}
#endif
