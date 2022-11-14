#include <iostream>

#include <CDS/experimental/TreeSet>
#include <CDS/experimental/TreeMap>
#include <CDS/experimental/HashMap>
#include <CDS/experimental/HashSet>
//#include <CDS/Collection>

//#include <string>

int main() {
//    cds :: experimental :: TreeMap < int, int > t;
    cds :: experimental :: TreeSet < int > t2 { 1, 2, 3, 4 };
    cds :: experimental :: TreeSet < int > t3 { 3, 4, 5, 6 };
//    int const * v = new int ( 6 );
//    int const * p =  & v[0] ;
//    t2.removeAllOf ( t3 );
    cds :: HashSet < int > h2;
    cds :: HashSet < int > h3;
    h2.removeAllOf ( h3 );
//    std :: cout << h << '\n';
    int x;
    return 0;
}