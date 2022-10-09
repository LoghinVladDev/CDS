/*
 * Created by loghin on 17/07/22.
 */

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_HPP__
#define __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > class __SingleLinkedList {                                            /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    using ElementType = __ElementType;

                public:
                    using __sll_Iterator                = UnidirectionalNodeIterator < __ElementType >;       /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __sll_ConstIterator           = UnidirectionalNodeConstIterator < __ElementType >;  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using __NodeType = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    __NodeType * _pFront    { nullptr };

                private:
                    __NodeType * _pBack     { nullptr };

                private:
                    __CDS_NoDiscard static auto __sll_allocateNode () noexcept -> __NodeType *;     /* NOLINT(bugprone-reserved-identifier) */

                private:
                    static auto __sll_freeNode (                                                    /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType * pNode
                    ) noexcept -> void;

                protected:
                    constexpr __SingleLinkedList () noexcept; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __SingleLinkedList (    /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList const & list
                    ) noexcept;

                protected:
                    constexpr __SingleLinkedList (  /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList && list
                    ) noexcept;

                protected:
                    auto __sll_clear () noexcept -> void;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_empty () const noexcept -> bool;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_front () const noexcept -> __ElementType const *;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_front () noexcept -> __ElementType *;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    auto __sll_removeFront () noexcept -> void; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    auto __sll_newFront () noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    auto __sll_newBack () noexcept -> __ElementType *;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    auto __sll_new (                                    /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const * pReferenceElement,
                            bool                * pNewElementCreated
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard constexpr auto __sll_cbegin () const noexcept -> __sll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_cend () const noexcept -> __sll_ConstIterator;     /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_begin () noexcept -> __sll_Iterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_end () noexcept -> __sll_Iterator;     /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    auto __sll_removeNode ( /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType * pPrevious,
                            __NodeType * pCurrent
                    ) noexcept -> void;

                protected:
                    auto __sll_remove ( /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const & value
                    ) noexcept -> bool;

                protected:
                    auto __sll_removeIterator ( /* NOLINT(bugprone-reserved-identifier) */
                            __sll_Iterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __sll_removeConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
                            __sll_ConstIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __sll_removeIteratorArray (    /* NOLINT(bugprone-reserved-identifier) */
                            __sll_Iterator  const * const * ppIterators,
                            Size                            iteratorCount
                    ) noexcept -> Size;

                private:
                    auto __sll_removeIteratorRange (   /* NOLINT(bugprone-reserved-identifier) */
                            __sll_Iterator const * pStart,
                            __sll_Iterator const * pEnd
                    ) noexcept -> Size;

                protected:
                    auto __sll_removeConstIteratorArray (   /* NOLINT(bugprone-reserved-identifier) */
                            __sll_ConstIterator const * const * ppIterators,
                            Size                                iteratorCount
                    ) noexcept -> Size;

                private:
                    auto __sll_removeConstIteratorRange (   /* NOLINT(bugprone-reserved-identifier) */
                            __sll_ConstIterator const * pStart,
                            __sll_ConstIterator const * pEnd
                    ) noexcept -> Size;

                protected:
                    template <
                            typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __sll_copy (
                            __SingleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __sll_copyCleared (                          /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    auto __sll_move (   /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList && list
                    ) noexcept -> void;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_moveCleared (  /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList && list
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __sll_equals (  /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList const & list
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ */
