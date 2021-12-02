#include <CDS/Array>

using namespace cds;

#include <CDS/SingleLinkedList>

int main () {
    SingleLinkedList < int > a = {1, 2, 3};

    a.forEach([](auto e) { std :: cout << e << '\n'; });

    std :: cout << a << '\n';
}