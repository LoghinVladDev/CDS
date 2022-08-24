#include <iostream>

#include <CDS/Object>

#include <CDS/experimental/Collection>
#include <CDS/experimental/MutableCollection>
#include <CDS/experimental/Set>
#include <CDS/experimental/Map>
#include <CDS/experimental/List>
#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>
#include <CDS/experimental/HashSet>
#include <CDS/experimental/HashMap>
#include <CDS/experimental/LinkedHashSet>
#include <CDS/experimental/LinkedHashMap>


enum class E1 {
    f1 = 0x01,
    f2 = 0x02
};

class A {
public:
    virtual void f () = 0;
};

class B : public A {
public:
    void f () override {
        std :: cout << "test\n";
    }
};

void f ( auto (*g) () -> void ) noexcept {
    g();
}


template < typename Last >
void printAll ( Last && value ) {
    std :: cout << value << '\n';
}

template < typename First, typename ... TheRest >
void printAll ( First && first, TheRest && ... theRest ) {
    std :: cout << first << ", ";
    printAll ( std :: forward < TheRest > ( theRest ) ... );
}

void f2();

#include <chrono>
#include <vector>
#include <CDS/Range>

class C {
public:
    C ( int ) noexcept {}
    C ( double ) noexcept (false) {}
};

template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}

using namespace cds :: experimental;

void timingTest (int n) {

    Array < int > a;
    std :: vector < int > v;
    auto pClassic = new int [n];

    timed (
            "Classic 100m insertion",
            [pClassic, n] {
                for (int i = 0; i < n; ++i) {
                    pClassic [i] = i;
                }
            }
    );

    timed (
            "CDS 100m insertion",
            [& a, n] {
                for (int i = 0; i < n; ++i) {
                    a.emplaceBack(i);
                }
            }
    );

    timed (
            "STL 100m insertion",
            [& v, n] {
                for (int i = 0; i < n; ++i) {
                    v.emplace_back(i);
                }
            }
    );

    timed (
            "CDS 100m iter",
            [& a] {
                for ( auto & e : a ) {
                    e = 5;
                }
            }
    );

    timed (
            "STL 100m iter",
            [& v] {
                for ( auto & e : v ) {
                    e = 5;
                }
            }
    );

    timed (
            "CDS 100m manual iter",
            [& a] {
                for ( cds :: Size i = 0, l = a.size(); i < l; ++ i ) {
                    a[i] = 5;
                }
            }
    );

    timed (
            "CDS 100m manual by addr iter",
            [& a, n] {
                auto p = a.data();
                for ( cds :: Size i = 0, l = a.size(); i < l; ++ i ) {
                    p[i] = 5;
                }
            }
    );

    timed (
            "STL 100m manual iter",
            [& v] {
                for ( cds :: Size i = 0, l = v.size(); i < l; ++ i ) {
                    v[i] = 5;
                }
            }
    );

    timed (
            "STL 100m manual by addr iter",
            [& v] {
                auto p = v.data();
                for ( cds :: Size i = 0, l = v.size(); i < l; ++ i ) {
                    p[i] = 5;
                }
            }
    );

    timed (
            "Classic 100m manual iter",
            [pClassic, n] {
                for ( cds :: Size i = 0, l = n; i < l; ++ i ) {
                    pClassic [i] = 5;
                }
            }
    );

    delete [] pClassic;
}

#include <CDS/Function>

class Test {public:
    void log (...) {}
    void logOK (...) {}
    void logError (...) {}
};

template <
        typename __Original,
        typename __MemberType,
        typename __MatchingNonePredicateType,
        typename __MatchingOnePredicateType,
        typename __MatchingMoreLTLPredicateType,
        typename __MatchingMorePredicateType,
        typename __MatchingMoreMTLPredicateType,
        typename __MatchingAllPredicateType
> auto collectionTestGroupRemoveBy (
        __Original & original,
        Test                                               * pTestLib,
        cds :: Size                                                       removeThatLimit,
        cds :: Size                                                       removeThatResultWhenLessThanLimit,
        __MatchingNonePredicateType                        const & matchingNone,
        __MatchingOnePredicateType                         const & matchingOne,
        __MatchingMoreLTLPredicateType                     const & matchingMoreLessThanLimit,
        __MatchingMorePredicateType                        const & matchingMore,
        __MatchingMoreMTLPredicateType                     const & matchingMoreMoreThanLimit,
        __MatchingAllPredicateType                         const & matchingAll,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveThatMatchesNone,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveThatMatchesOne,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveThatMatchesMoreLessThanLimit,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveThatMatchesMoreExact,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveThatMatchesMoreMoreThanLimit,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveThatMatchesAll,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesNone,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesOne,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesMore,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesAll,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesNone,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesOne,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesMore,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesAll,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesNone,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesOne,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesMore,
        cds :: experimental :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesAll
) -> bool {
//
//    pTestLib->log ( "Object Under Test : %s", original.toString().cStr() );
//
//    /* CollectionTestCase-RemoveBy-removeThatMatchesNone-CPP20 : CTC-00401-RB-removeThatMatchesNone-CPP20 */
//    auto       copyRB401            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB401 = copyRB401;
//    auto       removedCountRB401    = collectionRB401.removeThat ( removeThatLimit, matchingNone );
//    auto const expectedRemovedCountRB401 = 0;
//    pTestLib->log ( "object after 'removeThat with none matching' : '%s'. expected : '%s'", collectionRB401.toString().cStr(), equivAfterRemoveThatMatchesNone.toString().cStr() );
//    if ( removedCountRB401 != expectedRemovedCountRB401 || ! collectionRB401.equals ( equivAfterRemoveThatMatchesNone ) ) {
//        pTestLib->logError( "'CTC-00401-RB-removeThatMatchesNone-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00401-RB-removeThatMatchesNone-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeThatMatchesOne-CPP20 : CTC-00402-RB-removeThatMatchesOne-CPP20 */
//    auto       copyRB402            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB402 = copyRB402;
//    auto       removedCountRB402    = collectionRB402.removeThat ( removeThatLimit, matchingOne );
//    auto const expectedRemovedCountRB402 = 1;
//    pTestLib->log ( "object after 'removeThat with one matching' : '%s'. expected : '%s'", collectionRB402.toString().cStr(), equivAfterRemoveThatMatchesOne.toString().cStr() );
//    if ( removedCountRB402 != expectedRemovedCountRB402 || ! collectionRB402.equals ( equivAfterRemoveThatMatchesOne ) ) {
//        pTestLib->logError( "'CTC-00402-RB-removeThatMatchesOne-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00402-RB-removeThatMatchesOne-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeThatMatchesMoreLessThanLimit-CPP20 : CTC-00403-RB-removeThatMatchesMoreLessThanLimit-CPP20 */
//    auto       copyRB403            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB403 = copyRB403;
//    auto       removedCountRB403    = collectionRB403.removeThat ( removeThatLimit, matchingMoreLessThanLimit );
//    auto const expectedRemovedCountRB403 = removeThatResultWhenLessThanLimit;
//    pTestLib->log ( "object after 'removeThat with more matching, less than limit' : '%s'. expected : '%s'", collectionRB403.toString().cStr(), equivAfterRemoveThatMatchesMoreLessThanLimit.toString().cStr() );
//    if ( removedCountRB403 != expectedRemovedCountRB403 || ! collectionRB403.equals ( equivAfterRemoveThatMatchesMoreLessThanLimit ) ) {
//        pTestLib->logError( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-CPP20' OK" );
//    }

    /* CollectionTestCase-RemoveBy-removeThatMatchesMoreExact-CPP20 : CTC-00404-RB-removeThatMatchesMoreExact-CPP20 */
    auto       copyRB404            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB404 = original;
    auto       removedCountRB404    = collectionRB404.removeThat ( removeThatLimit, matchingMore );
    auto const expectedRemovedCountRB404 = removeThatLimit;
    pTestLib->log ( "object after 'removeThat with more matching, exact' : '%s'. expected : '%s'", collectionRB404.toString().cStr(), equivAfterRemoveThatMatchesMoreExact.toString().cStr() );
    if ( removedCountRB404 != expectedRemovedCountRB404 || ! collectionRB404.equals ( equivAfterRemoveThatMatchesMoreExact ) ) {
        pTestLib->logError( "'CTC-00404-RB-removeThatMatchesMoreExact-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00404-RB-removeThatMatchesMoreExact-CPP20' OK" );
    }
//
//    /* CollectionTestCase-RemoveBy-removeThatMatchesMoreMoreThanLimit-CPP20 : CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-CPP20 */
//    auto       copyRB405            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB405 = copyRB405;
//    auto       removedCountRB405    = collectionRB405.removeThat ( removeThatLimit, matchingMoreMoreThanLimit );
//    auto const expectedRemovedCountRB405 = removeThatLimit;
//    pTestLib->log ( "object after 'removeThat with more matching' : '%s'. expected : '%s'", collectionRB405.toString().cStr(), equivAfterRemoveThatMatchesMoreMoreThanLimit.toString().cStr() );
//    if ( removedCountRB405 != expectedRemovedCountRB405 || ! collectionRB405.equals ( equivAfterRemoveThatMatchesMoreMoreThanLimit ) ) {
//        pTestLib->logError( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-CPP20' OK" );
//    }

//    /* CollectionTestCase-RemoveBy-removeThatMatchesAll-CPP20 : CTC-00406-RB-removeThatMatchesAll-CPP20 */
//    auto       copyRB406            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB406 = copyRB406;
//    auto       removedCountRB406    = collectionRB406.removeThat ( removeThatLimit, matchingAll );
//    auto const expectedRemovedCountRB406 = removeThatLimit;
//    pTestLib->log ( "object after 'removeThat with all matching, less than limit' : '%s'. expected : '%s'", collectionRB406.toString().cStr(), equivAfterRemoveThatMatchesAll.toString().cStr() );
//    if ( removedCountRB406 != expectedRemovedCountRB406 || ! collectionRB406.equals ( equivAfterRemoveThatMatchesAll ) ) {
//        pTestLib->logError( "'CTC-00406-RB-removeThatMatchesAll-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00406-RB-removeThatMatchesAll-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesNone-CPP20 : CTC-00407-RB-removeFirstThatMatchesNone-CPP20 */
//    auto       copyRB407            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB407 = copyRB407;
//    auto       removedCountRB407    = collectionRB407.removeFirstThat ( matchingNone );
//    auto const expectedRemovedCountRB407 = false;
//    pTestLib->log ( "object after 'removeFirstThat with no matches' : '%s'. expected : '%s'", collectionRB407.toString().cStr(), equivAfterRemoveFirstThatMatchesNone.toString().cStr() );
//    if ( removedCountRB407 != expectedRemovedCountRB407 || ! collectionRB407.equals ( equivAfterRemoveFirstThatMatchesNone ) ) {
//        pTestLib->logError( "'CTC-00407-RB-removeFirstThatMatchesNone-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00407-RB-removeFirstThatMatchesNone-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesOne-CPP20 : CTC-00408-RB-removeFirstThatMatchesOne-CPP20 */
//    auto       copyRB408            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB408 = copyRB408;
//    auto       removedCountRB408    = collectionRB408.removeFirstThat ( matchingOne );
//    auto const expectedRemovedCountRB408 = true;
//    pTestLib->log ( "object after 'removeFirstThat with one match' : '%s'. expected : '%s'", collectionRB408.toString().cStr(), equivAfterRemoveFirstThatMatchesOne.toString().cStr() );
//    if ( removedCountRB408 != expectedRemovedCountRB408 || ! collectionRB408.equals ( equivAfterRemoveFirstThatMatchesOne ) ) {
//        pTestLib->logError( "'CTC-00408-RB-removeFirstThatMatchesOne-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00408-RB-removeFirstThatMatchesOne-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesMore-CPP20 : CTC-00409-RB-removeFirstThatMatchesMore-CPP20 */
//    auto       copyRB409            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB409 = copyRB409;
//    auto       removedCountRB409    = collectionRB409.removeFirstThat ( matchingMore );
//    auto const expectedRemovedCountRB409 = true;
//    pTestLib->log ( "object after 'removeFirstThat with one or more matches' : '%s'. expected : '%s'", collectionRB409.toString().cStr(), equivAfterRemoveFirstThatMatchesMore.toString().cStr() );
//    if ( removedCountRB409 != expectedRemovedCountRB409 || ! collectionRB409.equals ( equivAfterRemoveFirstThatMatchesMore ) ) {
//        pTestLib->logError( "'CTC-00409-RB-removeFirstThatMatchesMore-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00409-RB-removeFirstThatMatchesMore-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesAll-CPP20 : CTC-00410-RB-removeFirstThatMatchesAll-CPP20 */
//    auto       copyRB410            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB410 = copyRB410;
//    auto       removedCountRB410    = collectionRB410.removeFirstThat ( matchingAll );
//    auto const expectedRemovedCountRB410 = true;
//    pTestLib->log ( "object after 'removeFirstThat matches all' : '%s'. expected : '%s'", collectionRB410.toString().cStr(), equivAfterRemoveFirstThatMatchesAll.toString().cStr() );
//    if ( removedCountRB410 != expectedRemovedCountRB410 || ! collectionRB410.equals ( equivAfterRemoveFirstThatMatchesAll ) ) {
//        pTestLib->logError( "'CTC-00410-RB-removeFirstThatMatchesAll-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00410-RB-removeFirstThatMatchesAll-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeLastThatMatchesNone-CPP20 : CTC-00411-RB-removeLastThatMatchesNone-CPP20 */
//    auto       copyRB411            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB411 = copyRB411;
//    auto       removedCountRB411    = collectionRB411.removeLastThat ( matchingNone );
//    auto const expectedRemovedCountRB411 = false;
//    pTestLib->log ( "object after 'removeLastThat with no matches' : '%s'. expected : '%s'", collectionRB411.toString().cStr(), equivAfterRemoveLastThatMatchesNone.toString().cStr() );
//    if ( removedCountRB411 != expectedRemovedCountRB411 || ! collectionRB411.equals ( equivAfterRemoveLastThatMatchesNone ) ) {
//        pTestLib->logError( "'CTC-00411-RB-removeLastThatMatchesNone-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00411-RB-removeLastThatMatchesNone-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeLastThatMatchesOne-CPP20 : CTC-00412-RB-removeLastThatMatchesOne-CPP20 */
//    auto       copyRB412            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB412 = copyRB412;
//    auto       removedCountRB412    = collectionRB412.removeLastThat ( matchingOne );
//    auto const expectedRemovedCountRB412 = true;
//    pTestLib->log ( "object after 'removeLastThat with one match' : '%s'. expected : '%s'", collectionRB412.toString().cStr(), equivAfterRemoveLastThatMatchesOne.toString().cStr() );
//    if ( removedCountRB412 != expectedRemovedCountRB412 || ! collectionRB412.equals ( equivAfterRemoveLastThatMatchesOne ) ) {
//        pTestLib->logError( "'CTC-00412-RB-removeLastThatMatchesOne-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00412-RB-removeLastThatMatchesOne-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeLastThatMatchesMore-CPP20 : CTC-00413-RB-removeLastThatMatchesMore-CPP20 */
//    auto       copyRB413            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB413 = copyRB413;
//    auto       removedCountRB413    = collectionRB413.removeLastThat ( matchingMore );
//    auto const expectedRemovedCountRB413 = true;
//    pTestLib->log ( "object after 'removeLastThat with one or more matches' : '%s'. expected : '%s'", collectionRB413.toString().cStr(), equivAfterRemoveLastThatMatchesMore.toString().cStr() );
//    if ( removedCountRB413 != expectedRemovedCountRB413 || ! collectionRB413.equals ( equivAfterRemoveLastThatMatchesMore ) ) {
//        pTestLib->logError( "'CTC-00413-RB-removeLastThatMatchesMore-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00413-RB-removeLastThatMatchesMore-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeLastThatMatchesAll-CPP20 : CTC-00414-RB-removeLastThatMatchesAll-CPP20 */
//    auto       copyRB414            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB414 = copyRB414;
//    auto       removedCountRB414    = collectionRB414.removeLastThat ( matchingAll );
//    auto const expectedRemovedCountRB414 = true;
//    pTestLib->log ( "object after 'removeLastThat matching all' : '%s'. expected : '%s'", collectionRB414.toString().cStr(), equivAfterRemoveLastThatMatchesAll.toString().cStr() );
//    if ( removedCountRB414 != expectedRemovedCountRB414 || ! collectionRB414.equals ( equivAfterRemoveLastThatMatchesAll ) ) {
//        pTestLib->logError( "'CTC-00414-RB-removeLastThatMatchesAll-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00414-RB-removeLastThatMatchesAll-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeAllThatMatchesNone-CPP20 : CTC-00415-RB-removeAllThatMatchesNone-CPP20 */
//    auto       copyRB415            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB415 = copyRB415;
//    auto const expectedRemovedCountRB415 = collectionRB415.count ( matchingNone );
//    auto       removedCountRB415    = collectionRB415.removeAllThat ( matchingNone );
//    pTestLib->log ( "object after 'removeAllThat match none' : '%s'. expected : '%s'", collectionRB415.toString().cStr(), equivAfterRemoveAllThatMatchesNone.toString().cStr() );
//    if ( removedCountRB415 != expectedRemovedCountRB415 || ! collectionRB415.equals ( equivAfterRemoveAllThatMatchesNone ) ) {
//        pTestLib->logError( "'CTC-00415-RB-removeAllThatMatchesNone-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00415-RB-removeAllThatMatchesNone-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeAllThatMatchesOne-CPP20 : CTC-00416-RB-removeAllThatMatchesOne-CPP20 */
//    auto       copyRB416            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB416 = copyRB416;
//    auto const expectedRemovedCountRB416 = collectionRB416.count ( matchingOne );
//    auto       removedCountRB416    = collectionRB416.removeAllThat ( matchingOne );
//    pTestLib->log ( "object after 'removeAllThat matching one' : '%s'. expected : '%s'", collectionRB416.toString().cStr(), equivAfterRemoveAllThatMatchesOne.toString().cStr() );
//    if ( removedCountRB416 != expectedRemovedCountRB416 || ! collectionRB416.equals ( equivAfterRemoveAllThatMatchesOne ) ) {
//        pTestLib->logError( "'CTC-00416-RB-removeAllThatMatchesNone-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00416-RB-removeAllThatMatchesNone-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeAllThatMatchesMore-CPP20 : CTC-00417-RB-removeAllThatMatchesMore-CPP20 */
//    auto       copyRB417            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB417 = copyRB417;
//    auto const expectedRemovedCountRB417 = collectionRB417.count ( matchingMore );
//    auto       removedCountRB417    = collectionRB417.removeAllThat ( matchingMore );
//    pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB417.toString().cStr(), equivAfterRemoveAllThatMatchesMore.toString().cStr() );
//    if ( removedCountRB417 != expectedRemovedCountRB417 || ! collectionRB417.equals ( equivAfterRemoveAllThatMatchesMore ) ) {
//        pTestLib->logError( "'CTC-00417-RB-removeAllThatMatchesMore-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00417-RB-removeAllThatMatchesMore-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-RemoveBy-removeAllThatMatchesAll-CPP20 : CTC-00418-RB-removeAllThatMatchesAll-CPP20 */
//    auto       copyRB418            = original;
//    cds :: experimental :: Collection < __MemberType > & collectionRB418 = copyRB418;
//    auto const expectedRemovedCountRB418 = collectionRB418.count ( matchingAll );
//    auto       removedCountRB418    = collectionRB418.removeAllThat ( matchingAll );
//    pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB418.toString().cStr(), equivAfterRemoveAllThatMatchesAll.toString().cStr() );
//    if ( removedCountRB418 != expectedRemovedCountRB418 || ! collectionRB418.equals ( equivAfterRemoveAllThatMatchesAll ) ) {
//        pTestLib->logError( "'CTC-00418-RB-removeAllThatMatchesAll-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00418-RB-removeAllThatMatchesAll-CPP20' OK" );
//    }

    return true;
}

int main () {

    Test t;
#define make_a(t, ...) cds :: experimental :: Array < t > { __VA_ARGS__ }

    cds :: experimental :: Array < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto copy = originalArray;

    collectionTestGroupRemoveBy (
            /* original= */                                         originalArray,
            /* pTestLib= */                                         & t,
            /* removeThatLimit = */                                 3,
            /* removeThatResultWhenLessThanLimit = */               2,
            /* matchingNone = */                                    [](int x) { return x > 100; },
            /* matchingOne = */                                     [](int x) { return x == 3; },
            /* matchingMoreLessThanLimit = */                       [](int x) { return x >= 4 && x <= 5; },
            /* matchingMore = */                                    [](int x) { return x >= 4 && x <= 6; },
            /* matchingMoreMoreThanLimit = */                       [](int x) { return x >= 4 && x <= 7; },
            /* matchingAll = */                                     [](int x) { return x >= 1 && x <= 9; },
            /* equivAfterRemoveThatMatchesNone = */                 make_a ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveThatMatchesOne = */                  make_a ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_a ( int, 1, 2, 3, 6, 7, 8, 9 ),
            /* equivAfterRemoveThatMatchesMoreExact = */            make_a ( int, 1, 2, 3, 7, 8, 9 ),
            /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_a ( int, 1, 2, 3, 7, 8, 9 ),
            /* equivAfterRemoveThatMatchesAll = */                  make_a ( int, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveFirstThatMatchesNone = */            make_a ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveFirstThatMatchesOne = */             make_a ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveFirstThatMatchesMore = */            make_a ( int, 1, 2, 3, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveFirstThatMatchesAll = */             make_a ( int, 2, 3, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveLastThatMatchesNone = */             make_a ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveLastThatMatchesOne = */              make_a ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveLastThatMatchesMore = */             make_a ( int, 1, 2, 3, 4, 5, 7, 8, 9 ),
            /* equivAfterRemoveLastThatMatchesAll = */              make_a ( int, 1, 2, 3, 4, 5, 6, 7, 8 ),
            /* equivAfterRemoveAllThatMatchesNone = */              make_a ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveAllThatMatchesOne = */               make_a ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
            /* equivAfterRemoveAllThatMatchesMore = */              make_a ( int, 1, 2, 3, 7, 8, 9 ),
            /* equivAfterRemoveAllThatMatchesAll = */               make_a ( int )
    );

    return 0;

//    cds :: experimental :: Array < int > arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    auto copy = arr;
//    cds :: experimental :: Collection < int > & c242 = copy;
//    c242.removeThat (2, [](int e){return e >= 4 && e <= 6;});
//
//    std :: cout << arr << '\n';

    return 0;

//    cds :: experimental :: HashMap < int, int > * pM;
//
//    pM->remove(pM->begin());
    cds :: experimental :: Array < cds :: String > strArr = { "Ana", "are", "mere" };

    cds :: experimental :: __hidden :: __impl :: __forEach (
            strArr.cbegin(),
            strArr.cend(),
            & cds :: String :: length
    );

    cds :: experimental :: __hidden :: __impl :: __forEach (
            strArr.begin(),
            strArr.end(),
            [] ( cds :: String & e ) { e = "ana"; }
    );

//    cds :: experimental :: __hidden :: __impl :: __some (
//            strArr.begin(),
//            strArr.end(),
//            2,
//            & cds :: String :: empty
//    );

    strArr.forEach ( & cds :: String :: clear );

    std :: cout << strArr << '\n';

    cds :: experimental :: HashMap < cds :: String, cds :: String > hm12312;
    hm12312.emplace ( "Ana", "name" );
    hm12312.emplace ( "are", "verb" );
    hm12312.emplace ("mere", "noun");

    std :: cout << hm12312.hash () << '\n'
        << ( ( ( ( cds :: hash ("are") ^ cds :: hash ( "verb" ) ) * 31 ) + ( cds :: hash ( "Ana" ) ^ cds :: hash ( "name" ) ) ) *
        31 + ( cds :: hash ( "mere" ) ^ cds :: hash  ("noun") )) << '\n';

    auto v123 = cds :: hash ( "Ana" );

    cds :: Function < int (int) > fact = [& fact](int n) -> int {
        if ( n == 1 ) {
            return 1;
        }

        return fact(n-1) * n;
    };

    std :: cout << fact(5) << '\n';

    HashSet < int > hs;
    hs.emplace (3);
    hs.emplace (4);
    hs.emplace (5);
    hs.emplace (3);
    hs.emplace (5);

    HashMap < int, cds :: String > hm;
    hm.emplace ( 3, "Abc" );
    hm.emplace ( 3, "Bcd" );
    hm.emplace ( 4, "cad" );

    HashMap < int, int > hm2 = { {1, 2}, {3, 4} };
    auto hm3 = HashMap < int, int > { {1, 2}, {3, 4} };

    auto & keys = hm.keys ();

    try {
        keys.emplace( 3 );
    } catch ( cds :: Exception const & e ) {
        std :: cout << e << '\n';
    }

    auto & entries = hm.entries ();

    entries.emplace ( 5, "bdc" );

    std :: cout << hm << '\n';

    std :: cout << hs << '\n';

    std :: cout << sizeof ( Array < int > ) << '\n';

    LinkedList < int > a;
    std :: vector < int > v;

    a.pushBackAll ( 1, 2, 3 );
    std :: cout << a << '\n';

    a.insertBefore ( a.begin(), -1 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( a.begin(), -2 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertBefore ( ++ a.begin(), 4 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( ++ a.begin(), 5 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertBefore ( a.end(), 7 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( a.end(), 8 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertBefore ( -- a.end(), 9 );
    std :: cout << a << '\n';
    std::cout.flush();
    a.insertAfter ( -- a.end(), 10 );
    std :: cout << a << '\n';
    std::cout.flush();

    std :: cout << a.sub ( 2, 5 ) << '\n';


    Array < int > otherArray;
    List < int > & otherAsList = otherArray;

    otherArray.pushBackAllOf ( cds :: Range (20, 30) );

    List < int > * pList = & a;
    (void) pList->begin();
    (void) pList->end();
    (void) pList->cbegin();
    (void) pList->cend();
    (void) pList->rbegin();
    (void) pList->rend();
    (void) pList->crbegin();
    (void) pList->crend();


    pList->pushBack(3);
    pList->pushFront(3);
    pList->pushBackAll(1, 2, 3);
    pList->pushFrontAll (1, 2, 3);
    pList->pushBackAllOf({1, 2, 3});
    pList->pushBackAllOf(otherArray);
    pList->pushBackAllOf(otherArray.begin(), otherArray.end());
    pList->pushFrontAllOf({1, 2, 3});
    pList->pushFrontAllOf(otherArray);
    pList->pushFrontAllOf(otherArray.begin(), otherArray.end());
    pList->pushBackAllOf(otherAsList);
    pList->pushBackAllOf(otherAsList.begin(), otherAsList.end());
    pList->pushFrontAllOf(otherAsList);
    pList->pushFrontAllOf(otherAsList.begin(), otherAsList.end());

    std :: cout << a << '\n';

    pList->insertBefore( pList->begin(), 3);
    pList->insertBefore ( pList->cbegin(), 3);
    pList->insertAfter( pList->begin(), 3);
    pList->insertAfter ( pList->cbegin(), 3);
    pList->insertAllBefore ( pList->begin(), 1, 2, 3);
    pList->insertAllBefore ( pList->cbegin(), 1, 2, 3);
    pList->insertAllAfter ( pList->begin(), 1, 2, 3);
    pList->insertAllAfter ( pList->cbegin(), 1, 2, 3);
    pList->insertAllOfBefore ( pList->begin(), { 1, 2, 3 } );
    pList->insertAllOfBefore ( pList->cbegin(), { 1, 2, 3 } );
    pList->insertAllOfAfter ( pList->begin(), { 1, 2, 3 } );
    pList->insertAllOfAfter ( pList->cbegin(), { 1, 2, 3 } );
    pList->insertAllOfBefore ( pList->begin(), * pList );
    pList->insertAllOfBefore ( pList->cbegin(), * pList );
    pList->insertAllOfAfter ( pList->begin(), * pList );
    pList->insertAllOfAfter ( pList->cbegin(), * pList );
    pList->insertAllOfBefore ( pList->begin(), pList->begin(), pList->end() );
    pList->insertAllOfBefore ( pList->cbegin(), pList->begin(), pList->end() );
    pList->insertAllOfAfter ( pList->begin(), pList->begin(), pList->end() );
    pList->insertAllOfAfter ( pList->cbegin(), pList->begin(), pList->end() );

    pList->sub(otherAsList, 2, 3);
    (*pList)[2] = 3;
    pList->removeAt ( { 1, 3 } );

    cds :: experimental :: Array < cds :: Index > indices = { 2, 3 };
    pList->removeAt ( indices );

    /// TODO : client/server for sort
//    pList->sort();
//    pList->sort(& cds :: predicates :: greaterThan);
//    pList->sort([](int a, int b){ return a < b; });

    pList->replace ( 3, 1, 2 );
    pList->replaceFirst ( 1, 2 );
    pList->replaceLast ( 1, 2 );
    pList->replaceAll ( 2, 1 );
    pList->replaceOf ( 2, otherAsList, 1 );
    pList->replaceFirstOf ( otherAsList, 1 );
    pList->replaceLastOf ( otherAsList, 1 );
    pList->replaceAllOf ( otherAsList, 1 );
    pList->replaceNotOf ( 2, otherAsList, 1 );
    pList->replaceFirstNotOf ( otherAsList, 1 );
    pList->replaceLastNotOf ( otherAsList, 1 );
    pList->replaceAllNotOf ( otherAsList, 1 );
    pList->replaceOf ( 2, { 1, 2, 3 }, 1 );
    pList->replaceFirstOf ( { 1, 2, 3 }, 1 );
    pList->replaceLastOf ( { 1, 2, 3 }, 1 );
    pList->replaceAllOf ( { 1, 2, 3 }, 1 );
    pList->replaceNotOf ( 2, { 1, 2, 3 }, 1 );
    pList->replaceFirstNotOf ( { 1, 2, 3 }, 1 );
    pList->replaceLastNotOf ( { 1, 2, 3 }, 1 );
    pList->replaceAllNotOf ( { 1, 2, 3 }, 1 );

    pList->replaceThat ( 3, [](int x){ return x > 2; }, 1 );
    pList->replaceFirstThat ( [](int x){ return x > 2; }, 1 );
    pList->replaceLastThat ( [](int x){ return x > 2; }, 1 );
    pList->replaceAllThat ( [](int x){ return x > 2; }, 1 );

    pList->replaceThatBy ( 4, [](int x){ return x == 1; }, [](int & x) { return x + 3; } );
    pList->replaceFirstThatBy ( [](int x){ return x == 1; }, [](int & x) { return x + 3; } );
    pList->replaceLastThatBy ( [](int x){ return x == 1; }, [](int & x) { return x + 3; } );
    pList->replaceAllThatBy ( [](int x){ return x == 1; }, [](int & x) { return x + 3; } );

    pList->indicesOf ( 3, otherAsList, 2 );
    (void) pList->firstIndexOf ( 2 );
    (void) pList->lastIndexOf ( 2 );
    pList->allIndicesOf ( otherAsList, 2 );

    pList->indicesOfFrom ( 3, otherAsList, * pList );
    (void) pList->firstIndexOfFrom ( * pList );
    (void) pList->lastIndexOfFrom ( * pList );
    pList->allIndicesOfFrom ( otherAsList, * pList );
    pList->indicesOfNotFrom ( 3, otherAsList, * pList );
    (void) pList->firstIndexOfNotFrom ( * pList );
    (void) pList->lastIndexOfNotFrom ( * pList );
    pList->allIndicesOfNotFrom ( otherAsList, * pList );

    pList->indicesOfFrom ( 3, otherAsList, { 1, 2, 3 } );
    (void) pList->firstIndexOfFrom ( { 1, 2, 3 } );
    (void) pList->lastIndexOfFrom ( { 1, 2, 3 } );
    pList->allIndicesOfFrom ( otherAsList, { 1, 2, 3 } );
    pList->indicesOfNotFrom ( 3, otherAsList, { 1, 2, 3 } );
    (void) pList->firstIndexOfNotFrom ( { 1, 2, 3 } );
    (void) pList->lastIndexOfNotFrom ( { 1, 2, 3 } );
    pList->allIndicesOfNotFrom ( otherAsList, { 1, 2, 3 } );

    pList->indicesOfThat ( 3, otherAsList, [](int x) { return x % 2 == 0; } );
    (void) pList->firstIndexOfThat ( [](int x) { return x % 2 == 0; } );
    (void) pList->lastIndexOfThat ( [](int x) { return x % 2 == 0; } );
    pList->allIndicesOfThat ( otherAsList, [](int x) { return x % 2 == 0; } );

    Collection < int > * pColl = & a;

    (void)pColl->begin();
    (void)pColl->end();
    (void)pColl->cbegin();
    (void)pColl->cend();
    pColl->remove(pColl->begin());
    pColl->remove(pColl->cbegin());
    pColl->remove(pColl->end());
    pColl->remove(pColl->cend());

    (void)pColl->size();
    (void)pColl->empty();
    (void)(bool)*pColl;
    (void)pColl->toString();
    (void)pColl->hash();
    (void)pColl->equals(* pColl);
    pColl->clear();
    (void)pColl->contains(5);
    pColl->insert(5);
    pColl->insertAll(5, 3, 1);
    pColl->insertAllOf(std :: initializer_list<int>{1, 4, 5});
    pColl->insertAllOf(otherAsList);
    pColl->insertAllOf(otherArray);

    pColl->removeThat (
            3,
            [](int){return true;}
    );

    pColl->removeFirstThat (
            [](int){return true;}
    );

    pColl->removeLastThat (
            [](int){return true;}
    );

    pColl->removeAllThat (
            [](int){return true;}
    );

    pColl->forEach([](int){});
    (void)pColl->some(2, [](int){return true;});
    (void)pColl->atLeast(2, [](int){return true;});
    (void)pColl->atMost(2, [](int){return true;});
    (void)pColl->moreThan(2, [](int){return true;});
    (void)pColl->fewerThan(2, [](int){return true;});
    (void)pColl->count([](int){return true;});
    (void)pColl->all([](int){return true;});
    (void)pColl->any([](int){return true;});
    (void)pColl->none([](int){return true;});

    pColl->removeOf ( 5, otherAsList );
    pColl->removeFirstOf ( otherAsList );
    pColl->removeLastOf ( otherAsList );
    pColl->removeAllOf ( otherAsList );

    pColl->removeNotOf ( 5, otherAsList );
    pColl->removeFirstNotOf ( otherAsList );
    pColl->removeLastNotOf ( otherAsList );
    pColl->removeAllNotOf ( otherAsList );

    pColl->removeOf ( 5, { 1, 3, 4 } );
    pColl->removeFirstOf ( { 1, 3, 4 } );
    pColl->removeLastOf ( { 1, 3, 4 } );
    pColl->removeAllOf ( { 1, 3, 4 } );

    pColl->removeNotOf ( 5, { 1, 3, 4 } );
    pColl->removeFirstNotOf ( { 1, 3, 4 } );
    pColl->removeLastNotOf ( { 1, 3, 4 } );
    pColl->removeAllNotOf ( { 1, 3, 4 } );

    (void)pColl->containsAnyOf ( * pColl );
    (void)pColl->containsAllOf ( * pColl );
    (void)pColl->containsAnyNotOf ( * pColl );
    (void)pColl->containsNoneOf ( * pColl );

    (void)pColl->containsAnyOf ( { 1, 2, 3 } );
    (void)pColl->containsAllOf ( { 1, 2, 3 } );
    (void)pColl->containsAnyNotOf ( { 1, 2, 3 } );
    (void)pColl->containsNoneOf ( { 1, 2, 3 } );

    Collection < Collection < int > :: ConstIterator > * pItColl;
    (void) pColl->findThat(3, *pItColl, [](int){return true;});
    (void) pColl->findFirstThat([](int){return true;});
    (void) pColl->findLastThat([](int){return true;});
    (void) pColl->findAllThat(*pItColl, [](int){return true;});

    (void) pColl->findOf ( 3, * pItColl, * pColl );
    (void) pColl->findFirstOf ( * pColl );
    (void) pColl->findLastOf ( * pColl );
    (void) pColl->findAllOf ( * pItColl, * pColl );

    (void) pColl->findNotOf ( 3, * pItColl, * pColl );
    (void) pColl->findFirstNotOf ( * pColl );
    (void) pColl->findLastNotOf ( * pColl );
    (void) pColl->findAllNotOf ( * pItColl, * pColl );

    (void) pColl->findOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pColl->findFirstOf ( { 1, 2, 3 } );
    (void) pColl->findLastOf ( { 1, 2, 3 } );
    (void) pColl->findAllOf ( * pItColl, { 1, 2, 3 } );

    (void) pColl->findNotOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pColl->findFirstNotOf ( { 1, 2, 3 } );
    (void) pColl->findLastNotOf ( { 1, 2, 3 } );
    (void) pColl->findAllNotOf ( * pItColl, { 1, 2, 3 } );

    MutableCollection < int > * pMutColl = & a;

    MutableCollection < int > :: Iterator e = pMutColl->begin();
    MutableCollection < int > :: Iterator e2 = pMutColl->end();

    pMutColl->remove(pMutColl->begin());
    pMutColl->remove(e);

    Collection < MutableCollection < int > :: Iterator > * pItMutColl;

    (void) pMutColl->findThat(3, * pItMutColl, [](int &){return true;});
    (void) pMutColl->findFirstThat([](int &){return true;});
    (void) pMutColl->findLastThat([](int &){return true;});
    (void) pMutColl->findAllThat( *pItMutColl, [](int &){return true;});

    (void)pMutColl->begin();
    (void)pMutColl->end();
    (void)pMutColl->cbegin();
    (void)pMutColl->cend();
    pMutColl->remove(pMutColl->begin());
    pMutColl->remove(pMutColl->cbegin());
    pMutColl->remove(pMutColl->end());
    pMutColl->remove(pMutColl->cend());

    (void)pMutColl->size();
    (void)pMutColl->empty();
    (void)(bool)*pMutColl;
    (void)pMutColl->toString();
    (void)pMutColl->hash();
    (void)pMutColl->equals(* pMutColl);
    pMutColl->clear();
    (void)pMutColl->find(5);
    (void)pMutColl->contains(5);
    pMutColl->insert(5);
    pMutColl->insertAll(5, 3, 1);
    pMutColl->insertAllOf({1, 4, 5});
    pMutColl->insertAllOf(otherAsList);
    pMutColl->insertAllOf(otherAsList.begin(), otherAsList.end());

    pMutColl->removeThat (
            3,
            [](int){return true;}
    );

    pMutColl->removeFirstThat (
            [](int){return true;}
    );

    pMutColl->removeLastThat (
            [](int){return true;}
    );

    pMutColl->removeAllThat (
            [](int){return true;}
    );

    pMutColl->forEach([](int){});
    (void)pMutColl->some(2, [](int){return true;});
    (void)pMutColl->atLeast(2, [](int){return true;});
    (void)pMutColl->atMost(2, [](int){return true;});
    (void)pMutColl->moreThan(2, [](int){return true;});
    (void)pMutColl->fewerThan(2, [](int){return true;});
    (void)pMutColl->count([](int){return true;});
    (void)pMutColl->all([](int){return true;});
    (void)pMutColl->any([](int){return true;});
    (void)pMutColl->none([](int){return true;});

    pMutColl->removeOf ( 5, otherAsList );
    pMutColl->removeFirstOf ( otherAsList );
    pMutColl->removeLastOf ( otherAsList );
    pMutColl->removeAllOf ( otherAsList );

    pMutColl->removeNotOf ( 5, otherAsList );
    pMutColl->removeFirstNotOf ( otherAsList );
    pMutColl->removeLastNotOf ( otherAsList );
    pMutColl->removeAllNotOf ( otherAsList );

    pMutColl->removeOf ( 5, { 1, 3, 4 } );
    pMutColl->removeFirstOf ( { 1, 3, 4 } );
    pMutColl->removeLastOf ( { 1, 3, 4 } );
    pMutColl->removeAllOf ( { 1, 3, 4 } );

    pMutColl->removeNotOf ( 5, { 1, 3, 4 } );
    pMutColl->removeFirstNotOf ( { 1, 3, 4 } );
    pMutColl->removeLastNotOf ( { 1, 3, 4 } );
    pMutColl->removeAllNotOf ( { 1, 3, 4 } );

    (void)pMutColl->containsAnyOf ( * pMutColl );
    (void)pMutColl->containsAllOf ( * pMutColl );
    (void)pMutColl->containsAnyNotOf ( * pMutColl );
    (void)pMutColl->containsNoneOf ( * pMutColl );

    (void)pMutColl->containsAnyOf ( { 1, 2, 3 } );
    (void)pMutColl->containsAllOf ( { 1, 2, 3 } );
    (void)pMutColl->containsAnyNotOf ( { 1, 2, 3 } );
    (void)pMutColl->containsNoneOf ( { 1, 2, 3 } );

    (void) pMutColl->findThat(3, *pItColl, [](int){return true;});
    (void) pMutColl->findFirstThat([](int){return true;});
    (void) pMutColl->findLastThat([](int){return true;});
    (void) pMutColl->findAllThat(*pItColl, [](int){return true;});

    (void) pMutColl->findOf ( 3, * pItColl, * pMutColl );
    (void) pMutColl->findFirstOf ( * pMutColl );
    (void) pMutColl->findLastOf ( * pMutColl );
    (void) pMutColl->findAllOf ( * pItColl, * pMutColl );

    (void) pMutColl->findNotOf ( 3, * pItColl, * pMutColl );
    (void) pMutColl->findFirstNotOf ( * pMutColl );
    (void) pMutColl->findLastNotOf ( * pMutColl );
    (void) pMutColl->findAllNotOf ( * pItColl, * pMutColl );

    (void) pMutColl->findOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllOf ( * pItColl, { 1, 2, 3 } );

    (void) pMutColl->findNotOf ( 3, * pItColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllNotOf ( * pItColl, { 1, 2, 3 } );

    (void) pMutColl->findThat(3, *pItMutColl, [](int){return true;});
    (void) pMutColl->findFirstThat([](int){return true;});
    (void) pMutColl->findLastThat([](int){return true;});
    (void) pMutColl->findAllThat(*pItMutColl, [](int){return true;});

    (void) pMutColl->findOf ( 3, * pItMutColl, * pMutColl );
    (void) pMutColl->findFirstOf ( * pMutColl );
    (void) pMutColl->findLastOf ( * pMutColl );
    (void) pMutColl->findAllOf ( * pItMutColl, * pMutColl );

    (void) pMutColl->findNotOf ( 3, * pItMutColl, * pMutColl );
    (void) pMutColl->findFirstNotOf ( * pMutColl );
    (void) pMutColl->findLastNotOf ( * pMutColl );
    (void) pMutColl->findAllNotOf ( * pItMutColl, * pMutColl );

    (void) pMutColl->findOf ( 3, * pItMutColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllOf ( * pItMutColl, { 1, 2, 3 } );

    (void) pMutColl->findNotOf ( 3, * pItMutColl, { 1, 2, 3 } );
    (void) pMutColl->findFirstNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findLastNotOf ( { 1, 2, 3 } );
    (void) pMutColl->findAllNotOf ( * pItMutColl, { 1, 2, 3 } );

    (void)pMutColl->some(2, [](int &){return true;});
    (void)pMutColl->atLeast(2, [](int &){return true;});
    (void)pMutColl->atMost(2, [](int &){return true;});
    (void)pMutColl->moreThan(2, [](int &){return true;});
    (void)pMutColl->fewerThan(2, [](int &){return true;});
    (void)pMutColl->count([](int &){return true;});
    (void)pMutColl->all([](int &){return true;});
    (void)pMutColl->any([](int &){return true;});
    (void)pMutColl->none([](int &){return true;});

    pMutColl->insert (5) = 3;

    timingTest ( 1000 );

    return 0;
}