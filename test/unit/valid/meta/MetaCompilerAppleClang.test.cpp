// DCR-TEST
// STEPS: compile(apple:clang),run(apple:clang)
// STD: 11+

#include "cds/meta/Compiler"
#include <string>
#include "UnitTest.hpp"

using namespace cds::compiler;

#if defined(__clang__) && defined(__APPLE__)
TEST(MetaCompilerAppleClang, Id) {
  ASSERT_EQ(std::string(CurrentCompiler::id), "clang");
  ASSERT_EQ(std::string(CurrentCompiler::name), "LLVM/Apple clang");
  // prevents ODR
  ASSERT_NE(static_cast<int>(CurrentCompiler::version), 0);
}
#endif

#ifdef DCR_CPP11
TEST(MetaCompilerAppleClang, Standard11) {
  static_assert(CurrentStd::version == StdCpp11::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-11");
}
#endif

#ifdef DCR_CPP14
TEST(MetaCompilerAppleClang, Standard14) {
  static_assert(CurrentStd::version == StdCpp14::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-14");
}
#endif

#ifdef DCR_CPP17
TEST(MetaCompilerAppleClang, Standard17) {
  static_assert(CurrentStd::version == StdCpp17::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-17");
}
#endif

#ifdef DCR_CPP20
TEST(MetaCompilerAppleClang, Standard20) {
  static_assert(CurrentStd::version == StdCpp20::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-20");
}
#endif

#ifdef DCR_CPP23
TEST(MetaCompilerAppleClang, Standard23) {
  static_assert(CurrentStd::version == StdCpp23::version, "Invalid Standard Version");
  ASSERT_EQ(std::string(CurrentStd::literal), "cpp-23");
}
#endif
