#include "MutableCollectionTest.h"
#include "MutableCollectionTest_common.hpp"


namespace {
    /* MutableCollectionTestGroup-MemberFunctions-cpp-xx : MCTG-00002-MF-cpp-xx. Tests MCTC-00003 to MCTC-00004 */
    template <
            typename __MemberType /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupMemberFunctions (
            cds :: MutableCollection < __MemberType >        & collection,
            Test                                                             * pTestLib,
            String                                                     const & expectedToString
    ) -> bool {

        pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );


        /* MutableCollectionTestGroup-MemberFunctions-toString-cpp-xx : MCTC-00003-MF-toString-cpp-xx */
        auto asString = collection.toString();
        pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
        if ( asString != expectedToString ) {
            pTestLib->logError ( "'MCTC-00003-MF-toString-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00003-MF-toString-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestGroup-MemberFunctions-clear-cpp-xx : MCTC-00004-MF-clear-cpp-xx */
        collection.clear();

        asString                    = collection.toString();

        pTestLib->log ( "Object Cleared using 'clear'. Re-execution after clear : " );
        pTestLib->log ( "object 'toString' : '%s'. potential expected 'toString' : '%s'", asString.cStr(), "[]" );

        if ( asString.length() > 2ULL ) {
            pTestLib->logError( "'MCTC-00004-MF-clear-cpp-xx - toString' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00004-MF-clear-" __CDS_cpplang_core_version_name "' OK" );
        }


        return true;
    }

    /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-cpp-xx : MCTG-00050-IT-cpp-xx. Tests MCTC-00051 to MCTC-00056 */
    template <
            typename __MemberType,                              /* NOLINT(bugprone-reserved-identifier) */
            typename ... __OrderedValues                        /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupDelegateForwardIterableClientImports (
            MutableCollection < __MemberType > & collection,
            Test                  *     pTestLib,
            bool                        mutabilityTestExecute,
            __MemberType    const &     mutabilityTestValue,
            __MemberType    const &     mutabilityTestValue2,
            __OrderedValues const & ... orderedValues
    ) -> bool {

        pTestLib->log ( "Object under test, to be iterated : '%s'", collection.toString().cStr() );

        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-range-cpp-xx : MCTC-00051-IT-range-cpp-xx */
        pTestLib->log ( "Standard iteration : " );
        for ( auto & e : collection ) {
            std :: stringstream oss;
            cds :: streamPrint ( oss, e );
            pTestLib->log ( "'%s'", cds :: String ( oss.str() ).toString().cStr() );
        }

        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-begin_endIteration-cpp-xx : MCTC-00052-IT-begin_end-cpp-xx */
        auto stdIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
        if ( ! stdIterResult ) {
            pTestLib->logError( "'MCTC-00052-IT-begin_end-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00052-IT-begin_end-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-begin_endIteration-cpp-xx : MCTC-00053-IT-begin_end-cpp-xx */
        auto stdCIterResult = fwdCheckIterator < __MemberType > ( collection.begin(), collection.end(), orderedValues ... );
        if ( ! stdCIterResult ) {
            pTestLib->logError( "'MCTC-00053-IT-begin_end-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00053-IT-begin_end-" __CDS_cpplang_core_version_name "' OK" );
        }

        if ( mutabilityTestExecute ) {
            /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-mutabilityRange-cpp-xx : MCTC-00058-IT-mutabilityRange-cpp-xx */
            for ( auto & e : collection ) {
                e = mutabilityTestValue;
            }

            if ( collection.any ( [& mutabilityTestValue](__MemberType const & e) { return e != mutabilityTestValue; } ) ) {
                pTestLib->logError ( "'MCTC-00058-IT-mutabilityRange-" __CDS_cpplang_core_version_name "' failed" );
                return false;
            } else {
                pTestLib->logOK ( "'MCTC-00058-IT-mutabilityRange-" __CDS_cpplang_core_version_name "' OK" );
            };

            /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-mutabilityIteration-cpp-xx : MCTC-00059-IT-mutabilityIteration-cpp-xx */
            for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
                * it = mutabilityTestValue2;
            }

            if ( collection.any ( [& mutabilityTestValue2](__MemberType const & e) { return e != mutabilityTestValue2; } ) ) {
                pTestLib->logError ( "'MCTC-00059-IT-mutabilityIteration-" __CDS_cpplang_core_version_name "' failed" );
                return false;
            } else {
                pTestLib->logOK ( "'MCTC-00059-IT-mutabilityIteration-" __CDS_cpplang_core_version_name "' OK" );
            };
        }


        collection.clear();

        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-emptybegin_end-cpp-xx : MCTC-00054-IT-e_begin_end-cpp-xx */
        {
            auto it = collection.begin();
            if (it != collection.end()) {
                pTestLib->logError( "'MCTC-00054-IT-e_begin_end-" __CDS_cpplang_core_version_name "' failed" );
                return false;
            }
        }

        pTestLib->logOK ( "'MCTC-00054-IT-e_begin_end-" __CDS_cpplang_core_version_name "' OK" );

        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-emptycbegin_cend-cpp-xx : MCTC-00055-IT-e_cbegin_cend-cpp-xx */
        {
            auto it = collection.cbegin();
            if (it != collection.cend()) {
                pTestLib->logError( "'MCTC-00055-IT-e_begin_end-" __CDS_cpplang_core_version_name "' failed" );
                return false;
            }
        }

        pTestLib->logOK ( "'MCTC-00055-IT-e_begin_end-" __CDS_cpplang_core_version_name "' OK" );

        /* MutableCollectionTestGroup-DelegateForwardIterableClientImports-e_emptyRange-cpp-xx : MCTC-00056-IT-e_emptyRange-cpp-xx */
        /* validated by begin / end tests */
        /*
        for ( auto & e : collection ) {
            pTestLib->logError( "'MCTC-00056-IT-e_emptyRange-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        }
        */

        pTestLib->logOK ( "'MCTC-00056-IT-e_emptyRange-" __CDS_cpplang_core_version_name "' OK" );

        return true;
    }
}


auto MutableCollectionTest::tests_00000_00099 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        cds :: Array < int > intArrayObjectUnderTest;
        intArrayObjectUnderTest     = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto status = mutableCollectionTestGroupMemberFunctions (
                intArrayObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        cds :: LinkedList < int > intLinkedListObjectUnderTest;
        intLinkedListObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";

        auto status = mutableCollectionTestGroupMemberFunctions (
                intLinkedListObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        cds :: HashMap < int, int > intIntHashMapObjectUnderTest;
        intIntHashMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";

        auto status = mutableCollectionTestGroupMemberFunctions (
                intIntHashMapObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        cds :: Array < cds :: String > stringArrayObjectUnderTest;
        stringArrayObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";

        auto status = mutableCollectionTestGroupMemberFunctions < cds :: String > (
                stringArrayObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        cds :: LinkedList < cds :: String > stringLinkedListObjectUnderTest;
        stringLinkedListObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";

        auto status = mutableCollectionTestGroupMemberFunctions < cds :: String > (
                stringLinkedListObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : MCTG-00002-MF-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        cds :: HashMap < cds :: String, cds :: String > stringStringHashMapObjectUnderTest;
        stringStringHashMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ are: verb, Ana: name, mere: noun }"; /* due to hash table */

        auto status = mutableCollectionTestGroupMemberFunctions < cds :: MapEntry < cds :: String, cds :: String > > (
                stringStringHashMapObjectUnderTest,
                this,
                expectedToString
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });


    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        cds :: Array < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < int > (
                objUnderTest,
                this,
                true,
                20, 40,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        cds :: LinkedList < int > objUnderTest = {3, 4, 5, 6, 7};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < int > (
                objUnderTest,
                this,
                true,
                20, 40,
                3, 4, 5, 6, 7
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        cds :: HashMap < int, int > objUnderTest = {{3,4}, {4,5}, {5,6}, {6,7}, {7,8}};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < MapEntry < int, int > > (
                objUnderTest,
                this,
                false,
                MapEntry < int, int > { 20, 30 },
                MapEntry < int, int > { 40, 60 },
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
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        cds :: Array < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < String > (
                objUnderTest,
                this,
                true,
                "Ion", "Gigel",
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        cds :: LinkedList < String > objUnderTest = {"Ana", "are", "mere"};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < String > (
                objUnderTest,
                this,
                true,
                "Ion", "Gigel",
                "Ana", "are", "mere"
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-DelegateForwardIterableClientImports-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        cds :: HashMap < String, String > objUnderTest = {{"are","verb"}, {"Ana","name"}, {"mere","noun"}};
        auto status = mutableCollectionTestGroupDelegateForwardIterableClientImports < MapEntry < String, String > > (
                objUnderTest,
                this,
                false,
                MapEntry < String, String > { "Gigel", "name" },
                MapEntry < String, String > { "them", "pronoun" },
                MapEntry < String, String > { "are", "verb" },
                MapEntry < String, String > { "Ana", "name" },
                MapEntry < String, String > { "mere", "noun" }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "MutableCollectionTestGroup-SpecialAddressBasedIteratorAccess-" __CDS_cpplang_core_version_name " : MCTG-00050-IT-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* only one test required, as it uses operator *, which was tested in previous group */
        cds :: Array < String > arr = { "Ana", "are", "mere" };
        cds :: MutableCollection < String > & c = arr;
        auto begin = c.begin();

        /* MutableCollectionTestGroup-SpecialAddressBasedIteratorAccess-addressOperator-cpp-xx : MCTC-00057-IT-addressOperator-cpp-xx */
        auto expectedLen = 3;
        auto len = begin->length();

        this->log ( "iterator '-> operator length' : '%llu', expected '-> operator length' : '%llu'", len, expectedLen );
        if ( expectedLen != len ) {
            this->logError ( "'MCTC-00057-IT-addressOperator-" __CDS_cpplang_core_version_name "' error" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00057-IT-addressOperator-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

    return allOk;
}
