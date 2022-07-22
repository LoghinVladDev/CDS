#include <iostream>

#include <CDS/Object>

#include <CDS/experimental/Collection>
#include <CDS/experimental/MutableCollection>
#include <CDS/experimental/Set>
#include <CDS/experimental/Map>
#include <CDS/experimental/List>
#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>


enum class E1 {
    f1 = 0x01,
    f2 = 0x02
};

class A {
public:
    virtual void f () = 0;
};

class B : public A {
public:
    void f () override {
        std :: cout << "test\n";
    }
};

void f ( auto (*g) () -> void ) noexcept {
    g();
}


template < typename Last >
void printAll ( Last && value ) {
    std :: cout << value << '\n';
}

template < typename First, typename ... TheRest >
void printAll ( First && first, TheRest && ... theRest ) {
    std :: cout << first << ", ";
    printAll ( std :: forward < TheRest > ( theRest ) ... );
}

void f2();

#include <chrono>
#include <vector>
#include <CDS/Range>

class C {
public:
    C ( int ) noexcept {}
    C ( double ) noexcept (false) {}
};

template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}

using namespace cds :: experimental;

void timingTest (int n) {

    Array < int > a;
    std :: vector < int > v;
    auto pClassic = new int [n];

    timed (
            "Classic 100m insertion",
            [pClassic, n] {
                for (int i = 0; i < n; ++i) {
                    pClassic [i] = i;
                }
            }
    );

    timed (
            "CDS 100m insertion",
            [& a, n] {
                for (int i = 0; i < n; ++i) {
                    a.emplaceBack(i);
                }
            }
    );

    timed (
            "STL 100m insertion",
            [& v, n] {
                for (int i = 0; i < n; ++i) {
                    v.emplace_back(i);
                }
            }
    );

    timed (
            "CDS 100m iter",
            [& a] {
                for ( auto & e : a ) {
                    e = 5;
                }
            }
    );

    timed (
            "STL 100m iter",
            [& v] {
                for ( auto & e : v ) {
                    e = 5;
                }
            }
    );

    timed (
            "CDS 100m manual iter",
            [& a] {
                for ( cds :: Size i = 0, l = a.size(); i < l; ++ i ) {
                    a[i] = 5;
                }
            }
    );

    timed (
            "CDS 100m manual by addr iter",
            [& a, n] {
                auto p = a.data();
                for ( cds :: Size i = 0, l = a.size(); i < l; ++ i ) {
                    p[i] = 5;
                }
            }
    );

    timed (
            "STL 100m manual iter",
            [& v] {
                for ( cds :: Size i = 0, l = v.size(); i < l; ++ i ) {
                    v[i] = 5;
                }
            }
    );

    timed (
            "STL 100m manual by addr iter",
            [& v] {
                auto p = v.data();
                for ( cds :: Size i = 0, l = v.size(); i < l; ++ i ) {
                    p[i] = 5;
                }
            }
    );

    timed (
            "Classic 100m manual iter",
            [pClassic, n] {
                for ( cds :: Size i = 0, l = n; i < l; ++ i ) {
                    pClassic [i] = 5;
                }
            }
    );

    delete [] pClassic;
}

int main () {


    std :: cout << sizeof ( Array < int > ) << '\n';

    LinkedList < int > a;
    std :: vector < int > v;

    a.pushBackAll ( 1, 2, 3 );
    std :: cout << a << '\n';

    a.insertBefore ( a.begin(), -1 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( a.begin(), -2 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertBefore ( ++ a.begin(), 4 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( ++ a.begin(), 5 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertBefore ( a.end(), 7 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( a.end(), 8 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertBefore ( -- a.end(), 9 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( -- a.end(), 10 );
    std :: cout << a << '\n';
    std::cout.flush();

    std :: cout << a.sub ( 2, 5 ) << '\n';


    Array < int > otherArray;
    List < int > & otherAsList = otherArray;

    otherArray.pushBackAllOf ( cds :: Range (20, 30) );

    List < int > * pList = & a;
    (void) pList->begin();
    (void) pList->end();
    (void) pList->cbegin();
    (void) pList->cend();
    (void) pList->rbegin();
    (void) pList->rend();
    (void) pList->crbegin();
    (void) pList->crend();


    pList->pushBack(3);
    pList->pushFront(3);
    pList->pushBackAll(1, 2, 3);
    pList->pushFrontAll (1, 2, 3);
    pList->pushBackAllOf({1, 2, 3});
    pList->pushBackAllOf(otherArray);
    pList->pushBackAllOf(otherArray.begin(), otherArray.end());
    pList->pushFrontAllOf({1, 2, 3});
    pList->pushFrontAllOf(otherArray);
    pList->pushFrontAllOf(otherArray.begin(), otherArray.end());
    pList->pushBackAllOf(otherAsList);
    pList->pushBackAllOf(otherAsList.begin(), otherAsList.end());
    pList->pushFrontAllOf(otherAsList);
    pList->pushFrontAllOf(otherAsList.begin(), otherAsList.end());

    std :: cout << a << '\n';

//    pList->insertBefore( pList->begin(), 3);
//    pList->insertBefore ( pList->cbegin(), 3);
//    pList->insertAfter( pList->begin(), 3);
//    pList->insertAfter ( pList->cbegin(), 3);
//    pList->insertAllBefore ( pList->begin(), 1, 2, 3);
//    pList->insertAllBefore ( pList->cbegin(), 1, 2, 3);
//    pList->insertAllAfter ( pList->begin(), 1, 2, 3);
//    pList->insertAllAfter ( pList->cbegin(), 1, 2, 3);
//    pList->insertAllOfBefore ( pList->begin(), { 1, 2, 3 } );
//    pList->insertAllOfBefore ( pList->cbegin(), { 1, 2, 3 } );
//    pList->insertAllOfAfter ( pList->begin(), { 1, 2, 3 } );
//    pList->insertAllOfAfter ( pList->cbegin(), { 1, 2, 3 } );
//    pList->insertAllOfBefore ( pList->begin(), * pList );
//    pList->insertAllOfBefore ( pList->cbegin(), * pList );
//    pList->insertAllOfAfter ( pList->begin(), * pList );
//    pList->insertAllOfAfter ( pList->cbegin(), * pList );
//    pList->insertAllOfBefore ( pList->begin(), pList->begin(), pList->end() );
//    pList->insertAllOfBefore ( pList->cbegin(), pList->begin(), pList->end() );
//    pList->insertAllOfAfter ( pList->begin(), pList->begin(), pList->end() );
//    pList->insertAllOfAfter ( pList->cbegin(), pList->begin(), pList->end() );

    pList->sub(otherAsList, 2, 3);
    (*pList)[2] = 3;
    pList->removeAt ( { 1, 3 } );

    cds :: experimental :: Array < cds :: Index > indices = { 2, 3 };
    pList->removeAt ( indices );

    /// TODO : client/server for sort
//    pList->sort();
//    pList->sort(& cds :: predicates :: greaterThan);
//    pList->sort([](int a, int b){ return a < b; });

    pList->replace ( 3, 1, 2 );
    pList->replaceFirst ( 1, 2 );
    pList->replaceLast ( 1, 2 );
    pList->replaceAll ( 2, 1 );
    pList->replaceOf ( 2, otherAsList, 1 );
    pList->replaceFirstOf ( otherAsList, 1 );
    pList->replaceLastOf ( otherAsList, 1 );
    pList->replaceAllOf ( otherAsList, 1 );
    pList->replaceNotOf ( 2, otherAsList, 1 );
    pList->replaceFirstNotOf ( otherAsList, 1 );
    pList->replaceLastNotOf ( otherAsList, 1 );
    pList->replaceAllNotOf ( otherAsList, 1 );
    pList->replaceOf ( 2, { 1, 2, 3 }, 1 );
    pList->replaceFirstOf ( { 1, 2, 3 }, 1 );
    pList->replaceLastOf ( { 1, 2, 3 }, 1 );
    pList->replaceAllOf ( { 1, 2, 3 }, 1 );
    pList->replaceNotOf ( 2, { 1, 2, 3 }, 1 );
    pList->replaceFirstNotOf ( { 1, 2, 3 }, 1 );
    pList->replaceLastNotOf ( { 1, 2, 3 }, 1 );
    pList->replaceAllNotOf ( { 1, 2, 3 }, 1 );

    pList->replaceThat ( 3, [](int x){ return x > 2; }, 1 );
    pList->replaceFirstThat ( [](int x){ return x > 2; }, 1 );
    pList->replaceLastThat ( [](int x){ return x > 2; }, 1 );
    pList->replaceAllThat ( [](int x){ return x > 2; }, 1 );

    pList->replaceThatBy ( 4, [](int x){ return x == 1; }, [](int & x) { return x + 3; } );
    pList->replaceFirstThatBy ( [](int x){ return x == 1; }, [](int & x) { return x + 3; } );
    pList->replaceLastThatBy ( [](int x){ return x == 1; }, [](int & x) { return x + 3; } );
    pList->replaceAllThatBy ( [](int x){ return x == 1; }, [](int & x) { return x + 3; } );

    pList->indicesOf ( 3, otherAsList, 2 );
    (void) pList->firstIndexOf ( 2 );
    (void) pList->lastIndexOf ( 2 );
    pList->allIndicesOf ( otherAsList, 2 );

    pList->indicesOfFrom ( 3, otherAsList, * pList );
    (void) pList->firstIndexOfFrom ( * pList );
    (void) pList->lastIndexOfFrom ( * pList );
    pList->allIndicesOfFrom ( otherAsList, * pList );
    pList->indicesOfNotFrom ( 3, otherAsList, * pList );
    (void) pList->firstIndexOfNotFrom ( * pList );
    (void) pList->lastIndexOfNotFrom ( * pList );
    pList->allIndicesOfNotFrom ( otherAsList, * pList );

    pList->indicesOfFrom ( 3, otherAsList, { 1, 2, 3 } );
    (void) pList->firstIndexOfFrom ( { 1, 2, 3 } );
    (void) pList->lastIndexOfFrom ( { 1, 2, 3 } );
    pList->allIndicesOfFrom ( otherAsList, { 1, 2, 3 } );
    pList->indicesOfNotFrom ( 3, otherAsList, { 1, 2, 3 } );
    (void) pList->firstIndexOfNotFrom ( { 1, 2, 3 } );
    (void) pList->lastIndexOfNotFrom ( { 1, 2, 3 } );
    pList->allIndicesOfNotFrom ( otherAsList, { 1, 2, 3 } );

    pList->indicesOfThat ( 3, otherAsList, [](int x) { return x % 2 == 0; } );
    (void) pList->firstIndexOfThat ( [](int x) { return x % 2 == 0; } );
    (void) pList->lastIndexOfThat ( [](int x) { return x % 2 == 0; } );
    pList->allIndicesOfThat ( otherAsList, [](int x) { return x % 2 == 0; } );

    Collection < int > * pColl = & a;

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
    pColl->insert(5);
    pColl->insertAll(5, 3, 1);
    pColl->insertAllOf(std :: initializer_list<int>{1, 4, 5});
    pColl->insertAllOf(otherAsList);
    pColl->insertAllOf(otherArray);

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

    pColl->removeOf ( 5, otherAsList );
    pColl->removeFirstOf ( otherAsList );
    pColl->removeLastOf ( otherAsList );
    pColl->removeAllOf ( otherAsList );

    pColl->removeNotOf ( 5, otherAsList );
    pColl->removeFirstNotOf ( otherAsList );
    pColl->removeLastNotOf ( otherAsList );
    pColl->removeAllNotOf ( otherAsList );

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

    MutableCollection < int > * pMutColl = & a;

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
    pMutColl->insert(5);
    pMutColl->insertAll(5, 3, 1);
    pMutColl->insertAllOf({1, 4, 5});
    pMutColl->insertAllOf(otherAsList);
    pMutColl->insertAllOf(pMutColl->begin(), pMutColl->end());

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

    pMutColl->removeOf ( 5, otherAsList );
    pMutColl->removeFirstOf ( otherAsList );
    pMutColl->removeLastOf ( otherAsList );
    pMutColl->removeAllOf ( otherAsList );

    pMutColl->removeNotOf ( 5, otherAsList );
    pMutColl->removeFirstNotOf ( otherAsList );
    pMutColl->removeLastNotOf ( otherAsList );
    pMutColl->removeAllNotOf ( otherAsList );

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

    pMutColl->insert (5) = 3;

    timingTest ( 1000 );

    return 0;
}