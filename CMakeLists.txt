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
        src/primitive/View.hpp
        src/primitive/Sequence.hpp
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
)

set(
        CDS_COLLECTION_UNORDERED

        src/collection/unordered/UnorderedSet.hpp
        src/collection/unordered/HashMap.hpp
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
)

set(
        CDS_THREADING
        src/threading/Thread.hpp
        src/threading/Semaphore.hpp
        src/threading/Mutex.hpp
        include/CDS/Timer)

set(
        CDS_CRYPTO
        src/crypto/primitives/CryptoBlock.hpp
        src/crypto/interface/CryptoOperation.hpp src/crypto/primitives/SignatureGeneratorED25519.hpp src/crypto/primitives/EncryptorAES.hpp)

set(
        CDS_STREAM
        src/stream/InputStream.hpp src/stream/OutputStream.hpp src/stream/Stream.hpp src/stream/AbstractStream.hpp)

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
        src/primitive/Integer.hpp
        src/primitive/Long.hpp
        src/primitive/Float.hpp
        src/primitive/Double.hpp
        src/primitive/Boolean.hpp
        src/cdsIntern/PrimitiveGenerator.hpp
        src/collection/unordered/JSON.hpp
        src/collection/ordered/Array.hpp
        src/collection/ordered/StaticArray.hpp
        src/functional/Random.hpp
        src/primitive/Tuple.hpp
        src/threading/Atomic.hpp
        src/cdsIntern/Concepts.hpp
        src/cdsIntern/Traits.hpp
        src/cdsIntern/Types.hpp
        include/CDS/InputStream
        include/CDS/OutputStream
        include/CDS/Stream
        include/CDS/AbstractStream
)

#set(
#        CDS_LIB_SRC
#        src/primitive/String.cpp
#)

set(
        CDS_GLOBAL_HEADERS ${CDS_INCLUDE_DIRECTORIES} CACHE INTERNAL "DIRS"
)


#add_library( CDS ${CDS_LIB_SRC} )

if (WIN32)
    set(
            CDS_LIBRARIES
#            CDS
    )
else()
    set(
            CDS_LIBRARIES
#            CDS
            pthread
    )
endif()

add_executable(
        CDS-dummy
        main.cpp
#        ${CDS_LIB_SRC}
        ${CDS_HEADERS}
)
target_link_libraries(
        CDS-dummy
        ${CDS_LIBRARIES}
)

add_executable(
        CDS-dummy2
        tests2.cpp
#        ${CDS_LIB_SRC}
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
#            ${CDS_LIB_SRC}
            ${CDS_HEADERS}
    )

    target_link_libraries(
            CDS-wintests
#            ${CDS_LIBRAIES}
    )
endif()

if(WIN32)
else()
    target_link_libraries(CDS-dummy pthread)
endif()

set(
        TEST_DEFAULT_SRC
        src/cdsIntern/tests/Test.cpp
        src/cdsIntern/tests/Test.h
)

set(
        TEST_ALL_SRC
        include/CDS/Types include/CDS/crypto/CryptoBlock include/CDS/crypto/CryptoOperation src/crypto/interface/AsymmetricCryptoOperation.hpp src/crypto/interface/SymmetricCryptoOperation.hpp src/crypto/interface/Encryptor.hpp src/crypto/interface/Decryptor.hpp src/crypto/interface/SignatureGenerator.hpp src/crypto/interface/SignatureVerifier.hpp include/CDS/crypto/SignatureVerifier src/crypto/interface/Hasher.hpp src/crypto/primitives/DecryptorAES.hpp)

macro(testSuite)
    set(
            ${ARGV1}_SRC
            src/cdsIntern/tests/${ARGV0}/${ARGV1}Test.cpp
            src/cdsIntern/tests/${ARGV0}/${ARGV1}Test.h
    )

    set(
            TEST_ALL_SRC
            ${TEST_ALL_SRC}
            ${${ARGV1}_SRC}
    )

    add_executable(Test_${ARGV1}_Only
            ${${ARGV1}_SRC}
            ${TEST_DEFAULT_SRC}
#            ${CDS_LIB_SRC}
            src/cdsIntern/tests/${ARGV0}/${ARGV1}Only.cpp
    )

    target_link_libraries(
            Test_${ARGV1}_Only
            ${CDS_LIBRARIES}
    )
endmacro()

testSuite(primitive Boolean)
testSuite(primitive Double)
testSuite(primitive Float)
testSuite(primitive Integer)
testSuite(primitive Long)
testSuite(primitive Optional)
testSuite(primitive Pair)
testSuite(primitive Pointer)
testSuite(primitive Reference)
testSuite(primitive String)
testSuite(primitive Sequence)

testSuite(collection/unordered Json)

add_executable(
        Test_All
        src/cdsIntern/tests/all.cpp
        ${TEST_ALL_SRC}
#        ${CDS_LIB_SRC}
)

target_link_libraries(
        Test_All
        ${CDS_LIBRARIES}
)
