#include <iostream>

#include "src/experimental/Array.hpp"


enum class E1 {
    f1 = 0x01,
    f2 = 0x02
};


using namespace cds :: experimental;

int main () {
    Array < int > a;

    a.pushBack (3);
    a.pushBack (2);
    a.pushBack (1);
    a.pushBack (2);
    a.pushBack (3);

    for ( auto & e : a ) {
        std :: cout << e << ' ';
    }
    std :: cout << '\n';
    for ( auto & e : ( Collection < int > const & ) a ) {
        std :: cout << e << ' ';
    }

    return 0;
}