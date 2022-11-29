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
#include <CDS/memory/RawPointer>
#include <CDS/memory/WeakPointer>


template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}

int main () {
    std::make_shared<int>(3);
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

    constexpr int thCount = 2;
    SharedPointer < Atomic < int > > sp = new Atomic <int> (0);
    cds :: Function threadFunc = [tsp = sp]{
        cds :: Function innerThreadFunc = [itsp = tsp]{
            cds :: Function innerInnerThreadFunc = [iitsp = itsp]{
                cds :: Function innerInnerInnerThreadFunc = [iiitsp = iitsp]{
                    cds :: Function innerInnerInnerInnerThreadFunc = [iiiitsp = iiitsp]{
                        ++ * iiiitsp;
                    };

                    cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
                    for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerInnerInnerThreadFunc ) ); }
                    threads.forEach ([](auto & th){th->start();});
                    -- * iiitsp;
                    threads.forEach ([](auto & th){th->join();});
                };

                cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
                for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerInnerThreadFunc ) ); }
                threads.forEach ([](auto & th){th->start();});
                ++ * iitsp;
                threads.forEach ([](auto & th){th->join();});
            };

            cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
            for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerThreadFunc ) ); }
            threads.forEach ([](auto & th){th->start();});
            -- * itsp;
            threads.forEach ([](auto & th){th->join();});
        };

        cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
        for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerThreadFunc ) ); }
        threads.forEach ([](auto & th){th->start();});
        -- * tsp;
        threads.forEach ([](auto & th){th->join();});
    };

    cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
    for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( threadFunc ) ); }
    threads.forEach ([](auto & th){th->start();});
    threads.forEach ([](auto & th){th->join();});
    std :: cout << * sp << '\n';

    auto f = []{
        SharedPointer < int > intSP = new int(3);
        WeakPointer < int > intWP = intSP;
        WeakPointer < int > intWP2 = intWP;

        if ( auto intSP2 = intWP2.acquire() ) {
            std :: cout << * intSP2 << '\n';
        } else {
            std :: cout << "Expired\n";
        }

        intSP.reset();

        if ( auto intSP3 = intWP.acquire() ) {
            std :: cout << * intSP3 << '\n';
        } else {
            std :: cout << "Expired\n";
        }

        if ( auto intSP2 = intWP2.acquire() ) {
            std :: cout << * intSP2 << '\n';
        } else {
            std :: cout << "Expired\n";
        }
    };

    f();

    auto g = []{
        return UniquePointer <int> (new int (3));
    };

    auto h = []{
        auto h1 = []{
            return UniquePointer <int> (new int (5));
        };

        return h1();
    };

    std :: cout << *g() + *h() << '\n';

    auto gs = []{
        return SharedPointer <int> (new int (3));
    };

    auto hs = []{
        auto h1 = []{
            return SharedPointer <int> (new int (5));
        };

        return h1();
    };

    std :: cout << *gs() + *hs() << '\n';

    auto ptr1 = cds :: makeUnique <int> ( 3 );
    auto ptr2 = cds :: makeUnique <int[]> ( 5 );
    auto sptr1 = cds :: makeShared <int> ( 3 );
    auto sptr2 = cds :: makeShared <int[]> ( 5 );

    auto wptr2 = sptr2.observe();
    auto sptr3 = wptr2.acquire();

    Tuple t = {1, 3.4f, String ("test"), false, String ("test2")};
    Tuple t2 = t;

    std :: cout << t << '\n' << t2 << '\n';
    Tuple t3 = std :: move (t2);
    std :: cout << t << '\n' << t2 << '\n' << t3 << '\n';

    return 0;
}