//
// Created by loghin on 04/09/22.
//

#include "MutableCollectionTest.h"

#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/HashMap>

#include <CDS/Range>
#include <vector>
#include <array>

/* MutableCollectionTestGroup-MemberFunctions-cpp-xx : MCTG-00002-MF-cpp-xx. Tests MCTC-00003 to MCTC-00004 */
template <
        typename __MemberType /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupMemberFunctions (
        cds :: MutableCollection < __MemberType >        & collection,
        Test                                                             * pTestLib,
        String                                                     const & expectedToString
) -> bool {

    pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );


    /* MutableCollectionTestGroup-MemberFunctions-toString-cpp-xx : MCTC-00003-MF-toString-cpp-xx */
    auto asString = collection.toString();
    pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
    if ( asString != expectedToString ) {
        pTestLib->logError ( "'MCTC-00003-MF-toString-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00003-MF-toString-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestGroup-MemberFunctions-clear-cpp-xx : MCTC-00004-MF-clear-cpp-xx */
    collection.clear();

    asString                    = collection.toString();

    pTestLib->log ( "Object Cleared using 'clear'. Re-execution after clear : " );
    pTestLib->log ( "object 'toString' : '%s'. potential expected 'toString' : '%s'", asString.cStr(), "[]" );

    if ( asString.length() > 2ULL ) {
        pTestLib->logError( "'MCTC-00004-MF-clear-cpp-xx - toString' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00004-MF-clear-" __CDS_cpplang_core_version_name "' OK" );
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
) -> bool {

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

/* MutableCollectionTestGroup-DelegateForwardIterableClientImports-cpp-xx : MCTG-00050-IT-cpp-xx. Tests MCTC-00051 to MCTC-00056 */
template <
        typename __MemberType,                              /* NOLINT(bugprone-reserved-identifier) */
        typename ... __OrderedValues                        /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupDelegateForwardIterableClientImports (
        MutableCollection < __MemberType > & collection,
        Test                  *     pTestLib,
        bool                        mutabilityTestExecute,
        __MemberType    const &     mutabilityTestValue,
        __MemberType    const &     mutabilityTestValue2,
        __OrderedValues const & ... orderedValues
) -> bool {

    pTestLib->log ( "Object under test, to be iterated : '%s'", collection.toString().cStr() );

    /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-range-cpp-xx : MCTC-00051-IT-range-cpp-xx */
    pTestLib->log ( "Standard iteration : " );
    for ( auto & e : collection ) {
        std :: stringstream oss;
        cds :: streamPrint ( oss, e );
        pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
    }

    /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-begin_endIteration-cpp-xx : MCTC-00052-IT-begin_end-cpp-xx */
    auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
    if ( ! stdIterResult ) {
        pTestLib->logError( "'MCTC-00052-IT-begin_end-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00052-IT-begin_end-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-begin_endIteration-cpp-xx : MCTC-00053-IT-begin_end-cpp-xx */
    auto stdCIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
    if ( ! stdCIterResult ) {
        pTestLib->logError( "'MCTC-00053-IT-begin_end-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00053-IT-begin_end-" __CDS_cpplang_core_version_name "' OK" );
    }

    if ( mutabilityTestExecute ) {
        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-mutabilityRange-cpp-xx : MCTC-00058-IT-mutabilityRange-cpp-xx */
        for ( auto & e : collection ) {
            e = mutabilityTestValue;
        }

        if ( collection.any ( [& mutabilityTestValue](__MemberType const & e) { return e != mutabilityTestValue; } ) ) {
            pTestLib->logError ( "'MCTC-00058-IT-mutabilityRange-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00058-IT-mutabilityRange-" __CDS_cpplang_core_version_name "' OK" );
        };

        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-mutabilityIteration-cpp-xx : MCTC-00059-IT-mutabilityIteration-cpp-xx */
        for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
            * it = mutabilityTestValue2;
        }

        if ( collection.any ( [& mutabilityTestValue2](__MemberType const & e) { return e != mutabilityTestValue2; } ) ) {
            pTestLib->logError ( "'MCTC-00059-IT-mutabilityIteration-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00059-IT-mutabilityIteration-" __CDS_cpplang_core_version_name "' OK" );
        };
    }


    collection.clear();

    /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-emptybegin_end-cpp-xx : MCTC-00054-IT-e_begin_end-cpp-xx */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'MCTC-00054-IT-e_begin_end-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }

    pTestLib->logOK ( "'MCTC-00054-IT-e_begin_end-" __CDS_cpplang_core_version_name "' OK" );

    /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-emptybegin_end-cpp-xx : MCTC-00055-IT-e_begin_end-cpp-xx */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'MCTC-00055-IT-e_begin_end-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }

    pTestLib->logOK ( "'MCTC-00055-IT-e_begin_end-" __CDS_cpplang_core_version_name "' OK" );

    /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-e_emptyRange-cpp-xx : MCTC-00056-IT-e_emptyRange-cpp-xx */
    for ( auto & e : collection ) {
        pTestLib->logError( "'MCTC-00056-IT-e_emptyRange-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }

    pTestLib->logOK ( "'MCTC-00056-IT-e_emptyRange-" __CDS_cpplang_core_version_name "' OK" );

    return true;
}

template <
        typename __PredicateReturnType, /* NOLINT(bugprone-reserved-identifier) */
        typename __MemberType,          /* NOLINT(bugprone-reserved-identifier) */
        typename __Predicate            /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestCasePredicateHandle (
        StringLiteral testCaseName,
        MutableCollection < __MemberType > const & collection,
        Test                                              * pTestLib,
        auto ( MutableCollection < __MemberType > :: * pFunctionalCall ) ( __Predicate const & ) const -> __PredicateReturnType,
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
> auto mutableCollectionTestCasePredicateCountedHandle (
        StringLiteral testCaseName,
        MutableCollection < __MemberType > const & collection,
        Test                                              * pTestLib,
        auto ( MutableCollection < __MemberType > :: * pFunctionalCall ) ( Size, __Predicate const & ) const -> __PredicateReturnType,
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

/* MutableCollectionTestGroup-RemoveAbsIt-cpp-xx : MCTG-00350-RAIT-cpp-xx. MCTC-00351-RAIT to MCTC-00356-RAIT */
template <
        typename __MemberType  /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupRemoveAbstractIterator (
        cds :: MutableCollection < __MemberType >       & collection,
        Test                                                     * pTestLib,
        cds :: MutableCollection < __MemberType > const & equivAfter1,
        cds :: MutableCollection < __MemberType >  & equivAfter2,
        cds :: MutableCollection < __MemberType > const & equivAfter3,
//        cds :: Collection < __MemberType > const & equivAfter3,                                   N/A with Collection
//        typename cds :: Collection < __MemberType > :: Iterator const & toRemoveBeforeFront,
        cds :: MutableCollection < __MemberType > const & equivAfter5,
        cds :: MutableCollection < __MemberType > const & equivAfter6
) -> bool {

    pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );

    /* MutableCollectionTestGroup-RemoveAbsIt-removeAtFront-cpp-xx : MCTC-00351-RAIT-removeAtFront-cpp-xx */
    typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveAtFront = collection.begin();
    auto const resultToRemoveAtFront = collection.remove( toRemoveAtFront );
    auto const expectedResultToRemoveAtFront = true;
    pTestLib->log ( "object after 'removeAtFront' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter1.toString().cStr() );
    if ( resultToRemoveAtFront != expectedResultToRemoveAtFront || ! collection.equals ( equivAfter1 ) ) {
        pTestLib->logError( "'MCTC-00351-RAIT-removeAtFront-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00351-RAIT-removeAtFront-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestGroup-RemoveAbsIt-removeInBounds-cpp-xx : MCTC-00352-RAIT-removeInBounds-cpp-xx */
    typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveInBounds = collection.begin();
    for ( uint32 i = 0; i * 2 < collection.size(); ++ i ) {
        ++ toRemoveInBounds;
    }

    auto const resultToRemoveAtInBounds = collection.remove( toRemoveInBounds );
    auto const expectedResultToRemoveAtInBounds = true;
    pTestLib->log ( "object after 'removeInBounds' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter2.toString().cStr() );
    if ( resultToRemoveAtInBounds != expectedResultToRemoveAtInBounds || ! collection.equals ( equivAfter2 ) ) {
        pTestLib->logError( "'MCTC-00352-RAIT-removeInBounds-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00352-RAIT-removeInBounds-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestGroup-RemoveAbsIt-removeAtEnd-cpp-xx : MCTC-00353-RAIT-removeAtEnd-cpp-xx */
    typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveAtEnd = collection.begin();
    for ( uint32 i = 0; i + 1 < collection.size(); ++ i ) {
        ++ toRemoveAtEnd;
    }

    auto const resultToRemoveAtEnd = collection.remove( toRemoveAtEnd );
    auto const expectedResultToRemoveAtEnd = true;
    pTestLib->log ( "object after 'removeAtEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter3.toString().cStr() );
    if ( resultToRemoveAtEnd != expectedResultToRemoveAtEnd || ! collection.equals ( equivAfter3 ) ) {
        pTestLib->logError( "'MCTC-00353-RAIT-removeAtEnd-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00353-RAIT-removeAtEnd-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestGroup-RemoveAbsIt-removeBeforeFront-" __CDS_cpplang_core_version_name " : MCTC-00354-RAIT-removeBeforeFront-cpp-xx : N/A */

    /* MutableCollectionTestGroup-RemoveAbsIt-removeAfterEnd-cpp-xx : MCTC-00355-RAIT-removeAfterEnd-cpp-xx */
    typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveAfterBack = collection.end();
    auto const resultToRemoveAfterEnd = collection.remove( toRemoveAfterBack );
    auto const expectedResultToRemoveAfterEnd = false;
    pTestLib->log ( "object after 'removeAfterEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
    if ( resultToRemoveAfterEnd != expectedResultToRemoveAfterEnd || ! collection.equals ( equivAfter5 ) ) {
        pTestLib->logError( "'MCTC-00355-RAIT-removeAfterEnd-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00355-RAIT-removeAfterEnd-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestGroup-RemoveAbsIt-removeFromOther-cpp-xx : MCTC-00355-RAIT-removeFromOther-cpp-xx */
    typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveFromSimilar = equivAfter2.begin();
    auto const resultToRemoveFromSimilar = collection.remove( toRemoveFromSimilar );
    auto const expectedResultToRemoveFromSimilar = false;
    pTestLib->log ( "object after 'removeFromOther' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
    if ( resultToRemoveFromSimilar != expectedResultToRemoveFromSimilar || ! collection.equals ( equivAfter6 ) ) {
        pTestLib->logError( "'MCTC-00356-RAIT-removeFromOther-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00356-RAIT-removeFromOther-" __CDS_cpplang_core_version_name "' OK" );
    }

    return true;
}



/* MutableCollectionTestGroup-RemoveBy-cpp-xx : MCTG-00400-RB-cpp-xx. MCTC-00401-RB to MCTC-00418-RB */
template <
        typename __Original,                        /* NOLINT(bugprone-reserved-identifier) */
        typename __MemberType,                      /* NOLINT(bugprone-reserved-identifier) */
        typename __MatchingNonePredicateType,       /* NOLINT(bugprone-reserved-identifier) */
        typename __MatchingOnePredicateType,        /* NOLINT(bugprone-reserved-identifier) */
        typename __MatchingMoreLTLPredicateType,    /* NOLINT(bugprone-reserved-identifier) */
        typename __MatchingMorePredicateType,       /* NOLINT(bugprone-reserved-identifier) */
        typename __MatchingMoreMTLPredicateType,    /* NOLINT(bugprone-reserved-identifier) */
        typename __MatchingAllPredicateType         /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupRemoveBy (
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
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveThatMatchesNone,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveThatMatchesOne,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveThatMatchesMoreLessThanLimit,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveThatMatchesMoreExact,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveThatMatchesMoreMoreThanLimit,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveThatMatchesAll,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveFirstThatMatchesNone,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveFirstThatMatchesOne,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveFirstThatMatchesMore,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveFirstThatMatchesAll,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveLastThatMatchesNone,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveLastThatMatchesOne,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveLastThatMatchesMore,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveLastThatMatchesAll,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveAllThatMatchesNone,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveAllThatMatchesOne,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveAllThatMatchesMore,
        cds :: MutableCollection < __MemberType > const & equivAfterRemoveAllThatMatchesAll
) -> bool {

    pTestLib->log ( "Object Under Test : %s", original.toString().cStr() );

    /* MutableCollectionTestCase-RemoveBy-removeThatMatchesNone-cpp-xx : MCTC-00401-RB-removeThatMatchesNone-cpp-xx */
    auto       copyRB401            = original;
    cds :: MutableCollection < __MemberType > & collectionRB401 = copyRB401;
    auto       removedCountRB401    = collectionRB401.removeThat ( removeThatLimit, matchingNone );
    auto const expectedRemovedCountRB401 = 0;
    pTestLib->log ( "object after 'removeThat with none matching' : '%s'. expected : '%s'", collectionRB401.toString().cStr(), equivAfterRemoveThatMatchesNone.toString().cStr() );
    if ( removedCountRB401 != expectedRemovedCountRB401 || ! collectionRB401.equals ( equivAfterRemoveThatMatchesNone ) ) {
        pTestLib->logError( "'MCTC-00401-RB-removeThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00401-RB-removeThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeThatMatchesOne-cpp-xx : MCTC-00402-RB-removeThatMatchesOne-cpp-xx */
    auto       copyRB402            = original;
    cds :: MutableCollection < __MemberType > & collectionRB402 = copyRB402;
    auto       removedCountRB402    = collectionRB402.removeThat ( removeThatLimit, matchingOne );
    auto const expectedRemovedCountRB402 = 1;
    pTestLib->log ( "object after 'removeThat with one matching' : '%s'. expected : '%s'", collectionRB402.toString().cStr(), equivAfterRemoveThatMatchesOne.toString().cStr() );
    if ( removedCountRB402 != expectedRemovedCountRB402 || ! collectionRB402.equals ( equivAfterRemoveThatMatchesOne ) ) {
        pTestLib->logError( "'MCTC-00402-RB-removeThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00402-RB-removeThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeThatMatchesMoreLessThanLimit-cpp-xx : MCTC-00403-RB-removeThatMatchesMoreLessThanLimit-cpp-xx */
    auto       copyRB403            = original;
    cds :: MutableCollection < __MemberType > & collectionRB403 = copyRB403;
    auto       removedCountRB403    = collectionRB403.removeThat ( removeThatLimit, matchingMoreLessThanLimit );
    auto const expectedRemovedCountRB403 = removeThatResultWhenLessThanLimit;
    pTestLib->log ( "object after 'removeThat with more matching, less than limit' : '%s'. expected : '%s'", collectionRB403.toString().cStr(), equivAfterRemoveThatMatchesMoreLessThanLimit.toString().cStr() );
    if ( removedCountRB403 != expectedRemovedCountRB403 || ! collectionRB403.equals ( equivAfterRemoveThatMatchesMoreLessThanLimit ) ) {
        pTestLib->logError( "'MCTC-00403-RB-removeThatMatchesMoreLessThanLimit-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00403-RB-removeThatMatchesMoreLessThanLimit-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeThatMatchesMoreExact-cpp-xx : MCTC-00404-RB-removeThatMatchesMoreExact-cpp-xx */
    auto       copyRB404            = original;
    cds :: MutableCollection < __MemberType > & collectionRB404 = copyRB404;
    auto       removedCountRB404    = collectionRB404.removeThat ( removeThatLimit, matchingMore );
    auto const expectedRemovedCountRB404 = removeThatLimit;
    pTestLib->log ( "object after 'removeThat with more matching, exact' : '%s'. expected : '%s'", collectionRB404.toString().cStr(), equivAfterRemoveThatMatchesMoreExact.toString().cStr() );
    if ( removedCountRB404 != expectedRemovedCountRB404 || ! collectionRB404.equals ( equivAfterRemoveThatMatchesMoreExact ) ) {
        pTestLib->logError( "'MCTC-00404-RB-removeThatMatchesMoreExact-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00404-RB-removeThatMatchesMoreExact-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeThatMatchesMoreMoreThanLimit-cpp-xx : MCTC-00405-RB-removeThatMatchesMoreMoreThanLimit-cpp-xx */
    auto       copyRB405            = original;
    cds :: MutableCollection < __MemberType > & collectionRB405 = copyRB405;
    auto       removedCountRB405    = collectionRB405.removeThat ( removeThatLimit, matchingMoreMoreThanLimit );
    auto const expectedRemovedCountRB405 = removeThatLimit;
    pTestLib->log ( "object after 'removeThat with more matching' : '%s'. expected : '%s'", collectionRB405.toString().cStr(), equivAfterRemoveThatMatchesMoreMoreThanLimit.toString().cStr() );
    if ( removedCountRB405 != expectedRemovedCountRB405 || ! collectionRB405.equals ( equivAfterRemoveThatMatchesMoreMoreThanLimit ) ) {
        pTestLib->logError( "'MCTC-00405-RB-removeThatMatchesMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00405-RB-removeThatMatchesMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeThatMatchesAll-cpp-xx : MCTC-00406-RB-removeThatMatchesAll-cpp-xx */
    auto       copyRB406            = original;
    cds :: MutableCollection < __MemberType > & collectionRB406 = copyRB406;
    auto       removedCountRB406    = collectionRB406.removeThat ( removeThatLimit, matchingAll );
    auto const expectedRemovedCountRB406 = removeThatLimit;
    pTestLib->log ( "object after 'removeThat with all matching, less than limit' : '%s'. expected : '%s'", collectionRB406.toString().cStr(), equivAfterRemoveThatMatchesAll.toString().cStr() );
    if ( removedCountRB406 != expectedRemovedCountRB406 || ! collectionRB406.equals ( equivAfterRemoveThatMatchesAll ) ) {
        pTestLib->logError( "'MCTC-00406-RB-removeThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00406-RB-removeThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeFirstThatMatchesNone-cpp-xx : MCTC-00407-RB-removeFirstThatMatchesNone-cpp-xx */
    auto       copyRB407            = original;
    cds :: MutableCollection < __MemberType > & collectionRB407 = copyRB407;
    auto       removedCountRB407    = collectionRB407.removeFirstThat ( matchingNone );
    auto const expectedRemovedCountRB407 = false;
    pTestLib->log ( "object after 'removeFirstThat with no matches' : '%s'. expected : '%s'", collectionRB407.toString().cStr(), equivAfterRemoveFirstThatMatchesNone.toString().cStr() );
    if ( removedCountRB407 != expectedRemovedCountRB407 || ! collectionRB407.equals ( equivAfterRemoveFirstThatMatchesNone ) ) {
        pTestLib->logError( "'MCTC-00407-RB-removeFirstThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00407-RB-removeFirstThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeFirstThatMatchesOne-cpp-xx : MCTC-00408-RB-removeFirstThatMatchesOne-cpp-xx */
    auto       copyRB408            = original;
    cds :: MutableCollection < __MemberType > & collectionRB408 = copyRB408;
    auto       removedCountRB408    = collectionRB408.removeFirstThat ( matchingOne );
    auto const expectedRemovedCountRB408 = true;
    pTestLib->log ( "object after 'removeFirstThat with one match' : '%s'. expected : '%s'", collectionRB408.toString().cStr(), equivAfterRemoveFirstThatMatchesOne.toString().cStr() );
    if ( removedCountRB408 != expectedRemovedCountRB408 || ! collectionRB408.equals ( equivAfterRemoveFirstThatMatchesOne ) ) {
        pTestLib->logError( "'MCTC-00408-RB-removeFirstThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00408-RB-removeFirstThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeFirstThatMatchesMore-cpp-xx : MCTC-00409-RB-removeFirstThatMatchesMore-cpp-xx */
    auto       copyRB409            = original;
    cds :: MutableCollection < __MemberType > & collectionRB409 = copyRB409;
    auto       removedCountRB409    = collectionRB409.removeFirstThat ( matchingMore );
    auto const expectedRemovedCountRB409 = true;
    pTestLib->log ( "object after 'removeFirstThat with one or more matches' : '%s'. expected : '%s'", collectionRB409.toString().cStr(), equivAfterRemoveFirstThatMatchesMore.toString().cStr() );
    if ( removedCountRB409 != expectedRemovedCountRB409 || ! collectionRB409.equals ( equivAfterRemoveFirstThatMatchesMore ) ) {
        pTestLib->logError( "'MCTC-00409-RB-removeFirstThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00409-RB-removeFirstThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeFirstThatMatchesAll-cpp-xx : MCTC-00410-RB-removeFirstThatMatchesAll-cpp-xx */
    auto       copyRB410            = original;
    cds :: MutableCollection < __MemberType > & collectionRB410 = copyRB410;
    auto       removedCountRB410    = collectionRB410.removeFirstThat ( matchingAll );
    auto const expectedRemovedCountRB410 = true;
    pTestLib->log ( "object after 'removeFirstThat matches all' : '%s'. expected : '%s'", collectionRB410.toString().cStr(), equivAfterRemoveFirstThatMatchesAll.toString().cStr() );
    if ( removedCountRB410 != expectedRemovedCountRB410 || ! collectionRB410.equals ( equivAfterRemoveFirstThatMatchesAll ) ) {
        pTestLib->logError( "'MCTC-00410-RB-removeFirstThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00410-RB-removeFirstThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeLastThatMatchesNone-cpp-xx : MCTC-00411-RB-removeLastThatMatchesNone-cpp-xx */
    auto       copyRB411            = original;
    cds :: MutableCollection < __MemberType > & collectionRB411 = copyRB411;
    auto       removedCountRB411    = collectionRB411.removeLastThat ( matchingNone );
    auto const expectedRemovedCountRB411 = false;
    pTestLib->log ( "object after 'removeLastThat with no matches' : '%s'. expected : '%s'", collectionRB411.toString().cStr(), equivAfterRemoveLastThatMatchesNone.toString().cStr() );
    if ( removedCountRB411 != expectedRemovedCountRB411 || ! collectionRB411.equals ( equivAfterRemoveLastThatMatchesNone ) ) {
        pTestLib->logError( "'MCTC-00411-RB-removeLastThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00411-RB-removeLastThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeLastThatMatchesOne-cpp-xx : MCTC-00412-RB-removeLastThatMatchesOne-cpp-xx */
    auto       copyRB412            = original;
    cds :: MutableCollection < __MemberType > & collectionRB412 = copyRB412;
    auto       removedCountRB412    = collectionRB412.removeLastThat ( matchingOne );
    auto const expectedRemovedCountRB412 = true;
    pTestLib->log ( "object after 'removeLastThat with one match' : '%s'. expected : '%s'", collectionRB412.toString().cStr(), equivAfterRemoveLastThatMatchesOne.toString().cStr() );
    if ( removedCountRB412 != expectedRemovedCountRB412 || ! collectionRB412.equals ( equivAfterRemoveLastThatMatchesOne ) ) {
        pTestLib->logError( "'MCTC-00412-RB-removeLastThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00412-RB-removeLastThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeLastThatMatchesMore-cpp-xx : MCTC-00413-RB-removeLastThatMatchesMore-cpp-xx */
    auto       copyRB413            = original;
    cds :: MutableCollection < __MemberType > & collectionRB413 = copyRB413;
    auto       removedCountRB413    = collectionRB413.removeLastThat ( matchingMore );
    auto const expectedRemovedCountRB413 = true;
    pTestLib->log ( "object after 'removeLastThat with one or more matches' : '%s'. expected : '%s'", collectionRB413.toString().cStr(), equivAfterRemoveLastThatMatchesMore.toString().cStr() );
    if ( removedCountRB413 != expectedRemovedCountRB413 || ! collectionRB413.equals ( equivAfterRemoveLastThatMatchesMore ) ) {
        pTestLib->logError( "'MCTC-00413-RB-removeLastThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00413-RB-removeLastThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeLastThatMatchesAll-cpp-xx : MCTC-00414-RB-removeLastThatMatchesAll-cpp-xx */
    auto       copyRB414            = original;
    cds :: MutableCollection < __MemberType > & collectionRB414 = copyRB414;
    auto       removedCountRB414    = collectionRB414.removeLastThat ( matchingAll );
    auto const expectedRemovedCountRB414 = true;
    pTestLib->log ( "object after 'removeLastThat matching all' : '%s'. expected : '%s'", collectionRB414.toString().cStr(), equivAfterRemoveLastThatMatchesAll.toString().cStr() );
    if ( removedCountRB414 != expectedRemovedCountRB414 || ! collectionRB414.equals ( equivAfterRemoveLastThatMatchesAll ) ) {
        pTestLib->logError( "'MCTC-00414-RB-removeLastThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00414-RB-removeLastThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeAllThatMatchesNone-cpp-xx : MCTC-00415-RB-removeAllThatMatchesNone-cpp-xx */
    auto       copyRB415            = original;
    cds :: MutableCollection < __MemberType > & collectionRB415 = copyRB415;
    auto const expectedRemovedCountRB415 = collectionRB415.count ( matchingNone );
    auto       removedCountRB415    = collectionRB415.removeAllThat ( matchingNone );
    pTestLib->log ( "object after 'removeAllThat match none' : '%s'. expected : '%s'", collectionRB415.toString().cStr(), equivAfterRemoveAllThatMatchesNone.toString().cStr() );
    if ( removedCountRB415 != expectedRemovedCountRB415 || ! collectionRB415.equals ( equivAfterRemoveAllThatMatchesNone ) ) {
        pTestLib->logError( "'MCTC-00415-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00415-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeAllThatMatchesOne-cpp-xx : MCTC-00416-RB-removeAllThatMatchesOne-cpp-xx */
    auto       copyRB416            = original;
    cds :: MutableCollection < __MemberType > & collectionRB416 = copyRB416;
    auto const expectedRemovedCountRB416 = collectionRB416.count ( matchingOne );
    auto       removedCountRB416    = collectionRB416.removeAllThat ( matchingOne );
    pTestLib->log ( "object after 'removeAllThat matching one' : '%s'. expected : '%s'", collectionRB416.toString().cStr(), equivAfterRemoveAllThatMatchesOne.toString().cStr() );
    if ( removedCountRB416 != expectedRemovedCountRB416 || ! collectionRB416.equals ( equivAfterRemoveAllThatMatchesOne ) ) {
        pTestLib->logError( "'MCTC-00416-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00416-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeAllThatMatchesMore-cpp-xx : MCTC-00417-RB-removeAllThatMatchesMore-cpp-xx */
    auto       copyRB417            = original;
    cds :: MutableCollection < __MemberType > & collectionRB417 = copyRB417;
    auto const expectedRemovedCountRB417 = collectionRB417.count ( matchingMore );
    auto       removedCountRB417    = collectionRB417.removeAllThat ( matchingMore );
    pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB417.toString().cStr(), equivAfterRemoveAllThatMatchesMore.toString().cStr() );
    if ( removedCountRB417 != expectedRemovedCountRB417 || ! collectionRB417.equals ( equivAfterRemoveAllThatMatchesMore ) ) {
        pTestLib->logError( "'MCTC-00417-RB-removeAllThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00417-RB-removeAllThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RemoveBy-removeAllThatMatchesAll-cpp-xx : MCTC-00418-RB-removeAllThatMatchesAll-cpp-xx */
    auto       copyRB418            = original;
    cds :: MutableCollection < __MemberType > & collectionRB418 = copyRB418;
    auto const expectedRemovedCountRB418 = collectionRB418.count ( matchingAll );
    auto       removedCountRB418    = collectionRB418.removeAllThat ( matchingAll );
    pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB418.toString().cStr(), equivAfterRemoveAllThatMatchesAll.toString().cStr() );
    if ( removedCountRB418 != expectedRemovedCountRB418 || ! collectionRB418.equals ( equivAfterRemoveAllThatMatchesAll ) ) {
        pTestLib->logError( "'MCTC-00418-RB-removeAllThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00418-RB-removeAllThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    return true;
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


/* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTG-00450-RO-cpp-xx. MCTC-00451-RO to MCTC-00464-RO */
template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupItemRemoveOf (
        Test                      * pTestLib,
        cds :: String       const & groupVariant,
        StringLiteral               subvariant,
        Size                        subvariantOffset,
        __IterableType      const & iterableUnderTest,
        Size ( cds :: MutableCollection < __ElementType > :: * removePfnVariant ) ( Size, __OtherIterableType const & ),
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
) -> bool {

    pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

/* MutableCollectionTestCase-RemoveOf-removeOfNoneCommon-cpp-xx : MCTC-00451-RO-removeOfNoneCommon-cpp-xx */
/* MutableCollectionTestCase-RemoveOf-removeNotOfNoneCommon-cpp-xx : MCTC-00458-RO-removeNotOfNoneCommon-cpp-xx */
    auto       copyRO451            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO451 = copyRO451;
    auto       removedCountRB451    = ( collectionRO451.* removePfnVariant ) ( limit, noneCommon );
    pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO451.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
    if ( removedCountRB451 != expectedResultFromNone || ! equals ( collectionRO451, expectedCollectionFromNone ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", 451 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", 451 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

/* MutableCollectionTestCase-RemoveOf-removeOfOneCommon-cpp-xx : MCTC-00452-RO-removeOfOneCommon-cpp-xx */
/* MutableCollectionTestCase-RemoveOf-removeNotOfOneCommon-cpp-xx : MCTC-00459-RO-removeNotOfOneCommon-cpp-xx */
    auto       copyRO452            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO452 = copyRO452;
    auto       removedCountRB452    = ( collectionRO452.* removePfnVariant ) ( limit, oneCommon );
    pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO452.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
    if ( removedCountRB452 != expectedResultFromOne || ! equals ( collectionRO452, expectedCollectionFromOne ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", 452 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", 452 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

/* MutableCollectionTestCase-RemoveOf-removeOfMoreLessThanLimitCommon-cpp-xx : MCTC-00453-RO-removeOfMoreLessThanLimitCommon-cpp-xx */
/* MutableCollectionTestCase-RemoveOf-removeNotOfMoreLessThanLimitCommon-cpp-xx : MCTC-00460-RO-removeOfMoreLessThanLimitCommon-cpp-xx */
    auto       copyRO453            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO453 = copyRO453;
    auto       removedCountRB453    = ( collectionRO453.* removePfnVariant ) ( limit, moreLessThanLimitCommon );
    pTestLib->log ( "object after '%s with more less than limit common' : '%s'. expected : '%s'", subvariant, collectionRO453.toString().cStr(), toString ( expectedCollectionFromMoreLessThanLimit ).cStr() );
    if ( removedCountRB453 != expectedResultFromMoreLessThanLimit || ! equals ( collectionRO453, expectedCollectionFromMoreLessThanLimit ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sMoreLessThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' failed", 453 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreLessThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' OK", 453 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

/* MutableCollectionTestCase-RemoveOf-removeOfMoreCommon-cpp-xx : MCTC-00454-RO-removeOfMoreCommon-cpp-xx */
/* MutableCollectionTestCase-RemoveOf-removeNotOfMoreCommon-cpp-xx : MCTC-00461-RO-removeNotOfMoreCommon-cpp-xx */
    auto       copyRO454            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO454 = copyRO454;
    auto       removedCountRB454    = ( collectionRO454.* removePfnVariant ) ( limit, moreCommon );
    pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO454.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
    if ( removedCountRB454 != expectedResultFromMore || ! equals ( collectionRO454, expectedCollectionFromMore ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", 454 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", 454 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

/* MutableCollectionTestCase-RemoveOf-removeOfMoreMoreThanLimitCommon-cpp-xx : MCTC-00455-RO-removeOfMoreMoreThanLimitCommon-cpp-xx */
/* MutableCollectionTestCase-RemoveOf-removeNotOfMoreMoreThanLimitCommon-cpp-xx : MCTC-00462-RO-removeNotOfMoreMoreThanLimitCommon-cpp-xx */
    auto       copyRO455            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO455 = copyRO455;
    auto       removedCountRB455    = ( collectionRO455.* removePfnVariant ) ( limit, moreMoreThanLimitCommon );
    pTestLib->log ( "object after '%s with more than limit common' : '%s'. expected : '%s'", subvariant, collectionRO455.toString().cStr(), toString ( expectedCollectionFromMoreMoreThanLimit ).cStr() );
    if ( removedCountRB455 != expectedResultFromMoreMoreThanLimit || ! equals ( collectionRO455, expectedCollectionFromMoreMoreThanLimit ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' failed", 455 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' OK", 455 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

/* MutableCollectionTestCase-RemoveOf-removeOfAllCommon-cpp-xx : MCTC-00456-RO-removeOfAllCommon-cpp-xx */
/* MutableCollectionTestCase-RemoveOf-removeNotOfAllCommon-cpp-xx : MCTC-00463-RO-removeNotOfAllCommon-cpp-xx */
    auto       copyRO456            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO456 = copyRO456;
    auto       removedCountRB456    = ( collectionRO456.* removePfnVariant ) ( limit, allCommon );
    pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO456.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
    if ( removedCountRB456 != expectedResultFromAll || ! equals ( collectionRO456, expectedCollectionFromAll ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", 456 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", 456 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

/* MutableCollectionTestCase-RemoveOf-removeOfAllAndMoreCommon-cpp-xx : MCTC-00457-RO-removeOfAllAndMoreCommon-cpp-xx */
/* MutableCollectionTestCase-RemoveOf-removeNotOfAllAndMoreCommon-cpp-xx : MCTC-00464-RO-removeNotOfAllAndMoreCommon-cpp-xx */
    auto       copyRO457            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO457 = copyRO457;
    auto       removedCountRB457    = ( collectionRO457.* removePfnVariant ) ( limit, allAndMoreCommon );
    pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO457.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
    if ( removedCountRB457 != expectedResultFromAllAndMore || ! equals ( collectionRO457, expectedCollectionFromAllAndMore ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", 457 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", 457 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    return true;
}



/* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTG-00450-RO-cpp-xx. MMCTC-00501-RO to MMCTC-00520-RO. */
template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupItemRemoveFirstLastOf (
        Test                      * pTestLib,
        cds :: String       const & groupVariant,
        StringLiteral               subvariant,
        Size                        subvariantOffset,
        __IterableType      const & iterableUnderTest,
        bool ( cds :: MutableCollection < __ElementType > :: * removeFirstLastPfnVariant ) ( __OtherIterableType const & ),
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
) -> bool {

    pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

    /* MutableCollectionTestCase-RemoveOf-removeFirstOfNoneCommon-cpp-xx : MCTC-00501-RO-removeFirstOfNoneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastOfNoneCommon-cpp-xx : MCTC-00506-RO-removeLastOfNoneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfNoneCommon-cpp-xx : MCTC-00511-RO-removeFirstNotOfNoneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastNotOfNoneCommon-cpp-xx : MCTC-00516-RO-removeLastNotOfNoneCommon-cpp-xx */
    auto       copyRO501            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO501 = copyRO501;
    auto       removedCountRB501    = ( collectionRO501.* removeFirstLastPfnVariant ) ( noneCommon );
    pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO501.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
    if ( removedCountRB501 != expectedResultFromNone || ! equals ( collectionRO501, expectedCollectionFromNone ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", 501 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", 501 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeFirstOfOneCommon-cpp-xx : MCTC-00502-RO-removeFirstOfOneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastOfOneCommon-cpp-xx : MCTC-00507-RO-removeLastOfOneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfOneCommon-cpp-xx : MCTC-00512-RO-removeFirstNotOfOneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastNotOfOneCommon-cpp-xx : MCTC-00517-RO-removeLastNotOfOneCommon-cpp-xx */
    auto       copyRO502            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO502 = copyRO502;
    auto       removedCountRB502    = ( collectionRO502.* removeFirstLastPfnVariant ) ( oneCommon );
    pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO502.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
    if ( removedCountRB502 != expectedResultFromOne || ! equals ( collectionRO502, expectedCollectionFromOne ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", 502 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", 502 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeFirstOfMoreCommon-cpp-xx : MCTC-00503-RO-removeFirstOfMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastOfMoreCommon-cpp-xx : MCTC-00508-RO-removeLastOfMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfMoreCommon-cpp-xx : MCTC-00513-RO-removeFirstNotOfMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastNotOfMoreCommon-cpp-xx : MCTC-00518-RO-removeLastNotOfMoreCommon-cpp-xx */
    auto       copyRO503            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO503 = copyRO503;
    auto       removedCountRB503    = ( collectionRO503.* removeFirstLastPfnVariant ) ( moreCommon );
    pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO503.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
    if ( removedCountRB503 != expectedResultFromMore || ! equals ( collectionRO503, expectedCollectionFromMore ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", 503 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", 503 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeFirstOfAllCommon-cpp-xx : MCTC-00504-RO-removeFirstOfAllCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastOfAllCommon-cpp-xx : MCTC-00509-RO-removeLastOfAllCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfAllCommon-cpp-xx : MCTC-00514-RO-removeFirstNotOfAllCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastNotOfAllCommon-cpp-xx : MCTC-00519-RO-removeLastNotOfAllCommon-cpp-xx */
    auto       copyRO504            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO504 = copyRO504;
    auto       removedCountRB504    = ( collectionRO504.* removeFirstLastPfnVariant ) ( allCommon );
    pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO504.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
    if ( removedCountRB504 != expectedResultFromAll || ! equals ( collectionRO504, expectedCollectionFromAll ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", 504 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", 504 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeFirstOfAllAndMoreCommon-cpp-xx : MCTC-00505-RO-removeFirstOfAllAndMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastOfAllAndMoreCommon-cpp-xx : MCTC-00510-RO-removeLastOfAllAndMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfAllAndMoreCommon-cpp-xx : MCTC-00515-RO-removeFirstNotOfAllAndMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeLastNotOfAllAndMoreCommon-cpp-xx : MCTC-00520-RO-removeLastNotOfAllAndMoreCommon-cpp-xx */
    auto       copyRO505            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO505 = copyRO505;
    auto       removedCountRB505    = ( collectionRO505.* removeFirstLastPfnVariant ) ( allAndMoreCommon );
    pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO505.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
    if ( removedCountRB505 != expectedResultFromAllAndMore || ! equals ( collectionRO505, expectedCollectionFromAllAndMore ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", 505 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", 505 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    return true;
}

/* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTC-00450-RO-cpp-xx. MCTC-00481-RO to MCTC-00490-RO. */
template <
        typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupItemRemoveAllOf (
        Test                      * pTestLib,
        cds :: String       const & groupVariant,
        StringLiteral               subvariant,
        Size                        subvariantOffset,
        __IterableType      const & iterableUnderTest,
        Size ( cds :: MutableCollection < __ElementType > :: * removeAllPfnVariant ) ( __OtherIterableType const & ),
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
) -> bool {

    pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

    /* MutableCollectionTestCase-RemoveOf-removeAllOfNoneCommon-cpp-xx : MCTC-00481-RO-removeAllOfNoneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeAllNotOfNoneCommon-cpp-xx : MCTC-00486-RO-removeAllNotOfNoneCommon-cpp-xx */
    auto       copyRO481            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO481 = copyRO481;
    auto       removedCountRB481    = ( collectionRO481.* removeAllPfnVariant ) ( noneCommon );
    pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO481.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
    if ( removedCountRB481 != expectedResultFromNone || ! equals ( collectionRO481, expectedCollectionFromNone ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", 481 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", 481 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeAllOfOneCommon-cpp-xx : MCTC-00482-RO-removeAllOfOneCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeAllNotOfOneCommon-cpp-xx : MCTC-00487-RO-removeAllNotOfOneCommon-cpp-xx */
    auto       copyRO482            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO482 = copyRO482;
    auto       removedCountRB482    = ( collectionRO482.* removeAllPfnVariant ) ( oneCommon );
    pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO482.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
    if ( removedCountRB482 != expectedResultFromOne || ! equals ( collectionRO482, expectedCollectionFromOne ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", 482 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", 482 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeAllOfMoreCommon-cpp-xx : MCTC-00483-RO-removeAllOfMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeAllNotOfMoreCommon-cpp-xx : MCTC-00488-RO-removeAllNotOfMoreCommon-cpp-xx */
    auto       copyRO483            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO483 = copyRO483;
    auto       removedCountRB483    = ( collectionRO483.* removeAllPfnVariant ) ( moreCommon );
    pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO483.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
    if ( removedCountRB483 != expectedResultFromMore || ! equals ( collectionRO483, expectedCollectionFromMore ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", 483 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", 483 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeAllOfAllCommon-cpp-xx : MCTC-00484-RO-removeAllOfAllCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeAllNotOfAllCommon-cpp-xx : MCTC-00489-RO-removeAllNotOfAllCommon-cpp-xx */
    auto       copyRO484            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO484 = copyRO484;
    auto       removedCountRB484    = ( collectionRO484.* removeAllPfnVariant ) ( allCommon );
    pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO484.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
    if ( removedCountRB484 != expectedResultFromAll || ! equals ( collectionRO484, expectedCollectionFromAll ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", 484 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", 484 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    /* MutableCollectionTestCase-RemoveOf-removeAllOfAllAndMoreCommon-cpp-xx : MCTC-00485-RO-removeAllOfAllAndMoreCommon-cpp-xx */
    /* MutableCollectionTestCase-RemoveOf-removeAllNotOfAllAndMoreCommon-cpp-xx : MCTC-00490-RO-removeAllNotOfAllAndMoreCommon-cpp-xx */
    auto       copyRO485            = iterableUnderTest;
    cds :: MutableCollection < __ElementType > & collectionRO485 = copyRO485;
    auto       removedCountRB485    = ( collectionRO485.* removeAllPfnVariant ) ( allAndMoreCommon );
    pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO485.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
    if ( removedCountRB485 != expectedResultFromAllAndMore || ! equals ( collectionRO485, expectedCollectionFromAllAndMore ) ) {
        pTestLib->logError( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", 485 + subvariantOffset, subvariant, groupVariant.cStr() );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", 485 + subvariantOffset, subvariant, groupVariant.cStr() );
    }

    return true;
}

template <
        typename __ElementType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        template < typename ... > class __CollectionType,                                                       /* NOLINT(bugprone-reserved-identifier) */
        typename __ValidatorPredicate,                                                                          /* NOLINT(bugprone-reserved-identifier) */
        typename __IteratorType = typename cds :: Collection < __ElementType > :: Iterator /* NOLINT(bugprone-reserved-identifier) */
> auto iteratorListEqualityCheck (
        __ValidatorPredicate                const & validator,
        __CollectionType < __IteratorType > const & iteratorCollection,
        __CollectionType < __ElementType >  const & elementCollection
) -> bool {

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
        typename __IteratorType = typename cds :: Collection < __ElementType > :: Iterator /* NOLINT(bugprone-reserved-identifier) */
> auto iteratorListEqualityCheckNoPred (
        __CollectionType < __IteratorType > const & iteratorCollection,
        __CollectionType < __ElementType >  const & elementCollection
) -> bool {

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



/* MutableCollectionTestGroup-FindThat-cpp-xx : MCTG-00600-FT-cpp-xx. MCTC-00601-FT to MCTC-00634-FT */
template <
        typename __ElementType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
        typename __NonePredicate,                                                               /* NOLINT(bugprone-reserved-identifier) */
        typename __OnePredicate,                                                                /* NOLINT(bugprone-reserved-identifier) */
        typename __MorePredicateLessThanLimit,                                                  /* NOLINT(bugprone-reserved-identifier) */
        typename __MorePredicate,                                                               /* NOLINT(bugprone-reserved-identifier) */
        typename __MorePredicateMoreThanLimit,                                                  /* NOLINT(bugprone-reserved-identifier) */
        typename __AllPredicate,                                                                /* NOLINT(bugprone-reserved-identifier) */
        typename __AllAndMorePredicate,                                                         /* NOLINT(bugprone-reserved-identifier) */
        template < typename ... > class __ComparisonEquivalent = cds :: Array   /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupFindThat (
        Test                                                      * pTestLib,
        cds :: MutableCollection < __ElementType > & underTest,
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
    using Iterator = typename cds :: MutableCollection < __ElementType > :: Iterator;

    /* MutableCollectionTestCase-FindThat-findThatStoreInMatchingNone-cpp-xx : MCTC-00601-FT-findThatStoreInMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00601 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00601;
    auto                                                        expectedSize00601 = expectedSizeFindThatNone;
    auto                                                const & expected00601 = expectedFindThatNone;
    auto                                                const & predicate00601 = none;

    (void) collection00601.findThat ( limit, storeIn00601, predicate00601 );
    if ( storeIn00601.size() != expectedSize00601 || ! iteratorListEqualityCheck ( predicate00601, storeIn00601, expected00601 ) ) {
        pTestLib->logError( "'MCTC-00601-FT-findThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00601-FT-findThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatStoreInMatchingOne-cpp-xx : MCTC-00602-FT-findThatStoreInMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00602 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00602;
    auto                                                        expectedSize00602 = expectedSizeFindThatOne;
    auto                                                const & expected00602 = expectedFindThatOne;
    auto                                                const & predicate00602 = one;

    (void) collection00602.findThat ( limit, storeIn00602, predicate00602 );
    if ( storeIn00602.size() != expectedSize00602 || ! iteratorListEqualityCheck ( predicate00602, storeIn00602, expected00602 ) ) {
        pTestLib->logError( "'MCTC-00602-FT-findThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00602-FT-findThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatStoreInMatchingMoreLessThanLimit-cpp-xx : MCTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00603 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00603;
    auto                                                        expectedSize00603 = expectedSizeFindThatMoreLessThanLimit;
    auto                                                const & expected00603 = expectedFindThatMoreLessThanLimit;
    auto                                                const & predicate00603 = moreLessThanLimit;

    (void) collection00603.findThat ( limit, storeIn00603, predicate00603 );
    if ( storeIn00603.size() != expectedSize00603 || ! iteratorListEqualityCheck ( predicate00603, storeIn00603, expected00603 ) ) {
        pTestLib->logError( "'MCTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatStoreInMatchingMore-cpp-xx : MCTC-00604-FT-findThatStoreInMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00604 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00604;
    auto                                                        expectedSize00604 = expectedSizeFindThatMore;
    auto                                                const & expected00604 = expectedFindThatMore;
    auto                                                const & predicate00604 = more;

    (void) collection00604.findThat ( limit, storeIn00604, predicate00604 );
    if ( storeIn00604.size() != expectedSize00604 || ! iteratorListEqualityCheck ( predicate00604, storeIn00604, expected00604 ) ) {
        pTestLib->logError( "'MCTC-00604-FT-findThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00604-FT-findThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatStoreInMatchingMoreMoreThanLimit-cpp-xx : MCTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00605 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00605;
    auto                                                        expectedSize00605 = expectedSizeFindThatMoreMoreThanLimit;
    auto                                                const & expected00605 = expectedFindThatMoreMoreThanLimit;
    auto                                                const & predicate00605 = moreMoreThanLimit;

    (void) collection00605.findThat ( limit, storeIn00605, predicate00605 );
    if ( storeIn00605.size() != expectedSize00605 || ! iteratorListEqualityCheck ( predicate00605, storeIn00605, expected00605 ) ) {
        pTestLib->logError( "'MCTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatStoreInMatchingAll-cpp-xx : MCTC-00606-FT-findThatStoreInMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00606 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00606;
    auto                                                        expectedSize00606 = expectedSizeFindThatAll;
    auto                                                const & expected00606 = expectedFindThatAll;
    auto                                                const & predicate00606 = all;

    (void) collection00606.findThat ( limit, storeIn00606, predicate00606 );
    if ( storeIn00606.size() != expectedSize00606 || ! iteratorListEqualityCheck ( predicate00606, storeIn00606, expected00606 ) ) {
        pTestLib->logError( "'MCTC-00606-FT-findThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00606-FT-findThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatStoreInMatchingAllAndMore-cpp-xx : MCTC-00607-FT-findThatStoreInMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00607 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00607;
    auto                                                        expectedSize00607 = expectedSizeFindThatAllAndMore;
    auto                                                const & expected00607 = expectedFindThatAllAndMore;
    auto                                                const & predicate00607 = allAndMore;

    (void) collection00607.findThat ( limit, storeIn00607, predicate00607 );
    if ( storeIn00607.size() != expectedSize00607 || ! iteratorListEqualityCheck ( predicate00607, storeIn00607, expected00607 ) ) {
        pTestLib->logError( "'MCTC-00607-FT-findThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00607-FT-findThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatReturnedMatchingNone-cpp-xx : MCTC-00608-FT-findThatReturnedMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00608 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00608;
    auto                                                        expectedSize00608 = expectedSizeFindThatNone;
    auto                                                const & expected00608 = expectedFindThatNone;
    auto                                                const & predicate00608 = none;

    storeIn00608 = collection00608.template findThat < __ComparisonEquivalent > ( limit, predicate00608 );
    if ( storeIn00608.size() != expectedSize00608 || ! iteratorListEqualityCheck ( predicate00608, storeIn00608, expected00608 ) ) {
        pTestLib->logError( "'MCTC-00608-FT-findThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00608-FT-findThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatReturnedMatchingOne-cpp-xx : MCTC-00609-FT-findThatReturnedMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00609 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00609;
    auto                                                        expectedSize00609 = expectedSizeFindThatOne;
    auto                                                const & expected00609 = expectedFindThatOne;
    auto                                                const & predicate00609 = one;

    storeIn00609 = collection00609.template findThat < __ComparisonEquivalent > ( limit, predicate00609 );
    if ( storeIn00609.size() != expectedSize00609 || ! iteratorListEqualityCheck ( predicate00609, storeIn00609, expected00609 ) ) {
        pTestLib->logError( "'MCTC-00609-FT-findThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00609-FT-findThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatReturnedMatchingMoreLessThanLimit-cpp-xx : MCTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00610 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00610;
    auto                                                        expectedSize00610 = expectedSizeFindThatMoreLessThanLimit;
    auto                                                const & expected00610 = expectedFindThatMoreLessThanLimit;
    auto                                                const & predicate00610 = moreLessThanLimit;

    storeIn00610 = collection00610.template findThat < __ComparisonEquivalent > ( limit, predicate00610 );
    if ( storeIn00610.size() != expectedSize00610 || ! iteratorListEqualityCheck ( predicate00610, storeIn00610, expected00610 ) ) {
        pTestLib->logError( "'MCTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatReturnedMatchingMore-cpp-xx : MCTC-00611-FT-findThatReturnedMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00611 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00611;
    auto                                                        expectedSize00611 = expectedSizeFindThatMore;
    auto                                                const & expected00611 = expectedFindThatMore;
    auto                                                const & predicate00611 = more;

    storeIn00611 = collection00611.template findThat < __ComparisonEquivalent > ( limit, predicate00611 );
    if ( storeIn00611.size() != expectedSize00611 || ! iteratorListEqualityCheck ( predicate00611, storeIn00611, expected00611 ) ) {
        pTestLib->logError( "'MCTC-00611-FT-findThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00611-FT-findThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatReturnedMatchingMoreMoreThanLimit-cpp-xx : MCTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00612 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00612;
    auto                                                        expectedSize00612 = expectedSizeFindThatMoreMoreThanLimit;
    auto                                                const & expected00612 = expectedFindThatMoreMoreThanLimit;
    auto                                                const & predicate00612 = moreMoreThanLimit;

    storeIn00612 = collection00612.template findThat < __ComparisonEquivalent > ( limit, predicate00612 );
    if ( storeIn00612.size() != expectedSize00612 || ! iteratorListEqualityCheck ( predicate00612, storeIn00612, expected00612 ) ) {
        pTestLib->logError( "'MCTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatReturnedMatchingAll-cpp-xx : MCTC-00613-FT-findThatReturnedMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00613 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00613;
    auto                                                        expectedSize00613 = expectedSizeFindThatAll;
    auto                                                const & expected00613 = expectedFindThatAll;
    auto                                                const & predicate00613 = all;

    storeIn00613 = collection00613.template findThat < __ComparisonEquivalent > ( limit, predicate00613 );
    if ( storeIn00613.size() != expectedSize00613 || ! iteratorListEqualityCheck ( predicate00613, storeIn00613, expected00613 ) ) {
        pTestLib->logError( "'MCTC-00613-FT-findThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00613-FT-findThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findThatReturnedMatchingAllAndMore-cpp-xx : MCTC-00614-FT-findThatReturnedMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00614 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00614;
    auto                                                        expectedSize00614 = expectedSizeFindThatAllAndMore;
    auto                                                const & expected00614 = expectedFindThatAllAndMore;
    auto                                                const & predicate00614 = allAndMore;

    storeIn00614 = collection00614.template findThat < __ComparisonEquivalent > ( limit, predicate00614 );
    if ( storeIn00614.size() != expectedSize00614 || ! iteratorListEqualityCheck ( predicate00614, storeIn00614, expected00614 ) ) {
        pTestLib->logError( "'MCTC-00614-FT-findThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00614-FT-findThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findFirstThatMatchingNone-cpp-xx : MCTC-00615-FT-findFirstThatMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00615 = underTest;
    Iterator                                               result00615;
    auto                                                        expectedValid00615 = expectedResultFindFirstThatNone;
    auto                                                        expectedValue00615 = expectedFindFirstThatNone;
    auto                                                const & predicate00615 = none;

    result00615 = collection00615.findFirstThat ( predicate00615 );
    if ( ( result00615 != collection00615.end() ) != expectedValid00615 || expectedValid00615 && expectedValue00615 != * result00615 ) {
        pTestLib->logError( "'MCTC-00615-FT-findFirstThatMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00615-FT-findFirstThatMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findFirstThatMatchingOne-cpp-xx : MCTC-00616-FT-findFirstThatMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00616 = underTest;
    Iterator                                               result00616;
    auto                                                        expectedValid00616 = expectedResultFindFirstThatOne;
    auto                                                        expectedValue00616 = expectedFindFirstThatOne;
    auto                                                const & predicate00616 = one;

    result00616 = collection00616.findFirstThat ( predicate00616 );
    if ( ( result00616 != collection00616.end() ) != expectedValid00616 || expectedValid00616 && expectedValue00616 != * result00616 ) {
        pTestLib->logError( "'MCTC-00616-FT-findFirstThatMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00616-FT-findFirstThatMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findFirstThatMatchingMore-cpp-xx : MCTC-00617-FT-findFirstThatMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00617 = underTest;
    Iterator                                               result00617;
    auto                                                        expectedValid00617 = expectedResultFindFirstThatMore;
    auto                                                        expectedValue00617 = expectedFindFirstThatMore;
    auto                                                const & predicate00617 = more;

    result00617 = collection00617.findFirstThat ( predicate00617 );
    if ( ( result00617 != collection00617.end() ) != expectedValid00617 || expectedValid00617 && expectedValue00617 != * result00617 ) {
        pTestLib->logError( "'MCTC-00617-FT-findFirstThatMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00617-FT-findFirstThatMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findFirstThatMatchingAll-cpp-xx : MCTC-00618-FT-findFirstThatMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00618 = underTest;
    Iterator                                               result00618;
    auto                                                        expectedValid00618 = expectedResultFindFirstThatAll;
    auto                                                        expectedValue00618 = expectedFindFirstThatAll;
    auto                                                const & predicate00618 = all;

    result00618 = collection00618.findFirstThat ( predicate00618 );
    if ( ( result00618 != collection00618.end() ) != expectedValid00618 || expectedValid00618 && expectedValue00618 != * result00618 ) {
        pTestLib->logError( "'MCTC-00618-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00618-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findFirstThatMatchingAllAndMore-cpp-xx : MCTC-00619-FT-findFirstThatMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00619 = underTest;
    Iterator                                               result00619;
    auto                                                        expectedValid00619 = expectedResultFindFirstThatAllAndMore;
    auto                                                        expectedValue00619 = expectedFindFirstThatAllAndMore;
    auto                                                const & predicate00619 = allAndMore;

    result00619 = collection00619.findFirstThat ( predicate00619 );
    if ( ( result00619 != collection00619.end() ) != expectedValid00619 || expectedValid00619 && expectedValue00619 != * result00619 ) {
        pTestLib->logError( "'MCTC-00619-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00619-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findLastThatMatchingNone-cpp-xx : MCTC-00620-FT-findLastThatMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00620 = underTest;
    Iterator                                               result00620;
    auto                                                        expectedValid00620 = expectedResultFindLastThatNone;
    auto                                                        expectedValue00620 = expectedFindLastThatNone;
    auto                                                const & predicate00620 = none;

    result00620 = collection00620.findLastThat ( predicate00620 );
    if ( ( result00620 != collection00620.end() ) != expectedValid00620 || expectedValid00620 && expectedValue00620 != * result00620 ) {
        pTestLib->logError( "'MCTC-00620-FT-findLastThatMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00620-FT-findLastThatMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findLastThatMatchingOne-cpp-xx : MCTC-00621-FT-findLastThatMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00621 = underTest;
    Iterator                                               result00621;
    auto                                                        expectedValid00621 = expectedResultFindLastThatOne;
    auto                                                        expectedValue00621 = expectedFindLastThatOne;
    auto                                                const & predicate00621 = one;

    result00621 = collection00621.findLastThat ( predicate00621 );
    if ( ( result00621 != collection00621.end() ) != expectedValid00621 || expectedValid00621 && expectedValue00621 != * result00621 ) {
        pTestLib->logError( "'MCTC-00621-FT-findLastThatMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00621-FT-findLastThatMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findLastThatMatchingMore-cpp-xx : MCTC-00622-FT-findLastThatMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00622 = underTest;
    Iterator                                               result00622;
    auto                                                        expectedValid00622 = expectedResultFindLastThatMore;
    auto                                                        expectedValue00622 = expectedFindLastThatMore;
    auto                                                const & predicate00622 = more;

    result00622 = collection00622.findLastThat ( predicate00622 );
    if ( ( result00622 != collection00622.end() ) != expectedValid00622 || expectedValid00622 && expectedValue00622 != * result00622 ) {
        pTestLib->logError( "'MCTC-00622-FT-findLastThatMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00622-FT-findLastThatMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findLastThatMatchingAll-cpp-xx : MCTC-00623-FT-findLastThatMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00623 = underTest;
    Iterator                                               result00623;
    auto                                                        expectedValid00623 = expectedResultFindLastThatAll;
    auto                                                        expectedValue00623 = expectedFindLastThatAll;
    auto                                                const & predicate00623 = all;

    result00623 = collection00623.findLastThat ( predicate00623 );
    if ( ( result00623 != collection00623.end() ) != expectedValid00623 || expectedValid00623 && expectedValue00623 != * result00623 ) {
        pTestLib->logError( "'MCTC-00623-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00623-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findLastThatMatchingAllAndMore-cpp-xx : MCTC-00624-FT-findLastThatMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00624 = underTest;
    Iterator                                               result00624;
    auto                                                        expectedValid00624 = expectedResultFindLastThatAllAndMore;
    auto                                                        expectedValue00624 = expectedFindLastThatAllAndMore;
    auto                                                const & predicate00624 = allAndMore;

    result00624 = collection00624.findLastThat ( predicate00624 );
    if ( ( result00624 != collection00624.end() ) != expectedValid00624 || expectedValid00624 && expectedValue00624 != * result00624 ) {
        pTestLib->logError( "'MCTC-00624-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00624-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatStoreInMatchingNone-cpp-xx : MCTC-00625-FT-findAllThatStoreInMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00625 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00625;
    auto                                                        expectedSize00625 = expectedSizeFindAllThatNone;
    auto                                                const & expected00625 = expectedFindAllThatNone;
    auto                                                const & predicate00625 = none;

    (void) collection00625.findAllThat ( storeIn00625, predicate00625 );
    if ( storeIn00625.size() != expectedSize00625 || ! iteratorListEqualityCheck ( predicate00625, storeIn00625, expected00625 ) ) {
        pTestLib->logError( "'MCTC-00625-FT-findAllThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00625-FT-findAllThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatStoreInMatchingOne-cpp-xx : MCTC-00626-FT-findAllThatStoreInMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00626 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00626;
    auto                                                        expectedSize00626 = expectedSizeFindAllThatOne;
    auto                                                const & expected00626 = expectedFindAllThatOne;
    auto                                                const & predicate00626 = one;

    (void) collection00626.findAllThat ( storeIn00626, predicate00626 );
    if ( storeIn00626.size() != expectedSize00626 || ! iteratorListEqualityCheck ( predicate00626, storeIn00626, expected00626 ) ) {
        pTestLib->logError( "'MCTC-00626-FT-findAllThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00626-FT-findAllThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatStoreInMatchingMore-cpp-xx : MCTC-00627-FT-findAllThatStoreInMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00627 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00627;
    auto                                                        expectedSize00627 = expectedSizeFindAllThatMore;
    auto                                                const & expected00627 = expectedFindAllThatMore;
    auto                                                const & predicate00627 = more;

    (void) collection00627.findAllThat ( storeIn00627, predicate00627 );
    if ( storeIn00627.size() != expectedSize00627 || ! iteratorListEqualityCheck ( predicate00627, storeIn00627, expected00627 ) ) {
        pTestLib->logError( "'MCTC-00627-FT-findAllThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00627-FT-findAllThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatStoreInMatchingAll-cpp-xx : MCTC-00628-FT-findAllThatStoreInMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00628 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00628;
    auto                                                        expectedSize00628 = expectedSizeFindAllThatAll;
    auto                                                const & expected00628 = expectedFindAllThatAll;
    auto                                                const & predicate00628 = all;

    (void) collection00628.findAllThat ( storeIn00628, predicate00628 );
    if ( storeIn00628.size() != expectedSize00628 || ! iteratorListEqualityCheck ( predicate00628, storeIn00628, expected00628 ) ) {
        pTestLib->logError( "'MCTC-00628-FT-findAllThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00628-FT-findAllThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatStoreInMatchingAllAndMore-cpp-xx : MCTC-00629-FT-findAllThatStoreInMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00629 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00629;
    auto                                                        expectedSize00629 = expectedSizeFindAllThatAllAndMore;
    auto                                                const & expected00629 = expectedFindAllThatAllAndMore;
    auto                                                const & predicate00629 = allAndMore;

    (void) collection00629.findAllThat ( storeIn00629, predicate00629 );
    if ( storeIn00629.size() != expectedSize00629 || ! iteratorListEqualityCheck ( predicate00629, storeIn00629, expected00629 ) ) {
        pTestLib->logError( "'MCTC-00629-FT-findAllThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00629-FT-findAllThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatReturnedMatchingNone-cpp-xx : MCTC-00630-FT-findAllThatReturnedMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00630 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00630;
    auto                                                        expectedSize00630 = expectedSizeFindAllThatNone;
    auto                                                const & expected00630 = expectedFindAllThatNone;
    auto                                                const & predicate00630 = none;

    storeIn00630 = collection00630.template findAllThat < __ComparisonEquivalent > ( predicate00630 );
    if ( storeIn00630.size() != expectedSize00630 || ! iteratorListEqualityCheck ( predicate00630, storeIn00630, expected00630 ) ) {
        pTestLib->logError( "'MCTC-00630-FT-findAllThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00630-FT-findAllThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatReturnedMatchingOne-cpp-xx : MCTC-00631-FT-findAllThatReturnedMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00631 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00631;
    auto                                                        expectedSize00631 = expectedSizeFindAllThatOne;
    auto                                                const & expected00631 = expectedFindAllThatOne;
    auto                                                const & predicate00631 = one;

    storeIn00631 = collection00631.template findAllThat < __ComparisonEquivalent > ( predicate00631 );
    if ( storeIn00631.size() != expectedSize00631 || ! iteratorListEqualityCheck ( predicate00631, storeIn00631, expected00631 ) ) {
        pTestLib->logError( "'MCTC-00631-FT-findAllThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00631-FT-findAllThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatReturnedMatchingMore-cpp-xx : MCTC-00632-FT-findAllThatReturnedMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00632 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00632;
    auto                                                        expectedSize00632 = expectedSizeFindAllThatMore;
    auto                                                const & expected00632 = expectedFindAllThatMore;
    auto                                                const & predicate00632 = more;

    storeIn00632 = collection00632.template findAllThat < __ComparisonEquivalent > ( predicate00632 );
    if ( storeIn00632.size() != expectedSize00632 || ! iteratorListEqualityCheck ( predicate00632, storeIn00632, expected00632 ) ) {
        pTestLib->logError( "'MCTC-00632-FT-findAllThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00632-FT-findAllThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatReturnedMatchingAll-cpp-xx : MCTC-00633-FT-findAllThatReturnedMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00633 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00633;
    auto                                                        expectedSize00633 = expectedSizeFindAllThatAll;
    auto                                                const & expected00633 = expectedFindAllThatAll;
    auto                                                const & predicate00633 = all;

    storeIn00633 = collection00633.template findAllThat < __ComparisonEquivalent > ( predicate00633 );
    if ( storeIn00633.size() != expectedSize00633 || ! iteratorListEqualityCheck ( predicate00633, storeIn00633, expected00633 ) ) {
        pTestLib->logError( "'MCTC-00633-FT-findAllThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00633-FT-findAllThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-FindThat-findAllThatReturnedMatchingAllAndMore-cpp-xx : MCTC-00634-FT-findAllThatReturnedMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00634 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00634;
    auto                                                        expectedSize00634 = expectedSizeFindAllThatAllAndMore;
    auto                                                const & expected00634 = expectedFindAllThatAllAndMore;
    auto                                                const & predicate00634 = allAndMore;

    storeIn00634 = collection00634.template findAllThat < __ComparisonEquivalent > ( predicate00634 );
    if ( storeIn00634.size() != expectedSize00634 || ! iteratorListEqualityCheck ( predicate00634, storeIn00634, expected00634 ) ) {
        pTestLib->logError( "'MCTC-00634-FT-findAllThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00634-FT-findAllThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
    }

    return true;
}

/* MutableCollectionTestGroup-FindOf-cpp-xx : MCTG-00700-FO-cpp-xx. MCTC-00701-FO to MCTC-00768-FO */
template <
        typename __IterableType,                                                                /* NOLINT(bugprone-reserved-identifier) */
        typename __ElementType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
        template < typename ... > class __ComparisonEquivalent = cds :: Array   /* NOLINT(bugprone-reserved-identifier) */
> auto mutableCollectionTestGroupFindOf (
        Test                                                      * pTestLib,
        StringLiteral                                               variant,
        cds :: MutableCollection < __ElementType > & underTest,
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
    using Iterator = typename cds :: MutableCollection < __ElementType > :: Iterator;

    /* MutableCollectionTestCase-FindOf-findOfStoreInMatchingNone-cpp-xx : MCTC-00701-FO-findOfStoreInMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00701 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00701;
    auto                                                        expectedSize00701 = expectedSizeFindOfNone;
    auto                                                const & expected00701 = expectedFindOfNone;
    auto                                                const & target00701 = none;

    (void) collection00701.findOf ( limit, storeIn00701, target00701 );
    if ( storeIn00701.size() != expectedSize00701 || ! iteratorListEqualityCheckNoPred ( storeIn00701, expected00701 ) ) {
        pTestLib->logError( "'MCTC-00701-FO-findOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00701-FO-findOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfStoreInMatchingOne-cpp-xx : MCTC-00702-FO-findOfStoreInMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00702 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00702;
    auto                                                        expectedSize00702 = expectedSizeFindOfOne;
    auto                                                const & expected00702 = expectedFindOfOne;
    auto                                                const & target00702 = one;

    (void) collection00702.findOf ( limit, storeIn00702, target00702 );
    if ( storeIn00702.size() != expectedSize00702 || ! iteratorListEqualityCheckNoPred ( storeIn00702, expected00702 ) ) {
        pTestLib->logError( "'MCTC-00702-FO-findOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00702-FO-findOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfStoreInMatchingMoreLessThanLimit-cpp-xx : MCTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00703 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00703;
    auto                                                        expectedSize00703 = expectedSizeFindOfMoreLessThanLimit;
    auto                                                const & expected00703 = expectedFindOfMoreLessThanLimit;
    auto                                                const & target00703 = moreLessThanLimit;

    (void) collection00703.findOf ( limit, storeIn00703, target00703 );
    if ( storeIn00703.size() != expectedSize00703 || ! iteratorListEqualityCheckNoPred ( storeIn00703, expected00703 ) ) {
        pTestLib->logError( "'MCTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfStoreInMatchingMore-cpp-xx : MCTC-00704-FO-findOfStoreInMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00704 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00704;
    auto                                                        expectedSize00704 = expectedSizeFindOfMore;
    auto                                                const & expected00704 = expectedFindOfMore;
    auto                                                const & target00704 = more;

    (void) collection00704.findOf ( limit, storeIn00704, target00704 );
    if ( storeIn00704.size() != expectedSize00704 || ! iteratorListEqualityCheckNoPred ( storeIn00704, expected00704 ) ) {
        pTestLib->logError( "'MCTC-00704-FO-findOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00704-FO-findOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfStoreInMatchingMoreMoreThanLimit-cpp-xx : MCTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00705 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00705;
    auto                                                        expectedSize00705 = expectedSizeFindOfMoreMoreThanLimit;
    auto                                                const & expected00705 = expectedFindOfMoreMoreThanLimit;
    auto                                                const & target00705 = moreMoreThanLimit;

    (void) collection00705.findOf ( limit, storeIn00705, target00705 );
    if ( storeIn00705.size() != expectedSize00705 || ! iteratorListEqualityCheckNoPred ( storeIn00705, expected00705 ) ) {
        pTestLib->logError( "'MCTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfStoreInMatchingAll-cpp-xx : MCTC-00706-FO-findOfStoreInMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00706 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00706;
    auto                                                        expectedSize00706 = expectedSizeFindOfAll;
    auto                                                const & expected00706 = expectedFindOfAll;
    auto                                                const & target00706 = all;

    (void) collection00706.findOf ( limit, storeIn00706, target00706 );
    if ( storeIn00706.size() != expectedSize00706 || ! iteratorListEqualityCheckNoPred ( storeIn00706, expected00706 ) ) {
        pTestLib->logError( "'MCTC-00706-FO-findOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00706-FO-findOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfStoreInMatchingAllAndMore-cpp-xx : MCTC-00707-FO-findOfStoreInMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00707 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00707;
    auto                                                        expectedSize00707 = expectedSizeFindOfAllAndMore;
    auto                                                const & expected00707 = expectedFindOfAllAndMore;
    auto                                                const & target00707 = allAndMore;

    (void) collection00707.findOf ( limit, storeIn00707, target00707 );
    if ( storeIn00707.size() != expectedSize00707 || ! iteratorListEqualityCheckNoPred ( storeIn00707, expected00707 ) ) {
        pTestLib->logError( "'MCTC-00707-FO-findOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00707-FO-findOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfReturnedMatchingNone-cpp-xx : MCTC-00708-FO-findOfReturnedMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00708 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00708;
    auto                                                        expectedSize00708 = expectedSizeFindOfNone;
    auto                                                const & expected00708 = expectedFindOfNone;
    auto                                                const & target00708 = none;

    storeIn00708 = collection00708.template findOf < __ComparisonEquivalent > ( limit, target00708 );
    if ( storeIn00708.size() != expectedSize00708 || ! iteratorListEqualityCheckNoPred ( storeIn00708, expected00708 ) ) {
        pTestLib->logError( "'MCTC-00708-FO-findOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00708-FO-findOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfReturnedMatchingOne-cpp-xx : MCTC-00709-FO-findOfReturnedMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00709 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00709;
    auto                                                        expectedSize00709 = expectedSizeFindOfOne;
    auto                                                const & expected00709 = expectedFindOfOne;
    auto                                                const & target00709 = one;

    storeIn00709 = collection00709.template findOf < __ComparisonEquivalent > ( limit, target00709 );
    if ( storeIn00709.size() != expectedSize00709 || ! iteratorListEqualityCheckNoPred ( storeIn00709, expected00709 ) ) {
        pTestLib->logError( "'MCTC-00709-FO-findOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00709-FO-findOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfReturnedMatchingMoreLessThanLimit-cpp-xx : MCTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00710 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00710;
    auto                                                        expectedSize00710 = expectedSizeFindOfMoreLessThanLimit;
    auto                                                const & expected00710 = expectedFindOfMoreLessThanLimit;
    auto                                                const & target00710 = moreLessThanLimit;

    storeIn00710 = collection00710.template findOf < __ComparisonEquivalent > ( limit, target00710 );
    if ( storeIn00710.size() != expectedSize00710 || ! iteratorListEqualityCheckNoPred ( storeIn00710, expected00710 ) ) {
        pTestLib->logError( "'MCTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfReturnedMatchingMore-cpp-xx : MCTC-00711-FO-findOfReturnedMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00711 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00711;
    auto                                                        expectedSize00711 = expectedSizeFindOfMore;
    auto                                                const & expected00711 = expectedFindOfMore;
    auto                                                const & target00711 = more;

    storeIn00711 = collection00711.template findOf < __ComparisonEquivalent > ( limit, target00711 );
    if ( storeIn00711.size() != expectedSize00711 || ! iteratorListEqualityCheckNoPred ( storeIn00711, expected00711 ) ) {
        pTestLib->logError( "'MCTC-00711-FO-findOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00711-FO-findOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfReturnedMatchingMoreMoreThanLimit-cpp-xx : MCTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00712 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00712;
    auto                                                        expectedSize00712 = expectedSizeFindOfMoreMoreThanLimit;
    auto                                                const & expected00712 = expectedFindOfMoreMoreThanLimit;
    auto                                                const & target00712 = moreMoreThanLimit;

    storeIn00712 = collection00712.template findOf < __ComparisonEquivalent > ( limit, target00712 );
    if ( storeIn00712.size() != expectedSize00712 || ! iteratorListEqualityCheckNoPred ( storeIn00712, expected00712 ) ) {
        pTestLib->logError( "'MCTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfReturnedMatchingAll-cpp-xx : MCTC-00713-FO-findOfReturnedMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00713 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00713;
    auto                                                        expectedSize00713 = expectedSizeFindOfAll;
    auto                                                const & expected00713 = expectedFindOfAll;
    auto                                                const & target00713 = all;

    storeIn00713 = collection00713.template findOf < __ComparisonEquivalent > ( limit, target00713 );
    if ( storeIn00713.size() != expectedSize00713 || ! iteratorListEqualityCheckNoPred ( storeIn00713, expected00713 ) ) {
        pTestLib->logError( "'MCTC-00713-FO-findOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00713-FO-findOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findOfReturnedMatchingAllAndMore-cpp-xx : MCTC-00714-FO-findOfReturnedMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00714 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00714;
    auto                                                        expectedSize00714 = expectedSizeFindOfAllAndMore;
    auto                                                const & expected00714 = expectedFindOfAllAndMore;
    auto                                                const & target00714 = allAndMore;

    storeIn00714 = collection00714.template findOf < __ComparisonEquivalent > ( limit, target00714 );
    if ( storeIn00714.size() != expectedSize00714 || ! iteratorListEqualityCheckNoPred ( storeIn00714, expected00714 ) ) {
        pTestLib->logError( "'MCTC-00714-FO-findOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00714-FO-findOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstOfMatchingNone-cpp-xx : MCTC-00715-FO-findFirstOfMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00715 = underTest;
    Iterator                                               result00715;
    auto                                                        expectedResult00715 = expectedResultFindFirstOfNone;
    auto                                                const & expected00715 = expectedFindFirstOfNone;
    auto                                                const & target00715 = none;

    result00715 = collection00715.findFirstOf ( target00715 );
    if ( ( result00715 != collection00715.end() ) != expectedResult00715 || expectedResult00715 && expected00715 != * result00715 ) {
        pTestLib->logError( "'MCTC-00715-FO-findFirstOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00715-FO-findFirstOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstOfMatchingOne-cpp-xx : MCTC-00716-FO-findFirstOfMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00716 = underTest;
    Iterator                                               result00716;
    auto                                                        expectedResult00716 = expectedResultFindFirstOfOne;
    auto                                                const & expected00716 = expectedFindFirstOfOne;
    auto                                                const & target00716 = one;

    result00716 = collection00716.findFirstOf ( target00716 );
    if ( ( result00716 != collection00716.end() ) != expectedResult00716 || expectedResult00716 && expected00716 != * result00716 ) {
        pTestLib->logError( "'MCTC-00716-FO-findFirstOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00716-FO-findFirstOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstOfMatchingMore-cpp-xx : MCTC-00717-FO-findFirstOfMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00717 = underTest;
    Iterator                                               result00717;
    auto                                                        expectedResult00717 = expectedResultFindFirstOfMore;
    auto                                                const & expected00717 = expectedFindFirstOfMore;
    auto                                                const & target00717 = more;

    result00717 = collection00717.findFirstOf ( target00717 );
    if ( ( result00717 != collection00717.end() ) != expectedResult00717 || expectedResult00717 && expected00717 != * result00717 ) {
        pTestLib->logError( "'MCTC-00717-FO-findFirstOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00717-FO-findFirstOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstOfMatchingAll-cpp-xx : MCTC-00718-FO-findFirstOfMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00718 = underTest;
    Iterator                                               result00718;
    auto                                                        expectedResult00718 = expectedResultFindFirstOfAll;
    auto                                                const & expected00718 = expectedFindFirstOfAll;
    auto                                                const & target00718 = all;

    result00718 = collection00718.findFirstOf ( target00718 );
    if ( ( result00718 != collection00718.end() ) != expectedResult00718 || expectedResult00718 && expected00718 != * result00718 ) {
        pTestLib->logError( "'MCTC-00718-FO-findFirstOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00718-FO-findFirstOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstOfMatchingAllAndMore-cpp-xx : MCTC-00719-FO-findFirstOfMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00719 = underTest;
    Iterator                                               result00719;
    auto                                                        expectedResult00719 = expectedResultFindFirstOfAllAndMore;
    auto                                                const & expected00719 = expectedFindFirstOfAllAndMore;
    auto                                                const & target00719 = allAndMore;

    result00719 = collection00719.findFirstOf ( target00719 );
    if ( ( result00719 != collection00719.end() ) != expectedResult00719 || expectedResult00719 && expected00719 != * result00719 ) {
        pTestLib->logError( "'MCTC-00719-FO-findFirstOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00719-FO-findFirstOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastOfMatchingNone-cpp-xx : MCTC-00720-FO-findLastOfMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00720 = underTest;
    Iterator                                               result00720;
    auto                                                        expectedResult00720 = expectedResultFindLastOfNone;
    auto                                                const & expected00720 = expectedFindLastOfNone;
    auto                                                const & target00720 = none;

    result00720 = collection00720.findLastOf ( target00720 );
    if ( ( result00720 != collection00720.end() ) != expectedResult00720 || expectedResult00720 && expected00720 != * result00720 ) {
        pTestLib->logError( "'MCTC-00720-FO-findLastOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00720-FO-findLastOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastOfMatchingOne-cpp-xx : MCTC-00721-FO-findLastOfMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00721 = underTest;
    Iterator                                               result00721;
    auto                                                        expectedResult00721 = expectedResultFindLastOfOne;
    auto                                                const & expected00721 = expectedFindLastOfOne;
    auto                                                const & target00721 = one;

    result00721 = collection00721.findLastOf ( target00721 );
    if ( ( result00721 != collection00721.end() ) != expectedResult00721 || expectedResult00721 && expected00721 != * result00721 ) {
        pTestLib->logError( "'MCTC-00721-FO-findLastOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00721-FO-findLastOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastOfMatchingMore-cpp-xx : MCTC-00722-FO-findLastOfMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00722 = underTest;
    Iterator                                               result00722;
    auto                                                        expectedResult00722 = expectedResultFindLastOfMore;
    auto                                                const & expected00722 = expectedFindLastOfMore;
    auto                                                const & target00722 = more;

    result00722 = collection00722.findLastOf ( target00722 );
    if ( ( result00722 != collection00722.end() ) != expectedResult00722 || expectedResult00722 && expected00722 != * result00722 ) {
        pTestLib->logError( "'MCTC-00722-FO-findLastOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00722-FO-findLastOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastOfMatchingAll-cpp-xx : MCTC-00723-FO-findLastOfMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00723 = underTest;
    Iterator                                               result00723;
    auto                                                        expectedResult00723 = expectedResultFindLastOfAll;
    auto                                                const & expected00723 = expectedFindLastOfAll;
    auto                                                const & target00723 = all;

    result00723 = collection00723.findLastOf ( target00723 );
    if ( ( result00723 != collection00723.end() ) != expectedResult00723 || expectedResult00723 && expected00723 != * result00723 ) {
        pTestLib->logError( "'MCTC-00723-FO-findLastOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00723-FO-findLastOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastOfMatchingAllAndMore-cpp-xx : MCTC-00724-FO-findLastOfMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00724 = underTest;
    Iterator                                               result00724;
    auto                                                        expectedResult00724 = expectedResultFindLastOfAllAndMore;
    auto                                                const & expected00724 = expectedFindLastOfAllAndMore;
    auto                                                const & target00724 = allAndMore;

    result00724 = collection00724.findLastOf ( target00724 );
    if ( ( result00724 != collection00724.end() ) != expectedResult00724 || expectedResult00724 && expected00724 != * result00724 ) {
        pTestLib->logError( "'MCTC-00724-FO-findLastOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00724-FO-findLastOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfStoreInMatchingNone-cpp-xx : MCTC-00725-FO-findAllOfStoreInMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00725 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00725;
    auto                                                        expectedSize00725 = expectedSizeFindAllOfNone;
    auto                                                const & expected00725 = expectedFindAllOfNone;
    auto                                                const & target00725 = none;

    (void) collection00725.findAllOf ( storeIn00725, target00725 );
    if ( storeIn00725.size() != expectedSize00725 || ! iteratorListEqualityCheckNoPred ( storeIn00725, expected00725 ) ) {
        pTestLib->logError( "'MCTC-00725-FO-findAllOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00725-FO-findAllOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfStoreInMatchingOne-cpp-xx : MCTC-00726-FO-findAllOfStoreInMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00726 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00726;
    auto                                                        expectedSize00726 = expectedSizeFindAllOfOne;
    auto                                                const & expected00726 = expectedFindAllOfOne;
    auto                                                const & target00726 = one;

    (void) collection00726.findAllOf ( storeIn00726, target00726 );
    if ( storeIn00726.size() != expectedSize00726 || ! iteratorListEqualityCheckNoPred ( storeIn00726, expected00726 ) ) {
        pTestLib->logError( "'MCTC-00726-FO-findAllOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00726-FO-findAllOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfStoreInMatchingMore-cpp-xx : MCTC-00727-FO-findAllOfStoreInMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00727 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00727;
    auto                                                        expectedSize00727 = expectedSizeFindAllOfMore;
    auto                                                const & expected00727 = expectedFindAllOfMore;
    auto                                                const & target00727 = more;

    (void) collection00727.findAllOf ( storeIn00727, target00727 );
    if ( storeIn00727.size() != expectedSize00727 || ! iteratorListEqualityCheckNoPred ( storeIn00727, expected00727 ) ) {
        pTestLib->logError( "'MCTC-00727-FO-findAllOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00727-FO-findAllOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfStoreInMatchingAll-cpp-xx : MCTC-00728-FO-findAllOfStoreInMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00728 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00728;
    auto                                                        expectedSize00728 = expectedSizeFindAllOfAll;
    auto                                                const & expected00728 = expectedFindAllOfAll;
    auto                                                const & target00728 = all;

    (void) collection00728.findAllOf ( storeIn00728, target00728 );
    if ( storeIn00728.size() != expectedSize00728 || ! iteratorListEqualityCheckNoPred ( storeIn00728, expected00728 ) ) {
        pTestLib->logError( "'MCTC-00728-FO-findAllOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00728-FO-findAllOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfStoreInMatchingAllAndMore-cpp-xx : MCTC-00729-FO-findAllOfStoreInMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00729 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00729;
    auto                                                        expectedSize00729 = expectedSizeFindAllOfAllAndMore;
    auto                                                const & expected00729 = expectedFindAllOfAllAndMore;
    auto                                                const & target00729 = allAndMore;

    (void) collection00729.findAllOf ( storeIn00729, target00729 );
    if ( storeIn00729.size() != expectedSize00729 || ! iteratorListEqualityCheckNoPred ( storeIn00729, expected00729 ) ) {
        pTestLib->logError( "'MCTC-00729-FO-findAllOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00729-FO-findAllOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfReturnedMatchingNone-cpp-xx : MCTC-00730-FO-findAllOfReturnedMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00730 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00730;
    auto                                                        expectedSize00730 = expectedSizeFindAllOfNone;
    auto                                                const & expected00730 = expectedFindAllOfNone;
    auto                                                const & target00730 = none;

    storeIn00730 = collection00730.template findAllOf < __ComparisonEquivalent > ( target00730 );
    if ( storeIn00730.size() != expectedSize00730 || ! iteratorListEqualityCheckNoPred ( storeIn00730, expected00730 ) ) {
        pTestLib->logError( "'MCTC-00730-FO-findAllOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00730-FO-findAllOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfReturnedMatchingOne-cpp-xx : MCTC-00731-FO-findAllOfReturnedMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00731 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00731;
    auto                                                        expectedSize00731 = expectedSizeFindAllOfOne;
    auto                                                const & expected00731 = expectedFindAllOfOne;
    auto                                                const & target00731 = one;

    storeIn00731 = collection00731.template findAllOf < __ComparisonEquivalent > ( target00731 );
    if ( storeIn00731.size() != expectedSize00731 || ! iteratorListEqualityCheckNoPred ( storeIn00731, expected00731 ) ) {
        pTestLib->logError( "'MCTC-00731-FO-findAllOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00731-FO-findAllOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfReturnedMatchingMore-cpp-xx : MCTC-00732-FO-findAllOfReturnedMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00732 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00732;
    auto                                                        expectedSize00732 = expectedSizeFindAllOfMore;
    auto                                                const & expected00732 = expectedFindAllOfMore;
    auto                                                const & target00732 = more;

    storeIn00732 = collection00732.template findAllOf < __ComparisonEquivalent > ( target00732 );
    if ( storeIn00732.size() != expectedSize00732 || ! iteratorListEqualityCheckNoPred ( storeIn00732, expected00732 ) ) {
        pTestLib->logError( "'MCTC-00732-FO-findAllOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00732-FO-findAllOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfReturnedMatchingAll-cpp-xx : MCTC-00733-FO-findAllOfReturnedMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00733 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00733;
    auto                                                        expectedSize00733 = expectedSizeFindAllOfAll;
    auto                                                const & expected00733 = expectedFindAllOfAll;
    auto                                                const & target00733 = all;

    storeIn00733 = collection00733.template findAllOf < __ComparisonEquivalent > ( target00733 );
    if ( storeIn00733.size() != expectedSize00733 || ! iteratorListEqualityCheckNoPred ( storeIn00733, expected00733 ) ) {
        pTestLib->logError( "'MCTC-00733-FO-findAllOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00733-FO-findAllOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllOfReturnedMatchingAllAndMore-cpp-xx : MCTC-00734-FO-findAllOfReturnedMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00734 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00734;
    auto                                                        expectedSize00734 = expectedSizeFindAllOfAllAndMore;
    auto                                                const & expected00734 = expectedFindAllOfAllAndMore;
    auto                                                const & target00734 = allAndMore;

    storeIn00734 = collection00734.template findAllOf < __ComparisonEquivalent > ( target00734 );
    if ( storeIn00734.size() != expectedSize00734 || ! iteratorListEqualityCheckNoPred ( storeIn00734, expected00734 ) ) {
        pTestLib->logError( "'MCTC-00734-FO-findAllOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00734-FO-findAllOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfStoreInMatchingNone-cpp-xx : MCTC-00735-FO-findNotOfStoreInMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00735 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00735;
    auto                                                        expectedSize00735 = expectedSizeFindNotOfNone;
    auto                                                const & expected00735 = expectedFindNotOfNone;
    auto                                                const & target00735 = none;

    (void) collection00735.findNotOf ( limit, storeIn00735, target00735 );
    if ( storeIn00735.size() != expectedSize00735 || ! iteratorListEqualityCheckNoPred ( storeIn00735, expected00735 ) ) {
        pTestLib->logError( "'MCTC-00735-FO-findNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00735-FO-findNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfStoreInMatchingOne-cpp-xx : MCTC-00736-FO-findNotOfStoreInMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00736 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00736;
    auto                                                        expectedSize00736 = expectedSizeFindNotOfOne;
    auto                                                const & expected00736 = expectedFindNotOfOne;
    auto                                                const & target00736 = one;

    (void) collection00736.findNotOf ( limit, storeIn00736, target00736 );
    if ( storeIn00736.size() != expectedSize00736 || ! iteratorListEqualityCheckNoPred ( storeIn00736, expected00736 ) ) {
        pTestLib->logError( "'MCTC-00736-FO-findNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00736-FO-findNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfStoreInMatchingMoreLessThanLimit-cpp-xx : MCTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00737 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00737;
    auto                                                        expectedSize00737 = expectedSizeFindNotOfMoreLessThanLimit;
    auto                                                const & expected00737 = expectedFindNotOfMoreLessThanLimit;
    auto                                                const & target00737 = moreLessThanLimit;

    (void) collection00737.findNotOf ( limit, storeIn00737, target00737 );
    if ( storeIn00737.size() != expectedSize00737 || ! iteratorListEqualityCheckNoPred ( storeIn00737, expected00737 ) ) {
        pTestLib->logError( "'MCTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfStoreInMatchingMore-cpp-xx : MCTC-00738-FO-findNotOfStoreInMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00738 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00738;
    auto                                                        expectedSize00738 = expectedSizeFindNotOfMore;
    auto                                                const & expected00738 = expectedFindNotOfMore;
    auto                                                const & target00738 = more;

    (void) collection00738.findNotOf ( limit, storeIn00738, target00738 );
    if ( storeIn00738.size() != expectedSize00738 || ! iteratorListEqualityCheckNoPred ( storeIn00738, expected00738 ) ) {
        pTestLib->logError( "'MCTC-00738-FO-findNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00738-FO-findNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfStoreInMatchingMoreMoreThanLimit-cpp-xx : MCTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00739 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00739;
    auto                                                        expectedSize00739 = expectedSizeFindNotOfMoreMoreThanLimit;
    auto                                                const & expected00739 = expectedFindNotOfMoreMoreThanLimit;
    auto                                                const & target00739 = moreMoreThanLimit;

    (void) collection00739.findNotOf ( limit, storeIn00739, target00739 );
    if ( storeIn00739.size() != expectedSize00739 || ! iteratorListEqualityCheckNoPred ( storeIn00739, expected00739 ) ) {
        pTestLib->logError( "'MCTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfStoreInMatchingAll-cpp-xx : MCTC-00740-FO-findNotOfStoreInMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00740 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00740;
    auto                                                        expectedSize00740 = expectedSizeFindNotOfAll;
    auto                                                const & expected00740 = expectedFindNotOfAll;
    auto                                                const & target00740 = all;

    (void) collection00740.findNotOf ( limit, storeIn00740, target00740 );
    if ( storeIn00740.size() != expectedSize00740 || ! iteratorListEqualityCheckNoPred ( storeIn00740, expected00740 ) ) {
        pTestLib->logError( "'MCTC-00740-FO-findNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00740-FO-findNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfStoreInMatchingAllAndMore-cpp-xx : MCTC-00741-FO-findNotOfStoreInMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00741 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00741;
    auto                                                        expectedSize00741 = expectedSizeFindNotOfAllAndMore;
    auto                                                const & expected00741 = expectedFindNotOfAllAndMore;
    auto                                                const & target00741 = allAndMore;

    (void) collection00741.findNotOf ( limit, storeIn00741, target00741 );
    if ( storeIn00741.size() != expectedSize00741 || ! iteratorListEqualityCheckNoPred ( storeIn00741, expected00741 ) ) {
        pTestLib->logError( "'MCTC-00741-FO-findNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00741-FO-findNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfReturnedMatchingNone-cpp-xx : MCTC-00742-FO-findNotOfReturnedMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00742 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00742;
    auto                                                        expectedSize00742 = expectedSizeFindNotOfNone;
    auto                                                const & expected00742 = expectedFindNotOfNone;
    auto                                                const & target00742 = none;

    storeIn00742 = collection00742.template findNotOf < __ComparisonEquivalent > ( limit, target00742 );
    if ( storeIn00742.size() != expectedSize00742 || ! iteratorListEqualityCheckNoPred ( storeIn00742, expected00742 ) ) {
        pTestLib->logError( "'MCTC-00742-FO-findNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00742-FO-findNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfReturnedMatchingOne-cpp-xx : MCTC-00743-FO-findNotOfReturnedMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00743 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00743;
    auto                                                        expectedSize00743 = expectedSizeFindNotOfOne;
    auto                                                const & expected00743 = expectedFindNotOfOne;
    auto                                                const & target00743 = one;

    storeIn00743 = collection00743.template findNotOf < __ComparisonEquivalent > ( limit, target00743 );
    if ( storeIn00743.size() != expectedSize00743 || ! iteratorListEqualityCheckNoPred ( storeIn00743, expected00743 ) ) {
        pTestLib->logError( "'MCTC-00743-FO-findNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00743-FO-findNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfReturnedMatchingMoreLessThanLimit-cpp-xx : MCTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00744 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00744;
    auto                                                        expectedSize00744 = expectedSizeFindNotOfMoreLessThanLimit;
    auto                                                const & expected00744 = expectedFindNotOfMoreLessThanLimit;
    auto                                                const & target00744 = moreLessThanLimit;

    storeIn00744 = collection00744.template findNotOf < __ComparisonEquivalent > ( limit, target00744 );
    if ( storeIn00744.size() != expectedSize00744 || ! iteratorListEqualityCheckNoPred ( storeIn00744, expected00744 ) ) {
        pTestLib->logError( "'MCTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfReturnedMatchingMore-cpp-xx : MCTC-00745-FO-findNotOfReturnedMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00745 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00745;
    auto                                                        expectedSize00745 = expectedSizeFindNotOfMore;
    auto                                                const & expected00745 = expectedFindNotOfMore;
    auto                                                const & target00745 = more;

    storeIn00745 = collection00745.template findNotOf < __ComparisonEquivalent > ( limit, target00745 );
    if ( storeIn00745.size() != expectedSize00745 || ! iteratorListEqualityCheckNoPred ( storeIn00745, expected00745 ) ) {
        pTestLib->logError( "'MCTC-00745-FO-findNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00745-FO-findNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfReturnedMatchingMoreMoreThanLimit-cpp-xx : MCTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00746 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00746;
    auto                                                        expectedSize00746 = expectedSizeFindNotOfMoreMoreThanLimit;
    auto                                                const & expected00746 = expectedFindNotOfMoreMoreThanLimit;
    auto                                                const & target00746 = moreMoreThanLimit;

    storeIn00746 = collection00746.template findNotOf < __ComparisonEquivalent > ( limit, target00746 );
    if ( storeIn00746.size() != expectedSize00746 || ! iteratorListEqualityCheckNoPred ( storeIn00746, expected00746 ) ) {
        pTestLib->logError( "'MCTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfReturnedMatchingAll-cpp-xx : MCTC-00747-FO-findNotOfReturnedMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00747 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00747;
    auto                                                        expectedSize00747 = expectedSizeFindNotOfAll;
    auto                                                const & expected00747 = expectedFindNotOfAll;
    auto                                                const & target00747 = all;

    storeIn00747 = collection00747.template findNotOf < __ComparisonEquivalent > ( limit, target00747 );
    if ( storeIn00747.size() != expectedSize00747 || ! iteratorListEqualityCheckNoPred ( storeIn00747, expected00747 ) ) {
        pTestLib->logError( "'MCTC-00747-FO-findNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00747-FO-findNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findNotOfReturnedMatchingAllAndMore-cpp-xx : MCTC-00748-FO-findNotOfReturnedMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00748 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00748;
    auto                                                        expectedSize00748 = expectedSizeFindNotOfAllAndMore;
    auto                                                const & expected00748 = expectedFindNotOfAllAndMore;
    auto                                                const & target00748 = allAndMore;

    storeIn00748 = collection00748.template findNotOf < __ComparisonEquivalent > ( limit, target00748 );
    if ( storeIn00748.size() != expectedSize00748 || ! iteratorListEqualityCheckNoPred ( storeIn00748, expected00748 ) ) {
        pTestLib->logError( "'MCTC-00748-FO-findNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00748-FO-findNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstNotOfMatchingNone-cpp-xx : MCTC-00749-FO-findFirstNotOfMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00749 = underTest;
    Iterator                                               result00749;
    auto                                                        expectedResult00749 = expectedResultFindFirstNotOfNone;
    auto                                                const & expected00749 = expectedFindFirstNotOfNone;
    auto                                                const & target00749 = none;

    result00749 = collection00749.findFirstNotOf ( target00749 );
    if ( ( result00749 != collection00749.end() ) != expectedResult00749 || expectedResult00749 && expected00749 != * result00749 ) {
        pTestLib->logError( "'MCTC-00749-FO-findFirstNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00749-FO-findFirstNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstNotOfMatchingOne-cpp-xx : MCTC-00750-FO-findFirstNotOfMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00750 = underTest;
    Iterator                                               result00750;
    auto                                                        expectedResult00750 = expectedResultFindFirstNotOfOne;
    auto                                                const & expected00750 = expectedFindFirstNotOfOne;
    auto                                                const & target00750 = one;

    result00750 = collection00750.findFirstNotOf ( target00750 );
    if ( ( result00750 != collection00750.end() ) != expectedResult00750 || expectedResult00750 && expected00750 != * result00750 ) {
        pTestLib->logError( "'MCTC-00750-FO-findFirstNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00750-FO-findFirstNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstNotOfMatchingMore-cpp-xx : MCTC-00751-FO-findFirstNotOfMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00751 = underTest;
    Iterator                                               result00751;
    auto                                                        expectedResult00751 = expectedResultFindFirstNotOfMore;
    auto                                                const & expected00751 = expectedFindFirstNotOfMore;
    auto                                                const & target00751 = more;

    result00751 = collection00751.findFirstNotOf ( target00751 );
    if ( ( result00751 != collection00751.end() ) != expectedResult00751 || expectedResult00751 && expected00751 != * result00751 ) {
        pTestLib->logError( "'MCTC-00751-FO-findFirstNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00751-FO-findFirstNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstNotOfMatchingAll-cpp-xx : MCTC-00752-FO-findFirstNotOfMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00752 = underTest;
    Iterator                                               result00752;
    auto                                                        expectedResult00752 = expectedResultFindFirstNotOfAll;
    auto                                                const & expected00752 = expectedFindFirstNotOfAll;
    auto                                                const & target00752 = all;

    result00752 = collection00752.findFirstNotOf ( target00752 );
    if ( ( result00752 != collection00752.end() ) != expectedResult00752 || expectedResult00752 && expected00752 != * result00752 ) {
        pTestLib->logError( "'MCTC-00752-FO-findFirstNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00752-FO-findFirstNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findFirstNotOfMatchingAllAndMore-cpp-xx : MCTC-00753-FO-findFirstNotOfMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00753 = underTest;
    Iterator                                               result00753;
    auto                                                        expectedResult00753 = expectedResultFindFirstNotOfAllAndMore;
    auto                                                const & expected00753 = expectedFindFirstNotOfAllAndMore;
    auto                                                const & target00753 = allAndMore;

    result00753 = collection00753.findFirstNotOf ( target00753 );
    if ( ( result00753 != collection00753.end() ) != expectedResult00753 || expectedResult00753 && expected00753 != * result00753 ) {
        pTestLib->logError( "'MCTC-00753-FO-findFirstNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00753-FO-findFirstNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastNotOfMatchingNone-cpp-xx : MCTC-00754-FO-findLastNotOfMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00754 = underTest;
    Iterator                                               result00754;
    auto                                                        expectedResult00754 = expectedResultFindLastNotOfNone;
    auto                                                const & expected00754 = expectedFindLastNotOfNone;
    auto                                                const & target00754 = none;

    result00754 = collection00754.findLastNotOf ( target00754 );
    if ( ( result00754 != collection00754.end() ) != expectedResult00754 || expectedResult00754 && expected00754 != * result00754 ) {
        pTestLib->logError( "'MCTC-00754-FO-findLastNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00754-FO-findLastNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastNotOfMatchingOne-cpp-xx : MCTC-00755-FO-findLastNotOfMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00755 = underTest;
    Iterator                                               result00755;
    auto                                                        expectedResult00755 = expectedResultFindLastNotOfOne;
    auto                                                const & expected00755 = expectedFindLastNotOfOne;
    auto                                                const & target00755 = one;

    result00755 = collection00755.findLastNotOf ( target00755 );
    if ( ( result00755 != collection00755.end() ) != expectedResult00755 || expectedResult00755 && expected00755 != * result00755 ) {
        pTestLib->logError( "'MCTC-00755-FO-findLastNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00755-FO-findLastNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastNotOfMatchingMore-cpp-xx : MCTC-00756-FO-findLastNotOfMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00756 = underTest;
    Iterator                                               result00756;
    auto                                                        expectedResult00756 = expectedResultFindLastNotOfMore;
    auto                                                const & expected00756 = expectedFindLastNotOfMore;
    auto                                                const & target00756 = more;

    result00756 = collection00756.findLastNotOf ( target00756 );
    if ( ( result00756 != collection00756.end() ) != expectedResult00756 || expectedResult00756 && expected00756 != * result00756 ) {
        pTestLib->logError( "'MCTC-00756-FO-findLastNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00756-FO-findLastNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastNotOfMatchingAll-cpp-xx : MCTC-00757-FO-findLastNotOfMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00757 = underTest;
    Iterator                                               result00757;
    auto                                                        expectedResult00757 = expectedResultFindLastNotOfAll;
    auto                                                const & expected00757 = expectedFindLastNotOfAll;
    auto                                                const & target00757 = all;

    result00757 = collection00757.findLastNotOf ( target00757 );
    if ( ( result00757 != collection00757.end() ) != expectedResult00757 || expectedResult00757 && expected00757 != * result00757 ) {
        pTestLib->logError( "'MCTC-00757-FO-findLastNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00757-FO-findLastNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findLastOfMatchingAllAndMore-cpp-xx : MCTC-00758-FO-findLastNotOfMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00758 = underTest;
    Iterator                                               result00758;
    auto                                                        expectedResult00758 = expectedResultFindLastNotOfAllAndMore;
    auto                                                const & expected00758 = expectedFindLastNotOfAllAndMore;
    auto                                                const & target00758 = allAndMore;

    result00758 = collection00758.findLastNotOf ( target00758 );
    if ( ( result00758 != collection00758.end() ) != expectedResult00758 || expectedResult00758 && expected00758 != * result00758 ) {
        pTestLib->logError( "'MCTC-00758-FO-findLastNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00758-FO-findLastNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfStoreInMatchingNone-cpp-xx : MCTC-00759-FO-findAllNotOfStoreInMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00759 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00759;
    auto                                                        expectedSize00759 = expectedSizeFindAllNotOfNone;
    auto                                                const & expected00759 = expectedFindAllNotOfNone;
    auto                                                const & target00759 = none;

    (void) collection00759.findAllNotOf ( storeIn00759, target00759 );
    if ( storeIn00759.size() != expectedSize00759 || ! iteratorListEqualityCheckNoPred ( storeIn00759, expected00759 ) ) {
        pTestLib->logError( "'MCTC-00759-FO-findAllNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00759-FO-findAllNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfStoreInMatchingOne-cpp-xx : MCTC-00760-FO-findAllNotOfStoreInMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00760 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00760;
    auto                                                        expectedSize00760 = expectedSizeFindAllNotOfOne;
    auto                                                const & expected00760 = expectedFindAllNotOfOne;
    auto                                                const & target00760 = one;

    (void) collection00760.findAllNotOf ( storeIn00760, target00760 );
    if ( storeIn00760.size() != expectedSize00760 || ! iteratorListEqualityCheckNoPred ( storeIn00760, expected00760 ) ) {
        pTestLib->logError( "'MCTC-00760-FO-findAllNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00760-FO-findAllNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfStoreInMatchingMore-cpp-xx : MCTC-00761-FO-findAllNotOfStoreInMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00761 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00761;
    auto                                                        expectedSize00761 = expectedSizeFindAllNotOfMore;
    auto                                                const & expected00761 = expectedFindAllNotOfMore;
    auto                                                const & target00761 = more;

    (void) collection00761.findAllNotOf ( storeIn00761, target00761 );
    if ( storeIn00761.size() != expectedSize00761 || ! iteratorListEqualityCheckNoPred ( storeIn00761, expected00761 ) ) {
        pTestLib->logError( "'MCTC-00761-FO-findAllNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00761-FO-findAllNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfStoreInMatchingAll-cpp-xx : MCTC-00762-FO-findAllNotOfStoreInMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00762 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00762;
    auto                                                        expectedSize00762 = expectedSizeFindAllNotOfAll;
    auto                                                const & expected00762 = expectedFindAllNotOfAll;
    auto                                                const & target00762 = all;

    (void) collection00762.findAllNotOf ( storeIn00762, target00762 );
    if ( storeIn00762.size() != expectedSize00762 || ! iteratorListEqualityCheckNoPred ( storeIn00762, expected00762 ) ) {
        pTestLib->logError( "'MCTC-00762-FO-findAllNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00762-FO-findAllNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfStoreInMatchingAllAndMore-cpp-xx : MCTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00763 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00763;
    auto                                                        expectedSize00763 = expectedSizeFindAllNotOfAllAndMore;
    auto                                                const & expected00763 = expectedFindAllNotOfAllAndMore;
    auto                                                const & target00763 = allAndMore;

    (void) collection00763.findAllNotOf ( storeIn00763, target00763 );
    if ( storeIn00763.size() != expectedSize00763 || ! iteratorListEqualityCheckNoPred ( storeIn00763, expected00763 ) ) {
        pTestLib->logError( "'MCTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfReturnedMatchingNone-cpp-xx : MCTC-00764-FO-findAllNotOfReturnedMatchingNone-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00764 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00764;
    auto                                                        expectedSize00764 = expectedSizeFindAllNotOfNone;
    auto                                                const & expected00764 = expectedFindAllNotOfNone;
    auto                                                const & target00764 = none;

    storeIn00764 = collection00764.template findAllNotOf < __ComparisonEquivalent > ( target00764 );
    if ( storeIn00764.size() != expectedSize00764 || ! iteratorListEqualityCheckNoPred ( storeIn00764, expected00764 ) ) {
        pTestLib->logError( "'MCTC-00764-FO-findAllNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00764-FO-findAllNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfReturnedMatchingOne-cpp-xx : MCTC-00765-FO-findAllNotOfReturnedMatchingOne-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00765 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00765;
    auto                                                        expectedSize00765 = expectedSizeFindAllNotOfOne;
    auto                                                const & expected00765 = expectedFindAllNotOfOne;
    auto                                                const & target00765 = one;

    storeIn00765 = collection00765.template findAllNotOf < __ComparisonEquivalent > ( target00765 );
    if ( storeIn00765.size() != expectedSize00765 || ! iteratorListEqualityCheckNoPred ( storeIn00765, expected00765 ) ) {
        pTestLib->logError( "'MCTC-00765-FO-findAllNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00765-FO-findAllNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfReturnedMatchingMore-cpp-xx : MCTC-00766-FO-findAllNotOfReturnedMatchingMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00766 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00766;
    auto                                                        expectedSize00766 = expectedSizeFindAllNotOfMore;
    auto                                                const & expected00766 = expectedFindAllNotOfMore;
    auto                                                const & target00766 = more;

    storeIn00766 = collection00766.template findAllNotOf < __ComparisonEquivalent > ( target00766 );
    if ( storeIn00766.size() != expectedSize00766 || ! iteratorListEqualityCheckNoPred ( storeIn00766, expected00766 ) ) {
        pTestLib->logError( "'MCTC-00766-FO-findAllNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00766-FO-findAllNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfReturnedMatchingAll-cpp-xx : MCTC-00767-FO-findAllNotOfReturnedMatchingAll-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00767 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00767;
    auto                                                        expectedSize00767 = expectedSizeFindAllNotOfAll;
    auto                                                const & expected00767 = expectedFindAllNotOfAll;
    auto                                                const & target00767 = all;

    storeIn00767 = collection00767.template findAllNotOf < __ComparisonEquivalent > ( target00767 );
    if ( storeIn00767.size() != expectedSize00767 || ! iteratorListEqualityCheckNoPred ( storeIn00767, expected00767 ) ) {
        pTestLib->logError( "'MCTC-00767-FO-findAllNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00767-FO-findAllNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    /* MutableCollectionTestCase-FindOf-findAllNotOfReturnedMatchingAllAndMore-cpp-xx : MCTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-cpp-xx */
    cds :: MutableCollection < __ElementType > & collection00768 = underTest;
    __ComparisonEquivalent < Iterator >                    storeIn00768;
    auto                                                        expectedSize00768 = expectedSizeFindAllNotOfAllAndMore;
    auto                                                const & expected00768 = expectedFindAllNotOfAllAndMore;
    auto                                                const & target00768 = allAndMore;

    storeIn00768 = collection00768.template findAllNotOf < __ComparisonEquivalent > ( target00768 );
    if ( storeIn00768.size() != expectedSize00768 || ! iteratorListEqualityCheckNoPred ( storeIn00768, expected00768 ) ) {
        pTestLib->logError( "'MCTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
    }

    return true;
}

/* MutableCollectionTestGroup-RandomInsertion-cpp-xx : MCTG-00800-RI-cpp-xx. MCTC-00801-RI to MCTC-008xx-RI */
template <
        typename __DerivedType,
        typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
        typename __FwdElementType1,
        typename __FwdElementType2,
        typename __FwdElementType3,
        typename __ItType1,
        typename __ItType2,
        typename __ItType3,
        typename ... __Pack
> auto mutableCollectionTestGroupRandomInsertion (
        Test * pTestLib,
        __ElementType const & insertByCopy,
        __ElementType && insertByMove,
        __FwdElementType1 && insertByEmplace1,
        __FwdElementType2 && insertByEmplace2,
        __FwdElementType3 && insertByEmplace3,
        cds :: MutableCollection < __ElementType > const & toInsertAll,
        std :: initializer_list < __ElementType > const & toInsertAllList,
        __ItType1 const & r1Begin, __ItType1 const & r1End,
        __ItType2 const & r2Begin, __ItType2 const & r2End,
        __ItType3 const & r3Begin, __ItType3 const & r3End,
        cds :: MutableCollection < __ElementType > const & expectedInsertByCopy,
        cds :: MutableCollection < __ElementType > const & expectedInsertByMove,
        cds :: MutableCollection < __ElementType > const & expectedAfterAllInsertByEmplace,
        cds :: MutableCollection < __ElementType > const & expectedAfterPackInsertion,
        cds :: MutableCollection < __ElementType > const & expectedAfterInsertAll,
        cds :: MutableCollection < __ElementType > const & expectedAfterInsertAllList,
        cds :: MutableCollection < __ElementType > const & expectedAfterR1Insert,
        cds :: MutableCollection < __ElementType > const & expectedAfterR2Insert,
        cds :: MutableCollection < __ElementType > const & expectedAfterR3Insert,

        __Pack && ... insertedPack
) -> bool {

    /* MutableCollectionTestCase-RandomInsertion-insertByCopy-cpp-xx : MCTC-00801-RI-insertByCopy-cpp-xx */
    __DerivedType RI00801;
    cds :: MutableCollection < __ElementType > & baseRI00801 = RI00801;

    baseRI00801.insert ( insertByCopy );
    if ( ! RI00801.equals ( expectedInsertByCopy ) ) {
        pTestLib->logError( "'MCTC-00801-RI-insertByCopy-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00801-RI-insertByCopy-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByMove-cpp-xx : MCTC-00802-RI-insertByMove-cpp-xx */
    __DerivedType RI00802;
    cds :: MutableCollection < __ElementType > & baseRI00802 = RI00802;

    baseRI00802.insert ( std :: move ( insertByMove ) );
    if ( ! RI00802.equals ( expectedInsertByMove ) ) {
        pTestLib->logError( "'MCTC-00802-RI-insertByMove-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00802-RI-insertByMove-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByEmplace-cpp-xx : MCTC-00803-RI-insertByEmplace-cpp-xx */
    __DerivedType RI00803;
    cds :: MutableCollection < __ElementType > & baseRI00803 = RI00803;

    baseRI00803.emplace ( std :: forward < __FwdElementType1 > ( insertByEmplace1 ) );
    baseRI00803.emplace ( std :: forward < __FwdElementType2 > ( insertByEmplace2 ) );
    baseRI00803.emplace ( std :: forward < __FwdElementType3 > ( insertByEmplace3 ) );
    if ( ! RI00803.equals ( expectedAfterAllInsertByEmplace ) ) {
        pTestLib->logError( "'MCTC-00803-RI-insertByEmplace-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00803-RI-insertByEmplace-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByPack-cpp-xx : MCTC-00804-RI-insertByPack-cpp-xx */
    __DerivedType RI00804;
    cds :: MutableCollection < __ElementType > & baseRI00804 = RI00804;

    baseRI00804.insertAll ( std :: forward < __Pack > ( insertedPack ) ... );
    if ( ! RI00804.equals ( expectedAfterPackInsertion ) ) {
        pTestLib->logError( "'MCTC-00804-RI-insertByPack-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00804-RI-insertByPack-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByInsertAllIterable-cpp-xx : MCTC-00805-RI-insertByInsertAllIterable-cpp-xx */
    __DerivedType RI00805;
    cds :: MutableCollection < __ElementType > & baseRI00805 = RI00805;

    baseRI00805.insertAllOf ( toInsertAll );
    if ( ! RI00805.equals ( expectedAfterInsertAll ) ) {
        pTestLib->logError( "'MCTC-00805-RI-insertByInsertAllIterable-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00805-RI-insertByInsertAllIterable-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByInsertAllList-cpp-xx : MCTC-00806-RI-insertByInsertAllList-cpp-xx */
    __DerivedType RI00806;
    cds :: MutableCollection < __ElementType > & baseRI00806 = RI00806;

    baseRI00806.insertAllOf ( toInsertAllList );
    if ( ! RI00806.equals ( expectedAfterInsertAllList ) ) {
        pTestLib->logError( "'MCTC-00806-RI-insertByInsertAllList-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00806-RI-insertByInsertAllList-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByRange1-cpp-xx : MCTC-00807-RI-insertByRange1-cpp-xx */
    __DerivedType RI00807;
    cds :: MutableCollection < __ElementType > & baseRI00807 = RI00807;

    baseRI00807.insertAllOf ( r1Begin, r1End );
    if ( ! RI00807.equals ( expectedAfterR1Insert ) ) {
        pTestLib->logError( "'MCTC-00807-RI-insertByRange1-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00807-RI-insertByRange1-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByRange2-cpp-xx : MCTC-00808-RI-insertByRange2-cpp-xx */
    __DerivedType RI00808;
    cds :: MutableCollection < __ElementType > & baseRI00808 = RI00808;

    baseRI00808.insertAllOf ( r2Begin, r2End );
    if ( ! RI00808.equals ( expectedAfterR2Insert ) ) {
        pTestLib->logError( "'MCTC-00808-RI-insertByRange2-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00808-RI-insertByRange2-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* MutableCollectionTestCase-RandomInsertion-insertByRange3-cpp-xx : MCTC-00809-RI-insertByRange3-cpp-xx */
    __DerivedType RI00809;
    cds :: MutableCollection < __ElementType > & baseRI00809 = RI00809;

    baseRI00809.insertAllOf ( r3Begin, r3End );
    if ( ! RI00809.equals ( expectedAfterR3Insert ) ) {
        pTestLib->logError( "'MCTC-00809-RI-insertByRange3-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'MCTC-00809-RI-insertByRange3-" __CDS_cpplang_core_version_name "' OK" );
    }

    return true;
}

/* MutableCollectionTestSuite-cpp-xx : MCTS-00001-cpp-xx */
auto MutableCollectionTest :: execute () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        cds :: Array < int > intArrayObjectUnderTest;
        intArrayObjectUnderTest     = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto status = mutableCollectionTestGroupMemberFunctions (
                intArrayObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        cds :: LinkedList < int > intLinkedListObjectUnderTest;
        intLinkedListObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";

        auto status = mutableCollectionTestGroupMemberFunctions (
                intLinkedListObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        cds :: HashMap < int, int > intIntHashMapObjectUnderTest;
        intIntHashMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";

        auto status = mutableCollectionTestGroupMemberFunctions (
                intIntHashMapObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        cds :: Array < cds :: String > stringArrayObjectUnderTest;
        stringArrayObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";

        auto status = mutableCollectionTestGroupMemberFunctions < cds :: String > (
                stringArrayObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        cds :: LinkedList < cds :: String > stringLinkedListObjectUnderTest;
        stringLinkedListObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";

        auto status = mutableCollectionTestGroupMemberFunctions < cds :: String > (
                stringLinkedListObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        cds :: HashMap < cds :: String, cds :: String > stringStringHashMapObjectUnderTest;
        stringStringHashMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ are: verb, Ana: name, mere: noun }"; /// due to hash table

        auto status = mutableCollectionTestGroupMemberFunctions < cds :: MapEntry < cds :: String, cds :: String > > (
                stringStringHashMapObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });


    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        cds :: Array < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < int > (
                objUnderTest,
                this,
                true,
                20, 40,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        cds :: LinkedList < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < int > (
                objUnderTest,
                this,
                true,
                20, 40,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        cds :: HashMap < int, int > objUnderTest = {{3,4}, {4,5}, {5,6}, {6,7}, {7,8}};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < MapEntry < int, int > > (
                objUnderTest,
                this,
                false,
                MapEntry < int, int > { 20, 30 },
                MapEntry < int, int > { 40, 60 },
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
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        cds :: Array < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < String > (
                objUnderTest,
                this,
                true,
                "Ion", "Gigel",
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        cds :: LinkedList < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < String > (
                objUnderTest,
                this,
                true,
                "Ion", "Gigel",
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        cds :: HashMap < String, String > objUnderTest = {{"are","verb"}, {"Ana","name"}, {"mere","noun"}};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < MapEntry < String, String > > (
                objUnderTest,
                this,
                false,
                MapEntry < String, String > { "Gigel", "name" },
                MapEntry < String, String > { "them", "pronoun" },
                MapEntry < String, String > { "are", "verb" },
                MapEntry < String, String > { "Ana", "name" },
                MapEntry < String, String > { "mere", "noun" }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-SpecialAddressBasedIteratorAccess-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* only one test required, as it uses operator *, which was tested in previous group */
        cds :: Array < String > arr = { "Ana", "are", "mere" };
        cds :: MutableCollection < String > & c = arr;
        auto begin = c.begin();

        /* MutableCollectionTestGroup-SpecialAddressBasedIteratorAccess-addressOperator-cpp-xx : MCTC-00057-IT-addressOperator-cpp-xx */
        auto expectedLen = 3;
        auto len = begin->length();

        this->log ( "iterator '-> operator length' : '%llu', expected '-> operator length' : '%llu'", len, expectedLen );
        if ( expectedLen != len ) {
            this->logError ( "'MCTC-00057-IT-addressOperator-" __CDS_cpplang_core_version_name "' error" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00057-IT-addressOperator-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* MutableCollectionTestGroup-FunctionalStatements-cpp-xx : MCTG-00100-FS-cpp-xx - Tests MCTC-00101-FS to MCTC-10139-FS - located directly below due to varability of these tests */
    /* IntArray */              this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : IntArray */
        cds :: Array < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : IntArray */
        cds :: Array < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : IntArray */
        cds :: Array < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : IntArray */
        cds :: Array < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : IntArray */
        cds :: Array < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : IntArray */
        cds :: Array < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : IntArray */
        cds :: Array < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : IntArray */
        cds :: Array < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : IntArray */
        cds :: Array < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : IntArray */
        cds :: Array < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : IntArray */
        cds :: Array < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : IntArray */
        cds :: Array < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : IntArray */
        cds :: Array < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : IntArray */
        cds :: Array < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : IntArray */
        cds :: Array < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : IntArray */
        cds :: Array < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : IntArray */
        cds :: Array < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : IntArray */
        cds :: Array < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : IntArray */
        cds :: Array < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntArray */
        cds :: Array < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : IntArray */
        cds :: Array < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : IntArray */
        cds :: Array < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntArray */
        cds :: Array < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : IntArray */
        cds :: Array < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : IntArray */
        cds :: Array < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : IntArray */
        cds :: Array < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : IntArray */
        cds :: Array < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : IntArray */
        cds :: Array < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : IntArray */
        cds :: Array < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : IntArray */
        cds :: Array < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : IntArray */
        cds :: Array < int > fs139 = { 1, 2, 3, 4, 5 };
        MutableCollection < int > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: Array < int > fs140 = { 1, 2, 3, 4, 5 };
        cds :: MutableCollection < int > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( int & e ) { e = 3; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](int e) { return e == 3; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntLinkedList */         this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > fs139 = { 1, 2, 3, 4, 5 };
        MutableCollection < int > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: LinkedList < int > fs140 = { 1, 2, 3, 4, 5 };
        cds :: MutableCollection < int > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( int & e ) { e = 3; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](int e) { return e == 3; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntToIntHashMap */       this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs101 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs102 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs103 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs104 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs105 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs106 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs107 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs108 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs109 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs110 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {8, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs111 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs112 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs113 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs114 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs115 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs116 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs117 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [comparedTo] (MapEntry<int, int>const & e) { return e.key() > comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs118 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs119 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs120 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs121 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs122 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs123 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs124 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs125 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs126 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs127 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs128 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs129 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs130 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs131 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs132 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs133 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs134 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs135 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs136 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs137 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs138 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > fs139 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        MutableCollection < MapEntry < int, int > > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<int, int>const & e ) { if ( e.key() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: HashMap < int, int > fs140 = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: MutableCollection < MapEntry < int, int > > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( MapEntry < int, int > & e ) {
//            e.key() = 3;  must always fail compilation
            e.value () = 7;
        };

        MutableCollectionFS140.forEach (actionfs140);
        int growingKey = 1;
        auto countfs140 = MutableCollectionFS140.count ([& growingKey](MapEntry < int, int > & e) {
            return e.key() == growingKey ++ && e.value () == 7;
        });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringArray */           this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : StringArray */
        cds :: Array < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : StringArray */
        cds :: Array < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : StringArray */
        cds :: Array < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : StringArray */
        cds :: Array < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : StringArray */
        cds :: Array < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : StringArray */
        cds :: Array < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : StringArray */
        cds :: Array < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : StringArray */
        cds :: Array < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : StringArray */
        cds :: Array < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : StringArray */
        cds :: Array < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : StringArray */
        cds :: Array < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : StringArray */
        cds :: Array < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : StringArray */
        cds :: Array < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : StringArray */
        cds :: Array < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : StringArray */
        cds :: Array < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : StringArray */
        cds :: Array < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : StringArray */
        cds :: Array < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : StringArray */
        cds :: Array < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : StringArray */
        cds :: Array < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringArray */
        cds :: Array < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : StringArray */
        cds :: Array < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : StringArray */
        cds :: Array < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringArray */
        cds :: Array < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : StringArray */
        cds :: Array < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : StringArray */
        cds :: Array < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : StringArray */
        cds :: Array < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : StringArray */
        cds :: Array < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : StringArray */
        cds :: Array < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : StringArray */
        cds :: Array < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : StringArray */
        cds :: Array < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : StringArray */
        cds :: Array < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        MutableCollection < String > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: Array < String > fs140 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( String & e ) { e = "ccc"; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](String const & e) { return e == "ccc"; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMemberFnMutability-" __CDS_cpplang_core_version_name " : MCTC-00141-FS-forEachMemberFnMutability-cpp-xx : IntArray */
        cds :: Array < String > fs141 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS141 = fs141;
        auto actionfs141 = & String :: clear;

        MutableCollectionFS141.forEach (actionfs141);
        auto countfs141 = MutableCollectionFS141.count (& String :: empty);

        if ( countfs141 != fs141.size() ) {
            this->logError ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringLinkedList */      this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );
        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        MutableCollection < String > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: LinkedList < String > fs140 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( String & e ) { e = "ccc"; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](String const & e) { return e == "ccc"; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMemberFnMutability-" __CDS_cpplang_core_version_name " : MCTC-00141-FS-forEachMemberFnMutability-cpp-xx : IntArray */
        cds :: LinkedList < String > fs141 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS141 = fs141;
        auto actionfs141 = & String :: clear;

        MutableCollectionFS141.forEach (actionfs141);
        auto countfs141 = MutableCollectionFS141.count (& String :: empty);

        if ( countfs141 != fs141.size() ) {
            this->logError ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

    /* StringToStringHashMap */ this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs101 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs102 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs103 = { {"x", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs104 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs105 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs106 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs107 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs108 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs109 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs110 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs111 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs112 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs113 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs114 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs115 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs116 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs117 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [comparedTo] (MapEntry<String, String>const & e) { return e.key().length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs118 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs119 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs120 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs121 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs122 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs123 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs124 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs125 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs126 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs127 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs128 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs129 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs130 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs131 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs132 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs133 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs134 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs135 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs136 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs137 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs138 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > fs139 = { {"X", "x"}, {"YY" ,"Y"}, {"z", "Z"}, {"WW", "W"}, {"t", "TTT"} };
        MutableCollection < MapEntry < String, String > > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<String, String>const & e ) { if ( e.key().length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: HashMap < String, String > fs140 = { {"a", "1"}, {"bb", "2"}, {"ccc", "3"}, {"dddd", "4"}, {"eeeee", "5"} };
        cds :: MutableCollection < MapEntry < String, String > > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( MapEntry < String, String > & e ) {
//            e.key() = "ccc"; // should not compile
            e.value() = "8";
        };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](MapEntry < String, String > const & e) { return e.value() == "8"; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

#endif

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* MutableCollectionTestGroup-FunctionalStatementsMemberFunction-cpp-xx : MCTG-00200-FSMF-cpp-xx - Tests MCTC-00201-FSMF to MCTC-00229-FSMF */
    this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatementsMemberFunction-" __CDS_cpplang_core_version_name " : MCTG-00200-FSMF-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-forEach-cpp-xx : MCTC-00201-FSMF-forEach-cpp-xx. Test Success if compile success */
        cds :: Array < String > fs201 = { "Ana", "are", "mere" };
        fs201.forEach ( [](String const & e){ (void) e.length(); } );
        fs201.forEach ( & String :: length );
        this->logOK ( "'MCTC-00201-FSMF-forEach-" __CDS_cpplang_core_version_name "' OK" );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-someEqual-cpp-xx : MCTC-00202-FSMF-someEqual-cpp-xx. */
        cds :: Array < String > fs202 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00202-FSMF-someEqual-cpp-xx",
                /* objUnderTest */  fs202,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-someLess-cpp-xx : MCTC-00203-FSMF-someLess-cpp-xx. */
        cds :: Array < String > fs203 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00203-FSMF-someLess-cpp-xx",
                /* objUnderTest */  fs203,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-someMore-cpp-xx : MCTC-00204-FSMF-someMore-cpp-xx. */
        cds :: Array < String > fs204 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00204-FSMF-someMore-cpp-xx",
                /* objUnderTest */  fs204,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atLeast-cpp-xx : MCTC-00205-FSMF-atLeast-cpp-xx. */
        cds :: Array < String > fs205 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00205-FSMF-atLeast-cpp-xx",
                /* objUnderTest */  fs205,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atLeastLess-cpp-xx : MCTC-00206-FSMF-atLeastLess-cpp-xx. */
        cds :: Array < String > fs206 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00206-FSMF-atLeastLess-cpp-xx",
                /* objUnderTest */  fs206,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atLeastMore-cpp-xx : MCTC-00207-FSMF-atLeastMore-cpp-xx. */
        cds :: Array < String > fs207 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00207-FSMF-atLeastMore-cpp-xx",
                /* objUnderTest */  fs207,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atMost-cpp-xx : MCTC-00208-FSMF-atMost-cpp-xx. */
        cds :: Array < String > fs208 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00208-FSMF-atMost-cpp-xx",
                /* objUnderTest */  fs208,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atMostLess-cpp-xx : MCTC-00209-FSMF-atMostLess-cpp-xx. */
        cds :: Array < String > fs209 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00209-FSMF-atMostLess-cpp-xx",
                /* objUnderTest */  fs209,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atMostMore-cpp-xx : MCTC-00210-FSMF-atMostMore-cpp-xx. */
        cds :: Array < String > fs210 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00210-FSMF-atMostMore-cpp-xx",
                /* objUnderTest */  fs210,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-moreThan-cpp-xx : MCTC-00211-FSMF-moreThan-cpp-xx. */
        cds :: Array < String > fs211 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00211-FSMF-moreThan-cpp-xx",
                /* objUnderTest */  fs211,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-moreThanLess-cpp-xx : MCTC-00212-FSMF-moreThanLess-cpp-xx. */
        cds :: Array < String > fs212 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00212-FSMF-moreThanLess-cpp-xx",
                /* objUnderTest */  fs212,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-moreThanMore-cpp-xx : MCTC-00213-FSMF-moreThanMore-cpp-xx. */
        cds :: Array < String > fs213 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00213-FSMF-moreThanMore-cpp-xx",
                /* objUnderTest */  fs213,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-fewerThan-cpp-xx : MCTC-00214-FSMF-fewerThan-cpp-xx. */
        cds :: Array < String > fs214 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00214-FSMF-fewerThan-cpp-xx",
                /* objUnderTest */  fs214,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-fewerThanLess-cpp-xx : MCTC-00215-FSMF-fewerThanLess-cpp-xx. */
        cds :: Array < String > fs215 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00215-FSMF-fewerThanLess-cpp-xx",
                /* objUnderTest */  fs215,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-fewerThanMore-cpp-xx : MCTC-00216-FSMF-fewerThanMore-cpp-xx. */
        cds :: Array < String > fs216 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00216-FSMF-fewerThanMore-cpp-xx",
                /* objUnderTest */  fs216,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-countExact-cpp-xx : MCTC-00217-FSMF-countExact-cpp-xx. */
        cds :: Array < String > fs217 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00217-FSMF-countExact-cpp-xx",
                /* objUnderTest */  fs217,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     & String :: empty,
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyNone-cpp-xx : MCTC-00218-FSMF-anyNone-cpp-xx. */
        cds :: Array < String > fs218 = { "a", "b", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00218-FSMF-anyNone-cpp-xx",
                /* objUnderTest */  fs218,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyOne-cpp-xx : MCTC-00219-FSMF-anyOne-cpp-xx. */
        cds :: Array < String > fs219 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00219-FSMF-anyOne-cpp-xx",
                /* objUnderTest */  fs219,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyMore-cpp-xx : MCTC-00220-FSMF-anyMore-cpp-xx. */
        cds :: Array < String > fs220 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00220-FSMF-anyMore-cpp-xx",
                /* objUnderTest */  fs220,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyAll-cpp-xx : MCTC-00221-FSMF-anyAll-cpp-xx. */
        cds :: Array < String > fs221 = { "", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00221-FSMF-anyAll-cpp-xx",
                /* objUnderTest */  fs221,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allNone-cpp-xx : MCTC-00222-FSMF-allNone-cpp-xx. */
        cds :: Array < String > fs222 = { "a", "b", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00222-FSMF-allNone-cpp-xx",
                /* objUnderTest */  fs222,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allOne-cpp-xx : MCTC-00223-FSMF-allOne-cpp-xx. */
        cds :: Array < String > fs223 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00223-FSMF-allOne-cpp-xx",
                /* objUnderTest */  fs223,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allMore-cpp-xx : MCTC-00224-FSMF-allMore-cpp-xx. */
        cds :: Array < String > fs224 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00224-FSMF-allMore-cpp-xx",
                /* objUnderTest */  fs224,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allAll-cpp-xx : MCTC-00225-FSMF-allAll-cpp-xx. */
        cds :: Array < String > fs225 = { "", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00225-FSMF-allAll-cpp-xx",
                /* objUnderTest */  fs225,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneNone-cpp-xx : MCTC-00226-FSMF-noneNone-cpp-xx. */
        cds :: Array < String > fs226 = { "a", "b", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00226-FSMF-noneNone-cpp-xx",
                /* objUnderTest */  fs226,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneOne-cpp-xx : MCTC-00227-FSMF-noneOne-cpp-xx. */
        cds :: Array < String > fs227 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00227-FSMF-noneOne-cpp-xx",
                /* objUnderTest */  fs227,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneMore-cpp-xx : MCTC-00228-FSMF-noneMore-cpp-xx. */
        cds :: Array < String > fs228 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00228-FSMF-noneMore-cpp-xx",
                /* objUnderTest */  fs228,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneAll-cpp-xx : MCTC-00229-FSMF-noneAll-cpp-xx. */
        cds :: Array < String > fs229 = { "", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00229-FSMF-noneAll-cpp-xx",
                /* objUnderTest */  fs229,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );
    });

#endif

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < int > & underTestColl = underTest;

        cds :: Array < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Array < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: Array < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < int > & underTestColl = underTest;

        cds :: LinkedList < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedList < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedList < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: MutableCollection < MapEntry < int, int > > & underTestColl = underTest;

        cds :: HashMap < int, int > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: HashMap < int, int > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: HashMap < int, int > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: HashMap < int, int > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: HashMap < int, int > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < String > & underTestColl = underTest;

        cds :: Array < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Array < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: Array < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < String > & underTestColl = underTest;

        cds :: LinkedList < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedList < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedList < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > underTest = { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        cds :: MutableCollection < MapEntry < String, String > > & underTestColl = underTest;

        cds :: HashMap < String, String > afterFrontRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3},  };
        cds :: HashMap < String, String > afterMidRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2}, {3, 3} };
        cds :: HashMap < String, String > afterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: HashMap < String, String > afterAfterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: HashMap < String, String > afterOtherRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });

#define make_a(type, ...) cds :: Array < type > { __VA_ARGS__ }
#define make_ll(type, ...) cds :: LinkedList < type > { __VA_ARGS__ }
#define make_hs(type, ...) cds :: HashSet < type > { __VA_ARGS__ }
#define make_hm(ktype, vtype, ...) cds :: HashMap < ktype, vtype > { __VA_ARGS__ }
#define make_il(...) { __VA_ARGS__ }

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : MCTG-00400-RB-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


        allOk = allOk && mutableCollectionTestGroupRemoveBy (
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
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : MCTG-00400-RB-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


        allOk = allOk && mutableCollectionTestGroupRemoveBy (
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
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : MCTG-00400-RB-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };


        allOk = allOk && mutableCollectionTestGroupRemoveBy (
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
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : MCTG-00400-RB-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


        allOk = allOk && mutableCollectionTestGroupRemoveBy (
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
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : MCTG-00400-RB-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };


        allOk = allOk && mutableCollectionTestGroupRemoveBy (
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
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : MCTG-00400-RB-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > originalArray = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };


        allOk = allOk && mutableCollectionTestGroupRemoveBy (
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
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : MCTG-00400-RB-" __CDS_cpplang_core_version_name " : StringArrayMemberFunction", [this, & allOk]{

        cds :: Array < String > strArray = { "word1", "word2", "", "", "word3", "", "word4", "", "", "","", "word5", "" };

        auto copyForRemoveThat      = strArray;
        auto copyForRemoveFirstThat = strArray;
        auto copyForRemoveLastThat  = strArray;
        auto copyForRemoveAllThat   = strArray;
        cds :: Array < String > copyForRemoveAllThatCoverage   = {"word1", "word2", "", "word3", "word4", "word5"};

        cds :: MutableCollection < String > & cRT  = copyForRemoveThat;
        cds :: MutableCollection < String > & cRFT = copyForRemoveFirstThat;
        cds :: MutableCollection < String > & cRLT = copyForRemoveLastThat;
        cds :: MutableCollection < String > & cRAT = copyForRemoveAllThat;
        cds :: MutableCollection < String > & cRATCoverage = copyForRemoveAllThatCoverage;
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

        /* MutableCollectionTestCase-RemoveBy-memberRemoveThat-cpp-xx : MCTC-00419-RB-memberRemoveThat-cpp-xx */
        Size removeThatRes = cRT.removeThat ( removeThatLimit, & String :: empty );
        if ( removeThatExpected != removeThatRes || ! cRT.equals ( expectedAfterRemoveThat ) ) {
            this->logError ( "'MCTC-00419-RB-memberRemoveThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00419-RB-memberRemoveThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-RemoveBy-memberRemoveFirstThat-cpp-xx : MCTC-00420-RB-memberRemoveFirstThat-cpp-xx */
        bool removeFirstThatRes = cRFT.removeFirstThat ( & String :: empty );
        if ( removeFirstThatExpected != removeFirstThatRes || ! cRFT.equals ( expectedAfterRemoveFirstThat ) ) {
            this->logError ( "'MCTC-00420-RB-memberRemoveFirstThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00420-RB-memberRemoveFirstThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-RemoveBy-memberRemoveLastThat-cpp-xx : MCTC-00421-RB-memberRemoveLastThat-cpp-xx */
        bool removeLastThatRes = cRLT.removeLastThat ( & String :: empty );
        if ( removeLastThatExpected != removeLastThatRes || ! cRLT.equals ( expectedAfterRemoveLastThat ) ) {
            this->logError ( "'MCTC-00421-RB-memberRemoveLastThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00421-RB-memberRemoveLastThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-RemoveBy-memberRemoveAllThat-cpp-xx : MCTC-00422-RB-memberRemoveAllThat-cpp-xx */
        Size removeAllThatRes = cRAT.removeAllThat ( & String :: empty );
        if ( removeAllThatExpected != removeAllThatRes || ! cRAT.equals ( expectedAfterRemoveAllThat ) ) {
            this->logError ( "'MCTC-00422-RB-memberRemoveAllThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00422-RB-memberRemoveAllThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-RemoveBy-memberRemoveThatCoverage-cpp-xx : MCTC-00423-RB-memberRemoveThatCoverage-cpp-xx */
        Size removeAllThatCovRes = cRATCoverage.removeAllThat ( & String :: empty );
        if ( 1U != removeAllThatCovRes || ! cRATCoverage.equals ( expectedAfterRemoveAllThatCoverage ) ) {
            this->logError ( "'MCTC-00423-RB-memberRemoveThatCoverage-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00423-RB-memberRemoveThatCoverage-" __CDS_cpplang_core_version_name "' OK" );
        }

        cds :: MutableCollection < String > & extraForNegCoverage = expectedAfterRemoveAllThatCoverage;

        (void) extraForNegCoverage.removeThat (5, & String :: empty);
        (void) extraForNegCoverage.removeFirstThat (& String :: empty);
        (void) extraForNegCoverage.removeLastThat (& String :: empty);
        (void) extraForNegCoverage.removeAllThat (& String :: empty);

        (void) extraForNegCoverage.insert ("");
        (void) extraForNegCoverage.removeThat (5, & String :: empty);

    });


    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_a(t, __VA_ARGS__)

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_ll(t, __VA_ARGS__)

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, 10, 11, 12, 13),
                /* oneCommon= */                                make(int, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(int, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(int, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(int, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(int),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(int, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(int, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(int, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       make(int, 10, 11, 12, 13),
                /* oneCommon= */                        make(int, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(int, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(int, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(int, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

#define make(k, v, ...) make_hm(k, v, __VA_ARGS__)

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, int, {1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(int, int ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, int, {2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(int, int),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(int, int, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(int, int, {3, 3}, {5, 5}, {7, 7} ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

#undef make
#define make(k, v, ...) {__VA_ARGS__}

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, int, {1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(int, int),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(int, int, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(int, int, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(int, int, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(int, int, {2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(int, int),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(int, int, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(int, int, {3, 3}, {5, 5}, {7, 7} ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastNotOf,
                /* noneCommon= */                       make(int, int, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(int, int, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(int, int, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(int, int, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(int, int, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

#undef make
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_a(t, __VA_ARGS__)

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#define make(t, ...) make_ll(t, __VA_ARGS__)

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
#define make(t, ...) {__VA_ARGS__}

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, 10, 11, 12, 13),
                /* oneCommon= */                                make(String, 16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make(String, 20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make(String, 2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(String, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, 3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, 2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(String),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(String, 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(String, 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(String, 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       make(String, 10, 11, 12, 13),
                /* oneCommon= */                        make(String, 16, 6, 11, 12, 13),
                /* moreCommon= */                       make(String, 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make(String, 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make(String, 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, 1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, 1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

#undef make
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

#define make(k, v, ...) make_hm(k, v, __VA_ARGS__)

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, String, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, String, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, String, {1, 1}, {3, 3}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(String, String, {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, String, {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(String, String, {1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(String, String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(String, String, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, String, {5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(String, String),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(String, String, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(String, String, {3, 3}, {5, 5}, {7, 7} ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(String, String, {1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9})
        );

#undef make
#define make(k, v, ...) {__VA_ARGS__}

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, String, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, String, {4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, String, {4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {3, 3} ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make(String, String, {4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make(String, String ),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                                make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreLessThanLimitCommon= */                  make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}),
                /* moreCommon= */                               make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* moreMoreThanLimitCommon= */                  make(String, String, {2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                                make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                         make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make(String, String, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make(String, String, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make(String, String, {5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make(String, String, {5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make(String, String),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make(String, String, {6, 6} ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make(String, String, {5, 5}, {7, 7}, {3, 3} ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3})
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastNotOf,
                /* noneCommon= */                       make(String, String, {10, 10}, {11, 11}, {12, 12}, {13, 13}),
                /* oneCommon= */                        make(String, String, {16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}),
                /* moreCommon= */                       make(String, String, {20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}),
                /* allCommon= */                        make(String, String, {9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} ),
                /* allAndMoreCommon= */                 make(String, String, {91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} ),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make(String, String, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} )
        );

#undef make
    });


    this->executeSubtest ( "MutableCollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : MCTG-00600-FT-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        cds :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindThat (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : MCTG-00600-FT-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindThat (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : MCTG-00600-FT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk] {

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupFindThat (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : MCTG-00600-FT-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindThat < String > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : MCTG-00600-FT-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindThat < String > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : MCTG-00600-FT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk] {

        cds :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupFindThat < MapEntry < String, String > > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindThatMemberFunction-" __CDS_cpplang_core_version_name " : MCTG-00650-FTMF-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        /* MutableCollectionTestGroup-FindThatMemberFunction-" __CDS_cpplang_core_version_name " : MCTG-00650-FTMF-cpp-xx : MCTC-00651-FTMF to MCTC-00656-FTMF */

        cds :: Array < String > arr = { "word1", "", "word2", "", "word3", "word4", "", "word5" };
        cds :: MutableCollection < String > & underTest = arr;
        using Iterator = cds :: MutableCollection < String > :: Iterator;

        /* MutableCollectionTestCase-FindThatMemberFunction-findThatStoreInMemberFunction-cpp-xx : MCTC-00651-FTMF-findThatStoreInMemberFunction-cpp-xx */
        cds :: Array < Iterator > storeIn651;
        underTest.findThat ( 2, storeIn651, & String :: empty );

        if ( storeIn651.size() != 2 || * ( ++ storeIn651[0] ) != "word2" || * ( ++ storeIn651[1] ) != "word3" ) {
            this->logError( "'MCTC-00651-FTMF-findThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'MCTC-00651-FTMF-findThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FindThatMemberFunction-findThatReturnedMemberFunction-cpp-xx : MCTC-00652-FTMF-findThatReturnedMemberFunction-cpp-xx */
        cds :: Array < Iterator > storeIn652;
        storeIn652 = underTest.findThat < cds :: Array > ( 2, & String :: empty );

        if ( storeIn652.size() != 2 || * ( ++ storeIn652[0] ) != "word2" || * ( ++ storeIn652[1] ) != "word3" ) {
            this->logError( "'MCTC-00652-FTMF-findThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'MCTC-00652-FTMF-findThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FindThatMemberFunction-findFirstThatMemberFunction-cpp-xx : MCTC-00653-FTMF-findFirstThatMemberFunction-cpp-xx */
        Iterator res653;
        res653 = underTest.findFirstThat ( & String :: empty );

        if ( ! static_cast <bool> (res653) || * ( ++ res653 ) != "word2" ) {
            this->logError( "'MCTC-00653-FTMF-findFirstThatMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'MCTC-00653-FTMF-findFirstThatMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FindThatMemberFunction-findLastThatMemberFunction-cpp-xx : MCTC-00654-FTMF-findLastThatMemberFunction-cpp-xx */
        Iterator res654;
        res654 = underTest.findLastThat ( & String :: empty );

        if ( ! static_cast <bool> (res654) || * ( ++ res654 ) != "word5" ) {
            this->logError( "'MCTC-00654-FTMF-findLastThatMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'MCTC-00654-FTMF-findLastThatMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FindThatMemberFunction-findAllThatStoreInMemberFunction-cpp-xx : MCTC-00655-FTMF-findAllThatStoreInMemberFunction-cpp-xx */
        cds :: Array < Iterator > storeIn655;
        underTest.findAllThat ( storeIn655, & String :: empty );

        if ( storeIn655.size() != 3 || * ( ++ storeIn655[0] ) != "word2" || * ( ++ storeIn655[1] ) != "word3" || * ( ++ storeIn655 [2] ) != "word5" ) {
            this->logError( "'MCTC-00655-FTMF-findAllThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'MCTC-00655-FTMF-findAllThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FindThatMemberFunction-findAllThatReturnedMemberFunction-cpp-xx : MCTC-00656-FTMF-findAllThatReturnedMemberFunction-cpp-xx */
        cds :: Array < Iterator > storeIn656;
        storeIn656 = underTest.findAllThat < cds :: Array > ( & String :: empty );

        if ( storeIn656.size() != 3 || * ( ++ storeIn656[0] ) != "word2" || * ( ++ storeIn656[1] ) != "word3" || * ( ++ storeIn656 [2] ) != "word5" ) {
            this->logError( "'MCTC-00656-FTMF-findAllThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'MCTC-00656-FTMF-findAllThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }
    });


    this->executeSubtest ( "MutableCollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : MCTG-00700-FO-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        cds :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindOf < cds :: MutableCollection < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "MutableCollection",
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

        allOk = allOk && mutableCollectionTestGroupFindOf < std :: initializer_list < int > > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : MCTG-00700-FO-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindOf < cds :: MutableCollection < int > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "MutableCollection",
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

        allOk = allOk && mutableCollectionTestGroupFindOf < std :: initializer_list < int > > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : MCTG-00700-FO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk] {

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupFindOf < cds :: MutableCollection < MapEntry < int, int > > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "MutableCollection",
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

        allOk = allOk && mutableCollectionTestGroupFindOf < std :: initializer_list < MapEntry < int, int > > > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : MCTG-00700-FO-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindOf < cds :: MutableCollection < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "MutableCollection",
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

        allOk = allOk && mutableCollectionTestGroupFindOf < std :: initializer_list < String >, String > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : MCTG-00700-FO-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupFindOf < cds :: MutableCollection < String >, String > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "MutableCollection",
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

        allOk = allOk && mutableCollectionTestGroupFindOf < std :: initializer_list < String >, String > (
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
    this->executeSubtest ( "MutableCollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : MCTG-00700-FO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk] {

        cds :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupFindOf < cds :: MutableCollection < MapEntry < String, String > > > (
                /* pTestLib= */                                 this,
                /* variant= */                                  "MutableCollection",
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

        allOk = allOk && mutableCollectionTestGroupFindOf < std :: initializer_list < MapEntry < String, String > > > (
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


    this->executeSubtest ( "MutableCollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : MCTG-00800-RI-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        int byCopy = 5;
        int byMove = 8;

        cds :: Array < int > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < int > range3Definer { 20, 21, 22, 23, 24, 25 };

        allOk = allOk && mutableCollectionTestGroupRandomInsertion <
                cds :: Array < int >,
                int
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, 3, 4,
                make_a (int, 1, 2, 3, 4, 5),
                { 5, 6, 7, 8, 9 },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_a (int, 5),
                make_a (int, 8),
                make_a (int, 2, 3, 4),
                make_a (int, 100, 200, 300, 400),
                make_a (int, 1, 2, 3, 4, 5),
                make_a (int, 5, 6, 7, 8, 9),
                make_a (int, 10, 20, 30, 40),
                make_a (int, 10, 11, 12, 13, 14),
                make_a (int, 20, 21, 22, 23, 24, 25),
                100, 200, 300, 400
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : MCTG-00800-RI-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        int byCopy = 5;
        int byMove = 8;

        cds :: Array < int > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < int > range3Definer { 20, 21, 22, 23, 24, 25 };

        allOk = allOk && mutableCollectionTestGroupRandomInsertion <
                cds :: LinkedList < int >,
                int
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, 3, 4,
                make_a (int, 1, 2, 3, 4, 5),
                { 5, 6, 7, 8, 9 },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_ll (int, 5),
                make_ll (int, 8),
                make_ll (int, 2, 3, 4),
                make_ll (int, 100, 200, 300, 400),
                make_ll (int, 1, 2, 3, 4, 5),
                make_ll (int, 5, 6, 7, 8, 9),
                make_ll (int, 10, 20, 30, 40),
                make_ll (int, 10, 11, 12, 13, 14),
                make_ll (int, 20, 21, 22, 23, 24, 25),
                100, 200, 300, 400
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : MCTG-00800-RI-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk] {

        MapEntry < int, int > byCopy = {5, 87};
        MapEntry < int, int > byMove = {8, 16};

        cds :: Array < MapEntry < int, int > > range1Definer = { {10, 20}, {20, 40}, {30, 60}, {40, 80} };
        std :: array < MapEntry < int, int >, 3 > range2Definer { MapEntry < int, int > ( 5, 1 ), MapEntry < int, int > (6, 2), MapEntry < int, int > (7, 2) };
        std :: vector < MapEntry < int, int > > range3Definer { {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25} };

        allOk = allOk && mutableCollectionTestGroupRandomInsertion <
                cds :: HashMap < int, int >,
                MapEntry < int, int >
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                MapEntry < int, int > {2, 3}, MapEntry < int, int > {3, 2}, MapEntry < int, int > {4, 6},
                cds :: Array < MapEntry < int, int > > ( { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} } ),
                { {5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18} },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_hm (int, int, {5, 87}),
                make_hm (int, int, {8, 16}),
                make_hm (int, int, {2, 3}, {3, 2}, {4, 6}),
                make_hm (int, int, {100, 10}, {200, 20}, {300, 30}, {400, 40}),
                make_hm (int, int, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}),
                make_hm (int, int, {5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18}),
                make_hm (int, int, {10, 20}, {20, 40}, {30, 60}, {40, 80}),
                make_hm (int, int, {5, 1}, {6,2 }, {7, 2}),
                make_hm (int, int, {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}),
                MapEntry < int, int > {100, 10}, MapEntry < int, int > {200, 20}, MapEntry < int, int > {300, 30}, MapEntry < int, int > {400, 40}
        );

        /* MutableCollectionTestCase-RandomInsertion-specialEmplace-cpp-xx : MCTC-00810-RI-specialEmplace-cpp-xx */
        cds :: HashMap < int, int > hm00810;
        cds :: MutableCollection < MapEntry < int, int > > & RI00810 = hm00810;

        RI00810.emplace ( 3, 5 );
        RI00810.emplace ( 4, 5 );

        if ( ! RI00810.equals ( cds :: HashMap < int, int > { { 3, 5 }, { 4, 5 } } ) ) {
            this->logError( "'MCTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : MCTG-00800-RI-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        String byCopy = 5;
        String byMove = "Ana are mere";

        cds :: Array < String > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < std :: string > range3Definer { "w1", "s2", "s3", "w4", "s25", "t35" };

        allOk = allOk && mutableCollectionTestGroupRandomInsertion <
                cds :: Array < String >,
                String
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, "Whoa", cds :: StringView ( "Test case" ),
                make_a (String, 1, 2, 3, 4, 5),
                { "w1", 6, "w2", 8, "W3" },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_a (String, 5),
                make_a (String, "Ana are mere"),
                make_a (String, "2", "Whoa", "Test case"),
                make_a (String, "100", "-300", "word", "word2"),
                make_a (String, 1, 2, 3, 4, 5),
                make_a (String, "w1", 6, "w2", 8, "W3"),
                make_a (String, 10, 20, 30, 40),
                make_a (String, 10, 11, 12, 13, 14),
                make_a (String, "w1", "s2", "s3", "w4", "s25", "t35"),
                100, -300, "word", "word2"
        );
    });

    return allOk;
}
