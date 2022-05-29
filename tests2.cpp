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

    cds :: experimental :: Tuple < int, String, float > t = { 3, "some String", 4.5f };

    std :: cout << t.get<0>() << '\n';
    std :: cout << t.get<1>() << '\n';
    std :: cout << t.get<2>() << '\n';

    auto arr = experimental :: arrayOf ( 1, 2, "test"_s, 3, 4, 5, 6, 1, 2.4f );
    std :: cout << arr << '\n';

    std :: cout << arr.sub <experimental::Array> (2, 5) << '\n';

    * arr.begin() = "ana";
    auto it = arr.begin();

    arr.insertBefore (it, "test");

    std :: cout << arr << '\n';

    arr.sort ();

    std :: cout << arr << '\n';

    arr.count ( Function ( [] (String v) { return true; } ) );


    return 0;
}