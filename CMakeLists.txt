cmake_minimum_required(VERSION 3.16)
project(CDS)

set(CMAKE_CXX_STANDARD 23)

# DCMAKE_EXPORT_COMPILE_COMMANDS=1
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(GCC_COMPILE_OPTIONS "-Wa,-mbig-obj")
        set(GCC_COMPILE_DEBUG_OPTIONS "${GCC_COMPILE_OPTIONS};-Os")
        set(GCC_COMPILE_RELEASE_OPTIONS "${GCC_COMPILE_OPTIONS};-O3")
        add_compile_options("$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
        add_compile_options("$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
    endif()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /Zc:__cplusplus")
    endif()
elseif (linux)
    set(GCC_COMPILE_OPTIONS "-Wa")
    set(GCC_COMPILE_DEBUG_OPTIONS "${GCC_COMPILE_OPTIONS}")
    set(GCC_COMPILE_RELEASE_OPTIONS "${GCC_COMPILE_OPTIONS};-O3")
    add_compile_options("$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
    add_compile_options("$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
endif()

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")

#set(
#        CDS_SANITIZE_FLAGS
#        "-fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address -fsanitize-address-use-after-return=always -fsanitize-address-use-after-scope -fsanitize=memory -fsanitize-memory-track-origins=2 ASAN_OPTIONS=detect_stack_use_after_return=1:detect_stack_use_after_return=1:detect_leaks=1:check_initialization_order=1"
#)
#
#
#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CDS_SANITIZE_FLAGS}")
#
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} ${CDS_SANITIZE_FLAGS}")

set (
        CDS_INCLUDE_DIRECTORIES
        include
)

include_directories(${CDS_INCLUDE_DIRECTORIES})

set(
        CDS_HEADERS
)

if (WIN32)
    set(
            CDS_LIBRARIES
            ws2_32
    )
else()
    set(
            CDS_LIBRARIES
            pthread
    )
endif()

add_executable(
        CDS-dummy
        main.cpp
        ${CDS_HEADERS}
        src/collection/set/treeSet/treeSet/impl/TreeSetCTAD.hpp src/shared/iterator/NodeIteratorTraits.hpp)

target_link_libraries(
        CDS-dummy
        ${CDS_LIBRARIES}
)

add_executable(
        CDS-dummy2
        tests2.cpp
        ${CDS_HEADERS}
)

target_link_libraries(
        CDS-dummy2
        ${CDS_LIBRARIES}
)

if(WIN32)
    add_executable(
            CDS-wintests
            wTests.cpp
            ${CDS_HEADERS}
    )

    target_link_libraries(
            CDS-wintests
    )
endif()

if(WIN32)
else()
    target_link_libraries(CDS-dummy pthread)
endif()

cmake_minimum_required(VERSION 3.16)
project(CDS)

set(CMAKE_CXX_STANDARD 23)

macro(test_suite)
    set(
            CPP${ARGV0}_${ARGV2}_SRC
            src/cdsIntern/tests/cpp${ARGV0}/${ARGV1}/${ARGV2}Test.cpp
            src/cdsIntern/tests/cpp${ARGV0}/${ARGV1}/${ARGV2}Test.h
    )

    set(
            CPP${ARGV0}_TEST_ALL_SRC
            ${CPP${ARGV0}_TEST_ALL_SRC}
            ${CPP${ARGV0}_${ARGV2}_SRC}
    )

    add_executable(
            cpp${ARGV0}_test_${ARGV2}_only
            ${CPP${ARGV0}_TEST_DEFAULT_SRC}
            ${CPP${ARGV0}_${ARGV2}_SRC}
            src/cdsIntern/tests/cpp${ARGV0}/${ARGV1}/${ARGV2}Only.cpp
    )

    target_link_libraries(
            cpp${ARGV0}_test_${ARGV2}_only
            ${CDS_LIBRARIES}
    )
endmacro()

macro(test_set)
    set(CMAKE_CXX_STANDARD ${ARGV0})

    set(
            CPP${ARGV0}_TEST_DEFAULT_SRC
            src/cdsIntern/tests/cpp${ARGV0}/Test.cpp
            src/cdsIntern/tests/cpp${ARGV0}/Test.h
    )

    set(
            CPP${ARGV0}_TEST_ALL_SRC
            ${CPP${ARGV0}_TEST_DEFAULT_SRC}
    )

    test_suite(${ARGV0} primitive String)
    test_suite(${ARGV0} collection Collection)
    test_suite(${ARGV0} collection/mutableCollection MutableCollection)
    test_suite(${ARGV0} collection/mutableCollection/list List)
    test_suite(${ARGV0} collection/set Set)
    test_suite(${ARGV0} collection/unordered Json)

    add_executable(
            cpp${ARGV0}_test_all
            src/cdsIntern/tests/cpp${ARGV0}/all.cpp
            ${CPP${ARGV0}_TEST_ALL_SRC}
    )

    target_link_libraries(
            cpp${ARGV0}_test_all
            ${CDS_LIBRARIES}
    )
endmacro()

macro(test_suite_nodup)

    file(
        GLOB
        ${ARGV1}_SOURCES
        src/cdsIntern/tests/generic/${ARGV1}/${ARGV2}Test*.cpp    
        src/cdsIntern/tests/generic/${ARGV1}/${ARGV2}Test*.h    
        src/cdsIntern/tests/generic/${ARGV1}/${ARGV2}Test*.hpp    
    )

    set(
            CPP${ARGV0}_${ARGV2}_SRC
            ${${ARGV1}_SOURCES}
    )

    set(
            CPP${ARGV0}_TEST_ALL_SRC
            ${CPP${ARGV0}_TEST_ALL_SRC}
            ${CPP${ARGV0}_${ARGV2}_SRC}
    )

    add_executable(
            cpp${ARGV0}_test_${ARGV2}_only
            ${CPP${ARGV0}_TEST_DEFAULT_SRC}
            ${CPP${ARGV0}_${ARGV2}_SRC}
            src/cdsIntern/tests/generic/${ARGV1}/${ARGV2}Only.cpp
    )

    target_link_libraries(
            cpp${ARGV0}_test_${ARGV2}_only
            ${CDS_LIBRARIES}
    )
endmacro()

macro(test_set_nodup)
    set(CMAKE_CXX_STANDARD ${ARGV0})

    set(
            CPP${ARGV0}_TEST_DEFAULT_SRC
            src/cdsIntern/tests/generic/Test.cpp
            src/cdsIntern/tests/generic/Test.h
    )

    set(
            CPP${ARGV0}_TEST_ALL_SRC
            ${CPP${ARGV0}_TEST_DEFAULT_SRC}
    )

    test_suite_nodup(${ARGV0} primitive String)
    test_suite_nodup(${ARGV0} collection Collection)
    test_suite_nodup(${ARGV0} collection/mutableCollection MutableCollection)
    test_suite_nodup(${ARGV0} collection/mutableCollection/list List)
    test_suite_nodup(${ARGV0} collection/set Set)
    test_suite_nodup(${ARGV0} collection/unordered Json)

    add_executable(
            cpp${ARGV0}_test_all
            src/cdsIntern/tests/generic/all.cpp
            ${CPP${ARGV0}_TEST_ALL_SRC}
    )

    target_link_libraries(
            cpp${ARGV0}_test_all
            ${CDS_LIBRARIES}
    )
endmacro()

test_set_nodup(11)
test_set_nodup(14)
test_set_nodup(17)
test_set_nodup(20)