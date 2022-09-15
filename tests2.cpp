#include <iostream>

#include <CDS/experimental/TreeSet>

int main () {

    cds :: experimental :: TreeSet < int > t { 1, 2, 3, 4, 5};
    cds :: experimental :: TreeSet < int > x ( t );
    t.clear();
    return 0;
}