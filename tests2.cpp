#include <CDS/experimental/Collection>
#include <CDS/Array>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/experimental/meta/TypeTraits>
#include <CDS/experimental/meta/FunctionTraits>
#include <CDS/Pair>
#include <CDS/experimental/Tuple>
#include <CDS/Pointer>
#include <CDS/experimental/Array>
#include <CDS/experimental/Set>
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

    class Test {

    };

    experimental :: Array < Test > test;
    test.pushBack(Test());
    test.pushBack(Test());
    test.pushBack(Test());

    std :: cout << test << '\n';

//    experimental :: Array a2 ( arr.begin(), arr.end() );
//    experimental :: Array a3 ( 2, 5 );

//    std :: cout << experimental :: meta :: isIterator < decltype ( a2.begin() ) > () << '\n';
    std :: cout << experimental :: meta :: isIterator < int > () << '\n';

//    experimental :: Set < int > set;

    return 0;
}