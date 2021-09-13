cmake_minimum_required(VERSION 3.16)
project(CDS)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(GCC_COMPILE_OPTIONS "-Wa,-mbig-obj")
        set(GCC_COMPILE_DEBUG_OPTIONS "${GCC_COMPILE_OPTIONS};-O0")
        set(GCC_COMPILE_RELEASE_OPTIONS "${GCC_COMPILE_OPTIONS};-O3")
        add_compile_options("$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
        add_compile_options("$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
    endif()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    endif()
endif()

set(CDS_INCLUDE_DIRECTORIES
        src
        src/collection
        src/collection/unordered
        src/collection/ordered
        src/exception
        src/primitive
        src/cdsIntern
        src/stream

        include
)

include_directories(${CDS_INCLUDE_DIRECTORIES})

set(
        CDS_EXCEPTION
        src/exception/NotImplementedException.h
)

set(
        CDS_PRIMITIVE
        src/primitive/Object.hpp
        src/primitive/Pointer.hpp
        src/primitive/Reference.hpp
        src/primitive/Optional.hpp
        src/primitive/Pair.hpp
        src/primitive/Range.hpp
        src/primitive/String.hpp
        src/primitive/Sequence.hpp
        src/primitive/Regex.hpp
        src/primitive/ParallelSequence.hpp
        src/primitive/Integer.hpp
        src/primitive/Long.hpp
        src/primitive/Float.hpp
        src/primitive/Double.hpp
        src/primitive/Boolean.hpp
        src/primitive/Tuple.hpp
)

set(
        CDS_EXTRA
        src/collection/ordered/BTree.h
)

set(
        CDS_COLLECTION_INTERFACE
        ${CDS_PRIMITIVE}
        ${CDS_EXCEPTION}
        src/collection/Collection.hpp
        src/collection/ordered/List.hpp
        src/collection/unordered/Set.hpp
        src/collection/unordered/SetBase.hpp
        src/collection/unordered/HashMap.hpp
)

set(
        CDS_COLLECTION_ORDERED

        src/collection/ordered/LinkedListPublic.hpp
        src/collection/ordered/LinkedList.hpp

        src/collection/ordered/OrderedSet.hpp
        src/collection/ordered/Queue.hpp
        src/collection/ordered/SingleLinkedList.hpp
        src/collection/ordered/Array.hpp
        src/collection/ordered/StaticArray.hpp
)

set(
        CDS_COLLECTION_UNORDERED

        src/collection/unordered/UnorderedSet.hpp
        src/collection/unordered/HashMap.hpp
        src/collection/unordered/JSON.hpp
)

set(
        CDS_COLLECTION
        ${CDS_COLLECTION_INTERFACE}
        ${CDS_COLLECTION_ORDERED}
        ${CDS_COLLECTION_UNORDERED}
)

set(
        CDS_FUNCTIONAL
        src/functional/Generator.hpp
        src/functional/Random.hpp
)

set(
        CDS_THREADING
        src/threading/Thread.hpp
        src/threading/Semaphore.hpp
        src/threading/Mutex.hpp
        src/threading/Atomic.hpp
)

set(
        CDS_CRYPTO
        src/crypto/primitives/CryptoBlock.hpp
        src/crypto/interface/CryptoOperation.hpp
        src/crypto/primitives/SignatureGeneratorED25519.hpp
        src/crypto/primitives/EncryptorAES.hpp
)

set(
        CDS_STREAM
        src/stream/InputStream.hpp
        src/stream/OutputStream.hpp
        src/stream/Stream.hpp
        src/stream/AbstractStream.hpp
)

set(
        CDS_PLATFORM
        src/platform/File.hpp
        src/platform/Path.hpp
)

set(
        CDS_HEADERS
        ${CDS_COLLECTION}
        ${CDS_EXTRA}
        ${CDS_FUNCTIONAL}
        ${CDS_THREADING}
        ${CDS_CRYPTO}
        ${CDS_STREAM}
        ${CDS_PLATFORM}
        src/std-types.h
        src/cdsIntern/Concepts.hpp
        src/cdsIntern/Traits.hpp
        src/cdsIntern/Types.hpp
)

if (WIN32)
    set(
            CDS_LIBRARIES
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
)
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

set(CMAKE_CXX_STANDARD 20)

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

    test_suite(${ARGV0} primitive Boolean)
    test_suite(${ARGV0} primitive Double)
    test_suite(${ARGV0} primitive Float)
    test_suite(${ARGV0} primitive Integer)
    test_suite(${ARGV0} primitive Long)
    test_suite(${ARGV0} primitive Optional)
    test_suite(${ARGV0} primitive Pair)
    test_suite(${ARGV0} primitive Pointer)
    test_suite(${ARGV0} primitive Reference)
    test_suite(${ARGV0} primitive String)
    test_suite(${ARGV0} primitive Sequence)

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

test_set(20)
test_set(17)
test_set(14)
test_set(11)