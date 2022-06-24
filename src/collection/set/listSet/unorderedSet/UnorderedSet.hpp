//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_UNORDERED_SET_HPP__
#define __CDS_UNORDERED_SET_HPP__

#include "../ListSet.hpp"

#include "../../../../shared/impl/generalPredicates.hpp"

namespace cds {

    template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
    class Sequence;

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class UnorderedSet : public ListSet < __ElementType > {

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

    public:
        constexpr UnorderedSet () noexcept;

    public:
        UnorderedSet (
                UnorderedSet const & set
        ) noexcept;

    public:
        constexpr UnorderedSet (
                UnorderedSet && set
        ) noexcept;

    public:
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        UnorderedSet (
                __IteratorType          const & begin,
                __IteratorType          const & end
        ) noexcept;

    public:
        __CDS_Implicit UnorderedSet ( // NOLINT(google-explicit-constructor)
                InitializerList const & initializerList
        ) noexcept;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_Implicit UnorderedSet ( // NOLINT(google-explicit-constructor)
                Collection < __OtherElementType > const & collection
        ) noexcept;

    public:
        ~UnorderedSet() noexcept override;

    private:
        auto pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * override;

    public:
        auto operator == (
                UnorderedSet const & set
        ) const noexcept -> bool;

    public:
        auto operator != (
                UnorderedSet const & set
        ) const noexcept -> bool;

    public:
        template < typename __VElementType = __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto operator = (
                UnorderedSet const & set
        ) noexcept -> UnorderedSet &;

    public:
        auto operator = (
                UnorderedSet && set
        ) noexcept -> UnorderedSet &;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> UnorderedSet &;

    public:
        auto sequence () & noexcept -> Sequence < UnorderedSet < __ElementType > >;

    public:
        auto sequence () && noexcept -> Sequence < UnorderedSet < __ElementType > >;

    public:
        auto sequence () const & noexcept -> Sequence < UnorderedSet < __ElementType > const >;

    public:
        auto sequence () const && noexcept -> Sequence < UnorderedSet < __ElementType > const >;
    };

}

#include "unorderedSet/impl/UnorderedSet.hpp"

#include "unorderedSet/CTAD.hpp"

#include "../../../../shared/unorderedSet/impl/UnorderedSetSequence.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif //__CDS_UNORDERED_SET_HPP__
