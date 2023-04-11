#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

#include <functional>

namespace {
    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __EqualsFunction       /* NOLINT(bugprone-reserved-identifier) */
    > auto composePredicate (
            __OtherIterableType const & other,
            __EqualsFunction    const & equals,
            bool                        onEquals
    ) -> std :: function < bool ( __ElementType const & ) > {

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
            Collection < __ElementType >    const & collection,
            Test                                                  * pTestLib,
            __OtherIterableType                             const & other,
            bool ( Collection < __ElementType > :: * collectionOperation ) ( __OtherIterableType const & ) const,
            bool ( Collection < __ElementType > :: * equivalentWithEquals ) ( __PredicateType const & ) const,
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

    /* CollectionTestGroup-ContainsOf-cpp-xx : CTG-00300-CO-cpp-xx. Tests CTC-00301-CO to CTC-30320-CO [-Collection/-InitializerList Groups] */
    template <
            typename __OtherIterableType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupContainsGroupByEquivalent (
            StringLiteral                                        groupName,
            Collection < __ElementType > const & collection,
            Test                                               * pTestLib,
            __OtherIterableType                          const & noneCommon,
            __OtherIterableType                          const & oneCommon,
            __OtherIterableType                          const & moreCommon,
            __OtherIterableType                          const & allCommon,
            __OtherIterableType                          const & allCommonAndMore
    ) -> bool {

        bool status = true;

        /* CollectionTestCase-ContainsOf-containsAnyOfCollectionNoneCommon-cpp-xx : CTC-00301-CO-containsAnyOfCollectionNoneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00301-CO-containsAnyOfCollectionNoneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                noneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        noneCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyOfCollectionOneCommon-cpp-xx : CTC-00302-CO-containsAnyOfCollectionOneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00302-CO-containsAnyOfCollectionOneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                oneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        oneCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyOfCollectionMoreCommon-cpp-xx : CTC-00303-CO-containsAnyOfCollectionMoreCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00303-CO-containsAnyOfCollectionMoreCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                moreCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        moreCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyOfCollectionAllCommon-cpp-xx : CTC-00304-CO-containsAnyOfCollectionAllCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00304-CO-containsAnyOfCollectionAllCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                allCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        allCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyOfCollectionAllCommonAndMore-cpp-xx : CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                allCommonAndMore,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        allCommonAndMore,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAllOfCollectionNoneCommon-cpp-xx : CTC-00306-CO-containsAllOfCollectionNoneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00306-CO-containsAllOfCollectionNoneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                noneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAllOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        noneCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAllOfCollectionOneCommon-cpp-xx : CTC-00307-CO-containsAllOfCollectionOneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00307-CO-containsAllOfCollectionOneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                oneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAllOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        oneCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAllOfCollectionMoreCommon-cpp-xx : CTC-00308-CO-containsAllOfCollectionMoreCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00308-CO-containsAllOfCollectionMoreCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                moreCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAllOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        moreCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAllOfCollectionAllCommon-cpp-xx : CTC-00309-CO-containsAllOfCollectionAllCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00309-CO-containsAllOfCollectionAllCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                allCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAllOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        allCommon,
                        cds::meta::equals < __ElementType >,
                        true
                )
        );

        /* CollectionTestCase-ContainsOf-containsAllOfCollectionAllCommonAndMore-cpp-xx : CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-cpp-xx. */
        auto containsAllOfCollectionAllCommonAndMoreStatus          = collection.containsAllOf ( allCommonAndMore );
        auto containsAllOfCollectionAllCommonAndMoreExpectedStatus  = false;
        if ( containsAllOfCollectionAllCommonAndMoreStatus != containsAllOfCollectionAllCommonAndMoreExpectedStatus ) {
            pTestLib->logError ( "'%s' failed", ( String ("CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-") + groupName + "-cpp-xx" ).cStr() );
            return false;
        }

        pTestLib->logOK ( "'%s' OK", ( String ("CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-") + groupName + "-cpp-xx" ).cStr() );

        /* CollectionTestCase-ContainsOf-containsAnyNotOfNoneCommon-cpp-xx : CTC-00311-CO-containsAnyNotOfNoneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00311-CO-containsAnyNotOfNoneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                noneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyNotOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        noneCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyNotOfOneCommon-cpp-xx : CTC-00312-CO-containsAnyNotOfOneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00312-CO-containsAnyNotOfOneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                oneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyNotOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        oneCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyNotOfMoreCommon-cpp-xx : CTC-00313-CO-containsAnyNotOfMoreCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00313-CO-containsAnyNotOfMoreCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                moreCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyNotOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        moreCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyNotOfAllCommon-cpp-xx : CTC-00314-CO-containsAnyNotOfAllCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00314-CO-containsAnyNotOfAllCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                allCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyNotOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        allCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsAnyNotOfAllCommonAndMore-cpp-xx : CTC-00315-CO-containsAnyNotOfAllCommonAndMore-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00315-CO-containsAnyNotOfAllCommonAndMore-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                allCommonAndMore,
                /* collectionOperation= */  & Collection < __ElementType > :: containsAnyNotOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: any,
                /* predicate= */            composePredicate < __ElementType > (
                        allCommonAndMore,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsNoneOfNoneCommon-cpp-xx : CTC-00316-CO-containsNoneOfNoneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00316-CO-containsNoneOfNoneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                noneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsNoneOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        noneCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsNoneOfOneCommon-cpp-xx : CTC-00317-CO-containsNoneOfOneCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00317-CO-containsNoneOfOneCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                oneCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsNoneOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        oneCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsNoneOfMoreCommon-cpp-xx : CTC-00318-CO-containsNoneOfMoreCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00318-CO-containsNoneOfMoreCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                moreCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsNoneOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        moreCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsNoneOfAllCommon-cpp-xx : CTC-00319-CO-containsNoneOfAllCommon-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00319-CO-containsNoneOfAllCommon-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                allCommon,
                /* collectionOperation= */  & Collection < __ElementType > :: containsNoneOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        allCommon,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        /* CollectionTestCase-ContainsOf-containsNoneOfAllCommonAndMore-cpp-xx : CTC-00320-CO-containsNoneOfAllCommonAndMore-cpp-xx. */
        status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
                /* caseName= */             ( String ("CTC-00320-CO-containsNoneOfAllCommonAndMore-") + groupName + "-cpp-xx" ).cStr(),
                /* collection= */           collection,
                /* pTestLib= */             pTestLib,
                /* other= */                allCommonAndMore,
                /* collectionOperation= */  & Collection < __ElementType > :: containsNoneOf,
                /* equivalentWithEquals= */ & Collection < __ElementType > :: all,
                /* predicate= */            composePredicate < __ElementType > (
                        allCommonAndMore,
                        cds::meta::equals < __ElementType >,
                        false
                )
        );

        return status;
    }

    /* CollectionTestGroup-RemoveAbsIt-cpp-xx : CTG-00350-RAIT-cpp-xx. CTC-00351-RAIT to CTC-00356-RAIT */
    template <
            typename __MemberType  /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupRemoveAbstractIterator (
            cds :: Collection < __MemberType >       & collection,
            Test                                                     * pTestLib,
            cds :: Collection < __MemberType > const & equivAfter1,
            cds :: Collection < __MemberType > const & equivAfter2,
            cds :: Collection < __MemberType > const & equivAfter3,
            cds :: Collection < __MemberType > const & equivAfter5,
            cds :: Collection < __MemberType > const & equivAfter6
    ) -> bool {

        pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );

        /* CollectionTestCase-RemoveAbsIt-removeAtFront-cpp-xx : CTC-00351-RAIT-removeAtFront-cpp-xx */
        auto       toRemoveAtFront = collection.begin();
        auto const resultToRemoveAtFront = collection.remove( toRemoveAtFront );
        auto const expectedResultToRemoveAtFront = true;
        pTestLib->log ( "object after 'removeAtFront' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter1.toString().cStr() );
        if ( resultToRemoveAtFront != expectedResultToRemoveAtFront || ! collection.equals ( equivAfter1 ) ) {
            pTestLib->logError( "'CTC-00351-RAIT-removeAtFront-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00351-RAIT-removeAtFront-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveAbsIt-removeInBounds-cpp-xx : CTC-00352-RAIT-removeInBounds-cpp-xx */
        auto       toRemoveInBounds = collection.begin();
        for ( uint32 i = 0; i * 2 < collection.size(); ++ i ) {
            ++ toRemoveInBounds;
        }

        auto const resultToRemoveAtInBounds = collection.remove( toRemoveInBounds );
        auto const expectedResultToRemoveAtInBounds = true;
        pTestLib->log ( "object after 'removeInBounds' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter2.toString().cStr() );
        if ( resultToRemoveAtInBounds != expectedResultToRemoveAtInBounds || ! collection.equals ( equivAfter2 ) ) {
            pTestLib->logError( "'CTC-00352-RAIT-removeInBounds-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00352-RAIT-removeInBounds-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveAbsIt-removeAtEnd-cpp-xx : CTC-00353-RAIT-removeAtEnd-cpp-xx */
        auto       toRemoveAtEnd = collection.begin();
        for ( uint32 i = 0; i + 1 < collection.size(); ++ i ) {
            ++ toRemoveAtEnd;
        }

        auto const resultToRemoveAtEnd = collection.remove( toRemoveAtEnd );
        auto const expectedResultToRemoveAtEnd = true;
        pTestLib->log ( "object after 'removeAtEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter3.toString().cStr() );
        if ( resultToRemoveAtEnd != expectedResultToRemoveAtEnd || ! collection.equals ( equivAfter3 ) ) {
            pTestLib->logError( "'CTC-00353-RAIT-removeAtEnd-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00353-RAIT-removeAtEnd-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveAbsIt-removeBeforeFront-cpp-xx : CTC-00354-RAIT-removeBeforeFront-cpp-xx : N/A */

        /* CollectionTestCase-RemoveAbsIt-removeAfterEnd-cpp-xx : CTC-00355-RAIT-removeAfterEnd-cpp-xx */
        auto       toRemoveAfterBack = collection.end();
        auto const resultToRemoveAfterEnd = collection.remove( toRemoveAfterBack );
        auto const expectedResultToRemoveAfterEnd = false;
        pTestLib->log ( "object after 'removeAfterEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
        if ( resultToRemoveAfterEnd != expectedResultToRemoveAfterEnd || ! collection.equals ( equivAfter5 ) ) {
            pTestLib->logError( "'CTC-00355-RAIT-removeAfterEnd-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00355-RAIT-removeAfterEnd-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveAbsIt-removeFromOther-cpp-xx : CTC-00355-RAIT-removeFromOther-cpp-xx */
        auto toRemoveFromSimilar = equivAfter2.begin();
        auto const resultToRemoveFromSimilar = collection.remove( toRemoveFromSimilar );
        auto const expectedResultToRemoveFromSimilar = false;
        pTestLib->log ( "object after 'removeFromOther' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
        if ( resultToRemoveFromSimilar != expectedResultToRemoveFromSimilar || ! collection.equals ( equivAfter6 ) ) {
            pTestLib->logError( "'CTC-00356-RAIT-removeFromOther-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00356-RAIT-removeFromOther-" __CDS_cpplang_core_version_name "' OK" );
        }

        return true;
    }

}

auto CollectionTest::tests_00300_00399 () noexcept -> bool {
    
    bool allOk = true;

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {


        cds :: Array < int > intArray = { 1, 2, 3, 4, 5 };

        cds :: Array < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: Array < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: Array < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: Array < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: Array < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < int > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        cds :: LinkedList < int > intLinkedList = { 1, 2, 3, 4, 5 };

        cds :: LinkedList < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: LinkedList < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: LinkedList < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: LinkedList < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: LinkedList < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < int > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntHashSet", [& allOk, this] {

        cds :: HashSet < int > intHashSet = { 1, 2, 3, 4, 5 };

        cds :: HashSet < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: HashSet < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: HashSet < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: HashSet < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: HashSet < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < int > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntTreeSet", [& allOk, this] {

        cds :: TreeSet < int > intTreeSet = { 1, 2, 3, 4, 5 };

        cds :: TreeSet < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: TreeSet < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: TreeSet < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: TreeSet < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: TreeSet < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < int > > (
                /* groupName= */        "Collection",
                /* collection= */       intTreeSet,
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < int > > (
                /* groupName= */        "InitializerList",
                /* collection= */       intTreeSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < int > intTreeSet = { 1, 2, 3, 4, 5 };

        cds :: LinkedHashSet < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: LinkedHashSet < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: LinkedHashSet < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: LinkedHashSet < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: LinkedHashSet < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < int > > (
                /* groupName= */        "Collection",
                /* collection= */       intTreeSet,
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < int > > (
                /* groupName= */        "InitializerList",
                /* collection= */       intTreeSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        cds :: HashMap < int, int > intToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: HashMap < int, int > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: HashMap < int, int > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: HashMap < int, int > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: HashMap < int, int > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: HashMap < int, int > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < MapEntry < int, int > > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [& allOk, this] {

        cds :: LinkedHashMap < int, int > intToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: LinkedHashMap < int, int > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: LinkedHashMap < int, int > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: LinkedHashMap < int, int > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: LinkedHashMap < int, int > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: LinkedHashMap < int, int > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < MapEntry < int, int > > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [& allOk, this] {

        cds :: TreeMap < int, int > intToIntTreeMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: TreeMap < int, int > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: TreeMap < int, int > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: TreeMap < int, int > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: TreeMap < int, int > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: TreeMap < int, int > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < MapEntry < int, int > > > (
                /* groupName= */        "Collection",
                /* collection= */       intToIntTreeMap,
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < MapEntry < int, int > > > (
                /* groupName= */        "InitializerList",
                /* collection= */       intToIntTreeMap,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        cds :: Array < String > StringArray = { 1, 2, 3, 4, 5 };

        cds :: Array < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: Array < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: Array < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: Array < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: Array < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < String > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        cds :: LinkedList < String > StringLinkedList = { 1, 2, 3, 4, 5 };

        cds :: LinkedList < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: LinkedList < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: LinkedList < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: LinkedList < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: LinkedList < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < String > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringHashSet", [& allOk, this] {

        cds :: HashSet < String > StringHashSet = { 1, 2, 3, 4, 5 };

        cds :: HashSet < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: HashSet < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: HashSet < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: HashSet < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: HashSet < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < String > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringTreeSet", [& allOk, this] {

        cds :: TreeSet < String > StringTreeSet = { 1, 2, 3, 4, 5 };

        cds :: TreeSet < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: TreeSet < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: TreeSet < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: TreeSet < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: TreeSet < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < String > > (
                /* groupName= */        "Collection",
                /* collection= */       StringTreeSet,
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < String > > (
                /* groupName= */        "InitializerList",
                /* collection= */       StringTreeSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < String > StringLinkedHashSet = { 1, 2, 3, 4, 5 };

        cds :: LinkedHashSet < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: LinkedHashSet < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: LinkedHashSet < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: LinkedHashSet < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: LinkedHashSet < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < String > > (
                /* groupName= */        "Collection",
                /* collection= */       StringLinkedHashSet,
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < String > > (
                /* groupName= */        "InitializerList",
                /* collection= */       StringLinkedHashSet,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringToIntHashMap", [& allOk, this] {

        cds :: HashMap < String, String > StringToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: HashMap < String, String > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: HashMap < String, String > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: HashMap < String, String > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: HashMap < String, String > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: HashMap < String, String > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < MapEntry < String, String > > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringToIntLinkedHashMap", [& allOk, this] {

        cds :: LinkedHashMap < String, String > StringToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: LinkedHashMap < String, String > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: LinkedHashMap < String, String > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: LinkedHashMap < String, String > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: LinkedHashMap < String, String > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: LinkedHashMap < String, String > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < MapEntry < String, String > > > (
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-" __CDS_cpplang_core_version_name " : CTG-00300-CO-" __CDS_cpplang_core_version_name " : StringToIntTreeMap", [& allOk, this] {

        cds :: TreeMap < String, String > StringToIntTreeMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: TreeMap < String, String > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: TreeMap < String, String > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: TreeMap < String, String > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: TreeMap < String, String > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: TreeMap < String, String > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < Iterable < MapEntry < String, String > > > (
                /* groupName= */        "Collection",
                /* collection= */       StringToIntTreeMap,
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

        /* CTC-00301-C0-InitializerList-cpp-xx */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < std :: initializer_list < MapEntry < String, String > > > (
                /* groupName= */        "InitializerList",
                /* collection= */       StringToIntTreeMap,
                /* pTestLib= */         this,
                /* noneCommon= */       noneCommonList,
                /* oneCommon= */        oneCommonList,
                /* moreCommon= */       moreCommonList,
                /* allCommon= */        allCommonList,
                /* allCommonAndMore= */ allCommonAndMoreList
        );
    });

#endif

    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < int > & underTestColl = underTest;

        cds :: Array < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Array < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: Array < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < int > & underTestColl = underTest;

        cds :: LinkedList < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedList < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedList < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntHashSet", [this, & allOk]{

        cds :: HashSet < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < int > & underTestColl = underTest;

        cds :: HashSet < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: HashSet < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: HashSet < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: HashSet < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: HashSet < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntTreeSet", [this, & allOk]{

        cds :: TreeSet < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < int > & underTestColl = underTest;

        cds :: TreeSet < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: TreeSet < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: TreeSet < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: TreeSet < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: TreeSet < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [this, & allOk]{

        cds :: LinkedHashSet < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < int > & underTestColl = underTest;

        cds :: LinkedHashSet < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedHashSet < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedHashSet < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedHashSet < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedHashSet < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: Collection < MapEntry < int, int > > & underTestColl = underTest;

        cds :: HashMap < int, int > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: HashMap < int, int > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: HashMap < int, int > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: HashMap < int, int > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: HashMap < int, int > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: Collection < MapEntry < int, int > > & underTestColl = underTest;

        cds :: LinkedHashMap < int, int > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: LinkedHashMap < int, int > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: LinkedHashMap < int, int > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: LinkedHashMap < int, int > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: LinkedHashMap < int, int > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, & allOk]{

        cds :: TreeMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: Collection < MapEntry < int, int > > & underTestColl = underTest;

        cds :: TreeMap < int, int > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: TreeMap < int, int > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: TreeMap < int, int > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: TreeMap < int, int > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: TreeMap < int, int > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < String > & underTestColl = underTest;

        cds :: Array < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Array < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: Array < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < String > & underTestColl = underTest;

        cds :: LinkedList < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedList < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedList < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringHashSet", [this, & allOk]{

        cds :: HashSet < String > underTest = { 4, 5, 6, 7, 8, 9, 1, 2, 3 }; /** by hash order */
        cds :: Collection < String > & underTestColl = underTest;

        cds :: HashSet < String > afterFrontRemove = { 5, 6, 7, 8, 9, 1, 2, 3 };
        cds :: HashSet < String > afterMidRemove = { 5, 6, 7, 8, 1, 2, 3 };
        cds :: HashSet < String > afterBackRemove = { 5, 6, 7, 8, 1, 2 };
        cds :: HashSet < String > afterAfterBackRemove = { 5, 6, 7, 8, 1, 2 };
        cds :: HashSet < String > afterOtherRemove = { 5, 6, 7, 8, 1, 2 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringTreeSet", [this, & allOk]{

        cds :: TreeSet < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < String > & underTestColl = underTest;

        cds :: TreeSet < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: TreeSet < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: TreeSet < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: TreeSet < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: TreeSet < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [this, & allOk]{

        cds :: LinkedHashSet < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Collection < String > & underTestColl = underTest;

        cds :: LinkedHashSet < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedHashSet < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedHashSet < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedHashSet < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedHashSet < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > underTest = { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        cds :: Collection < MapEntry < String, String > > & underTestColl = underTest;

        cds :: HashMap < String, String > afterFrontRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3},  };
        cds :: HashMap < String, String > afterMidRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2}, {3, 3} };
        cds :: HashMap < String, String > afterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: HashMap < String, String > afterAfterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: HashMap < String, String > afterOtherRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: Collection < MapEntry < String, String > > & underTestColl = underTest;

        cds :: LinkedHashMap < String, String > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: LinkedHashMap < String, String > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: LinkedHashMap < String, String > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: LinkedHashMap < String, String > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: LinkedHashMap < String, String > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

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
    this->executeSubtest ( "CollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : CTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [this, & allOk]{

        cds :: TreeMap < String, String > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: Collection < MapEntry < String, String > > & underTestColl = underTest;

        cds :: TreeMap < String, String > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: TreeMap < String, String > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: TreeMap < String, String > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: TreeMap < String, String > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: TreeMap < String, String > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

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

    return allOk;
}
