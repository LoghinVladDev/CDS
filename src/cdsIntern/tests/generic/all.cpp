/*
 * Created by loghin on 05.04.2021.
 */

#include "primitive/StringTest.h"
#include "collection/CollectionTest.h"
#include "collection/mutableCollection/MutableCollectionTest.h"
#include "collection/mutableCollection/list/ListTest.h"
#include "collection/set/SetTest.h"
#include "collection/unordered/JsonTest.h"

#include <CDS/Array>
#include <CDS/Pair>
#include <CDS/memory/UniquePointer>
#include <CDS/util/JSON>

namespace {

    using cds::uint32;

    using cds::String;
    using cds::UniquePointer;
    using cds::Pair;

    using glob::Test;

    using glob::StringTest;

    using glob::CollectionTest;
    using glob::MutableCollectionTest;
    using glob::ListTest;
    using glob::SetTest;

    using glob::JsonTest;

    template <typename TestType>
    __CDS_NoDiscard auto createTest (cds::StringView name) noexcept -> Pair <UniquePointer <Test>, String> {
        return {cds::makeUnique <TestType> (), name};
    }
}


auto main (int argc, char** argv) -> int {

  bool silent = false;
    if (argc > 1) {
      for (auto const& arg : cds::Array<cds::String> (argv + 1, argv + argc)) {
        if (arg == "-silent") {
          silent = true;
        }
      }
    }

    auto const start = std::chrono::high_resolution_clock::now();

    auto test = [silent] ( Test & lTest, String const & name ) {
        return lTest.disableLog(silent).start(name);
    };

    auto tests = cds :: arrayOf (
            createTest <StringTest> ("StringTest"),
            createTest <CollectionTest> ("CollectionTest"),
            createTest <MutableCollectionTest> ("MutableCollectionTest"),
            createTest <SetTest> ("SetTest"),
            createTest <ListTest> ("ListTest"),
            createTest <JsonTest> ("JsonTest")
    );

    uint32 failedTestCount = 0U;
    uint32 successfulTestCount = 0U;
    auto const totalTestCount = static_cast <uint32> (tests.size());

    for ( auto & t : tests ) {
        if ( ! test ( * t.first(), t.second() ) ) {
            ++ failedTestCount;
        } else {
            ++ successfulTestCount;
        }
    }

    auto const end = std::chrono::high_resolution_clock::now();

    auto const diff = std::chrono::duration_cast < std::chrono::nanoseconds > ( (end - start) );

    double const power = std::pow(10, 9);
    std::cout << "Total Duration: " << diff.count() << " nanoseconds ( " << (static_cast < double > (diff.count()) / power) << " seconds )" << '\n';
    std::cout << "Out of " << totalTestCount << " tests, " << successfulTestCount << " passed and " << failedTestCount << " failed\n";

    return 0;
}