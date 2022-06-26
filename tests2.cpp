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
    (void)pColl->some(2, [](int){return true;});
    (void)pColl->atLeast(2, [](int){return true;});
    (void)pColl->atMost(2, [](int){return true;});
    (void)pColl->moreThan(2, [](int){return true;});
    (void)pColl->fewerThan(2, [](int){return true;});
    (void)pColl->count([](int){return true;});
    (void)pColl->all([](int){return true;});
    (void)pColl->any([](int){return true;});
    (void)pColl->none([](int){return true;});

    pColl->removeOf ( 5, * pColl );
    pColl->removeFirstOf ( * pColl );
    pColl->removeLastOf ( * pColl );
    pColl->removeAllOf ( * pColl );

    pColl->removeNotOf ( 5, * pColl );
    pColl->removeFirstNotOf ( * pColl );
    pColl->removeLastNotOf ( * pColl );
    pColl->removeAllNotOf ( * pColl );

    pColl->removeOf ( 5, { 1, 3, 4 } );
    pColl->removeFirstOf ( { 1, 3, 4 } );
    pColl->removeLastOf ( { 1, 3, 4 } );
    pColl->removeAllOf ( { 1, 3, 4 } );

    pColl->removeNotOf ( 5, { 1, 3, 4 } );
    pColl->removeFirstNotOf ( { 1, 3, 4 } );
    pColl->removeLastNotOf ( { 1, 3, 4 } );
    pColl->removeAllNotOf ( { 1, 3, 4 } );

    (void)pColl->containsAnyOf ( * pColl );
    (void)pColl->containsAllOf ( * pColl );
    (void)pColl->containsAnyNotOf ( * pColl );
    (void)pColl->containsAllNotOf ( * pColl );

    (void)pColl->containsAnyOf ( { 1, 2, 3 } );
    (void)pColl->containsAllOf ( { 1, 2, 3 } );
    (void)pColl->containsAnyNotOf ( { 1, 2, 3 } );
    (void)pColl->containsAllNotOf ( { 1, 2, 3 } );

    Collection < Collection < int > :: ConstIterator > * pItColl;
    (void) pColl->findThat(3, *pItColl, [](int){return true;});
    (void) pColl->findFirstThat([](int){return true;});
    (void) pColl->findLastThat([](int){return true;});
    (void) pColl->findAllThat(*pItColl, [](int){return true;});

    (void) pColl->findOf ( 3, * pItColl, * pColl );
    (void) pColl->findFirstOf ( * pColl );
    (void) pColl->findLastOf ( * pColl );
    (void) pColl->findAllOf ( * pItColl, * pColl );

    (void) pColl->findNotOf ( 3, * pItColl, * pColl );
    (void) pColl->findFirstNotOf ( * pColl );
    (void) pColl->findLastNotOf ( * pColl );
    (void) pColl->findAllNotOf ( * pItColl, * pColl );

    (void) pColl->findOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pColl->findFirstOf ( { 1, 2, 3 } );
    (void) pColl->findLastOf ( { 1, 2, 3 } );
    (void) pColl->findAllOf ( * pItColl, { 1, 2, 3 } );

    (void) pColl->findNotOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pColl->findFirstNotOf ( { 1, 2, 3 } );
    (void) pColl->findLastNotOf ( { 1, 2, 3 } );
    (void) pColl->findAllNotOf ( * pItColl, { 1, 2, 3 } );

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