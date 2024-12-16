// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/exception/NoSuchElementException>
#include <cds/String>
#include <cds/StringView>

namespace {
using cds::Exception;
using cds::RuntimeException;
using cds::NoSuchElementException;
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

TEST(NoSuchElementExceptionTest, construction) {
  ASSERT_TRUE(throws<Exception>([](){
    throw NoSuchElementException();
  }, "No such element exists"));

  ASSERT_TRUE(throws<Exception>([](){
    throw NoSuchElementException("test");
  }, "test"));

  ASSERT_TRUE(throws<RuntimeException>([](){
    throw NoSuchElementException();
  }, "No such element exists"));

  ASSERT_TRUE(throws<RuntimeException>([](){
    throw NoSuchElementException("test");
  }, "test"));

  ASSERT_TRUE(throws<NoSuchElementException>([](){
    throw NoSuchElementException();
  }, "No such element exists"));

  ASSERT_TRUE(throws<NoSuchElementException>([](){
    throw NoSuchElementException("test");
  }, "test"));
}

TEST(NoSuchElementExceptionTest, wrap) {
  ASSERT_TRUE(throws<Exception>([](){
    throw NoSuchElementException(static_cast<std::exception const&>(RuntimeException("test")));
  }, "test"));
  ASSERT_TRUE(throws<RuntimeException>([](){
    throw NoSuchElementException(static_cast<std::exception const&>(RuntimeException("test")));
  }, "test"));
  ASSERT_TRUE(throws<NoSuchElementException>([](){
    throw NoSuchElementException(static_cast<std::exception const&>(RuntimeException("test")));
  }, "test"));
}
