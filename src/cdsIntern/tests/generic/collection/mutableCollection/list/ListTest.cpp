/*
 * Created by loghin on 18/09/22.
 */

#include "ListTest.h"

#include <CDS/Array>
#include <CDS/LinkedList>

#include <initializer_list>
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


namespace relIns {

    enum TFlags {
        TNoMask         = 0x0000FFFFU,
        ItCase1         = 0x00010000U,
        ItCase2         = 0x00020000U,
        ItCase3         = 0x00040000U,
        ItCase4         = 0x00080000U,
        ItCaseMask      = 0x000F0000U,
        ValueCase1      = 0x00100000U,
        ValueCase2      = 0x00200000U,
        ValueCase3      = 0x00400000U,
        ValueCase4      = 0x00800000U,
        ValueCaseMask   = 0x00F00000U,
        OffsetCase1     = 0x01000000U,
        OffsetCase2     = 0x02000000U,
        OffsetCase3     = 0x04000000U,
        OffsetCase4     = 0x08000000U,
        OffsetCaseMask  = 0x0F000000U
    };

    struct TData {
        cds::uint32 tNo;
        cds::uint32 itCaseNo;
        cds::uint32 valueCaseNo;
        cds::uint32 offsetCaseNo;
    };

    inline auto tFlagsToTData (cds::uint32 flags) noexcept -> TData {

        TData data;
        data.tNo = flags & TFlags::TNoMask;

        switch (flags & TFlags::ItCaseMask) {
            case TFlags::ItCase1: {
                data.itCaseNo = 1;
                break;
            }
            case TFlags::ItCase2: {
                data.itCaseNo = 2;
                break;
            }
            case TFlags::ItCase3: {
                data.itCaseNo = 3;
                break;
            }
            case TFlags::ItCase4: {
                data.itCaseNo = 4;
                break;
            }
            default: {
                return {};
            }
        }

        switch (flags & TFlags::ValueCaseMask) {
            case TFlags::ValueCase1: {
                data.valueCaseNo = 1;
                break;
            }
            case TFlags::ValueCase2: {
                data.valueCaseNo = 2;
                break;
            }
            case TFlags::ValueCase3: {
                data.valueCaseNo = 3;
                break;
            }
            case TFlags::ValueCase4: {
                data.valueCaseNo = 4;
                break;
            }
            default: {
                return {};
            }
        }

        switch (flags & TFlags::OffsetCaseMask) {
            case TFlags::OffsetCase1: {
                data.offsetCaseNo = 1;
                break;
            }
            case TFlags::OffsetCase2: {
                data.offsetCaseNo = 2;
                break;
            }
            case TFlags::OffsetCase3: {
                data.offsetCaseNo = 3;
                break;
            }
            case TFlags::OffsetCase4: {
                data.offsetCaseNo = 4;
                break;
            }

            default: {
                return {};
            }
        }

        return data;
    }

    template <typename E> using BeginPfn = 
            typename List<E> :: Iterator (List <E> :: *) ();

    template <typename E> using RBeginPfn = 
            typename List<E> :: ReverseIterator (List <E> :: *) ();

    template <typename E> using CBeginPfn = 
            typename List<E> :: ConstIterator (List <E> :: *) () const;

    template <typename E> using CRBeginPfn = 
            typename List<E> :: ConstReverseIterator (List <E> :: *) () const;

    template <typename, bool, typename = void> struct ItCaseDet {};

    template <typename E> struct ItCaseDet <BeginPfn<E>, false> {
        constexpr static TFlags const itCase = ItCase1;
    };
    
    template <typename E> struct ItCaseDet <RBeginPfn<E>, true> {
        constexpr static TFlags const itCase = ItCase3;
    };
    
    template <typename E> struct ItCaseDet <CBeginPfn<E>, false> {
        constexpr static TFlags const itCase = ItCase2;
    };
    
    template <typename E> struct ItCaseDet <CRBeginPfn<E>, true> {
        constexpr static TFlags const itCase = ItCase4;
    };
    

    template <
            typename E,
            template <typename ...> class C,
            typename F,
            typename R
    > auto singleInsBefIt (
            cds::uint32 testData,
            C <E> underTest,
            Test const * pTestLib,
            F pfnBegin,
            cds::uint32 offset,
            E const & singleValue,
            bool opStatus,
            R const & opResult
    ) noexcept -> bool {

        auto const tData = tFlagsToTData(testData);
        List <E> & lRef = underTest;
        auto it = (lRef.*pfnBegin) ();
        for (int i = 0; i < offset; ++ i) {
            ++ it;
        }

        if (
                (opStatus != lRef.insertBefore (it, singleValue)) ||
                ! equals (lRef, opResult)
        ) {

            pTestLib->logError (
                "'LTC-%zu-"
                "insertBefore"
                "ItCase%zu"
                "SingleValue%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' failed",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return false;
        }
        

        pTestLib->logOK (
            "'LTC-%zu-"
            "insertBefore"
            "ItCase%zu"
            "SingleValue%zu"
            "OffsetCase%zu"
            "-" __CDS_cpplang_core_version_name "' OK",
            tData.tNo,
            tData.itCaseNo,
            tData.valueCaseNo,
            tData.offsetCaseNo
        );
        return true;
    }


    template <
            typename E,
            template <typename ...> class C,
            typename IGen, bool reversed
    > auto singleInsBefAll (
            cds::uint32 & tNo,
            std::initializer_list<E> const & initValues,
            Test const * pTestLib,
            IGen pfn,
            cds::Array <cds::Size> const & offsets,
            cds::Array <E> const & singleValues,
            cds::Array <cds::Array <bool>> const & statuses,
            cds::Array <cds::Array <cds::Array <E>>> const & results
    ) -> bool {

        bool result = true;
        cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
        cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

        for (cds::uint32 vIdx = 0; vIdx < singleValues.size(); ++ vIdx) {
            for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                result = result && singleInsBefIt <E, C, IGen> (
                        tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                        initValues, pTestLib, pfn,
                        offsets [offIdx], singleValues [vIdx],
                        statuses [vIdx] [offIdx],
                        results [vIdx] [offIdx]
                );

                tNo ++;
            }
        }

        return result;
    }
    

    template <
            typename E,
            template <typename ...> class C,
            typename F,
            typename R
    > auto singleInsAftIt (
            cds::uint32 testData,
            C <E> underTest,
            Test const * pTestLib,
            F pfnBegin,
            cds::uint32 offset,
            E const & singleValue,
            bool opStatus,
            R const & opResult
    ) noexcept -> bool {

        auto const tData = tFlagsToTData(testData);
        List <E> & lRef = underTest;
        auto it = (lRef.*pfnBegin) ();
        for (int i = 0; i < offset; ++ i) {
            ++ it;
        }

        if (
                (opStatus != lRef.insertAfter (it, singleValue)) ||
                ! equals (lRef, opResult)
        ) {

            pTestLib->logError (
                "'LTC-%zu-"
                "insertAfter"
                "ItCase%zu"
                "SingleValue%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' failed",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return false;
        }
        

        pTestLib->logOK (
            "'LTC-%zu-"
            "insertAfter"
            "ItCase%zu"
            "SingleValue%zu"
            "OffsetCase%zu"
            "-" __CDS_cpplang_core_version_name "' OK",
            tData.tNo,
            tData.itCaseNo,
            tData.valueCaseNo,
            tData.offsetCaseNo
        );
        return true;
    }


    template <
            typename E,
            template <typename ...> class C,
            typename IGen, bool reversed
    > auto singleInsAftAll (
            cds::uint32 & tNo,
            std::initializer_list<E> const & initValues,
            Test const * pTestLib,
            IGen pfn,
            cds::Array <cds::Size> const & offsets,
            cds::Array <E> const & singleValues,
            cds::Array <cds::Array <bool>> const & statuses,
            cds::Array <cds::Array <cds::Array <E>>> const & results
    ) -> bool {

        bool result = true;
        cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
        cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

        for (cds::uint32 vIdx = 0; vIdx < singleValues.size(); ++ vIdx) {
            for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                result = result && singleInsAftIt <E, C, IGen> (
                        tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                        initValues, pTestLib, pfn,
                        offsets [offIdx], singleValues [vIdx],
                        statuses [vIdx] [offIdx],
                        results [vIdx] [offIdx]
                );

                tNo ++;
            }
        }

        return result;
    }
    

    template <
            typename E,
            template <typename ...> class C,
            typename F,
            typename R
    > auto mulInsBefIt (
            cds::uint32 testData,
            C <E> underTest,
            Test const * pTestLib,
            F pfnBegin,
            cds::uint32 offset,
            cds::Array <E> const & mValues,
            bool opStatus,
            R const & opResult
    ) noexcept -> bool {

        auto const tData = tFlagsToTData(testData);
        List <E> & lRef = underTest;
        auto it = (lRef.*pfnBegin) ();
        for (int i = 0; i < offset; ++ i) {
            ++ it;
        }

        if (
                (opStatus != lRef.insertAllOfBefore (it, mValues)) ||
                ! equals (lRef, opResult)
        ) {

            pTestLib->logError (
                "'LTC-%zu-"
                "insertAllOfBefore"
                "ItCase%zu"
                "MultipleValues%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' failed",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return false;
        }
        

        pTestLib->logOK (
            "'LTC-%zu-"
            "insertAllOfBefore"
            "ItCase%zu"
            "MultipleValues%zu"
            "OffsetCase%zu"
            "-" __CDS_cpplang_core_version_name "' OK",
            tData.tNo,
            tData.itCaseNo,
            tData.valueCaseNo,
            tData.offsetCaseNo
        );
        return true;
    }


    template <
            typename E,
            template <typename ...> class C,
            typename IGen, bool reversed
    > auto mulInsBefAll (
            cds::uint32 & tNo,
            std::initializer_list<E> const & initValues,
            Test const * pTestLib,
            IGen pfn,
            cds::Array <cds::Size> const & offsets,
            cds::Array <cds::Array<E>> const & mValues,
            cds::Array <cds::Array <bool>> const & statuses,
            cds::Array <cds::Array <cds::Array <E>>> const & results
    ) -> bool {

        bool result = true;
        cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
        cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

        for (cds::uint32 vIdx = 0; vIdx < mValues.size(); ++ vIdx) {
            for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                result = result && mulInsBefIt <E, C, IGen> (
                        tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                        initValues, pTestLib, pfn,
                        offsets [offIdx], mValues [vIdx],
                        statuses [vIdx] [offIdx],
                        results [vIdx] [offIdx]
                );

                tNo ++;
            }
        }

        return result;
    }
    

    template <
            typename E,
            template <typename ...> class C,
            typename F,
            typename R
    > auto mulInsAftIt (
            cds::uint32 testData,
            C <E> underTest,
            Test const * pTestLib,
            F pfnBegin,
            cds::uint32 offset,
            cds::Array <E> const & mValues,
            bool opStatus,
            R const & opResult
    ) noexcept -> bool {

        auto const tData = tFlagsToTData(testData);
        List <E> & lRef = underTest;
        auto it = (lRef.*pfnBegin) ();
        for (int i = 0; i < offset; ++ i) {
            ++ it;
        }

        if (
                (opStatus != lRef.insertAllOfAfter (it, mValues)) ||
                ! equals (lRef, opResult)
        ) {

            pTestLib->logError (
                "'LTC-%zu-"
                "insertAllOfAfter"
                "ItCase%zu"
                "MultipleValues%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' failed",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return false;
        }
        

        pTestLib->logOK (
            "'LTC-%zu-"
            "insertAllOfAfter"
            "ItCase%zu"
            "MultipleValues%zu"
            "OffsetCase%zu"
            "-" __CDS_cpplang_core_version_name "' OK",
            tData.tNo,
            tData.itCaseNo,
            tData.valueCaseNo,
            tData.offsetCaseNo
        );
        return true;
    }


    template <
            typename E,
            template <typename ...> class C,
            typename IGen, bool reversed
    > auto mulInsAftAll (
            cds::uint32 & tNo,
            std::initializer_list<E> const & initValues,
            Test const * pTestLib,
            IGen pfn,
            cds::Array <cds::Size> const & offsets,
            cds::Array <cds::Array <E>> const & mValues,
            cds::Array <cds::Array <bool>> const & statuses,
            cds::Array <cds::Array <cds::Array <E>>> const & results
    ) -> bool {

        bool result = true;
        cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
        cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

        for (cds::uint32 vIdx = 0; vIdx < mValues.size(); ++ vIdx) {
            for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                result = result && mulInsAftIt <E, C, IGen> (
                        tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                        initValues, pTestLib, pfn,
                        offsets [offIdx], mValues [vIdx],
                        statuses [vIdx] [offIdx],
                        results [vIdx] [offIdx]
                );

                tNo ++;
            }
        }

        return result;
    }
    

    template <
            typename E,
            template <typename ...> class C,
            typename F,
            typename R,
            typename ... P
    > auto packInsBefIt (
            cds::uint32 testData,
            C <E> underTest,
            Test const * pTestLib,
            F pfnBegin,
            cds::uint32 offset,
            bool opStatus,
            R const & opResult,
            P && ... pack
    ) noexcept -> bool {

        auto const tData = tFlagsToTData(testData);
        List <E> & lRef = underTest;
        auto it = (lRef.*pfnBegin) ();
        for (int i = 0; i < offset; ++ i) {
            ++ it;
        }

        if (
                (opStatus != lRef.insertAllBefore (it, std::forward <P> (pack) ...)) ||
                ! equals (lRef, opResult)
        ) {

            pTestLib->logError (
                "'LTC-%zu-"
                "insertAllBefore"
                "ItCase%zu"
                "Pack%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' failed",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return false;
        }
        

        pTestLib->logOK (
            "'LTC-%zu-"
            "insertAllBefore"
            "ItCase%zu"
            "Pack%zu"
            "OffsetCase%zu"
            "-" __CDS_cpplang_core_version_name "' OK",
            tData.tNo,
            tData.itCaseNo,
            tData.valueCaseNo,
            tData.offsetCaseNo
        );
        return true;
    }


    template <
            typename E,
            template <typename ...> class C,
            typename IGen, bool reversed, typename ... P
    > auto packInsBefAll (
            cds::uint32 & tNo,
            std::initializer_list<E> const & initValues,
            Test const * pTestLib,
            IGen pfn,
            cds::Array <cds::Size> const & offsets,
            cds::Array <bool> const & statuses,
            cds::Array <cds::Array <E>> const & results,
            P const & ... pack
    ) -> bool {

        bool result = true;
        cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};

        for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
            result = result && packInsBefIt <E, C, IGen> (
                    tNo | ItCaseDet <IGen, reversed> :: itCase | ValueCase1 | offsetDatas [offIdx],
                    initValues, pTestLib, pfn,
                    offsets [offIdx], 
                    statuses [offIdx],
                    results [offIdx],
                    pack ...
            );

            tNo ++;
        }

        return result;
    }
    

    template <
            typename E,
            template <typename ...> class C,
            typename F,
            typename R,
            typename ... P
    > auto packInsAftIt (
            cds::uint32 testData,
            C <E> underTest,
            Test const * pTestLib,
            F pfnBegin,
            cds::uint32 offset,
            bool opStatus,
            R const & opResult,
            P && ... pack
    ) noexcept -> bool {

        auto const tData = tFlagsToTData(testData);
        List <E> & lRef = underTest;
        auto it = (lRef.*pfnBegin) ();
        for (int i = 0; i < offset; ++ i) {
            ++ it;
        }

        if (
                (opStatus != lRef.insertAllAfter (it, std::forward <P> (pack) ...)) ||
                ! equals (lRef, opResult)
        ) {

            pTestLib->logError (
                "'LTC-%zu-"
                "insertAllAfter"
                "ItCase%zu"
                "Pack%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' failed",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return false;
        }
        

        pTestLib->logOK (
            "'LTC-%zu-"
            "insertAllAfter"
            "ItCase%zu"
            "Pack%zu"
            "OffsetCase%zu"
            "-" __CDS_cpplang_core_version_name "' OK",
            tData.tNo,
            tData.itCaseNo,
            tData.valueCaseNo,
            tData.offsetCaseNo
        );
        return true;
    }


    template <
            typename E,
            template <typename ...> class C,
            typename IGen, bool reversed, typename ... P
    > auto packInsAftAll (
            cds::uint32 & tNo,
            std::initializer_list<E> const & initValues,
            Test const * pTestLib,
            IGen pfn,
            cds::Array <cds::Size> const & offsets,
            cds::Array <bool> const & statuses,
            cds::Array <cds::Array <E>> const & results,
            P const & ... pack
    ) -> bool {

        bool result = true;
        cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};

        for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
            result = result && packInsAftIt <E, C, IGen> (
                    tNo | ItCaseDet <IGen, reversed> :: itCase | ValueCase1 | offsetDatas [offIdx],
                    initValues, pTestLib, pfn,
                    offsets [offIdx], 
                    statuses [offIdx],
                    results [offIdx],
                    pack ...
            );

            tNo ++;
        }

        return result;
    }

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

    bool status = true;
    cds::uint32 tNo = 401U;
    
    status = relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resSingle1Case1, resSingle1Case2, resSingle1Case3, resSingle1Case4 },
                    { resSingle2Case1, resSingle2Case2, resSingle2Case3, resSingle2Case4 },
                    { resSingle3Case1, resSingle3Case2, resSingle3Case3, resSingle3Case4 }
            }
    );
    
    status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resSingle1RevCase1, resSingle1RevCase2, resSingle1RevCase3, resSingle1RevCase4 },
                    { resSingle2RevCase1, resSingle2RevCase2, resSingle2RevCase3, resSingle2RevCase4 },
                    { resSingle3RevCase1, resSingle3RevCase2, resSingle3RevCase3, resSingle3RevCase4 }
            }
    );
    
    status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resSingle1Case1, resSingle1Case2, resSingle1Case3, resSingle1Case4 },
                    { resSingle2Case1, resSingle2Case2, resSingle2Case3, resSingle2Case4 },
                    { resSingle3Case1, resSingle3Case2, resSingle3Case3, resSingle3Case4 }
            }
    );
    
    status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resSingle1RevCase1, resSingle1RevCase2, resSingle1RevCase3, resSingle1RevCase4 },
                    { resSingle2RevCase1, resSingle2RevCase2, resSingle2RevCase3, resSingle2RevCase4 },
                    { resSingle3RevCase1, resSingle3RevCase2, resSingle3RevCase3, resSingle3RevCase4 }
            }
    );
    
    status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresSingle1Case1, aresSingle1Case2, aresSingle1Case3, aresSingle1Case4 },
                    { aresSingle2Case1, aresSingle2Case2, aresSingle2Case3, aresSingle2Case4 },
                    { aresSingle3Case1, aresSingle3Case2, aresSingle3Case3, aresSingle3Case4 }
            }
    );
    
    status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresSingle1RevCase1, aresSingle1RevCase2, aresSingle1RevCase3, aresSingle1RevCase4 },
                    { aresSingle2RevCase1, aresSingle2RevCase2, aresSingle2RevCase3, aresSingle2RevCase4 },
                    { aresSingle3RevCase1, aresSingle3RevCase2, aresSingle3RevCase3, aresSingle3RevCase4 }
            }
    );
    
    status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresSingle1Case1, aresSingle1Case2, aresSingle1Case3, aresSingle1Case4 },
                    { aresSingle2Case1, aresSingle2Case2, aresSingle2Case3, aresSingle2Case4 },
                    { aresSingle3Case1, aresSingle3Case2, aresSingle3Case3, aresSingle3Case4 }
            }
    );
    
    status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { singleValue1, singleValue2, singleValue3 },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresSingle1RevCase1, aresSingle1RevCase2, aresSingle1RevCase3, aresSingle1RevCase4 },
                    { aresSingle2RevCase1, aresSingle2RevCase2, aresSingle2RevCase3, aresSingle2RevCase4 },
                    { aresSingle3RevCase1, aresSingle3RevCase2, aresSingle3RevCase3, aresSingle3RevCase4 }
            }
    );
    
    status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resMultiple1Case1, resMultiple1Case2, resMultiple1Case3, resMultiple1Case4 },
                    { resMultiple2Case1, resMultiple2Case2, resMultiple2Case3, resMultiple2Case4 },
                    { resMultiple3Case1, resMultiple3Case2, resMultiple3Case3, resMultiple3Case4 },
            }
    );
    
    status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resMultiple1RevCase1, resMultiple1RevCase2, resMultiple1RevCase3, resMultiple1RevCase4 },
                    { resMultiple2RevCase1, resMultiple2RevCase2, resMultiple2RevCase3, resMultiple2RevCase4 },
                    { resMultiple3RevCase1, resMultiple3RevCase2, resMultiple3RevCase3, resMultiple3RevCase4 },
            }
    );
    
    status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resMultiple1Case1, resMultiple1Case2, resMultiple1Case3, resMultiple1Case4 },
                    { resMultiple2Case1, resMultiple2Case2, resMultiple2Case3, resMultiple2Case4 },
                    { resMultiple3Case1, resMultiple3Case2, resMultiple3Case3, resMultiple3Case4 },
            }
    );
    
    status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { resMultiple1RevCase1, resMultiple1RevCase2, resMultiple1RevCase3, resMultiple1RevCase4 },
                    { resMultiple2RevCase1, resMultiple2RevCase2, resMultiple2RevCase3, resMultiple2RevCase4 },
                    { resMultiple3RevCase1, resMultiple3RevCase2, resMultiple3RevCase3, resMultiple3RevCase4 },
            }
    );
    
    status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresMultiple1Case1, aresMultiple1Case2, aresMultiple1Case3, aresMultiple1Case4 },
                    { aresMultiple2Case1, aresMultiple2Case2, aresMultiple2Case3, aresMultiple2Case4 },
                    { aresMultiple3Case1, aresMultiple3Case2, aresMultiple3Case3, aresMultiple3Case4 },
            }
    );
    
    status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresMultiple1RevCase1, aresMultiple1RevCase2, aresMultiple1RevCase3, aresMultiple1RevCase4 },
                    { aresMultiple2RevCase1, aresMultiple2RevCase2, aresMultiple2RevCase3, aresMultiple2RevCase4 },
                    { aresMultiple3RevCase1, aresMultiple3RevCase2, aresMultiple3RevCase3, aresMultiple3RevCase4 },
            }
    );
    
    status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresMultiple1Case1, aresMultiple1Case2, aresMultiple1Case3, aresMultiple1Case4 },
                    { aresMultiple2Case1, aresMultiple2Case2, aresMultiple2Case3, aresMultiple2Case4 },
                    { aresMultiple3Case1, aresMultiple3Case2, aresMultiple3Case3, aresMultiple3Case4 },
            }
    );
    
    status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            { {multipleValues1}, {multipleValues2}, {multipleValues3} },
            {
                    { true, true, true, false },
                    { true, true, true, false },
                    { true, true, true, false }
            }, {
                    { aresMultiple1RevCase1, aresMultiple1RevCase2, aresMultiple1RevCase3, aresMultiple1RevCase4 },
                    { aresMultiple2RevCase1, aresMultiple2RevCase2, aresMultiple2RevCase3, aresMultiple2RevCase4 },
                    { aresMultiple3RevCase1, aresMultiple3RevCase2, aresMultiple3RevCase3, aresMultiple3RevCase4 },
            }
    );
    
    status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {resMultipleVCase1, resMultipleVCase2, resMultipleVCase3, resMultipleVCase4},
            values ...
    );
    
    status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {resMultipleVRevCase1, resMultipleVRevCase2, resMultipleVRevCase3, resMultipleVRevCase4},
            values ...
    );
    
    status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {resMultipleVCase1, resMultipleVCase2, resMultipleVCase3, resMultipleVCase4},
            values ...
    );
    
    status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {resMultipleVRevCase1, resMultipleVRevCase2, resMultipleVRevCase3, resMultipleVRevCase4},
            values ...
    );
    
    status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {aresMultipleVCase1, aresMultipleVCase2, aresMultipleVCase3, aresMultipleVCase4},
            values ...
    );
    
    status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {aresMultipleVRevCase1, aresMultipleVRevCase2, aresMultipleVRevCase3, aresMultipleVRevCase4},
            values ...
    );
    
    status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {aresMultipleVCase1, aresMultipleVCase2, aresMultipleVCase3, aresMultipleVCase4},
            values ...
    );
    
    status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
            tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
            {case1Offset, case2Offset, case3Offset, case4Offset },
            {true, true, true, false}, 
            {aresMultipleVRevCase1, aresMultipleVRevCase2, aresMultipleVRevCase3, aresMultipleVRevCase4},
            values ...
    );

    return status;
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
