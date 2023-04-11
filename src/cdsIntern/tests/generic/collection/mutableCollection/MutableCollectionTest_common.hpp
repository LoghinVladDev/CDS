/*
 * Created by loghin on 04/09/22.
 */

#ifndef MUTABLE_COLLECTION_TEST_COMMON_H
#define MUTABLE_COLLECTION_TEST_COMMON_H

#include "MutableCollectionTest.h"

#include <CDS/Array>
#include <CDS/HashMap>
#include <CDS/LinkedList>
#include <CDS/Range>

#include <array>
#include <vector>


namespace {

    using cds::uint32;
    using cds::Size;


    using cds::Object;

    using cds::String;
    using cds::StringLiteral;
    using cds::MapEntry;

    using cds::MutableCollection;


    using cds::meta::TrueType;
    using cds::meta::FalseType;
    using cds::meta::Void;
    using cds::meta::EnableIf;

    using cds::meta::addressOf;
    using cds::meta::referenceOf;


    using glob::Test;
    using glob::MutableCollectionTest;


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
        ) {
            if (!cds::meta::equals(*lIt, *rIt)) {
                return false;
            }
        }

        return true;
    }

}


#endif
