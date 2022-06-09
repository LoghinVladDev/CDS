#include <CDS/experimental/Collection>
#include <CDS/Array>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/meta/TypeTraits>
#include <CDS/meta/FunctionTraits>
#include <CDS/Pair>
#include <CDS/Tuple>
#include <CDS/Pointer>
#include <CDS/experimental/Array>
#include <CDS/experimental/Set>
#include <CDS/String>
using namespace cds;
using namespace cds :: literals;


int main () {

    cds :: Tuple < int, String, float > t = { 3, "some String", 4.5f };

    std :: cout << t.get<0>() << '\n';
    std :: cout << t.get<1>() << '\n';
    std :: cout << t.get<2>() << '\n';

    auto arr = experimental :: arrayOf ( 1, 2, String("test"), 3, 4, 5, 6, 1, 2.4f );
    std :: cout << arr << '\n';

    std :: cout << arr.sub <experimental::Array> (2, 5) << '\n';

    * arr.begin() = "ana";
    auto it = arr.begin();

    arr.insertBefore (it, "test");

    std :: cout << arr << '\n';


    arr.sort ();
    std :: cout << arr << '\n';

    std :: string trivial = "test string";
    cds :: String copyByView = trivial;

    std :: cout << copyByView << '\n';

//    experimental :: String s23;



    String s;
    s += 'a';

    arr.count ( Function < bool (String) > ( [] (String v) { return true; } ) );

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
    std :: cout << meta :: isIterator < int > () << '\n';


    cds :: String str;

    for ( char c = 'z'; c >= 'A'; -- c ) {
        str += cds :: String :: consonants;
    }

    std :: wcout << str << '\n';

    std :: cout << String :: f ( "%s are %d mere", "Ana", 5 ) << '\n';

    std :: cout << meta :: isCallable < decltype ( StringUtils < char > :: isVowel ) > () << '\n';

    decltype ( StringUtils < char > :: isVowel ) v;

    std :: cout << str.sequence();
//    v

//    experimental :: Set < int > set;

    return 0;
}