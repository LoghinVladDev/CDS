#ifndef MUTABLE_COLLECTION_TEST_450_COMMON_H
#define MUTABLE_COLLECTION_TEST_450_COMMON_H

#include "MutableCollectionTest.h"
#include "MutableCollectionTest_common.hpp"
#include <initializer_list>
#include <CDS/Tuple>

namespace {
    template <typename E, typename I>
    using RemovePfn = Size (cds::MutableCollection <E> :: *) (Size, I const &);

    template <typename E, typename I>
    using RemoveOnePfn = bool (cds::MutableCollection <E> :: *) (I const &);

    template <typename E, typename I>
    using RemoveAllPfn = Size (cds::MutableCollection <E> :: *) (I const &);

    /* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTG-00450-RO-cpp-xx. MCTC-00451-RO to MCTC-00464-RO */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupItemRemoveOfFirstHalf (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemovePfn <__ElementType, __OtherIterableType> removePfnVariant,
            Size const limit,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <Size> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        auto const * const pTestLib = tData.template get <0> ();
        auto const & groupVariant = tData.template get <1> ();
        auto const subvariant = tData.template get <2> ();
        auto const subvariantOffset = tData.template get <3> ();

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

        cds::Size variantBase = 451U;
        pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

        /* MutableCollectionTestCase-RemoveOf-removeOfNoneCommon-cpp-xx : MCTC-00451-RO-removeOfNoneCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeNotOfNoneCommon-cpp-xx : MCTC-00458-RO-removeNotOfNoneCommon-cpp-xx */
        auto       copyRO451            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO451 = copyRO451;
        auto       removedCountRB451    = ( collectionRO451.* removePfnVariant ) ( limit, noneCommon );
        pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO451.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
        if ( (removedCountRB451 != expectedResultFromNone) || (! equals ( collectionRO451, expectedCollectionFromNone )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeOfOneCommon-cpp-xx : MCTC-00452-RO-removeOfOneCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeNotOfOneCommon-cpp-xx : MCTC-00459-RO-removeNotOfOneCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO452            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO452 = copyRO452;
        auto       removedCountRB452    = ( collectionRO452.* removePfnVariant ) ( limit, oneCommon );
        pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO452.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
        if ( (removedCountRB452 != expectedResultFromOne) || (! equals ( collectionRO452, expectedCollectionFromOne)) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeOfMoreLessThanLimitCommon-cpp-xx : MCTC-00453-RO-removeOfMoreLessThanLimitCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeNotOfMoreLessThanLimitCommon-cpp-xx : MCTC-00460-RO-removeOfMoreLessThanLimitCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO453            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO453 = copyRO453;
        auto       removedCountRB453    = ( collectionRO453.* removePfnVariant ) ( limit, moreLessThanLimitCommon );
        pTestLib->log ( "object after '%s with more less than limit common' : '%s'. expected : '%s'", subvariant, collectionRO453.toString().cStr(), 
                toString ( expectedCollectionFromMoreLessThanLimit ).cStr() );
        if ( (removedCountRB453 != expectedResultFromMoreLessThanLimit) || (! equals ( collectionRO453, expectedCollectionFromMoreLessThanLimit )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sMoreLessThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreLessThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeOfMoreCommon-cpp-xx : MCTC-00454-RO-removeOfMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeNotOfMoreCommon-cpp-xx : MCTC-00461-RO-removeNotOfMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO454            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO454 = copyRO454;
        auto       removedCountRB454    = ( collectionRO454.* removePfnVariant ) ( limit, moreCommon );
        pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO454.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
        if ( (removedCountRB454 != expectedResultFromMore) || (! equals ( collectionRO454, expectedCollectionFromMore )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
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
            Size                       const limit,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <Size> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        auto const * const pTestLib = tData.template get <0> ();
        auto const & groupVariant = tData.template get <1> ();
        auto const subvariant = tData.template get <2> ();
        auto const subvariantOffset = tData.template get <3> ();

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
        cds::Size variantBase = 455U;
        auto       copyRO455            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO455 = copyRO455;
        auto       removedCountRB455    = ( collectionRO455.* removePfnVariant ) ( limit, moreMoreThanLimitCommon );
        pTestLib->log ( "object after '%s with more than limit common' : '%s'. expected : '%s'", subvariant, collectionRO455.toString().cStr(), toString ( expectedCollectionFromMoreMoreThanLimit ).cStr() );
        if ( (removedCountRB455 != expectedResultFromMoreMoreThanLimit) || (! equals ( collectionRO455, expectedCollectionFromMoreMoreThanLimit )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeOfAllCommon-cpp-xx : MCTC-00456-RO-removeOfAllCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeNotOfAllCommon-cpp-xx : MCTC-00463-RO-removeNotOfAllCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO456            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO456 = copyRO456;
        auto       removedCountRB456    = ( collectionRO456.* removePfnVariant ) ( limit, allCommon );
        pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO456.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
        if ( (removedCountRB456 != expectedResultFromAll) || (! equals ( collectionRO456, expectedCollectionFromAll )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeOfAllAndMoreCommon-cpp-xx : MCTC-00457-RO-removeOfAllAndMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeNotOfAllAndMoreCommon-cpp-xx : MCTC-00464-RO-removeNotOfAllAndMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO457            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO457 = copyRO457;
        auto       removedCountRB457    = ( collectionRO457.* removePfnVariant ) ( limit, allAndMoreCommon );
        pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO457.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
        if ( (removedCountRB457 != expectedResultFromAllAndMore) || (! equals ( collectionRO457, expectedCollectionFromAllAndMore )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
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
            Size                       const limit,
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

        auto const * const pTestLib = tData.template get <0> ();
        auto const & groupVariant = tData.template get <1> ();
        auto const subvariant = tData.template get <2> ();
        auto const subvariantOffset = tData.template get <3> ();

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
        cds::Size variantBase = 501U;
        auto       copyRO501            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO501 = copyRO501;
        auto       removedCountRB501    = ( collectionRO501.* removeFirstLastPfnVariant ) ( noneCommon );
        pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO501.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
        if ( (removedCountRB501 != expectedResultFromNone) || (! equals ( collectionRO501, expectedCollectionFromNone )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeFirstOfOneCommon-cpp-xx : MCTC-00502-RO-removeFirstOfOneCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastOfOneCommon-cpp-xx : MCTC-00507-RO-removeLastOfOneCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfOneCommon-cpp-xx : MCTC-00512-RO-removeFirstNotOfOneCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastNotOfOneCommon-cpp-xx : MCTC-00517-RO-removeLastNotOfOneCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO502            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO502 = copyRO502;
        auto       removedCountRB502    = ( collectionRO502.* removeFirstLastPfnVariant ) ( oneCommon );
        pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO502.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
        if ( (removedCountRB502 != expectedResultFromOne) || (! equals ( collectionRO502, expectedCollectionFromOne )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeFirstOfMoreCommon-cpp-xx : MCTC-00503-RO-removeFirstOfMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastOfMoreCommon-cpp-xx : MCTC-00508-RO-removeLastOfMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfMoreCommon-cpp-xx : MCTC-00513-RO-removeFirstNotOfMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastNotOfMoreCommon-cpp-xx : MCTC-00518-RO-removeLastNotOfMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO503            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO503 = copyRO503;
        auto       removedCountRB503    = ( collectionRO503.* removeFirstLastPfnVariant ) ( moreCommon );
        pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO503.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
        if ( (removedCountRB503 != expectedResultFromMore) || (! equals ( collectionRO503, expectedCollectionFromMore )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeFirstOfAllCommon-cpp-xx : MCTC-00504-RO-removeFirstOfAllCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastOfAllCommon-cpp-xx : MCTC-00509-RO-removeLastOfAllCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfAllCommon-cpp-xx : MCTC-00514-RO-removeFirstNotOfAllCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastNotOfAllCommon-cpp-xx : MCTC-00519-RO-removeLastNotOfAllCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO504            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO504 = copyRO504;
        auto       removedCountRB504    = ( collectionRO504.* removeFirstLastPfnVariant ) ( allCommon );
        pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO504.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
        if ( (removedCountRB504 != expectedResultFromAll) || (! equals ( collectionRO504, expectedCollectionFromAll )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeFirstOfAllAndMoreCommon-cpp-xx : MCTC-00505-RO-removeFirstOfAllAndMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastOfAllAndMoreCommon-cpp-xx : MCTC-00510-RO-removeLastOfAllAndMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeFirstNotOfAllAndMoreCommon-cpp-xx : MCTC-00515-RO-removeFirstNotOfAllAndMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeLastNotOfAllAndMoreCommon-cpp-xx : MCTC-00520-RO-removeLastNotOfAllAndMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO505            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO505 = copyRO505;
        auto       removedCountRB505    = ( collectionRO505.* removeFirstLastPfnVariant ) ( allAndMoreCommon );
        pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO505.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
        if ( (removedCountRB505 != expectedResultFromAllAndMore) || (! equals ( collectionRO505, expectedCollectionFromAllAndMore )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        return true;
    }

    /* MutableCollectionTestGroup-RemoveOf-cpp-xx : MCTC-00450-RO-cpp-xx. MCTC-00481-RO to MCTC-00490-RO. */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupItemRemoveAllOf (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemoveAllPfn <__ElementType, __OtherIterableType> removeAllPfnVariant,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <Size> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        auto const * const pTestLib = tData.template get <0> ();
        auto const & groupVariant = tData.template get <1> ();
        auto const subvariant = tData.template get <2> ();
        auto const subvariantOffset = tData.template get <3> ();

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

        /* MutableCollectionTestCase-RemoveOf-removeAllOfNoneCommon-cpp-xx : MCTC-00481-RO-removeAllOfNoneCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeAllNotOfNoneCommon-cpp-xx : MCTC-00486-RO-removeAllNotOfNoneCommon-cpp-xx */
        cds::Size variantBase = 481U;
        auto       copyRO481            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO481 = copyRO481;
        auto       removedCountRB481    = ( collectionRO481.* removeAllPfnVariant ) ( noneCommon );
        pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO481.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
        if ( (removedCountRB481 != expectedResultFromNone) || (! equals ( collectionRO481, expectedCollectionFromNone )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeAllOfOneCommon-cpp-xx : MCTC-00482-RO-removeAllOfOneCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeAllNotOfOneCommon-cpp-xx : MCTC-00487-RO-removeAllNotOfOneCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO482            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO482 = copyRO482;
        auto       removedCountRB482    = ( collectionRO482.* removeAllPfnVariant ) ( oneCommon );
        pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO482.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
        if ( (removedCountRB482 != expectedResultFromOne) || (! equals ( collectionRO482, expectedCollectionFromOne )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeAllOfMoreCommon-cpp-xx : MCTC-00483-RO-removeAllOfMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeAllNotOfMoreCommon-cpp-xx : MCTC-00488-RO-removeAllNotOfMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO483            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO483 = copyRO483;
        auto       removedCountRB483    = ( collectionRO483.* removeAllPfnVariant ) ( moreCommon );
        pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO483.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
        if ( (removedCountRB483 != expectedResultFromMore) || (! equals ( collectionRO483, expectedCollectionFromMore )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeAllOfAllCommon-cpp-xx : MCTC-00484-RO-removeAllOfAllCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeAllNotOfAllCommon-cpp-xx : MCTC-00489-RO-removeAllNotOfAllCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO484            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO484 = copyRO484;
        auto       removedCountRB484    = ( collectionRO484.* removeAllPfnVariant ) ( allCommon );
        pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO484.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
        if ( (removedCountRB484 != expectedResultFromAll) || (! equals ( collectionRO484, expectedCollectionFromAll )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* MutableCollectionTestCase-RemoveOf-removeAllOfAllAndMoreCommon-cpp-xx : MCTC-00485-RO-removeAllOfAllAndMoreCommon-cpp-xx */
        /* MutableCollectionTestCase-RemoveOf-removeAllNotOfAllAndMoreCommon-cpp-xx : MCTC-00490-RO-removeAllNotOfAllAndMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO485            = iterableUnderTest;
        cds :: MutableCollection < __ElementType > & collectionRO485 = copyRO485;
        auto       removedCountRB485    = ( collectionRO485.* removeAllPfnVariant ) ( allAndMoreCommon );
        pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO485.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
        if ( (removedCountRB485 != expectedResultFromAllAndMore) || (! equals ( collectionRO485, expectedCollectionFromAllAndMore )) ) {
            pTestLib->logError( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        return true;
    }
    
    Size const vOffsetRO = 0U;
    Size const vOffsetRAO = 0U;
    Size const vOffsetRFO = 0U;
    Size const vOffsetRLO = 5U;
    Size const vOffsetRNO = 7U;
    Size const vOffsetRANO = 5U;
    Size const vOffsetRFNO = 10U;
    Size const vOffsetRLNO = 15U;

    Size const limitR1 = 3U;

    std::initializer_list<Size> const statusSetRO = {0U, 1U, 2U, 3U, 3U, 3u, 3U};
    std::initializer_list<Size> const statusSetRAO = {0U, 1U, 3U, 9U, 9U};
    std::initializer_list<bool> const statusSetRFO = { false, true, true, true, true };
    std::initializer_list<bool> const statusSetRLO = { false, true, true, true, true };
    std::initializer_list<Size> const statusSetRNO = {3U, 3U, 3U, 3U, 3U, 0U, 0U};
    std::initializer_list<Size> const statusSetRANO = {9U, 8U, 6U, 0U, 0U };
    std::initializer_list<bool> const statusSetRFNO = { true, true, true, false, false };
    std::initializer_list<bool> const statusSetRLNO = { true, true, true, false, false };
}

#endif
