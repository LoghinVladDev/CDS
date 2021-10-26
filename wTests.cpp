#include <CDS/Object>

int main () {
//    auto v = std :: is_arithmetic < int > :: value;
    auto v = Type < int > :: isNumeric;

    std :: cout << v << '\n';
}