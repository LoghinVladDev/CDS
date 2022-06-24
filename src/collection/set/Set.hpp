//
// Created by loghin on 6/3/2022.
//

#ifndef __CDS_SET_HPP__
#define __CDS_SET_HPP__

#include <CDS/Collection>
#include "set/SetMeta.hpp"

namespace cds {

    template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
    class Set : public Collection < __ElementType > {

    public:
        using typename Collection < __ElementType > :: ElementType;

    protected:
        using typename Collection < __ElementType > :: InitializerList;

    protected:
        using typename Collection < __ElementType > :: DelegateConstIterator;

    protected:
        using typename Collection < __ElementType > :: DelegateIteratorRequestType;

    public:
        using typename Collection < __ElementType > :: ConstIterator;

    public:
        using typename Collection < __ElementType > :: ConstReverseIterator;

    protected:
        auto delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

    public:
        constexpr Set () noexcept = default;

    public:
        constexpr Set (
                Set const & set
        ) noexcept;

    public:
        constexpr Set (
                Set && set
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~Set () noexcept override = default;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        auto clear () noexcept -> void override = 0;

    public:
        virtual auto remove (
                ElementType const & element
        ) noexcept -> bool;

    public:
        auto remove (
                ConstIterator const & iterator
        ) noexcept -> bool override = 0;

    public:
        auto remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool override = 0;

    protected:
        auto remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size override = 0;

    protected:
        auto remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size override = 0;

    protected:
        auto pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * override = 0;

    public:
        template < typename __VElementType = __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto insert (
                ElementType const & element
        ) noexcept -> void;

    public:
        template < typename __VElementType = __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto insert (
                ElementType && element
        ) noexcept -> void;
    };

}

#include "set/impl/Set.hpp"

#endif // __CDS_SET_HPP__