//
// Created by loghin on 30.11.2021.
//

#include "CollectionTest.h"

#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>
#include <CDS/experimental/HashSet>
#include <CDS/experimental/HashMap>

/* CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20. Tests CTC-00003 to CTC-00016 */
template <
        typename __MemberType // NOLINT(bugprone-reserved-identifier)
> auto collectionTestGroupMemberFunctions (
        cds :: experimental :: Collection < __MemberType >        & collection,
        Test                                                      * pTestLib,
        String                                              const & expectedToString,
        Size                                                        expectedSize,
        __MemberType                                        const & toBeFound,
        __MemberType                                        const & toNotBeFound,
        Size                                                        expectedHash,
        cds :: Object                                       const & equalSameType,
        cds :: Object                                       const & equalDifferentType,
        cds :: Object                                       const & notEqualSameType,
        cds :: Object                                       const & notEqualDifferentType,
        cds :: Object                                       const & notEqualNonCollection
) -> bool {

    pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );


    /* CollectionTestCase-MemberFunctions-toString-CPP20 : CTC-00003-MF-toString-CPP20 */
    auto asString = collection.toString();
    pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
    if ( asString != expectedToString ) {
        pTestLib->logError ( "'CTC-00003-MF-toString-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00003-MF-toString-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-size-CPP20 : CTC-00004-MF-size-CPP20 */
    auto size = collection.size();
    pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, expectedSize );
    if ( size != expectedSize ) {
        pTestLib->logError( "'CTC-00004-MF-size-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00004-MF-size-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-empty-CPP20 : CTC-00005-MF-empty-CPP20 */
    auto empty = collection.empty();
    pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( empty != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CTC-00005-MF-empty-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00005-MF-empty-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-boolCast-CPP20 : CTC-00006-MF-boolCast-CPP20 */
    auto boolCast = static_cast < bool > ( collection.empty() );
    pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( boolCast != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CTC-00006-MF-boolCast-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00006-MF-boolCast-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-containsTrue-CPP20 : CTC-00007-MF-containsTrue-CPP20 */
    auto containsTrue = collection.contains ( toBeFound );
    pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "true" );
    if ( ! containsTrue ) {
        pTestLib->logError( "'CTC-00007-MF-containsTrue-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00007-MF-containsTrue-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-containsFalse-CPP20 : CTC-00008-MF-containsFalse-CPP20 */
    auto containsFalse = collection.contains ( toNotBeFound );
    pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
    if ( containsFalse ) {
        pTestLib->logError( "'CTC-00008-MF-containsFalse-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00008-MF-containsFalse-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-hash-CPP20 : CTC-00009-MF-hash-CPP20 */
    auto hash = collection.hash();
    pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, expectedHash );
    if ( hash != expectedHash ) {
        pTestLib->logError( "'CTC-00009-MF-hash-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00009-MF-hash-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsSelf-CPP20 : CTC-00011-MF-equalsSelf-CPP20 */
    auto equalsToSelf = collection.equals ( collection );
    pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
    if ( ! equalsToSelf ) {
        pTestLib->logError( "'CTC-00011-MF-equalsSelf-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00011-MF-equalsSelf-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsTrueSameType-CPP20 : CTC-00012-MF-equalsTrueSameType-CPP20 */
    auto equalsToEqualSameType = collection.equals ( equalSameType );
    pTestLib->log ( "object 'equals to equal, same type' : '%s', expected 'equals to equal, same type' : '%s'", equalsToEqualSameType ? "true" : "false", "true" );
    if ( ! equalsToEqualSameType ) {
        pTestLib->logError( "'CTC-00012-MF-equalsTrueSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00012-MF-equalsTrueSameType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsTrueDifferentType-CPP20 : CTC-00013-MF-equalsTrueDifferentType-CPP20 */
    auto equalsToEqualDiffType = collection.equals ( equalDifferentType );
    pTestLib->log ( "object 'equals to equal, different type' : '%s', expected 'equals to equal, different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "true" );
    if ( ! equalsToEqualDiffType ) {
        pTestLib->logError( "'CTC-00013-MF-equalsTrueDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00013-MF-equalsTrueDifferentType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsFalseSameType-CPP20 : CTC-00014-MF-equalsFalseSameType-CPP20 */
    auto notEqualsToSameType = collection.equals ( notEqualSameType );
    pTestLib->log ( "object 'equals to not equal, same type' : '%s', expected 'equals to not equal, same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
    if ( notEqualsToSameType ) {
        pTestLib->logError( "'CTC-00014-MF-equalsFalseSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00014-MF-equalsFalseSameType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsFalseDifferentType-CPP20 : CTC-00015-MF-equalsFalseDifferentType-CPP20 */
    auto notEqualsToDifferentType = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, different type' : '%s', expected 'equals to not equal, different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
    if ( notEqualsToDifferentType ) {
        pTestLib->logError( "'CTC-00015-MF-equalsFalseDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00015-MF-equalsFalseDifferentType-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-equalsFalseNotCollection-CPP20 : CTC-00016-MF-equalsFalseNotCollection-CPP20 */
    auto notEqualsToOtherObject = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, not collection' : '%s', expected 'equals to not equal, not collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );
    if ( notEqualsToOtherObject ) {
        pTestLib->logError( "'CTC-00016-MF-equalsFalseNotCollection-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00016-MF-equalsFalseNotCollection-CPP20' OK" );
    }

    /* CollectionTestCase-MemberFunctions-clear-CPP20 : CTC-00010-MF-clear-CPP20 */
    collection.clear();

    empty                       = collection.empty();
    boolCast                    = static_cast < bool > ( collection.empty() );
    size                        = collection.size();
    hash                        = collection.hash();
    containsTrue                = collection.contains( toBeFound );
    containsFalse               = collection.contains( toNotBeFound );
    asString                    = collection.toString();
    equalsToSelf                = collection.equals ( collection );
    equalsToEqualSameType       = collection.equals ( equalSameType );
    equalsToEqualDiffType       = collection.equals ( equalDifferentType );
    notEqualsToSameType         = collection.equals ( notEqualSameType );
    notEqualsToDifferentType    = collection.equals ( notEqualDifferentType );
    notEqualsToOtherObject      = collection.equals ( notEqualNonCollection );

    pTestLib->log ( "Object Cleared using 'clear'. Re-execution after clear : " );
    pTestLib->log ( "object 'toString' : '%s'. potential expected 'toString' : '%s'", asString.cStr(), "[]" );
    pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, 0ULL );
    pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", "true" );
    pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", "true" );
    pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "false" );
    pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
    pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, 0ULL );
    pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
    pTestLib->log ( "object 'equals to equal same type' : '%s', expected 'equals to equal same type' : '%s'", equalsToEqualSameType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to equal different type' : '%s', expected 'equals to equal different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to not equal same type' : '%s', expected 'equals to not equal same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to not equal different type' : '%s', expected 'equals to not equal different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to non-collection' : '%s', expected 'equals to non-collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );

    if ( asString.length() > 2ULL ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - toString' failed" );
        return false;
    } else if ( size != 0ULL ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - size' failed" );
        return false;
    } else if ( ! empty ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - empty' failed" );
        return false;
    } else if ( ! boolCast ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - bool cast' failed" );
        return false;
    } else if ( containsTrue || containsFalse ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - contains' failed" );
        return false;
    } else if ( hash != 0ULL ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - hash' failed" );
        return false;
    } else if ( ! equalsToSelf ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToSelf' failed" );
        return false;
    } else if ( equalsToEqualSameType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToEqualSameTypePrevToClear' failed" );
        return false;
    } else if ( equalsToEqualDiffType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToEqualDiffTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToSameType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToNotEqualSameTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToDifferentType ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToNotEqualDiffTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToOtherObject ) {
        pTestLib->logError( "'CTC-00010-MF-clear-CPP20 - equalsToNotEqualOtherObj' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00010-MF-clear-CPP20' OK" );
    }


    return true;
}

template <
        typename __T,
        typename __ItType,
        typename __LastArg
> auto fwdCheckIterator (
        __ItType const & cur,
        __ItType const & end,
        __LastArg const & lastE
) {

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
        typename __T,
        typename __ItType,
        typename __CurrArg,
        typename ... __RemainingArgs
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


/// INVALID, REUSE IN DERIVED TESTS - ARRAY, ETC.
///* CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20. Tests CTC-00051 to CTC-00056 */
//template <
//        typename __MemberType,                              // NOLINT(bugprone-reserved-identifier)
//        typename __CollectionType,                          // NOLINT(bugprone-reserved-identifier)
//        typename ... __OrderedValues                        // NOLINT(bugprone-reserved-identifier)
//> auto collectionTestGroupDelegateForwardConstIterableClientImports (
//        Test                  *     pTestLib,
//        __OrderedValues const & ... orderedValues
//) -> bool {
//
//    __CollectionType collection;
//    collection.insertAll ( orderedValues ... );
//
//
//    pTestLib->log ( "Object under test, to be iterated : '%s'", collection.toString().cStr() );
//
//    /* CollectionTestCase-DelegateForwardConstIterableClientImports-range-CPP20 : CTC-00051-IT-range-CPP20 */
//    pTestLib->log ( "Standard iteration : " );
//    for ( auto e : collection ) {
//        std :: stringstream oss;
//        cds :: streamPrint ( oss, e );
//        pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
//    }
//
//    /* CollectionTestCase-DelegateForwardConstIterableClientImports-begin_endIteration-CPP20 : CTC-00052-IT-begin_end-CPP20 */
//    auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
//    if ( ! stdIterResult ) {
//        pTestLib->logError( "'CTC-00052-IT-begin_end-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00052-IT-begin_end-CPP20' OK" );
//    }
//
//    /* CollectionTestCase-DelegateForwardConstIterableClientImports-cbegin_cendIteration-CPP20 : CTC-00053-IT-cbegin_cend-CPP20 */
//    auto stdCIterResult = fwdCheckIterator < __MemberType > ( collection.cbegin(), collection.cend(), orderedValues ... );
//    if ( ! stdCIterResult ) {
//        pTestLib->logError( "'CTC-00053-IT-cbegin_cend-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00053-IT-cbegin_cend-CPP20' OK" );
//    }
//
//    collection.clear();
//
//    /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptybegin_end-CPP20 : CTC-00054-IT-e_begin_end-CPP20 */
//    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
//        pTestLib->logError( "'CTC-00054-IT-e_begin_end-CPP20' failed" );
//        return false;
//    }
//
//    pTestLib->logOK ( "'CTC-00054-IT-e_begin_end-CPP20' OK" );
//
//    /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptycbegin_cend-CPP20 : CTC-00055-IT-e_cbegin_cend-CPP20 */
//    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
//        pTestLib->logError( "'CTC-00055-IT-e_cbegin_cend-CPP20' failed" );
//        return false;
//    }
//
//    pTestLib->logOK ( "'CTC-00055-IT-e_cbegin_cend-CPP20' OK" );
//
//    /* CollectionTestCase-DelegateForwardConstIterableClientImports-e_emptyRange-CPP20 : CTC-00056-IT-e_emptyRange-CPP20 */
//    for ( auto e : collection ) {
//        pTestLib->logError( "'CTC-00056-IT-e_emptyRange-CPP20' failed" );
//        return false;
//    }
//
//    pTestLib->logOK ( "'CTC-00056-IT-e_emptyRange-CPP20' OK" );
//
//    return true;
//}

/* CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20. Tests CTC-00051 to CTC-00056 */
template <
        typename __MemberType,                              // NOLINT(bugprone-reserved-identifier)
        typename ... __OrderedValues                        // NOLINT(bugprone-reserved-identifier)
> auto collectionTestGroupDelegateForwardConstIterableClientImports (
        experimental :: Collection < __MemberType > & collection,
        Test                  *     pTestLib,
        __OrderedValues const & ... orderedValues
) -> bool {

    pTestLib->log ( "Object under test, to be iterated : '%s'", collection.toString().cStr() );

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-range-CPP20 : CTC-00051-IT-range-CPP20 */
    pTestLib->log ( "Standard iteration : " );
    for ( auto e : collection ) {
        std :: stringstream oss;
        cds :: streamPrint ( oss, e );
        pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
    }

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-begin_endIteration-CPP20 : CTC-00052-IT-begin_end-CPP20 */
    auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
    if ( ! stdIterResult ) {
        pTestLib->logError( "'CTC-00052-IT-begin_end-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00052-IT-begin_end-CPP20' OK" );
    }

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-cbegin_cendIteration-CPP20 : CTC-00053-IT-cbegin_cend-CPP20 */
    auto stdCIterResult = fwdCheckIterator < __MemberType > ( collection.cbegin(), collection.cend(), orderedValues ... );
    if ( ! stdCIterResult ) {
        pTestLib->logError( "'CTC-00053-IT-cbegin_cend-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00053-IT-cbegin_cend-CPP20' OK" );
    }

    collection.clear();

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptybegin_end-CPP20 : CTC-00054-IT-e_begin_end-CPP20 */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'CTC-00054-IT-e_begin_end-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00054-IT-e_begin_end-CPP20' OK" );

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptycbegin_cend-CPP20 : CTC-00055-IT-e_cbegin_cend-CPP20 */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'CTC-00055-IT-e_cbegin_cend-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00055-IT-e_cbegin_cend-CPP20' OK" );

    /* CollectionTestCase-DelegateForwardConstIterableClientImports-e_emptyRange-CPP20 : CTC-00056-IT-e_emptyRange-CPP20 */
    for ( auto e : collection ) {
        pTestLib->logError( "'CTC-00056-IT-e_emptyRange-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00056-IT-e_emptyRange-CPP20' OK" );

    return true;
}

template <
        typename __PredicateReturnType,
        typename __MemberType,
        typename __Predicate
> auto collectionTestCasePredicateHandle (
        StringLiteral testCaseName,
        experimental :: Collection < __MemberType > const & collection,
        Test                                              * pTestLib,
        auto ( experimental :: Collection < __MemberType > :: * pFunctionalCall ) ( __Predicate const & ) const -> __PredicateReturnType,
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
        typename __PredicateReturnType,
        typename __MemberType,
        typename __Predicate
> auto collectionTestCasePredicateCountedHandle (
        StringLiteral testCaseName,
        experimental :: Collection < __MemberType > const & collection,
        Test                                              * pTestLib,
        auto ( experimental :: Collection < __MemberType > :: * pFunctionalCall ) ( Size, __Predicate const & ) const -> __PredicateReturnType,
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

template <
        typename __ElementType,
        typename __OtherIterableType,
        typename __EqualsFunction
> auto composePredicate (
        __OtherIterableType const & other,
        __EqualsFunction    const & equals,
        bool                        onEquals
) {

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
        typename __OtherIterableType,
        typename __ElementType,
        typename __PredicateType
> auto collectionTestCaseContainsWithEquivalent (
        StringLiteral                                           caseName,
        experimental :: Collection < __ElementType >    const & collection,
        Test                                                  * pTestLib,
        __OtherIterableType                             const & other,
        bool ( experimental :: Collection < __ElementType > :: * collectionOperation ) ( __OtherIterableType const & ) const,
        bool ( experimental :: Collection < __ElementType > :: * equivalentWithEquals ) ( __PredicateType const & ) const,
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

/* CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20. Tests CTC-00301-CO to CTC-30320-CO [-Collection/-InitializerList Groups] */
template <
        typename __OtherIterableType,
        typename __ElementType
> auto collectionTestGroupContainsGroupByEquivalent (
        StringLiteral                                        groupName,
        experimental :: Collection < __ElementType > const & collection,
        Test                                               * pTestLib,
        __OtherIterableType                          const & noneCommon,
        __OtherIterableType                          const & oneCommon,
        __OtherIterableType                          const & moreCommon,
        __OtherIterableType                          const & allCommon,
        __OtherIterableType                          const & allCommonAndMore
) -> bool {

    bool status = true;

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionNoneCommon-CPP20 : CTC-00301-CO-containsAnyOfCollectionNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00301-CO-containsAnyOfCollectionNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionOneCommon-CPP20 : CTC-00302-CO-containsAnyOfCollectionOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00302-CO-containsAnyOfCollectionOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionMoreCommon-CPP20 : CTC-00303-CO-containsAnyOfCollectionMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00303-CO-containsAnyOfCollectionMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionAllCommon-CPP20 : CTC-00304-CO-containsAnyOfCollectionAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00304-CO-containsAnyOfCollectionAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyOfCollectionAllCommonAndMore-CPP20 : CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommonAndMore,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommonAndMore,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionNoneCommon-CPP20 : CTC-00306-CO-containsAllOfCollectionNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00306-CO-containsAllOfCollectionNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionOneCommon-CPP20 : CTC-00307-CO-containsAllOfCollectionOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00307-CO-containsAllOfCollectionOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionMoreCommon-CPP20 : CTC-00308-CO-containsAllOfCollectionMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00308-CO-containsAllOfCollectionMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionAllCommon-CPP20 : CTC-00309-CO-containsAllOfCollectionAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00309-CO-containsAllOfCollectionAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAllOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    true
            )
    );

    /* CollectionTestCase-ContainsOf-containsAllOfCollectionAllCommonAndMore-CPP20 : CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-CPP20. */
    auto containsAllOfCollectionAllCommonAndMoreStatus          = collection.containsAllOf ( allCommonAndMore );
    auto containsAllOfCollectionAllCommonAndMoreExpectedStatus  = false;
    if ( containsAllOfCollectionAllCommonAndMoreStatus != containsAllOfCollectionAllCommonAndMoreExpectedStatus ) {
        pTestLib->logError ( "'%s' failed", ( String ("CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-") + groupName + "-CPP20" ).cStr() );
        return false;
    }

    pTestLib->logOK ( "'%s' OK", ( String ("CTC-00310-CO-containsAllOfCollectionAllCommonAndMore-") + groupName + "-CPP20" ).cStr() );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfNoneCommon-CPP20 : CTC-00311-CO-containsAnyNotOfNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00311-CO-containsAnyNotOfNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfOneCommon-CPP20 : CTC-00312-CO-containsAnyNotOfOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00312-CO-containsAnyNotOfOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfMoreCommon-CPP20 : CTC-00313-CO-containsAnyNotOfMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00313-CO-containsAnyNotOfMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfAllCommon-CPP20 : CTC-00314-CO-containsAnyNotOfAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00314-CO-containsAnyNotOfAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsAnyNotOfAllCommonAndMore-CPP20 : CTC-00315-CO-containsAnyNotOfAllCommonAndMore-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00315-CO-containsAnyNotOfAllCommonAndMore-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommonAndMore,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsAnyNotOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: any,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommonAndMore,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfNoneCommon-CPP20 : CTC-00316-CO-containsNoneOfNoneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00316-CO-containsNoneOfNoneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                noneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    noneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfOneCommon-CPP20 : CTC-00317-CO-containsNoneOfOneCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00317-CO-containsNoneOfOneCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                oneCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    oneCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfMoreCommon-CPP20 : CTC-00318-CO-containsNoneOfMoreCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00318-CO-containsNoneOfMoreCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                moreCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    moreCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfAllCommon-CPP20 : CTC-00319-CO-containsNoneOfAllCommon-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00319-CO-containsNoneOfAllCommon-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommon,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommon,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    /* CollectionTestCase-ContainsOf-containsNoneOfAllCommonAndMore-CPP20 : CTC-00320-CO-containsNoneOfAllCommonAndMore-CPP20. */
    status = status && collectionTestCaseContainsWithEquivalent < __OtherIterableType > (
            /* caseName= */             ( String ("CTC-00320-CO-containsNoneOfAllCommonAndMore-") + groupName + "-CPP20" ).cStr(),
            /* collection= */           collection,
            /* pTestLib= */             pTestLib,
            /* other= */                allCommonAndMore,
            /* collectionOperation= */  & experimental :: Collection < __ElementType > :: containsNoneOf,
            /* equivalentWithEquals= */ & experimental :: Collection < __ElementType > :: all,
            /* predicate= */            composePredicate < __ElementType > (
                    allCommonAndMore,
                    meta :: equals < __ElementType >,
                    false
            )
    );

    return status;
}

/* CollectionTestSuite-CPP20 : CTS-00001-CPP20 */
auto CollectionTest :: execute () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntArray", [& allOk, this] {

        cds :: experimental :: Array < int > intArrayObjectUnderTest;
        intArrayObjectUnderTest     = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
        ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: Array < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: Array < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: LinkedList < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intArrayObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < int > intLinkedListObjectUnderTest;
        intLinkedListObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: Array < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: LinkedList < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: Array < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intLinkedListObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < int > intHashSetObjectUnderTest;
        intHashSetObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: HashSet < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: HashSet < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intHashSetObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < int, int > intIntHashMapObjectUnderTest;
        intIntHashMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 2, 7 );
        auto expectedToBeNotFound   = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 6, 20 );
        auto expectedHash           = ((((
                                                 ( cds :: hash (1) ^ cds :: hash (6) ) * 31 + ( cds :: hash ( 2 ) ^ cds :: hash (7))
                                         ) * 31 + ( cds :: hash ( 3 )) ^ cds :: hash (8)) * 31 + ( cds :: hash ( 4 ) ^ cds :: hash (9)) ) * 31 + ( cds :: hash ( 5 )) ^ cds :: hash (10));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto equalDifferentType     = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto notEqualSameType       = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualDifferentType  = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions (
                intIntHashMapObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringArray", [& allOk, this] {

        cds :: experimental :: Array < cds :: String > stringArrayObjectUnderTest;
        stringArrayObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
        ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: Array < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: Array < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringArrayObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < cds :: String > stringLinkedListObjectUnderTest;
        stringLinkedListObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: Array < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: Array < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringLinkedListObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < cds :: String > stringHashSetObjectUnderTest;
        stringHashSetObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "{ are, Ana, mere }"; /// due to hash table
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "are" ) * 31 + cds :: hash ( "Ana" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringHashSetObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringToStringHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < cds :: String, cds :: String > stringStringHashMapObjectUnderTest;
        stringStringHashMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ are: verb, Ana: name, mere: noun }"; /// due to hash table
        auto expectedSize           = 3;
        auto expectedToBeFound      = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "are", "verb" );
        auto expectedToBeNotFound   = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "pere", "noun" );
        auto expectedHash           = (
                                               (( cds :: hash ("are") ^ cds :: hash ("verb") ) * 31 + ( cds :: hash ( "Ana" ) ^ cds :: hash ("name")))
                                          * 31 + ( cds :: hash ( "mere" ) ^ cds :: hash ("noun")));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto equalDifferentType     = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto notEqualSameType       = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "pere", "noun" } };
        auto notEqualDifferentType  = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "other" } };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions < cds :: MapEntry < cds :: String, cds :: String > > (
                stringStringHashMapObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });


    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntArray", [& allOk, this] {

        cds :: experimental :: Array < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : IntToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < int, int > objUnderTest = {{3,4}, {4,5}, {5,6}, {6,7}, {7,8}};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < MapEntry < int, int > > (
                objUnderTest,
                this,
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
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringArray", [& allOk, this] {

        cds :: experimental :: Array < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < String > objUnderTest = {"are", "Ana", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "are", "Ana", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-CPP20 : CTG-00050-IT-CPP20 : StringToStringHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < String, String > objUnderTest = {{"are","verb"}, {"Ana","name"}, {"mere","noun"}};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < MapEntry < String, String > > (
                objUnderTest,
                this,
                MapEntry < String, String > { "are", "verb" },
                MapEntry < String, String > { "Ana", "name" },
                MapEntry < String, String > { "mere", "noun" }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-SpecialAddressBasedIteratorAccess-CPP20 : CTG-00050-IT-CPP20 : StringArray", [& allOk, this] {

        /* only one test required, as it uses operator *, which was tested in previous group */
        cds :: experimental :: Array < String > arr = { "Ana", "are", "mere" };
        cds :: experimental :: Collection < String > & c = arr;
        auto begin = c.begin();

        /* CollectionTestCase-SpecialAddressBasedIteratorAccess-addressOperator-CPP20 : CTC-00057-IT-addressOperator-CPP20 */
        auto expectedLen = 3;
        auto len = begin->length();

        this->log ( "iterator '-> operator length' : '%llu', expected '-> operator length' : '%llu'", len, expectedLen );
        if ( expectedLen != len ) {
            this->logError ( "'CTC-00057-IT-addressOperator-CPP20' error" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00057-IT-addressOperator-CPP20' OK" );
        }
    });


    /* CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 - Tests CTC-00101-FS to CTC-10139-FS - located directly below due to varability of these tests */
    /* IntArray */              this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntArray */
        cds :: experimental :: Array < int > fs139 = { 1, 2, 3, 4, 5 };
        experimental :: Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* IntLinkedList */         this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntLinkedList", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntLinkedList */
        cds :: experimental :: LinkedList < int > fs139 = { 1, 2, 3, 4, 5 };
        experimental :: Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* IntHashSet */            this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: any,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: all,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: none,
                /* predicate */     [] (int e) -> bool { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntHashSet */
        cds :: experimental :: HashSet < int > fs139 = { 1, 2, 3, 4, 5 };
        experimental :: Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* IntToIntHashMap */       this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : IntToIntHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs101 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs102 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs103 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs104 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs105 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs106 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs107 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs108 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs109 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs110 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {8, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs111 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs112 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs113 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs114 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs115 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs116 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs117 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: count,
                /* predicate */     [comparedTo] (auto e) -> bool { return e.key() > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs118 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs119 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs120 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs121 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs122 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs123 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs124 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs125 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs126 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs127 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs128 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs129 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs130 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs131 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs132 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs133 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs134 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs135 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs136 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs137 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs138 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (auto e) -> bool { return e.key() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : IntToIntHashMap */
        cds :: experimental :: HashMap < int, int > fs139 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        experimental :: Collection < MapEntry < int, int > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( auto e ) { if ( e.key() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringArray */           this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) -> bool { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringArray */
        cds :: experimental :: Array < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        experimental :: Collection < String > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringLinkedList */      this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringLinkedList", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) -> bool { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringLinkedList */
        cds :: experimental :: LinkedList < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        experimental :: Collection < String > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringHashSet */         this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [] (String const & e) -> bool { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) -> bool { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     [] (String const & e) -> bool { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringHashSet */
        cds :: experimental :: HashSet < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        experimental :: Collection < String > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });
    /* StringToStringHashMap */ this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-CPP20 : CTG-00100-FS-CPP20 : StringToStringHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-CPP20 : CTC-00101-FS-anyNone-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs101 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-CPP20",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-CPP20 : CTC-00102-FS-anyOne-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs102 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-CPP20",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-CPP20 : CTC-00103-FS-anyMore-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs103 = { {"x", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-CPP20",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-CPP20 : CTC-00104-FS-anyAll-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs104 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-CPP20",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-CPP20 : CTC-00105-FS-allNone-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs105 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-CPP20",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-CPP20 : CTC-00106-FS-allOne-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs106 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-CPP20",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-CPP20 : CTC-00107-FS-allMore-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs107 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-CPP20",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-CPP20 : CTC-00108-FS-allAll-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs108 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-CPP20",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-CPP20 : CTC-00109-FS-noneNone-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs109 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-CPP20",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-CPP20 : CTC-00110-FS-noneOne-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs110 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-CPP20",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-CPP20 : CTC-00111-FS-noneMore-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs111 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-CPP20",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-CPP20 : CTC-00112-FS-noneAll-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs112 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-CPP20",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-CPP20 : CTC-00113-FS-countProp1-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs113 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-CPP20",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-CPP20 : CTC-00114-FS-countProp2-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs114 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-CPP20",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-CPP20 : CTC-00115-FS-countProp3-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs115 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-CPP20",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-CPP20 : CTC-00116-FS-countProp4-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs116 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-CPP20",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (auto e) -> bool { return e.key().length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-CPP20 : CTC-00117-FS-countPropLbd-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs117 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-CPP20",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: count,
                /* predicate */     [comparedTo] (auto e) -> bool { return e.key().length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-CPP20 : CTC-00118-FS-fewerThanTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs118 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-CPP20",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-CPP20 : CTC-00119-FS-fewerThanCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs119 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-CPP20",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-CPP20 : CTC-00120-FS-fewerThanCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs120 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-CPP20",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-CPP20 : CTC-00121-FS-fewerThanFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs121 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-CPP20",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-CPP20 : CTC-00122-FS-fewerThanCompletelyFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs122 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-CPP20 : CTC-00123-FS-moreThanTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs123 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-CPP20",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-CPP20 : CTC-00124-FS-moreThanCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs124 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-CPP20",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-CPP20 : CTC-00125-FS-moreThanCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs125 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-CPP20",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-CPP20 : CTC-00126-FS-moreThanFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs126 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-CPP20",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-CPP20 : CTC-00127-FS-moreThanCompletelyFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs127 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-CPP20",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-CPP20 : CTC-00128-FS-atMostTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs128 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-CPP20",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-CPP20 : CTC-00129-FS-atMostCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs129 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-CPP20",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-CPP20 : CTC-00130-FS-atMostCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs130 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-CPP20",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-CPP20 : CTC-00131-FS-atMostFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs131 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-CPP20",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-CPP20 : CTC-00132-FS-atLeastTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs132 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-CPP20",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-CPP20 : CTC-00133-FS-atLeastCloseTrue-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs133 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-CPP20",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-CPP20 : CTC-00134-FS-atLeastCloseFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs134 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-CPP20",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-CPP20 : CTC-00135-FS-atLeastFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs135 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-CPP20",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (auto e) -> bool { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-CPP20 : CTC-00136-FS-someExact-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs136 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-CPP20",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-CPP20 : CTC-00137-FS-someLessFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs137 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-CPP20",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-CPP20 : CTC-00138-FS-someMoreFalse-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs138 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-CPP20",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (auto e) -> bool { return e.key().length() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-CPP20 : CTC-00139-FS-forEachCount-CPP20 : StringToStringHashMap */
        cds :: experimental :: HashMap < String, String > fs139 = { {"X", "x"}, {"YY" ,"Y"}, {"z", "Z"}, {"WW", "W"}, {"t", "TTT"} };
        experimental :: Collection < MapEntry < String, String > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( auto e ) { if ( e.key().length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-CPP20' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-CPP20' OK" );
        }
    });

    /* CollectionTestGroup-FunctionalStatementsMemberFunction-CPP20 : CTG-00200-FSMF-CPP20 - Tests CTC-00201-FSMF to CTC-00229-FSMF */
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatementsMemberFunction-CPP20 : CTG-00200-FSMF-CPP20 : StringArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatementsMemberFunction-forEach-CPP20 : CTC-00201-FSMF-forEach-CPP20. Test Success if compile success */
        cds :: experimental :: Array < String > fs201 = { "Ana", "are", "mere" };
        fs201.forEach ( [](auto e){ (void) e.length(); } );
        fs201.forEach ( & String :: length );
        this->logOK ( "'CTC-00201-FSMF-forEach-CPP20' OK" );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someEqual-CPP20 : CTC-00202-FSMF-someEqual-CPP20. */
        cds :: experimental :: Array < String > fs202 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00202-FSMF-someEqual-CPP20",
                /* objUnderTest */  fs202,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someLess-CPP20 : CTC-00203-FSMF-someLess-CPP20. */
        cds :: experimental :: Array < String > fs203 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00203-FSMF-someLess-CPP20",
                /* objUnderTest */  fs203,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someMore-CPP20 : CTC-00204-FSMF-someMore-CPP20. */
        cds :: experimental :: Array < String > fs204 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00204-FSMF-someMore-CPP20",
                /* objUnderTest */  fs204,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeast-CPP20 : CTC-00205-FSMF-atLeast-CPP20. */
        cds :: experimental :: Array < String > fs205 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00205-FSMF-atLeast-CPP20",
                /* objUnderTest */  fs205,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeastLess-CPP20 : CTC-00206-FSMF-atLeastLess-CPP20. */
        cds :: experimental :: Array < String > fs206 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00206-FSMF-atLeastLess-CPP20",
                /* objUnderTest */  fs206,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeastMore-CPP20 : CTC-00207-FSMF-atLeastMore-CPP20. */
        cds :: experimental :: Array < String > fs207 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00207-FSMF-atLeastMore-CPP20",
                /* objUnderTest */  fs207,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMost-CPP20 : CTC-00208-FSMF-atMost-CPP20. */
        cds :: experimental :: Array < String > fs208 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00208-FSMF-atMost-CPP20",
                /* objUnderTest */  fs208,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMostLess-CPP20 : CTC-00209-FSMF-atMostLess-CPP20. */
        cds :: experimental :: Array < String > fs209 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00209-FSMF-atMostLess-CPP20",
                /* objUnderTest */  fs209,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMostMore-CPP20 : CTC-00210-FSMF-atMostMore-CPP20. */
        cds :: experimental :: Array < String > fs210 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00210-FSMF-atMostMore-CPP20",
                /* objUnderTest */  fs210,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThan-CPP20 : CTC-00211-FSMF-moreThan-CPP20. */
        cds :: experimental :: Array < String > fs211 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00211-FSMF-moreThan-CPP20",
                /* objUnderTest */  fs211,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThanLess-CPP20 : CTC-00212-FSMF-moreThanLess-CPP20. */
        cds :: experimental :: Array < String > fs212 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00212-FSMF-moreThanLess-CPP20",
                /* objUnderTest */  fs212,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThanMore-CPP20 : CTC-00213-FSMF-moreThanMore-CPP20. */
        cds :: experimental :: Array < String > fs213 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00213-FSMF-moreThanMore-CPP20",
                /* objUnderTest */  fs213,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThan-CPP20 : CTC-00214-FSMF-fewerThan-CPP20. */
        cds :: experimental :: Array < String > fs214 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00214-FSMF-fewerThan-CPP20",
                /* objUnderTest */  fs214,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThanLess-CPP20 : CTC-00215-FSMF-fewerThanLess-CPP20. */
        cds :: experimental :: Array < String > fs215 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00215-FSMF-fewerThanLess-CPP20",
                /* objUnderTest */  fs215,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThanMore-CPP20 : CTC-00216-FSMF-fewerThanMore-CPP20. */
        cds :: experimental :: Array < String > fs216 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00216-FSMF-fewerThanMore-CPP20",
                /* objUnderTest */  fs216,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-countExact-CPP20 : CTC-00217-FSMF-countExact-CPP20. */
        cds :: experimental :: Array < String > fs217 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00217-FSMF-countExact-CPP20",
                /* objUnderTest */  fs217,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: count,
                /* predicate */     & String :: empty,
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyNone-CPP20 : CTC-00218-FSMF-anyNone-CPP20. */
        cds :: experimental :: Array < String > fs218 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00218-FSMF-anyNone-CPP20",
                /* objUnderTest */  fs218,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyOne-CPP20 : CTC-00219-FSMF-anyOne-CPP20. */
        cds :: experimental :: Array < String > fs219 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00219-FSMF-anyOne-CPP20",
                /* objUnderTest */  fs219,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyMore-CPP20 : CTC-00220-FSMF-anyMore-CPP20. */
        cds :: experimental :: Array < String > fs220 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00220-FSMF-anyMore-CPP20",
                /* objUnderTest */  fs220,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyAll-CPP20 : CTC-00221-FSMF-anyAll-CPP20. */
        cds :: experimental :: Array < String > fs221 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00221-FSMF-anyAll-CPP20",
                /* objUnderTest */  fs221,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allNone-CPP20 : CTC-00222-FSMF-allNone-CPP20. */
        cds :: experimental :: Array < String > fs222 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00222-FSMF-allNone-CPP20",
                /* objUnderTest */  fs222,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allOne-CPP20 : CTC-00223-FSMF-allOne-CPP20. */
        cds :: experimental :: Array < String > fs223 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00223-FSMF-allOne-CPP20",
                /* objUnderTest */  fs223,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allMore-CPP20 : CTC-00224-FSMF-allMore-CPP20. */
        cds :: experimental :: Array < String > fs224 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00224-FSMF-allMore-CPP20",
                /* objUnderTest */  fs224,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allAll-CPP20 : CTC-00225-FSMF-allAll-CPP20. */
        cds :: experimental :: Array < String > fs225 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00225-FSMF-allAll-CPP20",
                /* objUnderTest */  fs225,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneNone-CPP20 : CTC-00226-FSMF-noneNone-CPP20. */
        cds :: experimental :: Array < String > fs226 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00226-FSMF-noneNone-CPP20",
                /* objUnderTest */  fs226,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneOne-CPP20 : CTC-00227-FSMF-noneOne-CPP20. */
        cds :: experimental :: Array < String > fs227 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00227-FSMF-noneOne-CPP20",
                /* objUnderTest */  fs227,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneMore-CPP20 : CTC-00228-FSMF-noneMore-CPP20. */
        cds :: experimental :: Array < String > fs228 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00228-FSMF-noneMore-CPP20",
                /* objUnderTest */  fs228,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneAll-CPP20 : CTC-00229-FSMF-noneAll-CPP20. */
        cds :: experimental :: Array < String > fs229 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00229-FSMF-noneAll-CPP20",
                /* objUnderTest */  fs229,
                /* testLib */       this,
                /* funcCaller */    & experimental :: Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );
    });


    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntArray", [& allOk, this] {

        cds :: experimental :: Array < int > intArray = { 1, 2, 3, 4, 5 };

        cds :: experimental :: Array < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: Array < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: Array < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: Array < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: Array < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < int > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < int > intLinkedList = { 1, 2, 3, 4, 5 };

        cds :: experimental :: LinkedList < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: LinkedList < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: LinkedList < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: LinkedList < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: LinkedList < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < int > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < int > intHashSet = { 1, 2, 3, 4, 5 };

        cds :: experimental :: HashSet < int > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: HashSet < int > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: HashSet < int > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: HashSet < int > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: HashSet < int > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < int > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : IntToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < int, int > intToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: experimental :: HashMap < int, int > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < int, int > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < int, int > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < int, int > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < int, int > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < MapEntry < int, int > > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringArray", [& allOk, this] {

        cds :: experimental :: Array < String > StringArray = { 1, 2, 3, 4, 5 };

        cds :: experimental :: Array < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: Array < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: Array < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: Array < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: Array < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < String > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < String > StringLinkedList = { 1, 2, 3, 4, 5 };

        cds :: experimental :: LinkedList < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: LinkedList < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: LinkedList < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: LinkedList < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: LinkedList < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < String > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < String > StringHashSet = { 1, 2, 3, 4, 5 };

        cds :: experimental :: HashSet < String > noneCommon = { 6, 7, 8, 9, 10 };
        cds :: experimental :: HashSet < String > oneCommon = { 6, 2, 8, 9, 10 };
        cds :: experimental :: HashSet < String > moreCommon = { 6, 2, 8, 4, 5 };
        cds :: experimental :: HashSet < String > allCommon = { 1, 2, 3, 4, 5 };
        cds :: experimental :: HashSet < String > allCommonAndMore = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < String > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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
    this->executeSubtest ( "CollectionTestGroup-ContainsOf-CPP20 : CTG-00300-CO-CPP20 : StringToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < String, String > StringToIntHashMap = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

        cds :: experimental :: HashMap < String, String > noneCommon = { {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < String, String > oneCommon = { {6, 6}, {2, 2}, {8, 8}, {9, 9}, {10, 10} };
        cds :: experimental :: HashMap < String, String > moreCommon = { {6, 6}, {2, 2}, {8, 8}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < String, String > allCommon = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: experimental :: HashMap < String, String > allCommonAndMore = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        /* CTC-00301-C0-Collection-CPP20 */
        allOk = allOk && collectionTestGroupContainsGroupByEquivalent < experimental :: Collection < MapEntry < String, String > > > (
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

        /* CTC-00301-C0-InitializerList-CPP20 */
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

    return allOk;
}
