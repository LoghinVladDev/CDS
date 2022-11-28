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
#include <memory>
#include <CDS/memory/UniquePointer>
#include <CDS/memory/SharedPointer>

template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}

int main () {
std::shared_ptr <int> p24121;
p24121.~shared_ptr();
    using namespace cds;
    using namespace cds :: json;
    using namespace cds :: literals;
    using namespace cds :: filesystem;

    HashMap < int, int > m;
    class  T1: HashMap < int, int > {} m2;
    T1 m3;

    JsonArray arr;

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

    UniquePointer <int> p54 = new int (3);
    UniquePointer <int[]> p64 = new int [5];
    SharedPointer <int> s54 = new int (3);
    SharedPointer <int[]> s64 = new int[5];

    auto sp5 = s54;
    std :: cout << * sp5 << '\n';
    std :: cout << sp5 << '\n';
    auto sp6 = s54;
    auto sp7 = sp6;
    std :: cout << sp6 << '\n';
    std :: cout << sp7 << '\n';

    constexpr int thCount = 10;
    SharedPointer <int> sp = new int(0);
    cds :: Function < void () > threadFunc = [tsp = sp]{
        cds :: Function < void () > innerThreadFunc = [itsp = tsp]{
            cds :: Function < void () > innerInnerThreadFunc = [iitsp = itsp]{
                cds :: Function < void () > innerInnerInnerThreadFunc = [iiitsp = iitsp]{
                    cds :: Function < void () > innerInnerInnerInnerThreadFunc = [iiiitsp = iiitsp]{
                        ++ * iiiitsp;
                    };

                    cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
                    for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerInnerInnerThreadFunc ) ); }
                    threads.forEach ([](auto & th){th->start();});
                    threads.forEach ([](auto & th){th->join();});
                    -- * iiitsp;
                };

                cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
                for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerInnerThreadFunc ) ); }
                threads.forEach ([](auto & th){th->start();});
                threads.forEach ([](auto & th){th->join();});
                ++ * iitsp;
            };

            cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
            for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerThreadFunc ) ); }
            threads.forEach ([](auto & th){th->start();});
            threads.forEach ([](auto & th){th->join();});
            -- * itsp;
        };

        cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
        for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerThreadFunc ) ); }
        threads.forEach ([](auto & th){th->start();});
        threads.forEach ([](auto & th){th->join();});
        -- * tsp;
    };

    cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
    for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( threadFunc ) ); }
    threads.forEach ([](auto & th){th->start();});
    threads.forEach ([](auto & th){th->join();});
    std :: cout << * sp << '\n';

    return 0;
}