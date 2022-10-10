#include <CDS/LinkedHashSet>

int main () {

    cds :: LinkedHashSet < int > a;
    a.insert(3);
    a.insert(3);
    a.insert(3);
    a.insert(2);
    a.insert(4);

    std :: cout << a << '\n';

    return 0;
}