//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_HPP__
#define __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class LinkedList < __ElementType > :: LinkedListDelegateIterator : public LinkedList < __ElementType > :: DelegateIterator {

        private:
            LinkedList < __ElementType > :: Node      * _pNode;

        private:
            bool                                        _forward;

        public:
            constexpr LinkedListDelegateIterator (
                    LinkedList < __ElementType > :: Node  * pNode,
                    bool                                    forward
            ) noexcept;

        public:
            constexpr LinkedListDelegateIterator (
                    LinkedListDelegateIterator const & iterator
            ) noexcept;

        public:
            constexpr LinkedListDelegateIterator (
                    LinkedListDelegateIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~LinkedListDelegateIterator () noexcept override = default;

        public:
            __CDS_NoDiscard constexpr auto node () const noexcept -> LinkedList < __ElementType > :: Node *;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;

        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> LinkedListDelegateIterator & override;

        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> LinkedListDelegateIterator & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                    AbstractDelegateIterator const & iterator
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard auto copy () const noexcept -> LinkedListDelegateIterator * override;
        };

    }
}

#endif // __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_HPP__
