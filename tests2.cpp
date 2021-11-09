#include <iostream>
#include <CDS/Array>

int main () {
    Array < Array < int > > matrix;
    matrix.resize(3);

    int i = 1;

    for ( auto & e : matrix ) {
        e.resize( 4 );
        e.forEach ( [&](int & v){ v = i++; } );
    }

    for ( auto it = matrix.rbegin(); it != matrix.rend(); ++ it ) {
        std :: cout << it->back() << '\n';
    }
}