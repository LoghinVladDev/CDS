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

                public:
                    template < typename __ServerType >  /* NOLINT(bugprone-reserved-identifier) */
                    class __Dispatcher;                 /* NOLINT(bugprone-reserved-identifier) */

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
                    __CDS_NoDiscard constexpr auto __sll_empty () const noexcept -> bool;

                protected:
                    __CDS_NoDiscard constexpr auto __sll_front () const noexcept -> __ElementType const *;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_front () noexcept -> __ElementType *;

                protected:
                    auto __sll_removeFront () noexcept -> void;

                protected:
                    auto __sll_newFront () noexcept -> __ElementType *;

                protected:
                    auto __sll_newBack () noexcept -> __ElementType *;

                protected:
                    auto __sll_new ( __ElementType const *, bool * ) -> __ElementType *;

                protected:
                    __CDS_NoDiscard constexpr auto __sll_cbegin () const noexcept -> __sll_ConstIterator;

                protected:
                    __CDS_NoDiscard constexpr auto __sll_cend () const noexcept -> __sll_ConstIterator;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_begin () noexcept -> __sll_Iterator;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_end () noexcept -> __sll_Iterator;

                protected:
                    auto __sll_removeIterator (
                            UnidirectionalNodeIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __sll_removeConstIterator (
                            UnidirectionalNodeConstIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __sll_removeIteratorArray (
                            UnidirectionalNodeIterator < __ElementType >    const * const * ppIterators,
                            Size                                                            iteratorCount
                    ) noexcept -> Size;

                protected:
                    auto __sll_removeConstIteratorArray (
                            UnidirectionalNodeConstIterator < __ElementType >   const * const * ppIterators,
                            Size                                                                iteratorCount
                    ) noexcept -> Size;

                protected:
                    template <
                            typename __TElementType = __ElementType,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __sll_copy (
                            __SingleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __sll_copyCleared (
                            __SingleLinkedList const & list
                    ) noexcept -> void;

                protected:
                    auto __sll_move (
                            __SingleLinkedList && list
                    ) noexcept -> void;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_moveCleared (
                            __SingleLinkedList && list
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __sll_equals (
                            __SingleLinkedList const & list
                    ) const noexcept -> bool;
                };


                template <
                        typename                                                __ElementType,
                        cds :: utility :: ComparisonFunction < __ElementType >  __equals
                > template <
                        typename                                                __ServerType
                > class __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __Dispatcher :
                        public __MutableCollectionServerDispatcher <
                                __ServerType,
                                __SingleLinkedList < __ElementType, __equals >,
                                __ElementType,
                                UnidirectionalNodeIterator < __ElementType >,
                                UnidirectionalNodeConstIterator < __ElementType >,
                                UnidirectionalNodeIterator < __ElementType >,
                                UnidirectionalNodeConstIterator < __ElementType >,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_begin,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_end,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_cbegin,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_cend,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_new,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_removeIterator,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_removeConstIterator,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_removeIteratorArray,
                                & __SingleLinkedList < __ElementType, __equals > :: __sll_removeConstIteratorArray
                        > {};

            }
        }
    }
}

#endif /* __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ */
