// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/exception/UnionTypeException>
#include <cds/String>
#include <cds/StringView>

namespace {
using cds::Exception;
using cds::RuntimeException;
using cds::UnionTypeException;
using cds::String;
using cds::StringView;

template <typename E, typename R> auto throws(R const& r, StringView message) -> bool {
  try {
    r();
    return false;
  } catch (E const& e) {
    return e.message() == message;
  }
}
}

#if !CDS_ATTR(msvc)
TEST(UnionTypeExceptionTest, expectedMessage) {
  auto const e1 = UnionTypeException::of<int, float>();
  ASSERT_EQ(
      e1.message(),
      "Union Type Exception: 'float' is not "
      "the active Union member. "
      "Actual: 'signed int'"
  );
}

TEST(UnionTypeExceptionTest, expectedThrow) {
  ASSERT_TRUE(
    throws<Exception>([]() {
      throw UnionTypeException::of<int, float>();
    },
    "Union Type Exception: 'float' is not "
    "the active Union member. "
    "Actual: 'signed int'"
  ));

  ASSERT_TRUE(
    throws<RuntimeException>([]() {
      throw UnionTypeException::of<int, float>();
    },
    "Union Type Exception: 'float' is not "
    "the active Union member. "
    "Actual: 'signed int'"
  ));

  ASSERT_TRUE(
    throws<UnionTypeException>([]() {
      throw UnionTypeException::of<int, float>();
    },
    "Union Type Exception: 'float' is not "
    "the active Union member. "
    "Actual: 'signed int'"
  ));
}
#endif
