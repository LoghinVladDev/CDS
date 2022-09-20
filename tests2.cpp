#include <iostream>

#include <CDS/experimental/TreeSet>
#include <CDS/String>
#include <CDS/experimental/Array>
#include "src/experimental/collection_new_iterable_model/shared/iterator/IteratorSort.hpp"
#include "src/experimental/collection_new_iterable_model/shared/iterator/impl/IteratorSort.hpp"

int main () {

    using namespace cds :: experimental;
    std :: cout << (int) __hidden :: __impl :: __helpers :: __lg(17) << '\n';

    cds :: experimental :: TreeSet < cds :: String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std :: cout << ( cds :: String ( "2" ) > cds :: String ( "5" ) ) << '\n';
    cds :: experimental :: TreeSet < cds :: String > ceva = { 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };
    std :: cout << ceva << '\n';
    using namespace cds :: experimental;

    Array < int > a = { 9, 1, 2, 7, 4, 5, 8, 1 ,2 ,8 ,9, 7, 0, 4, 5, 1, 2,5, 2, 3, 8,7,7,5,2,5,4,4,8,6,1,1,1,5,1,8,65,2,1,5,8,96,4,2,4,7,8,5,6,4,1,5,8,7 };
    introSort (
            a.begin(),
            a.end()
    );

    std :: cout << a << '\n';

    return 0;
}