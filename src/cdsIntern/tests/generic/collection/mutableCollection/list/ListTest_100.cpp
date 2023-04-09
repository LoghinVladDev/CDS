#include "ListTest_common.hpp"

namespace {

    template < typename I, typename C >
    auto sortCheck ( I const & iterable, C const & comparator ) -> bool {

        auto const size = iterable.size();
        for ( int i = 0; (i + 1) < size; ++ i ) {
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
}

auto ListTest::tests_00100_00199 () noexcept -> bool {

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

    return allOk;
}
