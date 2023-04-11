#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

namespace {
    template <
            typename __T,       /* NOLINT(bugprone-reserved-identifier) */
            typename __ItType,  /* NOLINT(bugprone-reserved-identifier) */
            typename __LastArg  /* NOLINT(bugprone-reserved-identifier) */
    > auto fwdCheckIterator (
            __ItType const & cur,
            __ItType const & end,
            __LastArg const & lastE
    ) -> bool {

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
            typename __T,                   /* NOLINT(bugprone-reserved-identifier) */
            typename __ItType,              /* NOLINT(bugprone-reserved-identifier) */
            typename __CurrArg,             /* NOLINT(bugprone-reserved-identifier) */
            typename ... __RemainingArgs    /* NOLINT(bugprone-reserved-identifier) */
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

    /* CollectionTestGroup-MemberFunctions-cpp-xx : CTG-00002-MF-cpp-xx. Tests CTC-00003 to CTC-00016 */
    template <
            typename __MemberType /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupMemberFunctions (
            cds :: Collection < __MemberType >        & collection,
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


        /* CollectionTestCase-MemberFunctions-toString-cpp-xx : CTC-00003-MF-toString-cpp-xx */
        auto asString = collection.toString();
        pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
        if ( asString != expectedToString ) {
            pTestLib->logError ( "'CTC-00003-MF-toString-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00003-MF-toString-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-size-cpp-xx : CTC-00004-MF-size-cpp-xx */
        auto size = collection.size();
        pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, expectedSize );
        if ( size != expectedSize ) {
            pTestLib->logError( "'CTC-00004-MF-size-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00004-MF-size-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-empty-cpp-xx : CTC-00005-MF-empty-cpp-xx */
        auto empty = collection.empty();
        pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
        if ( empty != ( expectedSize == 0ULL ) ) {
            pTestLib->logError( "'CTC-00005-MF-empty-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00005-MF-empty-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-boolCast-cpp-xx : CTC-00006-MF-boolCast-cpp-xx */
        auto boolCast = static_cast < bool > ( collection.empty() );
        pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
        if ( boolCast != ( expectedSize == 0ULL ) ) {
            pTestLib->logError( "'CTC-00006-MF-boolCast-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00006-MF-boolCast-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-containsTrue-cpp-xx : CTC-00007-MF-containsTrue-cpp-xx */
        auto containsTrue = collection.contains ( toBeFound );
        pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "true" );
        if ( ! containsTrue ) {
            pTestLib->logError( "'CTC-00007-MF-containsTrue-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00007-MF-containsTrue-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-containsFalse-cpp-xx : CTC-00008-MF-containsFalse-cpp-xx */
        auto containsFalse = collection.contains ( toNotBeFound );
        pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
        if ( containsFalse ) {
            pTestLib->logError( "'CTC-00008-MF-containsFalse-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00008-MF-containsFalse-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-hash-cpp-xx : CTC-00009-MF-hash-cpp-xx */
        auto hash = collection.hash();
        pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, expectedHash );
        if ( hash != expectedHash ) {
            pTestLib->logError( "'CTC-00009-MF-hash-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00009-MF-hash-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-equalsSelf-cpp-xx : CTC-00011-MF-equalsSelf-cpp-xx */
        auto equalsToSelf = collection.equals ( collection );
        pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
        if ( ! equalsToSelf ) {
            pTestLib->logError( "'CTC-00011-MF-equalsSelf-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00011-MF-equalsSelf-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-equalsTrueSameType-cpp-xx : CTC-00012-MF-equalsTrueSameType-cpp-xx */
        auto equalsToEqualSameType = collection.equals ( equalSameType );
        pTestLib->log ( "object 'equals to equal, same type' : '%s', expected 'equals to equal, same type' : '%s'", equalsToEqualSameType ? "true" : "false", "true" );
        if ( ! equalsToEqualSameType ) {
            pTestLib->logError( "'CTC-00012-MF-equalsTrueSameType-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00012-MF-equalsTrueSameType-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-equalsTrueDifferentType-cpp-xx : CTC-00013-MF-equalsTrueDifferentType-cpp-xx */
        auto equalsToEqualDiffType = collection.equals ( equalDifferentType );
        pTestLib->log ( "object 'equals to equal, different type' : '%s', expected 'equals to equal, different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "true" );
        if ( ! equalsToEqualDiffType ) {
            pTestLib->logError( "'CTC-00013-MF-equalsTrueDifferentType-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00013-MF-equalsTrueDifferentType-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-equalsFalseSameType-cpp-xx : CTC-00014-MF-equalsFalseSameType-cpp-xx */
        auto notEqualsToSameType = collection.equals ( notEqualSameType );
        pTestLib->log ( "object 'equals to not equal, same type' : '%s', expected 'equals to not equal, same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
        if ( notEqualsToSameType ) {
            pTestLib->logError( "'CTC-00014-MF-equalsFalseSameType-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00014-MF-equalsFalseSameType-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-equalsFalseDifferentType-cpp-xx : CTC-00015-MF-equalsFalseDifferentType-cpp-xx */
        auto notEqualsToDifferentType = collection.equals ( notEqualDifferentType );
        pTestLib->log ( "object 'equals to not equal, different type' : '%s', expected 'equals to not equal, different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
        if ( notEqualsToDifferentType ) {
            pTestLib->logError( "'CTC-00015-MF-equalsFalseDifferentType-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00015-MF-equalsFalseDifferentType-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-equalsFalseNotCollection-cpp-xx : CTC-00016-MF-equalsFalseNotCollection-cpp-xx */
        auto notEqualsToOtherObject = collection.equals ( notEqualDifferentType );
        pTestLib->log ( "object 'equals to not equal, not collection' : '%s', expected 'equals to not equal, not collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );
        if ( notEqualsToOtherObject ) {
            pTestLib->logError( "'CTC-00016-MF-equalsFalseNotCollection-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00016-MF-equalsFalseNotCollection-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-MemberFunctions-clear-cpp-xx : CTC-00010-MF-clear-cpp-xx */
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
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - toString' failed" );
            return false;
        } else if ( size != 0ULL ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - size' failed" );
            return false;
        } else if ( ! empty ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - empty' failed" );
            return false;
        } else if ( ! boolCast ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - bool cast' failed" );
            return false;
        } else if ( containsTrue || containsFalse ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - contains' failed" );
            return false;
        } else if ( hash != 0ULL ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - hash' failed" );
            return false;
        } else if ( ! equalsToSelf ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - equalsToSelf' failed" );
            return false;
        } else if ( equalsToEqualSameType ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - equalsToEqualSameTypePrevToClear' failed" );
            return false;
        } else if ( equalsToEqualDiffType ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - equalsToEqualDiffTypePrevToClear' failed" );
            return false;
        } else if ( notEqualsToSameType ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - equalsToNotEqualSameTypePrevToClear' failed" );
            return false;
        } else if ( notEqualsToDifferentType ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - equalsToNotEqualDiffTypePrevToClear' failed" );
            return false;
        } else if ( notEqualsToOtherObject ) {
            pTestLib->logError( "'CTC-00010-MF-clear-cpp-xx - equalsToNotEqualOtherObj' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00010-MF-clear-" __CDS_cpplang_core_version_name "' OK" );
        }


        return true;
    }

    /* CollectionTestGroup-DelegateForwardConstIterableClientImports-cpp-xx : CTG-00050-IT-cpp-xx. Tests CTC-00051 to CTC-00056 */
    template <
            typename __MemberType,                              /* NOLINT(bugprone-reserved-identifier) */
            typename ... __OrderedValues                        /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupDelegateForwardConstIterableClientImports (
            Collection < __MemberType > & collection,
            Test                  *     pTestLib,
            __OrderedValues const & ... orderedValues
    ) -> bool {

        pTestLib->log ( "Object under test, to be iterated : '%s'", collection.toString().cStr() );

        /* CollectionTestCase-DelegateForwardConstIterableClientImports-range-cpp-xx : CTC-00051-IT-range-cpp-xx */
        pTestLib->log ( "Standard iteration : " );
        for ( auto const & e : collection ) {
            std :: stringstream oss;
            cds :: streamPrint ( oss, e );
            pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
        }

        /* CollectionTestCase-DelegateForwardConstIterableClientImports-begin_endIteration-cpp-xx : CTC-00052-IT-begin_end-cpp-xx */
        auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
        if ( ! stdIterResult ) {
            pTestLib->logError( "'CTC-00052-IT-begin_end-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00052-IT-begin_end-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-DelegateForwardConstIterableClientImports-cbegin_cendIteration-cpp-xx : CTC-00053-IT-cbegin_cend-cpp-xx */
        auto stdCIterResult = fwdCheckIterator < __MemberType > ( collection.cbegin(), collection.cend(), orderedValues ... );
        if ( ! stdCIterResult ) {
            pTestLib->logError( "'CTC-00053-IT-cbegin_cend-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00053-IT-cbegin_cend-" __CDS_cpplang_core_version_name "' OK" );
        }

        collection.clear();

        /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptybegin_end-cpp-xx : CTC-00054-IT-e_begin_end-cpp-xx */
        {
            auto it = collection.begin();
            if (it != collection.end()) {
                pTestLib->logError("'CTC-00054-IT-e_begin_end-" __CDS_cpplang_core_version_name "' failed");
                return false;
            }
        }

        pTestLib->logOK ( "'CTC-00054-IT-e_begin_end-" __CDS_cpplang_core_version_name "' OK" );

        {
            auto it = collection.cbegin();
            /* CollectionTestCase-DelegateForwardConstIterableClientImports-emptycbegin_cend-cpp-xx : CTC-00055-IT-e_cbegin_cend-cpp-xx */
            if (it != collection.cend()) {
                pTestLib->logError( "'CTC-00055-IT-e_cbegin_cend-" __CDS_cpplang_core_version_name "' failed" );
                return false;
            }
        }

        pTestLib->logOK ( "'CTC-00055-IT-e_cbegin_cend-" __CDS_cpplang_core_version_name "' OK" );

        /* CollectionTestCase-DelegateForwardConstIterableClientImports-e_emptyRange-cpp-xx : CTC-00056-IT-e_emptyRange-cpp-xx */
        /* not required, covered by previous tests - 00054, 00055 */
        /*
        for ( auto const & e : collection ) {
            pTestLib->logError( "'CTC-00056-IT-e_emptyRange-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        }
        */

        pTestLib->logOK ( "'CTC-00056-IT-e_emptyRange-" __CDS_cpplang_core_version_name "' OK" );

        return true;
    }
}

auto CollectionTest::tests_00000_00099 () noexcept -> bool {
    
    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        cds :: Array < int > intArrayObjectUnderTest;
        intArrayObjectUnderTest     = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: Array < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: Array < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: LinkedList < int > { 1, 2, 3, 5 };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        cds :: LinkedList < int > intLinkedListObjectUnderTest;
        intLinkedListObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: Array < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: LinkedList < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: Array < int > { 1, 2, 3, 5 };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntHashSet", [& allOk, this] {

        cds :: HashSet < int > intHashSetObjectUnderTest;
        intHashSetObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: HashSet < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: HashSet < int > { 1, 2, 3, 5 };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntTreeSet", [& allOk, this] {

        cds :: TreeSet < int > intTreeSetObjectUnderTest;
        intTreeSetObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: TreeSet < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: TreeSet < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: TreeSet < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: TreeSet < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intTreeSetObjectUnderTest,
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < int > intTreeSetObjectUnderTest;
        intTreeSetObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: LinkedHashSet < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: LinkedHashSet < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: LinkedHashSet < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: LinkedHashSet < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intTreeSetObjectUnderTest,
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        cds :: HashMap < int, int > intIntHashMapObjectUnderTest;
        intIntHashMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 2, 7 );
        auto expectedToBeNotFound   = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 6, 20 );
        auto expectedHash           = ((((
                                                 ( cds :: hash (1) ^ cds :: hash (6) ) * 31 + ( cds :: hash ( 2 ) ^ cds :: hash (7))
                                         ) * 31 + ( cds :: hash ( 3 )) ^ cds :: hash (8)) * 31 + ( cds :: hash ( 4 ) ^ cds :: hash (9)) ) * 31 + ( cds :: hash ( 5 )) ^ cds :: hash (10));

        auto equalSameType          = cds :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto equalDifferentType     = cds :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto notEqualSameType       = cds :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualDifferentType  = cds :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [& allOk, this] {

        cds :: LinkedHashMap < int, int > intIntHashMapObjectUnderTest;
        intIntHashMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 2, 7 );
        auto expectedToBeNotFound   = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 6, 20 );
        auto expectedHash           = ((((
                                                 ( cds :: hash (1) ^ cds :: hash (6) ) * 31 + ( cds :: hash ( 2 ) ^ cds :: hash (7))
                                         ) * 31 + ( cds :: hash ( 3 )) ^ cds :: hash (8)) * 31 + ( cds :: hash ( 4 ) ^ cds :: hash (9)) ) * 31 + ( cds :: hash ( 5 )) ^ cds :: hash (10));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: LinkedHashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto equalDifferentType     = cds :: LinkedHashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto notEqualSameType       = cds :: LinkedHashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualDifferentType  = cds :: LinkedHashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [& allOk, this] {

        cds :: TreeMap < int, int > intIntTreeMapObjectUnderTest;
        intIntTreeMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = decltype ( intIntTreeMapObjectUnderTest ) :: EntryType ( 2, 7 );
        auto expectedToBeNotFound   = decltype ( intIntTreeMapObjectUnderTest ) :: EntryType ( 6, 20 );
        auto expectedHash           = ((((
                                                 ( cds :: hash (1) ^ cds :: hash (6) ) * 31 + ( cds :: hash ( 2 ) ^ cds :: hash (7))
                                         ) * 31 + ( cds :: hash ( 3 )) ^ cds :: hash (8)) * 31 + ( cds :: hash ( 4 ) ^ cds :: hash (9)) ) * 31 + ( cds :: hash ( 5 )) ^ cds :: hash (10));

        /* error reported by IDE makes no sense? */
        auto equalDifferentType     = cds :: TreeMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto notEqualSameType       = cds :: TreeMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto equalSameType          = cds :: TreeMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto notEqualDifferentType  = cds :: TreeMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions (
                intIntTreeMapObjectUnderTest,
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        cds :: Array < cds :: String > stringArrayObjectUnderTest;
        stringArrayObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: Array < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: Array < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: LinkedList < cds :: String > { "Ana", "are", "pere" };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        cds :: LinkedList < cds :: String > stringLinkedListObjectUnderTest;
        stringLinkedListObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: Array < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: LinkedList < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: Array < cds :: String > { "Ana", "are", "pere" };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringHashSet", [& allOk, this] {

        cds :: HashSet < cds :: String > stringHashSetObjectUnderTest;
        stringHashSetObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "{ are, Ana, mere }"; /** due to hash table */
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "are" ) * 31 + cds :: hash ( "Ana" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: HashSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: HashSet < cds :: String > { "Ana", "are", "pere" };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringTreeSet", [& allOk, this] {

        cds :: TreeSet < cds :: String > stringTreeSetObjectUnderTest;
        stringTreeSetObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "{ Ana, are, mere }";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: TreeSet < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: TreeSet < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: TreeSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: TreeSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringTreeSetObjectUnderTest,
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < cds :: String > stringTreeSetObjectUnderTest;
        stringTreeSetObjectUnderTest     = { "ana", "are", "mere" };

        auto expectedToString       = "{ ana, are, mere }";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "ana";
        auto expectedToBeNotFound   = "Ana";
        auto expectedHash           = (
                                              cds :: hash ( "ana" ) * 31 + cds :: hash ( "are" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: LinkedHashSet < cds :: String > { "ana", "are", "mere" };
        auto equalDifferentType     = cds :: LinkedHashSet < cds :: String > { "ana", "are", "mere" };
        auto notEqualSameType       = cds :: LinkedHashSet < cds :: String > { "ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: LinkedHashSet < cds :: String > { "ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringTreeSetObjectUnderTest,
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        cds :: HashMap < cds :: String, cds :: String > stringStringHashMapObjectUnderTest;
        stringStringHashMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ are: verb, Ana: name, mere: noun }"; /** due to hash table */
        auto expectedSize           = 3;
        auto expectedToBeFound      = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "are", "verb" );
        auto expectedToBeNotFound   = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "pere", "noun" );
        auto expectedHash           = (
                (( cds :: hash ("are") ^ cds :: hash ("verb") ) * 31 + ( cds :: hash ( "Ana" ) ^ cds :: hash ("name")))
                * 31 + ( cds :: hash ( "mere" ) ^ cds :: hash ("noun")));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto equalDifferentType     = cds :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto notEqualSameType       = cds :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "pere", "noun" } };
        auto notEqualDifferentType  = cds :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "other" } };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [& allOk, this] {

        cds :: LinkedHashMap < cds :: String, cds :: String > stringStringHashMapObjectUnderTest;
        stringStringHashMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ Ana: name, are: verb, mere: noun }";
        auto expectedSize           = 3;
        auto expectedToBeFound      = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "are", "verb" );
        auto expectedToBeNotFound   = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "pere", "noun" );
        auto expectedHash           = (
                (( cds :: hash ("Ana") ^ cds :: hash ("name") ) * 31 + ( cds :: hash ( "are" ) ^ cds :: hash ("verb")))
                * 31 + ( cds :: hash ( "mere" ) ^ cds :: hash ("noun")));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: LinkedHashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto equalDifferentType     = cds :: LinkedHashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto notEqualSameType       = cds :: LinkedHashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "pere", "noun" } };
        auto notEqualDifferentType  = cds :: LinkedHashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "other" } };
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
    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : CTG-00002-MF-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [& allOk, this] {

        cds :: TreeMap < cds :: String, cds :: String > stringStringTreeMapObjectUnderTest;
        stringStringTreeMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ Ana: name, are: verb, mere: noun }";
        auto expectedSize           = 3;
        auto expectedToBeFound      = decltype ( stringStringTreeMapObjectUnderTest ) :: EntryType ( "are", "verb" );
        auto expectedToBeNotFound   = decltype ( stringStringTreeMapObjectUnderTest ) :: EntryType ( "pere", "noun" );
        auto expectedHash           = (
                (( cds :: hash ("Ana") ^ cds :: hash ("name") ) * 31 + ( cds :: hash ( "are" ) ^ cds :: hash ("verb")))
                * 31 + ( cds :: hash ( "mere" ) ^ cds :: hash ("noun")));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: TreeMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto equalDifferentType     = cds :: TreeMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto notEqualSameType       = cds :: TreeMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "pere", "noun" } };
        auto notEqualDifferentType  = cds :: TreeMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "other" } };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions < cds :: MapEntry < cds :: String, cds :: String > > (
                stringStringTreeMapObjectUnderTest,
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


    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        cds :: Array < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        cds :: LinkedList < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntHashSet", [& allOk, this] {

        cds :: HashSet < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntTreeSet", [& allOk, this] {

        cds :: TreeSet < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < int > (
                objUnderTest,
                this,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        cds :: HashMap < int, int > objUnderTest = {{3,4}, {4,5}, {5,6}, {6,7}, {7,8}};
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
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [& allOk, this] {

        cds :: LinkedHashMap < int, int > objUnderTest = {{3,4}, {4,5}, {5,6}, {6,7}, {7,8}};
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
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [& allOk, this] {

        cds :: TreeMap < int, int > objUnderTest = {{3,4}, {4,5}, {5,6}, {6,7}, {7,8}};
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
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        cds :: Array < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        cds :: LinkedList < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringHashSet", [& allOk, this] {

        cds :: HashSet < String > objUnderTest = {"are", "Ana", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "are", "Ana", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringTreeSet", [& allOk, this] {

        cds :: TreeSet < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < String > objUnderTest = {"Ana", "are", "mere", "dar", "pere", "o", "au", "pe", "ana"};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < String > (
                objUnderTest,
                this,
                "Ana", "are", "mere", "dar", "pere", "o", "au", "pe", "ana"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        cds :: HashMap < String, String > objUnderTest = {{"are","verb"}, {"Ana","name"}, {"mere","noun"}};
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
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [& allOk, this] {

        cds :: LinkedHashMap < String, String > objUnderTest = {{"Ana","name"}, {"are","verb"}, {"mere","noun"}};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < MapEntry < String, String > > (
                objUnderTest,
                this,
                MapEntry < String, String > { "Ana", "name" },
                MapEntry < String, String > { "are", "verb" },
                MapEntry < String, String > { "mere", "noun" }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-DelegateForwardConstIterableClientImports-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [& allOk, this] {

        cds :: TreeMap < String, String > objUnderTest = {{"Ana","name"}, {"are","verb"}, {"mere","noun"}};
        auto status = collectionTestGroupDelegateForwardConstIterableClientImports < MapEntry < String, String > > (
                objUnderTest,
                this,
                MapEntry < String, String > { "Ana", "name" },
                MapEntry < String, String > { "are", "verb" },
                MapEntry < String, String > { "mere", "noun" }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "CollectionTestGroup-SpecialAddressBasedIteratorAccess-" __CDS_cpplang_core_version_name " : CTG-00050-IT-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* only one test required, as it uses operator *, which was tested in previous group */
        cds :: Array < String > arr = { "Ana", "are", "mere" };
        cds :: Collection < String > & c = arr;
        auto begin = c.begin();

        /* CollectionTestCase-SpecialAddressBasedIteratorAccess-addressOperator-cpp-xx : CTC-00057-IT-addressOperator-cpp-xx */
        auto expectedLen = 3;
        auto len = begin->length();

        this->log ( "iterator '-> operator length' : '%llu', expected '-> operator length' : '%llu'", len, expectedLen );
        if ( expectedLen != len ) {
            this->logError ( "'CTC-00057-IT-addressOperator-" __CDS_cpplang_core_version_name "' error" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00057-IT-addressOperator-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

    return allOk;
}
