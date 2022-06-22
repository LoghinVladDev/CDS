#include <CDS/experimental/Collection>
#include <CDS/Array>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/meta/TypeTraits>
#include <CDS/meta/FunctionTraits>
#include <CDS/Pair>
#include <CDS/Tuple>
#include <CDS/Pointer>
#include <CDS/experimental/Array>
#include <CDS/experimental/HashSet>
#include <CDS/String>
#include <CDS/experimental/OrderedSet>
#include <CDS/experimental/UnorderedSet>
#include <CDS/experimental/HashMap>
#include <CDS/HashMap>
#include <chrono>

#include <random>
#include <fstream>

using namespace cds;
using namespace cds :: literals;


int main () {
    cds :: experimental :: HashMap < String, String > m;
//    cds :: HashMap < int, int > m;

//    struct _h {
//        auto operator () (String const & s)const{ return s.hash(); }
//    };
//    std :: unordered_map < String, String, _h > m;
    std :: random_device rd;
    std :: mt19937 mt(rd());
    std :: uniform_int_distribution < uint32 > dist (0U, cds :: limits :: U32_MAX);

    auto start = std :: chrono :: system_clock :: now();
    for ( int i = 0; i < 100000; ++ i ) {

        int k = dist(mt);
        int v = dist(mt);
        m.emplace ( k, v );

        if ( m[k] != String(v) ) {
            std :: cout << "ohoh\n";
        }
    }

    for ( auto & e : m ) {
        std :: cout << e.key() << ':' << e.value() << '\n';
    }

//    m.clear();
//
//    m[1] = 3;
//    std :: cout << m[1] << '\n';

//    std :: cout << m.bucket_count() << '\n';
    auto end = std :: chrono :: system_clock :: now();
    std :: cout
            << "Duration : "
            << std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count() << '\n';

////    auto it1 = testArr.begin();
////    for ( int i = 0; i < 500; ++ i ) {
////        ++ it1;
////    }
////
////    for ( int i = 0; i < 1000; ++ i ) {
////        testArr.insertBefore ( it1, i );
////        testArr.insertAfter ( it1, - i );
////    }
//
////    int k1 = 572660336, v1 = 1159126505;
////    m.emplace ( k1, v1 );
//
//
//    std :: cout << cds :: meta :: isDerivedFrom < cds :: experimental :: HashSet < int, cds :: utility :: MediumCollisionDefaultHashFunction < int > >, cds :: experimental :: Set < int > > () << '\n';
//    std :: cout << cds :: meta :: isDerivedFrom < cds :: experimental :: Array < int >, cds :: experimental :: Collection < int > > () << '\n';
//    std :: cout << cds :: meta :: isDerivedFrom < cds :: experimental :: Array < cds :: experimental :: __hidden :: __impl :: __MapEntry < int, int > >, cds :: experimental :: Collection < cds :: experimental :: __hidden :: __impl :: __MapEntry < int, int > > > () << '\n';
////    cds :: meta :: isDerivedFrom < __KeySetType, Set < __KeySetType > > () &&
////    cds :: meta :: isDerivedFrom < __ValueCollectionType, Collection < __ValueType > > () &&
////    cds :: meta :: isDerivedFrom < __EntryCollectionType, Collection < __MapEntry < __KeyType, __ValueType > > > ()
//
//    std :: cout << meta :: isDerivedFrom < cds :: experimental :: HashSet < int >, cds :: experimental :: Set < int > > () << '\n';
//
//    auto set = cds :: experimental :: setOf ( 1, 2, 3, 4 );
//
//    cds :: experimental::FunctionComparator <int, & predicates::lessThan<int>> comp;
//    std :: cout << noexcept ( comp ( 2, 3 ) ) << '\n';
//
//    meta :: RemoveConstVolatile < int > var2 = 3;
//    auto set2 = cds :: experimental :: orderedSetOf ( 2, 4, 3, 1 );
//
//    auto set3 = cds :: experimental :: unorderedSetOf ( 3, 5, 1, 6, 7, 4 ,5, 3 );
//
//    std :: cout << set2 << '\n';
//    std :: cout << set3 << '\n';
//
//    std :: cout << set << '\n';
//
//    cds :: Tuple < int, String, float > t = { 3, "some String", 4.5f };
//
//    std :: cout << t.get<0>() << '\n';
//    std :: cout << t.get<1>() << '\n';
//    std :: cout << t.get<2>() << '\n';
//
//    auto arr = experimental :: arrayOf ( 1, 2, String("test"), 3, 4, 5, 6, 1, 2.4f );
//    std :: cout << arr << '\n';
//
//    std :: cout << arr.sub <experimental::Array> (2, 5) << '\n';
//
//    * arr.begin() = "ana";
//    auto it = arr.begin();
//
//    arr.insertBefore (it, "test");
//
//    std :: cout << arr << '\n';
//
//
//    arr.sort ();
//    std :: cout << arr << '\n';
//
//    std :: string trivial = "test string";
//    cds :: String copyByView = trivial;
//
//    std :: cout << copyByView << '\n';
//
//
////    experimental :: String s23;
//
//
//
//    String s;
//    s += 'a';
//
//    arr.count ( Function < bool (String) > ( [] (String v) { return true; } ) );
//
//    class Test {
//
//    };
//
//    experimental :: Array < Test > test;
//    test.pushBack(Test());
//    test.pushBack(Test());
//    test.pushBack(Test());
//
//    std :: cout << test << '\n';
//
////    experimental :: Array a2 ( arr.begin(), arr.end() );
////    experimental :: Array a3 ( 2, 5 );
//
////    std :: cout << experimental :: meta :: isIterator < decltype ( a2.begin() ) > () << '\n';
//    std :: cout << meta :: isIterator < int > () << '\n';
//
//
//    cds :: String str;
//
//    for ( char c = 'z'; c >= 'A'; -- c ) {
//        str += cds :: String :: consonants;
//    }
//
//    std :: wcout << str << '\n';
//
//    std :: cout << String :: f ( "%s are %d mere", "Ana", 5 ) << '\n';
//
//    std :: cout << meta :: isCallable < decltype ( StringUtils < char > :: isVowel ) > () << '\n';
//
//    decltype ( StringUtils < char > :: isVowel ) v;
//
//    std :: cout << str.sequence();
////    v
//
////    experimental :: Set < int > set;

    return 0;
}