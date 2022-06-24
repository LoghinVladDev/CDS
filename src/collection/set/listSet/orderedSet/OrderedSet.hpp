//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_ORDERED_SET_HPP__
#define __CDS_ORDERED_SET_HPP__

#include "../ListSet.hpp"
#include <CDS/Comparator>

#include "../../../../shared/impl/generalPredicates.hpp"

namespace cds {

    template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
    class Sequence;

    template <
            typename __ElementType, // NOLINT(bugprone-reserved-identifier)
            typename __ComparatorFunction = FunctionComparator < __ElementType, & predicates :: lessThan < __ElementType > > // NOLINT(bugprone-reserved-identifier)
    > class OrderedSet : public ListSet < __ElementType > {

    public:
        using typename ListSet < __ElementType > :: ElementType;

    public:
        using typename ListSet < __ElementType > :: ConstIterator;

    public:
        using typename ListSet < __ElementType > :: ConstReverseIterator;

    protected:
        using typename ListSet < __ElementType > :: InitializerList;

    protected:
        using typename ListSet < __ElementType > :: Node;

    private:
        __CDS_NoUniqueAddress __ComparatorFunction _comparatorFunction;

    public:
        constexpr OrderedSet () noexcept;

    public:
        OrderedSet (
                OrderedSet const & set
        ) noexcept;

    public:
        constexpr OrderedSet (
                OrderedSet && set
        ) noexcept;

    public:
        __CDS_Explicit OrderedSet (
                __ComparatorFunction const & comparatorFunction
        ) noexcept;

    public:
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        OrderedSet (
                __IteratorType          const & begin,
                __IteratorType          const & end
        ) noexcept;

    public:
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        OrderedSet (
                __IteratorType          const & begin,
                __IteratorType          const & end,
                __ComparatorFunction    const & comparatorFunction
        ) noexcept;

    public:
        __CDS_Implicit OrderedSet ( // NOLINT(google-explicit-constructor)
                InitializerList const & initializerList
        ) noexcept;

    public:
        OrderedSet (
                InitializerList         const & initializerList,
                __ComparatorFunction    const & comparatorFunction
        ) noexcept;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_Implicit OrderedSet ( // NOLINT(google-explicit-constructor)
                Collection < __OtherElementType > const & collection
        ) noexcept;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_Implicit OrderedSet (
                Collection < __OtherElementType >   const & collection,
                __ComparatorFunction                const & comparatorFunction
        ) noexcept;

    public:
        ~OrderedSet() noexcept override;

    private:
        auto pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * override;

    public:
        auto operator == (
                OrderedSet const & set
        ) const noexcept -> bool;

    public:
        auto operator != (
                OrderedSet const & set
        ) const noexcept -> bool;

    public:
        template < typename __VElementType = __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto operator = (
                OrderedSet const & set
        ) noexcept -> OrderedSet &;

    public:
        auto operator = (
                OrderedSet && set
        ) noexcept -> OrderedSet &;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> OrderedSet &;

    public:
        auto sequence () & noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > >;

    public:
        auto sequence () && noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > >;

    public:
        auto sequence () const & noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > const >;

    public:
        auto sequence () const && noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > const >;
    };

}

#include "orderedSet/impl/OrderedSet.hpp"

#include "orderedSet/CTAD.hpp"

#include "../../../../shared/orderedSet/impl/OrderedSetSequence.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_ORDERED_SET_HPP__
