#include <CDS/Thread>
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
    experimental :: Array < UniquePointer < int > > arr;

    arr.addAll ( new int (3), new int (4), new int (5) );

    std :: cout << arr << '\n';

    return 0;
}