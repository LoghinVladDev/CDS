#ifndef COLLECTION_TEST_100_COMMON_H
#define COLLECTION_TEST_100_COMMON_H

#include "CollectionTest.h"
#include "CollectionTest_common.hpp"
#include <CDS/Tuple>
#include <CDS/Function>

inline namespace ctc100 {

    using cds::Tuple;
    using cds::Collection;
    using cds::makeTuple;
    using cds::Size;
    using cds::Function;


    template <typename E, typename F, typename R>
    using CPred = R (cds::Collection<E> :: *) (F const &) const;

    template <typename E, typename F, typename R>
    using CCountedPred = R (cds::Collection<E> :: *) (Size, F const &) const;

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

    template <typename E, typename C, typename R>
    using STestData = Tuple <
            cds::StringView, C, R, Function <bool (E)>
    >;

    template <
            typename E,
            typename C,
            typename P,
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
}


#endif /* COLLECTION_TEST_100_COMMON_H */
