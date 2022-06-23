//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_EX_LINKED_LIST_HPP__
#define __CDS_EX_LINKED_LIST_HPP__

#include <CDS/experimental/List>

#include "shared/Node.hpp"
#include "../shared/memory/PrimitiveAllocation.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class LinkedList : public List < __ElementType > {

        public:
            using typename List < __ElementType > :: ElementType;

        public:
            using typename List < __ElementType > :: Iterator;

        public:
            using typename List < __ElementType > :: ConstIterator;

        public:
            using typename List < __ElementType > :: ReverseIterator;

        public:
            using typename List < __ElementType > :: ConstReverseIterator;

        protected:
            using typename List < __ElementType > :: InitializerList;

        protected:
            using typename List < __ElementType > :: DelegateIterator;

        protected:
            using typename List < __ElementType > :: DelegateConstIterator;

        protected:
            using typename List < __ElementType > :: AbstractIterator;

        protected:
            using typename List < __ElementType > :: AbstractDelegateIterator;

        private:
            class LinkedListDelegateIterator;

        private:
            class LinkedListDelegateConstIterator;

        private:
            using typename Collection < __ElementType > :: DelegateIteratorRequestType;

        private:
            __CDS_NoDiscard auto delegateIterator (
                    DelegateIteratorRequestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override;

        private:
            __CDS_NoDiscard auto delegateConstIterator (
                    DelegateIteratorRequestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        private:
            using NodeData = cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ElementType >;

        private:
            using Node = __hidden :: __impl :: __BidirectionalNode < NodeData >;

        private:
            Node * _pFront  { nullptr };
        private:
            Node * _pBack   { nullptr };

        private:
            static auto __allocateNode () noexcept -> Node *;

        private:
            static auto __freeNode (
                    Node * pNode
            ) noexcept -> void;

        public:
            constexpr LinkedList () noexcept = default;

        public:
            LinkedList (
                    LinkedList const & list
            ) noexcept;

        public:
            constexpr LinkedList (
                    LinkedList &&
            ) noexcept;

        public:
            template < typename __IteratorType, meta :: EnableIf < meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            LinkedList (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept;

        public:
            __CDS_Implicit LinkedList ( // NOLINT(google-explicit-constructor)
                    InitializerList const &
            ) noexcept;

        public:
            template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_Explicit LinkedList (
                    Collection < __OtherElementType > const & collection
            ) noexcept;

        public:
            ~LinkedList () noexcept override;

        private:
            auto remove (
                    Node const * pNode
            ) noexcept -> bool;

        private:
            auto remove (
                    Collection < Node const * > const & nodes
            ) noexcept -> Size;

        public:
            auto removeAt (
                    Index index
            ) noexcept -> bool override;

        public:
            auto removeAt (
                    Collection < Index > const & indices
            ) noexcept -> Size override;

        public:
            auto removeAt (
                    std :: initializer_list < Index > const & indices
            ) noexcept -> Size override;

        public:
            auto remove (
                    Iterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;


        protected:
            auto remove (
                    Iterator    const * pIterator,
                    Size                iteratorCount
            ) noexcept -> Size override;
        protected:
            auto remove (
                    ConstIterator   const * pIterator,
                    Size                    iteratorCount
            ) noexcept -> Size override;
        protected:
            auto remove (
                    ReverseIterator const * pIterator,
                    Size                    iteratorCount
            ) noexcept -> Size override;
        protected:
            auto remove (
                    ConstReverseIterator    const * pIterator,
                    Size                            iteratorCount
            ) noexcept -> Size override;


        private:
            auto pNewBefore (
                    Node const * pNode
            ) noexcept -> ElementType *;

        private:
            auto pNewAfter (
                    Node const * pNode
            ) noexcept -> ElementType *;

        protected:
            auto pNewFront () noexcept -> ElementType * override;

        protected:
            auto pNewBack () noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    Iterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    Iterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * override;

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
                    Index index
            ) noexcept (false) -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index index
            ) const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard auto operator == (
                    LinkedList const & list
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator != (
                    LinkedList const & list
            ) const noexcept -> bool;

        public:
            auto clear () noexcept -> void override;
        public:
            auto makeUnique () noexcept -> void override;

        public:
            auto popFront () noexcept -> void override;
        public:
            auto popBack () noexcept -> void override;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    LinkedList const &
            ) noexcept -> LinkedList &;

        public:
            auto operator = (
                    LinkedList &&
            ) noexcept -> LinkedList &;

        public:
            template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    Collection < __OtherElementType > const & collection
            ) noexcept -> LinkedList &;

        public:
            auto sequence () & noexcept -> Sequence < LinkedList < __ElementType > >;

        public:
            auto sequence () && noexcept -> Sequence < LinkedList < __ElementType > >;

        public:
            __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < LinkedList < __ElementType > const >;

        public:
            __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < LinkedList < __ElementType > const >;

        };

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        using SingleLinkedList __CDS_Deprecated = LinkedList < __ElementType >;

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        using DoubleLinkedList __CDS_Deprecated = LinkedList < __ElementType >;

    }
}

#include "linkedList/LinkedListDelegateIterator.hpp"
#include "linkedList/LinkedListDelegateConstIterator.hpp"

#include "linkedList/impl/LinkedListDelegateIterator.hpp"
#include "linkedList/impl/LinkedListDelegateConstIterator.hpp"
#include "linkedList/impl/LinkedList.hpp"

#include "linkedList/CTAD.hpp"

#include "shared/linkedList/impl/LinkedListSequence.hpp"

#include "shared/collection/FunctionalConstructors.hpp"
#include "shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_EX_LINKED_LIST_HPP__
