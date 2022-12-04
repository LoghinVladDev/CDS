//
// Created by loghin on 05.04.2021.
//

#include "primitive/StringTest.h"
#include "collection/CollectionTest.h"
#include "collection/mutableCollection/MutableCollectionTest.h"
#include "collection/mutableCollection/list/ListTest.h"
#include "collection/set/SetTest.h"
#include "collection/unordered/JsonTest.h"

#include <CDS/Array>
#include <CDS/Pair>
#include <CDS/memory/SharedPointer>
#include <CDS/util/JSON>
#include <CDS/Union>

int main () {


    Union < int, float, String > unionTest = "test";
    unionTest.emplace < float > (3.4f);
    std :: cout << unionTest.get <1>() << '\n';
    return 0;

    auto start = std::chrono::high_resolution_clock::now();

    auto test = [] ( Test & test, String const & name ) {
        return test.start(name);
    };

    cds :: Array < Pair < SharedPointer < Test >, String > > tests = {
            Pair < SharedPointer < Test >, String > { new StringTest (),  "StringTest" },
            Pair < SharedPointer < Test >, String > { new CollectionTest (),  "CollectionTest" },
            Pair < SharedPointer < Test >, String > { new MutableCollectionTest (),  "MutableCollectionTest" },
            Pair < SharedPointer < Test >, String > { new SetTest (),  "SetTest" },
            Pair < SharedPointer < Test >, String > { new ListTest (),  "ListTest" },
            Pair < SharedPointer < Test >, String > { new JsonTest (),  "JsonTest" }
    };

    for ( auto & t : tests ) {
        if ( ! test ( * t.first(), t.second() ) ) {
            return 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto diff = std::chrono::duration_cast < std::chrono::nanoseconds > ( (end - start) );

    double power = std::pow(10, 9);
    std::cout << "Total Duration: " << diff.count() << " nanoseconds ( " << static_cast < double > (diff.count()) / power << " seconds )" << '\n';\

    return 0;
}