cmake_minimum_required(VERSION 3.17)
project(CDS)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(src/collection)
include_directories(src/collection/ordered)
include_directories(src/collection/unordered)
include_directories(src/primitive)
include_directories(src/exception)

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
        CDS_HEADERS
        ${CDS_COLLECTION}
        ${CDS_EXTRA}
        src/std-types.h
)

add_executable(
        CDS-dummy
        main.cpp
        ${CDS_HEADERS}
)