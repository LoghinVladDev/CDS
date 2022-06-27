#include <iostream>

#include <CDS/Object>

#include <CDS/experimental/Collection>
#include <CDS/experimental/MutableCollection>
#include <CDS/experimental/Set>
#include <CDS/experimental/Map>
#include <CDS/experimental/List>


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
    std :: cout << sizeof ( Collection < int > ) << '\n';
    std :: cout << sizeof ( MutableCollection < int > ) << '\n';
    std :: cout << sizeof ( List < int > ) << '\n';
    std :: cout.flush();

    List < int > * pList = nullptr;
    (void) pList->begin();
    (void) pList->end();
    (void) pList->cbegin();
    (void) pList->cend();
    (void) pList->rbegin();
    (void) pList->rend();
    (void) pList->crbegin();
    (void) pList->crend();

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

    MutableCollection < int > * pMutColl;

    MutableCollection < int > :: Iterator e = pMutColl->begin();
    MutableCollection < int > :: Iterator e2 = pMutColl->end();

    pMutColl->remove(pMutColl->begin());
    pMutColl->remove(e);

    Collection < MutableCollection < int > :: Iterator > * pItMutColl;

    (void) pMutColl->findThat(3, * pItMutColl, [](int &){return true;});
    (void) pMutColl->findFirstThat([](int &){return true;});
    (void) pMutColl->findLastThat([](int &){return true;});
    (void) pMutColl->findAllThat( *pItMutColl, [](int &){return true;});

    (void)pMutColl->begin();
    (void)pMutColl->end();
    (void)pMutColl->cbegin();
    (void)pMutColl->cend();
    pMutColl->remove(pMutColl->begin());
    pMutColl->remove(pMutColl->cbegin());
    pMutColl->remove(pMutColl->end());
    pMutColl->remove(pMutColl->cend());
    pMutColl->remove(5);

    (void)pMutColl->size();
    (void)pMutColl->empty();
    (void)(bool)*pMutColl;
    (void)pMutColl->toString();
    (void)pMutColl->hash();
    (void)pMutColl->equals(* pMutColl);
    pMutColl->clear();
    (void)pMutColl->find(5);
    (void)pMutColl->contains(5);
    pMutColl->add(5);
    pMutColl->addAll(5, 3, 1);
    pMutColl->addAllOf(std :: initializer_list<int>{1, 4, 5});
    pMutColl->addAllOf(* pMutColl);

    pMutColl->removeIf (
            3,
            [](int){return true;}
    );

    pMutColl->removeFirstIf (
            [](int){return true;}
    );

    pMutColl->removeLastIf (
            [](int){return true;}
    );

    pMutColl->removeAllIf (
            [](int){return true;}
    );

    pMutColl->forEach([](int){});
    (void)pMutColl->some(2, [](int){return true;});
    (void)pMutColl->atLeast(2, [](int){return true;});
    (void)pMutColl->atMost(2, [](int){return true;});
    (void)pMutColl->moreThan(2, [](int){return true;});
    (void)pMutColl->fewerThan(2, [](int){return true;});
    (void)pMutColl->count([](int){return true;});
    (void)pMutColl->all([](int){return true;});
    (void)pMutColl->any([](int){return true;});
    (void)pMutColl->none([](int){return true;});

    pMutColl->removeOf ( 5, * pMutColl );
    pMutColl->removeFirstOf ( * pMutColl );
    pMutColl->removeLastOf ( * pMutColl );
    pMutColl->removeAllOf ( * pMutColl );

    pMutColl->removeNotOf ( 5, * pMutColl );
    pMutColl->removeFirstNotOf ( * pMutColl );
    pMutColl->removeLastNotOf ( * pMutColl );
    pMutColl->removeAllNotOf ( * pMutColl );

    pMutColl->removeOf ( 5, { 1, 3, 4 } );
    pMutColl->removeFirstOf ( { 1, 3, 4 } );
    pMutColl->removeLastOf ( { 1, 3, 4 } );
    pMutColl->removeAllOf ( { 1, 3, 4 } );

    pMutColl->removeNotOf ( 5, { 1, 3, 4 } );
    pMutColl->removeFirstNotOf ( { 1, 3, 4 } );
    pMutColl->removeLastNotOf ( { 1, 3, 4 } );
    pMutColl->removeAllNotOf ( { 1, 3, 4 } );

    (void)pMutColl->containsAnyOf ( * pMutColl );
    (void)pMutColl->containsAllOf ( * pMutColl );
    (void)pMutColl->containsAnyNotOf ( * pMutColl );
    (void)pMutColl->containsAllNotOf ( * pMutColl );

    (void)pMutColl->containsAnyOf ( { 1, 2, 3 } );
    (void)pMutColl->containsAllOf ( { 1, 2, 3 } );
    (void)pMutColl->containsAnyNotOf ( { 1, 2, 3 } );
    (void)pMutColl->containsAllNotOf ( { 1, 2, 3 } );

    (void) pMutColl->findThat(3, *pItColl, [](int){return true;});
    (void) pMutColl->findFirstThat([](int){return true;});
    (void) pMutColl->findLastThat([](int){return true;});
    (void) pMutColl->findAllThat(*pItColl, [](int){return true;});

    (void) pMutColl->findOf ( 3, * pItColl, * pMutColl );
    (void) pMutColl->findFirstOf ( * pMutColl );
    (void) pMutColl->findLastOf ( * pMutColl );
    (void) pMutColl->findAllOf ( * pItColl, * pMutColl );

    (void) pMutColl->findNotOf ( 3, * pItColl, * pMutColl );
    (void) pMutColl->findFirstNotOf ( * pMutColl );
    (void) pMutColl->findLastNotOf ( * pMutColl );
    (void) pMutColl->findAllNotOf ( * pItColl, * pMutColl );

    (void) pMutColl->findOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllOf ( * pItColl, { 1, 2, 3 } );

    (void) pMutColl->findNotOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllNotOf ( * pItColl, { 1, 2, 3 } );

    (void) pMutColl->findThat(3, *pItMutColl, [](int){return true;});
    (void) pMutColl->findFirstThat([](int){return true;});
    (void) pMutColl->findLastThat([](int){return true;});
    (void) pMutColl->findAllThat(*pItMutColl, [](int){return true;});

    (void) pMutColl->findOf ( 3, * pItMutColl, * pMutColl );
    (void) pMutColl->findFirstOf ( * pMutColl );
    (void) pMutColl->findLastOf ( * pMutColl );
    (void) pMutColl->findAllOf ( * pItMutColl, * pMutColl );

    (void) pMutColl->findNotOf ( 3, * pItMutColl, * pMutColl );
    (void) pMutColl->findFirstNotOf ( * pMutColl );
    (void) pMutColl->findLastNotOf ( * pMutColl );
    (void) pMutColl->findAllNotOf ( * pItMutColl, * pMutColl );

    (void) pMutColl->findOf ( 3, * pItMutColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllOf ( * pItMutColl, { 1, 2, 3 } );

    (void) pMutColl->findNotOf ( 3, * pItMutColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllNotOf ( * pItMutColl, { 1, 2, 3 } );

    (void)pMutColl->some(2, [](int &){return true;});
    (void)pMutColl->atLeast(2, [](int &){return true;});
    (void)pMutColl->atMost(2, [](int &){return true;});
    (void)pMutColl->moreThan(2, [](int &){return true;});
    (void)pMutColl->fewerThan(2, [](int &){return true;});
    (void)pMutColl->count([](int &){return true;});
    (void)pMutColl->all([](int &){return true;});
    (void)pMutColl->any([](int &){return true;});
    (void)pMutColl->none([](int &){return true;});

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