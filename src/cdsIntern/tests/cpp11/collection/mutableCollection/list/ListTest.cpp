//
// Created by loghin on 18/09/22.
//

#include "ListTest.h"

#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>

#include <vector>
#include <array>

using namespace cds :: experimental;

template < typename I, typename C >
auto sortCheck ( I const & iterable, C const & comparator ) -> bool {
    for ( int i = 0; i + 1 < iterable.size(); ++ i ) {
        if ( ! comparator ( iterable[i], iterable[i + 1] ) ) {
            return true;
        }
    }
    return false;
}

/* ListTestGroup-MemberFunctions-CPP11 : LTG-00100-MF-CPP11. LTC-00101-MF to LTC-00127-MF */
template <
        template < typename ... > class __TestedType,
        typename __EnclosedType
> auto listTestGroupMemberFunctions (
        Test * pTestLib,
        std :: initializer_list < __EnclosedType > const & values,
        std :: initializer_list < __EnclosedType > const & valuesLessThan6,
        cds :: String const & expectedToString,
        __EnclosedType const & firstAtFront,
        __EnclosedType const & secondAtFront,
        __EnclosedType const & thirdAtFront,
        __EnclosedType const & firstAtBack,
        __EnclosedType const & secondAtBack,
        __EnclosedType const & thirdAtBack
) noexcept -> bool {

    __TestedType < __EnclosedType > underTest = values;
    List < __EnclosedType > & lref = underTest;

    /* ListTestCase-MemberFunctions-toString-CPP11 : LTC-00101-MF-toString-CPP11 */
    if ( lref.toString() != expectedToString ) {
        pTestLib->logError( "'LTS-00101-MF-toString-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTS-00101-MF-toString-CPP11' OK" );
    }

    /* ListTestCase-MemberFunctions-clear-CPP11 : LTC-00102-MF-clear-CPP11 */
    lref.clear();
    if ( lref.toString() == expectedToString ) {
        pTestLib->logError( "'LTS-00102-MF-clear-CPP11' failed" );
    } else {
        pTestLib->logOK ( "'LTS-00102-MF-clear-CPP11' OK" );
    }

    /* ListTestCase-MemberFunctions-front-CPP11 : LTC-00103-MF-front-CPP11 */
    /* ListTestCase-MemberFunctions-popFront-CPP11 : LTC-00104-MF-popFront-CPP11 */
    underTest = values;
    if ( underTest.front () != firstAtFront ) {
        pTestLib->logError( "'LTC-00103-MF-front-CPP11 / LTC-00104-MF-popFront-CPP11' failed" );
    } else {
        underTest.popFront ();
        if ( underTest.front () != secondAtFront ) {
            pTestLib->logError( "'LTC-00103-MF-front-CPP11 / LTC-00104-MF-popFront-CPP11' failed" );
        } else {
            underTest.popFront ();
            if ( underTest.front () != thirdAtFront ) {
                pTestLib->logError( "'LTC-00103-MF-front-CPP11 / LTC-00104-MF-popFront-CPP11' failed" );
            } else {

                pTestLib->logOK( "'LTC-00103-MF-front-CPP11 / LTC-00104-MF-popFront-CPP11' OK" );
            }
        }
    }

    /* ListTestCase-MemberFunctions-back-CPP11 : LTC-00105-MF-back-CPP11 */
    /* ListTestCase-MemberFunctions-popBack-CPP11 : LTC-00106-MF-popBack-CPP11 */
    underTest = values;
    if ( underTest.back () != firstAtBack ) {
        pTestLib->logError( "'LTC-00105-MF-back-CPP11 / LTC-00106-MF-popBack-CPP11' failed" );
    } else {
        underTest.popBack ();
        if ( underTest.back () != secondAtBack ) {
            pTestLib->logError( "'LTC-00105-MF-back-CPP11 / LTC-00106-MF-popBack-CPP11' failed" );
        } else {
            underTest.popBack ();
            if ( underTest.back () != thirdAtBack ) {
                pTestLib->logError( "'LTC-00105-MF-back-CPP11 / LTC-00106-MF-popBack-CPP11' failed" );
            } else {
                pTestLib->logOK( "'LTC-00105-MF-back-CPP11 / LTC-00106-MF-popBack-CPP11' OK" );
            }
        }
    }

    /* ListTestCase-MemberFunctions-get-CPP11 : LTC-00107-MF-get-CPP11 */
    underTest = values;
    auto vIt = values.begin();
    for ( Index i = 0; i < lref.size(); ++ i, ++ vIt ) {
        if ( lref.get(i) != * vIt ) {
            pTestLib->logError( "'LTC-00107-MF-get-CPP11' failed" );
        }
    }
    pTestLib->logOK( "'LTC-00107-MF-get-CPP11' OK" );

    /* ListTestCase-MemberFunctions-getCircularRight-CPP11 : LTC-00108-MF-getCircularRight-CPP11 */
    int iter = 10;
    int cur = 1;
    while ( cur < iter ) {
        vIt = values.begin();
        for ( Index i = cur * lref.size(); i < lref.size() + cur * lref.size(); ++ i, ++ vIt ) {
            if ( lref.get(i) != * vIt ) {
                pTestLib->logError( "'LTC-00108-MF-getCircularRight-CPP11' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00108-MF-getCircularRight-CPP11' OK" );

    /* ListTestCase-MemberFunctions-getCircularLeft-CPP11 : LTC-00109-MF-getCircularLeft-CPP11 */
    iter = 10;
    cur = 1;
    while ( cur < iter ) {
        vIt = values.end();
        -- vIt;
        for ( Index i = lref.size() - 1; i >= 0; -- i, -- vIt ) {
            if ( lref.get(i - (int) ( cur * lref.size()) ) != * vIt ) {
                pTestLib->logError( "'LTC-00109-MF-getCircularLeft-CPP11' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00109-MF-getCircularLeft-CPP11' OK" );

    /* ListTestCase-MemberFunctions-frontThrow-CPP11 : LTC-00110-MF-frontThrow-CPP11 */
    underTest = valuesLessThan6;
    lref.popFront();
    lref.popFront();
    lref.popFront();
    lref.popBack();
    lref.popBack();
    lref.popBack();

    try {
        lref.front();
        pTestLib->logError( "'LTC-00110-MF-frontThrow-CPP11' failed" );
        return false;
    } catch ( cds :: Exception const & ) {
        pTestLib->logOK( "'LTC-00110-MF-frontThrow-CPP11' OK" );
    }

    /* ListTestCase-MemberFunctions-backThrow-CPP11 : LTC-00111-MF-backThrow-CPP11 */
    try {
        lref.back();
        pTestLib->logError( "'LTC-00111-MF-backThrow-CPP11' failed" );
        return false;
    } catch ( cds :: Exception const & ) {
        pTestLib->logOK( "'LTC-00111-MF-backThrow-CPP11' OK" );
    }

    /* ListTestCase-MemberFunctions-getThrow-CPP11 : LTC-00112-MF-getThrow-CPP11 */
    for ( int i = 0; i < valuesLessThan6.size(); ++ i ) {
        try {
            lref.get(i);
            pTestLib->logError( "'LTC-00112-MF-getThrow-CPP11' failed" );
            return false;
        } catch ( cds :: Exception const & ) {
            pTestLib->logOK( "'LTC-00112-MF-getThrow-CPP11' OK" );
        }
    }

    /* ListTestCase-MemberFunctions-removeAtEmpty-CPP11 : LTC-00113-MF-removeAtEmpty-CPP11 */
    lref.clear();
    if ( lref.removeAt ( 0 ) || lref.removeAt ( 1 ) ) {
        pTestLib->logError( "'LTC-00113-MF-removeAtEmpty-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00113-MF-removeAtEmpty-CPP11' OK" );

    /* ListTestCase-MemberFunctions-removeAtFront-CPP11 : LTC-00114-MF-removeAtFront-CPP11 */
    underTest = values;
    if ( ! lref.removeAt(0) || lref.front() != secondAtFront ) {
        pTestLib->logError( "'LTC-00114-MF-removeAtFront-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00114-MF-removeAtFront-CPP11' OK" );

    /* ListTestCase-MemberFunctions-removeAtBack-CPP11 : LTC-00115-MF-removeAtBack-CPP11 */
    if ( ! lref.removeAt(lref.size() - 1) || lref.back() != secondAtBack ) {
        pTestLib->logError( "'LTC-00115-MF-removeAtBack-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00115-MF-removeAtBack-CPP11' OK" );

    /* ListTestCase-MemberFunctions-removeAt-CPP11 : LTC-00116-MF-removeAt-CPP11 */
    underTest = values;
    vIt = values.begin();
    for ( int i = 0; i < underTest.size(); ++ i, ++ vIt ) {
        auto copy = underTest;
        copy.removeAt ( i );
        if ( copy.get(i) == * vIt ) {
            pTestLib->logError( "'LTC-00116-MF-removeAt-CPP11' failed" );
            return false;
        }
    }
    pTestLib->logOK( "'LTC-00116-MF-removeAt-CPP11' OK" );


    /* ListTestCase-MemberFunctions-getOp-CPP11 : LTC-00117-MF-getOp-CPP11 */
    underTest = values;
    vIt = values.begin();
    for ( Index i = 0; i < lref.size(); ++ i, ++ vIt ) {
        if ( lref[i] != * vIt ) {
            pTestLib->logError( "'LTC-00117-MF-getOp-CPP11' failed" );
        }
    }
    pTestLib->logOK( "'LTC-00117-MF-getOp-CPP11' OK" );

    /* ListTestCase-MemberFunctions-getCircularRightOp-CPP11 : LTC-00118-MF-getCircularRightOp-CPP11 */
    iter = 10;
    cur = 1;
    while ( cur < iter ) {
        vIt = values.begin();
        for ( Index i = cur * lref.size(); i < lref.size() + cur * lref.size(); ++ i, ++ vIt ) {
            if ( lref[i] != * vIt ) {
                pTestLib->logError( "'LTC-00118-MF-getCircularRightOp-CPP11' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00118-MF-getCircularRightOp-CPP11' OK" );

    /* ListTestCase-MemberFunctions-getCircularLeftOp-CPP11 : LTC-00119-MF-getCircularLeftOp-CPP11 */
    iter = 10;
    cur = 1;
    while ( cur < iter ) {
        vIt = values.end();
        -- vIt;
        for ( Index i = lref.size() - 1; i >= 0; -- i, -- vIt ) {
            if ( lref[i - cur * lref.size()] != * vIt ) {
                pTestLib->logError( "'LTC-00119-MF-getCircularLeftOp-CPP11' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00119-MF-getCircularLeftOp-CPP11' OK" );

    underTest = valuesLessThan6;
    lref.popFront();
    lref.popFront();
    lref.popFront();
    lref.popBack();
    lref.popBack();
    lref.popBack();
    /* ListTestCase-MemberFunctions-getOpThrow-CPP11 : LTC-00120-MF-getOpThrow-CPP11 */
    for ( int i = 0; i < valuesLessThan6.size(); ++ i ) {
        try {
            lref[i];
            pTestLib->logError( "'LTC-00120-MF-getOpThrow-CPP11' failed" );
            return false;
        } catch ( cds :: Exception const & ) {
            pTestLib->logOK( "'LTC-00120-MF-getOpThrow-CPP11' OK" );
        }
    }

    underTest = values;

    /* ListTestCase-MemberFunctions-sortAscFn-CPP11 : LTC-00121-MF-sortAscFn-CPP11 */
    auto pred00121 = & cds :: predicates :: lessThan < __EnclosedType >;
    lref.sort ( pred00121 );
    if ( ! sortCheck ( lref, pred00121 ) ) {
        pTestLib->logError( "'LTC-00121-MF-sortAscFn-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00121-MF-sortAscFn-CPP11' OK" );

    /* ListTestCase-MemberFunctions-sortDescFn-CPP11 : LTC-00122-MF-sortDescFn-CPP11 */
    auto pred00122 = & cds :: predicates :: greaterThan < __EnclosedType >;
    lref.sort ( pred00122 );
    if ( ! sortCheck ( lref, pred00122 ) ) {
        pTestLib->logError( "'LTC-00122-MF-sortDescFn-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00122-MF-sortDescFn-CPP11' OK" );

    /* ListTestCase-MemberFunctions-sortAscLambda-CPP11 : LTC-00123-MF-sortAscLambda-CPP11 */
    auto pred00123 = [] (__EnclosedType const & a, __EnclosedType const & b) { return a < b; };
    lref.sort ( pred00123 );
    if ( ! sortCheck ( lref, pred00123 ) ) {
        pTestLib->logError( "'LTC-00123-MF-sortAscLambda-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00123-MF-sortAscLambda-CPP11' OK" );

    /* ListTestCase-MemberFunctions-sortDescLambda-CPP11 : LTC-00124-MF-sortDescLambda-CPP11 */
    auto pred00124 = [] (__EnclosedType const & a, __EnclosedType const & b) { return a > b; };
    lref.sort ( pred00124 );
    if ( ! sortCheck ( lref, pred00124 ) ) {
        pTestLib->logError( "'LTC-00124-MF-sortDescLambda-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00124-MF-sortDescLambda-CPP11' OK" );

    /* ListTestCase-MemberFunctions-sortAscFunctor-CPP11 : LTC-00125-MF-sortAscFunctor-CPP11 */
    class {
    public:
        auto operator () (__EnclosedType const & a, __EnclosedType const & b) const -> bool { return a < b; }
    } pred00125;
    lref.sort ( pred00125 );
    if ( ! sortCheck ( lref, pred00125 ) ) {
        pTestLib->logError( "'LTC-00125-MF-sortAscFunctor-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00125-MF-sortAscFunctor-CPP11' OK" );

    /* ListTestCase-MemberFunctions-sortDescFunctor-CPP11 : LTC-00126-MF-sortDescFunctor-CPP11 */
    class {
    public:
        auto operator () (__EnclosedType const & a, __EnclosedType const & b) const -> bool { return a > b; }
    } pred00126;
    lref.sort ( pred00126 );
    if ( ! sortCheck ( lref, pred00126 ) ) {
        pTestLib->logError( "'LTC-00126-MF-sortDescFunctor-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00126-MF-sortDescFunctor-CPP11' OK" );


    /* ListTestCase-MemberFunctions-sortDefault-CPP11 : LTC-00127-MF-sortDefault-CPP11 */
    lref.sort();
    if ( ! sortCheck ( lref, pred00121 ) ) {
        pTestLib->logError( "'LTC-00127-MF-sortDescFunctor-CPP11' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00127-MF-sortDescFunctor-CPP11' OK" );


    return true;
}


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


template <
        typename __T,       /* NOLINT(bugprone-reserved-identifier) */
        typename __ItType,  /* NOLINT(bugprone-reserved-identifier) */
        typename __LastArg  /* NOLINT(bugprone-reserved-identifier) */
> auto bwdRCheckIterator (
        __ItType const & cur,
        __ItType const & end,
        __LastArg const & lastE
) -> bool {


    auto next = cur;
    -- next;
    if ( ! cds :: meta :: equals ( __T ( lastE ), * next ) ) {
        return false;
    }
    return next == end;
}

template <
        typename __T,                   /* NOLINT(bugprone-reserved-identifier) */
        typename __ItType,              /* NOLINT(bugprone-reserved-identifier) */
        typename __CurrArg,             /* NOLINT(bugprone-reserved-identifier) */
        typename ... __RemainingArgs    /* NOLINT(bugprone-reserved-identifier) */
> auto bwdRCheckIterator (
        __ItType const & cur,
        __ItType const & end,
        __CurrArg const & currE,
        __RemainingArgs const & ... remE
) noexcept -> bool {

    auto next = cur;
    -- next;

    if ( ! cds :: meta :: equals ( __T ( currE ), * next ) ) {
        return false;
    }

    return bwdRCheckIterator < __T > ( next, end, remE ... );
}

template < typename __T, typename __F >
auto bwdAcquire ( Index i, __F const & f ) -> __T {

    if ( i == 0 ) {
        return __T(f);
    }

    throw std :: runtime_error ("unexpected");
}

template < typename __T, typename __F, typename ... __Args >
auto bwdAcquire ( Index i, __F const & f, __Args const & ... v ) -> __T {

    if ( i == 0 ) {
        return __T(f);
    }

    return bwdAcquire < __T > ( i - 1, v ... );
}

template <
        typename __T,                   /* NOLINT(bugprone-reserved-identifier) */
        typename __ItType,              /* NOLINT(bugprone-reserved-identifier) */
        typename ... __RemainingArgs    /* NOLINT(bugprone-reserved-identifier) */
> auto bwdCheckIterator (
        __ItType const & cur,
        __ItType const & end,
        Index current,
        __RemainingArgs const & ... v
) noexcept -> bool {

    if ( current == -1 ) {
        return true;
    }

    if ( cur == end ) {
        return false;
    }

    if ( ! cds :: meta :: equals ( bwdAcquire < __T > ( current, v ... ), * cur ) ) {
        return false;
    }

    auto next = cur;
    return bwdCheckIterator < __T, __ItType, __RemainingArgs ... > ( ++ next, end, current - 1, v ... );
}

template <
        typename __T,                   /* NOLINT(bugprone-reserved-identifier) */
        typename __ItType,              /* NOLINT(bugprone-reserved-identifier) */
        typename ... __RemainingArgs    /* NOLINT(bugprone-reserved-identifier) */
> auto fwdRCheckIterator (
        __ItType const & cur,
        Index current,
        __RemainingArgs const & ... v
) noexcept -> bool {

    if ( current == -1 ) {
        return true;
    }

    auto next = cur;
    --next;
    if ( ! cds :: meta :: equals ( bwdAcquire < __T > ( current, v ... ), * next ) ) {
        return false;
    }

    return fwdRCheckIterator < __T, __ItType, __RemainingArgs ... > ( next, current - 1, v ... );
}


/* ListTestGroup-DelegateBidirectionalIterableClientImports-CPP11 : LTG-00200-IT-CPP11. Tests LTC-00201 to LTC-002xx */
template <
        template < typename ... > class __TestedType,
        typename __EnclosedType,
//        auto ( List < __EnclosedType > :: * pFnBeginMut ) () -> __IteratorType,
//        auto ( List < __EnclosedType > :: * pFnEndMut ) () -> __IteratorType,
//        auto ( List < __EnclosedType > :: * pFnBeginImmut ) () const -> __ConstIteratorType,
//        auto ( List < __EnclosedType > :: * pFnEndImmut ) () const -> __ConstIteratorType,
        typename ... __ValuesInOrder
> auto listTestGroupDelegateBidirectionalIterableClientImports (
        Test * pTestLib,
        __EnclosedType const & mutabilityTestValue1,
        __EnclosedType const & mutabilityTestValue2,
        typename List < __EnclosedType > :: Iterator ( List < __EnclosedType > :: * pFnBeginMut ) (),
        typename List < __EnclosedType > :: Iterator ( List < __EnclosedType > :: * pFnEndMut ) (),
        typename List < __EnclosedType > :: ConstIterator ( List < __EnclosedType > :: * pFnBeginImmut ) () const,
        typename List < __EnclosedType > :: ConstIterator ( List < __EnclosedType > :: * pFnEndImmut ) () const,
        typename List < __EnclosedType > :: ReverseIterator ( List < __EnclosedType > :: * pFnRBeginMut ) (),
        typename List < __EnclosedType > :: ReverseIterator ( List < __EnclosedType > :: * pFnREndMut ) (),
        typename List < __EnclosedType > :: ConstReverseIterator ( List < __EnclosedType > :: * pFnRBeginImmut ) () const,
        typename List < __EnclosedType > :: ConstReverseIterator ( List < __EnclosedType > :: * pFnREndImmut ) () const,
        __ValuesInOrder const & ... values
) noexcept -> bool {

    __TestedType < __EnclosedType > underTest;
    List < __EnclosedType > & lref = underTest;

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueCheck-CPP11 : LTC-00201-IT-perValueCheck-CPP11 */
    underTest.insertAll ( values ... );
    auto iterResult = fwdCheckIterator < __EnclosedType > (
            ( lref.*pFnBeginMut ) (),
            ( lref.*pFnEndMut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00201-IT-perValueCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00201-IT-perValueCheck-CPP11' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueImmCheck-CPP11 : LTC-00202-IT-perValueImmCheck-CPP11 */
    iterResult = fwdCheckIterator < __EnclosedType > (
            ( lref.*pFnBeginImmut ) (),
            ( lref.*pFnEndImmut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00202-IT-perValueImmCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00202-IT-perValueImmCheck-CPP11' OK" );
    }

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevCheck-CPP11 : LTC-00203-IT-perValueRevCheck-CPP11 */
    iterResult = bwdCheckIterator < __EnclosedType > (
            ( lref.*pFnRBeginMut ) (),
            ( lref.*pFnREndMut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00203-IT-perValueRevCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00203-IT-perValueRevCheck-CPP11' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevImmCheck-CPP11 : LTC-00204-IT-perValueRevImmCheck-CPP11 */
    iterResult = bwdCheckIterator < __EnclosedType > (
            ( lref.*pFnRBeginImmut ) (),
            ( lref.*pFnREndImmut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00204-IT-perValueRevImmCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00204-IT-perValueRevImmCheck-CPP11' OK" );
    }

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueBwdCheck-CPP11 : LTC-00205-IT-perValueBwdCheck-CPP11 */
    iterResult = fwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnEndMut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00205-IT-perValueBwdCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00205-IT-perValueBwdCheck-CPP11' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueBwdImmCheck-CPP11 : LTC-00202-IT-perValueBwdImmCheck-CPP11 */
    iterResult = fwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnEndImmut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00206-IT-perValueBwdImmCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00206-IT-perValueBwdImmCheck-CPP11' OK" );
    }

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevBwdCheck-CPP11 : LTC-00207-IT-perValueRevBwdCheck-CPP11 */
    iterResult = bwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnREndMut ) (),
            ( lref.*pFnRBeginMut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00207-IT-perValueRevBwdCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00207-IT-perValueRevBwdCheck-CPP11' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevBwdImmCheck-CPP11 : LTC-00208-IT-perValueRevBwdImmCheck-CPP11 */
    iterResult = bwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnREndImmut ) (),
            ( lref.*pFnRBeginImmut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00208-IT-perValueRevBwdImmCheck-CPP11' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00208-IT-perValueRevBwdImmCheck-CPP11' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-itMutabilityRange-CPP11 : LTC-00209-IT-itMutabilityRange-CPP11 */
    for ( auto & e : lref ) {
        e = mutabilityTestValue1;
    }

    if ( ! lref.all ( [& mutabilityTestValue1](__EnclosedType const & v) { return mutabilityTestValue1 == v; } ) ) {
        pTestLib->logError( "'LTC-00209-IT-itMutabilityRange-CPP11' failed" );
        return false;
    }
    pTestLib->logOK ( "'LTC-00209-IT-itMutabilityRange-CPP11' OK" );


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-itMutabilityStd-CPP11 : LTC-00210-IT-itMutabilityStd-CPP11 */
    for ( auto it = lref.begin(); it != lref.end(); ++ it ) {
        * it = mutabilityTestValue2;
    }

    if ( ! lref.all ( [& mutabilityTestValue2](__EnclosedType const & v) { return mutabilityTestValue2 == v; } ) ) {
        pTestLib->logError( "'LTC-00210-IT-itMutabilityStd-CPP11' failed" );
        return false;
    }
    pTestLib->logOK ( "'LTC-00210-IT-itMutabilityStd-CPP11' OK" );


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-itMutabilityStdRev-CPP11 : LTC-00211-IT-itMutabilityStdRev-CPP11 */
    for ( auto it = lref.rbegin(); it != lref.rend(); ++ it ) {
        * it = mutabilityTestValue1;
    }

    if ( ! lref.all ( [& mutabilityTestValue1](__EnclosedType const & v) { return mutabilityTestValue1 == v; } ) ) {
        pTestLib->logError( "'LTC-00211-IT-itMutabilityStdRev-CPP11' failed" );
        return false;
    }
    pTestLib->logOK ( "'LTC-00211-IT-itMutabilityStdRev-CPP11' OK" );

    return true;
}


/* ListTestSuite-CPP11 : LTS-00001-CPP11 */
auto ListTest :: execute () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "ListTestGroup-MemberFunctions-CPP11 : LTG-00100-MF-CPP11 : IntArray", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < Array, int > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });
    this->executeSubtest ( "ListTestGroup-MemberFunctions-CPP11 : LTG-00100-MF-CPP11 : IntLinkedList", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < LinkedList, int > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });
    this->executeSubtest ( "ListTestGroup-MemberFunctions-CPP11 : LTG-00100-MF-CPP11 : StringArray", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < Array, String > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });
    this->executeSubtest ( "ListTestGroup-MemberFunctions-CPP11 : LTG-00100-MF-CPP11 : StringLinkedList", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < LinkedList, String > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });


    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-CPP11 : LTG-00200-IT-CPP11 : IntArray", [this, & allOk] {
        allOk = allOk && listTestGroupDelegateBidirectionalIterableClientImports <
                Array,
                int
        > (
                this,
                3,5,
                & List < int > :: begin,
                & List < int > :: end,
                & List < int > :: cbegin,
                & List < int > :: cend,
                & List < int > :: rbegin,
                & List < int > :: rend,
                & List < int > :: crbegin,
                & List < int > :: crend,
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        );
    });
    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-CPP11 : LTG-00200-IT-CPP11 : IntLinkedList", [this, & allOk] {
        allOk = allOk && listTestGroupDelegateBidirectionalIterableClientImports <
                LinkedList,
                int
        > (
                this,
                3,5,
                & List < int > :: begin,
                & List < int > :: end,
                & List < int > :: cbegin,
                & List < int > :: cend,
                & List < int > :: rbegin,
                & List < int > :: rend,
                & List < int > :: crbegin,
                & List < int > :: crend,
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        );
    });
    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-CPP11 : LTG-00200-IT-CPP11 : StringArray", [this, & allOk] {
        allOk = allOk && listTestGroupDelegateBidirectionalIterableClientImports <
                Array,
                String
        > (
                this,
                3,5,
                & List < String > :: begin,
                & List < String > :: end,
                & List < String > :: cbegin,
                & List < String > :: cend,
                & List < String > :: rbegin,
                & List < String > :: rend,
                & List < String > :: crbegin,
                & List < String > :: crend,
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        );
    });
    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-CPP11 : LTG-00200-IT-CPP11 : StringLinkedList", [this, & allOk] {
        allOk = allOk && listTestGroupDelegateBidirectionalIterableClientImports <
                LinkedList,
                String
        > (
                this,
                3,5,
                & List < String > :: begin,
                & List < String > :: end,
                & List < String > :: cbegin,
                & List < String > :: cend,
                & List < String > :: rbegin,
                & List < String > :: rend,
                & List < String > :: crbegin,
                & List < String > :: crend,
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        );
    });

    return allOk;
}
