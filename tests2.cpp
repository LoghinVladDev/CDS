#include <CDS/LinkedList>
#include <CDS/Array>

using namespace cds;

int main () {

    Array < int > a = { 1, 2, 3, 4 };
    std :: cout << a << '\n';

    LinkedList < int > l = { 1, 2, 3, 4 };
    std :: cout << l << '\n';

    DoubleLinkedList< int> dll = { 1, 2, 3 ,4 };
    std :: cout << l << '\n';


    return 0;
}