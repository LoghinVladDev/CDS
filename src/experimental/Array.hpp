//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include <CDS/experimental/List>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class Array : public List < T > {
        public:
            using typename List < T > :: ElementType;

        public:
            using typename List < T > :: Iterator;
        public:
            using typename List < T > :: ConstIterator;
        public:
            using typename List < T > :: ReverseIterator;
        public:
            using typename List < T > :: ConstReverseIterator;

        protected:
            using typename List < T > :: InitializerList;
        protected:
            using typename List < T > :: DelegateIterator;
        protected:
            using typename List < T > :: DelegateConstIterator;
        protected:
            using typename List < T > :: AbstractIterator;
        protected:
            using typename List < T > :: AbstractDelegateIterator;

        private:
            class ArrayDelegateIterator;
        private:
            class ArrayDelegateConstIterator;
        private:
            using typename Collection < T > :: DelegateIteratorRequestType;
        private:
            auto delegateIterator ( DelegateIteratorRequestType ) noexcept -> cds :: UniquePointer < DelegateIterator > override;
        private:
            auto delegateConstIterator ( DelegateIteratorRequestType ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        private:
            ElementType ** _pData       { nullptr };
            Size           _capacity    { 0ULL };

        private:
            auto initializeByCopy ( Array const & ) noexcept -> void;

        public:
            constexpr Array () noexcept = default;
        public:
            __CDS_OptimalInline Array ( Array const & ) noexcept;
        public:
            constexpr Array ( Array && ) noexcept;
        public:
            Array (
                    AbstractIterator const &,
                    AbstractIterator const &
            ) noexcept;
        public:
            Array ( InitializerList const & ) noexcept; // NOLINT(google-explicit-constructor)
        public:
            template < typename V = T, meta :: EnableIf < meta :: isDefaultConstructible < V > () > >
            explicit Array ( Size ) noexcept;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
            Array ( Size, ElementType const & ) noexcept;
        public:
            Array ( Collection < T > const & ) noexcept;
        public:
            ~Array () noexcept override;

        private:
            auto _resize ( Size ) noexcept -> void;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isDefaultConstructible < V > () > >
            auto resize ( Size ) noexcept -> void;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
            auto resize ( Size, ElementType const & ) noexcept -> void;

        public:
            auto shrink ( Size ) noexcept -> void;

        public:
            auto removeAt ( Index ) noexcept -> bool override;
        public:
            auto removeAt ( Collection < Index > const & ) noexcept -> Size override;

        public:
            __CDS_OptimalInline auto remove ( Iterator const & ) noexcept -> bool override;
        public:
            __CDS_OptimalInline auto remove ( ConstIterator const & ) noexcept -> bool override;
        public:
            __CDS_OptimalInline auto remove ( ReverseIterator const & ) noexcept -> bool override;
        public:
            __CDS_OptimalInline auto remove ( ConstReverseIterator const & ) noexcept -> bool override;

//        public:
//            auto remove ( Collection < Iterator > const & ) noexcept -> Size override;
//        public:
//            auto remove ( Collection < ConstIterator > const & ) noexcept -> Size override;
//        public:
//            auto remove ( Collection < ReverseIterator > const & ) noexcept -> Size override;
//        public:
//            auto remove ( Collection < ConstReverseIterator > const & ) noexcept -> Size override;

        protected:
            auto remove ( Iterator const *, Size ) noexcept -> Size override;
        protected:
            auto remove ( ConstIterator const *, Size ) noexcept -> Size override;
        protected:
            auto remove ( ReverseIterator const *, Size ) noexcept -> Size override;
        protected:
            auto remove ( ConstReverseIterator const *, Size ) noexcept -> Size override;

        private:
            auto pNewBefore ( Index ) noexcept -> ElementType * &;
        private:
            auto pNewAfter ( Index ) noexcept -> ElementType * &;

        protected:
            __CDS_OptimalInline auto pNewFront () noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewBack () noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewBefore ( Iterator const & ) noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewAfter ( Iterator const & ) noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewBefore ( ConstIterator const & ) noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewAfter ( ConstIterator const & ) noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewBefore ( ReverseIterator const & ) noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewAfter ( ReverseIterator const & ) noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewBefore ( ConstReverseIterator const & ) noexcept -> ElementType * & override;
        protected:
            __CDS_OptimalInline auto pNewAfter ( ConstReverseIterator const & ) noexcept -> ElementType * & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get ( Index ) noexcept (false) -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get ( Index ) const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_OptimalInline auto equals ( Object const & ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;
        public:
            auto makeUnique () noexcept -> void override;

        public:
            auto popFront () noexcept -> void override;
        public:
            auto popBack () noexcept -> void override;

        public:
            auto operator = ( Array const & ) noexcept -> Array &;
        public:
            auto operator = ( Array && ) noexcept -> Array &;
        public:
            auto operator = ( Collection < T > const & ) noexcept -> Array &;

        public:
            auto sequence () & noexcept -> Sequence < Array < T > >;
        public:
            auto sequence () && noexcept -> Sequence < Array < T > >;
        public:
            auto sequence () const & noexcept -> Sequence < Array < T > const >;
        public:
            auto sequence () const && noexcept -> Sequence < Array < T > const >;
        };

    }
}

#include "array/ArrayDelegateIterator.hpp"
#include "array/ArrayDelegateConstIterator.hpp"

#include "array/impl/Array.hpp"
#include "array/impl/ArrayDelegateIterator.hpp"
#include "array/impl/ArrayDelegateConstIterator.hpp"

#endif // __CDS_EX_ARRAY_HPP__
