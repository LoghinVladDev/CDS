#include <iostream>

#include <CDS/experimental/TreeSet>

int main () {

    cds :: experimental :: TreeSet < int > t;
    t.insertAll(1,2,3,4,5);
    t.remove ( 4 );
    std :: cout << t << '\n';
    return 0;
}