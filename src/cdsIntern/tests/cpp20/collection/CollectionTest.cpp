//
// Created by loghin on 30.11.2021.
//

#include "CollectionTest.h"

#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>
#include <CDS/experimental/HashSet>
#include <CDS/experimental/HashMap>

/* CollectionTestGroup-RemoveAbsIt-Cpp20 : CTG-00350-RAIT-CPP20. CTC-00351-RAIT to CTC-00356-RAIT */
template <
        typename __MemberType  /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupRemoveAbstractIterator (
        cds :: experimental :: Collection < __MemberType >       & collection,
        Test                                                     * pTestLib,
        cds :: experimental :: Collection < __MemberType > const & equivAfter1,
        cds :: experimental :: Collection < __MemberType > const & equivAfter2,
        cds :: experimental :: Collection < __MemberType > const & equivAfter3,
//        cds :: experimental :: Collection < __MemberType > const & equivAfter3,                                   N/A with Collection
//        typename cds :: experimental :: Collection < __MemberType > :: ConstIterator const & toRemoveBeforeFront,
        cds :: experimental :: Collection < __MemberType > const & equivAfter5,
        cds :: experimental :: Collection < __MemberType > const & equivAfter6
) -> bool {

    pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );

    /* CollectionTestCase-RemoveAbsIt-removeAtFront-CPP20 : CTC-00351-RAIT-removeAtFront-CPP20 */
    auto       toRemoveAtFront = collection.begin();
    auto const resultToRemoveAtFront = collection.remove( toRemoveAtFront );
    auto const expectedResultToRemoveAtFront = true;
    pTestLib->log ( "object after 'removeAtFront' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter1.toString().cStr() );
    if ( resultToRemoveAtFront != expectedResultToRemoveAtFront || ! collection.equals ( equivAfter1 ) ) {
        pTestLib->logError( "'CTC-00351-RAIT-removeAtFront-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00351-RAIT-removeAtFront-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveAbsIt-removeInBounds-CPP20 : CTC-00352-RAIT-removeInBounds-CPP20 */
    auto       toRemoveInBounds = collection.begin();
    for ( uint32 i = 0; i * 2 < collection.size(); ++ i ) {
        ++ toRemoveInBounds;
    }

    auto const resultToRemoveAtInBounds = collection.remove( toRemoveInBounds );
    auto const expectedResultToRemoveAtInBounds = true;
    pTestLib->log ( "object after 'removeInBounds' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter2.toString().cStr() );
    if ( resultToRemoveAtInBounds != expectedResultToRemoveAtInBounds || ! collection.equals ( equivAfter2 ) ) {
        pTestLib->logError( "'CTC-00352-RAIT-removeInBounds-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00352-RAIT-removeInBounds-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveAbsIt-removeAtEnd-CPP20 : CTC-00353-RAIT-removeAtEnd-CPP20 */
    auto       toRemoveAtEnd = collection.begin();
    for ( uint32 i = 0; i + 1 < collection.size(); ++ i ) {
        ++ toRemoveAtEnd;
    }

    auto const resultToRemoveAtEnd = collection.remove( toRemoveAtEnd );
    auto const expectedResultToRemoveAtEnd = true;
    pTestLib->log ( "object after 'removeAtEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter3.toString().cStr() );
    if ( resultToRemoveAtEnd != expectedResultToRemoveAtEnd || ! collection.equals ( equivAfter3 ) ) {
        pTestLib->logError( "'CTC-00353-RAIT-removeAtEnd-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00353-RAIT-removeAtEnd-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveAbsIt-removeBeforeFront-CPP20 : CTC-00354-RAIT-removeBeforeFront-CPP20 : N/A */

    /* CollectionTestCase-RemoveAbsIt-removeAfterEnd-CPP20 : CTC-00355-RAIT-removeAfterEnd-CPP20 */
    auto       toRemoveAfterBack = collection.end();
    auto const resultToRemoveAfterEnd = collection.remove( toRemoveAfterBack );
    auto const expectedResultToRemoveAfterEnd = false;
    pTestLib->log ( "object after 'removeAfterEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
    if ( resultToRemoveAfterEnd != expectedResultToRemoveAfterEnd || ! collection.equals ( equivAfter5 ) ) {
        pTestLib->logError( "'CTC-00355-RAIT-removeAfterEnd-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00355-RAIT-removeAfterEnd-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveAbsIt-removeFromOther-CPP20 : CTC-00355-RAIT-removeFromOther-CPP20 */
    auto toRemoveFromSimilar = equivAfter2.begin();
    auto const resultToRemoveFromSimilar = collection.remove( toRemoveFromSimilar );
    auto const expectedResultToRemoveFromSimilar = false;
    pTestLib->log ( "object after 'removeFromOther' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
    if ( resultToRemoveFromSimilar != expectedResultToRemoveFromSimilar || ! collection.equals ( equivAfter6 ) ) {
        pTestLib->logError( "'CTC-00356-RAIT-removeFromOther-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00356-RAIT-removeFromOther-CPP20' OK" );
    }

    return true;
}

/* CollectionTestGroup-RemoveBy-Cpp20 : CTG-00400-RB-CPP20. CTC-00401-RB to CTC-00418-RB */
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

    pTestLib->log ( "Object Under Test : %s", original.toString().cStr() );

    /* CollectionTestCase-RemoveBy-removeThatMatchesNone-CPP20 : CTC-00401-RB-removeThatMatchesNone-CPP20 */
    auto       copyRB401            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB401 = copyRB401;
    auto       removedCountRB401    = collectionRB401.removeThat ( removeThatLimit, matchingNone );
    auto const expectedRemovedCountRB401 = 0;
    pTestLib->log ( "object after 'removeThat with none matching' : '%s'. expected : '%s'", collectionRB401.toString().cStr(), equivAfterRemoveThatMatchesNone.toString().cStr() );
    if ( removedCountRB401 != expectedRemovedCountRB401 || ! collectionRB401.equals ( equivAfterRemoveThatMatchesNone ) ) {
        pTestLib->logError( "'CTC-00401-RB-removeThatMatchesNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00401-RB-removeThatMatchesNone-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeThatMatchesOne-CPP20 : CTC-00402-RB-removeThatMatchesOne-CPP20 */
    auto       copyRB402            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB402 = copyRB402;
    auto       removedCountRB402    = collectionRB402.removeThat ( removeThatLimit, matchingOne );
    auto const expectedRemovedCountRB402 = 1;
    pTestLib->log ( "object after 'removeThat with one matching' : '%s'. expected : '%s'", collectionRB402.toString().cStr(), equivAfterRemoveThatMatchesOne.toString().cStr() );
    if ( removedCountRB402 != expectedRemovedCountRB402 || ! collectionRB402.equals ( equivAfterRemoveThatMatchesOne ) ) {
        pTestLib->logError( "'CTC-00402-RB-removeThatMatchesOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00402-RB-removeThatMatchesOne-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeThatMatchesMoreLessThanLimit-CPP20 : CTC-00403-RB-removeThatMatchesMoreLessThanLimit-CPP20 */
    auto       copyRB403            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB403 = copyRB403;
    auto       removedCountRB403    = collectionRB403.removeThat ( removeThatLimit, matchingMoreLessThanLimit );
    auto const expectedRemovedCountRB403 = removeThatResultWhenLessThanLimit;
    pTestLib->log ( "object after 'removeThat with more matching, less than limit' : '%s'. expected : '%s'", collectionRB403.toString().cStr(), equivAfterRemoveThatMatchesMoreLessThanLimit.toString().cStr() );
    if ( removedCountRB403 != expectedRemovedCountRB403 || ! collectionRB403.equals ( equivAfterRemoveThatMatchesMoreLessThanLimit ) ) {
        pTestLib->logError( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeThatMatchesMoreExact-CPP20 : CTC-00404-RB-removeThatMatchesMoreExact-CPP20 */
    auto       copyRB404            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB404 = copyRB404;
    auto       removedCountRB404    = collectionRB404.removeThat ( removeThatLimit, matchingMore );
    auto const expectedRemovedCountRB404 = removeThatLimit;
    pTestLib->log ( "object after 'removeThat with more matching, exact' : '%s'. expected : '%s'", collectionRB404.toString().cStr(), equivAfterRemoveThatMatchesMoreExact.toString().cStr() );
    if ( removedCountRB404 != expectedRemovedCountRB404 || ! collectionRB404.equals ( equivAfterRemoveThatMatchesMoreExact ) ) {
        pTestLib->logError( "'CTC-00404-RB-removeThatMatchesMoreExact-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00404-RB-removeThatMatchesMoreExact-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeThatMatchesMoreMoreThanLimit-CPP20 : CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-CPP20 */
    auto       copyRB405            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB405 = copyRB405;
    auto       removedCountRB405    = collectionRB405.removeThat ( removeThatLimit, matchingMoreMoreThanLimit );
    auto const expectedRemovedCountRB405 = removeThatLimit;
    pTestLib->log ( "object after 'removeThat with more matching' : '%s'. expected : '%s'", collectionRB405.toString().cStr(), equivAfterRemoveThatMatchesMoreMoreThanLimit.toString().cStr() );
    if ( removedCountRB405 != expectedRemovedCountRB405 || ! collectionRB405.equals ( equivAfterRemoveThatMatchesMoreMoreThanLimit ) ) {
        pTestLib->logError( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeThatMatchesAll-CPP20 : CTC-00406-RB-removeThatMatchesAll-CPP20 */
    auto       copyRB406            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB406 = copyRB406;
    auto       removedCountRB406    = collectionRB406.removeThat ( removeThatLimit, matchingAll );
    auto const expectedRemovedCountRB406 = removeThatLimit;
    pTestLib->log ( "object after 'removeThat with all matching, less than limit' : '%s'. expected : '%s'", collectionRB406.toString().cStr(), equivAfterRemoveThatMatchesAll.toString().cStr() );
    if ( removedCountRB406 != expectedRemovedCountRB406 || ! collectionRB406.equals ( equivAfterRemoveThatMatchesAll ) ) {
        pTestLib->logError( "'CTC-00406-RB-removeThatMatchesAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00406-RB-removeThatMatchesAll-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesNone-CPP20 : CTC-00407-RB-removeFirstThatMatchesNone-CPP20 */
    auto       copyRB407            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB407 = copyRB407;
    auto       removedCountRB407    = collectionRB407.removeFirstThat ( matchingNone );
    auto const expectedRemovedCountRB407 = false;
    pTestLib->log ( "object after 'removeFirstThat with no matches' : '%s'. expected : '%s'", collectionRB407.toString().cStr(), equivAfterRemoveFirstThatMatchesNone.toString().cStr() );
    if ( removedCountRB407 != expectedRemovedCountRB407 || ! collectionRB407.equals ( equivAfterRemoveFirstThatMatchesNone ) ) {
        pTestLib->logError( "'CTC-00407-RB-removeFirstThatMatchesNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00407-RB-removeFirstThatMatchesNone-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesOne-CPP20 : CTC-00408-RB-removeFirstThatMatchesOne-CPP20 */
    auto       copyRB408            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB408 = copyRB408;
    auto       removedCountRB408    = collectionRB408.removeFirstThat ( matchingOne );
    auto const expectedRemovedCountRB408 = true;
    pTestLib->log ( "object after 'removeFirstThat with one match' : '%s'. expected : '%s'", collectionRB408.toString().cStr(), equivAfterRemoveFirstThatMatchesOne.toString().cStr() );
    if ( removedCountRB408 != expectedRemovedCountRB408 || ! collectionRB408.equals ( equivAfterRemoveFirstThatMatchesOne ) ) {
        pTestLib->logError( "'CTC-00408-RB-removeFirstThatMatchesOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00408-RB-removeFirstThatMatchesOne-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesMore-CPP20 : CTC-00409-RB-removeFirstThatMatchesMore-CPP20 */
    auto       copyRB409            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB409 = copyRB409;
    auto       removedCountRB409    = collectionRB409.removeFirstThat ( matchingMore );
    auto const expectedRemovedCountRB409 = true;
    pTestLib->log ( "object after 'removeFirstThat with one or more matches' : '%s'. expected : '%s'", collectionRB409.toString().cStr(), equivAfterRemoveFirstThatMatchesMore.toString().cStr() );
    if ( removedCountRB409 != expectedRemovedCountRB409 || ! collectionRB409.equals ( equivAfterRemoveFirstThatMatchesMore ) ) {
        pTestLib->logError( "'CTC-00409-RB-removeFirstThatMatchesMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00409-RB-removeFirstThatMatchesMore-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeFirstThatMatchesAll-CPP20 : CTC-00410-RB-removeFirstThatMatchesAll-CPP20 */
    auto       copyRB410            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB410 = copyRB410;
    auto       removedCountRB410    = collectionRB410.removeFirstThat ( matchingAll );
    auto const expectedRemovedCountRB410 = true;
    pTestLib->log ( "object after 'removeFirstThat matches all' : '%s'. expected : '%s'", collectionRB410.toString().cStr(), equivAfterRemoveFirstThatMatchesAll.toString().cStr() );
    if ( removedCountRB410 != expectedRemovedCountRB410 || ! collectionRB410.equals ( equivAfterRemoveFirstThatMatchesAll ) ) {
        pTestLib->logError( "'CTC-00410-RB-removeFirstThatMatchesAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00410-RB-removeFirstThatMatchesAll-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeLastThatMatchesNone-CPP20 : CTC-00411-RB-removeLastThatMatchesNone-CPP20 */
    auto       copyRB411            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB411 = copyRB411;
    auto       removedCountRB411    = collectionRB411.removeLastThat ( matchingNone );
    auto const expectedRemovedCountRB411 = false;
    pTestLib->log ( "object after 'removeLastThat with no matches' : '%s'. expected : '%s'", collectionRB411.toString().cStr(), equivAfterRemoveLastThatMatchesNone.toString().cStr() );
    if ( removedCountRB411 != expectedRemovedCountRB411 || ! collectionRB411.equals ( equivAfterRemoveLastThatMatchesNone ) ) {
        pTestLib->logError( "'CTC-00411-RB-removeLastThatMatchesNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00411-RB-removeLastThatMatchesNone-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeLastThatMatchesOne-CPP20 : CTC-00412-RB-removeLastThatMatchesOne-CPP20 */
    auto       copyRB412            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB412 = copyRB412;
    auto       removedCountRB412    = collectionRB412.removeLastThat ( matchingOne );
    auto const expectedRemovedCountRB412 = true;
    pTestLib->log ( "object after 'removeLastThat with one match' : '%s'. expected : '%s'", collectionRB412.toString().cStr(), equivAfterRemoveLastThatMatchesOne.toString().cStr() );
    if ( removedCountRB412 != expectedRemovedCountRB412 || ! collectionRB412.equals ( equivAfterRemoveLastThatMatchesOne ) ) {
        pTestLib->logError( "'CTC-00412-RB-removeLastThatMatchesOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00412-RB-removeLastThatMatchesOne-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeLastThatMatchesMore-CPP20 : CTC-00413-RB-removeLastThatMatchesMore-CPP20 */
    auto       copyRB413            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB413 = copyRB413;
    auto       removedCountRB413    = collectionRB413.removeLastThat ( matchingMore );
    auto const expectedRemovedCountRB413 = true;
    pTestLib->log ( "object after 'removeLastThat with one or more matches' : '%s'. expected : '%s'", collectionRB413.toString().cStr(), equivAfterRemoveLastThatMatchesMore.toString().cStr() );
    if ( removedCountRB413 != expectedRemovedCountRB413 || ! collectionRB413.equals ( equivAfterRemoveLastThatMatchesMore ) ) {
        pTestLib->logError( "'CTC-00413-RB-removeLastThatMatchesMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00413-RB-removeLastThatMatchesMore-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeLastThatMatchesAll-CPP20 : CTC-00414-RB-removeLastThatMatchesAll-CPP20 */
    auto       copyRB414            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB414 = copyRB414;
    auto       removedCountRB414    = collectionRB414.removeLastThat ( matchingAll );
    auto const expectedRemovedCountRB414 = true;
    pTestLib->log ( "object after 'removeLastThat matching all' : '%s'. expected : '%s'", collectionRB414.toString().cStr(), equivAfterRemoveLastThatMatchesAll.toString().cStr() );
    if ( removedCountRB414 != expectedRemovedCountRB414 || ! collectionRB414.equals ( equivAfterRemoveLastThatMatchesAll ) ) {
        pTestLib->logError( "'CTC-00414-RB-removeLastThatMatchesAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00414-RB-removeLastThatMatchesAll-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeAllThatMatchesNone-CPP20 : CTC-00415-RB-removeAllThatMatchesNone-CPP20 */
    auto       copyRB415            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB415 = copyRB415;
    auto const expectedRemovedCountRB415 = collectionRB415.count ( matchingNone );
    auto       removedCountRB415    = collectionRB415.removeAllThat ( matchingNone );
    pTestLib->log ( "object after 'removeAllThat match none' : '%s'. expected : '%s'", collectionRB415.toString().cStr(), equivAfterRemoveAllThatMatchesNone.toString().cStr() );
    if ( removedCountRB415 != expectedRemovedCountRB415 || ! collectionRB415.equals ( equivAfterRemoveAllThatMatchesNone ) ) {
        pTestLib->logError( "'CTC-00415-RB-removeAllThatMatchesNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00415-RB-removeAllThatMatchesNone-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeAllThatMatchesOne-CPP20 : CTC-00416-RB-removeAllThatMatchesOne-CPP20 */
    auto       copyRB416            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB416 = copyRB416;
    auto const expectedRemovedCountRB416 = collectionRB416.count ( matchingOne );
    auto       removedCountRB416    = collectionRB416.removeAllThat ( matchingOne );
    pTestLib->log ( "object after 'removeAllThat matching one' : '%s'. expected : '%s'", collectionRB416.toString().cStr(), equivAfterRemoveAllThatMatchesOne.toString().cStr() );
    if ( removedCountRB416 != expectedRemovedCountRB416 || ! collectionRB416.equals ( equivAfterRemoveAllThatMatchesOne ) ) {
        pTestLib->logError( "'CTC-00416-RB-removeAllThatMatchesNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00416-RB-removeAllThatMatchesNone-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeAllThatMatchesMore-CPP20 : CTC-00417-RB-removeAllThatMatchesMore-CPP20 */
    auto       copyRB417            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB417 = copyRB417;
    auto const expectedRemovedCountRB417 = collectionRB417.count ( matchingMore );
    auto       removedCountRB417    = collectionRB417.removeAllThat ( matchingMore );
    pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB417.toString().cStr(), equivAfterRemoveAllThatMatchesMore.toString().cStr() );
    if ( removedCountRB417 != expectedRemovedCountRB417 || ! collectionRB417.equals ( equivAfterRemoveAllThatMatchesMore ) ) {
        pTestLib->logError( "'CTC-00417-RB-removeAllThatMatchesMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00417-RB-removeAllThatMatchesMore-CPP20' OK" );
    }

    /* CollectionTestCase-RemoveBy-removeAllThatMatchesAll-CPP20 : CTC-00418-RB-removeAllThatMatchesAll-CPP20 */
    auto       copyRB418            = original;
    cds :: experimental :: Collection < __MemberType > & collectionRB418 = copyRB418;
    auto const expectedRemovedCountRB418 = collectionRB418.count ( matchingAll );
    auto       removedCountRB418    = collectionRB418.removeAllThat ( matchingAll );
    pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB418.toString().cStr(), equivAfterRemoveAllThatMatchesAll.toString().cStr() );
    if ( removedCountRB418 != expectedRemovedCountRB418 || ! collectionRB418.equals ( equivAfterRemoveAllThatMatchesAll ) ) {
        pTestLib->logError( "'CTC-00418-RB-removeAllThatMatchesAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00418-RB-removeAllThatMatchesAll-CPP20' OK" );
    }

    return true;
}

/* CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20. Tests CTC-00003 to CTC-00016 */
template <
        typename __MemberType /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupMemberFunctions (
        cds :: experimental :: Collection < __MemberType >        & collection,
        Test                                                      * pTestLib,
        String                                              const & expectedToString,
        Size                                                        expectedSize,
        __MemberType                                        const & toBeFound,
        __MemberType                                        const & toNotBeFound,
        Size                                                        expectedHash,
        cds :: Object                                       const & equalSameType,
        cds :: Object                                       const & equalDifferentType,
        cds :: Object                                       const & notEqualSameType,
        cds :: Object                                       const & notEqualDifferentType,
        cds :: Object                                       const & notEqualNonCollection
) -> bool {

    pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );


    /* CollectionTestCase-MemberFunctions-toString-CPP20 : CTC-00003-MF-toString-CPP20 */
    auto asString = collection.toString();
    pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
    if ( asString != expectedToString ) {
        pTestLib->logError ( "'CTC-00003-MF-toString-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00003-MF-toString-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-size-CPP20 : CTC-00004-MF-size-CPP20 */
    auto size = collection.size();
    pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, expectedSize );
    if ( size != expectedSize ) {
        pTestLib->logError( "'CTC-00004-MF-size-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00004-MF-size-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-empty-CPP20 : CTC-00005-MF-empty-CPP20 */
    auto empty = collection.empty();
    pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( empty != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CTC-00005-MF-empty-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00005-MF-empty-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-boolCast-CPP20 : CTC-00006-MF-boolCast-CPP20 */
    auto boolCast = static_cast < bool > ( collection.empty() );
    pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( boolCast != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CTC-00006-MF-boolCast-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00006-MF-boolCast-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-containsTrue-CPP20 : CTC-00007-MF-containsTrue-CPP20 */
    auto containsTrue = collection.contains ( toBeFound );
    pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "true" );
    if ( ! containsTrue ) {
        pTestLib->logError( "'CTC-00007-MF-containsTrue-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00007-MF-containsTrue-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-containsFalse-CPP20 : CTC-00008-MF-containsFalse-CPP20 */
    auto containsFalse = collection.contains ( toNotBeFound );
    pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
    if ( containsFalse ) {
        pTestLib->logError( "'CTC-00008-MF-containsFalse-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00008-MF-containsFalse-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-hash-CPP20 : CTC-00009-MF-hash-CPP20 */
    auto hash = collection.hash();
    pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, expectedHash );
    if ( hash != expectedHash ) {
        pTestLib->logError( "'CTC-00009-MF-hash-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00009-MF-hash-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsSelf-CPP20 : CTC-00011-MF-equalsSelf-CPP20 */
    auto equalsToSelf = collection.equals ( collection );
    pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
    if ( ! equalsToSelf ) {
        pTestLib->logError( "'CTC-00011-MF-equalsSelf-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00011-MF-equalsSelf-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsTrueSameType-CPP20 : CTC-00012-MF-equalsTrueSameType-CPP20 */
    auto equalsToEqualSameType = collection.equals ( equalSameType );
    pTestLib->log ( "object 'equals to equal, same type' : '%s', expected 'equals to equal, same type' : '%s'", equalsToEqualSameType ? "true" : "false", "true" );
    if ( ! equalsToEqualSameType ) {
        pTestLib->logError( "'CTC-00012-MF-equalsTrueSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00012-MF-equalsTrueSameType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsTrueDifferentType-CPP20 : CTC-00013-MF-equalsTrueDifferentType-CPP20 */
    auto equalsToEqualDiffType = collection.equals ( equalDifferentType );
    pTestLib->log ( "object 'equals to equal, different type' : '%s', expected 'equals to equal, different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "true" );
    if ( ! equalsToEqualDiffType ) {
        pTestLib->logError( "'CTC-00013-MF-equalsTrueDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00013-MF-equalsTrueDifferentType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsFalseSameType-CPP20 : CTC-00014-MF-equalsFalseSameType-CPP20 */
    auto notEqualsToSameType = collection.equals ( notEqualSameType );
    pTestLib->log ( "object 'equals to not equal, same type' : '%s', expected 'equals to not equal, same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
    if ( notEqualsToSameType ) {
        pTestLib->logError( "'CTC-00014-MF-equalsFalseSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00014-MF-equalsFalseSameType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsFalseDifferentType-CPP20 : CTC-00015-MF-equalsFalseDifferentType-CPP20 */
    auto notEqualsToDifferentType = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, different type' : '%s', expected 'equals to not equal, different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
    if ( notEqualsToDifferentType ) {
        pTestLib->logError( "'CTC-00015-MF-equalsFalseDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00015-MF-equalsFalseDifferentType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsFalseNotCollection-CPP20 : CTC-00016-MF-equalsFalseNotCollection-CPP20 */
    auto notEqualsToOtherObject = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, not collection' : '%s', expected 'equals to not equal, not collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );
    if ( notEqualsToOtherObject ) {
        pTestLib->logError( "'CTC-00016-MF-equalsFalseNotCollection-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00016-MF-equalsFalseNotCollection-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-clear-CPP20 : CTC-00010-MF-clear-CPP20 */
    collection.clear();

    empty                       = collection.empty();
    boolCast                    = static_cast < bool > ( collection.empty() );
    size                        = collection.size();
    hash                        = collection.hash();
    containsTrue                = collection.contains( toBeFound );
    containsFalse               = collection.contains( toNotBeFound );
    asString                    = collection.toString();
    equalsToSelf                = collection.equals ( collection );
    equalsToEqualSameType       = collection.equals ( equalSameType );
    equalsToEqualDiffType       = collection.equals ( equalDifferentType );
    notEqualsToSameType         = collection.equals ( notEqualSameType );
    notEqualsToDifferentType    = collection.equals ( notEqualDifferentType );
    notEqualsToOtherObject      = collection.equals ( notEqualNonCollection );

    pTestLib->log ( "Object Cleared using 'clear'. Re-execution after clear : " );
    pTestLib->log ( "object 'toString' : '%s'. potential expected 'toString' : '%s'", asString.cStr(), "[]" );
    pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, 0ULL );
    pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", "true" );
    pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", "true" );
    pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "false" );
    pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
    pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, 0ULL );
    pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
    pTestLib->log ( "object 'equals to equal same type' : '%s', expected 'equals to equal same type' : '%s'", equalsToEqualSameType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to equal different type' : '%s', expected 'equals to equal different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to not equal same type' : '%s', expected 'equals to not equal same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to not equal different type' : '%s', expected 'equals to not equal different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to non-collection' : '%s', expected 'equals to non-collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );

    if ( asString.length() > 2ULL ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - toString' failed" );
        return false;
    } else if ( size != 0ULL ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - size' failed" );
        return false;
    } else if ( ! empty ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - empty' failed" );
        return false;
    } else if ( ! boolCast ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - bool cast' failed" );
        return false;
    } else if ( containsTrue || containsFalse ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - contains' failed" );
        return false;
    } else if ( hash != 0ULL ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - hash' failed" );
        return false;
    } else if ( ! equalsToSelf ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToSelf' failed" );
        return false;
    } else if ( equalsToEqualSameType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToEqualSameTypePrevToClear' failed" );
        return false;
    } else if ( equalsToEqualDiffType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToEqualDiffTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToSameType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToNotEqualSameTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToDifferentType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToNotEqualDiffTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToOtherObject ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToNotEqualOtherObj' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00010-MF-clear-CPP20' OK" );
    }


    return true;
}

template <
        typename __T,       /* NOLINT(bugprone-reserved-identifier) */
        typename __ItType,  /* NOLINT(bugprone-reserved-identifier) */
        typename __LastArg  /* NOLINT(bugprone-reserved-identifier) */
> auto fwdCheckIterator (
        __ItType const & cur,
        __ItType const & end,
        __LastArg const & lastE
) {

    if ( cur == end ) {
        return false;
    }

    if ( ! cds :: meta :: equals ( __T ( lastE ), * cur ) ) {
        return false;
    }

    auto next = cur;
    return ++ next == end;
}

template <
        typename __T,                   /* NOLINT(bugprone-reserved-identifier) */
        typename __ItType,              /* NOLINT(bugprone-reserved-identifier) */
        typename __CurrArg,             /* NOLINT(bugprone-reserved-identifier) */
        typename ... __RemainingArgs    /* NOLINT(bugprone-reserved-identifier) */
> auto fwdCheckIterator (
        __ItType const & cur,
        __ItType const & end,
        __CurrArg const & currE,
        __RemainingArgs const & ... remE
) noexcept -> bool {

    if ( cur == end ) {
        return false;
    }

    if ( ! cds :: meta :: equals ( __T ( currE ), * cur ) ) {
        return false;
    }

    auto next = cur;
    return fwdCheckIterator < __T > ( ++ next, end, remE ... );
}

/* CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20. Tests CTC-00051 to CTC-00056 */
template <
        typename __MemberType,                              /* NOLINT(bugprone-reserved-identifier) */
        typename ... __OrderedValues                        /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupDelegateForwardConstIterableClientImports (
        experimental :: Collection < __MemberType > & collection,
        Test                  *     pTestLib,
        __OrderedValues const & ... orderedValues
) -> bool {

    pTestLib->log ( "Object under test, to be iterated : '%s'", collection.toString().cStr() );

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-range-CPP20 : CTC-00051-IT-range-CPP20 */
    pTestLib->log ( "Standard iteration : " );
    for ( auto const & e : collection ) {
        std :: stringstream oss;
        cds :: streamPrint ( oss, e );
        pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
    }

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-begin_endIteration-CPP20 : CTC-00052-IT-begin_end-CPP20 */
    auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
    if ( ! stdIterResult ) {
        pTestLib->logError( "'CTC-00052-IT-begin_end-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00052-IT-begin_end-CPP20' OK" );
    }

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-cbegin_cendIteration-CPP20 : CTC-00053-IT-cbegin_cend-CPP20 */
    auto stdCIterResult = fwdCheckIterator < __MemberType > ( collection.cbegin(), collection.cend(), orderedValues ... );
    if ( ! stdCIterResult ) {
        pTestLib->logError( "'CTC-00053-IT-cbegin_cend-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00053-IT-cbegin_cend-CPP20' OK" );
    }

    collection.clear();

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptybegin_end-CPP20 : CTC-00054-IT-e_begin_end-CPP20 */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'CTC-00054-IT-e_begin_end-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00054-IT-e_begin_end-CPP20' OK" );

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptycbegin_cend-CPP20 : CTC-00055-IT-e_cbegin_cend-CPP20 */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'CTC-00055-IT-e_cbegin_cend-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00055-IT-e_cbegin_cend-CPP20' OK" );

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-e_emptyRange-CPP20 : CTC-00056-IT-e_emptyRange-CPP20 */
    for ( auto const & e : collection ) {
        pTestLib->logError( "'CTC-00056-IT-e_emptyRange-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00056-IT-e_emptyRange-CPP20' OK" );

    return true;
}

template <
        typename __PredicateReturnType, /* NOLINT(bugprone-reserved-identifier) */
        typename __MemberType,          /* NOLINT(bugprone-reserved-identifier) */
        typename __Predicate            /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestCasePredicateHandle (
        StringLiteral testCaseName,
        experimental :: Collection < __MemberType > const & collection,
        Test                                              * pTestLib,
        auto ( experimental :: Collection < __MemberType > :: * pFunctionalCall ) ( __Predicate const & ) const -> __PredicateReturnType,
        __Predicate const & predicate,
        __PredicateReturnType                       const & expectedReturn
) -> bool {

    auto returned = (collection.*pFunctionalCall) ( predicate );
    if ( returned != expectedReturn ) {
        pTestLib->logError( "'%s' failed", testCaseName);
        return false;
    }

    pTestLib->logOK ( "'%s' OK", testCaseName );
    return true;
}

template <
        typename __PredicateReturnType, /* NOLINT(bugprone-reserved-identifier) */
        typename __MemberType,          /* NOLINT(bugprone-reserved-identifier) */
        typename __Predicate            /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestCasePredicateCountedHandle (
        StringLiteral testCaseName,
        experimental :: Collection < __MemberType > const & collection,
        Test                                              * pTestLib,
        auto ( experimental :: Collection < __MemberType > :: * pFunctionalCall ) ( Size, __Predicate const & ) const -> __PredicateReturnType,
        __Predicate const & predicate,
        Size desiredCount,
        __PredicateReturnType                       const & expectedReturn
) -> bool {

    auto returned = (collection.*pFunctionalCall) ( desiredCount, predicate );
    if ( returned != expectedReturn ) {
        pTestLib->logError( "'%s' failed", testCaseName);
        return false;
    }

    pTestLib->logOK ( "'%s' OK", testCaseName );
    return true;
}

template <
        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __EqualsFunction       /* NOLINT(bugprone-reserved-identifier) */
> auto composePredicate (
        __OtherIterableType const & other,
        __EqualsFunction    const & equals,
        bool                        onEquals
) {

    return [& other, & equals, onEquals]( __ElementType const & e ) {
        for ( __ElementType const & otherE : other ) {
            if ( equals ( e, otherE ) ) {
                return onEquals;
            }
        }

        return ! onEquals;
    };
}

template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
        typename __PredicateType        /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestCaseContainsWithEquivalent (
        StringLiteral                                           caseName,
        experimental :: Collection < __ElementType >    const & collection,
        Test                                                  * pTestLib,
        __OtherIterableType                             const & other,
        bool ( experimental :: Collection < __ElementType > :: * collectionOperation ) ( __OtherIterableType const & ) const,
        bool ( experimental :: Collection < __ElementType > :: * equivalentWithEquals ) ( __PredicateType const & ) const,
        __PredicateType                                 const & predicate
) -> bool {

    auto status         = ( collection.*collectionOperation ) ( other );
    auto expectedStatus = ( collection.*equivalentWithEquals ) ( predicate );

    if ( status != expectedStatus ) {
        pTestLib->logError( "'%s' failed", caseName );
        return false;
    }

    pTestLib->logOK ( "'%s' OK", caseName );
    return true;
}

/* CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20. Tests CTC-00301-CO to CTC-30320-CO [-Collection/-InitializerList Groups] */
template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupContainsGroupByEquivalent (
        StringLiteral                                        groupName,
        experimental :: Collection < __ElementType > const & collection,
        Test                                               * pTestLib,
        __OtherIterableType                          const & noneCommon,
        __OtherIterableType                          const & oneCommon,
        __OtherIterableType                          const & moreCommon,
        __OtherIterableType                          const & allCommon,
        __OtherIterableType                          const & allCommonAndMore
) -> bool {

    bool status = true;

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionNoneCommon-CPP20 : CTC-00301-CO-containsAnyOfCollectionNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00301-CO-containsAnyOfCollectionNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionOneCommon-CPP20 : CTC-00302-CO-containsAnyOfCollectionOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00302-CO-containsAnyOfCollectionOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionMoreCommon-CPP20 : CTC-00303-CO-containsAnyOfCollectionMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00303-CO-containsAnyOfCollectionMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionAllCommon-CPP20 : CTC-00304-CO-containsAnyOfCollectionAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00304-CO-containsAnyOfCollectionAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionAllCommonAndMore-CPP20 : CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommonAndMore,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommonAndMore,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionNoneCommon-CPP20 : CTC-00306-CO-containsAllOfCollectionNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00306-CO-containsAllOfCollectionNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionOneCommon-CPP20 : CTC-00307-CO-containsAllOfCollectionOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00307-CO-containsAllOfCollectionOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionMoreCommon-CPP20 : CTC-00308-CO-containsAllOfCollectionMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00308-CO-containsAllOfCollectionMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionAllCommon-CPP20 : CTC-00309-CO-containsAllOfCollectionAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00309-CO-containsAllOfCollectionAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionAllCommonAndMore-CPP20 : CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-CPP20. */
    auto containsAllOfCollectionAllCommonAndMoreStatus          = collection.containsAllOf ( allCommonAndMore );
    auto containsAllOfCollectionAllCommonAndMoreExpectedStatus  = false;
    if ( containsAllOfCollectionAllCommonAndMoreStatus != containsAllOfCollectionAllCommonAndMoreExpectedStatus ) {
        pTestLib->logError ( "'%s' failed", ( String ("CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-") + groupName + "-CPP20" ).cStr() );
        return false;
    }

    pTestLib->logOK ( "'%s' OK", ( String ("CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-") + groupName + "-CPP20" ).cStr() );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfNoneCommon-CPP20 : CTC-00311-CO-containsAnyNotOfNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00311-CO-containsAnyNotOfNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfOneCommon-CPP20 : CTC-00312-CO-containsAnyNotOfOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00312-CO-containsAnyNotOfOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfMoreCommon-CPP20 : CTC-00313-CO-containsAnyNotOfMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00313-CO-containsAnyNotOfMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfAllCommon-CPP20 : CTC-00314-CO-containsAnyNotOfAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00314-CO-containsAnyNotOfAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfAllCommonAndMore-CPP20 : CTC-00315-CO-containsAnyNotOfAllCommonAndMore-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00315-CO-containsAnyNotOfAllCommonAndMore-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommonAndMore,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommonAndMore,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfNoneCommon-CPP20 : CTC-00316-CO-containsNoneOfNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00316-CO-containsNoneOfNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfOneCommon-CPP20 : CTC-00317-CO-containsNoneOfOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00317-CO-containsNoneOfOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfMoreCommon-CPP20 : CTC-00318-CO-containsNoneOfMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00318-CO-containsNoneOfMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfAllCommon-CPP20 : CTC-00319-CO-containsNoneOfAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00319-CO-containsNoneOfAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfAllCommonAndMore-CPP20 : CTC-00320-CO-containsNoneOfAllCommonAndMore-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00320-CO-containsNoneOfAllCommonAndMore-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommonAndMore,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommonAndMore,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    return status;
}

template < typename T, typename = void > struct _HasToString : meta :: FalseType {};    /* NOLINT(bugprone-reserved-identifier) */
template < typename T > struct _HasToString < T, meta :: Void < decltype ( meta :: addressOf < T > ()->toString () ) > > : meta :: TrueType {}; /* NOLINT(bugprone-reserved-identifier) */

template < typename T, typename = void > struct _HasEquals : meta :: FalseType {};  /* NOLINT(bugprone-reserved-identifier) */
template < typename T > struct _HasEquals < T, meta :: Void < decltype ( meta :: addressOf < T > ()->equals ( meta :: referenceOf < Object const > () ) ) > > : meta :: TrueType {};    /* NOLINT(bugprone-reserved-identifier) */

template <
        typename T,
        meta :: EnableIf < _HasToString < T > :: value > = 0
> auto toString (T const & v) -> String {

    return v.toString ();
}

template <
        typename T,
        meta :: EnableIf < ! _HasToString < T > :: value > = 0
> auto toString (T const & v) -> String {

    if ( v.size() == 0ULL ) {
        return "[]";
    }

    String s = "[ ";
    for ( auto & e : v ) {
        s += e;
        s += ", ";
    }

    return s.removeSuffix (", ") + " ]";
}

template <
        typename T,
        typename V,
        meta :: EnableIf < _HasEquals < T > :: value && _HasEquals < V > :: value > = 0
> auto equals (T const & t, V const & v) -> bool {

    return t.equals (v);
}

template <
        typename T,
        typename V,
        meta :: EnableIf < ! _HasEquals < T > :: value || ! _HasEquals < V > :: value > = 0
> auto equals (T const & t, V const & v) -> bool {

    auto lIt = t.begin();
    auto le = t.end();
    auto rIt = v.begin();
    auto re = v.end();
    for (
         ;   lIt != le && rIt != re; ++ lIt, ++ rIt
    )
        if ( ! meta :: equals ( * lIt, * rIt ) )
            return false;

    return true;
}

/* CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20. CTC-00481-RO to CTC-00490-RO. */
template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupItemRemoveAllOf (
        Test                      * pTestLib,
        cds :: String       const & groupVariant,
        StringLiteral               subvariant,
        Size                        subvariantOffset,
        __IterableType      const & iterableUnderTest,
        Size ( cds :: experimental :: Collection < __ElementType > :: * removeAllPfnVariant ) ( __OtherIterableType const & ),
        __OtherIterableType const & noneCommon,
        __OtherIterableType const & oneCommon,
        __OtherIterableType const & moreCommon,
        __OtherIterableType const & allCommon,
        __OtherIterableType const & allAndMoreCommon,
        Size                        expectedResultFromNone,
        __OtherIterableType const & expectedCollectionFromNone,
        Size                        expectedResultFromOne,
        __OtherIterableType const & expectedCollectionFromOne,
        Size                        expectedResultFromMore,
        __OtherIterableType const & expectedCollectionFromMore,
        Size                        expectedResultFromAll,
        __OtherIterableType const & expectedCollectionFromAll,
        Size                        expectedResultFromAllAndMore,
        __OtherIterableType const & expectedCollectionFromAllAndMore
) {

    pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

    /* CollectionTestCase-RemoveOf-removeAllOfNoneCommon-CPP20 : CTC-00481-RO-removeAllOfNoneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeAllNotOfNoneCommon-CPP20 : CTC-00486-RO-removeAllNotOfNoneCommon-CPP20 */
    auto       copyRO481            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO481 = copyRO481;
    auto       removedCountRB481    = ( collectionRO481.* removeAllPfnVariant ) ( noneCommon );
    pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO481.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
    if ( removedCountRB481 != expectedResultFromNone || ! equals ( collectionRO481, expectedCollectionFromNone ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sNoneCommon-%s-CPP20' failed", 481 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sNoneCommon-%s-CPP20' OK", 481 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeAllOfOneCommon-CPP20 : CTC-00482-RO-removeAllOfOneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeAllNotOfOneCommon-CPP20 : CTC-00487-RO-removeAllNotOfOneCommon-CPP20 */
    auto       copyRO482            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO482 = copyRO482;
    auto       removedCountRB482    = ( collectionRO482.* removeAllPfnVariant ) ( oneCommon );
    pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO482.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
    if ( removedCountRB482 != expectedResultFromOne || ! equals ( collectionRO482, expectedCollectionFromOne ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sOneCommon-%s-CPP20' failed", 482 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sOneCommon-%s-CPP20' OK", 482 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeAllOfMoreCommon-CPP20 : CTC-00483-RO-removeAllOfMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeAllNotOfMoreCommon-CPP20 : CTC-00488-RO-removeAllNotOfMoreCommon-CPP20 */
    auto       copyRO483            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO483 = copyRO483;
    auto       removedCountRB483    = ( collectionRO483.* removeAllPfnVariant ) ( moreCommon );
    pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO483.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
    if ( removedCountRB483 != expectedResultFromMore || ! equals ( collectionRO483, expectedCollectionFromMore ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sMoreCommon-%s-CPP20' failed", 483 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sMoreCommon-%s-CPP20' OK", 483 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeAllOfAllCommon-CPP20 : CTC-00484-RO-removeAllOfAllCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeAllNotOfAllCommon-CPP20 : CTC-00489-RO-removeAllNotOfAllCommon-CPP20 */
    auto       copyRO484            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO484 = copyRO484;
    auto       removedCountRB484    = ( collectionRO484.* removeAllPfnVariant ) ( allCommon );
    pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO484.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
    if ( removedCountRB484 != expectedResultFromAll || ! equals ( collectionRO484, expectedCollectionFromAll ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sAllCommon-%s-CPP20' failed", 484 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sAllCommon-%s-CPP20' OK", 484 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeAllOfAllAndMoreCommon-CPP20 : CTC-00485-RO-removeAllOfAllAndMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeAllNotOfAllAndMoreCommon-CPP20 : CTC-00490-RO-removeAllNotOfAllAndMoreCommon-CPP20 */
    auto       copyRO485            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO485 = copyRO485;
    auto       removedCountRB485    = ( collectionRO485.* removeAllPfnVariant ) ( allAndMoreCommon );
    pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO485.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
    if ( removedCountRB485 != expectedResultFromAllAndMore || ! equals ( collectionRO485, expectedCollectionFromAllAndMore ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-CPP20' failed", 485 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-CPP20' OK", 485 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    return true;
}

/* CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20. CTC-00501-RO to CTC-00520-RO. */
template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupItemRemoveFirstLastOf (
        Test                      * pTestLib,
        cds :: String       const & groupVariant,
        StringLiteral               subvariant,
        Size                        subvariantOffset,
        __IterableType      const & iterableUnderTest,
        bool ( cds :: experimental :: Collection < __ElementType > :: * removeFirstLastPfnVariant ) ( __OtherIterableType const & ),
        __OtherIterableType const & noneCommon,
        __OtherIterableType const & oneCommon,
        __OtherIterableType const & moreCommon,
        __OtherIterableType const & allCommon,
        __OtherIterableType const & allAndMoreCommon,
        bool                        expectedResultFromNone,
        __OtherIterableType const & expectedCollectionFromNone,
        bool                        expectedResultFromOne,
        __OtherIterableType const & expectedCollectionFromOne,
        bool                        expectedResultFromMore,
        __OtherIterableType const & expectedCollectionFromMore,
        bool                        expectedResultFromAll,
        __OtherIterableType const & expectedCollectionFromAll,
        bool                        expectedResultFromAllAndMore,
        __OtherIterableType const & expectedCollectionFromAllAndMore
) {

    pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

    /* CollectionTestCase-RemoveOf-removeFirstOfNoneCommon-CPP20 : CTC-00501-RO-removeFirstOfNoneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastOfNoneCommon-CPP20 : CTC-00506-RO-removeLastOfNoneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeFirstNotOfNoneCommon-CPP20 : CTC-00511-RO-removeFirstNotOfNoneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastNotOfNoneCommon-CPP20 : CTC-00516-RO-removeLastNotOfNoneCommon-CPP20 */
    auto       copyRO501            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO501 = copyRO501;
    auto       removedCountRB501    = ( collectionRO501.* removeFirstLastPfnVariant ) ( noneCommon );
    pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO501.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
    if ( removedCountRB501 != expectedResultFromNone || ! equals ( collectionRO501, expectedCollectionFromNone ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sNoneCommon-%s-CPP20' failed", 501 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sNoneCommon-%s-CPP20' OK", 501 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeFirstOfOneCommon-CPP20 : CTC-00502-RO-removeFirstOfOneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastOfOneCommon-CPP20 : CTC-00507-RO-removeLastOfOneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeFirstNotOfOneCommon-CPP20 : CTC-00512-RO-removeFirstNotOfOneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastNotOfOneCommon-CPP20 : CTC-00517-RO-removeLastNotOfOneCommon-CPP20 */
    auto       copyRO502            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO502 = copyRO502;
    auto       removedCountRB502    = ( collectionRO502.* removeFirstLastPfnVariant ) ( oneCommon );
    pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO502.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
    if ( removedCountRB502 != expectedResultFromOne || ! equals ( collectionRO502, expectedCollectionFromOne ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sOneCommon-%s-CPP20' failed", 502 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sOneCommon-%s-CPP20' OK", 502 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeFirstOfMoreCommon-CPP20 : CTC-00503-RO-removeFirstOfMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastOfMoreCommon-CPP20 : CTC-00508-RO-removeLastOfMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeFirstNotOfMoreCommon-CPP20 : CTC-00513-RO-removeFirstNotOfMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastNotOfMoreCommon-CPP20 : CTC-00518-RO-removeLastNotOfMoreCommon-CPP20 */
    auto       copyRO503            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO503 = copyRO503;
    auto       removedCountRB503    = ( collectionRO503.* removeFirstLastPfnVariant ) ( moreCommon );
    pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO503.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
    if ( removedCountRB503 != expectedResultFromMore || ! equals ( collectionRO503, expectedCollectionFromMore ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sMoreCommon-%s-CPP20' failed", 503 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sMoreCommon-%s-CPP20' OK", 503 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeFirstOfAllCommon-CPP20 : CTC-00504-RO-removeFirstOfAllCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastOfAllCommon-CPP20 : CTC-00509-RO-removeLastOfAllCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeFirstNotOfAllCommon-CPP20 : CTC-00514-RO-removeFirstNotOfAllCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastNotOfAllCommon-CPP20 : CTC-00519-RO-removeLastNotOfAllCommon-CPP20 */
    auto       copyRO504            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO504 = copyRO504;
    auto       removedCountRB504    = ( collectionRO504.* removeFirstLastPfnVariant ) ( allCommon );
    pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO504.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
    if ( removedCountRB504 != expectedResultFromAll || ! equals ( collectionRO504, expectedCollectionFromAll ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sAllCommon-%s-CPP20' failed", 504 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sAllCommon-%s-CPP20' OK", 504 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeFirstOfAllAndMoreCommon-CPP20 : CTC-00505-RO-removeFirstOfAllAndMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastOfAllAndMoreCommon-CPP20 : CTC-00510-RO-removeLastOfAllAndMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeFirstNotOfAllAndMoreCommon-CPP20 : CTC-00515-RO-removeFirstNotOfAllAndMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeLastNotOfAllAndMoreCommon-CPP20 : CTC-00520-RO-removeLastNotOfAllAndMoreCommon-CPP20 */
    auto       copyRO505            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO505 = copyRO505;
    auto       removedCountRB505    = ( collectionRO505.* removeFirstLastPfnVariant ) ( allAndMoreCommon );
    pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO505.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
    if ( removedCountRB505 != expectedResultFromAllAndMore || ! equals ( collectionRO505, expectedCollectionFromAllAndMore ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-CPP20' failed", 505 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-CPP20' OK", 505 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    return true;
}

/* CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20. CTC-00451-RO to CTC-00464-RO */
template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupItemRemoveOf (
        Test                      * pTestLib,
        cds :: String       const & groupVariant,
        StringLiteral               subvariant,
        Size                        subvariantOffset,
        __IterableType      const & iterableUnderTest,
        Size ( cds :: experimental :: Collection < __ElementType > :: * removePfnVariant ) ( Size, __OtherIterableType const & ),
        Size                        limit,
        __OtherIterableType const & noneCommon,
        __OtherIterableType const & oneCommon,
        __OtherIterableType const & moreLessThanLimitCommon,
        __OtherIterableType const & moreCommon,
        __OtherIterableType const & moreMoreThanLimitCommon,
        __OtherIterableType const & allCommon,
        __OtherIterableType const & allAndMoreCommon,
        Size                        expectedResultFromNone,
        __OtherIterableType const & expectedCollectionFromNone,
        Size                        expectedResultFromOne,
        __OtherIterableType const & expectedCollectionFromOne,
        Size                        expectedResultFromMoreLessThanLimit,
        __OtherIterableType const & expectedCollectionFromMoreLessThanLimit,
        Size                        expectedResultFromMore,
        __OtherIterableType const & expectedCollectionFromMore,
        Size                        expectedResultFromMoreMoreThanLimit,
        __OtherIterableType const & expectedCollectionFromMoreMoreThanLimit,
        Size                        expectedResultFromAll,
        __OtherIterableType const & expectedCollectionFromAll,
        Size                        expectedResultFromAllAndMore,
        __OtherIterableType const & expectedCollectionFromAllAndMore
) {

    pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

    /* CollectionTestCase-RemoveOf-removeOfNoneCommon-CPP20 : CTC-00451-RO-removeOfNoneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeNotOfNoneCommon-CPP20 : CTC-00458-RO-removeNotOfNoneCommon-CPP20 */
    auto       copyRO451            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO451 = copyRO451;
    auto       removedCountRB451    = ( collectionRO451.* removePfnVariant ) ( limit, noneCommon );
    pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO451.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
    if ( removedCountRB451 != expectedResultFromNone || ! equals ( collectionRO451, expectedCollectionFromNone ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sNoneCommon-%s-CPP20' failed", 451 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sNoneCommon-%s-CPP20' OK", 451 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeOfOneCommon-CPP20 : CTC-00452-RO-removeOfOneCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeNotOfOneCommon-CPP20 : CTC-00459-RO-removeNotOfOneCommon-CPP20 */
    auto       copyRO452            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO452 = copyRO452;
    auto       removedCountRB452    = ( collectionRO452.* removePfnVariant ) ( limit, oneCommon );
    pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO452.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
    if ( removedCountRB452 != expectedResultFromOne || ! equals ( collectionRO452, expectedCollectionFromOne ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sOneCommon-%s-CPP20' failed", 452 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sOneCommon-%s-CPP20' OK", 452 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeOfMoreLessThanLimitCommon-CPP20 : CTC-00453-RO-removeOfMoreLessThanLimitCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeNotOfMoreLessThanLimitCommon-CPP20 : CTC-00460-RO-removeOfMoreLessThanLimitCommon-CPP20 */
    auto       copyRO453            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO453 = copyRO453;
    auto       removedCountRB453    = ( collectionRO453.* removePfnVariant ) ( limit, moreLessThanLimitCommon );
    pTestLib->log ( "object after '%s with more less than limit common' : '%s'. expected : '%s'", subvariant, collectionRO453.toString().cStr(), toString ( expectedCollectionFromMoreLessThanLimit ).cStr() );
    if ( removedCountRB453 != expectedResultFromMoreLessThanLimit || ! equals ( collectionRO453, expectedCollectionFromMoreLessThanLimit ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sMoreLessThanLimitCommon-%s-CPP20' failed", 453 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sMoreLessThanLimitCommon-%s-CPP20' OK", 453 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeOfMoreCommon-CPP20 : CTC-00454-RO-removeOfMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeNotOfMoreCommon-CPP20 : CTC-00461-RO-removeNotOfMoreCommon-CPP20 */
    auto       copyRO454            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO454 = copyRO454;
    auto       removedCountRB454    = ( collectionRO454.* removePfnVariant ) ( limit, moreCommon );
    pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO454.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
    if ( removedCountRB454 != expectedResultFromMore || ! equals ( collectionRO454, expectedCollectionFromMore ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sMoreCommon-%s-CPP20' failed", 454 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sMoreCommon-%s-CPP20' OK", 454 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeOfMoreMoreThanLimitCommon-CPP20 : CTC-00455-RO-removeOfMoreMoreThanLimitCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeNotOfMoreMoreThanLimitCommon-CPP20 : CTC-00462-RO-removeNotOfMoreMoreThanLimitCommon-CPP20 */
    auto       copyRO455            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO455 = copyRO455;
    auto       removedCountRB455    = ( collectionRO455.* removePfnVariant ) ( limit, moreMoreThanLimitCommon );
    pTestLib->log ( "object after '%s with more than limit common' : '%s'. expected : '%s'", subvariant, collectionRO455.toString().cStr(), toString ( expectedCollectionFromMoreMoreThanLimit ).cStr() );
    if ( removedCountRB455 != expectedResultFromMoreMoreThanLimit || ! equals ( collectionRO455, expectedCollectionFromMoreMoreThanLimit ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-CPP20' failed", 455 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-CPP20' OK", 455 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeOfAllCommon-CPP20 : CTC-00456-RO-removeOfAllCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeNotOfAllCommon-CPP20 : CTC-00463-RO-removeNotOfAllCommon-CPP20 */
    auto       copyRO456            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO456 = copyRO456;
    auto       removedCountRB456    = ( collectionRO456.* removePfnVariant ) ( limit, allCommon );
    pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO456.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
    if ( removedCountRB456 != expectedResultFromAll || ! equals ( collectionRO456, expectedCollectionFromAll ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sAllCommon-%s-CPP20' failed", 456 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sAllCommon-%s-CPP20' OK", 456 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* CollectionTestCase-RemoveOf-removeOfAllAndMoreCommon-CPP20 : CTC-00457-RO-removeOfAllAndMoreCommon-CPP20 */
    /* CollectionTestCase-RemoveOf-removeNotOfAllAndMoreCommon-CPP20 : CTC-00464-RO-removeNotOfAllAndMoreCommon-CPP20 */
    auto       copyRO457            = iterableUnderTest;
    cds :: experimental :: Collection < __ElementType > & collectionRO457 = copyRO457;
    auto       removedCountRB457    = ( collectionRO457.* removePfnVariant ) ( limit, allAndMoreCommon );
    pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO457.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
    if ( removedCountRB457 != expectedResultFromAllAndMore || ! equals ( collectionRO457, expectedCollectionFromAllAndMore ) ) {
        pTestLib->logError( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-CPP20' failed", 457 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-CPP20' OK", 457 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    return true;
}

template <
        typename __ElementType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        template < typename ... > class __CollectionType,                                                       /* NOLINT(bugprone-reserved-identifier) */
        typename __ValidatorPredicate,                                                                          /* NOLINT(bugprone-reserved-identifier) */
        typename __IteratorType = typename cds :: experimental :: Collection < __ElementType > :: ConstIterator /* NOLINT(bugprone-reserved-identifier) */
> auto iteratorListEqualityCheck (
        __ValidatorPredicate                const & validator,
        __CollectionType < __IteratorType > const & iteratorCollection,
        __CollectionType < __ElementType >  const & elementCollection
) {

    auto leftIt = iteratorCollection.begin();
    auto leftEnd = iteratorCollection.end();
    auto rightIt = elementCollection.begin();
    auto rightEnd = elementCollection.end();

    if ( iteratorCollection.size() != elementCollection.size() ) {
        return false;
    }

    for ( ; leftIt != leftEnd && rightIt != rightEnd; ++ leftIt, ++ rightIt ) {
        if ( ! validator ( * ( * leftIt ) ) || ! validator ( * rightIt ) || * ( * leftIt ) != * rightIt ) {
            return false;
        }
    }

    return true;
}

template <
        typename __ElementType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        template < typename ... > class __CollectionType,                                                                           /* NOLINT(bugprone-reserved-identifier) */
        typename __IteratorType = typename cds :: experimental :: Collection < __ElementType > :: ConstIterator /* NOLINT(bugprone-reserved-identifier) */
> auto iteratorListEqualityCheckNoPred (
        __CollectionType < __IteratorType > const & iteratorCollection,
        __CollectionType < __ElementType >  const & elementCollection
) {

    auto leftIt = iteratorCollection.begin();
    auto leftEnd = iteratorCollection.end();
    auto rightIt = elementCollection.begin();
    auto rightEnd = elementCollection.end();

    if ( iteratorCollection.size() != elementCollection.size() ) {
        return false;
    }

    for ( ; leftIt != leftEnd && rightIt != rightEnd; ++ leftIt, ++ rightIt ) {
        if ( * ( * leftIt ) != * rightIt ) {
            return false;
        }
    }

    return true;
}

/* CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20. CTC-00601-FT to CTC-00634-FT */
template <
        typename __ElementType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
        typename __NonePredicate,                                                               /* NOLINT(bugprone-reserved-identifier) */
        typename __OnePredicate,                                                                /* NOLINT(bugprone-reserved-identifier) */
        typename __MorePredicateLessThanLimit,                                                  /* NOLINT(bugprone-reserved-identifier) */
        typename __MorePredicate,                                                               /* NOLINT(bugprone-reserved-identifier) */
        typename __MorePredicateMoreThanLimit,                                                  /* NOLINT(bugprone-reserved-identifier) */
        typename __AllPredicate,                                                                /* NOLINT(bugprone-reserved-identifier) */
        typename __AllAndMorePredicate,                                                         /* NOLINT(bugprone-reserved-identifier) */
        template < typename ... > class __ComparisonEquivalent = cds :: experimental :: Array   /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupFindThat (
        Test                                                      * pTestLib,
        cds :: experimental :: Collection < __ElementType > const & underTest,
        Size                                                        limit,
        __NonePredicate                                     const & none,
        __OnePredicate                                      const & one,
        __MorePredicateLessThanLimit                        const & moreLessThanLimit,
        __MorePredicate                                     const & more,
        __MorePredicateMoreThanLimit                        const & moreMoreThanLimit,
        __AllPredicate                                      const & all,
        __AllAndMorePredicate                               const & allAndMore,
        Size                                                        expectedSizeFindThatNone,
        __ComparisonEquivalent < __ElementType >            const & expectedFindThatNone,
        Size                                                        expectedSizeFindThatOne,
        __ComparisonEquivalent < __ElementType >            const & expectedFindThatOne,
        Size                                                        expectedSizeFindThatMoreLessThanLimit,
        __ComparisonEquivalent < __ElementType >            const & expectedFindThatMoreLessThanLimit,
        Size                                                        expectedSizeFindThatMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindThatMore,
        Size                                                        expectedSizeFindThatMoreMoreThanLimit,
        __ComparisonEquivalent < __ElementType >            const & expectedFindThatMoreMoreThanLimit,
        Size                                                        expectedSizeFindThatAll,
        __ComparisonEquivalent < __ElementType >            const & expectedFindThatAll,
        Size                                                        expectedSizeFindThatAllAndMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindThatAllAndMore,
        bool                                                        expectedResultFindFirstThatNone,
        __ElementType                                       const & expectedFindFirstThatNone,
        bool                                                        expectedResultFindFirstThatOne,
        __ElementType                                       const & expectedFindFirstThatOne,
        bool                                                        expectedResultFindFirstThatMore,
        __ElementType                                       const & expectedFindFirstThatMore,
        bool                                                        expectedResultFindFirstThatAll,
        __ElementType                                       const & expectedFindFirstThatAll,
        bool                                                        expectedResultFindFirstThatAllAndMore,
        __ElementType                                       const & expectedFindFirstThatAllAndMore,
        bool                                                        expectedResultFindLastThatNone,
        __ElementType                                       const & expectedFindLastThatNone,
        bool                                                        expectedResultFindLastThatOne,
        __ElementType                                       const & expectedFindLastThatOne,
        bool                                                        expectedResultFindLastThatMore,
        __ElementType                                       const & expectedFindLastThatMore,
        bool                                                        expectedResultFindLastThatAll,
        __ElementType                                       const & expectedFindLastThatAll,
        bool                                                        expectedResultFindLastThatAllAndMore,
        __ElementType                                       const & expectedFindLastThatAllAndMore,
        Size                                                        expectedSizeFindAllThatNone,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllThatNone,
        Size                                                        expectedSizeFindAllThatOne,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllThatOne,
        Size                                                        expectedSizeFindAllThatMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllThatMore,
        Size                                                        expectedSizeFindAllThatAll,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllThatAll,
        Size                                                        expectedSizeFindAllThatAllAndMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllThatAllAndMore
) -> bool {

    pTestLib->log ( "Object Under Test : %s", underTest.toString().cStr() );
    using ConstIterator = typename cds :: experimental :: Collection < __ElementType > :: ConstIterator;

    /* CollectionTestCase-FindThat-findThatStoreInMatchingNone-CPP20 : CTC-00601-FT-findThatStoreInMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00601 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00601;
    auto                                                        expectedSize00601 = expectedSizeFindThatNone;
    auto                                                const & expected00601 = expectedFindThatNone;
    auto                                                const & predicate00601 = none;

    (void) collection00601.findThat ( limit, storeIn00601, predicate00601 );
    if ( storeIn00601.size() != expectedSize00601 || ! iteratorListEqualityCheck ( predicate00601, storeIn00601, expected00601 ) ) {
        pTestLib->logError( "'CTC-00601-FT-findThatStoreInMatchingNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00601-FT-findThatStoreInMatchingNone-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatStoreInMatchingOne-CPP20 : CTC-00602-FT-findThatStoreInMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00602 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00602;
    auto                                                        expectedSize00602 = expectedSizeFindThatOne;
    auto                                                const & expected00602 = expectedFindThatOne;
    auto                                                const & predicate00602 = one;

    (void) collection00602.findThat ( limit, storeIn00602, predicate00602 );
    if ( storeIn00602.size() != expectedSize00602 || ! iteratorListEqualityCheck ( predicate00602, storeIn00602, expected00602 ) ) {
        pTestLib->logError( "'CTC-00602-FT-findThatStoreInMatchingOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00602-FT-findThatStoreInMatchingOne-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatStoreInMatchingMoreLessThanLimit-CPP20 : CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00603 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00603;
    auto                                                        expectedSize00603 = expectedSizeFindThatMoreLessThanLimit;
    auto                                                const & expected00603 = expectedFindThatMoreLessThanLimit;
    auto                                                const & predicate00603 = moreLessThanLimit;

    (void) collection00603.findThat ( limit, storeIn00603, predicate00603 );
    if ( storeIn00603.size() != expectedSize00603 || ! iteratorListEqualityCheck ( predicate00603, storeIn00603, expected00603 ) ) {
        pTestLib->logError( "'CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatStoreInMatchingMore-CPP20 : CTC-00604-FT-findThatStoreInMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00604 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00604;
    auto                                                        expectedSize00604 = expectedSizeFindThatMore;
    auto                                                const & expected00604 = expectedFindThatMore;
    auto                                                const & predicate00604 = more;

    (void) collection00604.findThat ( limit, storeIn00604, predicate00604 );
    if ( storeIn00604.size() != expectedSize00604 || ! iteratorListEqualityCheck ( predicate00604, storeIn00604, expected00604 ) ) {
        pTestLib->logError( "'CTC-00604-FT-findThatStoreInMatchingMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00604-FT-findThatStoreInMatchingMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatStoreInMatchingMoreMoreThanLimit-CPP20 : CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00605 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00605;
    auto                                                        expectedSize00605 = expectedSizeFindThatMoreMoreThanLimit;
    auto                                                const & expected00605 = expectedFindThatMoreMoreThanLimit;
    auto                                                const & predicate00605 = moreMoreThanLimit;

    (void) collection00605.findThat ( limit, storeIn00605, predicate00605 );
    if ( storeIn00605.size() != expectedSize00605 || ! iteratorListEqualityCheck ( predicate00605, storeIn00605, expected00605 ) ) {
        pTestLib->logError( "'CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatStoreInMatchingAll-CPP20 : CTC-00606-FT-findThatStoreInMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00606 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00606;
    auto                                                        expectedSize00606 = expectedSizeFindThatAll;
    auto                                                const & expected00606 = expectedFindThatAll;
    auto                                                const & predicate00606 = all;

    (void) collection00606.findThat ( limit, storeIn00606, predicate00606 );
    if ( storeIn00606.size() != expectedSize00606 || ! iteratorListEqualityCheck ( predicate00606, storeIn00606, expected00606 ) ) {
        pTestLib->logError( "'CTC-00606-FT-findThatStoreInMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00606-FT-findThatStoreInMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatStoreInMatchingAllAndMore-CPP20 : CTC-00607-FT-findThatStoreInMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00607 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00607;
    auto                                                        expectedSize00607 = expectedSizeFindThatAllAndMore;
    auto                                                const & expected00607 = expectedFindThatAllAndMore;
    auto                                                const & predicate00607 = allAndMore;

    (void) collection00607.findThat ( limit, storeIn00607, predicate00607 );
    if ( storeIn00607.size() != expectedSize00607 || ! iteratorListEqualityCheck ( predicate00607, storeIn00607, expected00607 ) ) {
        pTestLib->logError( "'CTC-00607-FT-findThatStoreInMatchingAllAndMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00607-FT-findThatStoreInMatchingAllAndMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatReturnedMatchingNone-CPP20 : CTC-00608-FT-findThatReturnedMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00608 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00608;
    auto                                                        expectedSize00608 = expectedSizeFindThatNone;
    auto                                                const & expected00608 = expectedFindThatNone;
    auto                                                const & predicate00608 = none;

    storeIn00608 = collection00608.template findThat < __ComparisonEquivalent > ( limit, predicate00608 );
    if ( storeIn00608.size() != expectedSize00608 || ! iteratorListEqualityCheck ( predicate00608, storeIn00608, expected00608 ) ) {
        pTestLib->logError( "'CTC-00608-FT-findThatReturnedMatchingNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00608-FT-findThatReturnedMatchingNone-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatReturnedMatchingOne-CPP20 : CTC-00609-FT-findThatReturnedMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00609 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00609;
    auto                                                        expectedSize00609 = expectedSizeFindThatOne;
    auto                                                const & expected00609 = expectedFindThatOne;
    auto                                                const & predicate00609 = one;

    storeIn00609 = collection00609.template findThat < __ComparisonEquivalent > ( limit, predicate00609 );
    if ( storeIn00609.size() != expectedSize00609 || ! iteratorListEqualityCheck ( predicate00609, storeIn00609, expected00609 ) ) {
        pTestLib->logError( "'CTC-00609-FT-findThatReturnedMatchingOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00609-FT-findThatReturnedMatchingOne-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatReturnedMatchingMoreLessThanLimit-CPP20 : CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00610 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00610;
    auto                                                        expectedSize00610 = expectedSizeFindThatMoreLessThanLimit;
    auto                                                const & expected00610 = expectedFindThatMoreLessThanLimit;
    auto                                                const & predicate00610 = moreLessThanLimit;

    storeIn00610 = collection00610.template findThat < __ComparisonEquivalent > ( limit, predicate00610 );
    if ( storeIn00610.size() != expectedSize00610 || ! iteratorListEqualityCheck ( predicate00610, storeIn00610, expected00610 ) ) {
        pTestLib->logError( "'CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatReturnedMatchingMore-CPP20 : CTC-00611-FT-findThatReturnedMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00611 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00611;
    auto                                                        expectedSize00611 = expectedSizeFindThatMore;
    auto                                                const & expected00611 = expectedFindThatMore;
    auto                                                const & predicate00611 = more;

    storeIn00611 = collection00611.template findThat < __ComparisonEquivalent > ( limit, predicate00611 );
    if ( storeIn00611.size() != expectedSize00611 || ! iteratorListEqualityCheck ( predicate00611, storeIn00611, expected00611 ) ) {
        pTestLib->logError( "'CTC-00611-FT-findThatReturnedMatchingMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00611-FT-findThatReturnedMatchingMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatReturnedMatchingMoreMoreThanLimit-CPP20 : CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00612 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00612;
    auto                                                        expectedSize00612 = expectedSizeFindThatMoreMoreThanLimit;
    auto                                                const & expected00612 = expectedFindThatMoreMoreThanLimit;
    auto                                                const & predicate00612 = moreMoreThanLimit;

    storeIn00612 = collection00612.template findThat < __ComparisonEquivalent > ( limit, predicate00612 );
    if ( storeIn00612.size() != expectedSize00612 || ! iteratorListEqualityCheck ( predicate00612, storeIn00612, expected00612 ) ) {
        pTestLib->logError( "'CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatReturnedMatchingAll-CPP20 : CTC-00613-FT-findThatReturnedMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00613 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00613;
    auto                                                        expectedSize00613 = expectedSizeFindThatAll;
    auto                                                const & expected00613 = expectedFindThatAll;
    auto                                                const & predicate00613 = all;

    storeIn00613 = collection00613.template findThat < __ComparisonEquivalent > ( limit, predicate00613 );
    if ( storeIn00613.size() != expectedSize00613 || ! iteratorListEqualityCheck ( predicate00613, storeIn00613, expected00613 ) ) {
        pTestLib->logError( "'CTC-00613-FT-findThatReturnedMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00613-FT-findThatReturnedMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findThatReturnedMatchingAllAndMore-CPP20 : CTC-00614-FT-findThatReturnedMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00614 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00614;
    auto                                                        expectedSize00614 = expectedSizeFindThatAllAndMore;
    auto                                                const & expected00614 = expectedFindThatAllAndMore;
    auto                                                const & predicate00614 = allAndMore;

    storeIn00614 = collection00614.template findThat < __ComparisonEquivalent > ( limit, predicate00614 );
    if ( storeIn00614.size() != expectedSize00614 || ! iteratorListEqualityCheck ( predicate00614, storeIn00614, expected00614 ) ) {
        pTestLib->logError( "'CTC-00614-FT-findThatReturnedMatchingAllAndMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00614-FT-findThatReturnedMatchingAllAndMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findFirstThatMatchingNone-CPP20 : CTC-00615-FT-findFirstThatMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00615 = underTest;
    ConstIterator                                               result00615;
    auto                                                        expectedValid00615 = expectedResultFindFirstThatNone;
    auto                                                        expectedValue00615 = expectedFindFirstThatNone;
    auto                                                const & predicate00615 = none;

    result00615 = collection00615.findFirstThat ( predicate00615 );
    if ( ( result00615 != collection00615.cend() ) != expectedValid00615 || expectedValid00615 && expectedValue00615 != * result00615 ) {
        pTestLib->logError( "'CTC-00615-FT-findFirstThatMatchingNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00615-FT-findFirstThatMatchingNone-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findFirstThatMatchingOne-CPP20 : CTC-00616-FT-findFirstThatMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00616 = underTest;
    ConstIterator                                               result00616;
    auto                                                        expectedValid00616 = expectedResultFindFirstThatOne;
    auto                                                        expectedValue00616 = expectedFindFirstThatOne;
    auto                                                const & predicate00616 = one;

    result00616 = collection00616.findFirstThat ( predicate00616 );
    if ( ( result00616 != collection00616.cend() ) != expectedValid00616 || expectedValid00616 && expectedValue00616 != * result00616 ) {
        pTestLib->logError( "'CTC-00616-FT-findFirstThatMatchingOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00616-FT-findFirstThatMatchingOne-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findFirstThatMatchingMore-CPP20 : CTC-00617-FT-findFirstThatMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00617 = underTest;
    ConstIterator                                               result00617;
    auto                                                        expectedValid00617 = expectedResultFindFirstThatMore;
    auto                                                        expectedValue00617 = expectedFindFirstThatMore;
    auto                                                const & predicate00617 = more;

    result00617 = collection00617.findFirstThat ( predicate00617 );
    if ( ( result00617 != collection00617.cend() ) != expectedValid00617 || expectedValid00617 && expectedValue00617 != * result00617 ) {
        pTestLib->logError( "'CTC-00617-FT-findFirstThatMatchingMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00617-FT-findFirstThatMatchingMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findFirstThatMatchingAll-CPP20 : CTC-00618-FT-findFirstThatMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00618 = underTest;
    ConstIterator                                               result00618;
    auto                                                        expectedValid00618 = expectedResultFindFirstThatAll;
    auto                                                        expectedValue00618 = expectedFindFirstThatAll;
    auto                                                const & predicate00618 = all;

    result00618 = collection00618.findFirstThat ( predicate00618 );
    if ( ( result00618 != collection00618.cend() ) != expectedValid00618 || expectedValid00618 && expectedValue00618 != * result00618 ) {
        pTestLib->logError( "'CTC-00618-FT-findFirstThatMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00618-FT-findFirstThatMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findFirstThatMatchingAllAndMore-CPP20 : CTC-00619-FT-findFirstThatMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00619 = underTest;
    ConstIterator                                               result00619;
    auto                                                        expectedValid00619 = expectedResultFindFirstThatAllAndMore;
    auto                                                        expectedValue00619 = expectedFindFirstThatAllAndMore;
    auto                                                const & predicate00619 = allAndMore;

    result00619 = collection00619.findFirstThat ( predicate00619 );
    if ( ( result00619 != collection00619.cend() ) != expectedValid00619 || expectedValid00619 && expectedValue00619 != * result00619 ) {
        pTestLib->logError( "'CTC-00619-FT-findFirstThatMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00619-FT-findFirstThatMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findLastThatMatchingNone-CPP20 : CTC-00620-FT-findLastThatMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00620 = underTest;
    ConstIterator                                               result00620;
    auto                                                        expectedValid00620 = expectedResultFindLastThatNone;
    auto                                                        expectedValue00620 = expectedFindLastThatNone;
    auto                                                const & predicate00620 = none;

    result00620 = collection00620.findLastThat ( predicate00620 );
    if ( ( result00620 != collection00620.cend() ) != expectedValid00620 || expectedValid00620 && expectedValue00620 != * result00620 ) {
        pTestLib->logError( "'CTC-00620-FT-findLastThatMatchingNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00620-FT-findLastThatMatchingNone-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findLastThatMatchingOne-CPP20 : CTC-00621-FT-findLastThatMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00621 = underTest;
    ConstIterator                                               result00621;
    auto                                                        expectedValid00621 = expectedResultFindLastThatOne;
    auto                                                        expectedValue00621 = expectedFindLastThatOne;
    auto                                                const & predicate00621 = one;

    result00621 = collection00621.findLastThat ( predicate00621 );
    if ( ( result00621 != collection00621.cend() ) != expectedValid00621 || expectedValid00621 && expectedValue00621 != * result00621 ) {
        pTestLib->logError( "'CTC-00621-FT-findLastThatMatchingOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00621-FT-findLastThatMatchingOne-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findLastThatMatchingMore-CPP20 : CTC-00622-FT-findLastThatMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00622 = underTest;
    ConstIterator                                               result00622;
    auto                                                        expectedValid00622 = expectedResultFindLastThatMore;
    auto                                                        expectedValue00622 = expectedFindLastThatMore;
    auto                                                const & predicate00622 = more;

    result00622 = collection00622.findLastThat ( predicate00622 );
    if ( ( result00622 != collection00622.cend() ) != expectedValid00622 || expectedValid00622 && expectedValue00622 != * result00622 ) {
        pTestLib->logError( "'CTC-00622-FT-findLastThatMatchingMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00622-FT-findLastThatMatchingMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findLastThatMatchingAll-CPP20 : CTC-00623-FT-findLastThatMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00623 = underTest;
    ConstIterator                                               result00623;
    auto                                                        expectedValid00623 = expectedResultFindLastThatAll;
    auto                                                        expectedValue00623 = expectedFindLastThatAll;
    auto                                                const & predicate00623 = all;

    result00623 = collection00623.findLastThat ( predicate00623 );
    if ( ( result00623 != collection00623.cend() ) != expectedValid00623 || expectedValid00623 && expectedValue00623 != * result00623 ) {
        pTestLib->logError( "'CTC-00623-FT-findLastThatMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00623-FT-findLastThatMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findLastThatMatchingAllAndMore-CPP20 : CTC-00624-FT-findLastThatMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00624 = underTest;
    ConstIterator                                               result00624;
    auto                                                        expectedValid00624 = expectedResultFindLastThatAllAndMore;
    auto                                                        expectedValue00624 = expectedFindLastThatAllAndMore;
    auto                                                const & predicate00624 = allAndMore;

    result00624 = collection00624.findLastThat ( predicate00624 );
    if ( ( result00624 != collection00624.cend() ) != expectedValid00624 || expectedValid00624 && expectedValue00624 != * result00624 ) {
        pTestLib->logError( "'CTC-00624-FT-findLastThatMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00624-FT-findLastThatMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatStoreInMatchingNone-CPP20 : CTC-00625-FT-findAllThatStoreInMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00625 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00625;
    auto                                                        expectedSize00625 = expectedSizeFindAllThatNone;
    auto                                                const & expected00625 = expectedFindAllThatNone;
    auto                                                const & predicate00625 = none;

    (void) collection00625.findAllThat ( storeIn00625, predicate00625 );
    if ( storeIn00625.size() != expectedSize00625 || ! iteratorListEqualityCheck ( predicate00625, storeIn00625, expected00625 ) ) {
        pTestLib->logError( "'CTC-00625-FT-findAllThatStoreInMatchingNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00625-FT-findAllThatStoreInMatchingNone-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatStoreInMatchingOne-CPP20 : CTC-00626-FT-findAllThatStoreInMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00626 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00626;
    auto                                                        expectedSize00626 = expectedSizeFindAllThatOne;
    auto                                                const & expected00626 = expectedFindAllThatOne;
    auto                                                const & predicate00626 = one;

    (void) collection00626.findAllThat ( storeIn00626, predicate00626 );
    if ( storeIn00626.size() != expectedSize00626 || ! iteratorListEqualityCheck ( predicate00626, storeIn00626, expected00626 ) ) {
        pTestLib->logError( "'CTC-00626-FT-findAllThatStoreInMatchingOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00626-FT-findAllThatStoreInMatchingOne-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatStoreInMatchingMore-CPP20 : CTC-00627-FT-findAllThatStoreInMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00627 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00627;
    auto                                                        expectedSize00627 = expectedSizeFindAllThatMore;
    auto                                                const & expected00627 = expectedFindAllThatMore;
    auto                                                const & predicate00627 = more;

    (void) collection00627.findAllThat ( storeIn00627, predicate00627 );
    if ( storeIn00627.size() != expectedSize00627 || ! iteratorListEqualityCheck ( predicate00627, storeIn00627, expected00627 ) ) {
        pTestLib->logError( "'CTC-00627-FT-findAllThatStoreInMatchingMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00627-FT-findAllThatStoreInMatchingMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatStoreInMatchingAll-CPP20 : CTC-00628-FT-findAllThatStoreInMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00628 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00628;
    auto                                                        expectedSize00628 = expectedSizeFindAllThatAll;
    auto                                                const & expected00628 = expectedFindAllThatAll;
    auto                                                const & predicate00628 = all;

    (void) collection00628.findAllThat ( storeIn00628, predicate00628 );
    if ( storeIn00628.size() != expectedSize00628 || ! iteratorListEqualityCheck ( predicate00628, storeIn00628, expected00628 ) ) {
        pTestLib->logError( "'CTC-00628-FT-findAllThatStoreInMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00628-FT-findAllThatStoreInMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatStoreInMatchingAllAndMore-CPP20 : CTC-00629-FT-findAllThatStoreInMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00629 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00629;
    auto                                                        expectedSize00629 = expectedSizeFindAllThatAllAndMore;
    auto                                                const & expected00629 = expectedFindAllThatAllAndMore;
    auto                                                const & predicate00629 = allAndMore;

    (void) collection00629.findAllThat ( storeIn00629, predicate00629 );
    if ( storeIn00629.size() != expectedSize00629 || ! iteratorListEqualityCheck ( predicate00629, storeIn00629, expected00629 ) ) {
        pTestLib->logError( "'CTC-00629-FT-findAllThatStoreInMatchingAllAndMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00629-FT-findAllThatStoreInMatchingAllAndMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatReturnedMatchingNone-CPP20 : CTC-00630-FT-findAllThatReturnedMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00630 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00630;
    auto                                                        expectedSize00630 = expectedSizeFindAllThatNone;
    auto                                                const & expected00630 = expectedFindAllThatNone;
    auto                                                const & predicate00630 = none;

    storeIn00630 = collection00630.template findAllThat < __ComparisonEquivalent > ( predicate00630 );
    if ( storeIn00630.size() != expectedSize00630 || ! iteratorListEqualityCheck ( predicate00630, storeIn00630, expected00630 ) ) {
        pTestLib->logError( "'CTC-00630-FT-findAllThatReturnedMatchingNone-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00630-FT-findAllThatReturnedMatchingNone-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatReturnedMatchingOne-CPP20 : CTC-00631-FT-findAllThatReturnedMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00631 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00631;
    auto                                                        expectedSize00631 = expectedSizeFindAllThatOne;
    auto                                                const & expected00631 = expectedFindAllThatOne;
    auto                                                const & predicate00631 = one;

    storeIn00631 = collection00631.template findAllThat < __ComparisonEquivalent > ( predicate00631 );
    if ( storeIn00631.size() != expectedSize00631 || ! iteratorListEqualityCheck ( predicate00631, storeIn00631, expected00631 ) ) {
        pTestLib->logError( "'CTC-00631-FT-findAllThatReturnedMatchingOne-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00631-FT-findAllThatReturnedMatchingOne-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatReturnedMatchingMore-CPP20 : CTC-00632-FT-findAllThatReturnedMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00632 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00632;
    auto                                                        expectedSize00632 = expectedSizeFindAllThatMore;
    auto                                                const & expected00632 = expectedFindAllThatMore;
    auto                                                const & predicate00632 = more;

    storeIn00632 = collection00632.template findAllThat < __ComparisonEquivalent > ( predicate00632 );
    if ( storeIn00632.size() != expectedSize00632 || ! iteratorListEqualityCheck ( predicate00632, storeIn00632, expected00632 ) ) {
        pTestLib->logError( "'CTC-00632-FT-findAllThatReturnedMatchingMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00632-FT-findAllThatReturnedMatchingMore-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatReturnedMatchingAll-CPP20 : CTC-00633-FT-findAllThatReturnedMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00633 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00633;
    auto                                                        expectedSize00633 = expectedSizeFindAllThatAll;
    auto                                                const & expected00633 = expectedFindAllThatAll;
    auto                                                const & predicate00633 = all;

    storeIn00633 = collection00633.template findAllThat < __ComparisonEquivalent > ( predicate00633 );
    if ( storeIn00633.size() != expectedSize00633 || ! iteratorListEqualityCheck ( predicate00633, storeIn00633, expected00633 ) ) {
        pTestLib->logError( "'CTC-00633-FT-findAllThatReturnedMatchingAll-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00633-FT-findAllThatReturnedMatchingAll-CPP20' OK" );
    }

    /* CollectionTestCase-FindThat-findAllThatReturnedMatchingAllAndMore-CPP20 : CTC-00634-FT-findAllThatReturnedMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00634 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00634;
    auto                                                        expectedSize00634 = expectedSizeFindAllThatAllAndMore;
    auto                                                const & expected00634 = expectedFindAllThatAllAndMore;
    auto                                                const & predicate00634 = allAndMore;

    storeIn00634 = collection00634.template findAllThat < __ComparisonEquivalent > ( predicate00634 );
    if ( storeIn00634.size() != expectedSize00634 || ! iteratorListEqualityCheck ( predicate00634, storeIn00634, expected00634 ) ) {
        pTestLib->logError( "'CTC-00634-FT-findAllThatReturnedMatchingAllAndMore-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00634-FT-findAllThatReturnedMatchingAllAndMore-CPP20' OK" );
    }

    return true;
}

/* CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20. CTC-00701-FO to CTC-00768-FO */
template <
        typename __IterableType,                                                                /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
        template < typename ... > class __ComparisonEquivalent = cds :: experimental :: Array   /* NOLINT(bugprone-reserved-identifier) */
> auto collectionTestGroupFindOf (
        Test                                                      * pTestLib,
        StringLiteral                                               variant,
        cds :: experimental :: Collection < __ElementType > const & underTest,
        Size                                                        limit,
        __IterableType                                      const & none,
        __IterableType                                      const & one,
        __IterableType                                      const & moreLessThanLimit,
        __IterableType                                      const & more,
        __IterableType                                      const & moreMoreThanLimit,
        __IterableType                                      const & all,
        __IterableType                                      const & allAndMore,
        Size                                                        expectedSizeFindOfNone,
        __ComparisonEquivalent < __ElementType >            const & expectedFindOfNone,
        Size                                                        expectedSizeFindOfOne,
        __ComparisonEquivalent < __ElementType >            const & expectedFindOfOne,
        Size                                                        expectedSizeFindOfMoreLessThanLimit,
        __ComparisonEquivalent < __ElementType >            const & expectedFindOfMoreLessThanLimit,
        Size                                                        expectedSizeFindOfMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindOfMore,
        Size                                                        expectedSizeFindOfMoreMoreThanLimit,
        __ComparisonEquivalent < __ElementType >            const & expectedFindOfMoreMoreThanLimit,
        Size                                                        expectedSizeFindOfAll,
        __ComparisonEquivalent < __ElementType >            const & expectedFindOfAll,
        Size                                                        expectedSizeFindOfAllAndMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindOfAllAndMore,
        bool                                                        expectedResultFindFirstOfNone,
        __ElementType                                       const & expectedFindFirstOfNone,
        bool                                                        expectedResultFindFirstOfOne,
        __ElementType                                       const & expectedFindFirstOfOne,
        bool                                                        expectedResultFindFirstOfMore,
        __ElementType                                       const & expectedFindFirstOfMore,
        bool                                                        expectedResultFindFirstOfAll,
        __ElementType                                       const & expectedFindFirstOfAll,
        bool                                                        expectedResultFindFirstOfAllAndMore,
        __ElementType                                       const & expectedFindFirstOfAllAndMore,
        bool                                                        expectedResultFindLastOfNone,
        __ElementType                                       const & expectedFindLastOfNone,
        bool                                                        expectedResultFindLastOfOne,
        __ElementType                                       const & expectedFindLastOfOne,
        bool                                                        expectedResultFindLastOfMore,
        __ElementType                                       const & expectedFindLastOfMore,
        bool                                                        expectedResultFindLastOfAll,
        __ElementType                                       const & expectedFindLastOfAll,
        bool                                                        expectedResultFindLastOfAllAndMore,
        __ElementType                                       const & expectedFindLastOfAllAndMore,
        Size                                                        expectedSizeFindAllOfNone,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfNone,
        Size                                                        expectedSizeFindAllOfOne,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfOne,
        Size                                                        expectedSizeFindAllOfMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfMore,
        Size                                                        expectedSizeFindAllOfAll,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfAll,
        Size                                                        expectedSizeFindAllOfAllAndMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfAllAndMore,
        Size                                                        expectedSizeFindNotOfNone,
        __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfNone,
        Size                                                        expectedSizeFindNotOfOne,
        __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfOne,
        Size                                                        expectedSizeFindNotOfMoreLessThanLimit,
        __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfMoreLessThanLimit,
        Size                                                        expectedSizeFindNotOfMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfMore,
        Size                                                        expectedSizeFindNotOfMoreMoreThanLimit,
        __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfMoreMoreThanLimit,
        Size                                                        expectedSizeFindNotOfAll,
        __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfAll,
        Size                                                        expectedSizeFindNotOfAllAndMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfAllAndMore,
        bool                                                        expectedResultFindFirstNotOfNone,
        __ElementType                                       const & expectedFindFirstNotOfNone,
        bool                                                        expectedResultFindFirstNotOfOne,
        __ElementType                                       const & expectedFindFirstNotOfOne,
        bool                                                        expectedResultFindFirstNotOfMore,
        __ElementType                                       const & expectedFindFirstNotOfMore,
        bool                                                        expectedResultFindFirstNotOfAll,
        __ElementType                                       const & expectedFindFirstNotOfAll,
        bool                                                        expectedResultFindFirstNotOfAllAndMore,
        __ElementType                                       const & expectedFindFirstNotOfAllAndMore,
        bool                                                        expectedResultFindLastNotOfNone,
        __ElementType                                       const & expectedFindLastNotOfNone,
        bool                                                        expectedResultFindLastNotOfOne,
        __ElementType                                       const & expectedFindLastNotOfOne,
        bool                                                        expectedResultFindLastNotOfMore,
        __ElementType                                       const & expectedFindLastNotOfMore,
        bool                                                        expectedResultFindLastNotOfAll,
        __ElementType                                       const & expectedFindLastNotOfAll,
        bool                                                        expectedResultFindLastNotOfAllAndMore,
        __ElementType                                       const & expectedFindLastNotOfAllAndMore,
        Size                                                        expectedSizeFindAllNotOfNone,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfNone,
        Size                                                        expectedSizeFindAllNotOfOne,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfOne,
        Size                                                        expectedSizeFindAllNotOfMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfMore,
        Size                                                        expectedSizeFindAllNotOfAll,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfAll,
        Size                                                        expectedSizeFindAllNotOfAllAndMore,
        __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfAllAndMore
) -> bool {

    pTestLib->log ( "Object Under Test : %s", underTest.toString().cStr() );
    using ConstIterator = typename cds :: experimental :: Collection < __ElementType > :: ConstIterator;

    /* CollectionTestCase-FindOf-findOfStoreInMatchingNone-CPP20 : CTC-00701-FO-findOfStoreInMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00701 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00701;
    auto                                                        expectedSize00701 = expectedSizeFindOfNone;
    auto                                                const & expected00701 = expectedFindOfNone;
    auto                                                const & target00701 = none;

    (void) collection00701.findOf ( limit, storeIn00701, target00701 );
    if ( storeIn00701.size() != expectedSize00701 || ! iteratorListEqualityCheckNoPred ( storeIn00701, expected00701 ) ) {
        pTestLib->logError( "'CTC-00701-FO-findOfStoreInMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00701-FO-findOfStoreInMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfStoreInMatchingOne-CPP20 : CTC-00702-FO-findOfStoreInMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00702 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00702;
    auto                                                        expectedSize00702 = expectedSizeFindOfOne;
    auto                                                const & expected00702 = expectedFindOfOne;
    auto                                                const & target00702 = one;

    (void) collection00702.findOf ( limit, storeIn00702, target00702 );
    if ( storeIn00702.size() != expectedSize00702 || ! iteratorListEqualityCheckNoPred ( storeIn00702, expected00702 ) ) {
        pTestLib->logError( "'CTC-00702-FO-findOfStoreInMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00702-FO-findOfStoreInMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfStoreInMatchingMoreLessThanLimit-CPP20 : CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00703 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00703;
    auto                                                        expectedSize00703 = expectedSizeFindOfMoreLessThanLimit;
    auto                                                const & expected00703 = expectedFindOfMoreLessThanLimit;
    auto                                                const & target00703 = moreLessThanLimit;

    (void) collection00703.findOf ( limit, storeIn00703, target00703 );
    if ( storeIn00703.size() != expectedSize00703 || ! iteratorListEqualityCheckNoPred ( storeIn00703, expected00703 ) ) {
        pTestLib->logError( "'CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfStoreInMatchingMore-CPP20 : CTC-00704-FO-findOfStoreInMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00704 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00704;
    auto                                                        expectedSize00704 = expectedSizeFindOfMore;
    auto                                                const & expected00704 = expectedFindOfMore;
    auto                                                const & target00704 = more;

    (void) collection00704.findOf ( limit, storeIn00704, target00704 );
    if ( storeIn00704.size() != expectedSize00704 || ! iteratorListEqualityCheckNoPred ( storeIn00704, expected00704 ) ) {
        pTestLib->logError( "'CTC-00704-FO-findOfStoreInMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00704-FO-findOfStoreInMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfStoreInMatchingMoreMoreThanLimit-CPP20 : CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00705 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00705;
    auto                                                        expectedSize00705 = expectedSizeFindOfMoreMoreThanLimit;
    auto                                                const & expected00705 = expectedFindOfMoreMoreThanLimit;
    auto                                                const & target00705 = moreMoreThanLimit;

    (void) collection00705.findOf ( limit, storeIn00705, target00705 );
    if ( storeIn00705.size() != expectedSize00705 || ! iteratorListEqualityCheckNoPred ( storeIn00705, expected00705 ) ) {
        pTestLib->logError( "'CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfStoreInMatchingAll-CPP20 : CTC-00706-FO-findOfStoreInMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00706 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00706;
    auto                                                        expectedSize00706 = expectedSizeFindOfAll;
    auto                                                const & expected00706 = expectedFindOfAll;
    auto                                                const & target00706 = all;

    (void) collection00706.findOf ( limit, storeIn00706, target00706 );
    if ( storeIn00706.size() != expectedSize00706 || ! iteratorListEqualityCheckNoPred ( storeIn00706, expected00706 ) ) {
        pTestLib->logError( "'CTC-00706-FO-findOfStoreInMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00706-FO-findOfStoreInMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfStoreInMatchingAllAndMore-CPP20 : CTC-00707-FO-findOfStoreInMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00707 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00707;
    auto                                                        expectedSize00707 = expectedSizeFindOfAllAndMore;
    auto                                                const & expected00707 = expectedFindOfAllAndMore;
    auto                                                const & target00707 = allAndMore;

    (void) collection00707.findOf ( limit, storeIn00707, target00707 );
    if ( storeIn00707.size() != expectedSize00707 || ! iteratorListEqualityCheckNoPred ( storeIn00707, expected00707 ) ) {
        pTestLib->logError( "'CTC-00707-FO-findOfStoreInMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00707-FO-findOfStoreInMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfReturnedMatchingNone-CPP20 : CTC-00708-FO-findOfReturnedMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00708 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00708;
    auto                                                        expectedSize00708 = expectedSizeFindOfNone;
    auto                                                const & expected00708 = expectedFindOfNone;
    auto                                                const & target00708 = none;

    storeIn00708 = collection00708.template findOf < __ComparisonEquivalent > ( limit, target00708 );
    if ( storeIn00708.size() != expectedSize00708 || ! iteratorListEqualityCheckNoPred ( storeIn00708, expected00708 ) ) {
        pTestLib->logError( "'CTC-00708-FO-findOfReturnedMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00708-FO-findOfReturnedMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfReturnedMatchingOne-CPP20 : CTC-00709-FO-findOfReturnedMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00709 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00709;
    auto                                                        expectedSize00709 = expectedSizeFindOfOne;
    auto                                                const & expected00709 = expectedFindOfOne;
    auto                                                const & target00709 = one;

    storeIn00709 = collection00709.template findOf < __ComparisonEquivalent > ( limit, target00709 );
    if ( storeIn00709.size() != expectedSize00709 || ! iteratorListEqualityCheckNoPred ( storeIn00709, expected00709 ) ) {
        pTestLib->logError( "'CTC-00709-FO-findOfReturnedMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00709-FO-findOfReturnedMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfReturnedMatchingMoreLessThanLimit-CPP20 : CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00710 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00710;
    auto                                                        expectedSize00710 = expectedSizeFindOfMoreLessThanLimit;
    auto                                                const & expected00710 = expectedFindOfMoreLessThanLimit;
    auto                                                const & target00710 = moreLessThanLimit;

    storeIn00710 = collection00710.template findOf < __ComparisonEquivalent > ( limit, target00710 );
    if ( storeIn00710.size() != expectedSize00710 || ! iteratorListEqualityCheckNoPred ( storeIn00710, expected00710 ) ) {
        pTestLib->logError( "'CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfReturnedMatchingMore-CPP20 : CTC-00711-FO-findOfReturnedMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00711 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00711;
    auto                                                        expectedSize00711 = expectedSizeFindOfMore;
    auto                                                const & expected00711 = expectedFindOfMore;
    auto                                                const & target00711 = more;

    storeIn00711 = collection00711.template findOf < __ComparisonEquivalent > ( limit, target00711 );
    if ( storeIn00711.size() != expectedSize00711 || ! iteratorListEqualityCheckNoPred ( storeIn00711, expected00711 ) ) {
        pTestLib->logError( "'CTC-00711-FO-findOfReturnedMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00711-FO-findOfReturnedMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfReturnedMatchingMoreMoreThanLimit-CPP20 : CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00712 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00712;
    auto                                                        expectedSize00712 = expectedSizeFindOfMoreMoreThanLimit;
    auto                                                const & expected00712 = expectedFindOfMoreMoreThanLimit;
    auto                                                const & target00712 = moreMoreThanLimit;

    storeIn00712 = collection00712.template findOf < __ComparisonEquivalent > ( limit, target00712 );
    if ( storeIn00712.size() != expectedSize00712 || ! iteratorListEqualityCheckNoPred ( storeIn00712, expected00712 ) ) {
        pTestLib->logError( "'CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfReturnedMatchingAll-CPP20 : CTC-00713-FO-findOfReturnedMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00713 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00713;
    auto                                                        expectedSize00713 = expectedSizeFindOfAll;
    auto                                                const & expected00713 = expectedFindOfAll;
    auto                                                const & target00713 = all;

    storeIn00713 = collection00713.template findOf < __ComparisonEquivalent > ( limit, target00713 );
    if ( storeIn00713.size() != expectedSize00713 || ! iteratorListEqualityCheckNoPred ( storeIn00713, expected00713 ) ) {
        pTestLib->logError( "'CTC-00713-FO-findOfReturnedMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00713-FO-findOfReturnedMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findOfReturnedMatchingAllAndMore-CPP20 : CTC-00714-FO-findOfReturnedMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00714 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00714;
    auto                                                        expectedSize00714 = expectedSizeFindOfAllAndMore;
    auto                                                const & expected00714 = expectedFindOfAllAndMore;
    auto                                                const & target00714 = allAndMore;

    storeIn00714 = collection00714.template findOf < __ComparisonEquivalent > ( limit, target00714 );
    if ( storeIn00714.size() != expectedSize00714 || ! iteratorListEqualityCheckNoPred ( storeIn00714, expected00714 ) ) {
        pTestLib->logError( "'CTC-00714-FO-findOfReturnedMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00714-FO-findOfReturnedMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstOfMatchingNone-CPP20 : CTC-00715-FO-findFirstOfMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00715 = underTest;
    ConstIterator                                               result00715;
    auto                                                        expectedResult00715 = expectedResultFindFirstOfNone;
    auto                                                const & expected00715 = expectedFindFirstOfNone;
    auto                                                const & target00715 = none;

    result00715 = collection00715.findFirstOf ( target00715 );
    if ( ( result00715 != collection00715.cend() ) != expectedResult00715 || expectedResult00715 && expected00715 != * result00715 ) {
        pTestLib->logError( "'CTC-00715-FO-findFirstOfMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00715-FO-findFirstOfMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstOfMatchingOne-CPP20 : CTC-00716-FO-findFirstOfMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00716 = underTest;
    ConstIterator                                               result00716;
    auto                                                        expectedResult00716 = expectedResultFindFirstOfOne;
    auto                                                const & expected00716 = expectedFindFirstOfOne;
    auto                                                const & target00716 = one;

    result00716 = collection00716.findFirstOf ( target00716 );
    if ( ( result00716 != collection00716.cend() ) != expectedResult00716 || expectedResult00716 && expected00716 != * result00716 ) {
        pTestLib->logError( "'CTC-00716-FO-findFirstOfMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00716-FO-findFirstOfMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstOfMatchingMore-CPP20 : CTC-00717-FO-findFirstOfMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00717 = underTest;
    ConstIterator                                               result00717;
    auto                                                        expectedResult00717 = expectedResultFindFirstOfMore;
    auto                                                const & expected00717 = expectedFindFirstOfMore;
    auto                                                const & target00717 = more;

    result00717 = collection00717.findFirstOf ( target00717 );
    if ( ( result00717 != collection00717.cend() ) != expectedResult00717 || expectedResult00717 && expected00717 != * result00717 ) {
        pTestLib->logError( "'CTC-00717-FO-findFirstOfMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00717-FO-findFirstOfMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstOfMatchingAll-CPP20 : CTC-00718-FO-findFirstOfMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00718 = underTest;
    ConstIterator                                               result00718;
    auto                                                        expectedResult00718 = expectedResultFindFirstOfAll;
    auto                                                const & expected00718 = expectedFindFirstOfAll;
    auto                                                const & target00718 = all;

    result00718 = collection00718.findFirstOf ( target00718 );
    if ( ( result00718 != collection00718.cend() ) != expectedResult00718 || expectedResult00718 && expected00718 != * result00718 ) {
        pTestLib->logError( "'CTC-00718-FO-findFirstOfMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00718-FO-findFirstOfMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstOfMatchingAllAndMore-CPP20 : CTC-00719-FO-findFirstOfMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00719 = underTest;
    ConstIterator                                               result00719;
    auto                                                        expectedResult00719 = expectedResultFindFirstOfAllAndMore;
    auto                                                const & expected00719 = expectedFindFirstOfAllAndMore;
    auto                                                const & target00719 = allAndMore;

    result00719 = collection00719.findFirstOf ( target00719 );
    if ( ( result00719 != collection00719.cend() ) != expectedResult00719 || expectedResult00719 && expected00719 != * result00719 ) {
        pTestLib->logError( "'CTC-00719-FO-findFirstOfMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00719-FO-findFirstOfMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastOfMatchingNone-CPP20 : CTC-00720-FO-findLastOfMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00720 = underTest;
    ConstIterator                                               result00720;
    auto                                                        expectedResult00720 = expectedResultFindLastOfNone;
    auto                                                const & expected00720 = expectedFindLastOfNone;
    auto                                                const & target00720 = none;

    result00720 = collection00720.findLastOf ( target00720 );
    if ( ( result00720 != collection00720.cend() ) != expectedResult00720 || expectedResult00720 && expected00720 != * result00720 ) {
        pTestLib->logError( "'CTC-00720-FO-findLastOfMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00720-FO-findLastOfMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastOfMatchingOne-CPP20 : CTC-00721-FO-findLastOfMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00721 = underTest;
    ConstIterator                                               result00721;
    auto                                                        expectedResult00721 = expectedResultFindLastOfOne;
    auto                                                const & expected00721 = expectedFindLastOfOne;
    auto                                                const & target00721 = one;

    result00721 = collection00721.findLastOf ( target00721 );
    if ( ( result00721 != collection00721.cend() ) != expectedResult00721 || expectedResult00721 && expected00721 != * result00721 ) {
        pTestLib->logError( "'CTC-00721-FO-findLastOfMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00721-FO-findLastOfMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastOfMatchingMore-CPP20 : CTC-00722-FO-findLastOfMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00722 = underTest;
    ConstIterator                                               result00722;
    auto                                                        expectedResult00722 = expectedResultFindLastOfMore;
    auto                                                const & expected00722 = expectedFindLastOfMore;
    auto                                                const & target00722 = more;

    result00722 = collection00722.findLastOf ( target00722 );
    if ( ( result00722 != collection00722.cend() ) != expectedResult00722 || expectedResult00722 && expected00722 != * result00722 ) {
        pTestLib->logError( "'CTC-00722-FO-findLastOfMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00722-FO-findLastOfMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastOfMatchingAll-CPP20 : CTC-00723-FO-findLastOfMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00723 = underTest;
    ConstIterator                                               result00723;
    auto                                                        expectedResult00723 = expectedResultFindLastOfAll;
    auto                                                const & expected00723 = expectedFindLastOfAll;
    auto                                                const & target00723 = all;

    result00723 = collection00723.findLastOf ( target00723 );
    if ( ( result00723 != collection00723.cend() ) != expectedResult00723 || expectedResult00723 && expected00723 != * result00723 ) {
        pTestLib->logError( "'CTC-00723-FO-findLastOfMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00723-FO-findLastOfMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastOfMatchingAllAndMore-CPP20 : CTC-00724-FO-findLastOfMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00724 = underTest;
    ConstIterator                                               result00724;
    auto                                                        expectedResult00724 = expectedResultFindLastOfAllAndMore;
    auto                                                const & expected00724 = expectedFindLastOfAllAndMore;
    auto                                                const & target00724 = allAndMore;

    result00724 = collection00724.findLastOf ( target00724 );
    if ( ( result00724 != collection00724.cend() ) != expectedResult00724 || expectedResult00724 && expected00724 != * result00724 ) {
        pTestLib->logError( "'CTC-00724-FO-findLastOfMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00724-FO-findLastOfMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfStoreInMatchingNone-CPP20 : CTC-00725-FO-findAllOfStoreInMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00725 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00725;
    auto                                                        expectedSize00725 = expectedSizeFindAllOfNone;
    auto                                                const & expected00725 = expectedFindAllOfNone;
    auto                                                const & target00725 = none;

    (void) collection00725.findAllOf ( storeIn00725, target00725 );
    if ( storeIn00725.size() != expectedSize00725 || ! iteratorListEqualityCheckNoPred ( storeIn00725, expected00725 ) ) {
        pTestLib->logError( "'CTC-00725-FO-findAllOfStoreInMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00725-FO-findAllOfStoreInMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfStoreInMatchingOne-CPP20 : CTC-00726-FO-findAllOfStoreInMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00726 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00726;
    auto                                                        expectedSize00726 = expectedSizeFindAllOfOne;
    auto                                                const & expected00726 = expectedFindAllOfOne;
    auto                                                const & target00726 = one;

    (void) collection00726.findAllOf ( storeIn00726, target00726 );
    if ( storeIn00726.size() != expectedSize00726 || ! iteratorListEqualityCheckNoPred ( storeIn00726, expected00726 ) ) {
        pTestLib->logError( "'CTC-00726-FO-findAllOfStoreInMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00726-FO-findAllOfStoreInMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfStoreInMatchingMore-CPP20 : CTC-00727-FO-findAllOfStoreInMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00727 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00727;
    auto                                                        expectedSize00727 = expectedSizeFindAllOfMore;
    auto                                                const & expected00727 = expectedFindAllOfMore;
    auto                                                const & target00727 = more;

    (void) collection00727.findAllOf ( storeIn00727, target00727 );
    if ( storeIn00727.size() != expectedSize00727 || ! iteratorListEqualityCheckNoPred ( storeIn00727, expected00727 ) ) {
        pTestLib->logError( "'CTC-00727-FO-findAllOfStoreInMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00727-FO-findAllOfStoreInMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfStoreInMatchingAll-CPP20 : CTC-00728-FO-findAllOfStoreInMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00728 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00728;
    auto                                                        expectedSize00728 = expectedSizeFindAllOfAll;
    auto                                                const & expected00728 = expectedFindAllOfAll;
    auto                                                const & target00728 = all;

    (void) collection00728.findAllOf ( storeIn00728, target00728 );
    if ( storeIn00728.size() != expectedSize00728 || ! iteratorListEqualityCheckNoPred ( storeIn00728, expected00728 ) ) {
        pTestLib->logError( "'CTC-00728-FO-findAllOfStoreInMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00728-FO-findAllOfStoreInMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfStoreInMatchingAllAndMore-CPP20 : CTC-00729-FO-findAllOfStoreInMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00729 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00729;
    auto                                                        expectedSize00729 = expectedSizeFindAllOfAllAndMore;
    auto                                                const & expected00729 = expectedFindAllOfAllAndMore;
    auto                                                const & target00729 = allAndMore;

    (void) collection00729.findAllOf ( storeIn00729, target00729 );
    if ( storeIn00729.size() != expectedSize00729 || ! iteratorListEqualityCheckNoPred ( storeIn00729, expected00729 ) ) {
        pTestLib->logError( "'CTC-00729-FO-findAllOfStoreInMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00729-FO-findAllOfStoreInMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfReturnedMatchingNone-CPP20 : CTC-00730-FO-findAllOfReturnedMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00730 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00730;
    auto                                                        expectedSize00730 = expectedSizeFindAllOfNone;
    auto                                                const & expected00730 = expectedFindAllOfNone;
    auto                                                const & target00730 = none;

    storeIn00730 = collection00730.template findAllOf < __ComparisonEquivalent > ( target00730 );
    if ( storeIn00730.size() != expectedSize00730 || ! iteratorListEqualityCheckNoPred ( storeIn00730, expected00730 ) ) {
        pTestLib->logError( "'CTC-00730-FO-findAllOfReturnedMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00730-FO-findAllOfReturnedMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfReturnedMatchingOne-CPP20 : CTC-00731-FO-findAllOfReturnedMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00731 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00731;
    auto                                                        expectedSize00731 = expectedSizeFindAllOfOne;
    auto                                                const & expected00731 = expectedFindAllOfOne;
    auto                                                const & target00731 = one;

    storeIn00731 = collection00731.template findAllOf < __ComparisonEquivalent > ( target00731 );
    if ( storeIn00731.size() != expectedSize00731 || ! iteratorListEqualityCheckNoPred ( storeIn00731, expected00731 ) ) {
        pTestLib->logError( "'CTC-00731-FO-findAllOfReturnedMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00731-FO-findAllOfReturnedMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfReturnedMatchingMore-CPP20 : CTC-00732-FO-findAllOfReturnedMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00732 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00732;
    auto                                                        expectedSize00732 = expectedSizeFindAllOfMore;
    auto                                                const & expected00732 = expectedFindAllOfMore;
    auto                                                const & target00732 = more;

    storeIn00732 = collection00732.template findAllOf < __ComparisonEquivalent > ( target00732 );
    if ( storeIn00732.size() != expectedSize00732 || ! iteratorListEqualityCheckNoPred ( storeIn00732, expected00732 ) ) {
        pTestLib->logError( "'CTC-00732-FO-findAllOfReturnedMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00732-FO-findAllOfReturnedMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfReturnedMatchingAll-CPP20 : CTC-00733-FO-findAllOfReturnedMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00733 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00733;
    auto                                                        expectedSize00733 = expectedSizeFindAllOfAll;
    auto                                                const & expected00733 = expectedFindAllOfAll;
    auto                                                const & target00733 = all;

    storeIn00733 = collection00733.template findAllOf < __ComparisonEquivalent > ( target00733 );
    if ( storeIn00733.size() != expectedSize00733 || ! iteratorListEqualityCheckNoPred ( storeIn00733, expected00733 ) ) {
        pTestLib->logError( "'CTC-00733-FO-findAllOfReturnedMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00733-FO-findAllOfReturnedMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllOfReturnedMatchingAllAndMore-CPP20 : CTC-00734-FO-findAllOfReturnedMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00734 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00734;
    auto                                                        expectedSize00734 = expectedSizeFindAllOfAllAndMore;
    auto                                                const & expected00734 = expectedFindAllOfAllAndMore;
    auto                                                const & target00734 = allAndMore;

    storeIn00734 = collection00734.template findAllOf < __ComparisonEquivalent > ( target00734 );
    if ( storeIn00734.size() != expectedSize00734 || ! iteratorListEqualityCheckNoPred ( storeIn00734, expected00734 ) ) {
        pTestLib->logError( "'CTC-00734-FO-findAllOfReturnedMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00734-FO-findAllOfReturnedMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfStoreInMatchingNone-CPP20 : CTC-00735-FO-findNotOfStoreInMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00735 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00735;
    auto                                                        expectedSize00735 = expectedSizeFindNotOfNone;
    auto                                                const & expected00735 = expectedFindNotOfNone;
    auto                                                const & target00735 = none;

    (void) collection00735.findNotOf ( limit, storeIn00735, target00735 );
    if ( storeIn00735.size() != expectedSize00735 || ! iteratorListEqualityCheckNoPred ( storeIn00735, expected00735 ) ) {
        pTestLib->logError( "'CTC-00735-FO-findNotOfStoreInMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00735-FO-findNotOfStoreInMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfStoreInMatchingOne-CPP20 : CTC-00736-FO-findNotOfStoreInMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00736 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00736;
    auto                                                        expectedSize00736 = expectedSizeFindNotOfOne;
    auto                                                const & expected00736 = expectedFindNotOfOne;
    auto                                                const & target00736 = one;

    (void) collection00736.findNotOf ( limit, storeIn00736, target00736 );
    if ( storeIn00736.size() != expectedSize00736 || ! iteratorListEqualityCheckNoPred ( storeIn00736, expected00736 ) ) {
        pTestLib->logError( "'CTC-00736-FO-findNotOfStoreInMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00736-FO-findNotOfStoreInMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfStoreInMatchingMoreLessThanLimit-CPP20 : CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00737 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00737;
    auto                                                        expectedSize00737 = expectedSizeFindNotOfMoreLessThanLimit;
    auto                                                const & expected00737 = expectedFindNotOfMoreLessThanLimit;
    auto                                                const & target00737 = moreLessThanLimit;

    (void) collection00737.findNotOf ( limit, storeIn00737, target00737 );
    if ( storeIn00737.size() != expectedSize00737 || ! iteratorListEqualityCheckNoPred ( storeIn00737, expected00737 ) ) {
        pTestLib->logError( "'CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfStoreInMatchingMore-CPP20 : CTC-00738-FO-findNotOfStoreInMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00738 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00738;
    auto                                                        expectedSize00738 = expectedSizeFindNotOfMore;
    auto                                                const & expected00738 = expectedFindNotOfMore;
    auto                                                const & target00738 = more;

    (void) collection00738.findNotOf ( limit, storeIn00738, target00738 );
    if ( storeIn00738.size() != expectedSize00738 || ! iteratorListEqualityCheckNoPred ( storeIn00738, expected00738 ) ) {
        pTestLib->logError( "'CTC-00738-FO-findNotOfStoreInMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00738-FO-findNotOfStoreInMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfStoreInMatchingMoreMoreThanLimit-CPP20 : CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00739 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00739;
    auto                                                        expectedSize00739 = expectedSizeFindNotOfMoreMoreThanLimit;
    auto                                                const & expected00739 = expectedFindNotOfMoreMoreThanLimit;
    auto                                                const & target00739 = moreMoreThanLimit;

    (void) collection00739.findNotOf ( limit, storeIn00739, target00739 );
    if ( storeIn00739.size() != expectedSize00739 || ! iteratorListEqualityCheckNoPred ( storeIn00739, expected00739 ) ) {
        pTestLib->logError( "'CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfStoreInMatchingAll-CPP20 : CTC-00740-FO-findNotOfStoreInMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00740 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00740;
    auto                                                        expectedSize00740 = expectedSizeFindNotOfAll;
    auto                                                const & expected00740 = expectedFindNotOfAll;
    auto                                                const & target00740 = all;

    (void) collection00740.findNotOf ( limit, storeIn00740, target00740 );
    if ( storeIn00740.size() != expectedSize00740 || ! iteratorListEqualityCheckNoPred ( storeIn00740, expected00740 ) ) {
        pTestLib->logError( "'CTC-00740-FO-findNotOfStoreInMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00740-FO-findNotOfStoreInMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfStoreInMatchingAllAndMore-CPP20 : CTC-00741-FO-findNotOfStoreInMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00741 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00741;
    auto                                                        expectedSize00741 = expectedSizeFindNotOfAllAndMore;
    auto                                                const & expected00741 = expectedFindNotOfAllAndMore;
    auto                                                const & target00741 = allAndMore;

    (void) collection00741.findNotOf ( limit, storeIn00741, target00741 );
    if ( storeIn00741.size() != expectedSize00741 || ! iteratorListEqualityCheckNoPred ( storeIn00741, expected00741 ) ) {
        pTestLib->logError( "'CTC-00741-FO-findNotOfStoreInMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00741-FO-findNotOfStoreInMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfReturnedMatchingNone-CPP20 : CTC-00742-FO-findNotOfReturnedMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00742 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00742;
    auto                                                        expectedSize00742 = expectedSizeFindNotOfNone;
    auto                                                const & expected00742 = expectedFindNotOfNone;
    auto                                                const & target00742 = none;

    storeIn00742 = collection00742.template findNotOf < __ComparisonEquivalent > ( limit, target00742 );
    if ( storeIn00742.size() != expectedSize00742 || ! iteratorListEqualityCheckNoPred ( storeIn00742, expected00742 ) ) {
        pTestLib->logError( "'CTC-00742-FO-findNotOfReturnedMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00742-FO-findNotOfReturnedMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfReturnedMatchingOne-CPP20 : CTC-00743-FO-findNotOfReturnedMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00743 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00743;
    auto                                                        expectedSize00743 = expectedSizeFindNotOfOne;
    auto                                                const & expected00743 = expectedFindNotOfOne;
    auto                                                const & target00743 = one;

    storeIn00743 = collection00743.template findNotOf < __ComparisonEquivalent > ( limit, target00743 );
    if ( storeIn00743.size() != expectedSize00743 || ! iteratorListEqualityCheckNoPred ( storeIn00743, expected00743 ) ) {
        pTestLib->logError( "'CTC-00743-FO-findNotOfReturnedMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00743-FO-findNotOfReturnedMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfReturnedMatchingMoreLessThanLimit-CPP20 : CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00744 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00744;
    auto                                                        expectedSize00744 = expectedSizeFindNotOfMoreLessThanLimit;
    auto                                                const & expected00744 = expectedFindNotOfMoreLessThanLimit;
    auto                                                const & target00744 = moreLessThanLimit;

    storeIn00744 = collection00744.template findNotOf < __ComparisonEquivalent > ( limit, target00744 );
    if ( storeIn00744.size() != expectedSize00744 || ! iteratorListEqualityCheckNoPred ( storeIn00744, expected00744 ) ) {
        pTestLib->logError( "'CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfReturnedMatchingMore-CPP20 : CTC-00745-FO-findNotOfReturnedMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00745 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00745;
    auto                                                        expectedSize00745 = expectedSizeFindNotOfMore;
    auto                                                const & expected00745 = expectedFindNotOfMore;
    auto                                                const & target00745 = more;

    storeIn00745 = collection00745.template findNotOf < __ComparisonEquivalent > ( limit, target00745 );
    if ( storeIn00745.size() != expectedSize00745 || ! iteratorListEqualityCheckNoPred ( storeIn00745, expected00745 ) ) {
        pTestLib->logError( "'CTC-00745-FO-findNotOfReturnedMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00745-FO-findNotOfReturnedMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfReturnedMatchingMoreMoreThanLimit-CPP20 : CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00746 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00746;
    auto                                                        expectedSize00746 = expectedSizeFindNotOfMoreMoreThanLimit;
    auto                                                const & expected00746 = expectedFindNotOfMoreMoreThanLimit;
    auto                                                const & target00746 = moreMoreThanLimit;

    storeIn00746 = collection00746.template findNotOf < __ComparisonEquivalent > ( limit, target00746 );
    if ( storeIn00746.size() != expectedSize00746 || ! iteratorListEqualityCheckNoPred ( storeIn00746, expected00746 ) ) {
        pTestLib->logError( "'CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfReturnedMatchingAll-CPP20 : CTC-00747-FO-findNotOfReturnedMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00747 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00747;
    auto                                                        expectedSize00747 = expectedSizeFindNotOfAll;
    auto                                                const & expected00747 = expectedFindNotOfAll;
    auto                                                const & target00747 = all;

    storeIn00747 = collection00747.template findNotOf < __ComparisonEquivalent > ( limit, target00747 );
    if ( storeIn00747.size() != expectedSize00747 || ! iteratorListEqualityCheckNoPred ( storeIn00747, expected00747 ) ) {
        pTestLib->logError( "'CTC-00747-FO-findNotOfReturnedMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00747-FO-findNotOfReturnedMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findNotOfReturnedMatchingAllAndMore-CPP20 : CTC-00748-FO-findNotOfReturnedMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00748 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00748;
    auto                                                        expectedSize00748 = expectedSizeFindNotOfAllAndMore;
    auto                                                const & expected00748 = expectedFindNotOfAllAndMore;
    auto                                                const & target00748 = allAndMore;

    storeIn00748 = collection00748.template findNotOf < __ComparisonEquivalent > ( limit, target00748 );
    if ( storeIn00748.size() != expectedSize00748 || ! iteratorListEqualityCheckNoPred ( storeIn00748, expected00748 ) ) {
        pTestLib->logError( "'CTC-00748-FO-findNotOfReturnedMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00748-FO-findNotOfReturnedMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstNotOfMatchingNone-CPP20 : CTC-00749-FO-findFirstNotOfMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00749 = underTest;
    ConstIterator                                               result00749;
    auto                                                        expectedResult00749 = expectedResultFindFirstNotOfNone;
    auto                                                const & expected00749 = expectedFindFirstNotOfNone;
    auto                                                const & target00749 = none;

    result00749 = collection00749.findFirstNotOf ( target00749 );
    if ( ( result00749 != collection00749.cend() ) != expectedResult00749 || expectedResult00749 && expected00749 != * result00749 ) {
        pTestLib->logError( "'CTC-00749-FO-findFirstNotOfMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00749-FO-findFirstNotOfMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstNotOfMatchingOne-CPP20 : CTC-00750-FO-findFirstNotOfMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00750 = underTest;
    ConstIterator                                               result00750;
    auto                                                        expectedResult00750 = expectedResultFindFirstNotOfOne;
    auto                                                const & expected00750 = expectedFindFirstNotOfOne;
    auto                                                const & target00750 = one;

    result00750 = collection00750.findFirstNotOf ( target00750 );
    if ( ( result00750 != collection00750.cend() ) != expectedResult00750 || expectedResult00750 && expected00750 != * result00750 ) {
        pTestLib->logError( "'CTC-00750-FO-findFirstNotOfMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00750-FO-findFirstNotOfMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstNotOfMatchingMore-CPP20 : CTC-00751-FO-findFirstNotOfMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00751 = underTest;
    ConstIterator                                               result00751;
    auto                                                        expectedResult00751 = expectedResultFindFirstNotOfMore;
    auto                                                const & expected00751 = expectedFindFirstNotOfMore;
    auto                                                const & target00751 = more;

    result00751 = collection00751.findFirstNotOf ( target00751 );
    if ( ( result00751 != collection00751.cend() ) != expectedResult00751 || expectedResult00751 && expected00751 != * result00751 ) {
        pTestLib->logError( "'CTC-00751-FO-findFirstNotOfMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00751-FO-findFirstNotOfMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstNotOfMatchingAll-CPP20 : CTC-00752-FO-findFirstNotOfMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00752 = underTest;
    ConstIterator                                               result00752;
    auto                                                        expectedResult00752 = expectedResultFindFirstNotOfAll;
    auto                                                const & expected00752 = expectedFindFirstNotOfAll;
    auto                                                const & target00752 = all;

    result00752 = collection00752.findFirstNotOf ( target00752 );
    if ( ( result00752 != collection00752.cend() ) != expectedResult00752 || expectedResult00752 && expected00752 != * result00752 ) {
        pTestLib->logError( "'CTC-00752-FO-findFirstNotOfMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00752-FO-findFirstNotOfMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findFirstNotOfMatchingAllAndMore-CPP20 : CTC-00753-FO-findFirstNotOfMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00753 = underTest;
    ConstIterator                                               result00753;
    auto                                                        expectedResult00753 = expectedResultFindFirstNotOfAllAndMore;
    auto                                                const & expected00753 = expectedFindFirstNotOfAllAndMore;
    auto                                                const & target00753 = allAndMore;

    result00753 = collection00753.findFirstNotOf ( target00753 );
    if ( ( result00753 != collection00753.cend() ) != expectedResult00753 || expectedResult00753 && expected00753 != * result00753 ) {
        pTestLib->logError( "'CTC-00753-FO-findFirstNotOfMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00753-FO-findFirstNotOfMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastNotOfMatchingNone-CPP20 : CTC-00754-FO-findLastNotOfMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00754 = underTest;
    ConstIterator                                               result00754;
    auto                                                        expectedResult00754 = expectedResultFindLastNotOfNone;
    auto                                                const & expected00754 = expectedFindLastNotOfNone;
    auto                                                const & target00754 = none;

    result00754 = collection00754.findLastNotOf ( target00754 );
    if ( ( result00754 != collection00754.cend() ) != expectedResult00754 || expectedResult00754 && expected00754 != * result00754 ) {
        pTestLib->logError( "'CTC-00754-FO-findLastNotOfMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00754-FO-findLastNotOfMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastNotOfMatchingOne-CPP20 : CTC-00755-FO-findLastNotOfMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00755 = underTest;
    ConstIterator                                               result00755;
    auto                                                        expectedResult00755 = expectedResultFindLastNotOfOne;
    auto                                                const & expected00755 = expectedFindLastNotOfOne;
    auto                                                const & target00755 = one;

    result00755 = collection00755.findLastNotOf ( target00755 );
    if ( ( result00755 != collection00755.cend() ) != expectedResult00755 || expectedResult00755 && expected00755 != * result00755 ) {
        pTestLib->logError( "'CTC-00755-FO-findLastNotOfMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00755-FO-findLastNotOfMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastNotOfMatchingMore-CPP20 : CTC-00756-FO-findLastNotOfMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00756 = underTest;
    ConstIterator                                               result00756;
    auto                                                        expectedResult00756 = expectedResultFindLastNotOfMore;
    auto                                                const & expected00756 = expectedFindLastNotOfMore;
    auto                                                const & target00756 = more;

    result00756 = collection00756.findLastNotOf ( target00756 );
    if ( ( result00756 != collection00756.cend() ) != expectedResult00756 || expectedResult00756 && expected00756 != * result00756 ) {
        pTestLib->logError( "'CTC-00756-FO-findLastNotOfMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00756-FO-findLastNotOfMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastNotOfMatchingAll-CPP20 : CTC-00757-FO-findLastNotOfMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00757 = underTest;
    ConstIterator                                               result00757;
    auto                                                        expectedResult00757 = expectedResultFindLastNotOfAll;
    auto                                                const & expected00757 = expectedFindLastNotOfAll;
    auto                                                const & target00757 = all;

    result00757 = collection00757.findLastNotOf ( target00757 );
    if ( ( result00757 != collection00757.cend() ) != expectedResult00757 || expectedResult00757 && expected00757 != * result00757 ) {
        pTestLib->logError( "'CTC-00757-FO-findLastNotOfMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00757-FO-findLastNotOfMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findLastOfMatchingAllAndMore-CPP20 : CTC-00758-FO-findLastNotOfMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00758 = underTest;
    ConstIterator                                               result00758;
    auto                                                        expectedResult00758 = expectedResultFindLastNotOfAllAndMore;
    auto                                                const & expected00758 = expectedFindLastNotOfAllAndMore;
    auto                                                const & target00758 = allAndMore;

    result00758 = collection00758.findLastNotOf ( target00758 );
    if ( ( result00758 != collection00758.cend() ) != expectedResult00758 || expectedResult00758 && expected00758 != * result00758 ) {
        pTestLib->logError( "'CTC-00758-FO-findLastNotOfMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00758-FO-findLastNotOfMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingNone-CPP20 : CTC-00759-FO-findAllNotOfStoreInMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00759 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00759;
    auto                                                        expectedSize00759 = expectedSizeFindAllNotOfNone;
    auto                                                const & expected00759 = expectedFindAllNotOfNone;
    auto                                                const & target00759 = none;

    (void) collection00759.findAllNotOf ( storeIn00759, target00759 );
    if ( storeIn00759.size() != expectedSize00759 || ! iteratorListEqualityCheckNoPred ( storeIn00759, expected00759 ) ) {
        pTestLib->logError( "'CTC-00759-FO-findAllNotOfStoreInMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00759-FO-findAllNotOfStoreInMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingOne-CPP20 : CTC-00760-FO-findAllNotOfStoreInMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00760 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00760;
    auto                                                        expectedSize00760 = expectedSizeFindAllNotOfOne;
    auto                                                const & expected00760 = expectedFindAllNotOfOne;
    auto                                                const & target00760 = one;

    (void) collection00760.findAllNotOf ( storeIn00760, target00760 );
    if ( storeIn00760.size() != expectedSize00760 || ! iteratorListEqualityCheckNoPred ( storeIn00760, expected00760 ) ) {
        pTestLib->logError( "'CTC-00760-FO-findAllNotOfStoreInMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00760-FO-findAllNotOfStoreInMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingMore-CPP20 : CTC-00761-FO-findAllNotOfStoreInMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00761 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00761;
    auto                                                        expectedSize00761 = expectedSizeFindAllNotOfMore;
    auto                                                const & expected00761 = expectedFindAllNotOfMore;
    auto                                                const & target00761 = more;

    (void) collection00761.findAllNotOf ( storeIn00761, target00761 );
    if ( storeIn00761.size() != expectedSize00761 || ! iteratorListEqualityCheckNoPred ( storeIn00761, expected00761 ) ) {
        pTestLib->logError( "'CTC-00761-FO-findAllNotOfStoreInMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00761-FO-findAllNotOfStoreInMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingAll-CPP20 : CTC-00762-FO-findAllNotOfStoreInMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00762 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00762;
    auto                                                        expectedSize00762 = expectedSizeFindAllNotOfAll;
    auto                                                const & expected00762 = expectedFindAllNotOfAll;
    auto                                                const & target00762 = all;

    (void) collection00762.findAllNotOf ( storeIn00762, target00762 );
    if ( storeIn00762.size() != expectedSize00762 || ! iteratorListEqualityCheckNoPred ( storeIn00762, expected00762 ) ) {
        pTestLib->logError( "'CTC-00762-FO-findAllNotOfStoreInMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00762-FO-findAllNotOfStoreInMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingAllAndMore-CPP20 : CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00763 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00763;
    auto                                                        expectedSize00763 = expectedSizeFindAllNotOfAllAndMore;
    auto                                                const & expected00763 = expectedFindAllNotOfAllAndMore;
    auto                                                const & target00763 = allAndMore;

    (void) collection00763.findAllNotOf ( storeIn00763, target00763 );
    if ( storeIn00763.size() != expectedSize00763 || ! iteratorListEqualityCheckNoPred ( storeIn00763, expected00763 ) ) {
        pTestLib->logError( "'CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingNone-CPP20 : CTC-00764-FO-findAllNotOfReturnedMatchingNone-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00764 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00764;
    auto                                                        expectedSize00764 = expectedSizeFindAllNotOfNone;
    auto                                                const & expected00764 = expectedFindAllNotOfNone;
    auto                                                const & target00764 = none;

    storeIn00764 = collection00764.template findAllNotOf < __ComparisonEquivalent > ( target00764 );
    if ( storeIn00764.size() != expectedSize00764 || ! iteratorListEqualityCheckNoPred ( storeIn00764, expected00764 ) ) {
        pTestLib->logError( "'CTC-00764-FO-findAllNotOfReturnedMatchingNone-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00764-FO-findAllNotOfReturnedMatchingNone-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingOne-CPP20 : CTC-00765-FO-findAllNotOfReturnedMatchingOne-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00765 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00765;
    auto                                                        expectedSize00765 = expectedSizeFindAllNotOfOne;
    auto                                                const & expected00765 = expectedFindAllNotOfOne;
    auto                                                const & target00765 = one;

    storeIn00765 = collection00765.template findAllNotOf < __ComparisonEquivalent > ( target00765 );
    if ( storeIn00765.size() != expectedSize00765 || ! iteratorListEqualityCheckNoPred ( storeIn00765, expected00765 ) ) {
        pTestLib->logError( "'CTC-00765-FO-findAllNotOfReturnedMatchingOne-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00765-FO-findAllNotOfReturnedMatchingOne-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingMore-CPP20 : CTC-00766-FO-findAllNotOfReturnedMatchingMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00766 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00766;
    auto                                                        expectedSize00766 = expectedSizeFindAllNotOfMore;
    auto                                                const & expected00766 = expectedFindAllNotOfMore;
    auto                                                const & target00766 = more;

    storeIn00766 = collection00766.template findAllNotOf < __ComparisonEquivalent > ( target00766 );
    if ( storeIn00766.size() != expectedSize00766 || ! iteratorListEqualityCheckNoPred ( storeIn00766, expected00766 ) ) {
        pTestLib->logError( "'CTC-00766-FO-findAllNotOfReturnedMatchingMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00766-FO-findAllNotOfReturnedMatchingMore-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingAll-CPP20 : CTC-00767-FO-findAllNotOfReturnedMatchingAll-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00767 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00767;
    auto                                                        expectedSize00767 = expectedSizeFindAllNotOfAll;
    auto                                                const & expected00767 = expectedFindAllNotOfAll;
    auto                                                const & target00767 = all;

    storeIn00767 = collection00767.template findAllNotOf < __ComparisonEquivalent > ( target00767 );
    if ( storeIn00767.size() != expectedSize00767 || ! iteratorListEqualityCheckNoPred ( storeIn00767, expected00767 ) ) {
        pTestLib->logError( "'CTC-00767-FO-findAllNotOfReturnedMatchingAll-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00767-FO-findAllNotOfReturnedMatchingAll-%s-CPP20' OK", variant );
    }

    /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingAllAndMore-CPP20 : CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-CPP20 */
    cds :: experimental :: Collection < __ElementType > const & collection00768 = underTest;
    __ComparisonEquivalent < ConstIterator >                    storeIn00768;
    auto                                                        expectedSize00768 = expectedSizeFindAllNotOfAllAndMore;
    auto                                                const & expected00768 = expectedFindAllNotOfAllAndMore;
    auto                                                const & target00768 = allAndMore;

    storeIn00768 = collection00768.template findAllNotOf < __ComparisonEquivalent > ( target00768 );
    if ( storeIn00768.size() != expectedSize00768 || ! iteratorListEqualityCheckNoPred ( storeIn00768, expected00768 ) ) {
        pTestLib->logError( "'CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-%s-CPP20' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-%s-CPP20' OK", variant );
    }

    return true;
}

/* CollectionTestSuite-CPP20 : CTS-00001-CPP20 */
auto CollectionTest :: execute () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntArray", [& allOk, this] {

        cds :: experimental :: Array < int > intArrayObjectUnderTest;
        intArrayObjectUnderTest     = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
        ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: Array < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: Array < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: LinkedList < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intArrayObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < int > intLinkedListObjectUnderTest;
        intLinkedListObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: Array < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: LinkedList < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: Array < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intLinkedListObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < int > intHashSetObjectUnderTest;
        intHashSetObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: HashSet < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: HashSet < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intHashSetObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < int, int > intIntHashMapObjectUnderTest;
        intIntHashMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 2, 7 );
        auto expectedToBeNotFound   = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 6, 20 );
        auto expectedHash           = ((((
                                                 ( cds :: hash (1) ^ cds :: hash (6) ) * 31 + ( cds :: hash ( 2 ) ^ cds :: hash (7))
                                         ) * 31 + ( cds :: hash ( 3 )) ^ cds :: hash (8)) * 31 + ( cds :: hash ( 4 ) ^ cds :: hash (9)) ) * 31 + ( cds :: hash ( 5 )) ^ cds :: hash (10));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto equalDifferentType     = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto notEqualSameType       = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualDifferentType  = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions (
                intIntHashMapObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringArray", [& allOk, this] {

        cds :: experimental :: Array < cds :: String > stringArrayObjectUnderTest;
        stringArrayObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
        ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: Array < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: Array < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringArrayObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < cds :: String > stringLinkedListObjectUnderTest;
        stringLinkedListObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: Array < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: Array < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringLinkedListObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < cds :: String > stringHashSetObjectUnderTest;
        stringHashSetObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "{ are, Ana, mere }"; /// due to hash table
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "are" ) * 31 + cds :: hash ( "Ana" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringHashSetObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringToStringHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < cds :: String, cds :: String > stringStringHashMapObjectUnderTest;
        stringStringHashMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ are: verb, Ana: name, mere: noun }"; /// due to hash table
        auto expectedSize           = 3;
        auto expectedToBeFound      = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "are", "verb" );
        auto expectedToBeNotFound   = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "pere", "noun" );
        auto expectedHash           = (
                                               (( cds :: hash ("are") ^ cds :: hash ("verb") ) * 31 + ( cds :: hash ( "Ana" ) ^ cds :: hash ("name")))
                                          * 31 + ( cds :: hash ( "mere" ) ^ cds :: hash ("noun")));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto equalDifferentType     = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto notEqualSameType       = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "pere", "noun" } };
        auto notEqualDifferentType  = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "other" } };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions < cds :: MapEntry < cds :: String, cds :: String > > (
                stringStringHashMapObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });


    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntArray", [& allOk, this] {

        cds :: experimental :: Array < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < int, int > objUnderTest = {{3,4}, {4,5}, {5,6}, {6,7}, {7,8}};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < MapEntry < int, int > > (
                objUnderTest,
                this,
                MapEntry < int, int > { 3, 4 },
                MapEntry < int, int > { 4, 5 },
                MapEntry < int, int > { 5, 6 },
                MapEntry < int, int > { 6, 7 },
                MapEntry < int, int > { 7, 8 }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringArray", [& allOk, this] {

        cds :: experimental :: Array < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < String > objUnderTest = {"are", "Ana", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "are", "Ana", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringToStringHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < String, String > objUnderTest = {{"are","verb"}, {"Ana","name"}, {"mere","noun"}};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < MapEntry < String, String > > (
                objUnderTest,
                this,
                MapEntry < String, String > { "are", "verb" },
                MapEntry < String, String > { "Ana", "name" },
                MapEntry < String, String > { "mere", "noun" }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-SpecialAddressBasedIteratorAccess-CPP20 : CTG-00050-IT-CPP20 : StringArray", [& allOk, this] {

        /* only one test required, as it uses operator *, which was tested in previous group */
        cds :: experimental :: Array < String > arr = { "Ana", "are", "mere" };
        cds :: experimental :: Collection < String > & c = arr;
        auto begin = c.begin();

        /* CollectionTestCase-SpecialAddressBasedIteratorAccess-addressOperator-CPP20 : CTC-00057-IT-addressOperator-CPP20 */
        auto expectedLen = 3;
        auto len = begin->length();

        this->log ( "iterator '-> operator length' : '%llu', expected '-> operator length' : '%llu'", len, expectedLen );
        if ( expectedLen != len ) {
            this->logError ( "'CTC-00057-IT-addressOperator-CPP20' error" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00057-IT-addressOperator-CPP20' OK" );
        }
    });


    /* CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 - Tests CTC-00101-FS to CTC-10139-FS - located directly below due to varability of these tests */
    /* IntArray */              this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs139 = { 1, 2, 3, 4, 5 };
        experimental :: Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* IntLinkedList */         this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntLinkedList", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs139 = { 1, 2, 3, 4, 5 };
        experimental :: Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* IntHashSet */            this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs139 = { 1, 2, 3, 4, 5 };
        experimental :: Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* IntToIntHashMap */       this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntToIntHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs101 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs102 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs103 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs104 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs105 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs106 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs107 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs108 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs109 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs110 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {8, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs111 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs112 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs113 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs114 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) { return e.key() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs115 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs116 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) { return e.key() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs117 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [comparedTo] (auto e) { return e.key() > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs118 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs119 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs120 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs121 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs122 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs123 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs124 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs125 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs126 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs127 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs128 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs129 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs130 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs131 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs132 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs133 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs134 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs135 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs136 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs137 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs138 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (auto e) { return e.key() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs139 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        experimental :: Collection < MapEntry < int, int > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( auto e ) { if ( e.key() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringArray */           this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        experimental :: Collection < String > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringLinkedList */      this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringLinkedList", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        experimental :: Collection < String > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringHashSet */         this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        experimental :: Collection < String > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringToStringHashMap */ this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringToStringHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs101 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs102 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs103 = { {"x", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs104 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs105 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs106 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs107 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs108 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs109 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs110 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs111 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs112 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs113 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs114 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs115 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs116 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) { return e.key().length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs117 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [comparedTo] (auto e) { return e.key().length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs118 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs119 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs120 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs121 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs122 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs123 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs124 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs125 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs126 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs127 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs128 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs129 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs130 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs131 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs132 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs133 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs134 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs135 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs136 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs137 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs138 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (auto e) { return e.key().length() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs139 = { {"X", "x"}, {"YY" ,"Y"}, {"z", "Z"}, {"WW", "W"}, {"t", "TTT"} };
        experimental :: Collection < MapEntry < String, String > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( auto e ) { if ( e.key().length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });

    /* CollectionTestGroup-FunctionalStatementsMemberFunction-CPP20 : CTG-00200-FSMF-CPP20 - Tests CTC-00201-FSMF to CTC-00229-FSMF */
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatementsMemberFunction-CPP20 : CTG-00200-FSMF-CPP20 : StringArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatementsMemberFunction-forEach-CPP20 : CTC-00201-FSMF-forEach-CPP20. Test Success if compile success */
        cds :: experimental :: Array < String > fs201 = { "Ana", "are", "mere" };
        fs201.forEach ( [](auto e){ (void) e.length(); } );
        fs201.forEach ( & String :: length );
        this->logOK ( "'CTC-00201-FSMF-forEach-CPP20' OK" );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someEqual-CPP20 : CTC-00202-FSMF-someEqual-CPP20. */
        cds :: experimental :: Array < String > fs202 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00202-FSMF-someEqual-CPP20",
                /* objUnderTest */  fs202,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someLess-CPP20 : CTC-00203-FSMF-someLess-CPP20. */
        cds :: experimental :: Array < String > fs203 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00203-FSMF-someLess-CPP20",
                /* objUnderTest */  fs203,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someMore-CPP20 : CTC-00204-FSMF-someMore-CPP20. */
        cds :: experimental :: Array < String > fs204 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00204-FSMF-someMore-CPP20",
                /* objUnderTest */  fs204,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeast-CPP20 : CTC-00205-FSMF-atLeast-CPP20. */
        cds :: experimental :: Array < String > fs205 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00205-FSMF-atLeast-CPP20",
                /* objUnderTest */  fs205,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeastLess-CPP20 : CTC-00206-FSMF-atLeastLess-CPP20. */
        cds :: experimental :: Array < String > fs206 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00206-FSMF-atLeastLess-CPP20",
                /* objUnderTest */  fs206,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeastMore-CPP20 : CTC-00207-FSMF-atLeastMore-CPP20. */
        cds :: experimental :: Array < String > fs207 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00207-FSMF-atLeastMore-CPP20",
                /* objUnderTest */  fs207,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMost-CPP20 : CTC-00208-FSMF-atMost-CPP20. */
        cds :: experimental :: Array < String > fs208 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00208-FSMF-atMost-CPP20",
                /* objUnderTest */  fs208,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMostLess-CPP20 : CTC-00209-FSMF-atMostLess-CPP20. */
        cds :: experimental :: Array < String > fs209 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00209-FSMF-atMostLess-CPP20",
                /* objUnderTest */  fs209,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMostMore-CPP20 : CTC-00210-FSMF-atMostMore-CPP20. */
        cds :: experimental :: Array < String > fs210 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00210-FSMF-atMostMore-CPP20",
                /* objUnderTest */  fs210,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThan-CPP20 : CTC-00211-FSMF-moreThan-CPP20. */
        cds :: experimental :: Array < String > fs211 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00211-FSMF-moreThan-CPP20",
                /* objUnderTest */  fs211,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThanLess-CPP20 : CTC-00212-FSMF-moreThanLess-CPP20. */
        cds :: experimental :: Array < String > fs212 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00212-FSMF-moreThanLess-CPP20",
                /* objUnderTest */  fs212,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThanMore-CPP20 : CTC-00213-FSMF-moreThanMore-CPP20. */
        cds :: experimental :: Array < String > fs213 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00213-FSMF-moreThanMore-CPP20",
                /* objUnderTest */  fs213,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThan-CPP20 : CTC-00214-FSMF-fewerThan-CPP20. */
        cds :: experimental :: Array < String > fs214 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00214-FSMF-fewerThan-CPP20",
                /* objUnderTest */  fs214,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThanLess-CPP20 : CTC-00215-FSMF-fewerThanLess-CPP20. */
        cds :: experimental :: Array < String > fs215 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00215-FSMF-fewerThanLess-CPP20",
                /* objUnderTest */  fs215,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThanMore-CPP20 : CTC-00216-FSMF-fewerThanMore-CPP20. */
        cds :: experimental :: Array < String > fs216 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00216-FSMF-fewerThanMore-CPP20",
                /* objUnderTest */  fs216,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-countExact-CPP20 : CTC-00217-FSMF-countExact-CPP20. */
        cds :: experimental :: Array < String > fs217 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00217-FSMF-countExact-CPP20",
                /* objUnderTest */  fs217,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     & String :: empty,
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyNone-CPP20 : CTC-00218-FSMF-anyNone-CPP20. */
        cds :: experimental :: Array < String > fs218 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00218-FSMF-anyNone-CPP20",
                /* objUnderTest */  fs218,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyOne-CPP20 : CTC-00219-FSMF-anyOne-CPP20. */
        cds :: experimental :: Array < String > fs219 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00219-FSMF-anyOne-CPP20",
                /* objUnderTest */  fs219,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyMore-CPP20 : CTC-00220-FSMF-anyMore-CPP20. */
        cds :: experimental :: Array < String > fs220 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00220-FSMF-anyMore-CPP20",
                /* objUnderTest */  fs220,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyAll-CPP20 : CTC-00221-FSMF-anyAll-CPP20. */
        cds :: experimental :: Array < String > fs221 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00221-FSMF-anyAll-CPP20",
                /* objUnderTest */  fs221,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allNone-CPP20 : CTC-00222-FSMF-allNone-CPP20. */
        cds :: experimental :: Array < String > fs222 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00222-FSMF-allNone-CPP20",
                /* objUnderTest */  fs222,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allOne-CPP20 : CTC-00223-FSMF-allOne-CPP20. */
        cds :: experimental :: Array < String > fs223 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00223-FSMF-allOne-CPP20",
                /* objUnderTest */  fs223,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allMore-CPP20 : CTC-00224-FSMF-allMore-CPP20. */
        cds :: experimental :: Array < String > fs224 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00224-FSMF-allMore-CPP20",
                /* objUnderTest */  fs224,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allAll-CPP20 : CTC-00225-FSMF-allAll-CPP20. */
        cds :: experimental :: Array < String > fs225 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00225-FSMF-allAll-CPP20",
                /* objUnderTest */  fs225,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneNone-CPP20 : CTC-00226-FSMF-noneNone-CPP20. */
        cds :: experimental :: Array < String > fs226 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00226-FSMF-noneNone-CPP20",
                /* objUnderTest */  fs226,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneOne-CPP20 : CTC-00227-FSMF-noneOne-CPP20. */
        cds :: experimental :: Array < String > fs227 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00227-FSMF-noneOne-CPP20",
                /* objUnderTest */  fs227,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneMore-CPP20 : CTC-00228-FSMF-noneMore-CPP20. */
        cds :: experimental :: Array < String > fs228 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00228-FSMF-noneMore-CPP20",
                /* objUnderTest */  fs228,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneAll-CPP20 : CTC-00229-FSMF-noneAll-CPP20. */
        cds :: experimental :: Array < String > fs229 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00229-FSMF-noneAll-CPP20",
                /* objUnderTest */  fs229,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );
    });


    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntArray", [& allOk, this] {

        cds :: experimental :: Array < int > intArray = { 1, 2, 3, 4, 5 };

        cds :: experimental :: Array < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: Array < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: Array < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: Array < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: Array < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < int > > (
                /* groupName= */        "Collection",
                /* collection= */       intArray,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < int > noneCommonList = { 6, 7, 8, 9, 10 };
        std :: initializer_list < int > oneCommonList = { 6, 2, 8, 9, 10 };
        std :: initializer_list < int > moreCommonList = { 6, 2, 8, 4, 5 };
        std :: initializer_list < int > allCommonList = { 1, 2, 3, 4, 5 };
        std :: initializer_list < int > allCommonAndMoreList = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < int > > (
                /* groupName= */        "InitializerList",
                /* collection= */       intArray,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < int > intLinkedList = { 1, 2, 3, 4, 5 };

        cds :: experimental :: LinkedList < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: LinkedList < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: LinkedList < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: LinkedList < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: LinkedList < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < int > > (
                /* groupName= */        "Collection",
                /* collection= */       intLinkedList,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < int > noneCommonList = { 6, 7, 8, 9, 10 };
        std :: initializer_list < int > oneCommonList = { 6, 2, 8, 9, 10 };
        std :: initializer_list < int > moreCommonList = { 6, 2, 8, 4, 5 };
        std :: initializer_list < int > allCommonList = { 1, 2, 3, 4, 5 };
        std :: initializer_list < int > allCommonAndMoreList = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < int > > (
                /* groupName= */        "InitializerList",
                /* collection= */       intLinkedList,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < int > intHashSet = { 1, 2, 3, 4, 5 };

        cds :: experimental :: HashSet < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: HashSet < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: HashSet < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: HashSet < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: HashSet < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < int > > (
                /* groupName= */        "Collection",
                /* collection= */       intHashSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < int > noneCommonList = { 6, 7, 8, 9, 10 };
        std :: initializer_list < int > oneCommonList = { 6, 2, 8, 9, 10 };
        std :: initializer_list < int > moreCommonList = { 6, 2, 8, 4, 5 };
        std :: initializer_list < int > allCommonList = { 1, 2, 3, 4, 5 };
        std :: initializer_list < int > allCommonAndMoreList = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < int > > (
                /* groupName= */        "InitializerList",
                /* collection= */       intHashSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < int, int > intToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: experimental :: HashMap < int, int > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < int, int > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < int, int > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < int, int > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < int, int > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < MapEntry < int, int > > > (
                /* groupName= */        "Collection",
                /* collection= */       intToIntHashMap,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < MapEntry < int, int > > noneCommonList = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        std :: initializer_list < MapEntry < int, int > > oneCommonList = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        std :: initializer_list < MapEntry < int, int > > moreCommonList = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        std :: initializer_list < MapEntry < int, int > > allCommonList = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        std :: initializer_list < MapEntry < int, int > > allCommonAndMoreList = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < MapEntry < int, int > > > (
                /* groupName= */        "InitializerList",
                /* collection= */       intToIntHashMap,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringArray", [& allOk, this] {

        cds :: experimental :: Array < String > StringArray = { 1, 2, 3, 4, 5 };

        cds :: experimental :: Array < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: Array < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: Array < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: Array < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: Array < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < String > > (
                /* groupName= */        "Collection",
                /* collection= */       StringArray,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < String > noneCommonList = { 6, 7, 8, 9, 10 };
        std :: initializer_list < String > oneCommonList = { 6, 2, 8, 9, 10 };
        std :: initializer_list < String > moreCommonList = { 6, 2, 8, 4, 5 };
        std :: initializer_list < String > allCommonList = { 1, 2, 3, 4, 5 };
        std :: initializer_list < String > allCommonAndMoreList = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < String > > (
                /* groupName= */        "InitializerList",
                /* collection= */       StringArray,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < String > StringLinkedList = { 1, 2, 3, 4, 5 };

        cds :: experimental :: LinkedList < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: LinkedList < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: LinkedList < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: LinkedList < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: LinkedList < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < String > > (
                /* groupName= */        "Collection",
                /* collection= */       StringLinkedList,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < String > noneCommonList = { 6, 7, 8, 9, 10 };
        std :: initializer_list < String > oneCommonList = { 6, 2, 8, 9, 10 };
        std :: initializer_list < String > moreCommonList = { 6, 2, 8, 4, 5 };
        std :: initializer_list < String > allCommonList = { 1, 2, 3, 4, 5 };
        std :: initializer_list < String > allCommonAndMoreList = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < String > > (
                /* groupName= */        "InitializerList",
                /* collection= */       StringLinkedList,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < String > StringHashSet = { 1, 2, 3, 4, 5 };

        cds :: experimental :: HashSet < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: HashSet < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: HashSet < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: HashSet < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: HashSet < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < String > > (
                /* groupName= */        "Collection",
                /* collection= */       StringHashSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < String > noneCommonList = { 6, 7, 8, 9, 10 };
        std :: initializer_list < String > oneCommonList = { 6, 2, 8, 9, 10 };
        std :: initializer_list < String > moreCommonList = { 6, 2, 8, 4, 5 };
        std :: initializer_list < String > allCommonList = { 1, 2, 3, 4, 5 };
        std :: initializer_list < String > allCommonAndMoreList = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < String > > (
                /* groupName= */        "InitializerList",
                /* collection= */       StringHashSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < String, String > StringToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: experimental :: HashMap < String, String > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < String, String > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < String, String > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < String, String > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < String, String > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < MapEntry < String, String > > > (
                /* groupName= */        "Collection",
                /* collection= */       StringToIntHashMap,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommon,
                /* oneCommon= */        oneCommon,
                /* moreCommon= */       moreCommon,
                /* allCommon= */        allCommon,
                /* allCommonAndMore= */ allCommonAndMore
        );

        std :: initializer_list < MapEntry < String, String > > noneCommonList = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        std :: initializer_list < MapEntry < String, String > > oneCommonList = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        std :: initializer_list < MapEntry < String, String > > moreCommonList = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        std :: initializer_list < MapEntry < String, String > > allCommonList = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        std :: initializer_list < MapEntry < String, String > > allCommonAndMoreList = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-InitializerList-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < MapEntry < String, String > > > (
                /* groupName= */        "InitializerList",
                /* collection= */       StringToIntHashMap,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });


    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : IntArray", [this, & allOk]{

        cds :: experimental :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: Collection < int > & underTestColl = underTest;

        cds :: experimental :: Array < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: Array < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: experimental :: Array < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: Array < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: Array < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : IntLinkedList", [this, & allOk]{

        cds :: experimental :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: Collection < int > & underTestColl = underTest;

        cds :: experimental :: LinkedList < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: LinkedList < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: experimental :: LinkedList < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: LinkedList < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: LinkedList < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : IntHashSet", [this, & allOk]{

        cds :: experimental :: HashSet < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: Collection < int > & underTestColl = underTest;

        cds :: experimental :: HashSet < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: HashSet < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: experimental :: HashSet < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: HashSet < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: HashSet < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : IntToIntHashMap", [this, & allOk]{

        cds :: experimental :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: experimental :: Collection < MapEntry < int, int > > & underTestColl = underTest;

        cds :: experimental :: HashMap < int, int > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: experimental :: HashMap < int, int > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: experimental :: HashMap < int, int > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: experimental :: HashMap < int, int > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: experimental :: HashMap < int, int > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : StringArray", [this, & allOk]{

        cds :: experimental :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: Collection < String > & underTestColl = underTest;

        cds :: experimental :: Array < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: Array < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: experimental :: Array < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: Array < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: Array < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : StringLinkedList", [this, & allOk]{

        cds :: experimental :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: Collection < String > & underTestColl = underTest;

        cds :: experimental :: LinkedList < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: experimental :: LinkedList < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: experimental :: LinkedList < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: LinkedList < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: experimental :: LinkedList < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : StringHashSet", [this, & allOk]{

        cds :: experimental :: HashSet < String > underTest = { 4, 5, 6, 7, 8, 9, 1, 2, 3 }; /// by hash order
        cds :: experimental :: Collection < String > & underTestColl = underTest;

        cds :: experimental :: HashSet < String > afterFrontRemove = { 5, 6, 7, 8, 9, 1, 2, 3 };
        cds :: experimental :: HashSet < String > afterMidRemove = { 5, 6, 7, 8, 1, 2, 3 };
        cds :: experimental :: HashSet < String > afterBackRemove = { 5, 6, 7, 8, 1, 2 };
        cds :: experimental :: HashSet < String > afterAfterBackRemove = { 5, 6, 7, 8, 1, 2 };
        cds :: experimental :: HashSet < String > afterOtherRemove = { 5, 6, 7, 8, 1, 2 };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-CPP20 : CTG-00350-RAIT-CPP20 : StringToStringHashMap", [this, & allOk]{

        cds :: experimental :: HashMap < String, String > underTest = { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        cds :: experimental :: Collection < MapEntry < String, String > > & underTestColl = underTest;

        cds :: experimental :: HashMap < String, String > afterFrontRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3},  };
        cds :: experimental :: HashMap < String, String > afterMidRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2}, {3, 3} };
        cds :: experimental :: HashMap < String, String > afterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: experimental :: HashMap < String, String > afterAfterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: experimental :: HashMap < String, String > afterOtherRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };

        allOk = allOk && collectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });

#define make_a(type, ...) cds :: experimental :: Array < type > { __VA_ARGS__ }
#define make_ll(type, ...) cds :: experimental :: LinkedList < type > { __VA_ARGS__ }
#define make_hs(type, ...) cds :: experimental :: HashSet < type > { __VA_ARGS__ }
#define make_hm(ktype, vtype, ...) cds :: experimental :: HashMap < ktype, vtype > { __VA_ARGS__ }
#define make_il(...) { __VA_ARGS__ }

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : IntArray", [this, & allOk]{

        cds :: experimental :: Array < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


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
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : IntLinkedList", [this, & allOk]{

        cds :: experimental :: LinkedList < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


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
                /* equivAfterRemoveThatMatchesNone = */                 make_ll ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesOne = */                  make_ll ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_ll ( int, 1, 2, 3, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_ll ( int, 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_ll ( int, 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesAll = */                  make_ll ( int, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_ll ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_ll ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_ll ( int, 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_ll ( int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_ll ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_ll ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_ll ( int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_ll ( int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_ll ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_ll ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_ll ( int, 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_ll ( int )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : IntHashSet", [this, & allOk]{

        cds :: experimental :: HashSet < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


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
                /* equivAfterRemoveThatMatchesNone = */                 make_hs ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesOne = */                  make_hs ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_hs ( int, 1, 2, 3, 6, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_hs ( int, 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_hs ( int, 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveThatMatchesAll = */                  make_hs ( int, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_hs ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_hs ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_hs ( int, 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_hs ( int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_hs ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_hs ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_hs ( int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_hs ( int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_hs ( int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_hs ( int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_hs ( int, 1, 2, 3, 7, 8, 9 ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_hs ( int )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : IntToIntHashMap", [this, & allOk]{

        cds :: experimental :: HashMap < int, int > originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };


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
                /* equivAfterRemoveThatMatchesNone = */                 make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveThatMatchesOne = */                  make_hm ( int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveThatMatchesAll = */                  make_hm ( int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_hm ( int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_hm ( int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_hm ( int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_hm ( int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_hm ( int, int, {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_hm ( int, int )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : StringArray", [this, & allOk]{

        cds :: experimental :: Array < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


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
                /* equivAfterRemoveThatMatchesNone = */                 make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_a ( String, "aaa", "aab", "aac", "bba", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_a ( String, "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_a ( String, "aaa", "aac", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_a ( String, "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_a ( String, "aaa", "aab", "aac", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_a ( String, "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_a ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_a ( String, "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_a ( String )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : StringLinkedList", [this, & allOk]{

        cds :: experimental :: LinkedList < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


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
                /* equivAfterRemoveThatMatchesNone = */                 make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_ll ( String, "aaa", "aab", "aac", "bba", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_ll ( String, "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_ll ( String, "aaa", "aac", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_ll ( String, "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_ll ( String, "aaa", "aab", "aac", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_ll ( String, "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_ll ( String, "aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_ll ( String, "aaa", "aab", "aac", "cca", "ccb", "ccc" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_ll ( String )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : StringHashSet", [this, & allOk]{

        cds :: experimental :: HashSet < String > originalArray = { "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" };

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
                /* equivAfterRemoveThatMatchesNone = */                 make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveThatMatchesOne = */                  make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "cca" ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "cca" ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_hs ( String, "ccc", "aaa", "aac", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveThatMatchesAll = */                  make_hs ( String, "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_hs ( String, "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc" ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca" ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_hs ( String, "ccb", "ccc", "aaa", "aab", "aac", "cca" ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_hs ( String )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : StringToStringHashMap", [this, & allOk]{

        cds :: experimental :: HashMap < String, String > originalArray = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };


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
                /* equivAfterRemoveThatMatchesNone = */                 make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveThatMatchesOne = */                  make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} ),
                /* equivAfterRemoveThatMatchesMoreLessThanLimit = */    make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"cca", "cca"} ),
                /* equivAfterRemoveThatMatchesMoreExact = */            make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"} ),
                /* equivAfterRemoveThatMatchesMoreMoreThanLimit = */    make_hm ( String, String, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveThatMatchesAll = */                  make_hm ( String, String, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveFirstThatMatchesNone = */            make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveFirstThatMatchesOne = */             make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} ),
                /* equivAfterRemoveFirstThatMatchesMore = */            make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveFirstThatMatchesAll = */             make_hm ( String, String, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveLastThatMatchesNone = */             make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveLastThatMatchesOne = */              make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} ),
                /* equivAfterRemoveLastThatMatchesMore = */             make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} ),
                /* equivAfterRemoveLastThatMatchesAll = */              make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"} ),
                /* equivAfterRemoveAllThatMatchesNone = */              make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} ),
                /* equivAfterRemoveAllThatMatchesOne = */               make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} ),
                /* equivAfterRemoveAllThatMatchesMore = */              make_hm ( String, String, {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"} ),
                /* equivAfterRemoveAllThatMatchesAll = */               make_hm ( String, String )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-CPP20 : CTG-00400-RB-CPP20 : StringArrayMemberFunction", [this, & allOk]{

        cds :: experimental :: Array < String > strArray = { "word1", "word2", "", "", "word3", "", "word4", "", "", "","", "word5", "" };

        auto copyForRemoveThat      = strArray;
        auto copyForRemoveFirstThat = strArray;
        auto copyForRemoveLastThat  = strArray;
        auto copyForRemoveAllThat   = strArray;
        cds :: experimental :: Array < String > copyForRemoveAllThatCoverage   = {"word1", "word2", "", "word3", "word4", "word5"};

        cds :: experimental :: Collection < String > & cRT  = copyForRemoveThat;
        cds :: experimental :: Collection < String > & cRFT = copyForRemoveFirstThat;
        cds :: experimental :: Collection < String > & cRLT = copyForRemoveLastThat;
        cds :: experimental :: Collection < String > & cRAT = copyForRemoveAllThat;
        cds :: experimental :: Collection < String > & cRATCoverage = copyForRemoveAllThatCoverage;
        Size removeThatLimit = 5;

        cds :: experimental :: Array < String > expectedAfterRemoveThat         = { "word1", "word2", "word3", "word4", "", "", "word5", "" };
        cds :: experimental :: Array < String > expectedAfterRemoveFirstThat    = { "word1", "word2", "", "word3", "", "word4", "", "", "","", "word5", "" };
        cds :: experimental :: Array < String > expectedAfterRemoveLastThat     = { "word1", "word2", "", "", "word3", "", "word4", "", "", "","", "word5" };
        cds :: experimental :: Array < String > expectedAfterRemoveAllThat      = { "word1", "word2", "word3", "word4", "word5" };
        cds :: experimental :: Array < String > expectedAfterRemoveAllThatCoverage = { "word1", "word2", "word3", "word4", "word5" };

        Size removeThatExpected = 5;
        bool removeFirstThatExpected = true;
        bool removeLastThatExpected = true;
        Size removeAllThatExpected = 8;

        /* CollectionTestCase-RemoveBy-memberRemoveThat-CPP20 : CTC-00419-RB-memberRemoveThat-CPP20 */
        Size removeThatRes = cRT.removeThat ( removeThatLimit, & String :: empty );
        if ( removeThatExpected != removeThatRes || ! cRT.equals ( expectedAfterRemoveThat ) ) {
            this->logError ( "'CTC-00419-RB-memberRemoveThat-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00419-RB-memberRemoveThat-CPP20' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveFirstThat-CPP20 : CTC-00420-RB-memberRemoveFirstThat-CPP20 */
        bool removeFirstThatRes = cRFT.removeFirstThat ( & String :: empty );
        if ( removeFirstThatExpected != removeFirstThatRes || ! cRFT.equals ( expectedAfterRemoveFirstThat ) ) {
            this->logError ( "'CTC-00420-RB-memberRemoveFirstThat-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00420-RB-memberRemoveFirstThat-CPP20' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveLastThat-CPP20 : CTC-00421-RB-memberRemoveLastThat-CPP20 */
        bool removeLastThatRes = cRLT.removeLastThat ( & String :: empty );
        if ( removeLastThatExpected != removeLastThatRes || ! cRLT.equals ( expectedAfterRemoveLastThat ) ) {
            this->logError ( "'CTC-00421-RB-memberRemoveLastThat-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00421-RB-memberRemoveLastThat-CPP20' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveAllThat-CPP20 : CTC-00422-RB-memberRemoveAllThat-CPP20 */
        Size removeAllThatRes = cRAT.removeAllThat ( & String :: empty );
        if ( removeAllThatExpected != removeAllThatRes || ! cRAT.equals ( expectedAfterRemoveAllThat ) ) {
            this->logError ( "'CTC-00422-RB-memberRemoveAllThat-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00422-RB-memberRemoveAllThat-CPP20' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveThatCoverage-CPP20 : CTC-00423-RB-memberRemoveThatCoverage-CPP20 */
        Size removeAllThatCovRes = cRATCoverage.removeAllThat ( & String :: empty );
        if ( 1U != removeAllThatCovRes || ! cRATCoverage.equals ( expectedAfterRemoveAllThatCoverage ) ) {
            this->logError ( "'CTC-00423-RB-memberRemoveThatCoverage-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00423-RB-memberRemoveThatCoverage-CPP20' OK" );
        }

        cds :: experimental :: Collection < String > & extraForNegCoverage = expectedAfterRemoveAllThatCoverage;

        (void) extraForNegCoverage.removeThat (5, & String :: empty);
        (void) extraForNegCoverage.removeFirstThat (& String :: empty);
        (void) extraForNegCoverage.removeLastThat (& String :: empty);
        (void) extraForNegCoverage.removeAllThat (& String :: empty);

        (void) extraForNegCoverage.insert ("");
        (void) extraForNegCoverage.removeThat (5, & String :: empty);

    });


    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : IntArray", [this, & allOk]{

        cds :: experimental :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_a(t, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : IntLinkedList", [this, & allOk]{

        cds :: experimental :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_ll(t, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : IntHashSet", [this, & allOk]{

        cds :: experimental :: HashSet < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_hs(t, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : IntToIntHashMap", [this, & allOk]{

        cds :: experimental :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

#define make(k, v, ...) make_hm(k, v, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < int, int > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, int, {1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < int, int > > :: removeAllOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int, int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int, int )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeFirstOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeLastOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < int, int > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, int, {2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < int, int > > :: removeAllNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int, int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, int, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, int, {3, 3}, {5, 5}, {7, 7} ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeLastNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

#undef make
#define make(k, v, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < int, int > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, int, {1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < int, int > > :: removeAllOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(int, int),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(int, int)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeFirstOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeLastOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < int, int > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(int, int, {2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < int, int > > :: removeAllNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(int, int),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(int, int, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(int, int, {3, 3}, {5, 5}, {7, 7} ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < int, int > > :: removeLastNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

#undef make
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : StringArray", [this, & allOk]{

        cds :: experimental :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_a(t, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : StringLinkedList", [this, & allOk]{

        cds :: experimental :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_ll(t, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : StringHashSet", [this, & allOk]{

        cds :: experimental :: HashSet < String > underTest = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };

        /* due to hash table rules, oredring might be odd */
#define make(t, ...) make_hs(t, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 1, 3, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, 1, 2, 3, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, 1, 2, 3, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 3, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, 6, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 5, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 5, 7, 9, 1, 2, 3 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 5, 7, 9, 1, 2, 3 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 5, 6, 7, 8, 9, 1, 2, 3),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 5, 6, 7, 8, 9, 1, 2, 3),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 5, 6, 7, 8, 9, 1, 2, 3),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 4, 5, 6, 7, 8, 9, 1, 2 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 4, 5, 6, 7, 8, 9, 1, 2),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 4, 5, 6, 7, 8, 9, 1, 3),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, 4, 5, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 4, 6, 7, 8, 9, 1, 2 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 4, 6, 8, 9, 1, 2 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 4, 6, 8, 9, 1, 3 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, 7, 8, 9, 1 ,2, 3 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, 7, 8, 9, 1, 2, 3 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, 4, 5, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, 4, 6, 8, 9, 1, 2 ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 4, 5, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 4, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 5, 6, 7, 8, 9, 1, 2, 3 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 4, 5, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 4, 5, 6, 7, 8, 9, 1, 2 ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, 4, 5, 6, 7, 8, 9, 1, 2 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, 4, 5, 6, 7, 8, 9, 1, 2 )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, 6, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, 5, 8, 9, 1, 2, 3 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, 5, 7, 9, 1, 2, 3 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, 5, 7, 9, 1, 2, 3 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, 5, 7, 3 ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 5, 6, 7, 8, 9, 1, 2, 3),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 5, 6, 7, 8, 9, 1, 2, 3),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 5, 6, 7, 8, 9, 1, 2, 3),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3)
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, 4, 5, 6, 7, 8, 9, 1, 2 ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, 4, 5, 6, 7, 8, 9, 1, 2),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, 4, 5, 6, 7, 8, 9, 1, 3),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 ),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, 4, 5, 6, 7, 8, 9, 1, 2, 3 )
        );

#undef make
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-CPP20 : CTG-00450-RO-CPP20 : StringToStringHashMap", [this, & allOk]{

        cds :: experimental :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

#define make(k, v, ...) make_hm(k, v, __VA_ARGS__)

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < String, String > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, String, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, String, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, String, {1, 1}, {3, 3}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, String, {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, String, {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < String, String > > :: removeAllOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, String, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String, String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String, String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeFirstOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeLastOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "Collection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < String, String > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, String, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, String, {5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < String, String > > :: removeAllNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String, String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, String, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, String, {3, 3}, {5, 5}, {7, 7} ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, String, {1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: experimental :: Collection < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "Collection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeLastNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

#undef make
#define make(k, v, ...) {__VA_ARGS__}

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < String, String > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedCollectionFromNone= */               make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedCollectionFromOne= */                make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, String, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, String, {4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, String, {4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {3, 3} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedCollectionFromAll= */                make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedCollectionFromAllAndMore= */         make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < String, String > > :: removeAllOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */            1U,
                /* expectedCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */           3U,
                /* expectedCollectionFromMore= */       make(String, String, {4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromAll= */            9U,
                /* expectedCollectionFromAll= */        make(String, String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedCollectionFromAllAndMore= */ make(String, String )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeFirstOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeLastOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromAll= */            true,
                /* expectedCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} )
        );

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: experimental :: Collection < MapEntry < String, String > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedCollectionFromNone= */               make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedCollectionFromOne= */                make(String, String, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedCollectionFromMoreLessThanLimit= */  make(String, String, {5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedCollectionFromMore= */               make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedCollectionFromMoreMoreThanLimit= */  make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedCollectionFromAll= */                make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedCollectionFromAllAndMore= */         make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: experimental :: Collection < MapEntry < String, String > > :: removeAllNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedCollectionFromNone= */       make(String, String),
                /* expectedResultFromOne= */            8U,
                /* expectedCollectionFromOne= */        make(String, String, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedCollectionFromMore= */       make(String, String, {5, 5}, {7, 7}, {3, 3} ),
                /* expectedResultFromAll= */            0U,
                /* expectedCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3})
        );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: experimental :: Collection < MapEntry < String, String > > :: removeLastNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromOne= */            true,
                /* expectedCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}),
                /* expectedResultFromMore= */           true,
                /* expectedCollectionFromMore= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

#undef make
    });


    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : IntArray", [this, & allOk] {

        cds :: experimental :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( int x ){ return x == 10000; },
                /* one= */                                      []( int x ){ return x == 4; },
                /* moreLessThanLimit= */                        []( int x ){ return x >= 3 && x <= 5; },
                /* more= */                                     []( int x ){ return x >= 2 && x <= 6; },
                /* moreMoreThanLimit= */                        []( int x ){ return x >= 1 && x <= 3 || x >= 5 && x <= 8; },
                /* all= */                                      []( int x ){ return x >= 1 && x <= 9; },
                /* allAndMore= */                               []( int x ){ return x >= -50 && x <= 100; },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { 4U },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { 3, 4, 5 },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { 2, 3, 4, 5, 6 },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { 1, 2, 3, 5, 6 },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { 1, 2, 3, 4, 5 },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                -1,
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 4,
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                2,
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 1,
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          1,
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 -1,
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  4,
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 6,
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  9,
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           9,
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { 4 },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : IntLinkedList", [this, & allOk] {

        cds :: experimental :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( int x ){ return x == 10000; },
                /* one= */                                      []( int x ){ return x == 4; },
                /* moreLessThanLimit= */                        []( int x ){ return x >= 3 && x <= 5; },
                /* more= */                                     []( int x ){ return x >= 2 && x <= 6; },
                /* moreMoreThanLimit= */                        []( int x ){ return x >= 1 && x <= 3 || x >= 5 && x <= 8; },
                /* all= */                                      []( int x ){ return x >= 1 && x <= 9; },
                /* allAndMore= */                               []( int x ){ return x >= -50 && x <= 100; },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { 4U },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { 3, 4, 5 },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { 2, 3, 4, 5, 6 },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { 1, 2, 3, 5, 6 },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { 1, 2, 3, 4, 5 },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                -1,
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 4,
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                2,
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 1,
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          1,
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 -1,
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  4,
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 6,
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  9,
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           9,
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { 4 },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : IntHashSet", [this, & allOk] {

        cds :: experimental :: HashSet < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( int x ){ return x == 10000; },
                /* one= */                                      []( int x ){ return x == 4; },
                /* moreLessThanLimit= */                        []( int x ){ return x >= 3 && x <= 5; },
                /* more= */                                     []( int x ){ return x >= 2 && x <= 6; },
                /* moreMoreThanLimit= */                        []( int x ){ return x >= 1 && x <= 3 || x >= 5 && x <= 8; },
                /* all= */                                      []( int x ){ return x >= 1 && x <= 9; },
                /* allAndMore= */                               []( int x ){ return x >= -50 && x <= 100; },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { 4U },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { 3, 4, 5 },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { 2, 3, 4, 5, 6 },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { 1, 2, 3, 5, 6 },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { 1, 2, 3, 4, 5 },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                -1,
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 4,
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                2,
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 1,
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          1,
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 -1,
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  4,
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 6,
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  9,
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           9,
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { 4 },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : IntToIntHashMap", [this, & allOk] {

        cds :: experimental :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( MapEntry < int, int > const & x ){ return x.key() == 10000; },
                /* one= */                                      []( MapEntry < int, int > const & x ){ return x.key() == 4; },
                /* moreLessThanLimit= */                        []( MapEntry < int, int > const & x ){ return x.key() >= 3 && x.key() <= 5; },
                /* more= */                                     []( MapEntry < int, int > const & x ){ return x.key() >= 2 && x.key() <= 6; },
                /* moreMoreThanLimit= */                        []( MapEntry < int, int > const & x ){ return x.key() >= 1 && x.key() <= 3 || x.key() >= 5 && x.key() <= 8; },
                /* all= */                                      []( MapEntry < int, int > const & x ){ return x.key() >= 1 && x.key() <= 9; },
                /* allAndMore= */                               []( MapEntry < int, int > const & x ){ return x.key() >= -50 && x.key() <= 100; },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { {4, 4} },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6} },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                {-1, -1},
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 {4, 4},
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                {2, 2},
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 {1, 1},
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          {1, 1},
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 {-1, -1},
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  {4, 4},
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 {6, 6},
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  {9, 9},
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           {9, 9},
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { {4, 4} },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : StringArray", [this, & allOk] {

        cds :: experimental :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat < String > (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( String const & x ){ return x == String(10000); },
                /* one= */                                      []( String const & x ){ return x == String(4); },
                /* moreLessThanLimit= */                        []( String const & x ){ return x >= String(3) && x <= String(5); },
                /* more= */                                     []( String const & x ){ return x >= String(2) && x <= String(6); },
                /* moreMoreThanLimit= */                        []( String const & x ){ return x >= String(1) && x <= String(3) || x >= String(5) && x <= String(8); },
                /* all= */                                      []( String const & x ){ return x >= String(1) && x <= String(9); },
                /* allAndMore= */                               []( String const & x ){ return x >= String(0) && x <= String(9); },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { 4U },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { 3, 4, 5 },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { 2, 3, 4, 5, 6 },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { 1, 2, 3, 5, 6 },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { 1, 2, 3, 4, 5 },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                -1,
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 4,
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                2,
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 1,
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          1,
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 -1,
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  4,
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 6,
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  9,
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           9,
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { 4 },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : StringLinkedList", [this, & allOk] {

        cds :: experimental :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat < String > (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( String const & x ){ return x == String(10000); },
                /* one= */                                      []( String const & x ){ return x == String(4); },
                /* moreLessThanLimit= */                        []( String const & x ){ return x >= String(3) && x <= String(5); },
                /* more= */                                     []( String const & x ){ return x >= String(2) && x <= String(6); },
                /* moreMoreThanLimit= */                        []( String const & x ){ return x >= String(1) && x <= String(3) || x >= String(5) && x <= String(8); },
                /* all= */                                      []( String const & x ){ return x >= String(1) && x <= String(9); },
                /* allAndMore= */                               []( String const & x ){ return x >= String(0) && x <= String(9); },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { 4U },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { 3, 4, 5 },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { 2, 3, 4, 5, 6 },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { 1, 2, 3, 5, 6 },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { 1, 2, 3, 4, 5 },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                -1,
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 4,
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                2,
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 1,
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          1,
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 -1,
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  4,
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 6,
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  9,
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           9,
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { 4 },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : StringHashSet", [this, & allOk] {

        cds :: experimental :: HashSet < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat < String > (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( String const & x ){ return x == String(10000); },
                /* one= */                                      []( String const & x ){ return x == String(4); },
                /* moreLessThanLimit= */                        []( String const & x ){ return x >= String(3) && x <= String(5); },
                /* more= */                                     []( String const & x ){ return x >= String(2) && x <= String(6); },
                /* moreMoreThanLimit= */                        []( String const & x ){ return x >= String(1) && x <= String(3) || x >= String(5) && x <= String(8); },
                /* all= */                                      []( String const & x ){ return x >= String(1) && x <= String(9); },
                /* allAndMore= */                               []( String const & x ){ return x >= String(0) && x <= String(9); },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { 4 },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { 4, 5, 3 },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { 4, 5, 6, 2, 3 },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { 5, 6, 7, 8, 1 },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { 4, 5, 6, 7, 8 },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { 4, 5, 6, 7, 8 },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                -1,
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 4,
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                4,
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 4,
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          4,
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 -1,
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  4,
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 3,
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  3,
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           3,
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { 4 },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { 4, 5, 6, 2, 3 },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { 4, 5, 6, 7, 8, 9, 1, 2, 3 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-CPP20 : CTG-00600-FT-CPP20 : StringToStringHashMap", [this, & allOk] {

        cds :: experimental :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat < MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     []( MapEntry < String, String > const & x ){ return x.key() == String(10000); },
                /* one= */                                      []( MapEntry < String, String > const & x ){ return x.key() == String(4); },
                /* moreLessThanLimit= */                        []( MapEntry < String, String > const & x ){ return x.key() >= String(3) && x.key() <= String(5); },
                /* more= */                                     []( MapEntry < String, String > const & x ){ return x.key() >= String(2) && x.key() <= String(6); },
                /* moreMoreThanLimit= */                        []( MapEntry < String, String > const & x ){ return x.key() >= String(1) && x.key() <= String(3) || x.key() >= String(5) && x.key() <= String(8); },
                /* all= */                                      []( MapEntry < String, String > const & x ){ return x.key() >= String(1) && x.key() <= String(9); },
                /* allAndMore= */                               []( MapEntry < String, String > const & x ){ return x.key() >= String(0) && x.key() <= String(9); },
                /* expectedSizeFindThatNone= */                 0U,
                /* expectedFindThatNone= */                     {},
                /* expectedSizeFindThatOne= */                  1U,
                /* expectedFindThatOne= */                      { {4, 4} },
                /* expectedSizeFindThatMoreLessThanLimit= */    3U,
                /* expectedFindThatMoreLessThanLimit= */        { {4, 4}, {5, 5}, {3, 3} },
                /* expectedSizeFindThatMore= */                 5U,
                /* expectedFindThatMore= */                     { {4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3} },
                /* expectedSizeFindThatMoreMoreThanLimit= */    5U,
                /* expectedFindThatMoreMoreThanLimit= */        { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1} },
                /* expectedSizeFindThatAll= */                  5U,
                /* expectedFindThatAll= */                      { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedSizeFindThatAllAndMore= */           5U,
                /* expectedFindThatAllAndMore= */               { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedResultFindFirstThatNone= */          false,
                /* expectedFindFirstThatNone= */                {-1, -1},
                /* expectedResultFindFirstThatOne= */           true,
                /* expectedFindFirstThatOne= */                 {4, 4},
                /* expectedResultFindFirstThatMore= */          true,
                /* expectedFindFirstThatMore= */                {4, 4},
                /* expectedResultFindFirstThatAll= */           true,
                /* expectedFindFirstThatAll= */                 {4, 4},
                /* expectedResultFindFirstThatAllAndMore= */    true,
                /* expectedFindFirstThatAllAndMore= */          {4, 4},
                /* expectedResultFindLastThatNone= */           false,
                /* expectedFindLastThatNone= */                 {-1, -1},
                /* expectedResultFindLastThatOne= */            true,
                /* expectedFindLastThatOne= */                  {4, 4},
                /* expectedResultFindLastThatMore= */           true,
                /* expectedFindLastThatMore= */                 {3, 3},
                /* expectedResultFindLastThatAll= */            true,
                /* expectedFindLastThatAll= */                  {3, 3},
                /* expectedResultFindLastThatAllAndMore= */     true,
                /* expectedFindLastThatAllAndMore= */           {3, 3},
                /* expectedSizeFindAllThatNone= */              0U,
                /* expectedFindAllThatNone= */                  {},
                /* expectedSizeFindAllThatOne= */               1U,
                /* expectedFindAllThatOne= */                   { {4, 4} },
                /* expectedSizeFindAllThatMore= */              5U,
                /* expectedFindAllThatMore= */                  { {4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllThatAll= */               9U,
                /* expectedFindAllThatAll= */                   { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllThatAllAndMore= */        9U,
                /* expectedFindAllThatAllAndMore= */            { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThatMemberFunction-CPP20 : CTG-00650-FTMF-CPP20 : StringArray", [this, & allOk] {

        /* CollectionTestGroup-FindThatMemberFunction-CPP20 : CTG-00650-FTMF-CPP20 : CTC-00651-FTMF to CTC-00656-FTMF */

        cds :: experimental :: Array < String > arr = { "word1", "", "word2", "", "word3", "word4", "", "word5" };
        cds :: experimental :: Collection < String > const & underTest = arr;
        using ConstIterator = cds :: experimental :: Collection < String > :: ConstIterator;

        /* CollectionTestCase-FindThatMemberFunction-findThatStoreInMemberFunction-CPP20 : CTC-00651-FTMF-findThatStoreInMemberFunction-CPP20 */
        cds :: experimental :: Array < ConstIterator > storeIn651;
        underTest.findThat ( 2, storeIn651, & String :: empty );

        if ( storeIn651.size() != 2 || * ( ++ storeIn651[0] ) != "word2" || * ( ++ storeIn651[1] ) != "word3" ) {
            this->logError( "'CTC-00651-FTMF-findThatStoreInMemberFunction-CPP20' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00651-FTMF-findThatStoreInMemberFunction-CPP20' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findThatReturnedMemberFunction-CPP20 : CTC-00652-FTMF-findThatReturnedMemberFunction-CPP20 */
        cds :: experimental :: Array < ConstIterator > storeIn652;
        storeIn652 = underTest.findThat < cds :: experimental :: Array > ( 2, & String :: empty );

        if ( storeIn652.size() != 2 || * ( ++ storeIn652[0] ) != "word2" || * ( ++ storeIn652[1] ) != "word3" ) {
            this->logError( "'CTC-00652-FTMF-findThatReturnedMemberFunction-CPP20' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00652-FTMF-findThatReturnedMemberFunction-CPP20' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findFirstThatMemberFunction-CPP20 : CTC-00653-FTMF-findFirstThatMemberFunction-CPP20 */
        ConstIterator res653;
        res653 = underTest.findFirstThat ( & String :: empty );

        if ( ! res653.valid() || * ( ++ res653 ) != "word2" ) {
            this->logError( "'CTC-00653-FTMF-findFirstThatMemberFunction-CPP20' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00653-FTMF-findFirstThatMemberFunction-CPP20' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findLastThatMemberFunction-CPP20 : CTC-00654-FTMF-findLastThatMemberFunction-CPP20 */
        ConstIterator res654;
        res654 = underTest.findLastThat ( & String :: empty );

        if ( ! res654.valid() || * ( ++ res654 ) != "word5" ) {
            this->logError( "'CTC-00654-FTMF-findLastThatMemberFunction-CPP20' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00654-FTMF-findLastThatMemberFunction-CPP20' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findAllThatStoreInMemberFunction-CPP20 : CTC-00655-FTMF-findAllThatStoreInMemberFunction-CPP20 */
        cds :: experimental :: Array < ConstIterator > storeIn655;
        underTest.findAllThat ( storeIn655, & String :: empty );

        if ( storeIn655.size() != 3 || * ( ++ storeIn655[0] ) != "word2" || * ( ++ storeIn655[1] ) != "word3" || * ( ++ storeIn655 [2] ) != "word5" ) {
            this->logError( "'CTC-00655-FTMF-findAllThatStoreInMemberFunction-CPP20' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00655-FTMF-findAllThatStoreInMemberFunction-CPP20' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findAllThatReturnedMemberFunction-CPP20 : CTC-00656-FTMF-findAllThatReturnedMemberFunction-CPP20 */
        cds :: experimental :: Array < ConstIterator > storeIn656;
        storeIn656 = underTest.findAllThat < cds :: experimental :: Array > ( & String :: empty );

        if ( storeIn656.size() != 3 || * ( ++ storeIn656[0] ) != "word2" || * ( ++ storeIn656[1] ) != "word3" || * ( ++ storeIn656 [2] ) != "word5" ) {
            this->logError( "'CTC-00656-FTMF-findAllThatReturnedMemberFunction-CPP20' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00656-FTMF-findAllThatReturnedMemberFunction-CPP20' OK" );
        }
    });


    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : IntArray", [this, & allOk] {

        cds :: experimental :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_a(int, -1, -4, -7, 20),
                /* one= */                                      make_a(int, -9, -8, -7, -6, -5, 4, -3, -2, -1),
                /* moreLessThanLimit= */                        make_a(int, -9, -8, -7, -6, 5, 4, 3, -2, -1),
                /* more= */                                     make_a(int, -9, -8, -7, 6, 5, 4, 3, 2, -1),
                /* moreMoreThanLimit= */                        make_a(int, -9, 8, 7, 6, 5, -4, 3, 2, 1),
                /* all= */                                      make_a(int, 9, 8, 7, 6, 5, 4, 3, 2, 1),
                /* allAndMore= */                               make_a(int, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { -1, -4, -7, 20 },
                /* one= */                                      { -9, -8, -7, -6, -5, 4, -3, -2, -1 },
                /* moreLessThanLimit= */                        { -9, -8, -7, -6, 5, 4, 3, -2, -1 },
                /* more= */                                     { -9, -8, -7, 6, 5, 4, 3, 2, -1 },
                /* moreMoreThanLimit= */                        { -9, 8, 7, 6, 5, -4, 3, 2, 1 },
                /* all= */                                      { 9, 8, 7, 6, 5, 4, 3, 2, 1 },
                /* allAndMore= */                               { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20 },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : IntLinkedList", [this, & allOk] {

        cds :: experimental :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_ll(int, -1, -4, -7, 20),
                /* one= */                                      make_ll(int, -9, -8, -7, -6, -5, 4, -3, -2, -1),
                /* moreLessThanLimit= */                        make_ll(int, -9, -8, -7, -6, 5, 4, 3, -2, -1),
                /* more= */                                     make_ll(int, -9, -8, -7, 6, 5, 4, 3, 2, -1),
                /* moreMoreThanLimit= */                        make_ll(int, -9, 8, 7, 6, 5, -4, 3, 2, 1),
                /* all= */                                      make_ll(int, 9, 8, 7, 6, 5, 4, 3, 2, 1),
                /* allAndMore= */                               make_ll(int, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { -1, -4, -7, 20 },
                /* one= */                                      { -9, -8, -7, -6, -5, 4, -3, -2, -1 },
                /* moreLessThanLimit= */                        { -9, -8, -7, -6, 5, 4, 3, -2, -1 },
                /* more= */                                     { -9, -8, -7, 6, 5, 4, 3, 2, -1 },
                /* moreMoreThanLimit= */                        { -9, 8, 7, 6, 5, -4, 3, 2, 1 },
                /* all= */                                      { 9, 8, 7, 6, 5, 4, 3, 2, 1 },
                /* allAndMore= */                               { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20 },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : IntHashSet", [this, & allOk] {

        cds :: experimental :: HashSet < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_hs(int, -1, -4, -7, 20),
                /* one= */                                      make_hs(int, -9, -8, -7, -6, -5, 4, -3, -2, -1),
                /* moreLessThanLimit= */                        make_hs(int, -9, -8, -7, -6, 5, 4, 3, -2, -1),
                /* more= */                                     make_hs(int, -9, -8, -7, 6, 5, 4, 3, 2, -1),
                /* moreMoreThanLimit= */                        make_hs(int, -9, 8, 7, 6, 5, -4, 3, 2, 1),
                /* all= */                                      make_hs(int, 9, 8, 7, 6, 5, 4, 3, 2, 1),
                /* allAndMore= */                               make_hs(int, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { -1, -4, -7, 20 },
                /* one= */                                      { -9, -8, -7, -6, -5, 4, -3, -2, -1 },
                /* moreLessThanLimit= */                        { -9, -8, -7, -6, 5, 4, 3, -2, -1 },
                /* more= */                                     { -9, -8, -7, 6, 5, 4, 3, 2, -1 },
                /* moreMoreThanLimit= */                        { -9, 8, 7, 6, 5, -4, 3, 2, 1 },
                /* all= */                                      { 9, 8, 7, 6, 5, 4, 3, 2, 1 },
                /* allAndMore= */                               { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20 },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : IntToIntHashMap", [this, & allOk] {

        cds :: experimental :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < MapEntry < int, int > > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_hm(int, int, {-1, -1}, {-4, -4}, {-7, -7}, {20, 20}),
                /* one= */                                      make_hm(int, int, {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {4, 4}, {-3, -3}, {-2, -2}, {-1, -1}),
                /* moreLessThanLimit= */                        make_hm(int, int, {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {5, 5}, {4, 4}, {3, 3}, {-2, -2}, {-1, -1}),
                /* more= */                                     make_hm(int, int, {-9, -9}, {-8, -8}, {-7, -7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {-1, -1}),
                /* moreMoreThanLimit= */                        make_hm(int, int, {-9, -9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {-4, -4}, {3, 3}, {2, 2}, {1, 1}),
                /* all= */                                      make_hm(int, int, {9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}),
                /* allAndMore= */                               make_hm(int, int, {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {-4, -4}, {-3, -3}, {-2, -2}, {-1, -1}, {0, 0}, {1, 1}, {2, 2}, {3, 3},
                                                                        {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { {4, 4} },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6} },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  {-1, -1},
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   {4, 4},
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  {2, 2},
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   {1, 1},
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            {1, 1},
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   {-1, -1},
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    {4, 4},
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   {6, 6},
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    {9, 9},
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             {9, 9},
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { {4, 4} },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6} },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { {1, 1}, {2, 2}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { {1, 1}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { {4, 4}, {9, 9} },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               {1, 1},
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                {1, 1},
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               {1, 1},
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                {-1, -1},
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         {-1, -1},
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                {9, 9},
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 {9, 9},
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                {9, 9},
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 {-1, -1},
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          {-1, -1},
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { {1, 1}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry < int, int > > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { {-1, -1}, {-4, -4}, {-7, -7}, {20, 20} },
                /* one= */                                      { {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {4, 4}, {-3, -3}, {-2, -2}, {-1, -1} },
                /* moreLessThanLimit= */                        { {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {5, 5}, {4, 4}, {3, 3}, {-2, -2}, {-1, -1} },
                /* more= */                                     { {-9, -9}, {-8, -8}, {-7, -7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {-1, -1} },
                /* moreMoreThanLimit= */                        { {-9, -9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {-4, -4}, {3, 3}, {2, 2}, {1, 1} },
                /* all= */                                      { {9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1} },
                /* allAndMore= */                               { {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {-4, -4}, {-3, -3}, {-2, -2}, {-1, -1}, {0, 0}, {1, 1}, {2, 2}, {3, 3},
                                                                        {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20} },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { {4, 4} },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6} },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  {-1, -1},
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   {4, 4},
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  {2, 2},
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   {1, 1},
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            {1, 1},
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   {-1, -1},
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    {4, 4},
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   {6, 6},
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    {9, 9},
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             {9, 9},
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { {4, 4} },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6} },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { {1, 1}, {2, 2}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { {1, 1}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { {4, 4}, {9, 9} },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               {1, 1},
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                {1, 1},
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               {1, 1},
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                {-1, -1},
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         {-1, -1},
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                {9, 9},
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 {9, 9},
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                {9, 9},
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 {-1, -1},
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          {-1, -1},
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { {1, 1}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : StringArray", [this, & allOk] {

        cds :: experimental :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_a(String, -1, -4, -7, 20),
                /* one= */                                      make_a(String, -9, -8, -7, -6, -5, 4, -3, -2, -1),
                /* moreLessThanLimit= */                        make_a(String, -9, -8, -7, -6, 5, 4, 3, -2, -1),
                /* more= */                                     make_a(String, -9, -8, -7, 6, 5, 4, 3, 2, -1),
                /* moreMoreThanLimit= */                        make_a(String, -9, 8, 7, 6, 5, -4, 3, 2, 1),
                /* all= */                                      make_a(String, 9, 8, 7, 6, 5, 4, 3, 2, 1),
                /* allAndMore= */                               make_a(String, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { -1, -4, -7, 20 },
                /* one= */                                      { -9, -8, -7, -6, -5, 4, -3, -2, -1 },
                /* moreLessThanLimit= */                        { -9, -8, -7, -6, 5, 4, 3, -2, -1 },
                /* more= */                                     { -9, -8, -7, 6, 5, 4, 3, 2, -1 },
                /* moreMoreThanLimit= */                        { -9, 8, 7, 6, 5, -4, 3, 2, 1 },
                /* all= */                                      { 9, 8, 7, 6, 5, 4, 3, 2, 1 },
                /* allAndMore= */                               { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20 },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : StringLinkedList", [this, & allOk] {

        cds :: experimental :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_ll(String, -1, -4, -7, 20),
                /* one= */                                      make_ll(String, -9, -8, -7, -6, -5, 4, -3, -2, -1),
                /* moreLessThanLimit= */                        make_ll(String, -9, -8, -7, -6, 5, 4, 3, -2, -1),
                /* more= */                                     make_ll(String, -9, -8, -7, 6, 5, 4, 3, 2, -1),
                /* moreMoreThanLimit= */                        make_ll(String, -9, 8, 7, 6, 5, -4, 3, 2, 1),
                /* all= */                                      make_ll(String, 9, 8, 7, 6, 5, 4, 3, 2, 1),
                /* allAndMore= */                               make_ll(String, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { -1, -4, -7, 20 },
                /* one= */                                      { -9, -8, -7, -6, -5, 4, -3, -2, -1 },
                /* moreLessThanLimit= */                        { -9, -8, -7, -6, 5, 4, 3, -2, -1 },
                /* more= */                                     { -9, -8, -7, 6, 5, 4, 3, 2, -1 },
                /* moreMoreThanLimit= */                        { -9, 8, 7, 6, 5, -4, 3, 2, 1 },
                /* all= */                                      { 9, 8, 7, 6, 5, 4, 3, 2, 1 },
                /* allAndMore= */                               { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20 },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 3, 4, 5 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 2, 3, 4, 5, 6 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 1, 2, 3, 5, 6 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 1, 2, 3, 4, 5 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 1, 2, 3, 4, 5 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  2,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   1,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            1,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   6,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    9,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             9,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 2, 3, 4, 5, 6 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 1, 2, 3, 4, 5, 6, 7, 8, 9 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 1, 2, 3, 4, 5 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 1, 2, 3, 5, 6 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 1, 2, 6, 7, 8 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 1, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               1,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                1,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               1,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                9,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 9,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                9,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 1, 2, 3, 5, 6, 7, 8, 9 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 1, 7, 8, 9 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : StringHashSet", [this, & allOk] {

        cds :: experimental :: HashSet < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_hs(String, -1, -4, -7, 20),
                /* one= */                                      make_hs(String, -9, -8, -7, -6, -5, 4, -3, -2, -1),
                /* moreLessThanLimit= */                        make_hs(String, -9, -8, -7, -6, 5, 4, 3, -2, -1),
                /* more= */                                     make_hs(String, -9, -8, -7, 6, 5, 4, 3, 2, -1),
                /* moreMoreThanLimit= */                        make_hs(String, -9, 8, 7, 6, 5, -4, 3, 2, 1),
                /* all= */                                      make_hs(String, 9, 8, 7, 6, 5, 4, 3, 2, 1),
                /* allAndMore= */                               make_hs(String, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 4, 5, 3 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 4, 5, 6, 2, 3 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 5, 6, 7, 8, 1 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 4, 5, 6, 7, 8 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 4, 5, 6, 7, 8 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  4,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   4,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            4,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   3,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    3,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             3,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 4, 5, 6, 2, 3 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 4, 5, 6, 7, 8, 9, 1, 2, 3 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 4, 5, 6, 7, 8 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 5, 6, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 6, 7, 8, 9, 1 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 7, 8, 9, 1 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               4,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                5,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               7,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                3,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 3,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                1,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 5, 6, 7, 8, 9, 1, 2, 3 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 7, 8, 9, 1 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { -1, -4, -7, 20 },
                /* one= */                                      { -9, -8, -7, -6, -5, 4, -3, -2, -1 },
                /* moreLessThanLimit= */                        { -9, -8, -7, -6, 5, 4, 3, -2, -1 },
                /* more= */                                     { -9, -8, -7, 6, 5, 4, 3, 2, -1 },
                /* moreMoreThanLimit= */                        { -9, 8, 7, 6, 5, -4, 3, 2, 1 },
                /* all= */                                      { 9, 8, 7, 6, 5, 4, 3, 2, 1 },
                /* allAndMore= */                               { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20 },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { 4U },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { 4, 5, 3 },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { 4, 5, 6, 2, 3 },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { 5, 6, 7, 8, 1 },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { 4, 5, 6, 7, 8 },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { 4, 5, 6, 7, 8 },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  -1,
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   4,
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  4,
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   4,
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            4,
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   -1,
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    4,
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   3,
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    3,
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             3,
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { 4 },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { 4, 5, 6, 2, 3 },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { 4, 5, 6, 7, 8, 9, 1, 2, 3 },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { 4, 5, 6, 7, 8 },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { 5, 6, 7, 8, 9 },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { 6, 7, 8, 9, 1 },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { 7, 8, 9, 1 },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { 4, 9 },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               4,
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                5,
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               7,
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                -1,
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         -1,
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                3,
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 3,
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                1,
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 -1,
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          -1,
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { 5, 6, 7, 8, 9, 1, 2, 3 },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { 7, 8, 9, 1 },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-CPP20 : CTG-00700-FO-CPP20 : StringToStringHashMap", [this, & allOk] {

        cds :: experimental :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindOf < cds :: experimental :: Collection < MapEntry < String, String > > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "Collection",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     make_hm(String, String, {-1, -1}, {-4, -4}, {-7, -7}, {20, 20}),
                /* one= */                                      make_hm(String, String, {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {4, 4}, {-3, -3}, {-2, -2}, {-1, -1}),
                /* moreLessThanLimit= */                        make_hm(String, String, {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {5, 5}, {4, 4}, {3, 3}, {-2, -2}, {-1, -1}),
                /* more= */                                     make_hm(String, String, {-9, -9}, {-8, -8}, {-7, -7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {-1, -1}),
                /* moreMoreThanLimit= */                        make_hm(String, String, {-9, -9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {-4, -4}, {3, 3}, {2, 2}, {1, 1}),
                /* all= */                                      make_hm(String, String, {9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}),
                /* allAndMore= */                               make_hm(String, String, {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {-4, -4}, {-3, -3}, {-2, -2}, {-1, -1}, {0, 0}, {1, 1}, {2, 2}, {3, 3},
                                                                        {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}),
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { {4, 4} },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { {4, 4}, {5, 5}, {3, 3} },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { {4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3} },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1} },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  {-1, -1},
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   {4, 4},
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  {4, 4},
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   {4, 4},
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            {4, 4},
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   {-1, -1},
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    {4, 4},
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   {3, 3},
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    {3, 3},
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             {3, 3},
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { {4, 4} },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { {4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1} },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { {7, 7}, {8, 8}, {9, 9}, {1, 1} },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { {4, 4}, {9, 9} },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               {4, 4},
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                {5, 5},
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               {7, 7},
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                {-1, -1},
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         {-1, -1},
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                {3, 3},
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 {3, 3},
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                {1, 1},
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 {-1, -1},
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          {-1, -1},
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { {7, 7}, {8, 8}, {9, 9}, {1, 1} },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry < String, String > > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "InitializerList",
                /* underTest= */                                underTest,
                /* limit= */                                    5U,
                /* none= */                                     { {-1, -1}, {-4, -4}, {-7, -7}, {20, 20} },
                /* one= */                                      { {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {4, 4}, {-3, -3}, {-2, -2}, {-1, -1} },
                /* moreLessThanLimit= */                        { {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {5, 5}, {4, 4}, {3, 3}, {-2, -2}, {-1, -1} },
                /* more= */                                     { {-9, -9}, {-8, -8}, {-7, -7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {-1, -1} },
                /* moreMoreThanLimit= */                        { {-9, -9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {-4, -4}, {3, 3}, {2, 2}, {1, 1} },
                /* all= */                                      { {9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1} },
                /* allAndMore= */                               { {-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {-4, -4}, {-3, -3}, {-2, -2}, {-1, -1}, {0, 0}, {1, 1}, {2, 2}, {3, 3},
                                                                        {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20} },
                /* expectedSizeFindOfNone= */                   0U,
                /* expectedFindOfNone= */                       {},
                /* expectedSizeFindOfOne= */                    1U,
                /* expectedFindOfOne= */                        { {4, 4} },
                /* expectedSizeFindOfMoreLessThanLimit= */      3U,
                /* expectedFindOfMoreLessThanLimit= */          { {4, 4}, {5, 5}, {3, 3} },
                /* expectedSizeFindOfMore= */                   5U,
                /* expectedFindOfMore= */                       { {4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3} },
                /* expectedSizeFindOfMoreMoreThanLimit= */      5U,
                /* expectedFindOfMoreMoreThanLimit= */          { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1} },
                /* expectedSizeFindOfAll= */                    5U,
                /* expectedFindOfAll= */                        { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedSizeFindOfAllAndMore= */             5U,
                /* expectedFindOfAllAndMore= */                 { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedResultFindFirstOfNone= */            false,
                /* expectedFindFirstOfNone= */                  {-1, -1},
                /* expectedResultFindFirstOfOne= */             true,
                /* expectedFindFirstOfOne= */                   {4, 4},
                /* expectedResultFindFirstOfMore= */            true,
                /* expectedFindFirstOfMore= */                  {4, 4},
                /* expectedResultFindFirstOfAll= */             true,
                /* expectedFindFirstOfAll= */                   {4, 4},
                /* expectedResultFindFirstOfAllAndMore= */      true,
                /* expectedFindFirstOfAllAndMore= */            {4, 4},
                /* expectedResultFindLastOfNone= */             false,
                /* expectedFindLastOfNone= */                   {-1, -1},
                /* expectedResultFindLastOfOne= */              true,
                /* expectedFindLastOfOne= */                    {4, 4},
                /* expectedResultFindLastOfMore= */             true,
                /* expectedFindLastOfMore= */                   {3, 3},
                /* expectedResultFindLastOfAll= */              true,
                /* expectedFindLastOfAll= */                    {3, 3},
                /* expectedResultFindLastOfAllAndMore= */       true,
                /* expectedFindLastOfAllAndMore= */             {3, 3},
                /* expectedSizeFindAllOfNone= */                0U,
                /* expectedFindAllOfNone= */                    {},
                /* expectedSizeFindAllOfOne= */                 1U,
                /* expectedFindAllOfOne= */                     { {4, 4} },
                /* expectedSizeFindAllOfMore= */                5U,
                /* expectedFindAllOfMore= */                    { {4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllOfAll= */                 9U,
                /* expectedFindAllOfAll= */                     { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllOfAllAndMore= */          9U,
                /* expectedFindAllOfAllAndMore= */              { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },

                /* expectedSizeFindNotOfNone= */                5U,
                /* expectedFindNotOfNone= */                    { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedSizeFindNotOfOne= */                 5U,
                /* expectedFindNotOfOne= */                     { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedSizeFindNotOfMoreLessThanLimit= */   5U,
                /* expectedFindNotOfMoreLessThanLimit= */       { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1} },
                /* expectedSizeFindNotOfMore= */                4U,
                /* expectedFindNotOfMore= */                    { {7, 7}, {8, 8}, {9, 9}, {1, 1} },
                /* expectedSizeFindNotOfMoreMoreThanLimit= */   2U,
                /* expectedFindNotOfMoreMoreThanLimit= */       { {4, 4}, {9, 9} },
                /* expectedSizeFindNotOfAll= */                 0U,
                /* expectedFindNotOfAll= */                     {},
                /* expectedSizeFindNotOfAllAndMore= */          0U,
                /* expectedFindNotOfAllAndMore= */              {},
                /* expectedResultFindFirstNotOfNone= */         true,
                /* expectedFindFirstNotOfNone= */               {4, 4},
                /* expectedResultFindFirstNotOfOne= */          true,
                /* expectedFindFirstNotOfOne= */                {5, 5},
                /* expectedResultFindFirstNotOfMore= */         true,
                /* expectedFindFirstNotOfMore= */               {7, 7},
                /* expectedResultFindFirstNotOfAll= */          false,
                /* expectedFindFirstNotOfAll= */                {-1, -1},
                /* expectedResultFindFirstNotOfAllAndMore= */   false,
                /* expectedFindFirstNotOfAllAndMore= */         {-1, -1},
                /* expectedResultFindLastNotOfNone= */          true,
                /* expectedFindLastNotOfNone= */                {3, 3},
                /* expectedResultFindLastNotOfOne= */           true,
                /* expectedFindLastNotOfOne= */                 {3, 3},
                /* expectedResultFindLastNotOfMore= */          true,
                /* expectedFindLastNotOfMore= */                {1, 1},
                /* expectedResultFindLastNotOfAll= */           false,
                /* expectedFindLastNotOfAll= */                 {-1, -1},
                /* expectedResultFindLastNotOfAllAndMore= */    false,
                /* expectedFindLastNotOfAllAndMore= */          {-1, -1},
                /* expectedSizeFindAllNotOfNone= */             9U,
                /* expectedFindAllNotOfNone= */                 { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllNotOfOne= */              8U,
                /* expectedFindAllNotOfOne= */                  { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedSizeFindAllNotOfMore= */             4U,
                /* expectedFindAllNotOfMore= */                 { {7, 7}, {8, 8}, {9, 9}, {1, 1} },
                /* expectedSizeFindAllNotOfAll= */              0U,
                /* expectedFindAllNotOfAll= */                  {},
                /* expectedSizeFindAllNotOfAllAndMore= */       0U,
                /* expectedFindAllNotOfAllAndMore= */           {}
        );
    });

    return allOk;
}
