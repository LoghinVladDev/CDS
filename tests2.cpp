#include <CDS/experimental/Collection>
#include <CDS/Array>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/experimental/meta/TypeTraits>
#include <CDS/experimental/meta/FunctionTraits>
#include <CDS/Pair>
#include <CDS/experimental/Tuple>
#include <CDS/Pointer>
#include <CDS/experimental/Array>
using namespace cds;


int main () {

    auto arr = experimental :: arrayOf ( 1, 2, "test"_s, 3, 4, 5, 6, 1, 2.4f );
    std :: cout << arr << '\n';

    return 0;
}