#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

#include <CDS/Tuple>
#include <CDS/Array>

namespace {

    using cds::Tuple;
    using cds::Size;
    using cds::Array;

    using cds::makeTuple;

    template <typename E>
    using TestDataSRes = Tuple <bool, E>;

    template <typename E>
    using TestDataMRes = Tuple <Size, Array <E>>;

    template <typename E>
    using TestDataFindOf = Tuple <
            Size,
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>
    >;

    template <typename E>
    using TestDataFindNotOf = TestDataFindOf <E>;

    template <typename E>
    using TestDataFindFirstOf = Tuple <
            TestDataSRes <E>,
            TestDataSRes <E>,
            TestDataSRes <E>,
            TestDataSRes <E>,
            TestDataSRes <E>
    >;

    template <typename E>
    using TestDataFindFirstNotOf = TestDataFindFirstOf <E>;

    template <typename E>
    using TestDataFindLastOf = TestDataFindFirstOf <E>;

    template <typename E>
    using TestDataFindLastNotOf = TestDataFindFirstOf <E>;

    template <typename E>
    using TestDataFindAllOf = Tuple <
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>,
            TestDataMRes <E>
    >;

    template <typename E>
    using TestDataFindAllNotOf = TestDataFindAllOf <E>;

    template <typename E>
    using TestData = Tuple <
            TestDataFindOf <E>,
            TestDataFindFirstOf <E>,
            TestDataFindLastOf <E>,
            TestDataFindAllOf <E>
    >;

    /* CollectionTestGroup-FindThat-cpp-xx : CTG-00600-FT-cpp-xx. CTC-00601-FT to CTC-00634-FT */
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
    > auto collectionTestGroupFindThat (
            Test                                          const * const pTestLib,
            cds :: Collection < __ElementType >                 const & underTest,
            Tuple <
                    __NonePredicate, __OnePredicate,
                    __MorePredicateLessThanLimit, __MorePredicate,
                    __MorePredicateMoreThanLimit, __AllPredicate,
                    __AllAndMorePredicate
            >                                                   const & predicateSet,
            TestData <__ElementType>                            const & tData
    ) -> bool {

        auto const & none = predicateSet.template get <0> ();
        auto const & one = predicateSet.template get <1> ();
        auto const & moreLessThanLimit = predicateSet.template get <2> ();
        auto const & more = predicateSet.template get <3> ();
        auto const & moreMoreThanLimit = predicateSet.template get <4> ();
        auto const & all = predicateSet.template get <5> ();
        auto const & allAndMore = predicateSet.template get <6> ();

        auto const & tDataFT = tData.template get <0> ();
        auto const & tDataFFT = tData.template get <1> ();
        auto const & tDataFLT = tData.template get <2> ();
        auto const & tDataFAT = tData.template get <3> ();

        auto const limit = tDataFT.template get <0> ();

        auto const expectedSizeFindThatNone = tDataFT.template get<1> ().template get<0> ();
        auto const expectedSizeFindThatOne = tDataFT.template get<2> ().template get<0> ();
        auto const expectedSizeFindThatMoreLessThanLimit = tDataFT.template get<3> ().template get<0> ();
        auto const expectedSizeFindThatMore = tDataFT.template get<4> ().template get<0> ();
        auto const expectedSizeFindThatMoreMoreThanLimit = tDataFT.template get<5> ().template get<0> ();
        auto const expectedSizeFindThatAll = tDataFT.template get<6> ().template get<0> ();
        auto const expectedSizeFindThatAllAndMore = tDataFT.template get<7> ().template get<0> ();

        auto const & expectedFindThatNone = tDataFT.template get<1> ().template get<1> ();
        auto const & expectedFindThatOne = tDataFT.template get<2> ().template get<1> ();
        auto const & expectedFindThatMoreLessThanLimit = tDataFT.template get<3> ().template get<1> ();
        auto const & expectedFindThatMore = tDataFT.template get<4> ().template get<1> ();
        auto const & expectedFindThatMoreMoreThanLimit = tDataFT.template get<5> ().template get<1> ();
        auto const & expectedFindThatAll = tDataFT.template get<6> ().template get<1> ();
        auto const & expectedFindThatAllAndMore = tDataFT.template get<7> ().template get<1> ();

        auto const expectedResultFindFirstThatNone = tDataFFT.template get <0> ().template get<0> ();
        auto const expectedResultFindFirstThatOne = tDataFFT.template get <1> ().template get<0> ();
        auto const expectedResultFindFirstThatMore = tDataFFT.template get <2> ().template get<0> ();
        auto const expectedResultFindFirstThatAll = tDataFFT.template get <3> ().template get<0> ();
        auto const expectedResultFindFirstThatAllAndMore = tDataFFT.template get <4> ().template get<0> ();

        auto const & expectedFindFirstThatNone = tDataFFT.template get <0> ().template get<1> ();
        auto const & expectedFindFirstThatOne = tDataFFT.template get <1> ().template get<1> ();
        auto const & expectedFindFirstThatMore = tDataFFT.template get <2> ().template get<1> ();
        auto const & expectedFindFirstThatAll = tDataFFT.template get <3> ().template get<1> ();
        auto const & expectedFindFirstThatAllAndMore = tDataFFT.template get <4> ().template get<1> ();

        auto const expectedResultFindLastThatNone = tDataFLT.template get <0> ().template get<0> ();
        auto const expectedResultFindLastThatOne = tDataFLT.template get <1> ().template get<0> ();
        auto const expectedResultFindLastThatMore = tDataFLT.template get <2> ().template get<0> ();
        auto const expectedResultFindLastThatAll = tDataFLT.template get <3> ().template get<0> ();
        auto const expectedResultFindLastThatAllAndMore = tDataFLT.template get <4> ().template get<0> ();

        auto const & expectedFindLastThatNone = tDataFLT.template get <0> ().template get<1> ();
        auto const & expectedFindLastThatOne = tDataFLT.template get <1> ().template get<1> ();
        auto const & expectedFindLastThatMore = tDataFLT.template get <2> ().template get<1> ();
        auto const & expectedFindLastThatAll = tDataFLT.template get <3> ().template get<1> ();
        auto const & expectedFindLastThatAllAndMore = tDataFLT.template get <4> ().template get<1> ();

        auto const expectedSizeFindAllThatNone = tDataFAT.template get <0> ().template get<0> ();
        auto const expectedSizeFindAllThatOne = tDataFAT.template get <1> ().template get<0> ();
        auto const expectedSizeFindAllThatMore = tDataFAT.template get <2> ().template get<0> ();
        auto const expectedSizeFindAllThatAll = tDataFAT.template get <3> ().template get<0> ();
        auto const expectedSizeFindAllThatAllAndMore = tDataFAT.template get <4> ().template get<0> ();

        auto const & expectedFindAllThatNone = tDataFAT.template get <0> ().template get<1> ();
        auto const & expectedFindAllThatOne = tDataFAT.template get <1> ().template get<1> ();
        auto const & expectedFindAllThatMore = tDataFAT.template get <2> ().template get<1> ();
        auto const & expectedFindAllThatAll = tDataFAT.template get <3> ().template get<1> ();
        auto const & expectedFindAllThatAllAndMore = tDataFAT.template get <4> ().template get<1> ();

        pTestLib->log ( "Object Under Test : %s", underTest.toString().cStr() );
        using ConstIterator = typename cds :: Collection < __ElementType > :: ConstIterator;

        /* CollectionTestCase-FindThat-findThatStoreInMatchingNone-cpp-xx : CTC-00601-FT-findThatStoreInMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00601 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00601;
        auto                                                        expectedSize00601 = expectedSizeFindThatNone;
        auto                                                const & expected00601 = expectedFindThatNone;
        auto                                                const & predicate00601 = none;

        (void) collection00601.findThat ( limit, storeIn00601, predicate00601 );
        if ( ( storeIn00601.size() != expectedSize00601 ) || ( ! iteratorListEqualityCheck ( predicate00601, storeIn00601, expected00601 ) ) ) {
            pTestLib->logError( "'CTC-00601-FT-findThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00601-FT-findThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatStoreInMatchingOne-cpp-xx : CTC-00602-FT-findThatStoreInMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00602 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00602;
        auto                                                        expectedSize00602 = expectedSizeFindThatOne;
        auto                                                const & expected00602 = expectedFindThatOne;
        auto                                                const & predicate00602 = one;

        (void) collection00602.findThat ( limit, storeIn00602, predicate00602 );
        if ( ( storeIn00602.size() != expectedSize00602 ) || ( ! iteratorListEqualityCheck ( predicate00602, storeIn00602, expected00602 ) ) ) {
            pTestLib->logError( "'CTC-00602-FT-findThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00602-FT-findThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatStoreInMatchingMoreLessThanLimit-cpp-xx : CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00603 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00603;
        auto                                                        expectedSize00603 = expectedSizeFindThatMoreLessThanLimit;
        auto                                                const & expected00603 = expectedFindThatMoreLessThanLimit;
        auto                                                const & predicate00603 = moreLessThanLimit;

        (void) collection00603.findThat ( limit, storeIn00603, predicate00603 );
        if ( ( storeIn00603.size() != expectedSize00603 ) || ( ! iteratorListEqualityCheck ( predicate00603, storeIn00603, expected00603 ) ) ) {
            pTestLib->logError( "'CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatStoreInMatchingMore-cpp-xx : CTC-00604-FT-findThatStoreInMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00604 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00604;
        auto                                                        expectedSize00604 = expectedSizeFindThatMore;
        auto                                                const & expected00604 = expectedFindThatMore;
        auto                                                const & predicate00604 = more;

        (void) collection00604.findThat ( limit, storeIn00604, predicate00604 );
        if ( ( storeIn00604.size() != expectedSize00604 ) || ( ! iteratorListEqualityCheck ( predicate00604, storeIn00604, expected00604 ) ) ) {
            pTestLib->logError( "'CTC-00604-FT-findThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00604-FT-findThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatStoreInMatchingMoreMoreThanLimit-cpp-xx : CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00605 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00605;
        auto                                                        expectedSize00605 = expectedSizeFindThatMoreMoreThanLimit;
        auto                                                const & expected00605 = expectedFindThatMoreMoreThanLimit;
        auto                                                const & predicate00605 = moreMoreThanLimit;

        (void) collection00605.findThat ( limit, storeIn00605, predicate00605 );
        if ( ( storeIn00605.size() != expectedSize00605 ) || ( ! iteratorListEqualityCheck ( predicate00605, storeIn00605, expected00605 ) ) ) {
            pTestLib->logError( "'CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatStoreInMatchingAll-cpp-xx : CTC-00606-FT-findThatStoreInMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00606 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00606;
        auto                                                        expectedSize00606 = expectedSizeFindThatAll;
        auto                                                const & expected00606 = expectedFindThatAll;
        auto                                                const & predicate00606 = all;

        (void) collection00606.findThat ( limit, storeIn00606, predicate00606 );
        if ( ( storeIn00606.size() != expectedSize00606 ) || ( ! iteratorListEqualityCheck ( predicate00606, storeIn00606, expected00606 ) ) ) {
            pTestLib->logError( "'CTC-00606-FT-findThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00606-FT-findThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatStoreInMatchingAllAndMore-cpp-xx : CTC-00607-FT-findThatStoreInMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00607 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00607;
        auto                                                        expectedSize00607 = expectedSizeFindThatAllAndMore;
        auto                                                const & expected00607 = expectedFindThatAllAndMore;
        auto                                                const & predicate00607 = allAndMore;

        (void) collection00607.findThat ( limit, storeIn00607, predicate00607 );
        if ( ( storeIn00607.size() != expectedSize00607 ) || ( ! iteratorListEqualityCheck ( predicate00607, storeIn00607, expected00607 ) ) ) {
            pTestLib->logError( "'CTC-00607-FT-findThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00607-FT-findThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatReturnedMatchingNone-cpp-xx : CTC-00608-FT-findThatReturnedMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00608 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00608;
        auto                                                        expectedSize00608 = expectedSizeFindThatNone;
        auto                                                const & expected00608 = expectedFindThatNone;
        auto                                                const & predicate00608 = none;

        storeIn00608 = collection00608.template findThat < __ComparisonEquivalent > ( limit, predicate00608 );
        if ( ( storeIn00608.size() != expectedSize00608 ) || ( ! iteratorListEqualityCheck ( predicate00608, storeIn00608, expected00608 ) ) ) {
            pTestLib->logError( "'CTC-00608-FT-findThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00608-FT-findThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatReturnedMatchingOne-cpp-xx : CTC-00609-FT-findThatReturnedMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00609 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00609;
        auto                                                        expectedSize00609 = expectedSizeFindThatOne;
        auto                                                const & expected00609 = expectedFindThatOne;
        auto                                                const & predicate00609 = one;

        storeIn00609 = collection00609.template findThat < __ComparisonEquivalent > ( limit, predicate00609 );
        if ( ( storeIn00609.size() != expectedSize00609 ) || ( ! iteratorListEqualityCheck ( predicate00609, storeIn00609, expected00609 ) ) ) {
            pTestLib->logError( "'CTC-00609-FT-findThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00609-FT-findThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatReturnedMatchingMoreLessThanLimit-cpp-xx : CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00610 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00610;
        auto                                                        expectedSize00610 = expectedSizeFindThatMoreLessThanLimit;
        auto                                                const & expected00610 = expectedFindThatMoreLessThanLimit;
        auto                                                const & predicate00610 = moreLessThanLimit;

        storeIn00610 = collection00610.template findThat < __ComparisonEquivalent > ( limit, predicate00610 );
        if ( ( storeIn00610.size() != expectedSize00610 ) || ( ! iteratorListEqualityCheck ( predicate00610, storeIn00610, expected00610 ) ) ) {
            pTestLib->logError( "'CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatReturnedMatchingMore-cpp-xx : CTC-00611-FT-findThatReturnedMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00611 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00611;
        auto                                                        expectedSize00611 = expectedSizeFindThatMore;
        auto                                                const & expected00611 = expectedFindThatMore;
        auto                                                const & predicate00611 = more;

        storeIn00611 = collection00611.template findThat < __ComparisonEquivalent > ( limit, predicate00611 );
        if ( ( storeIn00611.size() != expectedSize00611 ) || ( ! iteratorListEqualityCheck ( predicate00611, storeIn00611, expected00611 ) ) ) {
            pTestLib->logError( "'CTC-00611-FT-findThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00611-FT-findThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatReturnedMatchingMoreMoreThanLimit-cpp-xx : CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00612 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00612;
        auto                                                        expectedSize00612 = expectedSizeFindThatMoreMoreThanLimit;
        auto                                                const & expected00612 = expectedFindThatMoreMoreThanLimit;
        auto                                                const & predicate00612 = moreMoreThanLimit;

        storeIn00612 = collection00612.template findThat < __ComparisonEquivalent > ( limit, predicate00612 );
        if ( ( storeIn00612.size() != expectedSize00612 ) || ( ! iteratorListEqualityCheck ( predicate00612, storeIn00612, expected00612 ) ) ) {
            pTestLib->logError( "'CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatReturnedMatchingAll-cpp-xx : CTC-00613-FT-findThatReturnedMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00613 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00613;
        auto                                                        expectedSize00613 = expectedSizeFindThatAll;
        auto                                                const & expected00613 = expectedFindThatAll;
        auto                                                const & predicate00613 = all;

        storeIn00613 = collection00613.template findThat < __ComparisonEquivalent > ( limit, predicate00613 );
        if ( ( storeIn00613.size() != expectedSize00613 ) || ( ! iteratorListEqualityCheck ( predicate00613, storeIn00613, expected00613 ) ) ) {
            pTestLib->logError( "'CTC-00613-FT-findThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00613-FT-findThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findThatReturnedMatchingAllAndMore-cpp-xx : CTC-00614-FT-findThatReturnedMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00614 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00614;
        auto                                                        expectedSize00614 = expectedSizeFindThatAllAndMore;
        auto                                                const & expected00614 = expectedFindThatAllAndMore;
        auto                                                const & predicate00614 = allAndMore;

        storeIn00614 = collection00614.template findThat < __ComparisonEquivalent > ( limit, predicate00614 );
        if ( ( storeIn00614.size() != expectedSize00614 ) || ( ! iteratorListEqualityCheck ( predicate00614, storeIn00614, expected00614 ) ) ) {
            pTestLib->logError( "'CTC-00614-FT-findThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00614-FT-findThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findFirstThatMatchingNone-cpp-xx : CTC-00615-FT-findFirstThatMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00615 = underTest;
        ConstIterator                                               result00615;
        auto                                                        expectedValid00615 = expectedResultFindFirstThatNone;
        auto                                                        expectedValue00615 = expectedFindFirstThatNone;
        auto                                                const & predicate00615 = none;

        result00615 = collection00615.findFirstThat ( predicate00615 );
        if ( ( ( result00615 != collection00615.cend() ) != expectedValid00615 ) || (  expectedValid00615  && ( expectedValue00615  !=  * result00615 ) ) ) {
            pTestLib->logError( "'CTC-00615-FT-findFirstThatMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00615-FT-findFirstThatMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findFirstThatMatchingOne-cpp-xx : CTC-00616-FT-findFirstThatMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00616 = underTest;
        ConstIterator                                               result00616;
        auto                                                        expectedValid00616 = expectedResultFindFirstThatOne;
        auto                                                        expectedValue00616 = expectedFindFirstThatOne;
        auto                                                const & predicate00616 = one;

        result00616 = collection00616.findFirstThat ( predicate00616 );
        if ( ( ( result00616 != collection00616.cend() ) != expectedValid00616 ) || (  expectedValid00616  && ( expectedValue00616  !=  * result00616 ) ) ) {
            pTestLib->logError( "'CTC-00616-FT-findFirstThatMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00616-FT-findFirstThatMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findFirstThatMatchingMore-cpp-xx : CTC-00617-FT-findFirstThatMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00617 = underTest;
        ConstIterator                                               result00617;
        auto                                                        expectedValid00617 = expectedResultFindFirstThatMore;
        auto                                                        expectedValue00617 = expectedFindFirstThatMore;
        auto                                                const & predicate00617 = more;

        result00617 = collection00617.findFirstThat ( predicate00617 );
        if ( ( ( result00617 != collection00617.cend() ) != expectedValid00617 ) || (  expectedValid00617  && ( expectedValue00617  !=  * result00617 ) ) ) {
            pTestLib->logError( "'CTC-00617-FT-findFirstThatMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00617-FT-findFirstThatMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findFirstThatMatchingAll-cpp-xx : CTC-00618-FT-findFirstThatMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00618 = underTest;
        ConstIterator                                               result00618;
        auto                                                        expectedValid00618 = expectedResultFindFirstThatAll;
        auto                                                        expectedValue00618 = expectedFindFirstThatAll;
        auto                                                const & predicate00618 = all;

        result00618 = collection00618.findFirstThat ( predicate00618 );
        if ( ( ( result00618 != collection00618.cend() ) != expectedValid00618 ) || (  expectedValid00618  && ( expectedValue00618  !=  * result00618 ) ) ) {
            pTestLib->logError( "'CTC-00618-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00618-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findFirstThatMatchingAllAndMore-cpp-xx : CTC-00619-FT-findFirstThatMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00619 = underTest;
        ConstIterator                                               result00619;
        auto                                                        expectedValid00619 = expectedResultFindFirstThatAllAndMore;
        auto                                                        expectedValue00619 = expectedFindFirstThatAllAndMore;
        auto                                                const & predicate00619 = allAndMore;

        result00619 = collection00619.findFirstThat ( predicate00619 );
        if ( ( ( result00619 != collection00619.cend() ) != expectedValid00619 ) || (  expectedValid00619  && ( expectedValue00619  !=  * result00619 ) ) ) {
            pTestLib->logError( "'CTC-00619-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00619-FT-findFirstThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findLastThatMatchingNone-cpp-xx : CTC-00620-FT-findLastThatMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00620 = underTest;
        ConstIterator                                               result00620;
        auto                                                        expectedValid00620 = expectedResultFindLastThatNone;
        auto                                                        expectedValue00620 = expectedFindLastThatNone;
        auto                                                const & predicate00620 = none;

        result00620 = collection00620.findLastThat ( predicate00620 );
        if ( ( ( result00620 != collection00620.cend() ) != expectedValid00620 ) || (  expectedValid00620  && ( expectedValue00620  !=  * result00620 ) ) ) {
            pTestLib->logError( "'CTC-00620-FT-findLastThatMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00620-FT-findLastThatMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findLastThatMatchingOne-cpp-xx : CTC-00621-FT-findLastThatMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00621 = underTest;
        ConstIterator                                               result00621;
        auto                                                        expectedValid00621 = expectedResultFindLastThatOne;
        auto                                                        expectedValue00621 = expectedFindLastThatOne;
        auto                                                const & predicate00621 = one;

        result00621 = collection00621.findLastThat ( predicate00621 );
        if ( ( ( result00621 != collection00621.cend() ) != expectedValid00621 ) || (  expectedValid00621  && ( expectedValue00621  !=  * result00621 ) ) ) {
            pTestLib->logError( "'CTC-00621-FT-findLastThatMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00621-FT-findLastThatMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findLastThatMatchingMore-cpp-xx : CTC-00622-FT-findLastThatMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00622 = underTest;
        ConstIterator                                               result00622;
        auto                                                        expectedValid00622 = expectedResultFindLastThatMore;
        auto                                                        expectedValue00622 = expectedFindLastThatMore;
        auto                                                const & predicate00622 = more;

        result00622 = collection00622.findLastThat ( predicate00622 );
        if ( ( ( result00622 != collection00622.cend() ) != expectedValid00622 ) || (  expectedValid00622  && ( expectedValue00622  !=  * result00622 ) ) ) {
            pTestLib->logError( "'CTC-00622-FT-findLastThatMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00622-FT-findLastThatMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findLastThatMatchingAll-cpp-xx : CTC-00623-FT-findLastThatMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00623 = underTest;
        ConstIterator                                               result00623;
        auto                                                        expectedValid00623 = expectedResultFindLastThatAll;
        auto                                                        expectedValue00623 = expectedFindLastThatAll;
        auto                                                const & predicate00623 = all;

        result00623 = collection00623.findLastThat ( predicate00623 );
        if ( ( ( result00623 != collection00623.cend() ) != expectedValid00623 ) || (  expectedValid00623  && ( expectedValue00623  !=  * result00623 ) ) ) {
            pTestLib->logError( "'CTC-00623-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00623-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findLastThatMatchingAllAndMore-cpp-xx : CTC-00624-FT-findLastThatMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00624 = underTest;
        ConstIterator                                               result00624;
        auto                                                        expectedValid00624 = expectedResultFindLastThatAllAndMore;
        auto                                                        expectedValue00624 = expectedFindLastThatAllAndMore;
        auto                                                const & predicate00624 = allAndMore;

        result00624 = collection00624.findLastThat ( predicate00624 );
        if ( ( ( result00624 != collection00624.cend() ) != expectedValid00624 ) || (  expectedValid00624  && ( expectedValue00624  !=  * result00624 ) ) ) {
            pTestLib->logError( "'CTC-00624-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00624-FT-findLastThatMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatStoreInMatchingNone-cpp-xx : CTC-00625-FT-findAllThatStoreInMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00625 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00625;
        auto                                                        expectedSize00625 = expectedSizeFindAllThatNone;
        auto                                                const & expected00625 = expectedFindAllThatNone;
        auto                                                const & predicate00625 = none;

        (void) collection00625.findAllThat ( storeIn00625, predicate00625 );
        if ( ( storeIn00625.size() != expectedSize00625 ) || ( ! iteratorListEqualityCheck ( predicate00625, storeIn00625, expected00625 ) ) ) {
            pTestLib->logError( "'CTC-00625-FT-findAllThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00625-FT-findAllThatStoreInMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatStoreInMatchingOne-cpp-xx : CTC-00626-FT-findAllThatStoreInMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00626 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00626;
        auto                                                        expectedSize00626 = expectedSizeFindAllThatOne;
        auto                                                const & expected00626 = expectedFindAllThatOne;
        auto                                                const & predicate00626 = one;

        (void) collection00626.findAllThat ( storeIn00626, predicate00626 );
        if ( ( storeIn00626.size() != expectedSize00626 ) || ( ! iteratorListEqualityCheck ( predicate00626, storeIn00626, expected00626 ) ) ) {
            pTestLib->logError( "'CTC-00626-FT-findAllThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00626-FT-findAllThatStoreInMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatStoreInMatchingMore-cpp-xx : CTC-00627-FT-findAllThatStoreInMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00627 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00627;
        auto                                                        expectedSize00627 = expectedSizeFindAllThatMore;
        auto                                                const & expected00627 = expectedFindAllThatMore;
        auto                                                const & predicate00627 = more;

        (void) collection00627.findAllThat ( storeIn00627, predicate00627 );
        if ( ( storeIn00627.size() != expectedSize00627 ) || ( ! iteratorListEqualityCheck ( predicate00627, storeIn00627, expected00627 ) ) ) {
            pTestLib->logError( "'CTC-00627-FT-findAllThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00627-FT-findAllThatStoreInMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatStoreInMatchingAll-cpp-xx : CTC-00628-FT-findAllThatStoreInMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00628 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00628;
        auto                                                        expectedSize00628 = expectedSizeFindAllThatAll;
        auto                                                const & expected00628 = expectedFindAllThatAll;
        auto                                                const & predicate00628 = all;

        (void) collection00628.findAllThat ( storeIn00628, predicate00628 );
        if ( ( storeIn00628.size() != expectedSize00628 ) || ( ! iteratorListEqualityCheck ( predicate00628, storeIn00628, expected00628 ) ) ) {
            pTestLib->logError( "'CTC-00628-FT-findAllThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00628-FT-findAllThatStoreInMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatStoreInMatchingAllAndMore-cpp-xx : CTC-00629-FT-findAllThatStoreInMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00629 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00629;
        auto                                                        expectedSize00629 = expectedSizeFindAllThatAllAndMore;
        auto                                                const & expected00629 = expectedFindAllThatAllAndMore;
        auto                                                const & predicate00629 = allAndMore;

        (void) collection00629.findAllThat ( storeIn00629, predicate00629 );
        if ( ( storeIn00629.size() != expectedSize00629 ) || ( ! iteratorListEqualityCheck ( predicate00629, storeIn00629, expected00629 ) ) ) {
            pTestLib->logError( "'CTC-00629-FT-findAllThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00629-FT-findAllThatStoreInMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatReturnedMatchingNone-cpp-xx : CTC-00630-FT-findAllThatReturnedMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00630 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00630;
        auto                                                        expectedSize00630 = expectedSizeFindAllThatNone;
        auto                                                const & expected00630 = expectedFindAllThatNone;
        auto                                                const & predicate00630 = none;

        storeIn00630 = collection00630.template findAllThat < __ComparisonEquivalent > ( predicate00630 );
        if ( ( storeIn00630.size() != expectedSize00630 ) || ( ! iteratorListEqualityCheck ( predicate00630, storeIn00630, expected00630 ) ) ) {
            pTestLib->logError( "'CTC-00630-FT-findAllThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00630-FT-findAllThatReturnedMatchingNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatReturnedMatchingOne-cpp-xx : CTC-00631-FT-findAllThatReturnedMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00631 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00631;
        auto                                                        expectedSize00631 = expectedSizeFindAllThatOne;
        auto                                                const & expected00631 = expectedFindAllThatOne;
        auto                                                const & predicate00631 = one;

        storeIn00631 = collection00631.template findAllThat < __ComparisonEquivalent > ( predicate00631 );
        if ( ( storeIn00631.size() != expectedSize00631 ) || ( ! iteratorListEqualityCheck ( predicate00631, storeIn00631, expected00631 ) ) ) {
            pTestLib->logError( "'CTC-00631-FT-findAllThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00631-FT-findAllThatReturnedMatchingOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatReturnedMatchingMore-cpp-xx : CTC-00632-FT-findAllThatReturnedMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00632 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00632;
        auto                                                        expectedSize00632 = expectedSizeFindAllThatMore;
        auto                                                const & expected00632 = expectedFindAllThatMore;
        auto                                                const & predicate00632 = more;

        storeIn00632 = collection00632.template findAllThat < __ComparisonEquivalent > ( predicate00632 );
        if ( ( storeIn00632.size() != expectedSize00632 ) || ( ! iteratorListEqualityCheck ( predicate00632, storeIn00632, expected00632 ) ) ) {
            pTestLib->logError( "'CTC-00632-FT-findAllThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00632-FT-findAllThatReturnedMatchingMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatReturnedMatchingAll-cpp-xx : CTC-00633-FT-findAllThatReturnedMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00633 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00633;
        auto                                                        expectedSize00633 = expectedSizeFindAllThatAll;
        auto                                                const & expected00633 = expectedFindAllThatAll;
        auto                                                const & predicate00633 = all;

        storeIn00633 = collection00633.template findAllThat < __ComparisonEquivalent > ( predicate00633 );
        if ( ( storeIn00633.size() != expectedSize00633 ) || ( ! iteratorListEqualityCheck ( predicate00633, storeIn00633, expected00633 ) ) ) {
            pTestLib->logError( "'CTC-00633-FT-findAllThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00633-FT-findAllThatReturnedMatchingAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThat-findAllThatReturnedMatchingAllAndMore-cpp-xx : CTC-00634-FT-findAllThatReturnedMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00634 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00634;
        auto                                                        expectedSize00634 = expectedSizeFindAllThatAllAndMore;
        auto                                                const & expected00634 = expectedFindAllThatAllAndMore;
        auto                                                const & predicate00634 = allAndMore;

        storeIn00634 = collection00634.template findAllThat < __ComparisonEquivalent > ( predicate00634 );
        if ( ( storeIn00634.size() != expectedSize00634 ) || ( ! iteratorListEqualityCheck ( predicate00634, storeIn00634, expected00634 ) ) ) {
            pTestLib->logError( "'CTC-00634-FT-findAllThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00634-FT-findAllThatReturnedMatchingAllAndMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        return true;
    }

    Size const iLimit = 5U;

    auto const iPredPack = makeTuple (
            []( int x ){ return x == 10000; },
            []( int x ){ return x == 4; },
            []( int x ){ return x >= 3 && x <= 5; },
            []( int x ){ return x >= 2 && x <= 6; },
            []( int x ){ return x >= 1 && x <= 3 || x >= 5 && x <= 8; },
            []( int x ){ return x >= 1 && x <= 9; },
            []( int x ){ return x >= -50 && x <= 100; }
    );

    auto const ift = makeTuple (
            iLimit,
            makeTuple <Size, Array <int>> (0U, {}),
            makeTuple <Size, Array <int>> (1U, { 4 }),
            makeTuple <Size, Array <int>> (3U, { 3, 4, 5 }),
            makeTuple <Size, Array <int>> (5U, { 2, 3, 4, 5, 6 }),
            makeTuple <Size, Array <int>> (5U, { 1, 2, 3, 5, 6 }),
            makeTuple <Size, Array <int>> (5U, { 1, 2, 3, 4, 5 }),
            makeTuple <Size, Array <int>> (5U, { 1, 2, 3, 4, 5 })
    );

    auto const ifft = makeTuple (
            makeTuple <bool, int> (false, -1),
            makeTuple <bool, int> (true, 4),
            makeTuple <bool, int> (true, 2),
            makeTuple <bool, int> (true, 1),
            makeTuple <bool, int> (true, 1)
    );

    auto const iflt = makeTuple (
            makeTuple <bool, int> (false, -1),
            makeTuple <bool, int> (true, 4),
            makeTuple <bool, int> (true, 6),
            makeTuple <bool, int> (true, 9),
            makeTuple <bool, int> (true, 9)
    );

    auto const ifat = makeTuple (
            makeTuple <Size, Array <int>> (0U, {}),
            makeTuple <Size, Array <int>> (1U, {4}),
            makeTuple <Size, Array <int>> (5U, {2, 3, 4, 5, 6}),
            makeTuple <Size, Array <int>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <int>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9})
    );

    auto const iData = makeTuple (ift, ifft, iflt, ifat);

    auto const iiPredPack = makeTuple (
            []( MapEntry < int, int > const & x ){ return x.key() == 10000; },
            []( MapEntry < int, int > const & x ){ return x.key() == 4; },
            []( MapEntry < int, int > const & x ){ return x.key() >= 3 && x.key() <= 5; },
            []( MapEntry < int, int > const & x ){ return x.key() >= 2 && x.key() <= 6; },
            []( MapEntry < int, int > const & x ){ return x.key() >= 1 && x.key() <= 3 || x.key() >= 5 && x.key() <= 8; },
            []( MapEntry < int, int > const & x ){ return x.key() >= 1 && x.key() <= 9; },
            []( MapEntry < int, int > const & x ){ return x.key() >= -50 && x.key() <= 100; }
    );

    auto const iift = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <int, int>>> (1U, { {4, 4} }),
            makeTuple <Size, Array <MapEntry <int, int>>> (3U, { {3, 3}, {4, 4}, {5, 5} }),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} }),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6} }),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} }),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} })
    );

    auto const iifft = makeTuple (
            makeTuple <bool, MapEntry <int, int>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <int, int>> (true, {4, 4}),
            makeTuple <bool, MapEntry <int, int>> (true, {2, 2}),
            makeTuple <bool, MapEntry <int, int>> (true, {1, 1}),
            makeTuple <bool, MapEntry <int, int>> (true, {1, 1})
    );

    auto const iiflt = makeTuple (
            makeTuple <bool, MapEntry <int, int>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <int, int>> (true, {4, 4}),
            makeTuple <bool, MapEntry <int, int>> (true, {6, 6}),
            makeTuple <bool, MapEntry <int, int>> (true, {9, 9}),
            makeTuple <bool, MapEntry <int, int>> (true, {9, 9})
    );

    auto const iifat = makeTuple (
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <int, int>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}})
    );

    auto const iiData = makeTuple (iift, iifft, iiflt, iifat);

    auto const sPredPack = makeTuple (
            []( String const & x ){ return x == String(10000); },
            []( String const & x ){ return x == String(4); },
            []( String const & x ){ return x >= String(3) && x <= String(5); },
            []( String const & x ){ return x >= String(2) && x <= String(6); },
            []( String const & x ){ return x >= String(1) && x <= String(3) || x >= String(5) && x <= String(8); },
            []( String const & x ){ return x >= String(1) && x <= String(9); },
            []( String const & x ){ return x >= String(0) && x <= String(9); }
    );

    auto const sft = makeTuple (
            iLimit,
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, { 4 }),
            makeTuple <Size, Array <String>> (3U, { 3, 4, 5 }),
            makeTuple <Size, Array <String>> (5U, { 2, 3, 4, 5, 6 }),
            makeTuple <Size, Array <String>> (5U, { 1, 2, 3, 5, 6 }),
            makeTuple <Size, Array <String>> (5U, { 1, 2, 3, 4, 5 }),
            makeTuple <Size, Array <String>> (5U, { 1, 2, 3, 4, 5 })
    );

    auto const sfft = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 2),
            makeTuple <bool, String> (true, 1),
            makeTuple <bool, String> (true, 1)
    );

    auto const sflt = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 6),
            makeTuple <bool, String> (true, 9),
            makeTuple <bool, String> (true, 9)
    );

    auto const sfat = makeTuple (
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, {4}),
            makeTuple <Size, Array <String>> (5U, {2, 3, 4, 5, 6}),
            makeTuple <Size, Array <String>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <String>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9})
    );

    auto const sData = makeTuple (sft, sfft, sflt, sfat);

    auto const osPredPack = makeTuple (
            []( String const & x ){ return x == String(10000); },
            []( String const & x ){ return x == String(4); },
            []( String const & x ){ return x >= String(3) && x <= String(5); },
            []( String const & x ){ return x >= String(2) && x <= String(6); },
            []( String const & x ){ return x >= String(1) && x <= String(3) || x >= String(5) && x <= String(8); },
            []( String const & x ){ return x >= String(1) && x <= String(9); },
            []( String const & x ){ return x >= String(0) && x <= String(9); }
    );

    auto const osft = makeTuple (
            iLimit,
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, { 4 }),
            makeTuple <Size, Array <String>> (3U, { 4, 5, 3 }),
            makeTuple <Size, Array <String>> (5U, { 4, 5, 6, 2, 3 }),
            makeTuple <Size, Array <String>> (5U, { 5, 6, 7, 8, 1 }),
            makeTuple <Size, Array <String>> (5U, { 4, 5, 6, 7, 8 }),
            makeTuple <Size, Array <String>> (5U, { 4, 5, 6, 7, 8 })
    );

    auto const osfft = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 4)
    );

    auto const osflt = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 3),
            makeTuple <bool, String> (true, 3),
            makeTuple <bool, String> (true, 3)
    );

    auto const osfat = makeTuple (
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, {4}),
            makeTuple <Size, Array <String>> (5U, {4, 5, 6, 2, 3}),
            makeTuple <Size, Array <String>> (9U, {4, 5, 6, 7, 8, 9, 1, 2, 3}),
            makeTuple <Size, Array <String>> (9U, {4, 5, 6, 7, 8, 9, 1, 2, 3})
    );

    auto const osData = makeTuple (osft, osfft, osflt, osfat);

    auto const ssPredPack = makeTuple (
            []( MapEntry < String, String > const & x ){ return x.key() == String(10000); },
            []( MapEntry < String, String > const & x ){ return x.key() == String(4); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(3) && x.key() <= String(5); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(2) && x.key() <= String(6); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(1) && x.key() <= String(3) || x.key() >= String(5) && x.key() <= String(8); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(1) && x.key() <= String(9); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(0) && x.key() <= String(9); }
    );

    auto const ssft = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, { {4, 4} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (3U, { {3, 3}, {4, 4}, {5, 5} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} })
    );

    auto const ssfft = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {2, 2}),
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1}),
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1})
    );

    auto const ssflt = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {6, 6}),
            makeTuple <bool, MapEntry <String, String>> (true, {9, 9}),
            makeTuple <bool, MapEntry <String, String>> (true, {9, 9})
    );

    auto const ssfat = makeTuple (
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}})
    );

    auto const ssData = makeTuple (ssft, ssfft, ssflt, ssfat);

    auto const ossPredPack = makeTuple (
            []( MapEntry < String, String > const & x ){ return x.key() == String(10000); },
            []( MapEntry < String, String > const & x ){ return x.key() == String(4); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(3) && x.key() <= String(5); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(2) && x.key() <= String(6); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(1) && x.key() <= String(3) || x.key() >= String(5) && x.key() <= String(8); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(1) && x.key() <= String(9); },
            []( MapEntry < String, String > const & x ){ return x.key() >= String(0) && x.key() <= String(9); }
    );

    auto const ossft = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, { {4, 4} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (3U, { {4, 4}, {5, 5}, {3, 3} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} }),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} })
    );

    auto const ossfft = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4})
    );

    auto const ossflt = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3}),
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3}),
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3})
    );

    auto const ossfat = makeTuple (
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}})
    );

    auto const ossData = makeTuple (ossft, ossfft, ossflt, ossfat);
} /* namespace */

auto CollectionTest::tests_00600_00699 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        cds :: Array < int > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iPredPack, iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        cds :: LinkedList < int > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iPredPack, iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntHashSet", [this, & allOk] {

        cds :: HashSet < int > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iPredPack, iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntTreeSet", [this, & allOk] {

        cds :: TreeSet < int > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iPredPack, iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [this, & allOk] {

        cds :: LinkedHashSet < int > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iPredPack, iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk] {

        cds :: HashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iiPredPack, iiData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, & allOk] {

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iiPredPack, iiData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, & allOk] {

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                iiPredPack, iiData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                sPredPack, sData
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                sPredPack, sData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringHashSet", [this, & allOk] {

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                osPredPack, osData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringTreeSet", [this, & allOk] {

        cds :: TreeSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                sPredPack, sData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [this, & allOk] {

        cds :: LinkedHashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                sPredPack, sData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk] {

        cds :: HashMap < String, String > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                ossPredPack, ossData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [this, & allOk] {

        cds :: LinkedHashMap < String, String > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                ssPredPack, ssData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindThat-" __CDS_cpplang_core_version_name " : CTG-00600-FT-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [this, & allOk] {

        cds :: TreeMap < String, String > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupFindThat (
                this,
                underTest,
                ssPredPack, ssData
        );
    });
    
    this->executeSubtest ( "CollectionTestGroup-FindThatMemberFunction-" __CDS_cpplang_core_version_name " : CTG-00650-FTMF-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        /* CollectionTestGroup-FindThatMemberFunction-cpp-xx : CTG-00650-FTMF-cpp-xx : CTC-00651-FTMF to CTC-00656-FTMF */

        cds :: Array < String > arr = { "word1", "", "word2", "", "word3", "word4", "", "word5" };
        cds :: Collection < String > const & underTest = arr;
        using ConstIterator = cds :: Collection < String > :: ConstIterator;

        /* CollectionTestCase-FindThatMemberFunction-findThatStoreInMemberFunction-cpp-xx : CTC-00651-FTMF-findThatStoreInMemberFunction-cpp-xx */
        cds :: Array < ConstIterator > storeIn651;
        underTest.findThat ( 2, storeIn651, & String :: empty );

        if ( ( storeIn651.size() != 2 || * ( ++ storeIn651[0] ) != "word2" ) || ( * ( ++ storeIn651[1] ) != "word3" ) ) {
            this->logError( "'CTC-00651-FTMF-findThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00651-FTMF-findThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findThatReturnedMemberFunction-cpp-xx : CTC-00652-FTMF-findThatReturnedMemberFunction-cpp-xx */
        cds :: Array < ConstIterator > storeIn652;
        storeIn652 = underTest.findThat < cds :: Array > ( 2, & String :: empty );

        if ( ( storeIn652.size() != 2 || * ( ++ storeIn652[0] ) != "word2" ) || ( * ( ++ storeIn652[1] ) != "word3" ) ) {
            this->logError( "'CTC-00652-FTMF-findThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00652-FTMF-findThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findFirstThatMemberFunction-cpp-xx : CTC-00653-FTMF-findFirstThatMemberFunction-cpp-xx */
        ConstIterator res653;
        res653 = underTest.findFirstThat ( & String :: empty );

        if ( ( ! static_cast <bool> (res653) ) || ( * ( ++ res653 ) != "word2" ) ) {
            this->logError( "'CTC-00653-FTMF-findFirstThatMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00653-FTMF-findFirstThatMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findLastThatMemberFunction-cpp-xx : CTC-00654-FTMF-findLastThatMemberFunction-cpp-xx */
        ConstIterator res654;
        res654 = underTest.findLastThat ( & String :: empty );

        if ( ( ! static_cast <bool> (res654) ) || ( * ( ++ res654 ) != "word5" ) ) {
            this->logError( "'CTC-00654-FTMF-findLastThatMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00654-FTMF-findLastThatMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findAllThatStoreInMemberFunction-cpp-xx : CTC-00655-FTMF-findAllThatStoreInMemberFunction-cpp-xx */
        cds :: Array < ConstIterator > storeIn655;
        underTest.findAllThat ( storeIn655, & String :: empty );

        if ( ( storeIn655.size() != 3 || * ( ++ storeIn655[0] ) != "word2" || * ( ++ storeIn655[1] ) != "word3" ) || ( * ( ++ storeIn655 [2] ) != "word5" ) ) {
            this->logError( "'CTC-00655-FTMF-findAllThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00655-FTMF-findAllThatStoreInMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-FindThatMemberFunction-findAllThatReturnedMemberFunction-cpp-xx : CTC-00656-FTMF-findAllThatReturnedMemberFunction-cpp-xx */
        cds :: Array < ConstIterator > storeIn656;
        storeIn656 = underTest.findAllThat < cds :: Array > ( & String :: empty );

        if ( ( storeIn656.size() != 3 || * ( ++ storeIn656[0] ) != "word2" || * ( ++ storeIn656[1] ) != "word3" ) || ( * ( ++ storeIn656 [2] ) != "word5" ) ) {
            this->logError( "'CTC-00656-FTMF-findAllThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' failed" );
            return;
        } else {
            this->logOK ( "'CTC-00656-FTMF-findAllThatReturnedMemberFunction-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

    return allOk;
}
