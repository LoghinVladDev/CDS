// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/exception/Exception>
#include <cds/StringView>

namespace {
using cds::Exception;
using cds::StringView;
}

TEST(ExceptionTest, construction) {
  class DException : public Exception {
  public:
    [[nodiscard]] auto message() const noexcept -> cds::impl::BaseStringView<char> override {
      return "test";
    }
  };

  DException const ex;
  ASSERT_EQ(ex.message(), "test");
}

TEST(ExceptionTest, throwing) {
  auto thrower = []() {
    class DException : public Exception {
    public:
      [[nodiscard]] auto message() const noexcept -> cds::impl::BaseStringView<char> override {
        return "test2";
      }
    };

    throw DException();
  };

  try {
    thrower();
  } catch (Exception const& e) {
    ASSERT_EQ(e.message(), "test2");
  }

  try {
    thrower();
  } catch (std::exception const& e) {
    ASSERT_EQ(StringView{e.what()}, "test2");
  }
}
