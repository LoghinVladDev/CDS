/*
 * Created by loghin on 04/09/22.
 */

#ifndef MUTABLE_COLLECTION_TEST_100_200_COMMON_H
#define MUTABLE_COLLECTION_TEST_100_200_COMMON_H

#include "MutableCollectionTest.h"
#include "MutableCollectionTest_common.hpp"


namespace {
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
}


#endif
