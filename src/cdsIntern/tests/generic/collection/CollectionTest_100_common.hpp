#ifndef COLLECTION_TEST_100_COMMON_H
#define COLLECTION_TEST_100_COMMON_H

#include "CollectionTest.h"
#include "CollectionTest_common.hpp"
#include <CDS/Tuple>
#include <CDS/Function>
#include <initializer_list>

inline namespace ctc100 {

    using cds::Tuple;
    using cds::Collection;
    using cds::makeTuple;
    using cds::Size;
    using cds::Function;


    template <typename E, typename F, typename R>
    using CPred = R (cds::Collection<E> :: *) (F const &) const;

    template <typename E, typename F>
    using CCountedPred = bool (cds::Collection<E> :: *) (Size, F const &) const;

    template <
            typename __PredicateReturnType, /* NOLINT(bugprone-reserved-identifier) */
            typename __MemberType,          /* NOLINT(bugprone-reserved-identifier) */
            typename __Predicate            /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestCasePredicateHandle (
            StringLiteral testCaseName,
            Collection < __MemberType > const & collection,
            Test                                        const * pTestLib,
            auto ( Collection < __MemberType > :: * pFunctionalCall ) ( __Predicate const & ) const -> __PredicateReturnType,
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
            typename __PredicateReturnType, /* NOLINT(bugprone-reserved-identifier) */
            typename __MemberType,          /* NOLINT(bugprone-reserved-identifier) */
            typename __Predicate            /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestCasePredicateCountedHandle (
            StringLiteral testCaseName,
            Collection < __MemberType > const & collection,
            Test                                             const * pTestLib,
            auto ( Collection < __MemberType > :: * pFunctionalCall ) ( Size, __Predicate const & ) const -> __PredicateReturnType,
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

    template <typename E, typename R>
    using TBaseData = Tuple <
            Test const *,
            Size, cds::StringView,
            CPred <E, Function <bool (E)>, R>
    >;

    template <typename E>
    using TCountedBaseData = Tuple <
            Test const *,
            Size, cds::StringView,
            CCountedPred <E, Function <bool (E)>>
    >;

    template <typename E, typename C, typename R>
    using STestData = Tuple <
            cds::StringView, C, R, Function <bool (E)>
    >;

    template <typename E, typename C>
    using SCountedTestData = Tuple <
            cds::StringView, C, Size, bool, Function <bool (E)>
    >;

    template <
            typename E,
            typename C,
            typename R 
    > auto collectionTestGroupPredicate (
            TBaseData <E, R> const & bData,
            cds::Array <STestData <E, C, R>> const & items
    ) noexcept -> bool {

        auto const * const pTestLib = bData.template get <0> ();
        auto tId = bData.template get <1> ();
        auto const & gName = bData.template get<2> ();
        auto const & pfn = bData.template get<3> ();

        for (auto const & t : items) {
            auto const & tName = t.template get <0> ();
            auto const & obj = t.template get <1> ();
            auto const e = t.template get <2> ();
            auto const & f = t.template get <3> ();

            auto const tFName = 
                    cds::String ("CTC-00") + tId + 
                    "-FS-" + gName + tName + "-" + __CDS_cpplang_core_version_name;

            ++ tId;
            auto const r = collectionTestCasePredicateHandle (
                    tFName.cStr(),
                    obj,
                    pTestLib,
                    pfn,
                    f,
                    e
            );

            if (! r) {
                return false;
            }
        }  

        return true;
    }

    template <
            typename E,
            typename C
    > auto collectionTestGroupPredicateCounted (
            TCountedBaseData <E> const & bData,
            cds::Array <SCountedTestData <E, C>> const & items
    ) noexcept -> bool {

        auto const * const pTestLib = bData.template get <0> ();
        auto tId = bData.template get <1> ();
        auto const & gName = bData.template get<2> ();
        auto const & pfn = bData.template get<3> ();

        for (auto const & t : items) {
            auto const & tName = t.template get <0> ();
            auto const & obj = t.template get <1> ();
            auto const desired = t.template get <2> ();
            auto const expectedRes = t.template get <3> ();
            auto const & f = t.template get <4> ();

            auto const tFName = 
                    cds::String ("CTC-00") + tId + 
                    "-FS-" + gName + tName + "-" + __CDS_cpplang_core_version_name;

            ++ tId;
            auto const r = collectionTestCasePredicateCountedHandle (
                    tFName.cStr(),
                    obj,
                    pTestLib,
                    pfn,
                    f,
                    desired,
                    expectedRes
            );

            if (! r) {
                return false;
            }
        }  

        return true;
    }
    
    template <typename E, typename R>
    auto mSingleTD (
            cds::StringView const & name, cds::Array <E> const & e, R ex, Function <bool (E)> const & f
    ) noexcept -> cds::Tuple <cds::StringView, cds::Array <E>, R, Function <bool (E)>> {
        return {name, e, ex, f};
    }

    template <typename E>
    auto countedTD (
            cds::StringView const & name, cds::Array <E> const & e, Size d, bool ex, Function <bool (E)> const & f
    ) noexcept -> cds::Tuple <cds::StringView, cds::Array <E>, Size, bool, Function <bool (E)>> {
        return {name, e, d, ex, f};
    }

    template <typename C, typename E, typename R>
    auto makeTestDataItems (
            cds::Array <cds::Tuple <cds::StringView, cds::Array <E>, R, Function <bool (E)>>> const & data
    ) noexcept -> cds::Array <cds::Tuple <cds::StringView, C, R, Function <bool (E)>>> {

        cds::Array <cds::Tuple <cds::StringView, C, R, Function <bool (E)>>> res;
        for (auto const & e : data) {
            C converted;
            for (auto const & sConv : e.template get <1> ()) {
                converted.insert (sConv);
            }

            res.emplaceBack (e.template get<0> (), converted, e.template get<2>(), e.template get <3> ());
        }

        return res;
    }

    template <typename C, typename E>
    auto makeCountedTestDataItems (
            cds::Array <cds::Tuple <cds::StringView, cds::Array <E>, Size, bool, Function <bool (E)>>> const & data
    ) noexcept -> cds::Array <cds::Tuple <cds::StringView, C, Size, bool, Function <bool (E)>>> {

        cds::Array <cds::Tuple <cds::StringView, C, Size, bool, Function <bool (E)>>> res;
        for (auto const & e : data) {
            C converted;
            for (auto const & sConv : e.template get <1> ()) {
                converted.insert (sConv);
            }

            res.emplaceBack (e.template get<0> (), converted, e.template get<2>(), e.template get <3> (), e.template get <4> ());
        }

        return res;
    }

    template <typename E, typename C>
    auto allTest_100 (
            Test const * const pTestLib,
            std::initializer_list<std::initializer_list<E>> const & dataSets,
            std::initializer_list<cds::Function <bool(E)>> const & funcs,
            Size const lambdaCap = 3
    ) noexcept -> bool {

        auto makeiBData = [pTestLib] (Size const tNo, cds::StringView const name, CPred <E, Function <bool (E)>, bool> const & pfn) {
            return TBaseData <E, bool> (pTestLib, tNo, name, pfn);
        };
        auto makeiSData = [pTestLib] (Size const tNo, cds::StringView const name, CPred <E, Function <bool (E)>, Size> const & pfn) {
            return TBaseData <E, Size> (pTestLib, tNo, name, pfn);
        };
        auto makeiCData = [pTestLib] (Size const tNo, cds::StringView const name, CCountedPred <E, Function <bool (E)>> const & pfn) {
            return TCountedBaseData <E> (pTestLib, tNo, name, pfn);
        };
    
        Size const exOne = 1;
        Size const exTwo = 2;
        Size const exThree = 3;
        Size const exFour = 4;
        Size const exFive = 5;

        auto const tId1 = 101;
        auto const tId2 = 105;
        auto const tId3 = 109;
        auto const tId4 = 113;
        auto const tId5 = 118;
        auto const tId6 = 123;
        auto const tId7 = 128;
        auto const tId8 = 132;
        auto const tId9 = 136;

        auto dIt = dataSets.begin();
        auto const & td1 = * dIt;
        ++ dIt;
        auto const & td2 = * dIt;
        ++ dIt;
        auto const & td3 = * dIt;
        ++ dIt;
        auto const & td4 = * dIt;
        ++ dIt;
        auto const & td5 = * dIt;

        auto fIt = funcs.begin();
        auto const & p1 = * fIt;
        ++ fIt;
        auto const & p2 = * fIt;
        ++ fIt;
        auto const & p3 = * fIt;
        ++ fIt;
        auto const & p4 = * fIt;
        ++ fIt;
        auto const & p5 = * fIt;

        using R = bool;

        bool allOk = true;

        allOk = allOk && collectionTestGroupPredicate <E, C> (
                makeiBData(tId1, "any", & Collection <E> :: any), 
                makeTestDataItems <C, E, R> ({
                        mSingleTD <E, R> ("None", td1, false, p1),
                        mSingleTD <E, R> ("One", td2, true, p1),
                        mSingleTD <E, R> ("More", td3, true, p1),
                        mSingleTD <E, R> ("All", td4, true, p1),
                })
        );

        allOk = allOk && collectionTestGroupPredicate <E, C> (
                makeiBData(tId2, "all", & Collection <E> :: all), 
                makeTestDataItems <C, E, R> ({
                        mSingleTD <E, R> ("None", td1, false, p1),
                        mSingleTD <E, R> ("One", td2, false, p1),
                        mSingleTD <E, R> ("More", td3, false, p1),
                        mSingleTD <E, R> ("More", td4, true, p1),
                })
        );

        allOk = allOk && collectionTestGroupPredicate <E, C> (
                makeiBData(tId3, "none", & Collection <E> :: none), 
                makeTestDataItems <C, E, R> ({
                        mSingleTD <E, R> ("None", td1, true, p1),
                        mSingleTD <E, R> ("One", td2, false, p1),
                        mSingleTD <E, R> ("More", td3, false, p1),
                        mSingleTD <E, R> ("More", td4, false, p1),
                })
        );

        using RCount = Size;

        allOk = allOk && collectionTestGroupPredicate <E, C> (
                makeiSData(tId4, "count", & Collection <E> :: count), 
                makeTestDataItems <C, E, RCount> ({
                        mSingleTD <E, RCount> ("Prop1", td5, exTwo, p1),
                        mSingleTD <E, RCount> ("Prop2", td5, exThree, p2),
                        mSingleTD <E, RCount> ("Prop3", td5, exTwo, p3),
                        mSingleTD <E, RCount> ("Prop4", td5, exFour, p4),
                        mSingleTD <E, RCount> ("Prop5", td5, td5.size() - lambdaCap, p5)
                })
        );

        allOk = allOk && collectionTestGroupPredicateCounted <E, C> (
                makeiCData(tId5, "fewerThan", & Collection <E> :: fewerThan), 
                makeCountedTestDataItems <C, E> ({
                        countedTD <E> ("True", td5, exFour, true, p3),
                        countedTD <E> ("CloseTrue", td5, exThree, true, p3),
                        countedTD <E> ("CloseFalse", td5, exTwo, false, p3),
                        countedTD <E> ("False", td5, exOne, false, p3),
                        countedTD <E> ("CompletelyFalse", td5, 0U, false, p3)
                })
        );

        allOk = allOk && collectionTestGroupPredicateCounted <E, C> (
                makeiCData(tId6, "moreThan", & Collection <E> :: moreThan), 
                makeCountedTestDataItems <C, E> ({
                        countedTD <E> ("True", td5, 0U, true, p3),
                        countedTD <E> ("CloseTrue", td5, exOne, true, p3),
                        countedTD <E> ("CloseFalse", td5, exTwo, false, p3),
                        countedTD <E> ("False", td5, exThree, false, p3),
                        countedTD <E> ("CompletelyFalse", td5, exFour, false, p3)
                })
        );

        allOk = allOk && collectionTestGroupPredicateCounted <E, C> (
                makeiCData(tId7, "atMost", & Collection <E> :: atMost), 
                makeCountedTestDataItems <C, E> ({
                        countedTD <E> ("True", td5, exThree, true, p3),
                        countedTD <E> ("CloseTrue", td5, exTwo, true, p3),
                        countedTD <E> ("CloseFalse", td5, exOne, false, p3),
                        countedTD <E> ("False", td5, 0U, false, p3)
                })
        );

        allOk = allOk && collectionTestGroupPredicateCounted <E, C> (
                makeiCData(tId8, "atLeast", & Collection <E> :: atLeast), 
                makeCountedTestDataItems <C, E> ({
                        countedTD <E> ("True", td5, exOne, true, p3),
                        countedTD <E> ("CloseTrue", td5, exTwo, true, p3),
                        countedTD <E> ("CloseFalse", td5, exThree, false, p3),
                        countedTD <E> ("False", td5, exFour, false, p3)
                })
        );

        allOk = allOk && collectionTestGroupPredicateCounted <E, C> (
                makeiCData(tId9, "some", & Collection <E> :: some), 
                makeCountedTestDataItems <C, E> ({
                        countedTD <E> ("Exact", td5, exTwo, true, p1),
                        countedTD <E> ("LessFalse", td5, exOne, false, p1),
                        countedTD <E> ("MoreFalse", td5, exThree, false, p1)
                })
        );

        /* CollectionTestCase-FunctionalStatements-forEachCount-cpp-xx : CTC-00139-FS-forEachCount-cpp-xx : IntArray */
        cds :: Array < E > const fs139 = td5;
        Collection < E > const & collection = fs139;
        Size count = 0;
        auto action = [& count, &p1] ( E e ) { if (p1(e)) { ++ count; } };
        Size expected = 2;

        collection.forEach (action);
        if ( count != expected ) {
            pTestLib->logError ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            pTestLib->logOK ( "'CTC-00139-FS-forEachCount-" __CDS_cpplang_core_version_name "' OK" );
        }

        return allOk;
    }

}


#endif /* COLLECTION_TEST_100_COMMON_H */
