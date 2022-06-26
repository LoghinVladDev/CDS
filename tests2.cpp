#include <iostream>

#include <CDS/Object>

#include <CDS/experimental/Collection>


enum class E1 {
    f1 = 0x01,
    f2 = 0x02
};

template < typename D >
class B {
public:
    void f ();
};

class D : public B < D > {
public:
    using t = int;
};

template < typename D1 >
void B < D1 > :: f () {
    typename D1 :: t x = 3;
    std :: cout << x << '\n';
}


using namespace cds :: experimental;

int main () {
    D d;
    d.f();
    std :: cout << sizeof ( Collection < int > );

    Collection < int > * pColl;

    pColl->removeIf (
            3,
            [](int){return true;}
    );


//    Array < int > a;
//
//    a.pushBack (3);
//    a.pushBack (2);
//    a.pushBack (1);
//    a.pushBack (2);
//    a.pushBack (3);
//
//    for ( auto & e : a ) {
//        std :: cout << e << ' ';
//    }
//    std :: cout << '\n';
//    for ( auto & e : ( Collection < int > const & ) a ) {
//        std :: cout << e << ' ';
//    }
//
//    std :: cout << sizeof ( Array < int >  ) - 64 * 4;

    return 0;
}