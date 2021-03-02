cmake_minimum_required(VERSION 3.16)
project(CDS)

set(CMAKE_CXX_STANDARD 20)

set(CDS_INCLUDE_DIRECTORIES
        src
        src/collection
        src/collection/unordered
        src/collection/ordered
        src/exception
        src/primitive

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
        src/primitive/String.cpp)

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
        CDS_HEADERS
        ${CDS_COLLECTION}
        ${CDS_EXTRA}
        src/std-types.h
        src/primitive/Integer.hpp src/primitive/Long.hpp src/primitive/Float.hpp src/primitive/Double.hpp src/primitive/Boolean.hpp src/primitive/PrimitiveGenerator.hpp src/collection/unordered/JSON.hpp include/CDS/JSON src/collection/ordered/Array.hpp src/collection/ordered/StaticArray.hpp include/CDS/Array include/CDS/NotImplementedException)

set(
        CDS_GLOBAL_HEADERS ${CDS_INCLUDE_DIRECTORIES} CACHE INTERNAL "DIRS"
)

add_executable(
        CDS-dummy
        main.cpp
        ${CDS_HEADERS}
)

target_link_libraries(
        CDS-dummy
)