#include <CDS/HashSet>

using namespace cds;

int main () {
    HashSet <int> m;

    m.insert(4);
    m.insert(252943);
    m.insert(3);
    m.insert(2);
    m.insert(1);

    std :: cout << m << '\n';

    return 0;
}