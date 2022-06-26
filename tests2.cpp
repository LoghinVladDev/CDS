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
    std :: cout.flush();

    Collection < int > * pColl = nullptr;

    (void)pColl->begin();
    (void)pColl->end();
    (void)pColl->cbegin();
    (void)pColl->cend();
    pColl->remove(pColl->begin());
    pColl->remove(pColl->cbegin());
    pColl->remove(pColl->end());
    pColl->remove(pColl->cend());
    pColl->remove(5);

    (void)pColl->size();
    (void)pColl->empty();
    (void)(bool)*pColl;
    (void)pColl->toString();
    (void)pColl->hash();
    (void)pColl->equals(* pColl);
    pColl->clear();
    (void)pColl->find(5);
    (void)pColl->contains(5);
    pColl->add(5);
    pColl->addAll(5, 3, 1);
    pColl->addAllOf(std :: initializer_list<int>{1, 4, 5});
    pColl->addAllOf(* pColl);

    pColl->removeIf (
            3,
            [](int){return true;}
    );

    pColl->removeFirstIf (
            [](int){return true;}
    );

    pColl->removeLastIf (
            [](int){return true;}
    );

    pColl->removeAllIf (
            [](int){return true;}
    );

    pColl->forEach([](int){});
    pColl->some(2, [](int){return true;});
    pColl->atLeast(2, [](int){return true;});
    pColl->atMost(2, [](int){return true;});
    pColl->moreThan(2, [](int){return true;});
    pColl->fewerThan(2, [](int){return true;});
    pColl->count([](int){return true;});
    pColl->all([](int){return true;});
    pColl->any([](int){return true;});
    pColl->none([](int){return true;});


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