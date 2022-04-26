//
// Created by uic70278 on 4/24/2022.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include <CDS/experimental/List>

namespace cds {
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

        private:
            class ArrayDelegateIterator;
        private:
            class ArrayDelegateConstIterator;
        private:
            using typename Collection < T > :: DelegateIteratorRequestType;
        private:
            auto delegateIterator ( DelegateIteratorRequestType ) noexcept -> UniquePointer < DelegateIterator > override;
        private:
            auto delegateConstIterator ( DelegateIteratorRequestType ) noexcept -> UniquePointer < DelegateConstIterator > override;

        private:
            ElementType ** _pData       { nullptr };
            Size           _capacity    { 0ULL };

        public:
            Array () noexcept = default;
        public:
            Array ( Array const & ) noexcept;
        public:
            Array ( Array && ) noexcept;
        public:
            Array (
                    AbstractIterator const &,
                    AbstractIterator const &
            ) noexcept;
        public:
            Array ( InitializerList const & ) noexcept;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: defaultConstructible > >
            explicit Array ( Size ) noexcept;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyConstructible > >
            Array ( Size, ElementType const & ) noexcept;
        public:
            Array ( Collection < T > const & ) noexcept;
        public:
            ~Array () noexcept override;

        private:
            auto _resize ( Size ) noexcept -> void;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: defaultConstructible > >
            auto resize ( Size ) noexcept -> void;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyConstructible > >
            auto resize ( Size, ElementType const & ) noexcept -> void;

        public:
            auto shrink ( Size ) noexcept -> void;

        public:
            auto remove ( Iterator const & ) noexcept -> bool override;
        public:
            auto remove ( ConstIterator const & ) noexcept -> bool override;
        public:
            auto remove ( ReverseIterator const & ) noexcept -> bool override;
        public:
            auto remove ( ConstReverseIterator const & ) noexcept -> bool override;

        public:
            auto front () noexcept (false) -> ElementType & override;
        public:
            auto front () const noexcept (false) -> ElementType const & override;
        public:
            auto back () noexcept (false) -> ElementType & override;
        public:
            auto back () const noexcept (false) -> ElementType const & override;

        public:
            auto get ( Index ) noexcept (false) -> ElementType & override;
        public:
            auto get ( Index ) const noexcept (false) -> ElementType const & override;

        public:
            auto equals ( Object const & ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;
        public:
            auto makeUnique () noexcept -> void override;

        public:
            auto popFront () noexcept (false) -> void override;
        public:
            auto popBack () noexcept (false) -> void override;

        public:
            auto operator = ( Array const & ) noexcept -> Array &;
        public:
            auto operator = ( Array && ) noexcept -> Array &;
        public:
            auto operator = ( Collection < T > const & ) noexcept -> Array &;

        public:
            auto copy () const noexcept -> Array < T > * override;

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
