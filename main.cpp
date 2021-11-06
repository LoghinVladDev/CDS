
#include <CDS/Array>
#include <CDS/HashMap>
#include <iostream>

class A {
public:
    A() noexcept { std :: cout << "Create\n"; }
    ~A() noexcept { std :: cout << "Delete\n"; }
};

int main () {

    Array < int > a = { 1, 2, 3 };

    std :: cout << a [1] << '\n';

    for ( auto & e : a )
        std :: cout << e << '\n';

    LinkedList < int > ll = { 1, 2, 3, 4, 5 };

    for ( auto & e : ll )
        std :: cout << e << '\n';

    OrderedSet < int > os = { 1, 2, 3, 1, 2, 3 };
    UnorderedSet < int > us = { 1, 2, 3, 1, 2, 3 };

    for ( auto & e : os )
        std :: cout << e << '\n';
    for ( auto & e : us )
        std :: cout << e << '\n';

    HashMap <int, int> const hm = { { 1, 2 }, { 3, 4 }, { 5, 6 } };

    for ( auto & p : hm )
        std :: cout << p << '\n';

    for ( auto it = hm.rbegin(); it != hm.rend(); ++ it )
        std :: cout << * it << '\n';

    return 0;
}