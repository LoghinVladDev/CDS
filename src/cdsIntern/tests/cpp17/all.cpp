//
// Created by loghin on 05.04.2021.
//

#include "primitive/StringTest.h"
#include "primitive/IntegerTest.h"
#include "primitive/LongTest.h"
#include "primitive/BooleanTest.h"
#include "collection/unordered/JsonTest.h"

int main () {
    auto test = [] ( Test & test, String const & name ) {
        return test.start(name);
    };

    Array < Pair < SharedPointer < Test >, String > > tests = {
            Pair < SharedPointer < Test >, String > { new StringTest (),  "StringTest" },
            Pair < SharedPointer < Test >, String > { new BooleanTest (),  "BooleanTest" },
            Pair < SharedPointer < Test >, String > { new IntegerTest (),  "IntegerTest" },
            Pair < SharedPointer < Test >, String > { new LongTest (),  "LongTest" },
            Pair < SharedPointer < Test >, String > { new JsonTest (),  "JsonTest" }
    };

    for ( auto & t : tests ) {
        if ( ! test ( * t.first(), t.second() ) )
            break;
    }
}