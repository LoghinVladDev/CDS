/*
 * Created by loghin on 02.06.2021.
 */

#ifndef __CDS_SEQUENCE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SEQUENCE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>
#include <CDS/Optional>
#include <CDS/meta/TypeTraits>

/* TODO : indices of client */
/* TODO : Generic Statements */
/* TODO : Add apply, also, first, one to Generic Statements */
/* TODO : FindThat */
/* TODO : FindThat Optional? */
/* TODO : Drop Implemented with filter */

namespace cds {

    template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Sequence : public Object {

    private:
        using __IterableConstIteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin() );

    private:
        using __ElementType = decltype ( * ( cds :: meta :: referenceOf < __IterableConstIteratorType > () ) );

    public:
        Sequence () noexcept = delete;

    public:
        Sequence (
                Sequence const & sequence
        ) noexcept;

    public:
        Sequence (
                Sequence && sequence
        ) noexcept;

    public:
        Sequence (
                __IterableType const &
        ) noexcept;

    public:
        Sequence (
                __IterableType &&
        ) noexcept;

    public:
        ~Sequence () noexcept override;

    public:
        auto operator = (
                Sequence const & sequence
        ) noexcept -> Sequence &;

    public:
        auto operator = (
                Sequence && sequence
        ) noexcept -> Sequence &;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        __CDS_NoDiscard auto hash () const noexcept -> Size override;

    public:
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto contains (
                __ElementType const & element
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard auto at (
                Index index
        ) const noexcept -> Optional < __ElementType >;

    public:
        __CDS_NoDiscard auto atOr (
                Index                   index,
                __ElementType   const & defaultValue
        ) const noexcept -> __ElementType;

    public:
        template < cds :: meta :: EnableIf < cds :: meta :: isPointer < __ElementType > () > = 0 >
        __CDS_NoDiscard auto atOrNull (
                Index                   index
        ) const noexcept -> __ElementType;

    public:
        auto dropFirst (
                Size count
        ) noexcept -> Sequence < __IterableType > &;

    public:
        auto dropLast (
                Size count
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto dropFirstThat (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto dropLastThat (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto dropFirstWhile (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto dropLastWhile (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        auto keepFirst (
                Size count
        ) noexcept -> Sequence < __IterableType > &;

    public:
        auto keepLast (
                Size count
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto keepFirstWhile (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto keepLastWhile (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto keepFirstThat (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto keepLastThat (
                Size                count,
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __Predicate >
        auto filter (
                __Predicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;

    public:
        template < typename __IndexedPredicate >
        auto filterIndexed (
                __IndexedPredicate const & predicate
        ) noexcept -> Sequence < __IterableType > &;
    };

} /* namespace cds */

#endif /* __CDS_SEQUENCE_HPP__ */
