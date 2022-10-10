#include <CDS/HashSet>

int main () {

    cds :: HashSet < int > a;
    a.insert(3);
    a.insert(3);
    a.insert(3);

    std :: cout << a << '\n';

    return 0;
}