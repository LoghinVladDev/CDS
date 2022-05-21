#include <CDS/Thread>
#include <CDS/Array>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/experimental/meta/TypeTraits>
#include <CDS/experimental/meta/FunctionTraits>
#include <CDS/Pair>
#include <CDS/experimental/Tuple>
#include <CDS/Pointer>
using namespace cds;

int main () {

    auto a = arrayOf <String> ( "ana", "are", "mere" );
    a.forEach ( & println < String > );

String s;
auto pfn = & String::length;
    (s.*pfn)();


    a.forEach ( & String :: length );
//    std :: cout << experimental :: meta :: impl :: IsMemberFunctionPointer < decltype ( & String :: length ), String > :: value << '\n';

    return 0;
}