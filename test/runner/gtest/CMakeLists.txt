FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 9b12f74)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_library(lib.gtest
      ${googletest_SOURCE_DIR}/googletest/src/gtest-all.cc)
  target_include_directories(lib.gtest
      PUBLIC ${googletest_SOURCE_DIR}/googletest/include/
      PRIVATE ${googletest_SOURCE_DIR}/googletest)
endif()

list(TRANSFORM CDS_UNIT_TEST_SOURCES
    PREPEND "../../")

add_executable(cds_unit_tests_gtest
    ${CDS_UNIT_TEST_SOURCES}
    UnitTest.cpp)

target_include_directories(cds_unit_tests_gtest
    PRIVATE ".")

target_link_libraries(cds_unit_tests_gtest
    lib.gtest)

set_target_properties(cds_unit_tests_gtest
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME cds_unit_tests_gtest
    COMMAND cds_unit_tests_gtest)
