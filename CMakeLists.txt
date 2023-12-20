cmake_minimum_required(VERSION 3.16)
project(CDS)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CDS_COMPILER_SPECIFIC_COVERAGE_FLAGS "-fcoverage-mapping -fprofile-instr-generate -O0 -g")
else()
  set(CDS_COMPILER_SPECIFIC_COVERAGE_FLAGS "")
endif()

if(NOT DEFINED CDS_STANDARD)
  set(CDS_STANDARD 23)
  message("--   CDS_STANDARD not explicitly provided, defaulted to ${CDS_STANDARD}")
endif()
set(CMAKE_CXX_STANDARD ${CDS_STANDARD})

if (DEFINED CDS_SANITIZERS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CDS_SANITIZERS}")
endif()

if(NOT DEFINED CDS_COVERAGE)
  message("--   CDS_COVERAGE not explicitly provided, no coverage provided")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CDS_COMPILER_SPECIFIC_COVERAGE_FLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CDS_COMPILER_SPECIFIC_COVERAGE_FLAGS}")
  set(CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW "")
  if(${CDS_COVERAGE} STREQUAL "IDE")
    set(CDS_DCR_INCLUDE_TEST_SOURCES_FOR_COV "")
    set(CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW "CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW")
  elseif(${CDS_COVERAGE} STREQUAL "CI")
  else()
    message("--    CDS_COVERAGE invalid value '${CDS_COVERAGE}'")
  endif()
endif()




set (CDS_INCLUDE_DIRECTORIES include)
include_directories(${CDS_INCLUDE_DIRECTORIES})

if (WIN32)
  set(CDS_LIBRARIES ws2_32)
else()
  set(CDS_LIBRARIES pthread)
endif()

include(FetchContent)

enable_testing()
add_subdirectory(test)
