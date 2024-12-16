// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/exception/RuntimeException>
#include <cds/String>
#include <cds/StringView>

namespace {
using cds::Exception;
using cds::RuntimeException;
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

TEST(RuntimeExceptionTest, construction) {
  ASSERT_TRUE(throws<Exception>([](){
    throw RuntimeException();
  }, ""));

  ASSERT_TRUE(throws<Exception>([](){
    throw RuntimeException("test");
  }, "test"));
  ASSERT_TRUE(throws<RuntimeException>([](){
    throw RuntimeException();
  }, ""));

  ASSERT_TRUE(throws<RuntimeException>([](){
    throw RuntimeException("test");
  }, "test"));
}

TEST(RuntimeExceptionTest, wrap) {
  ASSERT_TRUE(throws<Exception>([](){
    throw RuntimeException(static_cast<std::exception const&>(RuntimeException("test")));
  }, "test"));
  ASSERT_TRUE(throws<RuntimeException>([](){
    throw RuntimeException(static_cast<std::exception const&>(RuntimeException("test")));
  }, "test"));
}
