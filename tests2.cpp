#include <iostream>

#include "src/iterable/DelegateIterableDetails.hpp"
#include "src/iterable/Iterable.hpp"
#include "src/iterable/DelegateIterable.hpp"
#include "src/iterable/DelegateConstIterable.hpp"


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

int main () {
    Lowest l;
    std :: cout << l.g();


    return 0;
}