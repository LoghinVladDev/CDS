/*
 * Created by loghin on 17/07/22.
 */

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                            __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __SingleLinkedList {                                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                using __sll_Iterator                = UnidirectionalNodeIterator < __ElementType >;       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                using __sll_ConstIterator           = UnidirectionalNodeConstIterator < __ElementType >;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using __NodeType = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __NodeType * _pFront    { nullptr };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __NodeType * _pBack     { nullptr };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard static auto __sll_allocateNode () noexcept -> __NodeType *;     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                static auto __sll_freeNode (                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __NodeType * pNode
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                constexpr __SingleLinkedList () noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __SingleLinkedList (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __SingleLinkedList const & list
                ) noexcept;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                constexpr __SingleLinkedList (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __SingleLinkedList && list
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                ~__SingleLinkedList () noexcept = default;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator = (
                        __SingleLinkedList const & /* list */
                ) noexcept -> __SingleLinkedList & = delete;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator = (
                        __SingleLinkedList && /* list */
                ) noexcept -> __SingleLinkedList & = delete;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_clear () noexcept -> void;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __sll_empty () const noexcept -> bool;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_MaybeUnused constexpr auto __sll_front () const noexcept -> __ElementType const *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_front () noexcept -> __ElementType *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_removeFront () noexcept -> void; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_newFront () noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_newBack () noexcept -> __ElementType *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_MaybeUnused auto __sll_new (                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __sll_cbegin () const noexcept -> __sll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __sll_cend () const noexcept -> __sll_ConstIterator;     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_begin () noexcept -> __sll_Iterator;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_end () noexcept -> __sll_Iterator;     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_removeNode ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __NodeType * pPrevious,
                        __NodeType * pCurrent
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_remove ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ElementType const & value
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_removeIterator ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __sll_Iterator const & iterator
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_removeConstIterator (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __sll_ConstIterator const & iterator
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_MaybeUnused auto __sll_removeIteratorArray (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __sll_Iterator  const * const * ppIterators,
                        Size                            iteratorCount
                ) noexcept -> Size;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_removeIteratorRange (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __sll_Iterator const * pStart,
                        __sll_Iterator const * pEnd
                ) noexcept -> Size;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_removeConstIteratorArray (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __sll_ConstIterator const * const * ppIterators,
                        Size                                iteratorCount
                ) noexcept -> Size;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_removeConstIteratorRange (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __sll_ConstIterator const * pStart,
                        __sll_ConstIterator const * pEnd
                ) noexcept -> Size;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > __CDS_MaybeUnused auto __sll_copy (
                        __SingleLinkedList const & list
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto __sll_copyCleared (                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __SingleLinkedList const & list
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                auto __sll_move (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __SingleLinkedList && list
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_moveCleared (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __SingleLinkedList && list
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __sll_equals (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __SingleLinkedList const & list
                ) const noexcept -> bool;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ */
