#include "CollectionTest.h"
#include "CollectionTest_100_common.hpp"
#include <initializer_list>

auto CollectionTest::tests_00100_00299_p2 () noexcept -> bool {

    bool allOk = true;

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function poStringer acquisiton code to standard.")
#else

    Size const exOne = 1;
    Size const exTwo = 2;
    Size const exThree = 3;
    Size const exFour = 4;

    auto const tId1 = 101;
    auto const tId2 = 105;
    auto const tId3 = 109;
    auto const tId4 = 113;
    auto const tId5 = 118;
    auto const tId6 = 123;
    auto const tId7 = 128;
    auto const tId8 = 132;
    auto const tId9 = 136;

    std::initializer_list<String> const td1 = {"aaa", "bbb", "ccc", "ddd", "eee"};
    std::initializer_list<String> const td2 = {"aaa", "bb", "ccc", "ddd", "eee"};
    std::initializer_list<String> const td3 = {"aaa", "bb", "ccc", "dd", "ee"};
    std::initializer_list<String> const td4 = {"aa", "bb", "cc", "dd", "ee"};
    std::initializer_list<String> const td5 = {"a", "bb", "ccc", "dddd", "eeeee"};

    std::initializer_list<MapEntry <String, String>> const td6 = {{"aaa", "aaa"}, {"bbb", "bbb"}, {"ccc", "ccc"}, {"ddd", "ddd"}, {"eee", "eee"}};
    std::initializer_list<MapEntry <String, String>> const td7 = {{"aaa", "aaa"}, {"bb", "bb"}, {"ccc", "ccc"}, {"ddd", "ddd"}, {"eee", "eee"}};
    std::initializer_list<MapEntry <String, String>> const td8 = {{"aaa", "aaa"}, {"bb", "bb"}, {"ccc", "ccc"}, {"dd", "dd"}, {"ee", "ee"}};
    std::initializer_list<MapEntry <String, String>> const td9 = {{"aa", "aa"}, {"bb", "bb"}, {"cc", "cc"}, {"dd", "dd"}, {"ee", "ee"}};
    std::initializer_list<MapEntry <String, String>> const td10 = {{"a", "a"}, {"bb", "bb"}, {"ccc", "ccc"}, {"dddd", "dddd"}, {"eeeee", "eeeee"}};

    Size const comparedToLbdCap = 3;

    auto const p1 = [](String const & e) {return (e.length() % 2) == 0;};
    auto const p2 = [](String const & e) {return (e.length() % 2) == 1;};
    auto const p3 = [](String const & e) {return e.length() < 3;};
    auto const p4 = [](String const & e) {return e.length() >= 2;};
    auto const p5 = [comparedToLbdCap] (String const & e) {return e.length() > comparedToLbdCap; };

    auto const p6 = [](MapEntry <String, String> const & e) {return (e.key().length() % 2) == 0;};
    auto const p7 = [](MapEntry <String, String> const & e) {return (e.key().length() % 2) == 1;};
    auto const p8 = [](MapEntry <String, String> const & e) {return e.key().length() < 3;};
    auto const p9 = [](MapEntry <String, String> const & e) {return e.key().length() >= 2;};
    auto const p10 = [comparedToLbdCap] (MapEntry <String, String> const & e) {return e.key().length() > comparedToLbdCap; };

    /* StringArray */ 
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringArray", [&] {
        allOk = allOk && allTest_100 <String, cds::Array <String>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* StringLinkedList */                 
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringLinkedList", [&] {
        allOk = allOk && allTest_100 <String, cds::LinkedList <String>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });
    
    /* StringHashSet */                    
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringHashSet", [&] {
        allOk = allOk && allTest_100 <String, cds::HashSet <String>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* StringTreeSet */                    
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringTreeSet", [&] {
        allOk = allOk && allTest_100 <String, cds::TreeSet <String>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* StringLinkedHashSet */
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [&] {
        allOk = allOk && allTest_100 <String, cds::LinkedHashSet <String>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* StringToStringHashMap */               
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [&] {
        allOk = allOk && allTest_100 <MapEntry <String, String>, cds::HashMap <String, String>> (
                this,
                {td6, td7, td8, td9, td10},
                {p6, p7, p8, p9, p10},
                comparedToLbdCap
        );
    });

    /* StringToStringTreeMap */               
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [&] {
        allOk = allOk && allTest_100 <MapEntry <String, String>, cds::TreeMap <String, String>> (
                this,
                {td6, td7, td8, td9, td10},
                {p6, p7, p8, p9, p10},
                comparedToLbdCap
        );
    });

    /* StringToStringLinkedHashMap */               
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [&] {
        allOk = allOk && allTest_100 <MapEntry <String, String>, cds::LinkedHashMap <String, String>> (
                this,
                {td6, td7, td8, td9, td10},
                {p6, p7, p8, p9, p10},
                comparedToLbdCap
        );
    });

#endif

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function poStringer acquisiton code to standard.")
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
