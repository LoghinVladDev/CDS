#include "MutableCollectionTest.h"
#include "MutableCollectionTest_100_200_common.hpp"


auto MutableCollectionTest::tests_00100_00199 () noexcept -> bool {

    bool allOk = true;

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* MutableCollectionTestGroup-FunctionalStatements-cpp-xx : MCTG-00100-FS-cpp-xx - Tests MCTC-00101-FS to MCTC-10139-FS - located directly below due to varability of these tests */
    /* IntArray */              this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : IntArray */
        cds :: Array < int > const fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : IntArray */
        cds :: Array < int > const fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : IntArray */
        cds :: Array < int > const fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : IntArray */
        cds :: Array < int > const fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : IntArray */
        cds :: Array < int > const fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : IntArray */
        cds :: Array < int > const fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : IntArray */
        cds :: Array < int > const fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : IntArray */
        cds :: Array < int > const fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : IntArray */
        cds :: Array < int > const fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : IntArray */
        cds :: Array < int > const fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : IntArray */
        cds :: Array < int > const fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : IntArray */
        cds :: Array < int > const fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : IntArray */
        cds :: Array < int > const fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : IntArray */
        cds :: Array < int > const fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : IntArray */
        cds :: Array < int > const fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : IntArray */
        cds :: Array < int > const fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : IntArray */
        cds :: Array < int > const fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : IntArray */
        cds :: Array < int > const fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : IntArray */
        cds :: Array < int > const fs139 = { 1, 2, 3, 4, 5 };
        MutableCollection < int > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: Array < int > fs140 = { 1, 2, 3, 4, 5 };
        cds :: MutableCollection < int > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( int & e ) { e = 3; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](int e) { return e == 3; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntLinkedList */         this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs139 = { 1, 2, 3, 4, 5 };
        MutableCollection < int > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: LinkedList < int > fs140 = { 1, 2, 3, 4, 5 };
        cds :: MutableCollection < int > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( int & e ) { e = 3; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](int e) { return e == 3; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntToIntHashMap */       this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs101 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs102 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs103 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs104 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs105 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs106 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs107 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs108 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs109 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs110 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {8, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs111 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs112 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs113 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs114 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs115 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs116 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs117 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: count,
                /* predicate */     [comparedTo] (MapEntry<int, int>const & e) { return e.key() > comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs118 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs119 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs120 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs121 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs122 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs123 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs124 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs125 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs126 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs127 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs128 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs129 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs130 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs131 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs132 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs133 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs134 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs135 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs136 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs137 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs138 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs139 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        MutableCollection < MapEntry < int, int > > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<int, int>const & e ) { if ( e.key() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: HashMap < int, int > fs140 = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
        cds :: MutableCollection < MapEntry < int, int > > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( MapEntry < int, int > & e ) {
            /* e.key() = 3;  must always fail compilation */
            e.value () = 7;
        };

        MutableCollectionFS140.forEach (actionfs140);
        int growingKey = 1;
        auto countfs140 = MutableCollectionFS140.count ([& growingKey](MapEntry < int, int > & e) {
            return e.key() == growingKey ++ && e.value () == 7;
        });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringArray */           this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : StringArray */
        cds :: Array < String > const fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : StringArray */
        cds :: Array < String > const fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : StringArray */
        cds :: Array < String > const fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : StringArray */
        cds :: Array < String > const fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : StringArray */
        cds :: Array < String > const fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : StringArray */
        cds :: Array < String > const fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : StringArray */
        cds :: Array < String > const fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : StringArray */
        cds :: Array < String > const fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : StringArray */
        cds :: Array < String > const fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : StringArray */
        cds :: Array < String > const fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : StringArray */
        cds :: Array < String > const fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : StringArray */
        cds :: Array < String > const fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : StringArray */
        cds :: Array < String > const fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : StringArray */
        cds :: Array < String > const fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : StringArray */
        cds :: Array < String > const fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : StringArray */
        cds :: Array < String > const fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : StringArray */
        cds :: Array < String > const fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > const fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : StringArray */
        cds :: Array < String > const fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : StringArray */
        cds :: Array < String > const fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : StringArray */
        cds :: Array < String > const fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        MutableCollection < String > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: Array < String > fs140 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( String & e ) { e = "ccc"; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](String const & e) { return e == "ccc"; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMemberFnMutability-" __CDS_cpplang_core_version_name " : MCTC-00141-FS-forEachMemberFnMutability-cpp-xx : IntArray */
        cds :: Array < String > fs141 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS141 = fs141;
        auto actionfs141 = & String :: clear;

        MutableCollectionFS141.forEach (actionfs141);
        auto countfs141 = MutableCollectionFS141.count (& String :: empty);

        if ( countfs141 != fs141.size() ) {
            this->logError ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringLinkedList */      this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );
        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > const fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        MutableCollection < String > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: LinkedList < String > fs140 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( String & e ) { e = "ccc"; };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](String const & e) { return e == "ccc"; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMemberFnMutability-" __CDS_cpplang_core_version_name " : MCTC-00141-FS-forEachMemberFnMutability-cpp-xx : IntArray */
        cds :: LinkedList < String > fs141 = { "a", "bb", "ccc", "dddd", "eeeee" };
        cds :: MutableCollection < String > & MutableCollectionFS141 = fs141;
        auto actionfs141 = & String :: clear;

        MutableCollectionFS141.forEach (actionfs141);
        auto countfs141 = MutableCollectionFS141.count (& String :: empty);

        if ( countfs141 != fs141.size() ) {
            this->logError ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00141-FS-forEachMemberFnMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

    /* StringToStringHashMap */ this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : MCTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatements-anyNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00101-FS-anyNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs101 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00102-FS-anyOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs102 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00103-FS-anyMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs103 = { {"x", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-anyAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00104-FS-anyAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs104 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-allNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00105-FS-allNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs105 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00106-FS-allOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs106 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00107-FS-allMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs107 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-allAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00108-FS-allAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs108 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneNoneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00109-FS-noneNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs109 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneOneApplicable-" __CDS_cpplang_core_version_name " : MCTC-00110-FS-noneOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs110 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneMoreApplicable-" __CDS_cpplang_core_version_name " : MCTC-00111-FS-noneMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs111 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-noneAllApplicable-" __CDS_cpplang_core_version_name " : MCTC-00112-FS-noneAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs112 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp1-" __CDS_cpplang_core_version_name " : MCTC-00113-FS-countProp1-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs113 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp2-" __CDS_cpplang_core_version_name " : MCTC-00114-FS-countProp2-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs114 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp3-" __CDS_cpplang_core_version_name " : MCTC-00115-FS-countProp3-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs115 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-countProp4-" __CDS_cpplang_core_version_name " : MCTC-00116-FS-countProp4-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs116 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* MutableCollectionTestCase-FunctionalStatements-countPropLbd-" __CDS_cpplang_core_version_name " : MCTC-00117-FS-countPropLbd-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs117 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: count,
                /* predicate */     [comparedTo] (MapEntry<String, String>const & e) { return e.key().length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00118-FS-fewerThanTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs118 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs119 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs120 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00121-FS-fewerThanFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs121 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs122 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanTrue-" __CDS_cpplang_core_version_name " : MCTC-00123-FS-moreThanTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs123 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00124-FS-moreThanCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs124 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00125-FS-moreThanCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs125 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanFalse-" __CDS_cpplang_core_version_name " : MCTC-00126-FS-moreThanFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs126 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-" __CDS_cpplang_core_version_name " : MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs127 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostTrue-" __CDS_cpplang_core_version_name " : MCTC-00128-FS-atMostTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs128 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00129-FS-atMostCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs129 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00130-FS-atMostCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs130 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atMostFalse-" __CDS_cpplang_core_version_name " : MCTC-00131-FS-atMostFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs131 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastTrue-" __CDS_cpplang_core_version_name " : MCTC-00132-FS-atLeastTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs132 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseTrue-" __CDS_cpplang_core_version_name " : MCTC-00133-FS-atLeastCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs133 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastCloseFalse-" __CDS_cpplang_core_version_name " : MCTC-00134-FS-atLeastCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs134 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-atLeastFalse-" __CDS_cpplang_core_version_name " : MCTC-00135-FS-atLeastFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs135 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someExact-" __CDS_cpplang_core_version_name " : MCTC-00136-FS-someExact-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs136 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatements-someLessFalse-" __CDS_cpplang_core_version_name " : MCTC-00137-FS-someLessFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs137 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-someMoreFalse-" __CDS_cpplang_core_version_name " : MCTC-00138-FS-someMoreFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs138 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatements-forEachCount-" __CDS_cpplang_core_version_name " : MCTC-00139-FS-forEachCount-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs139 = { {"X", "x"}, {"YY" ,"Y"}, {"z", "Z"}, {"WW", "W"}, {"t", "TTT"} };
        MutableCollection < MapEntry < String, String > > const & MutableCollection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<String, String>const & e ) { if ( e.key().length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        MutableCollection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestCase-FunctionalStatements-forEachMutability-" __CDS_cpplang_core_version_name " : MCTC-00140-FS-forEachMutability-cpp-xx : IntArray */
        cds :: HashMap < String, String > fs140 = { {"a", "1"}, {"bb", "2"}, {"ccc", "3"}, {"dddd", "4"}, {"eeeee", "5"} };
        cds :: MutableCollection < MapEntry < String, String > > & MutableCollectionFS140 = fs140;
        auto actionfs140 = [] ( MapEntry < String, String > & e ) {
            /* e.key() = "ccc"; should not compile */
            e.value() = "8";
        };

        MutableCollectionFS140.forEach (actionfs140);
        auto countfs140 = MutableCollectionFS140.count ([](MapEntry < String, String > const & e) { return e.value() == "8"; });

        if ( countfs140 != fs140.size() ) {
            this->logError ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'MCTC-00140-FS-forEachMutability-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

#endif

    return allOk;
}
