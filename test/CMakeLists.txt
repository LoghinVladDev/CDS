add_subdirectory(unit)

list(TRANSFORM CDS_UNIT_TEST_SOURCES PREPEND "unit/")

add_subdirectory(runner/gtest)
add_subdirectory(runner/dcr)
