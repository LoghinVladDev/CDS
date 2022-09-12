#include <iostream>

#include "src/experimental/collection_new_iterable_model/TreeSet.hpp"

int main () {
    cds :: experimental :: TreeSet < int > t;
    t.insertAll(1,2,3,4,5);
    t.remove ( 4 );
//    std :: cout << t << '\n';
    return 0;
}