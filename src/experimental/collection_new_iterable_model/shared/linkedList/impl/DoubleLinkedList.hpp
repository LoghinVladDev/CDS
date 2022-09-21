/*
 * Created by loghin on 18/07/22.
 */

#ifndef __CDS_SHARED_DOUBLE_LINKED_LIST_IMPL_HPP__
#define __CDS_SHARED_DOUBLE_LINKED_LIST_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_allocateNode () noexcept -> __NodeType * {

                    return cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __NodeType > ();
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_freeNode (
                        __NodeType * pNode
                ) noexcept -> void {

                    pNode->_data.~__ElementType ();
                    return cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __DoubleLinkedList () noexcept = default;


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __DoubleLinkedList (
                        __DoubleLinkedList const & list
                ) noexcept {

                    this->__dll_copyCleared ( list );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __DoubleLinkedList (
                        __DoubleLinkedList && list
                ) noexcept :
                        _pFront ( cds :: exchange ( list._pFront, nullptr ) ),
                        _pBack  ( cds :: exchange ( list._pBack, nullptr ) ),
                        _size ( cds :: exchange ( list._size, 0ULL ) ){

                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_clear () noexcept -> void {

                    while ( this->_pFront != nullptr ) {
                        auto pCopy      = this->_pFront;
                        this->_pFront   = this->_pFront->_pNext;
                        __DoubleLinkedList :: __dll_freeNode ( pCopy );
                    }

                    this->_pBack = nullptr;
                    this->_size = 0ULL;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_empty () const noexcept -> bool {

                    return this->_pFront == nullptr;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_size () const noexcept -> Size {

                    return this->_size;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_front () const noexcept -> __ElementType const * {

                    return this->_pFront == nullptr ? nullptr : & this->_pFront->_data;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_back () const noexcept -> __ElementType const * {

                    return this->_pBack == nullptr ? nullptr : & this->_pBack->_data;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_front () noexcept -> __ElementType * {

                    return this->_pFront == nullptr ? nullptr : & this->_pFront->_data;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_back () noexcept -> __ElementType * {

                    return this->_pBack == nullptr ? nullptr : & this->_pBack->_data;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_removeFront () noexcept -> void {

                    if ( this->__dll_empty() ) {
                        return;
                    }

                    auto pCopy = this->_pFront;
                    this->_pFront = this->_pFront->_pNext;
                    __DoubleLinkedList :: __dll_freeNode ( pCopy );

                    if ( this->_pFront == nullptr ) {
                        this->_pBack = nullptr;
                    } else {
                        this->_pFront->_pPrevious = nullptr;
                    }

                    -- this->_size;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_removeBack () noexcept -> void {

                    if ( this->__dll_empty() ) {
                        return;
                    }

                    auto pCopy = this->_pBack;
                    this->_pBack = this->_pBack->_pPrevious;
                    __DoubleLinkedList :: __dll_freeNode ( pCopy );

                    if ( this->_pBack == nullptr ) {
                        this->_pFront = nullptr;
                    } else {
                        this->_pBack->_pNext = nullptr;
                    }

                    -- this->_size;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_removeIterator (
                        AbstractBidirectionalNodeIterator < __ElementType > const & iterator
                ) noexcept -> bool {

                    if ( iterator._pCurrentNode == nullptr ) {
                        return false;
                    }

                    if ( iterator._pCurrentNode == this->_pFront ) {
                        this->__dll_removeFront();
                        return true;
                    }

                    if ( iterator._pCurrentNode == this->_pBack ) {
                        this->__dll_removeBack();
                        return true;
                    }

                    auto pNode = iterator._pCurrentNode;
                    pNode->_pPrevious->_pNext = pNode->_pNext;
                    pNode->_pNext->_pPrevious = pNode->_pPrevious;
                    __DoubleLinkedList :: __dll_freeNode ( pNode );
                    -- this->_size;

                    return true;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_removeConstIterator (
                        AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
                ) noexcept -> bool {

                    if ( iterator._pCurrentNode == nullptr ) {
                        return false;
                    }

                    if ( iterator._pCurrentNode == this->_pFront ) {
                        this->__dll_removeFront();
                        return true;
                    }

                    if ( iterator._pCurrentNode == this->_pBack ) {
                        this->__dll_removeBack();
                        return true;
                    }

                    auto pNode = const_cast < __NodeType * > ( iterator._pCurrentNode );
                    pNode->_pPrevious->_pNext = pNode->_pNext;
                    pNode->_pNext->_pPrevious = pNode->_pPrevious;
                    __DoubleLinkedList :: __dll_freeNode ( pNode );
                    -- this->_size;

                    return true;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_removeIteratorArray (
                        AbstractBidirectionalNodeIterator < __ElementType > const * const * ppIterators,
                        Size                                                                iteratorCount
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                        if ( this->__dll_removeIterator ( * ppIterators [ index ] ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_removeConstIteratorArray (
                        AbstractBidirectionalNodeConstIterator < __ElementType >    const * const * ppIterators,
                        Size                                                                        iteratorCount
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                        if ( this->__dll_removeConstIterator ( * ppIterators [ index ] ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_removeAt (
                        Index index
                ) noexcept -> void {

                    if ( this->__dll_empty() ) {
                        return;
                    }

                    Index current = 0;
                    auto pHead = this->_pFront;
                    __NodeType * pToRemove = nullptr;

                    while ( pHead != nullptr ) {
                        if ( current == index ) {
                            pToRemove = pHead;
                            break;
                        }

                        pHead = pHead->_pNext;
                        ++ current;
                    }

                    pToRemove->_pPrevious->_pNext = pToRemove->_pNext;
                    pToRemove->_pNext->_pPrevious = pToRemove->_pPrevious;

                    __DoubleLinkedList :: __dll_freeNode ( pToRemove );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_get (
                        Index index
                ) noexcept -> __ElementType * {

                    if ( this->__dll_empty() ) {
                        return nullptr;
                    }

                    Index current = 0;
                    auto pHead = this->_pFront;

                    while ( pHead != nullptr ) {
                        if ( current == index ) {
                            return & pHead->_data;
                        }

                        pHead = pHead->_pNext;
                        ++ current;
                    }

                    return nullptr;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_get (
                        Index index
                ) const noexcept -> __ElementType const * {

                    if ( this->__dll_empty() ) {
                        return nullptr;
                    }

                    Index current = 0;
                    auto pHead = this->_pFront;

                    while ( pHead != nullptr ) {
                        if ( current == index ) {
                            return & pHead->_data;
                        }

                        pHead = pHead->_pNext;
                        ++ current;
                    }

                    return nullptr;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newFront () noexcept -> __ElementType * {

                    __NodeType * pNewNode   = __DoubleLinkedList :: __dll_allocateNode();
                    pNewNode->_pNext        = this->_pFront;
                    pNewNode->_pPrevious    = nullptr;

                    if ( this->_pFront != nullptr ) {
                        this->_pFront->_pPrevious = pNewNode;
                    }

                    this->_pFront = pNewNode;

                    if ( this->_pBack == nullptr ) {
                        this->_pBack = pNewNode;
                    }

                    ++ this->_size;
                    return & pNewNode->_data;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBack () noexcept -> __ElementType * {

                    __NodeType * pNewNode   = __DoubleLinkedList :: __dll_allocateNode();
                    pNewNode->_pPrevious    = this->_pBack;
                    pNewNode->_pNext        = nullptr;

                    if ( this->_pBack != nullptr ) {
                        this->_pBack->_pNext = pNewNode;
                    }

                    this->_pBack = pNewNode;

                    if ( this->_pFront == nullptr ) {
                        this->_pFront = pNewNode;
                    }

                    ++ this->_size;
                    return & pNewNode->_data;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newFrontArray (
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void {

                    if ( count == 0U ) {
                        return;
                    }

                    __NodeType * pChainFront        = __DoubleLinkedList :: __dll_allocateNode();
                    __NodeType * pChainPrevious     = pChainFront;
                    __NodeType * pChainCurrent      = pChainPrevious;

                    pChainPrevious->_pPrevious      = nullptr;

                    for ( Size index = 0U; index + 1U < count; ++ index ) {
                        ppElements [ index ]        = & pChainPrevious->_data;
                        pChainCurrent               = __DoubleLinkedList :: __dll_allocateNode();

                        pChainPrevious->_pNext      = pChainCurrent;
                        pChainCurrent->_pPrevious   = pChainPrevious;

                        pChainPrevious              = pChainCurrent;
                    }

                    ppElements [ count - 1U ] = & pChainCurrent->_data;

                    pChainCurrent->_pNext     = this->_pFront;

                    if ( this->_pFront != nullptr ) {
                        this->_pFront->_pPrevious = pChainCurrent;
                    }

                    this->_pFront = pChainFront;

                    if ( this->_pBack == nullptr ) {
                        this->_pBack = pChainCurrent;
                    }

                    this->_size += count;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBackArray (
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void {

                    if ( count == 0U ) {
                        return;
                    }

                    __NodeType * pChainFront        = __DoubleLinkedList :: __dll_allocateNode();
                    __NodeType * pChainPrevious     = pChainFront;
                    __NodeType * pChainCurrent      = pChainPrevious;

                    for ( Size index = 0U; index + 1U < count; ++ index ) {
                        ppElements [ index ]        = & pChainPrevious->_data;
                        pChainCurrent               = __DoubleLinkedList :: __dll_allocateNode();

                        pChainPrevious->_pNext      = pChainCurrent;
                        pChainCurrent->_pPrevious   = pChainPrevious;

                        pChainPrevious              = pChainCurrent;
                    }

                    ppElements [ count - 1U ] = & pChainCurrent->_data;

                    pChainFront->_pPrevious   = this->_pBack;

                    if ( this->_pBack != nullptr ) {
                        this->_pBack->_pNext = pChainFront;
                    }

                    pChainCurrent->_pNext = nullptr;
                    this->_pBack = pChainCurrent;

                    if ( this->_pFront == nullptr ) {
                        this->_pFront = pChainFront;
                    }

                    this->_size += count;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newAddress (
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> __ElementType * {

                    (void) pReferenceElement;
                    * pNewElementCreated = true;

                    return this->__dll_newBack();
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBetweenNodes (
                        __NodeType  const * pPrevious,
                        __NodeType  const * pCurrent
                ) noexcept -> __ElementType * {

                    __NodeType * pNewNode           = __DoubleLinkedList :: __dll_allocateNode();
                    pNewNode->_pNext                = const_cast < __NodeType * > ( pCurrent );
                    pNewNode->_pPrevious            = const_cast < __NodeType * > ( pPrevious );

                    if ( pNewNode->_pNext != nullptr ) {
                        pNewNode->_pNext->_pPrevious = pNewNode;
                    } else {
                        this->_pBack = pNewNode;
                    }

                    if ( pNewNode->_pPrevious != nullptr ) {
                        pNewNode->_pPrevious->_pNext = pNewNode;
                    } else {
                        this->_pFront = pNewNode;
                    }

                    ++ this->_size;

                    return & pNewNode->_data;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBetweenNodesArray (
                        __NodeType  const * pPrevious,
                        __NodeType  const * pCurrent,
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void {

                    __NodeType * pChainFront        = __DoubleLinkedList :: __dll_allocateNode();
                    __NodeType * pChainPrevious     = pChainFront;
                    __NodeType * pChainCurrent      = pChainPrevious;

                    for ( Size index = 0U; index + 1U < count; ++ index ) {
                        ppElements [ index ]        = & pChainPrevious->_data;
                        pChainCurrent               = __DoubleLinkedList :: __dll_allocateNode();

                        pChainPrevious->_pNext      = pChainCurrent;
                        pChainCurrent->_pPrevious   = pChainPrevious;

                        pChainPrevious              = pChainCurrent;
                    }

                    ppElements [ count - 1U ] = & pChainCurrent->_data;

                    pChainCurrent->_pNext               = const_cast < __NodeType * > ( pCurrent );
                    pChainFront->_pPrevious             = const_cast < __NodeType * > ( pPrevious );
                    pChainCurrent->_pNext->_pPrevious   = pChainCurrent;
                    pChainFront->_pPrevious->_pNext     = pChainFront;

                    this->_size += count;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBefore (
                        AbstractBidirectionalNodeIterator < __ElementType > const & iterator
                ) noexcept -> __ElementType * {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ) {
                        return nullptr;
                    }

                    if ( iterator._pCurrentNode == this->_pFront && iterator._pPreviousNode == nullptr ) {
                        return this->__dll_newFront ();
                    }

                    if ( iterator._pCurrentNode == nullptr && iterator._pPreviousNode == this->_pBack ) {
                        return this->__dll_newBack ();
                    }

                    return this->__dll_newBetweenNodes (
                            iterator._pPreviousNode,
                            iterator._pCurrentNode
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBeforeConst (
                        AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
                ) noexcept -> __ElementType * {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ) {
                        return nullptr;
                    }

                    if ( iterator._pCurrentNode == this->_pFront && iterator._pPreviousNode == nullptr ) {
                        return this->__dll_newFront ();
                    }

                    if ( iterator._pCurrentNode == nullptr && iterator._pPreviousNode == this->_pBack ) {
                        return this->__dll_newBack ();
                    }

                    return this->__dll_newBetweenNodes (
                            iterator._pPreviousNode,
                            iterator._pCurrentNode
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newAfter (
                        AbstractBidirectionalNodeIterator < __ElementType > const & iterator
                ) noexcept -> __ElementType * {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ) {
                        return nullptr;
                    }

                    if ( iterator._pCurrentNode == this->_pFront && this->_pBack == this->_pFront ) {
                        return this->__dll_newBack ();
                    }

                    return this->__dll_newBetweenNodes (
                            iterator._pCurrentNode,
                            iterator._pCurrentNode->_pNext
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newAfterConst (
                        AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
                ) noexcept -> __ElementType * {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ) {
                        return nullptr;
                    }

                    if ( iterator._pCurrentNode == this->_pFront && this->_pBack == this->_pFront ) {
                        return this->__dll_newBack ();
                    }

                    return this->__dll_newBetweenNodes (
                            iterator._pCurrentNode,
                            iterator._pCurrentNode->_pNext
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBeforeArray (
                        AbstractBidirectionalNodeIterator < __ElementType > const & iterator,
                        Size                                                        count,
                        __ElementType                                            ** ppElements
                ) noexcept -> bool {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ) {
                        return false;
                    }

                    if ( iterator._pCurrentNode == this->_pFront && iterator._pPreviousNode == nullptr ) {
                        this->__dll_newFrontArray (
                                count,
                                ppElements
                        );

                    } else if ( iterator._pCurrentNode == nullptr && iterator._pPreviousNode == this->_pBack ) {
                        this->__dll_newBackArray (
                                count,
                                ppElements
                        );

                    } else {
                        this->__dll_newBetweenNodesArray (
                                iterator._pPreviousNode,
                                iterator._pCurrentNode,
                                count,
                                ppElements
                        );
                    }

                    return true;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newBeforeArrayConst (
                        AbstractBidirectionalNodeConstIterator < __ElementType >    const & iterator,
                        Size                                                                count,
                        __ElementType                                                    ** ppElements
                ) noexcept -> bool {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ) {
                        return false;
                    }

                    if ( iterator._pCurrentNode == this->_pFront && iterator._pPreviousNode == nullptr ) {
                        this->__dll_newFrontArray (
                                count,
                                ppElements
                        );

                    } else if ( iterator._pCurrentNode == nullptr && iterator._pPreviousNode == this->_pBack ) {
                        this->__dll_newBackArray (
                                count,
                                ppElements
                        );

                    } else {
                        this->__dll_newBetweenNodesArray (
                                iterator._pPreviousNode,
                                iterator._pCurrentNode,
                                count,
                                ppElements
                        );
                    }

                    return true;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newAfterArray (
                        AbstractBidirectionalNodeIterator < __ElementType > const & iterator,
                        Size                                                        count,
                        __ElementType                                            ** ppElements
                ) noexcept -> bool {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr || iterator._pPreviousNode == nullptr ) {
                        return false;
                    }

                    this->__dll_newBetweenNodesArray (
                            iterator._pPreviousNode->_pPrevious,
                            iterator._pCurrentNode->_pPrevious,
                            count,
                            ppElements
                    );

                    return true;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_newAfterArrayConst (
                        AbstractBidirectionalNodeConstIterator < __ElementType >    const & iterator,
                        Size                                                                count,
                        __ElementType                                                    ** ppElements
                ) noexcept -> bool {

                    if ( this->__dll_empty() || iterator._pCurrentNode == nullptr || iterator._pPreviousNode == nullptr ) {
                        return false;
                    }

                    this->__dll_newBetweenNodesArray (
                            iterator._pPreviousNode->_pPrevious,
                            iterator._pCurrentNode->_pPrevious,
                            count,
                            ppElements
                    );

                    return true;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_begin () noexcept -> __dll_Iterator {

                    return __dll_Iterator (
                            nullptr,
                            this->_pFront
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_end () noexcept -> __dll_Iterator {

                    return __dll_Iterator (
                            this->_pBack,
                            nullptr
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_cbegin () const noexcept -> __dll_ConstIterator {

                    return __dll_ConstIterator (
                            nullptr,
                            this->_pFront
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_cend () const noexcept -> __dll_ConstIterator {

                    return __dll_ConstIterator (
                            this->_pBack,
                            nullptr
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_rbegin () noexcept -> __dll_ReverseIterator {

                    return __dll_ReverseIterator (
                            nullptr,
                            this->_pBack
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_rend () noexcept -> __dll_ReverseIterator {

                    return __dll_ReverseIterator (
                            this->_pFront,
                            nullptr
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_crbegin () const noexcept -> __dll_ConstReverseIterator {

                    return __dll_ConstReverseIterator (
                            nullptr,
                            this->_pBack
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_crend () const noexcept -> __dll_ConstReverseIterator {

                    return __dll_ConstReverseIterator (
                            this->_pFront,
                            nullptr
                    );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_copy (
                        __DoubleLinkedList const & list
                ) noexcept -> void {

                    this->__dll_clear();
                    this->__dll_copyCleared ( list );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_move (
                        __DoubleLinkedList && list
                ) noexcept -> void {

                    this->__dll_clear();
                    this->__dll_moveCleared ( std :: move ( list ) );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_copyCleared (
                        __DoubleLinkedList const & list
                ) noexcept -> void {

                    __NodeType * pOtherHead = list._pFront;
                    while ( pOtherHead != nullptr ) {

                        __NodeType * pNewNode = __DoubleLinkedList :: __dll_allocateNode();
                        new ( & pNewNode->_data ) __ElementType ( pOtherHead->_data );
                        pNewNode->_pNext        = nullptr;
                        pNewNode->_pPrevious    = this->_pBack;

                        if ( this->_pBack == nullptr ) {
                            this->_pFront = pNewNode;
                        } else {
                            this->_pBack->_pNext = pNewNode;
                        }

                        this->_pBack = pNewNode;
                        pOtherHead = pOtherHead->_pNext;
                    }

                    this->_size = list._size;
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_moveCleared (
                        __DoubleLinkedList && list
                ) noexcept -> void {

                    this->_pFront   = cds :: exchange ( list._pFront, nullptr );
                    this->_pBack    = cds :: exchange ( list._pBack, nullptr );
                    this->_size     = cds :: exchange ( list._size, 0ULL );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_equals (
                        __DoubleLinkedList const & list
                ) const noexcept -> bool {

                    if ( this->_pFront == list._pFront ) {
                        return true;
                    }

                    if ( this->_pFront == nullptr || list._pFront == nullptr || this->_size != list._size ) {
                        return false;
                    }

                    auto thisFront  = this->_pFront;
                    auto otherFront = list._pFront;

                    while ( thisFront != nullptr ) {

                        if ( ! __equals ( thisFront->_data, otherFront->_data ) ) {
                            return false;
                        }

                        thisFront   = thisFront->_pNext;
                        otherFront  = otherFront->_pNext;
                    }

                    return true;
                }


                namespace __mergeSortHelpers {  /* NOLINT(bugprone-reserved-identifier) */

                    template <
                            typename __ElementType
                    > __CDS_OptimalInline auto __bidirectionalNodeMergeSortMidNode (
                            cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType > * pHead
                    ) noexcept -> cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType > * {

                        auto pMid = pHead;
                        pHead = pHead->_pNext;
                        while ( pHead != nullptr ) {
                            pHead = pHead->_pNext;
                            if ( pHead != nullptr ) {
                                pHead   = pHead->_pNext;
                                pMid    = pMid->_pNext;
                            }
                        }

                        return pMid;
                    }


                    template <
                            typename __ElementType,
                            typename __Comparator
                    > __CDS_OptimalInline auto __bidirectionalNodeMergeSortMergeSortedLists (
                            cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >        * pLeft,
                            cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >        * pRight,
                            __Comparator                                                        const & comparator
                    ) noexcept -> cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType > * {

                        if ( pLeft == nullptr ) {
                            return pRight;
                        }

                        if ( pRight == nullptr ) {
                            return pLeft;
                        }

                        decltype ( pLeft ) pFinalFront  = nullptr;
                        decltype ( pLeft ) pFinalBack;
                        decltype ( pLeft ) pToAdd;
                        while ( pLeft != nullptr && pRight != nullptr ) {

                            if ( comparator ( pLeft->_data, pRight->_data ) ) {
                                pToAdd  = pLeft;
                                pLeft   = pLeft->_pNext;
                            } else {
                                pToAdd  = pRight;
                                pRight  = pRight->_pNext;
                            }

                            if ( pFinalFront == nullptr ) {

                                pFinalFront         = pToAdd;
                                pFinalBack          = pToAdd;
                                pToAdd->_pNext      = nullptr;
                                pToAdd->_pPrevious  = nullptr;
                            } else {

                                pFinalBack->_pNext  = pToAdd;
                                pToAdd->_pPrevious  = pFinalBack;
                                pFinalBack          = pToAdd;
                            }
                        }

                        while ( pLeft != nullptr ) {

                            pToAdd              = pLeft;
                            pLeft               = pLeft->_pNext;
                            pFinalBack->_pNext  = pToAdd;
                            pToAdd->_pPrevious  = pFinalBack;
                            pFinalBack          = pToAdd;
                        }

                        while ( pRight != nullptr ) {

                            pToAdd              = pRight;
                            pRight              = pRight->_pNext;
                            pFinalBack->_pNext  = pToAdd;
                            pToAdd->_pPrevious  = pFinalBack;
                            pFinalBack          = pToAdd;
                        }

                        pFinalBack->_pNext = nullptr;
                        return pFinalFront;
                    }


                    template <
                            typename __ElementType,
                            typename __Comparator
                    > auto __bidirectionalNodeMergeSort (
                            cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >        * pHead,
                            __Comparator                                                        const & comparator
                    ) noexcept -> cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType > * {

                        if ( pHead == nullptr || pHead->_pNext == nullptr ) {
                            return pHead;
                        }

                        auto pMid       = __bidirectionalNodeMergeSortMidNode ( pHead );
                        auto pSplit     = pMid->_pNext;
                        pMid->_pNext    = nullptr;

                        return __bidirectionalNodeMergeSortMergeSortedLists (
                                __bidirectionalNodeMergeSort < __ElementType > ( pHead, comparator ),
                                __bidirectionalNodeMergeSort < __ElementType > ( pSplit, comparator ),
                                comparator
                        );
                    }

                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __Comparator
                > __CDS_OptimalInline auto __DoubleLinkedList <
                        __ElementType,
                        __equals
                > :: __dll_sort (
                        __Comparator const & comparator
                ) noexcept -> void {

                    this->_pFront = __mergeSortHelpers :: __bidirectionalNodeMergeSort (
                            this->_pFront,
                            comparator
                    );

                    auto pHead      = this->_pFront;
                    this->_pBack    = nullptr;
                    while ( pHead != nullptr ) {
                        this->_pBack    = pHead;
                        pHead           = pHead->_pNext;
                    }
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_DOUBLE_LINKED_LIST_IMPL_HPP__ */
