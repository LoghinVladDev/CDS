#include <CDS/LinkedHashMap>
#include <CDS/HashMap>
#include <CDS/HashSet>
#include <CDS/LinkedHashSet>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/threading/Atomic>
#include <CDS/threading/Mutex>
#include <CDS/threading/Lock>
#include <CDS/threading/Thread>
#include <CDS/util/JSON>
#include <mutex>
#include <thread>
#include <pthread.h>
#include <functional>
#include "src/functional/FunctionalInterface.hpp"
#include <variant>
#include <CDS/filesystem/Path>
#include <CDS/filesystem/Walk>

template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}

int main () {

    using namespace cds;
    using namespace cds :: json;
    using namespace cds :: literals;
    using namespace cds :: filesystem;

    JsonObject json;
    json.put ( "test1", 2 );
    json.put ( "test2", 4.3f );
    json.put ( "test3", "test" );
    json.put ( "test1", "test2"_s );
    json.at ( "test1" ) = "test2"_s;
    json.get ( "test3" ) = 5;

    StringView sv = "test";
    String path = "test";
    filesystem :: Path p = sv;
    filesystem :: Path p2 ( "test2" );
    filesystem :: Path p3 = path;

    p3 /= "test";
    p3 = "test";

    std :: cout << json << '\n';
    for ( auto & e : filesystem :: walk ( Path(__FILE__).parent() / "src" ) ) {
        std :: cout << e << '\n';
    }
}