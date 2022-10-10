#include <CDS/experimental/TreeSet>

int main () {

    cds :: experimental :: TreeSet < int > a;
    a.insert(3);
    a.insert(3);
    a.insert(3);
    a.insert(2);
    a.insert(4);

    std :: cout << a << '\n';

    return 0;
}