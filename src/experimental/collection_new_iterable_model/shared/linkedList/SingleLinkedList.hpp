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
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > class __SingleLinkedList {                                        /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    using ElementType = __ElementType;

                public:
                    using __sll_Iterator                = UnidirectionalNodeIterator < __ElementType >;       /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __sll_ConstIterator           = UnidirectionalNodeConstIterator < __ElementType >;  /* NOLINT(bugprone-reserved-identifier) */

                public:
                    class __Dispatcher; /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using __NodeType = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    __NodeType * _pFront    { nullptr };

                private:
                    __NodeType * _pBack     { nullptr };

                private:
                    __CDS_NoDiscard auto __sll_allocateNode () const noexcept -> __NodeType *;  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __sll_freeNode (   /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType * pNode
                    ) noexcept -> void;

                protected:
                    constexpr __SingleLinkedList () noexcept; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    template <
                            typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __SingleLinkedList (                              /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList const & list
                    ) noexcept;

                protected:
                    constexpr __SingleLinkedList (          /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList && list
                    ) noexcept;

                protected:
                    auto __sll_clear () noexcept -> void;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    auto __sll_remove (                     /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __sll_remove (                     /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeConstIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    __CDS_NoDiscard auto __sll_get (    /* NOLINT(bugprone-reserved-identifier) */
                            Index index
                    ) noexcept -> ElementType *;

                protected:
                    __CDS_NoDiscard auto __sll_get (    /* NOLINT(bugprone-reserved-identifier) */
                            Index index
                    ) const noexcept -> ElementType const *;

                protected:
                    __CDS_NoDiscard auto __sll_newFront () noexcept -> ElementType *;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __sll_newBack () noexcept -> ElementType *;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    auto __sll_newFrontArray (  /* NOLINT(bugprone-reserved-identifier) */
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __sll_newBackArray (   /* NOLINT(bugprone-reserved-identifier) */
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __sll_newAddress ( /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const * pReferenceElement,
                            bool                * pNewElementCreated
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __sll_newBefore (    /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType const * pNode
                    ) noexcept -> __ElementType *;

                protected:
                    auto __sll_newArrayBefore ( /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType  const * pNode,
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard auto __sll_newBefore (      /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __sll_newBeforeConst ( /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeConstIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __sll_newAfter (       /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __sll_newAfterConst (  /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeConstIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __sll_newBeforeArray ( /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeIterator < __ElementType >        const & iterator,
                            Size                                                        count,
                            __ElementType                                            ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __sll_newBeforeArrayConst ( /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeConstIterator < __ElementType >           const & iterator,
                            Size                                                                count,
                            __ElementType                                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __sll_newAfterArray ( /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeIterator < __ElementType >        const & iterator,
                            Size                                                        count,
                            __ElementType                                            ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __sll_newAfterArrayConst ( /* NOLINT(bugprone-reserved-identifier) */
                            UnidirectionalNodeConstIterator < __ElementType >           const & iterator,
                            Size                                                                count,
                            __ElementType                                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    __CDS_NoDiscard constexpr auto __sll_begin () noexcept -> __sll_Iterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_end () noexcept -> __sll_Iterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_begin () const noexcept -> __sll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_end () const noexcept -> __sll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_cbegin () const noexcept -> __sll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __sll_cend () const noexcept -> __sll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    template <
                            typename __TElementType = __ElementType,        /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __sll_copy (
                            __SingleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    auto __sll_move (   /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList && list
                    ) noexcept -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType,        /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __sll_copyCleared (
                            __SingleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_moveCleared (  /* NOLINT(bugprone-reserved-identifier) */
                            __SingleLinkedList && list
                    ) noexcept -> void;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ */
