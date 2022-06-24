#include <CDS/LinkedList>
#include <CDS/Array>
#include <CDS/Set>
#include <CDS/OrderedSet>
#include <CDS/UnorderedSet>

using namespace cds;

int main () {

    Array < int > a = { 1, 2, 3, 4 };
    std :: cout << a << '\n';

    LinkedList < int > l = { 1, 2, 3, 4 };
    std :: cout << l << '\n';


    DoubleLinkedList< int> dll = { 1, 2, 3 ,4 };
    std :: cout << l << '\n';

    OrderedSet < int > os = { 2, 1, 4, 3 };
    std :: cout << os << '\n';

    UnorderedSet < int > us = { 2, 1, 4, 3 };
    std :: cout << us << '\n';


    return 0;
}