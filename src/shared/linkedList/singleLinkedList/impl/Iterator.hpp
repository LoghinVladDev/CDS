//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_SINGLE_LINKED_LIST_ITERATOR_IMPL_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: SingleLinkedListIterator () noexcept = default;


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: SingleLinkedListIterator (
                    NodeType * pPrevious,
                    NodeType * pCurrent
            ) noexcept :
                    _pPrevious ( pPrevious ),
                    _pCurrent ( pCurrent ) {

            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: SingleLinkedListIterator (
                    SingleLinkedListIterator const & iterator
            ) noexcept :
                    _pPrevious ( iterator._pPrevious ),
                    _pCurrent ( iterator._pCurrent ) {

            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: SingleLinkedListIterator (
                    SingleLinkedListIterator && iterator
            ) noexcept :
                    _pPrevious ( cds :: exchange ( iterator._pPrevious, nullptr ) ),
                    _pCurrent ( cds :: exchange ( iterator._pCurrent, nullptr ) ) {

            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: operator = (
                    SingleLinkedListIterator const & iterator
            ) noexcept -> SingleLinkedListIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pPrevious    = iterator._pPrevious;
                this->_pCurrent     = iterator._pCurrent;

                return * this;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: operator = (
                    SingleLinkedListIterator && iterator
            ) noexcept -> SingleLinkedListIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pPrevious    = cds :: exchange ( iterator._pPrevious, nullptr );
                this->_pCurrent     = cds :: exchange ( iterator._pCurrent, nullptr );

                return * this;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: currentNode () const noexcept -> NodeType * {

                return this->_pCurrent;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: previousNode () const noexcept -> NodeType * {

                return this->_pPrevious;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: operator ++ () noexcept -> SingleLinkedListIterator & {

                this->_pPrevious    = this->_pCurrent;
                this->_pCurrent     = this->_pCurrent->_pNext;
                return * this;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: operator * () const noexcept -> SingleLinkedList :: ElementType & {

                return this->_pCurrent->_data.data();
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: operator == (
                    SingleLinkedListIterator const & iterator
            ) const noexcept -> bool {

                return this->_pCurrent == iterator._pCurrent;
            }


            template <
                    typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementEquals,   // NOLINT(bugprone-reserved-identifier)
                    typename __ElementDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __SingleLinkedList <
                    __ElementType,
                    __ElementEquals,
                    __ElementDestruct
            > :: SingleLinkedListIterator :: operator != (
                    SingleLinkedListIterator const & iterator
            ) const noexcept -> bool {

                return this->_pCurrent != iterator._pCurrent;
            }

        }
    }
}

#endif // __CDS_SHARED_SINGLE_LINKED_LIST_ITERATOR_IMPL_HPP__
