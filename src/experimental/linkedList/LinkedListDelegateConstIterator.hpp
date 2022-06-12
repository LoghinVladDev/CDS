//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class LinkedList < __ElementType > :: LinkedListDelegateConstIterator : public LinkedList < __ElementType > :: DelegateConstIterator {

        private:
            LinkedList < __ElementType > :: Node        const * _pNode;

        private:
            bool                                                _forward;

        public:
            constexpr LinkedListDelegateConstIterator (
                    LinkedList < __ElementType > :: Node    const * pNode,
                    bool                                            forward
            ) noexcept;

        public:
            constexpr LinkedListDelegateConstIterator (
                    LinkedListDelegateConstIterator const & iterator
            ) noexcept;

        public:
            constexpr LinkedListDelegateConstIterator (
                    LinkedListDelegateConstIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~LinkedListDelegateConstIterator () noexcept = default;

        public:
            __CDS_NoDiscard constexpr auto node () const noexcept -> LinkedList < __ElementType > :: Node const *;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;

        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> LinkedListDelegateConstIterator & override;

        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> LinkedListDelegateConstIterator & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                    AbstractDelegateIterator const & iterator
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> LinkedListDelegateConstIterator * override;
        };

    }
}

#endif // __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_HPP__
