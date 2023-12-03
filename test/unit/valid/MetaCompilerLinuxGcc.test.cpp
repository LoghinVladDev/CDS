// DCR-TEST
// STEPS: compile(linux:gcc),run(linux:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include "../../../src/meta/Compiler.hpp"
#include <string>

using namespace cds::compiler;

#if defined(__GNUC__) && !defined(__clang__)
TEST(Compiler, Id) {
  ASSERT_EQ(std::string(CurrentCompiler::id), "gcc");
  ASSERT_EQ(std::string(CurrentCompiler::name), "GNU gcc");
  // prevents ODR
  ASSERT_NE(static_cast<int>(CurrentCompiler::version), 0);
}
#endif

#ifdef DCR_CPP11
TEST(Compiler, Standard11) {
  static_assert(CurrentStd::version == StdCpp11::version, "Invalid Standard Version");
}
#endif

#ifdef DCR_CPP14
TEST(Compiler, Standard14) {
  static_assert(CurrentStd::version == StdCpp14::version, "Invalid Standard Version");
}
#endif

#ifdef DCR_CPP17
TEST(Compiler, Standard17) {
  static_assert(CurrentStd::version == StdCpp17::version, "Invalid Standard Version");
}
#endif

#ifdef DCR_CPP20
TEST(Compiler, Standard20) {
  static_assert(CurrentStd::version == StdCpp20::version, "Invalid Standard Version");
}
#endif

#ifdef DCR_CPP23
TEST(Compiler, Standard23) {
  static_assert(CurrentStd::version == StdCpp23::version, "Invalid Standard Version");
}
#endif
