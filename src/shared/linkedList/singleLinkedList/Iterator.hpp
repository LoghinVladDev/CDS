//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_ITERATOR_HPP__
#define __CDS_SHARED_SINGLE_LINKED_LIST_ITERATOR_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > class __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator {

            private:
                using SingleLinkedList = __SingleLinkedList <
                        __ElementType,
                        __ElementEquals,
                        __ElementDestruct
                >;

            private:
                using NodeType = typename SingleLinkedList :: __NodeType;

            private:
                NodeType * _pPrevious { nullptr };

            private:
                NodeType * _pCurrent { nullptr };

            public:
                constexpr SingleLinkedListIterator () noexcept;

            public:
                constexpr SingleLinkedListIterator (
                        NodeType * pPrevious,
                        NodeType * pCurrent
                ) noexcept;

            public:
                constexpr SingleLinkedListIterator (
                        SingleLinkedListIterator const & iterator
                ) noexcept;

            public:
                constexpr SingleLinkedListIterator (
                        SingleLinkedListIterator && iterator
                ) noexcept;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        SingleLinkedListIterator const & iterator
                ) noexcept -> SingleLinkedListIterator &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        SingleLinkedListIterator && iterator
                ) noexcept -> SingleLinkedListIterator &;

            public:
                __CDS_NoDiscard constexpr auto currentNode () const noexcept -> NodeType *;

            public:
                __CDS_NoDiscard constexpr auto previousNode () const noexcept -> NodeType *;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> SingleLinkedListIterator &;

            public:
                __CDS_NoDiscard constexpr auto operator * () const noexcept -> SingleLinkedList :: ElementType &;

            public:
                __CDS_NoDiscard constexpr auto operator == (
                        SingleLinkedListIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard constexpr auto operator != (
                        SingleLinkedListIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
            };

        }
    }
}

#endif // __CDS_SHARED_SINGLE_LINKED_LIST_ITERATOR_HPP__
