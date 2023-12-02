list(TRANSFORM CDS_UNIT_TEST_SOURCES
    PREPEND "../../")

if(DEFINED CDS_DCR_INCLUDE_TEST_SOURCES_FOR_COV)
  set(DCR_COVERAGE_TEST_SOURCES ${CDS_UNIT_TEST_SOURCES})
else()
  set(DCR_COVERAGE_TEST_SOURCES "")
endif()

set(DCR_SOURCES
    src/Dcr.cpp
    src/Test.cpp
    src/DcrMain.cpp)

add_library(lib.dcr
    STATIC
    ${DCR_SOURCES})

target_compile_definitions(
    lib.dcr
    PRIVATE
    DCR_OMIT_MAIN
    ${CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW}
)

add_executable(cds_unit_tests_dcr
    ${CDS_UNIT_TEST_SOURCES}
    UnitTest.cpp)

target_include_directories(lib.dcr
    PRIVATE ".")

target_include_directories(cds_unit_tests_dcr
    PRIVATE ".")

target_link_libraries(cds_unit_tests_dcr
    lib.dcr)

set_target_properties(cds_unit_tests_dcr
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME cds_unit_tests_dcr
    COMMAND cds_unit_tests_dcr)
