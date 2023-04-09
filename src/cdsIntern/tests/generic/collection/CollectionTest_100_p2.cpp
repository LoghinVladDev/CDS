#include "CollectionTest.h"
#include "CollectionTest_100_common.hpp"

auto CollectionTest::tests_00100_00299_p2 () noexcept -> bool {
    
    bool allOk = true;

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* IntToIntLinkedHashMap */         this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs101 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs102 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs103 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs104 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs105 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs106 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs107 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs108 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs109 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs110 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {8, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs111 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs112 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs113 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs114 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs115 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs116 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs117 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [comparedTo] (MapEntry<int, int>const & e) { return e.key() > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs118 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs119 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs120 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs121 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs122 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs123 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs124 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs125 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs126 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs127 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs128 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs129 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs130 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs131 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs132 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs133 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs134 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs135 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs136 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs137 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs138 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntToIntLinkedHashMap */
        cds :: LinkedHashMap < int, int > fs139 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        Collection < MapEntry < int, int > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<int, int>const & e ) { if ( e.key() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntToIntTreeMap */               this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs101 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs102 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs103 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs104 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs105 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs106 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs107 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs108 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs109 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs110 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {8, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs111 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs112 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs113 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs114 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs115 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs116 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs117 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [comparedTo] (MapEntry<int, int>const & e) { return e.key() > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs118 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs119 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs120 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs121 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs122 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs123 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs124 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs125 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs126 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs127 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs128 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs129 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs130 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs131 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs132 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs133 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs134 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs135 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs136 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs137 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs138 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntToIntTreeMap */
        cds :: TreeMap < int, int > fs139 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        Collection < MapEntry < int, int > > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( MapEntry<int, int>const & e ) { if ( e.key() % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* StringArray */                   this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringArray", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringArray */
        cds :: Array < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringArray */
        cds :: Array < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringArray */
        cds :: Array < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringArray */
        cds :: Array < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringArray */
        cds :: Array < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringArray */
        cds :: Array < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringArray */
        cds :: Array < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringArray */
        cds :: Array < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringArray */
        cds :: Array < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringArray */
        cds :: Array < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringArray */
        cds :: Array < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringArray */
        cds :: Array < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringArray */
        cds :: Array < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringArray */
        cds :: Array < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringArray */
        cds :: Array < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringArray */
        cds :: Array < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringArray */
        cds :: Array < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringArray */
        cds :: Array < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringArray */
        cds :: Array < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringArray */
        cds :: Array < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringArray */
        cds :: Array < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringArray */
        cds :: Array < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringArray */
        cds :: Array < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringArray */
        cds :: Array < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringArray */
        cds :: Array < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringArray */
        cds :: Array < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringArray */
        cds :: Array < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringArray */
        cds :: Array < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringArray */
        cds :: Array < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringArray */
        cds :: Array < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringArray */
        cds :: Array < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringArray */
        cds :: Array < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringArray */
        cds :: Array < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
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
    /* StringLinkedList */              this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringLinkedList", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringLinkedList */
        cds :: LinkedList < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
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
    /* StringHashSet */                 this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringHashSet */
        cds :: HashSet < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
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
    /* StringTreeSet */                 this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringTreeSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs101 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs102 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs103 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs104 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: any,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs105 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs106 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs107 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs108 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: all,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs109 = { "aaa", "bbb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs110 = { "aaa", "bb", "ccc", "ddd", "eee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs111 = { "aaa", "bb", "ccc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs112 = { "aa", "bb", "cc", "dd", "ee" };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: none,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs113 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs114 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs115 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs116 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [] (String const & e) { return e.length() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs117 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: count,
                /* predicate */     [comparedTo] (String const & e) { return e.length() < comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs118 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs119 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs120 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs121 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs122 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: fewerThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs123 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs124 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs125 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs126 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs127 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: moreThan,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs128 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs129 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs130 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs131 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atMost,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs132 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs133 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs134 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs135 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: atLeast,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs136 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs137 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs138 = { "a", "bb", "ccc", "dddd", "eeeee" };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < String > :: some,
                /* predicate */     [] (String const & e) { return e.length() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : StringTreeSet */
        cds :: TreeSet < String > fs139 = { "xxx", "yy", "zzz", "tt", "www" };
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


#endif

    return allOk;
}
