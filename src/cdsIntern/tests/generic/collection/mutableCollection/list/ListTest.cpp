/*
 * Created by loghin on 18/09/22.
 */

#include "ListTest.h"

#include <CDS/Array>
#include <CDS/LinkedList>

#include <vector>
#include <array>
#include <CDS/Range>


namespace {
    
    using glob::Test;
    using glob::ListTest;


    using cds::Index;
    using cds::Size;

    using cds::String;

    using cds::List;
    using cds::Array;
    using cds::LinkedList;

}


template < typename I, typename C >
auto sortCheck ( I const & iterable, C const & comparator ) -> bool {
    for ( int i = 0; i + 1 < iterable.size(); ++ i ) {
        if ( ! comparator ( iterable[i], iterable[i + 1] ) ) {
            return true;
        }
    }
    return false;
}

/* ListTestGroup-MemberFunctions-cpp-xx : LTG-00100-MF-cpp-xx. LTC-00101-MF to LTC-00127-MF */
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
    cds :: List < __EnclosedType > & lref = underTest;

    /* ListTestCase-MemberFunctions-toString-cpp-xx : LTC-00101-MF-toString-cpp-xx */
    if ( lref.toString() != expectedToString ) {
        pTestLib->logError( "'LTS-00101-MF-toString-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTS-00101-MF-toString-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* ListTestCase-MemberFunctions-clear-cpp-xx : LTC-00102-MF-clear-cpp-xx */
    lref.clear();
    if ( lref.toString() == expectedToString ) {
        pTestLib->logError( "'LTS-00102-MF-clear-" __CDS_cpplang_core_version_name "' failed" );
    } else {
        pTestLib->logOK ( "'LTS-00102-MF-clear-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* ListTestCase-MemberFunctions-front-cpp-xx : LTC-00103-MF-front-cpp-xx */
    /* ListTestCase-MemberFunctions-popFront-cpp-xx : LTC-00104-MF-popFront-cpp-xx */
    underTest = values;
    if ( underTest.front () != firstAtFront ) {
        pTestLib->logError( "'LTC-00103-MF-front-cpp-xx / LTC-00104-MF-popFront-" __CDS_cpplang_core_version_name "' failed" );
    } else {
        underTest.popFront ();
        if ( underTest.front () != secondAtFront ) {
            pTestLib->logError( "'LTC-00103-MF-front-cpp-xx / LTC-00104-MF-popFront-" __CDS_cpplang_core_version_name "' failed" );
        } else {
            underTest.popFront ();
            if ( underTest.front () != thirdAtFront ) {
                pTestLib->logError( "'LTC-00103-MF-front-cpp-xx / LTC-00104-MF-popFront-" __CDS_cpplang_core_version_name "' failed" );
            } else {

                pTestLib->logOK( "'LTC-00103-MF-front-cpp-xx / LTC-00104-MF-popFront-" __CDS_cpplang_core_version_name "' OK" );
            }
        }
    }

    /* ListTestCase-MemberFunctions-back-cpp-xx : LTC-00105-MF-back-cpp-xx */
    /* ListTestCase-MemberFunctions-popBack-cpp-xx : LTC-00106-MF-popBack-cpp-xx */
    underTest = values;
    if ( underTest.back () != firstAtBack ) {
        pTestLib->logError( "'LTC-00105-MF-back-cpp-xx / LTC-00106-MF-popBack-" __CDS_cpplang_core_version_name "' failed" );
    } else {
        underTest.popBack ();
        if ( underTest.back () != secondAtBack ) {
            pTestLib->logError( "'LTC-00105-MF-back-cpp-xx / LTC-00106-MF-popBack-" __CDS_cpplang_core_version_name "' failed" );
        } else {
            underTest.popBack ();
            if ( underTest.back () != thirdAtBack ) {
                pTestLib->logError( "'LTC-00105-MF-back-cpp-xx / LTC-00106-MF-popBack-" __CDS_cpplang_core_version_name "' failed" );
            } else {
                pTestLib->logOK( "'LTC-00105-MF-back-cpp-xx / LTC-00106-MF-popBack-" __CDS_cpplang_core_version_name "' OK" );
            }
        }
    }

    /* ListTestCase-MemberFunctions-get-cpp-xx : LTC-00107-MF-get-cpp-xx */
    underTest = values;
    auto vIt = values.begin();
    for ( Index i = 0; i < lref.size(); ++ i, ++ vIt ) {
        if ( lref.get(i) != * vIt ) {
            pTestLib->logError( "'LTC-00107-MF-get-" __CDS_cpplang_core_version_name "' failed" );
        }
    }
    pTestLib->logOK( "'LTC-00107-MF-get-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-getCircularRight-cpp-xx : LTC-00108-MF-getCircularRight-cpp-xx */
    int iter = 10;
    int cur = 1;
    while ( cur < iter ) {
        vIt = values.begin();
        for ( Index i = cur * lref.size(); i < lref.size() + cur * lref.size(); ++ i, ++ vIt ) {
            if ( lref.get(i) != * vIt ) {
                pTestLib->logError( "'LTC-00108-MF-getCircularRight-" __CDS_cpplang_core_version_name "' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00108-MF-getCircularRight-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-getCircularLeft-cpp-xx : LTC-00109-MF-getCircularLeft-cpp-xx */
    iter = 10;
    cur = 1;
    while ( cur < iter ) {
        vIt = values.end();
        -- vIt;
        for ( Index i = lref.size() - 1; i >= 0; -- i, -- vIt ) {
            if ( lref.get(i - (int) ( cur * lref.size()) ) != * vIt ) {
                pTestLib->logError( "'LTC-00109-MF-getCircularLeft-" __CDS_cpplang_core_version_name "' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00109-MF-getCircularLeft-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-frontThrow-cpp-xx : LTC-00110-MF-frontThrow-cpp-xx */
    underTest = valuesLessThan6;
    lref.popFront();
    lref.popFront();
    lref.popFront();
    lref.popBack();
    lref.popBack();
    lref.popBack();

    try {
        (void) lref.front();
        pTestLib->logError( "'LTC-00110-MF-frontThrow-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } catch ( cds :: Exception const & ) {
        pTestLib->logOK( "'LTC-00110-MF-frontThrow-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* ListTestCase-MemberFunctions-backThrow-cpp-xx : LTC-00111-MF-backThrow-cpp-xx */
    try {
        (void) lref.back();
        pTestLib->logError( "'LTC-00111-MF-backThrow-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } catch ( cds :: Exception const & ) {
        pTestLib->logOK( "'LTC-00111-MF-backThrow-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* ListTestCase-MemberFunctions-getThrow-cpp-xx : LTC-00112-MF-getThrow-cpp-xx */
    for ( int i = 0; i < valuesLessThan6.size(); ++ i ) {
        try {
            (void) lref.get(i);
            pTestLib->logError( "'LTC-00112-MF-getThrow-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } catch ( cds :: Exception const & ) {
            pTestLib->logOK( "'LTC-00112-MF-getThrow-" __CDS_cpplang_core_version_name "' OK" );
        }
    }

    /* ListTestCase-MemberFunctions-removeAtEmpty-cpp-xx : LTC-00113-MF-removeAtEmpty-cpp-xx */
    lref.clear();
    if ( lref.removeAt ( 0 ) || lref.removeAt ( 1 ) ) {
        pTestLib->logError( "'LTC-00113-MF-removeAtEmpty-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00113-MF-removeAtEmpty-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-removeAtFront-cpp-xx : LTC-00114-MF-removeAtFront-cpp-xx */
    underTest = values;
    if ( ! lref.removeAt(0) || lref.front() != secondAtFront ) {
        pTestLib->logError( "'LTC-00114-MF-removeAtFront-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00114-MF-removeAtFront-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-removeAtBack-cpp-xx : LTC-00115-MF-removeAtBack-cpp-xx */
    if ( ! lref.removeAt(lref.size() - 1) || lref.back() != secondAtBack ) {
        pTestLib->logError( "'LTC-00115-MF-removeAtBack-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00115-MF-removeAtBack-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-removeAt-cpp-xx : LTC-00116-MF-removeAt-cpp-xx */
    underTest = values;
    vIt = values.begin();
    for ( int i = 0; i < underTest.size(); ++ i, ++ vIt ) {
        auto copy = underTest;
        copy.removeAt ( i );
        if ( copy.get(i) == * vIt ) {
            pTestLib->logError( "'LTC-00116-MF-removeAt-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        }
    }
    pTestLib->logOK( "'LTC-00116-MF-removeAt-" __CDS_cpplang_core_version_name "' OK" );


    /* ListTestCase-MemberFunctions-getOp-cpp-xx : LTC-00117-MF-getOp-cpp-xx */
    underTest = values;
    vIt = values.begin();
    for ( Index i = 0; i < lref.size(); ++ i, ++ vIt ) {
        if ( lref[i] != * vIt ) {
            pTestLib->logError( "'LTC-00117-MF-getOp-" __CDS_cpplang_core_version_name "' failed" );
        }
    }
    pTestLib->logOK( "'LTC-00117-MF-getOp-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-getCircularRightOp-cpp-xx : LTC-00118-MF-getCircularRightOp-cpp-xx */
    iter = 10;
    cur = 1;
    while ( cur < iter ) {
        vIt = values.begin();
        for ( Index i = cur * lref.size(); i < lref.size() + cur * lref.size(); ++ i, ++ vIt ) {
            if ( lref[i] != * vIt ) {
                pTestLib->logError( "'LTC-00118-MF-getCircularRightOp-" __CDS_cpplang_core_version_name "' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00118-MF-getCircularRightOp-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-getCircularLeftOp-cpp-xx : LTC-00119-MF-getCircularLeftOp-cpp-xx */
    iter = 10;
    cur = 1;
    while ( cur < iter ) {
        vIt = values.end();
        -- vIt;
        for ( Index i = lref.size() - 1; i >= 0; -- i, -- vIt ) {
            if ( lref[i - cur * lref.size()] != * vIt ) {
                pTestLib->logError( "'LTC-00119-MF-getCircularLeftOp-" __CDS_cpplang_core_version_name "' failed" );
            }
        }
        ++ cur;
    }
    pTestLib->logOK( "'LTC-00119-MF-getCircularLeftOp-" __CDS_cpplang_core_version_name "' OK" );

    underTest = valuesLessThan6;
    lref.popFront();
    lref.popFront();
    lref.popFront();
    lref.popBack();
    lref.popBack();
    lref.popBack();
    /* ListTestCase-MemberFunctions-getOpThrow-cpp-xx : LTC-00120-MF-getOpThrow-cpp-xx */
    for ( int i = 0; i < valuesLessThan6.size(); ++ i ) {
        try {
            (void) lref[i];
            pTestLib->logError( "'LTC-00120-MF-getOpThrow-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } catch ( cds :: Exception const & ) {
            pTestLib->logOK( "'LTC-00120-MF-getOpThrow-" __CDS_cpplang_core_version_name "' OK" );
        }
    }

    underTest = values;

    /* ListTestCase-MemberFunctions-sortAscFn-cpp-xx : LTC-00121-MF-sortAscFn-cpp-xx */
    auto pred00121 = & cds :: predicates :: lessThan < __EnclosedType >;
    lref.sort ( pred00121 );
    if ( ! sortCheck ( lref, pred00121 ) ) {
        pTestLib->logError( "'LTC-00121-MF-sortAscFn-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00121-MF-sortAscFn-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-sortDescFn-cpp-xx : LTC-00122-MF-sortDescFn-cpp-xx */
    auto pred00122 = & cds :: predicates :: greaterThan < __EnclosedType >;
    lref.sort ( pred00122 );
    if ( ! sortCheck ( lref, pred00122 ) ) {
        pTestLib->logError( "'LTC-00122-MF-sortDescFn-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00122-MF-sortDescFn-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-sortAscLambda-cpp-xx : LTC-00123-MF-sortAscLambda-cpp-xx */
    auto pred00123 = [] (__EnclosedType const & a, __EnclosedType const & b) { return a < b; };
    lref.sort ( pred00123 );
    if ( ! sortCheck ( lref, pred00123 ) ) {
        pTestLib->logError( "'LTC-00123-MF-sortAscLambda-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00123-MF-sortAscLambda-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-sortDescLambda-cpp-xx : LTC-00124-MF-sortDescLambda-cpp-xx */
    auto pred00124 = [] (__EnclosedType const & a, __EnclosedType const & b) { return a > b; };
    lref.sort ( pred00124 );
    if ( ! sortCheck ( lref, pred00124 ) ) {
        pTestLib->logError( "'LTC-00124-MF-sortDescLambda-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00124-MF-sortDescLambda-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-sortAscFunctor-cpp-xx : LTC-00125-MF-sortAscFunctor-cpp-xx */
    class {
    public:
        auto operator () (__EnclosedType const & a, __EnclosedType const & b) const -> bool { return a < b; }
    } pred00125;
    lref.sort ( pred00125 );
    if ( ! sortCheck ( lref, pred00125 ) ) {
        pTestLib->logError( "'LTC-00125-MF-sortAscFunctor-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00125-MF-sortAscFunctor-" __CDS_cpplang_core_version_name "' OK" );

    /* ListTestCase-MemberFunctions-sortDescFunctor-cpp-xx : LTC-00126-MF-sortDescFunctor-cpp-xx */
    class {
    public:
        auto operator () (__EnclosedType const & a, __EnclosedType const & b) const -> bool { return a > b; }
    } pred00126;
    lref.sort ( pred00126 );
    if ( ! sortCheck ( lref, pred00126 ) ) {
        pTestLib->logError( "'LTC-00126-MF-sortDescFunctor-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00126-MF-sortDescFunctor-" __CDS_cpplang_core_version_name "' OK" );


    /* ListTestCase-MemberFunctions-sortDefault-cpp-xx : LTC-00127-MF-sortDefault-cpp-xx */
    lref.sort();
    if ( ! sortCheck ( lref, pred00121 ) ) {
        pTestLib->logError( "'LTC-00127-MF-sortDescFunctor-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK( "'LTC-00127-MF-sortDescFunctor-" __CDS_cpplang_core_version_name "' OK" );


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


/* ListTestGroup-DelegateBidirectionalIterableClientImports-cpp-xx : LTG-00200-IT-cpp-xx. Tests LTC-00201 to LTC-002xx */
template <
        template < typename ... > class __TestedType,
        typename __EnclosedType,
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

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueCheck-cpp-xx : LTC-00201-IT-perValueCheck-cpp-xx */
    underTest.insertAll ( values ... );
    auto iterResult = fwdCheckIterator < __EnclosedType > (
            ( lref.*pFnBeginMut ) (),
            ( lref.*pFnEndMut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00201-IT-perValueCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00201-IT-perValueCheck-" __CDS_cpplang_core_version_name "' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueImmCheck-cpp-xx : LTC-00202-IT-perValueImmCheck-cpp-xx */
    iterResult = fwdCheckIterator < __EnclosedType > (
            ( lref.*pFnBeginImmut ) (),
            ( lref.*pFnEndImmut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00202-IT-perValueImmCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00202-IT-perValueImmCheck-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevCheck-cpp-xx : LTC-00203-IT-perValueRevCheck-cpp-xx */
    iterResult = bwdCheckIterator < __EnclosedType > (
            ( lref.*pFnRBeginMut ) (),
            ( lref.*pFnREndMut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00203-IT-perValueRevCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00203-IT-perValueRevCheck-" __CDS_cpplang_core_version_name "' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevImmCheck-cpp-xx : LTC-00204-IT-perValueRevImmCheck-cpp-xx */
    iterResult = bwdCheckIterator < __EnclosedType > (
            ( lref.*pFnRBeginImmut ) (),
            ( lref.*pFnREndImmut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00204-IT-perValueRevImmCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00204-IT-perValueRevImmCheck-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueBwdCheck-cpp-xx : LTC-00205-IT-perValueBwdCheck-cpp-xx */
    iterResult = fwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnEndMut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00205-IT-perValueBwdCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00205-IT-perValueBwdCheck-" __CDS_cpplang_core_version_name "' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueBwdImmCheck-cpp-xx : LTC-00202-IT-perValueBwdImmCheck-cpp-xx */
    iterResult = fwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnEndImmut ) (),
            sizeof ... ( values ) - 1,
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00206-IT-perValueBwdImmCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00206-IT-perValueBwdImmCheck-" __CDS_cpplang_core_version_name "' OK" );
    }

    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevBwdCheck-cpp-xx : LTC-00207-IT-perValueRevBwdCheck-cpp-xx */
    iterResult = bwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnREndMut ) (),
            ( lref.*pFnRBeginMut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00207-IT-perValueRevBwdCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00207-IT-perValueRevBwdCheck-" __CDS_cpplang_core_version_name "' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-perValueRevBwdImmCheck-cpp-xx : LTC-00208-IT-perValueRevBwdImmCheck-cpp-xx */
    iterResult = bwdRCheckIterator < __EnclosedType > (
            ( lref.*pFnREndImmut ) (),
            ( lref.*pFnRBeginImmut ) (),
            values ...
    );

    if ( ! iterResult ) {
        pTestLib->logError( "'LTC-00208-IT-perValueRevBwdImmCheck-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'LTC-00208-IT-perValueRevBwdImmCheck-" __CDS_cpplang_core_version_name "' OK" );
    }


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-itMutabilityRange-cpp-xx : LTC-00209-IT-itMutabilityRange-cpp-xx */
    for ( auto & e : lref ) {
        e = mutabilityTestValue1;
    }

    if ( ! lref.all ( [& mutabilityTestValue1](__EnclosedType const & v) { return mutabilityTestValue1 == v; } ) ) {
        pTestLib->logError( "'LTC-00209-IT-itMutabilityRange-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK ( "'LTC-00209-IT-itMutabilityRange-" __CDS_cpplang_core_version_name "' OK" );


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-itMutabilityStd-cpp-xx : LTC-00210-IT-itMutabilityStd-cpp-xx */
    for ( auto it = lref.begin(); it != lref.end(); ++ it ) {
        * it = mutabilityTestValue2;
    }

    if ( ! lref.all ( [& mutabilityTestValue2](__EnclosedType const & v) { return mutabilityTestValue2 == v; } ) ) {
        pTestLib->logError( "'LTC-00210-IT-itMutabilityStd-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK ( "'LTC-00210-IT-itMutabilityStd-" __CDS_cpplang_core_version_name "' OK" );


    /* ListTestGroup-DelegateBidirectionalIterableClientImports-itMutabilityStdRev-cpp-xx : LTC-00211-IT-itMutabilityStdRev-cpp-xx */
    for ( auto it = lref.rbegin(); it != lref.rend(); ++ it ) {
        * it = mutabilityTestValue1;
    }

    if ( ! lref.all ( [& mutabilityTestValue1](__EnclosedType const & v) { return mutabilityTestValue1 == v; } ) ) {
        pTestLib->logError( "'LTC-00211-IT-itMutabilityStdRev-" __CDS_cpplang_core_version_name "' failed" );
        return false;
    }
    pTestLib->logOK ( "'LTC-00211-IT-itMutabilityStdRev-" __CDS_cpplang_core_version_name "' OK" );

    return true;
}


template <
        typename T,
        typename V
> auto equals (T const & t, V const & v) -> bool {

    auto lIt = t.begin();
    auto le = t.end();
    auto rIt = v.begin();
    auto re = v.end();
    for (
            ;   lIt != le && rIt != re; ++ lIt, ++ rIt
            )
        if ( ! cds :: meta :: equals ( * lIt, * rIt ) )
            return false;

    return true;
}

/* ListTestGroup-BoundaryInsertion-cpp-xx : LTG-00300-BI-cpp-xx. Tests LTC-00301-BI to LTC-00322-BI */
template <
        template < typename ... > class __TestedType,
        typename __EnclosedType,
        typename __ItType1,
        typename __ItType2,
        typename __ItType3,
        typename ... __Values
> auto listTestGroupBoundaryInsertion (
        Test * pTestLib,
        std :: initializer_list < __EnclosedType > const & initValues,
        __EnclosedType const & pbFirst,
        std :: initializer_list < __EnclosedType > const & equiv1,
        __EnclosedType const & pbSecond,
        std :: initializer_list < __EnclosedType > const & equiv2,
        __EnclosedType const & pbThird,
        std :: initializer_list < __EnclosedType > const & equiv3,
        __EnclosedType pbFourth,
        std :: initializer_list < __EnclosedType > const & equiv4,
        __EnclosedType pbFifth,
        std :: initializer_list < __EnclosedType > const & equiv5,
        __EnclosedType const & pfFirst,
        std :: initializer_list < __EnclosedType > const & equiv6,
        __EnclosedType const & pfSecond,
        std :: initializer_list < __EnclosedType > const & equiv7,
        __EnclosedType const & pfThird,
        std :: initializer_list < __EnclosedType > const & equiv8,
        __EnclosedType pfFourth,
        std :: initializer_list < __EnclosedType > const & equiv9,
        __EnclosedType pfFifth,
        std :: initializer_list < __EnclosedType > const & equiv10,
        std :: initializer_list < __EnclosedType > const & pbValues,
        std :: initializer_list < __EnclosedType > const & equiv11,
        std :: initializer_list < __EnclosedType > const & equiv12,
        std :: initializer_list < __EnclosedType > const & pfValues,
        std :: initializer_list < __EnclosedType > const & equiv13,
        std :: initializer_list < __EnclosedType > const & equiv14,
        __ItType1 const & b1, __ItType1 const & e1,
        std :: initializer_list < __EnclosedType > const & equiv15,
        std :: initializer_list < __EnclosedType > const & equiv16,
        __ItType2 const & b2, __ItType2 const & e2,
        std :: initializer_list < __EnclosedType > const & equiv17,
        std :: initializer_list < __EnclosedType > const & equiv18,
        __ItType3 const & b3, __ItType3 const & e3,
        std :: initializer_list < __EnclosedType > const & equiv19,
        std :: initializer_list < __EnclosedType > const & equiv20,
        std :: initializer_list < __EnclosedType > const & equiv21,
        std :: initializer_list < __EnclosedType > const & equiv22,
        __Values const & ... values
) noexcept -> bool {

    __TestedType < __EnclosedType > underTest = initValues;
    List < __EnclosedType > & lref = underTest;

    /* ListTestGroup-BoundaryInsertion-pushBackCopy1-cpp-xx : LTC-00301-IT-pushBackCopy1-cpp-xx */
    lref.pushBack ( pbFirst );
    if ( ! equals ( lref, equiv1 ) ) {
        pTestLib->logError("'LTC-00301-IT-pushBackCopy1-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00301-IT-pushBackCopy1-" __CDS_cpplang_core_version_name "' OK");

    /* ListTestGroup-BoundaryInsertion-pushBackCopy2-cpp-xx : LTC-00302-IT-pushBackCopy2-cpp-xx */
    lref.pushBack ( pbSecond );
    if ( ! equals ( lref, equiv2 ) ) {
        pTestLib->logError("'LTC-00302-IT-pushBackCopy2-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00302-IT-pushBackCopy2-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackCopy3-cpp-xx : LTC-00303-IT-pushBackCopy3-cpp-xx */
    lref.pushBack ( pbThird );
    if ( ! equals ( lref, equiv3 ) ) {
        pTestLib->logError("'LTC-00303-IT-pushBackCopy3-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00303-IT-pushBackCopy3-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackMove1-cpp-xx : LTC-00304-IT-pushBackMove1-cpp-xx */
    lref.pushBack ( std :: move ( pbFourth ) );
    if ( ! equals ( lref, equiv4 ) ) {
        pTestLib->logError("'LTC-00304-IT-pushBackMove1-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00304-IT-pushBackMove1-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackMove2-cpp-xx : LTC-00305-IT-pushBackMove2-cpp-xx */
    lref.pushBack ( std :: move ( pbFifth ) );
    if ( ! equals ( lref, equiv5 ) ) {
        pTestLib->logError("'LTC-00305-IT-pushBackMove2-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00305-IT-pushBackMove2-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontCopy1-cpp-xx : LTC-00306-IT-pushFrontCopy1-cpp-xx */
    lref.pushFront ( pfFirst );
    if ( ! equals ( lref, equiv6 ) ) {
        pTestLib->logError("'LTC-00306-IT-pushFrontCopy1-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00306-IT-pushFrontCopy1-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontCopy2-cpp-xx : LTC-00307-IT-pushFrontCopy2-cpp-xx */
    lref.pushFront ( pfSecond );
    if ( ! equals ( lref, equiv7 ) ) {
        pTestLib->logError("'LTC-00307-IT-pushFrontCopy2-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00307-IT-pushFrontCopy2-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontCopy3-cpp-xx : LTC-00308-IT-pushFrontCopy3-cpp-xx */
    lref.pushFront ( pfThird );
    if ( ! equals ( lref, equiv8 ) ) {
        pTestLib->logError("'LTC-00308-IT-pushFrontCopy3-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00308-IT-pushFrontCopy3-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontMove1-cpp-xx : LTC-00309-IT-pushFrontMove1-cpp-xx */
    lref.pushFront ( std :: move ( pfFourth ) );
    if ( ! equals ( lref, equiv9 ) ) {
        pTestLib->logError("'LTC-00309-IT-pushFrontMove1-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00309-IT-pushFrontMove1-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontMove2-cpp-xx : LTC-00310-IT-pushFrontMove2-cpp-xx */
    lref.pushFront ( std :: move ( pfFifth ) );
    if ( ! equals ( lref, equiv10 ) ) {
        pTestLib->logError("'LTC-00310-IT-pushFrontMove2-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00310-IT-pushFrontMove2-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackAllOfInitList-cpp-xx : LTC-00311-IT-pushBackAllOfInitList-cpp-xx */
    lref.pushBackAllOf ( pbValues );
    if ( ! equals ( lref, equiv11 ) ) {
        pTestLib->logError("'LTC-00311-IT-pushBackAllOfInitList-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00311-IT-pushBackAllOfInitList-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackAllOfColl-cpp-xx : LTC-00312-IT-pushBackAllOfColl-cpp-xx */
    __TestedType < __EnclosedType > v12 = pbValues;
    lref.pushBackAllOf ( v12 );
    if ( ! equals ( lref, equiv12 ) ) {
        pTestLib->logError("'LTC-00312-IT-pushBackAllOfColl-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00312-IT-pushBackAllOfColl-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontAllOfInitList-cpp-xx : LTC-00313-IT-pushFrontAllOfInitList-cpp-xx */
    lref.pushFrontAllOf ( pfValues );
    if ( ! equals ( lref, equiv13 ) ) {
        pTestLib->logError("'LTC-00313-IT-pushFrontAllOfInitList-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00313-IT-pushFrontAllOfInitList-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontAllOfColl-cpp-xx : LTC-00314-IT-pushFrontAllOfColl-cpp-xx */
    __TestedType < __EnclosedType > v14 = pfValues;
    lref.pushFrontAllOf ( v14 );
    if ( ! equals ( lref, equiv14 ) ) {
        pTestLib->logError("'LTC-00314-IT-pushFrontAllOfColl-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00314-IT-pushFrontAllOfColl-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackItRange1-cpp-xx : LTC-00315-IT-pushBackItRange1-cpp-xx */
    lref.pushBackAllOf ( b1, e1 );
    if ( ! equals ( lref, equiv15 ) ) {
        pTestLib->logError("'LTC-00315-IT-pushBackItRange1-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00315-IT-pushBackItRange1-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontItRange1-cpp-xx : LTC-00316-IT-pushFrontItRange1-cpp-xx */
    lref.pushFrontAllOf ( b1, e1 );
    if ( ! equals ( lref, equiv16 ) ) {
        pTestLib->logError("'LTC-00316-IT-pushFrontItRange1-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00316-IT-pushFrontItRange1-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackItRange2-cpp-xx : LTC-00317-IT-pushBackItRange2-cpp-xx */
    lref.pushBackAllOf ( b2, e2 );
    if ( ! equals ( lref, equiv17 ) ) {
        pTestLib->logError("'LTC-00317-IT-pushBackItRange2-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00317-IT-pushBackItRange2-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontItRange2-cpp-xx : LTC-00318-IT-pushFrontItRange2-cpp-xx */
    lref.pushFrontAllOf ( b2, e2 );
    if ( ! equals ( lref, equiv18 ) ) {
        pTestLib->logError("'LTC-00318-IT-pushFrontItRange2-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00318-IT-pushFrontItRange2-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackItRange3-cpp-xx : LTC-00319-IT-pushBackItRange3-cpp-xx */
    lref.pushBackAllOf ( b3, e3 );
    if ( ! equals ( lref, equiv19 ) ) {
        pTestLib->logError("'LTC-00319-IT-pushBackItRange3-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00319-IT-pushBackItRange3-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontItRange3-cpp-xx : LTC-00320-IT-pushFrontItRange3-cpp-xx */
    lref.pushFrontAllOf ( b3, e3 );
    if ( ! equals ( lref, equiv20 ) ) {
        pTestLib->logError("'LTC-00320-IT-pushFrontItRange3-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00320-IT-pushFrontItRange3-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushBackValues-cpp-xx : LTC-00321-IT-pushBackValues-cpp-xx */
    lref.pushBackAll ( values ... );
    if ( ! equals ( lref, equiv21 ) ) {
        pTestLib->logError("'LTC-00321-IT-pushBackValues-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00321-IT-pushBackValues-" __CDS_cpplang_core_version_name "' OK");


    /* ListTestGroup-BoundaryInsertion-pushFrontValues-cpp-xx : LTC-00322-IT-pushFrontValues-cpp-xx */
    lref.pushFrontAll ( values ... );
    if ( ! equals ( lref, equiv22 ) ) {
        pTestLib->logError("'LTC-00322-IT-pushFrontValues-" __CDS_cpplang_core_version_name "' failed");
        return false;
    }
    pTestLib->logOK("'LTC-00322-IT-pushFrontValues-" __CDS_cpplang_core_version_name "' OK");

    return true;
}


/* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
template <
        template < typename ... > class __TestedType,
        typename __EnclosedType,
        typename ... __Values
> auto listTestGroupRelativeInsertion (
        Test * pTestLib,
        std :: initializer_list < __EnclosedType > const & initValues,
        typename List < __EnclosedType > :: Iterator ( List < __EnclosedType > :: * pBeginFn ) (),
        typename List < __EnclosedType > :: Iterator ( List < __EnclosedType > :: * pEndFn ) (),
        typename List < __EnclosedType > :: ConstIterator ( List < __EnclosedType > :: * pBeginCFn ) () const,
        typename List < __EnclosedType > :: ConstIterator ( List < __EnclosedType > :: * pEndCFn ) () const,
        typename List < __EnclosedType > :: ReverseIterator ( List < __EnclosedType > :: * pRBeginFn ) (),
        typename List < __EnclosedType > :: ReverseIterator ( List < __EnclosedType > :: * pREndFn ) (),
        typename List < __EnclosedType > :: ConstReverseIterator ( List < __EnclosedType > :: * pRBeginCFn ) () const,
        typename List < __EnclosedType > :: ConstReverseIterator ( List < __EnclosedType > :: * pREndCFn ) () const,
        Size case1Offset,
        Size case2Offset,
        Size case3Offset,
        Size case4Offset,
        __EnclosedType const & singleValue1,
        __EnclosedType const & singleValue2,
        __EnclosedType const & singleValue3,
        std :: initializer_list < __EnclosedType > const & multipleValues1,
        std :: initializer_list < __EnclosedType > const & multipleValues2,
        std :: initializer_list < __EnclosedType > const & multipleValues3,

        std :: initializer_list < __EnclosedType > const & resSingle1Case1,
        std :: initializer_list < __EnclosedType > const & resSingle1Case2,
        std :: initializer_list < __EnclosedType > const & resSingle1Case3,
        std :: initializer_list < __EnclosedType > const & resSingle1Case4,
        std :: initializer_list < __EnclosedType > const & resSingle1RevCase1,
        std :: initializer_list < __EnclosedType > const & resSingle1RevCase2,
        std :: initializer_list < __EnclosedType > const & resSingle1RevCase3,
        std :: initializer_list < __EnclosedType > const & resSingle1RevCase4,

        std :: initializer_list < __EnclosedType > const & resSingle2Case1,
        std :: initializer_list < __EnclosedType > const & resSingle2Case2,
        std :: initializer_list < __EnclosedType > const & resSingle2Case3,
        std :: initializer_list < __EnclosedType > const & resSingle2Case4,
        std :: initializer_list < __EnclosedType > const & resSingle2RevCase1,
        std :: initializer_list < __EnclosedType > const & resSingle2RevCase2,
        std :: initializer_list < __EnclosedType > const & resSingle2RevCase3,
        std :: initializer_list < __EnclosedType > const & resSingle2RevCase4,

        std :: initializer_list < __EnclosedType > const & resSingle3Case1,
        std :: initializer_list < __EnclosedType > const & resSingle3Case2,
        std :: initializer_list < __EnclosedType > const & resSingle3Case3,
        std :: initializer_list < __EnclosedType > const & resSingle3Case4,
        std :: initializer_list < __EnclosedType > const & resSingle3RevCase1,
        std :: initializer_list < __EnclosedType > const & resSingle3RevCase2,
        std :: initializer_list < __EnclosedType > const & resSingle3RevCase3,
        std :: initializer_list < __EnclosedType > const & resSingle3RevCase4,

        std :: initializer_list < __EnclosedType > const & resMultiple1Case1,
        std :: initializer_list < __EnclosedType > const & resMultiple1Case2,
        std :: initializer_list < __EnclosedType > const & resMultiple1Case3,
        std :: initializer_list < __EnclosedType > const & resMultiple1Case4,
        std :: initializer_list < __EnclosedType > const & resMultiple1RevCase1,
        std :: initializer_list < __EnclosedType > const & resMultiple1RevCase2,
        std :: initializer_list < __EnclosedType > const & resMultiple1RevCase3,
        std :: initializer_list < __EnclosedType > const & resMultiple1RevCase4,

        std :: initializer_list < __EnclosedType > const & resMultiple2Case1,
        std :: initializer_list < __EnclosedType > const & resMultiple2Case2,
        std :: initializer_list < __EnclosedType > const & resMultiple2Case3,
        std :: initializer_list < __EnclosedType > const & resMultiple2Case4,
        std :: initializer_list < __EnclosedType > const & resMultiple2RevCase1,
        std :: initializer_list < __EnclosedType > const & resMultiple2RevCase2,
        std :: initializer_list < __EnclosedType > const & resMultiple2RevCase3,
        std :: initializer_list < __EnclosedType > const & resMultiple2RevCase4,

        std :: initializer_list < __EnclosedType > const & resMultiple3Case1,
        std :: initializer_list < __EnclosedType > const & resMultiple3Case2,
        std :: initializer_list < __EnclosedType > const & resMultiple3Case3,
        std :: initializer_list < __EnclosedType > const & resMultiple3Case4,
        std :: initializer_list < __EnclosedType > const & resMultiple3RevCase1,
        std :: initializer_list < __EnclosedType > const & resMultiple3RevCase2,
        std :: initializer_list < __EnclosedType > const & resMultiple3RevCase3,
        std :: initializer_list < __EnclosedType > const & resMultiple3RevCase4,

        std :: initializer_list < __EnclosedType > const & resMultipleVCase1,
        std :: initializer_list < __EnclosedType > const & resMultipleVCase2,
        std :: initializer_list < __EnclosedType > const & resMultipleVCase3,
        std :: initializer_list < __EnclosedType > const & resMultipleVCase4,
        std :: initializer_list < __EnclosedType > const & resMultipleVRevCase1,
        std :: initializer_list < __EnclosedType > const & resMultipleVRevCase2,
        std :: initializer_list < __EnclosedType > const & resMultipleVRevCase3,
        std :: initializer_list < __EnclosedType > const & resMultipleVRevCase4,

        std :: initializer_list < __EnclosedType > const & aresSingle1Case1,
        std :: initializer_list < __EnclosedType > const & aresSingle1Case2,
        std :: initializer_list < __EnclosedType > const & aresSingle1Case3,
        std :: initializer_list < __EnclosedType > const & aresSingle1Case4,
        std :: initializer_list < __EnclosedType > const & aresSingle1RevCase1,
        std :: initializer_list < __EnclosedType > const & aresSingle1RevCase2,
        std :: initializer_list < __EnclosedType > const & aresSingle1RevCase3,
        std :: initializer_list < __EnclosedType > const & aresSingle1RevCase4,

        std :: initializer_list < __EnclosedType > const & aresSingle2Case1,
        std :: initializer_list < __EnclosedType > const & aresSingle2Case2,
        std :: initializer_list < __EnclosedType > const & aresSingle2Case3,
        std :: initializer_list < __EnclosedType > const & aresSingle2Case4,
        std :: initializer_list < __EnclosedType > const & aresSingle2RevCase1,
        std :: initializer_list < __EnclosedType > const & aresSingle2RevCase2,
        std :: initializer_list < __EnclosedType > const & aresSingle2RevCase3,
        std :: initializer_list < __EnclosedType > const & aresSingle2RevCase4,

        std :: initializer_list < __EnclosedType > const & aresSingle3Case1,
        std :: initializer_list < __EnclosedType > const & aresSingle3Case2,
        std :: initializer_list < __EnclosedType > const & aresSingle3Case3,
        std :: initializer_list < __EnclosedType > const & aresSingle3Case4,
        std :: initializer_list < __EnclosedType > const & aresSingle3RevCase1,
        std :: initializer_list < __EnclosedType > const & aresSingle3RevCase2,
        std :: initializer_list < __EnclosedType > const & aresSingle3RevCase3,
        std :: initializer_list < __EnclosedType > const & aresSingle3RevCase4,

        std :: initializer_list < __EnclosedType > const & aresMultiple1Case1,
        std :: initializer_list < __EnclosedType > const & aresMultiple1Case2,
        std :: initializer_list < __EnclosedType > const & aresMultiple1Case3,
        std :: initializer_list < __EnclosedType > const & aresMultiple1Case4,
        std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase1,
        std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase2,
        std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase3,
        std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase4,

        std :: initializer_list < __EnclosedType > const & aresMultiple2Case1,
        std :: initializer_list < __EnclosedType > const & aresMultiple2Case2,
        std :: initializer_list < __EnclosedType > const & aresMultiple2Case3,
        std :: initializer_list < __EnclosedType > const & aresMultiple2Case4,
        std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase1,
        std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase2,
        std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase3,
        std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase4,

        std :: initializer_list < __EnclosedType > const & aresMultiple3Case1,
        std :: initializer_list < __EnclosedType > const & aresMultiple3Case2,
        std :: initializer_list < __EnclosedType > const & aresMultiple3Case3,
        std :: initializer_list < __EnclosedType > const & aresMultiple3Case4,
        std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase1,
        std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase2,
        std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase3,
        std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase4,

        std :: initializer_list < __EnclosedType > const & aresMultipleVCase1,
        std :: initializer_list < __EnclosedType > const & aresMultipleVCase2,
        std :: initializer_list < __EnclosedType > const & aresMultipleVCase3,
        std :: initializer_list < __EnclosedType > const & aresMultipleVCase4,
        std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase1,
        std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase2,
        std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase3,
        std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase4,
        __Values const & ... values
) -> bool {

    __TestedType < __EnclosedType > underTest = initValues;
    List < __EnclosedType > & lref = underTest;

#define resetData() underTest = initValues
#define __b1 (lref .* pBeginFn)()
#define __b2 (lref .* pBeginCFn)()
#define __b3 (lref .* pRBeginFn)()
#define __b4 (lref .* pRBeginCFn)()
#define __e1 (lref .* pEndFn)()
#define __e2 (lref .* pEndCFn)()
#define __e3 (lref .* pREndFn)()
#define __e4 (lref .* pREndCFn)()
#define __b(c) __b ## c
#define __e(c) __e ## c
#define b(c) __b(c)
#define e(c) __e(c)

#define sInsCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, singleValue ## c ) || ! equals ( lref, resSingle ## c ## Case ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" #name "ItCase" #ic "SingleValue" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "SingleValue" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define sInsRevCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, singleValue ## c ) || ! equals ( lref, resSingle ## c ## RevCase ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" # name "ItCase" #ic "SingleValue" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "SingleValue" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define saInsCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, singleValue ## c ) || ! equals ( lref, aresSingle ## c ## Case ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" #name "ItCase" #ic "SingleValue" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "SingleValue" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define saInsRevCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, singleValue ## c ) || ! equals ( lref, aresSingle ## c ## RevCase ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" # name "ItCase" #ic "SingleValue" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "SingleValue" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvInsCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, multipleValues ## c ) || ! equals ( lref, resMultiple ## c ## Case ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" #name "ItCase" #ic "MultipleValues" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "MultipleValues" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvInsRevCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, multipleValues ## c ) || ! equals ( lref, resMultiple ## c ## RevCase ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" # name "ItCase" #ic "MultipleValues" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "MultipleValues" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvaInsCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, multipleValues ## c ) || ! equals ( lref, aresMultiple ## c ## Case ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" #name "ItCase" #ic "MultipleValues" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "MultipleValues" #c "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvaInsRevCase(name, no, ic, c, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, multipleValues ## c ) || ! equals ( lref, aresMultiple ## c ## RevCase ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" # name "ItCase" #ic "MultipleValues" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "MultipleValues" #c "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvpInsCase(name, no, ic, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, values ... ) || ! equals ( lref, resMultipleV ## Case ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" #name "ItCase" #ic "Pack" "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "Pack" "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvpInsRevCase(name, no, ic, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, values ... ) || ! equals ( lref, resMultipleV ## RevCase ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" # name "ItCase" #ic "Pack" "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "Pack" "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvpaInsCase(name, no, ic, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, values ... ) || ! equals ( lref, aresMultipleV ## Case ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" #name "ItCase" #ic "Pack" "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "Pack" "OffsetCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );

#define mvpaInsRevCase(name, no, ic, oc, suc) \
    resetData();                          \
    auto it ## no = b(ic);                 \
    for (int i = 0; i < case ## oc ## Offset; ++ i) \
        ++ it ## no;  \
    if ( suc != lref.name( it ## no, values ... ) || ! equals ( lref, aresMultipleV ## RevCase ## oc ) ) { \
        pTestLib->logError ("'LTC-" # no "-" # name "ItCase" #ic "Pack" "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' failed" ); \
        return false;                              \
    }                                              \
                                                   \
    pTestLib->logOK ("'LTC-" # no "-" #name "ItCase" #ic "Pack" "OffsetRevCase" # oc "-" __CDS_cpplang_core_version_name "' OK" );


    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue1OffsetCase1-cpp-xx : LTC-00401-IT-insertBeforeItCase1SingleValue1OffsetCase1-cpp-xx */
    sInsCase ( insertBefore, 401, 1, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue1OffsetCase2-cpp-xx : LTC-00402-IT-insertBeforeItCase1SingleValue1OffsetCase2-cpp-xx */
    sInsCase ( insertBefore, 402, 1, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue1OffsetCase3-cpp-xx : LTC-00403-IT-insertBeforeItCase1SingleValue1OffsetCase3-cpp-xx */
    sInsCase ( insertBefore, 403, 1, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue1OffsetCase4-cpp-xx : LTC-00404-IT-insertBeforeItCase1SingleValue1OffsetCase4-cpp-xx */
    sInsCase ( insertBefore, 404, 1, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue2OffsetCase1-cpp-xx : LTC-00405-IT-insertBeforeItCase1SingleValue2OffsetCase1-cpp-xx */
    sInsCase ( insertBefore, 405, 1, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue2OffsetCase2-cpp-xx : LTC-00406-IT-insertBeforeItCase1SingleValue2OffsetCase2-cpp-xx */
    sInsCase ( insertBefore, 406, 1, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue2OffsetCase3-cpp-xx : LTC-00407-IT-insertBeforeItCase1SingleValue2OffsetCase3-cpp-xx */
    sInsCase ( insertBefore, 407, 1, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue2OffsetCase4-cpp-xx : LTC-00408-IT-insertBeforeItCase1SingleValue2OffsetCase4-cpp-xx */
    sInsCase ( insertBefore, 408, 1, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue3OffsetCase1-cpp-xx : LTC-00409-IT-insertBeforeItCase1SingleValue3OffsetCase1-cpp-xx */
    sInsCase ( insertBefore, 409, 1, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue3OffsetCase2-cpp-xx : LTC-00410-IT-insertBeforeItCase1SingleValue3OffsetCase2-cpp-xx */
    sInsCase ( insertBefore, 410, 1, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue3OffsetCase3-cpp-xx : LTC-00411-IT-insertBeforeItCase1SingleValue3OffsetCase3-cpp-xx */
    sInsCase ( insertBefore, 411, 1, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase1SingleValue3OffsetCase4-cpp-xx : LTC-00412-IT-insertBeforeItCase1SingleValue3OffsetCase4-cpp-xx */
    sInsCase ( insertBefore, 412, 1, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue1OffsetCase1-cpp-xx : LTC-00413-IT-insertBeforeItCase3SingleValue1OffsetCase1-cpp-xx */
    sInsRevCase ( insertBefore, 413, 3, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue1OffsetCase2-cpp-xx : LTC-00414-IT-insertBeforeItCase3SingleValue1OffsetCase2-cpp-xx */
    sInsRevCase ( insertBefore, 414, 3, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue1OffsetCase3-cpp-xx : LTC-00415-IT-insertBeforeItCase3SingleValue1OffsetCase3-cpp-xx */
    sInsRevCase ( insertBefore, 415, 3, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue1OffsetCase4-cpp-xx : LTC-00416-IT-insertBeforeItCase3SingleValue1OffsetCase4-cpp-xx */
    sInsRevCase ( insertBefore, 416, 3, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue2OffsetCase1-cpp-xx : LTC-00417-IT-insertBeforeItCase3SingleValue2OffsetCase1-cpp-xx */
    sInsRevCase ( insertBefore, 417, 3, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue2OffsetCase2-cpp-xx : LTC-00418-IT-insertBeforeItCase3SingleValue2OffsetCase2-cpp-xx */
    sInsRevCase ( insertBefore, 418, 3, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue2OffsetCase3-cpp-xx : LTC-00419-IT-insertBeforeItCase3SingleValue2OffsetCase3-cpp-xx */
    sInsRevCase ( insertBefore, 419, 3, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue2OffsetCase4-cpp-xx : LTC-00420-IT-insertBeforeItCase3SingleValue2OffsetCase4-cpp-xx */
    sInsRevCase ( insertBefore, 420, 3, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue3OffsetCase1-cpp-xx : LTC-00421-IT-insertBeforeItCase3SingleValue3OffsetCase1-cpp-xx */
    sInsRevCase ( insertBefore, 421, 3, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue3OffsetCase2-cpp-xx : LTC-00422-IT-insertBeforeItCase3SingleValue3OffsetCase2-cpp-xx */
    sInsRevCase ( insertBefore, 422, 3, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue3OffsetCase3-cpp-xx : LTC-00423-IT-insertBeforeItCase3SingleValue3OffsetCase3-cpp-xx */
    sInsRevCase ( insertBefore, 423, 3, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase3SingleValue3OffsetCase4-cpp-xx : LTC-00424-IT-insertBeforeItCase3SingleValue3OffsetCase4-cpp-xx */
    sInsRevCase ( insertBefore, 424, 3, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue1OffsetCase1-cpp-xx : LTC-00425-IT-insertBeforeItCase2SingleValue1OffsetCase1-cpp-xx */
    sInsCase ( insertBefore, 425, 2, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue1OffsetCase2-cpp-xx : LTC-00426-IT-insertBeforeItCase2SingleValue1OffsetCase2-cpp-xx */
    sInsCase ( insertBefore, 426, 2, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue1OffsetCase3-cpp-xx : LTC-00427-IT-insertBeforeItCase2SingleValue1OffsetCase3-cpp-xx */
    sInsCase ( insertBefore, 427, 2, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue1OffsetCase4-cpp-xx : LTC-00428-IT-insertBeforeItCase2SingleValue1OffsetCase4-cpp-xx */
    sInsCase ( insertBefore, 428, 2, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue2OffsetCase1-cpp-xx : LTC-00429-IT-insertBeforeItCase2SingleValue2OffsetCase1-cpp-xx */
    sInsCase ( insertBefore, 429, 2, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue2OffsetCase2-cpp-xx : LTC-00430-IT-insertBeforeItCase2SingleValue2OffsetCase2-cpp-xx */
    sInsCase ( insertBefore, 430, 2, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue2OffsetCase3-cpp-xx : LTC-00431-IT-insertBeforeItCase2SingleValue2OffsetCase3-cpp-xx */
    sInsCase ( insertBefore, 431, 2, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue2OffsetCase4-cpp-xx : LTC-00432-IT-insertBeforeItCase2SingleValue2OffsetCase4-cpp-xx */
    sInsCase ( insertBefore, 432, 2, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue3OffsetCase1-cpp-xx : LTC-00433-IT-insertBeforeItCase2SingleValue3OffsetCase1-cpp-xx */
    sInsCase ( insertBefore, 433, 2, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue3OffsetCase2-cpp-xx : LTC-00434-IT-insertBeforeItCase2SingleValue3OffsetCase2-cpp-xx */
    sInsCase ( insertBefore, 434, 2, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue3OffsetCase3-cpp-xx : LTC-00435-IT-insertBeforeItCase2SingleValue3OffsetCase3-cpp-xx */
    sInsCase ( insertBefore, 435, 2, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase2SingleValue3OffsetCase4-cpp-xx : LTC-00436-IT-insertBeforeItCase2SingleValue3OffsetCase4-cpp-xx */
    sInsCase ( insertBefore, 436, 2, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue1OffsetCase1-cpp-xx : LTC-00437-IT-insertBeforeItCase4SingleValue1OffsetCase1-cpp-xx */
    sInsRevCase ( insertBefore, 437, 4, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue1OffsetCase2-cpp-xx : LTC-00438-IT-insertBeforeItCase4SingleValue1OffsetCase2-cpp-xx */
    sInsRevCase ( insertBefore, 438, 4, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue1OffsetCase3-cpp-xx : LTC-00439-IT-insertBeforeItCase4SingleValue1OffsetCase3-cpp-xx */
    sInsRevCase ( insertBefore, 439, 4, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue1OffsetCase4-cpp-xx : LTC-00440-IT-insertBeforeItCase4SingleValue1OffsetCase4-cpp-xx */
    sInsRevCase ( insertBefore, 440, 4, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue2OffsetCase1-cpp-xx : LTC-00441-IT-insertBeforeItCase4SingleValue2OffsetCase1-cpp-xx */
    sInsRevCase ( insertBefore, 441, 4, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue2OffsetCase2-cpp-xx : LTC-00442-IT-insertBeforeItCase4SingleValue2OffsetCase2-cpp-xx */
    sInsRevCase ( insertBefore, 442, 4, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue2OffsetCase3-cpp-xx : LTC-00443-IT-insertBeforeItCase4SingleValue2OffsetCase3-cpp-xx */
    sInsRevCase ( insertBefore, 443, 4, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue2OffsetCase4-cpp-xx : LTC-00444-IT-insertBeforeItCase4SingleValue2OffsetCase4-cpp-xx */
    sInsRevCase ( insertBefore, 444, 4, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue3OffsetCase1-cpp-xx : LTC-00445-IT-insertBeforeItCase4SingleValue3OffsetCase1-cpp-xx */
    sInsRevCase ( insertBefore, 445, 4, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue3OffsetCase2-cpp-xx : LTC-00446-IT-insertBeforeItCase4SingleValue3OffsetCase2-cpp-xx */
    sInsRevCase ( insertBefore, 446, 4, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue3OffsetCase3-cpp-xx : LTC-00447-IT-insertBeforeItCase4SingleValue3OffsetCase3-cpp-xx */
    sInsRevCase ( insertBefore, 447, 4, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertBeforeItCase4SingleValue3OffsetCase4-cpp-xx : LTC-00448-IT-insertBeforeItCase4SingleValue3OffsetCase4-cpp-xx */
    sInsRevCase ( insertBefore, 448, 4, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue1OffsetCase1-cpp-xx : LTC-00449-IT-insertAfterItCase1SingleValue1OffsetCase1-cpp-xx */
    saInsCase ( insertAfter, 449, 1, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue1OffsetCase2-cpp-xx : LTC-00450-IT-insertAfterItCase1SingleValue1OffsetCase2-cpp-xx */
    saInsCase ( insertAfter, 450, 1, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue1OffsetCase3-cpp-xx : LTC-00451-IT-insertAfterItCase1SingleValue1OffsetCase3-cpp-xx */
    saInsCase ( insertAfter, 451, 1, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue1OffsetCase4-cpp-xx : LTC-00452-IT-insertAfterItCase1SingleValue1OffsetCase4-cpp-xx */
    saInsCase ( insertAfter, 452, 1, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue2OffsetCase1-cpp-xx : LTC-00453-IT-insertAfterItCase1SingleValue2OffsetCase1-cpp-xx */
    saInsCase ( insertAfter, 453, 1, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue2OffsetCase2-cpp-xx : LTC-00454-IT-insertAfterItCase1SingleValue2OffsetCase2-cpp-xx */
    saInsCase ( insertAfter, 454, 1, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue2OffsetCase3-cpp-xx : LTC-00455-IT-insertAfterItCase1SingleValue2OffsetCase3-cpp-xx */
    saInsCase ( insertAfter, 455, 1, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue2OffsetCase4-cpp-xx : LTC-00456-IT-insertAfterItCase1SingleValue2OffsetCase4-cpp-xx */
    saInsCase ( insertAfter, 456, 1, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue3OffsetCase1-cpp-xx : LTC-00457-IT-insertAfterItCase1SingleValue3OffsetCase1-cpp-xx */
    saInsCase ( insertAfter, 457, 1, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue3OffsetCase2-cpp-xx : LTC-00458-IT-insertAfterItCase1SingleValue3OffsetCase2-cpp-xx */
    saInsCase ( insertAfter, 458, 1, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue3OffsetCase3-cpp-xx : LTC-00459-IT-insertAfterItCase1SingleValue3OffsetCase3-cpp-xx */
    saInsCase ( insertAfter, 459, 1, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase1SingleValue3OffsetCase4-cpp-xx : LTC-00460-IT-insertAfterItCase1SingleValue3OffsetCase4-cpp-xx */
    saInsCase ( insertAfter, 460, 1, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue1OffsetCase1-cpp-xx : LTC-00461-IT-insertAfterItCase3SingleValue1OffsetCase1-cpp-xx */
    saInsRevCase ( insertAfter, 461, 3, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue1OffsetCase2-cpp-xx : LTC-00462-IT-insertAfterItCase3SingleValue1OffsetCase2-cpp-xx */
    saInsRevCase ( insertAfter, 462, 3, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue1OffsetCase3-cpp-xx : LTC-00463-IT-insertAfterItCase3SingleValue1OffsetCase3-cpp-xx */
    saInsRevCase ( insertAfter, 463, 3, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue1OffsetCase4-cpp-xx : LTC-00464-IT-insertAfterItCase3SingleValue1OffsetCase4-cpp-xx */
    saInsRevCase ( insertAfter, 464, 3, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue2OffsetCase1-cpp-xx : LTC-00465-IT-insertAfterItCase3SingleValue2OffsetCase1-cpp-xx */
    saInsRevCase ( insertAfter, 465, 3, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue2OffsetCase2-cpp-xx : LTC-00466-IT-insertAfterItCase3SingleValue2OffsetCase2-cpp-xx */
    saInsRevCase ( insertAfter, 466, 3, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue2OffsetCase3-cpp-xx : LTC-00467-IT-insertAfterItCase3SingleValue2OffsetCase3-cpp-xx */
    saInsRevCase ( insertAfter, 467, 3, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue2OffsetCase4-cpp-xx : LTC-00468-IT-insertAfterItCase3SingleValue2OffsetCase4-cpp-xx */
    saInsRevCase ( insertAfter, 468, 3, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue3OffsetCase1-cpp-xx : LTC-00469-IT-insertAfterItCase3SingleValue3OffsetCase1-cpp-xx */
    saInsRevCase ( insertAfter, 469, 3, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue3OffsetCase2-cpp-xx : LTC-00470-IT-insertAfterItCase3SingleValue3OffsetCase2-cpp-xx */
    saInsRevCase ( insertAfter, 470, 3, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue3OffsetCase3-cpp-xx : LTC-00471-IT-insertAfterItCase3SingleValue3OffsetCase3-cpp-xx */
    saInsRevCase ( insertAfter, 471, 3, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase3SingleValue3OffsetCase4-cpp-xx : LTC-00472-IT-insertAfterItCase3SingleValue3OffsetCase4-cpp-xx */
    saInsRevCase ( insertAfter, 472, 3, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue1OffsetCase1-cpp-xx : LTC-00473-IT-insertAfterItCase2SingleValue1OffsetCase1-cpp-xx */
    saInsCase ( insertAfter, 473, 2, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue1OffsetCase2-cpp-xx : LTC-00474-IT-insertAfterItCase2SingleValue1OffsetCase2-cpp-xx */
    saInsCase ( insertAfter, 474, 2, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue1OffsetCase3-cpp-xx : LTC-00475-IT-insertAfterItCase2SingleValue1OffsetCase3-cpp-xx */
    saInsCase ( insertAfter, 475, 2, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue1OffsetCase4-cpp-xx : LTC-00476-IT-insertAfterItCase2SingleValue1OffsetCase4-cpp-xx */
    saInsCase ( insertAfter, 476, 2, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue2OffsetCase1-cpp-xx : LTC-00477-IT-insertAfterItCase2SingleValue2OffsetCase1-cpp-xx */
    saInsCase ( insertAfter, 477, 2, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue2OffsetCase2-cpp-xx : LTC-00478-IT-insertAfterItCase2SingleValue2OffsetCase2-cpp-xx */
    saInsCase ( insertAfter, 478, 2, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue2OffsetCase3-cpp-xx : LTC-00479-IT-insertAfterItCase2SingleValue2OffsetCase3-cpp-xx */
    saInsCase ( insertAfter, 479, 2, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue2OffsetCase4-cpp-xx : LTC-00480-IT-insertAfterItCase2SingleValue2OffsetCase4-cpp-xx */
    saInsCase ( insertAfter, 480, 2, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue3OffsetCase1-cpp-xx : LTC-00481-IT-insertAfterItCase2SingleValue3OffsetCase1-cpp-xx */
    saInsCase ( insertAfter, 481, 2, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue3OffsetCase2-cpp-xx : LTC-00482-IT-insertAfterItCase2SingleValue3OffsetCase2-cpp-xx */
    saInsCase ( insertAfter, 482, 2, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue3OffsetCase3-cpp-xx : LTC-00483-IT-insertAfterItCase2SingleValue3OffsetCase3-cpp-xx */
    saInsCase ( insertAfter, 483, 2, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase2SingleValue3OffsetCase4-cpp-xx : LTC-00484-IT-insertAfterItCase2SingleValue3OffsetCase4-cpp-xx */
    saInsCase ( insertAfter, 484, 2, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue1OffsetCase1-cpp-xx : LTC-00485-IT-insertAfterItCase4SingleValue1OffsetCase1-cpp-xx */
    saInsRevCase ( insertAfter, 485, 4, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue1OffsetCase2-cpp-xx : LTC-00486-IT-insertAfterItCase4SingleValue1OffsetCase2-cpp-xx */
    saInsRevCase ( insertAfter, 486, 4, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue1OffsetCase3-cpp-xx : LTC-00487-IT-insertAfterItCase4SingleValue1OffsetCase3-cpp-xx */
    saInsRevCase ( insertAfter, 487, 4, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue1OffsetCase4-cpp-xx : LTC-00488-IT-insertAfterItCase4SingleValue1OffsetCase4-cpp-xx */
    saInsRevCase ( insertAfter, 488, 4, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue2OffsetCase1-cpp-xx : LTC-00489-IT-insertAfterItCase4SingleValue2OffsetCase1-cpp-xx */
    saInsRevCase ( insertAfter, 489, 4, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue2OffsetCase2-cpp-xx : LTC-00490-IT-insertAfterItCase4SingleValue2OffsetCase2-cpp-xx */
    saInsRevCase ( insertAfter, 490, 4, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue2OffsetCase3-cpp-xx : LTC-00491-IT-insertAfterItCase4SingleValue2OffsetCase3-cpp-xx */
    saInsRevCase ( insertAfter, 491, 4, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue2OffsetCase4-cpp-xx : LTC-00492-IT-insertAfterItCase4SingleValue2OffsetCase4-cpp-xx */
    saInsRevCase ( insertAfter, 492, 4, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue3OffsetCase1-cpp-xx : LTC-00493-IT-insertAfterItCase4SingleValue3OffsetCase1-cpp-xx */
    saInsRevCase ( insertAfter, 493, 4, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue3OffsetCase2-cpp-xx : LTC-00494-IT-insertAfterItCase4SingleValue3OffsetCase2-cpp-xx */
    saInsRevCase ( insertAfter, 494, 4, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue3OffsetCase3-cpp-xx : LTC-00495-IT-insertAfterItCase4SingleValue3OffsetCase3-cpp-xx */
    saInsRevCase ( insertAfter, 495, 4, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAfterItCase4SingleValue3OffsetCase4-cpp-xx : LTC-00496-IT-insertAfterItCase4SingleValue3OffsetCase4-cpp-xx */
    saInsRevCase ( insertAfter, 496, 4, 3, 4, false )


    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues1OffsetCase1-cpp-xx : LTC-00497-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase1-cpp-xx */
    mvInsCase ( insertAllOfBefore, 497, 1, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues1OffsetCase2-cpp-xx : LTC-00498-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase2-cpp-xx */
    mvInsCase ( insertAllOfBefore, 498, 1, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues1OffsetCase3-cpp-xx : LTC-00499-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase3-cpp-xx */
    mvInsCase ( insertAllOfBefore, 499, 1, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues1OffsetCase4-cpp-xx : LTC-00500-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase4-cpp-xx */
    mvInsCase ( insertAllOfBefore, 500, 1, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues2OffsetCase1-cpp-xx : LTC-00501-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase1-cpp-xx */
    mvInsCase ( insertAllOfBefore, 501, 1, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues2OffsetCase2-cpp-xx : LTC-00502-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase2-cpp-xx */
    mvInsCase ( insertAllOfBefore, 502, 1, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues2OffsetCase3-cpp-xx : LTC-00503-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase3-cpp-xx */
    mvInsCase ( insertAllOfBefore, 503, 1, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues2OffsetCase4-cpp-xx : LTC-00504-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase4-cpp-xx */
    mvInsCase ( insertAllOfBefore, 504, 1, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues3OffsetCase1-cpp-xx : LTC-00505-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase1-cpp-xx */
    mvInsCase ( insertAllOfBefore, 505, 1, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues3OffsetCase2-cpp-xx : LTC-00506-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase2-cpp-xx */
    mvInsCase ( insertAllOfBefore, 506, 1, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues3OffsetCase3-cpp-xx : LTC-00507-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase3-cpp-xx */
    mvInsCase ( insertAllOfBefore, 507, 1, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase1MultipleValues3OffsetCase4-cpp-xx : LTC-00508-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase4-cpp-xx */
    mvInsCase ( insertAllOfBefore, 508, 1, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues1OffsetCase1-cpp-xx : LTC-00509-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase1-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 509, 3, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues1OffsetCase2-cpp-xx : LTC-00510-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase2-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 510, 3, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues1OffsetCase3-cpp-xx : LTC-00511-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase3-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 511, 3, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues1OffsetCase4-cpp-xx : LTC-00512-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase4-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 512, 3, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues2OffsetCase1-cpp-xx : LTC-00513-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase1-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 513, 3, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues2OffsetCase2-cpp-xx : LTC-00514-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase2-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 514, 3, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues2OffsetCase3-cpp-xx : LTC-00515-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase3-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 515, 3, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues2OffsetCase4-cpp-xx : LTC-00516-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase4-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 516, 3, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues3OffsetCase1-cpp-xx : LTC-00517-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase1-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 517, 3, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues3OffsetCase2-cpp-xx : LTC-00518-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase2-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 518, 3, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues3OffsetCase3-cpp-xx : LTC-00519-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase3-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 519, 3, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase3MultipleValues3OffsetCase4-cpp-xx : LTC-00520-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase4-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 520, 3, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues1OffsetCase1-cpp-xx : LTC-00521-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase1-cpp-xx */
    mvInsCase ( insertAllOfBefore, 521, 2, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues1OffsetCase2-cpp-xx : LTC-00522-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase2-cpp-xx */
    mvInsCase ( insertAllOfBefore, 522, 2, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues1OffsetCase3-cpp-xx : LTC-00523-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase3-cpp-xx */
    mvInsCase ( insertAllOfBefore, 523, 2, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues1OffsetCase4-cpp-xx : LTC-00524-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase4-cpp-xx */
    mvInsCase ( insertAllOfBefore, 524, 2, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues2OffsetCase1-cpp-xx : LTC-00525-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase1-cpp-xx */
    mvInsCase ( insertAllOfBefore, 525, 2, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues2OffsetCase2-cpp-xx : LTC-00526-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase2-cpp-xx */
    mvInsCase ( insertAllOfBefore, 526, 2, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues2OffsetCase3-cpp-xx : LTC-00527-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase3-cpp-xx */
    mvInsCase ( insertAllOfBefore, 527, 2, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues2OffsetCase4-cpp-xx : LTC-00528-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase4-cpp-xx */
    mvInsCase ( insertAllOfBefore, 528, 2, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues3OffsetCase1-cpp-xx : LTC-00529-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase1-cpp-xx */
    mvInsCase ( insertAllOfBefore, 529, 2, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues3OffsetCase2-cpp-xx : LTC-00530-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase2-cpp-xx */
    mvInsCase ( insertAllOfBefore, 530, 2, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues3OffsetCase3-cpp-xx : LTC-00531-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase3-cpp-xx */
    mvInsCase ( insertAllOfBefore, 531, 2, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase2MultipleValues3OffsetCase4-cpp-xx : LTC-00532-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase4-cpp-xx */
    mvInsCase ( insertAllOfBefore, 532, 2, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues1OffsetCase1-cpp-xx : LTC-00533-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase1-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 533, 4, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues1OffsetCase2-cpp-xx : LTC-00534-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase2-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 534, 4, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues1OffsetCase3-cpp-xx : LTC-00535-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase3-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 535, 4, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues1OffsetCase4-cpp-xx : LTC-00536-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase4-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 536, 4, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues2OffsetCase1-cpp-xx : LTC-00537-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase1-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 537, 4, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues2OffsetCase2-cpp-xx : LTC-00538-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase2-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 538, 4, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues2OffsetCase3-cpp-xx : LTC-00539-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase3-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 539, 4, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues2OffsetCase4-cpp-xx : LTC-00540-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase4-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 540, 4, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues3OffsetCase1-cpp-xx : LTC-00541-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase1-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 541, 4, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues3OffsetCase2-cpp-xx : LTC-00542-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase2-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 542, 4, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues3OffsetCase3-cpp-xx : LTC-00543-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase3-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 543, 4, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfBeforeItCase4MultipleValues3OffsetCase4-cpp-xx : LTC-00544-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase4-cpp-xx */
    mvInsRevCase ( insertAllOfBefore, 544, 4, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues1OffsetCase1-cpp-xx : LTC-00545-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase1-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 545, 1, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues1OffsetCase2-cpp-xx : LTC-00546-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase2-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 546, 1, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues1OffsetCase3-cpp-xx : LTC-00547-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase3-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 547, 1, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues1OffsetCase4-cpp-xx : LTC-00548-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase4-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 548, 1, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues2OffsetCase1-cpp-xx : LTC-00549-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase1-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 549, 1, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues2OffsetCase2-cpp-xx : LTC-00550-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase2-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 550, 1, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues2OffsetCase3-cpp-xx : LTC-00551-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase3-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 551, 1, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues2OffsetCase4-cpp-xx : LTC-00552-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase4-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 552, 1, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues3OffsetCase1-cpp-xx : LTC-00553-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase1-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 553, 1, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues3OffsetCase2-cpp-xx : LTC-00554-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase2-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 554, 1, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues3OffsetCase3-cpp-xx : LTC-00555-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase3-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 555, 1, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase1MultipleValues3OffsetCase4-cpp-xx : LTC-00556-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase4-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 556, 1, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues1OffsetCase1-cpp-xx : LTC-00557-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase1-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 557, 3, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues1OffsetCase2-cpp-xx : LTC-00558-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase2-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 558, 3, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues1OffsetCase3-cpp-xx : LTC-00559-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase3-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 559, 3, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues1OffsetCase4-cpp-xx : LTC-00560-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase4-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 560, 3, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues2OffsetCase1-cpp-xx : LTC-00561-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase1-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 561, 3, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues2OffsetCase2-cpp-xx : LTC-00562-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase2-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 562, 3, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues2OffsetCase3-cpp-xx : LTC-00563-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase3-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 563, 3, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues2OffsetCase4-cpp-xx : LTC-00564-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase4-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 564, 3, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues3OffsetCase1-cpp-xx : LTC-00565-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase1-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 565, 3, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues3OffsetCase2-cpp-xx : LTC-00566-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase2-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 566, 3, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues3OffsetCase3-cpp-xx : LTC-00567-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase3-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 567, 3, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase3MultipleValues3OffsetCase4-cpp-xx : LTC-00568-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase4-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 568, 3, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues1OffsetCase1-cpp-xx : LTC-00569-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase1-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 569, 2, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues1OffsetCase2-cpp-xx : LTC-00570-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase2-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 570, 2, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues1OffsetCase3-cpp-xx : LTC-00571-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase3-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 571, 2, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues1OffsetCase4-cpp-xx : LTC-00572-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase4-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 572, 2, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues2OffsetCase1-cpp-xx : LTC-00573-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase1-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 573, 2, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues2OffsetCase2-cpp-xx : LTC-00574-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase2-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 574, 2, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues2OffsetCase3-cpp-xx : LTC-00575-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase3-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 575, 2, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues2OffsetCase4-cpp-xx : LTC-00576-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase4-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 576, 2, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues3OffsetCase1-cpp-xx : LTC-00577-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase1-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 577, 2, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues3OffsetCase2-cpp-xx : LTC-00578-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase2-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 578, 2, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues3OffsetCase3-cpp-xx : LTC-00579-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase3-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 579, 2, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase2MultipleValues3OffsetCase4-cpp-xx : LTC-00580-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase4-cpp-xx */
    mvaInsCase ( insertAllOfAfter, 580, 2, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues1OffsetCase1-cpp-xx : LTC-00581-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase1-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 581, 4, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues1OffsetCase2-cpp-xx : LTC-00582-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase2-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 582, 4, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues1OffsetCase3-cpp-xx : LTC-00583-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase3-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 583, 4, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues1OffsetCase4-cpp-xx : LTC-00584-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase4-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 584, 4, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues2OffsetCase1-cpp-xx : LTC-00585-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase1-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 585, 4, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues2OffsetCase2-cpp-xx : LTC-00586-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase2-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 586, 4, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues2OffsetCase3-cpp-xx : LTC-00587-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase3-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 587, 4, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues2OffsetCase4-cpp-xx : LTC-00588-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase4-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 588, 4, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues3OffsetCase1-cpp-xx : LTC-00589-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase1-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 589, 4, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues3OffsetCase2-cpp-xx : LTC-00590-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase2-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 590, 4, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues3OffsetCase3-cpp-xx : LTC-00591-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase3-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 591, 4, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllOfAfterItCase4MultipleValues3OffsetCase4-cpp-xx : LTC-00592-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase4-cpp-xx */
    mvaInsRevCase ( insertAllOfAfter, 592, 4, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase1PackOffsetCase1-cpp-xx : LTC-00593-IT-insertAllBeforeItCase1PackOffsetCase1-cpp-xx */
    mvpInsCase ( insertAllBefore, 593, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase1PackOffsetCase2-cpp-xx : LTC-00594-IT-insertAllBeforeItCase1PackOffsetCase2-cpp-xx */
    mvpInsCase ( insertAllBefore, 594, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase1PackOffsetCase3-cpp-xx : LTC-00595-IT-insertAllBeforeItCase1PackOffsetCase3-cpp-xx */
    mvpInsCase ( insertAllBefore, 595, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase1PackOffsetCase4-cpp-xx : LTC-00596-IT-insertAllBeforeItCase1PackOffsetCase4-cpp-xx */
    mvpInsCase ( insertAllBefore, 596, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase2PackOffsetCase1-cpp-xx : LTC-00597-IT-insertAllBeforeItCase1PackOffsetCase1-cpp-xx */
    mvpInsCase ( insertAllBefore, 597, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase2PackOffsetCase2-cpp-xx : LTC-00598-IT-insertAllBeforeItCase1PackOffsetCase2-cpp-xx */
    mvpInsCase ( insertAllBefore, 598, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase2PackOffsetCase3-cpp-xx : LTC-00599-IT-insertAllBeforeItCase1PackOffsetCase3-cpp-xx */
    mvpInsCase ( insertAllBefore, 599, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase2PackOffsetCase4-cpp-xx : LTC-00600-IT-insertAllBeforeItCase1PackOffsetCase4-cpp-xx */
    mvpInsCase ( insertAllBefore, 600, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase3PackOffsetCase1-cpp-xx : LTC-00601-IT-insertAllBeforeItCase1PackOffsetCase1-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 601, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase3PackOffsetCase2-cpp-xx : LTC-00602-IT-insertAllBeforeItCase1PackOffsetCase2-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 602, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase3PackOffsetCase3-cpp-xx : LTC-00603-IT-insertAllBeforeItCase1PackOffsetCase3-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 603, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase3PackOffsetCase4-cpp-xx : LTC-00604-IT-insertAllBeforeItCase1PackOffsetCase4-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 604, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase4PackOffsetCase1-cpp-xx : LTC-00605-IT-insertAllBeforeItCase1PackOffsetCase1-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 605, 4, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase4PackOffsetCase2-cpp-xx : LTC-00606-IT-insertAllBeforeItCase1PackOffsetCase2-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 606, 4, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase4PackOffsetCase3-cpp-xx : LTC-00607-IT-insertAllBeforeItCase1PackOffsetCase3-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 607, 4, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllBeforeItCase4PackOffsetCase4-cpp-xx : LTC-00608-IT-insertAllBeforeItCase1PackOffsetCase4-cpp-xx */
    mvpInsRevCase ( insertAllBefore, 608, 4, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase1PackOffsetCase1-cpp-xx : LTC-00609-IT-insertAllAfterItCase1PackOffsetCase1-cpp-xx */
    mvpaInsCase ( insertAllAfter, 609, 1, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase1PackOffsetCase2-cpp-xx : LTC-00610-IT-insertAllAfterItCase1PackOffsetCase2-cpp-xx */
    mvpaInsCase ( insertAllAfter, 610, 1, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase1PackOffsetCase3-cpp-xx : LTC-00611-IT-insertAllAfterItCase1PackOffsetCase3-cpp-xx */
    mvpaInsCase ( insertAllAfter, 611, 1, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase1PackOffsetCase4-cpp-xx : LTC-00612-IT-insertAllAfterItCase1PackOffsetCase4-cpp-xx */
    mvpaInsCase ( insertAllAfter, 612, 1, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase2PackOffsetCase1-cpp-xx : LTC-00613-IT-insertAllAfterItCase1PackOffsetCase1-cpp-xx */
    mvpaInsCase ( insertAllAfter, 613, 2, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase2PackOffsetCase2-cpp-xx : LTC-00614-IT-insertAllAfterItCase1PackOffsetCase2-cpp-xx */
    mvpaInsCase ( insertAllAfter, 614, 2, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase2PackOffsetCase3-cpp-xx : LTC-00615-IT-insertAllAfterItCase1PackOffsetCase3-cpp-xx */
    mvpaInsCase ( insertAllAfter, 615, 2, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase2PackOffsetCase4-cpp-xx : LTC-00616-IT-insertAllAfterItCase1PackOffsetCase4-cpp-xx */
    mvpaInsCase ( insertAllAfter, 616, 2, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase3PackOffsetCase1-cpp-xx : LTC-00617-IT-insertAllAfterItCase1PackOffsetCase1-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 617, 3, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase3PackOffsetCase2-cpp-xx : LTC-00618-IT-insertAllAfterItCase1PackOffsetCase2-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 618, 3, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase3PackOffsetCase3-cpp-xx : LTC-00619-IT-insertAllAfterItCase1PackOffsetCase3-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 619, 3, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase3PackOffsetCase4-cpp-xx : LTC-00620-IT-insertAllAfterItCase1PackOffsetCase4-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 620, 3, 4, false )

    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase4PackOffsetCase1-cpp-xx : LTC-00621-IT-insertAllAfterItCase1PackOffsetCase1-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 621, 4, 1, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase4PackOffsetCase2-cpp-xx : LTC-00622-IT-insertAllAfterItCase1PackOffsetCase2-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 622, 4, 2, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase4PackOffsetCase3-cpp-xx : LTC-00623-IT-insertAllAfterItCase1PackOffsetCase3-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 623, 4, 3, true )
    /* ListTestGroup-BoundaryInsertion-insertAllAfterItCase4PackOffsetCase4-cpp-xx : LTC-00624-IT-insertAllAfterItCase1PackOffsetCase4-cpp-xx */
    mvpaInsRevCase ( insertAllAfter, 624, 4, 4, false )


#undef resetData
#undef __b1
#undef __b2
#undef __b3
#undef __b4
#undef __e1
#undef __e2
#undef __e3
#undef __e4
#undef __b
#undef __e
#undef b
#undef e
#undef sInsCase
#undef sInsRevCase
#undef saInsRevCase
#undef saInsCase
#undef mvInsCase
#undef mvInsRevCase
#undef mvaInsCase
#undef mvaInsRevCase
#undef mvpInsCase
#undef mvpInsRevCase
#undef mvpaInsCase
#undef mvpaInsRevCase

    return true;
}


/* ListTestSuite-cpp-xx : LTS-00001-cpp-xx */
auto ListTest :: execute () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "ListTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : LTG-00100-MF-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < Array, int > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });
    this->executeSubtest ( "ListTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : LTG-00100-MF-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < LinkedList, int > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });
    this->executeSubtest ( "ListTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : LTG-00100-MF-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < Array, String > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });
    this->executeSubtest ( "ListTestGroup-MemberFunctions-" __CDS_cpplang_core_version_name " : LTG-00100-MF-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {
        allOk = allOk && listTestGroupMemberFunctions < LinkedList, String > (
                this,
                { 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 },
                { 4, 1, 5, 2 },
                "[ 5, 7, 9, 1, 4, 6, 3, 10, 6, 7, 1, 4, 9, 3, 0, -5, 1, 4, 3, 56, 1, 23, 0, 6, 8, 20 ]",
                5, 7, 9,
                20, 8, 6
        );
    });


    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-" __CDS_cpplang_core_version_name " : LTG-00200-IT-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {
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
    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-" __CDS_cpplang_core_version_name " : LTG-00200-IT-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {
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
    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-" __CDS_cpplang_core_version_name " : LTG-00200-IT-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {
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
    this->executeSubtest ( "ListTestGroup-DelegateBidirectionalIterableClientImports-" __CDS_cpplang_core_version_name " : LTG-00200-IT-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {
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


    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                Array,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                LinkedList,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                Array,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );

        /* ListTestGroup-BoundaryInsertion-emplaceFront-cpp-xx : LTC-00323-IT-emplaceFront-cpp-xx */
        Array < String > t;
        List < String > & lref = t;

        lref.emplaceFront ( 5, 'c' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc"} ) ) {
            this->logError("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' OK");

        /* ListTestGroup-BoundaryInsertion-emplaceBack-cpp-xx : LTC-00324-IT-emplaceBack-cpp-xx */

        lref.emplaceBack ( 6, 'd' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc", "dddddd"} ) ) {
            this->logError("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' OK");
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                LinkedList,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );

        /* ListTestGroup-BoundaryInsertion-emplaceFront-cpp-xx : LTC-00323-IT-emplaceFront-cpp-xx */
        LinkedList < String > t;
        List < String > & lref = t;

        lref.emplaceFront ( 5, 'c' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc"} ) ) {
            this->logError("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' OK");

        /* ListTestGroup-BoundaryInsertion-emplaceBack-cpp-xx : LTC-00324-IT-emplaceBack-cpp-xx */

        lref.emplaceBack ( 6, 'd' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc", "dddddd"} ) ) {
            this->logError("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' OK");
    });


    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                Array,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < int > :: begin,
                & List < int > :: end,
                & List < int > :: cbegin,
                & List < int > :: cend,
                & List < int > :: rbegin,
                & List < int > :: rend,
                & List < int > :: crbegin,
                & List < int > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });
    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                LinkedList,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < int > :: begin,
                & List < int > :: end,
                & List < int > :: cbegin,
                & List < int > :: cend,
                & List < int > :: rbegin,
                & List < int > :: rend,
                & List < int > :: crbegin,
                & List < int > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });
    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                Array,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < String > :: begin,
                & List < String > :: end,
                & List < String > :: cbegin,
                & List < String > :: cend,
                & List < String > :: rbegin,
                & List < String > :: rend,
                & List < String > :: crbegin,
                & List < String > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });
    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                LinkedList,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < String > :: begin,
                & List < String > :: end,
                & List < String > :: cbegin,
                & List < String > :: cend,
                & List < String > :: rbegin,
                & List < String > :: rend,
                & List < String > :: crbegin,
                & List < String > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });

    return allOk;
}
