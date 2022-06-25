//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_CONST_ITERATOR_HPP__
#define __CDS_SHARED_SINGLE_LINKED_LIST_CONST_ITERATOR_HPP__

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
            > :: SingleLinkedListConstIterator {

            private:
                using SingleLinkedList = __SingleLinkedList <
                        __ElementType,
                        __ElementEquals,
                        __ElementDestruct
                >;

            private:
                using NodeType = typename SingleLinkedList :: __NodeType;

            private:
                NodeType const * _pPrevious { nullptr };

            private:
                NodeType const * _pCurrent { nullptr };

            public:
                constexpr SingleLinkedListConstIterator () noexcept;

            public:
                constexpr SingleLinkedListConstIterator (
                        NodeType const * pPrevious,
                        NodeType const * pCurrent
                ) noexcept;

            public:
                constexpr SingleLinkedListConstIterator (
                        SingleLinkedListConstIterator const & iterator
                ) noexcept;

            public:
                constexpr SingleLinkedListConstIterator (
                        SingleLinkedListConstIterator && iterator
                ) noexcept;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        SingleLinkedListConstIterator const & iterator
                ) noexcept -> SingleLinkedListConstIterator &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        SingleLinkedListConstIterator && iterator
                ) noexcept -> SingleLinkedListConstIterator &;

            public:
                __CDS_NoDiscard constexpr auto currentNode () const noexcept -> NodeType const *;

            public:
                __CDS_NoDiscard constexpr auto previousNode () const noexcept -> NodeType const *;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> SingleLinkedListConstIterator &;

            public:
                __CDS_NoDiscard constexpr auto operator * () const noexcept -> SingleLinkedList :: ElementType const &;

            public:
                __CDS_NoDiscard constexpr auto operator == (
                        SingleLinkedListConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard constexpr auto operator != (
                        SingleLinkedListConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
            };

        }
    }
}

#endif // __CDS_SHARED_SINGLE_LINKED_LIST_CONST_ITERATOR_HPP__
