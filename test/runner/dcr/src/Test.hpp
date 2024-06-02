//
// Created by loghin on 12/1/23.
//

#ifndef CDS_DCR_TEST_HPP
#define CDS_DCR_TEST_HPP

#include <vector>
#include <memory>

#define TEST(n1, n2) _TEST(n1, n2)

#define _TEST(suiteName, testName)                              \
  namespace dcr {                                               \
  namespace generated {                                         \
  class suiteName ## testName : public ::dcr::Test {            \
  public:                                                       \
    suiteName ## testName() : Test(#suiteName, #testName) {}    \
    auto _run() const noexcept(false) -> void override;         \
  };                                                            \
                                                                \
  namespace {                                                   \
    ::dcr::TestRegistration<suiteName ## testName>              \
    const testObject ## suiteName ## testName;                  \
  }                                                             \
}                                                               \
}                                                               \
  auto ::dcr::generated::suiteName ## testName::_run() const noexcept(false) -> void

namespace dcr {
class Test {
public:
  Test(char const* suite, char const* test): _suite(suite), _test(test) {}
  virtual ~Test() noexcept = default;

  virtual auto _run() const noexcept(false) -> void = 0;
#ifndef DCR_NO_SUBPROCESS_LOGGING
  auto _execute(std::ostream& out) const noexcept -> bool;
#else
  auto _execute() const noexcept -> bool;
#endif

private:
  char const* _suite;
  char const* _test;
};

namespace internals {
auto tests() -> std::vector<std::unique_ptr<Test const>>&;
} // namespace internals

template <typename TestType>
class TestRegistration {
public:
  TestRegistration() {
    internals::tests().push_back(std::unique_ptr<TestType>(new TestType()));
  }
};
} // namespace dcr

#endif // CDS_DCR_TEST_HPP
