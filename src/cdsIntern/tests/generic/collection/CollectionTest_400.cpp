#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

namespace {
    /* CollectionTestGroup-RemoveBy-cpp-xx : CTG-00400-RB-cpp-xx. CTC-00401-RB to CTC-00418-RB */
    template <
            typename __Original,                        /* NOLINT(bugprone-reserved-identifier) */
            typename __MemberType,                      /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingNonePredicateType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingOnePredicateType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingMoreLTLPredicateType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingMorePredicateType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingMoreMTLPredicateType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingAllPredicateType         /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupRemoveBy (
            __Original const & original,
            Test                                                     * pTestLib,
            Size                                                       removeThatLimit,
            Size                                                       removeThatResultWhenLessThanLimit,
            __MatchingNonePredicateType                        const & matchingNone,
            __MatchingOnePredicateType                         const & matchingOne,
            __MatchingMoreLTLPredicateType                     const & matchingMoreLessThanLimit,
            __MatchingMorePredicateType                        const & matchingMore,
            __MatchingMoreMTLPredicateType                     const & matchingMoreMoreThanLimit,
            __MatchingAllPredicateType                         const & matchingAll,
            cds :: Collection < __MemberType > const & equivAfterRemoveThatMatchesNone,
            cds :: Collection < __MemberType > const & equivAfterRemoveThatMatchesOne,
            cds :: Collection < __MemberType > const & equivAfterRemoveThatMatchesMoreLessThanLimit,
            cds :: Collection < __MemberType > const & equivAfterRemoveThatMatchesMoreExact,
            cds :: Collection < __MemberType > const & equivAfterRemoveThatMatchesMoreMoreThanLimit,
            cds :: Collection < __MemberType > const & equivAfterRemoveThatMatchesAll,
            cds :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesNone,
            cds :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesOne,
            cds :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesMore,
            cds :: Collection < __MemberType > const & equivAfterRemoveFirstThatMatchesAll,
            cds :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesNone,
            cds :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesOne,
            cds :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesMore,
            cds :: Collection < __MemberType > const & equivAfterRemoveLastThatMatchesAll,
            cds :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesNone,
            cds :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesOne,
            cds :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesMore,
            cds :: Collection < __MemberType > const & equivAfterRemoveAllThatMatchesAll
    ) -> bool {

        pTestLib->log ( "Object Under Test : %s", original.toString().cStr() );

        /* CollectionTestCase-RemoveBy-removeThatMatchesNone-cpp-xx : CTC-00401-RB-removeThatMatchesNone-cpp-xx */
        auto       copyRB401            = original;
        cds :: Collection < __MemberType > & collectionRB401 = copyRB401;
        auto       removedCountRB401    = collectionRB401.removeThat ( removeThatLimit, matchingNone );
        auto const expectedRemovedCountRB401 = 0;
        pTestLib->log ( "object after 'removeThat with none matching' : '%s'. expected : '%s'", collectionRB401.toString().cStr(), equivAfterRemoveThatMatchesNone.toString().cStr() );
        if ( removedCountRB401 != expectedRemovedCountRB401 || ! collectionRB401.equals ( equivAfterRemoveThatMatchesNone ) ) {
            pTestLib->logError( "'CTC-00401-RB-removeThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00401-RB-removeThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesOne-cpp-xx : CTC-00402-RB-removeThatMatchesOne-cpp-xx */
        auto       copyRB402            = original;
        cds :: Collection < __MemberType > & collectionRB402 = copyRB402;
        auto       removedCountRB402    = collectionRB402.removeThat ( removeThatLimit, matchingOne );
        auto const expectedRemovedCountRB402 = 1;
        pTestLib->log ( "object after 'removeThat with one matching' : '%s'. expected : '%s'", collectionRB402.toString().cStr(), equivAfterRemoveThatMatchesOne.toString().cStr() );
        if ( removedCountRB402 != expectedRemovedCountRB402 || ! collectionRB402.equals ( equivAfterRemoveThatMatchesOne ) ) {
            pTestLib->logError( "'CTC-00402-RB-removeThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00402-RB-removeThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesMoreLessThanLimit-cpp-xx : CTC-00403-RB-removeThatMatchesMoreLessThanLimit-cpp-xx */
        auto       copyRB403            = original;
        cds :: Collection < __MemberType > & collectionRB403 = copyRB403;
        auto       removedCountRB403    = collectionRB403.removeThat ( removeThatLimit, matchingMoreLessThanLimit );
        auto const expectedRemovedCountRB403 = removeThatResultWhenLessThanLimit;
        pTestLib->log ( "object after 'removeThat with more matching, less than limit' : '%s'. expected : '%s'", collectionRB403.toString().cStr(), equivAfterRemoveThatMatchesMoreLessThanLimit.toString().cStr() );
        if ( removedCountRB403 != expectedRemovedCountRB403 || ! collectionRB403.equals ( equivAfterRemoveThatMatchesMoreLessThanLimit ) ) {
            pTestLib->logError( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesMoreExact-cpp-xx : CTC-00404-RB-removeThatMatchesMoreExact-cpp-xx */
        auto       copyRB404            = original;
        cds :: Collection < __MemberType > & collectionRB404 = copyRB404;
        auto       removedCountRB404    = collectionRB404.removeThat ( removeThatLimit, matchingMore );
        auto const expectedRemovedCountRB404 = removeThatLimit;
        pTestLib->log ( "object after 'removeThat with more matching, exact' : '%s'. expected : '%s'", collectionRB404.toString().cStr(), equivAfterRemoveThatMatchesMoreExact.toString().cStr() );
        if ( removedCountRB404 != expectedRemovedCountRB404 || ! collectionRB404.equals ( equivAfterRemoveThatMatchesMoreExact ) ) {
            pTestLib->logError( "'CTC-00404-RB-removeThatMatchesMoreExact-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00404-RB-removeThatMatchesMoreExact-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesMoreMoreThanLimit-cpp-xx : CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-cpp-xx */
        auto       copyRB405            = original;
        cds :: Collection < __MemberType > & collectionRB405 = copyRB405;
        auto       removedCountRB405    = collectionRB405.removeThat ( removeThatLimit, matchingMoreMoreThanLimit );
        auto const expectedRemovedCountRB405 = removeThatLimit;
        pTestLib->log ( "object after 'removeThat with more matching' : '%s'. expected : '%s'", collectionRB405.toString().cStr(), equivAfterRemoveThatMatchesMoreMoreThanLimit.toString().cStr() );
        if ( removedCountRB405 != expectedRemovedCountRB405 || ! collectionRB405.equals ( equivAfterRemoveThatMatchesMoreMoreThanLimit ) ) {
            pTestLib->logError( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesAll-cpp-xx : CTC-00406-RB-removeThatMatchesAll-cpp-xx */
        auto       copyRB406            = original;
        cds :: Collection < __MemberType > & collectionRB406 = copyRB406;
        auto       removedCountRB406    = collectionRB406.removeThat ( removeThatLimit, matchingAll );
        auto const expectedRemovedCountRB406 = removeThatLimit;
        pTestLib->log ( "object after 'removeThat with all matching, less than limit' : '%s'. expected : '%s'", collectionRB406.toString().cStr(), equivAfterRemoveThatMatchesAll.toString().cStr() );
        if ( removedCountRB406 != expectedRemovedCountRB406 || ! collectionRB406.equals ( equivAfterRemoveThatMatchesAll ) ) {
            pTestLib->logError( "'CTC-00406-RB-removeThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00406-RB-removeThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesNone-cpp-xx : CTC-00407-RB-removeFirstThatMatchesNone-cpp-xx */
        auto       copyRB407            = original;
        cds :: Collection < __MemberType > & collectionRB407 = copyRB407;
        auto       removedCountRB407    = collectionRB407.removeFirstThat ( matchingNone );
        auto const expectedRemovedCountRB407 = false;
        pTestLib->log ( "object after 'removeFirstThat with no matches' : '%s'. expected : '%s'", collectionRB407.toString().cStr(), equivAfterRemoveFirstThatMatchesNone.toString().cStr() );
        if ( removedCountRB407 != expectedRemovedCountRB407 || ! collectionRB407.equals ( equivAfterRemoveFirstThatMatchesNone ) ) {
            pTestLib->logError( "'CTC-00407-RB-removeFirstThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00407-RB-removeFirstThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesOne-cpp-xx : CTC-00408-RB-removeFirstThatMatchesOne-cpp-xx */
        auto       copyRB408            = original;
        cds :: Collection < __MemberType > & collectionRB408 = copyRB408;
        auto       removedCountRB408    = collectionRB408.removeFirstThat ( matchingOne );
        auto const expectedRemovedCountRB408 = true;
        pTestLib->log ( "object after 'removeFirstThat with one match' : '%s'. expected : '%s'", collectionRB408.toString().cStr(), equivAfterRemoveFirstThatMatchesOne.toString().cStr() );
        if ( removedCountRB408 != expectedRemovedCountRB408 || ! collectionRB408.equals ( equivAfterRemoveFirstThatMatchesOne ) ) {
            pTestLib->logError( "'CTC-00408-RB-removeFirstThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00408-RB-removeFirstThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesMore-cpp-xx : CTC-00409-RB-removeFirstThatMatchesMore-cpp-xx */
        auto       copyRB409            = original;
        cds :: Collection < __MemberType > & collectionRB409 = copyRB409;
        auto       removedCountRB409    = collectionRB409.removeFirstThat ( matchingMore );
        auto const expectedRemovedCountRB409 = true;
        pTestLib->log ( "object after 'removeFirstThat with one or more matches' : '%s'. expected : '%s'", collectionRB409.toString().cStr(), equivAfterRemoveFirstThatMatchesMore.toString().cStr() );
        if ( removedCountRB409 != expectedRemovedCountRB409 || ! collectionRB409.equals ( equivAfterRemoveFirstThatMatchesMore ) ) {
            pTestLib->logError( "'CTC-00409-RB-removeFirstThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00409-RB-removeFirstThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesAll-cpp-xx : CTC-00410-RB-removeFirstThatMatchesAll-cpp-xx */
        auto       copyRB410            = original;
        cds :: Collection < __MemberType > & collectionRB410 = copyRB410;
        auto       removedCountRB410    = collectionRB410.removeFirstThat ( matchingAll );
        auto const expectedRemovedCountRB410 = true;
        pTestLib->log ( "object after 'removeFirstThat matches all' : '%s'. expected : '%s'", collectionRB410.toString().cStr(), equivAfterRemoveFirstThatMatchesAll.toString().cStr() );
        if ( removedCountRB410 != expectedRemovedCountRB410 || ! collectionRB410.equals ( equivAfterRemoveFirstThatMatchesAll ) ) {
            pTestLib->logError( "'CTC-00410-RB-removeFirstThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00410-RB-removeFirstThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesNone-cpp-xx : CTC-00411-RB-removeLastThatMatchesNone-cpp-xx */
        auto       copyRB411            = original;
        cds :: Collection < __MemberType > & collectionRB411 = copyRB411;
        auto       removedCountRB411    = collectionRB411.removeLastThat ( matchingNone );
        auto const expectedRemovedCountRB411 = false;
        pTestLib->log ( "object after 'removeLastThat with no matches' : '%s'. expected : '%s'", collectionRB411.toString().cStr(), equivAfterRemoveLastThatMatchesNone.toString().cStr() );
        if ( removedCountRB411 != expectedRemovedCountRB411 || ! collectionRB411.equals ( equivAfterRemoveLastThatMatchesNone ) ) {
            pTestLib->logError( "'CTC-00411-RB-removeLastThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00411-RB-removeLastThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesOne-cpp-xx : CTC-00412-RB-removeLastThatMatchesOne-cpp-xx */
        auto       copyRB412            = original;
        cds :: Collection < __MemberType > & collectionRB412 = copyRB412;
        auto       removedCountRB412    = collectionRB412.removeLastThat ( matchingOne );
        auto const expectedRemovedCountRB412 = true;
        pTestLib->log ( "object after 'removeLastThat with one match' : '%s'. expected : '%s'", collectionRB412.toString().cStr(), equivAfterRemoveLastThatMatchesOne.toString().cStr() );
        if ( removedCountRB412 != expectedRemovedCountRB412 || ! collectionRB412.equals ( equivAfterRemoveLastThatMatchesOne ) ) {
            pTestLib->logError( "'CTC-00412-RB-removeLastThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00412-RB-removeLastThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesMore-cpp-xx : CTC-00413-RB-removeLastThatMatchesMore-cpp-xx */
        auto       copyRB413            = original;
        cds :: Collection < __MemberType > & collectionRB413 = copyRB413;
        auto       removedCountRB413    = collectionRB413.removeLastThat ( matchingMore );
        auto const expectedRemovedCountRB413 = true;
        pTestLib->log ( "object after 'removeLastThat with one or more matches' : '%s'. expected : '%s'", collectionRB413.toString().cStr(), equivAfterRemoveLastThatMatchesMore.toString().cStr() );
        if ( removedCountRB413 != expectedRemovedCountRB413 || ! collectionRB413.equals ( equivAfterRemoveLastThatMatchesMore ) ) {
            pTestLib->logError( "'CTC-00413-RB-removeLastThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00413-RB-removeLastThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesAll-cpp-xx : CTC-00414-RB-removeLastThatMatchesAll-cpp-xx */
        auto       copyRB414            = original;
        cds :: Collection < __MemberType > & collectionRB414 = copyRB414;
        auto       removedCountRB414    = collectionRB414.removeLastThat ( matchingAll );
        auto const expectedRemovedCountRB414 = true;
        pTestLib->log ( "object after 'removeLastThat matching all' : '%s'. expected : '%s'", collectionRB414.toString().cStr(), equivAfterRemoveLastThatMatchesAll.toString().cStr() );
        if ( removedCountRB414 != expectedRemovedCountRB414 || ! collectionRB414.equals ( equivAfterRemoveLastThatMatchesAll ) ) {
            pTestLib->logError( "'CTC-00414-RB-removeLastThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00414-RB-removeLastThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesNone-cpp-xx : CTC-00415-RB-removeAllThatMatchesNone-cpp-xx */
        auto       copyRB415            = original;
        cds :: Collection < __MemberType > & collectionRB415 = copyRB415;
        auto const expectedRemovedCountRB415 = collectionRB415.count ( matchingNone );
        auto       removedCountRB415    = collectionRB415.removeAllThat ( matchingNone );
        pTestLib->log ( "object after 'removeAllThat match none' : '%s'. expected : '%s'", collectionRB415.toString().cStr(), equivAfterRemoveAllThatMatchesNone.toString().cStr() );
        if ( removedCountRB415 != expectedRemovedCountRB415 || ! collectionRB415.equals ( equivAfterRemoveAllThatMatchesNone ) ) {
            pTestLib->logError( "'CTC-00415-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00415-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesOne-cpp-xx : CTC-00416-RB-removeAllThatMatchesOne-cpp-xx */
        auto       copyRB416            = original;
        cds :: Collection < __MemberType > & collectionRB416 = copyRB416;
        auto const expectedRemovedCountRB416 = collectionRB416.count ( matchingOne );
        auto       removedCountRB416    = collectionRB416.removeAllThat ( matchingOne );
        pTestLib->log ( "object after 'removeAllThat matching one' : '%s'. expected : '%s'", collectionRB416.toString().cStr(), equivAfterRemoveAllThatMatchesOne.toString().cStr() );
        if ( removedCountRB416 != expectedRemovedCountRB416 || ! collectionRB416.equals ( equivAfterRemoveAllThatMatchesOne ) ) {
            pTestLib->logError( "'CTC-00416-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00416-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesMore-cpp-xx : CTC-00417-RB-removeAllThatMatchesMore-cpp-xx */
        auto       copyRB417            = original;
        cds :: Collection < __MemberType > & collectionRB417 = copyRB417;
        auto const expectedRemovedCountRB417 = collectionRB417.count ( matchingMore );
        auto       removedCountRB417    = collectionRB417.removeAllThat ( matchingMore );
        pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB417.toString().cStr(), equivAfterRemoveAllThatMatchesMore.toString().cStr() );
        if ( removedCountRB417 != expectedRemovedCountRB417 || ! collectionRB417.equals ( equivAfterRemoveAllThatMatchesMore ) ) {
            pTestLib->logError( "'CTC-00417-RB-removeAllThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00417-RB-removeAllThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesAll-cpp-xx : CTC-00418-RB-removeAllThatMatchesAll-cpp-xx */
        auto       copyRB418            = original;
        cds :: Collection < __MemberType > & collectionRB418 = copyRB418;
        auto const expectedRemovedCountRB418 = collectionRB418.count ( matchingAll );
        auto       removedCountRB418    = collectionRB418.removeAllThat ( matchingAll );
        pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB418.toString().cStr(), equivAfterRemoveAllThatMatchesAll.toString().cStr() );
        if ( removedCountRB418 != expectedRemovedCountRB418 || ! collectionRB418.equals ( equivAfterRemoveAllThatMatchesAll ) ) {
            pTestLib->logError( "'CTC-00418-RB-removeAllThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00418-RB-removeAllThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        return true;
    }
}

auto CollectionTest::tests_00400_00449 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](int x) { return x > 100; },
                /* matchingOne = */                                     [](int x) { return x == 3; },
                /* matchingMoreLessThanLimit = */                       [](int x) { return x >= 4 && x <= 5; },
                /* matchingMore = */                                    [](int x) { return x >= 4 && x <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](int x) { return x >= 4 && x <= 7; },
                /* matchingAll = */                                     [](int x) { return x >= 1 && x <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 make_a <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesOne = */                  make_a <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_a <int> ( 1, 2, 3, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_a <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_a <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesAll = */                  make_a <int> ( 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_a <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_a <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_a <int> ( 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_a <int> ( 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_a <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_a <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_a <int> ( 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_a <int> ( 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_a <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_a <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_a <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_a <int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](int x) { return x > 100; },
                /* matchingOne = */                                     [](int x) { return x == 3; },
                /* matchingMoreLessThanLimit = */                       [](int x) { return x >= 4 && x <= 5; },
                /* matchingMore = */                                    [](int x) { return x >= 4 && x <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](int x) { return x >= 4 && x <= 7; },
                /* matchingAll = */                                     [](int x) { return x >= 1 && x <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 make_ll <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesOne = */                  make_ll <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_ll <int> ( 1, 2, 3, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_ll <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_ll <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesAll = */                  make_ll <int> ( 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_ll <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_ll <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_ll <int> ( 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_ll <int> ( 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_ll <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_ll <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_ll <int> ( 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_ll <int> ( 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_ll <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_ll <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_ll <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_ll <int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntHashSet", [this, & allOk]{

        cds :: HashSet < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](int x) { return x > 100; },
                /* matchingOne = */                                     [](int x) { return x == 3; },
                /* matchingMoreLessThanLimit = */                       [](int x) { return x >= 4 && x <= 5; },
                /* matchingMore = */                                    [](int x) { return x >= 4 && x <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](int x) { return x >= 4 && x <= 7; },
                /* matchingAll = */                                     [](int x) { return x >= 1 && x <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 make_hs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesOne = */                  make_hs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_hs <int> ( 1, 2, 3, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_hs <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_hs <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesAll = */                  make_hs <int> ( 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_hs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_hs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_hs <int> ( 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_hs <int> ( 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_hs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_hs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_hs <int> ( 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_hs <int> ( 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_hs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_hs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_hs <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_hs <int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntTreeSet", [this, & allOk]{

        cds :: TreeSet < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](int x) { return x > 100; },
                /* matchingOne = */                                     [](int x) { return x == 3; },
                /* matchingMoreLessThanLimit = */                       [](int x) { return x >= 4 && x <= 5; },
                /* matchingMore = */                                    [](int x) { return x >= 4 && x <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](int x) { return x >= 4 && x <= 7; },
                /* matchingAll = */                                     [](int x) { return x >= 1 && x <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 make_ts <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesOne = */                  make_ts <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_ts <int> ( 1, 2, 3, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_ts <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_ts <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesAll = */                  make_ts <int> ( 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_ts <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_ts <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_ts <int> ( 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_ts <int> ( 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_ts <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_ts <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_ts <int> ( 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_ts <int> ( 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_ts <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_ts <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_ts <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_ts <int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [this, & allOk]{

        cds :: LinkedHashSet < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](int x) { return x > 100; },
                /* matchingOne = */                                     [](int x) { return x == 3; },
                /* matchingMoreLessThanLimit = */                       [](int x) { return x >= 4 && x <= 5; },
                /* matchingMore = */                                    [](int x) { return x >= 4 && x <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](int x) { return x >= 4 && x <= 7; },
                /* matchingAll = */                                     [](int x) { return x >= 1 && x <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 make_lhs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesOne = */                  make_lhs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_lhs <int> ( 1, 2, 3, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_lhs <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_lhs <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesAll = */                  make_lhs <int> ( 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_lhs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_lhs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_lhs <int> ( 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_lhs <int> ( 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_lhs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_lhs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_lhs <int> ( 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_lhs <int> ( 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_lhs <int> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_lhs <int> ( 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_lhs <int> ( 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_lhs <int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](MapEntry < int, int > const & x) { return x.key() > 100; },
                /* matchingOne = */                                     [](MapEntry < int, int > const & x) { return x.key() == 3; },
                /* matchingMoreLessThanLimit = */                       [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 5; },
                /* matchingMore = */                                    [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 7; },
                /* matchingAll = */                                     [](MapEntry < int, int > const & x) { return x.key() >= 1 && x.key() <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* equivAfterRemoveThatMatchesOne = */                  cds::HashMap <int, int> { {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreExact = */            cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesAll = */                  cds::HashMap <int, int> { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesNone = */            cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesOne = */             cds::HashMap <int, int> { {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesMore = */            cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesAll = */             cds::HashMap <int, int> { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesNone = */             cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesOne = */              cds::HashMap <int, int> { {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesMore = */             cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesAll = */              cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* equivAfterRemoveAllThatMatchesNone = */              cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesOne = */               cds::HashMap <int, int> { {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesMore = */              cds::HashMap <int, int> { {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesAll = */               cds::HashMap <int, int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < int, int > originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](MapEntry < int, int > const & x) { return x.key() > 100; },
                /* matchingOne = */                                     [](MapEntry < int, int > const & x) { return x.key() == 3; },
                /* matchingMoreLessThanLimit = */                       [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 5; },
                /* matchingMore = */                                    [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 7; },
                /* matchingAll = */                                     [](MapEntry < int, int > const & x) { return x.key() >= 1 && x.key() <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesOne = */                  cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreExact = */            cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesAll = */                  cds::LinkedHashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesNone = */            cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesOne = */             cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesMore = */            cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesAll = */             cds::LinkedHashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesNone = */             cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesOne = */              cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesMore = */             cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesAll = */              cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* equivAfterRemoveAllThatMatchesNone = */              cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesOne = */               cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesMore = */              cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesAll = */               cds::LinkedHashMap <int, int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, & allOk]{

        cds :: TreeMap < int, int > originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](MapEntry < int, int > const & x) { return x.key() > 100; },
                /* matchingOne = */                                     [](MapEntry < int, int > const & x) { return x.key() == 3; },
                /* matchingMoreLessThanLimit = */                       [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 5; },
                /* matchingMore = */                                    [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 6; },
                /* matchingMoreMoreThanLimit = */                       [](MapEntry < int, int > const & x) { return x.key() >= 4 && x.key() <= 7; },
                /* matchingAll = */                                     [](MapEntry < int, int > const & x) { return x.key() >= 1 && x.key() <= 9; },
                /* equivAfterRemoveThatMatchesNone = */                 cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesOne = */                  cds::TreeMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreExact = */            cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveThatMatchesAll = */                  cds::TreeMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesNone = */            cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesOne = */             cds::TreeMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesMore = */            cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveFirstThatMatchesAll = */             cds::TreeMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesNone = */             cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesOne = */              cds::TreeMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesMore = */             cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveLastThatMatchesAll = */              cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* equivAfterRemoveAllThatMatchesNone = */              cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesOne = */               cds::TreeMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesMore = */              cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* equivAfterRemoveAllThatMatchesAll = */               cds::TreeMap <int, int> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](String const & x) { return x == "ddd"; },
                /* matchingOne = */                                     [](String const & x) { return x == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](String const & x) { return x.startsWith ("bb") && ! x.endsWith ("a"); },
                /* matchingMore = */                                    [](String const & x) { return x.startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](String const & x) { return x.startsWith ("bb") || x.endsWith ("b"); },
                /* matchingAll = */                                     [](String const & x) { return ! x.empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_a <String> ( "aaa", "aab", "aac", "bba", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_a <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_a <String> ( "aaa", "aac", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_a <String> ( "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_a <String> ( "aaa", "aab", "aac", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_a <String> ( "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_a <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_a <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_a < String > ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](String const & x) { return x == "ddd"; },
                /* matchingOne = */                                     [](String const & x) { return x == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](String const & x) { return x.startsWith ("bb") && ! x.endsWith ("a"); },
                /* matchingMore = */                                    [](String const & x) { return x.startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](String const & x) { return x.startsWith ("bb") || x.endsWith ("b"); },
                /* matchingAll = */                                     [](String const & x) { return ! x.empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_ll <String> ( "aaa", "aab", "aac", "bba", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_ll <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_ll <String> ( "aaa", "aac", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_ll <String> ( "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_ll <String> ( "aaa", "aab", "aac", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_ll <String> ( "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_ll <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_ll <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_ll <String> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringHashSet", [this, & allOk]{

        cds :: HashSet < String > originalArray = { "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" };

        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](String const & x) { return x == "ddd"; },
                /* matchingOne = */                                     [](String const & x) { return x == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](String const & x) { return x.startsWith ("bb") && ! x.endsWith ("a"); },
                /* matchingMore = */                                    [](String const & x) { return x.startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](String const & x) { return x.startsWith ("bb") || x.endsWith ("b"); },
                /* matchingAll = */                                     [](String const & x) { return ! x.empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "cca" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "cca" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_hs <String>( "ccc", "aaa", "aac", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_hs <String>( "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_hs <String>( "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_hs <String>( "ccb", "ccc", "aaa", "aab", "aac", "cca" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_hs <String>()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringTreeSet", [this, & allOk]{

        cds :: TreeSet < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](String const & x) { return x == "ddd"; },
                /* matchingOne = */                                     [](String const & x) { return x == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](String const & x) { return x.startsWith ("bb") && ! x.endsWith ("a"); },
                /* matchingMore = */                                    [](String const & x) { return x.startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](String const & x) { return x.startsWith ("bb") || x.endsWith ("b"); },
                /* matchingAll = */                                     [](String const & x) { return ! x.empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_ts <String> ( "aaa", "aab", "aac", "bba", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_ts <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_ts <String> ( "aaa", "aac", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_ts <String> ( "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_ts <String> ( "aaa", "aab", "aac", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_ts <String> ( "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_ts <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_ts <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_ts <String> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [this, & allOk]{

        cds :: LinkedHashSet < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](String const & x) { return x == "ddd"; },
                /* matchingOne = */                                     [](String const & x) { return x == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](String const & x) { return x.startsWith ("bb") && ! x.endsWith ("a"); },
                /* matchingMore = */                                    [](String const & x) { return x.startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](String const & x) { return x.startsWith ("bb") || x.endsWith ("b"); },
                /* matchingAll = */                                     [](String const & x) { return ! x.empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_lhs <String> ( "aaa", "aab", "aac", "bba", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_lhs <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_lhs <String> ( "aaa", "aac", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_lhs <String> ( "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_lhs <String> ( "aaa", "aab", "aac", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_lhs <String> ( "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_lhs <String> ( "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_lhs <String> ( "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_lhs <String> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > originalArray = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](MapEntry < String, String > const & x) { return x.key() == "ddd"; },
                /* matchingOne = */                                     [](MapEntry < String, String > const & x) { return x.key() == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") && ! x.key().endsWith ("a"); },
                /* matchingMore = */                                    [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") || x.key().endsWith ("b"); },
                /* matchingAll = */                                     [](MapEntry < String, String > const & x) { return ! x.key().empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveThatMatchesOne = */                  cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} },
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"cca", "cca"} },
                /* equivAfterRemoveThatMatchesMoreExact = */            cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"} },
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    cds::HashMap <String, String> { {"ccc", "ccc"}, {"aaa", "aaa"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveThatMatchesAll = */                  cds::HashMap <String, String> { {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveFirstThatMatchesNone = */            cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveFirstThatMatchesOne = */             cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} },
                /* equivAfterRemoveFirstThatMatchesMore = */            cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveFirstThatMatchesAll = */             cds::HashMap <String, String> { {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveLastThatMatchesNone = */             cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveLastThatMatchesOne = */              cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} },
                /* equivAfterRemoveLastThatMatchesMore = */             cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} },
                /* equivAfterRemoveLastThatMatchesAll = */              cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"} },
                /* equivAfterRemoveAllThatMatchesNone = */              cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} },
                /* equivAfterRemoveAllThatMatchesOne = */               cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} },
                /* equivAfterRemoveAllThatMatchesMore = */              cds::HashMap <String, String> { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"} },
                /* equivAfterRemoveAllThatMatchesAll = */               cds::HashMap <String, String> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < String, String > originalArray = { {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](MapEntry < String, String > const & x) { return x.key() == "ddd"; },
                /* matchingOne = */                                     [](MapEntry < String, String > const & x) { return x.key() == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") && ! x.key().endsWith ("a"); },
                /* matchingMore = */                                    [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") || x.key().endsWith ("b"); },
                /* matchingAll = */                                     [](MapEntry < String, String > const & x) { return ! x.key().empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesOne = */                  cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesMoreExact = */            cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aac", "aac"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesAll = */                  cds::LinkedHashMap <String, String> {{"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesNone = */            cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesOne = */             cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesMore = */            cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesAll = */             cds::LinkedHashMap <String, String> {{"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesNone = */             cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesOne = */              cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesMore = */             cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesAll = */              cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"} },
                /* equivAfterRemoveAllThatMatchesNone = */              cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveAllThatMatchesOne = */               cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveAllThatMatchesMore = */              cds::LinkedHashMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveAllThatMatchesAll = */               cds::LinkedHashMap <String, String> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [this, & allOk]{

        cds :: TreeMap < String, String > originalArray = { {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };


        allOk = allOk && collectionTestGroupRemoveBy (
                /* original= */                                         originalArray,
                /* pTestLib= */                                         this,
                /* removeThatLimit = */                                 3,
                /* removeThatResultWhenLessThanLimit = */               2,
                /* matchingNone = */                                    [](MapEntry < String, String > const & x) { return x.key() == "ddd"; },
                /* matchingOne = */                                     [](MapEntry < String, String > const & x) { return x.key() == "bbc"; },
                /* matchingMoreLessThanLimit = */                       [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") && ! x.key().endsWith ("a"); },
                /* matchingMore = */                                    [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb"); },
                /* matchingMoreMoreThanLimit = */                       [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") || x.key().endsWith ("b"); },
                /* matchingAll = */                                     [](MapEntry < String, String > const & x) { return ! x.key().empty(); },
                /* equivAfterRemoveThatMatchesNone = */                 cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesOne = */                  cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesMoreExact = */            cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aac", "aac"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveThatMatchesAll = */                  cds::TreeMap <String, String> {{"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesNone = */            cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesOne = */             cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesMore = */            cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveFirstThatMatchesAll = */             cds::TreeMap <String, String> {{"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesNone = */             cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesOne = */              cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesMore = */             cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveLastThatMatchesAll = */              cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"} },
                /* equivAfterRemoveAllThatMatchesNone = */              cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveAllThatMatchesOne = */               cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveAllThatMatchesMore = */              cds::TreeMap <String, String> {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} },
                /* equivAfterRemoveAllThatMatchesAll = */               cds::TreeMap <String, String> ()
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringArrayMemberFunction", [this, & allOk]{

        cds :: Array < String > strArray = { "word1", "word2", "", "", "word3", "", "word4", "", "", "","", "word5", "" };

        auto copyForRemoveThat      = strArray;
        auto copyForRemoveFirstThat = strArray;
        auto copyForRemoveLastThat  = strArray;
        auto copyForRemoveAllThat   = strArray;
        cds :: Array < String > copyForRemoveAllThatCoverage   = {"word1", "word2", "", "word3", "word4", "word5"};

        cds :: Collection < String > & cRT  = copyForRemoveThat;
        cds :: Collection < String > & cRFT = copyForRemoveFirstThat;
        cds :: Collection < String > & cRLT = copyForRemoveLastThat;
        cds :: Collection < String > & cRAT = copyForRemoveAllThat;
        cds :: Collection < String > & cRATCoverage = copyForRemoveAllThatCoverage;
        Size removeThatLimit = 5;

        cds :: Array < String > expectedAfterRemoveThat         = { "word1", "word2", "word3", "word4", "", "", "word5", "" };
        cds :: Array < String > expectedAfterRemoveFirstThat    = { "word1", "word2", "", "word3", "", "word4", "", "", "","", "word5", "" };
        cds :: Array < String > expectedAfterRemoveLastThat     = { "word1", "word2", "", "", "word3", "", "word4", "", "", "","", "word5" };
        cds :: Array < String > expectedAfterRemoveAllThat      = { "word1", "word2", "word3", "word4", "word5" };
        cds :: Array < String > expectedAfterRemoveAllThatCoverage = { "word1", "word2", "word3", "word4", "word5" };

        Size removeThatExpected = 5;
        bool removeFirstThatExpected = true;
        bool removeLastThatExpected = true;
        Size removeAllThatExpected = 8;

        /* CollectionTestCase-RemoveBy-memberRemoveThat-cpp-xx : CTC-00419-RB-memberRemoveThat-cpp-xx */
        Size removeThatRes = cRT.removeThat ( removeThatLimit, & String :: empty );
        if ( removeThatExpected != removeThatRes || ! cRT.equals ( expectedAfterRemoveThat ) ) {
            this->logError ( "'CTC-00419-RB-memberRemoveThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00419-RB-memberRemoveThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveFirstThat-cpp-xx : CTC-00420-RB-memberRemoveFirstThat-cpp-xx */
        bool removeFirstThatRes = cRFT.removeFirstThat ( & String :: empty );
        if ( removeFirstThatExpected != removeFirstThatRes || ! cRFT.equals ( expectedAfterRemoveFirstThat ) ) {
            this->logError ( "'CTC-00420-RB-memberRemoveFirstThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00420-RB-memberRemoveFirstThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveLastThat-cpp-xx : CTC-00421-RB-memberRemoveLastThat-cpp-xx */
        bool removeLastThatRes = cRLT.removeLastThat ( & String :: empty );
        if ( removeLastThatExpected != removeLastThatRes || ! cRLT.equals ( expectedAfterRemoveLastThat ) ) {
            this->logError ( "'CTC-00421-RB-memberRemoveLastThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00421-RB-memberRemoveLastThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveAllThat-cpp-xx : CTC-00422-RB-memberRemoveAllThat-cpp-xx */
        Size removeAllThatRes = cRAT.removeAllThat ( & String :: empty );
        if ( removeAllThatExpected != removeAllThatRes || ! cRAT.equals ( expectedAfterRemoveAllThat ) ) {
            this->logError ( "'CTC-00422-RB-memberRemoveAllThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00422-RB-memberRemoveAllThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveThatCoverage-cpp-xx : CTC-00423-RB-memberRemoveThatCoverage-cpp-xx */
        Size removeAllThatCovRes = cRATCoverage.removeAllThat ( & String :: empty );
        if ( 1U != removeAllThatCovRes || ! cRATCoverage.equals ( expectedAfterRemoveAllThatCoverage ) ) {
            this->logError ( "'CTC-00423-RB-memberRemoveThatCoverage-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00423-RB-memberRemoveThatCoverage-" __CDS_cpplang_core_version_name "' OK" );
        }

        cds :: Collection < String > & extraForNegCoverage = expectedAfterRemoveAllThatCoverage;

        (void) extraForNegCoverage.removeThat (5, & String :: empty);
        (void) extraForNegCoverage.removeFirstThat (& String :: empty);
        (void) extraForNegCoverage.removeLastThat (& String :: empty);
        (void) extraForNegCoverage.removeAllThat (& String :: empty);

        (void) extraForNegCoverage.insert ("");
        (void) extraForNegCoverage.removeThat (5, & String :: empty);

    });

    return allOk;
}
