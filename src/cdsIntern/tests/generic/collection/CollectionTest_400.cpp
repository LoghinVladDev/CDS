#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

#include <CDS/Tuple>

namespace {
    using cds::Size;
    using cds::Collection;
    using cds::Tuple;
    using cds::makeTuple;

    template <typename I>
    using RS6 = Tuple <I, I, I, I, I, I>;

    template <typename I>
    using RS4 = Tuple <I, I, I, I>;

    template <typename I>
    using ResultSet = Tuple <Size, Size, RS6 <I>, RS4 <I>, RS4<I>, RS4 <I>>;

    /* CollectionTestGroup-RemoveBy-cpp-xx : CTG-00400-RB-cpp-xx. CTC-00401-RB to CTC-00418-RB */
    template <
            typename __Original,   /* NOLINT(bugprone-reserved-identifier) */
            typename __MemberType,                      /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingNonePredicateType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingOnePredicateType,        /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingMoreLTLPredicateType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingMorePredicateType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingMoreMTLPredicateType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __MatchingAllPredicateType         /* NOLINT(bugprone-reserved-identifier) */
    > auto collectionTestGroupRemoveBy (
            __Original const & original,
            Test                                  const * const pTestLib,
            Tuple <
                    __MatchingNonePredicateType,
                    __MatchingOnePredicateType,
                    __MatchingMoreLTLPredicateType,
                    __MatchingMorePredicateType,
                    __MatchingMoreMTLPredicateType,
                    __MatchingAllPredicateType
            >                                           const & predicates,
            ResultSet <__Original>       const & resultSet
    ) -> bool {


        auto const removeThatLimit = resultSet.template get <0> ();
        auto const removeThatResultWhenLessThanLimit = resultSet.template get <1> ();

        auto const & matchingNone = predicates.template get <0> ();
        auto const & matchingOne = predicates.template get <1> ();
        auto const & matchingMoreLessThanLimit = predicates.template get <2> ();
        auto const & matchingMore = predicates.template get <3> ();
        auto const & matchingMoreMoreThanLimit = predicates.template get <4> ();
        auto const & matchingAll = predicates.template get <5> ();

        Collection <__MemberType> const & equivAfterRemoveThatMatchesNone = resultSet.template get <2> ().template get <0> ();
        Collection <__MemberType> const & equivAfterRemoveThatMatchesOne = resultSet.template get <2> ().template get <1> ();
        Collection <__MemberType> const & equivAfterRemoveThatMatchesMoreLessThanLimit = resultSet.template get <2> ().template get <2> ();
        Collection <__MemberType> const & equivAfterRemoveThatMatchesMoreExact = resultSet.template get <2> ().template get <3> ();
        Collection <__MemberType> const & equivAfterRemoveThatMatchesMoreMoreThanLimit = resultSet.template get <2> ().template get <4> ();
        Collection <__MemberType> const & equivAfterRemoveThatMatchesAll = resultSet.template get <2> ().template get <5> ();

        Collection <__MemberType> const & equivAfterRemoveFirstThatMatchesNone = resultSet.template get <3> ().template get <0> ();
        Collection <__MemberType> const & equivAfterRemoveFirstThatMatchesOne = resultSet.template get <3> ().template get <1> ();
        Collection <__MemberType> const & equivAfterRemoveFirstThatMatchesMore = resultSet.template get <3> ().template get <2> ();
        Collection <__MemberType> const & equivAfterRemoveFirstThatMatchesAll = resultSet.template get <3> ().template get <3> ();

        Collection <__MemberType> const & equivAfterRemoveLastThatMatchesNone = resultSet.template get <4> ().template get <0> ();
        Collection <__MemberType> const & equivAfterRemoveLastThatMatchesOne = resultSet.template get <4> ().template get <1> ();
        Collection <__MemberType> const & equivAfterRemoveLastThatMatchesMore = resultSet.template get <4> ().template get <2> ();
        Collection <__MemberType> const & equivAfterRemoveLastThatMatchesAll = resultSet.template get <4> ().template get <3> ();

        Collection <__MemberType> const & equivAfterRemoveAllThatMatchesNone = resultSet.template get <5> ().template get <0> ();
        Collection <__MemberType> const & equivAfterRemoveAllThatMatchesOne = resultSet.template get <5> ().template get <1> ();
        Collection <__MemberType> const & equivAfterRemoveAllThatMatchesMore = resultSet.template get <5> ().template get <2> ();
        Collection <__MemberType> const & equivAfterRemoveAllThatMatchesAll = resultSet.template get <5> ().template get <3> ();

        pTestLib->log ( "Object Under Test : %s", original.toString().cStr() );

        /* CollectionTestCase-RemoveBy-removeThatMatchesNone-cpp-xx : CTC-00401-RB-removeThatMatchesNone-cpp-xx */
        auto       copyRB401            = original;
        cds :: Collection < __MemberType > & collectionRB401 = copyRB401;
        auto       removedCountRB401    = collectionRB401.removeThat ( removeThatLimit, matchingNone );
        auto const expectedRemovedCountRB401 = 0;
        pTestLib->log ( "object after 'removeThat with none matching' : '%s'. expected : '%s'", collectionRB401.toString().cStr(), equivAfterRemoveThatMatchesNone.toString().cStr() );
        if ( ( removedCountRB401 != expectedRemovedCountRB401 ) || ( ! collectionRB401.equals ( equivAfterRemoveThatMatchesNone ) ) ) {
            pTestLib->logError( "'CTC-00401-RB-removeThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00401-RB-removeThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesOne-cpp-xx : CTC-00402-RB-removeThatMatchesOne-cpp-xx */
        auto       copyRB402            = original;
        cds :: Collection < __MemberType > & collectionRB402 = copyRB402;
        auto       removedCountRB402    = collectionRB402.removeThat ( removeThatLimit, matchingOne );
        auto const expectedRemovedCountRB402 = 1;
        pTestLib->log ( "object after 'removeThat with one matching' : '%s'. expected : '%s'", collectionRB402.toString().cStr(), equivAfterRemoveThatMatchesOne.toString().cStr() );
        if ( ( removedCountRB402 != expectedRemovedCountRB402 ) || ( ! collectionRB402.equals ( equivAfterRemoveThatMatchesOne ) ) ) {
            pTestLib->logError( "'CTC-00402-RB-removeThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00402-RB-removeThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesMoreLessThanLimit-cpp-xx : CTC-00403-RB-removeThatMatchesMoreLessThanLimit-cpp-xx */
        auto       copyRB403            = original;
        cds :: Collection < __MemberType > & collectionRB403 = copyRB403;
        auto       removedCountRB403    = collectionRB403.removeThat ( removeThatLimit, matchingMoreLessThanLimit );
        auto const expectedRemovedCountRB403 = removeThatResultWhenLessThanLimit;
        pTestLib->log ( "object after 'removeThat with more matching, less than limit' : '%s'. expected : '%s'", collectionRB403.toString().cStr(), equivAfterRemoveThatMatchesMoreLessThanLimit.toString().cStr() );
        if ( ( removedCountRB403 != expectedRemovedCountRB403 ) || ( ! collectionRB403.equals ( equivAfterRemoveThatMatchesMoreLessThanLimit ) ) ) {
            pTestLib->logError( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00403-RB-removeThatMatchesMoreLessThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesMoreExact-cpp-xx : CTC-00404-RB-removeThatMatchesMoreExact-cpp-xx */
        auto       copyRB404            = original;
        cds :: Collection < __MemberType > & collectionRB404 = copyRB404;
        auto       removedCountRB404    = collectionRB404.removeThat ( removeThatLimit, matchingMore );
        auto const expectedRemovedCountRB404 = removeThatLimit;
        pTestLib->log ( "object after 'removeThat with more matching, exact' : '%s'. expected : '%s'", collectionRB404.toString().cStr(), equivAfterRemoveThatMatchesMoreExact.toString().cStr() );
        if ( ( removedCountRB404 != expectedRemovedCountRB404 ) || ( ! collectionRB404.equals ( equivAfterRemoveThatMatchesMoreExact ) ) ) {
            pTestLib->logError( "'CTC-00404-RB-removeThatMatchesMoreExact-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00404-RB-removeThatMatchesMoreExact-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesMoreMoreThanLimit-cpp-xx : CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-cpp-xx */
        auto       copyRB405            = original;
        cds :: Collection < __MemberType > & collectionRB405 = copyRB405;
        auto       removedCountRB405    = collectionRB405.removeThat ( removeThatLimit, matchingMoreMoreThanLimit );
        auto const expectedRemovedCountRB405 = removeThatLimit;
        pTestLib->log ( "object after 'removeThat with more matching' : '%s'. expected : '%s'", collectionRB405.toString().cStr(), equivAfterRemoveThatMatchesMoreMoreThanLimit.toString().cStr() );
        if ( ( removedCountRB405 != expectedRemovedCountRB405 ) || ( ! collectionRB405.equals ( equivAfterRemoveThatMatchesMoreMoreThanLimit ) ) ) {
            pTestLib->logError( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00405-RB-removeThatMatchesMoreMoreThanLimit-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeThatMatchesAll-cpp-xx : CTC-00406-RB-removeThatMatchesAll-cpp-xx */
        auto       copyRB406            = original;
        cds :: Collection < __MemberType > & collectionRB406 = copyRB406;
        auto       removedCountRB406    = collectionRB406.removeThat ( removeThatLimit, matchingAll );
        auto const expectedRemovedCountRB406 = removeThatLimit;
        pTestLib->log ( "object after 'removeThat with all matching, less than limit' : '%s'. expected : '%s'", collectionRB406.toString().cStr(), equivAfterRemoveThatMatchesAll.toString().cStr() );
        if ( ( removedCountRB406 != expectedRemovedCountRB406 ) || ( ! collectionRB406.equals ( equivAfterRemoveThatMatchesAll ) ) ) {
            pTestLib->logError( "'CTC-00406-RB-removeThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00406-RB-removeThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesNone-cpp-xx : CTC-00407-RB-removeFirstThatMatchesNone-cpp-xx */
        auto       copyRB407            = original;
        cds :: Collection < __MemberType > & collectionRB407 = copyRB407;
        auto       removedCountRB407    = collectionRB407.removeFirstThat ( matchingNone );
        auto const expectedRemovedCountRB407 = false;
        pTestLib->log ( "object after 'removeFirstThat with no matches' : '%s'. expected : '%s'", collectionRB407.toString().cStr(), equivAfterRemoveFirstThatMatchesNone.toString().cStr() );
        if ( ( removedCountRB407 != expectedRemovedCountRB407 ) || ( ! collectionRB407.equals ( equivAfterRemoveFirstThatMatchesNone ) ) ) {
            pTestLib->logError( "'CTC-00407-RB-removeFirstThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00407-RB-removeFirstThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesOne-cpp-xx : CTC-00408-RB-removeFirstThatMatchesOne-cpp-xx */
        auto       copyRB408            = original;
        cds :: Collection < __MemberType > & collectionRB408 = copyRB408;
        auto       removedCountRB408    = collectionRB408.removeFirstThat ( matchingOne );
        auto const expectedRemovedCountRB408 = true;
        pTestLib->log ( "object after 'removeFirstThat with one match' : '%s'. expected : '%s'", collectionRB408.toString().cStr(), equivAfterRemoveFirstThatMatchesOne.toString().cStr() );
        if ( ( removedCountRB408 != expectedRemovedCountRB408 ) || ( ! collectionRB408.equals ( equivAfterRemoveFirstThatMatchesOne ) ) ) {
            pTestLib->logError( "'CTC-00408-RB-removeFirstThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00408-RB-removeFirstThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesMore-cpp-xx : CTC-00409-RB-removeFirstThatMatchesMore-cpp-xx */
        auto       copyRB409            = original;
        cds :: Collection < __MemberType > & collectionRB409 = copyRB409;
        auto       removedCountRB409    = collectionRB409.removeFirstThat ( matchingMore );
        auto const expectedRemovedCountRB409 = true;
        pTestLib->log ( "object after 'removeFirstThat with one or more matches' : '%s'. expected : '%s'", collectionRB409.toString().cStr(), equivAfterRemoveFirstThatMatchesMore.toString().cStr() );
        if ( ( removedCountRB409 != expectedRemovedCountRB409 ) || ( ! collectionRB409.equals ( equivAfterRemoveFirstThatMatchesMore ) ) ) {
            pTestLib->logError( "'CTC-00409-RB-removeFirstThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00409-RB-removeFirstThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeFirstThatMatchesAll-cpp-xx : CTC-00410-RB-removeFirstThatMatchesAll-cpp-xx */
        auto       copyRB410            = original;
        cds :: Collection < __MemberType > & collectionRB410 = copyRB410;
        auto       removedCountRB410    = collectionRB410.removeFirstThat ( matchingAll );
        auto const expectedRemovedCountRB410 = true;
        pTestLib->log ( "object after 'removeFirstThat matches all' : '%s'. expected : '%s'", collectionRB410.toString().cStr(), equivAfterRemoveFirstThatMatchesAll.toString().cStr() );
        if ( ( removedCountRB410 != expectedRemovedCountRB410 ) || ( ! collectionRB410.equals ( equivAfterRemoveFirstThatMatchesAll ) ) ) {
            pTestLib->logError( "'CTC-00410-RB-removeFirstThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00410-RB-removeFirstThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesNone-cpp-xx : CTC-00411-RB-removeLastThatMatchesNone-cpp-xx */
        auto       copyRB411            = original;
        cds :: Collection < __MemberType > & collectionRB411 = copyRB411;
        auto       removedCountRB411    = collectionRB411.removeLastThat ( matchingNone );
        auto const expectedRemovedCountRB411 = false;
        pTestLib->log ( "object after 'removeLastThat with no matches' : '%s'. expected : '%s'", collectionRB411.toString().cStr(), equivAfterRemoveLastThatMatchesNone.toString().cStr() );
        if ( ( removedCountRB411 != expectedRemovedCountRB411 ) || ( ! collectionRB411.equals ( equivAfterRemoveLastThatMatchesNone ) ) ) {
            pTestLib->logError( "'CTC-00411-RB-removeLastThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00411-RB-removeLastThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesOne-cpp-xx : CTC-00412-RB-removeLastThatMatchesOne-cpp-xx */
        auto       copyRB412            = original;
        cds :: Collection < __MemberType > & collectionRB412 = copyRB412;
        auto       removedCountRB412    = collectionRB412.removeLastThat ( matchingOne );
        auto const expectedRemovedCountRB412 = true;
        pTestLib->log ( "object after 'removeLastThat with one match' : '%s'. expected : '%s'", collectionRB412.toString().cStr(), equivAfterRemoveLastThatMatchesOne.toString().cStr() );
        if ( ( removedCountRB412 != expectedRemovedCountRB412 ) || ( ! collectionRB412.equals ( equivAfterRemoveLastThatMatchesOne ) ) ) {
            pTestLib->logError( "'CTC-00412-RB-removeLastThatMatchesOne-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00412-RB-removeLastThatMatchesOne-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesMore-cpp-xx : CTC-00413-RB-removeLastThatMatchesMore-cpp-xx */
        auto       copyRB413            = original;
        cds :: Collection < __MemberType > & collectionRB413 = copyRB413;
        auto       removedCountRB413    = collectionRB413.removeLastThat ( matchingMore );
        auto const expectedRemovedCountRB413 = true;
        pTestLib->log ( "object after 'removeLastThat with one or more matches' : '%s'. expected : '%s'", collectionRB413.toString().cStr(), equivAfterRemoveLastThatMatchesMore.toString().cStr() );
        if ( ( removedCountRB413 != expectedRemovedCountRB413 ) || ( ! collectionRB413.equals ( equivAfterRemoveLastThatMatchesMore ) ) ) {
            pTestLib->logError( "'CTC-00413-RB-removeLastThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00413-RB-removeLastThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeLastThatMatchesAll-cpp-xx : CTC-00414-RB-removeLastThatMatchesAll-cpp-xx */
        auto       copyRB414            = original;
        cds :: Collection < __MemberType > & collectionRB414 = copyRB414;
        auto       removedCountRB414    = collectionRB414.removeLastThat ( matchingAll );
        auto const expectedRemovedCountRB414 = true;
        pTestLib->log ( "object after 'removeLastThat matching all' : '%s'. expected : '%s'", collectionRB414.toString().cStr(), equivAfterRemoveLastThatMatchesAll.toString().cStr() );
        if ( ( removedCountRB414 != expectedRemovedCountRB414 ) || ( ! collectionRB414.equals ( equivAfterRemoveLastThatMatchesAll ) ) ) {
            pTestLib->logError( "'CTC-00414-RB-removeLastThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00414-RB-removeLastThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesNone-cpp-xx : CTC-00415-RB-removeAllThatMatchesNone-cpp-xx */
        auto       copyRB415            = original;
        cds :: Collection < __MemberType > & collectionRB415 = copyRB415;
        auto const expectedRemovedCountRB415 = collectionRB415.count ( matchingNone );
        auto       removedCountRB415    = collectionRB415.removeAllThat ( matchingNone );
        pTestLib->log ( "object after 'removeAllThat match none' : '%s'. expected : '%s'", collectionRB415.toString().cStr(), equivAfterRemoveAllThatMatchesNone.toString().cStr() );
        if ( ( removedCountRB415 != expectedRemovedCountRB415 ) || ( ! collectionRB415.equals ( equivAfterRemoveAllThatMatchesNone ) ) ) {
            pTestLib->logError( "'CTC-00415-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00415-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesOne-cpp-xx : CTC-00416-RB-removeAllThatMatchesOne-cpp-xx */
        auto       copyRB416            = original;
        cds :: Collection < __MemberType > & collectionRB416 = copyRB416;
        auto const expectedRemovedCountRB416 = collectionRB416.count ( matchingOne );
        auto       removedCountRB416    = collectionRB416.removeAllThat ( matchingOne );
        pTestLib->log ( "object after 'removeAllThat matching one' : '%s'. expected : '%s'", collectionRB416.toString().cStr(), equivAfterRemoveAllThatMatchesOne.toString().cStr() );
        if ( ( removedCountRB416 != expectedRemovedCountRB416 ) || ( ! collectionRB416.equals ( equivAfterRemoveAllThatMatchesOne ) ) ) {
            pTestLib->logError( "'CTC-00416-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00416-RB-removeAllThatMatchesNone-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesMore-cpp-xx : CTC-00417-RB-removeAllThatMatchesMore-cpp-xx */
        auto       copyRB417            = original;
        cds :: Collection < __MemberType > & collectionRB417 = copyRB417;
        auto const expectedRemovedCountRB417 = collectionRB417.count ( matchingMore );
        auto       removedCountRB417    = collectionRB417.removeAllThat ( matchingMore );
        pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB417.toString().cStr(), equivAfterRemoveAllThatMatchesMore.toString().cStr() );
        if ( ( removedCountRB417 != expectedRemovedCountRB417 ) || ( ! collectionRB417.equals ( equivAfterRemoveAllThatMatchesMore ) ) ) {
            pTestLib->logError( "'CTC-00417-RB-removeAllThatMatchesMore-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00417-RB-removeAllThatMatchesMore-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-removeAllThatMatchesAll-cpp-xx : CTC-00418-RB-removeAllThatMatchesAll-cpp-xx */
        auto       copyRB418            = original;
        cds :: Collection < __MemberType > & collectionRB418 = copyRB418;
        auto const expectedRemovedCountRB418 = collectionRB418.count ( matchingAll );
        auto       removedCountRB418    = collectionRB418.removeAllThat ( matchingAll );
        pTestLib->log ( "object after 'removeAllThat matching one or more' : '%s'. expected : '%s'", collectionRB418.toString().cStr(), equivAfterRemoveAllThatMatchesAll.toString().cStr() );
        if ( ( removedCountRB418 != expectedRemovedCountRB418 ) || ( ! collectionRB418.equals ( equivAfterRemoveAllThatMatchesAll ) ) ) {
            pTestLib->logError( "'CTC-00418-RB-removeAllThatMatchesAll-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00418-RB-removeAllThatMatchesAll-" __CDS_cpplang_core_version_name "' OK" );
        }

        return true;
    }

    Size const rtLimit = 3U;
    Size const rlLessRes = 2U;


    auto const iPred = makeTuple (
            [](int const x) { return x > 100; },
            [](int const x) { return x == 3; },
            [](int const x) { return (x >= 4) && (x <= 5); },
            [](int const x) { return (x >= 4) && (x <= 6); },
            [](int const x) { return (x >= 4) && (x <= 7); },
            [](int const x) { return (x >= 1) && (x <= 9); }
    );


    std::initializer_list <int> const ir1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const ir2 = {1, 2, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const ir3 = {1, 2, 3, 6, 7, 8, 9};
    std::initializer_list <int> const ir4 = {1, 2, 3, 7, 8, 9};
    std::initializer_list <int> const ir5 = {1, 2, 3, 7, 8, 9};
    std::initializer_list <int> const ir6 = {4, 5, 6, 7, 8, 9};

    std::initializer_list <int> const irf1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const irf2 = {1, 2, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const irf3 = {1, 2, 3, 5, 6, 7, 8, 9};
    std::initializer_list <int> const irf4 = {2, 3, 4, 5, 6, 7, 8, 9};

    std::initializer_list <int> const irl1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const irl2 = {1, 2, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const irl3 = {1, 2, 3, 4, 5, 7, 8, 9};
    std::initializer_list <int> const irl4 = {1, 2, 3, 4, 5, 6, 7, 8};

    std::initializer_list <int> const ira1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const ira2 = {1, 2, 4, 5, 6, 7, 8, 9};
    std::initializer_list <int> const ira3 = {1, 2, 3, 7, 8, 9};
    std::initializer_list <int> const ira4 = {};


    auto const iiPred = makeTuple (
            [](MapEntry < int, int > const & x) { return x.key() > 100; },
            [](MapEntry < int, int > const & x) { return x.key() == 3; },
            [](MapEntry < int, int > const & x) { return (x.key() >= 4) && (x.key() <= 5); },
            [](MapEntry < int, int > const & x) { return (x.key() >= 4) && (x.key() <= 6); },
            [](MapEntry < int, int > const & x) { return (x.key() >= 4) && (x.key() <= 7); },
            [](MapEntry < int, int > const & x) { return (x.key() >= 1) && (x.key() <= 9); }
    );


    std::initializer_list <MapEntry <int, int>> const iir1 = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    std::initializer_list <MapEntry <int, int>> const iir2 = { {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list <MapEntry <int, int>> const iir3 = { {1, 1}, {2, 2}, {3, 3}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list <MapEntry <int, int>> const iir4 = { {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list <MapEntry <int, int>> const iir5 = { {1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list <MapEntry <int, int>> const iir6 = { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

    std::initializer_list <MapEntry <int, int>> const iirf1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    std::initializer_list <MapEntry <int, int>> const iirf2 = {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    std::initializer_list <MapEntry <int, int>> const iirf3 = {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    std::initializer_list <MapEntry <int, int>> const iirf4 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

    std::initializer_list <MapEntry <int, int>> const iirl1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    std::initializer_list <MapEntry <int, int>> const iirl2 = {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    std::initializer_list <MapEntry <int, int>> const iirl3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9}};
    std::initializer_list <MapEntry <int, int>> const iirl4 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};

    std::initializer_list <MapEntry <int, int>> const iira1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list <MapEntry <int, int>> const iira2 = {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list <MapEntry <int, int>> const iira3 = {{1, 1}, {2, 2}, {3, 3}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list <MapEntry <int, int>> const iira4 = {};


    auto const sPred = makeTuple (
            [](String const & x) { return x == "ddd"; },
            [](String const & x) { return x == "bbc"; },
            [](String const & x) { return x.startsWith ("bb") && (! x.endsWith ("a")); },
            [](String const & x) { return x.startsWith ("bb"); },
            [](String const & x) { return x.startsWith ("bb") || x.endsWith ("b"); },
            [](String const & x) { return ! x.empty(); }
    );


    std::initializer_list <String> const sr1 = {"aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sr2 = {"aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sr3 = {"aaa", "aab", "aac", "bba", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sr4 = {"aaa", "aab", "aac", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sr5 = {"aaa", "aac", "bbc", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sr6 = {"bba", "bbb", "bbc", "cca", "ccb", "ccc"};

    std::initializer_list <String> const srf1 = {"aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc"};
    std::initializer_list <String> const srf2 = {"aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc"};
    std::initializer_list <String> const srf3 = {"aaa", "aab", "aac", "bbb", "bbc", "cca", "ccb", "ccc"};
    std::initializer_list <String> const srf4 = {"aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc"};

    std::initializer_list <String> const srl1 = {"aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc"};
    std::initializer_list <String> const srl2 = {"aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc"};
    std::initializer_list <String> const srl3 = {"aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc"};
    std::initializer_list <String> const srl4 = {"aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb"};

    std::initializer_list <String> const sra1 = {"aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sra2 = {"aaa", "aab", "aac", "bba", "bbb", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sra3 = {"aaa", "aab", "aac", "cca", "ccb", "ccc"};
    std::initializer_list <String> const sra4 = {};


    std::initializer_list <String> const osr1 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca"};
    std::initializer_list <String> const osr2 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca"};
    std::initializer_list <String> const osr3 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "cca"};
    std::initializer_list <String> const osr4 = {"ccb", "ccc", "aaa", "aab", "aac", "cca"};
    std::initializer_list <String> const osr5 = {"ccc", "aaa", "aac", "bbb", "bbc", "cca"};
    std::initializer_list <String> const osr6 = {"aab", "aac", "bba", "bbb", "bbc", "cca"};

    std::initializer_list <String> const osrf1 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca"};
    std::initializer_list <String> const osrf2 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca"};
    std::initializer_list <String> const osrf3 = {"ccb", "ccc", "aaa", "aab", "aac", "bbb", "bbc", "cca"};
    std::initializer_list <String> const osrf4 = {"ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca"};

    std::initializer_list <String> const osrl1 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca"};
    std::initializer_list <String> const osrl2 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca"};
    std::initializer_list <String> const osrl3 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca"};
    std::initializer_list <String> const osrl4 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc"};

    std::initializer_list <String> const osra1 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca"};
    std::initializer_list <String> const osra2 = {"ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "cca"};
    std::initializer_list <String> const osra3 = {"ccb", "ccc", "aaa", "aab", "aac", "cca"};
    std::initializer_list <String> const osra4 = {};


    auto const ssPred = makeTuple (
            [](MapEntry < String, String > const & x) { return x.key() == "ddd"; },
            [](MapEntry < String, String > const & x) { return x.key() == "bbc"; },
            [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") && (! x.key().endsWith ("a")); },
            [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb"); },
            [](MapEntry < String, String > const & x) { return x.key().startsWith ("bb") || x.key().endsWith ("b"); },
            [](MapEntry < String, String > const & x) { return ! x.key().empty(); }
    );


    std::initializer_list <MapEntry <String, String>> const ssr1 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssr2 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssr3 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssr4 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssr5 = {{"aaa", "aaa"}, {"aac", "aac"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssr6 = {{"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };

    std::initializer_list <MapEntry <String, String>> const ssrf1 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssrf2 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssrf3 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssrf4 = {{"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };

    std::initializer_list <MapEntry <String, String>> const ssrl1 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssrl2 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssrl3 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssrl4 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"} };

    std::initializer_list <MapEntry <String, String>> const ssra1 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssra2 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssra3 = {{"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };
    std::initializer_list <MapEntry <String, String>> const ssra4 = {};


    std::initializer_list <MapEntry <String, String>> const ossr1 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossr2 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossr3 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossr4 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossr5 = { {"ccc", "ccc"}, {"aaa", "aaa"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossr6 = { {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };

    std::initializer_list <MapEntry <String, String>> const ossrf1 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossrf2 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossrf3 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossrf4 = { {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };

    std::initializer_list <MapEntry <String, String>> const ossrl1 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossrl2 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossrl3 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossrl4 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"} };

    std::initializer_list <MapEntry <String, String>> const ossra1 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossra2 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossra3 = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"cca", "cca"} };
    std::initializer_list <MapEntry <String, String>> const ossra4 = {};
} /* namespace */

auto CollectionTest::tests_00400_00449 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        using C = cds::Array <int>;
        C const originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupRemoveBy <C, int> (
                originalArray, this, iPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ir1, ir2, ir3, ir4, ir5, ir6),
                        makeTuple <C, C, C, C> (irf1, irf2, irf3, irf4),
                        makeTuple <C, C, C, C> (irl1, irl2, irl3, irl4),
                        makeTuple <C, C, C, C> (ira1, ira2, ira3, ira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        using C = cds::LinkedList <int>;
        C const originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupRemoveBy <C, int> (
                originalArray, this, iPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ir1, ir2, ir3, ir4, ir5, ir6),
                        makeTuple <C, C, C, C> (irf1, irf2, irf3, irf4),
                        makeTuple <C, C, C, C> (irl1, irl2, irl3, irl4),
                        makeTuple <C, C, C, C> (ira1, ira2, ira3, ira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntHashSet", [this, & allOk]{

        using C = cds::HashSet <int>;
        C const originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupRemoveBy <C, int> (
                originalArray, this, iPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ir1, ir2, ir3, ir4, ir5, ir6),
                        makeTuple <C, C, C, C> (irf1, irf2, irf3, irf4),
                        makeTuple <C, C, C, C> (irl1, irl2, irl3, irl4),
                        makeTuple <C, C, C, C> (ira1, ira2, ira3, ira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntTreeSet", [this, & allOk]{

        using C = cds::TreeSet <int>;
        C const originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupRemoveBy <C, int> (
                originalArray, this, iPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ir1, ir2, ir3, ir4, ir5, ir6),
                        makeTuple <C, C, C, C> (irf1, irf2, irf3, irf4),
                        makeTuple <C, C, C, C> (irl1, irl2, irl3, irl4),
                        makeTuple <C, C, C, C> (ira1, ira2, ira3, ira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [this, & allOk]{

        using C = cds::LinkedHashSet <int>;
        C const originalArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupRemoveBy <C, int> (
                originalArray, this, iPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ir1, ir2, ir3, ir4, ir5, ir6),
                        makeTuple <C, C, C, C> (irf1, irf2, irf3, irf4),
                        makeTuple <C, C, C, C> (irl1, irl2, irl3, irl4),
                        makeTuple <C, C, C, C> (ira1, ira2, ira3, ira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        using C = cds::HashMap <int, int>;
        C const originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupRemoveBy <C, MapEntry <int ,int>> (
                originalArray, this, iiPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (iir1, iir2, iir3, iir4, iir5, iir6),
                        makeTuple <C, C, C, C> (iirf1, iirf2, iirf3, iirf4),
                        makeTuple <C, C, C, C> (iirl1, iirl2, iirl3, iirl4),
                        makeTuple <C, C, C, C> (iira1, iira2, iira3, iira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, & allOk]{

        using C = cds::LinkedHashMap <int, int>;
        C const originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupRemoveBy <C, MapEntry <int ,int>> (
                originalArray, this, iiPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (iir1, iir2, iir3, iir4, iir5, iir6),
                        makeTuple <C, C, C, C> (iirf1, iirf2, iirf3, iirf4),
                        makeTuple <C, C, C, C> (iirl1, iirl2, iirl3, iirl4),
                        makeTuple <C, C, C, C> (iira1, iira2, iira3, iira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, & allOk]{

        using C = cds::TreeMap <int, int>;
        C const originalArray = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupRemoveBy <C, MapEntry <int ,int>> (
                originalArray, this, iiPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (iir1, iir2, iir3, iir4, iir5, iir6),
                        makeTuple <C, C, C, C> (iirf1, iirf2, iirf3, iirf4),
                        makeTuple <C, C, C, C> (iirl1, iirl2, iirl3, iirl4),
                        makeTuple <C, C, C, C> (iira1, iira2, iira3, iira4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        using C = cds::Array <String>;
        C const originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };

        allOk = allOk && collectionTestGroupRemoveBy <C, String> (
                originalArray, this, sPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (sr1, sr2, sr3, sr4, sr5, sr6),
                        makeTuple <C, C, C, C> (srf1, srf2, srf3, srf4),
                        makeTuple <C, C, C, C> (srl1, srl2, srl3, srl4),
                        makeTuple <C, C, C, C> (sra1, sra2, sra3, sra4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        using C = cds::LinkedList <String>;
        C const originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };

        allOk = allOk && collectionTestGroupRemoveBy <C, String> (
                originalArray, this, sPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (sr1, sr2, sr3, sr4, sr5, sr6),
                        makeTuple <C, C, C, C> (srf1, srf2, srf3, srf4),
                        makeTuple <C, C, C, C> (srl1, srl2, srl3, srl4),
                        makeTuple <C, C, C, C> (sra1, sra2, sra3, sra4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringHashSet", [this, & allOk]{

        using C = cds::HashSet <String>;
        C const originalArray = { "ccb", "ccc", "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca" };

        allOk = allOk && collectionTestGroupRemoveBy <C, String> (
                originalArray, this, sPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (osr1, osr2, osr3, osr4, osr5, osr6),
                        makeTuple <C, C, C, C> (osrf1, osrf2, osrf3, osrf4),
                        makeTuple <C, C, C, C> (osrl1, osrl2, osrl3, osrl4),
                        makeTuple <C, C, C, C> (osra1, osra2, osra3, osra4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringTreeSet", [this, & allOk]{

        using C = cds::TreeSet <String>;
        C const originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };

        allOk = allOk && collectionTestGroupRemoveBy <C, String> (
                originalArray, this, sPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (sr1, sr2, sr3, sr4, sr5, sr6),
                        makeTuple <C, C, C, C> (srf1, srf2, srf3, srf4),
                        makeTuple <C, C, C, C> (srl1, srl2, srl3, srl4),
                        makeTuple <C, C, C, C> (sra1, sra2, sra3, sra4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [this, & allOk]{

        using C = cds::LinkedHashSet <String>;
        C const originalArray = { "aaa", "aab", "aac", "bba", "bbb", "bbc", "cca", "ccb", "ccc" };

        allOk = allOk && collectionTestGroupRemoveBy <C, String> (
                originalArray, this, sPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (sr1, sr2, sr3, sr4, sr5, sr6),
                        makeTuple <C, C, C, C> (srf1, srf2, srf3, srf4),
                        makeTuple <C, C, C, C> (srl1, srl2, srl3, srl4),
                        makeTuple <C, C, C, C> (sra1, sra2, sra3, sra4)
                )
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        using C = cds::HashMap <String, String>;
        C const originalArray = { {"ccb", "ccb"}, {"ccc", "ccc"}, {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"} };

        allOk = allOk && collectionTestGroupRemoveBy <C, MapEntry <String, String>> (
                originalArray, this, ssPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ossr1, ossr2, ossr3, ossr4, ossr5, ossr6),
                        makeTuple <C, C, C, C> (ossrf1, ossrf2, ossrf3, ossrf4),
                        makeTuple <C, C, C, C> (ossrl1, ossrl2, ossrl3, ossrl4),
                        makeTuple <C, C, C, C> (ossra1, ossra2, ossra3, ossra4)
                )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [this, & allOk]{

        using C = cds::LinkedHashMap <String, String>;
        C const originalArray = { {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };

        allOk = allOk && collectionTestGroupRemoveBy <C, MapEntry <String, String>> (
                originalArray, this, ssPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ssr1, ssr2, ssr3, ssr4, ssr5, ssr6),
                        makeTuple <C, C, C, C> (ssrf1, ssrf2, ssrf3, ssrf4),
                        makeTuple <C, C, C, C> (ssrl1, ssrl2, ssrl3, ssrl4),
                        makeTuple <C, C, C, C> (ssra1, ssra2, ssra3, ssra4)
                )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [this, & allOk]{

        using C = cds::TreeMap <String, String>;
        C const originalArray = { {"aaa", "aaa"}, {"aab", "aab"}, {"aac", "aac"}, {"bba", "bba"}, {"bbb", "bbb"}, {"bbc", "bbc"}, {"cca", "cca"}, {"ccb", "ccb"}, {"ccc", "ccc"} };

        allOk = allOk && collectionTestGroupRemoveBy <C, MapEntry <String, String>> (
                originalArray, this, ssPred, makeTuple (
                        rtLimit, rlLessRes,
                        makeTuple <C, C, C, C, C, C> (ssr1, ssr2, ssr3, ssr4, ssr5, ssr6),
                        makeTuple <C, C, C, C> (ssrf1, ssrf2, ssrf3, ssrf4),
                        makeTuple <C, C, C, C> (ssrl1, ssrl2, ssrl3, ssrl4),
                        makeTuple <C, C, C, C> (ssra1, ssra2, ssra3, ssra4)
                )
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveBy-" __CDS_cpplang_core_version_name " : CTG-00400-RB-" __CDS_cpplang_core_version_name " : StringArrayMemberFunction", [this, & allOk]{

        cds :: Array < String > const strArray = { "word1", "word2", "", "", "word3", "", "word4", "", "", "","", "word5", "" };

        auto copyForRemoveThat      = strArray;
        auto copyForRemoveFirstThat = strArray;
        auto copyForRemoveLastThat  = strArray;
        auto copyForRemoveAllThat   = strArray;
        cds :: Array < String > copyForRemoveAllThatCoverage   = {"word1", "word2", "", "word3", "word4", "word5"};

        cds :: Collection < String > & cRT  = copyForRemoveThat;
        cds :: Collection < String > & cRFT = copyForRemoveFirstThat;
        cds :: Collection < String > & cRLT = copyForRemoveLastThat;
        cds :: Collection < String > & cRAT = copyForRemoveAllThat;
        cds :: Collection < String > & cRATCoverage = copyForRemoveAllThatCoverage;
        Size const removeThatLimit = 5;

        cds :: Array < String > const expectedAfterRemoveThat         = { "word1", "word2", "word3", "word4", "", "", "word5", "" };
        cds :: Array < String > const expectedAfterRemoveFirstThat    = { "word1", "word2", "", "word3", "", "word4", "", "", "","", "word5", "" };
        cds :: Array < String > const expectedAfterRemoveLastThat     = { "word1", "word2", "", "", "word3", "", "word4", "", "", "","", "word5" };
        cds :: Array < String > const expectedAfterRemoveAllThat      = { "word1", "word2", "word3", "word4", "word5" };
        cds :: Array < String >       expectedAfterRemoveAllThatCoverage = { "word1", "word2", "word3", "word4", "word5" };

        Size const removeThatExpected = 5;
        bool const removeFirstThatExpected = true;
        bool const removeLastThatExpected = true;
        Size const removeAllThatExpected = 8;

        /* CollectionTestCase-RemoveBy-memberRemoveThat-cpp-xx : CTC-00419-RB-memberRemoveThat-cpp-xx */
        auto const  removeThatRes = cRT.removeThat ( removeThatLimit, & String :: empty );
        if ( ( removeThatExpected != removeThatRes ) || ( ! cRT.equals ( expectedAfterRemoveThat ) ) ) {
            this->logError ( "'CTC-00419-RB-memberRemoveThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00419-RB-memberRemoveThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveFirstThat-cpp-xx : CTC-00420-RB-memberRemoveFirstThat-cpp-xx */
        auto const  removeFirstThatRes = cRFT.removeFirstThat ( & String :: empty );
        if ( ( removeFirstThatExpected != removeFirstThatRes ) || ( ! cRFT.equals ( expectedAfterRemoveFirstThat ) ) ) {
            this->logError ( "'CTC-00420-RB-memberRemoveFirstThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00420-RB-memberRemoveFirstThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveLastThat-cpp-xx : CTC-00421-RB-memberRemoveLastThat-cpp-xx */
        auto const  removeLastThatRes = cRLT.removeLastThat ( & String :: empty );
        if ( ( removeLastThatExpected != removeLastThatRes ) || ( ! cRLT.equals ( expectedAfterRemoveLastThat ) ) ) {
            this->logError ( "'CTC-00421-RB-memberRemoveLastThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00421-RB-memberRemoveLastThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveAllThat-cpp-xx : CTC-00422-RB-memberRemoveAllThat-cpp-xx */
        auto const removeAllThatRes = cRAT.removeAllThat ( & String :: empty );
        if ( ( removeAllThatExpected != removeAllThatRes ) || ( ! cRAT.equals ( expectedAfterRemoveAllThat ) ) ) {
            this->logError ( "'CTC-00422-RB-memberRemoveAllThat-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00422-RB-memberRemoveAllThat-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RemoveBy-memberRemoveThatCoverage-cpp-xx : CTC-00423-RB-memberRemoveThatCoverage-cpp-xx */
        auto const  removeAllThatCovRes = cRATCoverage.removeAllThat ( & String :: empty );
        if ( ( 1U != removeAllThatCovRes ) || ( ! cRATCoverage.equals ( expectedAfterRemoveAllThatCoverage ) ) ) {
            this->logError ( "'CTC-00423-RB-memberRemoveThatCoverage-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00423-RB-memberRemoveThatCoverage-" __CDS_cpplang_core_version_name "' OK" );
        }

        cds :: Collection < String > & extraForNegCoverage = expectedAfterRemoveAllThatCoverage;

        (void) extraForNegCoverage.removeThat (5, & String :: empty);
        (void) extraForNegCoverage.removeFirstThat (& String :: empty);
        (void) extraForNegCoverage.removeLastThat (& String :: empty);
        (void) extraForNegCoverage.removeAllThat (& String :: empty);

        (void) extraForNegCoverage.insert ("");
        (void) extraForNegCoverage.removeThat (5, & String :: empty);

    });

    return allOk;
}
