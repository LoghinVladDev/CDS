// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include <cds/Utility>
#include "UnitTest.hpp"
#include <cds/StringView>
#include <chrono>
#include "../Shared.hpp"

using namespace cds;

namespace {

using testing::iteq;
using testing::citeq;
} // namespace

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

CDS_ATTR(constexpr(14)) auto testCopy() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto const eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto const e = impl::copy(begin(srcBuf), end(srcBuf), begin(dstBuf));
  auto const reachedExpected = e == end(dstBuf);
  auto const eqAtEnd = citeq(srcBuf, dstBuf);
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testCopyPartial() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto const eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto const e = impl::copy(begin(srcBuf), end(srcBuf) - 2, begin(dstBuf));
  auto const reachedExpected = e == end(dstBuf) - 2;
  auto const eqAtEndFull = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));
  auto const eqAtEndPartial = iteq(begin(srcBuf), end(srcBuf) - 2, begin(dstBuf), end(dstBuf) - 2);

  return !eqAtStart1 && !eqAtStart2 && reachedExpected && !eqAtEndFull && eqAtEndPartial;
}

CDS_ATTR(constexpr(14)) auto testCopyN() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto const eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto const e = impl::copyN(begin(srcBuf), 4, begin(dstBuf));
  auto const reachedExpected = e == end(dstBuf);
  auto const eqAtEnd = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testCopyNPartial() -> bool {
  int srcBuf[4] = {1, 2, 3, 4};
  int dstBuf[4] = {0, 0, 0, 0};

  auto const eqAtStart1 = iteq(srcBuf, srcBuf + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));

  auto const e = impl::copyN(begin(srcBuf), 2, begin(dstBuf));
  auto const reachedExpected = e == end(dstBuf) - 2;
  auto const eqAtEndFull = iteq(begin(srcBuf), end(srcBuf), begin(dstBuf), end(dstBuf));
  auto const eqAtEndPartial = iteq(begin(srcBuf), end(srcBuf) - 2, begin(dstBuf), end(dstBuf) - 2);

  return !eqAtStart1 && !eqAtStart2 && reachedExpected && !eqAtEndFull && eqAtEndPartial;
}

CDS_ATTR(constexpr(14)) auto testFill() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto const eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto const e = impl::fill(begin(dstBuf), end(dstBuf), 1);
  auto const reachedExpected = e == end(dstBuf);
  auto const eqAtEnd = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testFillPartial() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto const eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto const e = impl::fill(begin(dstBuf) + 1, end(dstBuf) - 1, 1);
  auto const reachedExpected = e == end(dstBuf) - 1;
  auto const eqAtEndFull = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  auto const eqAtEndPartial = iteq(begin(cmpAfter), end(cmpAfter) - 2, begin(dstBuf) + 1, end(dstBuf) - 1);
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && !eqAtEndFull && eqAtEndPartial;
}

CDS_ATTR(constexpr(14)) auto testFillN() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto const eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto const e = impl::fillN(begin(dstBuf), 4, 1);
  auto const reachedExpected = e == end(dstBuf);
  auto const eqAtEnd = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  return !eqAtStart1 && !eqAtStart2 && reachedExpected && eqAtEnd;
}

CDS_ATTR(constexpr(14)) auto testFillNPartial() -> bool {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};

  auto const eqAtStart1 = iteq(cmpAfter, cmpAfter + 4, dstBuf, dstBuf + 4);
  auto const eqAtStart2 = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));

  auto const e = impl::fillN(begin(dstBuf), 2, 1);
  auto const reachedExpected = e == end(dstBuf) - 2;
  auto const eqAtEndFull = iteq(begin(cmpAfter), end(cmpAfter), begin(dstBuf), end(dstBuf));
  auto const eqAtEndPartial = iteq(begin(cmpAfter), end(cmpAfter) - 2, begin(dstBuf), end(dstBuf) - 2);

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

TEST(Utility, copyNInitialize) {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};
  ASSERT_FALSE(citeq(dstBuf, cmpAfter));
  impl::copyNInitialize(dstBuf, 4, cmpAfter);
  ASSERT_TRUE(citeq(dstBuf, cmpAfter));
}

TEST(Utility, moveInitialize) {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};
  ASSERT_FALSE(citeq(dstBuf, cmpAfter));
  impl::moveInitialize(dstBuf, dstBuf + 4, cmpAfter);
  ASSERT_TRUE(citeq(dstBuf, cmpAfter));
}

TEST(Utility, moveNInitialize) {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};
  ASSERT_FALSE(citeq(dstBuf, cmpAfter));
  impl::moveNInitialize(dstBuf, 4, cmpAfter);
  ASSERT_TRUE(citeq(dstBuf, cmpAfter));
}

TEST(Utility, fillNInitialize) {
  int dstBuf[4] = {0, 0, 0, 0};
  int cmpAfter[4] = {1, 1, 1, 1};
  ASSERT_FALSE(citeq(dstBuf, cmpAfter));
  impl::fillNInitialize(dstBuf, 4, 1);
  ASSERT_TRUE(citeq(dstBuf, cmpAfter));
}

TEST(Utility, destructN) {
  int dstBuf[4] = {0, 0, 0, 0};
  impl::destructN(dstBuf, 4);
}

#ifdef DCR_SINCECPP14
TEST(Utility, cpp14Constexpr) {
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
