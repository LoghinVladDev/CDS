#include <iostream>

#include "src/experimental/RBTree/RBTree.hpp"

using namespace cds;

int main () {
    RBTree < int > t;
    t.Insert ( 5 );
    t.Insert ( 7 );
    t.Insert ( 50 );
    t.Delete ( 5 );
    t.Insert ( 4 );
    t.Delete ( 4 );
    if ( t.Find(50) != nullptr )
        printf ( "RBTree t contains value 50\n" );
    return 0;
}