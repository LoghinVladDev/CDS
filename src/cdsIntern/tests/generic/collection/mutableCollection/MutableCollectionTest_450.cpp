#include "MutableCollectionTest.h"
#include "MutableCollectionTest_common.hpp"

namespace {
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
}


auto MutableCollectionTest::tests_00450_00499 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                                make_a <int> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_a <int> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_a <int> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make_a <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_a <int> (1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_a <int> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_a <int> (1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make_a <int> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make_a <int> (4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <int> (1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_a <int> (2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <int> (2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <int> (1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_a <int> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <int> (1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                                make_a <int> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_a <int> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_a <int> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make_a <int> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make_a <int> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_a <int> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_a <int> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_a <int> (2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_a <int> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <int> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <int> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       make_a <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_a <int> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <int> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <int> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <int> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {1, 2, 4, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {1, 4, 6, 7, 8, 9 },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         {4, 5, 6, 7, 8, 9}
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {2, 3, 4, 5, 6, 7, 8, 9}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {2, 3, 5, 7, 8, 9 },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         {1, 2, 3, 4, 5, 6, 7, 8, 9 }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                                make_ll <int> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_ll <int> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_ll <int> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make_ll <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_ll <int> (1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_ll <int> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_ll <int> (1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make_ll <int> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make_ll <int> (4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <int> (1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <int> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <int> (1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                                make_ll <int> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_ll <int> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_ll <int> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make_ll <int> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make_ll <int> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_ll <int> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_ll <int> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_ll <int> (2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <int> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       make_ll <int> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <int> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <int> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <int> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <int> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <int> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );


        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {1, 2, 4, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {1, 4, 6, 7, 8, 9 },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         {4, 5, 6, 7, 8, 9 }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {2, 3, 4, 5, 6, 7, 8, 9 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < int > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {2, 3, 5, 7, 8, 9 },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         {1, 2, 3, 4, 5, 6, 7, 8, 9 }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeFirstNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < int >, decltype (underTest), int > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < int > :: removeLastNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               cds::HashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                cds::HashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  cds::HashMap <int, int> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                cds::HashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         cds::HashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  cds::HashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               cds::HashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  cds::HashMap <int, int> {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstOf,
                /* noneCommon= */                       cds::HashMap <int, int>  {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <int, int>  {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <int, int>  {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <int, int>  {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <int, int>  {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <int, int>  {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <int, int>  {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastOf,
                /* noneCommon= */                       cds::HashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               cds::HashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                cds::HashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  cds::HashMap <int, int> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                cds::HashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         cds::HashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                cds::HashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  cds::HashMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               cds::HashMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  cds::HashMap <int, int> {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstNotOf,
                /* noneCommon= */                       cds::HashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastNotOf,
                /* noneCommon= */                       cds::HashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < int, int > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeFirstNotOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < int, int > >, decltype (underTest), MapEntry < int, int > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < int, int > > :: removeLastNotOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                                make_a <String> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_a <String> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_a <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_a <String> (1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_a <String> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_a <String> (1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make_a <String> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make_a <String> (4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <String> (1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_a <String> (2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <String> (2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <String> (1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                                make_a <String> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_a <String> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_a <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make_a <String> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make_a <String> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_a <String> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_a <String> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_a <String> (2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_a <String> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <String> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <String> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       make_a <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_a <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_a <String> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_a <String> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {1, 2, 4, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {1, 4, 6, 7, 8, 9 },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         {4, 5, 6, 7, 8, 9 }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {2, 3, 4, 5, 6, 7, 8, 9 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {2, 3, 5, 7, 8, 9 },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         {1, 2, 3, 4, 5, 6, 7, 8, 9 }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_ll <String> (10, 11, 12, 13),
                /* oneCommon= */                                make_ll <String> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_ll <String> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_ll <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_ll <String> (1, 2, 4, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_ll <String> (1, 2, 4, 6, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_ll <String> (1, 4, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                make_ll <String> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         make_ll <String> (4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       make_ll <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <String> (1, 2, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       make_ll <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 ),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <String> (1, 2, 3, 4, 5, 6, 8, 9 ),
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 )
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               make_ll <String> (10, 11, 12, 13),
                /* oneCommon= */                                make_ll <String> (16, 6, 11, 12, 13),
                /* moreLessThanLimitCommon= */                  make_ll <String> (20, 123, 5, 1230, 435, 3, 1235, 9534),
                /* moreCommon= */                               make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* moreMoreThanLimitCommon= */                  make_ll <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                                make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                         make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               make_ll <String> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                make_ll <String> (4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  make_ll <String> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               make_ll <String> (3, 5, 6, 7, 8, 9 ),
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  make_ll <String> (2, 3, 5, 7, 8, 9 ),
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 ),
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 )
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       make_ll <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       make_ll <String> (10, 11, 12, 13),
                /* oneCommon= */                        make_ll <String> (16, 6, 11, 12, 13),
                /* moreCommon= */                       make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245),
                /* allCommon= */                        make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 ),
                /* allAndMoreCommon= */                 make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 ),
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 ),
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8),
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9),
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9)
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {1, 2, 4, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {1, 2, 4, 6, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {1, 4, 6, 7, 8, 9 },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         {4, 5, 6, 7, 8, 9 }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {2, 3, 4, 5, 6, 7, 8, 9 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 7, 8, 9 },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 8, 9 },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8 }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < String > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {10, 11, 12, 13},
                /* oneCommon= */                                {16, 6, 11, 12, 13},
                /* moreLessThanLimitCommon= */                  {20, 123, 5, 1230, 435, 3, 1235, 9534},
                /* moreCommon= */                               {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* moreMoreThanLimitCommon= */                  {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                                {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                         {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                {4, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {3, 5, 6, 7, 8, 9 },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {2, 3, 5, 7, 8, 9 },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                {1, 2, 3, 4, 5, 6, 7, 8, 9 },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         {1, 2, 3, 4, 5, 6, 7, 8, 9 }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeFirstNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < String >, decltype (underTest), String > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < String > :: removeLastNotOf,
                /* noneCommon= */                       {10, 11, 12, 13},
                /* oneCommon= */                        {16, 6, 11, 12, 13},
                /* moreCommon= */                       {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
                /* allCommon= */                        {9, 2, 5, 1, 4, 3, 7, 8, 6 },
                /* allAndMoreCommon= */                 {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {1, 2, 3, 4, 5, 6, 7, 8 },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {1, 2, 3, 4, 5, 6, 7, 8},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {1, 2, 3, 4, 5, 6, 7, 8, 9},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {1, 2, 3, 4, 5, 6, 7, 8, 9}
        );

    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  cds::HashMap <String, String> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  cds::HashMap <String, String> {{1, 1}, {3, 3}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9}}
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstOf,
                /* noneCommon= */                       cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastOf,
                /* noneCommon= */                       cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <String, String> {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "MutableCollection",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  cds::HashMap <String, String> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               cds::HashMap <String, String> {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                cds::HashMap <String, String> {{6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  cds::HashMap <String, String> {{5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               cds::HashMap <String, String> {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  cds::HashMap <String, String> {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstNotOf,
                /* noneCommon= */                       cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <String, String> {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <String, String> {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <String, String> {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "MutableCollection",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastNotOf,
                /* noneCommon= */                       cds::HashMap <String, String> {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        cds::HashMap <String, String> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       cds::HashMap <String, String> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        cds::HashMap <String, String> {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 cds::HashMap <String, String> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       cds::HashMap <String, String> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        cds::HashMap <String, String> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       cds::HashMap <String, String> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ cds::HashMap <String, String> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeOf",
                /* subvariantOffset= */                         0,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   0U,
                /* expectedMutableCollectionFromNone= */               {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromOne= */                    1U,
                /* expectedMutableCollectionFromOne= */                {{4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMoreLessThanLimit= */      2U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {{4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {{4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {{4, 4}, {6, 6}, {8, 8}, {9, 9}, {1, 1}, {3, 3} },
                /* expectedResultFromAll= */                    3U,
                /* expectedMutableCollectionFromAll= */                {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAllAndMore= */             3U,
                /* expectedMutableCollectionFromAllAndMore= */         {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstOf",
                /* subvariantOffset= */                 0,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastOf",
                /* subvariantOffset= */                 5,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           false,
                /* expectedMutableCollectionFromNone= */       {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} },
                /* expectedResultFromAll= */            true,
                /* expectedMutableCollectionFromAll= */        {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} },
                /* expectedResultFromAllAndMore= */     true,
                /* expectedMutableCollectionFromAllAndMore= */ {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} }
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                                 this,
                /* groupVariant= */                             "InitializerList",
                /* subvariant= */                               "removeNotOf",
                /* subvariantOffset= */                         7,
                /* iterableUnderTest= */                        underTest,
                /* removePfnVariant= */                         & cds :: MutableCollection < MapEntry < String, String > > :: removeNotOf,
                /* limit= */                                    3U,
                /* noneCommon= */                               {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                                {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreLessThanLimitCommon= */                  {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
                /* moreCommon= */                               {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* moreMoreThanLimitCommon= */                  {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                                {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                         {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */                   3U,
                /* expectedMutableCollectionFromNone= */               {{7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromOne= */                    3U,
                /* expectedMutableCollectionFromOne= */                {{6, 6}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMoreLessThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreLessThanLimit= */  {{5, 5}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMore= */                   3U,
                /* expectedMutableCollectionFromMore= */               {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromMoreMoreThanLimit= */      3U,
                /* expectedMutableCollectionFromMoreMoreThanLimit= */  {{5, 5}, {7, 7}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAll= */                    0U,
                /* expectedMutableCollectionFromAll= */                {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAllAndMore= */             0U,
                /* expectedMutableCollectionFromAllAndMore= */         {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} }
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

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeFirstNotOf",
                /* subvariantOffset= */                 10,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeFirstNotOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}},
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}},
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}}
        );

        allOk = allOk && mutableCollectionTestGroupItemRemoveFirstLastOf < std :: initializer_list < MapEntry < String, String > >, decltype (underTest), MapEntry < String, String > > (
                /* pTestLib= */                         this,
                /* groupVariant= */                     "InitializerList",
                /* subvariant= */                       "removeLastNotOf",
                /* subvariantOffset= */                 15,
                /* iterableUnderTest= */                underTest,
                /* removeFirstLastPfnVariant= */        & cds :: MutableCollection < MapEntry < String, String > > :: removeLastNotOf,
                /* noneCommon= */                       {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
                /* oneCommon= */                        {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
                /* moreCommon= */                       {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
                /* allCommon= */                        {{9, 9}, {2, 2}, {5, 5}, {1, 1}, {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
                /* allAndMoreCommon= */                 {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} },
                /* expectedResultFromNone= */           true,
                /* expectedMutableCollectionFromNone= */       {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2} },
                /* expectedResultFromOne= */            true,
                /* expectedMutableCollectionFromOne= */        {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}},
                /* expectedResultFromMore= */           true,
                /* expectedMutableCollectionFromMore= */       {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {3, 3}},
                /* expectedResultFromAll= */            false,
                /* expectedMutableCollectionFromAll= */        {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} },
                /* expectedResultFromAllAndMore= */     false,
                /* expectedMutableCollectionFromAllAndMore= */ {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} }
        );
    });

    return allOk;
}
