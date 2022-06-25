#include <iostream>

#include "src/experimental/Array.hpp"


enum class E1 {
    f1 = 0x01,
    f2 = 0x02
};

template < typename D >
class B1 {
public:
    int g() {
        return static_cast < D * > ( this )->f();
    }
};

template < typename D >
class B2 : public B1 < D > {

};

class Lowest : public B2 < Lowest > {
public:
    int f() {
        return 2;
    }
};

using namespace cds :: experimental;

int main () {
    Lowest l;
    std :: cout << l.g();

    Array < int > a;

    a.pushBack (3);
    a.pushBack (2);
    a.pushBack (1);
    a.pushBack (2);
    a.pushBack (3);

    for ( auto & e : a ) {
        std :: cout << e;
    }

    return 0;
}