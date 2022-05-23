//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_EX_LINKED_LIST_HPP__
#define __CDS_EX_LINKED_LIST_HPP__

#include <CDS/experimental/List>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class List;

        template < typename T >
        class LinkedList : public List < T > {
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
            class LinkedListDelegateIterator;
        private:
            class LinkedListDelegateConstIterator;
        private:
            using typename Collection < T > :: DelegateIteratorRequestType;

        private:
            auto delegateIterator (
                    DelegateIteratorRequestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override;
        private:
            auto delegateConstIterator (
                    DelegateIteratorRequestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        private:
            struct Node;

        private:
            Node * _pFront  { nullptr };
        private:
            Node * _pBack   { nullptr };

        public:
            constexpr LinkedList () noexcept = default;
        public:
            LinkedList (
                    LinkedList const &
            ) noexcept;
        public:
            constexpr LinkedList (
                    LinkedList &&
            ) noexcept;
        public:
            LinkedList (
                    AbstractIterator const &,
                    AbstractIterator const &
            ) noexcept;
        public:
            LinkedList (
                    InitializerList const &
            ) noexcept;
        public:
            ~LinkedList () noexcept;

        private:
            auto remove (
                    Node const *
            ) noexcept -> bool;
        private:
            auto remove (
                    Collection < Node const * > const &
            ) noexcept -> Size;

        public:
            auto removeAt (
                    Index
            ) noexcept -> bool override;
        public:
            auto removeAt (
                    Collection < Index > const &
            ) noexcept -> Size override;

        public:
            auto remove (
                    Iterator const &
            ) noexcept -> bool override;
        public:
            auto remove (
                    ConstIterator const &
            ) noexcept -> bool override;
        public:
            auto remove (
                    ReverseIterator const &
            ) noexcept -> bool override;
        public:
            auto remove (
                    ConstReverseIterator const &
            ) noexcept -> bool override;

        protected:
            auto remove (
                    Iterator const *,
                    Size
            ) noexcept -> Size override;
        protected:
            auto remove (
                    ConstIterator const *,
                    Size
            ) noexcept -> Size override;
        protected:
            auto remove (
                    ReverseIterator const *,
                    Size
            ) noexcept -> Size override;
        protected:
            auto remove (
                    ConstReverseIterator const *,
                    Size
            ) noexcept -> Size override;

        private:
            auto pNewBefore (
                    Node const *
            ) noexcept -> ElementType * &;
        private:
            auto pNewAfter (
                    Node const *
            ) noexcept -> ElementType * &;

        protected:
            auto pNewFront () noexcept -> ElementType * & override;
        protected:
            auto pNewBack () noexcept -> ElementType * & override;
        protected:
            auto pNewBefore (
                    Iterator const &
            ) noexcept -> ElementType * & override;
        protected:
            auto pNewAfter (
                    Iterator const &
            ) noexcept -> ElementType * & override;
        protected:
            auto pNewBefore (
                    ConstIterator const &
            ) noexcept -> ElementType * & override;
        protected:
            auto pNewAfter (
                    ConstIterator const &
            ) noexcept -> ElementType * & override;
        protected:
            auto pNewBefore (
                    ReverseIterator const &
            ) noexcept -> ElementType * & override;
        protected:
            auto pNewAfter (
                    ReverseIterator const &
            ) noexcept -> ElementType * & override;
        protected:
            auto pNewBefore (
                    ConstReverseIterator const &
            ) noexcept -> ElementType * & override;
        protected:
            auto pNewAfter (
                    ConstReverseIterator const &
            ) noexcept -> ElementType * & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index
            ) noexcept (false) -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index
            ) const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard auto equals (
                    Object const &
            ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;
        public:
            auto makeUnique () noexcept -> void override;

        public:
            auto popFront () noexcept -> void override;
        public:
            auto popBack () noexcept -> void override;

        public:
            auto operator = (
                    LinkedList const &
            ) noexcept -> LinkedList &;
        public:
            auto operator = (
                    LinkedList &&
            ) noexcept -> LinkedList &;
        public:
            auto operator = (
                    Collection < T > const &
            ) noexcept -> LinkedList &;

        public:
            auto sequence () & noexcept -> Sequence < LinkedList < T > >;
        public:
            auto sequence () && noexcept -> Sequence < LinkedList < T > >;
        public:
            auto sequence () const & noexcept -> Sequence < LinkedList < T > const >;
        public:
            auto sequence () const && noexcept -> Sequence < LinkedList < T > const >;
        };

        template < typename T >
        using SingleLinkedList __CDS_Deprecated = LinkedList < T >;

        template < typename T >
        using DoubleLinkedList __CDS_Deprecated = LinkedList < T >;

    }
}

#include "linkedList/Node.hpp"
#include "linkedList/LinkedListDelegateIterator.hpp"
#include "linkedList/LinkedListDelegateConstIterator.hpp"

#include "linkedList/impl/LinkedListDelegateIterator.hpp"
#include "linkedList/impl/LinkedListDelegateConstIterator.hpp"
#include "linkedList/impl/LinkedList.hpp"

#endif // __CDS_EX_LINKED_LIST_HPP__
