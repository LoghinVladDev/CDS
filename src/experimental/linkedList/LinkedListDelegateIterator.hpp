//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_HPP__
#define __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class LinkedList < T > :: LinkedListDelegateIterator : public LinkedList < T > :: DelegateIterator {
        private:
            ForeignPointer < LinkedList < T > :: Node > _pNode;
        private:
            bool                                        _forward;

        public:
            constexpr LinkedListDelegateIterator ( LinkedList < T > :: Node *, bool ) noexcept;
        public:
            constexpr LinkedListDelegateIterator ( LinkedListDelegateIterator const & ) noexcept;
        public:
            constexpr LinkedListDelegateIterator ( LinkedListDelegateIterator && ) noexcept;
        public:
            __CDS_cpplang_ConstexprDestructor ~LinkedListDelegateIterator () noexcept = default;

        public:
            __CDS_NoDiscard constexpr auto node () const noexcept -> LinkedList < T > :: Node *;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;
        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> LinkedListDelegateIterator & override;
        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> LinkedListDelegateIterator & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( AbstractDelegateIterator const & ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> LinkedListDelegateIterator * override;
        };

    }
}

#endif // __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_HPP__
