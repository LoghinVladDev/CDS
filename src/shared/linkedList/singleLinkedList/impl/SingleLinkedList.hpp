//
// Created by loghin on 6/24/22.
//

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__
#define __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_allocateNode () const noexcept -> __NodeType * {

                return __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __NodeType > ();
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_freeNode (
                    __NodeType * pNode
            ) noexcept -> void {

                this->_destruct ( pNode->_data.data() );
                __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_begin () noexcept -> SingleLinkedListIterator {

                return SingleLinkedListIterator (
                        nullptr,
                        this->_pFront
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_end () noexcept -> SingleLinkedListIterator {

                return SingleLinkedListIterator (
                        nullptr,
                        nullptr
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_cbegin () const noexcept -> SingleLinkedListConstIterator {

                return SingleLinkedListConstIterator (
                        nullptr,
                        this->_pFront
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_cend () const noexcept -> SingleLinkedListConstIterator {

                return SingleLinkedListConstIterator (
                        nullptr,
                        nullptr
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __SingleLinkedList () noexcept = default;


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            >
            template < typename __ElementCopy > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __SingleLinkedList (
                    __SingleLinkedList  const & list,
                    __ElementCopy       const & copyFunction
            ) noexcept {

                this->__sll_copyFrom (
                        list,
                        copyFunction
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __SingleLinkedList (
                    __SingleLinkedList && list
            ) noexcept {

                this->__sll_moveFrom (
                        std :: move ( list )
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_clear () noexcept -> void {

                while ( this->_pFront != nullptr ) {
                    this->__sll_freeNode ( cds :: exchange ( this->_pFront, this->_pFront->_pNext ) );
                }

                this->_pBack = nullptr;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_empty () const noexcept -> bool {

                return this->_pFront == nullptr;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_newFront () noexcept -> __ElementType * {

                auto pNewNode       = this->__sll_allocateNode();
                pNewNode->_pNext    = this->_pFront;
                this->_pFront       = pNewNode;

                if ( this->_pBack == nullptr ) {
                    this->_pBack = pNewNode;
                }

                return & pNewNode->_data.data();
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_newBack () noexcept -> __ElementType * {

                auto pNewNode       = this->__sll_allocateNode();
                pNewNode->_pNext    = nullptr;

                if ( this->_pBack != nullptr ) {
                    this->_pBack->_pNext = pNewNode;
                }

                this->_pBack = pNewNode;

                return & pNewNode->_data.data();
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_remove (
                    __ElementType const & element
            ) noexcept -> bool {

                if ( this->__sll_empty() ) {
                    return false;
                }

                if ( this->_equals ( element, this->_pFront->_data.data() ) ) {

                    this->__sll_freeNode ( cds :: exchange ( this->_pFront, this->_pFront->_pNext ) );
                    if ( this->_pFront == nullptr ) {
                        this->_pBack = nullptr;
                    }

                    return true;
                }

                auto pHead = this->_pFront;
                while ( pHead->_pNext != nullptr ) {

                    if ( this->_equals ( pHead->_pNext->_data.data(), element ) ) {

                        this->__sll_freeNode ( cds :: exchange ( pHead->_pNext, pHead->_pNext->_pNext ) );
                        if ( pHead->_pNext == nullptr ) {
                            this->_pBack = pHead;
                        }

                        return true;
                    }

                    pHead = pHead->_pNext;
                }

                return false;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_remove (
                    SingleLinkedListIterator const & iterator
            ) noexcept -> bool {

                if ( iterator.currentNode() == nullptr ) {
                    return false;
                }

                if ( iterator.previousNode() == nullptr ) {

                    this->__sll_freeNode ( cds :: exchange ( this->_pFront, this->_pFront->_pNext ) );
                    if ( this->_pFront == nullptr ) {
                        this->_pBack = nullptr;
                    }

                    return true;
                }

                this->__sll_freeNode ( cds :: exchange ( iterator.previousNode()->_pNext, iterator.currentNode()->_pNext ) );
                if ( iterator.previousNode()->_pNext == nullptr ) {
                    this->_pBack = nullptr;
                }

                return true;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_remove (
                    SingleLinkedListConstIterator const & iterator
            ) noexcept -> bool {

                return this->__sll_remove (
                        SingleLinkedListIterator (
                                const_cast < __NodeType * > ( iterator.previousNode() ),
                                const_cast < __NodeType * > ( iterator.currentNode() )
                        )
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_equals (
                    __SingleLinkedList const & list
            ) const noexcept -> bool {

                if ( this == & list || this->_pFront == list._pFront ) {
                    return true;
                }

                if ( this->__sll_empty() || list.__sll_empty() ) {
                    return false;
                }

                auto pThisHead  = this->_pFront;
                auto pOtherHead = list._pFront;

                while ( pThisHead != nullptr && pOtherHead != nullptr ) {

                    if ( ! this->_equals ( pThisHead->_data.data(), pOtherHead->_data.data() ) ) {
                        return false;
                    }

                    pThisHead   = pThisHead->_pNext;
                    pOtherHead  = pOtherHead->_pNext;
                }

                if ( pThisHead != nullptr || pOtherHead != nullptr ) {
                    return false;
                }

                return true;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            >
            template < typename __ElementCopy > // NOLINT(bugprone-reserved-identifier)
            auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_copyFrom (
                    __SingleLinkedList  const & list,
                    __ElementCopy       const & copyFunction
            ) noexcept -> void {

                auto pListHead = list._pFront;
                while ( pListHead != nullptr ) {

                    auto pNewNode       = this->__sll_allocateNode();
                    pNewNode->_pNext    = nullptr;
                    copyFunction ( pNewNode->_data.data(), pListHead->_data.data() );

                    pListHead = pListHead->_pNext;

                    if ( this->_pBack == nullptr ) {
                        this->_pFront           = pNewNode;
                    } else {
                        this->_pBack->_pNext    = pNewNode;
                    }

                    this->_pBack = pNewNode;
                }
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_moveFrom (
                    __SingleLinkedList && list
            ) noexcept -> void {

                this->_pFront   = cds :: exchange ( list._pFront, nullptr );
                this->_pBack    = cds :: exchange ( list._pBack, nullptr );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            >
            template < typename __ElementCopy > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_assign (
                    __SingleLinkedList  const & list,
                    __ElementCopy       const & copyFunction
            ) noexcept -> void {

                if ( this == & list ) {
                    return;
                }

                this->__sll_clear();
                this->__sll_copyFrom (
                        list,
                        copyFunction
                );
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: __sll_assign (
                    __SingleLinkedList && list
            ) noexcept -> void {

                if ( this == & list ) {
                    return;
                }

                this->__sll_clear();
                this->__sll_moveFrom ( std :: move ( list ) );
            }

        }
    }
}

#endif // __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__
