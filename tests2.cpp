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
#include <mutex>
#include <thread>
#include <pthread.h>
#include <functional>
#include "src/functional/FunctionalInterface.hpp"

template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}
int f2(int a) {return a * 2;}

void gC(int a, float b, cds :: String const & c) {
    std :: cout << a << '\n' << b << '\n' << c << '\n';
}

bool gP (int a, int b, float c, float d, cds :: String const & e, cds :: String const & f) {
    return a== b && c == d && e == f;
}

cds :: String gM ( int a, float b, int c, cds :: String const & d, float e ) {
    return cds :: String () + a + b + c + d + e;
}

cds :: String gS () {
    return "test";
}

int main () {

    cds :: Array < int > arr;
    cds :: Iterable < int > & coll = arr;
    std :: vector < int > v;

    for ( int i = 0; i < cds :: limits :: S32_MAX / 512; ++ i ) {
        arr.pushBack(i);
        v.push_back(i);
    }

    int even;
    timed ( "arr count even", [&]{
        even = 0;
        std :: cout << arr.count([](int e){return e % 2 == 0;}) << '\n';
    });
    timed ( "coll count even", [&]{
        even = 0;
        std :: cout << coll.count([](int e){return e % 2 == 0;}) << '\n';
    });
    timed ( "vect count even", [&]{
        even = 0;
        std :: cout << std :: count_if ( v.begin(), v.end(), [](int e) { return e % 2 == 0; } ) << '\n';
    });

    return 0;
}