// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11-2b

#include <cds/functional/Hash>
#include "UnitTest.hpp"

namespace {
using cds::functional::Hash;

using cds::U8;
using cds::U16;
using cds::U32;
using cds::U64;

using cds::S8;
using cds::S16;
using cds::S32;
using cds::S64;
}

TEST(Hash, unspecIntegrals) {
  Hash<char> h8;
  Hash<short> h116;
  Hash<short int> h216;
  Hash<int> h132;
  Hash<signed> h232;
  Hash<unsigned> h332;
  Hash<long> h164;
  Hash<long int> h264;
  Hash<long long> h364;
  Hash<long long int> h464;

  ASSERT_EQ(h8(10), 10);
  ASSERT_EQ(h116(10), 10);
  ASSERT_EQ(h216(10), 10);
  ASSERT_EQ(h132(10), 10);
  ASSERT_EQ(h232(10), 10);
  ASSERT_EQ(h332(10), 10);
  ASSERT_EQ(h164(10), 10);
  ASSERT_EQ(h264(10), 10);
  ASSERT_EQ(h364(10), 10);
  ASSERT_EQ(h464(10), 10);

  ASSERT_GE(h8(-10), 0);
  ASSERT_GE(h116(-10), 0);
  ASSERT_GE(h216(-10), 0);
  ASSERT_GE(h132(-10), 0);
  ASSERT_GE(h232(-10), 0);
  ASSERT_GE(h332(-10), 0);
  ASSERT_GE(h164(-10), 0);
  ASSERT_GE(h264(-10), 0);
  ASSERT_GE(h364(-10), 0);
  ASSERT_GE(h464(-10), 0);
}

TEST(Hash, signedIntegrals) {
  Hash<signed char> h8;
  Hash<signed short> h116;
  Hash<signed short int> h216;
  Hash<signed> h132;
  Hash<signed int> h232;
  Hash<signed long> h164;
  Hash<signed long int> h264;
  Hash<signed long long> h364;
  Hash<signed long long int> h464;

  ASSERT_EQ(h8(10), 10);
  ASSERT_EQ(h116(10), 10);
  ASSERT_EQ(h216(10), 10);
  ASSERT_EQ(h132(10), 10);
  ASSERT_EQ(h232(10), 10);
  ASSERT_EQ(h164(10), 10);
  ASSERT_EQ(h264(10), 10);
  ASSERT_EQ(h364(10), 10);
  ASSERT_EQ(h464(10), 10);

  ASSERT_GE(h8(-10), 0);
  ASSERT_GE(h116(-10), 0);
  ASSERT_GE(h216(-10), 0);
  ASSERT_GE(h132(-10), 0);
  ASSERT_GE(h232(-10), 0);
  ASSERT_GE(h164(-10), 0);
  ASSERT_GE(h264(-10), 0);
  ASSERT_GE(h364(-10), 0);
  ASSERT_GE(h464(-10), 0);
}

TEST(Hash, unsignedIntegrals) {
  Hash<unsigned char> h8;
  Hash<unsigned short> h116;
  Hash<unsigned short int> h216;
  Hash<unsigned> h132;
  Hash<unsigned int> h232;
  Hash<unsigned long> h164;
  Hash<unsigned long int> h264;
  Hash<unsigned long long> h364;
  Hash<unsigned long long int> h464;

  ASSERT_EQ(h8(10), 10);
  ASSERT_EQ(h116(10), 10);
  ASSERT_EQ(h216(10), 10);
  ASSERT_EQ(h132(10), 10);
  ASSERT_EQ(h232(10), 10);
  ASSERT_EQ(h164(10), 10);
  ASSERT_EQ(h264(10), 10);
  ASSERT_EQ(h364(10), 10);
  ASSERT_EQ(h464(10), 10);

  ASSERT_GE(h8(-10), 0);
  ASSERT_GE(h116(-10), 0);
  ASSERT_GE(h216(-10), 0);
  ASSERT_GE(h132(-10), 0);
  ASSERT_GE(h232(-10), 0);
  ASSERT_GE(h164(-10), 0);
  ASSERT_GE(h264(-10), 0);
  ASSERT_GE(h364(-10), 0);
  ASSERT_GE(h464(-10), 0);
}

TEST(Hash, sizedIntegrals) {
  Hash<U8> const hu8;
  Hash<U16> const hu16;
  Hash<U32> const hu32;
  Hash<U64> const hu64;
  Hash<S8> const hs8;
  Hash<S16> const hs16;
  Hash<S32> const hs32;
  Hash<S64> const hs64;

  ASSERT_EQ(hu8(10), 10);
  ASSERT_EQ(hu16(10), 10);
  ASSERT_EQ(hu32(10), 10);
  ASSERT_EQ(hu64(10), 10);
  ASSERT_EQ(hs8(10), 10);
  ASSERT_EQ(hs16(10), 10);
  ASSERT_EQ(hs32(10), 10);
  ASSERT_EQ(hs64(10), 10);

  ASSERT_GE(hs8(-10), 0);
  ASSERT_GE(hs16(-10), 0);
  ASSERT_GE(hs32(-10), 0);
  ASSERT_GE(hs64(-10), 0);
}

TEST(Hash, floating) {
  Hash<float> const hf;
  Hash<double> const hd;
  Hash<long double> const hld;

  ASSERT_NE(hf(5.14f), 0);
  ASSERT_NE(hf(5.14f), hf(102.3f));

  ASSERT_NE(hd(5.14), 0);
  ASSERT_NE(hd(5.14), hd(102.3));

  ASSERT_NE(hld(5.14L), 0);
  ASSERT_NE(hld(5.14L), hld(102.3L));
}

TEST(Hash, ptr) {
  int x;
  int y;

  Hash<int*> const h;
  ASSERT_EQ(h(&x), h(&x));
  ASSERT_EQ(h(&y), h(&y));
  ASSERT_NE(h(&x), h(&y));
}

struct S {int x;};
namespace cds {
namespace functional {
template <> struct Hash<S> {
  auto operator()(S obj) const noexcept -> Size {
    return Hash<int>()(obj.x);
  }
};
} // namespace functional
} // namespace cds

TEST(Hash, sizBufHash) {
  U8 const v1[1] = {10};
  U8 const v2[2] = {10, 0};
  U8 const v3[4] = {10, 0, 0, 0};
  U8 const v4[8] = {10, 0, 0, 0, 0, 0, 0, 0};

  ASSERT_EQ(cds::functional::impl::hash8<1>(v1), 10);
  ASSERT_EQ(cds::functional::impl::hash16<2>(v2), 10);
  ASSERT_EQ(cds::functional::impl::hash32<4>(v3), 10);
  ASSERT_EQ(cds::functional::impl::hash64<8>(v4), 10);
}

TEST(Hash, transparency) {
  Hash<> const th;
  int val;

  ASSERT_EQ(th(10), 10);
  ASSERT_EQ(th(10L), 10);
  ASSERT_EQ(th(10U), 10);
  ASSERT_EQ(th(10LU), 10);
  ASSERT_EQ(th(10LLU), 10);
  ASSERT_NE(th(5.14f), 0);
  ASSERT_NE(th(5.14), 0);
  ASSERT_NE(th(5.14L), 0);
  ASSERT_NE(th(&val), 0);
  ASSERT_EQ(th(nullptr), 0);
  ASSERT_EQ(th(S{5}), 5);
}

#ifdef DCR_SINCECPP11
TEST(Hash, constexpr11Test) {
  Hash<> const hf;
  static_assert(hf(1) == 1, "Failed constexpr test");
  static_assert(hf(-1) != 0, "Failed constexpr test");
  static_assert(hf(nullptr) == 0, "Failed constexpr test");
}
#endif

#ifdef DCR_SINCECPP14
TEST(Hash, constexpr14Test) {
  constexpr U8 v1[1] = {10};
  constexpr U8 v2[2] = {10, 0};
  constexpr U8 v3[4] = {10, 0, 0, 0};
  constexpr U8 v4[8] = {10, 0, 0, 0, 0, 0, 0, 0};

  static_assert(cds::functional::impl::hash8<1>(v1) == 10, "Failed constexpr test");
  static_assert(cds::functional::impl::hash16<2>(v2) == 10, "Failed constexpr test");
  static_assert(cds::functional::impl::hash32<4>(v3) == 10, "Failed constexpr test");
  static_assert(cds::functional::impl::hash64<8>(v4) == 10, "Failed constexpr test");
}
#endif

#ifdef DCR_SINCECPP20
TEST(Hash, constexpr20Test) {
  Hash<> const hf;

  static_assert(hf(5.14f) != 0, "Failed constexpr test");
  static_assert(hf(5.14) != 0, "Failed constexpr test");
  static_assert(hf(5.14L) != 0, "Failed constexpr test");
}
#endif
