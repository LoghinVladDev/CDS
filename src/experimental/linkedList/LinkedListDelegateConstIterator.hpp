//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class LinkedList < T > :: LinkedListDelegateConstIterator : public LinkedList < T > :: DelegateConstIterator {
        private:
            ForeignPointer < LinkedList < T > :: Node const >   _pNode;
        private:
            bool                                                _forward;

        public:
            constexpr LinkedListDelegateConstIterator ( LinkedList < T > :: Node const *, bool ) noexcept;
        public:
            constexpr LinkedListDelegateConstIterator ( LinkedListDelegateConstIterator const & ) noexcept;
        public:
            constexpr LinkedListDelegateConstIterator ( LinkedListDelegateConstIterator && ) noexcept;
        public:
            __CDS_cpplang_ConstexprDestructor ~LinkedListDelegateConstIterator () noexcept = default;

        public:
            __CDS_NoDiscard constexpr auto node () const noexcept -> LinkedList < T > :: Node const *;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;
        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> LinkedListDelegateConstIterator & override;
        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> LinkedListDelegateConstIterator & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementType const & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( AbstractDelegateIterator const & ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> LinkedListDelegateConstIterator * override;
        };

    }
}

#endif // __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_HPP__
