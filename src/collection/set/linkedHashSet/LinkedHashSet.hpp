//
// Created by loghin on 6/24/22.
//

#ifndef __CDS_LINKED_HASH_SET_HPP__
#define __CDS_LINKED_HASH_SET_HPP__

#include <CDS/HashSet>
#include "../../../shared/linkedList/SingleLinkedList.hpp"
#include "linkedHashSet/SingleLinkedListConstructs.hpp"

namespace cds {

    template <
            typename __ElementType,                                                                 // NOLINT(bugprone-reserved-identifier)
            typename __Hasher = FunctionHasher < __ElementType, & cds :: hash < __ElementType > >   // NOLINT(bugprone-reserved-identifier)
    > class LinkedHashSet :
            public HashSet < __ElementType, __Hasher >,
            protected __hidden :: __impl :: __SingleLinkedList <
                    __ElementType *,
                    FunctionComparator < __ElementType *, & cds :: meta :: equals < __ElementType * > >,
                    FunctionDestructor < __ElementType *, & __hidden :: __impl :: __linkedHashSetElementDestruct < __ElementType * > >
            > {

    protected:
        using __SingleLinkedListElementType =  // NOLINT(bugprone-reserved-identifier)
                __ElementType *;

    protected:
        using __SingleLinkedListElementComparator = // NOLINT(bugprone-reserved-identifier)
                FunctionComparator <
                        __ElementType *,
                        & cds :: meta :: equals < __ElementType * >
                >;

    protected:
        using __SingleLinkedListElementDestructor = // NOLINT(bugprone-reserved-identifier)
                FunctionDestructor <
                        __ElementType *,
                        & __hidden :: __impl :: __linkedHashSetElementDestruct < __ElementType * >
                >;

    protected:
        using __SingleLinkedListElementCopyConstructor = // NOLINT(bugprone-reserved-identifier)
                FunctionCopyConstructor <
                        __ElementType *,
                        & __hidden :: __impl :: __linkedHashSetElementCopyConstruct < __ElementType * >
                >;

    protected:
        using typename HashSet < __ElementType > :: ElementType;

    protected:
        using typename HashSet < __ElementType > :: ConstIterator;

    protected:
        using typename HashSet < __ElementType > :: ConstReverseIterator;

    protected:
        using typename HashSet < __ElementType > :: InitializerList;

    protected:
        using typename HashSet < __ElementType > :: DelegateConstIterator;

    protected:
        using typename HashSet < __ElementType > :: AbstractDelegateIterator;

    protected:
        using typename HashSet < __ElementType > :: DelegateIteratorRequestType;

    private:
        class LinkedHashSetDelegateConstIterator;

    private:
        auto delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

    public:
        constexpr LinkedHashSet () noexcept;

    public:
        template <
                typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > __CDS_Implicit LinkedHashSet (                          // NOLINT(google-explicit-constructor)
                LinkedHashSet const & set
        ) noexcept;

    public:
        constexpr LinkedHashSet (
                LinkedHashSet && set
        ) noexcept;

    public:
        __CDS_Explicit LinkedHashSet (
                __Hasher const & hasher
        ) noexcept;

    public:
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        LinkedHashSet (
                __IteratorType const & begin,
                __IteratorType const & end
        ) noexcept;

    public:
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        LinkedHashSet (
                __IteratorType      const & begin,
                __IteratorType      const & end,
                __Hasher            const & hasher
        ) noexcept;

    public:
        __CDS_Implicit LinkedHashSet ( // NOLINT(google-explicit-constructor)
                InitializerList const & initializerList
        ) noexcept;

    public:
        LinkedHashSet (
                InitializerList     const & initializerList,
        __Hasher            const & hasher
        ) noexcept;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_Explicit LinkedHashSet (
                Collection < __OtherElementType >   const & collection
        ) noexcept;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        LinkedHashSet (
                Collection < __OtherElementType >   const & collection,
        __Hasher                            const & hasher
        ) noexcept;

    public:
        ~LinkedHashSet() noexcept override;

    public:
        auto remove (
                ElementType const & element
        ) noexcept -> bool override;

    public:
        auto remove (
                ConstIterator const & iterator
        ) noexcept -> bool override;

    public:
        auto remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool override;

    protected:
        auto pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * override;

    public:
        auto clear () noexcept -> void override;

    public:
        auto operator == (
                LinkedHashSet const & set
        ) const noexcept -> bool;

    public:
        auto operator != (
                LinkedHashSet const & set
        ) const noexcept -> bool;

    public:
        template < typename __VElementType = __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto operator = (
                LinkedHashSet const & hashSet
        ) noexcept -> LinkedHashSet &;

    public:
        auto operator = (
                LinkedHashSet && hashSet
        ) noexcept -> LinkedHashSet &;

    public:
        __CDS_cpplang_ConstexprOverride auto move (
                HashSet < __ElementType, __Hasher > && hashSet
        ) noexcept -> LinkedHashSet & override;

    public:
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        auto operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> LinkedHashSet &;

    public:
        auto sequence () & noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > >;

    public:
        auto sequence () && noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > >;

    public:
        auto sequence () const & noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > const >;

    public:
        auto sequence () const && noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > const >;
    };

}

#include "linkedHashSet/DelegateConstIterator.hpp"

#include "linkedHashSet/impl/DelegateConstIterator.hpp"
#include "linkedHashSet/impl/LinkedHashSet.hpp"

#include "linkedHashSet/CTAD.hpp"

#endif // __CDS_LINKED_HASH_SET_HPP__
