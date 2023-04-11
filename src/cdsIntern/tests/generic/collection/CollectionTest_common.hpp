#ifndef COLLECTION_TEST_COMMON_H
#define COLLECTION_TEST_COMMON_H

#include "CollectionTest.h"
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/HashSet>
#include <CDS/HashMap>
#include <CDS/TreeSet>
#include <CDS/TreeMap>
#include <CDS/LinkedHashSet>
#include <CDS/LinkedHashMap>
#include <CDS/Range>

#include <initializer_list>
#include <vector>
#include <array>

namespace {

    using glob::Test;
    using glob::CollectionTest;


    using cds::uint32;
    using cds::Size;


    using cds::Object;

    using cds::String;
    using cds::StringLiteral;
    using cds::MapEntry;

    using cds::Collection;
    using cds::Iterable;


    using cds::meta::TrueType;
    using cds::meta::FalseType;
    using cds::meta::Void;
    using cds::meta::EnableIf;

    using cds::meta::addressOf;
    using cds::meta::referenceOf;


    template <typename ... T> auto make_a (T && ... elements) noexcept -> decltype (cds::arrayOf (std :: forward <T> (elements) ...)) {
        return cds::arrayOf (std :: forward <T> (elements) ...);
    }


    template <typename T> auto make_a () noexcept -> cds::Array<T> {
        return {};
    }


    template <typename ... T> auto make_ll (T && ... elements) noexcept -> decltype (cds::linkedListOf (std :: forward <T> (elements) ...)) {
        return cds::linkedListOf (std :: forward <T> (elements) ...);
    }


    template <typename T> auto make_ll () noexcept -> cds::LinkedList<T> {
        return {};
    }


    template <typename ... T> auto make_hs (T && ... elements) noexcept -> decltype (cds::hashSetOf (std :: forward <T> (elements) ...)) {
        return cds::hashSetOf (std :: forward <T> (elements) ...);
    }


    template <typename T> auto make_hs () noexcept -> cds::HashSet<T> {
        return {};
    }


    template <typename ... T> auto make_lhs (T && ... elements) noexcept -> decltype (cds::linkedHashSetOf (std :: forward <T> (elements) ...)) {
        return cds::linkedHashSetOf (std :: forward <T> (elements) ...);
    }


    template <typename T> auto make_lhs () noexcept -> cds::LinkedHashSet<T> {
        return {};
    }


    template <typename ... T> auto make_ts (T && ... elements) noexcept -> decltype (cds::treeSetOf (std :: forward <T> (elements) ...)) {
        return cds::treeSetOf (std :: forward <T> (elements) ...);
    }


    template <typename T> auto make_ts () noexcept -> cds::TreeSet<T> {
        return {};
    }


    template <
            typename __ElementType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
            template < typename ... > class __CollectionType,                                                       /* NOLINT(bugprone-reserved-identifier) */
            typename __ValidatorPredicate,                                                                          /* NOLINT(bugprone-reserved-identifier) */
            typename __IteratorType = typename cds :: Collection < __ElementType > :: ConstIterator /* NOLINT(bugprone-reserved-identifier) */
    > auto iteratorListEqualityCheck (
            __ValidatorPredicate                const & validator,
            __CollectionType < __IteratorType > const & iteratorCollection,
            __CollectionType < __ElementType >  const & elementCollection
    ) -> bool {

        auto leftIt = iteratorCollection.begin();
        auto leftEnd = iteratorCollection.end();
        auto rightIt = elementCollection.begin();
        auto rightEnd = elementCollection.end();

        if ( iteratorCollection.size() != elementCollection.size() ) {
            return false;
        }

        for ( ; leftIt != leftEnd && rightIt != rightEnd; ++ leftIt, ++ rightIt ) {
            if ( ! validator ( * ( * leftIt ) ) || ! validator ( * rightIt ) || * ( * leftIt ) != * rightIt ) {
                return false;
            }
        }

        return true;
    }

    template <
            typename __ElementType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
            template < typename ... > class __CollectionType,                                                                           /* NOLINT(bugprone-reserved-identifier) */
            typename __IteratorType = typename cds :: Collection < __ElementType > :: ConstIterator /* NOLINT(bugprone-reserved-identifier) */
    > auto iteratorListEqualityCheckNoPred (
            __CollectionType < __IteratorType > const & iteratorCollection,
            __CollectionType < __ElementType >  const & elementCollection
    ) -> bool {

        auto leftIt = iteratorCollection.begin();
        auto leftEnd = iteratorCollection.end();
        auto rightIt = elementCollection.begin();
        auto rightEnd = elementCollection.end();

        if ( iteratorCollection.size() != elementCollection.size() ) {
            return false;
        }

        for ( ; leftIt != leftEnd && rightIt != rightEnd; ++ leftIt, ++ rightIt ) {
            if ( * ( * leftIt ) != * rightIt ) {
                return false;
            }
        }

        return true;
    }

    template < typename T, typename = void > struct _HasToString : FalseType {};    /* NOLINT(bugprone-reserved-identifier) */
    template < typename T > struct _HasToString < T, Void < decltype ( addressOf < T > ()->toString () ) > > : TrueType {}; /* NOLINT(bugprone-reserved-identifier) */

    template < typename T, typename = void > struct _HasEquals : FalseType {};  /* NOLINT(bugprone-reserved-identifier) */
    template < typename T > struct _HasEquals < T, Void < decltype ( addressOf < T > ()->equals ( referenceOf < Object const > () ) ) > > : TrueType {};    /* NOLINT(bugprone-reserved-identifier) */

    template <
            typename T,
            EnableIf < _HasToString < T > :: value > = 0
    > auto toString (T const & v) -> String {

        return v.toString ();
    }

    template <
            typename T,
            EnableIf < ! _HasToString < T > :: value > = 0
    > auto toString (T const & v) -> String {

        if ( v.size() == 0ULL ) {
            return "[]";
        }

        String s = "[ ";
        for ( auto & e : v ) {
            s += e;
            s += ", ";
        }

        return s.removeSuffix (", ") + " ]";
    }

    template <
            typename T,
            typename V,
            EnableIf < _HasEquals < T > :: value && _HasEquals < V > :: value > = 0
    > auto equals (T const & t, V const & v) -> bool {

        return t.equals (v);
    }

    template <
            typename T,
            typename V,
            EnableIf < ! _HasEquals < T > :: value || ! _HasEquals < V > :: value > = 0
    > auto equals (T const & t, V const & v) -> bool {

        auto lIt = t.begin();
        auto le = t.end();
        auto rIt = v.begin();
        auto re = v.end();
        for (
                ;   lIt != le && rIt != re; ++ lIt, ++ rIt
                )
            if ( ! cds::meta::equals ( * lIt, * rIt ) )
                return false;

        return true;
    }

}

#endif /* COLLECTION_TEST_COMMON_H */
