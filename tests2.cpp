#include <iostream>

#include <CDS/experimental/TreeSet>
#include <CDS/experimental/TreeMap>
#include <CDS/experimental/HashMap>
#include <CDS/experimental/HashSet>
//#include <CDS/Collection>


int main() {
    cds :: experimental :: TreeMap < int, float > t1 { { { 5, 4.2 }, {9, 3.5 }, { 6, 4.7 } } };
    for ( auto e : t1.keys() ) {
        std :: cout << e << '\n';
    }
}