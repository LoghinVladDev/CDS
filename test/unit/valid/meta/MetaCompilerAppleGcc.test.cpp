// DCR-TEST
// STEPS: compile(macos:gcc),run(macos:gcc)
// STD: 11+

#include "cds/meta/Compiler"
#include <string>
#include "UnitTest.hpp"

using namespace cds::compiler;

#if defined(__GNUC__) && !defined(__clang__)
TEST(MetaCompilerAppleGcc, Id) {
  ASSERT_EQ(std::string(CurrentCompiler::id), "gcc");
  ASSERT_EQ(std::string(CurrentCompiler::name), "GNU gcc");
  // prevents ODR
  ASSERT_NE(static_cast<int>(CurrentCompiler::version), 0);
}
#endif

#ifdef DCR_CPP11
TEST(MetaCompilerAppleGcc, Standard11) {
  static_assert(CurrentStd::version == StdCpp11::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-11");
}
#endif

#ifdef DCR_CPP14
TEST(MetaCompilerAppleGcc, Standard14) {
  static_assert(CurrentStd::version == StdCpp14::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-14");
}
#endif

#ifdef DCR_CPP17
TEST(MetaCompilerAppleGcc, Standard17) {
  static_assert(CurrentStd::version == StdCpp17::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-17");
}
#endif

#ifdef DCR_CPP20
TEST(MetaCompilerAppleGcc, Standard20) {
  static_assert(CurrentStd::version == StdCpp20::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-20");
}
#endif

#ifdef DCR_CPP23
TEST(MetaCompilerAppleGcc, Standard23) {
  static_assert(CurrentStd::version == StdCpp23::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-23");
}
#endif
