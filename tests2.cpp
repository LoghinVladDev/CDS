#include <CDS/LinkedList>
#include <CDS/Array>
#include <CDS/Set>
#include <CDS/OrderedSet>
#include <CDS/UnorderedSet>
#include <CDS/HashSet>
#include <CDS/LinkedHashSet>
#include <CDS/Map>
#include <CDS/HashMap>

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

    HashSet < int > hs = { 2, 1, 4, 3 };
    std :: cout << hs << '\n';

    HashMap < int, int > hm = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
    std :: cout << hm << '\n';

    std :: cout << __CDS_cpplang_core_version << '\n';

    LinkedHashSet < int > lhs = { 3, 2, 1, 4 };
    std :: cout << lhs << '\n';


    return 0;
}