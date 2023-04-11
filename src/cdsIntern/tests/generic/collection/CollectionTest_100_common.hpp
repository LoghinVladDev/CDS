#ifndef COLLECTION_TEST_100_COMMON_H
#define COLLECTION_TEST_100_COMMON_H

#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

namespace {
    template <
            typename __PredicateReturnType, /* NOLINT(bugprone-reserved-identifier) */
            typename __MemberType,          /* NOLINT(bugprone-reserved-identifier) */
            typename __Predicate            /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestCasePredicateHandle (
            StringLiteral testCaseName,
            Collection < __MemberType > const & collection,
            Test                                              * pTestLib,
            auto ( Collection < __MemberType > :: * pFunctionalCall ) ( __Predicate const & ) const -> __PredicateReturnType,
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
            Collection < __MemberType > const & collection,
            Test                                              * pTestLib,
            auto ( Collection < __MemberType > :: * pFunctionalCall ) ( Size, __Predicate const & ) const -> __PredicateReturnType,
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


#endif /* COLLECTION_TEST_100_COMMON_H */
