//
// Created by loghin on 17/07/22.
//

#ifndef __CDS_SHARED_DOUBLE_LINKED_LIST_HPP__
#define __CDS_SHARED_DOUBLE_LINKED_LIST_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,                                     // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals    // NOLINT(bugprone-reserved-identifier)
                > class __DoubleLinkedList {                                        // NOLINT(bugprone-reserved-identifier)

                protected:
                    using ElementType = __ElementType;

                public:
                    using __dll_Iterator                = ForwardBidirectionalNodeIterator < __ElementType >;       // NOLINT(bugprone-reserved-identifier)

                public:
                    using __dll_ConstIterator           = ForwardBidirectionalNodeConstIterator < __ElementType >;  // NOLINT(bugprone-reserved-identifier)

                public:
                    using __dll_ReverseIterator         = BackwardBidirectionalNodeIterator < __ElementType >;      // NOLINT(bugprone-reserved-identifier)

                public:
                    using __dll_ConstReverseIterator    = BackwardBidirectionalNodeConstIterator < __ElementType >; // NOLINT(bugprone-reserved-identifier)

                public:
                    class __Dispatcher; // NOLINT(bugprone-reserved-identifier)

                private:
                    using __NodeType = cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >;  // NOLINT(bugprone-reserved-identifier)

                private:
                    __NodeType * _pFront    { nullptr };

                private:
                    __NodeType * _pBack     { nullptr };

                private:
                    __CDS_NoDiscard auto __dll_allocateNode () const noexcept -> __NodeType *;  // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __dll_freeNode (   // NOLINT(bugprone-reserved-identifier)
                            __NodeType * pNode
                    ) noexcept -> void;

                protected:
                    constexpr __DoubleLinkedList () noexcept; // NOLINT(bugprone-reserved-identifier)

                protected:
                    template <
                            typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __DoubleLinkedList (                              // NOLINT(bugprone-reserved-identifier)
                            __DoubleLinkedList const & list
                    ) noexcept;

                protected:
                    constexpr __DoubleLinkedList (          // NOLINT(bugprone-reserved-identifier)
                            __DoubleLinkedList && list
                    ) noexcept;

                protected:
                    auto __dll_clear () noexcept -> void;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __dll_remove (                     // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __dll_remove (                     // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    __CDS_NoDiscard auto __dll_get (    // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) noexcept -> ElementType *;

                protected:
                    __CDS_NoDiscard auto __dll_get (    // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) const noexcept -> ElementType const *;

                protected:
                    __CDS_NoDiscard auto __dll_newFront () noexcept -> ElementType *;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard auto __dll_newBack () noexcept -> ElementType *;    // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __dll_newFrontArray (  // NOLINT(bugprone-reserved-identifier)
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __dll_newBackArray (   // NOLINT(bugprone-reserved-identifier)
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __dll_newAddress ( // NOLINT(bugprone-reserved-identifier)
                            __ElementType const * pReferenceElement,
                            bool                * pNewElementCreated
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __dll_newBefore (    // NOLINT(bugprone-reserved-identifier)
                            __NodeType const * pNode
                    ) noexcept -> __ElementType *;

                protected:
                    auto __dll_newArrayBefore ( // NOLINT(bugprone-reserved-identifier)
                            __NodeType  const * pNode,
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard auto __dll_newBefore (      // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __dll_newBeforeConst ( // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __dll_newAfter (       // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __dll_newAfterConst (  // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __dll_newBeforeArray ( // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeIterator < __ElementType > const & iterator,
                            Size                                                        count,
                            __ElementType                                            ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __dll_newBeforeArrayConst ( // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeConstIterator < __ElementType >    const & iterator,
                            Size                                                                count,
                            __ElementType                                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __dll_newAfterArray ( // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeIterator < __ElementType > const & iterator,
                            Size                                                        count,
                            __ElementType                                            ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __dll_newAfterArrayConst ( // NOLINT(bugprone-reserved-identifier)
                            AbstractBidirectionalNodeConstIterator < __ElementType >    const & iterator,
                            Size                                                                count,
                            __ElementType                                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    __CDS_NoDiscard constexpr auto __dll_begin () noexcept -> __dll_Iterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_end () noexcept -> __dll_Iterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_begin () const noexcept -> __dll_ConstIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_end () const noexcept -> __dll_ConstIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_cbegin () const noexcept -> __dll_ConstIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_cend () const noexcept -> __dll_ConstIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_rbegin () noexcept -> __dll_ReverseIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_rend () noexcept -> __dll_ReverseIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_rbegin () const noexcept -> __dll_ConstReverseIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_rend () const noexcept -> __dll_ConstReverseIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_crbegin () const noexcept -> __dll_ConstReverseIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __dll_crend () const noexcept -> __dll_ConstReverseIterator;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    template <
                            typename __TElementType = __ElementType,        // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __dll_copy (
                            __DoubleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    auto __dll_move (   // NOLINT(bugprone-reserved-identifier)
                            __DoubleLinkedList && list
                    ) noexcept -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType,        // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __dll_copyCleared (
                            __DoubleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_moveCleared (  // NOLINT(bugprone-reserved-identifier)
                            __DoubleLinkedList && list
                    ) noexcept -> void;
                };


                template <
                        typename __ElementType,                                         // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType > __equals // NOLINT(bugprone-reserved-identifier)
                > class __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __Dispatcher : public __ListServerDispatcher <
                        cds :: experimental :: LinkedList < __ElementType >,
                        __DoubleLinkedList < __ElementType, __equals >,
                        __ElementType,
                        AbstractBidirectionalNodeIterator < __ElementType >,
                        AbstractBidirectionalNodeConstIterator < __ElementType >,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newAddress,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newFront,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newBack,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newFrontArray,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newBackArray,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newBefore,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newBeforeConst,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newAfter,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newAfterConst,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newBeforeArray,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newBeforeArrayConst,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newAfterArray,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_newAfterArrayConst,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_remove,
                        & __DoubleLinkedList < __ElementType, __equals > :: __dll_remove
                > {};

            }
        }
    }
}

#endif // __CDS_SHARED_DOUBLE_LINKED_LIST_HPP__
