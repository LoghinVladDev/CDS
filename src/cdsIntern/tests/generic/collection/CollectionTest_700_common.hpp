#ifndef COLLECTION_TEST_700_COMMON_H
#define COLLECTION_TEST_700_COMMON_H

#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

#include <CDS/Tuple>

namespace {

    using cds::Tuple;
    using cds::Size;
    using cds::Array;

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
            TestDataFindAllOf <E>,
            TestDataFindNotOf <E>,
            TestDataFindFirstNotOf <E>,
            TestDataFindLastNotOf <E>,
            TestDataFindAllNotOf <E>
    >;

    template <typename T>
    using __ComparisonEquivalent = cds::Array <T>;

    /* CollectionTestGroup-FindOf-cpp-xx : CTG-00700-FO-cpp-xx. CTC-00701-FO to CTC-00768-FO */
    template <
            typename __IterableType,                                                                /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType                                                                  /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupFindOf (
            Test                                                      * pTestLib,
            StringLiteral                                               variant,
            cds :: Collection < __ElementType >                 const & underTest,
            std::initializer_list <__IterableType const *>      const & targets, 
            TestData <__ElementType>                            const & tData
            // __IterableType                                      const & none,
            // __IterableType                                      const & one,
            // __IterableType                                      const & moreLessThanLimit,
            // __IterableType                                      const & more,
            // __IterableType                                      const & moreMoreThanLimit,
            // __IterableType                                      const & all,
            // __IterableType                                      const & allAndMore,
            // Size                                                        expectedSizeFindOfNone,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindOfNone,
            // Size                                                        expectedSizeFindOfOne,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindOfOne,
            // Size                                                        expectedSizeFindOfMoreLessThanLimit,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindOfMoreLessThanLimit,
            // Size                                                        expectedSizeFindOfMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindOfMore,
            // Size                                                        expectedSizeFindOfMoreMoreThanLimit,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindOfMoreMoreThanLimit,
            // Size                                                        expectedSizeFindOfAll,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindOfAll,
            // Size                                                        expectedSizeFindOfAllAndMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindOfAllAndMore,
            // bool                                                        expectedResultFindFirstOfNone,
            // __ElementType                                       const & expectedFindFirstOfNone,
            // bool                                                        expectedResultFindFirstOfOne,
            // __ElementType                                       const & expectedFindFirstOfOne,
            // bool                                                        expectedResultFindFirstOfMore,
            // __ElementType                                       const & expectedFindFirstOfMore,
            // bool                                                        expectedResultFindFirstOfAll,
            // __ElementType                                       const & expectedFindFirstOfAll,
            // bool                                                        expectedResultFindFirstOfAllAndMore,
            // __ElementType                                       const & expectedFindFirstOfAllAndMore,
            // bool                                                        expectedResultFindLastOfNone,
            // __ElementType                                       const & expectedFindLastOfNone,
            // bool                                                        expectedResultFindLastOfOne,
            // __ElementType                                       const & expectedFindLastOfOne,
            // bool                                                        expectedResultFindLastOfMore,
            // __ElementType                                       const & expectedFindLastOfMore,
            // bool                                                        expectedResultFindLastOfAll,
            // __ElementType                                       const & expectedFindLastOfAll,
            // bool                                                        expectedResultFindLastOfAllAndMore,
            // __ElementType                                       const & expectedFindLastOfAllAndMore,
            // Size                                                        expectedSizeFindAllOfNone,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfNone,
            // Size                                                        expectedSizeFindAllOfOne,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfOne,
            // Size                                                        expectedSizeFindAllOfMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfMore,
            // Size                                                        expectedSizeFindAllOfAll,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfAll,
            // Size                                                        expectedSizeFindAllOfAllAndMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllOfAllAndMore,
            // Size                                                        expectedSizeFindNotOfNone,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfNone,
            // Size                                                        expectedSizeFindNotOfOne,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfOne,
            // Size                                                        expectedSizeFindNotOfMoreLessThanLimit,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfMoreLessThanLimit,
            // Size                                                        expectedSizeFindNotOfMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfMore,
            // Size                                                        expectedSizeFindNotOfMoreMoreThanLimit,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfMoreMoreThanLimit,
            // Size                                                        expectedSizeFindNotOfAll,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfAll,
            // Size                                                        expectedSizeFindNotOfAllAndMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindNotOfAllAndMore,
            // bool                                                        expectedResultFindFirstNotOfNone,
            // __ElementType                                       const & expectedFindFirstNotOfNone,
            // bool                                                        expectedResultFindFirstNotOfOne,
            // __ElementType                                       const & expectedFindFirstNotOfOne,
            // bool                                                        expectedResultFindFirstNotOfMore,
            // __ElementType                                       const & expectedFindFirstNotOfMore,
            // bool                                                        expectedResultFindFirstNotOfAll,
            // __ElementType                                       const & expectedFindFirstNotOfAll,
            // bool                                                        expectedResultFindFirstNotOfAllAndMore,
            // __ElementType                                       const & expectedFindFirstNotOfAllAndMore,
            // bool                                                        expectedResultFindLastNotOfNone,
            // __ElementType                                       const & expectedFindLastNotOfNone,
            // bool                                                        expectedResultFindLastNotOfOne,
            // __ElementType                                       const & expectedFindLastNotOfOne,
            // bool                                                        expectedResultFindLastNotOfMore,
            // __ElementType                                       const & expectedFindLastNotOfMore,
            // bool                                                        expectedResultFindLastNotOfAll,
            // __ElementType                                       const & expectedFindLastNotOfAll,
            // bool                                                        expectedResultFindLastNotOfAllAndMore,
            // __ElementType                                       const & expectedFindLastNotOfAllAndMore,
            // Size                                                        expectedSizeFindAllNotOfNone,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfNone,
            // Size                                                        expectedSizeFindAllNotOfOne,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfOne,
            // Size                                                        expectedSizeFindAllNotOfMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfMore,
            // Size                                                        expectedSizeFindAllNotOfAll,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfAll,
            // Size                                                        expectedSizeFindAllNotOfAllAndMore,
            // __ComparisonEquivalent < __ElementType >            const & expectedFindAllNotOfAllAndMore
    ) -> bool {

        auto targetIt = targets.begin();
        auto const & none = ** targetIt;
        ++ targetIt;
        auto const & one = ** targetIt;
        ++ targetIt;
        auto const & moreLessThanLimit = ** targetIt;
        ++ targetIt;
        auto const & more = ** targetIt;
        ++ targetIt;
        auto const & moreMoreThanLimit = ** targetIt;
        ++ targetIt;
        auto const & all = ** targetIt;
        ++ targetIt;
        auto const & allAndMore = ** targetIt;

        auto const & tDataFO = tData.template get <0> ();
        auto const & tDataFFO = tData.template get <1> ();
        auto const & tDataFLO = tData.template get <2> ();
        auto const & tDataFAO = tData.template get <3> ();
        auto const & tDataFNO = tData.template get <4> ();
        auto const & tDataFFNO = tData.template get <5> ();
        auto const & tDataFLNO = tData.template get <6> ();
        auto const & tDataFANO = tData.template get <7> ();

        auto const limit = tDataFO.template get <0> ();

        auto const expectedSizeFindOfNone = tDataFO.template get<1> ().template get<0> ();
        auto const expectedSizeFindOfOne = tDataFO.template get<2> ().template get<0> ();
        auto const expectedSizeFindOfMoreLessThanLimit = tDataFO.template get<3> ().template get<0> ();
        auto const expectedSizeFindOfMore = tDataFO.template get<4> ().template get<0> ();
        auto const expectedSizeFindOfMoreMoreThanLimit = tDataFO.template get<5> ().template get<0> ();
        auto const expectedSizeFindOfAll = tDataFO.template get<6> ().template get<0> ();
        auto const expectedSizeFindOfAllAndMore = tDataFO.template get<7> ().template get<0> ();

        auto const & expectedFindOfNone = tDataFO.template get<1> ().template get<1> ();
        auto const & expectedFindOfOne = tDataFO.template get<2> ().template get<1> ();
        auto const & expectedFindOfMoreLessThanLimit = tDataFO.template get<3> ().template get<1> ();
        auto const & expectedFindOfMore = tDataFO.template get<4> ().template get<1> ();
        auto const & expectedFindOfMoreMoreThanLimit = tDataFO.template get<5> ().template get<1> ();
        auto const & expectedFindOfAll = tDataFO.template get<6> ().template get<1> ();
        auto const & expectedFindOfAllAndMore = tDataFO.template get<7> ().template get<1> ();

        auto const expectedResultFindFirstOfNone = tDataFFO.template get <0> ().template get<0> ();
        auto const expectedResultFindFirstOfOne = tDataFFO.template get <1> ().template get<0> ();
        auto const expectedResultFindFirstOfMore = tDataFFO.template get <2> ().template get<0> ();
        auto const expectedResultFindFirstOfAll = tDataFFO.template get <3> ().template get<0> ();
        auto const expectedResultFindFirstOfAllAndMore = tDataFFO.template get <4> ().template get<0> ();

        auto const & expectedFindFirstOfNone = tDataFFO.template get <0> ().template get<1> ();
        auto const & expectedFindFirstOfOne = tDataFFO.template get <1> ().template get<1> ();
        auto const & expectedFindFirstOfMore = tDataFFO.template get <2> ().template get<1> ();
        auto const & expectedFindFirstOfAll = tDataFFO.template get <3> ().template get<1> ();
        auto const & expectedFindFirstOfAllAndMore = tDataFFO.template get <4> ().template get<1> ();

        auto const expectedResultFindLastOfNone = tDataFLO.template get <0> ().template get<0> ();
        auto const expectedResultFindLastOfOne = tDataFLO.template get <1> ().template get<0> ();
        auto const expectedResultFindLastOfMore = tDataFLO.template get <2> ().template get<0> ();
        auto const expectedResultFindLastOfAll = tDataFLO.template get <3> ().template get<0> ();
        auto const expectedResultFindLastOfAllAndMore = tDataFLO.template get <4> ().template get<0> ();

        auto const & expectedFindLastOfNone = tDataFLO.template get <0> ().template get<1> ();
        auto const & expectedFindLastOfOne = tDataFLO.template get <1> ().template get<1> ();
        auto const & expectedFindLastOfMore = tDataFLO.template get <2> ().template get<1> ();
        auto const & expectedFindLastOfAll = tDataFLO.template get <3> ().template get<1> ();
        auto const & expectedFindLastOfAllAndMore = tDataFLO.template get <4> ().template get<1> ();

        auto const expectedSizeFindAllOfNone = tDataFAO.template get <0> ().template get<0> ();
        auto const expectedSizeFindAllOfOne = tDataFAO.template get <1> ().template get<0> ();
        auto const expectedSizeFindAllOfMore = tDataFAO.template get <2> ().template get<0> ();
        auto const expectedSizeFindAllOfAll = tDataFAO.template get <3> ().template get<0> ();
        auto const expectedSizeFindAllOfAllAndMore = tDataFAO.template get <4> ().template get<0> ();

        auto const & expectedFindAllOfNone = tDataFAO.template get <0> ().template get<1> ();
        auto const & expectedFindAllOfOne = tDataFAO.template get <1> ().template get<1> ();
        auto const & expectedFindAllOfMore = tDataFAO.template get <2> ().template get<1> ();
        auto const & expectedFindAllOfAll = tDataFAO.template get <3> ().template get<1> ();
        auto const & expectedFindAllOfAllAndMore = tDataFAO.template get <4> ().template get<1> ();

        auto const expectedSizeFindNotOfNone = tDataFNO.template get<1> ().template get<0> ();
        auto const expectedSizeFindNotOfOne = tDataFNO.template get<2> ().template get<0> ();
        auto const expectedSizeFindNotOfMoreLessThanLimit = tDataFNO.template get<3> ().template get<0> ();
        auto const expectedSizeFindNotOfMore = tDataFNO.template get<4> ().template get<0> ();
        auto const expectedSizeFindNotOfMoreMoreThanLimit = tDataFNO.template get<5> ().template get<0> ();
        auto const expectedSizeFindNotOfAll = tDataFNO.template get<6> ().template get<0> ();
        auto const expectedSizeFindNotOfAllAndMore = tDataFNO.template get<7> ().template get<0> ();

        auto const & expectedFindNotOfNone = tDataFNO.template get<1> ().template get<1> ();
        auto const & expectedFindNotOfOne = tDataFNO.template get<2> ().template get<1> ();
        auto const & expectedFindNotOfMoreLessThanLimit = tDataFNO.template get<3> ().template get<1> ();
        auto const & expectedFindNotOfMore = tDataFNO.template get<4> ().template get<1> ();
        auto const & expectedFindNotOfMoreMoreThanLimit = tDataFNO.template get<5> ().template get<1> ();
        auto const & expectedFindNotOfAll = tDataFNO.template get<6> ().template get<1> ();
        auto const & expectedFindNotOfAllAndMore = tDataFNO.template get<7> ().template get<1> ();

        auto const expectedResultFindFirstNotOfNone = tDataFFNO.template get <0> ().template get<0> ();
        auto const expectedResultFindFirstNotOfOne = tDataFFNO.template get <1> ().template get<0> ();
        auto const expectedResultFindFirstNotOfMore = tDataFFNO.template get <2> ().template get<0> ();
        auto const expectedResultFindFirstNotOfAll = tDataFFNO.template get <3> ().template get<0> ();
        auto const expectedResultFindFirstNotOfAllAndMore = tDataFFNO.template get <4> ().template get<0> ();

        auto const & expectedFindFirstNotOfNone = tDataFFNO.template get <0> ().template get<1> ();
        auto const & expectedFindFirstNotOfOne = tDataFFNO.template get <1> ().template get<1> ();
        auto const & expectedFindFirstNotOfMore = tDataFFNO.template get <2> ().template get<1> ();
        auto const & expectedFindFirstNotOfAll = tDataFFNO.template get <3> ().template get<1> ();
        auto const & expectedFindFirstNotOfAllAndMore = tDataFFNO.template get <4> ().template get<1> ();

        auto const expectedResultFindLastNotOfNone = tDataFLNO.template get <0> ().template get<0> ();
        auto const expectedResultFindLastNotOfOne = tDataFLNO.template get <1> ().template get<0> ();
        auto const expectedResultFindLastNotOfMore = tDataFLNO.template get <2> ().template get<0> ();
        auto const expectedResultFindLastNotOfAll = tDataFLNO.template get <3> ().template get<0> ();
        auto const expectedResultFindLastNotOfAllAndMore = tDataFLNO.template get <4> ().template get<0> ();

        auto const & expectedFindLastNotOfNone = tDataFLNO.template get <0> ().template get<1> ();
        auto const & expectedFindLastNotOfOne = tDataFLNO.template get <1> ().template get<1> ();
        auto const & expectedFindLastNotOfMore = tDataFLNO.template get <2> ().template get<1> ();
        auto const & expectedFindLastNotOfAll = tDataFLNO.template get <3> ().template get<1> ();
        auto const & expectedFindLastNotOfAllAndMore = tDataFLNO.template get <4> ().template get<1> ();

        auto const expectedSizeFindAllNotOfNone = tDataFANO.template get <0> ().template get<0> ();
        auto const expectedSizeFindAllNotOfOne = tDataFANO.template get <1> ().template get<0> ();
        auto const expectedSizeFindAllNotOfMore = tDataFANO.template get <2> ().template get<0> ();
        auto const expectedSizeFindAllNotOfAll = tDataFANO.template get <3> ().template get<0> ();
        auto const expectedSizeFindAllNotOfAllAndMore = tDataFANO.template get <4> ().template get<0> ();

        auto const & expectedFindAllNotOfNone = tDataFANO.template get <0> ().template get<1> ();
        auto const & expectedFindAllNotOfOne = tDataFANO.template get <1> ().template get<1> ();
        auto const & expectedFindAllNotOfMore = tDataFANO.template get <2> ().template get<1> ();
        auto const & expectedFindAllNotOfAll = tDataFANO.template get <3> ().template get<1> ();
        auto const & expectedFindAllNotOfAllAndMore = tDataFANO.template get <4> ().template get<1> ();


        pTestLib->log ( "Object Under Test : %s", underTest.toString().cStr() );
        using ConstIterator = typename cds :: Collection < __ElementType > :: ConstIterator;

        /* CollectionTestCase-FindOf-findOfStoreInMatchingNone-cpp-xx : CTC-00701-FO-findOfStoreInMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00701 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00701;
        auto                                                        expectedSize00701 = expectedSizeFindOfNone;
        auto                                                const & expected00701 = expectedFindOfNone;
        auto                                                const & target00701 = none;

        (void) collection00701.findOf ( limit, storeIn00701, target00701 );
        if (( storeIn00701.size() != expectedSize00701 )||( ! iteratorListEqualityCheckNoPred ( storeIn00701, expected00701 ) )) {
            pTestLib->logError( "'CTC-00701-FO-findOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00701-FO-findOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfStoreInMatchingOne-cpp-xx : CTC-00702-FO-findOfStoreInMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00702 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00702;
        auto                                                        expectedSize00702 = expectedSizeFindOfOne;
        auto                                                const & expected00702 = expectedFindOfOne;
        auto                                                const & target00702 = one;

        (void) collection00702.findOf ( limit, storeIn00702, target00702 );
        if (( storeIn00702.size() != expectedSize00702 )||( ! iteratorListEqualityCheckNoPred ( storeIn00702, expected00702 ) )) {
            pTestLib->logError( "'CTC-00702-FO-findOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00702-FO-findOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfStoreInMatchingMoreLessThanLimit-cpp-xx : CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00703 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00703;
        auto                                                        expectedSize00703 = expectedSizeFindOfMoreLessThanLimit;
        auto                                                const & expected00703 = expectedFindOfMoreLessThanLimit;
        auto                                                const & target00703 = moreLessThanLimit;

        (void) collection00703.findOf ( limit, storeIn00703, target00703 );
        if (( storeIn00703.size() != expectedSize00703 )||( ! iteratorListEqualityCheckNoPred ( storeIn00703, expected00703 ) )) {
            pTestLib->logError( "'CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfStoreInMatchingMore-cpp-xx : CTC-00704-FO-findOfStoreInMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00704 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00704;
        auto                                                        expectedSize00704 = expectedSizeFindOfMore;
        auto                                                const & expected00704 = expectedFindOfMore;
        auto                                                const & target00704 = more;

        (void) collection00704.findOf ( limit, storeIn00704, target00704 );
        if (( storeIn00704.size() != expectedSize00704 )||( ! iteratorListEqualityCheckNoPred ( storeIn00704, expected00704 ) )) {
            pTestLib->logError( "'CTC-00704-FO-findOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00704-FO-findOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfStoreInMatchingMoreMoreThanLimit-cpp-xx : CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00705 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00705;
        auto                                                        expectedSize00705 = expectedSizeFindOfMoreMoreThanLimit;
        auto                                                const & expected00705 = expectedFindOfMoreMoreThanLimit;
        auto                                                const & target00705 = moreMoreThanLimit;

        (void) collection00705.findOf ( limit, storeIn00705, target00705 );
        if (( storeIn00705.size() != expectedSize00705 )||( ! iteratorListEqualityCheckNoPred ( storeIn00705, expected00705 ) )) {
            pTestLib->logError( "'CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfStoreInMatchingAll-cpp-xx : CTC-00706-FO-findOfStoreInMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00706 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00706;
        auto                                                        expectedSize00706 = expectedSizeFindOfAll;
        auto                                                const & expected00706 = expectedFindOfAll;
        auto                                                const & target00706 = all;

        (void) collection00706.findOf ( limit, storeIn00706, target00706 );
        if (( storeIn00706.size() != expectedSize00706 )||( ! iteratorListEqualityCheckNoPred ( storeIn00706, expected00706 ) )) {
            pTestLib->logError( "'CTC-00706-FO-findOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00706-FO-findOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfStoreInMatchingAllAndMore-cpp-xx : CTC-00707-FO-findOfStoreInMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00707 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00707;
        auto                                                        expectedSize00707 = expectedSizeFindOfAllAndMore;
        auto                                                const & expected00707 = expectedFindOfAllAndMore;
        auto                                                const & target00707 = allAndMore;

        (void) collection00707.findOf ( limit, storeIn00707, target00707 );
        if (( storeIn00707.size() != expectedSize00707 )||( ! iteratorListEqualityCheckNoPred ( storeIn00707, expected00707 ) )) {
            pTestLib->logError( "'CTC-00707-FO-findOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00707-FO-findOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfReturnedMatchingNone-cpp-xx : CTC-00708-FO-findOfReturnedMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00708 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00708;
        auto                                                        expectedSize00708 = expectedSizeFindOfNone;
        auto                                                const & expected00708 = expectedFindOfNone;
        auto                                                const & target00708 = none;

        storeIn00708 = collection00708.template findOf < __ComparisonEquivalent > ( limit, target00708 );
        if (( storeIn00708.size() != expectedSize00708 )||( ! iteratorListEqualityCheckNoPred ( storeIn00708, expected00708 ) )) {
            pTestLib->logError( "'CTC-00708-FO-findOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00708-FO-findOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfReturnedMatchingOne-cpp-xx : CTC-00709-FO-findOfReturnedMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00709 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00709;
        auto                                                        expectedSize00709 = expectedSizeFindOfOne;
        auto                                                const & expected00709 = expectedFindOfOne;
        auto                                                const & target00709 = one;

        storeIn00709 = collection00709.template findOf < __ComparisonEquivalent > ( limit, target00709 );
        if (( storeIn00709.size() != expectedSize00709 )||( ! iteratorListEqualityCheckNoPred ( storeIn00709, expected00709 ) )) {
            pTestLib->logError( "'CTC-00709-FO-findOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00709-FO-findOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfReturnedMatchingMoreLessThanLimit-cpp-xx : CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00710 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00710;
        auto                                                        expectedSize00710 = expectedSizeFindOfMoreLessThanLimit;
        auto                                                const & expected00710 = expectedFindOfMoreLessThanLimit;
        auto                                                const & target00710 = moreLessThanLimit;

        storeIn00710 = collection00710.template findOf < __ComparisonEquivalent > ( limit, target00710 );
        if (( storeIn00710.size() != expectedSize00710 )||( ! iteratorListEqualityCheckNoPred ( storeIn00710, expected00710 ) )) {
            pTestLib->logError( "'CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfReturnedMatchingMore-cpp-xx : CTC-00711-FO-findOfReturnedMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00711 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00711;
        auto                                                        expectedSize00711 = expectedSizeFindOfMore;
        auto                                                const & expected00711 = expectedFindOfMore;
        auto                                                const & target00711 = more;

        storeIn00711 = collection00711.template findOf < __ComparisonEquivalent > ( limit, target00711 );
        if (( storeIn00711.size() != expectedSize00711 )||( ! iteratorListEqualityCheckNoPred ( storeIn00711, expected00711 ) )) {
            pTestLib->logError( "'CTC-00711-FO-findOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00711-FO-findOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfReturnedMatchingMoreMoreThanLimit-cpp-xx : CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00712 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00712;
        auto                                                        expectedSize00712 = expectedSizeFindOfMoreMoreThanLimit;
        auto                                                const & expected00712 = expectedFindOfMoreMoreThanLimit;
        auto                                                const & target00712 = moreMoreThanLimit;

        storeIn00712 = collection00712.template findOf < __ComparisonEquivalent > ( limit, target00712 );
        if (( storeIn00712.size() != expectedSize00712 )||( ! iteratorListEqualityCheckNoPred ( storeIn00712, expected00712 ) )) {
            pTestLib->logError( "'CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfReturnedMatchingAll-cpp-xx : CTC-00713-FO-findOfReturnedMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00713 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00713;
        auto                                                        expectedSize00713 = expectedSizeFindOfAll;
        auto                                                const & expected00713 = expectedFindOfAll;
        auto                                                const & target00713 = all;

        storeIn00713 = collection00713.template findOf < __ComparisonEquivalent > ( limit, target00713 );
        if (( storeIn00713.size() != expectedSize00713 )||( ! iteratorListEqualityCheckNoPred ( storeIn00713, expected00713 ) )) {
            pTestLib->logError( "'CTC-00713-FO-findOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00713-FO-findOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findOfReturnedMatchingAllAndMore-cpp-xx : CTC-00714-FO-findOfReturnedMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00714 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00714;
        auto                                                        expectedSize00714 = expectedSizeFindOfAllAndMore;
        auto                                                const & expected00714 = expectedFindOfAllAndMore;
        auto                                                const & target00714 = allAndMore;

        storeIn00714 = collection00714.template findOf < __ComparisonEquivalent > ( limit, target00714 );
        if (( storeIn00714.size() != expectedSize00714 )||( ! iteratorListEqualityCheckNoPred ( storeIn00714, expected00714 ) )) {
            pTestLib->logError( "'CTC-00714-FO-findOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00714-FO-findOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstOfMatchingNone-cpp-xx : CTC-00715-FO-findFirstOfMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00715 = underTest;
        ConstIterator                                               result00715;
        auto                                                        expectedResult00715 = expectedResultFindFirstOfNone;
        auto                                                const & expected00715 = expectedFindFirstOfNone;
        auto                                                const & target00715 = none;

        result00715 = collection00715.findFirstOf ( target00715 );
        if (( ( result00715 != collection00715.cend() ) != expectedResult00715 )||( expectedResult00715 && expected00715 != * result00715 )) {
            pTestLib->logError( "'CTC-00715-FO-findFirstOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00715-FO-findFirstOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstOfMatchingOne-cpp-xx : CTC-00716-FO-findFirstOfMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00716 = underTest;
        ConstIterator                                               result00716;
        auto                                                        expectedResult00716 = expectedResultFindFirstOfOne;
        auto                                                const & expected00716 = expectedFindFirstOfOne;
        auto                                                const & target00716 = one;

        result00716 = collection00716.findFirstOf ( target00716 );
        if (( ( result00716 != collection00716.cend() ) != expectedResult00716 )||( expectedResult00716 && expected00716 != * result00716 )) {
            pTestLib->logError( "'CTC-00716-FO-findFirstOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00716-FO-findFirstOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstOfMatchingMore-cpp-xx : CTC-00717-FO-findFirstOfMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00717 = underTest;
        ConstIterator                                               result00717;
        auto                                                        expectedResult00717 = expectedResultFindFirstOfMore;
        auto                                                const & expected00717 = expectedFindFirstOfMore;
        auto                                                const & target00717 = more;

        result00717 = collection00717.findFirstOf ( target00717 );
        if (( ( result00717 != collection00717.cend() ) != expectedResult00717 )||( expectedResult00717 && expected00717 != * result00717 )) {
            pTestLib->logError( "'CTC-00717-FO-findFirstOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00717-FO-findFirstOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstOfMatchingAll-cpp-xx : CTC-00718-FO-findFirstOfMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00718 = underTest;
        ConstIterator                                               result00718;
        auto                                                        expectedResult00718 = expectedResultFindFirstOfAll;
        auto                                                const & expected00718 = expectedFindFirstOfAll;
        auto                                                const & target00718 = all;

        result00718 = collection00718.findFirstOf ( target00718 );
        if (( ( result00718 != collection00718.cend() ) != expectedResult00718 )||( expectedResult00718 && expected00718 != * result00718 )) {
            pTestLib->logError( "'CTC-00718-FO-findFirstOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00718-FO-findFirstOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstOfMatchingAllAndMore-cpp-xx : CTC-00719-FO-findFirstOfMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00719 = underTest;
        ConstIterator                                               result00719;
        auto                                                        expectedResult00719 = expectedResultFindFirstOfAllAndMore;
        auto                                                const & expected00719 = expectedFindFirstOfAllAndMore;
        auto                                                const & target00719 = allAndMore;

        result00719 = collection00719.findFirstOf ( target00719 );
        if (( ( result00719 != collection00719.cend() ) != expectedResult00719 )||( expectedResult00719 && expected00719 != * result00719 )) {
            pTestLib->logError( "'CTC-00719-FO-findFirstOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00719-FO-findFirstOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastOfMatchingNone-cpp-xx : CTC-00720-FO-findLastOfMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00720 = underTest;
        ConstIterator                                               result00720;
        auto                                                        expectedResult00720 = expectedResultFindLastOfNone;
        auto                                                const & expected00720 = expectedFindLastOfNone;
        auto                                                const & target00720 = none;

        result00720 = collection00720.findLastOf ( target00720 );
        if (( ( result00720 != collection00720.cend() ) != expectedResult00720 )||( expectedResult00720 && expected00720 != * result00720 )) {
            pTestLib->logError( "'CTC-00720-FO-findLastOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00720-FO-findLastOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastOfMatchingOne-cpp-xx : CTC-00721-FO-findLastOfMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00721 = underTest;
        ConstIterator                                               result00721;
        auto                                                        expectedResult00721 = expectedResultFindLastOfOne;
        auto                                                const & expected00721 = expectedFindLastOfOne;
        auto                                                const & target00721 = one;

        result00721 = collection00721.findLastOf ( target00721 );
        if (( ( result00721 != collection00721.cend() ) != expectedResult00721 )||( expectedResult00721 && expected00721 != * result00721 )) {
            pTestLib->logError( "'CTC-00721-FO-findLastOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00721-FO-findLastOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastOfMatchingMore-cpp-xx : CTC-00722-FO-findLastOfMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00722 = underTest;
        ConstIterator                                               result00722;
        auto                                                        expectedResult00722 = expectedResultFindLastOfMore;
        auto                                                const & expected00722 = expectedFindLastOfMore;
        auto                                                const & target00722 = more;

        result00722 = collection00722.findLastOf ( target00722 );
        if (( ( result00722 != collection00722.cend() ) != expectedResult00722 )||( expectedResult00722 && expected00722 != * result00722 )) {
            pTestLib->logError( "'CTC-00722-FO-findLastOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00722-FO-findLastOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastOfMatchingAll-cpp-xx : CTC-00723-FO-findLastOfMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00723 = underTest;
        ConstIterator                                               result00723;
        auto                                                        expectedResult00723 = expectedResultFindLastOfAll;
        auto                                                const & expected00723 = expectedFindLastOfAll;
        auto                                                const & target00723 = all;

        result00723 = collection00723.findLastOf ( target00723 );
        if (( ( result00723 != collection00723.cend() ) != expectedResult00723 )||( expectedResult00723 && expected00723 != * result00723 )) {
            pTestLib->logError( "'CTC-00723-FO-findLastOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00723-FO-findLastOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastOfMatchingAllAndMore-cpp-xx : CTC-00724-FO-findLastOfMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00724 = underTest;
        ConstIterator                                               result00724;
        auto                                                        expectedResult00724 = expectedResultFindLastOfAllAndMore;
        auto                                                const & expected00724 = expectedFindLastOfAllAndMore;
        auto                                                const & target00724 = allAndMore;

        result00724 = collection00724.findLastOf ( target00724 );
        if (( ( result00724 != collection00724.cend() ) != expectedResult00724 )||( expectedResult00724 && expected00724 != * result00724 )) {
            pTestLib->logError( "'CTC-00724-FO-findLastOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00724-FO-findLastOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfStoreInMatchingNone-cpp-xx : CTC-00725-FO-findAllOfStoreInMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00725 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00725;
        auto                                                        expectedSize00725 = expectedSizeFindAllOfNone;
        auto                                                const & expected00725 = expectedFindAllOfNone;
        auto                                                const & target00725 = none;

        (void) collection00725.findAllOf ( storeIn00725, target00725 );
        if (( storeIn00725.size() != expectedSize00725 )||( ! iteratorListEqualityCheckNoPred ( storeIn00725, expected00725 ) )) {
            pTestLib->logError( "'CTC-00725-FO-findAllOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00725-FO-findAllOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfStoreInMatchingOne-cpp-xx : CTC-00726-FO-findAllOfStoreInMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00726 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00726;
        auto                                                        expectedSize00726 = expectedSizeFindAllOfOne;
        auto                                                const & expected00726 = expectedFindAllOfOne;
        auto                                                const & target00726 = one;

        (void) collection00726.findAllOf ( storeIn00726, target00726 );
        if (( storeIn00726.size() != expectedSize00726 )||( ! iteratorListEqualityCheckNoPred ( storeIn00726, expected00726 ) )) {
            pTestLib->logError( "'CTC-00726-FO-findAllOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00726-FO-findAllOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfStoreInMatchingMore-cpp-xx : CTC-00727-FO-findAllOfStoreInMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00727 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00727;
        auto                                                        expectedSize00727 = expectedSizeFindAllOfMore;
        auto                                                const & expected00727 = expectedFindAllOfMore;
        auto                                                const & target00727 = more;

        (void) collection00727.findAllOf ( storeIn00727, target00727 );
        if (( storeIn00727.size() != expectedSize00727 )||( ! iteratorListEqualityCheckNoPred ( storeIn00727, expected00727 ) )) {
            pTestLib->logError( "'CTC-00727-FO-findAllOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00727-FO-findAllOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfStoreInMatchingAll-cpp-xx : CTC-00728-FO-findAllOfStoreInMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00728 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00728;
        auto                                                        expectedSize00728 = expectedSizeFindAllOfAll;
        auto                                                const & expected00728 = expectedFindAllOfAll;
        auto                                                const & target00728 = all;

        (void) collection00728.findAllOf ( storeIn00728, target00728 );
        if (( storeIn00728.size() != expectedSize00728 )||( ! iteratorListEqualityCheckNoPred ( storeIn00728, expected00728 ) )) {
            pTestLib->logError( "'CTC-00728-FO-findAllOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00728-FO-findAllOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfStoreInMatchingAllAndMore-cpp-xx : CTC-00729-FO-findAllOfStoreInMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00729 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00729;
        auto                                                        expectedSize00729 = expectedSizeFindAllOfAllAndMore;
        auto                                                const & expected00729 = expectedFindAllOfAllAndMore;
        auto                                                const & target00729 = allAndMore;

        (void) collection00729.findAllOf ( storeIn00729, target00729 );
        if (( storeIn00729.size() != expectedSize00729 )||( ! iteratorListEqualityCheckNoPred ( storeIn00729, expected00729 ) )) {
            pTestLib->logError( "'CTC-00729-FO-findAllOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00729-FO-findAllOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfReturnedMatchingNone-cpp-xx : CTC-00730-FO-findAllOfReturnedMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00730 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00730;
        auto                                                        expectedSize00730 = expectedSizeFindAllOfNone;
        auto                                                const & expected00730 = expectedFindAllOfNone;
        auto                                                const & target00730 = none;

        storeIn00730 = collection00730.template findAllOf < __ComparisonEquivalent > ( target00730 );
        if (( storeIn00730.size() != expectedSize00730 )||( ! iteratorListEqualityCheckNoPred ( storeIn00730, expected00730 ) )) {
            pTestLib->logError( "'CTC-00730-FO-findAllOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00730-FO-findAllOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfReturnedMatchingOne-cpp-xx : CTC-00731-FO-findAllOfReturnedMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00731 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00731;
        auto                                                        expectedSize00731 = expectedSizeFindAllOfOne;
        auto                                                const & expected00731 = expectedFindAllOfOne;
        auto                                                const & target00731 = one;

        storeIn00731 = collection00731.template findAllOf < __ComparisonEquivalent > ( target00731 );
        if (( storeIn00731.size() != expectedSize00731 )||( ! iteratorListEqualityCheckNoPred ( storeIn00731, expected00731 ) )) {
            pTestLib->logError( "'CTC-00731-FO-findAllOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00731-FO-findAllOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfReturnedMatchingMore-cpp-xx : CTC-00732-FO-findAllOfReturnedMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00732 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00732;
        auto                                                        expectedSize00732 = expectedSizeFindAllOfMore;
        auto                                                const & expected00732 = expectedFindAllOfMore;
        auto                                                const & target00732 = more;

        storeIn00732 = collection00732.template findAllOf < __ComparisonEquivalent > ( target00732 );
        if (( storeIn00732.size() != expectedSize00732 )||( ! iteratorListEqualityCheckNoPred ( storeIn00732, expected00732 ) )) {
            pTestLib->logError( "'CTC-00732-FO-findAllOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00732-FO-findAllOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfReturnedMatchingAll-cpp-xx : CTC-00733-FO-findAllOfReturnedMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00733 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00733;
        auto                                                        expectedSize00733 = expectedSizeFindAllOfAll;
        auto                                                const & expected00733 = expectedFindAllOfAll;
        auto                                                const & target00733 = all;

        storeIn00733 = collection00733.template findAllOf < __ComparisonEquivalent > ( target00733 );
        if (( storeIn00733.size() != expectedSize00733 )||( ! iteratorListEqualityCheckNoPred ( storeIn00733, expected00733 ) )) {
            pTestLib->logError( "'CTC-00733-FO-findAllOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00733-FO-findAllOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllOfReturnedMatchingAllAndMore-cpp-xx : CTC-00734-FO-findAllOfReturnedMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00734 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00734;
        auto                                                        expectedSize00734 = expectedSizeFindAllOfAllAndMore;
        auto                                                const & expected00734 = expectedFindAllOfAllAndMore;
        auto                                                const & target00734 = allAndMore;

        storeIn00734 = collection00734.template findAllOf < __ComparisonEquivalent > ( target00734 );
        if (( storeIn00734.size() != expectedSize00734 )||( ! iteratorListEqualityCheckNoPred ( storeIn00734, expected00734 ) )) {
            pTestLib->logError( "'CTC-00734-FO-findAllOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00734-FO-findAllOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfStoreInMatchingNone-cpp-xx : CTC-00735-FO-findNotOfStoreInMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00735 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00735;
        auto                                                        expectedSize00735 = expectedSizeFindNotOfNone;
        auto                                                const & expected00735 = expectedFindNotOfNone;
        auto                                                const & target00735 = none;

        (void) collection00735.findNotOf ( limit, storeIn00735, target00735 );
        if (( storeIn00735.size() != expectedSize00735 )||( ! iteratorListEqualityCheckNoPred ( storeIn00735, expected00735 ) )) {
            pTestLib->logError( "'CTC-00735-FO-findNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00735-FO-findNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfStoreInMatchingOne-cpp-xx : CTC-00736-FO-findNotOfStoreInMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00736 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00736;
        auto                                                        expectedSize00736 = expectedSizeFindNotOfOne;
        auto                                                const & expected00736 = expectedFindNotOfOne;
        auto                                                const & target00736 = one;

        (void) collection00736.findNotOf ( limit, storeIn00736, target00736 );
        if (( storeIn00736.size() != expectedSize00736 )||( ! iteratorListEqualityCheckNoPred ( storeIn00736, expected00736 ) )) {
            pTestLib->logError( "'CTC-00736-FO-findNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00736-FO-findNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfStoreInMatchingMoreLessThanLimit-cpp-xx : CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00737 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00737;
        auto                                                        expectedSize00737 = expectedSizeFindNotOfMoreLessThanLimit;
        auto                                                const & expected00737 = expectedFindNotOfMoreLessThanLimit;
        auto                                                const & target00737 = moreLessThanLimit;

        (void) collection00737.findNotOf ( limit, storeIn00737, target00737 );
        if (( storeIn00737.size() != expectedSize00737 )||( ! iteratorListEqualityCheckNoPred ( storeIn00737, expected00737 ) )) {
            pTestLib->logError( "'CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfStoreInMatchingMore-cpp-xx : CTC-00738-FO-findNotOfStoreInMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00738 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00738;
        auto                                                        expectedSize00738 = expectedSizeFindNotOfMore;
        auto                                                const & expected00738 = expectedFindNotOfMore;
        auto                                                const & target00738 = more;

        (void) collection00738.findNotOf ( limit, storeIn00738, target00738 );
        if (( storeIn00738.size() != expectedSize00738 )||( ! iteratorListEqualityCheckNoPred ( storeIn00738, expected00738 ) )) {
            pTestLib->logError( "'CTC-00738-FO-findNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00738-FO-findNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfStoreInMatchingMoreMoreThanLimit-cpp-xx : CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00739 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00739;
        auto                                                        expectedSize00739 = expectedSizeFindNotOfMoreMoreThanLimit;
        auto                                                const & expected00739 = expectedFindNotOfMoreMoreThanLimit;
        auto                                                const & target00739 = moreMoreThanLimit;

        (void) collection00739.findNotOf ( limit, storeIn00739, target00739 );
        if (( storeIn00739.size() != expectedSize00739 )||( ! iteratorListEqualityCheckNoPred ( storeIn00739, expected00739 ) )) {
            pTestLib->logError( "'CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfStoreInMatchingAll-cpp-xx : CTC-00740-FO-findNotOfStoreInMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00740 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00740;
        auto                                                        expectedSize00740 = expectedSizeFindNotOfAll;
        auto                                                const & expected00740 = expectedFindNotOfAll;
        auto                                                const & target00740 = all;

        (void) collection00740.findNotOf ( limit, storeIn00740, target00740 );
        if (( storeIn00740.size() != expectedSize00740 )||( ! iteratorListEqualityCheckNoPred ( storeIn00740, expected00740 ) )) {
            pTestLib->logError( "'CTC-00740-FO-findNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00740-FO-findNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfStoreInMatchingAllAndMore-cpp-xx : CTC-00741-FO-findNotOfStoreInMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00741 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00741;
        auto                                                        expectedSize00741 = expectedSizeFindNotOfAllAndMore;
        auto                                                const & expected00741 = expectedFindNotOfAllAndMore;
        auto                                                const & target00741 = allAndMore;

        (void) collection00741.findNotOf ( limit, storeIn00741, target00741 );
        if (( storeIn00741.size() != expectedSize00741 )||( ! iteratorListEqualityCheckNoPred ( storeIn00741, expected00741 ) )) {
            pTestLib->logError( "'CTC-00741-FO-findNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00741-FO-findNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfReturnedMatchingNone-cpp-xx : CTC-00742-FO-findNotOfReturnedMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00742 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00742;
        auto                                                        expectedSize00742 = expectedSizeFindNotOfNone;
        auto                                                const & expected00742 = expectedFindNotOfNone;
        auto                                                const & target00742 = none;

        storeIn00742 = collection00742.template findNotOf < __ComparisonEquivalent > ( limit, target00742 );
        if (( storeIn00742.size() != expectedSize00742 )||( ! iteratorListEqualityCheckNoPred ( storeIn00742, expected00742 ) )) {
            pTestLib->logError( "'CTC-00742-FO-findNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00742-FO-findNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfReturnedMatchingOne-cpp-xx : CTC-00743-FO-findNotOfReturnedMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00743 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00743;
        auto                                                        expectedSize00743 = expectedSizeFindNotOfOne;
        auto                                                const & expected00743 = expectedFindNotOfOne;
        auto                                                const & target00743 = one;

        storeIn00743 = collection00743.template findNotOf < __ComparisonEquivalent > ( limit, target00743 );
        if (( storeIn00743.size() != expectedSize00743 )||( ! iteratorListEqualityCheckNoPred ( storeIn00743, expected00743 ) )) {
            pTestLib->logError( "'CTC-00743-FO-findNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00743-FO-findNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfReturnedMatchingMoreLessThanLimit-cpp-xx : CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00744 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00744;
        auto                                                        expectedSize00744 = expectedSizeFindNotOfMoreLessThanLimit;
        auto                                                const & expected00744 = expectedFindNotOfMoreLessThanLimit;
        auto                                                const & target00744 = moreLessThanLimit;

        storeIn00744 = collection00744.template findNotOf < __ComparisonEquivalent > ( limit, target00744 );
        if (( storeIn00744.size() != expectedSize00744 )||( ! iteratorListEqualityCheckNoPred ( storeIn00744, expected00744 ) )) {
            pTestLib->logError( "'CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfReturnedMatchingMore-cpp-xx : CTC-00745-FO-findNotOfReturnedMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00745 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00745;
        auto                                                        expectedSize00745 = expectedSizeFindNotOfMore;
        auto                                                const & expected00745 = expectedFindNotOfMore;
        auto                                                const & target00745 = more;

        storeIn00745 = collection00745.template findNotOf < __ComparisonEquivalent > ( limit, target00745 );
        if (( storeIn00745.size() != expectedSize00745 )||( ! iteratorListEqualityCheckNoPred ( storeIn00745, expected00745 ) )) {
            pTestLib->logError( "'CTC-00745-FO-findNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00745-FO-findNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfReturnedMatchingMoreMoreThanLimit-cpp-xx : CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-cpp-xx */
        cds :: Collection < __ElementType > const & collection00746 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00746;
        auto                                                        expectedSize00746 = expectedSizeFindNotOfMoreMoreThanLimit;
        auto                                                const & expected00746 = expectedFindNotOfMoreMoreThanLimit;
        auto                                                const & target00746 = moreMoreThanLimit;

        storeIn00746 = collection00746.template findNotOf < __ComparisonEquivalent > ( limit, target00746 );
        if (( storeIn00746.size() != expectedSize00746 )||( ! iteratorListEqualityCheckNoPred ( storeIn00746, expected00746 ) )) {
            pTestLib->logError( "'CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfReturnedMatchingAll-cpp-xx : CTC-00747-FO-findNotOfReturnedMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00747 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00747;
        auto                                                        expectedSize00747 = expectedSizeFindNotOfAll;
        auto                                                const & expected00747 = expectedFindNotOfAll;
        auto                                                const & target00747 = all;

        storeIn00747 = collection00747.template findNotOf < __ComparisonEquivalent > ( limit, target00747 );
        if (( storeIn00747.size() != expectedSize00747 )||( ! iteratorListEqualityCheckNoPred ( storeIn00747, expected00747 ) )) {
            pTestLib->logError( "'CTC-00747-FO-findNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00747-FO-findNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findNotOfReturnedMatchingAllAndMore-cpp-xx : CTC-00748-FO-findNotOfReturnedMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00748 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00748;
        auto                                                        expectedSize00748 = expectedSizeFindNotOfAllAndMore;
        auto                                                const & expected00748 = expectedFindNotOfAllAndMore;
        auto                                                const & target00748 = allAndMore;

        storeIn00748 = collection00748.template findNotOf < __ComparisonEquivalent > ( limit, target00748 );
        if (( storeIn00748.size() != expectedSize00748 )||( ! iteratorListEqualityCheckNoPred ( storeIn00748, expected00748 ) )) {
            pTestLib->logError( "'CTC-00748-FO-findNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00748-FO-findNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstNotOfMatchingNone-cpp-xx : CTC-00749-FO-findFirstNotOfMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00749 = underTest;
        ConstIterator                                               result00749;
        auto                                                        expectedResult00749 = expectedResultFindFirstNotOfNone;
        auto                                                const & expected00749 = expectedFindFirstNotOfNone;
        auto                                                const & target00749 = none;

        result00749 = collection00749.findFirstNotOf ( target00749 );
        if (( ( result00749 != collection00749.cend() ) != expectedResult00749 )||( expectedResult00749 && expected00749 != * result00749 )) {
            pTestLib->logError( "'CTC-00749-FO-findFirstNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00749-FO-findFirstNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstNotOfMatchingOne-cpp-xx : CTC-00750-FO-findFirstNotOfMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00750 = underTest;
        ConstIterator                                               result00750;
        auto                                                        expectedResult00750 = expectedResultFindFirstNotOfOne;
        auto                                                const & expected00750 = expectedFindFirstNotOfOne;
        auto                                                const & target00750 = one;

        result00750 = collection00750.findFirstNotOf ( target00750 );
        if (( ( result00750 != collection00750.cend() ) != expectedResult00750 )||( expectedResult00750 && expected00750 != * result00750 )) {
            pTestLib->logError( "'CTC-00750-FO-findFirstNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00750-FO-findFirstNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstNotOfMatchingMore-cpp-xx : CTC-00751-FO-findFirstNotOfMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00751 = underTest;
        ConstIterator                                               result00751;
        auto                                                        expectedResult00751 = expectedResultFindFirstNotOfMore;
        auto                                                const & expected00751 = expectedFindFirstNotOfMore;
        auto                                                const & target00751 = more;

        result00751 = collection00751.findFirstNotOf ( target00751 );
        if (( ( result00751 != collection00751.cend() ) != expectedResult00751 )||( expectedResult00751 && expected00751 != * result00751 )) {
            pTestLib->logError( "'CTC-00751-FO-findFirstNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00751-FO-findFirstNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstNotOfMatchingAll-cpp-xx : CTC-00752-FO-findFirstNotOfMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00752 = underTest;
        ConstIterator                                               result00752;
        auto                                                        expectedResult00752 = expectedResultFindFirstNotOfAll;
        auto                                                const & expected00752 = expectedFindFirstNotOfAll;
        auto                                                const & target00752 = all;

        result00752 = collection00752.findFirstNotOf ( target00752 );
        if (( ( result00752 != collection00752.cend() ) != expectedResult00752 )||( expectedResult00752 && expected00752 != * result00752 )) {
            pTestLib->logError( "'CTC-00752-FO-findFirstNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00752-FO-findFirstNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findFirstNotOfMatchingAllAndMore-cpp-xx : CTC-00753-FO-findFirstNotOfMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00753 = underTest;
        ConstIterator                                               result00753;
        auto                                                        expectedResult00753 = expectedResultFindFirstNotOfAllAndMore;
        auto                                                const & expected00753 = expectedFindFirstNotOfAllAndMore;
        auto                                                const & target00753 = allAndMore;

        result00753 = collection00753.findFirstNotOf ( target00753 );
        if (( ( result00753 != collection00753.cend() ) != expectedResult00753 )||( expectedResult00753 && expected00753 != * result00753 )) {
            pTestLib->logError( "'CTC-00753-FO-findFirstNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00753-FO-findFirstNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastNotOfMatchingNone-cpp-xx : CTC-00754-FO-findLastNotOfMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00754 = underTest;
        ConstIterator                                               result00754;
        auto                                                        expectedResult00754 = expectedResultFindLastNotOfNone;
        auto                                                const & expected00754 = expectedFindLastNotOfNone;
        auto                                                const & target00754 = none;

        result00754 = collection00754.findLastNotOf ( target00754 );
        if (( ( result00754 != collection00754.cend() ) != expectedResult00754 )||( expectedResult00754 && expected00754 != * result00754 )) {
            pTestLib->logError( "'CTC-00754-FO-findLastNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00754-FO-findLastNotOfMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastNotOfMatchingOne-cpp-xx : CTC-00755-FO-findLastNotOfMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00755 = underTest;
        ConstIterator                                               result00755;
        auto                                                        expectedResult00755 = expectedResultFindLastNotOfOne;
        auto                                                const & expected00755 = expectedFindLastNotOfOne;
        auto                                                const & target00755 = one;

        result00755 = collection00755.findLastNotOf ( target00755 );
        if (( ( result00755 != collection00755.cend() ) != expectedResult00755 )||( expectedResult00755 && expected00755 != * result00755 )) {
            pTestLib->logError( "'CTC-00755-FO-findLastNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00755-FO-findLastNotOfMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastNotOfMatchingMore-cpp-xx : CTC-00756-FO-findLastNotOfMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00756 = underTest;
        ConstIterator                                               result00756;
        auto                                                        expectedResult00756 = expectedResultFindLastNotOfMore;
        auto                                                const & expected00756 = expectedFindLastNotOfMore;
        auto                                                const & target00756 = more;

        result00756 = collection00756.findLastNotOf ( target00756 );
        if (( ( result00756 != collection00756.cend() ) != expectedResult00756 )||( expectedResult00756 && expected00756 != * result00756 )) {
            pTestLib->logError( "'CTC-00756-FO-findLastNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00756-FO-findLastNotOfMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastNotOfMatchingAll-cpp-xx : CTC-00757-FO-findLastNotOfMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00757 = underTest;
        ConstIterator                                               result00757;
        auto                                                        expectedResult00757 = expectedResultFindLastNotOfAll;
        auto                                                const & expected00757 = expectedFindLastNotOfAll;
        auto                                                const & target00757 = all;

        result00757 = collection00757.findLastNotOf ( target00757 );
        if (( ( result00757 != collection00757.cend() ) != expectedResult00757 )||( expectedResult00757 && expected00757 != * result00757 )) {
            pTestLib->logError( "'CTC-00757-FO-findLastNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00757-FO-findLastNotOfMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findLastOfMatchingAllAndMore-cpp-xx : CTC-00758-FO-findLastNotOfMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00758 = underTest;
        ConstIterator                                               result00758;
        auto                                                        expectedResult00758 = expectedResultFindLastNotOfAllAndMore;
        auto                                                const & expected00758 = expectedFindLastNotOfAllAndMore;
        auto                                                const & target00758 = allAndMore;

        result00758 = collection00758.findLastNotOf ( target00758 );
        if (( ( result00758 != collection00758.cend() ) != expectedResult00758 )||( expectedResult00758 && expected00758 != * result00758 )) {
            pTestLib->logError( "'CTC-00758-FO-findLastNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00758-FO-findLastNotOfMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingNone-cpp-xx : CTC-00759-FO-findAllNotOfStoreInMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00759 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00759;
        auto                                                        expectedSize00759 = expectedSizeFindAllNotOfNone;
        auto                                                const & expected00759 = expectedFindAllNotOfNone;
        auto                                                const & target00759 = none;

        (void) collection00759.findAllNotOf ( storeIn00759, target00759 );
        if (( storeIn00759.size() != expectedSize00759 )||( ! iteratorListEqualityCheckNoPred ( storeIn00759, expected00759 ) )) {
            pTestLib->logError( "'CTC-00759-FO-findAllNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00759-FO-findAllNotOfStoreInMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingOne-cpp-xx : CTC-00760-FO-findAllNotOfStoreInMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00760 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00760;
        auto                                                        expectedSize00760 = expectedSizeFindAllNotOfOne;
        auto                                                const & expected00760 = expectedFindAllNotOfOne;
        auto                                                const & target00760 = one;

        (void) collection00760.findAllNotOf ( storeIn00760, target00760 );
        if (( storeIn00760.size() != expectedSize00760 )||( ! iteratorListEqualityCheckNoPred ( storeIn00760, expected00760 ) )) {
            pTestLib->logError( "'CTC-00760-FO-findAllNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00760-FO-findAllNotOfStoreInMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingMore-cpp-xx : CTC-00761-FO-findAllNotOfStoreInMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00761 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00761;
        auto                                                        expectedSize00761 = expectedSizeFindAllNotOfMore;
        auto                                                const & expected00761 = expectedFindAllNotOfMore;
        auto                                                const & target00761 = more;

        (void) collection00761.findAllNotOf ( storeIn00761, target00761 );
        if (( storeIn00761.size() != expectedSize00761 )||( ! iteratorListEqualityCheckNoPred ( storeIn00761, expected00761 ) )) {
            pTestLib->logError( "'CTC-00761-FO-findAllNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00761-FO-findAllNotOfStoreInMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingAll-cpp-xx : CTC-00762-FO-findAllNotOfStoreInMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00762 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00762;
        auto                                                        expectedSize00762 = expectedSizeFindAllNotOfAll;
        auto                                                const & expected00762 = expectedFindAllNotOfAll;
        auto                                                const & target00762 = all;

        (void) collection00762.findAllNotOf ( storeIn00762, target00762 );
        if (( storeIn00762.size() != expectedSize00762 )||( ! iteratorListEqualityCheckNoPred ( storeIn00762, expected00762 ) )) {
            pTestLib->logError( "'CTC-00762-FO-findAllNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00762-FO-findAllNotOfStoreInMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfStoreInMatchingAllAndMore-cpp-xx : CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00763 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00763;
        auto                                                        expectedSize00763 = expectedSizeFindAllNotOfAllAndMore;
        auto                                                const & expected00763 = expectedFindAllNotOfAllAndMore;
        auto                                                const & target00763 = allAndMore;

        (void) collection00763.findAllNotOf ( storeIn00763, target00763 );
        if (( storeIn00763.size() != expectedSize00763 )||( ! iteratorListEqualityCheckNoPred ( storeIn00763, expected00763 ) )) {
            pTestLib->logError( "'CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingNone-cpp-xx : CTC-00764-FO-findAllNotOfReturnedMatchingNone-cpp-xx */
        cds :: Collection < __ElementType > const & collection00764 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00764;
        auto                                                        expectedSize00764 = expectedSizeFindAllNotOfNone;
        auto                                                const & expected00764 = expectedFindAllNotOfNone;
        auto                                                const & target00764 = none;

        storeIn00764 = collection00764.template findAllNotOf < __ComparisonEquivalent > ( target00764 );
        if (( storeIn00764.size() != expectedSize00764 )||( ! iteratorListEqualityCheckNoPred ( storeIn00764, expected00764 ) )) {
            pTestLib->logError( "'CTC-00764-FO-findAllNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00764-FO-findAllNotOfReturnedMatchingNone-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingOne-cpp-xx : CTC-00765-FO-findAllNotOfReturnedMatchingOne-cpp-xx */
        cds :: Collection < __ElementType > const & collection00765 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00765;
        auto                                                        expectedSize00765 = expectedSizeFindAllNotOfOne;
        auto                                                const & expected00765 = expectedFindAllNotOfOne;
        auto                                                const & target00765 = one;

        storeIn00765 = collection00765.template findAllNotOf < __ComparisonEquivalent > ( target00765 );
        if (( storeIn00765.size() != expectedSize00765 )||( ! iteratorListEqualityCheckNoPred ( storeIn00765, expected00765 ) )) {
            pTestLib->logError( "'CTC-00765-FO-findAllNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00765-FO-findAllNotOfReturnedMatchingOne-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingMore-cpp-xx : CTC-00766-FO-findAllNotOfReturnedMatchingMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00766 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00766;
        auto                                                        expectedSize00766 = expectedSizeFindAllNotOfMore;
        auto                                                const & expected00766 = expectedFindAllNotOfMore;
        auto                                                const & target00766 = more;

        storeIn00766 = collection00766.template findAllNotOf < __ComparisonEquivalent > ( target00766 );
        if (( storeIn00766.size() != expectedSize00766 )||( ! iteratorListEqualityCheckNoPred ( storeIn00766, expected00766 ) )) {
            pTestLib->logError( "'CTC-00766-FO-findAllNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00766-FO-findAllNotOfReturnedMatchingMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingAll-cpp-xx : CTC-00767-FO-findAllNotOfReturnedMatchingAll-cpp-xx */
        cds :: Collection < __ElementType > const & collection00767 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00767;
        auto                                                        expectedSize00767 = expectedSizeFindAllNotOfAll;
        auto                                                const & expected00767 = expectedFindAllNotOfAll;
        auto                                                const & target00767 = all;

        storeIn00767 = collection00767.template findAllNotOf < __ComparisonEquivalent > ( target00767 );
        if (( storeIn00767.size() != expectedSize00767 )||( ! iteratorListEqualityCheckNoPred ( storeIn00767, expected00767 ) )) {
            pTestLib->logError( "'CTC-00767-FO-findAllNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00767-FO-findAllNotOfReturnedMatchingAll-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        /* CollectionTestCase-FindOf-findAllNotOfReturnedMatchingAllAndMore-cpp-xx : CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-cpp-xx */
        cds :: Collection < __ElementType > const & collection00768 = underTest;
        __ComparisonEquivalent < ConstIterator >                    storeIn00768;
        auto                                                        expectedSize00768 = expectedSizeFindAllNotOfAllAndMore;
        auto                                                const & expected00768 = expectedFindAllNotOfAllAndMore;
        auto                                                const & target00768 = allAndMore;

        storeIn00768 = collection00768.template findAllNotOf < __ComparisonEquivalent > ( target00768 );
        if (( storeIn00768.size() != expectedSize00768 )||( ! iteratorListEqualityCheckNoPred ( storeIn00768, expected00768 ) )) {
            pTestLib->logError( "'CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' failed", variant );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore-%s-" __CDS_cpplang_core_version_name "' OK", variant );
        }

        return true;
    }
}

#endif /* COLLECTION_TEST_700_COMMON_H */
