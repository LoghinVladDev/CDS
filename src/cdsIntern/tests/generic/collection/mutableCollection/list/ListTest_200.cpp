#include "ListTest_common.hpp"

namespace {
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
}

auto ListTest::tests_00200_00299 () noexcept -> bool {

    bool allOk = true;

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

    return allOk;
}
