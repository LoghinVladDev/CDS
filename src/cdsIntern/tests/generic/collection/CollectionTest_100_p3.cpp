#include "CollectionTest.h"
#include "CollectionTest_100_common.hpp"

auto CollectionTest::tests_00100_00299_p3 () noexcept -> bool {
    
    bool allOk = true;

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* StringLinkedHashSet */           this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringLinkedHashSet */
        cds :: LinkedHashSet < String > const fs139 = { "xxx", "yy", "zzz", "tt", "www" };
        Collection < String > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( String const & e ) { if ( e.length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringToStringHashMap */         this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs101 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs102 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs103 = { {"x", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs104 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs105 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs106 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs107 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs108 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs109 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs110 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs111 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs112 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs113 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs114 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs115 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs116 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs117 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [comparedTo] (MapEntry<String, String>const & e) { return e.key().length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs118 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs119 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs120 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs121 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs122 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs123 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs124 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs125 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs126 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs127 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs128 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs129 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs130 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs131 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs132 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs133 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs134 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs135 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs136 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs137 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs138 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringToStringHashMap */
        cds :: HashMap < String, String > const fs139 = { {"X", "x"}, {"YY" ,"Y"}, {"z", "Z"}, {"WW", "W"}, {"t", "TTT"} };
        Collection < MapEntry < String, String > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<String, String>const & e ) { if ( e.key().length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringToStringLinkedHashMap */   this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs101 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs102 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs103 = { {"x", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs104 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs105 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs106 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs107 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs108 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs109 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs110 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs111 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs112 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs113 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs114 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs115 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs116 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs117 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [comparedTo] (MapEntry<String, String>const & e) { return e.key().length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs118 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs119 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs120 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs121 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs122 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs123 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs124 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs125 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs126 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs127 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs128 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs129 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs130 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs131 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs132 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs133 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs134 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs135 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs136 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs137 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs138 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringToStringLinkedHashMap */
        cds :: LinkedHashMap < String, String > const fs139 = { {"X", "x"}, {"YY" ,"Y"}, {"z", "Z"}, {"WW", "W"}, {"t", "TTT"} };
        Collection < MapEntry < String, String > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<String, String>const & e ) { if ( e.key().length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringToStringTreeMap */   this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs101 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs102 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs103 = { {"x", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs104 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: any,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs105 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs106 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs107 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs108 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: all,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs109 = { {"x", "x"}, {"y", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs110 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"w", "w"}, {"t", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs111 = { {"x", "x"}, {"yy", "y"}, {"z", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs112 = { {"xx", "x"}, {"yy", "y"}, {"zz", "z"}, {"ww", "w"}, {"tt", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: none,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs113 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs114 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs115 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs116 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs117 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: count,
                /* predicate */     [comparedTo] (MapEntry<String, String>const & e) { return e.key().length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs118 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs119 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs120 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs121 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs122 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: fewerThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs123 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs124 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs125 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs126 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs127 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: moreThan,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs128 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs129 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs130 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs131 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atMost,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs132 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs133 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs134 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs135 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: atLeast,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs136 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs137 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs138 = { {"a", "x"}, {"bb", "y"}, {"ccc", "z"}, {"dddd", "w"}, {"eeeee", "t"} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < String, String > > :: some,
                /* predicate */     [] (MapEntry<String, String>const & e) { return e.key().length() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringToStringTreeMap */
        cds :: TreeMap < String, String > const fs139 = { {"X", "x"}, {"YY" ,"Y"}, {"z", "Z"}, {"WW", "W"}, {"t", "TTT"} };
        Collection < MapEntry < String, String > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<String, String>const & e ) { if ( e.key().length() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });

#endif

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* CollectionTestGroup-FunctionalStatementsMemberFunction-cpp-xx : CTG-00200-FSMF-cpp-xx - Tests CTC-00201-FSMF to CTC-00229-FSMF */
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatementsMemberFunction-" __CDS_cpplang_core_version_name " : CTG-00200-FSMF-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatementsMemberFunction-forEach-cpp-xx : CTC-00201-FSMF-forEach-cpp-xx. Test Success if compile success */
        cds :: Array < String > const fs201 = { "Ana", "are", "mere" };
        fs201.forEach ( [](String const & e){ (void) e.length(); } );
        fs201.forEach ( & String :: length );
        this->logOK ( "'CTC-00201-FSMF-forEach-" __CDS_cpplang_core_version_name "' OK" );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someEqual-cpp-xx : CTC-00202-FSMF-someEqual-cpp-xx. */
        cds :: Array < String > const fs202 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00202-FSMF-someEqual-cpp-xx",
                /* objUnderTest */  fs202,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someLess-cpp-xx : CTC-00203-FSMF-someLess-cpp-xx. */
        cds :: Array < String > const fs203 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00203-FSMF-someLess-cpp-xx",
                /* objUnderTest */  fs203,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-someMore-cpp-xx : CTC-00204-FSMF-someMore-cpp-xx. */
        cds :: Array < String > const fs204 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00204-FSMF-someMore-cpp-xx",
                /* objUnderTest */  fs204,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeast-cpp-xx : CTC-00205-FSMF-atLeast-cpp-xx. */
        cds :: Array < String > const fs205 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00205-FSMF-atLeast-cpp-xx",
                /* objUnderTest */  fs205,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeastLess-cpp-xx : CTC-00206-FSMF-atLeastLess-cpp-xx. */
        cds :: Array < String > const fs206 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00206-FSMF-atLeastLess-cpp-xx",
                /* objUnderTest */  fs206,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atLeastMore-cpp-xx : CTC-00207-FSMF-atLeastMore-cpp-xx. */
        cds :: Array < String > const fs207 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00207-FSMF-atLeastMore-cpp-xx",
                /* objUnderTest */  fs207,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMost-cpp-xx : CTC-00208-FSMF-atMost-cpp-xx. */
        cds :: Array < String > const fs208 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00208-FSMF-atMost-cpp-xx",
                /* objUnderTest */  fs208,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMostLess-cpp-xx : CTC-00209-FSMF-atMostLess-cpp-xx. */
        cds :: Array < String > const fs209 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00209-FSMF-atMostLess-cpp-xx",
                /* objUnderTest */  fs209,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-atMostMore-cpp-xx : CTC-00210-FSMF-atMostMore-cpp-xx. */
        cds :: Array < String > const fs210 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00210-FSMF-atMostMore-cpp-xx",
                /* objUnderTest */  fs210,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThan-cpp-xx : CTC-00211-FSMF-moreThan-cpp-xx. */
        cds :: Array < String > const fs211 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00211-FSMF-moreThan-cpp-xx",
                /* objUnderTest */  fs211,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThanLess-cpp-xx : CTC-00212-FSMF-moreThanLess-cpp-xx. */
        cds :: Array < String > const fs212 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00212-FSMF-moreThanLess-cpp-xx",
                /* objUnderTest */  fs212,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-moreThanMore-cpp-xx : CTC-00213-FSMF-moreThanMore-cpp-xx. */
        cds :: Array < String > const fs213 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00213-FSMF-moreThanMore-cpp-xx",
                /* objUnderTest */  fs213,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThan-cpp-xx : CTC-00214-FSMF-fewerThan-cpp-xx. */
        cds :: Array < String > const fs214 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00214-FSMF-fewerThan-cpp-xx",
                /* objUnderTest */  fs214,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThanLess-cpp-xx : CTC-00215-FSMF-fewerThanLess-cpp-xx. */
        cds :: Array < String > const fs215 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00215-FSMF-fewerThanLess-cpp-xx",
                /* objUnderTest */  fs215,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-fewerThanMore-cpp-xx : CTC-00216-FSMF-fewerThanMore-cpp-xx. */
        cds :: Array < String > const fs216 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00216-FSMF-fewerThanMore-cpp-xx",
                /* objUnderTest */  fs216,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     & String :: empty,
                /* expectedCount */ 3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-countExact-cpp-xx : CTC-00217-FSMF-countExact-cpp-xx. */
        cds :: Array < String > const fs217 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00217-FSMF-countExact-cpp-xx",
                /* objUnderTest */  fs217,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     & String :: empty,
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyNone-cpp-xx : CTC-00218-FSMF-anyNone-cpp-xx. */
        cds :: Array < String > const fs218 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00218-FSMF-anyNone-cpp-xx",
                /* objUnderTest */  fs218,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyOne-cpp-xx : CTC-00219-FSMF-anyOne-cpp-xx. */
        cds :: Array < String > const fs219 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00219-FSMF-anyOne-cpp-xx",
                /* objUnderTest */  fs219,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyMore-cpp-xx : CTC-00220-FSMF-anyMore-cpp-xx. */
        cds :: Array < String > const fs220 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00220-FSMF-anyMore-cpp-xx",
                /* objUnderTest */  fs220,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-anyAll-cpp-xx : CTC-00221-FSMF-anyAll-cpp-xx. */
        cds :: Array < String > const fs221 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00221-FSMF-anyAll-cpp-xx",
                /* objUnderTest */  fs221,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allNone-cpp-xx : CTC-00222-FSMF-allNone-cpp-xx. */
        cds :: Array < String > const fs222 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00222-FSMF-allNone-cpp-xx",
                /* objUnderTest */  fs222,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allOne-cpp-xx : CTC-00223-FSMF-allOne-cpp-xx. */
        cds :: Array < String > const fs223 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00223-FSMF-allOne-cpp-xx",
                /* objUnderTest */  fs223,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allMore-cpp-xx : CTC-00224-FSMF-allMore-cpp-xx. */
        cds :: Array < String > const fs224 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00224-FSMF-allMore-cpp-xx",
                /* objUnderTest */  fs224,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-allAll-cpp-xx : CTC-00225-FSMF-allAll-cpp-xx. */
        cds :: Array < String > const fs225 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00225-FSMF-allAll-cpp-xx",
                /* objUnderTest */  fs225,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneNone-cpp-xx : CTC-00226-FSMF-noneNone-cpp-xx. */
        cds :: Array < String > const fs226 = { "a", "b", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00226-FSMF-noneNone-cpp-xx",
                /* objUnderTest */  fs226,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneOne-cpp-xx : CTC-00227-FSMF-noneOne-cpp-xx. */
        cds :: Array < String > const fs227 = { "a", "", "c" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00227-FSMF-noneOne-cpp-xx",
                /* objUnderTest */  fs227,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneMore-cpp-xx : CTC-00228-FSMF-noneMore-cpp-xx. */
        cds :: Array < String > const fs228 = { "a", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00228-FSMF-noneMore-cpp-xx",
                /* objUnderTest */  fs228,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatementsMemberFunction-noneAll-cpp-xx : CTC-00229-FSMF-noneAll-cpp-xx. */
        cds :: Array < String > const fs229 = { "", "", "" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00229-FSMF-noneAll-cpp-xx",
                /* objUnderTest */  fs229,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     & String :: empty,
                /* expectedRes. */  false
        );
    });

#endif

    return allOk;
}
