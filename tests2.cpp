#include <iostream>

#include <CDS/experimental/TreeSet>
#include <CDS/String>
#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>
#include <CDS/experimental/LinkedHashSet>
#include <CDS/experimental/LinkedHashMap>
#include <CDS/experimental/HashMap>
#include "src/experimental/collection_new_iterable_model/shared/iterator/IteratorSort.hpp"
#include "src/experimental/collection_new_iterable_model/shared/iterator/impl/IteratorSort.hpp"
#include <chrono>
#include <list>
#include <vector>
#include <functional>
template < typename T >
T f () {
    return T();
}

template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}

int main () {

    using namespace cds :: experimental;
    std :: cout << (int) __hidden :: __impl :: __helpers :: __lg(17) << '\n';

    cds :: experimental :: TreeSet < cds :: String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std :: cout << ( cds :: String ( "2" ) > cds :: String ( "5" ) ) << '\n';
    cds :: experimental :: TreeSet < cds :: String > ceva = { 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };
    std :: cout << ceva << '\n';
    using namespace cds :: experimental;

    Array < int > a = { 9, 1, 2, 7, 4, 5, 8, 1 ,2 ,8 ,9, 7, 0, 4, 5, 1, 2,5, 2, 3, 8,7,7,5,2,5,4,4,8,6,1,1,1,5,1,8,65,2,1,5,8,96,4,2,4,7,8,5,6,4,1,5,8,7 };
    Array < int > a2 = { 9, 1, 2, 7, 4, 5, 8, 1 ,2 ,8 ,9, 7, 0, 4, 5, 1, 2,5, 2, 3, 8,7,7,5,2,5,4,4,8,6,1,1,1,5,1,8,65,2,1,5,8,96,4,2,4,7,8,5,6,4,1,5,8,7 };
    LinkedList < int > ll = { 9, 1, 2, 7, 4, 5, 8, 1 ,2 ,8 ,9, 7, 0, 4, 5, 1, 2,5, 2, 3, 8,7,7,5,2,5,4,4,8,6,1,1,1,5,1,8,65,2,1,5,8,96,4,2,4,7,8,5,6,4,1,5,8,7 };
    LinkedList < int > ll2 = { 9, 1, 2, 7, 4, 5, 8, 1 ,2 ,8 ,9, 7, 0, 4, 5, 1, 2,5, 2, 3, 8,7,7,5,2,5,4,4,8,6,1,1,1,5,1,8,65,2,1,5,8,96,4,2,4,7,8,5,6,4,1,5,8,7 };

    a.sort();
    std :: cout << a << '\n';
    std :: cout.flush();

    ll.sort();
    std :: cout << ll << '\n';
    std :: cout.flush();

    List < int > & al1 = a2;
    List < int > & al2 = ll2;

    al1.sort();
    std :: cout << a2 << '\n';
    std :: cout.flush();

    al2.sort();
    std :: cout << ll2 << '\n';
    std :: cout.flush();

    a.sort(cds :: predicates :: greaterThan < int >);
    std :: cout << a << '\n';
    std :: cout.flush();

    ll.sort(cds :: predicates :: greaterThan < int >);
    std :: cout << ll << '\n';
    std :: cout.flush();

    al1.sort(cds :: predicates :: greaterThan < int >);
    std :: cout << a2 << '\n';
    std :: cout.flush();

    al2.sort(cds :: predicates :: greaterThan < int >);
    std :: cout << ll2 << '\n';
    std :: cout.flush();

    srand(time(nullptr));
    int limit = 10000;
    timed("cds array sort", [limit]{
        Array < int > a;

        for ( int i = 0; i < limit; ++ i ) {
            a.pushBack(rand());
        }

        a.sort();
    });

    timed("cds list-based sort", [limit]{
        Array < int > a;

        for ( int i = 0; i < limit; ++ i ) {
            a.pushBack(rand());
        }

        ((List < int > &) a ).sort();
    });

    al1.remove(al1.begin());
    al1.remove(al1.rbegin());

    std :: cout << al1 << '\n';

    std :: vector < int > v = {1,2 ,3 ,4, 5};


    Array < int > testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( -- -- testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( -- testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ ++ ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ ++ ++ ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( -- -- testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( -- testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ ++ ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ ++ ++ ++ testArr.begin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( -- -- testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( -- testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ ++ ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertBefore ( ++ ++ ++ ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( -- -- testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( -- testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ ++ ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};

    std :: cout << std :: boolalpha << testArr.insertAfter ( ++ ++ ++ ++ testArr.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testArr << '\n';
    testArr = {1, 2, 3};


    std :: cout << "--------------------LIST--------------------\n";
    LinkedList < int > testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( -- -- testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( -- testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( ++ testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( ++ ++ testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( ++ ++ ++ testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

//    std :: cout << std :: boolalpha << testList.insertBefore ( ++ ++ ++ ++ testList.begin(), 4 ) << " "; // obvious sigsegv
//    std :: cout << std :: dec << testList << '\n';
//    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( -- -- testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( -- testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( ++ testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};


    std :: cout << std :: boolalpha << testList.insertAfter ( ++ ++ testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( ++ ++ ++ testList.begin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

//    std :: cout << std :: boolalpha << testList.insertAfter ( ++ ++ ++ ++ testList.begin(), 4 ) << " "; // obvious sigsegv
//    std :: cout << std :: dec << testList << '\n';
//    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( -- -- testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( -- testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( ++ testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( ++ ++ testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertBefore ( ++ ++ ++ testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

//    std :: cout << std :: boolalpha << testList.insertBefore ( ++ ++ ++ ++ testList.rbegin(), 4 ) << " "; /// sigsegv
//    std :: cout << std :: dec << testList << '\n';
//    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( -- -- testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( -- testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( ++ testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( ++ ++ testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

    std :: cout << std :: boolalpha << testList.insertAfter ( ++ ++ ++ testList.rbegin(), 4 ) << " ";
    std :: cout << std :: dec << testList << '\n';
    testList = {1, 2, 3};

//    std :: cout << std :: boolalpha << testList.insertAfter ( ++ ++ ++ ++ testList.rbegin(), 4 ) << " "; /// sigsegv
//    std :: cout << std :: dec << testList << '\n';
//    testList = {1, 2, 3};

    LinkedHashSet < int > hssss;
    LinkedHashMap < int, int > hssssm;
    hssssm.emplace ( 3, 4 );
    std :: cout << hssssm.toString() << '\n';

//    hssss.insert (3);

    return 0;
}