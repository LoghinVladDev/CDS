/*
 * Created by loghin on 02/10/22.
 */

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__
#define __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_allocateNode () noexcept -> __NodeType * {

                    return cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __NodeType > ();
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_freeNode (
                        __NodeType * pNode
                ) noexcept -> void {

                    pNode->_data.~__ElementType ();
                    return cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __SingleLinkedList () noexcept = default;


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __SingleLinkedList (
                        __SingleLinkedList const & list
                ) noexcept {

                    this->__sll_copyCleared ( list );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __SingleLinkedList (
                        __SingleLinkedList && list
                ) noexcept :
                        _pFront ( cds :: exchange ( list._pFront, nullptr ) ),
                        _pBack ( cds :: exchange ( list._pBack, nullptr ) ) {

                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_clear () noexcept -> void {

                    while ( this->_pFront != nullptr ) {
                        auto pCopy      = this->_pFront;
                        this->_pFront   = this->_pFront->_pNext;
                        __SingleLinkedList :: __sll_freeNode ( pCopy );
                    }

                    this->_pBack = nullptr;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_empty () const noexcept -> bool {

                    return this->_pFront == nullptr;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_front () const noexcept -> __ElementType const * {

                    return this->_pFront;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_front () noexcept -> __ElementType * {

                    return this->_pFront;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_removeFront () noexcept -> void {

                    if ( this->__sll_empty() ) {
                        return;
                    }

                    auto pCopy      = this->_pFront;
                    this->_pFront   = this->_pFront->_pNext;
                    __SingleLinkedList :: __sll_freeNode ( pCopy );

                    if ( this->_pFront == nullptr ) {
                        this->_pBack = nullptr;
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_newFront () noexcept -> __ElementType * {

                    auto pNewNode       = __SingleLinkedList :: __sll_allocateNode();
                    pNewNode->_pNext    = this->_pFront;
                    this->_pFront       = pNewNode;

                    if ( this->_pBack == nullptr ) {
                        this->_pBack = pNewNode;
                    }

                    return & pNewNode->_data;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_newBack () noexcept -> __ElementType * {

                    if ( this->__sll_empty() ) {
                        return this->__sll_newFront();
                    }

                    auto pNewNode           = __SingleLinkedList :: __sll_allocateNode();
                    this->_pBack->_pNext    = pNewNode;
                    this->_pBack            = pNewNode;
                    this->_pBack->_pNext    = nullptr;

                    return & pNewNode->_data;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_new (
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> __ElementType * {

                    (void) pReferenceElement;
                    * pNewElementCreated = true;

                    return this->__sll_newBack ();
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_cbegin () const noexcept -> __sll_ConstIterator {

                    return __sll_ConstIterator (
                            nullptr,
                            this->_pFront
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_cend () const noexcept -> __sll_ConstIterator {

                    return __sll_ConstIterator (
                            this->_pBack,
                            nullptr
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_begin () noexcept -> __sll_Iterator {

                    return __sll_Iterator (
                            nullptr,
                            this->_pFront
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_end () noexcept -> __sll_Iterator {

                    return __sll_Iterator (
                            this->_pBack,
                            nullptr
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_removeNode (
                        __NodeType * pPrevious,
                        __NodeType * pCurrent
                ) noexcept -> void {

                    auto pNext = pCurrent->_pNext;
                    pPrevious->_pNext = pNext;
                    __SingleLinkedList :: __sll_freeNode ( pCurrent );

                    if ( pNext == nullptr ) {
                        this->_pBack = pPrevious;
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_remove (
                        __ElementType const & value
                ) noexcept -> bool {

                    if ( this->__sll_empty() ) {
                        return false;
                    }

                    if ( __equals ( this->_pFront->_data, value ) ) {
                        this->__sll_removeFront();
                        return true;
                    }

                    auto pPrevious = this->_pFront;
                    while ( pPrevious->_pNext != nullptr ) {
                        if ( __equals ( pPrevious->_pNext->_data, value ) ) {
                            this->__sll_removeNode ( pPrevious, pPrevious->_pNext );
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_removeIterator (
                        __sll_Iterator const & iterator
                ) noexcept -> bool {

                    if ( this->__sll_empty() || iterator == this->__sll_end() ) {
                        return false;
                    }

                    if ( this->__sll_begin() == iterator ) {
                        this->__sll_removeFront();
                    } else {
                        this->__sll_removeNode (
                                iterator._pPreviousNode,
                                iterator._pCurrentNode
                        );
                    }

                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_removeConstIterator (
                        __sll_ConstIterator const & iterator
                ) noexcept -> bool {

                    if ( this->__sll_empty() || iterator == this->__sll_cend() ) {
                        return false;
                    }

                    if ( this->__sll_cbegin() == iterator ) {
                        this->__sll_removeFront();
                    } else {
                        this->__sll_removeNode (
                                const_cast < __NodeType * > ( iterator._pPreviousNode ),
                                const_cast < __NodeType * > ( iterator._pCurrentNode )
                        );
                    }

                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_removeConstIteratorRange (
                        __sll_ConstIterator const * pStart,
                        __sll_ConstIterator const * pEnd
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    auto pKeepStartNode = const_cast < __NodeType * > ( pStart->_pPreviousNode );
                    auto pKeepEndNode   = const_cast < __NodeType * > ( pEnd->_pCurrentNode->_pNext );

                    auto pSeek          = const_cast < __NodeType * > ( pStart->_pCurrentNode );
                    while ( pSeek != pKeepEndNode ) {

                        auto pRemoveCopy = pSeek;
                        pSeek = pSeek->_pNext;
                        __SingleLinkedList :: __sll_freeNode ( pRemoveCopy );
                        ++ removedCount;
                    }

                    if ( pKeepStartNode != nullptr ) {
                        pKeepStartNode->_pNext  = pKeepEndNode;
                    } else {
                        this->_pFront           = pKeepEndNode;
                    }

                    if ( pKeepEndNode == nullptr ) {
                        this->_pBack            = pKeepStartNode == nullptr ? this->_pFront : pKeepStartNode->_pNext;
                    }

                    return removedCount;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_removeConstIteratorArray (
                        __sll_ConstIterator const * const * ppIterators,
                        Size                                iteratorCount
                ) noexcept -> Size {

                    Size removedCount = 0U;
                    while ( iteratorCount > 0 && & ( * ( * ppIterators [0U] ) ) == & this->_pFront->_data ) {
                        this->__sll_removeFront();
                        ++ ppIterators;
                        ++ removedCount;
                        -- iteratorCount;
                    }

                    if ( iteratorCount == 0U ) {
                        return removedCount;
                    }

                    __sll_ConstIterator const * pStartRange    = ppIterators [ 0U ];
                    __sll_ConstIterator const * pEndRange      = ppIterators [ 0U ];

                    for ( Size index = 1U; index < iteratorCount; ++ index ) {

                        if ( pEndRange->_pCurrentNode == ppIterators [ index ]->_pPreviousNode ) {
                            pEndRange = ppIterators [ index ];
                        } else if ( pStartRange == pEndRange ) {
                            if ( this->__sll_removeConstIterator ( * pStartRange ) ) {
                                ++ removedCount;
                            }

                            pStartRange = ppIterators [ index ];
                            pEndRange   = ppIterators [ index ];
                        } else {

                            removedCount += this->__sll_removeConstIteratorRange ( pStartRange, pEndRange );
                        }
                    }

                    if ( pStartRange == pEndRange ) {
                        if ( this->__sll_removeConstIterator ( * pStartRange ) ) {
                            ++ removedCount;
                        }
                    } else {

                        removedCount += this->__sll_removeConstIteratorRange ( pStartRange, pEndRange );
                    }

                    return removedCount;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > auto __SingleLinkedList <
                        __ElementType,
                        __equals
                > :: __sll_copyCleared (
                        __SingleLinkedList const & list
                ) noexcept -> void {

                    auto pOtherHead = list._pFront;
                    while ( pOtherHead != nullptr ) {

                        auto pNewNode           = __SingleLinkedList :: __sll_allocateNode();
                        new ( & pNewNode->_data ) __ElementType ( pOtherHead->_data );
                        pNewNode->_pNext        = nullptr;

                        if ( this->_pBack == nullptr ) {
                            this->_pFront = pNewNode;
                        } else {
                            this->_pBack->_pNext = pNewNode;
                        }

                        this->_pBack = pNewNode;
                        pOtherHead = pOtherHead->_pNext;
                    }
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__ */
