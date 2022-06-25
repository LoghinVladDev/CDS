//
// Created by loghin on 6/24/22.
//

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_HPP__
#define __CDS_SHARED_SINGLE_LINKED_LIST_HPP__

#include "../memory/PrimitiveAllocation.hpp"

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,       // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct      // NOLINT(bugprone-reserved-identifier)
            > class __SingleLinkedList {            // NOLINT(bugprone-reserved-identifier)

            protected:
                using ElementType = __ElementType;

            protected:
                using ElementEquals = __ElementEquals;

            protected:
                using ElementDestruct = __ElementDestruct;

            protected:
                class SingleLinkedListIterator;

            protected:
                class SingleLinkedListConstIterator;

            private:
                using __DataType = __hidden :: __impl :: __allocation :: __RawContainer < ElementType >;    // NOLINT(bugprone-reserved-identifier)

            private:
                using __NodeType = __UnidirectionalNode < __DataType >; // NOLINT(bugprone-reserved-identifier)

            private:
                __CDS_NoUniqueAddress __ElementEquals   _equals;

            private:
                __CDS_NoUniqueAddress __ElementDestruct _destruct;

            private:
                __NodeType * _pFront { nullptr };

            private:
                __NodeType * _pBack { nullptr };

            private:
                __CDS_NoDiscard auto __sll_allocateNode () const noexcept -> __NodeType *; // NOLINT(bugprone-reserved-identifier)

            private:
                auto __sll_freeNode ( // NOLINT(bugprone-reserved-identifier)
                        __NodeType * pNode
                ) noexcept -> void;

            protected:
                __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_begin () noexcept -> SingleLinkedListIterator; // NOLINT(bugprone-reserved-identifier)

            protected:
                __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_end () noexcept -> SingleLinkedListIterator; // NOLINT(bugprone-reserved-identifier)

            protected:
                constexpr auto __sll_cbegin () const noexcept -> SingleLinkedListConstIterator; // NOLINT(bugprone-reserved-identifier)

            protected:
                constexpr auto __sll_cend () const noexcept -> SingleLinkedListConstIterator; // NOLINT(bugprone-reserved-identifier)

            protected:
                constexpr __SingleLinkedList () noexcept; // NOLINT(bugprone-reserved-identifier)

            protected:
                template < typename __ElementCopy > // NOLINT(bugprone-reserved-identifier)
                __SingleLinkedList (                // NOLINT(bugprone-reserved-identifier)
                        __SingleLinkedList  const & list,
                        __ElementCopy       const & copyFunction
                ) noexcept;

            protected:
                constexpr __SingleLinkedList ( // NOLINT(bugprone-reserved-identifier)
                        __SingleLinkedList && list
                ) noexcept;

            protected:
                auto __sll_clear () noexcept -> void; // NOLINT(bugprone-reserved-identifier)

            protected:
                __CDS_NoDiscard constexpr auto __sll_empty () const noexcept -> bool; // NOLINT(bugprone-reserved-identifier)

            protected:
                __CDS_NoDiscard auto __sll_newFront () noexcept -> __ElementType *; // NOLINT(bugprone-reserved-identifier)

            protected:
                __CDS_NoDiscard auto __sll_newBack () noexcept -> __ElementType *; // NOLINT(bugprone-reserved-identifier)

            protected:
                auto __sll_remove ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType const & element
                ) noexcept -> bool;

            protected:
                auto __sll_remove ( // NOLINT(bugprone-reserved-identifier)
                        SingleLinkedListIterator const & iterator
                ) noexcept -> bool;

            protected:
                auto __sll_remove ( // NOLINT(bugprone-reserved-identifier)
                        SingleLinkedListConstIterator const & iterator
                ) noexcept -> bool;

            protected:
                auto __sll_equals ( // NOLINT(bugprone-reserved-identifier)
                        __SingleLinkedList const & list
                ) const noexcept -> bool;

            protected:
                template < typename __ElementCopy > // NOLINT(bugprone-reserved-identifier)
                auto __sll_copyFrom (               // NOLINT(bugprone-reserved-identifier)
                        __SingleLinkedList  const & list,
                        __ElementCopy       const & copyFunction
                ) noexcept -> void;

            protected:
                constexpr auto __sll_moveFrom ( // NOLINT(bugprone-reserved-identifier)
                        __SingleLinkedList && list
                ) noexcept -> void;

            protected:
                template < typename __ElementCopy > // NOLINT(bugprone-reserved-identifier)
                auto __sll_assign (                 // NOLINT(bugprone-reserved-identifier)
                        __SingleLinkedList  const & list,
                        __ElementCopy       const & copyFunction
                ) noexcept -> void;

            protected:
                auto __sll_assign ( // NOLINT(bugprone-reserved-identifier)
                        __SingleLinkedList && list
                ) noexcept -> void;
            };

        }
    }
}

#include "singleLinkedList/Iterator.hpp"
#include "singleLinkedList/ConstIterator.hpp"

#include "singleLinkedList/impl/Iterator.hpp"
#include "singleLinkedList/impl/ConstIterator.hpp"
#include "singleLinkedList/impl/SingleLinkedList.hpp"

#endif // __CDS_SHARED_SINGLE_LINKED_LIST_HPP__
