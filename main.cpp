class A {
private:
    int x;

public:
    A (int x) { this->x = x; }

    int getX() const {
        return x;
    }

    bool operator==(const A &rhs) const {
        return x == rhs.x;
    }

    bool operator!=(const A &rhs) const {
        return !(rhs == *this);
    }
};
class B {
private:
    int x;

public:
    B (int x) { this->x = x; }

    int getX() const {
        return x;
    }
};

#include <iostream>
#include <CDS/Object>
#include <CDS/Traits>

using namespace cds;

int main () {

    A a1 = 3, a2 = 3;
    B b1 = 3, b2 = 3;

    std :: cout << Type < A > :: compare (a1, a2) << '\n';
    std :: cout << Type < A > :: compare (a1, a1) << '\n';
    std :: cout << Type < A > :: compare (a2, a2) << '\n';

    std :: cout << Type < B > :: compare ( b1, b2 ) << '\n';
    std :: cout << Type < B > :: compare ( b1, b1 ) << '\n';
    std :: cout << Type < B > :: compare ( b2, b2 ) << '\n';

    auto l = []( String const & s, auto i ){ return s + i; };
    ArgumentsOf < decltype( l ) > v;-
//    l(""_s, 4);
//    decltype(*((decltype(l) *)(0x10)->operator())) v;

//    functionUtility :: returnOf < decltype ( l ) > t;
//    std :: cout << FunctionOver < decltype ( l ), returnOf < decltype ( l ) >, String, int >;

}