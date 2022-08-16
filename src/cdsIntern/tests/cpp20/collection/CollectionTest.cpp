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


    /* CollectionTest-MemberFunctions-toString-CPP20 : CTC-00003-MF-toString-CPP20 */
    auto asString = collection.toString();
    pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
    if ( asString != expectedToString ) {
        pTestLib->logError ( "'CTC-00003-MF-toString-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00003-MF-toString-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-size-CPP20 : CTC-00004-MF-size-CPP20 */
    auto size = collection.size();
    pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, expectedSize );
    if ( size != expectedSize ) {
        pTestLib->logError( "'CTC-00004-MF-size-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00004-MF-size-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-empty-CPP20 : CTC-00005-MF-empty-CPP20 */
    auto empty = collection.empty();
    pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( empty != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CTC-00005-MF-empty-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00005-MF-empty-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-boolCast-CPP20 : CTC-00006-MF-boolCast-CPP20 */
    auto boolCast = static_cast < bool > ( collection.empty() );
    pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( boolCast != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CTC-00006-MF-boolCast-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00006-MF-boolCast-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-containsTrue-CPP20 : CTC-00007-MF-containsTrue-CPP20 */
    auto containsTrue = collection.contains ( toBeFound );
    pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "true" );
    if ( ! containsTrue ) {
        pTestLib->logError( "'CTC-00007-MF-containsTrue-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00007-MF-containsTrue-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-containsFalse-CPP20 : CTC-00008-MF-containsFalse-CPP20 */
    auto containsFalse = collection.contains ( toNotBeFound );
    pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
    if ( containsFalse ) {
        pTestLib->logError( "'CTC-00008-MF-containsFalse-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00008-MF-containsFalse-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CTC-00009-MF-hash-CPP20 */
    auto hash = collection.hash();
    pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, expectedHash );
    if ( hash != expectedHash ) {
        pTestLib->logError( "'CTC-00009-MF-hash-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00009-MF-hash-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-equalsSelf-CPP20 : CTC-00011-MF-equalsSelf-CPP20 */
    auto equalsToSelf = collection.equals ( collection );
    pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
    if ( ! equalsToSelf ) {
        pTestLib->logError( "'CTC-00011-MF-equalsSelf-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00011-MF-equalsSelf-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-equalsTrueSameType-CPP20 : CTC-00012-MF-equalsTrueSameType-CPP20 */
    auto equalsToEqualSameType = collection.equals ( equalSameType );
    pTestLib->log ( "object 'equals to equal, same type' : '%s', expected 'equals to equal, same type' : '%s'", equalsToEqualSameType ? "true" : "false", "true" );
    if ( ! equalsToEqualSameType ) {
        pTestLib->logError( "'CTC-00012-MF-equalsTrueSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00012-MF-equalsTrueSameType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-equalsTrueDifferentType-CPP20 : CTC-00013-MF-equalsTrueDifferentType-CPP20 */
    auto equalsToEqualDiffType = collection.equals ( equalDifferentType );
    pTestLib->log ( "object 'equals to equal, different type' : '%s', expected 'equals to equal, different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "true" );
    if ( ! equalsToEqualDiffType ) {
        pTestLib->logError( "'CTC-00013-MF-equalsTrueDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00013-MF-equalsTrueDifferentType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-equalsFalseSameType-CPP20 : CTC-00014-MF-equalsFalseSameType-CPP20 */
    auto notEqualsToSameType = collection.equals ( notEqualSameType );
    pTestLib->log ( "object 'equals to not equal, same type' : '%s', expected 'equals to not equal, same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
    if ( notEqualsToSameType ) {
        pTestLib->logError( "'CTC-00014-MF-equalsFalseSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00014-MF-equalsFalseSameType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-equalsFalseDifferentType-CPP20 : CTC-00015-MF-equalsFalseDifferentType-CPP20 */
    auto notEqualsToDifferentType = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, different type' : '%s', expected 'equals to not equal, different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
    if ( notEqualsToDifferentType ) {
        pTestLib->logError( "'CTC-00015-MF-equalsFalseDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00015-MF-equalsFalseDifferentType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-equalsFalseNotCollection-CPP20 : CTC-00016-MF-equalsFalseNotCollection-CPP20 */
    auto notEqualsToOtherObject = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, not collection' : '%s', expected 'equals to not equal, not collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );
    if ( notEqualsToOtherObject ) {
        pTestLib->logError( "'CTC-00016-MF-equalsFalseNotCollection-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00016-MF-equalsFalseNotCollection-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-clear-CPP20 : CTC-00010-MF-clear-CPP20 */
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
//    /* CollectionTest-DelegateForwardConstIterableClientImports-range-CPP20 : CTC-00051-IT-range-CPP20 */
//    pTestLib->log ( "Standard iteration : " );
//    for ( auto e : collection ) {
//        std :: stringstream oss;
//        cds :: streamPrint ( oss, e );
//        pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
//    }
//
//    /* CollectionTest-DelegateForwardConstIterableClientImports-begin_endIteration-CPP20 : CTC-00052-IT-begin_end-CPP20 */
//    auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
//    if ( ! stdIterResult ) {
//        pTestLib->logError( "'CTC-00052-IT-begin_end-CPP20' failed" );
//        return false;
//    } else {
//        pTestLib->logOK ( "'CTC-00052-IT-begin_end-CPP20' OK" );
//    }
//
//    /* CollectionTest-DelegateForwardConstIterableClientImports-cbegin_cendIteration-CPP20 : CTC-00053-IT-cbegin_cend-CPP20 */
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
//    /* CollectionTest-DelegateForwardConstIterableClientImports-emptybegin_end-CPP20 : CTC-00054-IT-e_begin_end-CPP20 */
//    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
//        pTestLib->logError( "'CTC-00054-IT-e_begin_end-CPP20' failed" );
//        return false;
//    }
//
//    pTestLib->logOK ( "'CTC-00054-IT-e_begin_end-CPP20' OK" );
//
//    /* CollectionTest-DelegateForwardConstIterableClientImports-emptycbegin_cend-CPP20 : CTC-00055-IT-e_cbegin_cend-CPP20 */
//    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
//        pTestLib->logError( "'CTC-00055-IT-e_cbegin_cend-CPP20' failed" );
//        return false;
//    }
//
//    pTestLib->logOK ( "'CTC-00055-IT-e_cbegin_cend-CPP20' OK" );
//
//    /* CollectionTest-DelegateForwardConstIterableClientImports-e_emptyRange-CPP20 : CTC-00056-IT-e_emptyRange-CPP20 */
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

    /* CollectionTest-DelegateForwardConstIterableClientImports-range-CPP20 : CTC-00051-IT-range-CPP20 */
    pTestLib->log ( "Standard iteration : " );
    for ( auto e : collection ) {
        std :: stringstream oss;
        cds :: streamPrint ( oss, e );
        pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
    }

    /* CollectionTest-DelegateForwardConstIterableClientImports-begin_endIteration-CPP20 : CTC-00052-IT-begin_end-CPP20 */
    auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
    if ( ! stdIterResult ) {
        pTestLib->logError( "'CTC-00052-IT-begin_end-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00052-IT-begin_end-CPP20' OK" );
    }

    /* CollectionTest-DelegateForwardConstIterableClientImports-cbegin_cendIteration-CPP20 : CTC-00053-IT-cbegin_cend-CPP20 */
    auto stdCIterResult = fwdCheckIterator < __MemberType > ( collection.cbegin(), collection.cend(), orderedValues ... );
    if ( ! stdCIterResult ) {
        pTestLib->logError( "'CTC-00053-IT-cbegin_cend-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CTC-00053-IT-cbegin_cend-CPP20' OK" );
    }

    collection.clear();

    /* CollectionTest-DelegateForwardConstIterableClientImports-emptybegin_end-CPP20 : CTC-00054-IT-e_begin_end-CPP20 */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'CTC-00054-IT-e_begin_end-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00054-IT-e_begin_end-CPP20' OK" );

    /* CollectionTest-DelegateForwardConstIterableClientImports-emptycbegin_cend-CPP20 : CTC-00055-IT-e_cbegin_cend-CPP20 */
    for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
        pTestLib->logError( "'CTC-00055-IT-e_cbegin_cend-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00055-IT-e_cbegin_cend-CPP20' OK" );

    /* CollectionTest-DelegateForwardConstIterableClientImports-e_emptyRange-CPP20 : CTC-00056-IT-e_emptyRange-CPP20 */
    for ( auto e : collection ) {
        pTestLib->logError( "'CTC-00056-IT-e_emptyRange-CPP20' failed" );
        return false;
    }

    pTestLib->logOK ( "'CTC-00056-IT-e_emptyRange-CPP20' OK" );

    return true;
}

/* CollectionTestSuiteCPP20 : CTS-00001-CPP20 */
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

        /* CollectionTest-SpecialAddressBasedIteratorAccess-addressOperator-CPP20 : CTC-00057-IT-addressOperator-CPP20 */
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

    return allOk;
}
