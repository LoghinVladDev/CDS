list(TRANSFORM CDS_UNIT_TEST_SOURCES
    PREPEND "../../")

set(DCR_SOURCES
    src/Dcr.cpp
    src/Test.cpp)

add_library(lib.dcr
    STATIC
    ${DCR_SOURCES})

add_executable(cds_unit_tests_dcr
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
