#include "CollectionTest.h"
#include "CollectionTest_100_common.hpp"
#include <initializer_list>

namespace {
    template <typename E, typename R>
    auto mSingleTD (
            cds::StringView const & name, cds::Array <E> const & e, R ex, Function <R (E)> const & f
    ) noexcept -> cds::Tuple <cds::StringView, cds::Array <E>, R, Function <R (E)>> {
        return {name, e, ex, f};
    }

    template <typename C, typename E, typename R>
    auto makeTestDataItems (
            cds::Array <cds::Tuple <cds::StringView, cds::Array <E>, R, Function <R (E)>>> const & data
    ) noexcept -> cds::Array <cds::Tuple <cds::StringView, C, R, Function <R (E)>>> {

        cds::Array <cds::Tuple <cds::StringView, C, R, Function <R (E)>>> res;
        for (auto const & e : data) {
            C converted;
            for (auto const & sConv : e.template get <1> ()) {
                converted.pushBack (sConv);
            }

            res.emplaceBack (e.template get<0> (), converted, e.template get<2>(), e.template get <3> ());
        }

        return res;
    }

}

auto CollectionTest::tests_00100_00299_p1 () noexcept -> bool {
    
    bool allOk = true;
    auto makeiBData = [this] (Size const tNo, cds::StringView const name, CPred <int, Function <bool (int)>, bool> const & pfn) {
        return TBaseData <int, bool> (this, tNo, name, pfn);
    };

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else

    /* CollectionTestGroup-FunctionalStatements-cpp-xx : CTG-00100-FS-cpp-xx - Tests CTC-00101-FS to CTC-10139-FS - located directly below due to varability of these tests */
    /* IntArray */
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntArray", [& allOk, & makeiBData, this] {

        using E = int;
        using R = bool;
        using C = cds::Array <E>;

        auto const tId1 = 101;
        auto const tId2 = 105;
        auto const tId3 = 109;

        std::initializer_list<E> const td1 = {1, 3, 5, 7, 9};
        std::initializer_list<E> const td2 = {1, 4, 5, 7, 9};
        std::initializer_list<E> const td3 = { 1, 4, 5, 6, 8 };
        std::initializer_list<E> const td4 = { 2, 4, 6, 8, 10 };

        auto const p1 = [](E const & e) {return e % 2 == 0;};

        allOk = allOk && collectionTestGroupPredicate <E, C, Function <R (E)>, R> (
                makeiBData(tId1, "any", & Collection <E> :: any), 
                makeTestDataItems <C, E, R> ({
                        mSingleTD <E, R> ("None", td1, false, p1),
                        mSingleTD <E, R> ("One", td2, true, p1),
                        mSingleTD <E, R> ("More", td3, true, p1),
                        mSingleTD <E, R> ("All", td4, true, p1),
                })
        );

        allOk = allOk && collectionTestGroupPredicate <E, C, Function <R (E)>, R> (
                makeiBData(tId2, "all", & Collection <E> :: all), 
                makeTestDataItems <C, E, R> ({
                        mSingleTD <E, R> ("None", td1, false, p1),
                        mSingleTD <E, R> ("One", td2, false, p1),
                        mSingleTD <E, R> ("More", td3, false, p1),
                        mSingleTD <E, R> ("More", td4, true, p1),
                })
        );

        allOk = allOk && collectionTestGroupPredicate <E, C, Function <R (E)>, R> (
                makeiBData(tId3, "none", & Collection <E> :: none), 
                makeTestDataItems <C, E, R> ({
                        mSingleTD <E, R> ("None", td1, true, p1),
                        mSingleTD <E, R> ("One", td2, false, p1),
                        mSingleTD <E, R> ("More", td3, false, p1),
                        mSingleTD <E, R> ("More", td4, false, p1),
                })
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntArray */
        cds :: Array < int > const fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntArray */
        cds :: Array < int > const fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntArray */
        cds :: Array < int > const fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntArray */
        cds :: Array < int > const fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntArray */
        cds :: Array < int > const fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntArray */
        cds :: Array < int > const fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntArray */
        cds :: Array < int > const fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntArray */
        cds :: Array < int > const fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntArray */
        cds :: Array < int > const fs139 = { 1, 2, 3, 4, 5 };
        Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntLinkedList */                 this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntLinkedList", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntLinkedList */
        cds :: LinkedList < int > const fs139 = { 1, 2, 3, 4, 5 };
        Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntHashSet */                    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntHashSet */
        cds :: HashSet < int > const fs139 = { 1, 2, 3, 4, 5 };
        Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntTreeSet */                    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntTreeSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs139 = { 1, 2, 3, 4, 5 };
        Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntTreeSet */                    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : IntLinkedHashSet */
        cds :: LinkedHashSet < int > const fs101 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : IntTreeSet */
        cds :: LinkedHashSet < int > const fs102 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs103 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs104 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: any,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs105 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs106 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs107 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs108 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: all,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs109 = { 1, 3, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs110 = { 1, 4, 5, 7, 9 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs111 = { 1, 4, 5, 6, 8 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs112 = { 2, 4, 6, 8, 10 };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: none,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs113 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs114 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs115 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs116 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [] (int e) { return e >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs117 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: count,
                /* predicate */     [comparedTo] (int e) { return e > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs118 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs119 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs120 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs121 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs122 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: fewerThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs123 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs124 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs125 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs126 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs127 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: moreThan,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs128 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs129 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs130 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs131 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atMost,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs132 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs133 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs134 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs135 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: atLeast,
                /* predicate */     [] (int e) { return e < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs136 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs137 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs138 = { 1, 2, 3, 4, 5 };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < int > :: some,
                /* predicate */     [] (int e) { return e % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntTreeSet */
        cds :: TreeSet < int > const fs139 = { 1, 2, 3, 4, 5 };
        Collection < int > const & collection = fs139;
        Size count = 0;
        auto action = [& count] ( int e ) { if ( e % 2 == 0 ) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            this->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    /* IntToIntHashMap */               this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [& allOk, this] {

        /* CollectionTestCase-FunctionalStatements-anyNoneApplicable-cpp-xx : CTC-00101-FS-anyNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs101 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00101-FS-anyNone-cpp-xx",
                /* objUnderTest */  fs101,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-anyOneApplicable-cpp-xx : CTC-00102-FS-anyOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs102 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00102-FS-anyOne-cpp-xx",
                /* objUnderTest */  fs102,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyMoreApplicable-cpp-xx : CTC-00103-FS-anyMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs103 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00103-FS-anyMore-cpp-xx",
                /* objUnderTest */  fs103,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-anyAllApplicable-cpp-xx : CTC-00104-FS-anyAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs104 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00104-FS-anyAll-cpp-xx",
                /* objUnderTest */  fs104,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: any,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-allNoneApplicable-cpp-xx : CTC-00105-FS-allNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs105 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00105-FS-allNone-cpp-xx",
                /* objUnderTest */  fs105,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allOneApplicable-cpp-xx : CTC-00106-FS-allOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs106 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00106-FS-allOne-cpp-xx",
                /* objUnderTest */  fs106,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allMoreApplicable-cpp-xx : CTC-00107-FS-allMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs107 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00107-FS-allMore-cpp-xx",
                /* objUnderTest */  fs107,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-allAllApplicable-cpp-xx : CTC-00108-FS-allAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs108 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00108-FS-allAll-cpp-xx",
                /* objUnderTest */  fs108,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: all,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneNoneApplicable-cpp-xx : CTC-00109-FS-noneNone-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs109 = { {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00109-FS-noneNone-cpp-xx",
                /* objUnderTest */  fs109,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-noneOneApplicable-cpp-xx : CTC-00110-FS-noneOne-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs110 = { {1, 1}, {4, 3}, {5, 5}, {7, 7}, {8, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00110-FS-noneOne-cpp-xx",
                /* objUnderTest */  fs110,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneMoreApplicable-cpp-xx : CTC-00111-FS-noneMore-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs111 = { {1, 1}, {4, 3}, {5, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00111-FS-noneMore-cpp-xx",
                /* objUnderTest */  fs111,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-noneAllApplicable-cpp-xx : CTC-00112-FS-noneAll-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs112 = { {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9} };
        allOk = allOk && collectionTestCasePredicateHandle (
                /* tName */         "CTC-00112-FS-noneAll-cpp-xx",
                /* objUnderTest */  fs112,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: none,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-countProp1-cpp-xx : CTC-00113-FS-countProp1-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs113 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00113-FS-countProp1-cpp-xx",
                /* objUnderTest */  fs113,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp2-cpp-xx : CTC-00114-FS-countProp2-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs114 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00114-FS-countProp2-cpp-xx",
                /* objUnderTest */  fs114,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 1; },
                /* expectedRes. */  3
        );

        /* CollectionTestCase-FunctionalStatements-countProp3-cpp-xx : CTC-00115-FS-countProp3-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs115 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00115-FS-countProp3-cpp-xx",
                /* objUnderTest */  fs115,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-countProp4-cpp-xx : CTC-00116-FS-countProp4-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs116 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00116-FS-countProp4-cpp-xx",
                /* objUnderTest */  fs116,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() >= 2; },
                /* expectedRes. */  4
        );

        int comparedTo = 3;
        /* CollectionTestCase-FunctionalStatements-countPropLbd-cpp-xx : CTC-00117-FS-countPropLbd-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs117 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateHandle < Size > (
                /* tName */         "CTC-00117-FS-countPropLbd-cpp-xx",
                /* objUnderTest */  fs117,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: count,
                /* predicate */     [comparedTo] (MapEntry<int, int>const & e) { return e.key() > comparedTo; },
                /* expectedRes. */  2
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanTrue-cpp-xx : CTC-00118-FS-fewerThanTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs118 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00118-FS-fewerThanTrue-cpp-xx",
                /* objUnderTest */  fs118,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseTrue-cpp-xx : CTC-00119-FS-fewerThanCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs119 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00119-FS-fewerThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs119,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCloseFalse-cpp-xx : CTC-00120-FS-fewerThanCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs120 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00120-FS-fewerThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs120,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanFalse-cpp-xx : CTC-00121-FS-fewerThanFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs121 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00121-FS-fewerThanFalse-cpp-xx",
                /* objUnderTest */  fs121,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-fewerThanCompletelyFalse-cpp-xx : CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs122 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00122-FS-fewerThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs122,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: fewerThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanTrue-cpp-xx : CTC-00123-FS-moreThanTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs123 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00123-FS-moreThanTrue-cpp-xx",
                /* objUnderTest */  fs123,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseTrue-cpp-xx : CTC-00124-FS-moreThanCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs124 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00124-FS-moreThanCloseTrue-cpp-xx",
                /* objUnderTest */  fs124,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCloseFalse-cpp-xx : CTC-00125-FS-moreThanCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs125 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00125-FS-moreThanCloseFalse-cpp-xx",
                /* objUnderTest */  fs125,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanFalse-cpp-xx : CTC-00126-FS-moreThanFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs126 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00126-FS-moreThanFalse-cpp-xx",
                /* objUnderTest */  fs126,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-moreThanCompletelyFalse-cpp-xx : CTC-00127-FS-moreThanCompletelyFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs127 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00127-FS-moreThanCompletelyFalse-cpp-xx",
                /* objUnderTest */  fs127,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: moreThan,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       20,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostTrue-cpp-xx : CTC-00128-FS-atMostTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs128 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00128-FS-atMostTrue-cpp-xx",
                /* objUnderTest */  fs128,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseTrue-cpp-xx : CTC-00129-FS-atMostCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs129 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00129-FS-atMostCloseTrue-cpp-xx",
                /* objUnderTest */  fs129,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atMostCloseFalse-cpp-xx : CTC-00130-FS-atMostCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs130 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00130-FS-atMostCloseFalse-cpp-xx",
                /* objUnderTest */  fs130,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atMostFalse-cpp-xx : CTC-00131-FS-atMostFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs131 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00131-FS-atMostFalse-cpp-xx",
                /* objUnderTest */  fs131,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atMost,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       0,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastTrue-cpp-xx : CTC-00132-FS-atLeastTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs132 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00132-FS-atLeastTrue-cpp-xx",
                /* objUnderTest */  fs132,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       1,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseTrue-cpp-xx : CTC-00133-FS-atLeastCloseTrue-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs133 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00133-FS-atLeastCloseTrue-cpp-xx",
                /* objUnderTest */  fs133,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-atLeastCloseFalse-cpp-xx : CTC-00134-FS-atLeastCloseFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs134 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00134-FS-atLeastCloseFalse-cpp-xx",
                /* objUnderTest */  fs134,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-atLeastFalse-cpp-xx : CTC-00135-FS-atLeastFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs135 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00135-FS-atLeastFalse-cpp-xx",
                /* objUnderTest */  fs135,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: atLeast,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() < 3; },
                /* desired */       4,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someExact-cpp-xx : CTC-00136-FS-someExact-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs136 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00136-FS-someExact-cpp-xx",
                /* objUnderTest */  fs136,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       2,
                /* expectedRes. */  true
        );

        /* CollectionTestCase-FunctionalStatements-someLessFalse-cpp-xx : CTC-00137-FS-someLessFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs137 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00137-FS-someLessFalse-cpp-xx",
                /* objUnderTest */  fs137,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       1,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-someMoreFalse-cpp-xx : CTC-00138-FS-someMoreFalse-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs138 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
        allOk = allOk && collectionTestCasePredicateCountedHandle (
                /* tName */         "CTC-00138-FS-someMoreFalse-cpp-xx",
                /* objUnderTest */  fs138,
                /* testLib */       this,
                /* funcCaller */    & Collection < MapEntry < int, int > > :: some,
                /* predicate */     [] (MapEntry<int, int>const & e) { return e.key() % 2 == 0; },
                /* desired */       3,
                /* expectedRes. */  false
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntToIntHashMap */
        cds :: HashMap < int, int > const fs139 = { {1, 1}, {2 ,2}, {3, 3}, {4, 4}, {5, 5} };
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

#endif

    return allOk;
}
