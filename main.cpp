#include <CDS/Array>

using namespace cds;



int main () {
    Array const a = {1, 2, 3};

    a.forEach([](auto e) { std :: cout << e << '\n'; });

    std :: cout << a << '\n';
}