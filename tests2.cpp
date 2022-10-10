#include <CDS/HashMap>

int main () {

    cds :: HashMap < int, int > a;
    a.emplace(3, 4);
    a.emplace(3, 1);
    a.emplace(3, 2);
    a.emplace(2, 1);
    a.emplace(4, 4);

    std :: cout << a << '\n';

    return 0;
}