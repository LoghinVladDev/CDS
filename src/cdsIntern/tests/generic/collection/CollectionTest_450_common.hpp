#ifndef COLLECTION_TEST_450_COMMON_H
#define COLLECTION_TEST_450_COMMON_H

#include "CollectionTest.h"
#include "CollectionTest_common.hpp"
#include <CDS/Tuple>

namespace {
    template <typename E, typename I>
    using RemovePfn = Size (cds::Collection <E> :: *) (Size, I const &);

    template <typename E, typename I>
    using RemoveOnePfn = bool (cds::Collection <E> :: *) (I const &);

    template <typename E, typename I>
    using RemoveAllPfn = Size (cds::Collection <E> :: *) (I const &);

    /* CollectionTestGroup-RemoveOf-cpp-xx : CTG-00450-RO-cpp-xx. CTC-00451-RO to CTC-00464-RO */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupItemRemoveOfFH (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemovePfn <__ElementType, __OtherIterableType> removePfnVariant,
            Size                        limit,
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

        pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

        /* CollectionTestCase-RemoveOf-removeOfNoneCommon-cpp-xx : CTC-00451-RO-removeOfNoneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeNotOfNoneCommon-cpp-xx : CTC-00458-RO-removeNotOfNoneCommon-cpp-xx */
       
        cds::Size variantBase = 451U;
        auto       copyRO451            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO451 = copyRO451;
        auto       removedCountRB451    = ( collectionRO451.* removePfnVariant ) ( limit, noneCommon );
        pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO451.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
        if ( (removedCountRB451 != expectedResultFromNone) || (! equals ( collectionRO451, expectedCollectionFromNone )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeOfOneCommon-cpp-xx : CTC-00452-RO-removeOfOneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeNotOfOneCommon-cpp-xx : CTC-00459-RO-removeNotOfOneCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO452            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO452 = copyRO452;
        auto       removedCountRB452    = ( collectionRO452.* removePfnVariant ) ( limit, oneCommon );
        pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO452.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
        if ( (removedCountRB452 != expectedResultFromOne) || (! equals ( collectionRO452, expectedCollectionFromOne )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeOfMoreLessThanLimitCommon-cpp-xx : CTC-00453-RO-removeOfMoreLessThanLimitCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeNotOfMoreLessThanLimitCommon-cpp-xx : CTC-00460-RO-removeOfMoreLessThanLimitCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO453            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO453 = copyRO453;
        auto       removedCountRB453    = ( collectionRO453.* removePfnVariant ) ( limit, moreLessThanLimitCommon );
        pTestLib->log ( "object after '%s with more less than limit common' : '%s'. expected : '%s'", subvariant, collectionRO453.toString().cStr(), toString ( expectedCollectionFromMoreLessThanLimit ).cStr() );
        if ( (removedCountRB453 != expectedResultFromMoreLessThanLimit) || (! equals ( collectionRO453, expectedCollectionFromMoreLessThanLimit )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sMoreLessThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sMoreLessThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeOfMoreCommon-cpp-xx : CTC-00454-RO-removeOfMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeNotOfMoreCommon-cpp-xx : CTC-00461-RO-removeNotOfMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO454            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO454 = copyRO454;
        auto       removedCountRB454    = ( collectionRO454.* removePfnVariant ) ( limit, moreCommon );
        pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO454.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
        if ( (removedCountRB454 != expectedResultFromMore) || (! equals ( collectionRO454, expectedCollectionFromMore )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        return true;
    }

    /* CollectionTestGroup-RemoveOf-cpp-xx : CTG-00450-RO-cpp-xx. CTC-00451-RO to CTC-00464-RO */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupItemRemoveOfSH (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemovePfn <__ElementType, __OtherIterableType> removePfnVariant,
            Size                        limit,
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

        pTestLib->log ( "Object Under Test : %s", iterableUnderTest.toString().cStr() );

        /* CollectionTestCase-RemoveOf-removeOfMoreMoreThanLimitCommon-cpp-xx : CTC-00455-RO-removeOfMoreMoreThanLimitCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeNotOfMoreMoreThanLimitCommon-cpp-xx : CTC-00462-RO-removeNotOfMoreMoreThanLimitCommon-cpp-xx */
        cds::Size variantBase = 455U;
        auto       copyRO455            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO455 = copyRO455;
        auto       removedCountRB455    = ( collectionRO455.* removePfnVariant ) ( limit, moreMoreThanLimitCommon );
        pTestLib->log ( "object after '%s with more than limit common' : '%s'. expected : '%s'", subvariant, collectionRO455.toString().cStr(), toString ( expectedCollectionFromMoreMoreThanLimit ).cStr() );
        if ( (removedCountRB455 != expectedResultFromMoreMoreThanLimit) || (! equals ( collectionRO455, expectedCollectionFromMoreMoreThanLimit )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sMoreMoreThanLimitCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeOfAllCommon-cpp-xx : CTC-00456-RO-removeOfAllCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeNotOfAllCommon-cpp-xx : CTC-00463-RO-removeNotOfAllCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO456            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO456 = copyRO456;
        auto       removedCountRB456    = ( collectionRO456.* removePfnVariant ) ( limit, allCommon );
        pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO456.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
        if ( (removedCountRB456 != expectedResultFromAll) || (! equals ( collectionRO456, expectedCollectionFromAll )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeOfAllAndMoreCommon-cpp-xx : CTC-00457-RO-removeOfAllAndMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeNotOfAllAndMoreCommon-cpp-xx : CTC-00464-RO-removeNotOfAllAndMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO457            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO457 = copyRO457;
        auto       removedCountRB457    = ( collectionRO457.* removePfnVariant ) ( limit, allAndMoreCommon );
        pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO457.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
        if ( (removedCountRB457 != expectedResultFromAllAndMore) || (! equals ( collectionRO457, expectedCollectionFromAllAndMore )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        return true;
    }

    /* CollectionTestGroup-RemoveOf-cpp-xx : CTG-00450-RO-cpp-xx. CTC-00451-RO to CTC-00464-RO */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupItemRemoveOf (
            cds::Tuple <Test const *, cds::String, cds::StringLiteral, Size> const & tData,
            __IterableType      const & iterableUnderTest,
            RemovePfn <__ElementType, __OtherIterableType> removePfnVariant,
            Size                       const limit,
            std::initializer_list <__OtherIterableType const *> const & cases,
            std::initializer_list <Size> const & statuses,
            std::initializer_list <__OtherIterableType const *> const & results
    ) -> bool {

        return
                collectionTestGroupItemRemoveOfFH (
                        tData, iterableUnderTest, removePfnVariant,
                        limit, cases, statuses, results
                ) && collectionTestGroupItemRemoveOfSH (
                        tData, iterableUnderTest, removePfnVariant,
                        limit, cases, statuses, results
                );
    }

    /* CollectionTestGroup-RemoveOf-cpp-xx : CTG-00450-RO-cpp-xx. CTC-00481-RO to CTC-00490-RO. */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupItemRemoveAllOf (
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

        /* CollectionTestCase-RemoveOf-removeAllOfNoneCommon-cpp-xx : CTC-00481-RO-removeAllOfNoneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeAllNotOfNoneCommon-cpp-xx : CTC-00486-RO-removeAllNotOfNoneCommon-cpp-xx */
        cds::Size variantBase = 481U;
        auto       copyRO481            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO481 = copyRO481;
        auto       removedCountRB481    = ( collectionRO481.* removeAllPfnVariant ) ( noneCommon );
        pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO481.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
        if ( (removedCountRB481 != expectedResultFromNone) || (! equals ( collectionRO481, expectedCollectionFromNone )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeAllOfOneCommon-cpp-xx : CTC-00482-RO-removeAllOfOneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeAllNotOfOneCommon-cpp-xx : CTC-00487-RO-removeAllNotOfOneCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO482            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO482 = copyRO482;
        auto       removedCountRB482    = ( collectionRO482.* removeAllPfnVariant ) ( oneCommon );
        pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO482.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
        if ( (removedCountRB482 != expectedResultFromOne) || (! equals ( collectionRO482, expectedCollectionFromOne )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeAllOfMoreCommon-cpp-xx : CTC-00483-RO-removeAllOfMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeAllNotOfMoreCommon-cpp-xx : CTC-00488-RO-removeAllNotOfMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO483            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO483 = copyRO483;
        auto       removedCountRB483    = ( collectionRO483.* removeAllPfnVariant ) ( moreCommon );
        pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO483.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
        if ( (removedCountRB483 != expectedResultFromMore) || (! equals ( collectionRO483, expectedCollectionFromMore )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeAllOfAllCommon-cpp-xx : CTC-00484-RO-removeAllOfAllCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeAllNotOfAllCommon-cpp-xx : CTC-00489-RO-removeAllNotOfAllCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO484            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO484 = copyRO484;
        auto       removedCountRB484    = ( collectionRO484.* removeAllPfnVariant ) ( allCommon );
        pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO484.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
        if ( (removedCountRB484 != expectedResultFromAll) || (! equals ( collectionRO484, expectedCollectionFromAll )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeAllOfAllAndMoreCommon-cpp-xx : CTC-00485-RO-removeAllOfAllAndMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeAllNotOfAllAndMoreCommon-cpp-xx : CTC-00490-RO-removeAllNotOfAllAndMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO485            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO485 = copyRO485;
        auto       removedCountRB485    = ( collectionRO485.* removeAllPfnVariant ) ( allAndMoreCommon );
        pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO485.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
        if ( (removedCountRB485 != expectedResultFromAllAndMore) || (! equals ( collectionRO485, expectedCollectionFromAllAndMore )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        return true;
    }

    /* CollectionTestGroup-RemoveOf-cpp-xx : CTG-00450-RO-cpp-xx. CTC-00501-RO to CTC-00520-RO. */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupItemRemoveFirstLastOf (
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

        /* CollectionTestCase-RemoveOf-removeFirstOfNoneCommon-cpp-xx : CTC-00501-RO-removeFirstOfNoneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastOfNoneCommon-cpp-xx : CTC-00506-RO-removeLastOfNoneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeFirstNotOfNoneCommon-cpp-xx : CTC-00511-RO-removeFirstNotOfNoneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastNotOfNoneCommon-cpp-xx : CTC-00516-RO-removeLastNotOfNoneCommon-cpp-xx */
        cds::Size variantBase = 501U;
        auto       copyRO501            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO501 = copyRO501;
        auto       removedCountRB501    = ( collectionRO501.* removeFirstLastPfnVariant ) ( noneCommon );
        pTestLib->log ( "object after '%s with none common' : '%s'. expected : '%s'", subvariant, collectionRO501.toString().cStr(), toString ( expectedCollectionFromNone ).cStr() );
        if ( (removedCountRB501 != expectedResultFromNone) || (! equals ( collectionRO501, expectedCollectionFromNone )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sNoneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeFirstOfOneCommon-cpp-xx : CTC-00502-RO-removeFirstOfOneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastOfOneCommon-cpp-xx : CTC-00507-RO-removeLastOfOneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeFirstNotOfOneCommon-cpp-xx : CTC-00512-RO-removeFirstNotOfOneCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastNotOfOneCommon-cpp-xx : CTC-00517-RO-removeLastNotOfOneCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO502            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO502 = copyRO502;
        auto       removedCountRB502    = ( collectionRO502.* removeFirstLastPfnVariant ) ( oneCommon );
        pTestLib->log ( "object after '%s with one common' : '%s'. expected : '%s'", subvariant, collectionRO502.toString().cStr(), toString ( expectedCollectionFromOne ).cStr() );
        if ( (removedCountRB502 != expectedResultFromOne) || (! equals ( collectionRO502, expectedCollectionFromOne )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sOneCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeFirstOfMoreCommon-cpp-xx : CTC-00503-RO-removeFirstOfMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastOfMoreCommon-cpp-xx : CTC-00508-RO-removeLastOfMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeFirstNotOfMoreCommon-cpp-xx : CTC-00513-RO-removeFirstNotOfMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastNotOfMoreCommon-cpp-xx : CTC-00518-RO-removeLastNotOfMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO503            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO503 = copyRO503;
        auto       removedCountRB503    = ( collectionRO503.* removeFirstLastPfnVariant ) ( moreCommon );
        pTestLib->log ( "object after '%s with more common' : '%s'. expected : '%s'", subvariant, collectionRO503.toString().cStr(), toString ( expectedCollectionFromMore ).cStr() );
        if ( (removedCountRB503 != expectedResultFromMore) || (! equals ( collectionRO503, expectedCollectionFromMore )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeFirstOfAllCommon-cpp-xx : CTC-00504-RO-removeFirstOfAllCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastOfAllCommon-cpp-xx : CTC-00509-RO-removeLastOfAllCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeFirstNotOfAllCommon-cpp-xx : CTC-00514-RO-removeFirstNotOfAllCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastNotOfAllCommon-cpp-xx : CTC-00519-RO-removeLastNotOfAllCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO504            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO504 = copyRO504;
        auto       removedCountRB504    = ( collectionRO504.* removeFirstLastPfnVariant ) ( allCommon );
        pTestLib->log ( "object after '%s with all common' : '%s'. expected : '%s'", subvariant, collectionRO504.toString().cStr(), toString ( expectedCollectionFromAll ).cStr() );
        if ( (removedCountRB504 != expectedResultFromAll) || (! equals ( collectionRO504, expectedCollectionFromAll )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sAllCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
        }

        /* CollectionTestCase-RemoveOf-removeFirstOfAllAndMoreCommon-cpp-xx : CTC-00505-RO-removeFirstOfAllAndMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastOfAllAndMoreCommon-cpp-xx : CTC-00510-RO-removeLastOfAllAndMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeFirstNotOfAllAndMoreCommon-cpp-xx : CTC-00515-RO-removeFirstNotOfAllAndMoreCommon-cpp-xx */
        /* CollectionTestCase-RemoveOf-removeLastNotOfAllAndMoreCommon-cpp-xx : CTC-00520-RO-removeLastNotOfAllAndMoreCommon-cpp-xx */
        ++ variantBase;
        auto       copyRO505            = iterableUnderTest;
        cds :: Collection < __ElementType > & collectionRO505 = copyRO505;
        auto       removedCountRB505    = ( collectionRO505.* removeFirstLastPfnVariant ) ( allAndMoreCommon );
        pTestLib->log ( "object after '%s with all and more common' : '%s'. expected : '%s'", subvariant, collectionRO505.toString().cStr(), toString ( expectedCollectionFromAllAndMore ).cStr() );
        if ( (removedCountRB505 != expectedResultFromAllAndMore) || (! equals ( collectionRO505, expectedCollectionFromAllAndMore )) ) {
            pTestLib->logError( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' failed", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00%d-RO-%sAllAndMoreCommon-%s-" __CDS_cpplang_core_version_name "' OK", variantBase + subvariantOffset, subvariant, groupVariant.cStr() );
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

#endif /* COLLECTION_TEST_450_COMMON_H */
