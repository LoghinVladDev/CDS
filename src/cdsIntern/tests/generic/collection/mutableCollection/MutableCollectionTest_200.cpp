#include "MutableCollectionTest.h"
#include "MutableCollectionTest_100_200_common.hpp"

auto MutableCollectionTest::tests_00200_00349 () noexcept -> bool {

    bool allOk = true;

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* MutableCollectionTestGroup-FunctionalStatementsMemberFunction-cpp-xx : MCTG-00200-FSMF-cpp-xx - Tests MCTC-00201-FSMF to MCTC-00229-FSMF */
    this->executeSubtest ( "MutableCollectionTestGroup-FunctionalStatementsMemberFunction-" __CDS_cpplang_core_version_name " : MCTG-00200-FSMF-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-forEach-cpp-xx : MCTC-00201-FSMF-forEach-cpp-xx. Test Success if compile success */
        cds :: Array < String > fs201 = { "Ana", "are", "mere" };
        fs201.forEach ( [](String const & e){ (void) e.length(); } );
        fs201.forEach ( & String :: length );
        this->logOK ( "'MCTC-00201-FSMF-forEach-" __CDS_cpplang_core_version_name "' OK" );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-someEqual-cpp-xx : MCTC-00202-FSMF-someEqual-cpp-xx. */
        cds :: Array < String > fs202 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00202-FSMF-someEqual-cpp-xx",
                /* objUnderTest */  fs202,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-someLess-cpp-xx : MCTC-00203-FSMF-someLess-cpp-xx. */
        cds :: Array < String > fs203 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00203-FSMF-someLess-cpp-xx",
                /* objUnderTest */  fs203,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-someMore-cpp-xx : MCTC-00204-FSMF-someMore-cpp-xx. */
        cds :: Array < String > fs204 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00204-FSMF-someMore-cpp-xx",
                /* objUnderTest */  fs204,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atLeast-cpp-xx : MCTC-00205-FSMF-atLeast-cpp-xx. */
        cds :: Array < String > fs205 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00205-FSMF-atLeast-cpp-xx",
                /* objUnderTest */  fs205,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atLeastLess-cpp-xx : MCTC-00206-FSMF-atLeastLess-cpp-xx. */
        cds :: Array < String > fs206 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00206-FSMF-atLeastLess-cpp-xx",
                /* objUnderTest */  fs206,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atLeastMore-cpp-xx : MCTC-00207-FSMF-atLeastMore-cpp-xx. */
        cds :: Array < String > fs207 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00207-FSMF-atLeastMore-cpp-xx",
                /* objUnderTest */  fs207,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atMost-cpp-xx : MCTC-00208-FSMF-atMost-cpp-xx. */
        cds :: Array < String > fs208 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00208-FSMF-atMost-cpp-xx",
                /* objUnderTest */  fs208,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atMostLess-cpp-xx : MCTC-00209-FSMF-atMostLess-cpp-xx. */
        cds :: Array < String > fs209 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00209-FSMF-atMostLess-cpp-xx",
                /* objUnderTest */  fs209,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-atMostMore-cpp-xx : MCTC-00210-FSMF-atMostMore-cpp-xx. */
        cds :: Array < String > fs210 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00210-FSMF-atMostMore-cpp-xx",
                /* objUnderTest */  fs210,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-moreThan-cpp-xx : MCTC-00211-FSMF-moreThan-cpp-xx. */
        cds :: Array < String > fs211 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00211-FSMF-moreThan-cpp-xx",
                /* objUnderTest */  fs211,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-moreThanLess-cpp-xx : MCTC-00212-FSMF-moreThanLess-cpp-xx. */
        cds :: Array < String > fs212 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00212-FSMF-moreThanLess-cpp-xx",
                /* objUnderTest */  fs212,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-moreThanMore-cpp-xx : MCTC-00213-FSMF-moreThanMore-cpp-xx. */
        cds :: Array < String > fs213 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00213-FSMF-moreThanMore-cpp-xx",
                /* objUnderTest */  fs213,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-fewerThan-cpp-xx : MCTC-00214-FSMF-fewerThan-cpp-xx. */
        cds :: Array < String > fs214 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00214-FSMF-fewerThan-cpp-xx",
                /* objUnderTest */  fs214,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-fewerThanLess-cpp-xx : MCTC-00215-FSMF-fewerThanLess-cpp-xx. */
        cds :: Array < String > fs215 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00215-FSMF-fewerThanLess-cpp-xx",
                /* objUnderTest */  fs215,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-fewerThanMore-cpp-xx : MCTC-00216-FSMF-fewerThanMore-cpp-xx. */
        cds :: Array < String > fs216 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateCountedHandle (
                /* tName */         "MCTC-00216-FSMF-fewerThanMore-cpp-xx",
                /* objUnderTest */  fs216,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 3,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-countExact-cpp-xx : MCTC-00217-FSMF-countExact-cpp-xx. */
        cds :: Array < String > fs217 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle < Size > (
                /* tName */         "MCTC-00217-FSMF-countExact-cpp-xx",
                /* objUnderTest */  fs217,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: count,
                /* predicate */     & String :: empty,
                /* expectedRes. */  2
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyNone-cpp-xx : MCTC-00218-FSMF-anyNone-cpp-xx. */
        cds :: Array < String > fs218 = { "a", "b", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00218-FSMF-anyNone-cpp-xx",
                /* objUnderTest */  fs218,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyOne-cpp-xx : MCTC-00219-FSMF-anyOne-cpp-xx. */
        cds :: Array < String > fs219 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00219-FSMF-anyOne-cpp-xx",
                /* objUnderTest */  fs219,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyMore-cpp-xx : MCTC-00220-FSMF-anyMore-cpp-xx. */
        cds :: Array < String > fs220 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00220-FSMF-anyMore-cpp-xx",
                /* objUnderTest */  fs220,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-anyAll-cpp-xx : MCTC-00221-FSMF-anyAll-cpp-xx. */
        cds :: Array < String > fs221 = { "", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00221-FSMF-anyAll-cpp-xx",
                /* objUnderTest */  fs221,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allNone-cpp-xx : MCTC-00222-FSMF-allNone-cpp-xx. */
        cds :: Array < String > fs222 = { "a", "b", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00222-FSMF-allNone-cpp-xx",
                /* objUnderTest */  fs222,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allOne-cpp-xx : MCTC-00223-FSMF-allOne-cpp-xx. */
        cds :: Array < String > fs223 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00223-FSMF-allOne-cpp-xx",
                /* objUnderTest */  fs223,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allMore-cpp-xx : MCTC-00224-FSMF-allMore-cpp-xx. */
        cds :: Array < String > fs224 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00224-FSMF-allMore-cpp-xx",
                /* objUnderTest */  fs224,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-allAll-cpp-xx : MCTC-00225-FSMF-allAll-cpp-xx. */
        cds :: Array < String > fs225 = { "", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00225-FSMF-allAll-cpp-xx",
                /* objUnderTest */  fs225,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneNone-cpp-xx : MCTC-00226-FSMF-noneNone-cpp-xx. */
        cds :: Array < String > fs226 = { "a", "b", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00226-FSMF-noneNone-cpp-xx",
                /* objUnderTest */  fs226,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneOne-cpp-xx : MCTC-00227-FSMF-noneOne-cpp-xx. */
        cds :: Array < String > fs227 = { "a", "", "c" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00227-FSMF-noneOne-cpp-xx",
                /* objUnderTest */  fs227,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneMore-cpp-xx : MCTC-00228-FSMF-noneMore-cpp-xx. */
        cds :: Array < String > fs228 = { "a", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00228-FSMF-noneMore-cpp-xx",
                /* objUnderTest */  fs228,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* MutableCollectionTestCase-FunctionalStatementsMemberFunction-noneAll-cpp-xx : MCTC-00229-FSMF-noneAll-cpp-xx. */
        cds :: Array < String > fs229 = { "", "", "" };
        allOk = allOk && mutableCollectionTestCasePredicateHandle (
                /* tName */         "MCTC-00229-FSMF-noneAll-cpp-xx",
                /* objUnderTest */  fs229,
                /* testLib */       this,
                /* funcCaller */    & MutableCollection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );
    });

#endif

    return allOk;
}
