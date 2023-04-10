#include "MutableCollectionTest.h"
#include "MutableCollectionTest_common.hpp"
#include <initializer_list>
#include <CDS/Tuple>

namespace {

    template <typename E, typename I>
    using RemovePfn = Size (cds::MutableCollection <E> :: *) (Size, I const &);

    template <typename E, typename I>
    using RemoveOnePfn = bool (cds::MutableCollection <E> :: *) (I const &);

    /* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTG-00450-RO-cpp-xx. MCTC-00451-RO to MCTC-00464-RO */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupItemRemoveOfFirstHalf (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemovePfn <__ElementType, __OtherIterableType> removePfnVariant,
            Size                        limit,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <Size> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        auto pTestLib = tData.template get <0> ();
        auto const & groupVariant = tData.template get <1> ();
        auto subvariant = tData.template get <2> ();
        auto subvariantOffset = tData.template get <3> ();

        auto casesIt = cases.begin();
        auto const & noneCommon = ** casesIt; 
        ++ casesIt;
        auto const & oneCommon = ** casesIt; 
        ++ casesIt;
        auto const & moreLessThanLimitCommon = ** casesIt; 
        ++ casesIt;
        auto const & moreCommon = ** casesIt;

        auto statusesIt = statuses.begin();
        auto const expectedResultFromNone = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromOne = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromMoreLessThanLimit = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromMore = * statusesIt;

        auto resultsIt = results.begin();
        auto const & expectedCollectionFromNone = ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromOne= ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromMoreLessThanLimit = ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromMore = ** resultsIt;


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

        return true;
    }
    
    /* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTG-00450-RO-cpp-xx. MCTC-00451-RO to MCTC-00464-RO */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupItemRemoveOfLastHalf (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemovePfn <__ElementType, __OtherIterableType> removePfnVariant,
            Size                        limit,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <Size> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        auto pTestLib = tData.template get <0> ();
        auto const & groupVariant = tData.template get <1> ();
        auto subvariant = tData.template get <2> ();
        auto subvariantOffset = tData.template get <3> ();

        auto casesIt = cases.begin();
        ++ casesIt;
        ++ casesIt;
        ++ casesIt;
        ++ casesIt;
        auto const & moreMoreThanLimitCommon = ** casesIt; 
        ++ casesIt;
        auto const & allCommon = ** casesIt; 
        ++ casesIt;
        auto const & allAndMoreCommon = ** casesIt;

        auto statusesIt = statuses.begin();
        ++ statusesIt;
        ++ statusesIt;
        ++ statusesIt;
        ++ statusesIt;
        auto const expectedResultFromMoreMoreThanLimit = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromAll = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromAllAndMore = * statusesIt;

        auto resultsIt = results.begin();
        ++ resultsIt;
        ++ resultsIt;
        ++ resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromMoreMoreThanLimit = ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromAll = ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromAllAndMore = ** resultsIt;

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
    
    /* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTG-00450-RO-cpp-xx. MCTC-00451-RO to MCTC-00464-RO */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupItemRemoveOf (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemovePfn <__ElementType, __OtherIterableType> removePfnVariant,
            Size                        limit,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <Size> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        return
                mutableCollectionTestGroupItemRemoveOfFirstHalf (
                        tData, iterableUnderTest, removePfnVariant, limit,
                        cases, statuses, results
                ) && mutableCollectionTestGroupItemRemoveOfLastHalf (
                        tData, iterableUnderTest, removePfnVariant, limit,
                        cases, statuses, results
                );
    }

    /* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTG-00450-RO-cpp-xx. MMCTC-00501-RO to MMCTC-00520-RO. */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupItemRemoveFirstLastOf (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemoveOnePfn <__ElementType, __OtherIterableType> removeFirstLastPfnVariant,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <bool> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        auto pTestLib = tData.template get <0> ();
        auto const & groupVariant = tData.template get <1> ();
        auto subvariant = tData.template get <2> ();
        auto subvariantOffset = tData.template get <3> ();

        auto casesIt = cases.begin();
        auto const & noneCommon = ** casesIt; 
        ++ casesIt;
        auto const & oneCommon = ** casesIt; 
        ++ casesIt;
        auto const & moreCommon = ** casesIt; 
        ++ casesIt;
        auto const & allCommon = ** casesIt;
        ++ casesIt;
        auto const & allAndMoreCommon = ** casesIt;

        auto statusesIt = statuses.begin();
        auto const expectedResultFromNone = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromOne = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromMore = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromAll = * statusesIt;
        ++ statusesIt;
        auto const expectedResultFromAllAndMore = * statusesIt;

        auto resultsIt = results.begin();
        auto const & expectedCollectionFromNone = ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromOne= ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromMore = ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromAll = ** resultsIt;
        ++ resultsIt;
        auto const & expectedCollectionFromAllAndMore = ** resultsIt;

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
}


auto MutableCollectionTest::tests_00450_00499 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_a <int> (10, 11, 12, 13);
        auto const c2 = make_a <int> (16, 6, 11, 12, 13);
        auto const c3 = make_a <int> (20, 123, 5, 1230, 435, 3, 1235, 9534);
        auto const c4 = make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c5 = make_a <int> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const r1 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r2 = make_a <int> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const r3 = make_a <int> (1, 2, 4, 6, 7, 8, 9 );
        auto const r4 = make_a <int> (1, 2, 4, 6, 8, 9 );
        auto const r5 = make_a <int> (1, 4, 6, 7, 8, 9 );
        auto const r6 = make_a <int> (4, 5, 6, 7, 8, 9 );
        auto const r7 = make_a <int> (4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make_a <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make_a <int> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make_a <int> (),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <int> ()
        );

        auto const rf1 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf2 = make_a <int> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rf3 = make_a <int> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rf4 = make_a <int> (2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf5 = make_a <int> (2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rl1 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rl2 = make_a <int> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rl3 = make_a <int> (1, 2, 3, 4, 5, 6, 8, 9 );
        auto const rl4 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl5 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const r8 = make_a <int>  (4, 5, 6, 7, 8, 9 );
        auto const r9 = make_a <int>  (4, 5, 6, 7, 8, 9 );
        auto const r10 = make_a <int> (3, 5, 6, 7, 8, 9 );
        auto const r11 = make_a <int> (3, 5, 6, 7, 8, 9 );
        auto const r12 = make_a <int> (2, 3, 5, 7, 8, 9 );
        auto const r13 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r14 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        7
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeNotOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make_a <int> (),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make_a <int> (6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make_a <int> (3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make_a <int> (1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        auto const rf6 = make_a <int> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf7 = make_a <int> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf8 = make_a <int> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf9 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf10 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );

        auto const rl6 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl7 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl8 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl9 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rl10 = make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );

        std::initializer_list <int> const c8  = {10, 11, 12, 13};
        std::initializer_list <int> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <int> const c10 = {20, 123, 5, 1230, 435, 3, 1235, 9534};
        std::initializer_list <int> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <int> const c12 = {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <int> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <int> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <int> const r15 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r16 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <int> const r17 = {1, 2, 4, 6, 7, 8, 9 };
        std::initializer_list <int> const r18 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <int> const r19 = {1, 4, 6, 7, 8, 9 };
        std::initializer_list <int> const r20 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r21 = {4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        {},
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ {}
        );

        std::initializer_list <int> const rf11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rf12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <int> const rf13 = {1, 2, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rf14 = {2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rf15 = {2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <int> const rl11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rl12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <int> const rl13 = {1, 2, 3, 4, 5, 6, 8, 9 };
        std::initializer_list <int> const rl14 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <int> const rl15 = {1, 2, 3, 4, 5, 6, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <int> const r22 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r23 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r24 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r25 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r26 = {2, 3, 5, 7, 8, 9 };
        std::initializer_list <int> const r27 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r28 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        7U
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeNotOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       {},
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        {6 },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       {3, 5, 7 },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        {1 ,2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );

        std::initializer_list <int> const rf16 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf17 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf18 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );

        std::initializer_list <int> const rl16 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <int> const rl17 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <int> const rl18 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <int> const rl19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rl20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        
        auto const c1 = make_ll <int> (10, 11, 12, 13);
        auto const c2 = make_ll <int> (16, 6, 11, 12, 13);
        auto const c3 = make_ll <int> (20, 123, 5, 1230, 435, 3, 1235, 9534);
        auto const c4 = make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c5 = make_ll <int> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const r1 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r2 = make_ll <int> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const r3 = make_ll <int> (1, 2, 4, 6, 7, 8, 9 );
        auto const r4 = make_ll <int> (1, 2, 4, 6, 8, 9 );
        auto const r5 = make_ll <int> (1, 4, 6, 7, 8, 9 );
        auto const r6 = make_ll <int> (4, 5, 6, 7, 8, 9 );
        auto const r7 = make_ll <int> (4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make_ll <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make_ll <int> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make_ll <int> (),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <int> ()
        );

        auto const rf1 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf2 = make_ll <int> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rf3 = make_ll <int> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rf4 = make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf5 = make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rl1 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rl2 = make_ll <int> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rl3 = make_ll <int> (1, 2, 3, 4, 5, 6, 8, 9 );
        auto const rl4 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl5 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const r8  = make_ll <int>  (4, 5, 6, 7, 8, 9 );
        auto const r9  = make_ll <int>  (4, 5, 6, 7, 8, 9 );
        auto const r10 = make_ll <int> (3, 5, 6, 7, 8, 9 );
        auto const r11 = make_ll <int> (3, 5, 6, 7, 8, 9 );
        auto const r12 = make_ll <int> (2, 3, 5, 7, 8, 9 );
        auto const r13 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r14 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        7
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeNotOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make_ll <int> (),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make_ll <int> (6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make_ll <int> (3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make_ll <int> (1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        auto const rf6 = make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf7 = make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf8 = make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf9 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf10 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );

        auto const rl6 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl7 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl8 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl9 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rl10 = make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );

        std::initializer_list <int> const c8  = {10, 11, 12, 13};
        std::initializer_list <int> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <int> const c10 = {20, 123, 5, 1230, 435, 3, 1235, 9534};
        std::initializer_list <int> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <int> const c12 = {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <int> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <int> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <int> const r15 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r16 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <int> const r17 = {1, 2, 4, 6, 7, 8, 9 };
        std::initializer_list <int> const r18 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <int> const r19 = {1, 4, 6, 7, 8, 9 };
        std::initializer_list <int> const r20 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r21 = {4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        {},
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ {}
        );

        std::initializer_list <int> const rf11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rf12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <int> const rf13 = {1, 2, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rf14 = {2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rf15 = {2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <int> const rl11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const rl12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <int> const rl13 = {1, 2, 3, 4, 5, 6, 8, 9 };
        std::initializer_list <int> const rl14 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <int> const rl15 = {1, 2, 3, 4, 5, 6, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <int> const r22 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r23 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r24 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r25 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r26 = {2, 3, 5, 7, 8, 9 };
        std::initializer_list <int> const r27 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <int> const r28 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        7
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeNotOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < int > :: removeAllNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       {},
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        {6 },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       {3, 5, 7 },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        {1 ,2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );

        std::initializer_list <int> const rf16 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf17 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf18 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rf20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );

        std::initializer_list <int> const rl16 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <int> const rl17 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <int> const rl18 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <int> const rl19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <int> const rl20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < int >, decltype (underTest), int > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < int > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        
        auto const c1 = cds::HashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::HashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c3 = cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        auto const c4 = cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c5 = cds::HashMap <int, int> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::HashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::HashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const r1 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r2 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const r3 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r4 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        auto const r5 = cds::HashMap <int, int> {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r6 = cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r7 = cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllOf,
                /* noneCommon= */                       cds::HashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <int, int> (),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <int, int> ()
        );

        auto const rf1 = cds::HashMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf2 = cds::HashMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf3 = cds::HashMap <int, int>  {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf4 = cds::HashMap <int, int>  {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf5 = cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable <MapEntry <int, int>>, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rl1 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl2 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl3 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} };
        auto const rl4 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        auto const rl5 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );
        
        auto const r8 = cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r9 = cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r10 = cds::HashMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r11 = cds::HashMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r12 = cds::HashMap <int, int> {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const r13 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r14 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        7
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeNotOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllNotOf,
                /* noneCommon= */                       cds::HashMap <int, int>  {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <int, int>  {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <int, int>  {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <int, int>  {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <int, int>  {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <int, int> (),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <int, int>  {{6, 6} },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <int, int>  {{3, 3}, {5, 5}, {7, 7} },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <int, int>  {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );

        auto const rf6 = cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf7 = cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf8 = cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf9 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf10 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );

        auto const rl6 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        auto const rl7 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        auto const rl8 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        auto const rl9 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rl10 = cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c10 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c12 = {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const r15 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r16 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r17 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r18 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r19 = {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r20 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r21 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        {},
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ {}
        );

        std::initializer_list <MapEntry <int, int>> const rf11 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf12 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf13 =  {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf14 =  {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf15 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list <MapEntry <int, int>>, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <MapEntry <int, int>> const rl11 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl12 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl13 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl14 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        std::initializer_list <MapEntry <int, int>> const rl15 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <MapEntry <int, int>> const r22 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r23 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r24 = {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r25 = {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r26 = {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r27 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r28 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        7
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeNotOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < int, int > > :: removeAllNotOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       {},
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        {{6, 6} },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       {{3, 3}, {5, 5}, {7, 7} },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );

        std::initializer_list <MapEntry <int, int>> const rf16 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf17 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf18 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf19 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf20 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );

        std::initializer_list <MapEntry <int, int>> const rl16 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        std::initializer_list <MapEntry <int, int>> const rl17 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        std::initializer_list <MapEntry <int, int>> const rl18 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        std::initializer_list <MapEntry <int, int>> const rl19 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rl20 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_a <String> (10, 11, 12, 13);
        auto const c2 = make_a <String> (16, 6, 11, 12, 13);
        auto const c3 = make_a <String> (20, 123, 5, 1230, 435, 3, 1235, 9534);
        auto const c4 = make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c5 = make_a <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const r1 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r2 = make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const r3 = make_a <String> (1, 2, 4, 6, 7, 8, 9 );
        auto const r4 = make_a <String> (1, 2, 4, 6, 8, 9 );
        auto const r5 = make_a <String> (1, 4, 6, 7, 8, 9 );
        auto const r6 = make_a <String> (4, 5, 6, 7, 8, 9 );
        auto const r7 = make_a <String> (4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make_a <String> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make_a <String> (),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <String> ()
        );

        auto const rf1 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf2 = make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rf3 = make_a <String> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rf4 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf5 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rl1 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rl2 = make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rl3 = make_a <String> (1, 2, 3, 4, 5, 6, 8, 9 );
        auto const rl4 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl5 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const r8 = make_a <String>  (4, 5, 6, 7, 8, 9 );
        auto const r9 = make_a <String>  (4, 5, 6, 7, 8, 9 );
        auto const r10 = make_a <String> (3, 5, 6, 7, 8, 9 );
        auto const r11 = make_a <String> (3, 5, 6, 7, 8, 9 );
        auto const r12 = make_a <String> (2, 3, 5, 7, 8, 9 );
        auto const r13 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r14 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        7U
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make_a <String> (),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make_a <String> (6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make_a <String> (3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make_a <String> (1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        auto const rf6 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf7 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf8 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf9 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf10 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );

        auto const rl6 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl7 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl8 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl9 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rl10 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c10 = {20, 123, 5, 1230, 435, 3, 1235, 9534};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c12 = {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const r15 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r16 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const r17 = {1, 2, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r18 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <String> const r19 = {1, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r20 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r21 = {4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        {},
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ {}
        );

        std::initializer_list <String> const rf11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rf13 = {1, 2, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf14 = {2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf15 = {2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <String> const rl11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rl12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rl13 = {1, 2, 3, 4, 5, 6, 8, 9 };
        std::initializer_list <String> const rl14 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl15 = {1, 2, 3, 4, 5, 6, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <String> const r22 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r23 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r24 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r25 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r26 = {2, 3, 5, 7, 8, 9 };
        std::initializer_list <String> const r27 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r28 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        7U
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       { 10, 11, 12, 13},
                /* oneCommon= */                        { 16, 6, 11, 12, 13},
                /* moreCommon= */                       { 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        { 9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 { 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       {},
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        { 6 },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       { 3, 5, 7 },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        { 1 ,2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );

        std::initializer_list <String> const rf16 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf17 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf18 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );

        std::initializer_list <String> const rl16 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl17 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl18 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rl20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_ll <String> (10, 11, 12, 13);
        auto const c2 = make_ll <String> (16, 6, 11, 12, 13);
        auto const c3 = make_ll <String> (20, 123, 5, 1230, 435, 3, 1235, 9534);
        auto const c4 = make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c5 = make_ll <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const r1 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r2 = make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const r3 = make_ll <String> (1, 2, 4, 6, 7, 8, 9 );
        auto const r4 = make_ll <String> (1, 2, 4, 6, 8, 9 );
        auto const r5 = make_ll <String> (1, 4, 6, 7, 8, 9 );
        auto const r6 = make_ll <String> (4, 5, 6, 7, 8, 9 );
        auto const r7 = make_ll <String> (4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       make_ll <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       make_ll <String> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        make_ll <String> (),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <String> ()
        );

        auto const rf1 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf2 = make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rf3 = make_ll <String> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rf4 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf5 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rl1 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rl2 = make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rl3 = make_ll <String> (1, 2, 3, 4, 5, 6, 8, 9 );
        auto const rl4 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl5 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const r8 = make_ll <String>  (4, 5, 6, 7, 8, 9 );
        auto const r9 = make_ll <String>  (4, 5, 6, 7, 8, 9 );
        auto const r10 = make_ll <String> (3, 5, 6, 7, 8, 9 );
        auto const r11 = make_ll <String> (3, 5, 6, 7, 8, 9 );
        auto const r12 = make_ll <String> (2, 3, 5, 7, 8, 9 );
        auto const r13 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r14 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        7U
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       make_ll <String>( 10, 11, 12, 13),
                /* oneCommon= */                        make_ll <String>( 16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <String>( 20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <String>( 9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <String>( 91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       make_ll <String> (),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        make_ll <String>( 6 ),
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       make_ll <String>( 3, 5, 7 ),
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        make_ll <String>( 1 ,2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <String>( 1, 2, 3, 4, 5, 6, 7, 8, 9 )
        );

        auto const rf6 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf7 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf8 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf9 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf10 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );

        auto const rl6 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl7 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl8 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl9 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rl10 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c10 = {20, 123, 5, 1230, 435, 3, 1235, 9534};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c12 = {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const r15 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r16 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const r17 = {1, 2, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r18 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <String> const r19 = {1, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r20 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r21 = {4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        {},
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ {}
        );

        std::initializer_list <String> const rf11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rf13 = {1, 2, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf14 = {2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf15 = {2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <String> const rl11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rl12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rl13 = {1, 2, 3, 4, 5, 6, 8, 9 };
        std::initializer_list <String> const rl14 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl15 = {1, 2, 3, 4, 5, 6, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <String> const r22 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r23 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r24 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r25 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r26 = {2, 3, 5, 7, 8, 9 };
        std::initializer_list <String> const r27 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r28 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        7U
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < String > :: removeAllNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       {},
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        {6 },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       {3, 5, 7 },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        {1 ,2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9 }
        );

        std::initializer_list <String> const rf16 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf17 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf18 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );

        std::initializer_list <String> const rl16 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl17 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl18 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rl20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        
        auto const c1 = cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c3 = cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        auto const c4 = cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c5 = cds::HashMap <String, String> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const r1 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r2 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const r3 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r4 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        auto const r5 = cds::HashMap <String, String> {{1, 1}, {3, 3}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        auto const r6 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} };
        auto const r7 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllOf,
                /* noneCommon= */                       cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <String, String> (),
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <String, String> ()
        );

        auto const rf1 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf2 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf3 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf4 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf5 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable <MapEntry <String, String>>, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rl1 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl2 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl3 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl4 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl5 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { false, true, true, true, true },
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );
        
        auto const r8 = cds::HashMap <String, String> {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        auto const r9 = cds::HashMap <String, String> {{6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        auto const r10 = cds::HashMap <String, String> {{5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        auto const r11 = cds::HashMap <String, String> {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        auto const r12 = cds::HashMap <String, String> {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        auto const r13 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r14 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        7
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeNotOf,
                3U,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllNotOf,
                /* noneCommon= */                       cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <String, String> (),
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <String, String> {{6, 6} },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <String, String> {{3, 3}, {5, 5}, {7, 7} },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <String, String> {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );

        auto const rf6 = cds::HashMap <String, String> {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};
        auto const rf7 = cds::HashMap <String, String> {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};
        auto const rf8 = cds::HashMap <String, String> {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};
        auto const rf9 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf10 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );

        auto const rl6 = cds::HashMap <String, String> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} };
        auto const rl7 = cds::HashMap <String, String> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}};
        auto const rl8 = cds::HashMap <String, String> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}};
        auto const rl9 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rl10 = cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                { true, true, true, false, false },
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );

        std::initializer_list <MapEntry <String, String>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <String, String>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <String, String>> const c10 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        std::initializer_list <MapEntry <String, String>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <String, String>> const c12 = {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <String, String>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <String, String>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <String, String>> const r15 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r16 = {{4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r17 = {{4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} };
        std::initializer_list <MapEntry <String, String>> const r18 = {{4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2} };
        std::initializer_list <MapEntry <String, String>> const r19 = {{4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r20 = {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r21 = {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {0U, 1U, 2U, 3U, 3U, 3U, 3U},
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           0U,
                /* expectedMutableCollectionFromNone= */       {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromOne= */            1U,
                /* expectedMutableCollectionFromOne= */        {{4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMore= */           3U,
                /* expectedMutableCollectionFromMore= */       {{4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2} },
                /* expectedResultFromAll= */            9U,
                /* expectedMutableCollectionFromAll= */        {},
                /* expectedResultFromAllAndMore= */     9U,
                /* expectedMutableCollectionFromAllAndMore= */ {}
        );

        std::initializer_list <MapEntry <String, String>> const rf11 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const rf12 = {{4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const rf13 = {{4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const rf14 = {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const rf15 = {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list <MapEntry <String, String>>, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        0
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <MapEntry <String, String>> const rl11 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const rl12 = {{4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const rl13 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} };
        std::initializer_list <MapEntry <String, String>> const rl14 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} };
        std::initializer_list <MapEntry <String, String>> const rl15 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        5
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { false, true, true, true, true },
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <MapEntry <String, String>> const r22 = {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r23 = {{6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r24 = {{5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r25 = {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r26 = {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r27 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const r28 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        7
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeNotOf,
                3U,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                {3U, 3U, 3U, 3U, 3U, 0U, 0U},
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveAllOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeAllNotOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeAllPfnVariant= */              & cds :: MutableCollection < MapEntry < String, String > > :: removeAllNotOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           9U,
                /* expectedMutableCollectionFromNone= */       {},
                /* expectedResultFromOne= */            8U,
                /* expectedMutableCollectionFromOne= */        {{6, 6} },
                /* expectedResultFromMore= */           6U,
                /* expectedMutableCollectionFromMore= */       {{5, 5}, {7, 7}, {3, 3} },
                /* expectedResultFromAll= */            0U,
                /* expectedMutableCollectionFromAll= */        {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAllAndMore= */     0U,
                /* expectedMutableCollectionFromAllAndMore= */ {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} }
        );

        std::initializer_list <MapEntry <String, String>> const rf16 = {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};
        std::initializer_list <MapEntry <String, String>> const rf17 = {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};
        std::initializer_list <MapEntry <String, String>> const rf18 = {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};
        std::initializer_list <MapEntry <String, String>> const rf19 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};
        std::initializer_list <MapEntry <String, String>> const rf20 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}};

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        10
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );

        std::initializer_list <MapEntry <String, String>> const rl16 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} };
        std::initializer_list <MapEntry <String, String>> const rl17 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}};
        std::initializer_list <MapEntry <String, String>> const rl18 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}};
        std::initializer_list <MapEntry <String, String>> const rl19 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        std::initializer_list <MapEntry <String, String>> const rl20 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <String, String> >, decltype (underTest), MapEntry <String, String> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral, Size> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        15
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <String, String> > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                { true, true, true, false, false },
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );
    });

    return allOk;
}
