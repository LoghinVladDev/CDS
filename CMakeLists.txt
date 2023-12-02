cmake_minimum_required(VERSION 3.16)
project(CDS)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


if(NOT DEFINED CDS_STANDARD)
  set(CDS_STANDARD 23)
  message("--   CDS_STANDARD not explicitly provided, defaulted to ${CDS_STANDARD}")
endif()
set(CMAKE_CXX_STANDARD ${CDS_STANDARD})

if(NOT DEFINED CDS_SANITIZERS)
  set(CDS_SANITIZERS "-fsanitize=address -fsanitize=undefined")
  message("--   CDS_SANITIZERS not explicitly provided, defaulted to ${CDS_SANITIZERS}")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CDS_SANITIZERS}")


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
